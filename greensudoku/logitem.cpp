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

#include "logitem.h"
#include <iostream>
#include <vector>
using namespace std;

LogItem::LogItem(int r, LogType t){
    init(r,t,0,-1);
}

LogItem::LogItem(int r, LogType t, int v, int p){
    init(r,t,v,p);
}

void LogItem::init(int r, LogType t, int v, int p){
    round = r;
    type = t;
    value = v;
    position = p;
}

LogItem::~LogItem(){
}

int LogItem::getRound(){
    return round;
}

/**
 * Get the type of this log item.
 */
LogItem::LogType LogItem::getType(){
    return type;
}

/**
 * Print the current log item.  The message used is
 * determined by the type of log item.
 */
void LogItem::print(){
    cout << "Round: " << getRound() << " - ";
    switch(type){
        case GIVEN:{
            cout << "Mark given";
        } break;
        case ROLLBACK:{
            cout << "Roll back round";
        } break;
        case GUESS:{
            cout << "Mark guess (start round)";
        } break;
        case HIDDEN_SINGLE_ROW:{
            cout << "Mark single possibility for value in row";
        } break;
        case HIDDEN_SINGLE_COLUMN:{
            cout << "Mark single possibility for value in column";
        } break;
        case HIDDEN_SINGLE_SECTION:{
            cout << "Mark single possibility for value in section";
        } break;
        case SINGLE:{
            cout << "Mark only possibility for cell";
        } break;
        case NAKED_PAIR_ROW:{
            cout << "Remove possibilities for naked pair in row";
        } break;
        case NAKED_PAIR_COLUMN:{
            cout << "Remove possibilities for naked pair in column";
        } break;
        case NAKED_PAIR_SECTION:{
            cout << "Remove possibilities for naked pair in section";
        } break;
        case POINTING_PAIR_TRIPLE_ROW: {
            cout << "Remove possibilities for row because all values are in one section";
        } break;
        case POINTING_PAIR_TRIPLE_COLUMN: {
            cout << "Remove possibilities for column because all values are in one section";
        } break;
        case ROW_BOX: {
            cout << "Remove possibilities for section because all values are in one row";
        } break;
        case COLUMN_BOX: {
            cout << "Remove possibilities for section because all values are in one column";
        } break;
        case HIDDEN_PAIR_ROW: {
            cout << "Remove possibilities from hidden pair in row";
        } break;
        case HIDDEN_PAIR_COLUMN: {
            cout << "Remove possibilities from hidden pair in column";
        } break;
        case HIDDEN_PAIR_SECTION: {
            cout << "Remove possibilities from hidden pair in section";
        } break;
        default:{
            cout << "!!! Performed unknown optimization !!!";
        } break;
    }
    if (value > 0 || position > -1){
        cout << " (";
        bool printed = false;
        if (position > -1){
            if (printed) cout << " - ";
            cout << "Row: " << cellToRow(position)+1 << " - Column: " << cellToColumn(position)+1;
            printed = true;
        }
        if (value > 0){
            if (printed) cout << " - ";
            cout << "Value: " << value;
            printed = true;
        }
        cout  << ")";
    }

}

/**
 * Given a vector of LogItems, determine how many
 * log items in the vector are of the specified type.
 */
int getLogCount(vector<LogItem*>* v, LogItem::LogType type){
    int count = 0;
    {for (unsigned int i=0; i<v->size(); i++){
        if(v->at(i)->getType() == type) count++;
    }}
    return count;
}
