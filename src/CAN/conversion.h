#pragma once
#include <qmath.h>
#include <QString>
#include <QMap>
#include <QByteArray>
#include <sstream>

namespace CAN {

static quint32 HexToInt(QString str_hex)
{
    static QMap<QChar,int> hex = { {'0', 0}, {'1', 1}, {'2', 2}, {'3', 3}, {'4', 4},
                                       {'5', 5}, {'6', 6}, {'7', 7}, {'8', 8}, {'9', 9},
                                       {'a',10}, {'b', 11}, {'c', 12}, {'d', 13}, {'e', 14}, {'f', 15},
                                       {'A',10}, {'B', 11}, {'C', 12}, {'D', 13}, {'E', 14}, {'F', 15} };

    quint32 out = 0;
    for ( int index = 0; index < str_hex.size(); ++index )
        out += hex[str_hex[index]] * qPow(16, str_hex.size() - 1 - index);

    return out;
}

inline QString IntToHex(qint32 i)
{
    QByteArray array;
    array.append(i);

    return array.toHex().toUpper();
}

}
