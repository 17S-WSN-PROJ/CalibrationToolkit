#ifndef IMUROS
#define IMUROS

//=================================================
//Please add headers here:
#include<ImuDecoder.h>
#include<sensor_msgs/Imu.h>
#include<rosinterface.h>

//=================================================
#include<RobotSDK.h>
namespace RobotSDK_Module
{

//=================================================
//Node configuration

#undef NODE_CLASS
#define NODE_CLASS ImuRos

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
    int seqid;
    ADD_VAR(QString, frame_id, "/imudecoder")
    ADD_VAR(QString, topic, "/imumsg")
    ADD_VAR(u_int32_t, queuesize, 1000)
public:
    typedef ROSPub<sensor_msgs::Imu> rospub;
    ADD_INTERNAL_QOBJECT_TRIGGER(rospub, imupub, 1, topic, queuesize)
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
