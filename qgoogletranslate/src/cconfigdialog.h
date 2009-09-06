/* This file is part of QGoogleTranslate
 *
 * Copyright (C) 2009 Durachenko Alexei V. <lexnewton86@gmail.com>
 */

#ifndef CCONFIGDIALOG_H
#define CCONFIGDIALOG_H

#include <QtGui>
#include "ui_configdialog.h"

class CConfigDialog : public QDialog, public Ui::ConfigDialog
{
Q_OBJECT
public:
	CConfigDialog( QWidget * parent = 0, Qt::WFlags f = 0 );

    int defaultSourceLanguageIndex();
    int defaultDestinationLanguageIndex();
    bool dynamicDefaultLangs();

    void setDefaultSourceLanguageIndex(int index);
    void setDefaultDestinationLanguageIndex(int index);
    void setDynamicDefaultLangs(bool val);
};

#endif
