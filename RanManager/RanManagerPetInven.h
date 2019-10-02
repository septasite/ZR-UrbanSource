#pragma once


// CRanManagerPetInven dialog
class	CRanManagerPetTab;
class CRanManagerPetInven : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerPetInven)

public:
	CRanManagerPetInven(LOGFONT logfont);
	virtual ~CRanManagerPetInven();

// Dialog Data
	enum { IDD = IDD_RM_PET_INVEN };

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
