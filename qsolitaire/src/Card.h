/*
 * Copyright (c) 2009 Nokia Corporation.
 */

#ifndef CARD_H
#define CARD_H

// INCLUDES
#include <QGraphicsSvgItem>

// FORWARD DECLARATIONS
class QGraphicsItem;
class QGraphicsScene;
class BaseCardDeck;

// CLASS DECLARATION
class Card: public QGraphicsSvgItem
    {
    Q_OBJECT
    
    public:
        enum { CardType = UserType + 1 };
    
        // Card suite enum
        enum CardSuite
            {
            Club = 1,
            Diamond,
            Heart,
            Spade
            };
    
        // Card color enum
        enum CardColor
            {
            Red = 1,
            Black
            };
        
        
    public: // Constructor
        Card(const QString &fileName, int value, CardSuite suite, CardColor color, 
             BaseCardDeck* deck=0, QGraphicsItem *parentItem=0);
        ~Card();
    
    public:
        int type() const;
        
        void setPos(const QPointF &pos);
        void setZValue(qreal z);
        
        void mousePressEvent(QGraphicsSceneMouseEvent *event);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
        void cancelCardMove();
        
        QPainterPath shape() const;
        QRectF boundingRect() const;    
        
        void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0);
        QString svgPath(){return this->cardSvgPath;};
        CardSuite suite(){return this->cardSuite;};
        CardColor color(){return this->cardColor;};
        int value(){return this->cardValue;};
        BaseCardDeck* deck(){return this->cardDeck;};
        void setDeck(BaseCardDeck* deck);
    
        void setParentCard(Card* parent){this->parentcard = parent;};
        Card* parentCard(){return this->parentcard;};
    
        void setChildCard(Card* child){this->childcard = child;};
        Card* childCard(){return this->childcard;};
        void childPosChanged(QPointF parentPos);
    
        void setCardVisibility(bool visible);
        bool isCardFaceVisible(){return this->cardFaceVisible;};
        void setCarToTop();
        void storeDefaultPos();
        
    private:
        void zOrderUpdate(qreal topZ);
        void cancelZorderUpdate();

        
    private: // Data
        QPointF         pointerPos;
        QPointF         defaultPos;
        
        CardSuite       cardSuite;
        int             cardValue;
        CardColor       cardColor;
    
        BaseCardDeck*   cardDeck;
        qreal           prevZ;
        
        QString         cardSvgPath;
        Card*           parentcard; // Card on top of this car in the deck
        Card*           childcard;  // Card under this in the deck
        bool            cardFaceVisible;
    };

#endif // CARD_H

