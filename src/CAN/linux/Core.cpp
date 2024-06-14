#include "Core.h"
#include <sstream>
#include "Listner.h"
#include "../../domain.h"
#include "../conversion.h"
#include <qmath.h>
#include <QProcess>
#include <QStringList>
#include <QTime>

#define UP_INTERFACE   "./scripts/upCAN.sh"
#define DOWN_INTERFACE "./scripts/downCAN.sh"
#define ADD_INTERFACE  "./scripts/addVCAN.sh"
#define FIND_INTERFACE "./scripts/findCAN.sh"
#define SET_BITRATE_INTERFACE "./scripts/setBitrateCAN.sh"

#define BASH "/bin/sh"
#define NAME_VCAN "vcan0"

using namespace CAN;

Core::Core(QObject *parent)
    : BaseCore(parent)
{

}

bool Core::toConnect(QString name_interface, QString bitrate)
{
    bool status = true;

    if ( !downInterface(name_interface) )
    {
        emit sendRecordLog("ERROR: down interface " + name_interface);
        status = false;
    }

    if ( !status || !setBitrateInterface(name_interface, bitrate) )
    {
        emit sendRecordLog("ERROR: set bitrate on interface " + name_interface);
        status = false;
    }

    if ( !status || !upInterface(name_interface) )
    {
        emit sendRecordLog("ERROR: up interface " + name_interface);
        status = false;
    }

    if ( !status || init_rx(name_interface) != 0 || init_tx(name_interface) != 0 )
    {
        status = false;
    }

    status ? emit sendRecordLog("Удалсь подключиться к интерфейсу " + name_interface)   :
             emit sendRecordLog("Не удалсь подключиться к интерфейсу " + name_interface);
    return status;
}

void Core::toDisconnect(QString can_interface)
{
    send(CAN_LISTENER_ID, 0);
    emit sendRecordLog("Disconnect to " + can_interface);
    close(_socket_rx);
    close(_socket_tx);
}

void Core::send(QString id, QString payload)
{
    const QStringList data = payload.split(" ");

    struct can_frame frame;

    frame.can_id  = HexToInt(id);
    if ( id.size() > 3 )
    {
        frame.can_id |= CAN_EFF_FLAG;
    }

    frame.can_dlc = data.size();

    int index = 0;
    for ( const auto& value : data )
    {
        frame.data[index] = HexToInt(value);
        ++index;
    }

    if (write(_socket_rx, &frame, sizeof(struct can_frame)) != sizeof(struct can_frame)) {
        emit sendRecordLog("don`t write data to frame");
        return;
    }

    emit sendDataTX(frame.can_id, frame.can_dlc, data);

    return;
}

QStringList Core::getInterfaces()
{
    QStringList answer;
    QProcess console;

    console.start(BASH, QStringList() << FIND_INTERFACE);
    console.waitForFinished(-1);

    if ( console.exitCode() !=0 )
    {
        emit sendRecordLog("Error: ошибка при получение списка интерфейсов "
                           + QString::number(console.exitCode())
                           + console.readAllStandardError());
    }
    else
    {
        answer = QString(console.readAllStandardOutput()).split('\n');
        answer.pop_back();
    }

    if ( answer.size() == 0 )
    {
        const QString name = NAME_VCAN;
        if ( addInterfaceVCAN(name) )
        {
            answer << name;
        }
        else
        {
            emit sendRecordLog("ERROR: ошибка создания виртуального интерфейса " + name);
        }
    }
    return answer;
}

void Core::slotGetData(quint32 id, int dlc, std::vector<int> payload)
{
    static quint32 count = 0;
    QString _number(QString::number(++count));
    QString _id(QString::number(id));
    QString _time = QTime::currentTime().toString("hh::mm::ss::zzz");
    QString _dlc(QString::number(dlc));
    QString _payload;
    bool isFirst = true;
    for( const auto& value : payload )
    {
        if ( isFirst ) _payload += " ";
        else isFirst = !isFirst;
        _payload += QString::number(value);
    }
}

bool Core::runConsole(const QString& path, const QStringList arg)
{
    QProcess console;
    console.start(BASH, QStringList() << path << arg);
    console.waitForFinished(-1);
    if( console.exitCode() != 0 )
    {
        emit sendRecordLog( QString ( console.readAllStandardError() ) );
        return false;
    }
    return true;
}

bool Core::upInterface(const QString& name_interface)
{
    return runConsole(UP_INTERFACE, QStringList {name_interface});
}

bool Core::downInterface(const QString& name_interface)
{
    return runConsole(DOWN_INTERFACE, QStringList {name_interface});
}

bool Core::addInterfaceVCAN(const QString &name_interface)
{
    return runConsole(ADD_INTERFACE, QStringList {name_interface});
}

bool Core::setBitrateInterface(const QString& name_interface, const QString bitrate)
{
    // проверка виртуального интерфейса - не используется битрейт;
    if ( name_interface[0] == 'v' ) return true;

    return runConsole(SET_BITRATE_INTERFACE, QStringList {name_interface, bitrate});
}

int Core::init_rx(const QString& can_interface)
{
    _socket_rx = socket(PF_CAN, SOCK_RAW, CAN_RAW);
    if ( _socket_rx < 0 )
    {
        emit sendRecordLog("CANTester::init_rx error created socket");
        return 1;
    }

    strncpy(_ifr_rx.ifr_name, can_interface.toStdString().c_str(), can_interface.size());
    ioctl(_socket_rx, SIOCGIFINDEX, &_ifr_rx);

    memset(&_addr_rx, 0, sizeof(_addr_rx));
    _addr_rx.can_family = AF_CAN;
    _addr_rx.can_ifindex = _ifr_rx.ifr_ifindex;

    if(bind(_socket_rx, (struct sockaddr *)&_addr_rx, sizeof(_addr_rx)) < 0)
    {
        emit sendRecordLog("CANTester::init_rx error to bind CAN socket. CAN stoppin!");
        return 1;
    }
    emit sendRecordLog("Connect to " + can_interface);

    {
        QThread  *thread = new QThread;
        Listner *listner = new Listner(CAN_LISTENER_ID, _socket_rx);

        qRegisterMetaType<sockaddr_can>("sockaddr_can&");
        qRegisterMetaType<std::vector<int>>("std::vector<int>&");

        listner->moveToThread(thread);

        connect(thread,  &QThread::started,         listner, &Listner::start);

        connect(listner, &Listner::finish,          thread,  &QThread::quit);
        connect(listner, &Listner::finish,          thread,  &QThread::deleteLater);
        connect(listner, &Listner::finish,          listner, &Listner::deleteLater);
        connect(listner, &Listner::sendDataLog,     this,    &Core::sendRecordLog);
        connect(listner, &Listner::sendDataMonitor, this,    &Core::sendDataMonitor);

        thread->start();
    }
    return 0;
}

int Core::init_tx(const QString& can_interface)
{
    if ( (_socket_tx = socket(PF_CAN, SOCK_RAW, CAN_RAW)) < 0 )
    {
        emit sendRecordLog("ну удалось подключиться к сокету");
        return 1;
    }

    strncpy(_ifr_tx.ifr_name, can_interface.toStdString().c_str(), can_interface.size());
    ioctl(_socket_tx, SIOCGIFINDEX, &_ifr_tx);

//    memset(&addr_tx, 0, sizeof(addr_tx));
//    addr_tx.can_family = AF_CAN;
//    addr_tx.can_ifindex = _ifr_tx.ifr_ifindex;

    return 0;
}
