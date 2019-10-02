#include "../EngineUILib/GUInterface/UIGroup.h"
#include "GLDefine.h"
#include "GLCharDefine.h"

class	CItemSlot;
class	GLInventory;
struct	SINVENITEM;

class	CInterestItem : public CUIGroup
{
private:
static	const	int	nSTARTLINE;
static	const	int	nOUTOFRANGE;

protected:
	enum
	{		
		nMAX_ONE_VIEW_SLOT_NEW = 5
	};

	enum
	{
		ITEM_SLOT0 = NO_ID + 1,
		ITEM_SLOT1,
		ITEM_SLOT2,
		ITEM_SLOT3,
		ITEM_SLOT_END = ITEM_SLOT0 + INTEREST_INVEN_Y,
	};

public:
	CInterestItem ();
	virtual	~CInterestItem ();

public:
	void CreateSubControl ();

public:
	void	SetItemIndex ( int nPosX, int nPosY );
	void	GetItemIndex ( int* pnPosX, int* pnPosY );

public:
	void	LoadItemPage ( GLInventory &ItemData );
	void	LoadInterestItem ( GLInventory &ItemData );
	void	LoadItem (SINVENITEM& ref_InvenItem );
	void	SetUnUse();
	void	SetUnBuy();

	SINVENITEM&	GetItem ( int nPosX, int nPosY );

public:
	void	UnLoadItemPage ();
	void	UnLoadItem ( int nPosX, int nPosY );
	DWORD	GetPriceItem( int index );
	CString	GetNameItem( int index );

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );

protected:
	void	ResetAllItemSlotRender ( int nTotal );
	void	SetItemSlotRender ( int nStartIndex, int nTotal );

protected:
	CItemSlot*	CreateItemSlot ( CString strKeyword, UIGUID ControlID );
	CUIControl*	CreateControl ( const char* szControl );

private:
	int		m_nPosX;
	int		m_nPosY;
	int		m_nCurPos;
	int		m_PosXNew;
	int		m_PosYNew;
	DWORD	m_pPriceItem[5];
	CString m_pNameItem[5];

private:
	CItemSlot*	m_pItemSlotArray[INTEREST_INVEN_Y];
	CUIControl*	m_pItemSlotArrayDummy[nMAX_ONE_VIEW_SLOT_NEW];

};