#include "include/Output/impl/McOutput.h"

#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <qdatetime.h>
#include <QTextStream>

#define MC_DATE_TIME QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss,zzz")
#define MC_FILENAME_DATE_TIME QDateTime::currentDateTime().toString("yyyy-MM-dd_hh-mm-ss")

namespace McLog {

struct McOutputData {
    // TODO() 动态指针
    QHash<QFile *, qint64> fileDevices;         // 输出到的文件设备, value:设备的最大大小, 单位byte
    QString format;                             // 输出的格式
    QString level;                              // 输出的等级
    QString prefix;                             // 文件名前缀，通常为loggerName
    QString dirPath;                            // 所在文件夹
    QString suffix;                             // 文件名后缀

    ~McOutputData() {
        for (auto device : fileDevices.keys()) {
            device->close();
            device->deleteLater();
        }
    }
};

McOutput::McOutput(const QString& loggerName, const QString &level, QObject *parent)
    : QObject(parent)
    , d(new McOutputData())
{
    d->level = level.toUpper();
    d->prefix = loggerName;
//    d->format = "[" + d->level + "]:  "
//        + "Message:\"%1\"  File:%2  Line:%3  Function:%4  DateTime:%5\n";
    QTextStream textStream(&d->format);
    textStream << left
               << qSetFieldWidth(0) << "[%1]"
               << qSetFieldWidth(0) << QString("[%1]").arg(loggerName)
               << qSetFieldWidth(12) << QString("[%1]: ").arg(d->level)
               << qSetFieldWidth(0) << "%2  [File:%3] [Line:%4] [Function:%5]\n";
}

McOutput::~McOutput(){
}

void McOutput::addFileDevice(QFile *file, qint64 maxLen) noexcept {
    if (!file)
        return;
    if (d->fileDevices.contains(file))
        return;
    //file->setParent(this);
    d->fileDevices.insert(file, maxLen * 1024);
}

// filePath所在的文件夹一定存在
void McOutput::addFileDevice(const QString &filePath, bool isAppend, qint64 maxLen) noexcept {
    QFileInfo fileInfo(filePath);
    if(fileInfo.isDir()) {
        d->dirPath = filePath;
        d->suffix = ".log";
    } else {
        d->dirPath = fileInfo.absolutePath();
        auto prefix = fileInfo.baseName();
        if(!prefix.isEmpty()) {
            d->prefix = prefix;
        }
        d->suffix = "." + fileInfo.completeSuffix();
        if(d->suffix.size() == 1) {
            d->suffix = ".log";
        }
    }
    
    QFile *file = new QFile();
    qint64 maxByteSize = maxLen * 1024;
    
    d->fileDevices.insert(file, maxByteSize);
    
    QIODevice::OpenMode mode = QIODevice::WriteOnly;
    if (isAppend)
        mode |= QIODevice::Append;
    
    QDir dir(d->dirPath);
    auto fileInfos = dir.entryInfoList(QDir::Files, QDir::Time);    // 获取最新被修改的文件
    if(!fileInfos.isEmpty() && fileInfos.first().size() < maxByteSize) {
        auto fileName = fileInfos.first().fileName();
        if(fileName.startsWith(d->prefix) && fileName.endsWith(d->suffix)) {
            auto path = fileInfos.first().absoluteFilePath();
            openFile(file, path, mode);
            return;
        }
    }
    
    createNewFile(file, mode);
}

void McOutput::output(const QMessageLogContext &msgLogCtx, const QString &msg) noexcept {
    // 如果没有定义QT_MESSAGELOGCONTEXT
    if (msgLogCtx.file == Q_NULLPTR
        && msgLogCtx.line == 0
        && msgLogCtx.function == Q_NULLPTR) {
        fprintf(stderr, "in release, need to manual define QT_MESSAGELOGCONTEXT\n");
    }
    QString str = d->format.arg(MC_DATE_TIME, msg
        , msgLogCtx.file
        , QString::number(msgLogCtx.line)
        , msgLogCtx.function);
    for (auto file : d->fileDevices.keys()) {
        if(!file->isOpen())
            continue;
        if(!file->isSequential() && file->size() >= d->fileDevices[file]){
            QIODevice::OpenMode mode = file->openMode();
            file->close();
            createNewFile(file, mode);
        }
        file->write(str.toLocal8Bit());
        file->flush();
    }

    if (d->level == "FATAL") {
        abort();
    }
}

QString McOutput::getNewFilePath(){
    if(!d->dirPath.endsWith('/')) {
        d->dirPath += '/';
    }
    return QString("%1%2_%3%4").arg(d->dirPath, d->prefix, MC_FILENAME_DATE_TIME, d->suffix);
}

void McOutput::createNewFile(QFile *file, QIODevice::OpenMode mode) noexcept {
    QString newFilePath;
    do {
        newFilePath = getNewFilePath();
    }while(QFileInfo::exists(newFilePath));
    
    openFile(file, newFilePath, mode);
}

void McOutput::openFile(QFile *file, const QString &filePath, QIODevice::OpenMode mode) {
    file->setFileName(filePath);
    if (!file->open(mode)) {
        Q_ASSERT_X(false, "openFile", "open log file failure");
    }
}

}
