#pragma once

#include "TextScroller.h"
// CTabCredits dialog

class	CToolTab;
//class	CTextScroller;

class CTabCredits : public CPropertyPage
{
	DECLARE_DYNAMIC(CTabCredits)

public:
	CTabCredits(LOGFONT logfont);
	virtual ~CTabCredits();

	enum { IDD = IDD_CREDITS };

protected:
	CToolTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	CTextScroller	m_TextScroller;
	void			SetToolTab		( CToolTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
};
