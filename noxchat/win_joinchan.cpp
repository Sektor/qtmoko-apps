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
#include "win_joinchan.h"
#include <QGridLayout>

win_joinchan::win_joinchan(irc_engine *ch, QWidget *parent) : QDialog(parent)
{
        setWindowOpacity(0.90);
        resize(380,50);
	chat=ch;
	setModal(true);
	setWindowTitle(tr("Join channel"));
	edt_chan=new QLineEdit(this);
        //edt_chan->setGeometry(5,5,200,25);
	QPushButton *btn_join=new QPushButton(this);
        //btn_join->setGeometry(205,5,50,25);
        btn_join->setMinimumWidth(100);
	btn_join->setText(tr("Join"));

        QGridLayout *grid=new QGridLayout(this); //CHANGED: added
        grid->addWidget(edt_chan,0,0);
        grid->addWidget(btn_join,0,1);

	connect (btn_join,SIGNAL(clicked()),this,SLOT(join()));
};

void win_joinchan::join()
{
	if (edt_chan->text()[0]!='#')
		edt_chan->setText("#"+edt_chan->text());
	chat->send(tr("join %1").arg(edt_chan->text()));
	close();
};
