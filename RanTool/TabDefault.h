#pragma once


// CTabDefault dialog

class	CToolTab;

class CTabDefault : public CPropertyPage
{
	DECLARE_DYNAMIC(CTabDefault)

public:
	CTabDefault(LOGFONT logfont);
	virtual ~CTabDefault();

	enum { IDD = IDD_DEFAULT };

protected:
	CToolTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	CEdit			m_cEditHistory;


public:
	void			SetToolTab		( CToolTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			AddEditString( const char* szInfo );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

};

	int CALLBACK BrowseCallbackProc(HWND hwnd, UINT uMsg, LPARAM lParam, LPARAM dwData);
