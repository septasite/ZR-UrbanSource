#pragma once

#include "../EngineUILib/GUInterface/UIGroup.h"
#include "GLItem.h"

class	CBasicProgressBar;

class CPetIcon : public CUIGroup
{
public:
	CPetIcon(void);
	~CPetIcon(void);

public:
	enum
	{
		PetIconOnMouse = NO_ID + 1,
		PetType = 16,
	};

public:
	void	CreateSubControl ();


public:
	virtual	void	TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual	void	Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

private:
	CBasicButton* m_pPetIcon;
	void SetSatiety( int nNOW );
	CBasicProgressBar*  m_BoxGauge;
	CUIControl*	  m_pPetType[PetType];
};
