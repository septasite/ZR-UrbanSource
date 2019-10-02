// EditABLDlg.h : header file
//
#include "DxSkinPieceRootDataDummy.h"

#pragma once


// CEditABLDlg dialog
class CEditABLDlg : public CDialog
{
// Construction
public:
	CEditABLDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_EDITABL_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV support

public:
	DxSkinPieceRootDataDummy ABLDummy;
	BOOL UpdateData ();
	BOOL UpdateData2 ();
	BOOL SaveData ();
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
	afx_msg void OnBnClickedButtonLoadablneo();
	afx_msg void OnBnClickedButtonLoadabl();
	afx_msg void OnBnClickedButtonSaveabl();
};

