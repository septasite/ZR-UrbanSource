#pragma once


// CCharSearch dialog
class CCharSearch : public CDialog
{
	DECLARE_DYNAMIC(CCharSearch)

public:
	CCharSearch(CWnd* pParent = NULL);   // standard constructor
	virtual ~CCharSearch();

// Dialog Data
	enum { IDD = IDD_CHAR_DLG };

public:
	CListCtrl		m_list_Char;
	CComboBox		m_cSearchType;


public:
	void		ReadAllChar();
	void		ReadGuilds();
	void		SetMultiple(bool bEnable)	{	bMultiple = bEnable;	}

public:
	typedef std::vector<int>		VEC_CHAR_SEARCH_RESULT;
	typedef VEC_CHAR_SEARCH_RESULT::iterator	VEC_CHAR_SEARCH_RESULT_ITER;
	VEC_CHAR_SEARCH_RESULT	m_VecSearchResult;
	int			nSelectedChar;
	bool		bMultiple;

	

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonOk();
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonGuildsearch();
	afx_msg void OnCbnSelchangeComboSearchType();
};
