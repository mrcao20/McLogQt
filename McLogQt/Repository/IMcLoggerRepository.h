#ifndef _I_MC_LOGGER_REPOSITORY_H_
#define _I_MC_LOGGER_REPOSITORY_H_

#include <qglobal.h>

namespace McLog {

class McProperties;
class IMcLogger;

class IMcLoggerRepository {
public:
	virtual ~IMcLoggerRepository() = default;

    virtual void addLogger(const QString& loggerName, IMcLogger* logger) noexcept = 0;
    virtual IMcLogger* getLogger(const QString& loggerName) noexcept = 0;
};

}

#endif // !_I_MC_LOGGER_REPOSITORY_H_

