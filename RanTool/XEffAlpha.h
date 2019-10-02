#pragma once

#include "DxEffCharAlpha.h"
// CEffAlpha dialog
class	CEffTab;

class CEffAlpha : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffAlpha)

public:
	CEffAlpha(LOGFONT logfont);
	virtual ~CEffAlpha();

// Dialog Data
	enum { IDD = IDD_XALPHA };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	DxEffCharAlpha*	EffAlphaEdit;

public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffAlpha ( DxEffCharAlpha*	EffAlphaX);
	BOOL			Update ();
	BOOL			Save ();


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
};
