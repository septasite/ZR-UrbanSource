#pragma once

#include "DxEffCharBlur.h"
// CEffBlur dialog
class	CEffTab;

class CEffBlur : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffBlur)

public:
	CEffBlur(LOGFONT logfont);
	virtual ~CEffBlur();

// Dialog Data
	enum { IDD = IDD_XBLUR };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	DxEffCharBlur*	EffBlurEdit;

public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffBlur ( DxEffCharBlur*	EffBlurX);
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
