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

#ifndef LOGITEM_H
#define LOGITEM_H

#include "qqwing.h"

#include <vector>

/**
 * While solving the puzzle, log steps taken in a log item.
 * This is useful for later printing out the solve history
 * or gathering statistics about how hard the puzzle was to
 * solve.
 */
class LogItem {
    public:
        enum LogType {
            GIVEN,
            SINGLE,
            HIDDEN_SINGLE_ROW,
            HIDDEN_SINGLE_COLUMN,
            HIDDEN_SINGLE_SECTION,
            GUESS,
            ROLLBACK,
            NAKED_PAIR_ROW,
            NAKED_PAIR_COLUMN,
            NAKED_PAIR_SECTION,
            POINTING_PAIR_TRIPLE_ROW,
            POINTING_PAIR_TRIPLE_COLUMN,
            ROW_BOX,
            COLUMN_BOX,
            HIDDEN_PAIR_ROW,
            HIDDEN_PAIR_COLUMN,
            HIDDEN_PAIR_SECTION,
        };
        LogItem(int round, LogType type);
        LogItem(int round, LogType type, int value, int position);
        int getRound();
        void print();
        LogType getType();
        ~LogItem();
    private:
        void init(int round, LogType type, int value, int position);
        /**
         * The recursion level at which this item was gathered.
         * Used for backing out log items solve branches that
         * don't lead to a solution.
         */
        int round;

        /**
         * The type of log message that will determine the
         * message printed.
         */
        LogType type;

        /**
         * Value that was set by the operation (or zero for no value)
         */
        int value;

        /**
         * position on the board at which the value (if any) was set.
         */
        int position;
};

int getLogCount(std::vector<LogItem*>* v, LogItem::LogType type);

#endif
