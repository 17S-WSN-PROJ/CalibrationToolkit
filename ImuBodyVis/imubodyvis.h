#ifndef IMUBODYVIS_H
#define IMUBODYVIS_H

#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>

#include <rosinterface.h>
#include <sensor_msgs/Imu.h>
#include <visualization_msgs/MarkerArray.h>
#include <Eigen/Eigen>

class ImuBodyVis : public QWidget
{
    Q_OBJECT
public:
    explicit ImuBodyVis(QWidget *parent = 0);
protected:
    RobotSDK::ROSSub<sensor_msgs::ImuConstPtr> * rosimu_thigh;
    RobotSDK::ROSSub<sensor_msgs::ImuConstPtr> * rosimu_shank;
    RobotSDK::ROSSub<sensor_msgs::ImuConstPtr> * rosimu_foot;
    Eigen::Matrix3d init_thigh_rot;
    Eigen::Matrix3d init_shank_rot;
    Eigen::Matrix3d init_foot_rot;
signals:

public slots:
};

#endif // IMUBODYVIS_H
