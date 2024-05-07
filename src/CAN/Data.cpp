#include "Data.h"

Data::Data(const QString &id, const QString &time, const QString &dlc, const QString &payload)
{
    static quint32 count = 0;
    _count = ++count;
    _id = id;
    _time = time;
    _dlc = dlc;
    _payload = payload;
}

quint32 Data::count() const
{
    return _count;
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
