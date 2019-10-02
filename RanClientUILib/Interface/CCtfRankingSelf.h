#pragma	once

#include "UIWindowEx.h"
#include "BasicLineBoxEx.h"

class	CBasicTextBoxEx;
class	CBasicScrollBarEx;
class	CCtfRankingSlot;

class CCtfRankingSelf : public CUIGroup
{
protected:

	CCtfRankingSlot*	m_pRank;

public:
	CCtfRankingSelf();
	~CCtfRankingSelf();

	void	CreateSubControl();
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

public:
	void	RefreshRankSlot();

};