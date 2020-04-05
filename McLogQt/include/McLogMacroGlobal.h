#pragma once

#include <QtCore/qglobal.h>

#if defined(MCLOGQT_LIBRARY)
#  define MCLOGQT_EXPORT Q_DECL_EXPORT
#else
#  define MCLOGQT_EXPORT Q_DECL_IMPORT
#endif

#include <QLoggingCategory>

#define MC_LOGGER(name) QLoggingCategory(name)

#define MC_DEFAULT_LOGGER MC_LOGGER("default")

#define MC_PRINT_ERR(...) \
    fprintf(stderr, __VA_ARGS__); \
    fflush(stderr);
