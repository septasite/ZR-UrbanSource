#pragma once

#include "../EngineUILib/GUInterface/UIGroup.h"

class	CBasicProgressBar;

class CSWarIcon : public CUIGroup
{
public:
	CSWarIcon(void);
	~CSWarIcon(void);

public:
	void	CreateSubControl ();
	virtual	void	TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual	void	Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

public:
	enum
	{
		SWarIconOnMouse = NO_ID + 1,
	};


private:
	CBasicButton* m_pSWarIcon;

};
