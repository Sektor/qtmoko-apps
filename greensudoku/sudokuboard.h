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

#ifndef SUDOKUBOARD_H
#define SUDOKUBOARD_H

#include "qqwing.h"

#include <vector>

class LogItem;
 
/**
 * The board containing all the memory structures and
 * methods for solving or generating sudoku puzzles.
 */
class SudokuBoard {
    public:
        enum PrintStyle {
            ONE_LINE,
            COMPACT,
            READABLE,
            CSV,
        };
        enum Difficulty {
            UNKNOWN,
            SIMPLE,
            EASY,
            INTERMEDIATE,
            EXPERT,
        };
        SudokuBoard();
        bool setPuzzle(int* initPuzzle);
        int* getPuzzle();
        void printPuzzle();
        void printSolution();
        bool solve();
        int countSolutions();
        void printPossibilities();
        bool isSolved();
        void printSolveHistory();
        void setRecordHistory(bool recHistory);
        void setLogHistory(bool logHist);
        void setPrintStyle(PrintStyle ps);
        bool generatePuzzle();
        int getGivenCount();
        int getSingleCount();
        int getHiddenSingleCount();
        int getNakedPairCount();
        int getHiddenPairCount();
        int getBoxLineReductionCount();
        int getPointingPairTripleCount();
        int getGuessCount();
        int getBacktrackCount();
        void printSolveInstructions();
        SudokuBoard::Difficulty getDifficulty();
        char* getDifficultyAsString();
        ~SudokuBoard();

    private:
        /**
         * The 81 integers that make up a sudoku puzzle.
         * Givens are 1-9, unknows are 0.
         * Once initialized, this puzzle remains as is.
         * The answer is worked out in "solution".
         */
        int* puzzle;

        /**
         * The 81 integers that make up a sudoku puzzle.
         * The solution is built here, after completion
         * all will be 1-9.
         */
        int* solution;

        /**
         * Recursion depth at which each of the numbers
         * in the solution were placed.  Useful for backing
         * out solve branches that don't lead to a solution.
         */
        int* solutionRound;

        /**
         * The 729 integers that make up a the possible
         * values for a suduko puzzle. (9 possibilities
         * for each of 81 squares).  If possibilities[i]
         * is zero, then the possibility could still be
         * filled in according to the sudoku rules.  When
         * a possibility is eliminated, possibilities[i]
         * is assigned the round (recursion level) at
         * which it was determined that it could not be
         * a possibility.
         */
        int* possibilities;

        /**
         * An array the size of the board (81) containing each
         * of the numbers 0-n exactly once.  This array may
         * be shuffled so that operations that need to
         * look at each cell can do so in a random order.
         */
        int* randomBoardArray;

        /**
         * An array with one element for each position (9), in
         * some random order to be used when trying each
         * position in turn during guesses.
         */
        int* randomPossibilityArray;

        /**
         * Whether or not to record history
         */
        bool recordHistory;

        /**
         * Whether or not to print history as it happens
         */
        bool logHistory;

        /**
         * A list of moves used to solve the puzzle.
         * This list contains all moves, even on solve
         * branches that did not lead to a solution.
         */
        std::vector<LogItem*>* solveHistory;

        /**
         * A list of moves used to solve the puzzle.
         * This list contains only the moves needed
         * to solve the puzzle, but doesn't contain
         * information about bad guesses.
         */
        std::vector<LogItem*>* solveInstructions;

        /**
         * The style with which to print puzzles and solutions
         */
        PrintStyle printStyle;

        /**
         * The last round of solving
         */
        int lastSolveRound;
        bool reset();
        bool singleSolveMove(int round);
        bool onlyPossibilityForCell(int round);
        bool onlyValueInRow(int round);
        bool onlyValueInColumn(int round);
        bool onlyValueInSection(int round);
        bool solve(int round);
        int countSolutions(int round, bool limitToTwo);
        bool guess(int round, int guessNumber);
        bool isImpossible();
        void rollbackRound(int round);
        bool pointingRowReduction(int round);
        bool rowBoxReduction(int round);
        bool colBoxReduction(int round);
        bool pointingColumnReduction(int round);
        bool hiddenPairInRow(int round);
        bool hiddenPairInColumn(int round);
        bool hiddenPairInSection(int round);
        void mark(int position, int round, int value);
        int findPositionWithFewestPossibilities();
        bool handleNakedPairs(int round);
        int countPossibilities(int position);
        bool arePossibilitiesSame(int position1, int position2);
        void addHistoryItem(LogItem* l);
        void markRandomPossibility(int round);
        void shuffleRandomArrays();
        void print(int* sudoku);
        void rollbackNonGuesses();
        void clearPuzzle();
        void printHistory(std::vector<LogItem*>* v);
        bool removePossibilitiesInOneFromTwo(int position1, int position2, int round);

};

void shuffleArray(int* array, int size);

#endif

