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

#ifndef GRIDVIEW_H
#define GRIDVIEW_H

#include <QtGui>

class Grid;


/*!
 * \brief The GridView class is widget to view nomal sudoku grid
 */
class GridView : public QWidget
{
    Q_OBJECT

public:
    GridView( QWidget *parent = 0, Qt::WindowFlags f = 0 );

    void setGrid( Grid *grid );

    void updateCell( int row, int col );

    int currentRow() const;
    int currentCol() const;

    virtual int heightForWidth ( int w ) const;

signals:
    void cellSelected( int row, int col );
    void gridFull();
    void numberChanged( int row, int col, int number );

protected:
    virtual void keyPressEvent ( QKeyEvent * event );
    virtual void mouseMoveEvent ( QMouseEvent * event );
    virtual void mousePressEvent ( QMouseEvent * event );
    virtual void paintEvent ( QPaintEvent * event );
    virtual void resizeEvent ( QResizeEvent * event );

private:
    void paintGrid( QPainter *p );
    void paintCell( QPainter *p, int row, int col );

    int cellRow( QPoint point ) const;
    int cellCol( QPoint point ) const;
    QRect cellRect( int row, int col ) const;

private:
    int m_currentRow;
    int m_currentCol;
    int m_cellSize;
    int m_deltaX;
    int m_deltaY;
    const Grid * m_grid;
};

#endif // GRIDVIEW_H
