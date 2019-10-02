#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"

class	CBasicTextBox;

class CBasicPkLossDisplay : public CUIGroup
{
public:
	CBasicPkLossDisplay ();
	virtual	~CBasicPkLossDisplay ();

public:
	void	CreateSubControl ();

public:
	virtual void	Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

private:
	CBasicTextBox*	m_pPkLossText;
	DWORD m_dwPkLossBACK;
};