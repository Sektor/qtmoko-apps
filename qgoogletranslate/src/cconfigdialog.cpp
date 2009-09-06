/* This file is part of QGoogleTranslate
 *
 * Copyright (C) 2009 Durachenko Alexei V. <lexnewton86@gmail.com>
 */

#include "config.h"
#include "cconfigdialog.h"

CConfigDialog::CConfigDialog( QWidget * parent, Qt::WFlags f) : QDialog(parent, f | Qt::FramelessWindowHint)
{
    setupUi(this);
    setWindowState(Qt::WindowMaximized);
    for( int i = 0; i < gGoogleLangCount; ++i )
    {
        comboBox_LangSrc->addItem( gGoogleLang[i].name );
        comboBox_LangDest->addItem( gGoogleLang[i].name );

        /*QString path = QString(":/flags/flags/none.png");
        QString flag = QString(":/flags/flags/%1.png").arg( gGoogleLang[i].code );
        if( QFile::exists( flag ) )
        {
            path = flag;
        }
        comboBox_LangSrc->setItemIcon( i, QIcon( path ) );
        comboBox_LangDest->setItemIcon( i, QIcon( path ) );*/
    }
}


int CConfigDialog::defaultSourceLanguageIndex() {
    return comboBox_LangSrc->currentIndex();
}


int CConfigDialog::defaultDestinationLanguageIndex() {
    return comboBox_LangDest->currentIndex();
}

bool CConfigDialog::dynamicDefaultLangs() {
    return !groupBox->isChecked();
}

void CConfigDialog::setDefaultSourceLanguageIndex( int index )
{
    if( index < 0 || index > gGoogleLangCount ) index = 0;
    comboBox_LangSrc->setCurrentIndex( index );
}


void CConfigDialog::setDefaultDestinationLanguageIndex( int index )
{
    if( index < 0 || index > gGoogleLangCount ) index = 0;
    comboBox_LangDest->setCurrentIndex( index );
}

void CConfigDialog::setDynamicDefaultLangs(bool val) {
    groupBox->setChecked(!val);
}
