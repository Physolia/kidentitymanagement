#ifndef KABC_RESOURCEDIR_H
#define KABC_RESOURCEDIR_H

#include <kconfig.h>
#include <kdirwatch.h>

#include <sys/types.h>

#include "resource.h"

class QTimer;

namespace KABC {

class Format;

/**
  @internal
*/
class ResourceDir : public QObject, public Resource
{
    Q_OBJECT
  public:
    ResourceDir( AddressBook *, const KConfig * );
    ResourceDir( AddressBook *, const QString &filename, Format *format=0 );
    ~ResourceDir();
  
    bool open();
    void close();
  
    Ticket *requestSaveTicket();

    bool load();
    bool save( Ticket * );

    /**
      Set path to be used for saving.
    */
    void setPath( const QString & );
    /**
      Return path used for loading and saving the address book.
    */
    QString path() const;

    virtual QString identifier() const;

    /**
      Remove a addressee from its source.
      This method is mainly called by KABC::AddressBook.
     */
    void removeAddressee( const Addressee& addr );
	
  protected slots:
    void pathChanged();

  protected:
    bool lock( const QString &path );
    void unlock( const QString &path );

  private:
    void init( const QString &path, Format *format );

    Format *mFormat;

    KDirWatch mDirWatch;

    QString mPath;
    QString mLockUniqueName;
};

}

#endif
