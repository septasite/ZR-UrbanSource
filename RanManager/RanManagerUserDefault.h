#pragma once


// CRanManagerUserDefault dialog
class	CRanManagerUserTab;
class CRanManagerUserDefault : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerUserDefault)

public:
	CRanManagerUserDefault(LOGFONT logfont);
	virtual ~CRanManagerUserDefault();

// Dialog Data
	enum { IDD = IDD_RM_USER_BLANK };

protected:
	CRanManagerUserTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	void			SetToolTab		( CRanManagerUserTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
};
