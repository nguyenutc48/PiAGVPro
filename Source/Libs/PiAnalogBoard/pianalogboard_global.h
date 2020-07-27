#ifndef PIANALOGBOARD_GLOBAL_H
#define PIANALOGBOARD_GLOBAL_H

#include <QtCore/qglobal.h>

#if defined(PIANALOGBOARD_LIBRARY)
#  define PIANALOGBOARDSHARED_EXPORT Q_DECL_EXPORT
#else
#  define PIANALOGBOARDSHARED_EXPORT Q_DECL_IMPORT
#endif

#endif // PIANALOGBOARD_GLOBAL_H
