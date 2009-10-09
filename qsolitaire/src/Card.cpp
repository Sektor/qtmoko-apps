/*
 * Copyright (c) 2009 Nokia Corporation.
 */

#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include <QGraphicsSvgItem>
#include <QSvgRenderer>

#include "Card.h"
#include "CardDeck.h"
#include "SolitaireScene.h"


Card::Card(const QString &fileName, int value, CardSuite suite, CardColor color, 
BaseCardDeck* deck, QGraphicsItem *parentItem) : QGraphicsSvgItem(fileName,parentItem)
    {
    cardValue = value;
    cardSuite = suite;
    cardColor = color;
    cardDeck = deck;
    cardSvgPath = fileName;
    parentcard = 0;
    childcard = 0;
    cardFaceVisible = false;

    setFlag(ItemIsSelectable);
    setFlag(ItemIsMovable);
    setCacheMode(DeviceCoordinateCache);
    }

Card::~Card()
    {
    }

int Card::type() const
    {
    // Enable the use of qgraphicsitem_cast with this item
    return CardType;
    }

void Card::setPos(const QPointF &pos)
    {
    QGraphicsItem::setPos(pos);
    defaultPos = this->pos();
    }

void Card::storeDefaultPos()
    {
    defaultPos = pos();
    if (parentcard)
        {
        parentcard->storeDefaultPos();
        }
    }

void Card::setDeck(BaseCardDeck* deck)
    {
    // Remove from old deck
    if (cardDeck)
        {
        cardDeck->RemoveCard(this);
        }

    // Change pointer
    cardDeck = deck;

    // Add to new deck
    cardDeck->AddCard(this);

    // Set same deck for parent of this card
    if (parentcard)
        {
        parentcard->setDeck(cardDeck);
        }
    }

void Card::setCardVisibility(bool visible)
    {
    // Is card face or background shown
    cardFaceVisible = visible;
    }

QPainterPath Card::shape() const
    {
    // This is called when finding collinding items
    // with QGraphicScene::collidingItems()
    QPainterPath path;
    QRectF rect = boundingRect();
    path.addRect(rect);
    return path;
    }

QRectF Card::boundingRect() const
    {
    return QRectF(0, 0, CARD_WIDTH, CARD_HEIGHT);
    }

void Card::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
    {
    if (cardFaceVisible)
        {
        // Draw svg card face
        QGraphicsSvgItem::paint(painter, option, widget);
        }
    else
        {
        // Draw card background
        cardDeck->svgRenderer->render(painter,boundingRect());
        // NOTE: Do not call base class impl because it will then draw this
        // QGraphicsSvgItem's svg card face image
        }
    }

void Card::setZValue(qreal z)
    {
    QGraphicsItem::setZValue(z);
    prevZ = zValue();
    }

void Card::setCarToTop()
    {
    // Get top most item z order value
    SolitaireScene* scene = qobject_cast<SolitaireScene*>(this->scene());
    qreal z = scene->getItemsTopMostZOrder();

    // Set this card to top of others
    z += 0.1;
    setZValue(z);
    
    // Update parent (upper) cards z orders
    if (parentcard)
        {
        parentcard->zOrderUpdate(z);
        }
    }

void Card::cancelZorderUpdate()
    {
    setZValue(prevZ);

    // Cancel parent (upper) cards z orders
    if (parentcard)
        {
        parentcard->cancelZorderUpdate();
        }
    }

void Card::zOrderUpdate(qreal topZ)
    {
    topZ += 0.1;
    prevZ = zValue();
    setZValue(topZ);

    // Update parent (upper) cards z orders
    if (parentcard)
        {
        parentcard->zOrderUpdate(topZ);
        }
    }

void Card::mousePressEvent(QGraphicsSceneMouseEvent *event)
    {
    if (cardFaceVisible)
        {
        storeDefaultPos();
        pointerPos = event->scenePos();
        setCarToTop();
        }
    }

void Card::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
    {
    // Allow move visible items that belongs card deck or waste
    if (cardFaceVisible && 
            (cardDeck->Type() == BaseCardDeck::CardDeck ||
             cardDeck->Type() == BaseCardDeck::Waste))
        {
        QPointF currPointerPos = event->scenePos();
        QPointF offset;
        offset.setX(currPointerPos.x() - pointerPos.x());
        offset.setY(currPointerPos.y() - pointerPos.y());
        moveBy(offset.x(),offset.y());
        pointerPos = currPointerPos;

        // Move parent (upper) cards also if you are not top card
        if (parentcard)
            {
            parentcard->childPosChanged(pos());
            }
        }
    }

void Card::mouseReleaseEvent(QGraphicsSceneMouseEvent*)
    {
    if (cardFaceVisible && 
            (cardDeck->Type() == BaseCardDeck::CardDeck ||
             cardDeck->Type() == BaseCardDeck::Waste))
        {
        if (parentcard)
            {
            parentcard->childPosChanged(pos());
            }
        }
    }

void Card::childPosChanged(QPointF parentPos)
    {
    QPointF myPoss = pos();
    if (parentPos != myPoss)
        {
        QPointF offset;
        offset.setX(parentPos.x() - myPoss.x());
        offset.setY(parentPos.y() - myPoss.y());
        moveBy(offset.x(),offset.y() + CARD_TOP_CAP);
        }

    // Move parent (upper) cards also if you are not top card
    if (parentcard)
        {
        parentcard->childPosChanged(pos());
        }
    }

void Card::cancelCardMove()
    {
    setPos(defaultPos);
    
    // Move parent (upper) cards also if you are not top card
    if (parentcard)
        {
        parentcard->cancelCardMove();
        }
    
    // Cancel z order update
    cancelZorderUpdate();
    update();
    }

