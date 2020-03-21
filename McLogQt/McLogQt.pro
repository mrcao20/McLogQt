#-------------------------------------------------
#
# Project created by QtCreator 2019-07-28T21:26:44
#
#-------------------------------------------------

QT       -= gui

TARGET = McLogQt
TEMPLATE = lib

DEFINES += MCLOGQT_LIB

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    src/Event/McLoggingEvent.cpp \
    src/Logger/McLogger.cpp \
    src/McLogManager.cpp \
    src/Output/McOutput.cpp \
    src/Property/McProperties.cpp \
    src/Property/McPropertyConfigurator.cpp \
    src/Repository/McLoggerRepository.cpp

HEADERS += \
    include/Event/McLoggingEvent.h \
    include/Logger/IMcLogger.h \
    include/Logger/impl/McLogger.h \
    include/McGlobal.h \
    include/McLogManager.h \
    include/McLogQt_Global.h \
    include/McLogVersion.h \
    include/McMacroGlobal.h \
    include/Output/IMcOutput.h \
    include/Output/impl/McOutput.h \
    include/Property/McProperties.h \
    include/Property/McPropertyConfigurator.h \
    include/Repository/IMcLoggerRepository.h \
    include/Repository/impl/McLoggerRepository.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
