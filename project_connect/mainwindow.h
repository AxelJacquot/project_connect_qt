#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QTimer>
#include <QPushButton>
#include <QLineEdit>
#include <QDate>
#include <QTime>
#include <QSpinBox>
#include <QLabel>
#include <QLine>
#include <QMessageBox>
#include <QLayout>
#include <QHBoxLayout>
#include <QFormLayout>
#include <QIcon>
#include <QMainWindow>

#include <QDate>
#include <QTime>

#include <weather.h>
#include <mqtthandler.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void nowWeather(QString description, QString icon, QString temperature,
                    QString humidity, QString windspeed);
    void dayWeather(uint8_t countDay, QString description, QString icon, QString temp_max,
                           QString temp_min, QString humidity, QString windSpeed);
    void flameDisplay(int flame);
    void airqualityDisplay(QString co2, QString tvoc);
    void environmentDisplay(QString temp, QString humi, QString pres);
    void correctTime();
    void cityUpdate();

signals:

private:
    QLabel *mqttLabel = new QLabel("Connection to server");
    QPushButton *buttonConnect = new QPushButton("Connect");
    QLabel *addressLabel = new QLabel("Address:");
    QLineEdit *hostAddress = new QLineEdit();
    QLabel *portLabel = new QLabel("Port:");
    QSpinBox *hostPort = new QSpinBox();

    QLabel *interiorweatherLabel = new QLabel("Interior Weather");
    QLabel *measureLabel = new QLabel("Measure");
    QLabel *temperature = new QLabel("Temperature");
    QLabel *pressure = new QLabel("Preasure");
    QLabel *humidity = new QLabel("Humidity");
    QLabel *airquality = new QLabel("Air Quality");
    QLabel *co = new QLabel("CO2");
    QLabel *flameLabel = new QLabel("Flame");
    QLabel *alchqool = new QLabel("Alchool");

    QDate currentDate;
    QTime currentTime;
    void correctDate();

    QLabel *dateLabel = new QLabel("Date");
    QLabel *timeLabel = new QLabel("Time");

    QLabel *exteriorweatherLabel = new QLabel("Exterior Weather");

    QLabel *cityLabel = new QLabel("City");
    QLineEdit *city = new QLineEdit("Bordeaux");
    QLabel *countryLabel = new QLabel("Country");
    QLineEdit *country = new QLineEdit("fr");
    QPushButton *validateButton = new QPushButton("Validate");

    QLabel *today = new QLabel("Today");
    QLabel *weatherToday = new QLabel();
    QLabel *weatherDescriptionToday = new QLabel("Beau");
    QLabel *temperatureToday = new QLabel("25°C");
    QLabel *tempminToday = new QLabel("25°C");
    QLabel *tempmaxToday = new QLabel("25°C");
    QLabel *humidityToday = new QLabel("50%");
    QLabel *windToday = new QLabel("15km/h");

    QLabel *tomorrow = new QLabel("Tomorrow");
    QLabel *weatherTomorrow = new QLabel("Pluie");
    QLabel *weatherDescriptionTomorrow = new QLabel("Beau");
    QLabel *tempmaxTomorrow = new QLabel("28°C");
    QLabel *tempminTomorrow = new QLabel("28°C");
    QLabel *humidityTomorrow = new QLabel("15%");
    QLabel *windspeedTomorrow = new QLabel("3.6m/s");

    QLabel *twodays = new QLabel("Two Days");
    QLabel *weatherTwoDays = new QLabel("Pluie intensive");
    QLabel *weatherDescriptionTwoDays = new QLabel("Beau");
    QLabel *tempmaxTwoDays = new QLabel("26°C");
    QLabel *tempminTwoDays = new QLabel("26°C");
    QLabel *humidityTwoDays = new QLabel("15%");
    QLabel *windspeedTwoDays= new QLabel("3.6m/s");

    QLabel *threedays = new QLabel("Three Days");
    QLabel *weatherThreeDays = new QLabel("Pluie intensive");
    QLabel *weatherDescriptionThreeDays = new QLabel("Beau");
    QLabel *tempmaxThreeDays = new QLabel("26°C");
    QLabel *tempminThreeDays = new QLabel("26°C");
    QLabel *humidityThreeDays = new QLabel("15%");
    QLabel *windspeedThreeDays= new QLabel("3.6m/s");

    QLabel *fourdays = new QLabel("Four Days");
    QLabel *weatherFourDays = new QLabel("Pluie intensive");
    QLabel *weatherDescriptionFourDays = new QLabel("Beau");
    QLabel *tempmaxFourDays = new QLabel("26°C");
    QLabel *tempminFourDays = new QLabel("26°C");
    QLabel *humidityFourDays = new QLabel("15%");
    QLabel *windspeedFourDays= new QLabel("3.6m/s");

    MqttHandler *server;
    Weather *m_weather;
};
#endif // MAINWINDOW_H
