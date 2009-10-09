#include <QPaintEvent>
#include "SolitaireView.h"
#include <QApplication>


SolitaireView::SolitaireView(QGraphicsScene* scene, QWidget *parent)
: QGraphicsView(scene, parent)
    {
    messageBox = 0;
    }

SolitaireView::~SolitaireView()
    {
    }

#ifdef Q_OS_SYMBIAN
void SolitaireView::resizeEvent(QResizeEvent *event)
    {
    // call base class implementation
    QGraphicsView::resizeEvent(event);
    
    // draw a fixed overlay (exit button on bottom right corner)
    QFont f("Helvetica",8);
    QFontMetrics fm(f);
    exitRect.setRect(0,0,fm.width("Exit")+10,fm.height());
    exitRect.moveBottomRight(viewport()->geometry().bottomRight());
    exitRect.setBottom(exitRect.bottom()-10);
    }

void SolitaireView::mousePressEvent(QMouseEvent *event)
    {
    // call base class implementation
    QGraphicsView::mousePressEvent(event);
    
    if (exitRect.contains(event->pos()))
        {
        // Exit app
        
        if (!messageBox)
            {
            messageBox = new QMessageBox(0);
            if (QMessageBox::Ok == messageBox->question(this,"QSolitaire","Exit?",QMessageBox::Ok|QMessageBox::Cancel))
                {
                QApplication::instance()->exit();
                }
            delete messageBox;
            messageBox = 0;
            }
        }
    }

void SolitaireView::paintEvent(QPaintEvent *event)
    {
    // call base class implementation
    QGraphicsView::paintEvent(event);
    
    if(exitRect.intersects(event->rect()))
        {  
        QPainter painter(viewport());
        QFont f("Helvetica",8);
        painter.setFont(f);
        painter.setPen(Qt::white);
        painter.drawText(exitRect.bottomLeft(),"Exit");
        }
    }
#endif
