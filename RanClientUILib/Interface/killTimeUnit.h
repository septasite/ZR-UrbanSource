#pragma	once

#include "GLDefine.h"

class	CBasicTextBox;
class	CBasicLineBoxEx;

#include "../EngineUILib/GUInterface/UIGroup.h"
struct	SNATIVEID;

class	CkillTimeUnit : public CUIGroup
{
public:
	CkillTimeUnit ();
	virtual	~CkillTimeUnit ();
	CUIControl*	pControl;
public:
	void	CreateSubControl (int nClassType,int m_nKillClassType , int nSchoolKilled , int nSchoolKiller);

public:
	virtual	void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

public:
	void	SetLeftTime ( const float& fLeftTime );
	void	Setkill (const float& fLifeTime, const CString& strkillName , const CString& strMKillName , const CString& strSlayed  );

private:
	float	m_fLEFT_TIME;
	float	m_fLIFE_TIME;
CUIControl*	CreateControl ( const char* szControl );
private:
	CUIControl*			m_sClass[4];
	CBasicTextBox*		m_pstrName;
	CBasicTextBox*		m_pKillstrName;
	CBasicTextBox*		m_pStrSlayed;

public:
	SNATIVEID m_sKILLID;

};