#pragma once


// CRanManagerUserChar dialog
class	CRanManagerUserTab;

class CRanManagerUserChar : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerUserChar)

public:
	CRanManagerUserChar(LOGFONT logfont);
	virtual ~CRanManagerUserChar();

// Dialog Data
	enum { IDD = IDD_RM_USER_CHAR };

protected:
	CRanManagerUserTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	CListCtrl		m_list_Char;

public:
	void			SetToolTab		( CRanManagerUserTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetUser(int nUser);
	void			LoadUser(int nUser);
	void			LoadChar(int nUser);
	void			DeleteChar(int nChaNum);
	void			ClearChar();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonCharDelete();
	afx_msg void OnBnClickedButtonCharClear();
	afx_msg void OnBnClickedButtonUsercharCancel();
};
