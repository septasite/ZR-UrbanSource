#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"
#include "GLCharDefine.h"
//#include "GLParty.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../EngineUILib/GUInterface/BasicProgressBar.h"

////////////////////////////////////////////////////////////////////
//	사용자 메시지 정의
const DWORD UIMSG_MOUSEIN_RB_EVENT = UIMSG_USER1;
////////////////////////////////////////////////////////////////////

class	CBasicTextBox;
class	CBasicProgressBar;
class	CBasicLineBox;

class	CSWRankingSlot : public CUIGroup
{
protected:
	enum
	{
		/*HP_BAR = NO_ID + 1,
		HP_BAR0,
		HP_BAR1,
		HP_BAR2,
		HP_BAR3,
		HP_BAR4,
		HP_BAR5,
		HP_BAR6,
		HP_BAR7,
		HP_BAR8,
		HP_BAR9,
		HP_BAR10,
		HP_BAR11,
		HP_BAR12,
		HP_BAR13,
		HP_BAR14,
		HP_BAR15,*/
	};

	CUIControl*			m_pNumber[10];
	//CUIControl*		m_pClass[GLCI_NUM];

public:
	CSWRankingSlot ();
	virtual	~CSWRankingSlot ();

public:
	void	CreateSubControl ();

public:
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );

public:
	CBasicTextBox*	m_pSwPRankingText;
	
	void	SetPlayerName ( CString strName );

	void	SetNumber ( int nSlotNumber );
	CUIControl*			m_pClass[GLCI_NUM_NEWEST];
	void	SetClass ( int nClassType );

	CBasicTextBox*		m_pNumberSlot;
	CBasicLineBox*		pLineBoxCombo;
	CBasicLineBox*		pLineBox1;
	
	CBasicTextBox*	m_pPlayerName;
	CBasicTextBox*	m_pKill;
	CBasicTextBox*	m_pDeath;
	CBasicTextBox*	m_pRank;

	void	SetTextColorChange();
	void	SetTextColorRevert();
	BOOL	m_bMaster;
	CUIControl*			m_pSchool[3];

	void	SetSchool ( int nSchoolType );
	void	SetNameColorDefault ();

	void	IsPlayerSameMap ( BOOL bOK );

protected:
	CUIControl*		CreateControl ( const char* szControl );
	CBasicTextBox*	CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, D3DCOLOR D3DCOLOR, int nAlign );

public:

	void SetPlayerNameColor ( int nPercent );
	void SetScore( int nKill, int nDeath );
};