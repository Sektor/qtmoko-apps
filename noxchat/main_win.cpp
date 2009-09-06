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
#include "main_win.h"
#include <qsoftmenubar.h>
#include <QDebug>
#include <QMessageBox>
#include <QtopiaApplication>
#include "win_settings.h"

//main_win::main_win()
main_win::main_win( QWidget *parent, Qt::WFlags f ) //CHANGED:
{
	//CONFIG FILE
	config=new xml_config("NoChat.xml");
        if (!config->isLoaded()) config=new xml_config(QCoreApplication::applicationDirPath() + "/../etc/noxchat/NoChat.xml");
	//ridimensionameno finestra
	resize (480,640);
	setWindowIcon(QIcon(":icon.png"));

	//Creazione menu
	create_menu();

        /*
        //Toolbar
	tool=addToolBar(tr("Main"));
	tool->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
	tool->addAction(QIcon(":nuovo.png"),tr("Entra nel Canale"),this,SLOT(open_joinchan()));
	tool->addAction(QIcon(":exit.png"),tr("Esci dal Canale"),this,SLOT(close_chan()));
	tool->addAction(QIcon(":notify_list.png"),tr("Controlla Notify List"),this,SLOT(check_notify_list()));
	//StatusBar
        //status=new QStatusBar(this); //CHANGED: commented
        //setStatusBar(status);  //CHANGED: commented
        //status->showMessage(tr("Benvenuti nella NoChat"));  //CHANGED: commented
        */
        showStatusMessage(tr("Welcome to NoxChat"));

	win_title="NoxChat";
	setWindowTitle(win_title);
	//creazione oggetto CHAT
	chat=new irc_engine(this);
	//Associo il segnale di connesso allo slot di login dell'oggetto chat
	connect (chat,SIGNAL(connesso()),chat,SLOT(login()));
	connect (chat,SIGNAL(logged()),this,SLOT(logged()));
	connect (chat,SIGNAL(new_chan(QString)),this,SLOT(new_chan(QString)));
	connect (chat,SIGNAL(msg_from_chan(QString,QString)),this,SLOT(check_chan(QString,QString)));
	connect (chat,SIGNAL(ison(QString)),this,SLOT(ison(QString)));
	connect (chat,SIGNAL(del_user(QString)),this,SLOT(set_user_offline(QString)));
	connect (chat,SIGNAL(error(QString)),this,SLOT(open_error(QString)));
	connect (chat,SIGNAL(double_nick()),this,SLOT(change_nick()));
	connect (chat,SIGNAL(change_nick(QString,QString)),this,SLOT(nick_changed(QString,QString)));
        //connect (chat,SIGNAL(status_message(QString)),status,SLOT(showMessage(QString))); //CHANGED:
        connect (chat,SIGNAL(status_message(QString)),this,SLOT(showStatusMessage(QString)));
        connect (chat,SIGNAL(disconnesso()),this,SLOT(showStatusDisconnected())); //CHANGED: added
        //LAYOUT
	tab=new tab_manager(this);
	connect (tab,SIGNAL(currentChanged(int)),this,SLOT(changed_tab(int)));
	setCentralWidget(tab);
	tab_chat *tb=new tab_chat(tr("Main"),chat,false,config,this);
	tab->addTab(tb,tr("Main"));
	//CONNESSIONE
	//settaggio informazioni utente
	nk=config->get_identity(0);
	chat->set_userdata(nk.nick,nk.real_name,nk.password);
	n_nick=0;
	//connessione all'host 
	QC_server srv=config->get_server(0);
	chat->connetti(srv.host,srv.port);
        //status->showMessage(tr("Connection in progress..."));  //CHANGED:
        showStatusMessage(tr("Connection in progress..."));

        QtopiaApplication::setPowerConstraint(QtopiaApplication::DisableSuspend); //CHANGED: added - prevent suspend
};

void main_win::showStatusMessage(QString s)
{
}

void main_win::showStatusDisconnected()
{
        if (!noDisconnectedMessage)
        {
            showMessageBox("Disconnected from server.");
        }
}

void main_win::showMessageBox(QString s)
{
        QMessageBox::warning(this,tr("NoxChat"),s);
}

