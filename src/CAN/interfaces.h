#pragma once
#include <QObject>
#include <QStringList>

class BaseCore : public QObject
{
    Q_OBJECT
public:
    /// @brief соединение с интерфейсом CAN
    virtual bool toConnect(const QString name_interface, const QString bitrate) = 0;

    /// @brief отключение от интерфейса CAN
    virtual void toDisconnect(QString) = 0;

    /// @brief отправка фрейма в шину CAN
    virtual void send(QString id, QString value) = 0;

    /// @brief получение интерфейсов для подключния
    virtual  QStringList getInterfaces() = 0;
signals:
    /// @brief отправка сообщения в логгер
    void sendRecordLog(QString);

    /// @brief отправка данных в таблицу фреймов
    void sendDataMonitor(int id, int dlc, std::vector<int> payload);

protected:
    BaseCore(QObject *parent = nullptr) : QObject(parent) {}
    ~BaseCore() {}
};

