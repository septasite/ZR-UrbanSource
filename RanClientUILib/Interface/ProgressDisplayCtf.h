#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"

class	CProgressTypeCtf;
class	CProgressDisplayCtf : public CUIGroup
{
public:
	enum
	{
		CTF_CAPTURED_SG = NO_ID + 1,
		CTF_START,
		CTF_CAPTURED_PHX,
		CTF_ICO_CAPTURED_SG,
		CTF_ICO_CAPTURED_MP,
		CTF_ICO_CAPTURED_PHX,
		CTF_CAPTURED_MP,
		CTF_END,
		MAX_TYPE = 8
	};

	enum 
	{
		PROGRESS_DISPLAY_CTF_BACK_0 = NO_ID + 1,
		PROGRESS_DISPLAY_CTF_BACK_1,
		MAX_BACK_TYPE = 2
	};

public:
	CProgressDisplayCtf ();
	virtual	~CProgressDisplayCtf ();

public:
	void	CreateSubControl ();

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

public:
	bool	START ( UIGUID cID );
	bool	RESET ( UIGUID cID );
	bool	STOP ();

	bool	KEEP_START ();
	void	KEEP_STOP ();

private:
	CProgressTypeCtf*		m_pCtfBack_TYPE;
	CProgressTypeCtf*		m_pCtfText_TYPE[MAX_TYPE];

	CUIControl*				m_pCtfBack_KEEP;
	CUIControl*				m_pCtfText_KEEP[MAX_TYPE];
};