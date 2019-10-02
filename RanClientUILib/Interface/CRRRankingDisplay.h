#pragma once

#include "../EngineUILib/GUInterface/UIGroup.h"

class	CBasicTextButton;
class	CBasicButton;

class	CRRRankingDisplay : public CUIGroup
{
protected:
	enum
	{
		ROYALRUMBLE_SCOREBOARD_OPEN_BUTTON = NO_ID + 1,
	};

public:
	CRRRankingDisplay ();
	virtual	~CRRRankingDisplay ();

public:
	void	CreateSubControl ();
	CBasicButton*	CreateFlipButton ( char* szButton, char* szButtonFlip, UIGUID ControlID );
	CBasicTextButton*	CreateTextButton ( char* szButton, UIGUID ControlID, char* szText );

public:
	virtual	void	TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
};