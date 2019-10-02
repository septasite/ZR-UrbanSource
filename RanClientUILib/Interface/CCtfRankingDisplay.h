#pragma	once

#include "UIWindowEx.h"
#include "BasicLineBoxEx.h"

class	CBasicTextBox;
class	CBasicTextButton;
class	CCtfRankingPage2;
class	CCtfRankingSelf;

class CCtfRankingDisplay : public CUIWindowEx
{
protected:
	enum
	{
		PAGE_WHOLE = ET_CONTROL_NEXT,
		PAGE_SG,
		PAGE_MP,
		PAGE_PHX,
		BUTTON_CLOSE,
		PAGE_RANKING_0,
		PAGE_RANKING_1,
		PAGE_RANKING_2,
		PAGE_RANKING_3,
		PAGE_MYRANK
	};

	enum
	{
		nMAXPAGE = 4,
	};

private:
	CBasicTextBox*			m_pSwPRankingText;
	CBasicTextButton*		m_pPage_whole;
	CBasicTextButton*		m_pPage_sg;
	CBasicTextButton*		m_pPage_mp;
	CBasicTextButton*		m_pPage_phx;
	CBasicTextButton*		m_pCloseBtn;
	CBasicTextBox*			m_pClubTimeText;

	CBasicLineBoxEx*		m_pCTFBaseLineBoxHead;
	CBasicLineBoxEx*		m_pCTFBaseLineBoxBody;

	CCtfRankingPage2*		m_pCtfRankingPage[nMAXPAGE];
	CCtfRankingSelf*		m_pCtfMyRankingPage;

public:
	CCtfRankingDisplay();
	~CCtfRankingDisplay();

	void	CreateSubControl ();
	CBasicTextButton*	CreateTextButton23 ( const char* szButton, UIGUID ControlID, const char* szText );
	CBasicTextButton*	CreateTextButton ( const char* szButton, UIGUID ControlID, const char* szText );
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );

public:	
	void	RefreshSwPRanking();
	void	RefreshSwPRanking(int page);
	void	SetVisiblePage(int page);
	void	UpdateClubTime( float fCLUBBATTLETime );
};