#pragma once

#include "DxEffCharAttribute.h"
// CEffAttribute dialog
class	CEffTab;

class CEffAttribute : public CPropertyPage
{
	DECLARE_DYNAMIC(CEffAttribute)

public:
	CEffAttribute(LOGFONT logfont);
	virtual ~CEffAttribute();

// Dialog Data
	enum { IDD = IDD_XATTRI };

protected:
	CEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	DxEffCharAttribute*	EffAttributeEdit;

public:
	void			SetEffTab		( CEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffAttribute ( DxEffCharAttribute*	EffAttributeX);
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
