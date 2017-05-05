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
    outputdata->timestamp=portdata->timestamp;
    QList<QByteArray> imudata=portdata->message.split(',');
    outputdata->imutimestamp=imudata[0].trimmed().toUInt();
    outputdata->deviceid="0";
    outputdata->ax=imudata[1].trimmed().toDouble();
    outputdata->ay=imudata[2].trimmed().toDouble();
    outputdata->az=imudata[3].trimmed().toDouble();
    outputdata->rx=imudata[4].trimmed().toDouble();
    outputdata->ry=imudata[5].trimmed().toDouble();
    outputdata->rz=imudata[6].trimmed().toDouble();
    outputdata->x=0;
    outputdata->y=0;
    outputdata->z=0;
    outputdata->qw=imudata[7].trimmed().toDouble();
    outputdata->qx=imudata[8].trimmed().toDouble();
    outputdata->qy=imudata[9].trimmed().toDouble();
    outputdata->qz=imudata[10].trimmed().toDouble();
	return 1;
}
//=================================================
//Extended node functions ( RazorFireFly )

//If you don't need to initialize node, you can delete this code segment
NODE_EXFUNC_DEF_EXPORT(bool, initializeNode, RazorFireFly)
{
	NOUNUSEDWARNING;
    auto vars=NODE_VARS;
    //vars->setInputPortObtainDataBehavior(0,ObtainBehavior::GrabOldest);
	return 1;
}

//As an extended main function, if you delete this code segment, original main function will be used
NODE_EXFUNC_DEF_EXPORT(bool, main, RazorFireFly)
{
	NOUNUSEDWARNING;
    auto vars = NODE_VARS;
    auto portdata = PORT_DATA(0,0);
    auto outputdata = NODE_DATA;

    outputdata->timestamp=portdata->timestamp;
    QList<QByteArray> imudata=portdata->message.split(',');
    if(imudata.size()==9)
    {

        outputdata->deviceid=imudata[0].trimmed();
        outputdata->imutimestamp=imudata[1].trimmed().toUInt();
        outputdata->ax=imudata[2].trimmed().toDouble();
        outputdata->ay=imudata[3].trimmed().toDouble();
        outputdata->az=imudata[4].trimmed().toDouble();
        outputdata->rx=0;
        outputdata->ry=0;
        outputdata->rz=0;
        outputdata->x=0;
        outputdata->y=0;
        outputdata->z=0;
        outputdata->qw=imudata[5].trimmed().toDouble();
        outputdata->qx=imudata[6].trimmed().toDouble();
        outputdata->qy=imudata[7].trimmed().toDouble();
        outputdata->qz=imudata[8].trimmed().toDouble();
        double qnorm = sqrt(pow(outputdata->qw,2.0) + pow(outputdata->qx,2.0) + pow(outputdata->qy,2.0) + pow(outputdata->qz,2.0));
        if(qnorm - 1 > vars->quatfilter)
        {
            return 0;
        }
//        else
//        {
//            outputdata->qw/=qnorm;
//            outputdata->qx/=qnorm;
//            outputdata->qy/=qnorm;
//            outputdata->qz/=qnorm;
//        }
        return 1;
    }
    else
    {
        return 0;
    }
}

//=================================================
//Extended node functions ( Razor2FireFly )

//If you don't need to initialize node, you can delete this code segment
NODE_EXFUNC_DEF_EXPORT(bool, initializeNode, Razor2FireFly)
{
	NOUNUSEDWARNING;
	return 1;
}

//As an extended main function, if you delete this code segment, original main function will be used
NODE_EXFUNC_DEF_EXPORT(bool, main, Razor2FireFly)
{
	NOUNUSEDWARNING;
    auto vars=NODE_VARS;
    auto portdata = PORT_DATA(0,0);
    auto outputdata = NODE_DATA;

    outputdata->timestamp=portdata->timestamp;
    QList<QByteArray> imudata=portdata->message.split(',');
    if(imudata.size()==8)
    {
        QList<QByteArray> seq = imudata[0].split(':');
        outputdata->imutimestamp=seq[1].trimmed().toUInt();
        outputdata->deviceid=vars->deviceid;
        outputdata->ax=imudata[1].trimmed().toDouble();
        outputdata->ay=imudata[2].trimmed().toDouble();
        outputdata->az=imudata[3].trimmed().toDouble();
        outputdata->rx=0;
        outputdata->ry=0;
        outputdata->rz=0;
        outputdata->x=0;
        outputdata->y=0;
        outputdata->z=0;
        outputdata->qw=imudata[4].trimmed().toDouble();
        outputdata->qx=imudata[5].trimmed().toDouble();
        outputdata->qy=imudata[6].trimmed().toDouble();
        imudata[7].chop(1);
        outputdata->qz=imudata[7].trimmed().toDouble();
        return 1;
    }
    else
    {
        return 0;
    }
}

