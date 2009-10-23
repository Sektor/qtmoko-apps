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

#ifndef GRIDKERNEL_H
#define GRIDKERNEL_H

#include <QtCore>

class Grid;

/*!
 * \brief The GridKernel class provides functions for generating/validating a grid
 * This class is specialized in sudoku grid of 9x9.
 */
class GridKernel
{
public:
    GridKernel();
    virtual ~GridKernel();

    virtual void generate( Grid* grid, int level, int seed=0 );
    bool validate( const Grid& grid ) const;
    QList<int> possibleNumbers( int row, int col, const Grid& grid ) const;

protected:
    bool validateRow (const Grid &grid, int row) const;
    bool validateCol (const Grid &grid, int col) const;
    bool validateBloc (const Grid &grid, int i, int j) const;
};

#endif // GRIDKERNEL_H
