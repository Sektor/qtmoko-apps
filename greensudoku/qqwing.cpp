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

#include "qqwing.h"
#include "sudokuboard.h"
#include "logitem.h"

#include <stdio.h>
#include <string.h>
#include <iostream>
#include <string>
#include <vector>
#include <stdlib.h>
#if HAVE_GETTIMEOFDAY == 1
    #include <sys/time.h>
#else
    #include <time.h>
#endif

using namespace std;

std::string IntToString(int num);
long getMicroseconds();
bool readPuzzleFromStdIn(int* puzzle);
int main(int argc, char *argv[]);
void printHelp(char* programName);
void printVersion();
void printAbout();

/**
 * Main method -- the entry point into the program.
 * Run with --help as an argument for usage and documentation
 */
int mainQqwing(int argc, char *argv[]){
//    try {
        // Start time for the application for timing
        long applicationStartTime = getMicroseconds();

        // The number of puzzles solved or generated.
        int puzzleCount = 0;

        enum Action {NONE, GENERATE, SOLVE};

        // defaults for options
        bool printPuzzle = false;
        bool printSolution = false;
        bool printHistory = false;
        bool printInstructions = false;
        bool timer = false;
        bool countSolutions = false;
        Action action = NONE;
        bool logHistory = false;
        SudokuBoard::PrintStyle printStyle = SudokuBoard::READABLE;
        int numberToGenerate = 1;
        bool printStats = false;
        SudokuBoard::Difficulty difficulty = SudokuBoard::UNKNOWN;

        // Read the arguments and set the options
        {for (int i=1; i<argc; i++){
            if (!strcmp(argv[i],"--puzzle")){
                printPuzzle = true;
            } else if (!strcmp(argv[i],"--nopuzzle")){
                printPuzzle = false;
            } else if (!strcmp(argv[i],"--solution")){
                printSolution = true;
            } else if (!strcmp(argv[i],"--nosolution")){
                printSolution = false;
            } else if (!strcmp(argv[i],"--history")){
                printHistory = true;
            } else if (!strcmp(argv[i],"--nohistory")){
                printHistory = false;
            } else if (!strcmp(argv[i],"--instructions")){
                printInstructions = true;
            } else if (!strcmp(argv[i],"--noinstructions")){
                printInstructions = false;
            } else if (!strcmp(argv[i],"--stats")){
                printStats = true;
            } else if (!strcmp(argv[i],"--nostats")){
                printStats = false;
            #if HAVE_GETTIMEOFDAY == 1
                } else if (!strcmp(argv[i],"--timer")){
                    timer = true;
                } else if (!strcmp(argv[i],"--notimer")){
                    timer = false;
            #endif
            } else if (!strcmp(argv[i],"--count-solutions")){
                countSolutions = true;
            } else if (!strcmp(argv[i],"--nocount-solutions")){
                countSolutions = false;
            } else if (!strcmp(argv[i],"--generate")){
                action = GENERATE;
                printPuzzle = true;
                if (i+1 < argc && argv[i+1][0] >= '1' && argv[i+1][0] <= '9'){
                    numberToGenerate = atoi(argv[i+1]);
                    i++;
                }
            } else if (!strcmp(argv[i],"--difficulty")){
                if (argc < i+1){
                    cout << "Please specify a difficulty." << endl;
                    return 1;
                } else if (!strcmp(argv[i+1],"simple")){
                    difficulty = SudokuBoard::SIMPLE;
                } else if (!strcmp(argv[i+1],"easy")){
                    difficulty = SudokuBoard::EASY;
                } else if (!strcmp(argv[i+1],"intermediate")){
                    difficulty = SudokuBoard::INTERMEDIATE;
                } else if (!strcmp(argv[i+1],"expert")){
                    difficulty = SudokuBoard::EXPERT;
                } else {
                    cout << "Difficulty expected to be simple, easy, intermediate, or expert, not " << argv[i+1] << endl;
                    return 1;
                }
                i++;
            } else if (!strcmp(argv[i],"--solve")){
                action = SOLVE;
                printSolution = true;
            } else if (!strcmp(argv[i],"--log-history")){
                logHistory = true;
            } else if (!strcmp(argv[i],"--nolog-history")){
                logHistory = false;
            } else if (!strcmp(argv[i],"--one-line")){
                printStyle=SudokuBoard::ONE_LINE;
            } else if (!strcmp(argv[i],"--compact")){
                printStyle=SudokuBoard::COMPACT;
            } else if (!strcmp(argv[i],"--readable")){
                printStyle=SudokuBoard::READABLE;
            } else if (!strcmp(argv[i],"--csv")){
                printStyle=SudokuBoard::CSV;
            } else if (!strcmp(argv[i],"-n") || !strcmp(argv[i],"--number")){
                if (i+1 < argc){
                    numberToGenerate = atoi(argv[i+1]);
                    i++;
                } else {
                    cout << "Please specify a number." << endl;
                    return 1;
                }
            } else if (!strcmp(argv[i],"-h") || !strcmp(argv[i],"--help") || !strcmp(argv[i],"help") || !strcmp(argv[i],"?")){
                printHelp(argv[0]);
                return 0;
            } else if (!strcmp(argv[i],"--version")){
                printVersion();
                return 0;
            } else if (!strcmp(argv[i],"--about")){
                printAbout();
                return 0;
            } else {
                cout << "Unknown argument: '" << argv[i] << "'" << endl;
                printHelp(argv[0]);
                return 1;
            }
        }}

        if (action == NONE){
            cout << "Either --solve or --generate must be specified." << endl;
            printHelp(argv[0]);
            return 1;
        }

        // Initialize the random number generator
        int timeSeed = time(NULL);
        srand(timeSeed);

        // If printing out CSV, print a header
        if (printStyle == SudokuBoard::CSV){
            if (printPuzzle) cout << "Puzzle,";
            if (printSolution) cout << "Solution,";
            if (printHistory) cout << "Solve History,";
            if (printInstructions) cout << "Solve Instructions,";
            if (countSolutions) cout << "Solution Count,";
            if (timer) cout << "Time (milliseconds),";
            if (printStats) cout << "Givens,Singles,Hidden Singles,Naked Pairs,Hidden Pairs,Pointing Pairs/Triples,Box/Line Intersections,Guesses,Backtracks,Difficulty";
            cout << "" << endl;
        }

        // Create a new puzzle board
        // and set the options
        SudokuBoard* ss = new SudokuBoard();
        ss->setRecordHistory(printHistory || printInstructions || printStats || difficulty!=SudokuBoard::UNKNOWN);
        ss->setLogHistory(logHistory);
        ss->setPrintStyle(printStyle);

        // Solve puzzle or generate puzzles
        // until end of input for solving, or
        // until we have generated the specified number.
        bool done = false;
        int numberGenerated = 0;
        while (!done){
            // record the start time for the timer.
            long puzzleStartTime = getMicroseconds();

            // iff something has been printed for this particular puzzle
            bool printedSomething = false;

            // Record whether the puzzle was possible or not,
            // so that we don't try to solve impossible givens.
            bool havePuzzle = false;
            if (action == GENERATE){
                // Generate a puzzle
                havePuzzle = ss->generatePuzzle();
                if (!havePuzzle && printPuzzle){
                    cout << "Could not generate puzzle.";
                    if (printStyle==SudokuBoard::CSV){
                        cout << ",";
                    } else {
                        cout << endl;
                    }
                    printedSomething = true;
                }
            } else {
                // Read the next puzzle on STDIN
                int* puzzle = new int[BOARD_SIZE];
                if (readPuzzleFromStdIn(puzzle)){
                    havePuzzle = ss->setPuzzle(puzzle);
                    if (!havePuzzle){
                        if (printPuzzle){
                            ss->printPuzzle();
                            printedSomething = true;
                        }
                        if (printSolution) {
                            cout << "Puzzle is not possible.";
                            if (printStyle==SudokuBoard::CSV){
                                cout << ",";
                            } else {
                                cout << endl;
                            }
                            printedSomething = true;
                        }
                    }
                } else {
                    // Set loop to terminate when nothing is left on STDIN
                    havePuzzle = false;
                    done = true;
                }
                delete puzzle;
            }

           int solutions = 0;

            if (havePuzzle){

                // Count the solutions if requested.
                // (Must be done before solving, as it would
                // mess up the stats.)
                if (countSolutions){
                    solutions = ss->countSolutions();
                }

                // Solve the puzzle
                if (printSolution || printHistory || printStats || printInstructions || difficulty!=SudokuBoard::UNKNOWN){
                    ss->solve();
                }

                // Bail out if it didn't meet the difficulty standards for generation
                if (action == GENERATE){
                    if (difficulty!=SudokuBoard::UNKNOWN && difficulty!=ss->getDifficulty()){
                        havePuzzle = false;
                    } else {
                        numberGenerated++;
                        // Set loop to terminate if enough have been generated.
                        if (numberGenerated >= numberToGenerate) done = true;
                    }
                }
            }

            if (havePuzzle){

                // With a puzzle now in hand and possibly solved
                // print out the solution, stats, etc.
                printedSomething = true;

                // Record the end time for the timer.
                long puzzleDoneTime = getMicroseconds();

                // Print the puzzle itself.
                if (printPuzzle) ss->printPuzzle();

                // Print the solution if there is one
                if (printSolution){
                    if (ss->isSolved()){
                        ss->printSolution();
                    } else {
                        cout << "Puzzle has no solution.";
                        if (printStyle==SudokuBoard::CSV){
                            cout << ",";
                        } else {
                            cout << endl;
                        }
                    }
                }

                // Print the steps taken to solve or attempt to solve the puzzle.
                if (printHistory) ss->printSolveHistory();
                // Print the instructions for solving the puzzle
                if (printInstructions) ss->printSolveInstructions();

                // Print the number of solutions to the puzzle.
                if (countSolutions){
                    if (printStyle == SudokuBoard::CSV){
                        cout << solutions << ",";
                    } else {
                        if (solutions == 0){
                            cout << "There are no solutions to the puzzle." << endl;
                        } else if (solutions == 1){
                            cout << "The solution to the puzzle is unique." << endl;
                        } else {
                            cout << "There are " << solutions << " solutions to the puzzle." << endl;
                        }
                    }
                }

                // Print out the time it took to solve the puzzle.
                if (timer){
                    double t = ((double)(puzzleDoneTime - puzzleStartTime))/1000.0;
                    if (printStyle == SudokuBoard::CSV){
                        cout << t << ",";
                    } else {
                        cout << "Time: " << t  << " milliseconds" << endl;
                    }
                }

                // Print any stats we were able to gather while solving the puzzle.
                if (printStats){
                    int givenCount = ss->getGivenCount();
                    int singleCount = ss->getSingleCount();
                    int hiddenSingleCount = ss->getHiddenSingleCount();
                    int nakedPairCount = ss->getNakedPairCount();
                    int hiddenPairCount = ss->getHiddenPairCount();
                    int pointingPairTripleCount = ss->getPointingPairTripleCount();
                    int boxReductionCount = ss->getBoxLineReductionCount();
                    int guessCount = ss->getGuessCount();
                    int backtrackCount = ss->getBacktrackCount();
                    char* difficultyString = ss->getDifficultyAsString();
                    if (printStyle == SudokuBoard::CSV){
                        cout << givenCount << ","  << singleCount << "," << hiddenSingleCount
                                << "," << nakedPairCount << "," << hiddenPairCount
                                << ","  << pointingPairTripleCount  << ","  << boxReductionCount
                                << "," << guessCount << "," << backtrackCount
                                << "," << difficultyString << ",";
                    } else {
                        cout << "Number of Givens: " << givenCount  << endl;
                        cout << "Number of Singles: " << singleCount << endl;
                        cout << "Number of Hidden Singles: " << hiddenSingleCount  << endl;
                        cout << "Number of Naked Pairs: " << nakedPairCount  << endl;
                        cout << "Number of Hidden Pairs: " << hiddenPairCount  << endl;
                        cout << "Number of Pointing Pairs/Triples: " << pointingPairTripleCount  << endl;
                        cout << "Number of Box/Line Intersections: " << boxReductionCount  << endl;
                        cout << "Number of Guesses: " << guessCount  << endl;
                        cout << "Number of Backtracks: " << backtrackCount  << endl;
                        cout << "Difficulty: " << difficultyString  << endl;
                    }
                }
                puzzleCount++;
            }
            if (printedSomething && printStyle == SudokuBoard::CSV){
                cout << endl;
            }
        }

        delete ss;

        long applicationDoneTime = getMicroseconds();
        // Print out the time it took to do everything
        if (timer){
            double t = ((double)(applicationDoneTime - applicationStartTime))/1000000.0;
            cout << puzzleCount << " puzzle" << ((puzzleCount==1)?"":"s") << " " << (action==GENERATE?"generated":"solved") << " in " << t << " seconds." << endl;
        }


//    } catch (char const* s){
//OGN        cout << s <<  endl;
//        cout << "Error" << endl;
//        return 1;
//    }

    return 0;
}

