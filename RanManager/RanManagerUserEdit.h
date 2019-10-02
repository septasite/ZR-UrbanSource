#pragma once

#include "../NetServerLib/minTea.h"
// CRanManagerUserEdit dialog
class	CRanManagerUserTab;
class CRanManagerUserEdit : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerUserEdit)

public:
	CRanManagerUserEdit(LOGFONT logfont);
	virtual ~CRanManagerUserEdit();

// Dialog Data
	enum { IDD = IDD_RM_USER_EDIT };

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
	void			SetUser(int nUser);
	void			LoadUser(int nNum );
	void 			ConvertMD5(const TCHAR* szText,int nType);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonMd51();
	afx_msg void OnBnClickedButtonMd52();
	afx_msg void OnBnClickedBtnEditCreatedate();
	afx_msg void OnBnClickedBtnEditLastlogin();
	afx_msg void OnBnClickedBtnEditUserblock();
	afx_msg void OnBnClickedBtnEditPremiumdate();
	afx_msg void OnBnClickedBtnEditChatblock();
	afx_msg void OnBnClickedBtnEditSave();
	afx_msg void OnBnClickedBtnEditCreatedate2();
	afx_msg void OnBnClickedBtnEditLastlogin2();
	afx_msg void OnBnClickedBtnEditUserblock2();
	afx_msg void OnBnClickedBtnEditPremiumdate2();
	afx_msg void OnBnClickedBtnEditChatblock2();
	afx_msg void OnBnClickedBtnEditCancel();
};
