#pragma	once

#include "../RanClientUILib/Interface/UIWindowEx.h"
#include "../RanClientLib/G-Logic/GLContrlServerMsg.h"
#include "LargeMapWindowSetting.h"

struct GLCHARLOGIC;

class GLMapAxisInfo;
class CBasicTextBox;
class CLargeMapWindowMob;
class CLargeMapWindowImage;
class CLargeMapWindowRadio;
class CLargeMapWindowSetting;
enum
{
	MAX_RADIO_SETTINGS = 4,
};

class CLargeMapWindow : public CUIWindowEx
{
protected:
	enum
	{
		MAP_WINDOW_MAIN_SETTING_RADIO_BUTTON = ET_CONTROL_NEXT,
		MAP_WINDOW_MAIN_INFO_RADIO_BUTTON,
		MAP_WINDOW_MAIN_PARTY_RADIO_BUTTON,
		MAP_WINDOW_MAIN_SEARCH_RADIO_BUTTON,
		MAP_WINDOW_TAP_SETTINGS,
		MAP_WINDOW_TAP_INFO
	};

public:
	CLargeMapWindow ();
	virtual	~CLargeMapWindow ();
	void CreateSubControl();
	
	virtual	void	TranslateUIMessage ( UIGUID cID, DWORD dwMsg );

protected:
	CUIControl*					m_pBackGround;
	CLargeMapWindowImage*		m_pImage;
	CLargeMapWindowRadio*		m_pRadio[MAX_RADIO_SETTINGS];
	CLargeMapWindowSetting*		m_pSetting;
	CLargeMapWindowMob*			m_pInfo;

public:
	void						SetPage(int nIndex);
	void						SetMapAxisInfo ( GLMapAxisInfo &sInfo, CString strMapName );
	void						VISIBLE_TARGET_POS( BOOL bVisible = FALSE );
	void						ClearMobList();
	void						LoadMob(NET_MSG_GENERIC* nmg, GLCHARLOGIC *pCHAR );

	BOOL						m_bSUBSETTING[MAX_SUB_SETTING];
	BOOL						m_bSUBMOTION;

	BOOL						m_bMOB[MAXCROW];
	int							m_nIndex;
	SNATIVEID					m_sNativeID[MAXCROW];
};