void printVersion(){
    cout << PACKAGE_STRING << endl;
}

void printAbout(){
    cout << PACKAGE_NAME << " - Sudoku solver and generator." << endl;
    cout << "Written by Stephen Ostermiller copyright 2006." << endl;
    cout << "http://ostermiller.org/qqwing/" << endl;
    cout << "" << endl;
    cout << "This program is free software; you can redistribute it and/or modify" << endl;
    cout << "it under the terms of the GNU General Public License as published by" << endl;
    cout << "the Free Software Foundation; either version 2 of the License, or" << endl;
    cout << "(at your option) any later version." << endl;
    cout << "" << endl;
    cout << "This program is distributed in the hope that it will be useful," << endl;
    cout << "but WITHOUT ANY WARRANTY; without even the implied warranty of" << endl;
    cout << "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the" << endl;
    cout << "GNU General Public License for more details." << endl;
    cout << "" << endl;
    cout << "You should have received a copy of the GNU General Public License" << endl;
    cout << "along with this program; if not, write to the Free Software" << endl;
    cout << "Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA" << endl;
}

void printHelp(char* programName){
    cout << programName << " <options>" << endl;
    cout << "Sudoku solver and generator." << endl;
    cout << "  --generate <num>     Generate new puzzles" << endl;
    cout << "  --solve              Solve all the puzzles from standard input" << endl;
    cout << "  --difficulty <diff>  Generate only simple,easy, intermediate, or expert" << endl;
    cout << "  --puzzle             Print the puzzle (default when generating)" << endl;
    cout << "  --nopuzzle           Do not print the puzzle (default when solving)" << endl;
    cout << "  --solution           Print the solution (default when solving)" << endl;
    cout << "  --nosolution         Do not print the solution (default when generating)" << endl;
    cout << "  --stats              Print statistics about moves used to solve the puzzle" << endl;
    cout << "  --nostats            Do not print statistics (default)" << endl;
    #if HAVE_GETTIMEOFDAY == 1
        cout << "  --timer              Print time to generate or solve each puzzle" << endl;
        cout << "  --notimer            Do not print solve or generation times (default)" << endl;
    #endif
    cout << "  --count-solutions    Count the number of solutions to puzzles" << endl;
    cout << "  --nocount-solutions  Do not count the number of solutions (default)" << endl;
    cout << "  --history            Print trial and error used when solving" << endl;
    cout << "  --nohistory          Do not print trial and error to solve (default)" << endl;
    cout << "  --instructions       Print the steps (at least 81) needed to solve the puzzle" << endl;
    cout << "  --noinstructions     Do not print steps to solve (default)" << endl;
    cout << "  --log-history        Print trial and error to solve as it happens" << endl;
    cout << "  --nolog-history      Do not print trial and error  to solve as it happens" << endl;
    cout << "  --one-line           Print puzzles on one line of 81 characters" << endl;
    cout << "  --compact            Print puzzles on 9 lines of 9 characters" << endl;
    cout << "  --readable           Print puzzles in human readable form (default)" << endl;
    cout << "  --csv                Ouput CSV format with one line puzzles" << endl;
    cout << "  --help               Print this message" << endl;
    cout << "  --about              Author and license information" << endl;
    cout << "  --version            Display current version number" << endl;
}

/**
 * Get the current time in microseconds.
 */
long getMicroseconds(){
    #if HAVE_GETTIMEOFDAY == 1
        struct timeval tv;
        gettimeofday(&tv, NULL);
        return tv.tv_sec*1000000+tv.tv_usec;
    #else
        return 0;
    #endif
}


/**
 * Read a sudoku puzzle from standard input.
 * STDIN is processed one character at a time
 * until the sudoku is filled in.  Any digit
 * or period is used to fill the sudoku, any
 * other character is ignored.
 */
bool readPuzzleFromStdIn(int* puzzle){
    int read = 0;
    while (read < BOARD_SIZE){
        char c = getchar();
        if (c == EOF) return false;
        if (c >= '1' && c <='9'){
            puzzle[read] = c-'0';
            read++;
        }
        if (c == '.' || c == '0'){
            puzzle[read] = 0;
            read++;
        }
    }
    return true;
}

