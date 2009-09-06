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
#include "irc_engine.h"
#include <iostream>
#include <QDebug>
#include <QVibrateAccessory>
#include <QTimer>

using namespace std;

///COSTRUTTORE
irc_engine::irc_engine(QObject *parent)
{
	cout << "IRC ENGINE INITIALIZED"<<endl;
	//Creo il socket
	sock=new QTcpSocket(parent);
	error_list << "421" <<"401"<<"403"<<"404"<<"442"<<"433"<<"474"<<"482"<<"473";
};

QString irc_engine::get_nick()
{
	return nick;
};

///METODO per la connessione
void irc_engine::connetti(QString host,int p)
{
	server=host;
	port=p;
	sock->connectToHost(host,port);
	//Associo il segnale di connesso al metodo connected
	connect (sock,SIGNAL(connected()),this,SLOT(connected()));
	//Associo il segnale di disconnesso con il metodo disconnected
	connect (sock,SIGNAL(disconnected()),this,SLOT(disconnected()));
	//Associo il segnale di pronta lettura con il metodo recived
	connect (sock,SIGNAL(readyRead()),this,SLOT(recived()));
        msg_from_chan(tr("Main"),tr("Connecting to server (%1)...").arg(host));
};

void irc_engine::connected()
{
	//CONNESSO!!! HAVE a LOT FUN!!
	cout << "Connected !! " <<endl;
	//emetto il signal connesso()
	msg_from_chan(tr("Main"),tr("Server connected"));
	emit connesso();
};

void irc_engine::disconnected()
{
	//DISCONNESSO
	//spedisco la stringa quit al server irc per informarlo della disconnessione
	//in modo da non bloccare il nick name fino al timeout
	sock->write(tr("quit").toAscii());
	cout << "Disconnected !!" <<endl;
	//emetto il signal disconnesso
	emit disconnesso();
};

void irc_engine::disconnetti()
{
	///metodo per la disconnessione
	send("QUIT");
	sock->disconnectFromHost();
};

