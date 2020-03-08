#ifndef MCLOGQT_GLOBAL_H
#define MCLOGQT_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(MCLOGQT_LIB)
#  define MCLOGQT_EXPORT Q_DECL_EXPORT
#else
#  define MCLOGQT_EXPORT Q_DECL_IMPORT
#endif

#endif // MCLOGQT_GLOBAL_H
