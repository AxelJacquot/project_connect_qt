#ifndef MQTTHANDLER_H
#define MQTTHANDLER_H

#include <QObject>
#include "configuration_connect.h"


class MqttHandler : public QObject
{
    Q_OBJECT
public:
    MqttHandler(QString name, uint16_t port);

public slots:
    void updateMessage(const QMqttMessage &msg);
    void onSubscribed(const QString &topic);
    void updateStatus(QMqttClient::ClientState state);
    void publishData(QString &topic, QJsonObject &jobject);

private:
    QString hostName;
    uint16_t hostPort;
    QMqttClient *client = new QMqttClient();
};

#endif // MQTTHANDLER_H
