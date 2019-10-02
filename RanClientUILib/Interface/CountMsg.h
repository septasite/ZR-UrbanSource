#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"

class CCountMsg : public CUIGroup
{
public:
	CCountMsg ();
	virtual	~CCountMsg ();

public:
	void CreateSubControl();
	CUIControl*	CreateControl( CONST TCHAR* szControl );
	void SetCount( bool bVisible, int nRandomNumber );

public:
	virtual void Update( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

private:
	CUIControl * m_pTEN[10];
	CUIControl * m_pONE[10];
	CUIControl * m_pTENResult[10];
	CUIControl * m_pONEResult[10];

	INT m_nCount;
	INT m_nRandomNumber;
	INT m_nRandomNumberResult;
	float m_fElapsedTime;
};