#pragma once

#include <string>
#include <vector>
// CGuildSearch dialog

class CGuildSearch : public CDialog
{
	DECLARE_DYNAMIC(CGuildSearch)

public:
	CGuildSearch(CWnd* pParent = NULL);   // standard constructor
	virtual ~CGuildSearch();

// Dialog Data
	enum { IDD = IDD_GUILD_DLG };

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	typedef std::vector<int>			VEC_SEARCH_NUM;
	typedef VEC_SEARCH_NUM::iterator	VEC_SEARCH_NUM_ITER;
	VEC_SEARCH_NUM	m_VecSearchNum;
	CListCtrl		m_list_Guild;
	CComboBox		m_cSearchType;
	int	nSelectedGuild;


public:
	void	LoadGuild();
	void	GetMaster();
	void	GetMembers();
	void	GetGuildMaster( std::string strSearch );

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonGuildsearch();
	afx_msg void OnBnClickedButtonOk();
};
