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
 *                                                                         *
 *   09/2007 Olivier Guérin olivier.guerin@hotmail.fr                      *
 *   Moved some methods to the QSudoku component.                          *
 *                                                                         *
 ***************************************************************************/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>

class GameWidget;

/*!
 * \brief The MainWindow holds the QSudoku component. 
 * It manages the start and and the end of the game.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow( QWidget* parent = 0, Qt::WFlags f = 0 );
    ~MainWindow();

public slots:
    /*! 
      Show the GameDialog that ask the user to continue the last game or 
      start a new one with predefined levels. 
    */
    void newGame();

    /*!
      Show the ResultDialog that indicates to the user if he succeeded
      and the time it took. He can start a new game or restart this one.
    */
    void endGame( bool gameWon, QTime gameDuration );

protected:
    virtual void closeEvent ( QCloseEvent * event );

private:
    /*! Component that manage the Sudoku game. */
    GameWidget *m_sudoku;

    QAction * hintAction;
};

#endif // MAINWINDOW_H
