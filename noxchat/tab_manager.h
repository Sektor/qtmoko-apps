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
#ifndef TAB_MANAGER_H
#define TAB_MANAGER_H

#include <QTabWidget>
#include <QTabBar>
#include <QStringList>
#include <QTimer>

#include <iostream>

using namespace std;

class tab_manager : public QTabWidget
{
	Q_OBJECT
	private:
		QStringList alert_list;
		QTabBar *tab;
		QTimer *timer;
		QColor col;
	public:
		tab_manager(QWidget *);
	public slots:
		void add_alert(QString);
		void remove_alert(QString);
		void alert_tab();
		int tab_pos(QString);
};

#endif
