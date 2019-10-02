#pragma once

#include "../EngineUILib/GUInterface/UIGroup.h"

class	CBasicProgressBar;

class CFBButton : public CUIGroup
{
public:
	CFBButton(void);
	~CFBButton(void);

public:
	enum
	{
		FB_ON_OFF_BUTTON = NO_ID + 1,
		FB_CRAZY = 1,
		FB_EXP = 2,
		FB_LUCKY = 3,
		FB_MADNEES = 4,
		FB_POWER = 5,
		FB_POWER_MAX = 6,
		FB_SPEED = 7,
		FB_SPEED_MAX = 8,

		FB_SIZE = 9
	};

public:
	void	CreateSubControl ();
	bool	GetFBEnable() { return m_bFBEnable; }
	void	SetFBEnable( bool bFBEnable );

public:
	virtual	void	TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual	void	Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

public:
	bool		  SetImageBox ( UIGUID cID, float TimeBox );
	bool		  SetImageStop ();
	bool		  SetChangeImage ( UIGUID cID );
	void	 	  SetTimeConsume ( int nNOW, int nMAX );
	float		  m_CurrentTimeBox;
	float		  m_RemainTimeBox;

private:
	CBasicButton* m_pFBButton;
	CUIControl*	  m_pAlarmBlink;
	bool		  m_bFBEnable;
	bool		  m_bFBAlarm;
	float		  m_fBLINK_TIME;
	bool		  m_bFBLock;
	CUIControl*	  m_pFBLock;
	CUIControl*	  m_pFBImage[FB_SIZE];
	CBasicProgressBar*  m_BoxGauge;

};
