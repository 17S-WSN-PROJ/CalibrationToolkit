#ifndef IMUHUB
#define IMUHUB

//=================================================
//Please add headers here:
#include"imuserialportreader.h"

//=================================================
#include<RobotSDK.h>
namespace RobotSDK_Module
{

//=================================================
//Node configuration

#undef NODE_CLASS
#define NODE_CLASS ImuHub

#undef INPUT_PORT_NUM
#define INPUT_PORT_NUM 0

#undef OUTPUT_PORT_NUM
#define OUTPUT_PORT_NUM 1

//=================================================
//Params types configuration

//If you need to refer params type of other node class, please uncomment below and comment its own params type.
//NODE_PARAMS_TYPE_REF(RefNodeClassName)
class NODE_PARAMS_TYPE : public NODE_PARAMS_BASE_TYPE
{

};

//=================================================
//Vars types configuration

//If you need to refer vars type of other node class, please uncomment below and comment its own vars type.
//NODE_VARS_TYPE_REF(RefNodeClassName)
class NODE_VARS_TYPE : public NODE_VARS_BASE_TYPE
{
public:
    ADD_VAR(QString, portname, "ttyUSB1")
    ADD_ENUM_VAR_WITH_OPTIONS(QSerialPort::BaudRate, baudrate, QSerialPort::Baud115200, QList<QSerialPort::BaudRate>()
                              <<QSerialPort::Baud1200<<QSerialPort::Baud2400<<QSerialPort::Baud4800<<QSerialPort::Baud9600
                              <<QSerialPort::Baud19200<<QSerialPort::Baud38400<<QSerialPort::Baud57600<<QSerialPort::Baud115200)
public:
    ADD_INTERNAL_QOBJECT_TRIGGER(ImuSerialPortReader, port, 1)
    ADD_INTERNAL_DEFAULT_CONNECTION(port, signalImuReceived)
};

//=================================================
//Data types configuration

//If you need to refer data type of other node class, please uncomment below and comment its own data type.
//NODE_DATA_TYPE_REF(RefNodeClassName)
class NODE_DATA_TYPE : public NODE_DATA_BASE_TYPE
{
public:
    QByteArray message;
};

//=================================================
//You can declare functions here


//=================================================
}

#endif
