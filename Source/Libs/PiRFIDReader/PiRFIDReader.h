#ifndef PIRFIDREADER_H
#define PIRFIDREADER_H

#include <QThread>
#include <QElapsedTimer>
#include <QSerialPort>
#include <QObject>
#include "pirfidreader_global.h"



class PIRFIDREADERSHARED_EXPORT PiRFIDReader : public QThread
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
    PiRFIDReader(QObject *_parent = nullptr, QString _port = "/dev/ttyUS0", int _baudrate = 38400, int _timeout = 3000, int _nextcardtime = 2000);
    ~PiRFIDReader();


//***********************************PUBLIC VAILABLE**************************************//
public:
    QString     serialPort;         //Serial port
    int         baudRate;           //Serial baudrate
    int         timeOut;            //Timeout
    int         timeNextCard;       //Time next same card
    bool        onCard;             //Status over card

//***********************************PUBLIC FUNCTIONS**************************************//
public:
    void        run();
    int         state();
    QString     log();
    QString     dataCard();
    bool        dataCardWrite(QString);


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
    QSerialPort     *serial;
    QElapsedTimer   m_timeNextCard;
    int             m_checkHeader;
    QString         m_dataCardTemp;
    int             m_state = -1;
    QString         m_log;
    QString         m_dataCard;


//***********************************STATIC PRIVATE****************************************//
private:
    static      QList<QString>  m_serialPorts;  //Store all port using this lib

//***********************************PRIVATE SLOTS****************************************//
private slots:
    void readData();

};

#endif // PIRFIDREADER_H
