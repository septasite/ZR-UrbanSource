#pragma once

#include "DxEffCharSingle.h"
// CEffSingle dialog
class	CEffTab;

class CEffSingle : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffSingle)

public:
	CEffSingle(LOGFONT logfont);
	virtual ~CEffSingle();

// Dialog Data
	enum { IDD = IDD_XSINGLE };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	DxEffCharSingle*	EffSingleEdit;

public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffSingle ( DxEffCharSingle*	EffSingleX);
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
