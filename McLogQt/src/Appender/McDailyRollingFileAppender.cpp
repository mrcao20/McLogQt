#include "McLog/Appender/impl/McDailyRollingFileAppender.h"

#include <QFile>
#include <QFileInfo>
#include <QDateTime>

MC_INIT(McDailyRollingFileAppender)
MC_REGISTER_BEAN_FACTORY(MC_TYPELIST(McDailyRollingFileAppender))
MC_INIT_END

McDailyRollingFileAppender::McDailyRollingFileAppender() 
{
}

bool McDailyRollingFileAppender::isNewNextFile() noexcept 
{
    if(device().isNull()) {
        return false;
    }
    auto file = device().staticCast<QFile>();
    if(!file->isOpen()) {
        return false;
    }
    auto filePath = file->fileName();
    QFileInfo fileInfo(filePath);
    auto dateTime = fileInfo.birthTime();
    if(!dateTime.isValid()) {
        dateTime = fileInfo.metadataChangeTime();
    }
    if(!dateTime.isValid()) {
        qCritical("failed get birth time of the file: %s\n", qPrintable(filePath));
        return true;
    }
    auto curDateTime = QDateTime::currentDateTime();
    return qAbs(curDateTime.daysTo(dateTime)) > 0;
}
