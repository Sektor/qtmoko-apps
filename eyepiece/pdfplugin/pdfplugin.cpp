#include "pdfplugin.h"

#include <QtPlugin>

#include <QtDebug>

/**
 * Constructor
 */
PDFDocument::PDFDocument() :
		currPage ( 0 ),
		image ( NULL ),
		zoom ( 40 ),
		poppDocument ( NULL ),
		poppPage ( NULL )
{
}


/**
 * Destructor
 */
PDFDocument::~PDFDocument()
{
	if ( poppPage ) delete poppPage;
	if ( poppDocument ) delete poppDocument;
	if ( image ) delete image;
}


QImage * PDFDocument::getImage()
{
	return image;
}


/**
 * Renders current page to the memory, but not to the screen
 */
void PDFDocument::RenderPage()
{
	// Access page of the PDF file
	poppPage = poppDocument->page ( currPage ); // Document starts at page 0
	if ( !poppPage )
	{
		image = NULL;
		qWarning() << "Cannot open page";
		return;
	}

	if ( image ) delete image;
	// Generate a QImage of the rendered page
	image = new QImage ( poppPage->renderToImage
	                     ( zoom * 72.0 / 100.0, zoom * 72.0 / 100.0, -1, -1, -1, -1 ) );
	if ( image->isNull() )
	{
		qWarning() << "Cannot render page";
		return;
	}
}

/**
 * Go to next page and draw it
 * @return true if page is not last
 */
bool PDFDocument::nextPage()
{
	if ( image && currPage < poppDocument->numPages() - 1 )
	{
		currPage++;
		RenderPage();
		return true;
	}
	return false;
}

/**
 * Go to previous page and draw it
 * @return true if page is not first
 */
bool PDFDocument::prevPage()
{
	if ( image && currPage > 0 )
	{
		currPage--;
		RenderPage();
		return true;
	}
	return false;
}

/**
 * Go to first page and draw it
 */
void PDFDocument::firstPage()
{
	if ( image && currPage )
	{
		currPage = 0;
		RenderPage();
	}
}

/**
 * Go to last page and draw it
 */
void PDFDocument::lastPage()
{
	if ( image && currPage != poppDocument->numPages() - 1 )
	{
		currPage = poppDocument->numPages() - 1;
		RenderPage();
	}
}

/**
 * Gets number of current page
 * @return 
 */
int PDFDocument::getNumPage()
{
	return currPage;
}

/**
 *  Opens document
 * @param content
 */
bool PDFDocument::openDocument ( const QString & fileName )
{
	poppDocument = Poppler::Document::load ( fileName );
	if ( !poppDocument || poppDocument->isLocked() )
	{
		delete poppDocument;
		image = NULL;
		return false;
	}

	currPage = 0;

	// TODO: add this to preferences
	poppDocument->setRenderHint ( Poppler::Document::TextAntialiasing );
	poppDocument->setRenderHint ( Poppler::Document::Antialiasing );

	RenderPage();
	return true;
}


/**
 * Zooming
 * @param _zoom
 */
void PDFDocument::setZoom ( int _zoom )
{
	if ( image )
	{
		zoom = _zoom;
		RenderPage();
	}
}


/**
 * Getting zoom value
 * @return zoom value
 */
int PDFDocument::getZoom()
{ return zoom; }


Q_EXPORT_PLUGIN2 ( pdfplugin, PDFDocument );
