#ifndef _MC_LOGGER_H_
#define _MC_LOGGER_H_

#include <QObject>
#include "../IMcLogger.h"

namespace McLog {

struct McLoggerData;

class McLogger : public QObject, public IMcLogger {
    Q_OBJECT
    Q_DISABLE_COPY(McLogger)

public:
	explicit McLogger(QObject *parent = 0);
	virtual ~McLogger();

	void setProperties(const McProperties &properties) noexcept override;

protected:
	void customEvent(QEvent *event) override;

private:
	QScopedPointer<McLoggerData> d;
};

}

#endif // !_MC_LOGGER_H_
