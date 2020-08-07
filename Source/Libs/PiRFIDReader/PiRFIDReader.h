#ifndef PIRFIDREADER_H
#define PIRFIDREADER_H


#include <QElapsedTimer>
#include <QSerialPort>
#include <QObject>
//#include "pirfidreader_global.h"
#include <QTimer>



class PiRFIDReader : public QObject
{
    Q_OBJECT
//*******************************PROPERTIES***********************************************//
    Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)                 //State
    Q_PROPERTY(QString log READ log WRITE setLog NOTIFY logChanged)                     //Log
    Q_PROPERTY(QString dataCard READ dataCard WRITE setDataCard NOTIFY dataCardChanged) //Data

//*******************************LIST STATE************************************************//
    enum{
        RUNNING,        //Running
        OPENED,         //Port openning
        CLOSED,         //Port closed
        TIMEOUT,        //Timeout
        ERROR           //Error
    }State;


//******************************CONTRUCTOR*************************************************//
public:
    PiRFIDReader(QObject *_parent = nullptr, QString _port = "/dev/ttyS0", int _baudrate = 38400, int _timeout = 3000, int _nextcardtime = 2000);
    ~PiRFIDReader();


//***********************************PUBLIC VAILABLE**************************************//
public:
    QString     serialPort;         //Serial port
    int         baudRate;           //Serial baudrate
    int         timeOut;            //Timeout
    int         timeNextCard;       //Time next same card

//***********************************PUBLIC FUNCTIONS**************************************//
public:
    int         state();
    QString     log();
    QString     dataCard();
    bool        dataCardWrite(QString);
    bool        onCard;


//************************************PUBLIC SLOTS*****************************************//
public slots:
    void ReaderStart();
    void ReaderStop();

//************************************SIGNALS**********************************************//
signals:
    void stateChanged(int);
    void logChanged(QString);
    void dataCardChanged(QString);

//***********************************PRIVATE FUNCTIONS*************************************//
private:
    void setState(int);
    void setLog(QString);
    void setDataCard(QString);
    bool serialPortOpen();
    void serialPortClose();
    void setStateLog(int,QString);
    void serialPortAdd(QString);
    void serialPortSub(QString);
    bool serialPortCheck(QString);

//***********************************PRIVATE*************************************//
private:
    QString         m_oldCard;
    QSerialPort     *p_serial;
    QElapsedTimer   m_timeNextCard;
    int             m_checkHeader;
    QString         m_dataCardTemp;
    int             m_state = -1;
    QString         m_log;
    QString         m_dataCard;
    QElapsedTimer   m_timeCheckConnected;   //time counter when disconnected
    QTimer          *p_timer;
    bool            m_oneCon;   //Connecting one time


//***********************************STATIC PRIVATE****************************************//
private:
    static      QList<QString>  m_serialPorts;  //Store all port using this lib

//***********************************PRIVATE SLOTS****************************************//
private slots:
    void readData();
    void timer_update();

};

#endif // PIRFIDREADER_H
