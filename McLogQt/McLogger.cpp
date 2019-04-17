#include "McLogger.h"

#include "McProperties.h"
#include "IMcOutput.h"
#include "McLoggingEvent.h"

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
		McLoggingEvent *loggingEvent = static_cast<McLoggingEvent *>(event);
		if (!d->properties.contains(loggingEvent->m_msgType))
			return;
		d->properties[loggingEvent->m_msgType]->output(loggingEvent->m_msgLogCtx, loggingEvent->m_msg);
	}
}

}