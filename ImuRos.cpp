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
    if(vars->imupub==NULL||vars->posepub==NULL)
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
    if(vars->imupub==NULL||vars->posepub==NULL)
    {
        return 0;
    }
    vars->imupub->resetTopic(vars->imutopic,vars->queuesize);
    vars->posepub->resetTopic(vars->posetopic,vars->queuesize);
    vars->seqid=0;
	return 1;
}

//This is original main function, you must keep it
NODE_FUNC_DEF_EXPORT(bool, main)
{
	NOUNUSEDWARNING;
    auto vars=NODE_VARS;
    auto data=PORT_DATA(0,0);

    sensor_msgs::Imu imumsg;
    imumsg.header.seq=vars->seqid++;
    imumsg.header.frame_id=vars->frame_id.toStdString();
    imumsg.header.stamp.fromNSec(data->timestamp*1000000);
    imumsg.linear_acceleration.x=data->ax;
    imumsg.linear_acceleration.y=data->ay;
    imumsg.linear_acceleration.z=data->az;
    imumsg.angular_velocity.x=data->rx;
    imumsg.angular_velocity.y=data->ry;
    imumsg.angular_velocity.z=data->rz;
    imumsg.orientation.w=data->qw;
    imumsg.orientation.x=data->qx;
    imumsg.orientation.y=data->qy;
    imumsg.orientation.z=data->qz;
    vars->imupub->sendMessage(imumsg);

    geometry_msgs::PoseStamped posemsg;
    posemsg.header=imumsg.header;
    posemsg.pose.position.x=0;
    posemsg.pose.position.y=0;
    posemsg.pose.position.z=0;
    posemsg.pose.orientation=imumsg.orientation;
    vars->posepub->sendMessage(posemsg);

	return 1;
}
