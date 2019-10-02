#pragma once

#include "GLLandMan.h"

class	CToolTab;
// CDlgBasic dialog

class CDlgBasic : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgBasic)

public:
	CDlgBasic(LOGFONT logfont);
	virtual ~CDlgBasic();

// Dialog Data
	enum { IDD = IDD_DLG_BASIC };

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


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBasicBack();
	afx_msg void OnBnClickedButtonBasicSave();
	afx_msg void OnBnClickedButtonBasicWldopen();
	afx_msg void OnBnClickedButtonBasicBuildquad();
	afx_msg void OnCbnSelchangeComboBasicQuad();
};
