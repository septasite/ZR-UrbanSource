#pragma once


// CTabMMP dialog

class	CToolTab;

class CTabMMP : public CPropertyPage
{
	DECLARE_DYNAMIC(CTabMMP)

public:
	CTabMMP(LOGFONT logfont);
	virtual ~CTabMMP();

	enum { IDD = IDD_MMP_DIALOG };

protected:
	CToolTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	void			SetToolTab		( CToolTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			Reset();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

protected:
	int m_nLX;
	int m_nTY;
	int m_nRX;
	int m_nBY;
	int m_nSizeX;
	int m_nSizeY;
	int m_nCalcLX;
	int m_nCalcBY;
	CString m_strDDSFileName;
	RECT GetBitmapPosition();
	void MiniMapPositionCalc( RECT & rect);
	BOOL MiniMapPositionSave( CString & strPathName, CString & strBUFFER );

public:
	CStatic m_csFileName;
	CEdit	m_ctrlEditView;
	CStatic m_csDDSFileName;

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButton1();
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedOk();
};
