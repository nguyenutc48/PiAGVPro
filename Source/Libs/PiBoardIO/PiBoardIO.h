/* Config of file
 * Cac dia chi dau vao ra thuc te phu thuoc vao thu tu tram
 * gpio duoc dinh nghia uu tien cao nhat
 * [INPUT:0]    // 0 la khi dau vao nhan duoc on can dao tin hieu
 * mcp23017:0=0,1,2,3,4,5,6,7
 * [OUTPUT:1]  // 1 co nghia la khi dung define ON khong can dao lai tin hieu
 * mcp23017:0=8,9,10,11,12,13,14,15 //
 * mcp23017:5=8,9,10,11,12,13
 * */

#ifndef PIBOARDIO_H
#define PIBOARDIO_H

//#include "piboardio_global.h"
#include <QThread>
#include <QTimer>
#include <QMutex>
#include <QElapsedTimer>
#include "wiringPi.h"
#include "wiringPiI2C.h"
#include <wiringPiSPI.h>
#include "mcp23017.h"
#include <QVector>
#include <QMap>
#include <QSettings>
#include "sr595.h"
#include "pcf8591.h"

#define I2C_START_ADDRESS 100
#define I2C_ANALOG_ADDRESS 300
#define ON  1
#define OFF 0



class PIBoardIO : public QThread
{
    Q_OBJECT
    //*********************************PROPERTIES**********************************************************//
    Q_PROPERTY(QVector<bool> x READ x WRITE setX NOTIFY xChanged)
    Q_PROPERTY(QVector<bool> y READ y WRITE setY NOTIFY yChanged)

    Q_PROPERTY(QVector<double> adc READ adc WRITE setAdc NOTIFY adcChanged)
    Q_PROPERTY(QVector<double> dac READ dac WRITE setDac NOTIFY dacChanged)

    Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString log READ log WRITE setLog NOTIFY logChanged)

public:
    //*********************************CONTRUCTOR**********************************************************//
    PIBoardIO(QObject *parent = nullptr,QString config = "/home/pi/board_config.ini");
    ~PIBoardIO();

    enum {
        RUNNING,
        READCONFIG,
        INITIO,
        ERROR
    } State;

    struct SPI_Custom{
        int sc_pin;
        int sck_pin;
        int data_pin;
    };

    struct ADC{
        int scale;
        int addr;
        double vref;
    };

    struct DAC_SPI
    {
        SPI_Custom pin_layout;
        int scale;
        int addr;
        double vref;
    };


    //*************************************PUBLIC**********************************************************//
public:
    QString             configPath;         //Dir config

    //*************************************PUBLIC FUNC*****************************************************//
public:
    int                 state();
    QString             log();
    //IO
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
    //Analog
    QVector<double>     adc();
    QVector<double>     dac();

    double              getAnalog(int);
    bool                setAnalog(int,double);  //
    double              getAnalog();
    bool                setAnalog(double);  //

    int                 ADCChanelSelected;
    int                 DACChanelSelected;


    //*************************************SIGNAL**********************************************************//
signals:
    void xChanged(int);
    void yChanged(int);
    void stateChanged(int);
    void logChanged(QString);

    void adcChanged(int);
    void dacChanged(int);
    void analogChanged(double);


    //*************************************PUBLIC SlOT*****************************************************//
public slots:
    void StartScan();
    void StopScan();
    void analogSet(double);

    //*************************************STATIC PRIVATE**************************************************//
private:
    static  QVector<bool>       m_x;
    static  QVector<bool>       m_y;
    static  QVector<double>     m_adcDataList;
    static  QVector<double>     m_dacDataList;

    //*************************************STATIC**********************************************************//
private:
    QMutex                      m_Input;
    QMutex                      m_Output;
    QMutex                      m_ADC;
    QMutex                      m_DAC;
    int                         m_state;
    QString                     m_log;
    int                         m_oneScan;
    int                         m_stopScan;
    QMap<int,int>               m_xAddres;
    QMap<int,int>               m_yAddres;
    QMap<int,QMap<int,int>>     m_mcp23017ListIO;    //<diachii2c<pin_number,typeIO>>
    QMap<int,int>               m_gpioListIO;
    QVector<int>                m_listMCP23017Addr {0x20,0x21,0x22,0x23,0x24,0x25,0x26,0x27};
    QVector<int>                m_listPCF8591Addr {0x41,0x43,0x45,0x47,0x49,0x4B,0x4D,0x4F};
    bool                        m_Stop; //Stop scan
    int                         m_inputMark;
    int                         m_outputMark;
    int                         m_currentAnalogIN;
    int                         m_currentAnalogOUT;
    void                        setAdc(QVector<double>);
    void                        setDac(QVector<double>);
    int                         m_analogOutMark;
    QMap<int,QMap<int,SPI_Custom>>     m_mcp4921ListIO;
    QMap<int,int>               m_baseI2CStore;     //Luu tru cac base I2c <addres i2c>,<base address>
    QVector<SPI_Custom>         m_spiPins;          //Luu tru cac kenh cua DAC
    QVector<ADC>                m_analogAddr;       // Luu tru cac kenh cua ADC
    QVector<DAC_SPI>            m_analogAddrDAC;    // Luu cac kenh cua DAC
    QMap<int,QMap<int,ADC>>     m_pcf8591Config;        //Save config DAC
    QVector<double>             m_dacDataListOld;       //Old list dac


    //*************************************PRIVATE*********************************************************//
private:
    void        run();
    bool        initSetup(QString);
    void        readConfig(QString);
    void        setState(int);
    void        setLog(QString);
    void        setStateLog(int,QString);
    void        setSendSPIClock(int);
    void        setSendSPIHeader(int,int);
    void        setSendSPIData(SPI_Custom,int);
    int         numberConvert(int);


    //*************************************PRIVATE*********************************************************//
private slots:


};

#endif // PIBOARDIO_H
