#ifndef WEATHERINFOWIDGET_H
#define WEATHERINFOWIDGET_H

#include <QWidget>
class QRect;
class QLabel;
class QGridLayout;

class YWeatherInfo: public QWidget
{

    Q_OBJECT
    public:
        YWeatherInfo(QWidget *parent = 0);
    private:
        QRect       *imgRect;
        QLabel      *country;
        QLabel      *region;
        QLabel      *date;
        QLabel      *code;
        QLabel      *city;
        QLabel      *temperature;
        QLabel      *countryValue;
        QLabel      *condition;
        QLabel      *pressure;
        QLabel      *pressureValue;
        QLabel      *regionValue;
        QLabel      *cityValue;
        QLabel      *dateValue;
        QLabel      *codeValue;
        QLabel      *chill;
        QLabel      *chillValue;
        QLabel      *humdity;
        QLabel      *humdityValue;
        QLabel      *conditionValue;
        QLabel      *temperatureValue;
        QLabel      *weatherStateImg;
        QGridLayout *layout;
        //QString     *theme="";
      public:
        void getInfo(QStringList info);
//    private slots:
//        void update();
};

#endif // WEATHERINFOWIDGET_H
