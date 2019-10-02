#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"
#include "GLInventory.h"

class	CItemSlotEx;
class	CBasicScrollBarEx;
class	CBasicButton;
class	CBasicTextBox;
class	CD3DFontPar;
struct	SINVENITEM;

//--------------------------------------------------------------------
// RebuildInventoryPage : √÷¡ÿ«ı
//--------------------------------------------------------------------
class CRebuildInventoryPage : public CUIGroup	// ITEMREBUILD_MARK
{
private:
static	const	int	nSTARTLINE;
static	const	int	nOUTOFRANGE;

private:
	enum
	{
		nONE_VIEW_SLOT_DEFAULT = 4,
		nMAX_ONE_VIEW_SLOT = 10,
		nMAX_ONE_VIEW_SLOT2 = 20,
		nMAX_ONE_VIEW_SLOT3 = 30,
	};

protected:
	enum
	{
		EM_INVENSIZE_Y_FORCE = EM_INVENSIZE_Y,
		ITEM_SLOT00 = NO_ID + 1,
		ITEM_SLOT01,ITEM_SLOT02,ITEM_SLOT03,ITEM_SLOT04,ITEM_SLOT05,ITEM_SLOT06,ITEM_SLOT07,ITEM_SLOT08,ITEM_SLOT09,
		ITEM_SLOT10,ITEM_SLOT11,ITEM_SLOT12,ITEM_SLOT13,ITEM_SLOT14,ITEM_SLOT15,ITEM_SLOT16,ITEM_SLOT17,ITEM_SLOT18,ITEM_SLOT19,
		ITEM_SLOT20,ITEM_SLOT21,ITEM_SLOT22,ITEM_SLOT23,ITEM_SLOT24,ITEM_SLOT25,ITEM_SLOT26,ITEM_SLOT27,ITEM_SLOT28,ITEM_SLOT29,
		ITEM_SLOT_END = ITEM_SLOT00 + EM_INVENSIZE_Y_FORCE,
		INVENTORY_BUTTON0,
		INVENTORY_BUTTON1,
		INVENTORY_BUTTON2,
	};

public:
	CRebuildInventoryPage();
	virtual	~CRebuildInventoryPage();

public:
	VOID CreateSubControl();

	void	UpdateBLOCK ();

	void	INVENTORY1();
	void	INVENTORY2();
	void	INVENTORY3();

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );

protected:
	void	ResetAllItemSlotRender ( int index ,int nTotal );
	void	SetItemSlotRender ( int nStartIndex, int nTotal );

protected:
	CItemSlotEx*	CreateItemSlot ( CString strKeyword, UIGUID ControlID );
	CUIControl*	CreateControl ( const char* szControl );

	CUIControl*	m_Button[3];
	CUIControl*	m_ButtonSet[3];
	CBasicTextBox*	m_ButtonText[3];

public:
	void	SetItemIndex ( int nPosX, int nPosY );
	void	GetItemIndex ( int* pnPosX, int* pnPosY );

public:
	void	SetOneViewSlot ( const int& nMAX_ONE_VIEW );

public:
	VOID LoadItemPage( GLInventory &ItemData );
	VOID LoadItem( SINVENITEM& ref_InvenItem );
	
	SINVENITEM&	GetItem ( int nPosX, int nPosY );

public:
	void	UnLoadItemPage ();
	void	UnLoadItem ( int nPosX, int nPosY );

public:
	VOID ResetAllFlipItem();
	VOID UpdateFlipItem( GLInventory& ref_Inventory );
	VOID UpdateFlipItem( SINVEN_POS& ref_RebuildItem );

private:
	CItemSlotEx*	m_pItemSlotArray[EM_INVENSIZE_Y_FORCE];
	CUIControl*	m_pItemSlotArrayDummy[nMAX_ONE_VIEW_SLOT3];
	CBasicButton*	m_pPageButton[3];

	//CBasicScrollBarEx*	m_pScrollBar;
	int		m_nPosX;
	int		m_nPosY;
	int		m_nCurPos;
	int		m_nONE_VIEW_SLOT;

};