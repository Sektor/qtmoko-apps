/*
 * Copyright (c) 2009 Nokia Corporation.
 */

#ifndef WASTE_H
#define WASTE_H

// INCLUDES
#include <QGraphicsSvgItem>

// FORWARD DECLARATIONS
class QGraphicsItem;
class QGraphicsScene;
class BaseCardDeck;

// CLASS DECLARATION
class Waste: public QGraphicsSvgItem
    {
    Q_OBJECT
    
    public:
        enum { DeckType = UserType + 5 };
        
    public: // Constructor
        Waste(BaseCardDeck* deck=0, QGraphicsItem *parentItem=0);
        ~Waste();
    
    public:
        int type() const;
        QPainterPath shape() const;
        QRectF boundingRect() const;    
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
        BaseCardDeck* deck(){return this->deckData;};
        
    private: // Data
        BaseCardDeck*   deckData;
    };

#endif // WASTE_H

