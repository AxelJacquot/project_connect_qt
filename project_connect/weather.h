#ifndef WEATHER_H
#define WEATHER_H

#include <QObject>
#include <QNetworkConfigurationManager>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QNetworkSession>
#include <QUrl>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QStringLiteral>
#include <QJsonObject>
#include <QJsonArray>
#include <QTimer>

class Weather : public QObject
{
    Q_OBJECT
public:
    explicit Weather();
    QString niceTemperatureString(double temp);
    QString correctwindspeed(double speed);

    void citychanged(QString &city, QString &country);

public slots:
    void networkSessionOpened(void);
    void updateWeather(void);
    void handleWeekNetworkData(void);
    void handleTodayNetworkData(void);

    
signals:
    void datachanged();
    void nowWeatherChanged(QString description, QString icon, QString temperature,
                           QString humidity, QString windspeed);
    void dayWeatherChanged(uint8_t countDay, QString description, QString icon, QString temp_max,
                           QString temp_min, QString humidity, QString windSpeed);
private:
    QString m_city = "Bordeaux";
    QString m_country = "fr";
    QString m_id = QStringLiteral("36496bad1955bf3365448965a42b9eac");
    QTimer *delayWeather = new QTimer();

    QNetworkAccessManager *m_nam;
    QNetworkSession *m_ns;

    QNetworkReply *m_repToday;
    QNetworkReply *m_repDayly;
};

#endif // WEATHER_H
