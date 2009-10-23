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

#include "gridview.h"
#include "grid.h"
#include <math.h>

#define NUMBER 9


GridView::GridView( QWidget *parent, Qt::WindowFlags f ) :
        QWidget( parent, f ),
        m_currentRow( 0 ),
        m_currentCol( 0 ),
        m_cellSize( 0 ),
        m_deltaX( 0 ),
        m_deltaY( 0 ),
        m_grid( 0 )
{
    QSizePolicy policy( QSizePolicy::Expanding, QSizePolicy::Expanding );
    policy.setHeightForWidth( true );
    setSizePolicy( policy );
}

void GridView::setGrid( Grid *grid )
{
    m_grid = grid;
}

int GridView::currentRow() const
{
    return m_currentRow;
}

int GridView::currentCol() const
{
    return m_currentCol;
}

/*!
 * The sudoku grid is square.
 */
int GridView::heightForWidth ( int w ) const
{
    return w;
}

/*!
 * Reimplemented from QWidget
 * Navigate in the widget with the arrow keys and modiy one number
 * with the key 0-9 (0 = no number) or Suppr to delete a number.
 */
void GridView::keyPressEvent ( QKeyEvent * event )
{
    int row = m_currentRow;
    int col = m_currentCol;

    switch( event->key() ) {
        case Qt::Key_Left:
            m_currentCol = qMax(0, col-1);
            break;
        case Qt::Key_Up :
            m_currentRow = qMax(0, row-1);
            break;
        case Qt::Key_Right :
            m_currentCol = qMin(8, col+1);
            break;
        case Qt::Key_Down :
            m_currentRow = qMin(8, row+1);
            break;
        case Qt::Key_0 :
        case Qt::Key_1 :
        case Qt::Key_2 :
        case Qt::Key_3 :
        case Qt::Key_4 :
        case Qt::Key_5 :
        case Qt::Key_6 :
        case Qt::Key_7 :
        case Qt::Key_8 :
        case Qt::Key_9 :
            {
	        int number = event->key()-Qt::Key_0;
                emit numberChanged(m_currentRow, m_currentCol, number);
            }
            break;
        case Qt::Key_Delete :
            emit numberChanged(m_currentRow, m_currentCol, 0);
            break;
    }
    // Remove the selected indicator
    if ( row != m_currentRow || col != m_currentCol ) {
        updateCell( row, col );
        emit cellSelected( m_currentRow, m_currentCol );
    }
    updateCell( m_currentRow, m_currentCol );
}

/*!
 * Reimplemented from QWidget
 * Follow the mouse if the button is down.
 */
void GridView::mouseMoveEvent ( QMouseEvent * event )
{
    int row = m_currentRow;
    int col = m_currentCol;
    m_currentRow = cellRow( event->pos() );
    m_currentCol = cellCol( event->pos() );

    if ( row != m_currentRow || col != m_currentCol ) {
        updateCell( row, col );
        updateCell( m_currentRow, m_currentCol );
        emit cellSelected( m_currentRow, m_currentCol );
    }
    event->accept();
}

/*!
 * Reimplemented from QWidget
 * Change the current cell
 */
void GridView::mousePressEvent ( QMouseEvent * event )
{
    int row = m_currentRow;
    int col = m_currentCol;
    m_currentRow = cellRow( event->pos() );
    m_currentCol = cellCol( event->pos() );

    if ( row != m_currentRow || col != m_currentCol ) {
        updateCell( row, col );
        updateCell( m_currentRow, m_currentCol );
        emit cellSelected( m_currentRow, m_currentCol );
    }
    event->accept();
}

/*!
 * Reimplemented from QWidget
 * Paint the sudoku grid.
 */
void GridView::paintEvent ( QPaintEvent * event )
{
    QPainter p( this );

    // Draw the cells
    QRect rect = event->rect();
    int rowMin = cellRow( rect.topLeft() );
    int rowMax = cellRow( rect.bottomRight() ) + 1;
    int colMin = cellCol( rect.topLeft() );
    int colMax = cellCol( rect.bottomRight() ) + 1;
    for (int row=rowMin; row<rowMax; ++row) {
        for (int col=colMin; col<colMax; ++col) {
            paintCell( &p, row, col );
        }
    }

    // Update the grid
    paintGrid( &p );
}

/*!
 * Reimplemented from QWidget
 * Compute the size of one cell and the horizontal delta to center the grid
 * in the widget.
 */
void GridView::resizeEvent ( QResizeEvent * event )
{
   int size = qMin( event->size().width(), event->size().height() );
   m_cellSize = (size - (NUMBER+1)) / NUMBER;
   // deltaX and deltaY are used to center the grid in the widget
   m_deltaX = (event->size().width() - (NUMBER*(m_cellSize+1) + 1)) / 2;
   m_deltaY = (event->size().height() - (NUMBER*(m_cellSize+1) + 1)) / 2;
}


