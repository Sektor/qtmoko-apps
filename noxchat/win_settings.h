#ifndef WIN_SETTINGS_H
#define WIN_SETTINGS_H

#include <QDialog>
#include <QLineEdit>
#include <QPushButton>

#include "xml_config.h"
class win_settings : public QDialog
{
	Q_OBJECT
	private:
                xml_config *config;
                QLineEdit *edt_server;
                QLineEdit *edt_port;
                QLineEdit *edt_nick;
                QLineEdit *edt_nick2;
                QLineEdit *edt_nick3;
                QLineEdit *edt_name;
                QLineEdit *edt_away;
                QLineEdit *edt_pass;
        public:
                win_settings(xml_config*, QWidget *);
	public slots:
                void save();
};

#endif
