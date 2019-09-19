#include "McLoggerRepository.h"

#include <QHash>

#include "../../Property/McProperties.h"
#include "../../Output/IMcOutput.h"
#include "../../Logger/IMcLogger.h"

namespace McLog {

struct McLoggerRepositoryData {
    QHash<QString, IMcLogger *> loggers;

    ~McLoggerRepositoryData(){
        qDeleteAll(loggers);
    }
};

McLoggerRepository::McLoggerRepository(QObject *parent)
	: QObject(parent)
	, d(new McLoggerRepositoryData())
{
}

McLoggerRepository::~McLoggerRepository() {
}

void McLoggerRepository::addLogger(const QString& loggerName, IMcLogger* logger) noexcept{
    d->loggers.insert(loggerName, logger);
}

IMcLogger* McLoggerRepository::getLogger(const QString& loggerName) noexcept{
    if(!d->loggers.contains(loggerName))
        return nullptr;
    return d->loggers.value(loggerName);
}

}
