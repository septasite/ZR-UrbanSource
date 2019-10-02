#pragma	once

#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../RanClientUILib/Interface/UIWindowEx.h"
#include "GLCharDefine.h"

class CBasicTextBox;
class CItemRebuildOption : public CUIWindowEx
{
public:
	CItemRebuildOption ();
	virtual	~CItemRebuildOption ();
	void CreateSubControl();

private:
	CUIControl*				m_pNormal;
	CUIControl*				m_pFlip;

	CBasicTextBox*			m_pTextTitle;

	BOOL					m_bCHECKED;

public:
	void					SetCheck();
	void					ClearText() { m_pTextTitle->ClearText(); }

	BOOL					IsChecked() { return m_bCHECKED; }

	int						SetTextTitle(CString strText, D3DCOLOR dwColor );

	void					ShowCheckOption();
	void					HideCheckOption();

	void					ManageOption( BOOL bOPT );
};