/*
 * Copyright (c) 2009 Nokia Corporation.
 */

// INCLUDES
#include <QtGui>

#include "SolitaireScene.h"
#include "CardDeck.h"
#include "Card.h"
#include "GameLogic.h"
#include "Deck.h"
#include "Foundation.h"
#include "Stock.h"
#include "Waste.h"

SolitaireScene::SolitaireScene(GameLogic* gameLogic, QObject *parent)
: QGraphicsScene(parent)
    {
    this->gameLogic = gameLogic;

    // Listen scene rect changes
    QObject::connect(this, SIGNAL(sceneRectChanged(QRectF)),
                     this, SLOT(UpdatePositions(QRectF)));

    activeGraphicItem = 0;
    }

SolitaireScene::~SolitaireScene()
    {
    }

void SolitaireScene::createDecks()
    {
    int zorder = 0;

    // Get all messed cards
    QList<Card*> cards = gameLogic->messedCardList();
    
    
    // Create data classes
    deck1 = new CardDeck(BaseCardDeck::CardDeck,this);
    deck2 = new CardDeck(BaseCardDeck::CardDeck,this);
    deck3 = new CardDeck(BaseCardDeck::CardDeck,this);
    deck4 = new CardDeck(BaseCardDeck::CardDeck,this);
    deck5 = new CardDeck(BaseCardDeck::CardDeck,this);
    deck6 = new CardDeck(BaseCardDeck::CardDeck,this);
    deck7 = new CardDeck(BaseCardDeck::CardDeck,this);
    foundation1 = new CardDeck(BaseCardDeck::Foundation,this);
    foundation2 = new CardDeck(BaseCardDeck::Foundation,this);
    foundation3 = new CardDeck(BaseCardDeck::Foundation,this);
    foundation4 = new CardDeck(BaseCardDeck::Foundation,this);
    stock = new CardDeck(BaseCardDeck::Stock,this);
    waste = new CardDeck(BaseCardDeck::Waste,this);


    // Create graphic framework items
    // Deck background items
    deck1Item = new Deck(deck1);
    deck1Item->setZValue(zorder++);
    addItem(deck1Item);
    
    deck2Item = new Deck(deck2);
    deck2Item->setZValue(zorder++);
    addItem(deck2Item);
    
    deck3Item = new Deck(deck3);
    deck3Item->setZValue(zorder++);
    addItem(deck3Item);
    
    deck4Item = new Deck(deck4);
    deck4Item->setZValue(zorder++);
    addItem(deck4Item);
    
    deck5Item = new Deck(deck5);
    deck5Item->setZValue(zorder++);
    addItem(deck5Item);
    
    deck6Item = new Deck(deck6);
    deck6Item->setZValue(zorder++);
    addItem(deck6Item);
    
    deck7Item = new Deck(deck7);
    deck7Item->setZValue(zorder++);
    addItem(deck7Item);
    
    foundation1Item = new Foundation(foundation1);
    foundation1Item->setZValue(zorder++);
    addItem(foundation1Item);

    foundation2Item = new Foundation(foundation2);
    foundation2Item->setZValue(zorder++);
    addItem(foundation2Item);
    
    foundation3Item = new Foundation(foundation3);
    foundation3Item->setZValue(zorder++);
    addItem(foundation3Item);

    foundation4Item = new Foundation(foundation4);
    foundation4Item->setZValue(zorder++);
    addItem(foundation4Item);
    
    stockItem = new Stock(stock);
    addItem(stockItem);
    wasteItem = new Waste(waste);
    addItem(wasteItem);
    
    // Create card items
    // Deck1
    Card* childCard = 0;
    for(int i=0; i<1;i++)
        {
        Card* card = cards.first();
        card->setZValue(zorder++);
        card->setDeck(deck1);
        addItem(card);
        cards.removeFirst();
        childCard = card;
        }
    childCard->setCardVisibility(true);
    childCard = 0;
    
    // Deck2
    for(int i=0; i<2;i++)
        {
        Card* card = cards.first();
        card->setZValue(zorder++);
        card->setDeck(deck2);
        if (childCard)
            {
            childCard->setParentCard(card);
            card->setChildCard(childCard);
            }
        addItem(card);
        cards.removeFirst();
        childCard = card;
        }
    childCard->setCardVisibility(true);
    childCard = 0;
    
    // Deck3
    for(int i=0; i<3;i++)
        {
        Card* card = cards.first();
        card->setZValue(zorder++);
        card->setDeck(deck3);
        if (childCard)
            {
            childCard->setParentCard(card);
            card->setChildCard(childCard);
            }
        addItem(card);
        cards.removeFirst();
        childCard = card;
        }
    childCard->setCardVisibility(true);
    childCard = 0;

    // Deck4
    for(int i=0; i<4;i++)
        {
        Card* card = cards.first();
        card->setZValue(zorder++);
        card->setDeck(deck4);
        if (childCard)
            {
            childCard->setParentCard(card);
            card->setChildCard(childCard);
            }
        addItem(card);
        cards.removeFirst();
        childCard = card;
        }
    childCard->setCardVisibility(true);
    childCard = 0;

    // Deck5
    for(int i=0; i<5;i++)
        {
        Card* card = cards.first();
        card->setZValue(zorder++);
        card->setDeck(deck5);
        if (childCard)
            {
            childCard->setParentCard(card);
            card->setChildCard(childCard);
            }
        addItem(card);
        cards.removeFirst();
        childCard = card;
        }
    childCard->setCardVisibility(true);
    childCard = 0;

    // Deck6
    for(int i=0; i<6;i++)
        {
        Card* card = cards.first();
        card->setZValue(zorder++);
        card->setDeck(deck6);
        if (childCard)
            {
            childCard->setParentCard(card);
            card->setChildCard(childCard);
            }
        addItem(card);
        cards.removeFirst();
        childCard = card;
        }
    childCard->setCardVisibility(true);
    childCard = 0;

    // Deck 7
    for(int i=0; i<7;i++)
        {
        Card* card = cards.first();
        card->setZValue(zorder++);
        card->setDeck(deck7);
        if (childCard)
            {
            childCard->setParentCard(card);
            card->setChildCard(childCard);
            }
        addItem(card);
        cards.removeFirst();
        childCard = card;
        }
    childCard->setCardVisibility(true);
    childCard = 0;

    // Deal rest of the cards into stock deck
    while(!cards.isEmpty())
        {
        Card* card = cards.first();
        card->setZValue(zorder++);
        card->setCardVisibility(false);
        card->setDeck(stock);
        addItem(card);
        cards.removeFirst();
        }
    
    }
    
