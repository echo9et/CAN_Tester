#pragma once
#include <QObject>
#include "linux/Core.h"
#include "DataModel.h"

namespace CAN {

class Tester : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QStringList interfaces READ interfaces CONSTANT)
public:
    Tester(QObject *parent = 0);
    ~Tester();

    const QStringList interfaces();
    void setInterfaces( const QStringList &comboList);
    DataModel &getDataMonitoring();

public slots:
    void toConnect(QString, QString);
    void toDisconnect(QString);    
    void toSend(QString, QString);
    void getData(quint32 id, int dlc, std::vector<int> payload);

private:
    QStringList _interfaces;
    Core *_core;
    DataModel _dataModel;
signals:
    void sendRecordLog(QString);
};

}
