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
 *                                                                         *
 *   09/2007 Olivier Guérin olivier.guerin@hotmail.fr                      *
 *   Removed dependency with the MainWindow class by adding ActionCode.    *
 ***************************************************************************/

#ifndef GAMEDIALOG_H
#define GAMEDIALOG_H

#include <QtGui>
#include "ui_gamedialog.h"


/*!
 * \brief Dialog to start or continue game.
 * \code
 * GameDialog dlg(this, m_sudoku->isHintShown(), m_sudoku->isStarted());
 * if (dlg.exec() == QDialog::Accepted) {
 *     if (dlg.actionCode() == GameDialog::ContinueGame) {
 *         ...
 *     }
 * }
 * \endcode
 */
class GameDialog : public QDialog, private Ui::GameDialog
{
    Q_OBJECT

public:
    GameDialog( QWidget* parent, bool showHint, bool showContinue );
    ~GameDialog();

    enum ActionCode {
        ContinueGame,
        StartBeginner,
        StartIntermediate,
        StartExpert
    };

    bool isHintShown() const;

    ActionCode actionCode() const;

protected slots:
    void setActionCode( int code );

private:
    ActionCode m_actionCode;
};

#endif // GAMEDIALOG_H
