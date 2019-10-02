#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"

class	CBasicTextBox;

class CBasicRebornDisplay : public CUIGroup
{
public:
	CBasicRebornDisplay ();
	virtual	~CBasicRebornDisplay ();

public:
	void	CreateSubControl ();

public:
	virtual void	Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

private:
	CBasicTextBox*	m_pRebornText;
	DWORD m_nRebornBACK;
};