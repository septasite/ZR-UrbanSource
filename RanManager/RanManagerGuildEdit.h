#pragma once


// CRanManagerGuildEdit dialog
class	CRanManagerGuildTab;
class CRanManagerGuildEdit : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerGuildEdit)

public:
	CRanManagerGuildEdit(LOGFONT logfont);
	virtual ~CRanManagerGuildEdit();

// Dialog Data
	enum { IDD = IDD_RM_GUILD_EDIT };

protected:
	CRanManagerGuildTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	void			SetToolTab		( CRanManagerGuildTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetGuild(int nGuildNum);

	void			LoadGuild(int nGuildNum);
	void			LoadMaster(int nMaster );
	BOOL			DropMaster(int nMaster);


public:
	CComboBox		m_cRank;
	CComboBox		m_cExpire;

public:


protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBtnEditCancel();
	afx_msg void OnBnClickedButtonSetG1();
	afx_msg void OnBnClickedButtonSetG2();
	afx_msg void OnBnClickedButtonSetG3();
	afx_msg void OnBnClickedButtonSetG4();
	afx_msg void OnBnClickedButtonSetG5();
	afx_msg void OnBnClickedButtonSetG6();
	afx_msg void OnBnClickedButtonResetG1();
	afx_msg void OnBnClickedButtonResetG2();
	afx_msg void OnBnClickedButtonResetG3();
	afx_msg void OnBnClickedButtonResetG4();
	afx_msg void OnBnClickedButtonResetG5();
	afx_msg void OnBnClickedButtonResetG6();
	afx_msg void OnBnClickedButtonChangemaster();
	afx_msg void OnBnClickedBtnEditSave();
};
