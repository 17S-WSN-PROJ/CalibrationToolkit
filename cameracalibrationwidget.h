#ifndef CAMERACALIBRATIONWIDGET_H
#define CAMERACALIBRATIONWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QScrollArea>
#include <QSplitter>
#include <QListWidget>
#include <QPushButton>
#include <opencv2/opencv.hpp>

class CameraCalibrationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CameraCalibrationWidget(QWidget *parent = 0);
public:
    QString calibfilename;
    double projectionerror;
    cv::Mat cameramat;
    cv::Mat distcoeff;
    cv::Size2i imagesize;
public:
    cv::Size2i patternum;
    cv::Size2f patternsize;
public:
    cv::Mat calibimage;
    bool reviewmode=0;
    std::vector<cv::Mat> calibimages;
    std::vector<cv::Point3f> grid3dpoint;
    std::vector<cv::Point2f> grid2dpoint;
    std::vector< std::vector<cv::Point3f> > grid3dpoints;
    std::vector< std::vector<cv::Point2f> > grid2dpoints;
public:
    QVBoxLayout * layout;
    QSplitter * splitter;
    QScrollArea * scrollarea;
    QLabel * image;
    QListWidget * grablist;
    QHBoxLayout * btnlayout;
    QPushButton * btnviewmode;
    QPushButton * btngrab;
    QPushButton * btncalib;
public Q_SLOTS:
    void slotSwitchViewMode();
    void slotGrabData();
    void slotCalibrate();
    void slotViewImage(int row);
};

#endif // CAMERACALIBRATIONWIDGET_H
