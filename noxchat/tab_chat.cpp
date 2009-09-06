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
#include "tab_chat.h"
#include <QDebug>

tab_chat::tab_chat(QString a_name,irc_engine *a_chat,bool type,xml_config *cnf,QWidget *parent)
{
	prn=parent;
	ischan=type;
	chat=a_chat;
	name=a_name;
	config=cnf;
	grid=new QGridLayout(this);
	txt=new QTextBrowser(this);
        txt->setAutoFormatting(QTextEdit::AutoAll);
	connect (txt,SIGNAL(anchorClicked(QUrl)),this,SLOT(anchor(QUrl)));
	
        edt_cmd=new edit_message(this);

        grid_msg=new QGridLayout(this); //CHANGED: added
        send_btn = new QPushButton(this) ; //CHANGED: added
        send_btn->setText("Send");
        send_btn->setMinimumWidth(100);
        connect (send_btn,SIGNAL(clicked()),this,SLOT(send()));

	if (ischan)
	{
		//creo la lista degli utenti
		lst=new list_user(this,config,chat,&op,&halfop,&voice,name);
                //connect (lst,SIGNAL(itemDoubleClicked(QListWidgetItem*)),this,SLOT(open_query(QListWidgetItem*))); //CHANGED: DoubleClicked -> Clicked
                connect (lst,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(open_query(QListWidgetItem*)));
                lst->setMaximumWidth(150);
		lst->setAlternatingRowColors(true);
                edt_cmd->set_userlist(lst);

                grid->addWidget(txt,1,0);
		grid->addWidget(lst,1,1);
                grid->addLayout(grid_msg,2,0,1,2);
                //connect (chat,SIGNAL(topic(QString,QString)),this,SLOT(set_topic(QString,QString)));
	}
	else
	{//se Х una chat privata
		grid->addWidget(txt,0,0);
                grid->addLayout(grid_msg,1,0);
        }
        grid_msg->addWidget(edt_cmd,0,0);
        grid_msg->addWidget(send_btn,0,1);

        connect (edt_cmd,SIGNAL(returnPressed()),this,SLOT(send()));
	connect (chat,SIGNAL(ricevuto(QString)),this,SLOT(append(QString)));
	connect (chat,SIGNAL(del_user(QString,QString)),this,SLOT(del_user(QString,QString)));
	connect (chat,SIGNAL(del_user(QString)),this,SLOT(del_user(QString)));
	connect (chat,SIGNAL(add_users(QString,QStringList)),this,SLOT(add_users(QString,QStringList)));
	connect (chat,SIGNAL(change_nick(QString,QString)),this,SLOT(change_nick(QString,QString)));
	connect (chat,SIGNAL(msg_from_chan(QString,QString)),this,SLOT(msg_from_chan(QString,QString)));
	connect (chat,SIGNAL(mode(QString,QString,QString,QString)),this,SLOT(mode_user(QString,QString,QString,QString)));
        //connect (chat,SIGNAL(mode(QString,QString,QString)),this,SLOT(mode_chan(QString,QString,QString))); //CHANGED:
	connect (chat,SIGNAL(kick(QString,QString,QString,QString)),this,SLOT(kick(QString,QString,QString,QString)));
};

void tab_chat::set_topic_disabled(bool ds)
{
	if (!ds)
		connect (edt_topic,SIGNAL(editingFinished()),this,SLOT(change_topic()));
	else
		disconnect (edt_topic,SIGNAL(editingFinished()),this,SLOT(change_topic()));
	edt_topic->setReadOnly(ds);
};

void tab_chat::set_mode_buttons_disabled(bool ds)
{
	btn_t->setDisabled(ds);
	btn_n->setDisabled(ds);
	btn_s->setDisabled(ds);
	btn_i->setDisabled(ds);
	btn_p->setDisabled(ds);
	btn_m->setDisabled(ds);
	btn_k->setDisabled(ds);
	btn_l->setDisabled(ds);
	if (name!=tr("Main"))
		chat->send(tr("MODE %1").arg(name));
};

