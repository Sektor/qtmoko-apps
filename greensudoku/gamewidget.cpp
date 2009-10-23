/***************************************************************************
 *   Copyright (C) 2007 by Nicolas Arnaud-Cormos                           *
 *   nicolas@qtfr.org                                                      *
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
#include "gamewidget.h"

#include "grid.h"
#include "gridview.h"
#include "numberview.h"

GameWidget::GameWidget(QWidget *parent)
 : QWidget(parent), m_elapsedTime(0)
{
    QVBoxLayout * vLayout = new QVBoxLayout( this );
    setLayout( vLayout );

    m_gridView = new GridView( this );
    vLayout->addWidget( m_gridView );
    m_gridView->setFocus();
    m_numberView = new NumberView( this );
    vLayout->addWidget( m_numberView );

    m_grid = new Grid();
    readSettings();
    if ( !m_start ) {
        m_grid->generate();
    }
    m_gridView->setGrid( m_grid );
    m_numberView->setGrid( m_grid );

    connect( m_numberView, SIGNAL( numberLeftClicked(int) ),
             this, SLOT( currentNumberChanged(int) ) );
    connect( m_gridView, SIGNAL( numberChanged(int, int, int) ),
             this, SLOT( currentNumberChanged(int, int, int) ) );
//    connect( m_numberView, SIGNAL( numberDoubleClicked(int) ),
//             this, SLOT( currentNumberSelected(int) ) );
    connect( m_gridView, SIGNAL( cellSelected(int, int) ),
             m_numberView, SLOT( setSelectedCell(int, int) ) );
}

GameWidget::~GameWidget()
{
    writeSettings();
}

bool GameWidget::isHintShown() const
{
    return m_numberView->isHintShown();
}

bool GameWidget::isStarted() const
{
    return m_start;
}

void GameWidget::startBeginner()
{
    m_grid->setLevel( Grid::Beginner );
    startGame();
}

void GameWidget::startIntermediate()
{
    m_grid->setLevel( Grid::Intermediate );
    startGame();
}

void GameWidget::startExpert()
{
    m_grid->setLevel( Grid::Expert );
    startGame();
}

void GameWidget::continueGame()
{
    m_time.start();
}

/*!
 * Delete all user numbers and restart the game
 */
void GameWidget::restartGame()
{
    m_grid->clear();

    m_gridView->update();
    m_numberView->update();
    m_elapsedTime = 0;
    m_time.start();
    m_start = true;
}

/*!
 * Read the settings :
 *  - current game (if not finished)
 *  - current time
 *  - current level
 */
void GameWidget::readSettings()
{
    QSettings settings( "nikikko", "sudoku" );
    m_numberView->showHint( settings.value( "showHint" ).toBool() );
    m_start = settings.value( "start" ).toBool();
    if ( m_start ) {
        QString numbers = settings.value( "numbers" ).toString();
        QString startNumbers = settings.value( "startNumbers" ).toString();
        QString guessedNumbers = settings.value( "guessedNumbers" ).toString();
        int level = settings.value( "level" ).toInt();
        m_grid->setLevel( level );
        m_grid->importNumbers( numbers );
        m_grid->importStartNumbers( startNumbers );
        m_grid->importGuessedNumbers( guessedNumbers );
        m_elapsedTime = settings.value( "elapsedTime" ).toInt();
    }
}

/*!
 * Write the settings
 */
void GameWidget::writeSettings() const
{
    QSettings settings( "nikikko", "sudoku" );
    settings.setValue( "showHint", m_numberView->isHintShown() );
    settings.setValue( "start", m_start );
    if ( m_start ) {
        settings.setValue( "numbers", m_grid->exportNumbers() );
        settings.setValue( "startNumbers", m_grid->exportStartNumbers() );
        settings.setValue( "guessedNumbers", m_grid->exportGuessedNumbers() );
        settings.setValue( "level", m_grid->level() );
        settings.setValue( "elapsedTime", m_time.elapsed() );
    }
}

void GameWidget::showHint( bool show )
{
    m_numberView->showHint( show );
}

void GameWidget::currentNumberChanged( int number )
{
    int row = m_gridView->currentRow();
    int col = m_gridView->currentCol();
    currentNumberChanged(row, col, number);
}

void GameWidget::currentNumberChanged( int row, int col, int number )
{
    if ( !m_grid->isStartNumber( row, col ) ) {
        if (m_grid->guessedNumbers( row, col ).size() > 0 ||
            m_grid->number( row, col ) == number) 
        {
            m_grid->setGuessedNumber( row, col, number );
        } 
        else 
        {
            m_grid->setNumber( row, col, number );
            if (m_grid->isFull()) {
                endGame();
            }
        }
        m_gridView->updateCell( row, col );
    }
}

void GameWidget::currentNumberSelected( int number )
{
    int row = m_gridView->currentRow();
    int col = m_gridView->currentCol();
    if ( !m_grid->isStartNumber( row, col ) ) {
        m_grid->setNumber( row, col, number );
        if (m_grid->isFull()) {
                endGame();
        }
        m_gridView->updateCell( row, col );
    }
}

/*!
 * Start the game and the timer...
 */
void GameWidget::startGame()
{
    m_grid->generate();
    m_gridView->update();
    m_numberView->update();
    m_elapsedTime = 0;
    m_time.start();
    m_start = true;
}

void GameWidget::endGame()
{
    m_start = false;

    int elapsedTime = ( m_elapsedTime + m_time.elapsed() ) / 1000;
    int hour = elapsedTime/3600;
    int minute = (elapsedTime-3600*hour) / 60;
    int second = elapsedTime%60;
    QTime time( hour, minute, second );
    emit gameEnded(m_grid->validate(), time);
}
