#ifndef EYEOSD_H
#define EYEOSD_H

#include <QObject>
#include <QPainter>
#include <QIcon>
#include <QRect>
#include <QPicture>

// Why does this not affect the position of the icon? Shit...
#define BUGGG Qt::AlignLeft | Qt::AlignTop

#define NUM_BUTTONS 7

// TODO: preferences
#define SPAN        2
#define ICON_SIZE   60
#define REL_POS     0.85

/**
*/
class EyeOSD : public QObject
{
		Q_OBJECT
	public:
		EyeOSD();
		~EyeOSD();
		
		void setCurrPage( const int );
		void setDocActive( bool );
		
		enum MouseEvent
		{
			mousePress,
			mouseMove,
			mouseRelease
		};

	private:
		struct OSDButton
		{
			QIcon       icon;
			QRect       rect;
			QIcon::Mode mode;
		}
		* buttons[NUM_BUTTONS];
		int      currPage;
		QPicture digits[10];
		bool     docIsActive;

	public slots:
		void paint ( QPainter &, const QSize & );
		void onMouseEvent ( const QPoint &, EyeOSD::MouseEvent );

	signals:
		void needRepaint();
		void keyClicked( int );
};

#endif
