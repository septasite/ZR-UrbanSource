#pragma	once

#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../RanClientUILib/Interface/UIWindowEx.h"
#include "GLCharDefine.h"

class CCompoundWindowMenuButton;
class CCompoundWindowMenu : public CUIWindowEx
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
	};
public:
	CCompoundWindowMenu ();
	virtual	~CCompoundWindowMenu ();
	void CreateSubControl();
	virtual void TranslateUIMessage( UIGUID ControlID, DWORD dwMsg );

private:
	CCompoundWindowMenuButton*				m_pMenuButton[13];
	CCompoundWindowMenuButton*				CreateMenu ( CString strKeyword, UIGUID ControlID, CString strOn, CString strOff );

	WORD									m_wType;

public:
	void									SetType( WORD wType ) { m_wType = wType; }
	WORD									GetType() { return m_wType; }
};