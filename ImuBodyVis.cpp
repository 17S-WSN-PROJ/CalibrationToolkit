#include"ImuBodyVis.h"
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
    auto vars = NODE_VARS;
    if(vars->markerpub==NULL || vars->dispub==NULL || vars->latangleftpub==NULL || vars->latangrightpub==NULL)
    {
        return 0;
    }
    vars->setInputPortObtainDataBehavior(0, ObtainBehavior::GrabOldest);
	return 1;
}

//If you don't need to manually open node, you can delete this code segment
NODE_FUNC_DEF_EXPORT(bool, openNode)
{
	NOUNUSEDWARNING;
    auto vars = NODE_VARS;
    if(vars->markerpub==NULL)
    {
        return 0;
    }
    vars->seqid=0;
    vars->init_flags=0;
    vars->markerpub->resetTopic(vars->markertopic,vars->queuesize);
    vars->dispub->resetTopic(vars->distopic,vars->queuesize);
    vars->latangleftpub->resetTopic(vars->latanglefttopic,vars->queuesize);
    vars->latangrightpub->resetTopic(vars->latangrighttopic,vars->queuesize);
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
    auto vars=NODE_VARS;
    auto data=PORT_DATA(0,0);
    {
        if(data->deviceid == vars->id_right_thigh)
        {
            vars->ori_right_thigh = Eigen::Quaterniond(data->qw, data->qx, data->qy, data->qz);
            vars->init_flags |= 1<<0;
        }
        else if(data->deviceid == vars->id_right_culf)
        {
            vars->ori_right_culf = Eigen::Quaterniond(data->qw, data->qx, data->qy, data->qz);
            vars->init_flags |= 1<<1;
        }
        else if(data->deviceid == vars->id_left_thigh)
        {
            vars->ori_left_thigh = Eigen::Quaterniond(data->qw, data->qx, data->qy, data->qz);
            vars->init_flags |= 1<<2;
        }
        else if(data->deviceid == vars->id_left_culf)
        {
            vars->ori_left_culf = Eigen::Quaterniond(data->qw, data->qx, data->qy, data->qz);
            vars->init_flags |= 1<<3;
        }

        if(vars->init_flags>=15)
        {
            Eigen::Vector3d fix_hip(0,0,vars->culf_length+vars->thigh_length);
            Eigen::Vector3d forward_right = vars->ori_right_thigh.toRotationMatrix()*Eigen::Vector3d(0,0.3,0);
            forward_right(0) = -forward_right(0);
            forward_right(1) = -forward_right(1);
            forward_right(2) = 0;
            Eigen::Vector3d forward_left = vars->ori_left_thigh.toRotationMatrix()*Eigen::Vector3d(0,-0.3,0);
            forward_left(2) = 0;
            Eigen::Vector3d forward = (forward_right+forward_left)/2;

            Eigen::Vector3d fix_right_hip = vars->ori_right_thigh.toRotationMatrix()*Eigen::Vector3d(0,0,-vars->hip_spacing/2);
            fix_right_hip(0) = -fix_right_hip(0);
            fix_right_hip(1) = -fix_right_hip(1);
            fix_right_hip(2) = vars->culf_length+vars->thigh_length;

            Eigen::Vector3d fix_left_hip = vars->ori_left_thigh.toRotationMatrix()*Eigen::Vector3d(0,0,-vars->hip_spacing/2);
            fix_left_hip(2) = vars->culf_length+vars->thigh_length;

            vars->pos_right_knee = vars->ori_right_thigh.toRotationMatrix()*Eigen::Vector3d(-vars->thigh_length,0,0);
            vars->pos_right_knee(0) = -vars->pos_right_knee(0);
            vars->pos_right_knee(1) = -vars->pos_right_knee(1);
            vars->pos_right_knee = fix_right_hip + vars->pos_right_knee;

            vars->pos_left_knee = vars->ori_left_thigh.toRotationMatrix()*Eigen::Vector3d(-vars->thigh_length,0,0);
            vars->pos_left_knee = fix_left_hip + vars->pos_left_knee;

            vars->pos_right_ankle = vars->ori_right_culf.toRotationMatrix()*Eigen::Vector3d(-vars->culf_length,0,0);
            vars->pos_right_ankle(0) = -vars->pos_right_ankle(0);
            vars->pos_right_ankle(1) = -vars->pos_right_ankle(1);
            vars->pos_right_ankle = vars->pos_right_knee + vars->pos_right_ankle;

            vars->pos_left_ankle = vars->ori_left_culf.toRotationMatrix()*Eigen::Vector3d(-vars->culf_length,0,0);
            vars->pos_left_ankle = vars->pos_left_knee + vars->pos_left_ankle;

            visualization_msgs::MarkerArray lines;

            visualization_msgs::Marker line;
            line.header.seq = vars->seqid++;
            line.header.frame_id=vars->frame_id.toStdString();
            int msec=data->timestamp.msecsSinceStartOfDay();
            line.header.stamp.sec=msec/1000;
            line.header.stamp.nsec=(msec%1000)*1000000;
            line.type = visualization_msgs::Marker::ARROW;
            line.scale.x = 0.04;
            line.scale.y = 0.08;
            line.scale.z = 0.05;
            line.points.resize(2);

            line.id = lines.markers.size();
            line.points[0].x = fix_right_hip(0);
            line.points[0].y = fix_right_hip(1);
            line.points[0].z = fix_right_hip(2);
            line.points[1].x = fix_hip(0);
            line.points[1].y = fix_hip(1);
            line.points[1].z = fix_hip(2);
            line.color.r = 1.0; line.color.g = 0.0; line.color.b = 0.0, line.color.a = 1.0;
            lines.markers.push_back(line);

            line.id = lines.markers.size();
            line.points[0].x = fix_left_hip(0);
            line.points[0].y = fix_left_hip(1);
            line.points[0].z = fix_left_hip(2);
            line.points[1].x = fix_hip(0);
            line.points[1].y = fix_hip(1);
            line.points[1].z = fix_hip(2);
            line.color.r = 1.0; line.color.g = 0.0; line.color.b = 0.0, line.color.a = 1.0;
            lines.markers.push_back(line);

            line.id = lines.markers.size();
            line.points[0].x = fix_right_hip(0);
            line.points[0].y = fix_right_hip(1);
            line.points[0].z = fix_right_hip(2);
            line.points[1].x = vars->pos_right_knee(0);
            line.points[1].y = vars->pos_right_knee(1);
            line.points[1].z = vars->pos_right_knee(2);
            line.color.r = 0.0; line.color.g = 1.0; line.color.b = 0.0, line.color.a = 1.0;
            lines.markers.push_back(line);

            line.id = lines.markers.size();
            line.points[0].x = fix_left_hip(0);
            line.points[0].y = fix_left_hip(1);
            line.points[0].z = fix_left_hip(2);
            line.points[1].x = vars->pos_left_knee(0);
            line.points[1].y = vars->pos_left_knee(1);
            line.points[1].z = vars->pos_left_knee(2);
            line.color.r = 0.0; line.color.g = 1.0; line.color.b = 0.0, line.color.a = 1.0;
            lines.markers.push_back(line);

            line.id = lines.markers.size();
            line.points[0].x = vars->pos_right_knee(0);
            line.points[0].y = vars->pos_right_knee(1);
            line.points[0].z = vars->pos_right_knee(2);
            line.points[1].x = vars->pos_right_ankle(0);
            line.points[1].y = vars->pos_right_ankle(1);
            line.points[1].z = vars->pos_right_ankle(2);
            line.color.r = 0.0; line.color.g = 0.0; line.color.b = 1.0, line.color.a = 1.0;
            lines.markers.push_back(line);

            line.id = lines.markers.size();
            line.points[0].x = vars->pos_left_knee(0);
            line.points[0].y = vars->pos_left_knee(1);
            line.points[0].z = vars->pos_left_knee(2);
            line.points[1].x = vars->pos_left_ankle(0);
            line.points[1].y = vars->pos_left_ankle(1);
            line.points[1].z = vars->pos_left_ankle(2);
            line.color.r = 0.0; line.color.g = 0.0; line.color.b = 1.0, line.color.a = 1.0;
            lines.markers.push_back(line);

            line.id = lines.markers.size();
            line.points[0].x = -forward(0);
            line.points[0].y = -forward(1);
            line.points[0].z = -0.1;
            line.points[1].x = forward(0);
            line.points[1].y = forward(1);
            line.points[1].z = -0.1;
            line.color.r = 1.0; line.color.g = 1.0; line.color.b = 0.0, line.color.a = 1.0;
            lines.markers.push_back(line);

            vars->markerpub->sendMessage(lines);


            std_msgs::Float64 float64_msg;

            Eigen::Vector3d feet_vec = vars->pos_right_ankle-vars->pos_left_ankle;
            double forward_norm = forward.norm();
//            qInfo("Forward: %f, %f, %f, %f", forward(0), forward(1), forward(2), forward_norm);
            if(forward_norm>0)
            {
                double feet_dis = feet_vec.dot(forward)/forward_norm;
//                qInfo("Feet: %f, %f, %f, %f, %f", feet_vec(0), feet_vec(1), feet_vec(2), feet_vec.dot(forward), feet_dis);

                float64_msg.data=feet_dis;
                vars->dispub->sendMessage(float64_msg);
            }

            Eigen::Vector3d left_lateral(-forward(1), forward(0), 0);
            Eigen::Vector3d right_lateral(forward(1), -forward(0), 0);

            if(left_lateral.norm()>0 && right_lateral.norm()>0)
            {
                Eigen::Vector3d left_thigh=vars->pos_left_knee - fix_left_hip;
                Eigen::Vector3d right_thigh=vars->pos_right_knee - fix_right_hip;

                double left_z = left_thigh.dot(Eigen::Vector3d(0,0,1));
                double left_lat = left_thigh.dot(left_lateral)/left_lateral.norm();
                double right_z = right_thigh.dot(Eigen::Vector3d(0,0,1));
                double right_lat = right_thigh.dot(right_lateral)/right_lateral.norm();

                double left_lat_ang = atan2(left_z, left_lat);
                double right_lat_ang = atan2(right_z, right_lat);

                float64_msg.data = left_lat_ang;
                vars->latangleftpub->sendMessage(float64_msg);
                float64_msg.data = right_lat_ang;
                vars->latangrightpub->sendMessage(float64_msg);
            }
        }
    }
	return 1;
}
