#include "cameracalibrationwidget.h"

CameraCalibrationWidget::CameraCalibrationWidget(QWidget *parent)
    : QWidget(parent)
{
    layout=new QVBoxLayout();
    splitter=new QSplitter();
    scrollarea=new QScrollArea();
    image=new QLabel();
    grablist=new QListWidget();
    btnlayout=new QHBoxLayout();
    btnviewmode=new QPushButton("Review");
    btngrab=new QPushButton("Grab");
    btncalib=new QPushButton("Calibrate and Save");

    layout->addWidget(splitter);
    splitter->addWidget(scrollarea);
    scrollarea->setWidget(image);
    splitter->addWidget(grablist);

    layout->addLayout(btnlayout);
    btnlayout->addStretch();
    btnlayout->addWidget(btnviewmode);
    btnlayout->addWidget(btngrab);
    btnlayout->addWidget(btncalib);

    this->setLayout(layout);

    connect(btnviewmode,SIGNAL(clicked()),this,SLOT(slotSwitchViewMode()));
    connect(btngrab,SIGNAL(clicked()),this,SLOT(slotGrabData()));
    connect(btncalib,SIGNAL(clicked()),this,SLOT(slotCalibrate()));
    connect(grablist,SIGNAL(currentRowChanged(int)),this,SLOT(slotViewImage(int)));
}

void CameraCalibrationWidget::slotSwitchViewMode()
{
    if(reviewmode)
    {
        btnviewmode->setText("Reivew");
        btngrab->setText("Grab");
    }
    else
    {
        btnviewmode->setText("Capture");
        btngrab->setText("Delete");
    }
    reviewmode=!(reviewmode);
}

void CameraCalibrationWidget::slotGrabData()
{
    if(reviewmode)
    {
        int id=grablist->currentRow();
        if(id>=0)
        {
            calibimages.erase(calibimages.begin()+id);
            grid3dpoints.erase(grid3dpoints.begin()+id);
            grid2dpoints.erase(grid2dpoints.begin()+id);
            delete(grablist->takeItem(grablist->count()-1));
            grablist->setCurrentRow(-1);
            grablist->setCurrentRow(id);
        }
    }
    else
    {
        bool found=cv::findChessboardCorners(calibimage,patternum,grid2dpoint);
        if(found)
        {
            //cv::cornerSubPix(calibimage,grid2dpoint,cv::Size(11, 11), cv::Size(-1, -1),cv::TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
            calibimages.push_back(calibimage);
            grid3dpoints.push_back(grid3dpoint);
            grid2dpoints.push_back(grid2dpoint);
            grablist->addItem(QString("%1").arg(grablist->count()));
        }
    }
}

void CameraCalibrationWidget::slotCalibrate()
{
    if(calibimages.size()>0)
    {
        std::vector<cv::Mat> rvecs;
        std::vector<cv::Mat> tvecs;
        imagesize.height=calibimages[0].rows;
        imagesize.width=calibimages[0].cols;
        projectionerror=cv::calibrateCamera(grid3dpoints,grid2dpoints,imagesize,cameramat,distcoeff,rvecs,tvecs);
        cv::FileStorage fs(calibfilename.toStdString(),cv::FileStorage::WRITE);
        fs<<"ProjectionError"<<projectionerror;
        fs<<"CameraMat"<<cameramat;
        fs<<"DistCoeff"<<distcoeff;
        fs<<"ImageSize"<<imagesize;
        fs.release();
        qInfo("Finish Calibration.");
    }
}

void CameraCalibrationWidget::slotViewImage(int row)
{
    if(reviewmode&&row>=0)
    {
        cv::Mat tmpimage= calibimages[row].clone();
        cv::drawChessboardCorners(tmpimage,patternum,grid2dpoints[row],1);
        QImage img(tmpimage.data,tmpimage.cols,tmpimage.rows,tmpimage.step,QImage::Format_RGB888);
        img.rgbSwapped();
        image->setPixmap(QPixmap::fromImage(img));
        image->resize(img.size());
    }
}


