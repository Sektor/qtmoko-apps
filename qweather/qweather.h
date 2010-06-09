#ifndef QWEATHER_H
#define QWEATHER_H

#include <QObject>
#include <QFile>
#include <QUrl>
#include <QDomDocument>
#include <QSettings>

class QHttp;

class QWeather : public QObject
{
    Q_OBJECT
public:
    QWeather();
   // void exec();
    QStringList     getToday();
private:
    QHttp           *http;
    QString         xmldoc;
    QByteArray      getStream();
    void            getSettings();
    void            parcer(QDomDocument doc);
    QString         cityCode;
    QString         cf;
    QString         region;
    QString         country;
    QString         city;
    QString         chill;
    QString         temperature;
    QString         tomorrow_day;
    QString         tomorrow_code;
    QString         d_a_t;
    QString         d_a_t_low;
    QString         d_a_t_high;
    QString         d_a_t_condition;
    QString         d_a_t_code;
    QString         temperature_tomorrow_low;
    QString         temperature_tomorrow_high;
    QString         temperature_tomorrow_condition;
    QString         condition;
    QString         pressure;
    QString         humidity;
    QString         zip;
    QString         today_code;
    QString         updateFrequency;
    QString         condition_code;
    //QString     uncompress();
private slots:
    void            sendRequest();
    void            requestDone(bool error);
    void            uncompress(QByteArray data);
    void            requestState(int param);
public slots:
    void            exec();
signals:
    void            update();
    void            settingsReaded();
    void            streamReadFinished(QByteArray data);
    void            extractFinished(QString doc);
};


#endif // QWEATHER_H
