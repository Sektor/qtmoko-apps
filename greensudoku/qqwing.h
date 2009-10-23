/*
 * qqwing - A Sudoku solver and generator
 * Copyright (C) 2006 Stephen Ostermiller
 * http://ostermiller.org/qqwing/
 * Copyright (C) 2007 Jacques Bensimon (jacques@ipm.com)
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#ifndef QQWING_H
#define QQWING_H

#include <Qt/qglobal.h>

#ifdef QQWING_LIB
#define QQWING_EXPORT Q_DECL_EXPORT
#else
#define QQWING_EXPORT Q_DECL_IMPORT
#endif

static inline int cellToColumn(int cell);
static inline int cellToRow(int cell);
static inline int cellToSectionStartCell(int cell);
static inline int cellToSection(int cell);
static inline int rowToFirstCell(int row);
static inline int columnToFirstCell(int column);
static inline int sectionToFirstCell(int section);
static inline int getPossibilityIndex(int valueIndex, int cell);
static inline int rowColumnToCell(int row, int column);
static inline int sectionToCell(int section, int offset);

#define PACKAGE_NAME		"QQWing"
#define PACKAGE_STRING		"QQWing 1.0"

#define GRID_SIZE 3
#define ROW_LENGTH          (GRID_SIZE*GRID_SIZE)
#define COL_HEIGHT          (GRID_SIZE*GRID_SIZE)
#define SEC_SIZE            (GRID_SIZE*GRID_SIZE)
#define SEC_COUNT           (GRID_SIZE*GRID_SIZE)
#define SEC_GROUP_SIZE      (SEC_SIZE*GRID_SIZE)
#define NUM_POSS            (GRID_SIZE*GRID_SIZE)
#define BOARD_SIZE          (ROW_LENGTH*COL_HEIGHT)
#define POSSIBILITY_SIZE    (BOARD_SIZE*NUM_POSS)

/**
 * Given the index of a cell (0-80) calculate
 * the column (0-8) in which that cell resides.
 */
static inline int cellToColumn(int cell){
    return cell%COL_HEIGHT;

}

/**
 * Given the index of a cell (0-80) calculate
 * the row (0-8) in which it resides.
 */
static inline int cellToRow(int cell){
    return cell/ROW_LENGTH;
}

/**
 * Given the index of a cell (0-80) calculate
 * the section (0-8) in which it resides.
 */
static inline int cellToSection(int cell){
    return (cell/SEC_GROUP_SIZE*GRID_SIZE)
            + (cellToColumn(cell)/GRID_SIZE);
}

/**
 * Given the index of a cell (0-80) calculate
 * the cell (0-80) that is the upper left start
 * cell of that section.
 */
static inline int cellToSectionStartCell(int cell){
    return (cell/SEC_GROUP_SIZE*SEC_GROUP_SIZE)
            + (cellToColumn(cell)/GRID_SIZE*GRID_SIZE);
}

/**
 * Given a row (0-8) calculate the first cell (0-80)
 * of that row.
 */
static inline int rowToFirstCell(int row){
    return 9*row;
}

/**
 * Given a column (0-8) calculate the first cell (0-80)
 * of that column.
 */
static inline int columnToFirstCell(int column){
    return column;
}

/**
 * Given a section (0-8) calculate the first cell (0-80)
 * of that section.
 */
static inline int sectionToFirstCell(int section){
    return (section%GRID_SIZE*GRID_SIZE)
            + (section/GRID_SIZE*SEC_GROUP_SIZE);
}

/**
 * Given a value for a cell (0-8) and a cell (0-80)
 * calculate the offset into the possibility array (0-728).
 */
static inline int getPossibilityIndex(int valueIndex, int cell){
    return valueIndex+(NUM_POSS*cell);
}

/**
 * Given a row (0-8) and a column (0-8) calculate the
 * cell (0-80).
 */
static inline int rowColumnToCell(int row, int column){
    return (row*COL_HEIGHT)+column;
}

/**
 * Given a section (0-8) and an offset into that section (0-8)
 * calculate the cell (0-80)
 */
static inline int sectionToCell(int section, int offset){
    return sectionToFirstCell(section)
            + ((offset/GRID_SIZE)*SEC_SIZE)
            + (offset%GRID_SIZE);
}

#endif
