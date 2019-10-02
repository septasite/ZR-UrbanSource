#pragma	once

#include "../EngineUiLib/GUInterface/UIGroup.h"
#include "GLItem.h"

const DWORD UIMSG_MOUSEIN_NEWWEARSLOT = UIMSG_USER1;

class	CItemImageCharWear;

class	CCharacterWindowCharWear : public CUIGroup
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

		ITEM_IMAGE_SIZE = 17,
	};

public:
	CCharacterWindowCharWear ();
	virtual	~CCharacterWindowCharWear ();

public:
	void	CreateSubControl ();

private:
	CUIControl*	CreateControl ( const char* szControl );
	CItemImageCharWear*	CreateItemImage ( const char* szControl, UIGUID ControlID );

public:
	void	SetItemIndex ( int nIndex )				{ m_nIndex = nIndex; }
	int		GetItemIndex ()							{ return m_nIndex; }

	EMSLOT	GetItemSlot ();

public:
	void	LoadItem ( int nIndex, SITEMCUSTOM& ref_sItemCustom );
	SITEMCUSTOM&	GetItem ( int nIndex );
	void	UnLoadItem ( int nIndex );

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );

public:
	EMSLOT	IMAGE2EMSLOT ( int nIndex );

private:
	CUIControl*		m_pMouseOver;

	BOOL m_bRingSwap;
	BOOL m_bEarringSwap;

private:
	CUIControl*		m_pSlotDisplay[ITEM_IMAGE_SIZE];
	CItemImageCharWear*		m_pItemImage[ITEM_IMAGE_SIZE];
	SITEMCUSTOM		m_ItemCustomArray[ITEM_IMAGE_SIZE];

private:
	int		m_nIndex;	
};