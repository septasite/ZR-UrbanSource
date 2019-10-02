#pragma	once

#include "../UIWindowEx.h"

class CTyrannyWinnerRankSlot;
class CBasicScrollBarEx;

class	CTyrannyWinnerRank : public CUIWindowEx
{
protected:
	enum
	{
		RANKPLAYER_SCROLLBAR = ET_CONTROL_NEXT,
	};

	enum
	{
		TW_PLAYER_SLOT_MAX = 10,
	};
public:
	CTyrannyWinnerRank ();
	virtual	~CTyrannyWinnerRank ();

public:
	void CreateSubControl ();

private:
	int						m_nActivePage;
	CUIControl*				m_pBackGround;
	CTyrannyWinnerRankSlot*	m_pRankSlot[TW_PLAYER_SLOT_MAX];
	CBasicScrollBarEx*		m_pScrollBar;
	
	int		m_nStart;
	int		m_nTotal;

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual	void SetVisibleSingle ( BOOL bVisible );

public:
	void	RefreshRanking();
	void	RenderView();
};