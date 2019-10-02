#pragma once

#include "GLLandMan.h"

class	CToolTab;
// CDlgCrowEdit dialog

class CDlgCrowEdit : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgCrowEdit)

public:
	CDlgCrowEdit(LOGFONT logfont);
	virtual ~CDlgCrowEdit();

// Dialog Data
	enum { IDD = IDD_DLG_CROWEDIT };

protected:
	CToolTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

	GLLandMan		*pGLLand;
	GLMobSchedule	*pSched;

public:
	void			SetToolTab		( CToolTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetData( GLLandMan*	pLand, std::string strName, bool bEdit );
	void			ShowData();
	void			ResetData();
	BOOL			GetData();
	void			UpdateList();
	void			JumpTo( D3DXVECTOR3 vPos );
	void			EffTo( D3DXVECTOR3 vPos );
	void			UICHECK( bool bEnable );

public:
	CListCtrl		m_list_SCHED;
	BOOL			bEditACTION;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBasicSave();
	afx_msg void OnBnClickedButtonOpenbusloc();
	afx_msg void OnBnClickedButtonModMat();
	afx_msg void OnBnClickedButtonModMat2();
	afx_msg void OnBnClickedButtonRegister();
	afx_msg void OnBnClickedButtonSchedAdd();
	afx_msg void OnBnClickedButtonSchedEdit();
	afx_msg void OnBnClickedButtonSchedDel();
	afx_msg void OnBnClickedButtonPosGet();
	afx_msg void OnBnClickedButtonActionOk();
	afx_msg void OnCbnSelchangeComboMatType();
	afx_msg void OnNMDblclkListCrowaction(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonCrow();
	afx_msg void OnBnClickedButtonApply();
	afx_msg void OnBnClickedButtonNameCheck();
	afx_msg void OnBnClickedButtonNameNew();
	afx_msg void OnBnClickedButtonBasicClose();
	afx_msg void OnBnClickedButtonLmPosNew();
	afx_msg void OnBnClickedButtonLmPosRebuild();
};
