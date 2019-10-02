#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"

struct	SNATIVEID;
class	CBasicProgressBar;

class	CPetTimeUnit : public CUIGroup
{
public:
	CPetTimeUnit (void);
	virtual	~CPetTimeUnit (void);

public:
	void	CreateSubControl ();

public:
	virtual	void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

private:
	float	m_fLEFT_TIME;
	float	m_fLIFE_TIME;

private:
	CBasicProgressBar*	m_pProgressBar;
};