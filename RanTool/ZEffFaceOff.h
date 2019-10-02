#pragma once

#include "DxEffAniFaceOff.h"
// AEffFaceOff dialog
class	AEffTab;

class AEffFaceOff : public CPropertyPage
{
	DECLARE_DYNAMIC(AEffFaceOff)

public:
	AEffFaceOff(LOGFONT logfont);
	virtual ~AEffFaceOff();

// Dialog Data
	enum { IDD = IDD_ZFACEOFF };

protected:
	AEffTab*		m_pEffTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	DxEffAniData_FaceOff*	EffFaceOffEdit;

public:
	void			SetEffTab		( AEffTab *pEffTab ) { m_pEffTab = pEffTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetEffFaceOff ( DxEffAniData_FaceOff*	EffFaceOffX );
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
