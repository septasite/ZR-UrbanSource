#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"

class	CBasicTextBoxEx;

class	CCtfInfoDisplay : public CUIGroup
{
public:

public:
	CCtfInfoDisplay ();
	virtual	~CCtfInfoDisplay ();

public:
	void	CreateSubControl ();

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	void UpdateIcon();
	void ResetIcon();
	void UpdateClubTime( float fCLUBBATTLETime );

private:
	CUIControl*				m_pCtfBack_B;
	CUIControl*				m_pCtfBack_L;
	CUIControl*				m_pCtfBack_R;

	CUIControl*				m_pCtfMark0[4];
	CUIControl*				m_pCtfMark1[4];
	CUIControl*				m_pCtfMark2[4];

	CUIControl*				m_pCtfLine0;
	CUIControl*				m_pCtfLine1;

	CBasicTextBoxEx*		m_pCTFThermal;
	CBasicTextBoxEx*		m_pCTFFacility;
	CBasicTextBoxEx*		m_pCTFNuclear;

	CBasicTextBoxEx*		m_pClubTimeLabel;
	CBasicTextBoxEx*		m_pClubTimeText;

protected:
	CUIControl*		CreateControl ( const char* szControl, WORD wAlignFlag );
	CBasicTextBoxEx*	CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign );

};