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
    vars->file.setFileName(vars->filename);
    if(vars->file.open(QIODevice::WriteOnly|QIODevice::Text))
    {
        vars->stream.setDevice(&(vars->file));
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
    auto vars=NODE_VARS;
    vars->file.close();
	return 1;
}

//This is original main function, you must keep it
NODE_FUNC_DEF_EXPORT(bool, main)
{
	NOUNUSEDWARNING;
    auto vars=NODE_VARS;
    auto data=PORT_DATA(0,0);
    vars->stream<<data->timestamp.msecsSinceStartOfDay()<<"\t";
    vars->stream<<QString::number(data->qw,'f',6)<<"\t";
    vars->stream<<QString::number(data->qx,'f',6)<<"\t";
    vars->stream<<QString::number(data->qy,'f',6)<<"\t";
    vars->stream<<QString::number(data->qz,'f',6)<<"\t";
    vars->stream<<QString::number(data->ax,'f',6)<<"\t";
    vars->stream<<QString::number(data->ay,'f',6)<<"\t";
    vars->stream<<QString::number(data->az,'f',6)<<"\n";
	return 1;
}
