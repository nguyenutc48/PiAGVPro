#ifndef PIGYROREADER_H
#define PIGYROREADER_H

#include "pigyroreader_global.h"
#include <QObject>

class PIGYROREADERSHARED_EXPORT PiGyroReader : public QObject
{
    Q_OBJECT
public:
    PiGyroReader();
};

#endif // PIGYROREADER_H
