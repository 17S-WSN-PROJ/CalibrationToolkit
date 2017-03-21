#ifndef IMUCALIBRATIONWIDGET_H
#define IMUCALIBRATIONWIDGET_H

#include <QWidget>
#include <QLayout>
#include <QLabel>
#include <QScrollArea>
#include <QSplitter>
#include <QTabWidget>
#include <QListWidget>
#include <QTableWidget>
#include <QPushButton>
#include <QTime>
#include <QMap>
#include <glviewer.h>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>

#include <opencv2/opencv.hpp>

struct CvImageStamped
{
    QTime timestamp;
    cv::Mat image;
};

struct ImuStamped
{
    QTime timestamp;
    double ax,ay,az;
    double qw,qx,qy,qz;
};

class ImuCalibrationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ImuCalibrationWidget(QString devices, QWidget *parent = 0);
protected:
    QList<QString> devicelist;
    QMap<QString,int> devicemap;
protected:
    bool recordflag;
    QVector<CvImageStamped> images;
    QVector<QVector<ImuStamped> > imus;
protected:
    QVBoxLayout * layout;
    QSplitter * splitter;

    QScrollArea * scrollarea;
    QLabel * imageview;

    QTabWidget * imuviewtabs;
    float axespts[18]={0,0,0
                      ,1,0,0
                      ,0,0,0
                      ,0,1,0
                      ,0,0,0
                      ,0,0,1};
    float axeclrs[18]={1,0,0
                      ,1,0,0
                      ,0,1,0
                      ,0,1,0
                      ,0,0,1
                      ,0,0,1};
    QVector<RobotSDK::GLViewer *> imuviewers;
    QVector<GLuint> imudisplist;

    QTableWidget * calibdataview;

    QHBoxLayout * btnlayout;
    QPushButton * btnstart;
    QPushButton * btnsave;

public:
    void addImage(CvImageStamped & image);
    void addImu(ImuStamped & imu, QString deviceid);
    void clearData();

public Q_SLOTS:
    void slotStartRecord();
    void slotSaveRecord();
};

#endif // IMUCALIBRATIONWIDGET_H