void main_win::create_menu()
{
        /*
	QMenu *file=menuBar()->addMenu(tr("&File"));
		file->addAction(QIcon(":exit.png"),tr("&Esci"),this,SLOT(close()));
	QMenu *azioni=menuBar()->addMenu(tr("&Azioni"));
		act_away=azioni->addAction(tr("&Away"),this,SLOT(away()));
		act_away->setCheckable(true);
		azioni->addAction(QIcon(":nuovo.png"),tr("E&ntra nel Canale"),this,SLOT(open_joinchan()));
		azioni->addAction(QIcon(":exit.png"),tr("&Esci dal Canale"),this,SLOT(close_chan()));
	QMenu *aiuto=menuBar()->addMenu(tr("Aiu&to"));
		aiuto->addAction(QIcon(":icon.png"),tr("About NoChat"),this,SLOT(about_nochat()));
        */

        QMenu *menu = QSoftMenuBar::menuFor(this);
        menu->addAction(QIcon(":nuovo.png"),tr("Join channel"),this,SLOT(open_joinchan()));
        menu->addAction(QIcon(":exit.png"),tr("Quit channel"),this,SLOT(close_chan()));
        menu->addSeparator();
        act_away = menu->addAction(tr("&Away"),this,SLOT(away()));
        act_away->setCheckable(true);
        menu->addSeparator();
        menu->addAction(tr("&Settings"),this,SLOT(open_settings()));
        menu->addSeparator();
        menu->addAction(QIcon(":exit.png"),tr("Quit"),this,SLOT(close()));
        //QSoftMenuBar::setHelpEnabled(this,true);
};

void main_win::nick_changed(QString old ,QString new_nick)
{
	if (new_nick.toUpper()==chat->get_nick().toUpper())
		setWindowTitle(tr("%1 - %2").arg(win_title).arg(new_nick));
};

void main_win::logged()
{
	//After login
	//Inizializzo il timer della notify list
        showStatusMessage(tr("Login successful"));
        setWindowTitle(tr("%1 - %2").arg(win_title).arg(chat->get_nick()));
        if (!nk.password.isEmpty())
        {
                chat->send(tr("ns IDENTIFY %1\n").arg(nk.password));
        }
	check_notify_list();
	QTimer *notify_time=new QTimer(this);
	connect (notify_time,SIGNAL(timeout()),this,SLOT(check_notify_list()));
	notify_time->setInterval(60000);
	notify_time->start();
        //status->showMessage(tr("Login effettuato con successo"));  //CHANGED:
};

bool main_win::tab_exist(QString chan)
{
	return (tab->tab_pos(chan)>-1);
};

void main_win::away()
{
	if (act_away->isChecked())
		chat->send(tr("AWAY : %1").arg(nk.away_message));
	else
		chat->send(tr("AWAY"));
// 	act_away->setChecked(!act_away->isChecked());
};

void main_win::check_chan(QString chan,QString msg)
{
	//Controllo che il canale esiste altrimenti lo creo (succede quando c'Х un msg privato)	
	if (!tab_exist(chan))
	{
		int actual=tab->currentIndex();
		tab_chat *tb=new_query(chan);
		if (tb!=NULL)
		{
			tb->msg_from_chan(chan,msg);
			tab->setCurrentIndex(actual);
		}
	}
	else
	{
		//Se il canale esiste giЮ
		if (tab->tab_pos(chan)!=tab->currentIndex())
		{
			//Se il canale non Х quello visualizzato in questo momento avviso del messaggio
			tab->add_alert(chan);
		}
	}
};

tab_chat* main_win::new_query(QString user)
{
	if (!tab_exist(user))
	{
		//creo una nuova tab privata se non ne esiste giЮ una
		tab_chat *tb=new tab_chat(user,chat,false,config,this);
		connect (tb,SIGNAL(title_changed(QWidget*,QString)),this,SLOT(change_title(QWidget*,QString)));
		connect (tb,SIGNAL(chan_closed(tab_chat*)),this,SLOT(close_tab_chan(tab_chat*)));
		tab->addTab(tb,user);
		tab->setCurrentWidget(tb);
		return tb;
	}
	else
	{
		//Se il canale esiste giЮ
		if (tab->tab_pos(user)!=tab->currentIndex())
		{
			//Se il canale non Х quello visualizzato in questo momento avviso del messaggio
			tab->add_alert(user);
		}
		return NULL;
	}
};

