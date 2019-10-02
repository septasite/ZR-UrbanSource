#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"
#include "./UIWindowEx.h"
#include "GLCharDefine.h"

class CBasicTextBox;
class	CBasicLineBox;

class CSwPRankingDisplay : public CUIWindowEx
{
	protected:
	enum
	{
	};
private:
	CBasicLineBox*  	m_pBackLine1;
	CBasicLineBox*  	m_pBackLine2;
	CBasicLineBox*  	m_pBackLine3;
	CBasicLineBox*  	m_pBackLine4;
	CUIControl*			m_pBackGround;

	//For Player Ranking
	CBasicTextBox*	m_pSwPRankText;
	CBasicTextBox*	m_pSwPNameText;
	CBasicTextBox*	m_pSwPKillText;
	CBasicTextBox*	m_pSwPDeathText;

	//For School Ranking
	CBasicTextBox*	m_pSwRankText;
	CBasicTextBox*	m_pSwSchoolText;
	CBasicTextBox*	m_pSwKillText;
	CBasicTextBox*	m_pSwDeathText;

	//Gui for Menu Bar Player
	CBasicTextBox*	m_pSwStaticRankText;
	CBasicTextBox*	m_pSwStaticNameText;
	CBasicTextBox*	m_pSwStaticKillText;
	CBasicTextBox*	m_pSwStaticDeathText;

	//Gui for Menu Bar School
	CBasicTextBox*	m_pSwStaticRankText1;
	CBasicTextBox*	m_pSwStaticSchoolText1;
	CBasicTextBox*	m_pSwStaticKillText1;
	CBasicTextBox*	m_pSwStaticDeathText1;

public:
	CSwPRankingDisplay();
	~CSwPRankingDisplay();

	void	CreateSubControl ();
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

public:	
	void	RefreshSwPRanking();
};