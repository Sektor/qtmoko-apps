/*
 * Copyright (c) 2009 Nokia Corporation.
 */

#include <QSvgRenderer>

#include "CardDeck.h"
#include "Card.h"

// BaseCardDeck ---------------------------------------------------------------

BaseCardDeck::BaseCardDeck(BaseCardDeck::DeckType type, QObject *parent)
: QObject(parent)
    {
    deckType = type;

    // Common place for the cards to get background
    svgRenderer = new QSvgRenderer(this);
    svgRenderer->load(QString(":/images/card_background_75x110.svg"));
    }

BaseCardDeck::~BaseCardDeck()
    {
    // Clear items, do not delete these because GamoLogic::messedCards owns them
    cards.clear();
    }

void BaseCardDeck::AddCard(Card* newCard)
    {
    cards.append(newCard);
    }

void BaseCardDeck::RemoveCard(Card* card)
    {
    Card* item=0;
    int i = 0;
    foreach (item, cards)
        {
        if (item==card)
            {
            // Does not delete card object, only remove pointer
            cards.removeAt(i);
            break;
            }
        i++;
        }
    }

QList<Card*> BaseCardDeck::Cards()
    {
    return cards;
    }


// CardDeck -------------------------------------------------------------------

CardDeck::CardDeck(BaseCardDeck::DeckType type, QObject *parent)
: BaseCardDeck(type,parent)
    {
    }

CardDeck::~CardDeck()
    {
    }

