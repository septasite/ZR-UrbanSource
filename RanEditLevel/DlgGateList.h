#pragma once

#include "GLLandMan.h"

class	CToolTab;
// CDlgGateList dialog

class CDlgGateList : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgGateList)

public:
	CDlgGateList(LOGFONT logfont);
	virtual ~CDlgGateList();

// Dialog Data
	enum { IDD = IDD_DLG_GATELIST };

protected:
	CToolTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;
	std::string		strEDITID;

	GLLandMan		*pGLLand;
	DxLandGateMan	*pGate;

public:
	void			SetToolTab		( CToolTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetData( GLLandMan*	pLand );
	void			ShowData();
	void			JumpTo( D3DXVECTOR3 vMax, D3DXVECTOR3 vMin );

public:
	CListCtrl		m_list_Gate;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBasicBack();
	afx_msg void OnNMDblclkListGate(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonGateAdd();
	afx_msg void OnBnClickedButtonGateEdit();
	afx_msg void OnBnClickedButtonGateDel();
};
