#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"

class	CTowerFinalType;
class	CTowerFinalDisplay : public CUIGroup
{
public:
	enum
	{
		TOWER_FINAL_SG = NO_ID + 1,
		TOWER_FINAL_PHX,
		TOWER_FINAL_MP,
		TOWER_FINAL_TWO,

		MAXTYPE = 4
	};

public:
	CTowerFinalDisplay ();
	virtual	~CTowerFinalDisplay ();

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

private:
	CTowerFinalType*	m_pQI_TYPE[MAXTYPE];
	CUIControl*			m_QI_TYPE_KEEP[MAXTYPE];

	CUIControl*		m_pPositionControl;	
};