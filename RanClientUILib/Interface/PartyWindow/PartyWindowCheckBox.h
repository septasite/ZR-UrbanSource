#pragma	once

#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../RanClientUILib/Interface/UIWindowEx.h"
#include "GLCharDefine.h"

class CBasicTextBox;
class CPartyWindowCheckBox : public CUIWindowEx
{
public:
	CPartyWindowCheckBox ();
	virtual	~CPartyWindowCheckBox ();
	void CreateSubControl();

private:
	CUIControl*				m_pNormal;
	CUIControl*				m_pFlip;

	CBasicTextBox*			m_pTextTitle;

public:
	void					SetCheck();
	void					ClearText() { m_pTextTitle->ClearText(); }

	BOOL					m_bCHECKED;
	BOOL					IsChecked() { return m_bCHECKED; }

	int						SetTextTitle(CString strText, D3DCOLOR dwColor );
};