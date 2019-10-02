#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"


class CSwBonusMark : public CUIGroup
{
public:
	enum
	{
		CTF_REWARD_BUFF_TOP_TEXT00 = NO_ID + 1,
		CTF_REWARD_BUFF_TOP_TEXT01,
		CTF_REWARD_BUFF_TOP_TEXT02,
	};

public:
	CSwBonusMark();
	virtual ~CSwBonusMark();

	void	CreateSubControl ();
	virtual	void	TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	void	SetSwBonus( bool isWinner );

	CUIControl*			        m_pRewardBuffBack[3];
	
};