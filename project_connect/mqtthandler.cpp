#include "mqtthandler.h"
#include <QDebug>

MqttHandler::MqttHandler()
{
    connect(client, &QMqttClient::stateChanged, this, &MqttHandler::updateStatus);
    client->setPort(hostPort);
    client->setHostname(hostName);
    client->connectToHost();
    //client = createClientConfiguration(hostName, hostPort);
}

void MqttHandler::updateMessage(const QMqttMessage &message)
{
    quint32 rc;
    QString topic = "/data";
    QJsonObject jobject;

    qDebug() << "MQTT message" << message.topic().name() << message.payload();

    QStringList topic_parsed = message.topic().name().split('/');
    QString topic_origin = topic_parsed[1];
    QString topic_destination = topic_parsed[2];

    QString new_topic = "Error";

    QJsonDocument dataJSON = QJsonDocument::fromJson(message.payload());
    QJsonObject payload = dataJSON.object();
    QJsonObject tempObject;

    if(topic_origin == "server"){
        new_topic = "/gateway/" + topic_destination;
        if(topic_destination == "flame"){
            qDebug() << "Flame";
            QString flame;
            if(payload.contains("data")){
                flame = payload.value("data").toString();
            }
            qDebug() << "Flame :" << flame;
        }
        if(topic_destination == "air_quality"){
            qDebug() << "Air Quality";
            QString data_co2, data_tvoc;
            if(payload.contains("data_co2")){
               data_co2 = payload.value("data_co2").toString();
            }
            if(payload.contains("data_tvoc")){
                data_tvoc = payload.value("data_tvoc").toString();
            }
            qDebug() << "Co2: " << data_co2;
            qDebug() << "Tvoc: " << data_tvoc;

        }
        if(topic_destination == "weather"){

            qDebug() << "Weather";
            int humidityInt = 0, pressureInt = 0;
            double tempDouble = 0;
            QString temp, humidity, pressure;
            if(payload.contains("temperature")){
                tempDouble = payload.value("temperature").toDouble();
                temp = QString::number(tempDouble);
            }
            if(payload.contains("humidity")){
                humidityInt = payload.value("humidity").toInt();
                humidity = QString::number(humidityInt);
            }
            if(payload.contains("pressure")){
                pressureInt = payload.value("pressure").toInt();
                pressure = QString::number(pressureInt);
            }
            qDebug() << "Temperature: " << temp;
            qDebug() << "Humidity: : " << humidity;
            qDebug() << "Preasure: : " << pressure;
        }

    }else{
        qDebug() << "ERROR : le topic " << message.topic().name() << " n'est pas pris en charge";
    }

}

void MqttHandler::onSubscribed(const QString &topic)
{
    QMqttTopicFilter topicFilter;
    topicFilter.setFilter(topic);
    QMqttSubscription *sub = client->subscribe(topicFilter, 0);
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
        QString topic = "/server/#";
        onSubscribed(topic);
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
