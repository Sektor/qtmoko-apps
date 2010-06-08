#include "eyepiece.h"

#include <QWidget>
#include <QPushButton>
#include <QSoftMenuBar>
#include <QMenu>
#include <QDir>

#include <QMimeType>
#include <QtDebug>

#include <QFile>
#include <QMessageBox>
#include <QTimer>
#include <installer.h>
#include <accelerometers.h>
#include <math.h>

static const QString mime_pdf  = "application/pdf"; // TODO: get this from plugins
static const QString mime_djvu = "image/vnd.djvu";  // TODO: ^

int curRot = 0;
bool acc_enabled = false;
bool libCheckPassed = false;

/**
 * Constructor
 */
Eyepiece::Eyepiece ( QWidget *parent, Qt::WFlags f ) :
		QWidget ( parent, f ),
		document ( NULL ),
		pluginLoader ( NULL )

{
	Ui_Eyepiece::setupUi ( this );
	miscWidget->hide();

	documentSelector = new QDocumentSelector;

	QContentSet contentSet;
        contentSet.addCriteria ( QContentFilter::MimeType, mime_pdf,  QContentFilter::Or );
	contentSet.addCriteria ( QContentFilter::MimeType, mime_djvu, QContentFilter::Or );
	documentSelector->setFilter ( contentSet.filter() );

	// TODO: add sort mode selection to menu
	documentSelector->setSortMode ( QDocumentSelector::Alphabetical );
	eyeStackedWidget->addWidget ( documentSelector );

	QMenu *menu = QSoftMenuBar::menuFor ( viewPage );
	openAction      = new QAction ( "Open",       viewPage );
	rotateAction0   = new QAction ( "Rotate 0",   viewPage );
	rotateAction90  = new QAction ( "Rotate 90",  viewPage );
	rotateAction180 = new QAction ( "Rotate 180", viewPage );
	rotateAction270 = new QAction ( "Rotate 270", viewPage );
        rotateActionAuto = new QAction ( "Auto Rotate", viewPage );
        rotateActionAuto->setCheckable(true);

	disableRotateActions();
	menu->addAction ( openAction );
	menu->addSeparator();
	menu->addAction ( rotateAction0 );
	menu->addAction ( rotateAction90 );
	menu->addAction ( rotateAction180 );
	menu->addAction ( rotateAction270 );
        menu->addAction ( rotateActionAuto );
        //Q_UNUSED ( menu );
	//QSoftMenuBar::setHelpEnabled ( this,true );
	connect ( openAction,      SIGNAL ( triggered() ), this, SLOT ( onOpen() ) );
	connect ( rotateAction0,   SIGNAL ( triggered() ), this, SLOT ( onRotate0() ) );
	connect ( rotateAction90,  SIGNAL ( triggered() ), this, SLOT ( onRotate90() ) );
	connect ( rotateAction180, SIGNAL ( triggered() ), this, SLOT ( onRotate180() ) );
	connect ( rotateAction270, SIGNAL ( triggered() ), this, SLOT ( onRotate270() ) );
        connect ( rotateActionAuto, SIGNAL ( triggered() ), this, SLOT ( onRotateAuto() ) );

	connect ( eyeDrawWidget, SIGNAL ( pressedAtBottom() ), this, SLOT ( onPressedAtBottom() ) );
	connect ( eyeDrawWidget, SIGNAL ( paintOSD ( QPainter &, const QSize & ) ),
	          &eyeOSD, SLOT ( paint ( QPainter &, const QSize & ) ) );
	connect ( eyeDrawWidget, SIGNAL ( mouseEvent ( const QPoint &, EyeOSD::MouseEvent ) ),
	          &eyeOSD, SLOT ( onMouseEvent ( const QPoint &, EyeOSD::MouseEvent ) ) );
	connect ( &eyeOSD, SIGNAL ( needRepaint() ), eyeDrawWidget, SLOT ( repaint() ) );
	connect ( &eyeOSD, SIGNAL ( keyClicked ( int ) ), this, SLOT ( onKeyClicked ( int ) ) );

	connect ( documentSelector, SIGNAL ( documentSelected ( const QContent & ) ),
	          this, SLOT ( openDocument ( const QContent & ) ) );

        //
        acc_timer = new QTimer(this);
        connect(acc_timer, SIGNAL(timeout()), this, SLOT(acc_timerAction()));

        connect ( eyeDrawWidget, SIGNAL ( pressedAtRotateBtn() ), this, SLOT ( disableAutoRotate() ) );

        setWindowFlags(Qt::Dialog | Qt::WindowStaysOnTopHint);

        QTimer::singleShot(0, this, SLOT(checkLibs()));

}

