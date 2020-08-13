#include "PiBoardIO.h"

QVector<bool>     PIBoardIO::m_x;
QVector<bool>     PIBoardIO::m_y;

PIBoardIO::PIBoardIO(QObject *_parent,QString _config):
    QThread (_parent),
    configPath(_config)
{
}

PIBoardIO::~PIBoardIO()
{
    this->Stop = true;
    msleep(1000);
}

int PIBoardIO::state()
{
    return m_state;
}

QString PIBoardIO::log()
{
    return m_log;
}

QVector<bool> PIBoardIO::x()
{
    return m_x;
}

QVector<bool> PIBoardIO::y()
{
    return m_y;
}

void PIBoardIO::setY(QVector<bool> _y)
{
    foreach (bool Y, _y) {
        m_y[_y.indexOf(Y)] = Y;
    }
}

void PIBoardIO::setY(int index, bool value)
{
    if(outputMark == 0)
        value = !value;
    if(m_y[index] != value){
        m_y[index] = value;
        digitalWrite(m_yAddres[index],value);
        emit yChanged(index);
    }
}

bool PIBoardIO::getY(int _index)
{
    return m_y[_index];
}

void PIBoardIO::setX(QVector<bool> _x)
{
    foreach (bool X, _x) {
        m_x[_x.indexOf(X)] = X;
    }
}

void PIBoardIO::setX(int index, bool value)
{
    if(inputMark == 0)
        value = !value;
    if(m_x[index] != value){
        m_x[index] = value;
        emit xChanged(index);
    }
}

bool PIBoardIO::getX(int _index)
{
    return m_x[_index];
}

void PIBoardIO::setY(QMap<int, bool> _Y)
{
    foreach (int number, _Y.keys()) {
        m_y[number] = _Y[number];
    }
}

QMap<int, bool> PIBoardIO::getX(QVector<int> _X)
{
    QMap<int,bool> result;
    foreach (int number, _X) {
        result[number] = m_x[number];
    }
    return result;
}

void PIBoardIO::StartScan()
{
    if(m_oneScan != 1){
        Stop = false;
        bool check = initSetup("/home/pi/PiAGVPro/boar_config.ini");
        if(check)
            this->start();
    }
}

void PIBoardIO::StopScan()
{
    this->Stop = true;
    msleep(1000);

}

void PIBoardIO::run()
{
    if(m_oneScan != 1)
    {
        m_oneScan = 1;
        while(!Stop)
        {
            foreach (int inputAddr, m_xAddres.keys()) {
                bool result = digitalRead(m_xAddres[inputAddr]);
                setX(inputAddr,result);
            }

            foreach (int outputAddr, m_yAddres.keys()) {
                setY(outputAddr,m_y[outputAddr]);
            }
            msleep(100);
        }
    }
}

bool PIBoardIO::initSetup(QString dir)
{
    readConfig(dir);
    wiringPiSetup();
    int ioI2CAddress = I2C_START_ADDRESS;
    int inputNumber = 0;
    int outputNumber = 0;
    foreach (int gpio, m_gpioListIO.keys()) {
        if(m_gpioListIO[gpio] == 1)
        {
            pinMode(m_gpioListIO.value(gpio),INPUT);
            pullUpDnControl(m_gpioListIO.value(gpio),PUD_UP);
            m_xAddres[inputNumber] = gpio;
            m_x.append(OFF);
            inputNumber ++;
        }
        if(m_gpioListIO[gpio] == 0)
        {
            pinMode(m_gpioListIO.value(gpio),OUTPUT);
            digitalWrite(gpio,OFF);             // Clear cac trang thai khi init
            m_yAddres[outputNumber] = gpio;
            m_y.append(OFF);
            outputNumber ++;
        }
    }
    foreach (int mcpaddr, m_mcp23017ListIO.keys()) {
        mcp23017Setup(ioI2CAddress,mcpaddr);
        QMap<int,int> ic_pin = m_mcp23017ListIO.value(mcpaddr);
        foreach (int pin, ic_pin.keys()) {
            if(ic_pin[pin] == 1)
            {
                pinMode(ioI2CAddress,INPUT);
                pullUpDnControl(ioI2CAddress,PUD_UP);
                m_xAddres[inputNumber] = ioI2CAddress;
                m_x.append(OFF);
                inputNumber ++;
            }
            if(ic_pin[pin] == 0)
            {
                pinMode(ioI2CAddress,OUTPUT);
                digitalWrite(ioI2CAddress,OFF);     // Clear cac trang thai khi init
                m_yAddres[outputNumber] = ioI2CAddress;
                m_y.append(OFF);
                outputNumber ++;
            }
            ioI2CAddress ++;
        }
    }
    if(m_xAddres.size() == 0 || m_yAddres.size() == 0)
        return false;
    else {
        return true;
    }
}

