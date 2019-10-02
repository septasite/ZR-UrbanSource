#pragma once

#include "../EngineUILib/GUInterface/UIGroup.h"
class	CBasicButton;

class CQBoxButton : public CUIGroup
{
public:
	CQBoxButton(void);
	~CQBoxButton(void);

public:
	enum
	{
		QBOX_ON_OFF_BUTTON	= 0,
		QBOX_DEFAULT		= 1,
		QBOX_SPEED_UP		= 2,
		QBOX_CRAZY_TIME		= 3,
		QBOX_POWER_UP		= 4,
		QBOX_EXP_TIME		= 5,
		QBOX_LUCKY			= 6,
		QBOX_SPEED_UP_M		= 7,
		QBOX_MADNESS		= 8,
		QBOX_ATTACK_UP_M	= 9,
		QBOX_SIZE			= 10
	};

public:
	void	CreateSubControl ();
	bool	GetQBoxEnable() { return m_bQBoxEnable; }
	void	SetQBoxEnable( bool bQBoxEnable );

	void	Start( UIGUID ImageID );
	void	Change( UIGUID ImageID );
	void	Stop();

public:
	virtual	void	TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual	void	Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

private:
	CBasicButton* m_pQBoxButton[QBOX_SIZE];
	CUIControl*	  m_pAlarmBlink;
	CUIControl*	  m_pBoxLock;

	bool		  m_bQBoxEnable;
	bool		  m_bQBoxAlarm;
	float		  m_fBLINK_TIME;

LPDIRECT3DDEVICEQ	m_pd3dDevice;
	
};

