#pragma once

#include "GLLandMan.h"

class	CToolTab;
// CDlgCrowList dialog

class CDlgCrowList : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgCrowList)

public:
	CDlgCrowList(LOGFONT logfont);
	virtual ~CDlgCrowList();

// Dialog Data
	enum { IDD = IDD_DLG_CROWLIST };

protected:
	CToolTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;
	std::string		strEDITID;

	GLLandMan		*pGLLand;

public:
	void			SetToolTab		( CToolTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetData( GLLandMan*	pLand );
	void			ShowData();
	void			SelectCrow( std::string strName );
	void			JumpTo( D3DXVECTOR3 vPos );
	void			EffTo( D3DXVECTOR3 vPos );
	
public:
	CListCtrl		m_list_Crow;


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBasicBack();
	afx_msg void OnNMDblclkListCrow(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonCrowlistNew();
	afx_msg void OnBnClickedButtonCrowlistDelete();
	afx_msg void OnBnClickedButtonCrowlistEdit();
	afx_msg void OnBnClickedButtonCrowlistCopy();
	afx_msg void OnBnClickedButtonCrowlistPastenew();
	afx_msg void OnBnClickedButtonReplaceId();
	afx_msg void OnBnClickedButtonRefresh();
	afx_msg void OnBnClickedButtonRemovefilter();
	afx_msg void OnBnClickedButtonFix();
	afx_msg void OnBnClickedButtonReplaceId2();
	afx_msg void OnBnClickedButtonShowInvalid();
	afx_msg void OnBnClickedButtonShownpc();
};
