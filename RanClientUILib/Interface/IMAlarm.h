#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"

class	CItemMix : public CUIGroup
{
private:
static	const	float	fBLINK_TIME_LOOP;

private:
	enum
	{
		ITEM_MIX_BUTTON = NO_ID + 1,
	};

	bool m_bItemMix;
	CUIControl*	m_pItemMixBlink;
	float m_fBLINK_TIME;

public:
	CItemMix ();
	virtual	~CItemMix ();

public:
	void	SET_ALARM ()			{ m_bItemMix = true; }

	void	CreateSubControl ();

public:
	virtual	void	SetVisibleSingle ( BOOL bVisible );
	virtual	void	Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
};