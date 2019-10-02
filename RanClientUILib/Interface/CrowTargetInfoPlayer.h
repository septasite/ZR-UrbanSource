#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"
#include "BasicLineBoxEx.h"
#include "../RanClientLib/G-Logic/GLCharClient.h"

class	CD3DFontPar;
class	CBasicTextBox;
class	CBasicProgressBar;
class	CBasicTextBoxEx;
class   GLCharacter;

class	CCrowTargetInfoPlayer : public CUIGroup
{

public:
	CCrowTargetInfoPlayer ();
	virtual	~CCrowTargetInfoPlayer ();
public:
	void	CreateSubControl ();
	CUIControl*	CreateControl ( const char* szControl, WORD wAlignFlag );
	CBasicLineBoxEx*  m_pTargetBox;
	//GLCharacter* pMYCHAR;
public:
	void	SetTargetInfo ( int fNow, int fMax, int fPercent3,int fSchool, CString strClass, int strLevel, CString strPartyMember,CString strPartyM,CString strPartyNew, CString strPartyJoined,CString strParty, CString strGuild, CString strName, STARGETID sTargetID );
	const	CString& GetTargetName () const			{ return m_strName; }
public:
	CString		m_strName;
private:
	CBasicTextBox*		m_pNameBox;
	CBasicTextBox*		m_pSchoolBox;
	CBasicTextBox*		m_pClassBox;
	CBasicTextBox*		m_pRebornBox;
	CBasicTextBox*		m_pGuildBox;
	//CBasicTextBox*		m_pPartyBox;
	CBasicTextBox*		m_pTextBox;
	CUIControl*			m_pNameBoxDummy;
private:
	CD3DFontPar*		m_pFont8;
};