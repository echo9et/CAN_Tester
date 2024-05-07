#include "Tester.h"
#include <QDebug>
#include <QDateTime>
#include "conversion.h"

using namespace CAN;

Tester::Tester(QObject *parent) :
    QObject(parent),
    _core(new Core(parent))
{

    connect(_core, &Core::sendRecordLog,
            this,  &Tester::sendRecordLog);

    connect(_core, &Core::sendDataMonitor,
            this,  &Tester::getData);
    _core->init();
    _interfaces = _core->getInterfaces();
}

Tester::~Tester()
{

}

const QStringList Tester::interfaces()
{
    return _interfaces;
}

void Tester::setInterfaces(const QStringList &interfaces)
{
    _interfaces = interfaces;
}

DataModel &Tester::getDataMonitoring()
{
    return _dataModel;
}

void Tester::toConnect(QString name_interface, QString bitrate)
{
    _core->toConnect(name_interface, bitrate);
}

void Tester::toDisconnect(QString name_interface)
{
    _core->toDisconnect(name_interface);
}

void Tester::toSend(QString id, QString payload)
{
    _core->send(id, payload);
}

void Tester::getData(quint32 id, int dlc, std::vector<int> payload)
{
    QString out_payload;
    for ( size_t i = 0; i < payload.size(); ++i )
    {
        if ( i != 0 ) out_payload += " ";
        out_payload += IntToHex(payload[i]);
    }

    _dataModel.addData({IntToHex(id),
                        QDateTime::currentDateTime().toString("hh:mm:ss:zzz"),
                        QString::number(dlc),
                        out_payload});
    qDebug() << "get data";
}
