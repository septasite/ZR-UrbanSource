#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"
#include "../RanClientLib/G-Logic/GLogicEx.h"

class	CD3DFontPar;
class	CBasicTextBox;
class	CBasicProgressBar;

class	CTowerHPDisplay : public CUIGroup , public GLCROWLOGIC
{


public:
	CTowerHPDisplay ();
	virtual	~CTowerHPDisplay ();

public:
	void	CreateSubControl ();
	CUIControl*	CreateControl ( const char* szControl, WORD wAlignFlag );
public:
	void	SetTowerHPSG ( float fPercent );
	void	GetTowerHPSG ();
	void	SetTowerHPMP ( float fPercent );
	void	GetTowerHPMP ();
	void	SetTowerHPPHX ( float fPercent );
	void	GetTowerHPPHX ();
	
private:
	CBasicProgressBar*	m_pHP;
	CBasicProgressBar*	m_pHP2;
	CBasicProgressBar*	m_pHP3;
	CBasicTextBox*		m_pNameBox;
	CUIControl*			m_pNameBoxDummy;

private:
	CString		m_strName;

private:
	CD3DFontPar*	m_pFont8;

};