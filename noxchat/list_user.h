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
#ifndef LIST_USER_H
#define LIST_USER_H

#include <QListWidget>
#include <QMenu>
#include <QContextMenuEvent>
#include <QMessageBox>

#include "xml_config.h"
#include "irc_engine.h"

class list_user : public QListWidget
{
	Q_OBJECT
	private:
		xml_config *config;
		irc_engine* chat;
		QStringList *op,*voice,*halfop;
		QString chan;
	public:
		list_user(QWidget*,xml_config*,irc_engine*,QStringList *,QStringList *,QStringList *,QString);
	protected:
                //virtual void contextMenuEvent(QContextMenuEvent *);  //CHANGED: commented
	public slots:
		void add_to_notify_list();
		void del_from_notify_list();
		void kick_user();
		void ban_user();
		void add_op();
		void del_op();
		void add_halfop();
		void del_halfop();
		void add_voice();
		void del_voice();
};

#endif
