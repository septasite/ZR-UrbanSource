#pragma once

#include "GLLandMan.h"

class	CToolTab;
// CDlgCondition dialog

class CDlgCondition : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgCondition)

public:
	CDlgCondition(LOGFONT logfont);
	virtual ~CDlgCondition();

// Dialog Data
	enum { IDD = IDD_DLG_CONDITION };

protected:
	CToolTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

	GLLandMan		*pGLLand;
	SLEVEL_REQUIRE	*pReq;

public:
	void			SetToolTab		( CToolTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetData( GLLandMan*	pLand );
	void			ShowData();
	BOOL			GetData();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBasicCancel();
	afx_msg void OnBnClickedButtonBasicSave();
	afx_msg void OnBnClickedButtonReqLevel();
	afx_msg void OnBnClickedButtonReqItem();
	afx_msg void OnBnClickedButtonReqSkill();
	afx_msg void OnBnClickedButtonReqComquest();
	afx_msg void OnBnClickedButtonReqActquest();
	afx_msg void OnBnClickedButtonReqLiving();
	afx_msg void OnBnClickedButtonReqBright();
	afx_msg void OnBnClickedButtonDelItem();
	afx_msg void OnBnClickedButtonDelSkill();
	afx_msg void OnBnClickedButtonDelComquest();
	afx_msg void OnBnClickedButtonDelActquest();
};
