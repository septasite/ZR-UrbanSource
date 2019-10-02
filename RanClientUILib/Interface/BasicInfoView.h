#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"

////////////////////////////////////////////////////////////////////
//	사용자 메시지 정의
const DWORD UIMSG_BASICINFOVIEW_LBDUP = UIMSG_USER1;
////////////////////////////////////////////////////////////////////

class	CBasicProgressBar;
class	CBasicTextBox;

class CBasicInfoView : public CUIGroup
{
private:
	enum
	{
		HP_TEXT = NO_ID + 1,
		MP_TEXT,
		SP_TEXT,
		CP_TEXT, //add cp
		EXP_TEXT
	};

public:
	CBasicInfoView ();
	virtual	~CBasicInfoView ();

public:
	void	CreateSubControl ();

public:
	void	CheckMouseState ();

	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );

private:
	void	SetHP ( DWORD dwNOW, DWORD dwMAX );
	void	SetMP ( DWORD dwNOW, DWORD dwMAX );
	void	SetSP ( DWORD dwNOW, DWORD dwMAX );
	void	SetCP ( DWORD dwNOW, DWORD dwMAX ); //add cp
	void	SetEXP( LONGLONG lNOW, LONGLONG lMAX );
	void	SetLEVEL( WORD wLevel );

private:
	CBasicTextBox*	CreateStaticControl ( char* szConatrolKeyword, CD3DFontPar* pFont, int nAlign, const UIGUID& cID = NO_ID );
	CBasicTextBox*		m_pHPText;
	CBasicTextBox*		m_pMPText;
	CBasicTextBox*		m_pSPText;
	CBasicTextBox*		m_pCPText; //add cp
	CBasicTextBox*		m_pEXPText;
	CBasicTextBox*		m_pHP0Text;
	CBasicTextBox*		m_pMP0Text;
	CBasicTextBox*		m_pSP0Text;
	CBasicTextBox*		m_pCP0Text; //add cp
	CBasicTextBox*		m_pEXP0Text;

private:
	CBasicProgressBar*	m_pHP;
	CBasicProgressBar*	m_pMP;
	CBasicProgressBar*	m_pSP;
	CBasicProgressBar*	m_pCP; //add cp
	CBasicProgressBar*	m_pEXP;

private:
	DWORD	m_wHPBACK;
	DWORD	m_wMPBACK;
	DWORD	m_wSPBACK;
	DWORD	m_wCPBACK; //add cp
	LONGLONG	m_lEXPBACK;

	CBasicTextBox*	m_pLevelText;
	WORD m_wLevelBACK;

private:
	BOOL		m_bFirstGap;
	D3DXVECTOR2	m_vGap;

	int			m_PosX;
	int			m_PosY;

	bool		m_bCHECK_MOUSE_STATE;
};