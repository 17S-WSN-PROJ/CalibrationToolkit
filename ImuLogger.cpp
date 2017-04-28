#include"ImuLogger.h"
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
    vars->setInputPortObtainDataBehavior(0,GrabOldest);
	return 1;
}

//If you don't need to manually open node, you can delete this code segment
NODE_FUNC_DEF_EXPORT(bool, openNode)
{
	NOUNUSEDWARNING;
    auto vars=NODE_VARS;
    vars->timestamps.clear();
    vars->imudata.clear();
    return 1;
}

//If you don't need to manually close node, you can delete this code segment
NODE_FUNC_DEF_EXPORT(bool, closeNode)
{
	NOUNUSEDWARNING;
    auto vars=NODE_VARS;
    if(vars->timestamps.size()>0)
    {
        QString filename=vars->path+QString("/")+vars->filename+vars->deviceid+QString(".txt");
        QFile file(filename);
        file.open(QIODevice::WriteOnly|QIODevice::Text);
        QTextStream stream(&file);
        for(int i=0;i<vars->timestamps.size();i++)
        {
            stream<<vars->timestamps[i].msecsSinceStartOfDay();
            for(int j=0;j<7;j++)
            {
                stream<<"\t"<<QString::number(vars->imudata[i][j],'f',6);
            }
            stream<<"\n";
        }
        file.close();
    }
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
        vars->timestamps.push_back(data->timestamp);
        QVector<double> imudata;
        imudata.push_back(data->qw);
        imudata.push_back(data->qx);
        imudata.push_back(data->qy);
        imudata.push_back(data->qz);
        imudata.push_back(data->ax);
        imudata.push_back(data->ay);
        imudata.push_back(data->az);
        vars->imudata.push_back(imudata);
        return 1;
    }
    else
    {
        return 0;
    }
}
