#pragma once


// CRanManagerPetDefault dialog
class	CRanManagerPetTab;
class CRanManagerPetDefault : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerPetDefault)

public:
	CRanManagerPetDefault(LOGFONT logfont);
	virtual ~CRanManagerPetDefault();

// Dialog Data
	enum { IDD = IDD_RM_PET_BLANK };

protected:
	CRanManagerPetTab*		m_pToolTab;
	CFont*			m_pFont;
	int				m_CallPage;
	BOOL			m_bDlgInit;

public:
	void			SetToolTab		( CRanManagerPetTab *pToolTab ) { m_pToolTab = pToolTab; }
	void			SetCallPage ( int CallPage ) { m_CallPage = CallPage; }
	void			SetPet(int nPetNum);

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV support

	DECLARE_MESSAGE_MAP()

public:
	virtual BOOL OnInitDialog();
};
