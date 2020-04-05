#include "include/Appender/impl/McRollingFileAppender.h"

#include <QCoreApplication>
#include <QDir>
#include <QDateTime>
#include <QRegularExpression>
#include <QRegularExpressionMatch>

MC_DECL_PRIVATE_DATA(McRollingFileAppender)
QString backupDirPath;
QString backupDirPattern;
MC_DECL_PRIVATE_DATA_END

MC_INIT(McRollingFileAppender)
MC_INIT_END

McRollingFileAppender::McRollingFileAppender() {
    MC_NEW_PRIVATE_DATA(McRollingFileAppender);
}

McRollingFileAppender::~McRollingFileAppender() {
}

QString McRollingFileAppender::backupDirPath() const noexcept {
    return d->backupDirPath;
}

void McRollingFileAppender::setBackupDirPath(const QString &val) noexcept {
    d->backupDirPath = QDir::toNativeSeparators(val);
    QString sep = ".";
    sep += QDir::separator();
    if(d->backupDirPath.startsWith(sep)) {
        d->backupDirPath.remove(0, 1);
        d->backupDirPath = qApp->applicationDirPath() + d->backupDirPath;
    }
}

QString McRollingFileAppender::backupDirPattern() const noexcept {
    return d->backupDirPattern;
}

void McRollingFileAppender::setBackupDirPattern(const QString &val) noexcept {
    d->backupDirPattern = val;
}

void McRollingFileAppender::finished() noexcept {
    if(backupDirPath().isEmpty())
        setBackupDirPath("./backup/");
    if(backupDirPattern().isEmpty())
        setBackupDirPattern("%{time yyyy-MM-dd}");
}

void McRollingFileAppender::tryNextFile() noexcept {
    if(device().isNull()) {
        return;
    }
    
    if(!isNewNextFile()) {
        return;
    }
    
    auto file = device().staticCast<QFile>();
    
    auto mode = file->openMode();
    auto oldFilePath = file->fileName();
    file->close();
    file->setFileName(newFilePath());
    file->open(mode);
    
    auto backupPath = newBackupPath(oldFilePath);
    QDir dir(backupPath);
    if(!dir.exists() && !dir.mkpath(backupPath)) {
        MC_PRINT_ERR("mk the backup path: %s failure.\n", qPrintable(backupPath));
        return;
    }
    QFile::rename(oldFilePath, dir.absoluteFilePath(QFileInfo(oldFilePath).fileName()));
}

QString McRollingFileAppender::newBackupPath(const QString &oldFilePath) const noexcept {
    QRegularExpression re(R"((.*)%\{time (.*?)\}(.*))");
    auto match = re.match(d->backupDirPattern);
    
    QDir dir(d->backupDirPath);
    if(!match.hasMatch()) {
        return dir.absoluteFilePath(d->backupDirPattern);
    }
    
    auto list = match.capturedTexts();
    return dir.absoluteFilePath(list.at(1) 
                                + QFileInfo(oldFilePath).birthTime().toString(list.at(2)) 
                                + list.at(3));
}
