#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"

class	CTowerDownType;
class	CTowerDownDisplay : public CUIGroup
{
public:
	enum
	{
		TOWER_CAPTURED_SG = NO_ID + 1,
		TOWER_CAPTURED_PHX,
		TOWER_CAPTURED_MP,
		TOWER_CAPTURED_SG_SCHOOL,
		TOWER_CAPTURED_PHX_SCHOOL,
		TOWER_CAPTURED_MP_SCHOOL,
		TOWER_CAPTURED_BACK,
		LOGO_SW_STARTED_END,
		LOGO_SW_STARTED_TEXT,
		LOGO_SW_ENDED_TEXT,

		MAXTYPE = 10
	};

public:
	CTowerDownDisplay ();
	virtual	~CTowerDownDisplay ();

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
	CTowerDownType*	m_pQI_TYPE[MAXTYPE];
	CUIControl*			m_QI_TYPE_KEEP[MAXTYPE];

	CUIControl*		m_pPositionControl;	
};