void tab_chat::create_mode_buttons()
{
	//Creo i pulsanti dei MODE
	//T
	btn_t=new QPushButton(this);
	btn_t->setText("T");
        //btn_t->setToolTip(tr("Canale con topic bloccato dagli operatori.")); //CHANGED: commented
	btn_t->setFlat(true);
	btn_t->setMaximumWidth(20);
	btn_t->setMaximumHeight(20);
	connect (btn_t,SIGNAL(clicked()),this,SLOT(set_t()));
	grid_topic->addWidget(btn_t,0,1);
	//N
	btn_n=new QPushButton(this);
	btn_n->setText("N");
        //btn_n->setToolTip(tr("Nessun messaggio dall'esterno.")); //CHANGED: commented
	btn_n->setFlat(true);
	btn_n->setMaximumWidth(20);
	btn_n->setMaximumHeight(20);
	connect (btn_n,SIGNAL(clicked()),this,SLOT(set_n()));
	grid_topic->addWidget(btn_n,0,2);
	//S
	btn_s=new QPushButton(this);
	btn_s->setText("S");
        //btn_s->setToolTip(tr("Canale Segreto.")); //CHANGED: commented
	btn_s->setFlat(true);
	btn_s->setMaximumWidth(20);
	btn_s->setMaximumHeight(20);
	connect (btn_s,SIGNAL(clicked()),this,SLOT(set_s()));
	grid_topic->addWidget(btn_s,0,3);
	//I
	btn_i=new QPushButton(this);
	btn_i->setText("I");
        //btn_i->setToolTip(tr("Canale a solo invito.")); //CHANGED: commented
	btn_i->setFlat(true);
	btn_i->setMaximumWidth(20);
	btn_i->setMaximumHeight(20);
	connect (btn_i,SIGNAL(clicked()),this,SLOT(set_i()));
	grid_topic->addWidget(btn_i,0,4);
	//P
	btn_p=new QPushButton(this);
	btn_p->setText("P");
        //btn_p->setToolTip(tr("Canale Privato.")); //CHANGED: commented
	btn_p->setFlat(true);
	btn_p->setMaximumWidth(20);
	btn_p->setMaximumHeight(20);
	connect (btn_p,SIGNAL(clicked()),this,SLOT(set_p()));
	grid_topic->addWidget(btn_p,0,5);
	//M
	btn_m=new QPushButton(this);
	btn_m->setText("M");
        //btn_m->setToolTip(tr("Canale moderato.")); //CHANGED: commented
	btn_m->setFlat(true);
	btn_m->setMaximumWidth(20);
	btn_m->setMaximumHeight(20);
	connect (btn_m,SIGNAL(clicked()),this,SLOT(set_m()));
	grid_topic->addWidget(btn_m,0,6);
	//K
	btn_k=new QPushButton(this);
	btn_k->setText("K");
        //btn_k->setToolTip(tr("KeyWord.")); //CHANGED: commented
	btn_k->setFlat(true);
	btn_k->setMaximumWidth(20);
	btn_k->setMaximumHeight(20);
	connect (btn_k,SIGNAL(clicked()),this,SLOT(set_k()));
	grid_topic->addWidget(btn_k,0,7);
	//L
	btn_l=new QPushButton(this);
	btn_l->setText("L");
        //btn_l->setToolTip(tr("Canale con numero massimo di utenti.")); //CHANGED: commented
	btn_l->setFlat(true);
	btn_l->setMaximumWidth(20);
	btn_l->setMaximumHeight(20);
	connect (btn_l,SIGNAL(clicked()),this,SLOT(set_l()));
	grid_topic->addWidget(btn_l,0,8);
};

void tab_chat::set_t()
{
	if (!mode.contains('t'))
		chat->send(tr("MODE %1 +t").arg(name));
	else
		chat->send(tr("MODE %1 -t").arg(name));
	chat->send(tr("MODE %1").arg(name));
};

void tab_chat::set_n()
{
	if (!mode.contains('n'))
		chat->send(tr("MODE %1 +n").arg(name));
	else
		chat->send(tr("MODE %1 -n").arg(name));
	chat->send(tr("MODE %1").arg(name));
};

void tab_chat::set_s()
{
	if (!mode.contains('s'))
		chat->send(tr("MODE %1 +s").arg(name));
	else
		chat->send(tr("MODE %1 -s").arg(name));
	chat->send(tr("MODE %1").arg(name));
};

void tab_chat::set_i()
{
	if (!mode.contains('i'))
		chat->send(tr("MODE %1 +i").arg(name));
	else
		chat->send(tr("MODE %1 -i").arg(name));
	chat->send(tr("MODE %1").arg(name));
};

void tab_chat::set_p()
{
	if (!mode.contains('p'))
		chat->send(tr("MODE %1 +p").arg(name));
	else
		chat->send(tr("MODE %1 -p").arg(name));
	chat->send(tr("MODE %1").arg(name));
};

