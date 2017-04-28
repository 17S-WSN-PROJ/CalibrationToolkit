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
    vars->imupub->resetTopic(QString("%1_%2").arg(vars->imutopic).arg(vars->deviceid),vars->queuesize);
    vars->posepub->resetTopic(QString("%1_%2").arg(vars->posetopic).arg(vars->deviceid),vars->queuesize);
    vars->seqid=0;
	return 1;
}

//This is original main function, you must keep it
NODE_FUNC_DEF_EXPORT(bool, main)
{
    NOUNUSEDWARNING;
    auto vars=NODE_VARS;
    auto data=PORT_DATA(0,0);

    if(data->deviceid==vars->deviceid)
    {
        sensor_msgs::Imu imumsg;
        imumsg.header.seq=vars->seqid++;
        imumsg.header.frame_id=vars->frame_id.toStdString();
        int msec=data->timestamp.msecsSinceStartOfDay();
        imumsg.header.stamp.sec=msec/1000;
        imumsg.header.stamp.nsec=(msec%1000)*1000000;
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
        if(vars->SetPose)
        {
            posemsg.pose.position.x=vars->x;
            posemsg.pose.position.y=vars->y;
            posemsg.pose.position.z=vars->z;
        }
        else
        {
            posemsg.pose.position.x=data->x;
            posemsg.pose.position.y=data->y;
            posemsg.pose.position.z=data->z;
        }
        posemsg.pose.orientation=imumsg.orientation;
        vars->posepub->sendMessage(posemsg);

        return 1;
    }
    else
    {
        return 0;
    }
}
