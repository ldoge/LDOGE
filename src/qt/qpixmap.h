/****************************************************************************
** $Id:  qt/qpixmap.h   3.0.5   edited Oct 17 2001 $
**
** Definition of QPixmap class
**
** Created : 940501
**
** Copyright (C) 1992-2000 Trolltech AS.  All rights reserved.
**
** This file is part of the kernel module of the Qt GUI Toolkit.
**
** This file may be distributed under the terms of the Q Public License
** as defined by Trolltech AS of Norway and appearing in the file
** LICENSE.QPL included in the packaging of this file.
**
** This file may be distributed and/or modified under the terms of the
** GNU General Public License version 2 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.
**
** Licensees holding valid Qt Enterprise Edition or Qt Professional Edition
** licenses may use this file in accordance with the Qt Commercial License
** Agreement provided with the Software.
**
** This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
** WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
**
** See http://www.trolltech.com/pricing.html or email sales@trolltech.com for
**   information about Qt Commercial License Agreements.
** See http://www.trolltech.com/qpl/ for QPL licensing information.
** See http://www.trolltech.com/gpl/ for GPL licensing information.
**
** Contact info@trolltech.com if any conditions of this licensing are
** not clear to you.
**
**********************************************************************/

#ifndef QPIXMAP_H
#define QPIXMAP_H

#ifndef QT_H
#include "qpaintdevice.h"
#include "qcolor.h" // char*->QColor conversion
#include "qstring.h" // char*->QString conversion
#include "qnamespace.h"
#endif // QT_H

class QGfx;
class QPixmapPrivate;

#if defined(Q_WS_WIN)
// Internal pixmap memory optimization class for Windows 9x
class QMultiCellPixmap;
#endif


class Q_EXPORT QPixmap : public QPaintDevice, public Qt
{
public:
    enum ColorMode { Auto, Color, Mono };
    enum Optimization { DefaultOptim, NoOptim, MemoryOptim=NoOptim,
			NormalOptim, BestOptim };

    QPixmap();
    QPixmap( const QImage& image );
    QPixmap( int w, int h,  int depth = -1, Optimization = DefaultOptim );
    QPixmap( const QSize &, int depth = -1, Optimization = DefaultOptim );
#ifndef QT_NO_IMAGEIO
    QPixmap( const QString& fileName, const char *format=0,
	     ColorMode mode=Auto );
    QPixmap( const QString& fileName, const char *format,
	     int conversion_flags );
    QPixmap( const char *xpm[] ); // ### in 4.0, 'const char * const xpm[]'?
    QPixmap( const QByteArray &data );
#endif
    QPixmap( const QPixmap & );
   ~QPixmap();

    QPixmap    &operator=( const QPixmap & );
    QPixmap    &operator=( const QImage	 & );

    bool	isNull()	const;

    int		width()		const { return data->w; }
    int		height()	const { return data->h; }
    QSize	size()		const { return QSize(data->w,data->h); }
    QRect	rect()		const { return QRect(0,0,data->w,data->h); }
    int		depth()		const { return data->d; }
    static int	defaultDepth();

    void	fill( const QColor &fillColor = Qt::white );
    void	fill( const QWidget *, int xofs, int yofs );
    void	fill( const QWidget *, const QPoint &ofs );
    void	resize( int width, int height );
    void	resize( const QSize & );

    const QBitmap *mask() const;
    void	setMask( const QBitmap & );
    bool	selfMask() const;
#ifndef QT_NO_IMAGE_HEURISTIC_MASK
    QBitmap	createHeuristicMask( bool clipTight = TRUE ) const;
#endif
    static  QPixmap grabWindow( WId, int x=0, int y=0, int w=-1, int h=-1 );
    static  QPixmap grabWidget( QWidget * widget,
				int x=0, int y=0, int w=-1, int h=-1 );

#ifndef QT_NO_PIXMAP_TRANSFORMATION
    QPixmap	    xForm( const QWMatrix & ) const;
    static QWMatrix trueMatrix( const QWMatrix &, int w, int h );
#endif

    QImage	convertToImage() const;
    bool	convertFromImage( const QImage &, ColorMode mode=Auto );
    bool	convertFromImage( const QImage &, int conversion_flags );
#ifndef QT_NO_IMAGEIO
    static const char* imageFormat( const QString &fileName );
    bool	load( const QString& fileName, const char *format=0,
		      ColorMode mode=Auto );
    bool	load( const QString& fileName, const char *format,
		      int conversion_flags );
    bool	loadFromData( const uchar *buf, uint len,
			      const char* format=0,
			      ColorMode mode=Auto );
    bool	loadFromData( const uchar *buf, uint len,
			      const char* format,
			      int conversion_flags );
    bool	loadFromData( const QByteArray &data,
			      const char* format=0,
			      int conversion_flags=0 );
    bool	save( const QString& fileName, const char* format, int quality = -1 ) const;
#endif

#if defined(Q_WS_WIN)
    HBITMAP	hbm()		const;
#endif

    int		serialNumber()	const;

    Optimization	optimization() const;
    void		setOptimization( Optimization );
    static Optimization defaultOptimization();
    static void		setDefaultOptimization( Optimization );

    virtual void detach();

