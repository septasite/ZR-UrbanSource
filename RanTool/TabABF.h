#pragma once

#include "ABFClass.h"
// CTabABF dialog

class	CToolTab;

class CTabABF : public CPropertyPage
{
	DECLARE_DYNAMIC(CTabABF)

public:
	CTabABF(LOGFONT logfont);
	virtual ~CTabABF();

	enum { IDD = IDD_ABF_DIALOG };

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
	CABFClass	 m_pAbfCode;
	BOOL		 UpdateData();
	BOOL		 SaveData();
	void		 InitAniList();
	void		 InitBoneList();
	CListCtrl m_list_Ani;
	CListCtrl m_list_Bone;
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
	afx_msg void OnBnClickedButtonNeck();
	afx_msg void OnBnClickedButtonWrist();
	afx_msg void OnBnClickedButtonRfinger();
	afx_msg void OnBnClickedButtonAura();
	afx_msg void OnBnClickedButtonBelt();
	afx_msg void OnBnClickedButtonEar();
	afx_msg void OnBnClickedButtonAcce();
	afx_msg void OnBnClickedButtonCon();
	afx_msg void OnBnClickedButtonLfinger();
	afx_msg void OnBnClickedButtonBonelistCan();
	afx_msg void OnBnClickedButtonAnilistFolder();
	afx_msg void OnBnClickedButtonChfNew();
	afx_msg void OnBnClickedButtonAbfLoad2();
};
