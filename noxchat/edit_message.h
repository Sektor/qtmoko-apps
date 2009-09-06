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
#ifndef EDIT_MESSAGE_H
#define EDIT_MESSAGE_H
#include <QLineEdit>
#include <QKeyEvent>
#include <iostream>
#include <QEvent>
#include <QListWidget>
#include <QMenu>
#include <QStringList>

using namespace std;
class edit_message : public QLineEdit
{
	Q_OBJECT
	private:
		QListWidget *userlist;
		QMenu *menu;
		int num;
		QStringList messages;
	public:
		edit_message(QWidget*);
		void set_userlist(QListWidget *);
		QString get_actual_word();
		void sended();
	private slots:
		void append_nick(QAction*);
	protected:
		virtual bool event(QEvent *);
};

#endif
