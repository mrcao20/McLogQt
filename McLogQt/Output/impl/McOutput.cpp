#include "McOutput.h"

#include <QFile>
#include <QFileInfo>
#include <QDir>
#include <qdatetime.h>

#define __DATE_TIME__ QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")

namespace McLog {

struct McOutputData {
    QHash<QFile *, qint64> fileDevices;         // 输出到的文件设备, value:设备的最大大小, 单位byte
    QString format;                             // 输出的格式
    QString level;                              // 输出的等级

    ~McOutputData() {
        for (auto device : fileDevices.keys()) {
            device->close();
            device->deleteLater();
        }
    }
};

McOutput::McOutput(const QString &level, QObject *parent)
    : QObject(parent)
    , d(new McOutputData())
{
    d->level = level.toUpper();
    d->format = "[" + d->level + "]:  "
        + "Message:\"%1\"  File:%2  Line:%3  Function:%4  DateTime:%5\n";
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

void McOutput::addFileDevice(const QString &filePath, bool isAppend, qint64 maxLen) noexcept {
    QFile *file = new QFile();
    qint64 maxByteSize = maxLen * 1024;
    QIODevice::OpenMode mode = QIODevice::WriteOnly;
    if (isAppend)
        mode |= QIODevice::Append;
    if(!createNewFile(file, filePath, mode, maxByteSize))
        return;
    d->fileDevices.insert(file, maxByteSize);
}

void McOutput::output(const QMessageLogContext &msgLogCtx, const QString &msg) noexcept {
    // 如果没有定义QT_MESSAGELOGCONTEXT
    if (msgLogCtx.file == Q_NULLPTR
        && msgLogCtx.line == 0
        && msgLogCtx.function == Q_NULLPTR) {
        fprintf(stderr, "in release, need to manual define QT_MESSAGELOGCONTEXT\n");
    }
    QString str = d->format.arg(msg, msgLogCtx.file,
        QString::number(msgLogCtx.line),
        msgLogCtx.function, __DATE_TIME__);
    for (auto file : d->fileDevices.keys()) {
        if(!file->isOpen())
            continue;
        if(!file->isSequential() && file->size() >= d->fileDevices[file]){
            QIODevice::OpenMode mode = file->openMode();
            file->close();
            createNewFile(file, file->fileName(), mode, d->fileDevices[file]);
        }
        file->write(str.toLocal8Bit());
        file->flush();
    }

    if (d->level == "FATAL") {
        abort();
    }
}

QString McOutput::getNewFilePath(const QString& filePath){
    QFileInfo fileInfo(filePath);
    QString dirPath = fileInfo.absolutePath();
    QString suffix = fileInfo.completeSuffix();
    QString baseName = fileInfo.baseName();
    QString newFilePath;
    int num = 1;
    int index = -1;
    if((index = baseName.lastIndexOf("_")) >= 0){
        QString numStr = baseName.right(baseName.size() - index - 1);
        bool ok = false;
        int temp = numStr.toInt(&ok);
        if(ok){
            num = temp + 1;
            baseName = baseName.left(index);
        }
    }
    newFilePath = QString("%1/%2_%3").arg(dirPath, baseName, QString::number(num));
    if(!suffix.isEmpty())
        newFilePath += ("." + suffix);
    return newFilePath;
}

bool McOutput::createNewFile(QFile *file, const QString& filePath, QIODevice::OpenMode mode, qint64 maxLen) noexcept{
    QString newFilePath = filePath;
    while(true){
        newFilePath = getNewFilePath(newFilePath);
        if(QFileInfo(newFilePath).size() < maxLen)
            break;
    }
    file->setFileName(newFilePath);
    if (!file->open(mode)) {
        fprintf(stderr, "failed to open file named '%s'\n", filePath.toLocal8Bit().data());
        return false;
    }
    return true;
}

}
