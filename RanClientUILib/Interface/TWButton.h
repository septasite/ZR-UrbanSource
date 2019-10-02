#pragma once

#include "../EngineUILib/GUInterface/UIGroup.h"

class	CBasicProgressBar;

class CTWButton : public CUIGroup
{
public:
	CTWButton(void);
	~CTWButton(void);

public:
	enum
	{
		TW_ON_OFF_BUTTON = NO_ID + 1,
		TW_CRAZY = 1,
		TW_EXP = 2,
		TW_LUCKY = 3,
		TW_MADNEES = 4,
		TW_POWER = 5,
		TW_POWER_MAX = 6,
		TW_SPEED = 7,
		TW_SPEED_MAX = 8,

		TW_SIZE = 9
	};

public:
	void	CreateSubControl ();
	bool	GetTWEnable() { return m_bTWEnable; }
	void	SetTWEnable( bool bTWEnable );

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
	CBasicButton* m_pTWButton;
	CUIControl*	  m_pAlarmBlink;
	bool		  m_bTWEnable;
	bool		  m_bTWAlarm;
	float		  m_fBLINK_TIME;
	bool		  m_bTWLock;
	CUIControl*	  m_pTWLock;
	CUIControl*	  m_pTWImage[TW_SIZE];
	CBasicProgressBar*  m_BoxGauge;

};
