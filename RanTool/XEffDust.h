#pragma once

#include "DxEffCharDust.h"
// CEffDust dialog
class	CEffTab;

class CEffDust : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffDust)

public:
	CEffDust(LOGFONT logfont);
	virtual ~CEffDust();

// Dialog Data
	enum { IDD = IDD_XDUST };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	DxEffCharDust*	EffDustEdit;

public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffDust ( DxEffCharDust*	EffDustX);
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
