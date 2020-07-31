#include "PiRFIDReader.h"

//******************************STATIC DECLARE****************************//
int         PiRFIDReader::m_oneScan;
int         PiRFIDReader::m_state;
QString     PiRFIDReader::m_log;
QString     PiRFIDReader::m_dataCard;


PiRFIDReader::PiRFIDReader(QObject *_parent, QString _port, int _baudrate, int _timeout, int _timenextcard) :
    QThread(_parent),
    serialPort(_port),
    baudRate(_baudrate),
    timeOut(_timeout),
    timeNextCard(_timenextcard)
{
}

PiRFIDReader::~PiRFIDReader()
{
    disconnect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
    serialPortClose();
}

int PiRFIDReader::state()
{
    return m_state;
}

QString PiRFIDReader::log()
{
    return m_log;
}

void PiRFIDReader::ReaderStart()
{
    this->m_stopScan = false;
    this->start();
}

void PiRFIDReader::ReaderStop()
{
    this->m_stopScan = true;
}

void PiRFIDReader::run()
{
    if(m_oneScan != 1)
    {
        QElapsedTimer timer;
        timer.start();

        //Check connection time out
        while(timer.elapsed()< timeOut)
        {
            if(serialPortOpen())
            {
                connect(serial, SIGNAL(readyRead()), this, SLOT(readData()));
                setStateLog(RUNNING,"Reader is running");
                break;
            }
            else {
                serialPortClose();

            }
        }
        setStateLog(TIMEOUT,serialPort+" open is time out");
    }
    else
    {
        setLog("Device has connected");
    }
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
    serial->close();
    setStateLog(CLOSED,serialPort+" is Closed");
}

void PiRFIDReader::setStateLog(int state, QString log)
{
    setState(state);
    setLog(log);
}

void PiRFIDReader::readyRead()
{
    if(this->m_stopScan == false)
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
}
