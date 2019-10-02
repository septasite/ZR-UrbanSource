#pragma once

#include "../NetServerLib/minTea.h"
// CRanManagerUserNew dialog
class	CRanManagerUserTab;
class CRanManagerUserNew : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerUserNew)

public:
	CRanManagerUserNew(LOGFONT logfont);
	virtual ~CRanManagerUserNew();

// Dialog Data
	enum { IDD = IDD_RM_USER_NEW };

protected:
	CRanManagerUserTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	minTea			m_Tea;
	TCHAR*			szOut;
	CComboBox		m_cUserType;

public:
	void			SetToolTab		( CRanManagerUserTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void 			ConvertMD5(const TCHAR* szText,int nType);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonMd51();
	afx_msg void OnBnClickedButtonMd52();
	afx_msg void OnBnClickedButtonCreateuser();
	afx_msg void OnBnClickedButtonCreatecancel();
};
