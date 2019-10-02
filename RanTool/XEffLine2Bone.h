#pragma once

#include "DxEffCharLine2BoneEff.h"
// CEffLine2Bone dialog
class	CEffTab;


class CEffLine2Bone : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffLine2Bone)

public:
	CEffLine2Bone(LOGFONT logfont);
	virtual ~CEffLine2Bone();

// Dialog Data
	enum { IDD = IDD_XLINE2BONE };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;
	bool			bAdd;
	int				nLastEdit;

public:
	DxEffCharLine2BoneEff*	EffLine2BoneEdit;
	CListBox		m_list_line;

public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffLine2Bone ( DxEffCharLine2BoneEff*	EffLine2BoneX);
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
	afx_msg void OnBnClickedButtonL2add();
	afx_msg void OnBnClickedButtonL2edit();
	afx_msg void OnBnClickedButtonL2del();
	afx_msg void OnBnClickedButtonL2clr();
	afx_msg void OnBnClickedButtonL2ok();
	afx_msg void OnBnClickedButtonL2can();
};
