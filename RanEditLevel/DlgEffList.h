#pragma once

#include "GLLandMan.h"

class	CToolTab;
// CDlgEffList dialog

class CDlgEffList : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgEffList)

public:
	CDlgEffList(LOGFONT logfont);
	virtual ~CDlgEffList();

// Dialog Data
	enum { IDD = IDD_DLG_EFFLIST };

protected:
	CToolTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

	GLLandMan		*pGLLand;

public:
	void			SetToolTab		( CToolTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetData( GLLandMan*	pLand );
	void			ShowData();
	void			JumpTo( D3DXMATRIX sMat );

public:
	CListCtrl		m_list_Eff;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBasicBack();
	afx_msg void OnNMDblclkListEff(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonEffAdd();
	afx_msg void OnBnClickedButtonEffEdit();
	afx_msg void OnBnClickedButtonEffDel();
};
