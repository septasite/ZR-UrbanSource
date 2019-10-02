// RanToolDlg.h : header file
//

#pragma once

class	CToolTab;

// CRanToolDlg dialog
class CRanToolDlg : public CDialog
{
// Construction
	enum
	{
		TYPE_DEF = 0,
		TYPE_CHF = 1,
		TYPE_ABF = 2,
		TYPE_VCF = 3,
		TYPE_CPS = 4,
		TYPE_ABL = 5,
		TYPE_CFG = 6,
		TYPE_CNV = 7,
		TYPE_MMP = 8,
		TYPE_CRY = 9,

		TYPE_SIZE = 10
	};
public:
	CRanToolDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_RANTOOL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:
	CToolTab		*m_pToolTab;
	char			m_szAppPath[MAX_PATH];
	CString			m_strAppPath;
	CComboBox		m_cToolType;
	char*			GetPath ()	{ return m_szAppPath; }
	void			GetIPAdd();
	bool			bSave;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonRun();
	afx_msg void OnBnClickedButtonAbout();
};
