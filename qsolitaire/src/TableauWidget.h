/*
 * Copyright (c) 2009 Nokia Corporation.
 */

#ifndef TABLEAUWIDGET_H
#define TABLEAUWIDGET_H

// INCLUDES
#include <QWidget>
#include <QMainWindow>


// FORWARD DECLARATIONS
class SolitaireView;
class SolitaireScene;
class GameLogic;

// CLASS DECLARATION
class TableauWidget: public QMainWindow
    {
    Q_OBJECT
    
    public: // Constructor
        TableauWidget(QWidget *parent = 0, Qt::WFlags f = 0);
        ~TableauWidget();
    
    private:
        void resizeEvent (QResizeEvent* event);     
        QSize sizeHint() const;
        void createMenus();
        
    private: // Data
        QSize           widgetSize;
        SolitaireView   *graphicsView;
        SolitaireScene  *graphicsScene;
        GameLogic       *gameLogic;

        QAction         *exitAction; 
        QAction         *closeAction; 
        QMenu           *optionsMenu;
    };

#endif // TABLEAUWIDGET_H

