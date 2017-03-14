#ifndef IMUCALIBRATIONWIDGET_H
#define IMUCALIBRATIONWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QScrollArea>
#include <QSplitter>
#include <QTabWidget>
#include <QListWidget>
#include <QPushButton>
#include <glviewer.h>

#include <opencv2/opencv.hpp>
#include <geometry_msgs/Pose.h>

struct ImuCalibData
{

};


class ImuCalibrationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImuCalibrationWidget(QString deviceids, QWidget *parent = 0);
public:
    QVector<cv::Mat> images;
    QVector<QVector<geometry_msgs::Pose> > imuposes;
    QVector<QVector<ImuCalibData> > imageposes;
protected:
    QVBoxLayout * layout;
    QSplitter * splitter;

    QScrollArea * scrollarea;
    QLabel * imageview;

    QTabWidget * imuviewtabs;
    QVector<RobotSDK::GLViewer *> imuviewers;

    QListWidget *

    QHBoxLayout * btnlayout;
    QPushButton * btncalib;
    QPushButton * btnproject;
signals:

public slots:
};

#endif // IMUCALIBRATIONWIDGET_H
