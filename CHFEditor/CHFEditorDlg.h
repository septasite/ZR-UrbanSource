// CHFEditorDlg.h : header file
//

#pragma once
#include "ChfCode.h"
#include "afxcmn.h"


// CCHFEditorDlg dialog
class CCHFEditorDlg : public CDialog
{
// Construction
public:
	CCHFEditorDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_CHFEDITOR_DIALOG };

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
	void	LoadCpsfile( int nID );

public:
	CChfCode	 m_pChfCode;
	BOOL		 UpdateData();
	BOOL		 SaveData();
	void		 InitAniList();
	afx_msg void OnBnClickedButtonLoadChf();
	CListCtrl m_list_Ani;
	afx_msg void OnBnClickedButtonSaveChf();
	afx_msg void OnBnClickedButtonAnilistAdd();
	afx_msg void OnBnClickedButtonAnilistDelete();
	afx_msg void OnNMDblclkList1(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonAnilistEdit();
	afx_msg void OnBnClickedButtonAnilistOk();
	afx_msg void OnBnClickedButtonHead();
	afx_msg void OnBnClickedButtonBody();
	afx_msg void OnBnClickedButtonPant();
	afx_msg void OnBnClickedButtonGlove();
	afx_msg void OnBnClickedButtonRhand();
	afx_msg void OnBnClickedButtonLhand();
	afx_msg void OnBnClickedButtonFoot();
	afx_msg void OnBnClickedButtonHair();
	afx_msg void OnBnClickedButtonAcc();
	afx_msg void OnBnClickedButtonVehicle();
	afx_msg void OnBnClickedButtonAnilistSearch();
};
