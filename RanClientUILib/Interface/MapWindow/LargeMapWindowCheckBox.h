#pragma	once

#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../RanClientUILib/Interface/UIWindowEx.h"
#include "GLCharDefine.h"

class CBasicTextBox;
class CLargeMapWindowCheckBox : public CUIWindowEx
{
public:
	CLargeMapWindowCheckBox ();
	virtual	~CLargeMapWindowCheckBox ();
	void CreateSubControl();

private:
	CUIControl*				m_pNormal;
	CUIControl*				m_pFlip;

	CUIControl*				m_pIcon;

	CBasicTextBox*			m_pText;
	CBasicTextBox*			m_pTextTitle;

public:
	void					SetCheck();
	void					SetText(CString strText, D3DCOLOR dwColor, SNATIVEID sNativeID = NATIVEID_NULL());
	void					ClearText() { m_pText->ClearText(); }

	void					ForceCheck();
	void					ForceUnCheck();

	SNATIVEID				m_sNativeID;
	SNATIVEID				GetID() { return m_sNativeID; }
	BOOL					IsValidID() { return m_sNativeID != NATIVEID_NULL(); }

	BOOL					m_bCHECKED;
	BOOL					IsChecked() { return m_bCHECKED; }

	int						SetTextTitle(CString strText, D3DCOLOR dwColor );
};