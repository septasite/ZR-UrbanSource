#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "GLCharDefine.h"

class	CBasicTextBox;


class	CCTFTowerScoreSlot : public CUIGroup
{
public:
	CCTFTowerScoreSlot ();
	virtual	~CCTFTowerScoreSlot ();

public:
	void	CreateSubControl ();

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual	void SetVisibleSingle ( BOOL bVisible );

private:
	CBasicTextBox*		m_pName;
	CUIControl*			m_pSchool[3];
	CBasicTextBox*		m_pSchoolText;

	CBasicTextBox*		m_pDamageSG;
	CBasicTextBox*		m_pDamageMP;
	CBasicTextBox*		m_pDamagePHX;

protected:
	CUIControl*		CreateControl ( const char* szControl );
	CBasicTextBox*	CreateStaticControl ( char* szControlKeyword, char* szText, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign );

public:
	void	DataUpdate( std::string strNAME, int nSCHOOL, LONGLONG llDamageSG, LONGLONG llDamageMP, LONGLONG llDamagePHX );
	void	DataReset();

};