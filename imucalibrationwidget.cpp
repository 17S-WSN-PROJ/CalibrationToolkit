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
    imuposes.resize(n);
    imageposes.resize(n);
}

