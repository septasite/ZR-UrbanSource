#pragma once

class	CRanManagerTab;
class	CRanManagerCharTab;
// CRanManagerChar dialog

class CRanManagerChar : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerChar)

public:
	CRanManagerChar(LOGFONT logfont);
	virtual ~CRanManagerChar();

// Dialog Data
	enum { IDD = IDD_RM_CHAR };

protected:
	CRanManagerTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;


public:
	CRanManagerCharTab	*m_pCharTab;
	CListCtrl		m_list_Char;
	CComboBox		m_cSearchType;
	CComboBox		m_cCharPage;
	int				nChaNum;
	CString			strChar;
	BOOL			CheckOnline(int nCheck);

public:
	void			SetToolTab		( CRanManagerTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnCbnSelchangeComboCharsearchtype();
	afx_msg void OnNMDblclkListChar(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonCharSelect();
};
