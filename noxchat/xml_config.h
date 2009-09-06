/******************************************
**	Realized by 
**		GeoKronos
**			geokronos.homelinux.org
**			geokronos@yahoo.com
**	and
**		Clepto
**			cleptoiii@yahoo.it
**	License: GPL
*******************************************/
#ifndef XML_CONFIG_H
#define XML_CONFIG_H

#include <QDomDocument>
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <iostream>

using namespace std;

class QC_identity
{
	public:
		QString nick;
		QString real_name;
		QString password;
		QString away_message;
};

class QC_server
{
	public:
		QString host;
		int port;
};

class xml_config : public QObject
{
	Q_OBJECT
	private:
		QDomDocument doc;
		QFile *fl;
                QString err;
		int err_row,err_col;
                bool loaded;
	public:
		xml_config(QString);
		~xml_config();
		QStringList get_notify_list();
		QC_identity get_identity(int);
		QString get_browser();
		int identity_count();
		QC_server get_server(int);
		bool user_in_notify_list(QString user);
		bool save();
                bool isLoaded();
                void set_server(QString server);
                void set_port(QString port);
                void clear_identities();
                void add_identity(QString name, QString nick, QString pass, QString away);
	public slots:
		bool add_notify_user(QString user);
		void del_notify_user(QString user);
};

#endif
