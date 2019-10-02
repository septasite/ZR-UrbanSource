#pragma	once

#include "UIWindowEx.h"
#include "GLDefine.h"
#include "GLogicEx.h"
#include "GLCrowData.h"
#include "../RanClientLib/NpcTalk/NpcDialogueSet.h"

class	CBasicTextBoxEx;
class	CBasicScrollBarEx;
struct	SNpcTalk;
class	CNpcDialogueCase;
class	CBasicTextButton;
class	CBasicButtonText;
class	CBasicLineBox;
class	CBasicLineBoxEx;
class	CMarketPage;
class	CNewBuyItem;
class	CInterestItem;
struct	SINVENITEM;

class CDialogueWindow : public CUIWindowEx
{
private:
static	const	int		nSTARTINDEX;
static	const	int		nSTARTLINE;
static	const	float	fANSWER_PART_INTERVAL;
static	const	int		nMAXPAGENEW = 5 ;
static	const	int		nOUTOFRANGE;
private:
	enum
	{
		nMAXPAGE = SCROWACTION::SALENUM
	};
	enum
	{
		NEW_MARKET_PAGE0 = ET_CONTROL_NEXT,
		NEW_MARKET_PAGE1,
		NEW_MARKET_PAGE2,
		NEW_MARKET_PAGE_END = NEW_MARKET_PAGE0 + nMAXPAGE,
		INTEREST_ITEM_PAGE0,
		INTEREST_ITEM_PAGE1,
		INTEREST_ITEM_PAGE2,
		DIALOGUE_WINDOW_PAGE_BUTTON0,
		DIALOGUE_WINDOW_PAGE_BUTTON1,
		DIALOGUE_WINDOW_PAGE_BUTTON2,
		DIALOGUE_WINDOW_PAGE_BUTTON3,
		DIALOGUE_WINDOW_PAGE_BUTTON4,
		DIALOGUE_QUESTION_TEXTBOX,
		BASIC_DIALOGUE_SCROLLBAR,
		DIALOGUE_ANSWER_TEXTBOX,
		BASIC_DIALOGUE_ANSWER_SCROLLBAR,
		RANDOM_TIME_BUTTON,
		RANDOM_TIME_TEXT,
		NEW_BUY_ITEM_WINDOW,
		INTEREST_ITEM_WINDOW,
		CLOSE_BUTTON,
		BUY_BUTTON,
		BUTTON_CAN_USE,
		BUTTON_CAN_BUY,
		BUTTON_CAN_USE_SET,
		BUTTON_CAN_BUY_SET,
		NEW_PURCHASE_IMAGE,
	};

public:
	CDialogueWindow ();
	virtual	~CDialogueWindow ();
	
	float	m_fRandomTime;		// 흐른시간
	DWORD	m_dwRandomTime;		// 제한시간

	CUIControl*			m_pPurchaseImage;
	CUIControl*			m_pButtonImage[2];
	CUIControl*			m_pButtonImageSet[2];
	CUIControl*			m_bg_white;

	void		InitMarket ( SNATIVEID sNativeID );
	void		InitMarket ();

	SNATIVEID	GetMarketID ();

	void	SetItemIndex ( int nPosX, int nPosY );
	void	GetItemIndex ( int* pnPosX, int* pnPosY );	

	int		GetPageIndex ();

	SINVENITEM&	GetItem ( int nPosX, int nPosY );

	BOOL	IsUsingMaketPage( int nPage );
	BOOL	IsUse;
	BOOL	IsBuy;

	SNATIVEID	m_sMarketID;

	int		m_nPosX;
	int		m_nPosY;

	int		m_nPageIndex;

public:
	void	CreateSubControl ();

public:
	BOOL	SetDialogueData ( STARGETID sCrowID, GLCHARLOGIC *pCHAR );
	STARGETID	GetCrowID ()				{ return m_sCrowID; }

public:
	virtual	void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );

