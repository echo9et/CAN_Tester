#pragma once

#include <QObject>
#include <QDebug>

namespace CAN
{

class Listner : public QObject
{
    Q_OBJECT
public:
    Listner(int can_id, int socket);
    ~Listner();

private:
    int _socket;
    int _can_id;

public slots:
    void start();
    void stop();
signals:
    void sendDataLog(QString);
    void sendDataMonitor(quint32 id, int dlc, std::vector<int> payload);
    void finish();
};

}
