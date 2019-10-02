#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"

class	CD3DFontPar;
class	CBasicTextBox;
class	CBasicProgressBar;

class	CTargetInfoCtfDisplay : public CUIGroup
{

public:
	CTargetInfoCtfDisplay ();
	virtual	~CTargetInfoCtfDisplay ();

public:
	void	CreateSubControl ();
	CUIControl*	CreateControl ( const char* szControl, WORD wAlignFlag );

public:
	void	SetTargetInfo ( float fPercentsg, float fPercentmp,float fPercentphx, WORD wSchool, WORD wAuthID ); /*, int nSchoolMark = NODATA, int nPartyMark = NODATA );*/

private:
	CBasicProgressBar*	m_pHP_SG;
	CBasicProgressBar*	m_pHP_MP;
	CBasicProgressBar*	m_pHP_PHX;

	CUIControl*			m_pFightSignSG;
	CUIControl*			m_pFightSignMP;
	CUIControl*			m_pFightSignPHX;

	CUIControl*			m_pFightSignAuth;
private:
	CD3DFontPar*	m_pFont8;
};