#ifndef PIWEBREQUEST_GLOBAL_H
#define PIWEBREQUEST_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PIWEBREQUEST_LIBRARY)
#  define PIWEBREQUESTSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PIWEBREQUESTSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PIWEBREQUEST_GLOBAL_H