void tab_chat::set_m()
{
	if (!mode.contains('m'))
		chat->send(tr("MODE %1 +m").arg(name));
	else
		chat->send(tr("MODE %1 -m").arg(name));
	chat->send(tr("MODE %1").arg(name));
};

void tab_chat::set_k()
{
	chat->send(tr("MODE %1").arg(name));
};

void tab_chat::set_l()
{
	chat->send(tr("MODE %1").arg(name));
};


void tab_chat::kick(QString chan,QString origin,QString user,QString msg)
{
	if (ischan && name.toUpper()==chan.toUpper())
	{
		append(tr("<font color=\"#777777\"><i>%1 you KICKED %2 --> %3</i></font>").arg(origin).arg(user).arg(msg));
		if (user.toUpper()==chat->get_nick().toUpper())
		{
			QMessageBox::critical(this,tr("KICKED"),tr("%1 you was KICKED :%2").arg(origin).arg(msg));
			emit chan_closed(this);
			close();
		}
		else
			del_user(chan,user);
	}
};

QString tab_chat::get_name()
{
	return name;
};

void tab_chat::anchor(QUrl ur)
{
	txt->setSource(txt->source());
	QString url=ur.toString();
        //cout << "ANCHOR -"<<url.toStdString()<<"-"<<endl; //CHANGED: commented
        qDebug() << url;
	if (url[0]=='#')
	{
		chat->send(tr("join %1").arg(url));
	}
	else
	{
		if (url.contains("http://") || url.contains("https://") || url.contains("www."))
		{
// 			QProcess::startDetached(tr("%1").arg(config->get_browser()).arg(url));
		}
		else
		{
			if (url[0]=='@' || url[0]=='+'|| url[0]=='%')
				url=url.right(url.length()-1);
			emit new_query(url);
		}
	}
};

void tab_chat::change_topic()
{
	chat->send(tr("TOPIC %1 :%2").arg(name).arg(edt_topic->text()));
};

void tab_chat::set_topic(QString chan,QString topic)
{
	if (ischan && name.toUpper()==chan.toUpper())
	{
		edt_topic->setText(topic);
	}
};

void tab_chat::send()
{//spedisce il messaggio al server
	QString msg=edt_cmd->text();
	if (name!=tr("Main") && msg[0]!='/')
	{
		msg=tr("PRIVMSG %1 :%2").arg(name).arg(msg);
		append(tr("<font color=\"#FF0000\"><b>%1</b></font> ->%2").arg(chat->get_nick()).arg(edt_cmd->text()));
	}
	else
	{
		if (msg[0]=='/')
		{//messaggio di sistema
			//tolgo la barra iniziale
			msg=msg.right(msg.length()-1);
		}
	}
	chat->send(msg);
	edt_cmd->sended();
};

void tab_chat::open_query(QListWidgetItem *user)
{
	cout << "opening query" << endl;
	QString us=user->text();
	if (us[0]=='@' || us[0]=='+' || us[0]=='%')
		us=us.right(us.length()-1);
	emit new_query(us);
};

void tab_chat::msg_from_chan(QString chan,QString msg)
{
	if (chan.toUpper()==name.toUpper())
		append(msg);
};

void tab_chat::append(QString rc)
{
	//se trovo dei testi con # lo linko al canale
	QRegExp rg_chan("[^\"][#][A-Za-z][A-Za-z0-9]*");
	int pos=0;
	QString sub;
	while ((pos=rg_chan.indexIn(rc,pos))!=-1)
	{
		QString chan=rg_chan.capturedTexts().at(0);
                sub=tr("<font size=3><a href=\"%1\">%1</a></font>").arg(chan.right(chan.length()-1));
		rc.replace(pos+1,rg_chan.matchedLength()-1,sub);
		pos+=sub.length();
	}
	QRegExp rg_http("(http://|https://|www.)[A-Za-z][A-Za-z0-9./?&=]*");
	pos=0;
	sub="";
	while ((pos=rg_http.indexIn(rc,pos))!=-1)
	{
		QString http=rg_http.capturedTexts().at(0);
                sub=tr("<font size=3><a href=\"%1\">%1</a></font>").arg(http.right(http.length()));
		rc.replace(pos,rg_http.matchedLength(),sub);
		pos+=sub.length();
	}
	txt->append(rc);
        //qDebug() << "append: " << rc;
};

