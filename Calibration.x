N,CameraHub::Camera1,/home/alexanderhmw/SDK/RobotSDK_4.0/Module/CalibrationToolkit/lib/Debug/libCalibrationToolkit.so,Config.xml,0,1
N,CameraHub::Camera2,/home/alexanderhmw/SDK/RobotSDK_4.0/Module/CalibrationToolkit/lib/Debug/libCalibrationToolkit.so,Config.xml,0,1
N,ImageView::Viewer,/home/alexanderhmw/SDK/RobotSDK_4.0/Module/CalibrationToolkit/lib/Debug/libCalibrationToolkit.so,Config.xml,1,0
N,ImuCalibration::calibration, ,Config.xml,3,0
N,ImuDecoder::IMUDecoder::RazorASCII, ,Config.xml,1,1
N,ImuDecoder::IMUDecoder::RazorFireFly, ,Config.xml,1,1
N,ImuHub::IMU,/home/alexanderhmw/SDK/RobotSDK_4.0/Module/CalibrationToolkit/lib/Debug/libCalibrationToolkit.so,Config.xml,0,1
N,ImuMessageView::Viewer,/home/alexanderhmw/SDK/RobotSDK_4.0/Module/CalibrationToolkit/lib/Debug/libCalibrationToolkit.so,Config.xml,1,0
N,ImuRos::IMUROS, ,Config.xml,1,0
E,CameraHub::Camera1,0,ImageView::Viewer,0
E,CameraHub::Camera1,0,ImuCalibration::calibration,0
E,CameraHub::Camera2,0,ImuCalibration::calibration,1
E,ImuDecoder::IMUDecoder::RazorASCII,0,ImuCalibration::calibration,2
E,ImuDecoder::IMUDecoder::RazorASCII,0,ImuRos::IMUROS,0
E,ImuDecoder::IMUDecoder::RazorFireFly,0,ImuCalibration::calibration,2
E,ImuDecoder::IMUDecoder::RazorFireFly,0,ImuRos::IMUROS,0
E,ImuHub::IMU,0,ImuDecoder::IMUDecoder::RazorASCII,0
E,ImuHub::IMU,0,ImuDecoder::IMUDecoder::RazorFireFly,0
E,ImuHub::IMU,0,ImuMessageView::Viewer,0
