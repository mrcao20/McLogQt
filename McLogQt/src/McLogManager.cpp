#include "include/McLogManager.h"

#include <qcoreapplication.h>
#include <qmutex.h>

#include "include/McGlobal.h"
#include "include/Repository/impl/McLoggerRepository.h"
#include "include/Logger/IMcLogger.h"
#include "include/Event/McLoggingEvent.h"

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
    auto loggerName = msgLogCtx.category;

    IMcLogger *logger = getInstance()->m_loggerRepository->getLogger(loggerName);
    if(!logger){
        // 把这两行提取到一个宏中代替
        fprintf(stderr, "not exists logger for named: %s\n", loggerName);
        fflush(stderr);
        return;
    }
    QObject *obj = dynamic_cast<QObject *>(logger);
	if (!obj) {
        fprintf(stderr, "logger must be inherit from QObject\n");
		return;
	}
    QEvent *event = new McLoggingEvent(msgType, msgLogCtx, msg);
	qApp->postEvent(obj, event);
}

}
