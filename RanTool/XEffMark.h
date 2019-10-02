#pragma once

#include "DxEffCharMark.h"
// CEffMark dialog
class	CEffTab;

class CEffMark : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffMark)

public:
	CEffMark(LOGFONT logfont);
	virtual ~CEffMark();

// Dialog Data
	enum { IDD = IDD_XMARK };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	DxEffCharMark*	EffMarkEdit;

public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffMark ( DxEffCharMark*	EffMarkX);
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
