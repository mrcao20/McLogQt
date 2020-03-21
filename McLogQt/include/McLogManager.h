#pragma once

#include <QObject>

#include "McLogQt_Global.h"
#include "McGlobal.h"

namespace McLog {

class IMcLoggerRepository;

class MCLOGQT_EXPORT McLogManager : public QObject {
    Q_OBJECT
    Q_DISABLE_COPY(McLogManager)
	McLogManager(QObject *parent = nullptr);

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
