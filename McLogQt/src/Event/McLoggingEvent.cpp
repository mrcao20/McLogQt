#include "include/Event/McLoggingEvent.h"

namespace McLog {

// 静态变量的定义必须在CPP文件中，如果在头文件中，则会出现重复定义的错误
const QEvent::Type McLoggingEvent::eventType = static_cast<QEvent::Type>(QEvent::registerEventType(McLog::CustomEventType::LoggingEvent));

McLoggingEvent::~McLoggingEvent() {
}

}
