#pragma once
#include "../../EngineLib/G-Logic/GLDefine.h"

struct ITEMBANKINFO
{
	int nProductNum;
	std::string strItemName;
	ITEMBANKINFO(): 
	nProductNum(0),
	strItemName("")
	{
	}
};

// CRanManagerUserBank dialog
class	CRanManagerUserTab;
class CRanManagerUserBank : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerUserBank)

public:
	CRanManagerUserBank(LOGFONT logfont);
	virtual ~CRanManagerUserBank();

// Dialog Data
	enum { IDD = IDD_RM_USER_BANK };

protected:
	CRanManagerUserTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	CListCtrl		m_list_Shop;
	CListCtrl		m_list_Bank;
	CComboBox		m_cSearchType;

public:
	typedef std::vector<ITEMBANKINFO*>		ITEMBANK_LIST;
	typedef ITEMBANK_LIST::iterator			ITEMBANK_LIST_ITER;
	ITEMBANK_LIST	m_ShopVec;

public:
	void			SetToolTab		( CRanManagerUserTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetUser(int nUser);
	void			LoadShop(int nType,int nVal ,CString strSearch);
	void			LoadBank(int nUser);
	CString			GetShopName(int nItemNum );
	void			InsertItemToBank(int nItemNum );
	void			DeleteItemFromBank(int nKey );


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonInsert();
	afx_msg void OnBnClickedButtonDelete();
	afx_msg void OnBnClickedButtonClear();
	afx_msg void OnBnClickedButtonSearchShop();
	afx_msg void OnCbnSelchangeComboSearchType();
	afx_msg void OnBnClickedButtonUserbankClose();
	afx_msg void OnBnClickedButtonInsert2();
};
