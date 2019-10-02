#pragma once

#include "DxEffCharShock.h"
// CEffShock dialog
class	CEffTab;

class CEffShock : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffShock)

public:
	CEffShock(LOGFONT logfont);
	virtual ~CEffShock();

// Dialog Data
	enum { IDD = IDD_XSHOCK_A };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	DxEffCharShock*	EffShockEdit;

public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffShock ( DxEffCharShock*	EffShockX);
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
