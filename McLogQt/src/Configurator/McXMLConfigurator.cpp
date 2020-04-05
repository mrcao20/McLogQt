#include "include/Configurator/McXMLConfigurator.h"

#include <QCoreApplication>
#include <QDir>
#include <QThread>

#include <ApplicationContext/impl/McLocalPathApplicationContext.h>

#include "include/McLogManager.h"
#include "include/Repository/IMcLoggerRepository.h"

McXMLConfigurator::McXMLConfigurator() {
}

void McXMLConfigurator::configure(const QString &path, const QString &beanName) noexcept {
    McXMLConfigurator configurator;
    configurator.doConfigure(path, beanName);
}

void McXMLConfigurator::doConfigure(const QString &path, const QString &beanName) noexcept {
    auto xmlPath = QDir::toNativeSeparators(path);
    QString sep = ".";
    sep += QDir::separator();
    if(xmlPath.startsWith(sep)) {
        xmlPath.remove(0, 1);
        xmlPath = qApp->applicationDirPath() + xmlPath;
    }
    
    QThread *thread = new QThread();    //!< 此线程将在LoggerRepository被析构时退出和销毁
    McLocalPathApplicationContextPtr appContext = 
            McLocalPathApplicationContextPtr::create(xmlPath);
    appContext->refresh(thread);
    
    auto rep = appContext->getBean<IMcLoggerRepository>(beanName);
    McLogManager::instance()->setLoggerRepository(rep);
    
    thread->start();
}
