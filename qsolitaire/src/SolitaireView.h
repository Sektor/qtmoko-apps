#ifndef SOLITAIREVIEW_H
#define SOLITAIREVIEW_H

// INCLUDES
#include <QGraphicsView>
#include <QMessageBox>

// FORWARD DECLARATIONS
class QGraphicsScene;
class QPaintEvent;

// CLASS DECLARATION
class SolitaireView : public QGraphicsView
    {
    Q_OBJECT
    
    public:
        SolitaireView(QGraphicsScene* scene, QWidget *parent = 0);
        ~SolitaireView();

    #ifdef Q_OS_SYMBIAN
        void mousePressEvent(QMouseEvent *event);
        void resizeEvent(QResizeEvent *event);
    private:
        void paintEvent(QPaintEvent *event);
    #endif
    
    private:
        QRect exitRect;
        QMessageBox*    messageBox;
    };

#endif // SOLITAIREVIEW_H