void tab_chat::add_users(QString chan,QStringList users)
{
	//cerco il tab_chat relativo al canale
	if (chan.toUpper()==name.toUpper() && ischan)
	{
		for (int i=0;i<users.size();i++)
			add_user(users[i]);
	}
};

void tab_chat::add_user(QString user)
{	
	QList<QListWidgetItem *> find=lst->findItems(user,Qt::MatchExactly);
	if (find.count()==0)
	{
		QListWidgetItem *tmp;
		switch (user[0].toAscii())
		{
			case '@':
			{
				tmp=new QListWidgetItem(QIcon(":op.png"),user.right(user.length()-1));
				op << user.right(user.length()-1);
			}break;
			case '%':
			{
				tmp=new QListWidgetItem(QIcon(":halfop.png"),user.right(user.length()-1));
				halfop << user.right(user.length()-1);
			}break;
			case '+':
			{
				tmp=new QListWidgetItem(QIcon(":voice.png"),user.right(user.length()-1));
				voice << user.right(user.length()-1);
			}break;
			default:
			{
				tmp=new QListWidgetItem(QIcon(":user.png"),user);
			}
		}
		lst->addItem(tmp);
		lst->sortItems(Qt::AscendingOrder);
		//Se il primo valore della lista Х vuoto lo tolgo
		if (lst->item(0)->text().isEmpty())
		{
			lst->takeItem(0);
		}
	}
};

