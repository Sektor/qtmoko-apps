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
 *   Creation of this class and moved MainWindow methods in it.            *
 *                                                                         *
 ***************************************************************************/
#ifndef QSUDOKU_H
#define QSUDOKU_H

#include <QtGui>

class Grid;
class GridView;
class NumberView;

/*!
 * \brief Widget that show a Sudoku board and manage the game.
 *
 * This widget shows a Sudoku board. It is begun with the 
 * QSudoku::startBeginner(),QSudoku::startIntermediate() and 
 * QSudoku::startExpert() methods. 
 * When the user stops the game (whether it is the end or a pause), 
 * the game state is stored and it is restored when the user 
 * restarts the application.
 *
 * A game can be continued if it was left the last time 
 * the application was launched with the QSudoku::continueGame() method.
 * A game can be restarted with the QSudoku::restartGame() method. 
 * This removes the numbers set by the user.
 *
 * A completed board is signaled with the QSudoku::gameEnded() signal.
 *
 * A note on the implementation: This class act as a controller 
 * in a MVC paradigm. The model is represented by the Grid class and
 * the views are the GridView and NumberView classes.
 */
class GameWidget : public QWidget
{
Q_OBJECT

public:
    GameWidget(QWidget *parent = 0);
    ~GameWidget();

    bool isHintShown() const;

    bool isStarted() const;

signals:
    void gameEnded(bool won, QTime gameDuration);

public slots:
    /*! Generate a beginner grid and start the game. */
    void startBeginner();

    /*! Generate an intermediate grid and start the game. */
    void startIntermediate();

    /*! Generate an expert grid and start the game. */
    void startExpert();

    /*! Continue the game (launch the timer). */
    void continueGame();

    /*! Remove numbers set by the user and start the game. */
    void restartGame();

    void showHint( bool show );

public:
    void readSettings();
    void writeSettings() const;

protected:
    void startGame();
    void endGame();

protected slots:
    void currentNumberChanged( int number );
    void currentNumberChanged( int row, int col, int number );
    void currentNumberSelected( int number );

private:
    /*! Component that show the Sudoku grid. */
    GridView* m_gridView;

    /*! Component that show a row of numbers from 1 to 9. */
    NumberView* m_numberView;

    /*!
      Sudoku grid where are stored the initial numbers 
      and those set by the user. 
    */
    Grid* m_grid;

    /*! Timer used to compute the game duration. */
    QTime m_time;

    /*! Flag that indicate if a game is started. */
    bool m_start;

    /*!
      Time elapsed since the game was started.
      We cannot rely on the m_time timer since the game may have been paused. 
    */
    int m_elapsedTime;
};

#endif
