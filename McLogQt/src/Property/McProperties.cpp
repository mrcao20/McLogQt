#include "include/Property/McProperties.h"

#include <qsettings.h>
#include <qfileinfo.h>
#include <qdir.h>

#include "include/Output/impl/McOutput.h"

#define LEVEL_DEBUG "debug"
#define LEVEL_WARN "warn"
#define LEVEL_CRITICAL "critical"
#define LEVEL_FATAL "fatal"
#define LEVEL_INFO "info"

namespace McLog {

McProperties::McProperties()
{
}

McProperties::~McProperties() {
}

void McProperties::load(const QString& loggerName, QSettings &settings) noexcept {
#ifdef QT_DEBUG
    QString level = "debug-";
    QString console = "debug-";
#else
    QString level = "warn-";
    QString console = "";
#endif // QT_DEBUG

    QStringList levels;
    getValue(levels, settings, loggerName, "level", level);
    initLevel(levels);
    if (levels.isEmpty()) {
        fprintf(stderr,
            QString("level can only set to one of '%1, %2, %3, %4, %5'!!\n")
            .arg(LEVEL_DEBUG, LEVEL_WARN, LEVEL_CRITICAL, LEVEL_FATAL, LEVEL_INFO)
            .toLatin1().data());
        return;
    }
    createOutput(loggerName, levels);
    QStringList consoles;
    getValue(consoles, settings, loggerName, "console", console);
    setOutputIsConsole(consoles, levels);
    setOutputFile(settings, loggerName, levels);
}

void McProperties::getValue(QStringList &list, const QSettings &setting,
    const QString& loggerName, const QString &key, const QString &defaultValue) noexcept {

    QString settingKey = loggerName + "/" + key;
    if(!setting.contains(settingKey))
        settingKey = key;

    list = setting.value(settingKey, defaultValue).toStringList();

    for(int i = 0; i < list.size(); ++i)
        list.replace(i, list.at(i).toLower());
}

QtMsgType McProperties::strToEnum(const QString &level) noexcept {
    if (level == LEVEL_DEBUG)
        return QtMsgType::QtDebugMsg;
    else if (level == LEVEL_WARN)
        return QtMsgType::QtWarningMsg;
    else if (level == LEVEL_CRITICAL)
        return QtMsgType::QtCriticalMsg;
    else if (level == LEVEL_FATAL)
        return QtMsgType::QtFatalMsg;
    else if(level == LEVEL_INFO)
        return QtMsgType::QtInfoMsg;
    return static_cast<QtMsgType>(-1);
}

void McProperties::initLevel(QStringList &levels) noexcept {
    if (levels.size() != 1)
        return;
    if (!levels.at(0).endsWith('-')) {
        if (strToEnum(levels.at(0)) == -1)
            levels.clear();
        return;
    }
    QString level = levels.takeFirst().remove('-');
    levels << level;
    if (level == LEVEL_INFO)
        return;
    levels << LEVEL_INFO;
    if (level == LEVEL_FATAL)
        return;
    levels << LEVEL_FATAL;
    if (level == LEVEL_CRITICAL)
        return;
    levels << LEVEL_CRITICAL;
    if (level == LEVEL_WARN)
        return;
    levels << LEVEL_WARN;
    if (level != LEVEL_DEBUG) {
        levels.clear();
        return;
    }
}

void McProperties::createOutput(const QString& loggerName, const QStringList &levels) noexcept {
    for (const QString &level : levels) {
        QtMsgType type = strToEnum(level);
        if (type == -1)
            continue;
        insert(type, new McOutput(loggerName, level));
    }
}

void McProperties::setOutputIsConsole(QStringList &consoles, const QStringList &levels) noexcept {
    if (consoles.isEmpty())
        return;
    initLevel(consoles);
    for (const QString &con : consoles) {
        if (!levels.contains(con))
            continue;
        QtMsgType type = strToEnum(con);
        if (type == -1)
            continue;
        QFile *file = new QFile();
        if (!file->open(stdout, QIODevice::WriteOnly)) {
            fprintf(stderr, "QFile connot open stdout\n");
            continue;
        }
        value(type)->addFileDevice(file);
    }
}

void McProperties::setOutputFile(const QSettings &setting, const QString& loggerName, const QStringList &levels) noexcept {
    QHash<QString, std::tuple<QString, bool, qint64>> existsFileInfo;
    QString commonPath = setting.value("file", "").toString();
    for (const QString &level: levels) {
        QString key = loggerName + "/" + level + "/file";
        if(!setting.contains(key)){
            key = loggerName + "/file";
            if(!setting.contains(key))
                key = level + "/file";
        }
        QString logPath = setting.value(key, "").toString();
        if (logPath.isEmpty() && (logPath = commonPath).isEmpty())
            continue;
        QtMsgType type = strToEnum(level);
        if (type == -1)
            continue;
        bool ret = checkFilePath(logPath);
        Q_ASSERT_X(ret, "checkFilePath", "cannot create log dir");
        std::tuple<QString, bool, qint64> fileInfo;
        if (existsFileInfo.contains(logPath))
            fileInfo = existsFileInfo[logPath];
        else {
            bool isAppend = isFileAppend(setting, loggerName, level);
            // TODO: 这里的文件最大长度暂时固定为10MB，后续调整为配置文件设置
            fileInfo = std::tuple<QString, bool, qint64>(logPath, isAppend, 10240);
            existsFileInfo.insert(logPath, fileInfo);
        }
        IMcOutput *output = value(type);
        output->addFileDevice(std::get<0>(fileInfo), std::get<1>(fileInfo), std::get<2>(fileInfo));
    }
}

bool McProperties::isFileAppend(const QSettings &setting, const QString& loggerName, const QString &level) noexcept {
    bool commonAppend = setting.value("append", false).toBool();
    bool isAppend = false;
    QString key = loggerName + "/" + level + "/append";
    if(!setting.contains(key))
        key = level + "/append";
    if (setting.contains(key))
        isAppend = setting.value(key, false).toBool();
    else
        isAppend = commonAppend;

    return isAppend;
}

// TODO()后续应该移动到Output中
bool McProperties::checkFilePath(const QString &filePath) noexcept {
    QFileInfo fileInfo(filePath);
    if (fileInfo.exists())  // 不管指定的是文件还是文件夹，如果存在，则直接返回
        return true;
    QDir dir(filePath); // 假定为文件夹
    if(!filePath.endsWith('/')) {
        dir = fileInfo.absoluteDir();
    }
    if (dir.exists())
        return true;
    if (dir.mkpath(dir.absolutePath()))
        return true;
    fprintf(stderr, "failed to create path named '%s'\n", dir.absolutePath().toLocal8Bit().data());
    return false;
}

}
