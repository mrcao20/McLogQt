#include "McLoggerRepository.h"

#include "McLogger.h"
#include "McProperties.h"
#include "IMcOutput.h"

namespace McLog {

struct McLoggerRepositoryData {
	IMcLogger *rootLogger{ Q_NULLPTR };
	McProperties loggerProperties;

	void setProperties(const McProperties &properties) {
		clearProperties();
		loggerProperties = properties;
	}

	void clearProperties() {
		qDeleteAll(loggerProperties);
	}

	~McLoggerRepositoryData() {
		clearProperties();
	}
};

McLoggerRepository::McLoggerRepository(QObject *parent)
	: QObject(parent)
	, d(new McLoggerRepositoryData())
{
	d->rootLogger = new McLogger(this);
}

McLoggerRepository::~McLoggerRepository() {
}

void McLoggerRepository::configureLogger(const McProperties &properties) noexcept {
	d->setProperties(properties);
	d->rootLogger->setProperties(d->loggerProperties);
}

IMcLogger *McLoggerRepository::getRootLogger() noexcept {
	return d->rootLogger;
}

}