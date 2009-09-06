/* This file is part of QGoogleTranslate
 *
 * Copyright (C) 2009 Durachenko Alexei V. <lexnewton86@gmail.com>
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "ui_mainwindow.h"

class CMainWindow : public QMainWindow, public Ui::MainWindow
{
Q_OBJECT
public:
    CMainWindow( QWidget * parent = 0, Qt::WFlags f = 0 );
    ~CMainWindow();

private:
    void saveSettings();
    void loadSettings();

    void updateToolButtonState();

    int m_DynamicDefaultLangs;
    int m_DefaultSourceLanguageIndex;
    int m_DefaultDestinationLanguageIndex;

protected:
    void closeEvent( QCloseEvent* event );

private slots:
    void showHideAction();
    void showPreferences();
    void addNewTab();
    void closeTab();
    void aboutQGoogleTranslate();
    void swapLangs();
    void on_btnTranslate_clicked();

    void slot_src_new_index(int index);
    void slot_dst_new_index(int index);
    void updateTranslateButtonState();
};

#endif