void tab_chat::mode_user(QString chan,QString operation,QString origin,QString arg)
{
	if (chan.toUpper()==name.toUpper())
	{
		if (operation=="+o")
		{//Nuovo operatore
			//trovo l'operatore sulla lista
			QList<QListWidgetItem*> fnd=lst->findItems(arg,Qt::MatchExactly);
			if (fnd.count()==1)
			{
				fnd.at(0)->setIcon(QIcon(":op.png"));
				append(tr("<font color=\"#777777\"><i>%1 became operator of %2</i></font>").arg(origin).arg(arg));
				if (!op.contains(arg,Qt::CaseInsensitive))
				{
					op << arg;
					if (arg.toUpper()==chat->get_nick().toUpper())
					{
						set_mode_buttons_disabled(false);
						set_topic_disabled(false);
					}
				}
			}
		}
		if (operation=="-o")
		{//Tolgo operatore
			QList<QListWidgetItem*> fnd=lst->findItems(arg,Qt::MatchExactly);
			if (fnd.count()==1)
			{
				QIcon ic;
				if (!halfop.contains(arg,Qt::CaseInsensitive))
				{
					if (!voice.contains(arg,Qt::CaseInsensitive))
						ic=QIcon(":user.png");
					else
						ic=QIcon(":voice.png");
				}
				else
					ic=QIcon(":halfop.png");
				fnd.at(0)->setIcon(ic);
				append(tr("<font color=\"#777777\"><i>%1 is no longer operator of %2</i></font>").arg(origin).arg(arg));
				if (op.contains(arg,Qt::CaseInsensitive))
				{
					op.removeAll(arg);
					if (arg.toUpper()==chat->get_nick().toUpper())
					{
						set_mode_buttons_disabled(true);
						chat->send(tr("MODE %1").arg(name));
					}
				}
			}
		}
		if (operation=="+h")
		{//Nuovo HALFOP
			//trovo l'operatore sulla lista
			QList<QListWidgetItem*> fnd=lst->findItems(arg,Qt::MatchExactly);
			if (fnd.count()==1)
			{
				QIcon ic;
				if (!op.contains(arg,Qt::CaseInsensitive))
				{
					ic=QIcon(":halfop.png");
				}
				else
					ic=QIcon(":op.png");
				fnd.at(0)->setIcon(ic);
				append(tr("<font color=\"#777777\"><i>%1 became half-operator of %2</i></font>").arg(origin).arg(arg));
			}
			if (!halfop.contains(arg,Qt::CaseInsensitive))
				halfop << arg;
		}
		if (operation=="-h")
		{//Tolgo VOICE
			QList<QListWidgetItem*> fnd=lst->findItems(arg,Qt::MatchExactly);
			if (fnd.count()==1)
			{
				QIcon ic;
				if (!op.contains(arg,Qt::CaseInsensitive))
				{
					if (!voice.contains(arg,Qt::CaseInsensitive))
						ic=QIcon(":user.png");
					else
						ic=QIcon(":voice.png");
				}
				else
					ic=QIcon(":op.png");
				fnd.at(0)->setIcon(ic);
				append(tr("<font color=\"#777777\"><i>%1 is no longer half-operator of %2</i></font>").arg(origin).arg(arg));
				if (halfop.contains(arg,Qt::CaseInsensitive))
					halfop.removeAll(arg);
			}
		}
		if (operation=="+v")
		{//Nuovo VOICE
			//trovo l'operatore sulla lista
			QList<QListWidgetItem*> fnd=lst->findItems(arg,Qt::MatchExactly);
			if (fnd.count()==1)
			{
				QIcon ic;
				if (!op.contains(arg,Qt::CaseInsensitive))
				{
					if (!halfop.contains(arg,Qt::CaseInsensitive))
						ic=QIcon(":voice.png");
					else
						ic=QIcon(":halfop.png");
				}
				else
					ic=QIcon(":op.png");
				fnd.at(0)->setIcon(ic);
				append(tr("<font color=\"#777777\"><i>%1 now can talk at %2</i></font>").arg(origin).arg(arg));
			}
			if (!voice.contains(arg,Qt::CaseInsensitive))
				voice << arg;
		}
		if (operation=="-v")
		{//Tolgo VOICE
			QList<QListWidgetItem*> fnd=lst->findItems(arg,Qt::MatchExactly);
			if (fnd.count()==1)
			{
				QIcon ic;
				if (!op.contains(arg,Qt::CaseInsensitive))
				{
					if (!halfop.contains(arg,Qt::CaseInsensitive))
						ic=QIcon(":user.png");
					else
						ic=QIcon(":halfop.png");
				}
				else
					ic=QIcon(":op.png");
				fnd.at(0)->setIcon(ic);
				append(tr("<font color=\"#777777\"><i>%1 now can't talk at %2</i></font>").arg(origin).arg(arg));
				if (voice.contains(arg,Qt::CaseInsensitive))
					voice.removeAll(arg);
			}
		}
		if (operation=="+l")
		{//LIMIT
			append(tr("<font color=\"#777777\"><i>%1 set the limit of users %2</i></font>").arg(origin).arg(arg));
			btn_l->setDown(true);
		}
		if (operation=="-l")
		{//LIMIT
			append(tr("<font color=\"#777777\"><i>%1 removed the limit of users</i></font>").arg(origin));
		}
		if (operation=="+s")
		{//SECRET
			append(tr("<font color=\"#777777\"><i>%1 set the channel as secret</i></font>").arg(origin));
		}
		if (operation=="-s")
		{//SECRET
			append(tr("<font color=\"#777777\"><i>%1 lifted the secrecy of the channel</i></font>").arg(origin));
		}
		if (operation=="+i")
		{//INVITI
			append(tr("<font color=\"#777777\"><i>%1 set the channel as invite-only</i></font>").arg(origin));
		}
		if (operation=="-i")
		{//INVITI
			append(tr("<font color=\"#777777\"><i>%1 unset invite-only mode</i></font>").arg(origin));
		}
		if (operation=="+p")
		{//PRIVATO
			append(tr("<font color=\"#777777\"><i>%1 set the channel as private</i></font>").arg(origin));
		}
		if (operation=="-p")
		{//INVITI
			append(tr("<font color=\"#777777\"><i>%1 set the channel as public</i></font>").arg(origin));
		}
		if (operation=="+m")
		{//MODERATO
			append(tr("<font color=\"#777777\"><i>%1 set the channel as moderated</i></font>").arg(origin));
		}
		if (operation=="-m")
		{//MODERATO
			append(tr("<font color=\"#777777\"><i>%1 set the channel as unmoderated</i></font>").arg(origin));
		}
		if (operation=="+n")
		{//NESSUN MESSAGGIO DALL'ESTERNO
			append(tr("<font color=\"#777777\"><i>%1 set \"No messages from outside\"</i></font>").arg(origin));
		}
		if (operation=="-n")
		{//NESSUN MESSAGGIO DALL?ESTERNO
			append(tr("<font color=\"#777777\"><i>%1 removed \"No messages from outside\"</i></font>").arg(origin));
		}
		if (operation=="+t")
		{//BLOCCO Del TOPIC
			append(tr("<font color=\"#777777\"><i>%1 set the protection of Topic</i></font>").arg(origin));
		}
		if (operation=="-t")
		{//BLOCCO del TOPIC
			append(tr("<font color=\"#777777\"><i>%1 removed the protection of Topic</i></font>").arg(origin));
		}
		//aggiorno i pulsanti dei MODE del canale
		chat->send(tr("MODE %1").arg(name));
	}
};