    bool	isQBitmap() const;

#if defined(Q_WS_WIN)
    // These functions are internal and used by Windows 9x only
    bool	isMultiCellPixmap() const;
    HDC		multiCellHandle() const;
    HBITMAP	multiCellBitmap() const;
    int		multiCellOffset() const;
    int		allocCell();
    void	freeCell( bool = FALSE );
#endif

#if defined(Q_WS_QWS)
    virtual QGfx * graphicsContext(bool clip_children=TRUE) const;
    virtual unsigned char * scanLine(int) const;
    virtual int bytesPerLine() const;
    QRgb * clut() const;
    int numCols() const;
#elif defined(Q_WS_X11)
    static int x11SetDefaultScreen( int screen );
    void x11SetScreen( int screen );
#endif

#if defined(Q_FULL_TEMPLATE_INSTANTIATION)
    bool operator==( const QPixmap& ) const { return FALSE; }
#endif

protected:
    QPixmap( int w, int h, const uchar *data, bool isXbitmap );
    int metric( int ) const;

#if defined(Q_WS_WIN)
    struct QMCPI {				// mem optim for win9x
	QMultiCellPixmap *mcp;
	int	offset;
    };
#endif

    struct QPixmapData : public QShared {	// internal pixmap data
	QCOORD	w, h;
	short	d;
	uint	uninit	 : 1;
	uint	bitmap	 : 1;
	uint	selfmask : 1;
#if defined(Q_WS_WIN)
	uint	mcp	 : 1;
#endif
	int	ser_no;
	QBitmap *mask;
#if defined(Q_WS_WIN)
	void   *bits;
	QPixmap *maskpm;
	union {
	    HBITMAP hbm;    // if mcp == FALSE
	    QMCPI  *mcpi;   // if mcp == TRUE
	} hbm_or_mcpi;
	bool hasRealAlpha;
#elif defined(Q_WS_X11)
	void   *ximage;
	void   *maskgc;
	QPixmap *alphapm;
#elif defined(Q_WS_MAC)
	ColorTable *clut;
#elif defined(Q_WS_QWS)
	int id; // ### should use QPaintDevice::hd, since it is there
	QRgb * clut;
	int numcols;
	int rw;
	int rh;
	bool hasAlpha;
#endif
	Optimization optim;
    } *data;
private:
    QPixmap( int w, int h, int depth, bool, Optimization );
    void	init( int, int, int, bool, Optimization );
    void	deref();
    QPixmap	copy( bool ignoreMask = FALSE ) const;
    static Optimization defOptim;
    friend Q_EXPORT void bitBlt( QPaintDevice *, int, int,
				 const QPaintDevice *,
				 int, int, int, int, RasterOp, bool );
    friend Q_EXPORT void bitBlt( QPaintDevice *, int, int,
				 const QImage* src,
				 int, int, int, int, int conversion_flags );

#if defined(Q_WS_X11) && !defined(QT_NO_XRENDER)
    friend void qt_x11_copy_alpha_pixmap(QPixmap *dst, const QPixmap *src);
    friend void qt_x11_blit_alpha_pixmap(QPixmap *dst, int dx, int dy,
					 const QPixmap *src, int sx = 0, int sy = 0,
					 int sw = -1, int sh = -1);
#endif

    friend class QBitmap;
    friend class QPaintDevice;
    friend class QPainter;
};


inline bool QPixmap::isNull() const
{
    return data->w == 0;
}

inline void QPixmap::fill( const QWidget *w, const QPoint &ofs )
{
    fill( w, ofs.x(), ofs.y() );
}

inline void QPixmap::resize( const QSize &s )
{
    resize( s.width(), s.height() );
}

inline const QBitmap *QPixmap::mask() const
{
    return data->mask;
}

inline bool QPixmap::selfMask() const
{
    return data->selfmask;
}

#if defined(Q_WS_WIN)
inline HBITMAP QPixmap::hbm() const
{
    return data->mcp ? 0 : data->hbm_or_mcpi.hbm;
}
#endif

inline int QPixmap::serialNumber() const
{
    return data->ser_no;
}

inline QPixmap::Optimization QPixmap::optimization() const
{
    return data->optim;
}

inline bool QPixmap::isQBitmap() const
{
    return data->bitmap;
}

#if defined(Q_WS_WIN)
inline bool QPixmap::isMultiCellPixmap() const
{
    return data->mcp;
}
#endif


/*****************************************************************************
  QPixmap stream functions
 *****************************************************************************/

#if !defined(QT_NO_DATASTREAM) && !defined(QT_NO_IMAGEIO)
Q_EXPORT QDataStream &operator<<( QDataStream &, const QPixmap & );
Q_EXPORT QDataStream &operator>>( QDataStream &, QPixmap & );
#endif

/*****************************************************************************
  QPixmap (and QImage) helper functions
 *****************************************************************************/

#ifndef QT_NO_PIXMAP_TRANSFORMATION
#  define QT_XFORM_TYPE_MSBFIRST 0
#  define QT_XFORM_TYPE_LSBFIRST 1
#  if defined(Q_WS_WIN)
#    define QT_XFORM_TYPE_WINDOWSPIXMAP 2
#  endif
bool qt_xForm_helper( const QWMatrix&, int, int, int, uchar*, int, int, int, uchar*, int, int, int );
#endif

#endif // QPIXMAP_H
