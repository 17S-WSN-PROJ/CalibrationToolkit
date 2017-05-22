#include"VideoReplay.h"
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
	return 1;
}

//If you don't need to manually open node, you can delete this code segment
NODE_FUNC_DEF_EXPORT(bool, openNode)
{
	NOUNUSEDWARNING;
    auto vars = NODE_VARS;
    vars->timestamps.clear();
    vars->images.clear();
    QString timefile=vars->path+QString("/")+vars->filename+QString(".txt");
    QFile file(timefile);
    if(file.open(QIODevice::ReadOnly|QIODevice::Text))
    {
        while(!file.atEnd())
        {
            QByteArray dataline = file.readLine().trimmed();
            int timestamp=dataline.toInt();
            vars->timestamps.push_back(QTime::fromMSecsSinceStartOfDay(timestamp));
//            qInfo("%d", vars->timestamps.back().msecsSinceStartOfDay());
        }
        file.close();
    }
    else
    {
        return 0;
    }
    QString videofile=vars->path+QString("/")+vars->filename+QString(".avi");
    cv::VideoCapture cap(videofile.toStdString());
    if(!cap.isOpened())
    {
        return 0;
    }
    vars->images.resize(vars->timestamps.size());
    for(int i=0;i<vars->timestamps.size();i++)
    {
        cap.retrieve(vars->images[i]);
    }
    vars->curframe=-1;
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
    auto vars = NODE_VARS;
    auto data = PORT_DATA(0,0);
    auto outputdata = NODE_DATA;

    QTime timestamp = data->timestamp;
    int left=0, right=vars->images.size()-1, mid;
    while(left<=right)
    {
        mid = (left+right)/2;
        int offset = vars->timestamps[mid].msecsTo(timestamp);
//        qInfo("offset=%d", offset);
        if(offset==0)
        {
            break;
        }
        else if(offset<0)
        {
            right = mid-1;
        }
        else if(offset>0)
        {
            left = mid+1;
        }
    }
//    qInfo("%d", timestamp.msecsSinceStartOfDay());
//    qInfo("%d", mid);
    if(vars->curframe==mid)
    {
        return 0;
    }
    else if(mid>=0&&mid<vars->timestamps.size())
    {
        vars->curframe=mid;
        outputdata->timestamp=vars->timestamps[mid];
        outputdata->originalsize.width=vars->images[mid].cols;
        outputdata->originalsize.height=vars->images[mid].rows;
        outputdata->cvimage=vars->images[mid].clone();
        return 1;
    }
}
