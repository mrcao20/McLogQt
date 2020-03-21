#pragma once

#include "McMacroGlobal.h"

#define MC_SAFE_DELETE(p) (p) ? (delete p, p = Q_NULLPTR) : true

#include <QEvent>

namespace McLog {

enum CustomEventType {
	LoggingEvent = QEvent::Type::User + 1
};

}
