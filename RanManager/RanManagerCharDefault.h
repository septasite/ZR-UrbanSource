#pragma once


// CRanManagerCharDefault dialog
class	CRanManagerCharTab;
class CRanManagerCharDefault : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerCharDefault)

public:
	CRanManagerCharDefault(LOGFONT logfont);
	virtual ~CRanManagerCharDefault();

// Dialog Data
	enum { IDD = IDD_RM_CHAR_BLANK };

protected:
	CRanManagerCharTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	void			SetToolTab		( CRanManagerCharTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
};
