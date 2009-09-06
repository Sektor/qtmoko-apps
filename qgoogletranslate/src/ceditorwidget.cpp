/* This file is part of QGoogleTranslate
 *
 * Copyright (C) 2009 Durachenko Alexei V. <lexnewton86@gmail.com>
 */

#include "ceditorwidget.h"
#include "config.h"
#include "qjson/json_driver.h"

void simpleResponceParcer( QString& text );

CEditorWidget::CEditorWidget( QWidget * parent, Qt::WFlags f) : QWidget(parent, f)
{
    setupUi(this);
    for( int i = 0; i < gGoogleLangCount; ++i )
    {
        comboBox_LangSrc->addItem( gGoogleLang[i].name );
        comboBox_LangDest->addItem( gGoogleLang[i].name );
    }
    m_Buffer = 0;
    m_Http = new QHttp( this );
    connect( m_Http, SIGNAL( done( bool ) ), SLOT( slot_http_done( bool ) ) );
    connect( plainTextEdit_Input, SIGNAL( textChanged(QString) ), SLOT( slot_plainTextEdit_Input_textChanged(QString) ) );

    connect(comboBox_LangSrc, SIGNAL( activated(int) ), SIGNAL( signal_src_changed(int) ));
    connect(comboBox_LangDest, SIGNAL( activated(int) ), SIGNAL( signal_dst_changed(int) ));
}


CEditorWidget::~CEditorWidget() {
    if( m_Buffer )
        delete m_Buffer;
}

void CEditorWidget::setTabWidget( QTabWidget* tabWidget ) {
    m_TabWidget = tabWidget;
}

void CEditorWidget::setTranslateButton( QPushButton* btn ) {
    m_TranButton = btn;
}

void CEditorWidget::setSourceLanguageIndex( int index )
{
    if( index < 0 || index > gGoogleLangCount ) index = 0;
    comboBox_LangSrc->setCurrentIndex( index );
}

void CEditorWidget::setDestinationLanguageIndex( int index )
{
    if( index < 0 || index > gGoogleLangCount ) index = 0;
    comboBox_LangDest->setCurrentIndex( index );
}

void CEditorWidget::slot_plainTextEdit_Input_textChanged(QString str)
{
    QString text = str;
    bool enable = !text.isEmpty();
    m_TranButton->setEnabled(enable);
    m_TabWidget->setTabText(m_TabWidget->currentIndex(), enable ? text.left(5) : "...");
}

bool CEditorWidget::isTranslateAvail() {
    //true - в строке ввода есть текст, виджет доступен
    return !plainTextEdit_Input->text().isEmpty() && isEnabled();
}

void CEditorWidget::setBlocking( bool state )
{
    state = ! state;
    setEnabled(state);
    m_TranButton->setEnabled(state);
}

void CEditorWidget::slot_http_done( bool error )
{
    setBlocking( false );
    if( error == false ) {
        QString text = QString::fromUtf8( m_Http->readAll() );
/*        plainTextEdit_Output->clear();*/
        simpleResponceParcer( text );
/*        plainTextEdit_Output->insertPlainText( text );*/
        plainTextEdit_Output->setText(text);
    } else {
        plainTextEdit_Output->clear();
        plainTextEdit_Output->insertPlainText( tr("HTTP ERROR: ") );
        plainTextEdit_Output->insertPlainText( m_Http->errorString() );
    }
}


void CEditorWidget::translateIt()
{
    m_Http->abort();
    QString text = QString::fromUtf8(QUrl::toPercentEncoding( plainTextEdit_Input->text() ));
    QString url = QString("/translate_a/t?client=t&sl="
                       +  QString( gGoogleLang[comboBox_LangSrc->currentIndex()].code )
                       + "&tl="
                       + QString( gGoogleLang[comboBox_LangDest->currentIndex()].code ) );

    QHttpRequestHeader header = QHttpRequestHeader("POST", url, 1, 1);
    header.setValue("Host", "www.google.com");
    header.setValue("User-Agent", "Mozilla/5.0");
    header.setValue("Accept-Encoding", "deflate");
    header.setContentLength( text.length() );
    header.setValue("Connection", "Close");

    QByteArray ba("text=");
    ba.append( text );

    m_Http->setHost("www.google.com");
    m_Http->request(header,ba);

    setBlocking( true );
}


void CEditorWidget::on_toolButton_SwapLang_clicked()
{
	int srcLangIndex = comboBox_LangSrc->currentIndex();
	int destLangIndex = comboBox_LangDest->currentIndex();
	comboBox_LangSrc->setCurrentIndex( destLangIndex );
	comboBox_LangDest->setCurrentIndex( srcLangIndex );
}

void simpleResponceParcer( QString& text )
{
    text = text.replace(QString("\\\""),QString("\""));
    text = text.replace(QString("\\n"),QString("\n"));
    text = text.replace(QString("\n "),QString("\n"));
    text = text.replace(QString("\\x3c"),QString("<"));
    text = text.replace(QString("\\x3e"),QString(">"));

    if( text.startsWith( QString("\"") ) ) {
        //qDebug("This is a text.");
        text = text.remove( text.length()-1, 1).remove(0,1);
    } else if( text.startsWith( QString("[") ) && text.endsWith( QString("]") ) ) {
        //qDebug("This is a word.");
        QStringList tra;
        //tra = text.split(QRegExp(QString("\"(.*)\"")));
        text = text.replace(QString("]"),QString(""));
        tra = text.split(QString("["));
        text = QString("");
        for(int i=0,j=0;i<tra.count();i++)
        {
            if(tra.at(i)!="")
            {
                if(j==0)
                {
                    QString translation = tra.at(i);
                    translation = translation.replace("\"","");
                    translation = translation.replace(",","");
                    text.append( translation );
                    text.append( "\n\n") ;
                } else {
                    QString translation = tra.at(i);
                    QStringList translations = translation.split(",");
                    for(int y=0;y<translations.count();y++)
                    {
                        translation = translations.at(y);
                        translation = translation.replace("\"","");
                        if(y==0)
                        {
                            text.append( QString( translation + ": ") );
                        } else {
                            text.append( QString( "\t" + translation + "\n" ) );
                        }
                    }
                    text.append( "\n" );
                }
                j++;
            }
        }
    }
}
