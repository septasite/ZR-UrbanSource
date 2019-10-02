#pragma once


// CRanManagerCharPet dialog
class	CRanManagerCharTab;
class CRanManagerCharPet : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerCharPet)

public:
	CRanManagerCharPet(LOGFONT logfont);
	virtual ~CRanManagerCharPet();

// Dialog Data
	enum { IDD = IDD_RM_CHAR_PET };

protected:
	CRanManagerCharTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	void			SetToolTab		( CRanManagerCharTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetChar (int nChar);
	void			LoadChar(int nChar);
	void			LoadPet(int nChar);

public:
	CListCtrl		m_list_Pet;

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedButtonDelete2();
	afx_msg void OnBnClickedButtonDeleteAll2();
	afx_msg void OnBnClickedButtonCharpetCancel();
};
