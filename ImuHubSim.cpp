#include"ImuHubSim.h"
using namespace RobotSDK_Module;

//If you need to use extended node, please uncomment below and comment the using of default node
//USE_EXTENDED_NODE(ExtendedNodeClass[,...])
USE_DEFAULT_NODE

//=================================================
//Original node functions

//If you don't need to initialize node, you can delete this code segment
NODE_FUNC_DEF_EXPORT(bool, initializeNode)
{
	NOUNUSEDWARNING;
	return 1;
}

//If you don't need to manually open node, you can delete this code segment
NODE_FUNC_DEF_EXPORT(bool, openNode)
{
	NOUNUSEDWARNING;
    auto vars = NODE_VARS;
    vars->timestamps.clear();
    vars->imudata.clear();

    QString filename=vars->path+QString("/")+vars->filename;
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        while(!file.atEnd())
        {
            QByteArray dataline = file.readLine();
            QList<QByteArray> datas = dataline.split(':');
            int timestamp=datas[0].toInt();
            vars->timestamps.push_back(QTime::fromMSecsSinceStartOfDay(timestamp));
            vars->imudata.push_back(datas[1]);
        }
        file.close();
        vars->id=0;
        vars->timer->start(vars->interval);
        return 1;
    }
    else
    {
        return 0;
    }
}

//If you don't need to manually close node, you can delete this code segment
NODE_FUNC_DEF_EXPORT(bool, closeNode)
{
	NOUNUSEDWARNING;
    auto vars = NODE_VARS;
    vars->timer->stop();
    vars->timestamps.clear();
    vars->imudata.clear();
	return 1;
}

//This is original main function, you must keep it
NODE_FUNC_DEF_EXPORT(bool, main)
{
	NOUNUSEDWARNING;
    auto vars = NODE_VARS;
    auto data = NODE_DATA;
    data->timestamp = vars->timestamps[vars->id];
    data->message = vars->imudata[vars->id];
    vars->id++;
    if(vars->id>=vars->timestamps.size())
    {
        vars->id = 0;
    }
	return 1;
}
