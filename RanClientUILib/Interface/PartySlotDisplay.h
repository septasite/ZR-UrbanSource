#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"
#include "GLCharDefine.h"
#include "GLParty.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../EngineUILib/GUInterface/BasicProgressBar.h"

const DWORD UIMSG_MOUSEIN_RB_EVENT = UIMSG_USER1;

class	CBasicTextBox;
class	CBasicProgressBar;
class	CBasicLineBox;

class	CPartySlotDisplay : public CUIGroup
{
protected:
	enum
	{
		HP_BAR0 = NO_ID + 1,
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
		HP_BAR15,
	};

	CUIControl*			m_pNumber[MAXPARTY];

public:
	CPartySlotDisplay ();
	virtual	~CPartySlotDisplay ();

public:
	void	CreateSubControl ();

public:
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );

public:
	void	SetPlayerName ( CString strName )	{ m_pPlayerName->SetOneLineText( strName ); }
	void	SetPlayerHealth ( int fHPNow, int fHPMax );
	//void	SetSchool ( int nSchoolType );
	void	SetHP ( float fPercent )			
	{ 
		if ( m_pHP0->IsVisible() ) { m_pHP0->SetPercent( fPercent ); }
		else if ( m_pHP1->IsVisible() ) { m_pHP1->SetPercent( fPercent ); }
		else if ( m_pHP2->IsVisible() ) { m_pHP2->SetPercent( fPercent ); }
		else if ( m_pHP3->IsVisible() ) { m_pHP3->SetPercent( fPercent ); }
		else if ( m_pHP4->IsVisible() ) { m_pHP4->SetPercent( fPercent ); }
		else if ( m_pHP5->IsVisible() ) { m_pHP5->SetPercent( fPercent ); }
		else if ( m_pHP6->IsVisible() ) { m_pHP6->SetPercent( fPercent ); }
		else if ( m_pHP7->IsVisible() ) { m_pHP7->SetPercent( fPercent ); }
		else if ( m_pHP8->IsVisible() ) { m_pHP8->SetPercent( fPercent ); }
		else if ( m_pHP9->IsVisible() ) { m_pHP9->SetPercent( fPercent ); }
		else if ( m_pHP10->IsVisible() ) { m_pHP10->SetPercent( fPercent ); }
		else if ( m_pHP11->IsVisible() ) { m_pHP11->SetPercent( fPercent ); }
		else if ( m_pHP12->IsVisible() ) { m_pHP12->SetPercent( fPercent ); }
		else if ( m_pHP13->IsVisible() ) { m_pHP13->SetPercent( fPercent ); }
		else if ( m_pHP14->IsVisible() ) { m_pHP14->SetPercent( fPercent ); }
		else if ( m_pHP15->IsVisible() ) { m_pHP15->SetPercent( fPercent ); }
	}
	void	SetPlayerPos ( BOOL bSame );
	void	SetNumber ( int nSlotNumber );
	CUIControl*			m_pClass[GLCI_NUM_NEWEST];
	void	SetClass ( int nClassType );
	CUIControl*			m_pMaster;
	CBasicLineBox*		pLineBoxCombo;
	CBasicLineBox*		pLineBoxComboLow;
	CBasicTextBox*		m_pPlayerName;
	CBasicTextBox*		m_pPlayerHealth;
	//CUIControl*			m_pSchool[GLSCHOOL_NUM];
	CUIControl*			m_pRedLineBox;

	BOOL	m_bMaster;

	
	CBasicProgressBar*	m_pHP0;
	CBasicProgressBar*	m_pHP1;
	CBasicProgressBar*	m_pHP2;
	CBasicProgressBar*	m_pHP3;
	CBasicProgressBar*	m_pHP4;
	CBasicProgressBar*	m_pHP5;
	CBasicProgressBar*	m_pHP6;
	CBasicProgressBar*	m_pHP7;
	CBasicProgressBar*	m_pHP8;
	CBasicProgressBar*	m_pHP9;
	CBasicProgressBar*	m_pHP10;
	CBasicProgressBar*	m_pHP11;
	CBasicProgressBar*	m_pHP12;
	CBasicProgressBar*	m_pHP13;
	CBasicProgressBar*	m_pHP14;
	CBasicProgressBar*	m_pHP15;

protected:
	CUIControl*		CreateControl ( const char* szControl );
	CBasicTextBox*	CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, D3DCOLOR D3DCOLOR, int nAlign );
};