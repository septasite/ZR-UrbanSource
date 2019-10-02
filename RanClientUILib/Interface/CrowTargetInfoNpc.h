#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"
#include "BasicLineBoxEx.h"

class	CD3DFontPar;
class	CBasicTextBox;
class	CBasicProgressBar;
class	CBasicTextBoxEx;
struct	SNpcTalk;

class	CCrowTargetInfoNpc : public CUIGroup
{

public:
	CCrowTargetInfoNpc ();
	virtual	~CCrowTargetInfoNpc ();
public:
	void	CreateSubControl ();
	CUIControl*	CreateControl ( const char* szControl, WORD wAlignFlag );
	CBasicLineBoxEx*  m_pTargetBox;
public:
	void	SetTargetInfo ( CString strName );
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