/****************************************************************************
** $Id:  qt/qobject.h   3.0.5   edited Feb 4 07:26 $
**
** Definition of QObject class
**
** Created : 930418
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

#ifndef QOBJECT_H
#define QOBJECT_H

#ifndef QT_H
#include "qobjectdefs.h"
#include "qwindowdefs.h"
#include "qstring.h"
#include "qevent.h"
#include "qnamespace.h"
#endif // QT_H

#define QT_TR_NOOP(x) (x)
#define QT_TRANSLATE_NOOP(scope,x) (x)

class QMetaObject;
class QVariant;
class QMetaProperty;
class QPostEventList;
class QObjectPrivate;
struct QUObject;

class Q_EXPORT QObject: public Qt
{
    Q_OBJECT
    Q_PROPERTY( QCString name READ name WRITE setName )

public:
    QObject( QObject *parent=0, const char *name=0 );
    virtual ~QObject();

#ifdef Q_QDOC
    const char *className() const;
    QString tr( const char *, const char * ) const;
    QString trUtf8( const char *, const char * ) const;
    QMetaObject *metaObject() const;
#endif

    virtual bool event( QEvent * );
    virtual bool eventFilter( QObject *, QEvent * );

    bool	 isA( const char * )	 const;
    bool	 inherits( const char * ) const;

    const char  *name() const;
    const char  *name( const char * defaultName ) const;

    virtual void setName( const char *name );
    bool	 isWidgetType()	  const { return isWidget; }
    bool	 highPriority()	  const { return FALSE; }

    bool	 signalsBlocked()  const { return blockSig; }
    void	 blockSignals( bool b );

    int		 startTimer( int interval );
    void	 killTimer( int id );
    void	 killTimers();

    QObject           *child( const char *objName, const char *inheritsClass = 0, bool recursiveSearch = TRUE ); //### const in 4.0
    const QObjectList *children() const { return childObjects; }

    static const QObjectList *objectTrees();

    QObjectList	      *queryList( const char *inheritsClass = 0,
				  const char *objName = 0,
				  bool regexpMatch = TRUE,
				  bool recursiveSearch = TRUE ) const;

    virtual void insertChild( QObject * );
    virtual void removeChild( QObject * );

    void	 installEventFilter( const QObject * );
    void	 removeEventFilter( const QObject * );

    static bool  connect( const QObject *sender, const char *signal,
			  const QObject *receiver, const char *member );
    bool	 connect( const QObject *sender, const char *signal,
			  const char *member ) const;
    static bool  disconnect( const QObject *sender, const char *signal,
			     const QObject *receiver, const char *member );
    bool	 disconnect( const char *signal=0,
			     const QObject *receiver=0, const char *member=0 );
    bool	 disconnect( const QObject *receiver, const char *member=0 );
    static void 	 connectInternal( const QObject *sender, int signal_index, const QObject *receiver,
				  int membcode, int member_index );

    void	 dumpObjectTree();
    void	 dumpObjectInfo();

#ifndef QT_NO_PROPERTIES
    virtual bool setProperty( const char *name, const QVariant& value );
    virtual QVariant property( const char *name ) const;
#endif // QT_NO_PROPERTIES
#ifdef QT_NO_TRANSLATION
    static QString tr( const char *sourceText, const char * = 0);
#ifndef QT_NO_TEXTCODEC
    static QString trUtf8( const char *sourceText, const char * = 0);
#endif
#endif //QT_NO_TRANSLATION

signals:
    void	 destroyed();
    void	 destroyed( QObject* obj );

public:
    QObject	*parent() const { return parentObj; }

public slots:
    void	deleteLater();

private slots:
    void	 cleanupEventFilter( QObject* );

protected:
    bool	activate_filters( QEvent * );
    QConnectionList *receivers( const char* signal ) const;
    QConnectionList *receivers( int signal ) const;
    void	activate_signal( int signal );
    void	activate_signal( int signal, int );
    void	activate_signal( int signal, double );
    void	activate_signal( int signal, QString );
    void	activate_signal_bool( int signal, bool );
    void 	activate_signal( QConnectionList *clist, QUObject *o );

    const QObject *sender();

    virtual void timerEvent( QTimerEvent * );
    virtual void childEvent( QChildEvent * );
    virtual void customEvent( QCustomEvent * );

    virtual void connectNotify( const char *signal );
    virtual void disconnectNotify( const char *signal );
    virtual bool checkConnectArgs( const char *signal, const QObject *receiver,
				   const char *member );
    static QCString normalizeSignalSlot( const char *signalSlot );

private:
    uint	isSignal   : 1;
    uint	isWidget   : 1;
    uint	pendTimer  : 1;
    uint	blockSig   : 1;
    uint	wasDeleted : 1;
    uint	isTree : 1;

    const char	*objname;
    QObject	*parentObj;
    QObjectList *childObjects;
    QSignalVec *connections;
    QObjectList *senderObjects;
    QObjectList *eventFilters;
    QPostEventList *postedEvents;
    QObjectPrivate* d;

    static QMetaObject* staticQtMetaObject();

    friend class QApplication;
    friend class QBaseApplication;
    friend class QWidget;
    friend class QSignal;
    friend class QSenderObject;

private:	// Disabled copy constructor and operator=
#if defined(Q_DISABLE_COPY)
    QObject( const QObject & );
    QObject &operator=( const QObject & );
#endif
};


inline bool QObject::connect( const QObject *sender, const char *signal,
			      const char *member ) const
{
    return connect( sender, signal, this, member );
}


inline bool QObject::disconnect( const char *signal,
				 const QObject *receiver, const char *member )
{
    return disconnect( this, signal, receiver, member );
}


inline bool QObject::disconnect( const QObject *receiver, const char *member )
{
    return disconnect( this, 0, receiver, member );
}


class Q_EXPORT QSenderObject : public QObject		// object for sending signals
{
public:
    void setSender( QObject *s );
};

#ifdef QT_NO_TRANSLATION
inline QString QObject::tr( const char *sourceText, const char * ) {
    return QString::fromLatin1( sourceText );
}
#ifndef QT_NO_TEXTCODEC
inline QString QObject::trUtf8( const char *sourceText, const char * ) {
    return QString::fromUtf8( sourceText );
}
#endif
#endif //QT_NO_TRANSLATION



#endif // QOBJECT_H
