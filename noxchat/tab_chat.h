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
#ifndef TAB_CHAT_H
#define TAB_CHAT_H

#include <QWidget>
#include <QMessageBox>
#include <QTextBrowser>
#include <QFont>
#include <QLineEdit>
#include <QGridLayout>
#include <QListWidget>
#include <QMenu>
#include <QPushButton>
#include <QList>
#include <QKeyEvent>
#include <QUrl>
#include <QProcess>
#include <iostream>
#include "irc_engine.h"
#include "xml_config.h"
#include "edit_message.h"
#include "list_user.h"

using namespace std;
class tab_chat : public QWidget
{
	Q_OBJECT
	private:
		QString name;
		irc_engine* chat;
		QGridLayout *grid;
		QTextBrowser *txt;
// 		QListWidget *lst;
		list_user *lst;
		edit_message *edt_cmd;
		QLineEdit *edt_topic;
		xml_config *config;
		QWidget *prn;
		QString mode;
		QGridLayout *grid_topic;
		QPushButton *btn_t,*btn_n,*btn_s,*btn_i,*btn_p,*btn_m,*btn_k,*btn_l;
		void create_mode_buttons();
		void set_mode_buttons_disabled(bool);
		void set_topic_disabled(bool);
		QStringList voice,op,halfop;
                QPushButton *send_btn;
                QGridLayout *grid_msg;
        public:
		bool ischan;
		tab_chat(QString,irc_engine*,bool,xml_config*,QWidget*);
		QString get_name();
		
	public slots:
		void send(); //Spedisce il messaggio al server
		void append(QString);
		void add_user(QString);
		void add_users(QString chan,QStringList users);
		void del_user(QString,QString);
		void del_user(QString);
		void change_nick(QString,QString);
		void msg_from_chan(QString,QString);
		void close_chan();
		void open_query(QListWidgetItem*);
		void set_topic(QString,QString);
		void anchor(QUrl);
		void mode_user(QString,QString,QString,QString);
		void mode_chan(QString,QString,QString);
		void kick(QString,QString,QString,QString);
		//Operazioni dei pulsanti
		void set_t();
		void set_n();
		void set_s();
		void set_i();
		void set_p();
		void set_m();
		void set_k();
		void set_l();
		//cambio del topic
		void change_topic();
                //void send_clicked();
        protected:
		virtual void keyPressEvent(QKeyEvent*);
	signals:
		void title_changed(QWidget*,QString);
		void new_query(QString);
		void chan_closed(tab_chat*);
};

#endif
