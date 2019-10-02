#pragma	once

#include "../RanClientUILib/Interface/UIWindowEx.h"

class CLargeMapWindowCheckBox;

enum
{
	MAX_SUB_SETTING = 9,
	MAX_SUB_MOTION = 1,
};

class CLargeMapWindowSetting : public CUIWindowEx
{
protected:
	enum
	{
		LARGEMAP_WINDOW_SETTING = NO_ID + 1,
		LARGEMAP_WINDOW_SETTING0,
		LARGEMAP_WINDOW_SETTING1,
		LARGEMAP_WINDOW_SETTING2,
		LARGEMAP_WINDOW_SETTING3,
		LARGEMAP_WINDOW_SETTING4,
		LARGEMAP_WINDOW_SETTING5,
		LARGEMAP_WINDOW_SETTING6,
		LARGEMAP_WINDOW_SETTING7,
		LARGEMAP_WINDOW_SETTING8,

		MAP_WINDOW_SETTING_TAP_ACTION_SETTING_TEXT,
		MAP_WINDOW_SETTING_TAP_AUTO_RIDE_VEHICLE_TEXT,
	};

public:
	CLargeMapWindowSetting ();
	virtual	~CLargeMapWindowSetting ();
	void CreateSubControl();
	virtual void TranslateUIMessage ( UIGUID cID, DWORD dwMsg );

	CLargeMapWindowCheckBox*	CreateCheckBox( const char* strKeyword, UIGUID cID, CString strText );

private:
	CLargeMapWindowCheckBox*	m_pSetting;
	CLargeMapWindowCheckBox*	m_pSubSetting[MAX_SUB_SETTING];
	
	CLargeMapWindowCheckBox*	m_pMotion;
	CLargeMapWindowCheckBox*	m_pSubMotion;
};