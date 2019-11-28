#include "configuration_connect.h"

QMqttClient *createClientConfiguration(QString hostAddress,
                                       uint16_t portHost)
{
    QMqttClient *client = new QMqttClient();
    if(portHost != 0 && hostAddress != ""){
        client->setPort(portHost);
        client->setHostname(hostAddress);
        //qreturn client;
    }
    return client;
}
