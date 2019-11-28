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

#include <weather.h>
#include <mqtthandler.h>

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:


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
    QLabel *preasure = new QLabel("Preasure");
    QLabel *humidity = new QLabel("Humidity");
    QLabel *airquality = new QLabel("Air Quality");
    QLabel *co = new QLabel("CO2");
    QLabel *flameLabel = new QLabel("Flame");
    QLabel *alchqool = new QLabel("Alchool");

    QLabel *exteriorweatherLabel = new QLabel("Exterior Weather");
    QLineEdit *city = new QLineEdit();
    QLabel *today = new QLabel("Today");
    QLabel *weatherToday = new QLabel("Beau");
    QLabel *temperatureToday = new QLabel("25°C");
    QLabel *humidityToday = new QLabel("50%");
    QLabel *windToday = new QLabel("15km/h");
    QLabel *tomorrow = new QLabel("Tomorrow");
    QLabel *weatherTomorrow = new QLabel("Pluie");
    QLabel *temperatureTomorrow = new QLabel("28°C");
    QLabel *twodays = new QLabel("Two Days");
    QLabel *weatherTwoDays = new QLabel("Pluie intensive");
    QLabel *tempeartureTwoDays = new QLabel("26°C");

    MqttHandler *server;
    Weather *m_weather;
};
#endif // MAINWINDOW_H
