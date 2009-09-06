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
#ifndef MAIN_WIN_H
#define MAIN_WIN_H

#include <QMainWindow>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTabWidget>
#include <QTabBar>
#include <QStringList>
#include <QToolBar>
#include <QStatusBar>
#include <QMenuBar>
#include <QFile>
#include <QTimer>
#include <QKeyEvent>
#include <QIcon>
#include <QDialog>

#include "xml_config.h"
#include "irc_engine.h"
#include "tab_chat.h"
#include "tab_manager.h"
#include "win_joinchan.h"
//#include "win_about.h"

class main_win : public QMainWindow
{
	Q_OBJECT
	private:
		irc_engine *chat;
		tab_manager *tab;
		QToolBar *tool;
		xml_config *config;
		QStringList online;
		int n_nick;
		QC_identity nk;
		void create_menu();
                //QStatusBar *status;  //CHANGED: commented
		QString win_title;
		QAction *act_away;
                bool noDisconnectedMessage;
                void showMessageBox(QString s);
        public:
                //main_win(); //CHANGED:
                main_win( QWidget *parent = 0, Qt::WFlags f = 0 );
		void closeEvent(QCloseEvent *e);
	public slots:
		void new_chan(QString);
		void close_chan();
		void close_tab_chan(tab_chat*);
		void logged();
		void check_chan(QString,QString);
		void change_title(QWidget*,QString);
		void ison(QString);
		void check_notify_list();
		tab_chat* new_query(QString);
		void set_user_offline(QString);
		void open_error(QString);
		bool tab_exist(QString);
		void open_joinchan();
		virtual void keyPressEvent(QKeyEvent *e);
		void changed_tab(int);
		void change_nick();
		void nick_changed(QString,QString);
                //void about_nochat();
		void away();
                void open_settings();
        private slots:
                void showStatusMessage(QString s);
                void showStatusDisconnected();                
};

#endif
