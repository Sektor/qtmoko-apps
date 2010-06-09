#include "qweather.h"
#include <QSettings>
#include <QDebug>
#include <QHttp>
#include <QDomDocument>
#include <QHttpRequestHeader>
#include "gzip.h"

QWeather::QWeather()
{
    http = new QHttp;
    connect(this, SIGNAL(settingsReaded()), this, SLOT(sendRequest()));
    connect(http, SIGNAL(done(bool)), this, SLOT(requestDone(bool)));
    connect(this, SIGNAL(streamReadFinished(QByteArray)), this, SLOT(uncompress(QByteArray)));
    connect(http, SIGNAL(stateChanged(int)), this, SLOT(requestState(int)));
    connect(this, SIGNAL(update()), this, SLOT(sendRequest()));
}

void QWeather::exec()
{
    getSettings();
}

void QWeather::getSettings()
{
    qDebug() << "read settings";
    QSettings *settings = new QSettings("TQWeather", "YahooWeather");
    cityCode = settings->value("City", "44418").toString();
    cf = settings->value("TempType", "c").toString();
    emit settingsReaded();
    qDebug() << http->state();
}


void QWeather::sendRequest()
{
    QHttpRequestHeader header("GET", QString("/forecastrss?w=%1&u=%2").arg(cityCode).arg(cf)); //getQuery.toUtf8());
    http->setHost("weather.yahooapis.com");
    header.setValue("HOST", "weather.yahooapis.com");
    header.setValue("Content-Encoding", "gzip");
    header.setValue("X-Yahoo-Compressed",  "true");
    header.setValue("Accept-Encoding", "gzip");
    header.setValue("User-Agent", "TQWeather/0.3 (gzip)");
    http->request(header);
    qDebug() << "State" <<http->state();
    qDebug() << header.toString();
    qDebug() << "Error: " <<http->error();
    qDebug() << "Error string:" << http->errorString();

}

void QWeather::requestDone(bool error)
{
    qDebug() << "State: "<< http->state();
    if(error)
    {
        qDebug() << "Grrrrrr";
    }
    qDebug() << "Respondet encodings: "<< http->lastResponse().value("content-encoding");
    qDebug() << "request answer responded";
    QByteArray data;
    data = http->readAll();
    qDebug() << "Dr " <<http->lastResponse().values();
    qDebug() << "Grrrr " <<http->lastResponse().toString();
    if (http->lastResponse().value("content-encoding") == "gzip")
    {
        emit streamReadFinished(data);
    }
    else
    {
        qDebug() << "Content: " << data.constData();
        xmldoc = data.constData();
    }
}

void QWeather::uncompress(QByteArray data)
{
    qDebug() << "Stream responded";
    qDebug() << "Stream size: " << data.size();
    char *buff = inf(data.constData(), data.size());
    xmldoc = QString::fromUtf8(buff);
    free(buff);
}

void QWeather::requestState(int param)
{
    qDebug() << "Request in state: "<< param;
}

void QWeather::parcer(QDomDocument doc)
{
    qDebug() << "parcer";
    QDomElement root = doc.documentElement();
    QDomNode n = root.firstChild();
    n = root.firstChild();
    n = n.firstChild();
    while(!n.isNull())
    {
       QDomElement e = n.toElement();

       if(!e.isNull())
       {
          if(e.tagName() == "yweather:location")
          {
             city = e.attribute("city", "");
             region = e.attribute("region", "");
             country = e.attribute("country", "");
          }
          else if(e.tagName() == "yweather:wind")
          {
             temperature = e.attribute("chill", "");
          }
          else if(e.tagName() == "yweather:atmosphere")
          {
             humidity = e.attribute("humidity", "");
             pressure = e.attribute("pressure", "");
          }
          else if(e.tagName() == "item")
          {
             n = n.firstChild();

             while(!n.isNull())
             {
                QDomElement e = n.toElement();

                if(!e.isNull())
                {
                   if(e.tagName() == "yweather:condition")
                   {
                      condition = e.attribute("text", "");
                      today_code = e.attribute("code", "");
                      temperature = e.attribute("temp","");
                      qDebug() << today_code;
                   }
                   if(e.tagName() == "yweather:forecast")
                   {
                       tomorrow_day = e.attribute("day","");
                       temperature_tomorrow_low = e.attribute("low","");
                       temperature_tomorrow_high = e.attribute("high","");
                       temperature_tomorrow_condition = e.attribute("text","");
                       tomorrow_code = e.attribute("code","");

                       n = n.nextSibling();
                       QDomElement e = n.toElement();
                       if(e.tagName() == "yweather:forecast")
                       {
                           d_a_t = e.attribute("day","");
                           d_a_t_low = e.attribute("low","");
                           d_a_t_high = e.attribute("high","");
                           d_a_t_condition = e.attribute("text","");
                           d_a_t_code = e.attribute("code","");
                       }

                   }
                }
                n = n.nextSibling();
             }

             n = n.parentNode();
          }
       }

       n = n.nextSibling();
    }
}

QStringList QWeather::getToday()
{
    QDomDocument doc;
    doc.setContent(xmldoc);
    parcer(doc);
    doc.clear();
    qDebug() << "today" << today_code;
    QList<QString> today;
    today.append(today_code);
    today.append(country);
    today.append(region);
    today.append(city);
    today.append(temperature);
    today.append(cf);
    today.append(condition);
    today.append(today_code);
    today.append(chill);
    today.append(humidity);
    today.append(pressure);
    return today;
}









