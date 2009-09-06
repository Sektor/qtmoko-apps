#ifndef PDFPLUGIN_H
#define PDFPLUGIN_H

#include <QObject>
#include <QImage>
#include <QContent>
#include <QSize>
#include <poppler-qt4.h>

#include "document.h"

class PDFDocument : public QObject, Document
{
		Q_OBJECT
		Q_INTERFACES ( Document );
	public:
		PDFDocument();
		~PDFDocument();

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
		int      zoom;     // Zoom im percent ?

		Poppler::Document * poppDocument;
		Poppler::Page     * poppPage;

		void RenderPage();
};

#endif
