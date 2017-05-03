#include"ImuHubRec.h"
using namespace RobotSDK_Module;

//If you need to use extended node, please uncomment below and comment the using of default node
//USE_EXTENDED_NODE(ExtendedNodeClass[,...])
USE_DEFAULT_NODE

//=================================================
//Uncomment below PORT_DECL and set input node class name
PORT_DECL(0, ImuHub)

//=================================================
//Original node functions

//If you don't need to initialize node, you can delete this code segment
NODE_FUNC_DEF_EXPORT(bool, initializeNode)
{
	NOUNUSEDWARNING;
    auto vars=NODE_VARS;
    vars->setInputPortObtainDataBehavior(0, GrabOldest);
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
        QString filename=vars->path+QString("/")+vars->filename;
        QFile file(filename);
        file.open(QIODevice::WriteOnly|QIODevice::Text);
        QTextStream stream(&file);
        for(int i=0;i<vars->timestamps.size();i++)
        {
            stream<<vars->timestamps[i].msecsSinceStartOfDay()<<":";
            stream<<vars->imudata[i]<<"\n";
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

    vars->timestamps.push_back(data->timestamp);
    vars->imudata.push_back(data->message.trimmed());

	return 1;
}
