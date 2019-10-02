#pragma once

#include "ABLClass.h"
// CTabABL dialog

class	CToolTab;

class CTabABL : public CPropertyPage
{
	DECLARE_DYNAMIC(CTabABL)

public:
	CTabABL(LOGFONT logfont);
	virtual ~CTabABL();

	enum { IDD = IDD_ABL_DIALOG };

protected:
	CToolTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;
	BOOL			m_bActive;
	CString			strFileName;

public:
	void			SetToolTab		( CToolTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			Reset();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	CABLClass	m_pAblCode;
	BOOL		UpdateData ();
	BOOL		SaveData ();
	afx_msg void OnBnClickedButtonLoadablneo();
	afx_msg void OnBnClickedButtonLoadabl();
	afx_msg void OnBnClickedButtonSaveabl();
	afx_msg void OnBnClickedButtonNewabl();
};
