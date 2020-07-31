#include "PiGuideReader.h"


PiGuideReader::PiGuideReader(QObject *_parent, QString _port, int _baudrate, int _timeout):
    QThread(_parent),
    serialPort(_port),
    baudRate(_baudrate),
    timeOut(_timeout)
{
    m_stopScan = false;
}

void PiGuideReader::run()
{

}
