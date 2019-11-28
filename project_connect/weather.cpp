#include "weather.h"

#define ZERO_KELVIN 273.15

Weather::Weather()
{
    m_nam = new QNetworkAccessManager(this);

    QNetworkConfigurationManager ncm;
    m_ns = new QNetworkSession(ncm.defaultConfiguration(), this);

    connect(m_ns, SIGNAL(opened()), this, SLOT(networkSessionOpened()));

    if(m_ns->isOpen())
        networkSessionOpened();

    m_ns->open();
}

QString Weather::niceTemperatureString(double temp)
{
    return QString::number(qRound(temp-ZERO_KELVIN)) + QChar(0xB0);
}

void Weather::networkSessionOpened()
{
    qDebug() << "Connecté";
    updateWeather();
}

void Weather::updateWeather()
{
    QUrl url("http://api.openweathermap.org/data/2.5/weather");
    QUrlQuery query;

    query.addQueryItem("q", m_city);
    query.addQueryItem("mode", "json");
    query.addQueryItem("APPID", m_id);
    url.setQuery(query);

    m_repToday = m_nam->get(QNetworkRequest(url));

    connect(m_repToday, &QNetworkReply::finished,
            this, &Weather::handleTodayNetworkData);
}

void Weather::handleTodayNetworkData()
{
    if(!m_repToday){
        qDebug() << "error";
        return;
    }

    if(!m_repToday->error()){
        QJsonDocument document = QJsonDocument::fromJson(m_repToday->readAll());

        if(document.isObject()){
            QJsonObject obj = document.object();
            QJsonObject tempObject;
            QString description;
            QString temperature;
            QString temp_min;
            QString temp_max;
            int humiInt;
            QString humidity;
            double windSpeedDouble;
            QString windSpeed;

            if(obj.contains(QStringLiteral("weather"))){
                QJsonArray weatherArray  = obj.value(QStringLiteral("weather")).toArray();
                tempObject = weatherArray.at(0).toObject();
                description = tempObject.value(QStringLiteral("description")).toString();
                qDebug() << description;
            }
            if(obj.contains(QStringLiteral("main"))){
                tempObject = obj.value(QStringLiteral("main")).toObject();
                temperature = niceTemperatureString(tempObject.value(QStringLiteral("temp")).toDouble());
                humiInt = tempObject.value(QStringLiteral("humidity")).toInt();
                humidity = QString::number(humiInt);
                temp_min = niceTemperatureString(tempObject.value(QStringLiteral("temp_min")).toDouble());
                temp_max = niceTemperatureString(tempObject.value(QStringLiteral("temp_max")).toDouble());
                qDebug() << temperature;
                qDebug() << humidity;
                qDebug() << temp_min;
                qDebug() << temp_max;
            }
            if(obj.contains(QStringLiteral("wind"))){
                tempObject = obj.value(QStringLiteral("wind")).toObject();
                windSpeedDouble = tempObject.value(QStringLiteral("speed")).toDouble();
                windSpeed = QString::number(windSpeedDouble);
                qDebug() << windSpeed;
            }
        }
    }

    QUrl url("http://api.openweathermap.org/data/2.5/forecast/daily");
    QUrlQuery query;

    query.addQueryItem("q", m_city);
    query.addQueryItem("mode", "json");
    query.addQueryItem("cnt", "3");
    query.addQueryItem("APPID", m_id);
    url.setQuery(query);

    m_repToday->deleteLater();

    m_repDayly = m_nam->get(QNetworkRequest(url));

    connect(m_repDayly, &QNetworkReply::finished,
            this, &Weather::handleWeekNetworkData);
}

void Weather::handleWeekNetworkData()
{
    if(!m_repDayly){
        qDebug() << "error";
        return;
    }

    if(!m_repDayly->error()){
        QJsonDocument document = QJsonDocument::fromJson(m_repDayly->readAll());
        if(document.isObject()){
            QJsonObject obj = document.object();
            if(obj.contains(QStringLiteral("list"))){
                QJsonArray list = obj.value(QStringLiteral("list")).toArray();
                for(uint8_t i = 1; i<list.count(); i++){
                    QJsonObject tempObject;
                    QJsonObject listObj = list.at(i).toObject();
                    QString description;
                    QString temperature;
                    QString temp_min;
                    QString temp_max;
                    int humiInt;
                    QString humidity;
                    double windSpeedDouble;
                    QString windSpeed;

                    if(listObj.contains(QStringLiteral("temp"))){
                        tempObject = listObj.value(QStringLiteral("temp")).toObject();
                        temp_min = niceTemperatureString(tempObject.value(QStringLiteral("min")).toDouble());
                        temp_max = niceTemperatureString(tempObject.value(QStringLiteral("max")).toDouble());
                        qDebug() << temp_min;
                        qDebug() << temp_max;
                    }
                    humiInt = listObj.value(QStringLiteral("humidity")).toInt();
                    humidity = QString::number(humiInt);

                    qDebug() << humidity;

                    if(listObj.contains(QStringLiteral("weather"))){
                        QJsonArray weatherArray  = listObj.value(QStringLiteral("weather")).toArray();
                        tempObject = weatherArray.at(0).toObject();
                        description = tempObject.value(QStringLiteral("description")).toString();
                        qDebug() << description;
                    }
                    windSpeedDouble = listObj.value(QStringLiteral("speed")).toDouble();
                    windSpeed = QString::number(windSpeedDouble);
                    qDebug() << windSpeed;

                }

            }

        }

    }
    else
        qDebug() << m_repDayly->error();
}



void Weather::citychanged(QString city)
{
    m_city = city;
}


