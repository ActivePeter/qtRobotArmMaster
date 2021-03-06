#ifndef __SERIALMANAGER_H__
#define __SERIALMANAGER_H__
#include "QSerialPort"     //串口访问
#include "QSerialPortInfo" //串口端口信息访问
#include "PathBuilder/PathBuilder.h"

class SerialManager : public QObject
{
    Q_OBJECT
public:
    enum SlaveState
    {
        NotFound,
        FoundAndNotConnect,
        FoundAndConnect
    };
    // explicit SerialManager(QObject *parent = 0);
    void init();
    static SerialManager instance;
    void setSlaveState(SlaveState slaveState);
    SlaveState getSlaveState();
    void lookForDevice();
    void connectDevice();
    void disconnectDevice();
    void switchMotor(bool state);
    int pointReadStep = 0;

private:
    qint64 writeData(const char *data, qint64 len);
    QSerialPort *qSerialPort;
    void onDeviceFound(const QString &portName);
    bool getNextPoint(PathPointStruct3D &point);
    SlaveState slaveState;
    // QString portName;
    // bool deviceFound = false;
    // void onError();
public slots:
    void sendNextPointSet();
    void onError(QSerialPort::SerialPortError serialPortError);
    void receiveInfo();
};

#endif // __SERIALMANAGER_H__