#include"ImuDeviceIndicator.h"
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
    vars->layout->addWidget(vars->imu0);
    vars->layout->addWidget(vars->imu1);
    vars->layout->addWidget(vars->imu2);
    vars->layout->addWidget(vars->imu3);
    vars->layout->addWidget(vars->imu4);
    vars->layout->addWidget(vars->imu5);
    vars->widget->setLayout(vars->layout);
    vars->setNodeGUIThreadFlag(1);
    vars->setInputPortObtainDataBehavior(0, ObtainBehavior::GrabOldest);
	return 1;
}

//If you don't need to manually open node, you can delete this code segment
NODE_FUNC_DEF_EXPORT(bool, openNode)
{
	NOUNUSEDWARNING;
    auto vars = NODE_VARS;
    vars->counter.resize(6);
    for(int i=0;i<6;i++)
    {
        vars->counter[i]=0;
    }
    vars->deviceidlist=vars->deviceids.split(",",QString::SkipEmptyParts);
    if(vars->deviceidlist.size()!=6)
    {
        return 0;
    }
    vars->imu0->setStyleSheet("QPushButton{ background-color : red; color : black }");
    vars->imu0->setText(vars->deviceidlist[0]);
    vars->imu1->setStyleSheet("QPushButton{ background-color : red; color : black }");
    vars->imu1->setText(vars->deviceidlist[1]);
    vars->imu2->setStyleSheet("QPushButton{ background-color : red; color : black }");
    vars->imu2->setText(vars->deviceidlist[2]);
    vars->imu3->setStyleSheet("QPushButton{ background-color : red; color : black }");
    vars->imu3->setText(vars->deviceidlist[3]);
    vars->imu4->setStyleSheet("QPushButton{ background-color : red; color : black }");
    vars->imu4->setText(vars->deviceidlist[4]);
    vars->imu5->setStyleSheet("QPushButton{ background-color : red; color : black }");
    vars->imu5->setText(vars->deviceidlist[5]);
    vars->timer->start(vars->timecount);
	return 1;
}

//If you don't need to manually close node, you can delete this code segment
NODE_FUNC_DEF_EXPORT(bool, closeNode)
{
	NOUNUSEDWARNING;
    auto vars = NODE_VARS;
    vars->counter.resize(6);
    for(int i=0;i<6;i++)
    {
        vars->counter[i]=0;
    }
    vars->imu0->setStyleSheet("QPushButton{ background-color : red; color : black }");
    vars->imu1->setStyleSheet("QPushButton{ background-color : red; color : black }");
    vars->imu2->setStyleSheet("QPushButton{ background-color : red; color : black }");
    vars->imu3->setStyleSheet("QPushButton{ background-color : red; color : black }");
    vars->imu4->setStyleSheet("QPushButton{ background-color : red; color : black }");
    vars->imu5->setStyleSheet("QPushButton{ background-color : red; color : black }");
    vars->timer->stop();
	return 1;
}

//This is original main function, you must keep it
NODE_FUNC_DEF_EXPORT(bool, main)
{
	NOUNUSEDWARNING;
    auto vars = NODE_VARS;
    if(IS_INTERNAL_TRIGGER)
    {
        for(int i=0;i<6;i++)
        {
            vars->counter[i]--;
            if(vars->counter[i]<0)
            {
                vars->counter[i]=0;
                switch(i)
                {
                case 0:
                    vars->imu0->setStyleSheet("QPushButton{ background-color : red; color : black }");
                    break;
                case 1:
                    vars->imu1->setStyleSheet("QPushButton{ background-color : red; color : black }");
                    break;
                case 2:
                    vars->imu2->setStyleSheet("QPushButton{ background-color : red; color : black }");
                    break;
                case 3:
                    vars->imu3->setStyleSheet("QPushButton{ background-color : red; color : black }");
                    break;
                case 4:
                    vars->imu4->setStyleSheet("QPushButton{ background-color : red; color : black }");
                    break;
                case 5:
                    vars->imu5->setStyleSheet("QPushButton{ background-color : red; color : black }");
                    break;
                }
            }
        }
        return 1;
    }
    auto data = PORT_DATA(0,0);
    for(int i=0;i<6;i++)
    {
        if(data->deviceid==vars->deviceidlist[i])
        {
            vars->counter[i]=vars->refill;
            switch(i)
            {
            case 0:
                vars->imu0->setStyleSheet("QPushButton{ background-color : green; color : black }");
                break;
            case 1:
                vars->imu1->setStyleSheet("QPushButton{ background-color : green; color : black }");
                break;
            case 2:
                vars->imu2->setStyleSheet("QPushButton{ background-color : green; color : black }");
                break;
            case 3:
                vars->imu3->setStyleSheet("QPushButton{ background-color : green; color : black }");
                break;
            case 4:
                vars->imu4->setStyleSheet("QPushButton{ background-color : green; color : black }");
                break;
            case 5:
                vars->imu5->setStyleSheet("QPushButton{ background-color : green; color : black }");
                break;
            }
        }
        else
        {
            vars->counter[i]--;
            if(vars->counter[i]<0)
            {
                vars->counter[i]=0;
                switch(i)
                {
                case 0:
                    vars->imu0->setStyleSheet("QPushButton{ background-color : red; color : black }");
                    break;
                case 1:
                    vars->imu1->setStyleSheet("QPushButton{ background-color : red; color : black }");
                    break;
                case 2:
                    vars->imu2->setStyleSheet("QPushButton{ background-color : red; color : black }");
                    break;
                case 3:
                    vars->imu3->setStyleSheet("QPushButton{ background-color : red; color : black }");
                    break;
                case 4:
                    vars->imu4->setStyleSheet("QPushButton{ background-color : red; color : black }");
                    break;
                case 5:
                    vars->imu5->setStyleSheet("QPushButton{ background-color : red; color : black }");
                    break;
                }
            }
        }
    }
	return 1;
}
