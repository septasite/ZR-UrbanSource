#pragma	once

#include "../RanClientUILib/Interface/UIWindowEx.h"

class CBasicTextBox;
class CLargeMapWindowRadio : public CUIWindowEx
{
public:
	CLargeMapWindowRadio ();
	virtual	~CLargeMapWindowRadio ();
	void CreateSubControl();

private:
	CUIControl*				m_pNormal;
	CUIControl*				m_pFlip;

	CBasicTextBox*			m_pText;

public:
	void					SetRadioOn(BOOL bFLIP);
	int						SetRadioText(CString strText);
};