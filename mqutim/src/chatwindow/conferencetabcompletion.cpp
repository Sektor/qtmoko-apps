/*
* Copyright (C) 2001-2008 Justin Karneges, Martin Hostettler
*
* This program is free software; you can redistribute it and/or
* modify it under the terms of the GNU General Public License
* as published by the Free Software Foundation; either version 2
* of the License, or (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <http://www.gnu.org/licenses/>.
*
*/

// Generic tab completion support code.

#include "conferencetabcompletion.h"
#include "separateconference.h"

#include <QObject>

TabCompletion::TabCompletion(QObject *parent)
    : QObject(parent)
{
  typingStatus_ = Typing_Normal;
  textEdit_ = 0;
  nickSep = ":";
}

TabCompletion::~TabCompletion()
{
}

void TabCompletion::setContactList(ConferenceContactList *contact_list)
{
  contact_list_ = contact_list;
}

void TabCompletion::setLastReferrer(QString last_referrer)
{
  last_referrer_ = last_referrer;
}

void TabCompletion::setTextEdit(QTextEdit* conferenceTextEdit)
{
  textEdit_ = conferenceTextEdit;

  QColor editBackground(textEdit_->palette().color(QPalette::Active, QPalette::Base));

  if (editBackground.value() < 128)
  {
    highlight_ = editBackground.lighter(125);
  }
  else
  {
    highlight_ = editBackground.darker(125);
  }
}

QTextEdit* TabCompletion::getTextEdit()
{
  return textEdit_;
}

void TabCompletion::highlight(bool set)
{
  Q_UNUSED(set);
  /*
  	if (set) {
  		QTextEdit::ExtraSelection es;
  		es.cursor = replacementCursor_;
  		es.format.setBackground(highlight_);
  		textEdit_->setExtraSelections(QList<QTextEdit::ExtraSelection>() << es);
  	} else {
  		if (textEdit_) textEdit_->setExtraSelections(QList<QTextEdit::ExtraSelection>());
  	}*/
}

void TabCompletion::moveCursorToOffset(QTextCursor &cur, int offset, QTextCursor::MoveMode mode)
{
  cur.movePosition(QTextCursor::Start, mode);
  for (int i = 0; i < offset; i++)   // some sane limit on iterations
  {
    if (cur.position() >= offset) break; // done our work
    if (!cur.movePosition(QTextCursor::NextCharacter, mode)) break; // failed?
  }
}

/** Find longest common (case insensitive) prefix of \a list.
	*/
QString TabCompletion::longestCommonPrefix(QStringList list)
{
  QString candidate = list.first().toLower();
  int len = candidate.length();
  while (len > 0)
  {
    bool found = true;
    foreach(const QString &str, list)
    {
      if (str.left(len).toLower() != candidate)
      {
        found = false;
        break;
      }
    }

    if (found)
    {
      break;
    }

    --len;
    candidate = candidate.left(len);
  }
  return candidate;
}

void TabCompletion::setup(QString text, int pos, int &start, int &end)
{
  if (text.isEmpty() || pos==0)
  {
    atStart_ = true;
    toComplete_ = "";
    start = 0;
    end = 0;
    return;
  }
  end = pos;
  int i;
  for (i = pos - 1; i > 0; --i)
  {
    if (text[i].isSpace())
    {
      break;
    }
  }
  if (!text[i].isSpace())
  {
    atStart_ = true;
    start = 0;
  }
  else
  {
    atStart_ = false;
    start = i+1;
  }
  toComplete_ = text.mid(start, end-start);
}

QString TabCompletion::suggestCompletion(bool *replaced)
{

  suggestedCompletion_ = possibleCompletions();
  suggestedIndex_ = -1;

  QString newText;
  if (suggestedCompletion_.count() == 1)
  {
    *replaced = true;
    newText = suggestedCompletion_.first();
  }
  else if (suggestedCompletion_.count() > 1)
  {
    newText = longestCommonPrefix(suggestedCompletion_);
    if (newText.isEmpty())
    {
      return toComplete_; // FIXME is this right?
    }

    typingStatus_ = Typing_MultipleSuggestions;
    // TODO: display a tooltip that will contain all suggestedCompletion
    *replaced = true;
  }


  return newText;
}



