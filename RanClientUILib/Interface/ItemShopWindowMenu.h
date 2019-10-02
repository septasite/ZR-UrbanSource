#pragma	once

#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../RanClientUILib/Interface/UIWindowEx.h"
#include "GLCharDefine.h"

class CItemShopWindowMenuButton;
class CItemShopWindowMenu : public CUIWindowEx
{
protected:
	enum 
	{
		MENU_00 = NO_ID + 1,
		MENU_01,
		MENU_02,
		MENU_03,
		MENU_04,
		MENU_05,
		MENU_06,
		MENU_07,
		MENU_08,
		MENU_09,
		MENU_10,
		MENU_11,
		MENU_12,
		MENU_SIZE = 13,
	};
public:
	CItemShopWindowMenu ();
	virtual	~CItemShopWindowMenu ();
	void CreateSubControl();
	virtual void TranslateUIMessage( UIGUID ControlID, DWORD dwMsg );

private:
	CItemShopWindowMenuButton*				m_pMenuButton[13];
	CItemShopWindowMenuButton*				CreateMenu ( CString strKeyword, UIGUID ControlID, CString strOn, CString strOff );
	
	WORD									m_wType;

public:
	void									SetType( WORD wType ) { m_wType = wType; }
	void									SetButtonOn ( WORD wType );
	WORD									GetType() { return m_wType; }
};