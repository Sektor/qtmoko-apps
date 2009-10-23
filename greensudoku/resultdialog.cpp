/***************************************************************************
 *   Copyright (C) 2007 by Nicolas Arnaud-Cormos                           *
 *   nicolas.arnaudcormos@gmail.com                                        *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "resultdialog.h"

ResultDialog::ResultDialog( QWidget * parent ) :
    QDialog( parent, Qt::FramelessWindowHint )
{
    setupUi( this );

    QFont font = resultLabel->font();
    font.setBold( true );
    resultLabel->setFont( font );

    QSignalMapper* mapper = new QSignalMapper( this );
    mapper->setMapping(restartButton, (int) ResultDialog::RestartGame);
    mapper->setMapping(newButton, (int) ResultDialog::NewGame);

    connect( restartButton, SIGNAL( clicked() ),
             mapper, SLOT( map() ) );
    connect( newButton, SIGNAL( clicked() ),
             mapper, SLOT( map() ) );

    connect ( mapper, SIGNAL( mapped(int) ),
              this, SLOT( setActionCode(int) ) );
}

ResultDialog::~ResultDialog()
{
}

void ResultDialog::setResult( bool win, QTime time )
{
    timeLabel->setText( time.toString( "hh:mm:ss" ) );

    QPalette palette = resultLabel->palette();
    if ( win ) {
        restartButton->setHidden( true );
        palette.setColor( QPalette::WindowText, Qt::darkGreen );
        resultLabel->setPalette( palette );
        resultLabel->setText( tr("You WIN !!") );
    }
    else {
        palette.setColor( QPalette::WindowText, Qt::darkRed );
        resultLabel->setPalette( palette );
        resultLabel->setText( tr("Try again...") );
    }
}

ResultDialog::ActionCode ResultDialog::actionCode() const
{
    return m_actionCode;
}

void ResultDialog::setActionCode(int code)
{
    m_actionCode = (ResultDialog::ActionCode) code;
    accept();
}
