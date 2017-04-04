#include "imucalibrationwidget.h"

ImuCalibrationWidget::ImuCalibrationWidget(QString devices, QWidget *parent)
    : QWidget(parent)
{
    devicelist=devices.split(",",QString::SkipEmptyParts);
    int n=devicelist.size();
    for(int i=0;i<n;i++)
    {
        devicemap.insert(devicelist[i],i);
    }
    recordflag=false;
    imus.resize(n);

    layout = new QVBoxLayout();
    splitter = new QSplitter();
    layout->addWidget(splitter);

    scrollarea = new QScrollArea();
    splitter->addWidget(scrollarea);
    imageview = new QLabel("Image");
    scrollarea->setWidget(imageview);

    imuviewtabs = new QTabWidget();
    splitter->addWidget(imuviewtabs);
    imuviewers.resize(n);
    imudisplist.resize(n);
    for(int i=0;i<n;i++)
    {
        imuviewers[i] = new RobotSDK::GLViewer();
        imuviewtabs->addTab(imuviewers[i],QString("IMU %1").arg(i));

        imuviewers[i]->makeCurrent();
        imudisplist[i]=glGenLists(1);
        imuviewers[i]->addDisplayList(imudisplist[i]);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        glVertexPointer(3,GL_FLOAT,0,axespts);
        glColorPointer(3,GL_FLOAT,0,axeclrs);

        glNewList(imudisplist[i],GL_COMPILE);
        glDrawArrays(GL_LINES,0,6);
        glEndList();

        glDisableClientState(GL_VERTEX_ARRAY);
        glDisableClientState(GL_COLOR_ARRAY);

        imuviewers[i]->setDisplayListRotation(imudisplist[i],0,0,0);
        imuviewers[i]->update();
    }

    calibdataview = new QTableWidget;
    splitter->addWidget(calibdataview);

    btnlayout = new QHBoxLayout();
    btnstart = new QPushButton("Start Record");
    connect(btnstart,SIGNAL(clicked()),this,SLOT(slotStartRecord()));
    btnsave = new QPushButton("Save Record");
    connect(btnsave,SIGNAL(clicked()),this,SLOT(slotSaveRecord()));
    btnlayout->addWidget(btnstart);
    btnlayout->addWidget(btnsave);
    btnlayout->addStretch();
    layout->addLayout(btnlayout);

    this->setLayout(layout);
}

void ImuCalibrationWidget::addImage(CvImageStamped & image)
{
    if(recordflag)
    {
        images.push_back(image);
    }
    if(image.image.type()==CV_8UC3)
    {
        QImage img(image.image.data,image.image.cols,image.image.rows,image.image.step,QImage::Format_RGB888);
        imageview->setPixmap(QPixmap::fromImage(img));
        imageview->resize(img.size());
    }
}

void ImuCalibrationWidget::addImu(ImuStamped & imu, QString deviceid)
{
    if(devicemap.contains(deviceid))
    {
        int id=devicemap[deviceid];
        if(recordflag)
        {
            imus[id].push_back(imu);
        }
        imuviewers[id]->setDisplayListQuaternion(imudisplist[id],imu.qw,imu.qx,imu.qy,imu.qz);
        imuviewers[id]->setDisplayListPreScale(imudisplist[id],imu.ax+1,imu.ay+1,imu.az+1);
        imuviewers[id]->update();
    }
}

void ImuCalibrationWidget::clearData()
{
    images.clear();
    imageview->clear();
    for(int i=0;i<imus.size();i++)
    {
        imus[i].clear();
        imuviewers[i]->setDisplayListRotation(imudisplist[i],0,0,0);
        imuviewers[i]->setDisplayListPreScale(imudisplist[i],1,1,1);
        imuviewers[i]->update();
    }
}

void ImuCalibrationWidget::slotStartRecord()
{
    recordflag=!recordflag;
    if(recordflag)
    {
        btnstart->setText("Stop Record");
        clearData();
    }
    else
    {
        btnstart->setText("Start Record");
        //slotSaveRecord();
    }
}

void ImuCalibrationWidget::slotSaveRecord()
{
    if(recordflag)
    {
        return;
    }
    QString basename=QFileDialog::getSaveFileName(this,"Save Calibration Data");
    if(!basename.isEmpty()&&!images.isEmpty())
    {
        QString videofile=basename+QString(".avi");
        QString videotimestamp=basename+QString(".txt");
        cv::Size framesize=images[0].image.size();
        cv::VideoWriter video(videofile.toStdString(),CV_FOURCC('M','J','P','G'),30.0,framesize);
        QFile file(videotimestamp);
        file.open(QIODevice::WriteOnly|QIODevice::Text);
        QTextStream stream(&file);
        for(int i=0;i<images.size();i++)
        {
            video<<images[i].image;
            stream<<images[i].timestamp.msecsSinceStartOfDay()<<"\n";
        }
        video.release();
        file.close();
    }
    if(!basename.isEmpty()&&!imus.isEmpty())
    {
        for(int i=0;i<imus.size();i++)
        {
            QString imufile=basename+QString("_")+devicelist[i]+QString(".txt");
            QFile file(imufile);
            file.open(QIODevice::WriteOnly|QIODevice::Text);
            QTextStream stream(&file);
            for(int j=0;j<imus[i].size();j++)
            {
                stream<<imus[i][j].timestamp.msecsSinceStartOfDay()<<"\t";
                stream<<imus[i][j].qw<<"\t"<<imus[i][j].qx<<"\t"<<imus[i][j].qy<<"\t"<<imus[i][j].qz<<"\t";
                stream<<imus[i][j].ax<<"\t"<<imus[i][j].ay<<"\t"<<imus[i][j].az<<"\n";
            }
            file.close();
        }
    }
}


