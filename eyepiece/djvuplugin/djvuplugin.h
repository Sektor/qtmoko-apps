#ifndef DJVUPLUGIN_H
#define DJVUPLUGIN_H

#include <QObject>
#include <QImage>
#include <QContent>
#include <QSize>
#include <libdjvu/ddjvuapi.h>

#include "document.h"

class DJVUDocument : public QObject, Document
{
		Q_OBJECT
		Q_INTERFACES ( Document );
	public:
		DJVUDocument();
		~DJVUDocument();

		QImage * getImage();
		bool     nextPage();
		bool     prevPage();
		void     firstPage();
		void     lastPage();
		int      getNumPage();
		void     setZoom ( int );
		int      getZoom();

		bool openDocument ( const QString & fileName );

		// TODO:
		//bool goToPage( int page );
		//int  getNumPage();
		//int  getNumPages();

	private:
		int      currPage; // The number of the current page, first is 0
		//int    numPages; // The number of pages in the document
		QImage * image;    // Here is the current rendered page
		uchar  * imageBuf; // Image buffer
		int      zoom;     // Zoom im percent ?

		DDJVUAPI ddjvu_context_t  * context;    // This object holds global data structures such as the cache of decoded pages, or the list of pending event messages
		DDJVUAPI ddjvu_document_t * document;   // is a subclass of <ddjvu_job_t>
		ddjvu_page_t              * page;       // Each page of a document can be accessed by creating a <ddjvu_page_t> object
		ddjvu_rect_t                rendRect;   // Members: <x>, <y>, <w>, <h>
		ddjvu_rect_t                pageRect;
		ddjvu_format_t            * format;     // describes a pixel format
		int                         row_stride; // physical row width in output buffer

		void handle_ddjvu_messages ( ddjvu_context_t * ctx, int wait );
		void clean();

		void renderPage();
};

#endif