void irc_engine::recived()
{
	///Segnale attivato alla ricezione di messaggi dal server
	QString flow;
	//leggo i messaggi
	flow=sock->readAll();
	QStringList lines=flow.split("\r\n");
	//Interpretazione messaggio
	//prendo il primo argomento (cioХ tra i primi il car0 che Х : e il primo spazio)
	for (int i=0;i<lines.size();i++)
	{
		QString msg=lines[i];
                //cout <<'#'<< msg.toStdString()<<'#'<<endl; //CHANGED: commented
                qDebug() << msg;
		QString arg;
		QString arg1=get_arg(&msg,true);
		if (arg1!=server)
		{
			if (arg1.indexOf("!")>-1)
			{
				QString part1=arg1.left(arg1.indexOf("!"));
				//tolgo i :
				part1=part1.right(part1.length()-1);
				arg=get_arg(&msg,false);
				//COMANDI CHE NON VENGONO INFLUITI DAL PART1
				if (arg=="NICK")
				{//CAMBIO NICK
					QString new_nick=get_arg(&msg,false);
					if (part1==nick)
						nick=new_nick;
					emit change_nick(part1,new_nick);
				}
				if (arg=="KICK")
				{//KICK di un utente
					QString chan=get_arg(&msg,false);
					QString user=get_arg(&msg,false);
					QString messaggio=get_arg(&msg,false);
					emit kick(chan,part1,user,messaggio);
				}
				if (arg=="MODE")
				{//MODE
					QString chan=get_arg(&msg,false);
					QString operation=get_arg(&msg,false);
					arg=get_arg(&msg,false);
					emit mode(chan,operation,part1,arg);
				}
				if (part1.toUpper()==nick.toUpper())
				{//Messaggio che mi riguarda
					if (arg=="JOIN") //Entro in un nuovo canale
					{
						arg=get_arg(&msg,false);
						cout << "new channel"<<endl;
						emit new_chan(arg);
					}
				}
				else
				{//Messaggio che non mi riguarda
					if (arg=="JOIN") //E' entrato un nuovo utente
					{
						QString chan=get_arg(&msg,false);
						QStringList lst;
						lst<<part1;
						emit add_users(chan,lst);
						emit msg_from_chan(chan,tr("<font color=\"#777777\"><i>%1 entered the channel %2</i></font>").arg(part1).arg(chan));
					}
					if (arg=="PART") //E' uscito un utente dal canale
					{
						QString chan=get_arg(&msg,false);
						QString quit_message=get_arg(&msg,false);
						emit del_user(chan,part1);
						emit msg_from_chan(chan,tr("<font color=\"#777777\"><i>%1 left the channel %2</i></font>").arg(part1).arg(quit_message));
					}
					if (arg=="QUIT") //E' uscito un utente dalla chat
					{
						QString quit_message=get_arg(&msg,false);
						emit del_user(part1);
					}
					if (arg=="PRIVMSG")
					{
						QString chan=get_arg(&msg,false);
						QString messaggio=get_arg(&msg,false);
						//Se nel messaggio c'Х il mio nick lo coloro di rosso
						if (messaggio.contains(nick))
						{
							messaggio=tr("<font color=\"#FF0000\">%1</font>").arg(messaggio);
						}
						
						if (chan.toUpper()!=nick.toUpper())
						{//messaggio da un canale
							
							messaggio=tr("<b><font size=3><a href=\"%1\">%1</a></font></b> ->%2").arg(part1).arg(messaggio); //CHANGED: font size modified
							emit msg_from_chan(chan,messaggio);
						}
						else
						{//messaggio privato
							cout << "private message"<< endl;
							messaggio=tr("<b>%1</b> ->%2").arg(part1).arg(messaggio);
							emit msg_from_chan(part1,messaggio);
						}

                                                Vibrate(); //
					}
					if (arg=="TOPIC")
					{//CAMBIO di TOPIC
						QString chan=get_arg(&msg,false);
						QString tp=get_arg(&msg,false);
						emit topic(chan,tp);
					}
					if (arg=="NOTICE")
					{
						QString arg=get_arg(&msg,false);
						QString messaggio=get_arg(&msg,false);
						QRegExp exp("[[][ ]#.*[ ][]]");
						int st=exp.indexIn(messaggio);
						if (st>-1)
						{//CHANSERVER MESSAGE per il canale
							QString chan=messaggio.mid(st+2,exp.matchedLength()-4);
							messaggio=tr("<b>%2</b>").arg(messaggio);
							emit msg_from_chan(chan,messaggio);
						}
						else
						{//NOTICE PRIVATO mediamente dal ServNick o chanServer
							if (arg.toUpper()==nick.toUpper())
							{//NOTICE privato
								messaggio=tr("<b>%1 [ NOTICE ]->%2</b>").arg(part1).arg(messaggio);
								emit msg_from_chan(tr("Main"),messaggio);
							}
						}
					}
					if (arg=="INVITE")
					{//INVITE
						
						QString arg=get_arg(&msg,false);
						arg=arg.left(arg.length()-1);
						if (arg.toUpper()!=nick.toUpper())
						{//Se Х per me
							QString chan=get_arg(&msg,false);
							emit msg_from_chan(tr("Main"),tr("<font color=\"FF0000\"><b>%1 has invited you in %2</b></font>").arg(part1).arg(chan));
							emit status_message(tr("Received invitation to %1").arg(chan));
						}
					}
				}
			}
			else
			{
				if (arg1=="PING")
				{//rispondo con un PONG se no il server mi disconnette
					send(tr("PONG %1 %2").arg(sock->peerName()).arg(server));
				}
				arg=get_arg(&msg,false);
				if (arg=="433")
				{
					//nick duplicato prima di essere loggati almeno una volta
					emit double_nick();
				}
				if (arg=="001") 
				{//setto il nome del server restituito dalla prima connessione ed emetto il sengale logged
					server=arg1;
					emit logged();
				}
			}
			if (arg=="301")
			{//MESSAGGIO di Away di un utente che Х in un altro server
				arg=get_arg(&msg,false);
				QString nick=get_arg(&msg,false);
				QString message=get_arg(&msg,false);
				message=tr("<i>%1-> AWAY %2</i>").arg(nick).arg(message);
				emit msg_from_chan(nick,message);
			}
		}
		else
		{
			//MESSAGGIO DAL SERVER
			arg=get_arg(&msg,false);
			if (arg=="301")
			{//MESSAGGIO di Away di un utente che Х nel mio stesso server
				arg=get_arg(&msg,false);
				QString nick=get_arg(&msg,false);
				QString message=get_arg(&msg,false);
				message=tr("<font color=\"#CCCCCC\">%1-> AWAY %2</font>").arg(nick).arg(message);
				emit msg_from_chan(nick,message);
			}
			if (arg=="324")
			{//MODE di un canale
				arg=get_arg(&msg,false);
				if (arg.toUpper()==nick.toUpper()) 
				{//Se il destinatario sono io
					//Recupero il 3 argomento
					QString chan=get_arg(&msg,false);
					QString operation=get_arg(&msg,false);
					arg=get_arg(&msg,false);
					emit mode(chan,operation,arg);
				}
			}
			if (arg=="372")
			{//MEssaggio semplice dal server //es benvenuto
				arg=get_arg(&msg,false);
				if (arg.toUpper()==nick.toUpper()) 
				{//Se il destinatario sono io
					//Recupero il 3 argomento
					arg=get_arg(&msg,false);
					emit ricevuto(arg);
				}
			}
			if (arg=="332")
			{//TOPIC
				arg=get_arg(&msg,false);
				if (arg.toUpper()==nick.toUpper()) 
				{//Se il destinatario sono io
					//Recupero il 3 argomento
					QString chan=get_arg(&msg,false);
					QString tp=get_arg(&msg,false);
					emit topic(chan,tp);
				}
			}
			if (arg=="303")
			{//RISPOSTA ad un ISON
				arg=get_arg(&msg,false);
				if (arg.toUpper()==nick.toUpper())
				{//Se il destinatario sono io
					//Recupero il 3 argomento
					QString user=get_arg(&msg,false);
					//tolgo lo spazio finale che accompagna il nick dell'ison segnalato
					user=user.left(user.length()-1);
					if (!user.isEmpty())
					{
						emit ison(user);
						emit msg_from_chan(tr("Main"),tr("<font color=\"#FF0000\"><b>%1 Online</b></font>").arg(user));
					}
				}
			}
			if (arg=="NOTICE")
			{
				arg=get_arg(&msg,false);
				if (arg.toUpper()==nick.toUpper()) 
				{//Se il destinatario sono io
					//Recupero il 3 argomento
					arg=get_arg(&msg,false);
					emit ricevuto("<b>"+arg+"</b>");
				}
			}
			if (arg=="353")
			{//Lista utenti
				arg=get_arg(&msg,false);
				if (arg.toUpper()==nick.toUpper() && get_arg(&msg,false)=="=") 
				{//Se il destinatario sono io
					//Recupero il 3 (CANALE
					QString chan=get_arg(&msg,false);
					QString utenti=get_arg(&msg,false);
					QStringList lst_user=utenti.split(" ");
					emit add_users(chan,lst_user);
				}
			}
			if (arg=="401") //No such nick / channel
			{
				arg=get_arg(&msg,false);
				if (arg.toUpper()==nick.toUpper()) 
				{//Se il destinatario sono io
					//Recupero il 3 argomento
					arg=get_arg(&msg,false);
					emit del_user(arg);
				}
			}
			if (error_list.contains(arg))
			{//ERRORI
				arg=get_arg(&msg,false);
				if (arg.toUpper()==nick.toUpper()) 
				{//Se il destinatario sono io
					//Recupero il 3 argomento
					arg=get_arg(&msg,false)+" ";
					arg+=get_arg(&msg,false);
					emit error(arg);
				}
			}
		}
		cout << endl;
	}
};

