#include"ImuCalibration.h"
using namespace RobotSDK_Module;

//If you need to use extended node, please uncomment below and comment the using of default node
//USE_EXTENDED_NODE(ExtendedNodeClass[,...])
USE_DEFAULT_NODE

//=================================================
//Uncomment below PORT_DECL and set input node class name
PORT_DECL(0, CameraHub)
PORT_DECL(1, ImuDecoder)

//=================================================
//Original node functions

//If you don't need to initialize node, you can delete this code segment
NODE_FUNC_DEF_EXPORT(bool, initializeNode)
{
	NOUNUSEDWARNING;
    auto vars=NODE_VARS;
    vars->layout->addWidget(vars->imucalib);
    vars->widget->setLayout(vars->layout);
    vars->setNodeGUIThreadFlag(1);

    vars->setInputPortObtainDataBehavior(QList<ObtainBehavior>()<<GrabOldest<<GrabOldest);
	return 1;
}

//If you don't need to manually open node, you can delete this code segment
NODE_FUNC_DEF_EXPORT(bool, openNode)
{
	NOUNUSEDWARNING;
    auto vars=NODE_VARS;
    vars->imucalib->clearData();
	return 1;
}

//If you don't need to manually close node, you can delete this code segment
NODE_FUNC_DEF_EXPORT(bool, closeNode)
{
	NOUNUSEDWARNING;
	return 1;
}

//This is original main function, you must keep it
NODE_FUNC_DEF_EXPORT(bool, main)
{
	NOUNUSEDWARNING;
    auto vars= NODE_VARS;
    int camnum=PORT_DATA_SIZE(0);
    if(camnum>0)
    {
        for(int i=0;i<camnum;i++)
        {
            auto data=PORT_DATA(0,i);
            CvImageStamped image;
            image.timestamp=data->timestamp;
            image.image=data->cvimage;
            vars->imucalib->addImage(image);
        }
    }
    int imunum=PORT_DATA_SIZE(1);
    if(imunum>0)
    {
        for(int i=0;i<imunum;i++)
        {
            auto data=PORT_DATA(1,i);
            ImuStamped imu;
            imu.timestamp=data->timestamp;
            imu.ax=data->ax;
            imu.ay=data->ay;
            imu.az=data->az;
            imu.qw=data->qz;
            imu.qx=data->qx;
            imu.qy=data->qy;
            imu.qz=data->qz;
            vars->imucalib->addImu(imu,data->deviceid);
        }
    }
	return 1;
}
