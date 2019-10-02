#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"

class	CBasicTextBox;
class	CBasicScrollBarEx;
class	CCTFTowerStatusSlot;

const DWORD UIMSG_MOUSEIN_CTF_SCROLLBAR = UIMSG_USER1;

class	CCTFTowerStatus : public CUIGroup
{
private:
	enum
	{
		TOWERSCORE_SCROLLBAR = NO_ID + 1,
	};

	enum
	{
		TOWERSCORE_SLOT_MAX = 6,
	};

public:
	CCTFTowerStatus ();
	virtual	~CCTFTowerStatus ();

public:
	void	CreateSubControl ();

	CCTFTowerStatusSlot*		m_pSlot[TOWERSCORE_SLOT_MAX];
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