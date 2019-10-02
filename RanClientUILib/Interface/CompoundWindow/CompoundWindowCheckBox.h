#pragma	once

#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../RanClientUILib/Interface/UIWindowEx.h"
#include "GLCharDefine.h"

class CBasicTextBox;
class CCompoundWindowCheckBox : public CUIWindowEx
{
public:
	CCompoundWindowCheckBox ();
	virtual	~CCompoundWindowCheckBox ();
	void CreateSubControl();

private:
	CUIControl*				m_pNormal;
	CUIControl*				m_pFlip;

	CUIControl*				m_pIcon;

	CBasicTextBox*			m_pText;
	CBasicTextBox*			m_pTextTitle;

public:
	void					SetCheck();
	void					SetText(CString strText, D3DCOLOR dwColor );
	void					ClearText() { m_pText->ClearText(); }

	void					ForceCheck();
	void					ForceUnCheck();

	BOOL					m_bCHECKED;
	BOOL					IsChecked() { return m_bCHECKED; }

	int						SetTextTitle(CString strText, D3DCOLOR dwColor );
};