bool Eyepiece::libsFound()
{
    return QFile::exists("/usr/lib/libdjvulibre.so.21");
}

void Eyepiece::checkLibs()
{
    if (!libsFound())
    {
        if (QMessageBox::warning(
                this,
                tr("Eyepiece"),
                tr("libdjvulibre21 is not found. Do you want to install it now via apt-get?"),
                QMessageBox::Yes, QMessageBox::No) == QMessageBox::Yes)
        {
            Installer *apt = new Installer(this);
            apt->show();
            apt->start();
            if (libsFound())
                QMessageBox::information(
                    this,
                    tr("Eyepiece"),
                    tr("Installation completed successfully"));
            else
                QMessageBox::warning(
                    this,
                    tr("Eyepiece"),
                    tr("Installation failed"));
        }
    }
    libCheckPassed = true;
}

#define ANGLE_THRESHOLD  M_PI*12.0/180.0
#define ANGLE_MULTIPLIER 1.3
void Eyepiece::acc_timerAction()
{
    float ax = getacx();
    float ay = getacy();
    float angle_x = asin(fabs(ax));
    float angle_y = asin(fabs(ay));

    //qDebug() << angle_x << angle_y;

    if ( (angle_x >= ANGLE_THRESHOLD) && (angle_x > angle_y*ANGLE_MULTIPLIER) )
    {
        if (ax>0)
        {
            if (curRot!=3) eyeDrawWidget->setRotation(270);
            curRot=3;
        }
        else
        {
            if (curRot!=1) eyeDrawWidget->setRotation(90);
            curRot=1;
        }
    }
    else if ( (angle_y >= ANGLE_THRESHOLD) && (angle_y > angle_x*ANGLE_MULTIPLIER) )
    {
        if (ay>0)
        {
            if (curRot!=2) eyeDrawWidget->setRotation(180);
            curRot=2;
        }
        else
        {
            if (curRot!=0) eyeDrawWidget->setRotation(0);
            curRot=0;
        }
    }
}

void Eyepiece::setAutoRotate(bool x)
{
    if (acc_enabled == x) return;

    if (x)
    {
        accelerometer_start();
        acc_timer->start(1000);
    }
    else
    {
        acc_timer->stop();
        accelerometer_stop();
        curRot=-1;
    }

    acc_enabled = x;
    rotateActionAuto->setChecked(x);
}

void Eyepiece::disableAutoRotate()
{
    setAutoRotate(false);
}

/**
 * Destructor
 */
Eyepiece::~Eyepiece()
{
}


/**
 * OK to zoom
 */
void Eyepiece::on_okButton_clicked()
{
	miscWidget->hide();
	document->setZoom ( spinBox->value() );
	eyeDrawWidget->setZoom ( document->getZoom() );
	eyeDrawWidget->drawPage ( document->getImage() );
}


/**
 * Toggle full screen
 */
void Eyepiece::toggleWindowState()
{
        //QString title = windowTitle();
        //setWindowTitle ( QLatin1String ( "_allow_on_top_" ) );
	setWindowState ( windowState() ^ Qt::WindowFullScreen );
        //setWindowTitle ( title );
}


/**
 * Go to document selector
 */
void Eyepiece::onOpen()
{
	eyeStackedWidget->setCurrentWidget ( documentSelector );
}


void Eyepiece::onRotate0()
{
	eyeDrawWidget->setRotation ( 0 );
        setAutoRotate(false);
}

void Eyepiece::onRotate90()
{
	eyeDrawWidget->setRotation ( 90 );
        setAutoRotate(false);
}

void Eyepiece::onRotate180()
{
	eyeDrawWidget->setRotation ( 180 );
        setAutoRotate(false);
}

void Eyepiece::onRotate270()
{
	eyeDrawWidget->setRotation ( 270 );
        setAutoRotate(false);
}

void Eyepiece::onRotateAuto()
{
        setAutoRotate( rotateActionAuto->isChecked() );
}

void Eyepiece::onPressedAtBottom()
{
	if ( /* !navBtnWidget->isVisible() && */ windowState() & Qt::WindowFullScreen )
	{
                toggleWindowState();
        }
}


void Eyepiece::openDocument ( const QContent & cnt )
{
	contentID = cnt.type();
	qWarning() << contentID;
	setDocument ( cnt.fileName() );
}


/**
 * Error loading document
 */
void Eyepiece::onDocumentLoadError()
{
	unloadPlugin();
	eyeOSD.setDocActive ( false );
	eyeDrawWidget->cleanImage();
	eyeDrawWidget->setMessage ( "Error: cannot open document" );
	disableRotateActions();
	eyeStackedWidget->setCurrentWidget ( viewPage );
}

