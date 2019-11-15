#include "McLogManager.h"

#include <qcoreapplication.h>
#include <qmutex.h>

#include "McGlobal.h"
#include "Repository/impl/McLoggerRepository.h"
#include "Logger/IMcLogger.h"
#include "Event/McLoggingEvent.h"

namespace McLog {

McLogManager *McLogManager::m_instance = Q_NULLPTR;

McLogManager::McLogManager(QObject *parent)
	: QObject(parent)
	, m_loggerRepository(new McLoggerRepository(this))
{
}

McLogManager::~McLogManager(){
}

McLogManager *McLogManager::getInstance() noexcept {
	static QMutex mtx;
	if (!m_instance) {
		QMutexLocker locker(&mtx);
		if (!m_instance) {
			m_instance = new McLogManager(qApp);
		}
	}
	return m_instance;
}

void McLogManager::installQtMessageHandler() noexcept {
	qInstallMessageHandler(customMessageHandler);
}

void McLogManager::uninstallQtMessageHandler() noexcept {
	qInstallMessageHandler(0);
}

IMcLoggerRepository *McLogManager::getLoggerRepository() noexcept {
	return m_loggerRepository;
}

void McLogManager::customMessageHandler(QtMsgType msgType, const QMessageLogContext &msgLogCtx, const QString &msg) noexcept {
    QString log;
    QStringList strList = msg.split(' ');
    QString loggerName = strList.isEmpty() ? "" : strList.at(0);
    if(loggerName.startsWith('"') && loggerName.endsWith('"'))
        loggerName.remove(loggerName.size() - 1, 1).remove(0, 1);
    if(loggerName.isEmpty() || !loggerName.startsWith(':')){
        loggerName = ROOT_LOGGER;
        log = msg;
    }
    else {
        log = msg.right(msg.size() - 1 - msg.indexOf(' '));
        loggerName.remove(0, 1);
    }

    IMcLogger *logger = getInstance()->m_loggerRepository->getLogger(loggerName);
    if(!logger){
        logger = getInstance()->m_loggerRepository->getLogger(ROOT_LOGGER);
        log = msg;
    }
    QObject *obj = dynamic_cast<QObject *>(logger);
	if (!obj) {
        fprintf(stderr, "logger must be inherit from QObject\n");
		return;
	}
    QEvent *event = new McLoggingEvent(msgType, msgLogCtx, log);
	qApp->postEvent(obj, event);
}

}
