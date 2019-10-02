#pragma once


// CRanManagerGuildImage dialog
class	CRanManagerGuildTab;
class CRanManagerGuildImage : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerGuildImage)

public:
	CRanManagerGuildImage(LOGFONT logfont);
	virtual ~CRanManagerGuildImage();

// Dialog Data
	enum { IDD = IDD_RM_GUILD_IMAGE };

protected:
	CRanManagerGuildTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	void			SetToolTab		( CRanManagerGuildTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetGuild(int nGuildNum);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnImageCancel();
};
