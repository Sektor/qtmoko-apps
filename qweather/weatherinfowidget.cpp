#include "weatherinfowidget.h"
#include <QGridLayout>
#include <QLabel>
#include <QRect>
#include <QSpacerItem>
#include <QDebug>
#include <QImage>
#include <QPainter>
#include <QPixmap>


YWeatherInfo::YWeatherInfo(QWidget *parent)
   :QWidget(parent)
{
    country = new QLabel(tr("Country:"));
    region = new QLabel(tr("Region:"));
    date = new QLabel(tr("Date:"));
    city = new QLabel(tr("City:"));
    temperature = new QLabel(tr("Temp:"));
    countryValue = new QLabel;
    cityValue = new QLabel;
    regionValue = new QLabel;
    dateValue = new QLabel;
    chill = new QLabel(tr("Chill:"));
    chillValue = new QLabel;
    humdity= new QLabel(tr("Humdity:"));
    humdityValue = new QLabel;
    temperatureValue = new QLabel;
    condition = new QLabel(tr("Condition:"));
    conditionValue = new QLabel;
    pressure = new QLabel(tr("Barometer:"));
    pressureValue = new QLabel;
    weatherStateImg = new QLabel;
    weatherStateImg->setFixedSize(48, 48);
    //weatherStateImg->setBaseSize(QSize(32,32));
    //weatherStateImg->setGeometry(QRect(0,0,32,32));
    //weatherStateImg->setScaledContents(true);
    layout = new QGridLayout;
    layout->addWidget(country, 0, 0);
    layout->addWidget(countryValue, 0 ,1);
    layout->addWidget(region, 1, 0);
    layout->addWidget(regionValue, 1, 1);
    layout->addWidget(city, 2, 0);
    layout->addWidget(cityValue, 2, 1);
    layout->addWidget(temperature, 3, 0);
    layout->addWidget(temperatureValue, 3, 1);
    layout->addWidget(condition, 4, 0);
    layout->addWidget(conditionValue, 4, 1);
    layout->addWidget(weatherStateImg,4,2);
    layout->addWidget(pressure,5,0);
    layout->addWidget(pressureValue, 5, 1);
    layout->addWidget(chill, 6,0);
    layout->addWidget(chillValue, 6, 1);
    layout->addWidget(humdity, 7, 0);
    layout->addWidget(humdityValue, 7, 1);
    QSpacerItem *spacer = new QSpacerItem(20,40, QSizePolicy::Maximum, QSizePolicy::Expanding);
    layout->addItem(spacer, 8, 0);
    setLayout(layout);
}

void YWeatherInfo::getInfo(QStringList info)
{
    countryValue->setText(info.at(1));
    regionValue->setText(info.at(2));
    cityValue->setText(info.at(3));
    QString temp;
    QString pressurePref;
    qDebug() << info.size();
    if(info.at(5) == "c")
    {

        temp = " C";
        pressurePref = " mb";
    }
    else
    {
        temp = " F";
        pressurePref = " inc";
    };
    temperatureValue->setText(info.at(4)+temp);
    conditionValue->setText(info.at(6));
    pressureValue->setText(info.at(10)+ pressurePref);
    QString ico = (QString("./pics/qweather/state/%1").arg(info.at(7)));
    weatherStateImg->setPixmap(QPixmap(ico));
    //weatherStateImg->setText(info.at(6));
    qDebug() << "Condition picture:" << ico;
    chillValue->setText(info.at(8));
    humdityValue->setText(info.at(9)+" %");
}
