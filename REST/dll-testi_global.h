#ifndef DLLTESTI_GLOBAL_H
#define DLLTESTI_GLOBAL_H


#include <QtCore/qglobal.h>

#if defined(DLLTESTI_LIBRARY)
#define DLLTESTI_EXPORT Q_DECL_EXPORT
#else
#define DLLTESTI_EXPORT Q_DECL_IMPORT
#endif

#endif // DLLTESTI_GLOBAL_H
