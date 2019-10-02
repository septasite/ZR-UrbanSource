#pragma	once

#include "../Interface/UIWindowEx.h"
#include "GLItem.h"
#include "GLVehicle.h"
#include "GLDefine.h"

class	CItemImage;
class	CItemImageVehicle;
class	CBasicTextBox;
class	CBasicButtonRadio;
class	CCharacterWindowVehicleRender;

const DWORD UIMSG_MOUSEIN_VEHICLE_NEWWEARSLOT = UIMSG_USER1;

class CCharacterWindowVehicle : public CUIGroup
{
protected:
	enum
	{
		SLOT_SKIN_IMAGE_TYPE0 = NO_ID + 1,
		SLOT_PARTS_IMAGE_TYPE0,
		SLOT_PARTS_IMAGE_TYPE1,
		SLOT_PARTS_IMAGE_TYPE2,	
		SLOT_PARTS_IMAGE_TYPE3,
		SLOT_PARTS_IMAGE_TYPE4,
		SLOT_PARTS_IMAGE_TYPE5,	
		SLOT_VEHICLE_LIST0,
		SLOT_VEHICLE_LIST1,
		SLOT_VEHICLE_LIST2,
		SLOT_VEHICLE_LIST3,
		SLOT_VEHICLE_LIST4,
		SLOT_VEHICLE_LIST5,
		SLOT_VEHICLE_LIST6,
		SLOT_VEHICLE_POINTSHOP_LIST0,
		SLOT_VEHICLE_POINTSHOP_LIST1,
		SLOT_VEHICLE_POINTSHOP_LIST2,
		SLOT_VEHICLE_POINTSHOP_LIST3,
		SLOT_VEHICLE_POINTSHOP_LIST4,
		SLOT_VEHICLE_POINTSHOP_LIST5,
		SLOT_VEHICLE_POINTSHOP_LIST6,
		SLOT_VEHICLE_POINTSHOP_LIST7,
		SLOT_VEHICLE_ACTIVE,
		VEHICLE_BATTERY_TEXT,
		LIST_BUTTON_PREV,
		LIST_BUTTON_NEXT,
		LIST_POINTSHOP_BUTTON_PREV,
		LIST_POINTSHOP_BUTTON_NEXT,
		LIST_POINTSHOP_BUTTON_BOARD,
		LIST_POINTSHOP_BUTTON_BIKE,
		LIST_POINTSHOP_BUTTON_PARTS,
		LIST_POINTSHOP_BUTTON_BATTERY,
		BOOSTER_ICON_ON,
		BOOSTER_ICON_OFF,
		MOVE_CHECKBOX,

		SLOT_IMAGE_SIZE = 7,
		SLOT_VEHICLE_LIST = 7,
		SLOT_VEHICLE_POINTSHOP_LIST = 8,
	};

public:
    CCharacterWindowVehicle ();
	virtual	~CCharacterWindowVehicle ();

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual	void SetVisibleSingle ( BOOL bVisible );

public:
	void	CreateSubControl ();

private:
	CBasicTextBox*	CreateStaticControl ( char* szConatrolKeyword, CD3DFontPar* pFont, int nAlign, const UIGUID& cID = NO_ID );
	CUIControl*		CreateControl ( const char* szControl, const UIGUID& cID = NO_ID );
	CBasicButton*	CreateFlipButton ( char* szButton, char* szButtonFlip, char* szButtonMouseOver, UIGUID ControlID, WORD wFlipType );
	CItemImageVehicle*	CreateItemImageVehicle( const char* szControl, UIGUID ControlID );
	CBasicTextBox * CreateTextBox( char* szKeyword, CD3DFontPar* pFont );
	CBasicTextBox * CreateTextBoxCenter( char* szKeyword, CD3DFontPar* pFont );
	CBasicButtonRadio * CreateRadioButton( char* szKeyword, CD3DFontPar* pFont, int nTextSize, UIGUID ControlID );


private:
	CCharacterWindowVehicleRender* m_pRender;
	CUIControl*	m_pSlotDisplay[SLOT_IMAGE_SIZE];
	CItemImageVehicle*	m_pSlotImage[SLOT_IMAGE_SIZE];

	CUIControl*	m_pMouseOver;

	CItemImageVehicle*	m_pActiveVehicle;
	CItemImageVehicle*	m_pVehicleList[SLOT_VEHICLE_LIST];
	CItemImageVehicle*	m_pVehiclePointShopList[SLOT_VEHICLE_POINTSHOP_LIST];

	CBasicButton* m_pListPrev;
	CBasicButton* m_pListNext;
	CBasicTextBox* m_pListNum;

	CBasicButton* m_pListPointShopPrev;
	CBasicButton* m_pListPointShopNext;
	CBasicTextBox* m_pListPointShopNum;

	CBasicTextBox* m_pVehicleName;
	CBasicTextBox* m_pVehicleSpeed; 
	CBasicTextBox* m_pBatteryText;
	CBasicTextBox* m_pBoostText;

	CBasicButtonRadio*	m_pBoardButton;
	CBasicButtonRadio*	m_pBikeButton;
	CBasicButtonRadio*	m_pPartsButton;
	CBasicButtonRadio*	m_pBatteryButton;

	CUIControl*	m_pBoostIconOff;
	CUIControl*	m_pBoostIconOn;

	CBasicButton*		m_pMoveAnim;
	CBasicTextBox*		m_pMoveAnimText;

public:
	void LoadItem ( int nIndex, SITEMCUSTOM& ref_sItemCustom );
	void UnLoadItem ( int nIndex );

	void	LoadActiveVehicle();
	void	UnLoadActiveVehicle();
	void	LoadVehicleList( int nPage );
	void	UnLoadVehicleList ();
	void	LoadOwnVehicle();
	void	LoadListVehicle( int nSelect );
	void	LoadListPointShop( int nSelect );
	void	ChangePointShopCategory( int nSelect );

public:
	EMSUIT IMAGE2EMSLOT ( UIGUID ControlID );

public:
	typedef std::vector<SITEMCUSTOM>		VECVEHICLEID;
	typedef VECVEHICLEID::iterator			VECVEHICLEID_ITER;
	VECVEHICLEID	m_vecID;
	int				nCurrentPage;
	int				nCurrentPageShop;

	bool	bOWnVehicle;
	void	InitVehicle();
	void	ResetVehicleInfo();
	int		m_nBatteryBack;

public:
	void	ClearRender();
};