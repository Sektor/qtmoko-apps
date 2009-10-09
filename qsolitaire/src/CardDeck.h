/*
 * Copyright (c) 2009 Nokia Corporation.
 */

#ifndef CARDDECK_H
#define CARDDECK_H

// INCLUDES
#include <QObject>
#include <QList>

// FORWARD DECLARATIONS
class Card;
class QSvgRenderer;

// CLASS DECLARATION
class BaseCardDeck : public QObject
    {
    Q_OBJECT
    
    public:
        // Card deck type
        enum DeckType
            {
            CardDeck,
            Foundation,
            Stock,
            Waste
            };
        
    public:
        BaseCardDeck(BaseCardDeck::DeckType type, QObject *parent = 0);
        ~BaseCardDeck();
    
    public:
        void AddCard(Card* newCard);
        void RemoveCard(Card* card);
        QList<Card*> Cards();
        DeckType Type(){return deckType;};
    

    public: // Data
        QSvgRenderer*   svgRenderer;
    
    protected: // Data
        QList<Card*>    cards;
        DeckType        deckType;
    }; 
    
    
// CLASS DECLARATION
class CardDeck : public BaseCardDeck
    {
    Q_OBJECT
    
    public:
        CardDeck(BaseCardDeck::DeckType type, QObject *parent = 0);
        ~CardDeck();
    }; 

#endif //CARDDECK_H
