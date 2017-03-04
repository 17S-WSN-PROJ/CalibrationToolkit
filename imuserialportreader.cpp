#include "imuserialportreader.h"

ImuSerialPortReader::ImuSerialPortReader()
    : QSerialPort(Q_NULLPTR)
{
    receiveflag=false;
    connect(this,SIGNAL(signalStartImu()),this,SLOT(slotStartImu()),Qt::QueuedConnection);
}

ImuSerialPortReader::~ImuSerialPortReader()
{
    if(receiveflag)
    {
        mutex.lock();
        receiveflag=false;
        mutex.unlock();
    }
}

QList<QString> ImuSerialPortReader::getPortList()
{
    QList<QSerialPortInfo> list=QSerialPortInfo::availablePorts();
    QList<QString> portlist;
    for(int i=0;i<list.size();i++)
    {
        portlist.push_back(list[i].portName());
    }
    return portlist;
}

void ImuSerialPortReader::startImu()
{
    mutex.lock();
    receiveflag=true;
    mutex.unlock();
    emit signalStartImu();
}

void ImuSerialPortReader::stopImu()
{
    mutex.lock();
    receiveflag=false;
    mutex.unlock();
}

QByteArray ImuSerialPortReader::getImuMessage()
{
    QByteArray message=messagequeue.front();
    mutex.lock();
    messagequeue.pop_front();
    mutex.unlock();
    return message;
}

bool ImuSerialPortReader::checkReceiveFlag()
{
    bool result;
    mutex.lock();
    result=receiveflag;
    mutex.unlock();
    return result;
}

void ImuSerialPortReader::slotStartImu()
{
    messagequeue.clear();
    if(this->open(QIODevice::ReadOnly))
    {
        while(checkReceiveFlag()&&this->waitForReadyRead())
        {
            while(this->canReadLine())
            {
                mutex.lock();
                messagequeue.push_back(this->readLine());
                mutex.unlock();
                emit signalImuReceived();
            }
        }
        this->close();
        if(checkReceiveFlag())
        {
            emit signalImuStopped();
        }
    }
    else
    {
        mutex.lock();
        receiveflag=false;
        mutex.unlock();
        emit signalImuConnectError();
    }
}


