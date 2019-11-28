#include "mqtthandler.h"
#include <QDebug>

MqttHandler::MqttHandler(QString name, uint16_t port)
{
    hostName = name;
    hostPort = port;
    client->setPort(hostPort);
    client->setHostname(hostName);
    //client = createClientConfiguration(hostName, hostPort);
}

void MqttHandler::updateMessage(const QMqttMessage &message)
{
    quint32 rc;
    QString topic = "/data";
    QJsonObject jobject;

    qDebug() << "MQTT message" << message.topic().name() << message.payload();

    QStringList topic_parsed = message.topic().name().split('/');
    QString topic_origin = topic_parsed[0];
    QString topic_destination = topic_parsed[1];

    QString new_topic = "Error";

    QJsonDocument dataJSON = QJsonDocument::fromJson(message.payload());
    QJsonObject payload = dataJSON.object();

    if(topic_origin == "server"){
        new_topic = "/gateway/" + topic_destination;
    }else{
        qDebug() << "ERROR : le topic " << message.topic().name() << " n'est pas pris en charge";
    }
    qDebug() << new_topic;
    this->publishData(new_topic, payload); 
}

void MqttHandler::onSubscribed(const QString &topic)
{
    QMqttTopicFilter topicFilter;
    topicFilter.setFilter(topic);
    QMqttSubscription *sub = client->subscribe(topicFilter);
    if(sub){
        connect(sub, &QMqttSubscription::messageReceived, this, &MqttHandler::updateMessage);
    }
}

void MqttHandler::updateStatus(QMqttClient::ClientState state)
{
    switch (state) {
    case QMqttClient::Disconnected:
        qDebug() << "Client Disconnect";
        break;
    case QMqttClient::Connecting:
        qDebug() << "Client Connecting";
        break;
    case QMqttClient::Connected:
        qDebug() << "Client Connect";
        break;
    }
}

void MqttHandler::publishData(QString &topic, QJsonObject &jobject)
{
    QMqttTopicFilter topicFilter;
    topicFilter.setFilter(topic);
    QJsonDocument data(jobject);
    client->publish(topic,data.toJson());
}
