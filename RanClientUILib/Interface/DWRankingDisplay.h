#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"

class CBasicTextBox;

class CDWRankingDisplay : public CUIGroup
{
private:
	CBasicTextBox*	m_pDWRankingText;
	//CBasicTextBox*	m_pDWRankingSchoolText;

public:
	CDWRankingDisplay();
	~CDWRankingDisplay();

	void	SetSchool ( int nSchoolType );
	CUIControl*			m_pSchool[3];

	void	CreateSubControl ();
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

protected:
	CUIControl*		CreateControl ( const char* szControl );

public:	
	void	RefreashDWRanking();
};