#ifndef NEOITEMSETLISTOPTION_TEST_
#define NEOITEMSETLISTOPTION_TEST_

#include <iostream>
#include <windows.h>

#include "../../EngineLib/G-Logic/GLDefine.h"

struct SIDSETITEMLIST
{
	float	fMainID;
	float	fSubID;
	SIDSETITEMLIST(): fMainID( 0.f )
					, fSubID( 0.f )
	{
	}
};

struct SPARTOPTION
{
	DWORD	dwContPart;
	DWORD	dwType;
	DWORD	dwValue;
	SPARTOPTION() : dwContPart( 0 )
					, dwType( 0 )
					, dwValue( 0 )
	{
	}
};
/*
struct SItemSetListOption
{
	SIDSETITEMLIST	m_slot_headgear;
	SIDSETITEMLIST	m_slot_upper;
	SIDSETITEMLIST	m_slot_lower;
	SIDSETITEMLIST	m_slot_hand;
	SIDSETITEMLIST	m_slot_foot;
	SIDSETITEMLIST	m_slot_rhand;
	SIDSETITEMLIST	m_slot_lhand;
	SIDSETITEMLIST	m_slot_neck;
	SIDSETITEMLIST	m_slot_wrist;
	SIDSETITEMLIST	m_slot_rfinger;
	SIDSETITEMLIST	m_slot_lfinger;
	SIDSETITEMLIST	m_slot_rhand_s;
	SIDSETITEMLIST	m_slot_lhand_s;
	SIDSETITEMLIST	m_slot_vehicle;
};
*/
class CItemSetListsOption
{
public:
	enum
	{
		SLOT_HEADGEAR			=		0,
		SLOT_UPPER ,
		SLOT_LOWER ,
		SLOT_HAND ,
		SLOT_FOOT ,
		SLOT_RHAND ,
		SLOT_LHAND ,
		SLOT_NECK ,
		SLOT_WRIST ,
		SLOT_RFINGER ,
		SLOT_LFINGER ,
		SLOT_RHAND_S ,
		SLOT_LHAND_S ,
		SLOT_VEHICLE ,
		SLOT_WING ,
		SLOT_BELT ,	//  Å»°Í 
		SLOT_REARRING ,	//
		SLOT_LEARRING ,	//
		SLOT_ACCESSORY ,	//
		SLOT_MAX ,
	};
	enum
	{
		MAX_PIECE_TYPE			=		19,
		MAX_PARTOPTION_TYPE		=		13,
	};
public:
	//SItemSetListOption		m_sItemSetLists;
	SIDSETITEMLIST			m_sItemSetLists[MAX_PIECE_TYPE];
	SPARTOPTION				m_sPartOption[ MAX_PARTOPTION_TYPE ];
	DWORD					m_dwPartCount;

public:
	BOOL					Load( const std::string & strFileName );

public:
	CItemSetListsOption();
	~CItemSetListsOption();

};

#endif