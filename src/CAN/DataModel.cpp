#include "DataModel.h"

DataModel::DataModel(QObject *parent)
    : QAbstractListModel(parent)
{

}

void DataModel::addData(const Data &data)
{
    beginInsertRows(QModelIndex(), rowCount(), rowCount());
    _data << data;
    endInsertRows();
}

int DataModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent);
    return _data.count();
}

QVariant DataModel::data(const QModelIndex &index, int role) const
{
    if (index.row() < 0 || index.row() >= _data.count())
    {
        return QVariant();
    }

    const Data &Data = _data[index.row()];
    if (role == CountRole)
        return Data.count();
    else if (role == IsRX)
        return Data.isRX();
    else if (role == IdRole)
        return Data.id();
    else if (role == TimeRole)
        return Data.time();
    else if (role == DlcRole)
        return Data.dlc();
    else if (role == PayloadRole)
        return Data.payload();
    return QVariant();
}

const QList<Data> &DataModel::getData() const
{
    return _data;
}

QHash<int, QByteArray> DataModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[CountRole] = "count";
    roles[IsRX] = "isRX";
    roles[IdRole] = "id";
    roles[TimeRole] = "time";
    roles[DlcRole] = "dlc";
    roles[PayloadRole] = "payload";
    return roles;
}
