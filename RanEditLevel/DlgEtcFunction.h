#pragma once

#include "GLLandMan.h"

class	CToolTab;
// CDlgEtcFunction dialog

class CDlgEtcFunction : public CPropertyPage
{
	DECLARE_DYNAMIC(CDlgEtcFunction)

public:
	CDlgEtcFunction(LOGFONT logfont);
	virtual ~CDlgEtcFunction();

// Dialog Data
	enum { IDD = IDD_DLG_ETCHFUNCTION };

protected:
	CToolTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

	GLLandMan		*pGLLand;
	SLEVEL_ETC_FUNC	*pEtcFunction;

public:
	void			SetToolTab		( CToolTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetData( GLLandMan*	pLand );
	void			ShowData();
	BOOL			GetData();
	void			UpdateEffList();
	void			JumpTo( float fMinX,float fMinY, float fMaxX, float fMaxY );

public:
	CListCtrl		m_list_Eff;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonBasicBack();
	afx_msg void OnBnClickedButtonBasicSave();
	afx_msg void OnNMDblclkListLandeff(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonEtcEffAdd();
	afx_msg void OnBnClickedButtonEtcEffEdit();
	afx_msg void OnBnClickedButtonEtcEffDel();
	afx_msg void OnBnClickedButtonEtchCaptureCam();
	afx_msg void OnBnClickedButtonEtchEffOk();
	afx_msg void OnBnClickedButtonEtchEffPosEdit();
	afx_msg void OnBnClickedButtonEtchEffPosSave();
	afx_msg void OnBnClickedButtonEtchEffPosGet();
	afx_msg void OnBnClickedButtonEtchEffCancel();
};
