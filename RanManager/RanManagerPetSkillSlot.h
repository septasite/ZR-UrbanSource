#pragma once


// CRanManagerPetSkillSlot dialog
class	CRanManagerPetTab;
class CRanManagerPetSkillSlot : public CPropertyPage
{
	DECLARE_DYNAMIC(CRanManagerPetSkillSlot)

public:
	CRanManagerPetSkillSlot(LOGFONT logfont);
	virtual ~CRanManagerPetSkillSlot();

// Dialog Data
	enum { IDD = IDD_RM_PET_SKILLSLOT };

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
