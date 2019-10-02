#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"
#include "GLGaeaClient.h"

class	CD3DFontPar;
class	CBasicTextBox;
class	CBasicLineBox;
class	CBasicProgressBar;

class	CTargetBasicInfoDisplay : public CUIGroup
{
//public:
//	enum
//	{
//		nSCHOOLMARK = 3,
//		nPARTYMARK = 5,
//		NODATA = UINT_MAX
//	};

public:
	CTargetBasicInfoDisplay ();
	virtual	~CTargetBasicInfoDisplay ();

public:
	void	CreateSubControl ();
	CUIControl*	CreateControl ( const char* szControl, WORD wAlignFlag );

public:
	void  SetTargetInfo ( PGLCHARCLIENT pCHAR, DWORD TypeColor ); /*, int nSchoolMark = NODATA, int nPartyMark = NODATA );*/
	void  SetTargetInfoMobs ( int fNow, int fMax, int fPercent, CString Name, DWORD Level, DWORD TypeColor );
	void  SetTargetInfoNpc ( int fNow, int fMax, int fPercent, CString Name, DWORD TypeColor );
	const CString& GetTargetName () const			{ return m_strName; }

	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );


private:
	CBasicTextBox*		m_pNameBox;
	CBasicTextBox*		m_InfoCharMobs;
	CBasicTextBox*		m_InfoCharPC;
	CBasicTextBox*		m_InfoCharNpc;

	CBasicLineBox*		m_InfoCharMobsLine;
	CBasicLineBox*		m_InfoCharPCLine;
	CBasicLineBox*		m_InfoCharNpcLine;

	CUIControl*			m_pNameBoxDummy;
	CString				strCombine;
private:
	CString		m_strName;

private:
	CD3DFontPar*	m_pFont8;

protected:
	void	ResizeControl ( char* szWindowKeyword );


//private:
//	CUIControl*		m_pSchoolMark[nSCHOOLMARK];
//	CUIControl*		m_pPartyMark[nPARTYMARK];
};