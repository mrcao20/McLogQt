#include "McProperties.h"

#include <qsettings.h>
#include <qfileinfo.h>
#include <qdir.h>

#include "../Output/impl/McOutput.h"

#define LOGGER_DEBUG "debug"
#define LOGGER_WARN "warn"
#define LOGGER_CRITICAL "critical"
#define LOGGER_FATAL "fatal"
#define LOGGER_INFO "info"

namespace McLog {

McProperties::McProperties()
{
}

McProperties::~McProperties() {
}

void McProperties::load(QSettings &settings) noexcept {
#ifdef QT_DEBUG
	QString section = "DEBUG";
	QString logger = "debug-";
	QString console = "debug-";
#else
	QString section = "RELEASE";
	QString logger = "warn-";
	QString console = "";
#endif // QT_DEBUG

	settings.beginGroup(section);

	QStringList loggers;
	getValue(loggers, settings, "logger", logger);
	initLevel(loggers);
	if (loggers.isEmpty()) {
		fprintf_s(stderr, 
			QString("logger can only set to one of '%1, %2, %3, %4, %5'!!\n")
			.arg(LOGGER_DEBUG, LOGGER_WARN, LOGGER_CRITICAL, LOGGER_FATAL, LOGGER_INFO)
			.toLatin1().data());
		return;
	}
	createOutput(loggers);
	QStringList consoles;
	getValue(consoles, settings, "console", console);
	setOutputIsConsole(consoles, loggers);
	setOutputFile(settings, loggers);

	settings.endGroup();
}

void McProperties::getValue(QStringList &list, const QSettings &setting, 
    const QString &key, const QString &defaultValue) noexcept {

	if (setting.contains(key))
        list = setting.value(key, defaultValue).toStringList();
	else
        list << defaultValue;
}

QtMsgType McProperties::strToEnum(const QString &logger) noexcept {
	if (logger == LOGGER_DEBUG)
		return QtMsgType::QtDebugMsg;
	else if (logger == LOGGER_WARN)
		return QtMsgType::QtWarningMsg;
	else if (logger == LOGGER_CRITICAL)
		return QtMsgType::QtCriticalMsg;
	else if (logger == LOGGER_FATAL)
		return QtMsgType::QtFatalMsg;
	else if(logger == LOGGER_INFO)
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
	if (level == LOGGER_INFO)
		return;
	levels << LOGGER_INFO;
	if (level == LOGGER_FATAL)
		return;
	levels << LOGGER_FATAL;
	if (level == LOGGER_CRITICAL)
		return;
	levels << LOGGER_CRITICAL;
	if (level == LOGGER_WARN)
		return;
	levels << LOGGER_WARN;
	if (level != LOGGER_DEBUG) {
		levels.clear();
		return;
	}
}

void McProperties::createOutput(const QStringList &loggers) noexcept {
	for (const QString &logger : loggers) {
		QtMsgType type = strToEnum(logger);
		if (type == -1)
			continue;
		insert(type, new McOutput(logger));
	}
}

void McProperties::setOutputIsConsole(QStringList &consoles, const QStringList &loggers) noexcept {
	if (consoles.isEmpty())
		return;
	initLevel(consoles);
	for (const QString &con : consoles) {
		if (!loggers.contains(con))
			continue;
		QtMsgType type = strToEnum(con);
		if (type == -1)
			continue;
		QFile *file = new QFile();
		if (!file->open(stdout, QIODevice::WriteOnly)) {
			fprintf_s(stderr, "QFile connot open stdout\n");
			continue;
		}
		value(type)->addFileDevice(file);
	}
}

void McProperties::setOutputFile(const QSettings &setting, const QStringList &loggers) noexcept {
	QHash<QString, QFileDevice *> existsDevice;		// 已经在使用的文件
	QString commonPath = setting.value("file", "").toString();
	for (const QString &logger: loggers) {
		QString logPath = setting.value(logger + "/file", "").toString();
		if (logPath.isEmpty() && (logPath = commonPath).isEmpty())
			continue;
		QtMsgType type = strToEnum(logger);
		if (type == -1)
			continue;
		if (!checkFilePath(logPath))
			continue;
		QFileDevice *fileDevice = nullptr;
		if (existsDevice.contains(logPath))
			fileDevice = existsDevice[logPath];
		else {
			bool isAppend = isFileAppend(setting, logger);
			fileDevice = createFileDevice(logPath, isAppend);
			if (!fileDevice)
				continue;
			existsDevice.insert(logPath, fileDevice);
		}
		IMcOutput *output = value(type);
		output->addFileDevice(fileDevice);
	}
}

bool McProperties::isFileAppend(const QSettings &setting, const QString &logger) noexcept {
	bool commonAppend = setting.value("append", false).toBool();
	bool isAppend = false;
	if (setting.contains(logger + "/append"))
		isAppend = setting.value(logger + "/append", false).toBool();
	else
		isAppend = commonAppend;

	return isAppend;
}

bool McProperties::checkFilePath(const QString &filePath) noexcept {
	QFileInfo fileInfo(filePath);
	if (fileInfo.exists())
		return true;
	QDir dir = fileInfo.absoluteDir();
	if (dir.exists())
		return true;
	if (dir.mkpath(dir.absolutePath()))
		return true;
	fprintf_s(stderr, "failed to create path named '%s'\n", dir.absolutePath().toLocal8Bit().data());
	return false;
}

QFileDevice *McProperties::createFileDevice(const QString &filePath, bool isAppend) noexcept {
	QFile *file = new QFile(filePath);
	QIODevice::OpenMode mode = QIODevice::WriteOnly;
	if (isAppend)
		mode |= QIODevice::Append;
	if (!file->open(mode)) {
		fprintf_s(stderr, "failed to open file named '%s'\n", filePath.toLocal8Bit().data());
		return nullptr;
	}
	return file;
}

}
