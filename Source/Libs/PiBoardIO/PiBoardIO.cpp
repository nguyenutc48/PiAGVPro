#include "PiBoardIO.h"

QVector<bool>     PIBoardIO::m_x;
QVector<bool>     PIBoardIO::m_y;
QVector<double>   PIBoardIO::m_adcDataList;
QVector<double>   PIBoardIO::m_dacDataList;

PIBoardIO::PIBoardIO(QObject *_parent,QString _config):
    QThread (_parent),
    configPath(_config)
{
    ADCChanelSelected = 0;
    DACChanelSelected = 0;
}

PIBoardIO::~PIBoardIO()
{
    this->m_Stop = true;
    msleep(500);
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
    if(m_outputMark == 0)
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
    if(m_inputMark == 0)
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

QVector<double> PIBoardIO::adc()
{
    return m_adcDataList;
}

QVector<double> PIBoardIO::dac()
{
    return m_dacDataList;
}

void PIBoardIO::setAdc(QVector<double> data)
{
    m_adcDataList = data;
}

void PIBoardIO::setDac(QVector<double> data)
{
    m_dacDataList = data;
}

double PIBoardIO::getAnalog(int cn)
{
    if(!m_adcDataList.isEmpty())
    {
        if(cn<m_adcDataList.size())
            return m_adcDataList[cn];
        else
            return 0;
    }
    else {
        return 0;
    }
}

bool PIBoardIO::setAnalog(int cn, double data)
{
    if(!m_dacDataList.isEmpty())
    {
        if(cn<m_dacDataList.size())
        {
            if(m_dacDataList[cn] != data)
            {
                m_dacDataList[cn] = data;
            }
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
}

double PIBoardIO::getAnalog()
{
    return getAnalog(0);
}

bool PIBoardIO::setAnalog(double data)
{
    return setAnalog(0,data);
}


int PIBoardIO::numberConvert(int index)
{
    int result = 1;
    for (int i =0; i<index; i++) {
        result *= 2;
    }
    return result - 1;
}

int PIBoardIO::addInput(int addr)
{
    int current_index = m_xAddres.size();
    m_xAddres[current_index] = addr;
    m_x.append(OFF);
    return current_index;
}

int PIBoardIO::addOutput(int addr)
{
    int current_index = m_yAddres.size();
    m_yAddres[current_index] = addr;
    m_y.append(OFF);
    return current_index;
}


void PIBoardIO::StartScan()
{
    if(m_oneScan != 1){
        m_Stop = false;
        bool check = initSetup("/home/pi/PiAGVPro/boar_config.ini");
        if(check)
            this->start();
    }
}

void PIBoardIO::StopScan()
{
    this->m_Stop = true;
    msleep(500);
}

void PIBoardIO::analogSet(double data)
{
    setAnalog(DACChanelSelected,data);
}

void PIBoardIO::run()
{
    if(m_oneScan != 1)
    {
        setStateLog(RUNNING,"Tien hanh scan dau vao ra");
        m_oneScan = 1;
        while(!m_Stop)
        {
            foreach (int inputAddr, m_xAddres.keys()) {
                bool result = digitalRead(m_xAddres[inputAddr]);
                setX(inputAddr,result);
            }

            foreach (int outputAddr, m_yAddres.keys()) {
                setY(outputAddr,m_y[outputAddr]);
            }

            for(int i = 0;i<m_analogAddr.size();i++) {
                int digital_read = analogRead(m_analogAddr[i].addr);
                double analog = digital_read*(m_analogAddr[i].vref/m_analogAddr[i].scale);
                if(m_adcDataList[i] != analog)
                {
                    m_adcDataList[i] = analog;
                    if(i == ADCChanelSelected)
                        emit analogChanged(analog);
                    emit adcChanged(i);
                }
            }


            for (int i=0; i<m_analogAddrDAC.size(); i++) {
                if(m_dacDataList[i] != m_dacDataListOld[i])
                {
                    double analog = m_dacDataList[i];
                    int number_scale = m_analogAddrDAC[i].scale;
                    double vref = m_analogAddrDAC[i].vref;
                    double dac = (analog*number_scale)/vref;
                    int digital = (int)dac;
                    SPI_Custom pin = m_analogAddrDAC[i].pin_layout;
                    setSendSPIData(pin, digital);
                    m_dacDataListOld[i] = analog;
                    emit dacChanged(i);
                }
            }
            //msleep(100);
        }
        setStateLog(ERROR,"Dung scan hoac co loi phat sinh");
    }
}

bool PIBoardIO::initSetup(QString dir)
{
    readConfig(dir);
    setStateLog(INITIO,"Khoi tao dau vao va dau ra cho mach");
    int check = wiringPiSetup();
    if(check == -1)
    {
        setStateLog(ERROR,"Khong the khoi tao duoc wiringPI");
        return false;
    }
    int ioI2CAddress = I2C_START_ADDRESS;
    int ioI2CAddress_Exten = I2C_START_ADDRESS;
    int inputNumber = 0;
    int outputNumber = 0;
    if(!m_gpioListIO.isEmpty()){
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
    }
    if(!m_mcp23017ListIO.isEmpty()){
        foreach (int mcpaddr, m_mcp23017ListIO.keys()) {
            mcp23017Setup(ioI2CAddress,mcpaddr);
            m_baseI2CStore[mcpaddr] = ioI2CAddress;
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
            ioI2CAddress_Exten += 16;
        }
    }
    if(!m_mcp4921ListIO.isEmpty()){
        foreach (int mcp4921, m_mcp4921ListIO.keys()) {
            SPI_Custom ic_spi;
            int yAddress = m_x.size();
            if(m_mcp4921ListIO[mcp4921].keys()[0] == 0){
                ic_spi = m_mcp4921ListIO[mcp4921][0];
                pinMode(ic_spi.sc_pin,OUTPUT);
                //ic_spi.sc_pin = addOutput(ic_spi.sc_pin);
                pinMode(ic_spi.sck_pin,OUTPUT);
                //ic_spi.sck_pin = addOutput(ic_spi.sck_pin);
                pinMode(ic_spi.data_pin,OUTPUT);
                //ic_spi.data_pin = addOutput(ic_spi.data_pin);

            }
            else {
                if(m_mcp23017ListIO.contains(m_mcp4921ListIO[mcp4921].keys()[0]) == true)
                {
                    int base_i2c = m_baseI2CStore[m_mcp4921ListIO[mcp4921].keys()[0]];
                    ic_spi = m_mcp4921ListIO[mcp4921][m_mcp4921ListIO[mcp4921].keys()[0]];
                    pinMode(base_i2c+ic_spi.sc_pin,OUTPUT);
                    //ic_spi.sc_pin = addOutput(base_i2c+ic_spi.sc_pin);
                    pinMode(base_i2c+ic_spi.sck_pin,OUTPUT);
                    //ic_spi.sck_pin = addOutput(base_i2c+ic_spi.sck_pin);
                    pinMode(base_i2c+ic_spi.data_pin,OUTPUT);
                    //ic_spi.data_pin = addOutput(base_i2c+ic_spi.data_pin);
                }
                else {
                    mcp23017Setup(ioI2CAddress_Exten,m_mcp4921ListIO[mcp4921].keys()[0]);
                    pinMode(ioI2CAddress_Exten+ic_spi.sc_pin,OUTPUT);
                    //ic_spi.sc_pin = addOutput(ioI2CAddress_Exten+ic_spi.sc_pin);
                    pinMode(ioI2CAddress_Exten+ic_spi.sck_pin,OUTPUT);
                    //ic_spi.sck_pin = addOutput(ioI2CAddress_Exten+ic_spi.sck_pin);
                    pinMode(ioI2CAddress_Exten+ic_spi.data_pin,OUTPUT);
                    //ic_spi.data_pin = addOutput(ioI2CAddress_Exten+ic_spi.data_pin);
                    ioI2CAddress_Exten+=16;
                }
            }
            m_analogAddrDAC[m_mcp4921ListIO.keys().indexOf(mcp4921)].pin_layout = ic_spi;
            m_spiPins.insert(m_mcp4921ListIO.keys().indexOf(mcp4921),ic_spi);
            m_dacDataList.append(0);
            m_dacDataListOld.append(0);
        }
    }
    if(!m_pcf8591Config.isEmpty())
    {
        int analogAddress = I2C_ANALOG_ADDRESS;
        foreach (int addr, m_pcf8591Config.keys()) {
            pcf8591Setup(analogAddress,addr);
            foreach (int pin, m_pcf8591Config[addr].keys()) {
                ADC adc;
                adc.addr = analogAddress+pin;
                adc.vref = m_pcf8591Config[addr][pin].vref;
                adc.scale = numberConvert(m_pcf8591Config[addr][pin].scale);
                m_analogAddr.append(adc);
                m_adcDataList.append(0);
            }
            analogAddress += 16;
        }
    }
    return true;
}

void PIBoardIO::readConfig(QString dir)
{
    setStateLog(READCONFIG,"Dang doc config file");
    QSettings settings(dir,QSettings::IniFormat);
    foreach (QString group, settings.childGroups()) {
        QStringList _group = group.split(':');


        if(_group.size() <= 1)
        {
            if(_group[0] == "INPUT")
                m_inputMark = 1;
            if(_group[0] == "OUTPUT")
                m_outputMark = 1;
            if(_group[0] == "DACSPI")
                m_analogOutMark = 1;
        }
        else {
            if(_group[1].toInt() > 1)
            {
                if(_group[0] == "INPUT")
                    m_inputMark = 1;
                if(_group[0] == "OUTPUT")
                    m_outputMark = 1;
                if(_group[0] == "DACSPI")
                    m_analogOutMark = 1;
            }
            else {
                if(_group[0] == "INPUT")
                    m_inputMark = _group[1].toInt();
                if(_group[0] == "OUTPUT")
                    m_outputMark = _group[1].toInt();
                if(_group[0] == "DACSPI")
                    m_analogOutMark = _group[1].toInt();
            }
        }

        settings.beginGroup(group);

        foreach (QString childKey, settings.childKeys()) {
            QStringList ic_type = childKey.split(':');
            QStringList ic_pin_number = settings.value(childKey).toStringList();

            // ************************* Check group IO **************************************//
            if(_group[0] == "INPUT" || _group[0] == "OUTPUT")
            {
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
                            if(m_mcp23017ListIO.find(m_listMCP23017Addr[ic_addr]).key() != m_listMCP23017Addr[ic_addr]){
                                for (int i=0; i<16; i++) {
                                    data[i] = -1;
                                }
                            }
                            else {
                                data = m_mcp23017ListIO[m_listMCP23017Addr[ic_addr]];
                            }

                            if(ic_pin_number[0] == "16"){
                                for (int i = 0; i < 16; i++) {
                                    if(_group[0] == "INPUT"){
                                        data[i] = 1;
                                    }
                                    if(_group[0] == "OUTPUT"){
                                        data[i] = 0;
                                    }
                                    m_mcp23017ListIO[m_listMCP23017Addr[ic_addr]] = data;
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
                                        m_mcp23017ListIO[m_listMCP23017Addr[ic_addr]] = data;
                                    }
                                }

                            }
                        }
                        else {
                            setStateLog(ERROR,"Cau hinh file config loi");
                        }
                    }
                    else {
                        setStateLog(ERROR,"Cau hinh file config loi");
                    }
                }
            }

            // ************************* Check group Analog **********************************//
            if(_group[0] == "DACSPI")
            {
                int number_ic = ic_type[0].toInt();
                DAC_SPI dac;
                dac.vref = _group[1].toInt();
                dac.scale = numberConvert(_group[2].toInt());
                dac.addr = 0;
                m_dacDataList.append(0);
                if(ic_type[1] == "gpio")
                {
                    SPI_Custom spi_pin;
                    spi_pin.sc_pin = ic_pin_number[0].toInt();
                    spi_pin.sck_pin = ic_pin_number[1].toInt();
                    spi_pin.data_pin = ic_pin_number[2].toInt();
                    m_mcp4921ListIO[number_ic][0] = spi_pin;
                    dac.pin_layout = spi_pin;
                    m_analogAddrDAC.append(dac);
                }
                if(ic_type[1] == "mcp23017")
                {
                    int ic_addr = ic_type[2].toInt();
                    SPI_Custom spi_pin;
                    spi_pin.sc_pin = ic_pin_number[0].toInt();
                    spi_pin.sck_pin = ic_pin_number[1].toInt();
                    spi_pin.data_pin = ic_pin_number[2].toInt();
                    m_mcp4921ListIO[number_ic][ic_addr] = spi_pin;
                    dac.pin_layout = spi_pin;
                    m_analogAddrDAC.append(dac);
                }
            }

            if(_group[0] == "ADC")
            {
                if(ic_type.size() == 2){
                    int addr = ic_type[1].toInt();
                    foreach (QString pin, ic_pin_number) {
                        m_adcDataList.append(0);
                        int _pin = pin.toInt();
                        ADC adc;
                        adc.scale = _group[2].toInt();
                        adc.vref = _group[1].toDouble();
                        adc.addr = _pin;
                        m_pcf8591Config[m_listPCF8591Addr[addr]][_pin] = adc;
                    }
                }
            }

        }

        settings.endGroup();
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



void PIBoardIO::setSendSPIClock(int sck_pin)
{
    digitalWrite(sck_pin,OFF);
    digitalWrite(sck_pin,ON);
}

void PIBoardIO::setSendSPIHeader(int sck_pin,int data_pin)
{
    // bit 15
    // 0 write to DAC *
    // 1 ignore command
    digitalWrite(data_pin,OFF);
    setSendSPIClock(sck_pin);
    // bit 14 Vref input buffer control
    // 0 unbuffered *
    // 1 buffered
    digitalWrite(data_pin,OFF);
    setSendSPIClock(sck_pin);
    // bit 13 Output Gain selection
    // 0 2x
    // 1 1x *
    digitalWrite(data_pin,ON);
    setSendSPIClock(sck_pin);
    // bit 12 Output shutdown control bit
    // 0 Shutdown the device
    // 1 Active mode operation *
    digitalWrite(data_pin,ON);
    setSendSPIClock(sck_pin);
}

void PIBoardIO::setSendSPIData(SPI_Custom pin, int32_t data)
{
    // initiate data transfer with 4921

    digitalWrite(pin.sc_pin,OFF);
    // send 4 bit header
    setSendSPIHeader(pin.sck_pin,pin.data_pin);
    // send data
    for(int i = 11 ; i >= 0; i--)
    {
        digitalWrite(pin.data_pin, ((data & (1<<i))) >> i);
        setSendSPIClock(pin.sck_pin);
    }
    // finish data transfer
    digitalWrite(pin.sc_pin,ON);
}




