#pragma once

#include <QObject>
#include <QThread>
#include "../interfaces.h"
#include <unistd.h>

#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>

namespace CAN {

class Core : public BaseCore
{
    Q_OBJECT
    QThread ListenerCANThread;

public:
    Core(QObject *parent = nullptr);
    bool toConnect(const QString name_interfaces,const QString bitrate) override;
    void toDisconnect(QString) override;

    void send(QString id, QString value) override;
    QStringList getInterfaces() override;
    void init(){};
public slots:
    void slotGetData(quint32 id, int dlc, std::vector<int> payload);
signals:
    void startRxCan();

private:
    bool runConsole(const QString& path, const QStringList arg);
    bool upInterface(const QString& name_interface);
    bool downInterface(const QString& name_interface);
    bool addInterfaceVCAN(const QString& name_interface);
    bool setBitrateInterface(const QString& name_interface, const QString bitrate);

    int init_rx(const QString&);
    int init_tx(const QString&);

    struct sockaddr_can _addr_rx;
    struct ifreq _ifr_rx;
    struct sockaddr_can addr_tx;
    struct ifreq _ifr_tx;
    int _socket_tx;
    int _socket_rx;
};

}
