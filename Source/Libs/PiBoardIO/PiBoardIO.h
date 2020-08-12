#ifndef PIBOARDIO_H
#define PIBOARDIO_H

//#include "piboardio_global.h"
#include <QThread>
#include <QTimer>
#include <QElapsedTimer>
#include "wiringPi.h"
#include "wiringPiI2C.h"
#include "mcp23017.h"
#include <QVector>
#include <QMap>
#include <QSettings>

#define I2C_START_ADDRESS 100
#define ON  1
#define OFF 0



class PIBoardIO : public QThread
{
    Q_OBJECT
    //*********************************PROPERTIES**********************************************************//
    Q_PROPERTY(QVector<bool> x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(QVector<bool> y READ y WRITE setY NOTIFY yChanged)

    Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString log READ log WRITE setLog NOTIFY logChanged)

public:
    //*********************************CONTRUCTOR**********************************************************//
    PIBoardIO(QObject *parent = nullptr,QString config = "/home/pi/board_config.ini");
    ~PIBoardIO();

    //*************************************PUBLIC**********************************************************//
public:
    QString             configPath;         //Dir config

    //*************************************PUBLIC FUNC*****************************************************//
public:
    int                 state();
    QString             log();
    QVector<bool>       x();                            //Get all input
    QVector<bool>       y();                            //Get all output
    void                setY(QVector<bool>);            //Set list dau ra theo index cuar list truyen vao
    void                setY(int,bool);                 //Set gia tri bien Y
    bool                getY(int);                      //Get 1 dau ra
    void                setX(QVector<bool>);            //Set list dau vao theo index cua list truyen vao
    void                setX(int,bool);                 //Set gia tri bien X
    bool                getX(int);                      //Get 1 dau vao
    void                setY(QMap<int,bool>);           //Set list cac dau ra
    QMap<int,bool>      getX(QVector<int>);             //Get list cac dau vao
    //*************************************SIGNAL**********************************************************//
signals:
    void xChanged(int);
    void yChanged(int);
    void stateChanged(int);
    void logChanged(QString);

    //*************************************PUBLIC SlOT*****************************************************//
public slots:
    void StartScan();
    void StopScan();

    //*************************************STATIC PRIVATE**************************************************//
private:
    static  QVector<bool>       m_x;
    static  QVector<bool>       m_y;
    //*************************************STATIC**********************************************************//
private:
    int                         m_state;
    QString                     m_log;
    int                         m_oneScan;
    int                         m_stopScan;
    QMap<int,int>               m_xAddres;
    QMap<int,int>               m_yAddres;
    QMap<int,QMap<int,int>>     m_mcp23017ListIO;    //<diachii2c<pin_number,typeIO>>
    QMap<int,int>               m_gpioListIO;
    QVector<int>                listMCP23017Addr {0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27};
    bool                        Stop; //Stop scan

    //*************************************PRIVATE*********************************************************//
private:
    void        run();
    void        initSetup(QString);
    void        readConfig(QString);
    void        setState(int);
    void        setLog(QString);
    void        setStateLog(int,QString);

    //*************************************PRIVATE*********************************************************//
private slots:


};

#endif // PIBOARDIO_H
