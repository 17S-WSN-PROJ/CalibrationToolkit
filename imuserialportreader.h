#ifndef IMUSERIALPORTREADER_H
#define IMUSERIALPORTREADER_H

#include <QObject>
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMutex>
#include <QThread>
#include <QQueue>

class ImuSerialPortReader : public QSerialPort
{
    Q_OBJECT
public:
    explicit ImuSerialPortReader();
    ~ImuSerialPortReader();
public:
    static QList<QString> getPortList();

protected:
    QMutex mutex;
    bool receiveflag;
    QQueue<QByteArray> messagequeue;

public:
    void startImu();
    void stopImu();
    QByteArray getImuMessage();
Q_SIGNALS:
    void signalStartImu();
    void signalImuReceived();
    void signalImuStopped();
    void signalImuConnectError();
protected:
    bool checkReceiveFlag();
protected Q_SLOTS:
    void slotStartImu();
};

#endif // IMUSERIALPORTREADER_H
