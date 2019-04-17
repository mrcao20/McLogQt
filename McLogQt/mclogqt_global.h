#ifndef _MC_LOG_QT_GLOBAL_H_
#define _MC_LOG_QT_GLOBAL_H_

#include <QtCore/qglobal.h>

#ifndef BUILD_STATIC
# if defined(MCLOGQT_LIB)
#  define MCLOGQT_EXPORT Q_DECL_EXPORT
# else
#  define MCLOGQT_EXPORT Q_DECL_IMPORT
# endif
#else
# define MCLOGQT_EXPORT
#endif

#endif // !_MC_LOG_QT_GLOBAL_H_