#pragma once
#include <QString>

class Data
{
public:
    Data(const QString &id,
         const QString &time,
         const QString &dlc,
         const QString &payload,
         bool isRX = false);
    quint32 count() const;
    bool isRX() const;
    QString id() const;
    QString time() const;
    QString dlc() const;
    QString payload() const;

private:
    quint32 _count;
    bool _isRX;
    QString _id;
    QString _time;
    QString _dlc;
    QString _payload;
};
