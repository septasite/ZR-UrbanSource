#pragma	once

#include "../EngineUILib/GUInterface/UIWindow.h"
#include "../Interface/UIWindowEx.h"
#include "BasicLineBoxEx.h"

class	CBasicTextBox;
class	CBasicProgressBar;

class CForceRebirth : public CUIWindowEx
{
	static const float fDEFAULT_TIME_LEFT;
	static const float fDEFAULT_SELECT_TIME_LEFT;

private:
	enum
	{
		REBIRTH_CHECK_POINT = ET_CONTROL_NEXT,
	};	

public:
	CForceRebirth ();
	virtual	~CForceRebirth ();

public:
	void	CreateSubControl ();
private:
	void	DoACTION ()							{ m_bDO_ACTION = true; }

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

public:
	void	SetCallerID( UIGUID ControlID )		{ m_CallerID = ControlID; }
	UIGUID	GetCallerID()						{ return m_CallerID; }

	//dmk14 | 9-3-16 | Force rebirth
	void	DoForceRebirth();

private:
	CUIControl*	pTimerIcon;
	CBasicTextBox*		m_pTextBox;
	CBasicProgressBar*	m_pGauge;

private:
	float	m_fTIME_LEFT;
	float	m_fSelTIME_LEFT;
	float	m_fTime;
	bool	m_bDO_ACTION;
	int		m_nACTION;

	bool	m_bDONE_ACTION;

	UIGUID	m_CallerID;
	
};