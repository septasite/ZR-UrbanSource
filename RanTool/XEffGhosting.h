#pragma once

#include "DxEffCharGhosting.h"
// CEffGhosting dialog
class	CEffTab;

class CEffGhosting : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffGhosting)

public:
	CEffGhosting(LOGFONT logfont);
	virtual ~CEffGhosting();

// Dialog Data
	enum { IDD = IDD_XGHOSTING };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	DxEffCharGhosting*	EffGhostingEdit;

public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffGhosting ( DxEffCharGhosting*	EffGhostingX);
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
