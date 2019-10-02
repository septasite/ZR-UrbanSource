#pragma once

#include "../EngineUILib/GUInterface/UIGroup.h"

class	CBasicProgressBar;

class CAtteIcon : public CUIGroup
{
public:
	CAtteIcon(void);
	~CAtteIcon(void);

public:
	void	CreateSubControl ();
	virtual	void	TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual	void	Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

public:
	enum
	{
		AtteIconOnMouse = NO_ID + 1,
	};


private:
	CBasicButton* m_pAtteIcon;

};
