#ifndef IMUDEVICEINDICATOR
#define IMUDEVICEINDICATOR

//=================================================
//Please add headers here:
#include <ImuDecoder.h>
#include <QPushButton>
#include <QLayout>

//=================================================
#include<RobotSDK.h>
namespace RobotSDK_Module
{

//=================================================
//Node configuration

#undef NODE_CLASS
#define NODE_CLASS ImuDeviceIndicator

#undef INPUT_PORT_NUM
#define INPUT_PORT_NUM 1

#undef OUTPUT_PORT_NUM
#define OUTPUT_PORT_NUM 0

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
    ADD_VAR(QString, deviceids, "1,2,3,4,5,6")
    ADD_VAR(int, refill, 10)
public:
    ADD_QLAYOUT(QVBoxLayout, layout)
    ADD_QWIDGET(QPushButton, imu0)
    ADD_QWIDGET(QPushButton, imu1)
    ADD_QWIDGET(QPushButton, imu2)
    ADD_QWIDGET(QPushButton, imu3)
    ADD_QWIDGET(QPushButton, imu4)
    ADD_QWIDGET(QPushButton, imu5)
    QVector<int> counter;
    QList<QString> deviceidlist;
};

//=================================================
//Data types configuration

//If you need to refer data type of other node class, please uncomment below and comment its own data type.
//NODE_DATA_TYPE_REF(RefNodeClassName)
class NODE_DATA_TYPE : public NODE_DATA_BASE_TYPE
{

};

//=================================================
//You can declare functions here


//=================================================
}

#endif
