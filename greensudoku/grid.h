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
 *   Added the guessed numbers.                                            *
 *                                                                         *
 ***************************************************************************/

#ifndef GRID_H
#define GRID_H

#include <QtCore>

class GridKernel;


/*!
 * \brief The Grid class stores a normal sudoku grid
 * It provides functions to create, validate the grid and open/save grids.
 * By default, it create 9x9 sudoku grids.
 */
class Grid
{
public:
    enum Level {
        Beginner = 0,
        Intermediate = 1,
        Expert = 2
    };

    static const int MaxGuesses;

public:
    Grid();
    ~Grid();

    void clear();
    void generate();
    bool validate();
    QList<int> possibleNumbers( int row, int col ) const;

    bool open( QString filename );
    bool save( QString filename ) const;

    bool importNumbers( QString text );
    bool importStartNumbers( QString text );
    bool importGuessedNumbers( QString text );
    QString exportNumbers() const;
    QString exportStartNumbers() const;
    QString exportGuessedNumbers() const;
    void print() const;

    int level() const;
    void setLevel( int level );

    int number( int row, int col ) const;
    void setNumber( int row, int col, int number );

    bool isStartNumber( int row, int col ) const;
    void setStartNumber( int row, int col, bool start );

    /** 
     * Add the given number to the set of guessed numbers,
     * or remove it if it was already guessed. Do nothing
     * if the total number of guesses is over 6.
     */
    void setGuessedNumber( int row, int col, int number );

    QSet<int> guessedNumbers( int row, int col) const;

    int size() const;

    bool isFull() const;

protected:
    GridKernel * m_gridKernel;

private:
    int m_level;
    int m_size;
    QVector<int> m_numbers;
    QVector<bool> m_startNumbers;
    QVector<QSet<int> > m_guessedNumbers;
};

#endif // GRID_H
