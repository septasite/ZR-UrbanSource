#pragma once

#include "../EngineUILib/GUInterface/UIGroup.h"

class	CQBoxButtonImage : public CUIGroup
{
public:
	CQBoxButtonImage();
	virtual ~CQBoxButtonImage();

protected:
	enum
	{
		QBOX_NONE		= NO_ID + 1,
		QBOX_CRAZY,
		QBOX_EXP,
		QBOX_LUCKY,
		QBOX_MADNEES,
		QBOX_POWER,
		QBOX_POWER_MAX,
		QBOX_SPEED,
		QBOX_SPEED_MAX,

		QBOX_SIZE = 9
	};

public:
	void	CreateSubControl ();

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

public:
	void	SetQItem ( const UIGUID cID );

private:
	float	m_fLEFT_TIME;
	float	m_fLIFE_TIME;

private:
	CUIControl*		m_pQBoxImage[QBOX_SIZE];
	CUIControl*		m_pQBoxImageflip[QBOX_SIZE];
};