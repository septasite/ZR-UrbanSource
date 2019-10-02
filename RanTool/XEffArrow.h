#pragma once

#include "DxEffCharArrow.h"
// CEffArrow dialog
class	CEffTab;

class CEffArrow : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffArrow)

public:
	CEffArrow(LOGFONT logfont);
	virtual ~CEffArrow();

// Dialog Data
	enum { IDD = IDD_XARROW };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	DxEffCharArrow*	EffArrowEdit;

public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffArrow ( DxEffCharArrow*	EffArrowX);
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
