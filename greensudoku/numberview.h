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

#ifndef NUMBERVIEW_H
#define NUMBERVIEW_H

#include <QtGui>

class Grid;


/*!
 * \brief The NumberView is an "input" widget for sudoku game
 */
class NumberView : public QWidget
{
    Q_OBJECT

public:
    NumberView( QWidget* parent = 0, Qt::WFlags f = 0 );
    ~NumberView();

    void setGrid( Grid *grid );
    bool isHintShown() const;

    virtual int heightForWidth ( int w ) const;

public slots:
    void setSelectedCell( int row, int col );
    void showHint( bool show );

signals:
    void numberLeftClicked( int number );
    void numberRightClicked( int number );

protected:
    virtual void mouseReleaseEvent ( QMouseEvent * event );
    virtual void paintEvent ( QPaintEvent * event );
    virtual void resizeEvent ( QResizeEvent * event );

private:
    void paintCell( QPainter *p, int number, bool possible = true );
    int cellNumber( QPoint point ) const;

private:
    int m_cellSize;
    int m_deltaX;
    bool m_showHint;
    int m_currentRow;
    int m_currentCol;
    Grid * m_grid;
};

#endif // NUMBERVIEW_H
