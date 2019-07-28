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
	QObject *obj = dynamic_cast<QObject *>(getInstance()->m_loggerRepository->getRootLogger());
	if (!obj) {
		fprintf_s(stderr, "logger must be inherit from QObject\n");
		return;
	}
	QEvent *event = new McLoggingEvent(msgType, msgLogCtx, msg);
	qApp->postEvent(obj, event);
}

}
