/*
 * Copyright (c) 2009 Nokia Corporation.
 */

#ifndef FOUNDATION_H
#define FOUNDATION_H

// INCLUDES
#include <QGraphicsSvgItem>

// FORWARD DECLARATIONS
class QGraphicsItem;
class QGraphicsScene;
class BaseCardDeck;

// CLASS DECLARATION
class Foundation: public QGraphicsSvgItem
    {
    Q_OBJECT
    
    public:
        enum { DeckType = UserType + 3 };
        
    public: // Constructor
        Foundation(BaseCardDeck* deck=0, QGraphicsItem *parentItem=0);
        ~Foundation();
    
    public:
        int type() const;
        QPainterPath shape() const;
        QRectF boundingRect() const;    
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
        BaseCardDeck* deck(){return this->deckData;};
        
    private: // Data
        BaseCardDeck*   deckData;
    };

#endif // FOUNDATION_H

