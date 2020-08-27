#ifndef PIFOLLOWGUIDE_H
#define PIFOLLOWGUIDE_H

#include <QObject>
#include <math.h>
#include <PiBoardIO.h>
#include <PiGuideReader.h>


class PiFollowGuide : public QObject
{
    Q_OBJECT

    Q_PROPERTY(int state READ state WRITE setState NOTIFY stateChanged)
    Q_PROPERTY(QString log READ log WRITE setLog NOTIFY logChanged)



    enum{
        AUTO_RUNNING,
        JOG_RUNNING,
        STOPED,
        EMG_STOPED,
        ERROR_INIT
    } State;

    struct PID
    {
        double Kp;
        double Ki;
        double Kd;
    };

    struct InputControl
    {
        int Start;
        int Stop;
        int EMG;
        QVector<int> Bumper;
        QVector<int> SafeSensor;
    };

    struct AnalogChanel
    {
        int LeftMotor;
        int RightMotor;
    };

    struct RobotParameter
    {
        int ratioMotor;
        int diameterWheel;
        int wheelDistance;
        int motorMaxSpeed;
    };

public:
    PiFollowGuide(QObject *parent = nullptr, PiBoardIO *board = nullptr, PiGuideReader *guide = nullptr);
    ~PiFollowGuide();

public:
    int                 state();
    QString             log();

    //Cac ham control
    int             Init(InputControl control, AnalogChanel chanel, PID pid);
    int             StartAutoFollowLine();
    int             StopAutoFollowLine();


    //Cac ham set
    void            setMaxSpeed(int);     //(Max speed, Min speed)
    void            setMinSpeed(int);
    void            setTargetSpeed(int);
    void            setParameter(RobotParameter);       // Robot paremeter setting
    void            setTimeOutLine(int);
    void            setPID(PID);
    void            setInputControl(InputControl);



    //Cac ham display
    double          getMaxSpeed();
    double          getMinSpeed();
    RobotParameter  getParameter();
    PID             getPID();
    InputControl    getInputControl();
    int             getTimeOutLine();
    int             getMotorSpeed(int);     //Lay toc do so hien tai cua tung motor


signals:
    void logChanged(QString);
    void stateChanged(int);

private:
    PiBoardIO       *board;
    PiGuideReader   *guide;
    QString         m_log;
    int             m_state;

    //Dinh nghia banh trai phai
    int             m_motorLeft;
    int             m_motorRight;

    //PID
    double          dActualP = 0;
    double          dActualI = 0;
    double          dActualD = 0;
    int             nPreviousError = 0;
    double          kp,ki,kd;

    int             m_speedDigitalMax = 4000;
    int             m_speedDigitalMin = 100;
    int             m_speedDigitalTarget = 3000;

    AnalogChanel    m_pwmChanel;
    RobotParameter  m_parameter;

    QElapsedTimer   timeOutLine;
    int             m_timeOutLine;
    int             m_outlineTrigger = 0;
    bool            m_Auto = false;

    QMap<int,int>   m_motorSetSpeed;        //<chanel,value>Luu cac gia tri toc do cua banh dat truoc do

private:
    void        PIDCompute(int);
    void        setState(int);
    void        setLog(QString);
    double      computePID(int);
    void        motorControl(int,double,double);
    void        setSpeed2Motor(int,int);
    void        setMotorSpeed(int,int);         //set digital to analog driver




private slots:
    void        GuideUpdate(QString);

};

#endif // PIFOLLOWGUIDE_H
