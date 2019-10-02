#pragma once

#include "DxEffCharNoAlpha.h"
// CEffNoAlpha dialog
class	CEffTab;

class CEffNoAlpha : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffNoAlpha)

public:
	CEffNoAlpha(LOGFONT logfont);
	virtual ~CEffNoAlpha();

// Dialog Data
	enum { IDD = IDD_XNOALPHA };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	DxEffCharNoAlpha*	EffNoAlphaEdit;

public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffNoAlpha ( DxEffCharNoAlpha*	EffNoAlphaX);
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
