/****************************************************************************
**
** This file is part of the Qt Extended Opensource Package.
**
** Copyright (C) 2009 Trolltech ASA.
**
** Contact: Qt Extended Information (info@qtextended.org)
**
** This file may be used under the terms of the GNU General Public License
** version 2.0 as published by the Free Software Foundation and appearing
** in the file LICENSE.GPL included in the packaging of this file.
**
** Please review the following information to ensure GNU General Public
** Licensing requirements will be met:
**     http://www.fsf.org/licensing/licenses/info/GPLv2.html.
**
**
****************************************************************************/

#include "codecsinstaller.h"

CodecsInstaller::CodecsInstaller(QWidget *parent, Qt::WFlags f)
    : QWidget(parent, f)
{
    bOk = new QPushButton(tr("Install mp3 codec"), this);
    connect(bOk, SIGNAL(clicked()), this, SLOT(okClicked()));
    
    layout = new QVBoxLayout(this);
    layout->addWidget(bOk);
}

CodecsInstaller::~CodecsInstaller()
{
}

bool CodecsInstaller::installFile(QString srcFile, QString dstFile)
{
    QFile src(srcFile);
	QFile dst(dstFile);

    if(dst.exists() && !dst.remove())
    {
        QMessageBox::critical(this, tr("codec installer"),
            tr("Unable to remove ") + dstFile);
        return false;
    }
    if(!src.copy(dstFile))
    {
        QMessageBox::critical(this, tr("codec installer"),
            tr("Unable to create file ") + dstFile);
        return false;    	
    }
    return true;
}

void CodecsInstaller::okClicked()
{
    bool ok = installFile(":/libmad.so", "/opt/qtmoko/lib/libmad.so.0")
           && installFile(":/libmadplugin.so",
               "/opt/qtmoko/plugins/codecs/libmadplugin.so");

    if(ok) {
        QMessageBox::information(this, tr("codecs installer"),
            tr("MP3 codec installed sucessfully, you can uninstall this program now."));
        close();
    }
}