qreal SolitaireScene::deckCap()
    {
    return CARD_WIDTH / 8.0;
    }

void SolitaireScene::UpdatePositions(const QRectF& rect)
    {
    Card* card = 0;
    
    // Calculate 7 decks positions
    qreal deckX = 0;
    qreal deckY = 0;
    qreal deckCapVal = deckCap();

    if (rect.width() > rect.height())
        {
        // Terminal landscape
        deckY = rect.height() / 3;
        deckX = (rect.width() - (8 * CARD_WIDTH + 8 * deckCapVal)) /2;
        }
    else
        {
        // Terminal portrait
        deckY = rect.height()/2 - CARD_HEIGHT;
        deckX = (rect.width() - (8 * CARD_WIDTH + 8 * deckCapVal)) /2;
        }

    
    deckX += deckCapVal + CARD_WIDTH/2;
    deck1Item->setPos(deckX,deckY);
    stockItem->setPos(deckX,deckY - (CARD_HEIGHT+deckCapVal));
    int counter = 0;
    card = 0;
    foreach (card, deck1->Cards())
        {
        card->setPos(QPointF(deckX,deckY+CARD_TOP_CAP*counter));
        counter++;
        }
    
    deckX += deckCapVal + CARD_WIDTH;
    deck2Item->setPos(deckX,deckY);
    wasteItem->setPos(deckX,deckY - (CARD_HEIGHT+deckCapVal));
    counter = 0;
    card = 0;
    foreach (card, deck2->Cards())
        {
        card->setPos(QPointF(deckX,deckY+CARD_TOP_CAP*counter));
        counter++;
        }
    
    deckX += deckCapVal + CARD_WIDTH;
    deck3Item->setPos(deckX,deckY);
    counter = 0;
    card = 0;
    foreach (card, deck3->Cards())
        {
        card->setPos(QPointF(deckX,deckY+CARD_TOP_CAP*counter));
        counter++;
        }
    
    deckX += deckCapVal + CARD_WIDTH;
    deck4Item->setPos(deckX,deckY);
    foundation1Item->setPos(deckX,deckY - (CARD_HEIGHT+deckCapVal));
    counter = 0;
    card = 0;
    foreach (card, deck4->Cards())
        {
        card->setPos(QPointF(deckX,deckY+CARD_TOP_CAP*counter));
        counter++;
        }
    
    deckX += deckCapVal + CARD_WIDTH;
    deck5Item->setPos(deckX,deckY);
    foundation2Item->setPos(deckX,deckY - (CARD_HEIGHT+deckCapVal));
    counter = 0;
    card = 0;
    foreach (card, deck5->Cards())
        {
        card->setPos(QPointF(deckX,deckY+CARD_TOP_CAP*counter));
        counter++;
        }
    
    deckX += deckCapVal + CARD_WIDTH;
    deck6Item->setPos(deckX,deckY);
    foundation3Item->setPos(deckX,deckY - (CARD_HEIGHT+deckCapVal));
    counter = 0;
    card = 0;
    foreach (card, deck6->Cards())
        {
        card->setPos(QPointF(deckX,deckY+CARD_TOP_CAP*counter));
        counter++;
        }
    
    deckX += deckCapVal + CARD_WIDTH;
    deck7Item->setPos(deckX,deckY);
    foundation4Item->setPos(deckX,deckY - (CARD_HEIGHT+deckCapVal));
    counter = 0;
    card = 0;
    foreach (card, deck7->Cards())
        {
        card->setPos(QPointF(deckX,deckY+CARD_TOP_CAP*counter));
        counter++;
        }
    deckX += deckCapVal + CARD_WIDTH;

    // Update cards in stock
    card = 0;
    foreach (card, stock->Cards())
        {
        card->setPos(stockItem->pos());
        }

    // Update cards in waste
    card = 0;
    foreach (card, waste->Cards())
        {
        card->setPos(wasteItem->pos());
        }
    
    // Update foundation cards
    card = 0;
    foreach (card, foundation1->Cards())
        {
        card->setPos(foundation1Item->pos());
        }
    card = 0;
    foreach (card, foundation2->Cards())
        {
        card->setPos(foundation2Item->pos());
        }
    card = 0;
    foreach (card, foundation3->Cards())
        {
        card->setPos(foundation3Item->pos());
        }
    card = 0;
    foreach (card, foundation4->Cards())
        {
        card->setPos(foundation4Item->pos());
        }
    }


