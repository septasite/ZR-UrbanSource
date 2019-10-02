#pragma once


// CRanManagerPetSkill dialog
class	CRanManagerPetTab;
class CRanManagerPetSkill : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerPetSkill)

public:
	CRanManagerPetSkill(LOGFONT logfont);
	virtual ~CRanManagerPetSkill();

// Dialog Data
	enum { IDD = IDD_RM_PET_SKILLS };

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
