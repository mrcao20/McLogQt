#pragma once

#include <QObject>
#include "../IMcLogger.h"

namespace McLog {

struct McLoggerData;

class McLogger : public QObject, public IMcLogger {
    Q_OBJECT
    Q_DISABLE_COPY(McLogger)

public:
	explicit McLogger(QObject *parent = nullptr);
	virtual ~McLogger() override;

	void setProperties(const McProperties &properties) noexcept override;

protected:
	void customEvent(QEvent *event) override;

private:
	QScopedPointer<McLoggerData> d;
};

}
