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
#ifndef WIN_JOINCHAN_H
#define WIN_JOINCHAN_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

#include "irc_engine.h"
class win_joinchan : public QDialog
{
	Q_OBJECT
	private:
		irc_engine *chat;
		QLineEdit *edt_chan;
	public:
		win_joinchan(irc_engine*, QWidget *);
	public slots:
		void join();
};

#endif
