#ifndef EYEDRAWWIDGET_H
#define EYEDRAWWIDGET_H

#include <QWidget>
#include <QSize>
#include <QPainter>
#include <QMatrix>

#include "eyeosd.h"

/**
*/
class EyeDrawWidget : public QWidget
{
		Q_OBJECT
	public:
		EyeDrawWidget ( QWidget *parent = 0 );
		~EyeDrawWidget();
		void cleanImage();
		void setZoom( int _zoom );
		void setRotation( int );
		void rotateAnticlockwise();
		void setMessage( const QString & _message );
		void drawPage( QImage * );
		
	signals:
		void pressedAtBottom();
		void paintOSD( QPainter &, const QSize & );
		void mouseEvent( const QPoint &, EyeOSD::MouseEvent );
                void pressedAtRotateBtn(); //

	private:
		QImage * img;          // image for drawing
		QRect    srcRect;      // source area to draw
		QRect    dstRect;      // destination area
		QPoint   lastPoint;    // where is last coordinates of mouse pointer
		QPoint   delta;        // mouse offset
		bool     mousePressed;
		int      zoom;
		int      oldZoom;
		int      rotation;
		QString  message;
		QMatrix  matrix;
		
		void paintEvent        ( QPaintEvent * event );
		void mousePressEvent   ( QMouseEvent * event );
		void mouseMoveEvent    ( QMouseEvent * event );
		void mouseReleaseEvent ( QMouseEvent * event );
};

#endif
