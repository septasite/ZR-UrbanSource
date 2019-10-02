#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"
#include "../UIWindowEx.h"
#include "GLCharDefine.h"

class CBasicTextBox;
class	CBasicLineBox;

class CCtfTopTenRank : public CUIWindowEx
{
	protected:
	enum
	{
	};
private:
	CBasicLineBox*  	m_pBackLine1;
	CBasicLineBox*  	m_pBackLine2;
	CUIControl*			m_pBackGround;

	//For Player Ranking
	CBasicTextBox*	m_pRrPRankText;
	CBasicTextBox*	m_pRrPNameText;
	CBasicTextBox*	m_pRrPKillText;
	CBasicTextBox*	m_pRrPDeathText;

	//Gui for Menu Bar Player
	CBasicTextBox*	m_pRrStaticRankText;
	CBasicTextBox*	m_pRrStaticNameText;
	CBasicTextBox*	m_pRrStaticKillText;
	CBasicTextBox*	m_pRrStaticDeathText;

public:
	CCtfTopTenRank();
	~CCtfTopTenRank();

	void	CreateSubControl ();
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

public:	
	void	RefreshRrPRanking();
};