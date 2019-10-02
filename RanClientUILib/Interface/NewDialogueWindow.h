//	마켓 윈도우
//
//	최초 작성자 : 성기엽
//	이후 수정자 : 
//	로그
//		[2003.12.6]
//			@ 작성
//

#pragma	once

#include "UIWindowEx.h"
#include "GLDefine.h"
#include "GLCrowData.h"

class	CBasicTextButton;
struct	SINVENITEM;

class	CNewDialogueWindow : public CUIWindowEx
{
private:
static	const	int		nOUTOFRANGE;
protected:
	enum
	{
		nMAXPAGE = SCROWACTION::SALENUM
	};

	enum
	{
		DIALOG_PAGE0 = ET_CONTROL_NEXT,
		DIALOG_PAGE1,
		DIALOG_PAGE2,
		DIALOG_PAGE_END = DIALOG_PAGE0 + nMAXPAGE,
		DIALOG_WINDOW_PAGE_BUTTON0,
		DIALOG_WINDOW_PAGE_BUTTON1,
		DIALOG_WINDOW_PAGE_BUTTON2,
		DIALOG_WINDOW_PAGE_BUTTON_END = DIALOG_WINDOW_PAGE_BUTTON0 + nMAXPAGE,
	};

public:
	CNewDialogueWindow ();
	virtual	~CNewDialogueWindow ();

public:
	void	CreateSubControl ();
	void	SetVisiblePage ( int nPage );	

public:
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );

public:
	void		InitMarket ( SNATIVEID sNativeID );

public:
	SNATIVEID	GetMarketID ();

	void	SetItemIndex ( int nPosX, int nPosY );
	void	GetItemIndex ( int* pnPosX, int* pnPosY );	

	int		GetPageIndex ();

	SINVENITEM&	GetItem ( int nPosX, int nPosY );

	BOOL	IsUsingMaketPage( int nPage );

private:
	SNATIVEID	m_sMarketID;

private:
	int		m_nPosX;
	int		m_nPosY;

	int		m_nPageIndex;

protected:
	//CMarketPage*	CreateMarketPage ( UIGUID ControlID );
	CBasicTextButton*	CreateTextButton ( const char* szButton, UIGUID ControlID, const char* szText );

private:
	//CMarketPage*		m_pPage[nMAXPAGE];
	CBasicTextButton*	m_pPageButton[nMAXPAGE];
};