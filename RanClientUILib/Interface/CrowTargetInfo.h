#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"
#include "BasicLineBoxEx.h"
#include "../RanClientLib/G-Logic/GLCharClient.h"
class	CD3DFontPar;
class	CBasicTextBox;
class	CBasicProgressBar;
class	CBasicTextBoxEx;

class	CCrowTargetInfo : public CUIGroup
{

public:
	CCrowTargetInfo ();
	virtual	~CCrowTargetInfo ();
public:
	void	CreateSubControl ();
	CUIControl*	CreateControl ( const char* szControl, WORD wAlignFlag );
	CBasicLineBoxEx*  m_pTargetBox;
public:
	void	SetTargetInfo ( int fNow, int fMax, int fPercent,DWORD Level , CString strName, STARGETID sTargetID  );
	const	CString& GetTargetName () const			{ return m_strName; }
public:
	CString		m_strName;
private:
	CBasicTextBox*		m_pNameBox;
	CBasicTextBox*		m_pHPBox;
	CUIControl*			m_pNameBoxDummy;
private:
	CD3DFontPar*		m_pFont8;
};