#ifndef IMUBODYVIS
#define IMUBODYVIS

//=================================================
//Please add headers here:
#include <ImuDecoder.h>
#include <visualization_msgs/Marker.h>
#include <visualization_msgs/MarkerArray.h>
#include <rosinterface.h>
#include <Eigen/Eigen>

//=================================================
#include<RobotSDK.h>
namespace RobotSDK_Module
{

//=================================================
//Node configuration

#undef NODE_CLASS
#define NODE_CLASS ImuBodyVis

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
    ADD_VAR(QString, id_right_thigh, "6")
    ADD_VAR(QString, id_right_culf, "4")
    ADD_VAR(QString, id_left_thigh, "5")
    ADD_VAR(QString, id_left_culf, "3")
    ADD_VAR(double, thigh_length, 0.5)
    ADD_VAR(double, culf_length, 0.5)
    ADD_VAR(double, hip_spacing, 0.3)
public:
    int seqid;
    ADD_VAR(QString, frame_id, "/body")
    ADD_VAR(QString, markertopic, "/body")
    ADD_VAR(u_int32_t, queuesize, 1000)
public:
    typedef ROSPub<visualization_msgs::MarkerArray> rosmarkerpub;
    ADD_INTERNAL_QOBJECT_TRIGGER(rosmarkerpub, markerpub, 1, markertopic, queuesize)
public:
    int init_flags;
    Eigen::Quaterniond ori_right_thigh;
    Eigen::Quaterniond ori_right_culf;
    Eigen::Quaterniond ori_left_thigh;
    Eigen::Quaterniond ori_left_culf;
    Eigen::Vector3d pos_right_knee;
    Eigen::Vector3d pos_right_ankle;
    Eigen::Vector3d pos_left_knee;
    Eigen::Vector3d pos_left_ankle;
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
