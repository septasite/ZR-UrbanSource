#pragma	once

#include "UIWindowEx.h"
#include "GLFriendClient.h"

class	CBasicTextBoxEx;
class	CBasicScrollBarEx;
class	CBasicTextButton;
class	CUIEditBox;
class	CBasicButtonText;

class	CFriendWindowBlockPage : public CUIGroup
{
private:
static	const int nLIMIT_CHAR;

private:
	enum
	{
		FRIEND_LIST_TEXTBOX = NO_ID + 1,
		FRIEND_LIST_SCROLLBAR,
		FRIEND_LIST_ADD_BLOCK_BUTTON,
		FRIEND_LIST_DEL_BLOCK_BUTTON,
		FRIEND_EDITBOX_BLOCK
	};

public:
	CFriendWindowBlockPage ();
	virtual ~CFriendWindowBlockPage ();

public:
	void	CreateSubControl ();
	CBasicTextButton*	CreateTextButton24 ( const char* szButton, UIGUID ControlID, const char* szText );	
	CBasicButtonText*	CreateButtonBlue ( char* szButton, char* szTextBox, CD3DFontPar* pFont, int nAlign, UIGUID ControlID, CString strText );

public:
	void	LoadBlockList ();

public:
	virtual	void SetVisibleSingle ( BOOL bVisible );

public:
	void	ADD_NAME_TO_EDITBOX ( const CString& strName );
	void	ADD_BLOCK ( const CString& strName );
	void	DEL_BLOCK ( const CString& strName );
	const CString& GET_BLOCK_NAME () const						{ return m_strSelectName; }

public:
	virtual	void	Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void	TranslateUIMessage ( UIGUID cID, DWORD dwMsg );

private:
	void	LoadBlockFriend ( const SFRIEND& sFriend );
	CString	GetFriend ( const int nCharID );

	void	EDIT_BEGIN ( const CString& strName = "" );

public:
	void	EDIT_END ();	

private:
	int		m_nSelectIndex;
	CString	m_strSelectName;

private:
	CBasicTextBoxEx*	m_pListText;
	CBasicScrollBarEx*	m_pListScrollBar;

	CBasicButtonText*	m_pADD_BLOCK;
	CBasicButtonText*	m_pDEL_BLOCK;

	CUIEditBox*			m_pEditBox;
};