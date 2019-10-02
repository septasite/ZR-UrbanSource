#pragma once


// CItemSimple 대화 상자입니다.
class	CsheetWithTab;
struct	SITEMSIMPLE;
class CItemSimple : public CPropertyPage
{
	DECLARE_DYNAMIC(CItemSimple)

public:
	CItemSimple();
	virtual ~CItemSimple();

// 대화 상자 데이터입니다.
	enum { IDD = IDD_ITEMSIMPLE_DIALOG };

protected:
	CsheetWithTab*	m_pSheetTab;
	int				m_CallPage;

	SITEMSIMPLE*	m_pDummyItem;
	SITEMSIMPLE*	m_pItem;

	BOOL			m_bDlgInit;

public:
	void	SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void	SetSheetTab ( CsheetWithTab* pSheetTab ) { m_pSheetTab = pSheetTab; }
	BOOL	SetItem ( SITEMSIMPLE* pItem );

protected:
	void	UpdateItems ();
	void	InverseUpdateItems ();
	void	InitDefaultCtrls ();

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 지원입니다.

	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonCancel();
	afx_msg void OnBnClickedButtonOk();
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonPrev();
};