void SolitaireScene::mousePressEvent(QGraphicsSceneMouseEvent *mouseEvent)
    {
    // Check that is mouseReleaseEvent occured on previous mouse event 
    if (activeGraphicItem)
        {
        if (activeGraphicItem->type() == Card::CardType)
            {
            Card* losedCard = static_cast<Card*>(activeGraphicItem);
            losedCard->cancelCardMove();
            losedCard->update();
            }
        activeGraphicItem = 0;
        }
    else
        {
        // Store selected graphicitem
        activeGraphicItem = itemAt(mouseEvent->scenePos());
        }

    // Sends mouse events into graphics items
    QGraphicsScene::mousePressEvent(mouseEvent);
    }

void SolitaireScene::mouseMoveEvent(QGraphicsSceneMouseEvent *mouseEvent)
    {
    if (activeGraphicItem)
        QGraphicsScene::mouseMoveEvent(mouseEvent);
    }

void SolitaireScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *mouseEvent)
    {
    QGraphicsScene::mouseReleaseEvent(mouseEvent);
    
    if (activeGraphicItem && activeGraphicItem->type() == Card::CardType)
        {
        // Moving / pointing cards
        Card* activeCard = static_cast<Card*>(activeGraphicItem);
        int error = 0;
        if (activeCard->deck()->Type() == BaseCardDeck::CardDeck || 
                activeCard->deck()->Type() == BaseCardDeck::Waste)
            {
            // Dragging cards into card decks or foundation
            QList<QGraphicsItem*> items = collidingItems(activeGraphicItem);
            // Do some pre-cleaning for the colliding items
            cleanItems(items);

            // Colliding items?
            if (!items.isEmpty())
                {
                // Try to handle card moves between decks
                error = handleCardMoves(items);
                items.clear();
                }
            else
                {
                // Cancel card move, there was nothing under it
                error = -1;
                }
            }
        else if (activeCard->deck()->Type() == BaseCardDeck::Stock) 
            {
            // Getting new cards from stock to waste
            activeCard->setDeck(waste);
            activeCard->setCardVisibility(true);
            activeCard->setPos(wasteItem->pos());
            activeCard->setCarToTop();
            activeCard->update();
            }
        else
            {
            error = -1;
            }

        if (error)
            {
            // Cancel card move, there was nothing under it
            activeCard->cancelCardMove();
            activeCard->update();
            update();
            }
        }
    else if (activeGraphicItem && activeGraphicItem->type() == Stock::DeckType)
        {
        // Pointing empty Stock deck
        // Stock is empty, copy cards from waste back to stock
        Card* card = 0;
        while(!waste->Cards().isEmpty())
            {
            card = waste->Cards().first();
            card->setDeck(stock);
            card->setCardVisibility(false);
            card->setPos(stockItem->pos());
            card->update();
            }
        if (card)
            {
            card->setCardVisibility(true);
            card->setDeck(waste);
            card->setPos(wasteItem->pos());
            card->setCarToTop();
            card->update();
            }
        }

    // Reset active graphic iten
    activeGraphicItem = 0;
    }

