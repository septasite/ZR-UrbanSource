#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"

class	CTowerCapturedType : public CUIGroup
{

	bool		m_bPLAY;
	float		m_fPlayedTime;
	float		m_fBEGIN_TIME;
	float		m_fEND_TIME;
	CUIControl*	m_pXControl;

public:
	CTowerCapturedType ();
	virtual	~CTowerCapturedType ();

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