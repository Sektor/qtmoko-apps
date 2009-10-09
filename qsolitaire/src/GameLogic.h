/*
 * Copyright (c) 2009 Nokia Corporation.
 */

#ifndef GAMELOGIC_H
#define GAMELOGIC_H

// INCLUDES
#include <QObject>
#include <QList>
#include <QString>

// FORWARD DECLARATIONS
class Card;
class BaseCardDeck;

// CLASS DECLARATION
class GameLogic : public QObject
    {
    Q_OBJECT
    
    public:
        GameLogic(QObject *parent = 0);
        ~GameLogic();
    
    public:
        int randInt(int low, int high);
        void messCards();
        QList<Card*> messedCardList();
        bool isValidMove(Card* topCard, BaseCardDeck* deck);
        bool isValidMove(Card* topCard, Card* bottomCard);
        
    private:
        void createCards();
        
    private: // Data
        QList<Card*> cards;
        QList<Card*> messedCards;
    }; 

#endif //GAMELOGIC_H
