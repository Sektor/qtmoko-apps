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

#include "grid.h"
#include "gridkernel.h"

const int Grid::MaxGuesses = 6;

/*!
 * Constructeur
 * This class is generic, but it is used for 9x9 sudoku here
 */
Grid::Grid() :
    m_level( Beginner ),
    m_size( 3 ),
    m_numbers( 81, 0 ),
    m_startNumbers( 81, false ),
    m_guessedNumbers( 81 )
{
    m_gridKernel = new GridKernel();
}

Grid::~Grid()
{
    delete m_gridKernel;
}

void Grid::clear()
{
    int gridSize = size() * size();
    for (int row = 0; row<gridSize; ++row) {
        for (int col = 0; col<gridSize; ++col) {
            if ( !isStartNumber( row, col ) ) {
                setNumber( row, col, 0 );
            }
        }
    }
}

/*!
 * Generate the grids
 */
void Grid::generate()
{
    QTime t = QTime::currentTime();
    int seed = t.hour()*t.minute()*t.second()*t.msec();
    m_gridKernel->generate( this, m_level, seed );
}

/*!
 * Validate the current grid
 */
bool Grid::validate()
{
    return m_gridKernel->validate( *this );
}

/*!
 * Gives all the possible numbers for a given cell
 */
QList<int> Grid::possibleNumbers( int row, int col ) const
{
    return m_gridKernel->possibleNumbers( row, col, *this );
}


/*!
 * Open the grid given by the file filename
 * The file must have 3 lines with the syntax :
 *  - first line (numbers) : "level:n1:n2...:n80:n81"
 *  - second line (start numbers) : 1 if the number is a start number, 0 else
 *  - third line (guessed numbers) : "2,3,4:1,2:...:g80a,g80b:g81"
 * 0 in the first line indicates that there's no number for the moment.
 */
bool Grid::open( QString filename )
{
    QFile file( filename );
    if ( file.open( QIODevice::ReadOnly ) ) {
        QTextStream in( &file );

        QString numbersLine = in.readLine();
        if ( !importNumbers( numbersLine ) ) {
            return false;
        }

        QString startNumbersLine = in.readLine();
        if ( !importStartNumbers( startNumbersLine ) ) {
            return false;
        }

        QString guessedNumbersLine = in.readLine();
        if (!importGuessedNumbers( guessedNumbersLine ) ) {
            return false;
        }

        file.close();
        return true;
    }
    return false;
}

/*!
 * Save the grid in the file filename
 */
bool Grid::save( QString filename ) const
{
    QFile file( filename );
    if ( file.open( QIODevice::WriteOnly ) ) {
        QTextStream out( &file );

        out << exportNumbers() << endl;
        out << exportStartNumbers() << endl;
        out << exportGuessedNumbers();

        out.flush();
        file.close();
        return true;
    }
    return false;
}


/*!
 * Import the numbers of a grid
 * All defined numbers are start numbers.
 */
bool Grid::importNumbers( QString text )
{
    QStringList numbers = text.split( ':' );
    // there's m_size^4 numbers + level
    int nbNumbers = m_size*m_size*m_size*m_size;
    if ( numbers.count() == nbNumbers+1 ) {
        m_level = numbers[0].toInt();
        for (int i=1; i < numbers.count(); ++i) {
            int value = numbers[i].toInt();
            m_numbers[i-1] = value;
            m_startNumbers[i-1] = (value != 0);
        }
        return true;
    }
    return false;
}


/*!
 * Import the start numbers of a grid
 */
bool Grid::importStartNumbers( QString text )
{
    QStringList startNumbers = text.split( ':' );
    // there's m_size^4 numbers
    int nbNumbers = m_size*m_size*m_size*m_size;
    if ( startNumbers.count() == nbNumbers ) {
        for (int i=0; i < startNumbers.count(); ++i) {
            int value = startNumbers[i].toInt();
            m_startNumbers[i] = (value == 1);
        }
        return true;
    }
    return false;
}

bool Grid::importGuessedNumbers( QString text )
{
    QStringList allGuessedNumbers = text.split( ':' );
    int nbNumbers = m_size*m_size*m_size*m_size;
    if ( allGuessedNumbers.count() == nbNumbers ) {
        for (int i=0; i < allGuessedNumbers.count(); ++i) {
            QStringList guessedNumbers = allGuessedNumbers[i].split( ',' );
            for (int j=0; j< guessedNumbers.count(); ++j) {
                int value = guessedNumbers[j].toInt();
                if (value != 0) {
                    m_guessedNumbers[i].insert(value);
                }
            }
        }
        return true;
    }
    return false;
}

