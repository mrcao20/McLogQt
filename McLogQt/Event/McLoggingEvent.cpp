#include "McLoggingEvent.h"

namespace McLog {

// ��̬�����Ķ��������CPP�ļ��У������ͷ�ļ��У��������ظ�����Ĵ���
const QEvent::Type McLoggingEvent::eventType = static_cast<QEvent::Type>(QEvent::registerEventType(McLog::CustomEventType::LoggingEvent));

}