void SolitaireScene::cleanItems(QList<QGraphicsItem*>& items)
    {
    // List must has items that really collides with dragging items,
    // not also these actual dragging items etc.

    QGraphicsItem* collidingItem=0;
    int i = 0;
    foreach (collidingItem, items)
        {
        // Card graphic item
        if (collidingItem->type() == Card::CardType)
            {
            Card* collidingCard = static_cast<Card*>(collidingItem);
            // Remove items that user is dragging
            if (collidingItem->zValue() >= activeGraphicItem->zValue())
                {
                items.removeAt(i);
                i--;
                }
            // If colliding card does not belong card deck or foundation, remove it
            else if (collidingCard->deck()->Type() != BaseCardDeck::CardDeck &&
                    collidingCard->deck()->Type() != BaseCardDeck::Foundation )
                {
                items.removeAt(i);
                i--;
                }
            }
        // Deck graphic item
        else if (collidingItem->type() == Deck::DeckType)
            {
            // Do not remove this colliding item
            }
        // Deck graphic item
        else if (collidingItem->type() == Foundation::DeckType)
            {
            // Do not remove this colliding item
            }
        else
            {
            items.removeAt(i);
            i--;
            }
        i++;
        }
    }

int SolitaireScene::handleCardMoves(QList<QGraphicsItem*>& items)
    {
    int error = -1;
    QGraphicsItem* item=0;
    foreach (item, items)
        {
        // Card is moving top of another card
        if (item->type() == Card::CardType)
            {
            Card* bottomCard = static_cast<Card*>(item);
            Card* topCard = static_cast<Card*>(activeGraphicItem);
    
            // Bottom card can not have parent yet, if it
            // has we cannot put new card on it
            if (bottomCard->parentCard())
                {
                continue;
                }
    
            // Can add one card at the time into foundation decks
            if (topCard->parentCard() && bottomCard->deck()->Type() == BaseCardDeck::Foundation)
                {
                continue;
                }
            // Can not move items from other decks than card deck or waste
            if (topCard->deck()->Type() != BaseCardDeck::CardDeck &&
                topCard->deck()->Type() != BaseCardDeck::Waste)
                {
                break;
                }
    
            if (!topCard->isCardFaceVisible())
                {
                break;
                }
    
            // Check move validity
            if(gameLogic->isValidMove(topCard,bottomCard))
                {
                // Card move accepted, do move
                // NOTE: These changes affec also to topCard parent cards
                // when moving multiple cards
    
                // Change card deck to new one
                topCard->setDeck(bottomCard->deck());
    
                // Set new position
                QPointF pos = bottomCard->pos();
                if (topCard->deck()->Type() == BaseCardDeck::Foundation)
                    {
                    topCard->setPos(QPointF(pos.x(),pos.y()));
                    }
                else
                    {
                    topCard->setPos(QPointF(pos.x(),pos.y()+CARD_TOP_CAP));
                    // Move parent (upper) cards also if you are not top card
                    topCard->childPosChanged(topCard->pos());
                    }
    
                // Set child card visibility and
                // parent to zero values for card under moving
                if (topCard->childCard())
                    {
                    topCard->childCard()->setCardVisibility(true);
                    topCard->childCard()->setParentCard(0);
                    topCard->childCard()->update();
                    topCard->storeDefaultPos();
                    }
    
                // Set new parent / child realationship
                bottomCard->setParentCard(topCard);
                topCard->setChildCard(bottomCard);
    
                bottomCard->update();
                topCard->update();
    
                // Valid move done, no errors send
                error = 0;
                break;
                }
            }
        // Card is moving top of (empty) deck
        else if (item->type() == Deck::DeckType)
            {
            Deck* activedeck = static_cast<Deck*>(item);
            Card* card = static_cast<Card*>(activeGraphicItem);
    
            // Can not move items from other decks than card deck or waste
            if (card->deck()->Type() != BaseCardDeck::CardDeck &&
                card->deck()->Type() != BaseCardDeck::Waste)
                {
                break;
                }
    
            // Can not move card that face is not visible
            if (!card->isCardFaceVisible())
                {
                break;
                }
            
            // Can not add card to this level if it already has 
            // other cards. Insertion must go to card level.
            if (activedeck->deck()->Cards().count() > 0)
                {
                continue;
                }
            
            if (gameLogic->isValidMove(card,activedeck->deck()))
                {
                // Card is moving on top of new deck
    
                // Change card deck to new one
                card->setDeck(activedeck->deck());
    
                // Set child card visibility and
                // parent to zero values for card under moving
                if (card->childCard())
                    {
                    card->childCard()->setCardVisibility(true);
                    card->childCard()->setParentCard(0);
                    card->childCard()->update();
                    card->setChildCard(0);
                    }
    
                // Set card new position
                card->setPos(activedeck->pos());
                // Move parent (upper) cards also if you are not top card
                card->childPosChanged(card->pos());
                
                card->storeDefaultPos();
                
                card->update();
                error = 0;
                break;
                }
            }
        // Card is moving top of (empty) foundation
        else if (item->type() == Foundation::DeckType)
            {
            Foundation* activedeck = static_cast<Foundation*>(item);
            Card* card = static_cast<Card*>(activeGraphicItem);
    
            // Card can not have parent, we can set
            // one car in the same time to the new deck
            if (card->parentCard())
                {
                break;
                }
              
            // Can not move card that face is not visible
            if (!card->isCardFaceVisible())
                {
                break;
                }
            
            // Can not move items from other decks than card deck or waste
            if (card->deck()->Type() != BaseCardDeck::CardDeck &&
                card->deck()->Type() != BaseCardDeck::Waste)
                {
                break;
                }
    
            // Can not add card to this level if it already has 
            // other cards. Insertion must go to card level.
            if (activedeck->deck()->Cards().count() > 0)
                {
                continue;
                }
            
            if (gameLogic->isValidMove(card,activedeck->deck()))
                {
                // Card is moving on top of new deck
    
                // Change card deck to new one
                card->setDeck(activedeck->deck());
    
                // Set child card visibility and
                // parent to zero values for card under moving
                if (card->childCard())
                    {
                    card->childCard()->setCardVisibility(true);
                    card->childCard()->setParentCard(0);
                    card->childCard()->update();
                    card->setChildCard(0);
                    }
    
                // Remove parent
                card->setParentCard(0);
    
                // Set card new position
                card->setPos(activedeck->pos());
    
                card->update();
                error = 0;
                break;
                }
            }
        
        } // foreach
    
    return error;
    }


qreal SolitaireScene::getItemsTopMostZOrder()
    {
    qreal z = 0;
    QGraphicsItem* item = 0;
    foreach (item, items())
        {
        if (item->zValue() > z)
            {
            z = item->zValue();
            }
        }
    return z;
    }





