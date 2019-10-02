#pragma once

#include "../EngineUILib/GUInterface/UIGroup.h"
#include "BasicQuickSkillSlot.h"

const DWORD UIMSG_BASIC_LBDUP_WINDOW = UIMSG_USER1;

class CBasicTextButton;
class CBasicButton;
class CBasicQuickSkillSlotEx;
class CBasicQuickSkillSlot;

class CBasicQuickSkillWindow : public CUIGroup
{
public:
	enum
	{
		QUICK_SKILL_TRAY_OPEN_BUTTON_CLOSE = NO_ID + 1,
		QUICK_SKILL_TRAY_LOCK_BUTTON_CLOSE,
		QUICK_SKILL_TRAY_UNLOCK_BUTTON_CLOSE,
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

	void		SetLock();
	void		SetUnlock();

public:
	virtual void Update( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage( UIGUID ControlID, DWORD dwMsg );

public:
	CBasicQuickSkillWindow(void);
	virtual ~CBasicQuickSkillWindow(void);

	CBasicQuickSkillSlot*	m_pBasicQuickSkillSlot;
	CBasicButton*			pButtonLock;
	CBasicButton*			pButtonUnLock;

};
