#include "McLogger.h"

#include "../../Property/McProperties.h"
#include "../../Output/IMcOutput.h"
#include "../../Event/McLoggingEvent.h"

namespace McLog {

struct McLoggerData {
	McProperties properties;

    void setProperties(const McProperties &properties) {
        clearProperties();
        this->properties = properties;
    }

    void clearProperties() {
        qDeleteAll(properties);
    }

    ~McLoggerData() {
        clearProperties();
    }
};

McLogger::McLogger(QObject *parent)
	: QObject(parent)
	, d(new McLoggerData())
{
}

McLogger::~McLogger() {
}

void McLogger::setProperties(const McProperties &properties) noexcept {
    d->setProperties(properties);
}

void McLogger::customEvent(QEvent *event) {
	if (event->type() == McLog::CustomEventType::LoggingEvent) {
		if (d->properties.isEmpty()) {
            fprintf(stderr, "No configuration found, Maybe you can call "
				"'McPropertyConfigurator::defaultConfigure' do default configuration!!\n");
			return;
		}
		McLoggingEvent *loggingEvent = static_cast<McLoggingEvent *>(event);
		if (!d->properties.contains(loggingEvent->m_msgType))
			return;
		d->properties[loggingEvent->m_msgType]->output(loggingEvent->m_msgLogCtx, loggingEvent->m_msg);
	}
}

}
