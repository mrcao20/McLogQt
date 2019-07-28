#ifndef _MC_GLOBAL_H_
#define _MC_GLOBAL_H_

#define MC_SAFE_DELETE(p) (p) ? (delete p, p = Q_NULLPTR) : true

#include <QEvent>

namespace McLog {

enum CustomEventType {
	LoggingEvent = QEvent::Type::User + 1
};

}

#endif // !_MC_GLOBAL_H_