void PIBoardIO::readConfig(QString dir)
{
    QSettings settings(dir,QSettings::IniFormat);
    foreach (QString group, settings.childGroups()) {
        QStringList _group = group.split(':');
        if(_group.size() <= 1)
        {
            if(_group[0] == "INPUT")
                inputMark = 1;
            if(_group[0] == "OUTPUT")
                outputMark = 1;
        }
        else {
            if(_group[1].toInt() > 1)
            {
                if(_group[0] == "INPUT")
                    inputMark = 1;
                if(_group[0] == "OUTPUT")
                    outputMark = 1;
            }
            else {
                if(_group[0] == "INPUT")
                    inputMark = _group[1].toInt();
                if(_group[0] == "OUTPUT")
                    outputMark = _group[1].toInt();
            }

        }


        //Code here [INPUT],[OUTPUT]
        if(_group[0] == "INPUT" || _group[0] == "OUTPUT")
        {
            settings.beginGroup(group);
            foreach (QString childKey, settings.childKeys()) {
                QStringList ic_type = childKey.split(':');
                QStringList ic_pin_number = settings.value(childKey).toStringList();

                //Code here mcp,gpio
                if(ic_type[0] == "gpio")
                {
                    foreach (QString a, ic_pin_number) {
                        if(_group[0] == "INPUT")
                            m_gpioListIO[a.toInt()] = 1;
                        if(_group[0] == "OUTPUT")
                            m_gpioListIO[a.toInt()] = 0;
                    }
                }
                if(ic_type[0] == "mcp23017")
                {
                    if(ic_type.size() == 2)
                    {
                        int ic_addr = ic_type[1].toInt();
                        if(ic_addr < 8)
                        {
                            QMap<int,int> data;
                            if(m_mcp23017ListIO.find(listMCP23017Addr[ic_addr]).key() != listMCP23017Addr[ic_addr]){
                                for (int i=0; i<16; i++) {
                                    data[i] = -1;
                                }
                            }
                            else {
                                data = m_mcp23017ListIO[listMCP23017Addr[ic_addr]];
                            }

                            if(ic_pin_number[0] == "16"){
                                for (int i = 0; i < 16; i++) {
                                    if(_group[0] == "INPUT"){
                                        data[i] = 1;
                                    }
                                    if(_group[0] == "OUTPUT"){
                                        data[i] = 0;
                                    }
                                    m_mcp23017ListIO[listMCP23017Addr[ic_addr]] = data;
                                }
                            }
                            else {
                                foreach (QString pin, ic_pin_number) {
                                    int pin_number = pin.toInt();
                                    if(pin_number < 16){
                                        if(_group[0] == "INPUT"){
                                            data[pin_number] = 1;
                                        }
                                        if(_group[0] == "OUTPUT"){
                                            data[pin_number] = 0;
                                        }
                                        m_mcp23017ListIO[listMCP23017Addr[ic_addr]] = data;
                                    }
                                }

                            }
                        }
                    }
                }
            }
            settings.endGroup();
        }
    }

}

void PIBoardIO::setState(int _state)
{
    m_state = _state;
    emit stateChanged(m_state);
}

void PIBoardIO::setLog(QString _log)
{
    m_log = _log;
    emit logChanged(m_log);
}

void PIBoardIO::setStateLog(int _state, QString _log)
{
    setState(_state);
    setLog(_log);
}

//void initSetup(QString dir)
//{
//    wiringPiSetup();
//    QSettings settings(dir, QSettings::IniFormat );
//    foreach (QString group, settings.childGroups()) {
//        if(group == "INPUT"){
//            settings.beginGroup(group);
//            m_inputFirstI2CAddr = I2C_START_ADDRESS;
//            foreach(QString childKey, settings.childKeys() ){
//                QStringList ic_addr = childKey.split(":", QString::SkipEmptyParts);
//                QStringList ic_value = settings.value(childKey).toStringList();
//                if(ic_addr[0] == "gpio")
//                {
//                    foreach (QString value, ic_value) {
//                        int address = value.toInt();
//                        pinMode(address,INPUT);
//                        m_currentInAddr++;
//                        m_xAddres[m_currentInAddr] = address;
//                    }
//                }
//                if(ic_addr[0] == "mcp23017")
//                {
//                    bool ok;
//                    int hex_addr = ic_addr[1].toInt(&ok, 16);
//                    mcp23017Setup(I2C_START_ADDRESS, hex_addr);
//                    if(ic_value[0] == "16"){
//                        for (int i=0; i<16; i++) {
//                            m_currentInI2CAddr = m_inputFirstI2CAddr + i;
//                            pinMode(m_currentInI2CAddr,INPUT);
//                            m_currentInAddr++;
//                            m_xAddres[m_currentInAddr] = m_currentInI2CAddr;

//                        }
//                    }
//                    else {
//                        foreach (QString value, ic_value) {
//                            bool ok;
//                            m_currentInI2CAddr = m_inputFirstI2CAddr + value.toInt(&ok,10);
//                            pinMode(m_currentInI2CAddr,INPUT);
//                            m_currentInAddr++;
//                            m_xAddres[m_currentInAddr] = m_currentInI2CAddr;

//                        }
//                    }
//                    m_inputFirstI2CAddr = m_inputFirstI2CAddr + 16;
//                }
//            }
//            settings.endGroup();
//        }

//    }
//}


