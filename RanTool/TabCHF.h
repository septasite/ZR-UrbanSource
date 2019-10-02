#pragma once

#include "CHFClass.h"
// CTabCHF dialog

class	CToolTab;

class CTabCHF : public CPropertyPage
{
	DECLARE_DYNAMIC(CTabCHF)

public:
	CTabCHF(LOGFONT logfont);
	virtual ~CTabCHF();

	enum { IDD = IDD_CHF_DIALOG };

protected:
	CToolTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;
	BOOL			m_bActive;
	void			LoadCpsfile( int nID );
	bool			bAddBone;
	bool			bADD;
	CString			strFileName;

public:
	void			Reset();
	void			SetToolTab		( CToolTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	CCHFClass	 m_pChfCode;
	BOOL		 UpdateData();
	BOOL		 SaveData();
	void		 InitAniList();
	void		 InitBoneList();
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
	CListCtrl m_list_Ani;
	CListCtrl m_list_Bone;
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
	afx_msg void OnBnClickedButtonChfLoad();
	afx_msg void OnBnClickedButtonChfSave();
	afx_msg void OnBnClickedButtonNeck();
	afx_msg void OnBnClickedButtonWrist();
	afx_msg void OnBnClickedButtonRfinger();
	afx_msg void OnBnClickedButtonLfinger();
	afx_msg void OnBnClickedButtonAura();
	afx_msg void OnBnClickedButtonBelt();
	afx_msg void OnBnClickedButtonEar();
	afx_msg void OnBnClickedButtonAcceChf();
	afx_msg void OnBnClickedButtonConChf();
	afx_msg void OnBnClickedButtonBonelistCan();
	afx_msg void OnBnClickedButtonAnilistFolder();
	afx_msg void OnBnClickedButtonChfSave2();
	afx_msg void OnBnClickedButtonChfNew();
};
