#pragma once

#include "DxEffCharBoneListeff.h"
// CEffBoneList dialog
class	CEffTab;

class CEffBoneList : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffBoneList)

public:
	CEffBoneList(LOGFONT logfont);
	virtual ~CEffBoneList();

// Dialog Data
	enum { IDD = IDD_XBONELIST };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;
	bool			bAdd;
	int				nLastEdit;

public:
	DxEffCharBoneListEff*	EffBoneListEdit;
	CListBox		m_list_vec;

public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffBoneList ( DxEffCharBoneListEff*	EffBoneListX);
	BOOL			Update ();
	BOOL			UpdateList ();
	BOOL			Save ();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
	//afx_msg void OnBnClickedButtonPadd();
	//afx_msg void OnBnClickedButtonPedit();
	//afx_msg void OnBnClickedButtonPdel();
	//afx_msg void OnBnClickedButtonPclr();
	//afx_msg void OnBnClickedButtonPmup();
	//afx_msg void OnBnClickedButtonPmdn();
	//afx_msg void OnBnClickedButtonPok();
	//afx_msg void OnBnClickedButtonPcan();
	afx_msg void OnBnClickedButtonBladd();
	afx_msg void OnBnClickedButtonBledit();
	afx_msg void OnBnClickedButtonBldel();
	afx_msg void OnBnClickedButtonBlclr();
	afx_msg void OnBnClickedButtonBlup();
	afx_msg void OnBnClickedButtonBldn();
	afx_msg void OnBnClickedButtonBlcan();
	afx_msg void OnBnClickedButtonBlok();
};
