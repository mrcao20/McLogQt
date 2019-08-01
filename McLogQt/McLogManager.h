#ifndef _MC_LOG_MANAGER_H_
#define _MC_LOG_MANAGER_H_

#include <QObject>

#include "mclogqt_global.h"

#define ROOT_LOGGER "root"

namespace McLog {

class IMcLoggerRepository;

class MCLOGQT_EXPORT McLogManager : public QObject {
	Q_OBJECT;
	Q_DISABLE_COPY(McLogManager);
	McLogManager(QObject *parent = 0);

public:
	~McLogManager();

	static McLogManager *getInstance() noexcept;
	static void installQtMessageHandler() noexcept;
	static void uninstallQtMessageHandler() noexcept;

	IMcLoggerRepository *getLoggerRepository() noexcept;

private:
	static void customMessageHandler(QtMsgType msgType, const QMessageLogContext &msgLogCtx, const QString &msg) noexcept;
	
private:
	static McLogManager *m_instance;

	IMcLoggerRepository *m_loggerRepository{ Q_NULLPTR };
};

}

#endif // !_MC_LOG_MANAGER_H_
