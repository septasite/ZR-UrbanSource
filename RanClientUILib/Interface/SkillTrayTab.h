#pragma once

#include "../EngineUILib/GUInterface/UIGroup.h"
#include "SkillTrayTab.h"
#include "BasicQuickSkillSlot.h"

const INT MAX_TAB_INDEX = 4;
const INT QUICK_SKILL_SLOT_MAX = 10;
const DWORD UIMSG_BASIC_LBDUP = UIMSG_USER1;

class CBasicSkillTray;
class CBasicTextButton;
class CBasicButton;
class CBasicTextBox;
class CBasicQuickSkillSlotEx;
class CBasicQuickSkillSlot;

class CSkillTrayTab : public CUIGroup
{
	static INT NEXT_INDEX[MAX_TAB_INDEX];

public:
	enum
	{
		BASIC_QUICK_SKILL_TRAY_F1 = NO_ID + 1,
		BASIC_QUICK_SKILL_TRAY_F2,
		BASIC_QUICK_SKILL_TRAY_F3,
		BASIC_QUICK_SKILL_TRAY_F4,
		TEXT_BUTTON_CLICK,
		BASIC_LEVEL_DISPLAY,
		QUICK_SKILL_TRAY_CLOSE_BUTTON,
		QUICK_SKILL_TRAY_ROTATE_BUTTON,
		QUICK_SKILL_TRAY_LOCK_BUTTON,
		QUICK_SKILL_TRAY_UNLOCK_BUTTON,
	};

	enum
	{
		TABBUTTON_FOLDGROUP_ID = 1
	};

public:
	void CreateSubControl();
	void CheckMouseState();

	BOOL		m_bFirstGap;
	D3DXVECTOR2	m_vGap;

	int			m_PosX;
	int			m_PosY;

	bool		m_bCHECK_MOUSE_STATE;
	BOOL		TabLock;

	void SetTabIndex( INT nIndex )			{ GASSERT( 0 <= nIndex && nIndex <= MAX_TAB_INDEX ); m_nTabIndex = nIndex; SetTabTextIndex( m_nTabIndex );}
	void SetTabTextIndex( INT nIndex );
	INT GetTabIndex()						{ return m_nTabIndex; }

	void	SetLock();
	void	SetUnlock();

public:
	virtual void Update( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage( UIGUID ControlID, DWORD dwMsg );
	virtual	void SetVisibleSingle( BOOL bVisible );
	void	SetShotcutText ( DWORD nID, CString& strTemp );

public:
	CSkillTrayTab(void);
	virtual ~CSkillTrayTab(void);

	CBasicQuickSkillSlot*	m_pBasicQuickSkillSlot;
	CBasicButton*			pButtonLock;
	CBasicButton*			pButtonUnLock;

protected:
	CBasicSkillTray*		m_pSkillTray[MAX_TAB_INDEX];
	CBasicTextBox*			m_pPageNumber;
	CBasicButton*			pButtonRotate;

	INT m_nTabIndex;
	INT m_nCount;
};
