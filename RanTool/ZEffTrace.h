#pragma once

#include "DxEffAniTrace.h"
// AEffTrace dialog
class	AEffTab;

class AEffTrace : public CPropertyPage
{
	DECLARE_DYNAMIC(AEffTrace)

public:
	AEffTrace(LOGFONT logfont);
	virtual ~AEffTrace();

// Dialog Data
	enum { IDD = IDD_ZTRACE };

protected:
	AEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	DxEffAniData_Trace*	EffTraceEdit;

public:
	void			SetEffTab		( AEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffTrace ( DxEffAniData_Trace*	EffTraceX );
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
