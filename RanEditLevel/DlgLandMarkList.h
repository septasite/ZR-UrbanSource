#pragma once

#include "GLLandMan.h"

class	CToolTab;
// CDlgLandMarkList dialog

class CDlgLandMarkList : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgLandMarkList)

public:
	CDlgLandMarkList(LOGFONT logfont);
	virtual ~CDlgLandMarkList();

// Dialog Data
	enum { IDD = IDD_DLG_LANDMARKLIST };

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

public:
	CListCtrl		m_list_LandMark;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBasicBack();
	afx_msg void OnBnClickedButtonLmAdd();
	afx_msg void OnBnClickedButtonLmDel();
	afx_msg void OnBnClickedButtonLmEdit();
	afx_msg void OnNMDblclkListLandmark(NMHDR *pNMHDR, LRESULT *pResult);
};
