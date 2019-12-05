#include "mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    QHBoxLayout *mainLayout = new QHBoxLayout();

    QVBoxLayout *vboxMeasure = new QVBoxLayout();
    flameLabel->setPixmap(QPixmap("../icon/flame_off.png"));
    vboxMeasure->addWidget(flameLabel);
    vboxMeasure->addWidget(temperature);
    vboxMeasure->addWidget(humidity);
    vboxMeasure->addWidget(pressure);
    vboxMeasure->addWidget(co);
    vboxMeasure->addWidget(airquality);
    mainLayout->addLayout(vboxMeasure);

    QVBoxLayout *vboxDate = new QVBoxLayout();
    correctDate();
    correctTime();
    vboxDate->addWidget(dateLabel);
    vboxDate->addWidget(timeLabel);

    QVBoxLayout *vboxExterior = new QVBoxLayout();

    QHBoxLayout *hboxCity = new QHBoxLayout();
    hboxCity->addWidget(cityLabel);
    hboxCity->addWidget(city);
    hboxCity->addWidget(countryLabel);
    hboxCity->addWidget(country);
    hboxCity->addWidget(validateButton);
    vboxExterior->addLayout(hboxCity);

    QHBoxLayout *hboxToday = new QHBoxLayout();
    QVBoxLayout *vboxWeatherToday = new QVBoxLayout();
    vboxWeatherToday->addWidget(today);
    weatherToday->setPixmap(QPixmap("../icon/01d"));
    vboxWeatherToday->addWidget(weatherToday);
    QVBoxLayout *vboxMeasureToday = new QVBoxLayout();
    vboxMeasureToday->addWidget(temperatureToday);
    vboxMeasureToday->addWidget(tempmaxToday);
    vboxMeasureToday->addWidget(tempminToday);
    vboxMeasureToday->addWidget(humidityToday);
    vboxMeasureToday->addWidget(windToday);
    hboxToday->addLayout(vboxWeatherToday);
    hboxToday->addLayout(vboxMeasureToday);

    QHBoxLayout *hboxOtherDays = new QHBoxLayout();

    QVBoxLayout *vboxTomorrow = new QVBoxLayout();
    vboxTomorrow->addWidget(tomorrow);
    weatherTomorrow->setPixmap(QPixmap("../icon/01d"));
    vboxTomorrow->addWidget(weatherTomorrow);
    vboxTomorrow->addWidget(weatherDescriptionTomorrow);
    vboxTomorrow->addWidget(tempmaxTomorrow);
    vboxTomorrow->addWidget(tempminTomorrow);
    vboxTomorrow->addWidget(humidityTomorrow);
    vboxTomorrow->addWidget(windspeedTomorrow);

    QVBoxLayout *vboxTwoDays = new QVBoxLayout();
    vboxTwoDays->addWidget(twodays);
    weatherTwoDays->setPixmap(QPixmap("../icon/01d"));
    vboxTwoDays->addWidget(weatherTwoDays);
    vboxTwoDays->addWidget(weatherDescriptionTwoDays);
    vboxTwoDays->addWidget(tempmaxTwoDays);
    vboxTwoDays->addWidget(tempminTwoDays);
    vboxTwoDays->addWidget(humidityTwoDays);
    vboxTwoDays->addWidget(windspeedTwoDays);

    QVBoxLayout *vboxThreeDays = new QVBoxLayout();
    vboxThreeDays->addWidget(threedays );
    weatherThreeDays->setPixmap(QPixmap("../icon/01d"));
    vboxThreeDays->addWidget(weatherThreeDays);
    vboxThreeDays->addWidget(weatherDescriptionThreeDays);
    vboxThreeDays->addWidget(tempmaxThreeDays);
    vboxThreeDays->addWidget(tempminThreeDays);
    vboxThreeDays->addWidget(humidityThreeDays);
    vboxThreeDays->addWidget(windspeedThreeDays);

    QVBoxLayout *vboxFourDays = new QVBoxLayout();
    vboxFourDays->addWidget(fourdays);
    weatherFourDays->setPixmap(QPixmap("../icon/01d"));
    vboxFourDays->addWidget(weatherFourDays);
    vboxFourDays->addWidget(weatherDescriptionFourDays);
    vboxFourDays->addWidget(tempmaxFourDays);
    vboxFourDays->addWidget(tempminFourDays);
    vboxFourDays->addWidget(humidityFourDays);
    vboxFourDays->addWidget(windspeedFourDays);

    hboxOtherDays->addLayout(vboxTomorrow);
    hboxOtherDays->addLayout(vboxTwoDays);
    hboxOtherDays->addLayout(vboxThreeDays);
    hboxOtherDays->addLayout(vboxFourDays);

    vboxExterior->addLayout(hboxToday);
    vboxExterior->addLayout(hboxOtherDays);

    mainLayout->addLayout(vboxDate);
    mainLayout->addLayout(vboxExterior);

    QWidget *widgetCentral = new QWidget();
    widgetCentral->setLayout(mainLayout);

    m_weather = new Weather();

    server = new MqttHandler();
    this->setStyleSheet("background-color:white;");
    int width = this->width();
    int height = this->height();
    this->setMaximumWidth(width);
    this->setMaximumHeight(height);
    this->setCentralWidget(widgetCentral);

    QTimer *second = new QTimer();

    second->start(1000);

    connect(second, &QTimer::timeout,
            this, &MainWindow::correctTime);

    connect(m_weather, &Weather::nowWeatherChanged,
            this, &MainWindow::nowWeather);
    connect(m_weather, &Weather::dayWeatherChanged,
            this, &MainWindow::dayWeather);

    connect(server, &MqttHandler::flameChanged,
            this, &MainWindow::flameDisplay);
    connect(server, &MqttHandler::environmentChanged,
            this, &MainWindow::environmentDisplay);
    connect(server, &MqttHandler::airqualityChanged,
            this, &MainWindow::airqualityDisplay);

    connect(validateButton, &QPushButton::clicked,
            this, &MainWindow::cityUpdate);

}

