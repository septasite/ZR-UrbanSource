#pragma	once

#include "UIWindowEx.h"

class	CBasicLineBox;
class	CBasicTextBox;
class	CSWRankingSlot;

#include "GLGaeaClient.h"


class CSWRankingWindow : public CUIWindowEx
{
protected:
	enum
	{
		SW_RANKING_SLOT_01 = ET_CONTROL_NEXT,
		SW_RANKING_SLOT_02,
		SW_RANKING_SLOT_03,
		SW_RANKING_SLOT_04,
		SW_RANKING_SLOT_05,
		SW_RANKING_SLOT_06,
		SW_RANKING_SLOT_07,
		SW_RANKING_SLOT_08,
		SW_RANKING_SLOT_09,
		SW_RANKING_SLOT_10,

	};

private:

	CBasicTextBox*	m_pName;
	CBasicTextBox*	m_pKill;
	CBasicTextBox*	m_pDeath;
	CBasicTextBox*	m_pRank;

	CBasicTextBox*	m_pDWRankingText;

	CUIControl*		m_bg_white;
	CBasicLineBox*  m_pBackLine1;

	CSWRankingSlot*		m_pSWRankingSlot[10];



public:
	CSWRankingWindow ();
	virtual	~CSWRankingWindow ();

	//void	SetSchool ( int nSchoolType );
	//CUIControl*			m_pSchool[3];

public:
	void	CreateSubControl ();
	void	SetRanking ( CSWRankingSlot* pSWRankingSlot, PGLCHARCLIENT *pChar, const int nSlotNumber, CString strName, int nSchoolType, int nClassType, int nKill, int nDeath );

	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	
};