/*!
 * Export the numbers of a grid
 */
QString Grid::exportNumbers() const
{
    QString line;
    QTextStream out( &line );
    out << m_level << ':';
    for (int i=0; i < m_numbers.count()-1; ++i) {
        out << m_numbers[i] << ':';
    }
    out << m_numbers[m_numbers.count()-1];
    out.flush();
    return line;
}

/*!
 * Export the start numbers of a grid
 */
QString Grid::exportStartNumbers() const
{
    QString line;
    QTextStream out( &line );
    for (int i=0; i < m_startNumbers.count()-1; ++i) {
        out << m_startNumbers[i] << ':';
    }
    out << m_startNumbers[m_startNumbers.count()-1];
    out.flush();
    return line;
}

QString Grid::exportGuessedNumbers() const
{
    QString line;
    QTextStream out( &line );
    QVector<QSet<int> >::const_iterator iterAllNumbers = m_guessedNumbers.begin();
    while (iterAllNumbers != m_guessedNumbers.end()) {
        QSet<int> guessedNumbers = *iterAllNumbers;
        QSet<int>::const_iterator iter = guessedNumbers.begin();
        while (iter != guessedNumbers.end()) {
            int value = *iter;
            out << value;
            ++iter;
            if (iter != guessedNumbers.end()) {
                out << ',';
            }
        }
        ++iterAllNumbers;
        if (iterAllNumbers != m_guessedNumbers.end()) {
            out << ':';
        }
    }
    out.flush();
    return line;
}

/*!
 * Print the grid in the console
 * This function is mainly for debugging purpose
 */
void Grid::print() const
{
    QString text;
    QTextStream out( &text );
    int size2 = m_size*m_size;
    int ii, jj, kk;

    out << endl;
    for (ii=0; ii<size2; ++ii) {
        // Horizontal separation
        if ( (ii%m_size) == 0 && ii != 0 ) {
            for (jj=0; jj<m_size; ++jj) {
                for (kk = 0; kk < size2-2; ++kk) out << "-";
                if ( jj != m_size-1 ) out << "+";
            }
            out << endl;
        }
        out << " ";
        // Grid line
        for (jj=0; jj<m_size; ++jj) {
            for (kk=0; kk<m_size; ++kk) {
                if (number(ii, jj*m_size+kk) != -1) {
                    out << number(ii, jj*m_size+kk) << " ";
                } else {
                    out << ". ";
                }
            }
            // Vertical separation
            if (jj!=m_size-1) out << "| ";
        }
        out << endl;
    }
    out.flush();
    qDebug() << text;
}


int Grid::level() const
{
    return m_level;
}

void Grid::setLevel( int level )
{
    m_level = level;
}


int Grid::number( int row, int col ) const
{
    return m_numbers[row*m_size*m_size + col];
}

void Grid::setNumber( int row, int col, int number )
{
    m_numbers[row*m_size*m_size + col] = number;
    m_guessedNumbers[row*m_size*m_size + col].clear();
}


bool Grid::isStartNumber( int row, int col ) const
{
    return m_startNumbers[row*m_size*m_size + col];
}

void Grid::setStartNumber( int row, int col, bool start )
{
    m_startNumbers[row*m_size*m_size + col] = start;
}

void Grid::setGuessedNumber( int row, int col, int number )
{
    if (m_numbers[row*m_size*m_size + col] > 0 )
        setNumber( row, col, 0 );

    if (number == 0) {
      m_guessedNumbers[row*m_size*m_size + col].clear();
    } else {
        QSet<int>& guessedNumbers = m_guessedNumbers[row*m_size*m_size + col];
        if (guessedNumbers.contains(number)) {
            guessedNumbers.remove(number);
        } else if (guessedNumbers.count() < MaxGuesses) {
            guessedNumbers.insert(number);
        }
    }
}

QSet<int> Grid::guessedNumbers( int row, int col ) const
{
    return m_guessedNumbers[row*m_size*m_size + col];
}

int Grid::size() const
{
    return m_size;
}

/*!
 * Indicate if the grid is full and ready for validating
 */
bool Grid::isFull() const
{
    return ( !m_numbers.contains( 0 ) );
}
