#pragma once

#include "GLLandMan.h"

class	CToolTab;
// CDlgEffEdit dialog

class CDlgEffEdit : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgEffEdit)

public:
	CDlgEffEdit(LOGFONT logfont);
	virtual ~CDlgEffEdit();

// Dialog Data
	enum { IDD = IDD_DLG_EFFEDIT };

protected:
	CToolTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

	GLLandMan		*pGLLand;
	PLANDEFF		pEffEdit;

public:
	void			SetToolTab		( CToolTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetData( GLLandMan*	pLand, PLANDEFF pEff );
	void			ShowData();
	BOOL			GetData();
	void			CHECKUI( bool bEnable );
	D3DXMATRIX		matOrig;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBasicApply();
	afx_msg void OnBnClickedButtonBasicSave();
	afx_msg void OnBnClickedButtonBasicBack();
	afx_msg void OnBnClickedButtonEffOpen();
	afx_msg void OnBnClickedButtonEffEditmat();
	afx_msg void OnBnClickedButtonEffMatnew();
	afx_msg void OnBnClickedButtonEditEffmatrixCancel();
	afx_msg void OnBnClickedButtonBasicRegisterneweff();
	afx_msg void OnBnClickedButtonNameCheck();
	afx_msg void OnBnClickedButtonNameNew();
};
