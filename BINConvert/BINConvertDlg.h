// BINConvertDlg.h : header file
//
#include "CnvClass.h"

#pragma once


// CBINConvertDlg dialog
class CBINConvertDlg : public CDialog
{
// Construction
public:
	CBINConvertDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_BINCONVERT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:

	BinManager		BinFile;
	SANIMCONINFO	CfgFile;

// Implementation
protected:
	HICON m_hIcon;

	// Generated message map functions
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()

	void CleanUp();
public:
	afx_msg void OnBnClickedLoadBin();
	afx_msg void OnBnClickedSaveBin();
	afx_msg void OnBnClickedLoadCfg();
	afx_msg void OnBnClickedSaveCfg();
};
