#pragma once

#include "DxEffCharEmit.h"
// CEffEmit dialog
class	CEffTab;

class CEffEmit : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffEmit)

public:
	CEffEmit(LOGFONT logfont);
	virtual ~CEffEmit();

// Dialog Data
	enum { IDD = IDD_XEMIT };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	DxEffCharEmit*	EffEmitEdit;

public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffEmit ( DxEffCharEmit*	EffEmitX);
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