private:
	void	TranslateTalkMessage ( SNpcTalk* pNpcTalk );
	void	TranslateBasicMessage ( SNpcTalk* pNpcTalk );
	void	TranslateQuestStartMessage ( SNpcTalk* pNpcTalk );
	void	TranslateQuestStepMessage ( SNpcTalk* pNpcTalk );

public:
	void	LoadNode(DWORD NativeID, bool bRandom = false, DWORD dwRandomTime = 0 );
	void	LoadBasicTalk ();
	void	LoadButtonTalk ( bool bRandom = false );
	void	SetVisible ( int nPage );
	void	SetPageFalse ( int nPage );
	void	ClearItem();
	void	ReItemPosition( int x , int y);
	void	AddPrice( DWORD price );
	void	DelPrice( DWORD price );

	LONGLONG	Money;
	DWORD		MoneyTotal;	
	BOOL		m_pHaveItem;
	int			m_pCountSlot;

	CBasicTextButton*	CreateTextButton ( const char* szButton, UIGUID ControlID, const char* szText );
	CBasicTextButton*	CreateTextButton24 ( const char* szButton, UIGUID ControlID, const char* szText );
	CMarketPage*	CreateMarketPage ( UIGUID ControlID );
	CInterestItem*	CreateInterestItemPage( UIGUID ControlID );
	CBasicButtonText*	m_pBuyButton;
	CBasicButtonText*	m_pCloseButton;

	CBasicButtonText*	CreateButtonBlue ( char* szButton, char* szTextBox, CD3DFontPar* pFont, int nAlign, UIGUID ControlID, CString strText );

private:
	CBasicTextBox*		m_pQuestionBox;
	CBasicScrollBarEx*	m_pScrollBar;
	CBasicTextBoxEx*	m_pAnswerBox;
	CBasicScrollBarEx*	m_pAnswerScrollBar;
	CBasicTextButton*	m_pRandomTimeButton;
	CBasicTextBox*		m_pRandomTimeText;
	CBasicLineBox*		m_pRandomTimeBack;
	CBasicLineBoxEx*		m_pBasicLineBox;
	CBasicLineBoxEx*		m_pBasicLineBox1;
	CBasicLineBoxEx*		m_pBasicLineBox2;
	CBasicLineBoxEx*		m_pBasicLineBox3;
	CBasicLineBoxEx*		m_pBasicLineBox4;
	CBasicLineBoxEx*		m_pBasicLineBox5;
	CBasicLineBoxEx*		m_pBasicLineBox6;
	CBasicLineBoxEx*		m_pBasicLineBox7;
	CBasicLineBoxEx*		m_pBasicLineBox8;
	CBasicLineBoxEx*		m_pBasicLineBox9;
	CBasicLineBoxEx*		m_pBasicLineBox10;
	CBasicLineBoxEx*		m_pBasicLineBox11;

	CBasicLineBoxEx*		m_pBasicLineBox12;
	CBasicLineBoxEx*		m_pBasicLineBox13;
	CBasicLineBoxEx*		m_pBasicLineBox14;
	CBasicLineBoxEx*		m_pBasicLineBox15;
	CBasicLineBoxEx*		m_pBasicLineBox16;
	CBasicLineBoxEx*		m_pBasicLineBox17;

	CBasicTextButton*	m_pPageButton[nMAXPAGENEW];
	CMarketPage*		m_pPage[nMAXPAGE];
	CNewBuyItem*		m_pPageItem;
	CInterestItem*		m_pInterestItemPage[nMAXPAGE];
	CBasicTextBox*		m_pMoney;
	CBasicTextBox*		m_pMoneyItem;
	CBasicTextBox*		m_pMoneyItemTitle;
	CBasicTextBox*		m_pText[nMAXPAGE];
	CBasicTextBox*		m_pNameItem[nMAXPAGENEW];
	CBasicTextBox*		m_pPriceItem[nMAXPAGENEW];


private:
	CNpcDialogueSet		m_DialogueSet;
	CNpcDialogue*		m_pDialogue;
	CNpcDialogueCase*	m_pDialogueCase;

private:
	GLCHARLOGIC*	m_pCHAR;
	STARGETID		m_sCrowID;
};