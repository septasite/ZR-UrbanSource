#pragma once

#include "VCFClass.h"
// CTabVCF dialog

class	CToolTab;

class CTabVCF : public CPropertyPage
{
	DECLARE_DYNAMIC(CTabVCF)

public:
	CTabVCF(LOGFONT logfont);
	virtual ~CTabVCF();

	enum { IDD = IDD_VCF_DIALOG };

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
	CVCFClass	 m_pVcfCode;
	BOOL		 UpdateData();
	BOOL		 SaveData();
	void		 InitAniList();
	void		 InitBoneList();
	CListCtrl m_list_Ani;
	CListCtrl m_list_Bone;
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
	afx_msg void OnBnClickedButtonAnilistSearch();
	afx_msg void OnBnClickedButtonVcfLoad();
	afx_msg void OnBnClickedButtonVcfSave();

	afx_msg void OnBnClickedButtonNeckVcf();
	afx_msg void OnBnClickedButtonWristVcf();
	afx_msg void OnBnClickedButtonRfingerVcf();
	afx_msg void OnBnClickedButtonLfingerVcf();
	afx_msg void OnBnClickedButtonWingVcf();
	afx_msg void OnBnClickedButtonAuraVcf();
	afx_msg void OnBnClickedButtonBeltVcf();
	afx_msg void OnBnClickedButtonEarVcf();
	afx_msg void OnBnClickedButtonAcceVcf();
	afx_msg void OnBnClickedButtonConVcf();
	afx_msg void OnBnClickedButtonBonelistCancel();
	afx_msg void OnBnClickedButtonAnilistFolder2();
	afx_msg void OnBnClickedButtonChfNew2();
};
