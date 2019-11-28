#ifndef CONFIGURATION_CONNECT_H
#define CONFIGURATION_CONNECT_H

#include <QString>
#include <QtMqtt>

struct Configuration{
    QString topic;
    QByteArray content;
    uint8_t qos;
    bool retain{false};
};

QMqttClient *createClientConfiguration(QString hostAddress = "",
                                       uint16_t portHost = 0);







#endif // CONFIGURATION_CONNECT_H
