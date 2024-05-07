#pragma once

#include <QString>
#include <QAbstractListModel>
#include "Data.h"

class DataModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum DataRoles {
        CountRole = Qt::UserRole + 1,
        IdRole,
        TimeRole,
        DlcRole,
        PayloadRole
    };

    DataModel(QObject *parent = nullptr);

    void addData(const Data &data);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    const QList<Data> &getData() const;

protected:
    QHash<int, QByteArray> roleNames() const;
private:
    QList<Data> _data;
};
