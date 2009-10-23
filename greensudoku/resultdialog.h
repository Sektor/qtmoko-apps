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

#ifndef RESULTDIALOG_H
#define RESULTDIALOG_H

#include <QtGui>
#include "ui_resultdialog.h"


/*!
 * \brief Dialog to show result
 * \code
 * ResultDialog dlg(this);
 * dlg.setResult(won, gameDuration);
 * if (dlg.exec() == QDialog::Accepted) {
 *     if (dlg.actionCode() == ResultDialog::NewGame) {
 *         ...
 *     }
 * }
 * \endcode
 */
class ResultDialog : public QDialog, private Ui::ResultDialog
{
    Q_OBJECT

public:
    enum ActionCode {
      NewGame,
      RestartGame
    };

    ResultDialog( QWidget * parent = 0 );
    ~ResultDialog();

    void setResult( bool win, QTime time );

    ActionCode actionCode() const; 

protected slots:
    void setActionCode(int code);

private:
    ActionCode m_actionCode;
};

#endif // RESULTDIALOG_H
