#pragma once

#include "DxEffAniSingle.h"
// AEffSingle dialog
class	AEffTab;

class AEffSingle : public CPropertyPage
{
	DECLARE_DYNAMIC(AEffSingle)

public:
	AEffSingle(LOGFONT logfont);
	virtual ~AEffSingle();

// Dialog Data
	enum { IDD = IDD_ZSINGLE };

protected:
	AEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	DxEffAniData_Single*	EffSingleEdit;

public:
	void			SetEffTab		( AEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffSingle ( DxEffAniData_Single*	EffSIngleX );
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
