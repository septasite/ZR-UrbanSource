#pragma once

#include "DxCharAroundEff.h"
// CEffAround dialog
class	CEffTab;

class CEffAround : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffAround)

public:
	CEffAround(LOGFONT logfont);
	virtual ~CEffAround();

// Dialog Data
	enum { IDD = IDD_XAROUND };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;
	bool			bAdd;
	bool			bInit;
	int				nLastEdit;

public:
	DxCharAroundEff*	EffAroundEdit;
	CListBox		m_list_ar;

public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffAround ( DxCharAroundEff*	EffAroundX);
	BOOL			Update ();
	BOOL			UpdateList ();
	BOOL			Save ();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonAradd();
	afx_msg void OnBnClickedButtonAredit();
	afx_msg void OnBnClickedButtonArdel();
	afx_msg void OnBnClickedButtonArclr();
	afx_msg void OnBnClickedButtonArok();
	afx_msg void OnBnClickedButtonArcan();
	afx_msg void OnBnClickedButtonVpos();
};
