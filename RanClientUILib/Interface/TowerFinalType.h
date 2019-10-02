#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"

class	CTowerFinalType : public CUIGroup
{

	bool		m_bPLAY;
	float		m_fPlayedTime;
	float		m_fPlayedTime2;
	CUIControl*	m_pXControl;

public:
	CTowerFinalType ();
	virtual	~CTowerFinalType ();

public:
	void	CreateSubControl ( CString strKeyword );

public:
	void	START();
	void	STOP()				{ m_bPLAY = false; }
	bool	ISPLAYING()			{ return m_bPLAY; }
	void	RESET();

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
};