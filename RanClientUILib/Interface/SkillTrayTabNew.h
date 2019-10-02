#pragma once

#include "../EngineUILib/GUInterface/UIGroup.h"
#include "BasicQuickSkillSlot.h"

const INT MAX_TAB_INDEX_NEW = 4;
const INT QUICK_SKILL_SLOT_MAX_NEW = 10;
const DWORD UIMSG_BASIC_LBDUP_NEW = UIMSG_USER1;

class CBasicSkillTrayNew;
class CBasicTextButton;
class CBasicButton;
class CBasicTextBox;
class CBasicQuickSkillSlotEx;

class CSkillTrayTabNew : public CUIGroup
{
	static INT NEXT_INDEX_NEW[MAX_TAB_INDEX_NEW];

public:
	enum
	{
		BASIC_QUICK_SKILL_TRAY_F1 = NO_ID + 1,
		BASIC_QUICK_SKILL_TRAY_F2,
		BASIC_QUICK_SKILL_TRAY_F3,
		BASIC_QUICK_SKILL_TRAY_F4,
		BASIC_LEVEL_DISPLAY,
		TEXT_BUTTON_CLICK,
		QUICK_SKILL_TRAY_CLOSE_NEW_BUTTON,
		QUICK_SKILL_TRAY_ROTATE_NEW_BUTTON,
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

	void SetTabIndex( INT nIndex )			{ GASSERT( 0 <= nIndex && nIndex <= MAX_TAB_INDEX_NEW ); m_nTabIndex = nIndex; SetTabTextIndex( m_nTabIndex );}
	void SetTabTextIndex( INT nIndex );
	INT GetTabIndex()						{ return m_nTabIndex; }

	BOOL		TabLock;

public:
	virtual void Update( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage( UIGUID ControlID, DWORD dwMsg );
	virtual	void SetVisibleSingle( BOOL bVisible );
	void	SetShotcutText ( DWORD nID, CString& strTemp );

public:
	CSkillTrayTabNew(void);
	virtual ~CSkillTrayTabNew(void);

	void	SetLock();
	void	SetUnlock();

	CBasicQuickSkillSlot*	m_pBasicQuickSkillSlot;
	CBasicButton*			pButtonLock;
	CBasicButton*			pButtonUnLock;

protected:
	CBasicSkillTrayNew *	m_pSkillTray[MAX_TAB_INDEX_NEW];
	CBasicTextBox*			m_pPageNumber;
	CBasicButton*			pButtonRotate;
	int		state;

	BOOL		m_bFirstGap;
	D3DXVECTOR2	m_vGap;

	int			m_PosX;
	int			m_PosY;

	bool		m_bCHECK_MOUSE_STATE;

	INT m_nTabIndex;
	INT m_nCount;
};
