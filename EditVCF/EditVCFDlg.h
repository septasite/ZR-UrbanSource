// EditVCFDlg.h : header file
//
#include "VCFcode.h"
#include "afxcmn.h"

#pragma once


// CEditVCFDlg dialog
class CEditVCFDlg : public CDialog
{
// Construction
public:
	CEditVCFDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_VCF_DIALOG };

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
	CVcfCode	 m_pVcfCode;
	BOOL		 UpdateData();
	BOOL		 SaveData();
	void		 InitAniList();
	void		 InitBoneList();
	CListCtrl m_list_Ani;
	CListCtrl m_list_Bone;
	BOOL		bADD;
	afx_msg void OnNMDblclkListAni(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonAnilistAdd();
	afx_msg void OnBnClickedButtonAnilistDelete();
	afx_msg void OnBnClickedButtonAnilistEdit();
	afx_msg void OnBnClickedButtonAnilistOk();
	afx_msg void OnNMDblclkListBone(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonBonelistAdd();
	afx_msg void OnBnClickedButtonBonelistDel();
	afx_msg void OnBnClickedButtonBonelistEdit();
	afx_msg void OnBnClickedButtonBonelistOk();
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
	afx_msg void OnBnClickedButtonWing();
	afx_msg void OnBnClickedButtonAnilistSearch();
	afx_msg void OnBnClickedButtonVcfLoad();
	afx_msg void OnBnClickedButtonVcfSave();
};
