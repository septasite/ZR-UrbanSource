#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"

class	CTowerCapturedType;
class	CTowerCapturedDisplay : public CUIGroup
{
public:
	enum
	{
		TOWER_CAPTURED_THERMAL_TOWER_SG = NO_ID + 1,
		TOWER_CAPTURED_THERMAL_TOWER_MP,
		TOWER_CAPTURED_THERMAL_TOWER_PHX,

		MAXTYPE = 3
	};

public:
	CTowerCapturedDisplay ();
	virtual	~CTowerCapturedDisplay ();

public:
	void	CreateSubControl ();

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

public:
	bool	START ( UIGUID cID );
	bool	RESET ( UIGUID cID );
	bool	STOP ( UIGUID cID );

	void	ALLSTOP ();

public:
	bool	KEEP_START ( UIGUID cID );
	void	KEEP_STOP ();
	bool	START_FADEINOUT( UIGUID cID );

private:
	CTowerCapturedType*	m_pQI_TYPE[MAXTYPE];
	CUIControl*			m_QI_TYPE_KEEP[MAXTYPE];

	CUIControl*		m_pPositionControl;	
};