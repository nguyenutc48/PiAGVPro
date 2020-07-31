#ifndef PIGUIDEREADER_H
#define PIGUIDEREADER_H

#include "piguidereader_global.h"
#include <QThread>

class PIGUIDEREADERSHARED_EXPORT PiGuideReader : public QThread
{
    Q_OBJECT
//*******************************PROPERTIES***********************************************//
    //State
    Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)
    //Logs
    Q_PROPERTY(QString log READ log WRITE setLog NOTIFY logChanged)
    //Guide data
    Q_PROPERTY(int dataGuide READ dataGuide WRITE setDataGuide NOTIFY dataGuideChanged)

//*******************************LIST STATE************************************************//
    enum{
        RUNNING,
        CONNECTED,
        DISCONNECTED,
        TIMEOUT,
        ERROR
    }State;

public:
//******************************CONTRUCTOR*************************************************//
    PiGuideReader(QObject *_parent = nullptr, QString _port = "", int _baudrate = 115200, int _timeout= 3000);
    ~PiGuideReader();

//***********************************PUBLIC VAILABLE**************************************//
public:
    //Cong ket noi
    QString     serialPort;
    //Toc do truyen
    int         baudRate;
    //Thoi gian time out
    int         timeOut;
    //Thoi gian out guide cho phep
    int         timeOutGuide;
    //Trang thai dang co the
    bool        onGuide;

//***********************************PUBLIC FUNCTIONS**************************************//
public:
    //Lay trang thai hien tai
    int         state();
    //Lay log hien tai
    QString     log();
    //Lay ma the doc duoc hien tai
    int     dataGuide();


//************************************SIGNALS**********************************************//
signals:
    //Khi trang thai thay doi
    void stateChanged(int);
    //Khi log thay doi
    void logChanged(QString);
    //Khi the thay doi
    void dataGuideChanged(int);

//***********************************PRIVATE FUNCTIONS*************************************//
private:
    //Bat dau thread
    void run() override;
    //Set trang thai
    void setState(int);
    //Set log
    void setLog(QString);
    //Set rfid card
    void setDataGuide(QString);

//***********************************PRIVATE FUNCTIONS*************************************//
private:
    //Bien dung scan the rfid
    bool        m_stopScan;

//***********************************STATIC PRIVATE****************************************//
private:
    //Khoa trang thai chi cho 1 thread scan the rfid
    static      int         m_oneScan;
    //Trang thai cua thread
    static      int         m_state;
    //Log hien tai
    static      QString     m_log;
    //The hien tai
    static      QString     m_dataGuide;

};

#endif // PIGUIDEREADER_H