void TabCompletion::reset()
{
  typingStatus_ = Typing_Normal;
  highlight(false);
}

/** Handle tab completion.
	* User interface uses a dual model, first tab completes upto the
	* longest common (case insensitiv) match, further tabbing cycles through all
	* possible completions. When doing a tab completion without something to complete
	* possibly offers a special guess first.
	*/
void TabCompletion::tryComplete()
{
  switch (typingStatus_)
  {
  case Typing_Normal:
    typingStatus_ = Typing_TabPressed;
    break;
  case Typing_TabPressed:
    typingStatus_ = Typing_TabbingCompletions;
    break;
  default:
    break;
  }


  QString newText;
  bool replaced = false;

  if (typingStatus_ == Typing_MultipleSuggestions)
  {
    if (!suggestedCompletion_.isEmpty())
    {
      suggestedIndex_++;
      if (suggestedIndex_ >= (int)suggestedCompletion_.count())
      {
        suggestedIndex_ = 0;
      }
      newText = suggestedCompletion_[suggestedIndex_];
      replaced = true;
    }
  }
  else
  {
    QTextCursor cursor = textEdit_->textCursor();
    QString wholeText = textEdit_->toPlainText();

    int begin, end;
    setup(wholeText, cursor.position(), begin, end);
    replacementCursor_ = QTextCursor(textEdit_->document());
    moveCursorToOffset(replacementCursor_, begin);
    moveCursorToOffset(replacementCursor_, end, QTextCursor::KeepAnchor);

    if (toComplete_.isEmpty() && typingStatus_ == Typing_TabbingCompletions)
    {
      typingStatus_ = Typing_MultipleSuggestions;

      QString guess;
      suggestedCompletion_ = allChoices(guess);

      if ( !guess.isEmpty() )
      {
        suggestedIndex_ = -1;
        newText = guess;
        replaced = true;
      }
      else if (!suggestedCompletion_.isEmpty())
      {
        suggestedIndex_ = 0;
        newText = suggestedCompletion_.first();
        replaced = true;
      }
    }
    else
    {
      newText = suggestCompletion(&replaced);
    }
  }

  if (replaced)
  {
    textEdit_->setUpdatesEnabled(false);

    int start = qMin(replacementCursor_.anchor(), replacementCursor_.position());

    replacementCursor_.beginEditBlock();
    replacementCursor_.insertText(newText);
    replacementCursor_.endEditBlock();

    QTextCursor newPos(replacementCursor_);

    moveCursorToOffset(replacementCursor_, start, QTextCursor::KeepAnchor);


    newPos.clearSelection();

    textEdit_->setTextCursor(newPos);

    textEdit_->setUpdatesEnabled(true);
    textEdit_->viewport()->update();
  }
  highlight(typingStatus_ == Typing_MultipleSuggestions);
}


QStringList TabCompletion::possibleCompletions()
{
  QStringList suggestedNicks;
  QStringList nicks = getUsers();

  QString postAdd = atStart_ ? nickSep + " " : "";

  foreach(const QString &nick, nicks)
  {
    if (nick.left(toComplete_.length()).toLower() == toComplete_.toLower())
    {
      suggestedNicks << nick + postAdd;
    }
  }
  return suggestedNicks;
}

QStringList TabCompletion::allChoices(QString &guess)
{
  guess = last_referrer_;
  if (!guess.isEmpty() && atStart_)
  {
    guess += nickSep + " ";
  }

  QStringList all = getUsers();

  if (atStart_)
  {
    QStringList::Iterator it = all.begin();
    for ( ; it != all.end(); ++it)
    {
      *it = *it + nickSep + " ";
    }
  }
  return all;
}
QStringList TabCompletion::getUsers()
{
  return contact_list_->getUsers();
}


