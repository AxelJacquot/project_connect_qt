#include "mainwindow.h"
#include <QHostAddress>
#include <QtMqtt>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout();
    /*mainLayout->addWidget(mqttLabel);
    QVBoxLayout *vboxMQTT = new QVBoxLayout();
    vboxMQTT->addWidget(addressLabel);
    vboxMQTT->addWidget(hostAddress);
    vboxMQTT->addWidget(portLabel);
    vboxMQTT->addWidget(hostPort);
    vboxMQTT->addWidget(buttonConnect);
    mainLayout->addLayout(vboxMQTT);*/

    QVBoxLayout *vboxMeasure = new QVBoxLayout();
    QPixmap flame;
    flame.load("../icon/favicon.ico");
    flameLabel->setPixmap(flame);
    vboxMeasure->addWidget(flameLabel);
    vboxMeasure->addWidget(temperature);
    vboxMeasure->addWidget(humidity);
    vboxMeasure->addWidget(preasure);
    vboxMeasure->addWidget(co);
    vboxMeasure->addWidget(alchqool);
    mainLayout->addLayout(vboxMeasure);


    QVBoxLayout *vboxExterior = new QVBoxLayout();
    QHBoxLayout *hboxToday = new QHBoxLayout();
    vboxExterior->addWidget(city);
    QVBoxLayout *vboxWeatherToday = new QVBoxLayout();
    vboxWeatherToday->addWidget(today);
    /*QPixmap pictureToday;
    pictureToday.load();*/
    weatherToday->setPixmap(QPixmap("../icon/sun.png"));
    vboxWeatherToday->addWidget(weatherToday);
    QVBoxLayout *vboxMeasureToday = new QVBoxLayout();
    vboxMeasureToday->addWidget(temperatureToday);
    vboxMeasureToday->addWidget(humidityToday);
    vboxMeasureToday->addWidget(windToday);
    hboxToday->addLayout(vboxWeatherToday);
    hboxToday->addLayout(vboxMeasureToday);
    QHBoxLayout *hboxOtherDays = new QHBoxLayout();
    QVBoxLayout *vboxTomorrow = new QVBoxLayout();
    vboxTomorrow->addWidget(tomorrow);
    weatherTomorrow->setPixmap(QPixmap("../icon/cloud.png"));
    vboxTomorrow->addWidget(weatherTomorrow);
    vboxTomorrow->addWidget(temperatureTomorrow);
    QVBoxLayout *vboxTwoDays = new QVBoxLayout();
    vboxTwoDays->addWidget(twodays);
    weatherTwoDays->setPixmap(QPixmap("../icon/storm.png"));
    vboxTwoDays->addWidget(weatherTwoDays);
    vboxTwoDays->addWidget(tempeartureTwoDays);

    hboxOtherDays->addLayout(vboxTomorrow);
    hboxOtherDays->addLayout(vboxTwoDays);

    vboxExterior->addLayout(hboxToday);
    vboxExterior->addLayout(hboxOtherDays);

    mainLayout->addLayout(vboxExterior);

    QWidget *widgetCentral = new QWidget();
    widgetCentral->setLayout(mainLayout);

    //m_weather = new Weather();

    server = new MqttHandler();

    this->setCentralWidget(widgetCentral);
}

MainWindow::~MainWindow()
{
}

