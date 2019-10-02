#pragma	once

#include "UIWindowEx.h"

struct	SITEMCUSTOM;

class	CInventoryPageWear;
class	CInventoryPageWearEx;
class	CBasicTextButton;
class	CBasicButtonText;

class CRebuildInventoryPage;

//--------------------------------------------------------------------
// RebuildInventoryWindow : √÷¡ÿ«ı
//--------------------------------------------------------------------
class CRebuildInventoryWindow : public CUIWindowEx	// ITEMREBUILD_MARK
{
protected:
	enum
	{
		REBUILDINVENTORY_MONEY_BUTTON = ET_CONTROL_NEXT,
		REBUILDINVENTORY_PLUS_MONEY_BUTTON,
		REBUILDINVENTORY_MINUS_MONEY_BUTTON,
		REBUILDINVENTORY_PAGE,
		REBUILDINVENTORY_POINT_BUTTON,
		INVENTORY_PAGE_BUTTON0,
		INVENTORY_PAGE_BUTTON1,
		INVENTORY_PAGE_BUTTON2,
		INVENTORY_LOCKER_BUTTON,
		INVENTORY_ZOOM_BUTTON,
		INVENTORY_DELETE_BUTTON,
		INVENTORY_RANK_BUTTON,
	};

private:
	CRebuildInventoryPage*	m_pPage;
	CUIControl*			m_bg_white;
	CBasicTextBox*		m_pMoneyTextBox;
	CBasicTextBox*		m_pPointTextBox;
	CBasicTextButton*	m_pPageButton[1];
	int		m_nONE_VIEW_SLOT;

public:
	CRebuildInventoryWindow();
	virtual	~CRebuildInventoryWindow();

public:
	void	CreateSubControl ();
	CBasicButtonText*	m_pButton[4];

public:
	virtual	VOID Update( INT x, INT y, BYTE LB, BYTE MB, BYTE RB, INT nScroll, FLOAT fElapsedTime, BOOL bFirstControl );
	virtual	VOID TranslateUIMessage( UIGUID ControlID, DWORD dwMsg );
	virtual HRESULT RestoreDeviceObjects( LPDIRECT3DDEVICEQ pd3dDevice );

	CBasicTextButton*	CreateTextButton ( const char* szButton, UIGUID ControlID, const char* szText );
	CBasicTextButton*	CreateTextButton24 ( const char* szButton, UIGUID ControlID, const char* szText );
	CBasicButtonText*	CreateButtonBlue ( char* szButton, char* szTextBox, CD3DFontPar* pFont, int nAlign, UIGUID ControlID, CString strText );

	void	INVENTORY();

public:
	void	SetOneViewSlot ( const int& nONE_VIEW_SLOT );
};