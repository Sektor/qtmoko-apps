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
#ifndef IRC_ENGINE_H
#define IRC_ENGINE_H

#include <QTcpSocket>
#include <QStringList>
#include <QRegExp>

/*!
* Questo Х il motore IRC del sistema.
* \n
* Permette di collegarsi ad un server IRC e eseguire le principali funzionalitЮ
*
*/

class irc_engine :  public QObject
{
	Q_OBJECT
	private:
		QTcpSocket *sock;
		QString server;
		int port;
		//DAti utente
		QString nick,real_name,password;
		QString get_arg(QString*,bool);
		QStringList error_list;
                void Vibrate();
        public:
		irc_engine(QObject*);
		QString get_nick();
		void check_user_online(QString);
	public slots:
		void connetti(QString,int);
		void disconnetti();
		void connected();
		void disconnected();
		void set_userdata(QString nk,QString rn,QString pwd); //setta i dati utente nick e real name
		void recived(); //ad ogni messaggio ricevuto
		void login();//LOGIN
		void send(QString msg);
	signals:
		void disconnesso();
		void connesso();
		void ricevuto(QString);
		void new_chan(QString);
		void error(QString);
		void add_users(QString,QStringList);
		void del_user(QString,QString);
		void del_user(QString);
		void change_nick(QString,QString);
		void msg_from_chan(QString,QString);
		void topic(QString,QString);
		void ison(QString);
		void logged();
		void double_nick();
		void mode(QString,QString,QString);
		void mode(QString,QString,QString,QString);
		void kick(QString,QString,QString,QString);
		void status_message(QString);
        private slots:
                void stopVibrate();
};

#endif
