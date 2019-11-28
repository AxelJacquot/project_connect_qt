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

public slots:
    void networkSessionOpened(void);
    void updateWeather(void);
    void handleWeekNetworkData(void);
    void handleTodayNetworkData(void);
    void citychanged(QString city);

    
signals:
    void datachanged();
    void otherDaysWeather(QString description, QString temperature, QString);
    void todayWeatherChanged(QString description, QString temperature, QString humidity,
                             QString wind);
private:
    QString m_city = "Bordeaux";
    QString m_id = QStringLiteral("36496bad1955bf3365448965a42b9eac");
    QTimer delayWeather;

    QNetworkAccessManager *m_nam;
    QNetworkSession *m_ns;

    QNetworkReply *m_repToday;
    QNetworkReply *m_repDayly;
};

#endif // WEATHER_H
