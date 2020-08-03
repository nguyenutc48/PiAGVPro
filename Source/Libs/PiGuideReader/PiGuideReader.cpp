#include "PiGuideReader.h"


PiGuideReader::PiGuideReader(QObject *_parent, QString _port, int _baudrate, int _timeout):
    QThread(_parent),
    serialPort(_port),
    baudRate(_baudrate),
    timeOut(_timeout)
{
    m_stopScan = false;
}

int PiGuideReader::state()
{
    return m_state;
}

QString PiGuideReader::log()
{
    return m_log;
}

int PiGuideReader::dataGuide()
{
    return m_dataGuide;
}

void PiGuideReader::ReaderStart()
{
    this->m_stopScan = false;
    this->start();
}

void PiGuideReader::ReaderStop()
{
    this->m_stopScan = true;
    disconnect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
    this->serialPortClose();
}

void PiGuideReader::run()
{
    if(m_oneScan != 1)
    {
        QElapsedTimer timer;
        timer.start();

        //Check connection time out
        while(timer.elapsed()< timeOut)
        {
            m_oneScan = 1;
            if(serialPortOpen())
            {
                connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
                setStateLog(RUNNING,"Reader is running");
                while(!m_stopScan)
                {
                    serial->clear();
                    serial->write("\002A1\003");
                    this->msleep(100);
                }
            }
            else {
                serialPortClose();
            }
        }
        m_oneScan = 0;
        setStateLog(TIMEOUT,serialPort+" open is time out");
    }
    else
    {
        setLog("Device has connected");
    }
}

void PiGuideReader::setState(int data)
{
    m_state = data;
    emit stateChanged(m_state);
}

void PiGuideReader::setLog(QString data)
{
    m_log = data;
    emit logChanged(m_log);
}

void PiGuideReader::setDataGuide(int data)
{
    m_dataGuide = data;
    emit dataGuideChanged(m_dataGuide);
}

bool PiGuideReader::serialPortOpen()
{
    serial->setPortName(serialPort);

    if (serial->open(QIODevice::ReadWrite))
    {
       if (serial->setBaudRate(baudRate) &&
        serial->setDataBits(QSerialPort::Data8) &&
        serial->setParity(QSerialPort::NoParity) &&
        serial->setFlowControl(QSerialPort::NoFlowControl))
       {
            setStateLog(OPENED,serialPort+" is Opened");
            return true;
        }
        else
        {
            setStateLog(ERROR,serialPort+" Cannot setup parameter");
            return false;
        }
    } else {
        setStateLog(ERROR,serialPort+" Canot open this port");
        return  false;
    }
}

void PiGuideReader::serialPortClose()
{
    serial->close();
    setStateLog(CLOSED,serialPort+" is Closed");
}

void PiGuideReader::setStateLog(int state, QString log)
{
    setState(state);
    setLog(log);
}

void PiGuideReader::readData()
{

}
