#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"
#include "GLCharDefine.h"

class	CBasicButton;
class	CBasicTextBox;
class	CBasicLineBox;
class	CBasicTextButton;
class	CSelectCharacterInfoPage;
struct	SCHARINFO_LOBBY;


const DWORD UIMSG_MOUSEIN_SELECT_CHARACTERPAGE = UIMSG_USER1;

class CSelectCharacterPage : public CUIGroup
{
private:
	enum
	{
		SELECT_CHARACTER_START = NO_ID + 1,
		SELECT_CHARACTER_CANCEL,
		SELECT_CHARACTER_NEW,
		SELECT_CHARACTER_DELETE,
		SELECT_PAGE_CHARACTER_POSITION0,
		SELECT_PAGE_CHARACTER_POSITION1,
		SELECT_PAGE_CHARACTER_POSITION2,
		SELECT_PAGE_CHARACTER_POSITION3,
		SELECT_PAGE_CHARACTER_CLASS0,
		SELECT_PAGE_CHARACTER_CLASS1,
		SELECT_PAGE_CHARACTER_CLASS2,
		SELECT_PAGE_CHARACTER_CLASS3,
		SELECT_PAGE_CHARACTER_CLASS_NAME0,
		SELECT_PAGE_CHARACTER_CLASS_NAME1,
		SELECT_PAGE_CHARACTER_CLASS_NAME2,
		SELECT_PAGE_CHARACTER_CLASS_NAME3,
	};

public:
	CSelectCharacterPage ();
	virtual	~CSelectCharacterPage ();

public:
	void	CreateSubControl ();
	int		m_nPosition;
	void	SELECT_CLASS_PROCESS( int nSelect );

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );

public:
	BOOL	SndGameJoin ();
	BOOL	DelChar;
	BOOL	HaveCharacter_A;
	BOOL	HaveCharacter_B;
	BOOL	HaveCharacter_C;
	BOOL	HaveCharacter_D;

	D3DXVECTOR3 MousePose;

	int		Select;
	
public:
	void	ResetAll ();
	void    SetLeftButtonState(BOOL bState);
	void    SetRightButtonState(BOOL bState);
	void	SetPageNum(int nPageNum);
	int		GetPageNum();
	void    InitCharacter( EMCHARCLASS m_emClass ,int position);

	void	SetCharacterA( BOOL a)		{ HaveCharacter_A = a;}
	void	SetCharacterB( BOOL b)		{ HaveCharacter_B = b;}
	void	SetCharacterC( BOOL c)		{ HaveCharacter_C = c;}
	void	SetCharacterD( BOOL d)		{ HaveCharacter_D = d;}

	void	SetCharInfoA( SCHARINFO_LOBBY* charA);
	void	SetCharInfoB( SCHARINFO_LOBBY* charB);
	void	SetCharInfoC( SCHARINFO_LOBBY* charC);
	void	SetCharInfoD( SCHARINFO_LOBBY* charD);

	void	ShowClassPos1();
	void	ShowClassPos2();
	void	ShowClassPos3();
	void	ShowClassPos4();

	void	SetDelCharacter();

	void	SetLok(D3DXVECTOR3 lok)		{ MousePose = lok;}

private:
	CSelectCharacterInfoPage* m_pSelectCharacterPage;

public:
	SCHARINFO_LOBBY * GetDelCharInfo()				{ return m_pDelCharInfo; }

	CUIControl*			m_pFirstPosition;

	CUIControl*			m_pCharacterPosition[4];
	CUIControl*			m_pCharacterPositionSet[4];

	//CUIControl*			m_pCharacterClass[4];
	//CUIControl*			m_pCharacterClassSet[4];

	CUIControl*			m_pCharacterClassPos1[GLCI_NUM_NEWEST];
	CUIControl*			m_pCharacterClassSetPos1[GLCI_NUM_NEWEST];

	CUIControl*			m_pCharacterClassPos2[GLCI_NUM_NEWEST];
	CUIControl*			m_pCharacterClassSetPos2[GLCI_NUM_NEWEST];

	CUIControl*			m_pCharacterClassPos3[GLCI_NUM_NEWEST];
	CUIControl*			m_pCharacterClassSetPos3[GLCI_NUM_NEWEST];

	CUIControl*			m_pCharacterClassPos4[GLCI_NUM_NEWEST];
	CUIControl*			m_pCharacterClassSetPos4[GLCI_NUM_NEWEST];

	CBasicTextBox*      m_pNameClassPos[4];
	CBasicTextBox*      m_pNameClass[4];
	CBasicTextBox*      m_pLevelClass[4];


private:
	SCHARINFO_LOBBY* m_pDelCharInfo;
	SCHARINFO_LOBBY* pCharInfoA;
	SCHARINFO_LOBBY* pCharInfoB;
	SCHARINFO_LOBBY* pCharInfoC;
	SCHARINFO_LOBBY* pCharInfoD;

	USHORT m_uCharRemain;

	CBasicTextButton* m_pStartButton;
	CBasicTextButton* m_pNewButton;
	CBasicTextButton* m_pCancelButton;
	CBasicTextButton* m_pDeleteButton;
	CBasicTextBox*    m_pNameStatic;
	CBasicLineBox*	  m_pBasicLineBox;
	CBasicLineBox*	  m_pBasicLineBoxServer;
	CBasicLineBox*	  m_pBasicLineBoxSelect;
	SCHARINFO_LOBBY*   m_pCharInfoBack;

	UIRECT rcLocalPos;


};