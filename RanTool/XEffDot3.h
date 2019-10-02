#pragma once

#include "DxEffCharDot3.h"
// CEffDot3 dialog
class	CEffTab;

class CEffDot3 : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffDot3)

public:
	CEffDot3(LOGFONT logfont);
	virtual ~CEffDot3();

// Dialog Data
	enum { IDD = IDD_XDOT3 };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	DxEffCharDot3*	EffDot3Edit;

public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffDot3( DxEffCharDot3*	EffDot3X);
	BOOL			Update ();
	BOOL			Save ();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnCbnSelchangeComboColop();
};
