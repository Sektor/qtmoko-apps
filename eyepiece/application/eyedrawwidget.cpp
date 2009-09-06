#include <QRect>
#include <QPoint>
#include <QImage>
#include <QMouseEvent>
#include <QIcon>

#include <QtDebug>

#include "eyedrawwidget.h"

EyeDrawWidget::EyeDrawWidget ( QWidget *parent )
		: QWidget ( parent )
{
	setAttribute ( Qt::WA_NoSystemBackground );
	img          = NULL;
	srcRect      = QRect();
	oldZoom      = 40;      // TODO: preferences
	zoom         = oldZoom; // TODO: preferences
	rotation     = 0;       // TODO: preferences
	message      = "";
	mousePressed = false;
}


EyeDrawWidget::~EyeDrawWidget()
{
}

/**
 * Paint page to widget
 */
void EyeDrawWidget::paintEvent ( QPaintEvent* event )
{
	QPainter painter ( this );

	//painter.translate ( QPointF ( rect().width(), rect().height() ) / 2.0 ); //test
	painter.translate ( QPoint ( rect().width(), rect().height() ) / 2 );
	painter.rotate ( rotation );
	matrix = painter.worldMatrix().inverted();

	QRect  tmpRect = matrix.mapRect ( rect() );

	if ( img )
	{
		if ( srcRect.isNull() )
		{
			srcRect = tmpRect;
			srcRect.moveTo ( QPoint ( 0, 0 ) );
		}

		QPoint tmpPoint = srcRect.center();
		srcRect = tmpRect;
		srcRect.moveCenter ( tmpPoint );

		dstRect = tmpRect;
		dstRect.moveCenter ( QPoint ( 0, 0 ) );

		if ( zoom != oldZoom )
		{
			float zoomRatio = zoom / ( float ) oldZoom;
			oldZoom = zoom;
			tmpPoint *= zoomRatio;
			srcRect.moveCenter ( tmpPoint );
			delta = QPoint ( 0, 0 );
		}

		srcRect.moveCenter ( srcRect.center() + delta );

		if ( srcRect.left() < 0 ) srcRect.moveLeft ( 0 );
		if ( srcRect.top () < 0 ) srcRect.moveTop ( 0 );
		QSize pageSize = img->rect().size();
		if ( srcRect.right () + 1 > pageSize.width () ) srcRect.moveRight ( pageSize.width () - 1 );
		if ( srcRect.bottom() + 1 > pageSize.height() ) srcRect.moveBottom ( pageSize.height() - 1 );

		QRect rct = img->rect();
		srcRect = srcRect.intersected ( rct );
		rct.moveCenter ( QPoint ( 0, 0 ) );
		dstRect = dstRect.intersected ( rct );

		painter.drawImage ( dstRect, *img, srcRect );
		emit paintOSD ( painter, tmpRect.size() );
		painter.end();
		return;
	}

	if ( !message.isEmpty() )
		painter.drawText ( tmpRect, Qt::AlignCenter, message );

	emit paintOSD ( painter, tmpRect.size() );
}

/**
 * Store mouse coordinates
 */
void EyeDrawWidget::mousePressEvent ( QMouseEvent * event )
{
	lastPoint = matrix.map ( event->pos() );
	emit mouseEvent ( lastPoint, EyeOSD::mousePress );
	mousePressed = true;
        //if ( img  &&  event->pos().y() > height() - 20 ) emit pressedAtBottom(); //10 //COMMENTED OUT
}

/**
 * Move page
 */
void EyeDrawWidget::mouseMoveEvent ( QMouseEvent *event )
{
	if ( mousePressed )
	{
		delta = lastPoint - matrix.map ( event->pos() );
		lastPoint = matrix.map ( event->pos() );
		emit mouseEvent ( lastPoint, EyeOSD::mouseMove );
		repaint();
	}
}

void EyeDrawWidget::mouseReleaseEvent ( QMouseEvent *event )
{
	delta = QPoint ( 0, 0 );
	mousePressed = false;
	emit mouseEvent ( matrix.map ( event->pos() ), EyeOSD::mouseRelease );
}

/**
 * Slot for drawing
 * @param image
 * @param size
 */
void EyeDrawWidget::drawPage ( QImage * image )
{
	if ( image )
	{
		img = image;
		repaint();
	}
}

/**
 * Destroy image
 */
void EyeDrawWidget::cleanImage()
{
	img = NULL;
}


/**
 * Sets zoom
 * @param _zoom
 */
void EyeDrawWidget::setZoom ( int _zoom )
{
	zoom = _zoom;
}


/**
 * Rotate view
 * @param _rotation degrees
 */
void EyeDrawWidget::setRotation( int _rotation )
{
	rotation = _rotation;
	repaint();
}


/**
 * Rotate view anticlockwise
 */
void EyeDrawWidget::rotateAnticlockwise()
{
	rotation -= 90;
	if ( rotation < 0 ) rotation = 270;
	repaint();

        emit pressedAtRotateBtn(); //
}


/**
 * Set error? message
 * @param _message
 */
void EyeDrawWidget::setMessage ( const QString & _message )
{
	message = _message;
	repaint();
}
