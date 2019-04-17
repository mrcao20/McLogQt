#ifndef _MC_LOGGING_EVENT_H_
#define _MC_LOGGING_EVENT_H_

#include <QEvent>

#include <qstring.h>

#include "McGlobal.h"

namespace McLog {

class McLoggingEvent : public QEvent {
public:
	static const QEvent::Type eventType;

	inline McLoggingEvent(QtMsgType msgType, const QMessageLogContext &msgLogCtx, const QString &msg);
	virtual ~McLoggingEvent() = default;
private:
	QtMsgType m_msgType{ static_cast<QtMsgType>(-1) };
	QMessageLogContext m_msgLogCtx;
	QString m_msg;

	friend class McLogger;
};

inline McLoggingEvent::McLoggingEvent(QtMsgType msgType, const QMessageLogContext &msgLogCtx, const QString &msg)
	: QEvent(eventType)
	, m_msgType(msgType)
	, m_msgLogCtx(msgLogCtx.file, msgLogCtx.line, msgLogCtx.function, msgLogCtx.category)
	, m_msg(msg)
{
}

}

#endif // !_MC_LOGGING_EVENT_H_

