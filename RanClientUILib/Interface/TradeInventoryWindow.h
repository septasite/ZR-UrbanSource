#pragma	once

#include "UIWindowEx.h"

struct	SITEMCUSTOM;

class	CInventoryPageWear;
class	CInventoryPageWearEx;
class	CBasicTextButton;
class	CBasicButtonText;


class	CTradeInventoryPage;
class	CTradeInventoryWindow : public CUIWindowEx
{
protected:
	enum
	{
		TRADEINVENTORY_MONEY_BUTTON = ET_CONTROL_NEXT,
		TRADEINVENTORY_PLUS_MONEY_BUTTON,
		TRADEINVENTORY_MINUS_MONEY_BUTTON,
		TRADEINVENTORY_PAGE,
		TRADEINVENTORY_POINT_BUTTON,
		INVENTORY_PAGE_BUTTON0,
		INVENTORY_PAGE_BUTTON1,
		INVENTORY_PAGE_BUTTON2,
		INVENTORY_LOCKER_BUTTON,
		INVENTORY_ZOOM_BUTTON,
		INVENTORY_DELETE_BUTTON,
		INVENTORY_RANK_BUTTON,
	};

public:
	CTradeInventoryWindow ();
	virtual	~CTradeInventoryWindow ();

public:
	void	CreateSubControl ();
	CBasicButtonText*	m_pButton[4];

public:
	virtual	void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual HRESULT RestoreDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice );

	CBasicTextButton*	CreateTextButton ( const char* szButton, UIGUID ControlID, const char* szText );
	CBasicTextButton*	CreateTextButton24 ( const char* szButton, UIGUID ControlID, const char* szText );
	CBasicButtonText*	CreateButtonBlue ( char* szButton, char* szTextBox, CD3DFontPar* pFont, int nAlign, UIGUID ControlID, CString strText );

	void	TRADEINVENTORY();

public:
	void	SetOPENER ( bool bOPENER );

private:
	void	SetMoney ( LONGLONG Money );
	bool	IsTurnITEM ( SITEMCUSTOM& sItemCustom );

public:
	void	SetOneViewSlot ( const int& nONE_VIEW_SLOT );
	const int& GetOneViewSlot () const;

private:
	CTradeInventoryPage*	m_pPage;
	CUIControl*			m_bg_white;
	CBasicTextBox*		m_pMoneyTextBox;
	CBasicTextBox*		m_pPointTextBox;
	CBasicTextButton*	m_pPageButton[1];

	bool	m_bTRADE_MODE;
	bool	m_bOPENER;

	int		m_nONE_VIEW_SLOT;
};