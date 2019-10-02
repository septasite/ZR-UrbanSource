#pragma once

#include "GLLandMan.h"
#include "GLMapList.h"

class	CToolTab;
// CDlgGateEdit dialog

class CDlgGateEdit : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgGateEdit)

public:
	CDlgGateEdit(LOGFONT logfont);
	virtual ~CDlgGateEdit();

// Dialog Data
	enum { IDD = IDD_DLG_GATEEDIT };

protected:
	CToolTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

	GLLandMan		*pGLLand;
	PDXLANDGATE		pGate;
	GLMapList		m_sMap;

public:
	void			SetToolTab		( CToolTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetData( GLLandMan*	pLand, PDXLANDGATE pLandGate );
	void			ShowData();
	void			ResetData();
	BOOL			GetData();
	void			CHECKUI( bool bEnable );
	void			JumpTo( D3DXVECTOR3 vMax, D3DXVECTOR3 vMin );


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBasicSave();
	afx_msg void OnBnClickedButtonBasicBack();
	afx_msg void OnBnClickedButtonGateTomap();
	afx_msg void OnBnClickedButtonGateNameCheck();
	afx_msg void OnBnClickedButtonGateNameNew();
	afx_msg void OnBnClickedButtonBasicApply();
	afx_msg void OnBnClickedButtonGateRegnew();
	afx_msg void OnBnClickedButtonGateMatEdit();
	afx_msg void OnBnClickedButtonGateMatSave();
	afx_msg void OnBnClickedButtonGateMatScreenpos();
	afx_msg void OnBnClickedButtonGateIdCheck();
	afx_msg void OnBnClickedButtonGateIdNew();
};
