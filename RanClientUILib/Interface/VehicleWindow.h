#pragma	once

#include "UIWindowEx.h"
#include "GLItem.h"

////////////////////////////////////////////////////////////////////
//	사용자 메시지 정의
const DWORD UIMSG_MOUSEIN_VEHICLE_WEARSLOT = UIMSG_USER1;
////////////////////////////////////////////////////////////////////

class	CBasicProgressBar;
class	CBasicTextBox;
class	CItemImage;
class	CBasicLineBox;

class	CVehicleWindow : public CUIWindowEx
{
	enum
	{
		SLOT_SKIN_IMAGE_TYPE0 = ET_CONTROL_NEXT,
		SLOT_PARTS_IMAGE_TYPE0,
		SLOT_PARTS_IMAGE_TYPE1,
		SLOT_PARTS_IMAGE_TYPE2,	
		SLOT_PARTS_IMAGE_TYPE3,
		SLOT_PARTS_IMAGE_TYPE4,
		SLOT_PARTS_IMAGE_TYPE5,

		VEHICLE_BATTERY_TEXT,
		VEHICLE_QUESTION_BUTTON,
		FERRARI_BUTTON,
		SLOT_PARTS_IMAGE_TYPE01,
		SLOT_PARTS_IMAGE_TYPE02,
		SLOT_PARTS_IMAGE_TYPE03,	
		SLOT_PARTS_IMAGE_TYPE04,
		SLOT_PARTS_IMAGE_TYPE05,
		SLOT_PARTS_IMAGE_TYPE06,
		SLOT_PARTS_IMAGE_TYPE07,
		SLOT_PARTS_IMAGE_TYPE08,
		SLOT_PARTS_IMAGE_TYPE09,
		SLOT_PARTS_IMAGE_TYPE10,
		SLOT_PARTS_IMAGE_TYPE11,	
		SLOT_PARTS_IMAGE_TYPE12,
		SLOT_PARTS_IMAGE_TYPE13,
		SLOT_PARTS_IMAGE_TYPE14,
		SLOT_PARTS_IMAGE_TYPE15,

		SLOT_IMAGE_SIZE = 7
	};

	CBasicTextBox* m_pVehicleName;
	CBasicTextBox* m_pVehicleType; 
	CUIControl*	m_pMouseOver;

	//CUIControl* m_pSlotBack[VEHICLE_TYPE_SIZE];
	CUIControl*	m_pSlotDisplay[SLOT_IMAGE_SIZE];
	CItemImage*	m_pSlotImage[SLOT_IMAGE_SIZE];
	SITEMCUSTOM	m_ItemCustomArray[SLOT_IMAGE_SIZE];

	CBasicTextBox *	m_pBatteryText;
	CBasicLineBox*  pBasicLineBox;
	CBasicProgressBar * m_pBattery;
	CUIControl*		m_bg_white;
	CBasicButton* m_pButtonBooster;
	CBasicButton* m_pButtonQuestion;
	CUIControl* m_pButton[4];
	CUIControl* m_pButtonSet[4];
	CBasicTextBox* m_pButtonText[4];
	CBasicButton*	pButtonQue;
	CBasicButton*	pFerrariButton;
	CUIControl*	m_ButtonSet[15];

	UIGUID	m_RollOverID;

public:
	CVehicleWindow ();
	virtual	~CVehicleWindow ();

public:
	void CreateSubControl (int nClassType );
	void VEHICLE0();
	void VEHICLE1();
	void VEHICLE2();
	void VEHICLE3();

private:
	CBasicTextBox * CreateTextBox( char* szKeyword, CD3DFontPar* pFont );
	CUIControl*	CreateControl( const char* szControl );
	CItemImage*	CreateItemImage( const char* szControl, UIGUID ControlID );

public:
	virtual	void SetVisibleSingle ( BOOL bVisible );
	virtual	void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );

public:
	void LoadItem ( int nIndex, SITEMCUSTOM& ref_sItemCustom );
	void UnLoadItem ( int nIndex );
	SITEMCUSTOM& GetItem ( int nIndex )			{ return m_ItemCustomArray[nIndex]; }

private:
	int m_nBatteryBack;

	void SetName( const std::string & strName );
	void SetType( const std::string & strType );
	void SetBattery( int nNOW );

public:
	EMSUIT IMAGE2EMSLOT ( UIGUID ControlID );
};