MainWindow::~MainWindow()
{
}

void MainWindow::nowWeather(QString description, QString icon, QString temperature,
                            QString humidity, QString windspeed)
{
    if(icon == "04d" || icon == "04n"){
        icon = "03d";
    }
    QString link = "../icon/" + icon + ".png";
    qDebug() << link;
    weatherToday->setPixmap(QPixmap(link));
    weatherDescriptionToday->setText(description);
    temperatureToday->setText("Température: " + temperature + "°C");
    humidityToday->setText("Humidity: " + humidity + "%");
    windToday->setText("Wind Speed: " + windspeed + "km/h");
}

void MainWindow::dayWeather(uint8_t countDay, QString description, QString icon,
                            QString temp_max, QString temp_min, QString humidity,
                            QString windSpeed)
{
    QString link;
    switch (countDay) {
    case 0:
        tempmaxToday->setText("Temperature max: " + temp_max + "°C");
        tempminToday->setText("Temperature min: " + temp_min + "°C");
        break;
    case 1:
        if(icon == "04d" || icon == "04n"){
            icon = "03d";
        }
        link = "../icon/" + icon + ".png";
        qDebug() << link;
        weatherTomorrow->setPixmap(QPixmap(link));
        weatherDescriptionTomorrow->setText(description);
        tempmaxTomorrow->setText("Temp max: " + temp_max + "°C");
        tempminTomorrow->setText("Temp min: " + temp_min + "°C");
        humidityTomorrow->setText("Hum: " + humidity + "%");
        windspeedTomorrow->setText("Wind: " + windSpeed + "km/h");
        break;
    case 2:
        if(icon == "04d" || icon == "04n"){
            icon = "03d";
        }
        link = "../icon/" + icon + ".png";
        qDebug() << link;
        weatherTwoDays->setPixmap(QPixmap(link));
        weatherDescriptionTwoDays->setText(description);
        tempmaxTwoDays->setText("Temp max: " + temp_max + "°C");
        tempminTwoDays->setText("Temp min: " + temp_min + "°C");
        humidityTwoDays->setText("Hum: " + humidity + "%");
        windspeedTwoDays->setText("Wind: " + windSpeed + "km/h");
        break;
    case 3:
        if(icon == "04d" || icon == "04n"){
            icon = "03d";
        }
        link = "../icon/" + icon + ".png";
        qDebug() << link;
        weatherThreeDays->setPixmap(QPixmap(link));
        weatherDescriptionThreeDays->setText(description);
        tempmaxThreeDays->setText("Temp max: " + temp_max + "°C");
        tempminThreeDays->setText("Temp min: " + temp_min + "°C");
        humidityThreeDays->setText("Hum: " + humidity + "%");
        windspeedThreeDays->setText("Wind: " + windSpeed + "km/h");
        break;
    case 4:
        if(icon == "04d" || icon == "04n"){
            icon = "03d";
        }
        link = "../icon/" + icon + ".png";
        qDebug() << link;
        weatherFourDays->setPixmap(QPixmap(link));
        weatherDescriptionFourDays->setText(description);
        tempmaxFourDays->setText("Temp max: " + temp_max + "°C");
        tempminFourDays->setText("Temp min: " + temp_min + "°C");
        humidityFourDays->setText("Hum: " + humidity + "%");
        windspeedFourDays->setText("Wind: " + windSpeed + "km/h");
        break;
    default:
        break;
    }
}

void MainWindow::flameDisplay(int flame)
{
    if(flame == 0)
        flameLabel->setPixmap(QPixmap("../icon/flame_off.png"));
    else{

        flameLabel->setPixmap(QPixmap("../icon/flame_on.png"));
        QMessageBox *message = new QMessageBox();
        message->information(this, "WARNING!!!!!!!!!!!",
                             "FIREEEEE!!!!",
                             message->Ok, message->Ok);
        delete message;
    }
}

void MainWindow::airqualityDisplay(QString co2, QString tvoc)
{
    co->setText("Co2: " + co2 +" ppm");
    airquality->setText("Air quality: " + tvoc + "%");
}

void MainWindow::environmentDisplay(QString temp, QString humi, QString pres)
{
    temperature->setText("Temperature: " + temp + "°C");
    humidity->setText("Humidity: " + humi + "%");
    pressure->setText("Pressure: " + pres + "hpa");
}

void MainWindow::correctDate()
{
    currentDate = QDate::currentDate();
    QString day = currentDate.toString("dddd dd MMMM yyyy");
    dateLabel->setText(day);
}

void MainWindow::correctTime()
{
    currentTime = QTime::currentTime();
    QString time  = currentTime.toString("HH:mm");
    timeLabel->setText(time);
    if (time == "00:00"){
        correctDate();
    }
}

void MainWindow::cityUpdate()
{
    QString cityUpdate = city->text();
    QString countryUpdate = country->text();
    m_weather->citychanged(cityUpdate, countryUpdate);
}
