#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"
#include "GLDefine.h"
#include "GLCharDefine.h"

class	CItemSlot;
class	CBasicButton;
class	CBasicTextBox;
class	CBasicScrollBarEx;
class	GLInventory;
class	CD3DFontPar;
struct	SINVENITEM;

class	CItemBankPage : public CUIGroup
{
static	const	int	nSTARTLINE;
static	const	int	nOUTOFRANGE;

protected:
	enum
	{
		ITEMBANK_INVEN_X = 6,
		ITEMBANK_INVEN_Y = 40,
		nMAX_ONE_VIEW_SLOT = 40
	};

	enum
	{
		ITEM_SLOT0 = NO_ID + 1,
		ITEM_SLOT_END = ITEM_SLOT0 + ITEMBANK_INVEN_Y,
		ITEMBANK_BUTTON0,
		ITEMBANK_BUTTON1,
		ITEMBANK_BUTTON2,
		ITEMBANK_BUTTON3,
	};

public:
	CItemBankPage ();
	virtual	~CItemBankPage ();

public:
	void CreateSubControl ();

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );

public:
	void	SetItemIndex ( int nPosX, int nPosY );
	void	GetItemIndex ( int* pnPosX, int* pnPosY );
	void	ITEMBANK1();
	void	ITEMBANK2();
	void	ITEMBANK3();
	void	ITEMBANK4();

public:
	void	LoadItemPage ( GLInventory &ItemData );
	void	LoadItem ( SINVENITEM& ref_InvenItem );

	SINVENITEM&	GetItem ( int nPosX, int nPosY );

public:
	void	UnLoadItemPage ();
	void	UnLoadItem ( int nPosX, int nPosY );

private:
	void	ResetAllItemSlotRender ( int index,int nTotal );
	void	SetItemSlotRender ( int nStartIndex, int nTotal );

private:
	CItemSlot*	CreateItemSlot ( CString strKeyword, UIGUID ControlID );
	CUIControl*	CreateControl ( const char* szControl );

private:
	CItemSlot*	m_pItemSlotArray[ITEMBANK_INVEN_Y];
	CUIControl*	m_pItemSlotArrayDummy[nMAX_ONE_VIEW_SLOT];
	CUIControl*	m_Button[4];
	CUIControl*	m_ButtonSet[4];
	CBasicTextBox*	m_ButtonText[4];
	//CBasicScrollBarEx*	m_pScrollBar;

private:
	int		index;
	int		m_nPosX;
	int		m_nPosY;
	int		m_nCurPos;
};