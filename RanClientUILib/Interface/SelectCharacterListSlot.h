#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"
#include "UIOuterWindow.h"
#include "GLCharDefine.h"

const DWORD UIMSG_MOUSEIN_SELECT_CHARACTERLISTSLOT = UIMSG_USER1;

class	CSelectCharacterListImage;
class	CBasicScrollBarEx;
struct	SCHARINFO_LOBBY;

class	CSelectCharacterListSlot : public CUIGroup
{
protected:
static	const	int		nSTARTLINE;
static	const	int		nOUTOFRANGE;

protected:
	enum
	{
		SELECT_CHAR_ITEM0 = NO_ID + 1,
		SELECT_CHAR_ITEM1,
		SELECT_CHAR_ITEM2,
		SELECT_CHAR_ITEM3,
		SELECT_CHAR_ITEM4,
		SELECT_CHAR_ITEM5 = SELECT_CHAR_ITEM0 + GLCONST::MAX_SERVERCHAR,
	};

	enum
	{
		nMAX_ONE_VIEW_SLOT = 6
	};

public:
	CSelectCharacterListSlot ();
	virtual ~CSelectCharacterListSlot ();

public:
	void	CreateSubControl ( SCHARINFO_LOBBY sCharInfoArray[GLCONST::MAX_SERVERCHAR], int nCharCount );

public:
	virtual void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );

protected:
	void	ResetAllCharImageRender ( int nTotal );
	void	SetCharSlotRender ( int nStartIndex, int nTotal );

public:
	int					GetCharIndex()			{ return m_nImageIndex; }
	SCHARINFO_LOBBY		GetCharID ( int nIndex );

protected:
	CUIControl*	CreateControl ( const char* szControl );
	CSelectCharacterListImage*	CreateCharImage ( CString strKeyword, UIGUID ControlID, SCHARINFO_LOBBY sCharInfoID );

public:
	CSelectCharacterListImage*	m_pCharImageArray[GLCONST::MAX_SERVERCHAR];

private:
	CUIControl*	m_pCharImageArrayDummy[nMAX_ONE_VIEW_SLOT];

private:
	CBasicScrollBarEx*	m_pScrollBar;

private:
	int				m_nImageIndex;
	int				m_nCurPos;
	int				m_nMaxCharCnt;
	vector<int>		m_vecViewChar;
};
