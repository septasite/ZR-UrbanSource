#pragma once

#include "GLItemMan.h"
#include "GLItem.h"
#include "GLItemDef.h"

class	CRanManagerUserTab;
class RanAddItemShop : public CPropertyPage
{
DECLARE_DYNAMIC(RanAddItemShop)

public:
	RanAddItemShop(LOGFONT logfont);
	virtual ~RanAddItemShop();

	CComboBox		m_cCtg;
	CComboBox		m_cSec;

// Dialog Data
	enum { IDD = IDD_DIALOG1, IDH = IDR_HTML_RANADDITEMSHOP };

protected:
	CRanManagerUserTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support
	virtual BOOL OnInitDialog();
	
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonItemsearchM();
	afx_msg void OnBnClickedButton1();
};
