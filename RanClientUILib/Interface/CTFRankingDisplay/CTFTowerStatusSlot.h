#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "GLCharDefine.h"

class	CBasicTextBox;


class	CCTFTowerStatusSlot : public CUIGroup
{
public:
	CCTFTowerStatusSlot ();
	virtual	~CCTFTowerStatusSlot ();

public:
	void	CreateSubControl ();

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual	void SetVisibleSingle ( BOOL bVisible );

private:
	CBasicTextBox*		m_pName;
	CUIControl*			m_pSchool[3];

protected:
	CUIControl*		CreateControl ( const char* szControl );
	CBasicTextBox*	CreateStaticControl ( char* szControlKeyword, char* szText, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign );

public:
	void	DataUpdate( std::string strNAME, int nSCHOOL );
	void	DataReset();

};