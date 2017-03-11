#include"CameraCalibration.h"
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
    auto vars = NODE_VARS;
    vars->layout->addWidget(vars->camera);
    vars->widget->setLayout(vars->layout);
    vars->setNodeGUIThreadFlag(1);
    return 1;
}

//If you don't need to manually open node, you can delete this code segment
NODE_FUNC_DEF_EXPORT(bool, openNode)
{
    NOUNUSEDWARNING;
    auto vars = NODE_VARS;
    vars->camera->patternum.width=vars->patternumx;
    vars->camera->patternum.height=vars->patternumy;
    vars->camera->patternsize.width=vars->patternwidth;
    vars->camera->patternsize.height=vars->patternheight;
    vars->camera->calibfilename=vars->calibfilename;

    vars->camera->grid3dpoint.clear();
    for(int i=0;i<vars->camera->patternum.height;i++)
    {
        for(int j=0;j<vars->camera->patternum.width;j++)
        {
            cv::Point3f tmpgrid3dpoint;
            tmpgrid3dpoint.x=i*vars->camera->patternsize.height;
            tmpgrid3dpoint.y=j*vars->camera->patternsize.width;
            tmpgrid3dpoint.z=0;
            vars->camera->grid3dpoint.push_back(tmpgrid3dpoint);
        }
    }

    vars->camera->calibimages.clear();
    vars->camera->grid3dpoints.clear();
    vars->camera->grid2dpoints.clear();

    vars->camera->grablist->clear();
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

    vars->camera->calibimage=data->cvimage.clone();
    if(!vars->camera->reviewmode)
    {
        cv::Mat image= vars->camera->calibimage.clone();
        QImage img(image.data,image.cols,image.rows,image.step,QImage::Format_RGB888);
        img.rgbSwapped();
        vars->camera->image->setPixmap(QPixmap::fromImage(img));
        vars->camera->image->resize(img.size());
    }
    return 1;
}