QString irc_engine::get_arg(QString *msg, bool ignore_doublepoint)
{
	if (!msg->isEmpty())
	{
		QString arg=msg->left(msg->indexOf(" "));
		if (arg[0]==':' && !ignore_doublepoint)
		{//Se l'argomento contiene : significa che da li in poi la riga Х argomento unico
			arg=msg->right(msg->length()-1);
			msg->clear();
		}
		else
			*msg=msg->right(msg->length()-msg->indexOf(" ")-1);
		//tolgo i caratteri scomodi
		for (int i=1;i<32;i++)
			arg=arg.replace(QChar(i),"");
		//sostituisco i < e > con \< e \>
		arg=arg.replace('<','[');
		arg=arg.replace('>',']');
		return arg;
	}
	else
		return tr("");
};

void irc_engine::set_userdata(QString nk,QString rn,QString pwd)
{
	///Settaggio informazioni utente
	nick=nk;
	real_name=rn;
	password=pwd;
};

void irc_engine::send(QString msg)
{
        //cout << "SEND: " <<msg.toStdString()<<endl; //CHANGED: commented
        qDebug() << msg;
	sock->write(msg.toAscii()+"\r\n");
};

void irc_engine::check_user_online(QString user)
{
	send(tr("ison %1").arg(user));
};

void irc_engine::login()
{
	///Metodo per il login sul server
	sock->write((tr("NICK %1\r\n").arg(nick)).toAscii());
	sock->write((tr("USER %1 %2 %3 :%4\n\r").arg(nick).arg(sock->peerName()).arg(server).arg(nick)).toAscii());
        msg_from_chan(tr("Main"),tr("Entering user information (%1)...").arg(nick));
};

//----------------------------

void irc_engine::Vibrate()
{
    QVibrateAccessory vib;
    if (!vib.vibrateNow())
    {
        vib.setVibrateNow( true );
        QTimer::singleShot(300, this, SLOT(stopVibrate()));
    }
}

void irc_engine::stopVibrate()
{
    QVibrateAccessory vib;
    vib.setVibrateNow( false );
}
