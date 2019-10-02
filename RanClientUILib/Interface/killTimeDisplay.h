#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"
#include "GLCharData.h"

class	CkillTimeDisplay : public CUIGroup
{
private:
	enum
	{
		KILLTIME_DUMMY_BASE = NO_ID + 1,
		KILLTIME_DUMMY_SIZE = 5,
		KILLTIME_UNIT = 1000,
		KILLTIME_UNIT_END = KILLTIME_UNIT + 10000,
	};

public:
	CkillTimeDisplay ();
	virtual	~CkillTimeDisplay ();

public:
	void	CreateSubControl ();

	
	bool	NEW_PLAY_KILL (const DWORD& dwID, const DWORD& dwClassKilled , const DWORD& dwClassKiller , const CString &strKilled , const CString &strKiller ,const DWORD& nSchoolKilled , const DWORD& nSchoolKiller);


public:
	virtual HRESULT InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );
	virtual	void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

private:
	typedef	std::pair<DWORD,UIGUID>			KILLTIME_PAIR;
	typedef	std::list<KILLTIME_PAIR>		KILLTIME_DISPLAY_LIST;
	typedef	KILLTIME_DISPLAY_LIST::iterator	KILLTIME_DISPLAY_LIST_ITER;

	KILLTIME_DISPLAY_LIST	m_killPlayList;
	UIGUID	m_NEWID;
	float	m_fTimer;

	LPDIRECT3DDEVICEQ	m_pd3dDevice;

private:
	CUIControl*		m_pkillUnitDummy[KILLFACT_SIZE];

public:

	DWORD m_dwSLOT;
	SNATIVEID sKILLID[KILLFACT_SIZE];
	void SetkillSlot( DWORD dwSlot ) { m_dwSLOT = dwSlot; }
	DWORD GetkillSlot() { return m_dwSLOT; } 
	SNATIVEID GetkillSlotID( DWORD dwSlot ) { return sKILLID[dwSlot]; }
};