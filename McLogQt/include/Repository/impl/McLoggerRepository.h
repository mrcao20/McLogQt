#pragma once

#include <QObject>
#include "../IMcLoggerRepository.h"

namespace McLog {

struct McLoggerRepositoryData;

class McLoggerRepository : public QObject, public IMcLoggerRepository {
	Q_OBJECT

public:
	explicit McLoggerRepository(QObject *parent = nullptr);
	virtual ~McLoggerRepository();

    void addLogger(const QString& loggerName, IMcLogger* logger) noexcept;
    IMcLogger* getLogger(const QString& loggerName) noexcept;

private:
	QScopedPointer<McLoggerRepositoryData> d;
};

}
