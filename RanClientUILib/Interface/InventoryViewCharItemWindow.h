#pragma	once

#include "UIWindowEx.h"

class	CInventoryPageWearView;

class	CInventoryViewCharItemWindow : public CUIWindowEx
{
protected:
	enum
	{
		INVENTORY_PAGEWEAR_VIEW = ET_CONTROL_NEXT,
	};

public:
	CInventoryViewCharItemWindow ();
	virtual	~CInventoryViewCharItemWindow ();

public:
	void	CreateSubControl ();
	CInventoryPageWearView* m_pPageWearEx;

public:
	virtual	void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );

	void	SetItemInInventory( int nIndex , SITEMCUSTOM& sItemCustom );
};