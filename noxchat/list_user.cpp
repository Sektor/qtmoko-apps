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
#include "list_user.h"

list_user::list_user(QWidget *parent,xml_config *xc,irc_engine *a_chat,QStringList *a_op,QStringList *a_halfop,QStringList *a_voice,QString a_chan):QListWidget(parent)
{
	config=xc;
	chat=a_chat;
	op=a_op;
	halfop=a_halfop;
	voice=a_voice;
	chan=a_chan;
};

//CHANGED: commented - no ContextMenu in QtE
/*
void list_user::contextMenuEvent(QContextMenuEvent *e)
{
	QMenu *menu=new QMenu(this);
	menu->addAction(tr("Aggiungi alla Notify List"),this,SLOT(add_to_notify_list()));
	menu->addAction(tr("Rimuovi dalla Notify List"),this,SLOT(del_from_notify_list()));
	if (op->contains(chat->get_nick(),Qt::CaseInsensitive))
	{
		QListWidgetItem *it=selectedItems().at(0);
		QString user=it->text();
		if (!op->contains(user,Qt::CaseInsensitive))
		{
			menu->addAction(tr("Dai l'OP"),this,SLOT(add_op()));	
		}
		else
		{
			menu->addAction(tr("Togli l'OP"),this,SLOT(del_op()));
		}
		if (!halfop->contains(user,Qt::CaseInsensitive))
		{
			menu->addAction(tr("Dai l'HALFOP"),this,SLOT(add_halfop()));	
		}
		else
		{
			menu->addAction(tr("Togli l'HALFOP"),this,SLOT(del_halfop()));
		}
		if (!voice->contains(user,Qt::CaseInsensitive))
		{
			menu->addAction(tr("Dai il VOICE"),this,SLOT(add_voice()));
		}
		else
		{
			menu->addAction(tr("Togli il VOICE"),this,SLOT(del_voice()));
		}
		menu->addAction(tr("KICK"),this,SLOT(kick_user()));
		menu->addAction(tr("BAN"),this,SLOT(ban_user()));
	}
	else
		{
			if (halfop->contains(chat->get_nick(),Qt::CaseInsensitive))
			{
				QListWidgetItem *it=selectedItems().at(0);
				QString user=it->text();
				if (!voice->contains(user,Qt::CaseInsensitive))
				{
					menu->addAction(tr("Dai il VOICE"),this,SLOT(add_voice()));
				}
				else
				{
					menu->addAction(tr("Togli il VOICE"),this,SLOT(del_voice()));
				}
				if (!op->contains(user,Qt::CaseInsensitive) && !halfop->contains(user,Qt::CaseInsensitive))
				{
					menu->addAction(tr("KICK"),this,SLOT(kick_user()));
				}
			}
		}
        menu->popup(e->globalPos());
};
*/

void list_user::add_to_notify_list()
{
	QListWidgetItem *it=selectedItems().at(0);
	QString user=it->text();
	//tolgo il simbolo di OP se no non funziona
	if (user[0]=='@')
		user=user.right(user.length()-1);
	if(!config->add_notify_user(user))
		QMessageBox::warning(this,tr("Notify List"),tr("User already present in the notify list"));
};

void list_user::del_from_notify_list()
{
	QListWidgetItem *it=selectedItems().at(0);
	QString user=it->text();
	//tolgo il simbolo di OP se no non funziona
	if (user[0]=='@')
		user=user.right(user.length()-1);
	config->del_notify_user(user);
};

void list_user::kick_user()
{
	QListWidgetItem *it=selectedItems().at(0);
	QString user=it->text();
	chat->send(tr("KICK %1 %2").arg(chan).arg(user));
};

void list_user::ban_user()
{
	QListWidgetItem *it=selectedItems().at(0);
	QString user=it->text();
	chat->send(tr("MODE %1 +b %2").arg(chan).arg(user));
};

void list_user::add_op()
{
	QListWidgetItem *it=selectedItems().at(0);
	QString user=it->text();
	chat->send(tr("MODE %1 +o %2").arg(chan).arg(user));
};

void list_user::del_op()
{
	QListWidgetItem *it=selectedItems().at(0);
	QString user=it->text();
	chat->send(tr("MODE %1 -o %2").arg(chan).arg(user));
};

void list_user::add_halfop()
{
	QListWidgetItem *it=selectedItems().at(0);
	QString user=it->text();
	chat->send(tr("MODE %1 +h %2").arg(chan).arg(user));
};

void list_user::del_halfop()
{
	QListWidgetItem *it=selectedItems().at(0);
	QString user=it->text();
	chat->send(tr("MODE %1 -h %2").arg(chan).arg(user));
};

void list_user::add_voice()
{
	QListWidgetItem *it=selectedItems().at(0);
	QString user=it->text();
	chat->send(tr("MODE %1 +v %2").arg(chan).arg(user));
};

void list_user::del_voice()
{
	QListWidgetItem *it=selectedItems().at(0);
	QString user=it->text();
	chat->send(tr("MODE %1 -v %2").arg(chan).arg(user));
};
