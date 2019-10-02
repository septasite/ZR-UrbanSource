#pragma once

// CRanManagerMain dialog
class	CRanManagerTab;
class CRanManagerMain : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerMain)

public:
	CRanManagerMain(LOGFONT logfont);
	virtual ~CRanManagerMain();

// Dialog Data
	enum { IDD = IDD_RM_MAIN};

protected:
	CRanManagerTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	CEdit			m_cEditLog;
	CEdit			m_cEditInfo;

public:
	void			SetToolTab		( CRanManagerTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			AddLog( const char* szInfo );
	void			AddInfo( const char* szInfo );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);  

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();

};
