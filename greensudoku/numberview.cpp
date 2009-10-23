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

#include "numberview.h"
#include "grid.h"

// Add 0 before
#define NUMBER 9


NumberView::NumberView( QWidget* parent, Qt::WFlags f ) :
    QWidget( parent, f ),
    m_cellSize( 0 ),
    m_showHint( false ),
    m_currentRow( 0 ),
    m_currentCol( 0 ),
    m_grid( 0 )
{
    QSizePolicy policy( QSizePolicy::Expanding, QSizePolicy::Preferred );
    policy.setHeightForWidth( true );
    setSizePolicy( policy );
}

NumberView::~NumberView()
{
}


void NumberView::setGrid( Grid *grid )
{
    m_grid = grid;
}

bool NumberView::isHintShown() const
{
    return m_showHint;
}


/*!
 * Modify the current cell of the grid
 * This function is mainly used for the help.
 */
void NumberView::setSelectedCell( int row, int col )
{
    m_currentRow = row;
    m_currentCol = col;
    update();
}

void NumberView::showHint( bool show )
{
    m_showHint = show;
    update();
}


/*!
 * Redefined from QWidget
 */
int NumberView::heightForWidth ( int w ) const
{
    return (w-1)/(NUMBER+1)+2;
}


/*!
 * Redefined from QWidget
 */
void NumberView::mouseReleaseEvent ( QMouseEvent * event )
{
    bool startNumber = m_grid->isStartNumber( m_currentRow, m_currentCol );
    if ( !startNumber ) {
        int number = cellNumber( event->pos() );
        if (event->button() == Qt::LeftButton) {
            emit numberLeftClicked( number );
        } else if (event->button() == Qt::RightButton) {
            emit numberRightClicked( number );
        }
    }
}

/*!
 * Redefined from QWidget
 */
void NumberView::paintEvent ( QPaintEvent * event )
{
    Q_UNUSED( event );
    QPainter p( this );

    QList<int> possibleNumbers;
    if ( m_grid && m_showHint ) {
        possibleNumbers = m_grid->possibleNumbers( m_currentRow, m_currentCol );
    }
    for (int i=0; i<(NUMBER+1); ++i) {
        paintCell(&p, i, possibleNumbers.contains(i) );
    }
}

/*!
 * Reimplemented from QWidget
 */
void NumberView::resizeEvent ( QResizeEvent * event )
{
   int size = qMin( (event->size().width()-1)/(NUMBER+1), event->size().height()-1 );
   m_cellSize = size-1;

   m_deltaX = (event->size().width() - ((NUMBER+1)*(m_cellSize+1) + 1)) / 2;
}


/*!
 * Draw the number's cell
 */
void NumberView::paintCell( QPainter *p, int number, bool possible )
{
    p->save();

    int x = number*(m_cellSize+1) + m_deltaX;
    QRect rect = QRect( x, 0, m_cellSize+2, m_cellSize+2 );

    // Draw the background rect
    p->setPen( Qt::black );
    bool startNumber = m_grid->isStartNumber( m_currentRow, m_currentCol );
    if ( number && (startNumber || ( !possible && m_showHint ) ) ) {
        p->setBrush( QColor( 255, 100, 100 ) );
    }
    else {
        p->setBrush(Qt::white);
    }
    p->drawRect(rect);

    // Draw the number
    p->setPen( QPen(Qt::black) );
    p->setBrush(Qt::NoBrush);

    if ( number ) {
        QFont font = p->font();
        QString text = QString::number(number);
        int fontSize = qMin(rect.height()-10, 30);
        font.setPixelSize(fontSize);
        p->setFont(font);

        QTextOption textOption(Qt::AlignCenter);
        p->drawText(rect, text, textOption);
    }
    else {
        p->setPen( QPen( Qt::red, 2 ) );
        p->setClipRect( rect );
        p->drawLine( rect.topLeft(), rect.bottomRight() );
        p->drawLine( rect.topRight(), rect.bottomLeft() );
        p->setPen( QPen(Qt::black) );
        p->drawRect(rect);
    }

    p->restore();
}


/*!
 * Return the number under the point
 */
int NumberView::cellNumber( QPoint point ) const
{
    int col = (point.x()-m_deltaX) / (m_cellSize+1) - 1;
    return qMax( 0, qMin( (NUMBER+1), col+1 ) );
}
