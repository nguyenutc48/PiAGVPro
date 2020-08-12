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

public:
    //*********************************CONTRUCTOR**********************************************************//
    PIBoardIO(QObject *parent = nullptr,QString config = "/home/pi/board_config.ini");
    ~PIBoardIO();

    //*************************************PUBLIC**********************************************************//
public:
    QString             configPath;         //Dir config
    QVector<QString>    listICSupport {"mcp23017","mcp23s17"};
    QVector<int>        listMCP23017Addr {0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27};

    //*************************************PUBLIC FUNC*****************************************************//
public:
    QVector<bool>     x();
    QVector<bool>     y();
    void            setY(QVector<bool>);
    void            setY(int,bool);                //Set gia tri bien Y
    void            setX(QVector<bool>);
    void            setX(int,bool);                //Set gia tri bien X
    //*************************************SIGNAL**********************************************************//
signals:
    void xChanged(int);
    void yChanged(int);
    //*************************************PUBLIC SlOT*****************************************************//
public slots:
    void StartScan();
    void StopScan();

    //*************************************STATIC PRIVATE**************************************************//
private:
    static  QVector<bool>         m_x;
    static  QVector<bool>         m_y;
    //*************************************STATIC**********************************************************//
private:
    int             m_oneScan;
    int             m_stopScan;
    QMap<int,int>   m_xAddres;
    QMap<int,int>   m_yAddres;
    int             m_currentInAddr;
    int             m_currentOutAddr;
    int             m_currentInI2CAddr;
    int             m_currentOutI2CAddr;
    int             m_inputFirstI2CAddr;
    int             m_outputFirstI2CAddr;
    QMap<int,QMap<int,int>>     m_mcp23017ListIO;    //<diachii2c<pin_number,typeIO>>
    QMap<int,int>               m_gpioListIO;

    //*************************************PRIVATE*********************************************************//
private:
    void        run();
    void        initSetup(QString);
    void        readConfig(QString);

    //*************************************PRIVATE*********************************************************//
private slots:


};

#endif // PIBOARDIO_H
