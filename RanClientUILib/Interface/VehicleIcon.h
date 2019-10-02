#pragma once

#include "../EngineUILib/GUInterface/UIGroup.h"
#include "GLItem.h"

class	CBasicProgressBar;

class CVehicleIcon : public CUIGroup
{
public:
	CVehicleIcon(void);
	~CVehicleIcon(void);

public:
	enum
	{
		VehicleIconOnMouse = NO_ID + 1,
		VehicleType = 6,
	};

public:
	void	CreateSubControl ();


public:
	virtual	void	TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual	void	Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

private:
	CBasicButton* m_pVehicleIcon;
	void SetBattery( int nNOW );
	CBasicProgressBar*  m_BoxGauge;
	CUIControl*	  m_pVehicleType[VehicleType];
};
