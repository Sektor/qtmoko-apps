#ifndef DOCUMENT_H
#define DOCUMENT_H

class QString;

class Document
{
	public:
		virtual ~Document() {}

		virtual QImage * getImage()                                = 0;
		virtual bool     nextPage()                                = 0;
		virtual bool     prevPage()                                = 0;
		virtual void     firstPage()                               = 0;
		virtual void     lastPage()                                = 0;
		virtual int      getNumPage()                              = 0;
		virtual void     setZoom ( int )                           = 0;
		virtual int      getZoom()                                 = 0;
		virtual bool     openDocument ( const QString & fileName ) = 0;

		// TODO:
		//virtual bool goToPage( int page ) = 0;
		//virtual int  getNumPages() = 0;
};

Q_DECLARE_INTERFACE ( Document, "org.eyepiece-viewer.ImgPlugin.DocInterface/0.1" );

#endif
