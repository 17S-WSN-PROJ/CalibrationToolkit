N,CameraHub::Camera1, ,Config.xml,0,1
N,CameraHub::Camera2, ,Config.xml,0,1
N,ImageView::Viewer, ,Config.xml,1,0
N,ImuCalibration::calibration, ,Config.xml,3,0
N,ImuHub::IMU, ,Config.xml,0,1
N,ImuRos::IMUROS, ,Config.xml,1,0
E,CameraHub::Camera1,0,ImuCalibration::calibration,1
E,CameraHub::Camera2,0,ImageView::Viewer,0
E,CameraHub::Camera2,0,ImuCalibration::calibration,2
E,ImuHub::IMU,0,ImuCalibration::calibration,0
E,ImuHub::IMU,0,ImuRos::IMUROS,0
