/*
    This file is part of libkabc.
    Copyright (c) 2002 Tobias Koenig <tokoe@kde.org>

    This library is free software; you can redistribute it and/or
    modify it under the terms of the GNU Library General Public
    License as published by the Free Software Foundation; either
    version 2 of the License, or (at your option) any later version.

    This library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
    Library General Public License for more details.

    You should have received a copy of the GNU Library General Public License
    along with this library; see the file COPYING.LIB.  If not, write to
    the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
    Boston, MA 02111-1307, USA.
*/

#include <klocale.h>
#include <kbuttonbox.h>

#include <qgroupbox.h>
#include <qlayout.h>

#include "resourcedlg.h"

using namespace KABC;

ResourceDlg::ResourceDlg( AddressBook *ab, QWidget *parent, const char *name )
    : KDialog( parent, name, true )
{
    setCaption( i18n( "Resource Selection" ) );
    resize( 300, 200 );

    QVBoxLayout *mainLayout = new QVBoxLayout( this );
    mainLayout->setMargin( marginHint() );
    
    QGroupBox *groupBox = new QGroupBox( 2, Qt::Horizontal,  this );
    groupBox->setTitle( i18n( "Resources" ) );

    mResourceId = new KListBox( groupBox );

    mainLayout->addWidget( groupBox );

    mainLayout->addSpacing( 10 );

    KButtonBox *buttonBox = new KButtonBox( this );

    buttonBox->addStretch();    
    buttonBox->addButton( i18n( "&Apply" ), this, SLOT( accept() ) );
    buttonBox->addButton( i18n( "&Cancel" ), this, SLOT( reject() ) );
    buttonBox->layout();

    mainLayout->addWidget( buttonBox );


    // setup listbox
    uint counter = 0;
    QPtrList<Resource> list = ab->resources();
    for ( uint i = 0; i < list.count(); ++i ) {
	Resource *resource = list.at( i );
	if ( resource && !resource->readOnly() ) {
	    mResourceMap.insert( counter, resource );
	    mResourceId->insertItem( resource->name() + " " +
		    ( resource->fastResource() ? i18n( "(search)" ) : "" ) );
	    counter++;
	}
    }

    mResource = 0;

    mResourceId->setCurrentItem( 0 );
}

Resource *ResourceDlg::exec()
{
    QDialog::exec();
    return mResource;
}

void ResourceDlg::accept()
{
    if ( mResourceId->currentItem() != -1 )
	mResource = mResourceMap[ mResourceId->currentItem() ];
    else
	mResource = 0;

    QDialog::accept();
}

#include "resourcedlg.moc"