/*!
 * Call for an update of the cell (row, col)
 */
void GridView::updateCell( int row, int col )
{
    QRect rect = cellRect( row, col );
    update( rect );
}

/*!
 * Draw the cell (row, col)
 * If the cell is a startValue, the background is grey (red if selected),
 * else the background is white (green if selected).
 * The font size is adapted with the size of the cell.
 */
void GridView::paintCell( QPainter *p, int row, int col ) {
    p->save();
    if ( m_grid ) {
        bool startValue = m_grid->isStartNumber( row, col );
        bool selected = ( row == m_currentRow && col == m_currentCol );
        QRect rect = cellRect( row, col );

        // Draw the background rect
        p->setPen( QPen(Qt::NoPen) );
        if ( startValue ) {
            if ( selected ) p->setBrush(Qt::red);
            else p->setBrush( QColor( 230, 230, 230 ) );
        } else {
            if ( selected ) p->setBrush(Qt::green);
            else p->setBrush(Qt::white);
        }
        p->drawRect(rect);

        // Draw the number
        int value = m_grid->number( row, col );
        QSet<int> guessedNumbers = m_grid->guessedNumbers( row, col );
        p->setPen( QPen(Qt::black) );
        if ( value != 0 ) {
            QFont font = p->font();
            QString text = QString::number(value);
            int fontSize = qMin(rect.height()-2, 30);
            font.setPixelSize(fontSize);
            p->setFont(font);
            p->setBrush(Qt::NoBrush);

            QTextOption textOption(Qt::AlignCenter);
            p->drawText(rect, text, textOption);
        } else if (guessedNumbers.count() > 0 ) {
            QFont font = p->font();

            int fontSize = qMin((rect.height()-2)/2, 30);
            font.setPixelSize(fontSize);
            p->setFont(font);
            p->setBrush(Qt::NoBrush);

            QTextOption textOption(Qt::AlignCenter);
            const int ColCount = guessedNumbers.size() / 2 + guessedNumbers.size() % 2;
            rect.setHeight(rect.height() / 2);
            rect.setWidth(rect.width() / ColCount);
            int i = 0;
            foreach (int value, guessedNumbers)
            {
                p->drawText(rect, QString::number(value), textOption);

                i++;
                if (i % ColCount == 0)
                    rect.translate(-rect.width()*(ColCount - 1), rect.height());
                else
                    rect.translate(rect.width(), 0);
            }
        }
    }
    p->restore();
}

/*!
 * Draw the grid of the sudoku.
 * There are inner 6 segments in grey and 2 in black. Draw also the box
 * around the grid.
 * */
void GridView::paintGrid( QPainter *p )
{
    p->save();
    int max = NUMBER*(m_cellSize+1);
	int number2 = (int) sqrt((float)NUMBER);
    // Draw inner grey lines
    p->setPen( QPen(Qt::gray) );
    for (int i=1; i<NUMBER; ++i) {
        int v = i*m_cellSize + i;
        p->drawLine(m_deltaX, v+m_deltaY, max+m_deltaX, v+m_deltaY);
        p->drawLine(v+m_deltaX, m_deltaY, v+m_deltaX, max+m_deltaY);
    }
    // Draw inner black lines
    p->setPen( QPen(Qt::black, 2) );
    for (int i=1; i<number2; ++i) {
        int v = number2*( i*m_cellSize + i );
        p->drawLine(m_deltaX, v+m_deltaY, max+m_deltaX, v+m_deltaY);
        p->drawLine(v+m_deltaX, m_deltaY, v+m_deltaX, max+m_deltaY);
    }

    QRect bigRect(m_deltaX, m_deltaY, max, max);
    p->setBrush( Qt::NoBrush );
    p->setPen( QPen(Qt::black, 2) );
    p->drawRect( bigRect );
    p->restore();
}


/*!
 * Get the cell row for the current point
 */
int GridView::cellRow( QPoint point ) const
{
    int row = (point.y()-m_deltaY) / (m_cellSize+1);
    return qMax( 0, qMin( (NUMBER-1), row ) );
}

/*!
 * Get the cell row for the current point
 */
int GridView::cellCol( QPoint point ) const
{
    int col = (point.x()-m_deltaX) / (m_cellSize+1);
    return qMax( 0, qMin( (NUMBER-1), col ) );
}

/*!
 * Get the rectangle of the cell (row, col)
 */
QRect GridView::cellRect( int row, int col ) const
{
    int x = col*(m_cellSize+1)+1 + m_deltaX;
    int y = row*(m_cellSize+1)+1 + m_deltaY;
    return QRect( x, y, m_cellSize, m_cellSize );
}
