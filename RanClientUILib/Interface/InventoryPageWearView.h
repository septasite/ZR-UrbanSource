#pragma	once

#include "../EngineUILib/GUInterface/UIGroup.h"
#include "GLItem.h"
#include "UIWindowEx.h"
const DWORD UIMSG_MOUSEIN_WEARSLOTEX = UIMSG_USER1;

class CItemImage;
class CBasicTextButton;
class	CBasicTextBox;
class	CCharacterWindowCharRenderView;

class	CInventoryPageWearView : public CUIGroup
{

private:
	static	const	int	nOUTOFRANGE;

private:
	enum
	{
		ITEM_IMAGE0 = NO_ID + 1,
		ITEM_IMAGE1,
		ITEM_IMAGE2,
		ITEM_IMAGE3,
		ITEM_IMAGE4,
		ITEM_IMAGE5,
		ITEM_IMAGE6,
		ITEM_IMAGE7,
		ITEM_IMAGE8,
		ITEM_IMAGE9,
		ITEM_IMAGE10,
		ITEM_IMAGE11,
		ITEM_IMAGE12,
		ITEM_IMAGE13,
		ITEM_IMAGE14,
		ITEM_IMAGE15,
		ITEM_IMAGE16,
		ITEM_IMAGE17,
		ITEM_IMAGE18,

		ITEM_IMAGE_SIZE = 19,
	};

public:
	CInventoryPageWearView ();
	virtual	~CInventoryPageWearView ();

public:
	void	CreateSubControl ( int nClassType );

private:
	CUIControl*	CreateControl ( const char* szControl );
	CItemImage*	CreateItemImage ( const char* szControl, UIGUID ControlID );

	void	CreateNumberBox ();
	CBasicTextBox*	CreateNumberBox ( const char* szControl );

protected:
	CBasicTextBox*		m_pNumberBoxArray[ITEM_IMAGE_SIZE];
public:
	void	SetNumber ( int nIndex, int nNumber, int nMaxNumber );
	void	SetNumber2 ( int nIndex, int nNumber );
	void	SetNumber3 ( int nIndex, int nNumber );
	void	ResetNumber ( int nIndex );

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	EMSLOT	GetItemSlot ();
private:
	int		m_nIndex;	

public:
	void	LoadItem ( int nIndex, SITEMCUSTOM& ref_sItemCustom );
	SITEMCUSTOM&	GetItem ( int nIndex );
	void	UnLoadItem ( int nIndex );

	void	SetItemIndex ( int nIndex )				{ m_nIndex = nIndex; }
	int		GetItemIndex ()							{ return m_nIndex; }
public:
	EMSLOT	IMAGE2EMSLOT ( int nIndex );

public:
	CUIControl*		m_pMouseOver;

	void ReSetAllItemEx();

	void	SetItemInInventoryEx( int nIndex , SITEMCUSTOM& sItemCustom );
  CCharacterWindowCharRenderView* m_pRender;


	BOOL	m_bRingSwap;
	BOOL	m_bEarringSwap;
private:
	CUIControl*	m_pSlotDisplay[ITEM_IMAGE_SIZE];
	CUIControl*	m_pSlotDisplayDummy[10];
	CItemImage*	m_pItemImage[ITEM_IMAGE_SIZE];
	SITEMCUSTOM	m_ItemCustomArray[ITEM_IMAGE_SIZE];
};