#ifndef NEOITEMSETLIST_TEST_
#define NEOITEMSETLIST_TEST_

#include <iostream>
#include <windows.h>

#include "../../EngineLib/G-Logic/GLDefine.h"

#include "CItemSetListOption.h"

typedef std::list<std::string>		STRING_LIST;
typedef STRING_LIST::iterator		STRING_LIST_ITER;

class CItemSetLists
{
public:
	typedef std::list<CItemSetListsOption*>		ITEMSETLISTOPTION_LIST;
	typedef ITEMSETLISTOPTION_LIST::iterator	ITEMSETLISTOPTION_LIST_ITER;
public:
	ITEMSETLISTOPTION_LIST	m_listItemSet;
	STRING_LIST				m_listFileName;

public:
	BOOL					FindData( SNATIVEID sNATIVEID );

public:
	BOOL					LoadDataSet( );

public:
	CItemSetLists();
	~CItemSetLists();

public:
	static CItemSetLists& GetInstance ();

};

#endif