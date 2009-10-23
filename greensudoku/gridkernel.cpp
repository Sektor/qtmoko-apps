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

#include "gridkernel.h"
#include "grid.h"
#include "sudokuboard.h"

class GridKernelGenerator : public SudokuBoard 
{
public:
    GridKernelGenerator() {
    }
    Grid::Level generate(QVector<int>& numbers, int seed)
    {
        Q_UNUSED(seed)
        Grid::Level result = Grid::Beginner;
        generatePuzzle();
        SudokuBoard::Difficulty difficulty = getDifficulty();
        switch (difficulty)
        {
            case UNKNOWN:
            case SIMPLE:
            case EASY:
                result = Grid::Beginner;
                break;
            case INTERMEDIATE:
                result = Grid::Intermediate;
                break;
            case EXPERT:
                result = Grid::Expert;
                break;
        }
        int* board = getPuzzle();
        for (int i = 0; i < BOARD_SIZE; ++i)
        {
            numbers[i] = board[i];
        }
        return result;
    }
};

GridKernel::GridKernel()
{
}

GridKernel::~GridKernel()
{
}

/*!
 * Generate a grid with the given level
 */
void GridKernel::generate( Grid* grid, int level, int seed )
{
    if ( grid ) {
        GridKernelGenerator d;
        QVector<int> numbers(81, 0);
        bool ok = false;
        while( !ok ) {
            Grid::Level l = d.generate( numbers, seed );
            if (l == level) {
              ok = true;
            }
        }
        for (int i=0; i<numbers.count(); ++i) {
            int size = 9;
            grid->setNumber( i/size, i%size, numbers[i] );
            grid->setStartNumber( i/size, i%size, (numbers[i]!=0) );
        }
    }
}


/*!
 * Validate the given grid
 */
bool GridKernel::validate( const Grid& grid ) const
{
    int size = grid.size();
    int size2 = size*size;
    int ii, jj;
    // Validation des lignes et des colonnes
    for (ii=0; ii<size2; ++ii) {
        if (!validateRow(grid, ii)) return false;
        if (!validateCol(grid, ii)) return false;
    }
    // Validation des zones
    for (ii=0; ii<size; ++ii) {
        for (jj=0; jj<size; ++jj) {
            if (!validateBloc(grid, ii, jj)) return false;
        }
    }
    return true;
}


/*!
 * Give the possibles numbers for a given cell
 */
QList<int> GridKernel::possibleNumbers( int row, int col, const Grid& grid ) const
{
    QList<int> result;
    QMap<int, bool> number;
    int size = grid.size();
    int size2 = size*size;
    int ii, jj;

    // Colon and row
    for (int ii=0; ii<size2; ++ii) {
        if (ii!=row)
            number[grid.number(ii, col)] = true;
        if (ii!=col)
            number[grid.number(row, ii)] = true;
    }

    // Bloc
    for (ii=0; ii<size; ++ii) {
        for (jj=0; jj<size; ++jj) {
            int irow = ii+(row/size)*size;
            int jcol = jj+(col/size)*size;
            if (irow!=row && jcol!=col)
                number[grid.number(irow, jcol)] = true;
        }
    }

    // Create the list
    for (ii=1; ii<=size2; ++ii) {
        if (number.find(ii)==number.end())
            result << ii;
    }
    return result;
}


/*!
 * Validate a row
 */
bool GridKernel::validateRow (const Grid &grid, int row) const
{
    QMap<int, bool> number;
    int size2 = grid.size()*grid.size();
    for (int ii=0; ii<size2; ++ii) {
        number[grid.number(row, ii)] = true;
    }
    if (number.count()==size2 && number.find(0)==number.end())
        return true;
    else
        return false;
}


/*!
 * Validate a colon
 */
bool GridKernel::validateCol (const Grid &grid, int col) const
{
    QMap<int, bool> number;
    int size2 = grid.size()*grid.size();
    for (int ii=0; ii<size2; ++ii) {
        number[grid.number(ii, col)] = true;
    }
    if (number.count()==size2 && number.find(0)==number.end())
        return true;
    else
        return false;
}


/*!
 * Validate a bloc
 */
bool GridKernel::validateBloc(const Grid &grid, int i, int j) const
{
    QMap<int, bool> number;
    int size = grid.size();
    int size2 = size*size;
    for (int ii=0; ii<size; ++ii) {
        for (int jj=0; jj<size; ++jj) {
            number[grid.number(ii+i*size, jj+j*size)] = true;
        }
    }
    if (number.count()==size2 && number.find(0)==number.end())
        return true;
    else
        return false;
}
