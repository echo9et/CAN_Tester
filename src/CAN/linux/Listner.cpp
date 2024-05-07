#include "Listner.h"

#include <unistd.h>
#include <net/if.h>
#include <sys/ioctl.h>
#include <sys/socket.h>

#include <linux/can.h>
#include <linux/can/raw.h>

using namespace CAN;

Listner::Listner(int can_id, int socket) :
    _can_id(can_id),
    _socket(socket)
{
    qDebug() << "Listner::Listner listen " << _socket;
}

Listner::~Listner()
{
    qDebug() << "Listner::~Listner delete " << _socket;
}

void Listner::start()
{
    struct can_frame frame;
    int nbytes;
//    struct timeval tv;
//    tv.tv_sec = 1000;
//    tv.tv_usec = 0;
//    setsockopt(_socket, SOL_SOCKET, SO_RCVTIMEO, (const char*)&tv, sizeof tv);
    while( true )
    {
        nbytes = read(_socket, &frame, sizeof(struct can_frame));

        if( nbytes < 0 )
        {
            emit sendDataLog("CAN_RX ERROR: payload = " + QString::number(nbytes));
            return;
        }

        std::vector<int> payload;
        for( int i = 0; i < frame.can_dlc; ++i )
        {
            payload.push_back(frame.data[i]);
        }
        if ( frame.can_id == _can_id ) { qDebug() << " break "; break; }
        if ( frame.can_id > 4096 )
        {
            frame.can_id &= CAN_EFF_MASK;
        }
        emit sendDataMonitor(frame.can_id, frame.can_dlc, payload);
    }
    qDebug() << "FINISH!";
    emit finish();
}


void Listner::stop()
{
    qDebug() << "Listner::stop ";
}

