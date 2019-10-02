#pragma once

#include "DxEffCharCloneBlur.h"
// CEffCloneBlur dialog
class	CEffTab;

class CEffCloneBlur : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffCloneBlur)

public:
	CEffCloneBlur(LOGFONT logfont);
	virtual ~CEffCloneBlur();

// Dialog Data
	enum { IDD = IDD_XCLONEBLUR };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	DxEffCharCloneBlur*	EffCloneBlurEdit;


public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffCloneBlur ( DxEffCharCloneBlur*	EffCloneBlurX);
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
