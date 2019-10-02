#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"
#include "GLSkill.h"

class	CSkillSlot;
class	CBasicScrollBarEx;

class	CSkillPage : public CUIGroup
{
protected:
static	const	int		nSTARTLINE;
static	const	int		nOUTOFRANGE;

protected:
	enum
	{
		RNSKILL_SLOT_0 = NO_ID + 1,
		RNSKILL_SLOT_1,RNSKILL_SLOT_2,RNSKILL_SLOT_3,
		RNSKILL_SLOT_4,RNSKILL_SLOT_5,RNSKILL_SLOT_6,
		RNSKILL_SLOT_7,RNSKILL_SLOT_8,RNSKILL_SLOT_9,
		RNSKILL_SLOT_10,RNSKILL_SLOT_11,RNSKILL_SLOT_12,
		RNSKILL_SLOT_13,RNSKILL_SLOT_14,RNSKILL_SLOT_15,
		RNSKILL_SLOT_16,RNSKILL_SLOT_17,
		SKILL_SLOT_END = RNSKILL_SLOT_0 + GLSkillMan::MAX_CLASSSKILL,
	};

	enum
	{
		nMAX_ONE_VIEW_SLOT = 18
	};

public:
	CSkillPage ();
	virtual	~CSkillPage ();

public:
	void	CreateSubControl ( SNATIVEID sNativeIDArray[GLSkillMan::MAX_CLASSSKILL], int nSkillCount );	

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );

protected:
	void	ResetAllSkillSlotRender ( int nTotal );
	void	SetSkillSlotRender ( int nStartIndex, int nTotal );

public:
	int			GetSkillIndex ()						{ return m_nSlotIndex; }
	SNATIVEID	GetSkillID ( int nIndex );

protected:
	CUIControl*	CreateControl ( const char* szControl );
	CSkillSlot*	CreateSkillSlot ( CString strKeyword, UIGUID ControlID, SNATIVEID sNativeID );

public:
	CSkillSlot*	m_pSkillSlotArray[GLSkillMan::MAX_CLASSSKILL];
	int GetSlotIndex()		{ return m_nSlotIndex ; }

private:	
	CUIControl*	m_pSkillSlotArrayDummy[nMAX_ONE_VIEW_SLOT];

private:
	CBasicScrollBarEx*	m_pScrollBar;

private:
	int		m_nSlotIndex;
	int		m_nCurPos;
	int		m_nMaxSkillCnt;
	vector<int> m_vecViewSkill;
};