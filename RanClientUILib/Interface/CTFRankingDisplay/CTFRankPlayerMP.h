#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"

class	CBasicTextBox;
class	CBasicScrollBarEx;
class	CCTFRankPlayerBase;
class	CCTFRankPlayerSlot;

class	CCTFRankPlayerMP : public CUIGroup
{
private:
	enum
	{
		RANKPLAYER_SCROLLBAR = NO_ID + 1,
	};

	enum
	{
		CTF_PLAYER_SLOT_MAX = 10,
	};

public:
	CCTFRankPlayerMP ();
	virtual	~CCTFRankPlayerMP ();

public:
	void	CreateSubControl ();

	CCTFRankPlayerBase*		m_pBase;
	CCTFRankPlayerSlot*		m_pSlot[CTF_PLAYER_SLOT_MAX];
	CBasicScrollBarEx*		m_pScrollBar;

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual	void SetVisibleSingle ( BOOL bVisible );

	int		m_nStart;
	int		m_nTotal;

public:
	void	RefreshRanking();
	void	RenderView();

};