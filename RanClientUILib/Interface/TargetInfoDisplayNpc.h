#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"

class	CD3DFontPar;
class	CBasicTextBox;
class	CBasicProgressBar;

class	CTargetInfoDisplayNpc : public CUIGroup
{


public:
	CTargetInfoDisplayNpc ();
	virtual	~CTargetInfoDisplayNpc ();

public:
	void	CreateSubControl ();
	CUIControl*	CreateControl ( const char* szControl, WORD wAlignFlag );

public:
	void	SetTargetInfoNpc ( float fPercent, CString strName, D3DCOLOR dwColor ); /*, int nSchoolMark = NODATA, int nPartyMark = NODATA );*/
	const CString& GetTargetName () const			{ return m_strName; }

private:
	CBasicTextBox*		m_pNameBox;
	CBasicProgressBar*	m_pHP;
	CUIControl*			m_pNameBoxDummy;

private:
	CString		m_strName;

private:
	CD3DFontPar*	m_pFont8;

};