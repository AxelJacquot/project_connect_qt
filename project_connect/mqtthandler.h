#ifndef MQTTHANDLER_H
#define MQTTHANDLER_H

#include <QObject>
#include <QMqttClient>
#include <QMqttClient>
#include <QJsonDocument>
#include <QJsonObject>


class MqttHandler : public QObject
{
    Q_OBJECT
public:
    MqttHandler();
    ~MqttHandler();

public slots:
    void updateMessage(const QMqttMessage &msg);
    void onSubscribed(const QString &topic);
    void updateStatus(QMqttClient::ClientState state);
    void publishData(QString &topic, QJsonObject &jobject);

signals:
    void flameChanged(int flame);
    void airqualityChanged(QString co2, QString tvoc);
    void environmentChanged(QString temp, QString humidity, QString pressure);

private:
    QString hostName = "192.168.1.50";
    uint16_t hostPort = 1883;
    QMqttClient *client = new QMqttClient();
};

#endif // MQTTHANDLER_H
