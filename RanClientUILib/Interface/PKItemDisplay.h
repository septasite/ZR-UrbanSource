#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"

class	CBasicTextBox;
class	CPKItemType;
class	CBasicPkItemDisplay;
class	CBasicTextBox;
class	CBasicVarTextBox;

class CPKItemDisplay : public CUIGroup
{
public:
	CPKItemDisplay ();
	virtual	~CPKItemDisplay ();
public:
	enum
	{
		FIRSTBLOOD = 0,
		DOUBLEKILL = 1,
		TRIPLEKILL = 2,
		ULTRAKILL  = 3,
		MONSTERKILL= 4,
		GODLIKE		= 5,		
		
//		MAXTYPE1 = 6 ,
		MAXTYPE = 6
	};
public:
	void	CreateSubControl ();

public:
	virtual void	Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
public:
	bool	START ( UIGUID cID );
	bool	RESET ( UIGUID cID );
	bool	STOP ( UIGUID cID );

	void	ALLSTOP ();

public:
	bool	KEEP_START ( UIGUID cID );
	void	KEEP_STOP ();
private:
	CPKItemType*	m_pQI_TYPE[MAXTYPE];
	CUIControl*			m_QI_TYPE_KEEP[MAXTYPE];
//	CBasicPkWinDisplay*			m_pPkWinText[MAXTYPE];
public:	//	ªË¡¶
	DWORD m_dwPkWinBACK;
	CUIControl*		m_pPositionControl;	
private:
	CBasicTextBox*	m_pPkWinText[MAXTYPE];
/*private:
	CBasicTextBox*	CreateTextBox ( const char* szControl );*/
};