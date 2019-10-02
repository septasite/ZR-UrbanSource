// CryptionRCCDlg.h : header file
//

#pragma once
#include "afxwin.h"


// CCryptionRCCDlg dialog
class CCryptionRCCDlg : public CDialog
{
// Construction
public:
	CCryptionRCCDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CRYPTIONRCC_DIALOG };

	enum
	{
		NormalCryption = 0,

		CryptionType,
	};
	enum
	{
		FileCryption = 0,
		FolderCryption = 1,
	};

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support


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
	void clearslot();
	void AddEditString( const char* szInfo );
	BOOL FileEncryption();
	BOOL FileDecryption();
	BOOL FileEncryption(CString fileinput , CString fileoutput);
	BOOL FileDecryption(CString fileinput , CString fileoutput);
	BOOL FolderEncryption( const CString& strInput, const CString& strOutput );
	BOOL FolderDecryption( const CString& strInput, const CString& strOutput );
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton3();
	afx_msg void OnBnClickedButton4();
	afx_msg void OnBnClickedButton5();
	CString m_cInput;
	CString m_cOutput;
	afx_msg void OnCbnSelchangeCombo1();
	CComboBox m_cCombobox;
	afx_msg void OnBnClickedButton6();
	CComboBox m_cModCryption;
	CString m_cEditInfo;
	CEdit m_cEdit;
	afx_msg void OnEnChangeEditStatic();
};
