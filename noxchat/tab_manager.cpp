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
#include "tab_manager.h"

tab_manager::tab_manager(QWidget *parent): QTabWidget(parent)
{
	tab=tabBar();
	timer=new QTimer(this);
	connect (timer,SIGNAL(timeout()),this,SLOT(alert_tab()));
	timer->setInterval(500);
	timer->start();
	col=QColor(255,0,0);
};

void tab_manager::add_alert(QString alert)
{
	if (!alert_list.contains(alert.toUpper()))
		alert_list << alert.toUpper() ;
};

void tab_manager::remove_alert(QString alert)
{
	alert_list.removeAll(alert.toUpper());
	col=QColor(0,0,0);
	tab->setTabTextColor(tab_pos(alert),col);
};

int tab_manager::tab_pos(QString tab_name)
{
	bool ok=false;
	for (int i=0;i<count();i++)
	{
		if (tabText(i).toUpper()==tab_name.toUpper())
		{
			ok=true;
			return i;
		}
	}
		return -1;
};

void tab_manager::alert_tab()
{
	if (col==QColor(255,0,0))
		col=QColor(0,0,0);
	else
		col=QColor(255,0,0);
	for (int i=0;i<alert_list.count();i++)
	{
		int ind=tab_pos(alert_list.at(i));
		if (ind>-1)
			tab->setTabTextColor(ind,col);
	}
};
