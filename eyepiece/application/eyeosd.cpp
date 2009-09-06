#include "eyeosd.h"

#include <QtDebug> //debug

/**
 * Constructor
 */
EyeOSD::EyeOSD()
{
	docIsActive = false;

	int n;
	for ( n = 0; n < 10; ++n )
		digits[n].load ( ":/" + QString::number ( n ) + ".pic" );

	for ( n = 0; n < NUM_BUTTONS; ++n )
	{
		buttons[n] = new OSDButton;
		buttons[n]->mode = QIcon::Normal;
		buttons[n]->icon.addFile ( ":/" + QString::number ( n + 1 ) + "_nrml.pic",
		                           QSize (), QIcon::Normal );
		buttons[n]->icon.addFile ( ":/" + QString::number ( n + 1 ) + "_prss.pic",
		                           QSize (), QIcon::Selected );
// 		buttons[n]->icon.addFile ( ":/" + QString::number ( n + 1 ) + "_dsbl.pic",
// 		                           QSize (), QIcon::Disabled );
	}
}


/**
 * Destructor
 */
EyeOSD::~EyeOSD()
{
	//delete?
}

void EyeOSD::setCurrPage ( const int page )
{
	currPage = page;
}

void EyeOSD::setDocActive( bool a )
{
	docIsActive = a;
}

/**
 * Paints buttons
 * @param painter
 * @param size
 */
void EyeOSD::paint ( QPainter & painter, const QSize & size )
{
	painter.setOpacity ( 0.8 ); // TODO: preferences

	int interval = ICON_SIZE + SPAN;

	int n;
	for ( n = 0; n < NUM_BUTTONS; ++n )
	{
		buttons[n]->rect = QRect ( n * interval - ( ( NUM_BUTTONS - 1 ) * interval + ICON_SIZE ) / 2,
		                           size.height() / 2 - ICON_SIZE - 2,
		                           ICON_SIZE, ICON_SIZE );
		buttons[n]->icon.paint ( &painter, buttons[n]->rect, BUGGG, buttons[n]->mode );
	}

	painter.setOpacity ( 0.3 ); // TODO: preferences

	if ( docIsActive )
	{
		QString page = QString::number ( currPage + 1 );
		int i = digits[8].boundingRect().width() - 4;
		for ( n = 0; n < page.length(); n++ )
			painter.drawPicture ( ( n - page.length() ) * i + size.width() / 2 - 5,
			                      - size.height() / 2 + 2,
			                      digits[ page[n].digitValue() ] );
	}
}


/**
 * Whether the button is pressed or not
 */
void EyeOSD::onMouseEvent ( const QPoint & point, EyeOSD::MouseEvent event )
{
	for ( int n = 0; n < NUM_BUTTONS; ++n )
	{
		bool inside = buttons[n]->rect.contains ( point );
		switch ( event )
		{
			case mouseRelease:
				if ( buttons[n]->mode == QIcon::Selected )
				{
					buttons[n]->mode = QIcon::Normal;
					emit needRepaint();
					if ( inside ) emit keyClicked ( n );
					break; // it is worked?
				}
				break;
			case mouseMove:
				if ( buttons[n]->mode == QIcon::Selected && !inside )
				{
					buttons[n]->mode = QIcon::Normal;
					emit needRepaint();
					break;
				}
				break;
			case mousePress:
				if ( inside )
				{
					buttons[n]->mode = QIcon::Selected;
					emit needRepaint();
					break;
				}
				break;
		}
	}
}
