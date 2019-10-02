#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"
#include "GLCharDefine.h"

class	CBasicTextBox;
class	CBasicButton;
class	CPartySlot : public CUIGroup
{
protected:
	enum
	{
		PARTY_INFO_ADD_BUTTON = NO_ID + 1,
		PARTY_INFO_VIEW_BUTTON
	};

public:
	CPartySlot ();
	virtual	~CPartySlot ();
	void CreateSubControl ();
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	CBasicTextBox* CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, int nAlign );
	CUIControl* CreateControl ( const char* szControl );
	CBasicButton*	CreateFlipButton ( char* szButton, char* szButtonFlip, char* szButtonOver, UIGUID ControlID );

private:
	CBasicTextBox*	m_pTextNum;
	BOOL			m_bSameMap;
	CUIControl*		m_pMaster;
	BOOL			m_bMaster;

	CUIControl*		m_pClassLive[GLCI_NUM_NEWEST];
	CUIControl*		m_pClassDie[GLCI_NUM_NEWEST];

	CUIControl*		m_pDie;
	BOOL			m_bDIE;

	CUIControl*		m_pSchool[3];

	CBasicTextBox*	m_pLevelText;
	CBasicTextBox*	m_pMapText;
	CBasicTextBox*	m_pNameText;
	CBasicTextBox*	m_pPosText;

	CUIControl*		m_pSelect;
	BOOL			m_bSelect;

	CString			m_strName;

public:
	CString			GetName() { return m_strName; }

	void			SetSameMap(BOOL bSame) { m_bSameMap = bSame; }
	BOOL			IsSameMap()	{ return m_bSameMap; }

	int				SetSlotNum(CString strNum);

	void			SetMaster(BOOL bMaster);
	BOOL			IsMaster() { return m_bMaster; }

	void			SetClass(int nClass);
	void			SetDie(BOOL bDIE);
	BOOL			IsDie() { return m_bDIE; }

	void			SetSchool(int nSchool);
	void			SetInfo(CString strLevel, CString strMap, CString strName, CString strPos, BOOL bSELF = FALSE);

	void			SetSelect(BOOL bSELECT);
	BOOL			IsSELECT() { return m_bSelect; }

	CBasicButton*	m_pAddFriendBtn;
};