void main_win::changed_tab(int ind)
{
	//quando cambia il tab tolgo l'alert
	
	tab_chat *tmp=(tab_chat*)tab->widget(ind);
	tab->remove_alert(tmp->get_name());
        //cout << "cambiato tab"<<tmp->get_name().toStdString()<<endl; //CHANGED: commented
        qDebug() << tmp->get_name();
};

void main_win::change_title(QWidget *tb,QString new_name)
{
	//se una finestra di chat privata ha un cambio nick campio il topic del tab
	tab->setTabText(tab->indexOf(tb),new_name);
};

void main_win::new_chan(QString name)
{
	tab_chat *tb=new tab_chat(name,chat,true,config,this);
	connect (tb,SIGNAL(new_query(QString)),this,SLOT(new_query(QString)));
	connect (tb,SIGNAL(chan_closed(tab_chat*)),this,SLOT(close_tab_chan(tab_chat*)));
	tab->addTab(tb,name);
	tab->setCurrentWidget(tb);
};

void main_win::close_chan()
{
	int curr_tab=tab->currentIndex();
	if (curr_tab==0)
	{
		cout << "closing channel page" << endl;
		close();
	}
	else
	{
		tab_chat *tmp=(tab_chat*)tab->currentWidget();
		tmp->close_chan();
	}
};

void main_win::close_tab_chan(tab_chat *ch)
{
	//rimuovo gli alert sul canale appena chiuso
	tab->remove_alert(ch->get_name());
	int actual=tab->indexOf(ch);
	tab->removeTab(actual);
	tab->setCurrentIndex(actual-1);
};

void main_win::closeEvent(QCloseEvent *e)
{
        noDisconnectedMessage = true;
	//Alla chiusura della finestra disconnetto il socket dal server
	chat->disconnetti();
	e->accept();

        QtopiaApplication::setPowerConstraint(QtopiaApplication::Enable); //CHANGED: added - restore power saving settings
};

void main_win::ison(QString user)
{
	online << user;
};

void main_win::set_user_offline(QString user)
{
	cout << "set user OFFLINE" <<endl;
	int i=online.indexOf(user);
	if (i>-1)
		online.removeAt(i);
};

void main_win::check_notify_list()
{
        //status->showMessage(tr("Controllo Notify list..."),10);  //CHANGED:
        //showStatusMessage(tr("Checking Notify List..."),10);
        QStringList notify=config->get_notify_list();
	if (notify.count()<=0)
                cout << "check_notify_list: NOTIFY LIST IS EMPTY" << endl;
	for (int i=0;i<notify.count();i++)
	{
		//Segnalo solo se non l'ho giЮ segnalato prima
		if (!online.contains(notify[i],Qt::CaseInsensitive))
		{
			chat->check_user_online(notify[i]);
		}
	}
};

void main_win::keyPressEvent(QKeyEvent *e)
{
	cout << "key pressed in main window" << endl;
	if (e->key()==Qt::Key_Tab)
		e->ignore();
};

void main_win::change_nick()
{
	//Quando il nick principale Х occupato scorro nei nick della lista di identities
	if (n_nick+1<config->identity_count())
	{
		n_nick++;
		nk=config->get_identity(n_nick);
		chat->set_userdata(nk.nick,nk.real_name,nk.password);
		chat->login();
	}
	else
		open_error("Nickname is already in use. Change identities and try again.");
};

void main_win::open_joinchan()
{
	win_joinchan *win=new win_joinchan(chat,this);
	win->show();
};

void main_win::open_error(QString err)
{
	QMessageBox::warning(this,tr("Warning from Server"),err);
};

/*
void main_win::about_nochat()
{
	win_about *about=new win_about(this);
	about->show();
};
*/

void main_win::open_settings()
{
        win_settings *win=new win_settings(config,this);
        win->show();
};
