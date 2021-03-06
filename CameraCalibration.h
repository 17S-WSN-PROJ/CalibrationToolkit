#ifndef CAMERACALIBRATION
#define CAMERACALIBRATION

//=================================================
//Please add headers here:
#include<CameraHub.h>
#include"cameracalibrationwidget.h"

//=================================================
#include<RobotSDK.h>
namespace RobotSDK_Module
{

//=================================================
//Node configuration

#undef NODE_CLASS
#define NODE_CLASS CameraCalibration

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
    ADD_VAR(QString, calibfilename, "./camera.yml")
public:
    ADD_VAR(int, patternumx,10)
    ADD_VAR(int, patternumy,10)
    ADD_VAR(float, patternwidth,1)
    ADD_VAR(float, patternheight,1)
public:
    ADD_QLAYOUT(QVBoxLayout,layout)
    ADD_QWIDGET(CameraCalibrationWidget, camera)
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
