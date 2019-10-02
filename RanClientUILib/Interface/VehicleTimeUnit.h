#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"

struct	SNATIVEID;
class	CBasicProgressBar;


class	CVehicleTimeUnit : public CUIGroup
{
public:
	CVehicleTimeUnit (void);
	virtual	~CVehicleTimeUnit (void);

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