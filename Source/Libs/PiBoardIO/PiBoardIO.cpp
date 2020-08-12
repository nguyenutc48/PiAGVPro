#include "PiBoardIO.h"

QVector<bool>     PIBoardIO::m_x;
QVector<bool>     PIBoardIO::m_y;

PIBoardIO::PIBoardIO(QObject *_parent,QString _config):
    QThread (_parent),
    configPath(_config)
{
    m_currentInAddr = 0;
    m_currentOutAddr = 0;
}

PIBoardIO::~PIBoardIO()
{
}

QVector<bool> PIBoardIO::x()
{
    return m_x;
}

QVector<bool> PIBoardIO::y()
{
    return m_y;
}

void PIBoardIO::setY(QVector<bool>)
{

}

void PIBoardIO::setY(int index, bool value)
{
    m_y[index] = value;
    emit yChanged(index);
}

void PIBoardIO::setX(QVector<bool>)
{

}

void PIBoardIO::setX(int index, bool value)
{
    m_x[index] = value;
    emit xChanged(index);
}

void PIBoardIO::StartScan()
{
    initSetup("/home/pi/PiAGVPro/boar_config.ini");
}

void PIBoardIO::StopScan()
{

}

void PIBoardIO::run()
{

}

void PIBoardIO::initSetup(QString dir)
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
            m_xAddres[inputNumber] = gpio;
            inputNumber ++;
        }
        if(m_gpioListIO[gpio] == 0)
        {
            pinMode(m_gpioListIO.value(gpio),OUTPUT);
            digitalWrite(gpio,OFF);             // Clear cac trang thai khi init
            m_yAddres[outputNumber] = gpio;
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
                m_xAddres[inputNumber] = ioI2CAddress;
                inputNumber ++;
            }
            if(ic_pin[pin] == 0)
            {
                pinMode(ioI2CAddress,OUTPUT);
                digitalWrite(ioI2CAddress,OFF);     // Clear cac trang thai khi init
                m_yAddres[outputNumber] = ioI2CAddress;
                outputNumber ++;
            }
            ioI2CAddress ++;
        }
    }
}

void PIBoardIO::readConfig(QString dir)
{
    QSettings settings(dir,QSettings::IniFormat);
    foreach (QString group, settings.childGroups()) {

        //Code here [INPUT],[OUTPUT]
        if(group == "INPUT" || group == "OUTPUT")
        {
            settings.beginGroup(group);
            foreach (QString childKey, settings.childKeys()) {
                QStringList ic_type = childKey.split(':');
                QStringList ic_pin_number = settings.value(childKey).toStringList();

                //Code here mcp,gpio
                if(ic_type[0] == "gpio")
                {
                    foreach (QString a, ic_pin_number) {
                        if(group == "INPUT")
                            m_gpioListIO[a.toInt()] = 1;
                        if(group == "OUTPUT")
                            m_gpioListIO[a.toInt()] = 0;
                    }
                }
                if(ic_type[0] == "mcp23017")
                {
                    int ic_addr = ic_type[1].toInt();
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
                            if(group == "INPUT"){
                                data[i] = 1;
                            }
                            if(group == "OUTPUT"){
                                data[i] = 0;
                            }
                            m_mcp23017ListIO[listMCP23017Addr[ic_addr]] = data;
                        }
                    }
                    else {
                        foreach (QString pin, ic_pin_number) {
                            int pin_number = pin.toInt();
                            if(pin_number < 16){
                                if(group == "INPUT"){
                                    data[pin_number] = 1;
                                }
                                if(group == "OUTPUT"){
                                    data[pin_number] = 0;
                                }
                                m_mcp23017ListIO[listMCP23017Addr[ic_addr]] = data;
                            }
                        }

                    }
                }
            }
            settings.endGroup();
        }
    }

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


