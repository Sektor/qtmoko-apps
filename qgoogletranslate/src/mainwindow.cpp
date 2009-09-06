/* This file is part of QGoogleTranslate
 *
 * Copyright (C) 2009 Durachenko Alexei V. <lexnewton86@gmail.com>
 */

#include "mainwindow.h"
#include "ceditorwidget.h"
#include "cconfigdialog.h"
#include "config.h"
#include <QMenu>
#include <QSoftMenuBar>

CMainWindow::CMainWindow( QWidget * parent, Qt::WFlags f) : QMainWindow(parent, f)
{
    // init
    setupUi(this);
    tabWidget->clear();
    loadSettings();

    // create one empty tab
    addNewTab();

    QMenu* menu = QSoftMenuBar::menuFor(this);
    menu->addAction(tr("About"), this, SLOT( aboutQGoogleTranslate() ));
    menu->addAction(tr("Preferences"), this, SLOT( showPreferences() ));

    connect(btnSwap, SIGNAL(clicked()), this, SLOT(swapLangs()));
    connect(btnAdd, SIGNAL(clicked()), this, SLOT(addNewTab()));
    connect(btnClose, SIGNAL(clicked()), this, SLOT(closeTab()));
    connect(tabWidget, SIGNAL(currentChanged(int)), this, SLOT(updateTranslateButtonState()));
}

CMainWindow::~CMainWindow() {
    //
}

void CMainWindow::saveSettings()
{
    QSettings settings( QSettings::IniFormat, QSettings::UserScope, gProjectFamily, gProjectName );

    settings.setValue( "MainWindow/state", saveState() );
    settings.setValue( "MainWindow/geometry", saveGeometry() );
    settings.setValue( "DynamicDefaultLangs", m_DynamicDefaultLangs );
    settings.setValue( "DefaultSourceLanguageIndex", m_DefaultSourceLanguageIndex );
    settings.setValue( "DefaultDestinationLanguageIndex", m_DefaultDestinationLanguageIndex );
}


void CMainWindow::loadSettings()
{
    QSettings settings(QSettings::IniFormat,QSettings::UserScope,gProjectFamily,gProjectName);

    restoreState( settings.value("MainWindow/state",saveState()).toByteArray () );
    restoreGeometry( settings.value("MainWindow/geometry",saveGeometry()).toByteArray() );
    m_DynamicDefaultLangs = settings.value("DynamicDefaultLangs", 1 ).toInt();
    m_DefaultSourceLanguageIndex = settings.value("DefaultSourceLanguageIndex", 0 ).toInt();
    m_DefaultDestinationLanguageIndex = settings.value("DefaultDestinationLanguageIndex", 1 ).toInt();
}


void CMainWindow::updateToolButtonState()
{
    if(tabWidget->count() > 1)
        btnClose->setEnabled(true);
    else btnClose->setEnabled(false);
}


void CMainWindow::showHideAction() {
    setVisible(!isVisible());
}


void CMainWindow::addNewTab()
{
    CEditorWidget* curWidget = new CEditorWidget( this );
    tabWidget->addTab(curWidget, "...");
    tabWidget->setCurrentWidget( curWidget );
    curWidget->setTabWidget( tabWidget );
    curWidget->setTranslateButton( btnTranslate );
    curWidget->setSourceLanguageIndex( m_DefaultSourceLanguageIndex );
    curWidget->setDestinationLanguageIndex( m_DefaultDestinationLanguageIndex );
    updateToolButtonState();

    connect(curWidget, SIGNAL(signal_src_changed(int)), SLOT(slot_src_new_index(int)));
    connect(curWidget, SIGNAL(signal_dst_changed(int)), SLOT(slot_dst_new_index(int)));
}


void CMainWindow::closeTab()
{
	if( tabWidget->count() > 1 && tabWidget->currentIndex() != -1 )
	{
	    tabWidget->removeTab( tabWidget->currentIndex() );
	    updateToolButtonState();
	}
}

void CMainWindow::showPreferences()
{
        CConfigDialog dialog(this);

        dialog.setDefaultSourceLanguageIndex(m_DefaultSourceLanguageIndex);
        dialog.setDefaultDestinationLanguageIndex(m_DefaultDestinationLanguageIndex);
        dialog.setDynamicDefaultLangs(m_DynamicDefaultLangs);

        if(dialog.exec() == QDialog::Accepted)
	{
            m_DynamicDefaultLangs = dialog.dynamicDefaultLangs();
            if(!m_DynamicDefaultLangs) {
                m_DefaultSourceLanguageIndex = dialog.defaultSourceLanguageIndex();
                m_DefaultDestinationLanguageIndex = dialog.defaultDestinationLanguageIndex();
            }
            else {
                CEditorWidget *qw = static_cast<CEditorWidget*>(tabWidget->currentWidget());
                m_DefaultSourceLanguageIndex = qw->comboBox_LangSrc->currentIndex();
                m_DefaultDestinationLanguageIndex = qw->comboBox_LangDest->currentIndex();
            }
        }
}


void CMainWindow::aboutQGoogleTranslate()
{
	QMessageBox::about( this, tr("About"),
        G_FULL_PROGRAM_NAME + "\n\n" +
        tr("Author: Durachenko Alexei V. <lexnewton86 @gmail.com>") );
}

void CMainWindow::closeEvent( QCloseEvent* event ) {
    saveSettings();
}

void CMainWindow::swapLangs() {
    CEditorWidget *qw = static_cast<CEditorWidget*>(tabWidget->currentWidget());
    qw->on_toolButton_SwapLang_clicked();

    if(m_DynamicDefaultLangs) {
        int i = m_DefaultSourceLanguageIndex;
        m_DefaultSourceLanguageIndex = m_DefaultDestinationLanguageIndex;
        m_DefaultDestinationLanguageIndex = i;
    }
}

void CMainWindow::slot_src_new_index(int index) {
    if(m_DynamicDefaultLangs)
        m_DefaultSourceLanguageIndex = index;
}

void CMainWindow::slot_dst_new_index(int index) {
    if(m_DynamicDefaultLangs)
        m_DefaultDestinationLanguageIndex = index;
}

void CMainWindow::updateTranslateButtonState() {
    CEditorWidget *qw = static_cast<CEditorWidget*>(tabWidget->currentWidget());
    btnTranslate->setEnabled(qw->isTranslateAvail());
}

void CMainWindow::on_btnTranslate_clicked() {
    CEditorWidget *qw = static_cast<CEditorWidget*>(tabWidget->currentWidget());
    qw->translateIt();
}
