#include "win_settings.h"
#include <QGridLayout>
#include <QLabel>
#include <QMessageBox>

win_settings::win_settings(xml_config *conf, QWidget *parent) : QDialog(parent)
{
        setWindowOpacity(0.90);
        setFixedSize(380,400);
        config=conf;
	setModal(true);
        setWindowTitle(tr("Settings"));

        edt_server=new QLineEdit(this);
        edt_port=new QLineEdit(this);
        edt_nick=new QLineEdit(this);
        edt_nick2=new QLineEdit(this);
        edt_nick3=new QLineEdit(this);
        edt_name=new QLineEdit(this);
        edt_away=new QLineEdit(this);
        edt_pass=new QLineEdit(this);

        QLabel *serverLabel = new QLabel(this);
        QLabel *portLabel = new QLabel(this);
        QLabel *nickLabel = new QLabel(this);
        QLabel *nick2Label = new QLabel(this);
        QLabel *nick3Label = new QLabel(this);
        QLabel *nameLabel = new QLabel(this);
        QLabel *awayLabel = new QLabel(this);
        QLabel *passLabel = new QLabel(this);

        serverLabel->setText(tr("Server"));
        portLabel->setText(tr("Port"));
        nameLabel->setText(tr("Name"));
        nickLabel->setText(tr("Nick"));
        nick2Label->setText(tr("Nick 2"));
        nick3Label->setText(tr("Nick 3"));
        passLabel->setText(tr("Password"));
        awayLabel->setText(tr("Away msg"));

        QPushButton *btn_save=new QPushButton(this);
        btn_save->setMinimumWidth(100);
        btn_save->setText(tr("Save"));

        QGridLayout *grid=new QGridLayout(this);
        grid->addWidget(serverLabel,0,0); grid->addWidget(edt_server,0,1);
        grid->addWidget(portLabel,1,0); grid->addWidget(edt_port,1,1);
        grid->addWidget(nameLabel,2,0); grid->addWidget(edt_name,2,1);
        grid->addWidget(nickLabel,3,0); grid->addWidget(edt_nick,3,1);
        grid->addWidget(nick2Label,4,0); grid->addWidget(edt_nick2,4,1);
        grid->addWidget(nick3Label,5,0); grid->addWidget(edt_nick3,5,1);
        grid->addWidget(passLabel,6,0); grid->addWidget(edt_pass,6,1);
        grid->addWidget(awayLabel,7,0); grid->addWidget(edt_away,7,1);
        grid->addWidget(btn_save,8,0,1,2,Qt::AlignCenter);

        connect (btn_save,SIGNAL(clicked()),this,SLOT(save()));

        //---------------

        edt_server->setText( config->get_server(0).host );
        edt_port->setText( QString::number(config->get_server(0).port) );

        int idc = config->identity_count();
        if (idc>=1)
        {
            edt_nick->setText(config->get_identity(0).nick);
            edt_away->setText(config->get_identity(0).away_message);
            edt_pass->setText(config->get_identity(0).password);
            edt_name->setText(config->get_identity(0).real_name);
        }
        if (idc>=2) edt_nick2->setText(config->get_identity(1).nick);
        if (idc>=3) edt_nick3->setText(config->get_identity(2).nick);
};

void win_settings::save()
{
        config->set_server(edt_server->text());
        config->set_port(edt_port->text());
        config->clear_identities();
        config->add_identity(edt_name->text(), edt_nick->text(), edt_pass->text(), edt_away->text());
        if (!edt_nick2->text().isEmpty())
            config->add_identity(edt_name->text(), edt_nick2->text(), "", edt_away->text());
        if (!edt_nick3->text().isEmpty())
            config->add_identity(edt_name->text(), edt_nick3->text(), "", edt_away->text());
        config->save();
        close();

        QMessageBox::warning(this,tr("NoxChat"),tr("New settings will be applied after restart of the program"));
};
