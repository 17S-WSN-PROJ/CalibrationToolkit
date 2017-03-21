#include "imucalibrationwidget.h"

ImuCalibrationWidget::ImuCalibrationWidget(QString devices, QString intrinsicfilename, QWidget *parent)
    : QWidget(parent)
{
    cv::FileStorage fs(intrinsicfilename.toStdString(),cv::FileStorage::READ);
    fs["CameraMat"]>>cameramat;
    fs["DistCoeff"]>>distcoeff;
    fs.release();

    QList<QString> devicelist=devices.split(",",QString::SkipEmptyParts);
    int n=devicelist.size();
    for(int i=0;i<n;i++)
    {
        devicemap.insert(devicelist[i],i);
    }
    imus.resize(n);
    imageposes.resize(n);

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
    for(int i=0;i<n;i++)
    {
        imuviewers[i] = new RobotSDK::GLViewer();
        imuviewtabs->addTab(imuviewers[i],QString("IMU %1").arg(i));
        imuviewers[i]->makeCurrent();
        int orientationlist=glGenLists(1);
        imuviewers[i]->addDisplayList(orientationlist);

        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);

        glVertexPointer(3,GL_FLOAT,);
    }    

    calibdataview = new QTableWidget;
    splitter->addWidget(calibdataview);

    btnlayout = new QHBoxLayout();
    btncalib = new QPushButton("Calibrate");
    btnproject = new QPushButton("Project");
    btnlayout->addWidget(btncalib);
    btnlayout->addWidget(btnproject);
    layout->addLayout(btnlayout);
}

void ImuCalibrationWidget::addImage(CvImageStamped & image)
{
    images.push_back(image);
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
        imus[id].push_back(imu);
    }
}

