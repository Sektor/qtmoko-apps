/* This file is part of QGoogleTranslate
 *
 * Copyright (C) 2009 Durachenko Alexei V. <lexnewton86@gmail.com>
 */

#ifndef CEDITORWIDGET_H
#define CEDITORWIDGET_H

#include <QtGui>
#include <QtNetwork>
#include "ui_editorwidget.h"

class CEditorWidget : public QWidget, public Ui::EditorWidget
{
Q_OBJECT
public:
    CEditorWidget( QWidget * parent = 0, Qt::WFlags f = 0 );
    ~CEditorWidget();

    void setTabWidget( QTabWidget* tabWidget );
    void setTranslateButton( QPushButton* btn );
    void setSourceLanguageIndex( int index );
    void setDestinationLanguageIndex( int index );
    void on_toolButton_SwapLang_clicked();
    bool isTranslateAvail();
    void translateIt();

private:
    QHttp*      m_Http;
    QBuffer*    m_Buffer;
    QTabWidget* m_TabWidget;
    QPushButton* m_TranButton;
    void setBlocking( bool state );

private slots:
    void slot_http_done( bool );
    void slot_plainTextEdit_Input_textChanged(QString);

signals:
    void signal_src_changed(int);
    void signal_dst_changed(int);
};

#endif
