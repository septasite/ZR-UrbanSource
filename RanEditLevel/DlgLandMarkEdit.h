#pragma once

#include "GLLandMan.h"
#include "GLLandMark.h"

class	CToolTab;
// CDlgLandMarkEdit dialog

class CDlgLandMarkEdit : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgLandMarkEdit)

public:
	CDlgLandMarkEdit(LOGFONT logfont);
	virtual ~CDlgLandMarkEdit();

// Dialog Data
	enum { IDD = IDD_DLG_LANDMARKEDIT };

protected:
	CToolTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

	GLLandMan		*pGLLand;
	PLANDMARK		pLMEdit;

public:
	void			SetToolTab		( CToolTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetData( GLLandMan*	pLand, PLANDMARK pLM );
	void			ShowData();
	BOOL			GetData();
	void			CHECKUI( bool bEnable );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBasicSave();
	afx_msg void OnBnClickedButtonBasicBack();
	afx_msg void OnBnClickedButtonBasicApply();
	afx_msg void OnBnClickedButtonBasicReg();
	afx_msg void OnBnClickedButtonLmNameCheck();
	afx_msg void OnBnClickedButtonLmNameNew();
	afx_msg void OnBnClickedButtonLmPosEdit();
	afx_msg void OnBnClickedButtonLmPosSave();
	afx_msg void OnBnClickedButtonLmPosNew();
};
