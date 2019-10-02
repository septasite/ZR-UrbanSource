#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"
#include "../RanClientLib/G-Logic/GLContrlServerMsg.h"
#include "../RanClientLib/G-Logic/GLItemMan.h"
#include "LargeMapWindowCheckBox.h"

class CBasicScrollBarEx;
class CLargeMapWindowCheckBox;
class CLargeMapWindowMob : public CUIGroup
{
private:
static	const	int	nSTARTLINE;
static	const	int	nOUTOFRANGE;

protected:
	enum
	{
		nONE_VIEW_SLOT_DEFAULT = 10,
		nMAX_ONE_VIEW_SLOT = 10,
	};
	
	enum
	{
		CROW_SLOT0 = NO_ID + 1,
		CROW_SLOT1,
		CROW_SLOT_END = CROW_SLOT0 + MAXCROW,
		CROW_MAIN,
	};

public:
	CLargeMapWindowMob ();
	virtual	~CLargeMapWindowMob ();
	void CreateSubControl();
	virtual	void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID cID, DWORD dwMsg );

protected:
	CLargeMapWindowCheckBox*	m_pMobMain;
	CLargeMapWindowCheckBox*	m_pMob[MAXCROW];
	CUIControl*					m_pMobArrayDummy[nMAX_ONE_VIEW_SLOT];

	int							m_nONE_VIEW_SLOT;
	CBasicScrollBarEx*			m_pScrollBar;
	int							m_nCurPos;
	int							m_nIndex;

public:
	void LoadMob (NET_MSG_GENERIC* nmg);
	void ClearMobList();

	CUIControl*	CreateControl ( const char* szControl );
	CLargeMapWindowCheckBox*	CreateMobSlot ( CString strKeyword, UIGUID ControlID );

	void SetCrowRender ( int nStartIndex, int nTotal );
	void ResetAllCrowRender ( int nTotal );

	SNATIVEID					m_sNativeID[MAXCROW];

	BOOL						IsChecked(int nIndex) { return m_pMob[nIndex]->IsChecked(); }

	int							GetTotalCrow() { return m_nIndex; }
};