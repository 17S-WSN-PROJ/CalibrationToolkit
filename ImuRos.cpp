#include"ImuRos.h"
using namespace RobotSDK_Module;

//If you need to use extended node, please uncomment below and comment the using of default node
//USE_EXTENDED_NODE(ExtendedNodeClass[,...])
USE_DEFAULT_NODE

//=================================================
//Uncomment below PORT_DECL and set input node class name
PORT_DECL(0, ImuDecoder)

//=================================================
//Original node functions

//If you don't need to initialize node, you can delete this code segment
NODE_FUNC_DEF_EXPORT(bool, initializeNode)
{
	NOUNUSEDWARNING;
    auto vars=NODE_VARS;
    if(vars->imupub==NULL)
    {
        return 0;
    }
    vars->setInputPortObtainDataBehavior(0,ObtainBehavior::GrabOldest);
	return 1;
}

//If you don't need to manually open node, you can delete this code segment
NODE_FUNC_DEF_EXPORT(bool, openNode)
{
	NOUNUSEDWARNING;
    auto vars=NODE_VARS;
    if(vars->imupub==NULL)
    {
        return 0;
    }
    vars->imupub->resetTopic(vars->topic,vars->queuesize);
    vars->seqid=0;
	return 1;
}

//This is original main function, you must keep it
NODE_FUNC_DEF_EXPORT(bool, main)
{
	NOUNUSEDWARNING;
    auto vars=NODE_VARS;
    auto data=PORT_DATA(0,0);
    sensor_msgs::Imu msg;
    msg.header.seq=vars->seqid++;
    msg.header.frame_id=vars->frame_id.toStdString();
    msg.header.stamp.fromNSec(data->timestamp*1000000);
    msg.orientation.x=data->qx;
    msg.orientation.y=data->qy;
    msg.orientation.z=data->qz;
    msg.orientation.w=data->qw;
    msg.angular_velocity.x=data->rx;
    msg.angular_velocity.y=data->ry;
    msg.angular_velocity.z=data->rz;
    msg.linear_acceleration.x=data->ax;
    msg.linear_acceleration.y=data->ay;
    msg.linear_acceleration.z=data->az;
    vars->imupub->sendMessage(msg);
	return 1;
}
