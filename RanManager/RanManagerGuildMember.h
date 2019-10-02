#pragma once


// CRanManagerGuildMember dialog
class	CRanManagerGuildTab;
class CRanManagerGuildMember : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerGuildMember)

public:
	CRanManagerGuildMember(LOGFONT logfont);
	virtual ~CRanManagerGuildMember();

// Dialog Data
	enum { IDD = IDD_RM_GUILD_MEMBER };

protected:
	CRanManagerGuildTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	void			SetToolTab		( CRanManagerGuildTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetGuild(int nGuildNum);
	void			GetGuild(int nGuildNum);
	void			GetMembers(int nGuildNum);
	BOOL			RemoveMember(int nChaNum);
	BOOL			HaveGuild(int nChaNum);
	BOOL			JoinGuild(int nChaNum);

public:
	CListCtrl		m_list_Char;
	CComboBox		m_cSearchType;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnMemberCancel();
	afx_msg void OnBnClickedButtonMemberRemoveall();
	afx_msg void OnBnClickedButtonMemberRemove();
	afx_msg void OnBnClickedButtonMemberEdit();
	afx_msg void OnCbnSelchangeComboSearchType();
	afx_msg void OnBnClickedButtonGuildsearch();
	afx_msg void OnBnClickedButtonMemberAdd();
	afx_msg void OnBnClickedButtonChaSave();
	afx_msg void OnBnClickedButtonChaCancel();
};
