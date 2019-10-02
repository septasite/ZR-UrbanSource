#pragma once

class	CRanManagerTab;
class	CRanManagerGuildTab;
// CRanManagerGuild dialog

class CRanManagerGuild : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerGuild)

public:
	CRanManagerGuild(LOGFONT logfont);
	virtual ~CRanManagerGuild();

// Dialog Data
	enum { IDD = IDD_RM_GUILD };

protected:
	CRanManagerTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	void			SetToolTab		( CRanManagerTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }

public:
	CRanManagerGuildTab	*m_pGuildTab;
	CListCtrl		m_list_Guild;
	CComboBox		m_cSearchType;
	CComboBox		m_cGuildPage;

public:
	typedef std::vector<int>			VEC_SEARCH_NUM;
	typedef VEC_SEARCH_NUM::iterator	VEC_SEARCH_NUM_ITER;
	VEC_SEARCH_NUM	m_VecSearchNum;
	int				nGuildNum;
	CString			strGuild;

public:
	void	GetMaster();
	void	GetMembers();
	void	GetGuildMaster( std::string strSearch );

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonSearch();
	afx_msg void OnCbnSelchangeComboCharsearchtype();
	afx_msg void OnNMDblclkListGuild(NMHDR *pNMHDR, LRESULT *pResult);
	afx_msg void OnBnClickedButtonGuildSelect();
};
