#include"ImageLogger.h"
using namespace RobotSDK_Module;

//If you need to use extended node, please uncomment below and comment the using of default node
//USE_EXTENDED_NODE(ExtendedNodeClass[,...])
USE_DEFAULT_NODE

//=================================================
//Uncomment below PORT_DECL and set input node class name
PORT_DECL(0, CameraHub)

//=================================================
//Original node functions

//If you don't need to initialize node, you can delete this code segment
NODE_FUNC_DEF_EXPORT(bool, initializeNode)
{
	NOUNUSEDWARNING;
    auto vars=NODE_VARS;
    //vars->setInputPortObtainDataBehavior(0,GrabOldest);
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
    auto vars=NODE_VARS;
    qInfo("close");
    if(vars->timestamps.size()>0)
    {
        QString timefile=vars->path+QString("/")+vars->filename+QString(".txt");
        QFile file(timefile);
        file.open(QIODevice::WriteOnly|QIODevice::Text);
        QTextStream stream(&file);
        for(int i=0;i<vars->timestamps.size();i++)
        {
            stream<<vars->timestamps[i].msecsSinceStartOfDay()<<"\n";
        }
        file.close();
        qInfo("finish txt");
    }
    if(vars->images.size()>0)
    {
        QString videofile=vars->path+QString("/")+vars->filename+QString(".avi");
        cv::Size framesize=vars->images[0].size();
        cv::VideoWriter video(videofile.toStdString(),CV_FOURCC('M','J','P','G'),vars->fps,framesize);
        for(int i=0;i<vars->images.size();i++)
        {
            cv::Mat image;
            cv::cvtColor(vars->images[i],image,cv::COLOR_BGR2RGB);
            video<<image;
        }
        video.release();
        vars->images.clear();
        qInfo("finish video");
    }
    qInfo("close");
	return 1;
}

//This is original main function, you must keep it
NODE_FUNC_DEF_EXPORT(bool, main)
{
	NOUNUSEDWARNING;
    auto vars=NODE_VARS;
    auto data=PORT_DATA(0,0);
    vars->timestamps.push_back(data->timestamp);
    vars->images.push_back(data->cvimage);
	return 1;
}