void tab_chat::mode_chan(QString chan, QString operation, QString arg)
{
	if (chan.toUpper()==name.toUpper())
	{
		mode=operation;
		if (operation.contains("t"))
		{//Topic non modificabile
			btn_t->setDown(true);
		}
		else
		{
			btn_t->setDown(false);
			if (!op.contains(chat->get_nick(),Qt::CaseInsensitive))
			{
				set_topic_disabled(false);
			}
		}
		if (operation.contains("n"))
		{//Nessun messaggio dall'esterno
			btn_n->setDown(true);
		}
		else
		{
			btn_n->setDown(false);
		}
		if (operation.contains("s"))
		{//Nessun messaggio dall'esterno
			btn_s->setDown(true);
		}
		else
		{
			btn_s->setDown(false);
		}
		if (operation.contains("i"))
		{//INVITO
			btn_i->setDown(true);
		}
		else
		{
			btn_i->setDown(false);
		}
		if (operation.contains("p"))
		{//PRIVATO
			btn_p->setDown(true);
		}
		else
		{
			btn_p->setDown(false);
		}
		if (operation.contains("m"))
		{//MODERATO
			btn_m->setDown(true);
		}
		else
		{
			btn_m->setDown(false);
		}
		if (operation.contains("l"))
		{//LIMIT
			btn_l->setDown(true);
		}
		else
		{
			btn_l->setDown(false);
		}
		if (operation.contains("n"))
		{//Nessun msg dall'esterno
			btn_n->setDown(true);
		}
		else
		{
			btn_n->setDown(false);
		}
	}
};


void tab_chat::change_nick(QString old_nick,QString new_nick)
{
	if (ischan)
	{
		QList<QListWidgetItem *> find;
		find=lst->findItems(old_nick,Qt::MatchExactly);
		if (find.count()==1)
		{
			//USER LIST
			find[0]->setText(new_nick);
			append(tr("<font color=\"#777777\"><i>%1 now knows as %2</i></font>").arg(old_nick).arg(new_nick));
			//OP e VOICE REPLACE
			op.replaceInStrings(old_nick,new_nick,Qt::CaseInsensitive);
			voice.replaceInStrings(old_nick,new_nick,Qt::CaseInsensitive);
		}
	}
	else
	{
		if (name==old_nick)
		{
			name=new_nick;
			emit title_changed(this,new_nick);
		}
		if (name=="Main" && new_nick==chat->get_nick())
		{
			append(tr("<b>You're now known as %1").arg(new_nick));
		}
	}
};

void tab_chat::del_user(QString chan,QString user)
{
	if (chan.toUpper()==name.toUpper() && ischan)
	{
		//Se il messaggio Х per questa finestra
		QList<QListWidgetItem *> find=lst->findItems(user,Qt::MatchExactly);
		if (find.count()==0)
		{
			find=lst->findItems("@"+user,Qt::MatchExactly);
		}
		if (find.count()==0)
		{
			find=lst->findItems("%"+user,Qt::MatchExactly);
		}
		if (find.count()==0)
		{
			find=lst->findItems("+"+user,Qt::MatchExactly);
		}
		if (find.count()==1)
		{
			lst->takeItem(lst->row(find.at(0)));
			lst->sortItems(Qt::AscendingOrder);
		}
	}
};

void tab_chat::del_user(QString user)
{
	if (ischan)
	{
		//Se il messaggio Х per questa finestra
		QList<QListWidgetItem *> find=lst->findItems(user,Qt::MatchExactly);
		if (find.count()==0)
		{
			find=lst->findItems("@"+user,Qt::MatchExactly);
		}
		if (find.count()==0)
		{
			find=lst->findItems("%"+user,Qt::MatchExactly);
		}
		if (find.count()==0)
		{
			find=lst->findItems("+"+user,Qt::MatchExactly);
		}
		if (find.count()==1)
		{
			lst->takeItem(lst->row(find.at(0)));
			lst->sortItems(Qt::AscendingOrder);
			append(tr("<font color=\"#777777\"><i>%1 closed the chat</i></font>").arg(user)); //left the chat???
		}
	}
};

void tab_chat::close_chan()
{
	if (ischan)
		chat->send(tr("part %1").arg(name));
	emit chan_closed(this);
	close();
};

void tab_chat::keyPressEvent(QKeyEvent *e)
{
	if (e->key()==87 && name!=tr("Main"))
	{//CTRL+W
		close_chan();
	}
	else
	{
		edt_cmd->setFocus();
	}
	e->accept();
};
