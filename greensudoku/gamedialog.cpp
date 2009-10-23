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

#include "gamedialog.h"

GameDialog::GameDialog( QWidget * parent, bool showHint, bool showContinue ) :
    QDialog( parent, Qt::FramelessWindowHint )
{
    setupUi( this );

    continueButton->setHidden( !showContinue );
    hintCheckBox->setChecked( showHint );

    QSignalMapper* mapper = new QSignalMapper( this );
    mapper->setMapping(beginnerButton, (int) GameDialog::StartBeginner);
    mapper->setMapping(intermediateButton, (int) GameDialog::StartIntermediate);
    mapper->setMapping(expertButton, (int) GameDialog::StartExpert);
    mapper->setMapping(continueButton, (int) GameDialog::ContinueGame);

    connect( beginnerButton, SIGNAL( clicked() ),
             mapper, SLOT( map() ) );
    connect( intermediateButton, SIGNAL( clicked() ),
             mapper, SLOT( map() ) );
    connect( expertButton, SIGNAL( clicked() ),
             mapper, SLOT( map() ) );
    connect( continueButton, SIGNAL( clicked() ),
             mapper, SLOT( map() ) );

    connect ( mapper, SIGNAL( mapped(int) ),
              this, SLOT( setActionCode(int) ) );

}

GameDialog::~GameDialog()
{
}

bool GameDialog::isHintShown() const
{
    return hintCheckBox->isChecked();
}

GameDialog::ActionCode GameDialog::actionCode() const
{
    return m_actionCode;
}

void GameDialog::setActionCode( int code )
{
    m_actionCode = (GameDialog::ActionCode) code;
    accept();
}
