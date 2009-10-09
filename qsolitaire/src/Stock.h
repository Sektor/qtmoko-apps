/*
 * Copyright (c) 2009 Nokia Corporation.
 */

#ifndef STOCK_H
#define STOCK_H

// INCLUDES
#include <QGraphicsSvgItem>

// FORWARD DECLARATIONS
class QGraphicsItem;
class QGraphicsScene;
class BaseCardDeck;

// CLASS DECLARATION
class Stock: public QGraphicsSvgItem
    {
    Q_OBJECT
    
    public:
        enum { DeckType = UserType + 4 };
        
    public: // Constructor
        Stock(BaseCardDeck* deck=0, QGraphicsItem *parentItem=0);
        ~Stock();
    
    public:
        int type() const;
        QPainterPath shape() const;
        QRectF boundingRect() const;    
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
        BaseCardDeck* deck(){return this->deckData;};
        
    private: // Data
        BaseCardDeck*   deckData;
    };

#endif // STOCK_H

