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

#include "mainwindow.h"
#include "gamewidget.h"
#include "gamedialog.h"
#include "resultdialog.h"

#ifdef QTOPIA_PHONE
#include <QSoftMenuBar>
#endif

MainWindow::MainWindow( QWidget* parent, Qt::WFlags f ) :
    QMainWindow( parent, f )
{
    m_sudoku = new GameWidget( this );
    setCentralWidget( m_sudoku );

    setWindowTitle( tr("Greensudoku") );
    setWindowIcon( QPixmap( ":pics/greensudoku.png" ) );

    // Create Menu
#ifndef QTOPIA_PHONE
    QMenuBar * menuBar = new QMenuBar( this );
    setMenuBar( menuBar );

    QMenu *gameMenu = new QMenu( tr("Game"), menuBar );
    menuBar->addMenu( gameMenu );
#else
    QSoftMenuBar::setLabel( m_sudoku, Qt::Key_Select, QSoftMenuBar::NoLabel );
    QMenu *gameMenu = QSoftMenuBar::menuFor(this);
#endif

    gameMenu->addAction( QPixmap( ":pics/beginner.png" ), tr("Beginner"), 
        m_sudoku, SLOT( startBeginner() ) );
    gameMenu->addAction( QPixmap( ":pics/intermediate.png" ), tr("Intermediate"), 
        m_sudoku, SLOT( startIntermediate() ) );
    gameMenu->addAction( QPixmap( ":pics/expert.png" ), tr("Expert"), 
        m_sudoku, SLOT( startExpert() ) );
    gameMenu->addAction( QPixmap( ":pics/close.png" ), tr("Close"),
        QCoreApplication::instance(), SLOT( quit() ) );

    hintAction = new QAction( tr("Show hint"), gameMenu );
    hintAction->setCheckable( true );
    hintAction->setChecked( m_sudoku->isHintShown() );
    gameMenu->addAction( hintAction );
    connect( hintAction, SIGNAL( toggled( bool ) ),
             m_sudoku, SLOT( showHint( bool ) ) );

    connect( m_sudoku, SIGNAL( gameEnded( bool, QTime ) ),
             this, SLOT( endGame( bool, QTime ) ) );

    //QTimer::singleShot(0, this, SLOT(newGame()));
}

MainWindow::~MainWindow()
{
}

/*
 * Show the game dialog (new game, option, continue game if needed)
 */
void MainWindow::newGame()
{
    GameDialog dialog( this, m_sudoku->isHintShown(), m_sudoku->isStarted() );
    dialog.exec();
    m_sudoku->showHint( dialog.isHintShown() );
    if (dialog.actionCode() == GameDialog::StartBeginner)
        m_sudoku->startBeginner();
    else if (dialog.actionCode() == GameDialog::StartIntermediate)
        m_sudoku->startIntermediate();
    else if (dialog.actionCode() == GameDialog::StartExpert)
        m_sudoku->startExpert();
    else if (dialog.actionCode() == GameDialog::ContinueGame)
        m_sudoku->continueGame();
    else
        m_sudoku->startBeginner();
}

void MainWindow::endGame(bool gameWon, QTime duration)
{
    ResultDialog dialog( this );
    dialog.setResult( gameWon, duration );

    if ( dialog.exec() == QDialog::Accepted && 
         dialog.actionCode() == ResultDialog::RestartGame ) 
    {
        m_sudoku->restartGame();
    } 
    else 
    {
        newGame();
    }
}

/*!
 * Save the settings before quitting
 */
void MainWindow::closeEvent ( QCloseEvent * event )
{
    m_sudoku->writeSettings();
    QMainWindow::closeEvent( event );
}
