/*
 * Copyright (c) 2009 Nokia Corporation.
 */

// INCLUDE FILES
#include <QApplication>
#include <QPainter>
#include <QAction>
#include <QResizeEvent>
#include <QMenuBar>
#include <QDesktopWidget>

#include "TableauWidget.h"
#include "SolitaireView.h"
#include "SolitaireScene.h"
#include "GameLogic.h"


TableauWidget::TableauWidget(QWidget *parent, Qt::WFlags f)
    : QMainWindow(parent)
    {
    setWindowTitle("QSolitaire");
    //createMenus();
    
    setProperty("FingerScrollable", false);
    
    // Create gamelogic and mess cards
    gameLogic = new GameLogic(this);
    gameLogic->messCards();

    // Create Qt Graphics View Framework classes
    graphicsScene = new SolitaireScene(gameLogic);
    graphicsScene->setItemIndexMethod(QGraphicsScene::NoIndex);
    graphicsScene->setProperty("FingerScrollable", false);
    graphicsView = new SolitaireView(graphicsScene,this);
    graphicsView->setDragMode(QGraphicsView::NoDrag);
    graphicsView->setCacheMode(QGraphicsView::CacheBackground);
    graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    graphicsView->setProperty("FingerScrollable", false);
    setCentralWidget(graphicsView);

    // Set background color
    graphicsView->setBackgroundBrush(QBrush(QColor(0,128,0)));

    // Disable scrollbars
    graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    
    // Deal cards into decks
    graphicsScene->createDecks();
    }

TableauWidget::~TableauWidget()
    {
    delete gameLogic;
    delete graphicsScene;
    delete graphicsView;
    }

void TableauWidget::createMenus()
    {
    // Add item into menu
    #if defined(Q_OS_SYMBIAN)
    
    // into Symbian Options menu
    exitAction = new QAction(tr("&Exit"),this);
    menuBar()->addAction(exitAction);
    connect(exitAction, SIGNAL(triggered()),this, SLOT(close()));    
    
    #elif defined(Q_OS_LINUX)
    
    // into Maemo
    closeAction = new QAction(tr("C&lose"),this);
    menuBar()->addAction(closeAction);
    connect(closeAction, SIGNAL(triggered()),this, SLOT(close()));    
    
    #else
    
    // else
    optionsMenu = menuBar()->addMenu(tr("&File"));
    exitAction = new QAction(tr("&Exit"),this);
    optionsMenu->addAction(exitAction);
    connect(exitAction, SIGNAL(triggered()),this, SLOT(close()));    
    
    #endif
    }

QSize TableauWidget::sizeHint() const
    {
    // This property holds the recommended size for the widget
    return widgetSize;
    }


void TableauWidget::resizeEvent (QResizeEvent* event)
    {
    // This event handler can be reimplemented in a subclass to receive widget
    // resize events which are passed in the event parameter. 
    // When resizeEvent() is called, the widget already has its new geometry.
    
    widgetSize = event->size();

    
    // Scale Graphic View
    QMatrix matrix;
    qreal scaleValHeight = 0.0;
    qreal scaleValWidth = 0.0;
    
    // Calculate scale values for height and width
    scaleValHeight = (qreal)widgetSize.height() / (3.7 * CARD_HEIGHT);
    scaleValWidth = (qreal)widgetSize.width() / (8.0 * CARD_WIDTH + 8.0 * graphicsScene->deckCap());
    
    // Use smaller scale value for scaling
    if (scaleValHeight<scaleValWidth)
        matrix.scale(scaleValHeight,scaleValHeight);
    else
        matrix.scale(scaleValWidth,scaleValWidth);
    
    // Update graphics scene and view sizes
    graphicsScene->setSceneRect(graphicsView->rect());
    
    // Set scale to view
    graphicsView->setMatrix(matrix);
    
    QWidget::resizeEvent(event);
    }


