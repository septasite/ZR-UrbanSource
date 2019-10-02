#pragma once

#include "../EngineUILib/GUInterface/UIGroup.h"
class	CBasicButton;

class CCompundCompete : public CUIGroup
{
public:
	CCompundCompete(void);
	~CCompundCompete(void);

public:
	enum
	{
		COMPOUND_BUTTON	= NO_ID + 1,
	};

public:
	void	CreateSubControl ();


public:
	virtual	void	TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual	void	Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

private:
	CBasicButton*		m_pCompundButton;
	LPDIRECT3DDEVICEQ	m_pd3dDevice;
	
};

