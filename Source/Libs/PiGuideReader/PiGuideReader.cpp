#include "PiGuideReader.h"

//******************************STATIC DECLARE****************************//
QList<QString>  PiGuideReader::m_serialPorts;

PiGuideReader::PiGuideReader(QObject *_parent, QString _port, int _baudrate, int _timeout, int _timereconnect):
    QObject (_parent),
    serialPort(_port),
    baudRate(_baudrate),
    timeOut(_timeout),
    timeReconnect(_timereconnect)
{
    m_oneCon = false;
    p_timer = new QTimer(this);
    connect(p_timer, SIGNAL(timeout()), this, SLOT(timer_update()));

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

QString PiGuideReader::dataGuide()
{
    return m_dataGuide;
}

void PiGuideReader::ReaderStart()
{
    if(!m_oneCon){
        if(!serialPortCheck(serialPort))
        {
            m_oneCon = true;
            QElapsedTimer timer;
            int temp = 0;
            timer.start();
            while(timer.elapsed()< timeOut)
            {
                if(serialPortOpen())
                {
                    connect(p_serial, SIGNAL(readyRead()), this, SLOT(readData()));
                    setStateLog(RUNNING,"Reader is running");
                    serialPortAdd(serialPort);
                    p_serial->clear();
                    p_serial->write("\002A1\003");  //send first data request
                    p_timer->start(1000);
                    m_timeCheckConnected.start();
                    temp = 1;
                    break;
                }
                else {
                    serialPortClose();
                }
            }
            if(temp == 0)
                setStateLog(TIMEOUT, serialPort+" open is time out");
            m_oneCon = false;
        }
        else
        {
            setLog("Port has opened");
        }
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

void PiGuideReader::setDataGuide(QString data)
{
    m_dataGuide = data;
    emit dataGuideChanged(m_dataGuide);
}

bool PiGuideReader::serialPortOpen()
{
    p_serial = new QSerialPort();
    p_serial->setPortName(serialPort);
    setLog("Start opening to port "+serialPort);
    if (p_serial->open(QIODevice::ReadWrite))
    {
        if (p_serial->setBaudRate(baudRate) &&
                p_serial->setDataBits(QSerialPort::Data8) &&
                p_serial->setParity(QSerialPort::NoParity) &&
                p_serial->setFlowControl(QSerialPort::NoFlowControl))
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
        p_timer->stop();
        disconnect(p_serial, SIGNAL(readyRead()), this, SLOT(readData()));
        p_serial->close();
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
    m_timeCheckConnected.restart();
    QByteArray data = p_serial->readAll();
    int index_header = data.indexOf('a');
    if(index_header != -1)
    {
        m_dataGuideTemp = data.mid(index_header+1,3);
        setDataGuide(m_dataGuideTemp);
    }
    p_serial->clear();
    p_serial->write("\002A1\003");
    m_timeCheckConnected.start();
}

void PiGuideReader::timer_update()
{
    if(m_timeCheckConnected.elapsed()>timeReconnect)
    {
        this->serialPortClose();
        setLog(serialPort+" Can not read data from guide sensor, please check connection cable");
        m_timeCheckConnected.restart();
    }
}
