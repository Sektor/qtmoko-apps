/*
 * Copyright (c) 2009 Nokia Corporation.
 */

#ifndef DECK_H
#define DECK_H

// INCLUDES
#include <QGraphicsSvgItem>

// FORWARD DECLARATIONS
class QGraphicsItem;
class QGraphicsScene;
class BaseCardDeck;

// CLASS DECLARATION
class Deck: public QGraphicsSvgItem
    {
    Q_OBJECT
    
    public:
        enum { DeckType = UserType + 2 };
        
    public: // Constructor
        Deck(BaseCardDeck* deck=0, QGraphicsItem *parentItem=0);
        ~Deck();
    
    public:
        int type() const;
        QPainterPath shape() const;
        QRectF boundingRect() const;    
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
        BaseCardDeck* deck(){return this->deckData;};
        
    private: // Data
        BaseCardDeck*   deckData;
    };

#endif // DECK_H

