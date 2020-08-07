#ifndef PIGUIDEREADER_H
#define PIGUIDEREADER_H

//#include "piguidereader_global.h"
#include <QThread>
#include <QSerialPort>
#include <QMutex>
#include <QElapsedTimer>
#include <QObject>
#include <QTimer>


class PiGuideReader : public QObject
{
    Q_OBJECT
//*******************************PROPERTIES***********************************************//
    Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString log READ log WRITE setLog NOTIFY logChanged)
    Q_PROPERTY(QString dataGuide READ dataGuide WRITE setDataGuide NOTIFY dataGuideChanged)

//*******************************LIST STATE************************************************//
    enum{
        RUNNING,
        OPENED,
        CLOSED,
        TIMEOUT,
        ERROR
    }State;

public:
//******************************CONTRUCTOR*************************************************//
    PiGuideReader(QObject *_parent = nullptr, QString _port = "/dev/ttyAMA4", int _baudrate = 115200, int _timeout= 3000, int _timereconnect = 5000);
    ~PiGuideReader();

//***********************************PUBLIC VAILABLE**************************************//
public:
    QString     serialPort;         //Cong ket noi
    int         baudRate;           //Toc do truyen
    int         timeOut;            //Thoi gian time out
    int         timeOutGuide;       //Thoi gian out guide cho phep
    int         timeReconnect;      //Thoi gian cho kiem tra guide co nhan duoc data khong

//***********************************PUBLIC FUNCTIONS**************************************//
public:
    int         state();            //Lay trang thai hien tai
    QString     log();              //Lay log hien tai
    QString     dataGuide();            //Lay ma the doc duoc hien tai

//************************************PUBLIC SLOTS*****************************************//
public slots:
    //start reader
    void ReaderStart();
    void ReaderStop();

//************************************SIGNALS**********************************************//
signals:
    void stateChanged(int);         //Khi trang thai thay doi
    void logChanged(QString);       //Khi log thay doi
    void dataGuideChanged(QString);     //Khi the thay doi

//***********************************PRIVATE FUNCTIONS*************************************//
private:
    void setState(int);             //Set trang thai
    void setLog(QString);           //Set log
    void setDataGuide(QString);         //Set guide index
    bool serialPortOpen();          //Serial port connect
    void serialPortClose();         //close
    void setStateLog(int,QString);  //set state log
    void serialPortAdd(QString);
    void serialPortSub(QString);
    bool serialPortCheck(QString);

//***********************************PRIVATE FUNCTIONS*************************************//
private:
    bool            m_stopScan;     //Bien dung scan the rfid
    QSerialPort     *p_serial;        //Serial port pointer
    int             m_state;        //Trang thai cua thread
    QString         m_log;          //Log hien tai
    QString         m_dataGuide;    //The hien tai
    QString         m_dataGuideTemp;//data tam
    QElapsedTimer   m_timeCheckConnected;   //time counter when disconnected
    QTimer          *p_timer;
    bool            m_oneCon;   //Connecting one time

//***********************************STATIC PRIVATE****************************************//
private:
    static      QList<QString>  m_serialPorts;  //Store all port using this lib

private slots:
    void readData();
    void timer_update();

};

#endif // PIGUIDEREADER_H
