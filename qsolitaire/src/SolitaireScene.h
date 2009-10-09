/*
 * Copyright (c) 2009 Nokia Corporation.
 */

#ifndef SOLITAIRESCENE_H
#define SOLITAIRESCENE_H

// INCLUDES
#include <QGraphicsScene>

// FORWARD DECLARATIONS
class QGraphicsSceneMouseEvent;
class CardDeck;
class GameLogic;
class Deck;
class Foundation;
class Waste;
class Stock;

// CONSTS
const qreal CARD_WIDTH = 75.0;
const qreal CARD_HEIGHT = 110.0;
const qreal CARD_TOP_CAP = 20;

// CLASS DECLARATION
class SolitaireScene : public QGraphicsScene
    {
    Q_OBJECT
    
    public:
        SolitaireScene(GameLogic* gameLogic, QObject *parent = 0);
        ~SolitaireScene();
    
    private:
        void mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent);
        void mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent);
        void mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent);
    
        int handleCardMoves(QList<QGraphicsItem*>& items);
        void cleanItems(QList<QGraphicsItem*>& items);
        
    public slots:    
        void UpdatePositions(const QRectF& rect);
        
    public:
        void createDecks();
        qreal getItemsTopMostZOrder();
        qreal deckCap();
        
    private: // Data
    
        // Data classes
        CardDeck*           deck1;
        CardDeck*           deck2;
        CardDeck*           deck3;
        CardDeck*           deck4;
        CardDeck*           deck5;
        CardDeck*           deck6;
        CardDeck*           deck7;
        CardDeck*           foundation1;
        CardDeck*           foundation2;
        CardDeck*           foundation3;
        CardDeck*           foundation4;
        CardDeck*           stock;
        CardDeck*           waste;
        
        // Game engine
        GameLogic*          gameLogic;
    
        // Graphic item classes
        QGraphicsItem*      activeGraphicItem;
        Deck*               deck1Item;
        Deck*               deck2Item;
        Deck*               deck3Item;
        Deck*               deck4Item;
        Deck*               deck5Item;
        Deck*               deck6Item;
        Deck*               deck7Item;
        Foundation*         foundation1Item;
        Foundation*         foundation2Item;
        Foundation*         foundation3Item;
        Foundation*         foundation4Item;
        Stock*              stockItem;
        Waste*              wasteItem;
    };

#endif // SOLITAIRESCENE_H
