/*
 * Copyright (c) 2009 Nokia Corporation.
 */

// INCLUDE FILES
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSvgItem>

#include "Stock.h"
#include "CardDeck.h"
#include "SolitaireScene.h"

Stock::Stock( BaseCardDeck* deck, QGraphicsItem *parentItem)
    : QGraphicsSvgItem(parentItem)
    {
    deckData = deck;
    }

Stock::~Stock()
    {
    }

int Stock::type() const
    {
    // Enable the use of qgraphicsitem_cast with this item
    return DeckType;
    }

QPainterPath Stock::shape() const
    {
    // This is called when finding collinding items
    // with QGraphicScene::collidingItems()
    QPainterPath path;
    QRectF rect = boundingRect();
    path.addRect(rect);
    return path;
    }

QRectF Stock::boundingRect() const
    {
    return QRectF(0, 0, CARD_WIDTH, CARD_HEIGHT);
    }

void Stock::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
    {
    // Draw deck background rect
    painter->setPen(Qt::SolidLine);
    painter->setPen(QColor(Qt::black));
    QRectF rect = boundingRect();
    rect.adjust(4,4,-4,-4);
    
    painter->drawRoundedRect(rect,2,2);
    }
