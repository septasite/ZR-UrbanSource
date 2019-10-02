#pragma once


// CRanViewDlg dialog
class	CRanViewTab;
class CRanViewDlg : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanViewDlg)

public:
	CRanViewDlg(LOGFONT logfont);
	virtual ~CRanViewDlg();

// Dialog Data
	enum { IDD = IDD_DLGTOOL };

protected:
	CRanViewTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;
	CSliderCtrl		Slider_R;
	CSliderCtrl		Slider_G;
	CSliderCtrl		Slider_B;

public:
	void			SetToolTab		( CRanViewTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetColor();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonAnimate();
	afx_msg void OnBnClickedButtonSet();
	afx_msg void OnCbnSelchangeComboEdittype();
	afx_msg void OnBnClickedButtonSet2();
	afx_msg void OnNMCustomdrawSliderR(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderG(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnNMCustomdrawSliderB(NMHDR *pNMHDR, LRESULT *pResult);
};
