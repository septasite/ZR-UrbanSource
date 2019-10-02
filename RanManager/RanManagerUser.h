#pragma once

// CRanManagerUser dialog
class	CRanManagerTab;
class	CRanManagerUserTab;

class CRanManagerUser : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerUser)

public:
	CRanManagerUser(LOGFONT logfont);
	virtual ~CRanManagerUser();

// Dialog Data
	enum { IDD = IDD_RM_USER};



protected:
	CRanManagerTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	CRanManagerUserTab	*m_pUserTab;
	CListCtrl		m_list_User;
	CComboBox		m_cSearchType;
	CComboBox		m_cUserPage;
	int				nUserNum;
	CString			strUser;

public:
	void			SetToolTab		( CRanManagerTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	
protected:
	virtual void DoDataExchange(CDataExchange* pDX);  

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnCbnSelchangeComboSearchtype();
	afx_msg void OnNMDblclkListUser(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonUserSelect();
};
