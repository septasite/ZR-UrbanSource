#pragma once

#include "../EngineUILib/GUInterface/UIGroup.h"
#include ".\skilltraytab.h"
#include "BasicQuickSkillSlot.h"
#include "InnerInterface.h"

const DWORD UIMSG_NEW_SKILL_TAB_LBDUP = UIMSG_USER1;

class CBasicQuickSkillSlot;
class CSkillTrayTab;
class CSkillWindowToTray;

class CNewSkillQickAndTrayTab: public CUIGroup
{
	enum
	{
		//BASIC_QUICK_SKILL_SLOT = NO_ID + 1,
		//QUICK_SKILL_TRAY_TAB_WINDOW,
	};
private:
	CBasicQuickSkillSlot*	m_pBasicQuickSkillSlot;
	CSkillTrayTab*			m_pSkillTrayTab;

public:
	void CreateSubControl();
	void CheckMouseState();
	virtual void Update( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage( UIGUID ControlID, DWORD dwMsg );

	BOOL		m_bFirstGap;
	D3DXVECTOR2	m_vGap;

	int			m_PosX;
	int			m_PosY;

	bool		m_bCHECK_MOUSE_STATE;

public:
	CNewSkillQickAndTrayTab(void);
	virtual ~CNewSkillQickAndTrayTab(void);

};
