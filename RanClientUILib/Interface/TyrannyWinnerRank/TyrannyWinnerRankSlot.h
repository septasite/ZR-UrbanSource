#pragma	once

#include "../EngineUiLib/GUInterface/UIGroup.h"
#include "GLCharDefine.h"
#include "GLParty.h"
#include "../EngineUiLib/GUInterface/BasicTextBox.h"
#include "../EngineUiLib/GUInterface/BasicProgressBar.h"

class	CBasicTextBox;
class	CBasicProgressBar;
class	CBasicLineBox;

class	CTyrannyWinnerRankSlot : public CUIGroup
{
public:
	CTyrannyWinnerRankSlot ();
	virtual	~CTyrannyWinnerRankSlot ();

public:
	void	CreateSubControl ();

private:
	CBasicTextBox*		m_pRankNum;
	CUIControl*			m_pRankSchool[3];
	CUIControl*			m_pRankClass[GLCI_NUM_NEWSEX];
	CBasicTextBox*		m_pRankName;
	CUIControl*			m_pSelf;

protected:
	CUIControl*		CreateControl ( const char* szControl );
	CBasicTextBox*	CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, D3DCOLOR D3DCOLOR, int nAlign );

public:
	void	DataUpdate( int nNUM, std::string strNAME, int nSCHOOL, int nCLASS, DWORD dwCHARID = UINT_MAX );
	void	DataReset();
};