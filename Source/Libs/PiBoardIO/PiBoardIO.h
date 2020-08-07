#ifndef PIBOARDIO_H
#define PIBOARDIO_H

//#include "piboardio_global.h"
#include <QThread>
#include <QTimer>
#include <QElapsedTimer>

class PiIOBoard : public QThread
{
    Q_OBJECT


public:
    PiIOBoard();
};

#endif // PIBOARDIO_H
