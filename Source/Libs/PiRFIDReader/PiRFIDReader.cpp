#include "PiRFIDReader.h"

//******************************STATIC DECLARE****************************//
QList<QString>  PiRFIDReader::m_serialPorts;


PiRFIDReader::PiRFIDReader(QObject *_parent, QString _port, int _baudrate, int _timeout, int _timenextcard) :
    QObject(_parent),
    serialPort(_port),
    baudRate(_baudrate),
    timeOut(_timeout),
    timeNextCard(_timenextcard)
{
}

PiRFIDReader::~PiRFIDReader()
{
    this->serialPortClose();
}



int PiRFIDReader::state()
{
    return m_state;
}

QString PiRFIDReader::log()
{
    return m_log;
}

QString PiRFIDReader::dataCard()
{
    return m_dataCard;
}

bool PiRFIDReader::dataCardWrite(QString _data)
{
    if(m_state == RUNNING)
    {
        int length = _data.size();
        if(length != 4)
            return false;
        else
        {
            QByteArray temp = _data.toLocal8Bit();
            QByteArray dataFrame;
            dataFrame.resize(8);
            dataFrame[0] = 0xaa;
            dataFrame[1] = 0xc2;
            dataFrame[2] = 0x00;
            dataFrame[3] = temp[0];
            dataFrame[4] = temp[1];
            dataFrame[5] = temp[2];
            dataFrame[6] = temp[3];
            dataFrame[7] = 0xbb;
            serial->write(dataFrame);
        }
    }
    return false;
}

void PiRFIDReader::ReaderStart()
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

void PiRFIDReader::ReaderStop()
{
    this->serialPortClose();
}

void PiRFIDReader::setState(int data)
{
    m_state = data;
    emit stateChanged(m_state);
}

void PiRFIDReader::setLog(QString data)
{
    m_log = data;
    emit logChanged(m_log);
}

void PiRFIDReader::setDataCard(QString data)
{
    m_dataCard = data;
    emit dataCardChanged(m_dataCard);
}

bool PiRFIDReader::serialPortOpen()
{
    serial = new QSerialPort();
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

void PiRFIDReader::serialPortClose()
{
    if(m_state == RUNNING)
    {
        disconnect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
        serial->close();
        setStateLog(CLOSED,serialPort+" is Closed");
        serialPortSub(serialPort);
    }
}

void PiRFIDReader::setStateLog(int state, QString log)
{
    setState(state);
    setLog(log);
}

void PiRFIDReader::serialPortAdd(QString _port)
{
    if(!serialPortCheck(_port))
        m_serialPorts.append(_port);
}

void PiRFIDReader::serialPortSub(QString _port)
{
    if(serialPortCheck(_port))
        m_serialPorts.removeOne(_port);
}

bool PiRFIDReader::serialPortCheck(QString _port)
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

void PiRFIDReader::readData()
{
    if(m_timeNextCard.elapsed()<timeNextCard)
        m_timeNextCard.restart();
    else {
        m_oldCard = "";
        m_timeNextCard.restart();
    }
    m_timeNextCard.start();
    QByteArray data = serial->readAll();
    char check_header = data[0];
    if(m_checkHeader == 1)
    {
        if(check_header != 187)
        {
            if(check_header != 170)
                m_dataCardTemp += data[0];
        }
        else
        {
            if(m_dataCardTemp.length() == 4)
            {
                if(m_dataCardTemp != m_oldCard)
                {
                    m_oldCard = m_dataCardTemp;
                    setDataCard(m_dataCardTemp);
                }

            }
            m_dataCardTemp = "";
            check_header = 0;
        }

    }
    if(check_header == 170)
    {
        m_checkHeader = 1;
    }
    m_timeNextCard.start();

}
