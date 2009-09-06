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
#include "xml_config.h"
#include <QDebug>

xml_config::xml_config(QString filename)
{
	fl=new QFile(filename);
        if (fl->open(QIODevice::ReadOnly))
        {
            loaded = doc.setContent(fl,true,&err,&err_row,&err_col);
            fl->close();
        }
        else
        {
            loaded = false;
        }
};

bool xml_config::isLoaded()
{
        return loaded;
}

QString xml_config::get_browser()
{
	return tr("firefox");
};

QC_server xml_config::get_server(int n)
{
	QC_server srv;
        QDomNodeList node_list=doc.elementsByTagName(tr("server"));
        QDomElement e=node_list.item(n).toElement();
        srv.host=e.attribute(tr("host"));
        srv.port=e.attribute(tr("port")).toInt();
        return srv;
};

int xml_config::identity_count()
{
        QDomNodeList node_list=doc.elementsByTagName(tr("identity"));
        return node_list.count();
};

QC_identity xml_config::get_identity(int n)
{
	QC_identity ide;
        QDomNodeList node_list=doc.elementsByTagName(tr("identity"));
        if (n<node_list.count())
        {
                QDomElement e=node_list.item(n).toElement();
                ide.nick=e.attribute("nick");
                ide.real_name=e.attribute("real_name");
                ide.password=e.attribute("password");
                ide.away_message=e.attribute("away");
        }
	return ide;
};

QStringList xml_config::get_notify_list()
{
	//Recupera la notify list dal file xml
	QStringList list;
        QDomNodeList node_list=doc.elementsByTagName(tr("user"));
        //ciclo per tutti gli utenti
        for (int i=0;i<node_list.count();i++)
        {
                QDomElement e=node_list.item(i).toElement();
                list << e.attribute("nick").toUpper();
        }
	return list;
};

bool xml_config::user_in_notify_list(QString user)
{
	QStringList tmp=get_notify_list();
	if (tmp.indexOf(user.toUpper())==-1)
		return false;
	else
		return true;
};

bool xml_config::add_notify_user(QString user)
{
        //cout << "aggiungo l'utente " << user.toStdString()<<endl; //CHANGED: commented
        qDebug() << user;
	//controllo che non ci sia giЮ
	//faccio il backup del file attuale ed apro il file originale
        if ( !user_in_notify_list(user.toUpper()) )
	{
		//trovo i nodi relativi agli utenti
		QDomNodeList node_list=doc.elementsByTagName(tr("notify"));
		//creo un elemento sotto il nodo notify
		QDomElement e=doc.createElement("user");
		//creo l'attributo nick
		e.setAttribute("nick",user);
		//aggiungo il nuovo elemento al nodo notify trovato in precedenza
		node_list.item(0).appendChild(e);
		//salvataggio su file temporaneo
		return save();
	}
	else
		return false;
};

void xml_config::del_notify_user(QString user)
{
	//controllo che non ci sia giЮ
	//faccio il backup del file attuale ed apro il file originale
        if ( user_in_notify_list(user) )
	{
		//trovo i nodi relativi agli utenti
		QDomNodeList users=doc.elementsByTagName(tr("notify"));
		QDomNodeList node_list=doc.elementsByTagName(tr("user"));
		for (int i=0;i<node_list.count();i++)
		{
			QDomElement e=node_list.item(i).toElement();
			if (e.attribute("nick").toUpper()==user.toUpper())
			{
				cout << "del_notify_user: user removed" << endl;
				users.item(0).removeChild(node_list.item(i));
			}
		}
		save();
	}
};

bool xml_config::save()
{
        fl->open(QIODevice::WriteOnly);
        fl->write(doc.toByteArray());
        fl->close();
};

xml_config::~xml_config()
{
};

//------------------------

void xml_config::set_server(QString server)
{
        QDomNodeList node_list=doc.elementsByTagName(tr("server"));
        QDomElement e=node_list.item(0).toElement();
        e.setAttribute("host", server);
};

void xml_config::set_port(QString port)
{
        QDomNodeList node_list=doc.elementsByTagName(tr("server"));
        QDomElement e=node_list.item(0).toElement();
        e.setAttribute("port", port);
};

void xml_config::clear_identities()
{
        QDomNodeList identities=doc.elementsByTagName(tr("identities"));
        QDomNodeList node_list=doc.elementsByTagName(tr("identity"));
        //for (int i=0;i<node_list.count();i++)
        while (node_list.count() > 0)
        {
                //identities.item(0).removeChild(node_list.item(i));
                identities.item(0).removeChild(node_list.item(0));
                node_list=doc.elementsByTagName(tr("identity"));
        }
};

void xml_config::add_identity(QString name, QString nick, QString pass, QString away)
{
        QDomNodeList identities=doc.elementsByTagName(tr("identities"));
        QDomElement e=doc.createElement("identity");
        e.setAttribute("real_name",name);
        e.setAttribute("nick",nick);
        e.setAttribute("password",pass);
        e.setAttribute("away",away);
        identities.item(0).appendChild(e);
};
