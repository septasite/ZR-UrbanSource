#pragma once

class	CToolTab;
// CDlgMain dialog

class CDlgMain : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgMain)

public:
	CDlgMain(LOGFONT logfont);
	virtual ~CDlgMain();

// Dialog Data
	enum { IDD = IDD_DLG_MAIN };

protected:
	CToolTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	void			SetToolTab		( CToolTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonPagesel();
};
