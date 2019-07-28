#include "McLogger.h"

#include "../../Property/McProperties.h"
#include "../../Output/IMcOutput.h"
#include "../../Event/McLoggingEvent.h"

namespace McLog {

struct McLoggerData {
	McProperties properties;
};

McLogger::McLogger(QObject *parent)
	: QObject(parent)
	, d(new McLoggerData())
{
}

McLogger::~McLogger() {
}

void McLogger::setProperties(const McProperties &properties) noexcept {
	d->properties = properties;
}

void McLogger::customEvent(QEvent *event) {
	if (event->type() == McLog::CustomEventType::LoggingEvent) {
		if (d->properties.isEmpty()) {
			fprintf_s(stderr, "No configuration found, Maybe you can call "
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
