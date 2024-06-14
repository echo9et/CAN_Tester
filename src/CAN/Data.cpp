#include "Data.h"

Data::Data(const QString &id, const QString &time, const QString &dlc, const QString &payload, bool isRX)
    : _isRX(isRX) , _id(id), _time(time), _dlc(dlc), _payload(payload)
{
    static quint32 count = 0;
    _count = ++count;
}

quint32 Data::count() const
{
    return _count;
}

bool Data::isRX() const
{
    return _isRX;
}

QString Data::id() const
{
    return _id;
}

QString Data::time() const
{
    return _time;
}

QString Data::dlc() const
{
    return _dlc;
}

QString Data::payload() const
{
    return _payload;
}
