#pragma	once

#include "../UIWindowEx.h"

class	CBasicTextButton;
class	CCTFRankPlayer;
class	CCTFRankPlayerSG;
class	CCTFRankPlayerMP;
class	CCTFRankPlayerPHX;
class	CCTFRankSelf;
class	CCTFTowerScore;

//class	CSchoolWarRankingPageRank;
//class	CSchoolWarRankingPageWinner;

class	CCTFRankDisplay : public CUIWindowEx
{
protected:
	enum
	{
		CTF_RANK_BACKGROUND = ET_CONTROL_NEXT,
		CTF_RANK_BUTTON_SCHOOL,
		CTF_RANK_BUTTON_ALL,
		CTF_RANK_BUTTON_SG,
		CTF_RANK_BUTTON_MP,
		CTF_RANK_BUTTON_PHX,
	};

public:
	CCTFRankDisplay ();
	virtual	~CCTFRankDisplay ();

public:
	CBasicTextButton*	CreateTextButton23 ( const char* szButton, UIGUID ControlID, const char* szText );
	void CreateSubControl ();

private:
	int								m_nActivePage;
	CBasicTextButton*				m_pButtonSchool;
	CBasicTextButton*				m_pButtonAll;
	CBasicTextButton*				m_pButtonSG;
	CBasicTextButton*				m_pButtonMP;
	CBasicTextButton*				m_pButtonPHX;

	CCTFRankPlayer*					m_pRankAll;
	CCTFRankPlayerSG*				m_pRankSG;
	CCTFRankPlayerMP*				m_pRankMP;
	CCTFRankPlayerPHX*				m_pRankPHX;
	CCTFRankSelf*					m_pRankSelf;
	CCTFTowerScore*					m_pTowerScore;


public:
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual	void SetVisibleSingle ( BOOL bVisible );

public:
	void	RefreshRanking();
	void	OpenPage( int nPage );

};