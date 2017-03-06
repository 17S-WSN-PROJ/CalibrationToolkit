#include"ImuDecoder.h"
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
	return 1;
}

//If you don't need to manually open node, you can delete this code segment
NODE_FUNC_DEF_EXPORT(bool, openNode)
{
	NOUNUSEDWARNING;
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
	return 1;
}

//=================================================
//Extended node functions ( RazorASCII )

//If you don't need to initialize node, you can delete this code segment
NODE_EXFUNC_DEF_EXPORT(bool, initializeNode, RazorASCII)
{
    NOUNUSEDWARNING;
    auto vars=NODE_VARS;
    //vars->setInputPortObtainDataBehavior(0,ObtainBehavior::GrabOldest);
    return 1;
}

//As an extended main function, if you delete this code segment, original main function will be used
NODE_EXFUNC_DEF_EXPORT(bool, main, RazorASCII)
{
	NOUNUSEDWARNING;
    auto portdata = PORT_DATA(0,0);
    auto outputdata = NODE_DATA;
    QList<QByteArray> imudata=portdata->message.split(',');
    outputdata->timestamp=imudata[0].trimmed().toUInt();
    outputdata->ax=imudata[1].trimmed().toDouble();
    outputdata->ay=imudata[2].trimmed().toDouble();
    outputdata->az=imudata[3].trimmed().toDouble();
    outputdata->rx=imudata[4].trimmed().toDouble();
    outputdata->ry=imudata[5].trimmed().toDouble();
    outputdata->rz=imudata[6].trimmed().toDouble();
    outputdata->qx=imudata[7].trimmed().toDouble();
    outputdata->qy=imudata[8].trimmed().toDouble();
    outputdata->qz=imudata[9].trimmed().toDouble();
    outputdata->qw=imudata[10].trimmed().toDouble();

	return 1;
}
