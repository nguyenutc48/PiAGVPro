#include "PiFollowGuide.h"

constexpr double pi() { return M_PI; }
double deg2rad(double x) { return x * pi() / 180; }
double rad2deg(double x) { return x * 180 / pi(); }

PiFollowGuide::PiFollowGuide(QObject *parent, PiBoardIO *board, PiGuideReader *guide) :
    QObject (parent),
    board(board),
    guide(guide)
{

}

int PiFollowGuide::state()
{
    return m_state;
}

QString PiFollowGuide::log()
{
    return m_log;
}

int PiFollowGuide::Init(PiFollowGuide::InputControl control, PiFollowGuide::AnalogChanel chanel, PiFollowGuide::PID pid)
{
    if(board != nullptr && guide != nullptr)
    {
        if(chanel.LeftMotor > 0 && chanel.LeftMotor < 10) {
            m_motorLeft = chanel.LeftMotor;
        } else setState(ERROR_INIT);
        if(chanel.RightMotor > 0 && chanel.RightMotor < 10) {
            m_motorRight = chanel.RightMotor;
        } else setState(ERROR_INIT);

        m_pwmChanel = chanel;
        connect(guide,SIGNAL(dataGuideChanged(QString)),this,SLOT(GuideUpdate(QString)));
        return true;
    }
    else {

        return ERROR_INIT;
    }
}

void PiFollowGuide::setMaxSpeed(int max)
{
    m_speedDigitalMax = max;
}

void PiFollowGuide::setMinSpeed(int min)
{
    m_speedDigitalMin = min;
}

void PiFollowGuide::setTargetSpeed(int target)
{
    m_speedDigitalTarget = target;
}

void PiFollowGuide::setParameter(PiFollowGuide::RobotParameter para)
{
    m_parameter = para;
}

void PiFollowGuide::setTimeOutLine(int timeOut)
{
    m_timeOutLine = timeOut;
}

double PiFollowGuide::getMaxSpeed()
{
    return m_speedDigitalMax;
}

double PiFollowGuide::getMinSpeed()
{
    return m_speedDigitalMin;
}

PiFollowGuide::RobotParameter PiFollowGuide::getParameter()
{
    return m_parameter;
}

int PiFollowGuide::getMotorSpeed(int cn)
{
    return m_motorSetSpeed[cn];
}

void PiFollowGuide::setState(int data)
{
    m_state = data;
    emit stateChanged(m_state);
}

void PiFollowGuide::setLog(QString data)
{
    m_log = data;
    emit logChanged(m_log);
}

void PiFollowGuide::GuideUpdate(QString str_guide_error)
{
    int guide_error = abs(str_guide_error.toInt());
    if(guide_error < 17)
    {
        m_outlineTrigger = 0;
        timeOutLine.restart();
        motorControl(guide_error,m_speedDigitalMax,m_speedDigitalMin);
    }
    else {
        if(m_outlineTrigger == 0)
        {
            m_outlineTrigger = 1;
            timeOutLine.start();
        }
        if(m_outlineTrigger == 1 && timeOutLine.elapsed() > m_timeOutLine)
            setSpeed2Motor(0,0);
    }
}

double PiFollowGuide::computePID(int nDeviation)
{
    double dPIDResult = 0;
    int nAbsDeviation = abs(nDeviation);
    if(nAbsDeviation < 17)
    {
        dActualP = nAbsDeviation; // Tỉ lệ: Xác định tác động của sai số hiện tại
        dActualI = dActualI + nAbsDeviation; // Tích phân: Xác định tác động của tổng các sai số quá khứ
        dActualD = nAbsDeviation - nPreviousError; // Vi phân: Xác định tác động của tốc độ biến đổi sai số
        if(nAbsDeviation <= 6)
        {
            dActualI = 0; // Xóa lịch sử sai số khi quá trình ổn định
            if(nAbsDeviation <= 1)
            {
                dActualD = 0;
            }
        }
        dPIDResult = kp * dActualP + ki * dActualI + kd * dActualD;
        nPreviousError = nAbsDeviation;
    }
    return dPIDResult;
}

void PiFollowGuide::setSpeed2Motor(int speedLeft, int speedRight)
{
    setMotorSpeed(m_motorLeft,speedLeft);
    setMotorSpeed(m_motorRight,speedRight);
}

void PiFollowGuide::setMotorSpeed(int cn, int speed)
{
    board->setAnalog(cn,speed);
    m_motorSetSpeed[cn] = speed;
}

void PiFollowGuide::motorControl(int nDeviation, double baseMaxSpeed, double baseMinSpeed)
{
    double computeSpeedLeft;
    double computeSpeedRight;
    double dPIDResult = computePID(nDeviation);
    if(nDeviation < 0)
    {
        computeSpeedLeft = baseMaxSpeed;
        computeSpeedRight = baseMaxSpeed - int(abs(dPIDResult));
    }
    else if(nDeviation > 0)
    {
        computeSpeedLeft = baseMaxSpeed - int(abs(dPIDResult));
        computeSpeedRight = baseMaxSpeed;
    }
    else
    {
        computeSpeedLeft = baseMaxSpeed;
        computeSpeedRight = baseMaxSpeed;
    }
    //
    if(abs(nDeviation) >= 14) // Lệch Tape quá thì giảm tốc độ cả 2 bánh xe
    {
        if(baseMaxSpeed >= 1500)
        {
            computeSpeedLeft -= (3 * baseMinSpeed) / 2;
            computeSpeedRight -= (3 * baseMinSpeed) / 2;
        }
        else if(baseMaxSpeed >= 1000)
        {
            computeSpeedLeft -= baseMinSpeed;
            computeSpeedRight -= baseMinSpeed;
        }
    }
    //
    computeSpeedLeft = (computeSpeedLeft <= 0) ? 0 : ((computeSpeedLeft >= baseMaxSpeed) ? baseMaxSpeed : computeSpeedLeft);
    computeSpeedRight = (computeSpeedRight <= 0) ? 0 : ((computeSpeedRight >= baseMaxSpeed) ? baseMaxSpeed : computeSpeedRight);
    //
    setSpeed2Motor(computeSpeedLeft, computeSpeedRight);
}





