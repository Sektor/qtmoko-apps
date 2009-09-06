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
#include "edit_message.h"
#include <QDebug>

edit_message::edit_message(QWidget *parent) : QLineEdit(parent)
{
	userlist=NULL;
	menu=new QMenu(this);
	connect (menu,SIGNAL(triggered(QAction*)),this,SLOT(append_nick(QAction*)));
	num=-1;
};

void edit_message::set_userlist(QListWidget *lst)
{
	userlist=lst;
};

QString edit_message::get_actual_word()
{
	QString actual=text();
	if (!actual.isEmpty())
	{
		int length;
		int start;
		start=actual.lastIndexOf(' ',cursorPosition()-1)+1;
		length=cursorPosition()-start;
		actual=actual.mid(start,length);
	}
	return actual;
};

void edit_message::sended()
{
	//Un messaggio Х stato spedito
	//aggiorno la lista dei messaggi per abilitare i tasti direzionali
	messages<<text();
	num=messages.count();
	clear();
};

bool edit_message::event(QEvent *e)
{
	if (e->type()==QEvent::KeyPress)
	{
		QKeyEvent *ke=(QKeyEvent*)e;
		switch (ke->key())
		{
			case (Qt::Key_Tab):
			{
				//Recupero la parola che si sta scrivendo
				QString actual=get_actual_word();
                                //cout <<actual.toStdString()<<endl; //CHANGED: commented
                                //qDebug(actual.toUtf8());
                                qDebug() << actual;
				if (userlist!=NULL)
				{
					menu->clear();
					QList<QListWidgetItem *> find=userlist->findItems(actual,Qt::MatchStartsWith);
					//cerco anche gli operatori
					QList<QListWidgetItem *> find2=userlist->findItems("@"+actual,Qt::MatchStartsWith);
					//concateno le liste
					find << find2;
					for (int i=0;i<find.count();i++)
					{
						QString tmp=find.at(i)->text();
						if (tmp[0]=='@')
							tmp=tmp.right(tmp.length()-1);
						menu->addAction(tmp);
					}
					if (find.count()>1)
						menu->popup(QPoint(x(),y()));
					if (find.count()==1)
					{
						QString tmp=find.at(0)->text();
						if (tmp[0]=='@')
							tmp=tmp.right(tmp.length()-1);
						append_nick(new QAction(tmp,menu));
					}
				}
				return true;
			}break;
			case (Qt::Key_Up):
			{
				//Quando si preme il tasto su si vedono i vecchi messaggi scritti
				if (num>0)
				{
					num--;
					setText(messages.at(num));
				}
				return true;
			}break;
			case (Qt::Key_Down):
			{
				//Quando si preme il tasto giЫ si scorrono i messaggi giЮ scritti
				if (num<messages.count()-1)
				{
					num++;
					setText(messages.at(num));
				}
				else
				{
					num=messages.count();
					setText("");
				}
				return true;
			}break;
			default:return QWidget::event(e);
		}
	}
	else
		return QWidget::event(e);
};

void edit_message::append_nick(QAction *a)
{
	QString actual=text();
	if (!actual.isEmpty())
	{
		int length;
		int start;
		start=actual.lastIndexOf(' ',cursorPosition()-1)+1;
		length=cursorPosition()-start;
		actual=actual.mid(start,length);
		QString tmp=text();
		tmp=tmp.replace(start,length,a->text());
		setText(tmp);
	}
};
