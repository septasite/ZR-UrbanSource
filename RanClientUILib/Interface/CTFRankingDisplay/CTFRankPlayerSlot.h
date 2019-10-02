#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "GLCharDefine.h"

class	CBasicTextBox;


class	CCTFRankPlayerSlot : public CUIGroup
{
public:
	CCTFRankPlayerSlot ();
	virtual	~CCTFRankPlayerSlot ();

public:
	void	CreateSubControl ();

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual	void SetVisibleSingle ( BOOL bVisible );

private:
	CBasicTextBox*		m_pRankNum;
	CUIControl*			m_pRankSchool[3];
	CUIControl*			m_pRankClass[GLCI_NUM_NEWEST];
	CBasicTextBox*		m_pRankName;
	CBasicTextBox*		m_pRankDamage;
	CBasicTextBox*		m_pRankKill;
	CBasicTextBox*		m_pRankDeath;

protected:
	CUIControl*		CreateControl ( const char* szControl );
	CBasicTextBox*	CreateStaticControl ( char* szControlKeyword, char* szText, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign );

public:
	void	DataUpdate( int nNUM, std::string strNAME, int nSCHOOL, int nCLASS, LONGLONG llDAMAGE, int nKILL, int nDEATH );
	void	DataReset();

};