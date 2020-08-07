#include "PiGuideReader.h"

//******************************STATIC DECLARE****************************//
QList<QString>  PiGuideReader::m_serialPorts;

PiGuideReader::PiGuideReader(QObject *_parent, QString _port, int _baudrate, int _timeout):
    QObject (_parent),
    serialPort(_port),
    baudRate(_baudrate),
    timeOut(_timeout)
{
}

PiGuideReader::~PiGuideReader()
{
    this->serialPortClose();
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
    if(!serialPortCheck(serialPort))
    {
        QElapsedTimer timer;
        timer.start();
        int temp = 0;

        while(timer.elapsed()< timeOut)
        {
            if(serialPortOpen())
            {
                connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
                setStateLog(RUNNING,"Reader is running");
                serialPortAdd(serialPort);
                temp = 1;
                break;
            }
            else {
                serialPortClose();
            }
        }

        if(temp == 0)
            setStateLog(TIMEOUT, serialPort+" open is time out");
    }
    else
    {
        setLog("Port has opened");
    }
}

void PiGuideReader::ReaderStop()
{
    this->serialPortClose();
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
    if(m_state == RUNNING)
    {
        disconnect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
        serial->close();
        setStateLog(CLOSED,serialPort+" is Closed");
        serialPortSub(serialPort);
    }
}

void PiGuideReader::setStateLog(int state, QString log)
{
    setState(state);
    setLog(log);
}

void PiGuideReader::serialPortAdd(QString _port)
{
    if(!serialPortCheck(_port))
        m_serialPorts.append(_port);
}

void PiGuideReader::serialPortSub(QString _port)
{
    if(serialPortCheck(_port))
        m_serialPorts.removeOne(_port);
}

bool PiGuideReader::serialPortCheck(QString _port)
{
    bool temp = false;
    if(m_serialPorts.size() >= 1)
    {
        for (int i=0; i<m_serialPorts.size(); i++) {
            if (m_serialPorts.at(i) == _port)
                temp = true;
        }
    }
    return temp;
}

void PiGuideReader::readData()
{
    QByteArray data = serial->readAll();
    char check_header = data[0];
    if(m_checkHeader == 1)
    {
        m_dataScan += data;

        if(m_dataScan.size() >= 3)
        {
            if(m_dataScan[0] == '+' || m_dataScan[0] == '-')
            {
                m_dataGuideTemp = m_dataScan.mid(0,2);
            }
            m_dataScan.clear();
            serial->clear();
            serial->write("\002A1\003");
        }
    }
    if(check_header == 'a')
    {
        m_checkHeader = 1;
    }
}
