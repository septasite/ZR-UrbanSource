#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"
class CBasicTextBox;

class CCountMsgCD : public CUIGroup
{
public:
	CCountMsgCD ();
	virtual	~CCountMsgCD ();

public:
	void CreateSubControl();
	CUIControl*	CreateControl( CONST TCHAR* szControl );
	void SetCount( bool bVisible );
	CBasicTextBox*	CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign );

public:
	virtual void Update( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

private:
	CUIControl * m_pTEN[10];
	CUIControl * m_pONE[10];

	INT m_nCount;
	INT m_nRandomNumber;
	float m_fElapsedTime;

	CBasicTextBox*		m_pCoolDownText;
};