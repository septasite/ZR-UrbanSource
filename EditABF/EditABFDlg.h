// EditABFDlg.h : header file
//
#include "ABFcode.h"
#include "afxcmn.h"

#pragma once


// CEditABFDlg dialog
class CEditABFDlg : public CDialog
{
// Construction
public:
	CEditABFDlg(CWnd* pParent = NULL);	// standard constructor

// Dialog Data
	enum { IDD = IDD_ABF_DIALOG };


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
	CAbfCode	 m_pAbfCode;
	BOOL		 UpdateData();
	BOOL		 SaveData();
	void		 InitAniList();
	void		 InitBoneList();
	CListCtrl m_list_Ani;
	CListCtrl m_list_Bone;
	BOOL		bADD;
	afx_msg void OnBnClickedButtonAnilistAdd();
	afx_msg void OnBnClickedButtonAnilistDelete();
	afx_msg void OnNMDblclkListAni(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonAnilistEdit();

	afx_msg void OnBnClickedButtonBonelistAdd();
	afx_msg void OnBnClickedButtonBonelistDel();
	afx_msg void OnNMDblclkListBone(NMHDR *pNMHDR, LRESULT *pResult);
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
	afx_msg void OnBnClickedButtonAbfLoad();
	afx_msg void OnBnClickedButtonAbfSave();
	afx_msg void OnBnClickedButtonAnilistOk();
};