void Eyepiece::onKeyClicked ( int key )
{
	switch ( key )
	{
		case 0:  // Open
			eyeStackedWidget->setCurrentWidget ( documentSelector );
			return;
		case 5:  // Rotate
			eyeDrawWidget->rotateAnticlockwise();
			return;
		case 6:  // Toggle full screen
			toggleWindowState();
			return;
	}

	if ( document )
		switch ( key )
		{
			case 1:  // Prev page
				document->prevPage();
				eyeOSD.setCurrPage ( document->getNumPage() );
				eyeDrawWidget->drawPage ( document->getImage() );
				break;
			case 2:  // Next page
				document->nextPage();
				eyeOSD.setCurrPage ( document->getNumPage() );
				eyeDrawWidget->drawPage ( document->getImage() );
				break;
			case 3:  // Go to page - not implemented yet
				break;
			case 4:  // Zoom
				spinBox->setValue ( document->getZoom() );
				slider ->setValue ( document->getZoom() );
				miscWidget->setVisible ( !miscWidget->isVisible() );
				break;
		}
}

void Eyepiece::disableRotateActions()
{
	rotateAction0->setEnabled ( false );
	rotateAction90->setEnabled ( false );
	rotateAction180->setEnabled ( false );
	rotateAction270->setEnabled ( false );
}


void Eyepiece::enableRotateActions()
{
	rotateAction0->setEnabled ( true );
	rotateAction90->setEnabled ( true );
	rotateAction180->setEnabled ( true );
	rotateAction270->setEnabled ( true );
}


void Eyepiece::setDocument ( const QString & filename )
{
	if ( loadPlugin() )
	{
		eyeDrawWidget->setMessage ( "" );
		enableRotateActions();
		if ( !document->openDocument ( filename ) )
		{
			onDocumentLoadError();
		}
		else
		{
			eyeOSD.setCurrPage ( 0 );
			eyeOSD.setDocActive ( true );
			eyeStackedWidget->setCurrentWidget ( viewPage );
			eyeDrawWidget->drawPage ( document->getImage() );
		}
	}
	else
	{
		eyeDrawWidget->setMessage ( "Error: cannot load plugin" ); // TODO: plugin name
		eyeStackedWidget->setCurrentWidget ( viewPage );
	}
}


// -------------- LOAD PLUGIN -------------------
// TODO: refine code

bool Eyepiece::loadPlugin()
{
	if ( document && contentID == oldContID ) return true;
	oldContID = contentID;

	unloadPlugin();

	QDir pluginDirectory ( qApp->applicationDirPath() );
	qWarning() << qApp->applicationDirPath();
          
        QString fName;
	if ( contentID == mime_pdf )        // TODO: refine
        {
                fName = "libpdfplugin.so";
        }
	else if ( contentID == mime_djvu )
                fName = "libdjvuplugin.so";
	else
		return false;
        QString fPath1 = qApp->applicationDirPath() + "/../plugins/eyepiece/";
        QString fPath2 = qApp->applicationDirPath() + "/plugins/";
        QString fileName;
        if (QFile::exists(fPath1 + fName))
            fileName = fPath1 + fName;
        else
            fileName = fPath2 + fName;

	qWarning() << fileName;
	//pluginLoader = new QPluginLoader ( pluginDirectory.absoluteFilePath ( fileName ) );
	pluginLoader.setFileName ( pluginDirectory.absoluteFilePath ( fileName ) );
	plugin = pluginLoader.instance();

	if ( plugin )
	{
		qWarning() << "pluginloader - OK";

		document = qobject_cast<Document *> ( plugin );

		qWarning() << "document - " << ( bool ) document;

		if ( document ) return true;
	}
	return false;
}


void Eyepiece::unloadPlugin()
{
// 	if ( pluginLoader )
// 	{
	if ( pluginLoader.isLoaded() )
	{
		qWarning() << "Unload plugin: " << contentID << pluginLoader.unload();
		//delete pluginLoader;
		document = NULL;
	}
// 	}
}

bool Eyepiece::event(QEvent *event)
{
    if(event->type() == QEvent::WindowDeactivate)
    {
        if (libCheckPassed) lower();
    }
    else if(event->type() == QEvent::WindowActivate)
    {
        QString title = windowTitle();
        setWindowTitle(QLatin1String("_allow_on_top_"));
        raise();
        setWindowTitle(title);

        this->update();
    }
    else if(event->type() == QEvent::Close)
    {
        if (libCheckPassed)
            setAutoRotate(false);
        else
        {
            event->ignore();
            return true;
        }
    }

    return QWidget::event(event);
}
