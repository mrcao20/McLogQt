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
    Event/McLoggingEvent.cpp \
    Logger/impl/McLogger.cpp \
    McLogManager.cpp \
    Output/impl/McOutput.cpp \
    Property/McProperties.cpp \
    Property/McPropertyConfigurator.cpp \
    Repository/impl/McLoggerRepository.cpp

HEADERS += \
        Event/McLoggingEvent.h \
        Logger/IMcLogger.h \
        Logger/impl/McLogger.h \
        McGlobal.h \
        McLogManager.h \
        Output/IMcOutput.h \
        Output/impl/McOutput.h \
        Property/McProperties.h \
        Property/McPropertyConfigurator.h \
        Repository/IMcLoggerRepository.h \
        Repository/impl/McLoggerRepository.h \
        mclogqt_global.h 

unix {
    target.path = /usr/lib
    INSTALLS += target
}
