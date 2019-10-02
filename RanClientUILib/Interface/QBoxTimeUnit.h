#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"

struct	SNATIVEID;
class	CBasicProgressBar;


class	CQBoxTimeUnit : public CUIGroup
{
public:
	CQBoxTimeUnit (void);
	virtual	~CQBoxTimeUnit (void);

public:
	void	CreateSubControl ();

public:
	virtual	void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

public:
	void	SetLeftTime ( const float& fLeftTime );
	void	SetTime ( const float& fTime );

private:
	float	m_fLEFT_TIME;
	float	m_fLIFE_TIME;

private:
	CBasicProgressBar*	m_pProgressBar;
};