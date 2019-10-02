// RanManagerDlg.h : header file
//

#pragma once
#include "afxcmn.h"
#include "afxwin.h"

class	CRanManagerTab;

// CRanManagerDlg dialog
class CRanManagerDlg : public CDialog
{
// Construction
public:
	CRanManagerDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_RM_DLG};

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:
	CRanManagerTab		*m_pToolTab;
	bool				bSuccess;
	char			m_szAppPath[MAX_PATH];
	CString			m_strAppPath;
	CComboBox		m_cMainPage;

public:
	void ConnectDatabase();
// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:

	afx_msg void OnBnClickedButtonMainSelect();
};
