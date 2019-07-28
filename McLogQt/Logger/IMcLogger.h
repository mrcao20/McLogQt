#ifndef _I_MC_LOGGER_H_
#define _I_MC_LOGGER_H_

namespace McLog {

class McProperties;

class IMcLogger {
public:
	virtual ~IMcLogger() = default;

	virtual void setProperties(const McProperties &properties) noexcept = 0;
};

}

#endif // !_I_MC_LOGGER_H_

