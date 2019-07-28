#ifndef _MC_LOGGER_REPOSITORY_H_
#define _MC_LOGGER_REPOSITORY_H_

#include <QObject>
#include "../IMcLoggerRepository.h"

namespace McLog {

struct McLoggerRepositoryData;

class McLoggerRepository : public QObject, public IMcLoggerRepository {
	Q_OBJECT

public:
	explicit McLoggerRepository(QObject *parent = 0);
	virtual ~McLoggerRepository();

	void configureLogger(const McProperties &properties) noexcept;
	IMcLogger *getRootLogger() noexcept;

private:
	QScopedPointer<McLoggerRepositoryData> d;
};

}

#endif // !_MC_LOGGER_REPOSITORY_H_
