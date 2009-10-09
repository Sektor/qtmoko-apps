/*
 * Copyright (c) 2009 Nokia Corporation.
 */

// INCLUDE FILES
#include <QPainter>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QList>
#include <QGraphicsSvgItem>
#include <QSvgRenderer>

#include "Foundation.h"
#include "CardDeck.h"
#include "SolitaireScene.h"


Foundation::Foundation( BaseCardDeck* deck, QGraphicsItem *parentItem)
    : QGraphicsSvgItem(parentItem)
    {
    deckData = deck;
    }

Foundation::~Foundation()
    {
    }

int Foundation::type() const
    {
    // Enable the use of qgraphicsitem_cast with this item
    return DeckType;
    }

QPainterPath Foundation::shape() const
    {
    // This is called when finding collinding items
    // with QGraphicScene::collidingItems()
    QPainterPath path;
    QRectF rect = boundingRect();
    path.addRect(rect);
    return path;
    }

QRectF Foundation::boundingRect() const
    {
    return QRectF(0, 0, CARD_WIDTH, CARD_HEIGHT);
    }

void Foundation::paint(QPainter *painter, const QStyleOptionGraphicsItem */*option*/, QWidget */*widget*/)
    {
    // Draw deck background rect
    painter->setPen(Qt::SolidLine);
    painter->setPen(QColor(Qt::black));
    QRectF rect = boundingRect();
    rect.adjust(4,4,-4,-4);
    
    painter->drawRoundedRect(rect,2,2);
    }

