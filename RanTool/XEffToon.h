#pragma once

#include "DxEffCharToon.h"
// CEffToon dialog
class	CEffTab;

class CEffToon : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffToon)

public:
	CEffToon(LOGFONT logfont);
	virtual ~CEffToon();

// Dialog Data
	enum { IDD = IDD_XTOON };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	DxEffCharToon*	EffToonEdit;

public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffToon ( DxEffCharToon*	EffToonX);
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
