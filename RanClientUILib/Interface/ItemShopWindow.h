#pragma	once

#include "UIWindowEx.h"
#include "GLCharDefine.h"
#include "../../RanClientLib/G-Logic/GlogicEx.h"

class	GLInventory;
struct	SINVENITEM;
class	CItemShopPage;
class	CBasicTextBox;
class	CBasicTextButton;
class	CItemShopWindowMenu;
class	CBasicComboBox;
class	CBasicComboBoxRollOver;
class	CItemShopWindow : public CUIWindowEx	
{
protected:
	enum
	{
		ITEMSHOP_REFRESH_BUTTON = ET_CONTROL_NEXT,
		ITEMSHOP_PAGE,
		ITEMSHOPCURRENCY_COMBO_OPEN,
		ITEMSHOPCURRENCY_COMBO_ROLLOVER,
	};

	CItemShopPage*	m_pPage;
private:
	static	const	int		nOUTOFRANGE;
	CBasicComboBox*			m_pComboBoxOpen;
	CBasicComboBoxRollOver*	m_pComboRollOver;
	CBasicTextBox*			m_pPPoints;
	CBasicTextBox*			m_pVPoints;
	UIGUID					m_RollOverID;
	BOOL					m_bFirstLBUP;
public:
	CItemShopWindow ();
	virtual	~CItemShopWindow ();

public:
	void	CreateSubControl ();

public:
	virtual	void SetVisibleSingle ( BOOL bVisible );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	virtual	VOID Update( INT x, INT y, BYTE LB, BYTE MB, BYTE RB, INT nScroll, FLOAT fElapsedTime, BOOL bFirstControl );
	
	void	SetData( const GLCHARLOGIC& sCharData );

	void	GetPosItem ( int* pnPosX, int* pnPosY );
	void	SetPosItem ( int nPosX, int nPosY );
	SINVENITEM&	GetItem ( int nPosX, int nPosY );
public:
	CItemShopWindowMenu*				m_pMenu;
	WORD								m_wType;
	int		m_nPosX;
	int		m_nPosY;
	int		m_nPageIndex;
	int		m_nPageCurrency;
	int		GetPageIndex ();
	int		GetPageCurrency ();
	void	InitItemShop ( WORD wType  , WORD wCurrency );
	void	ClearItemShop();
private:
	CBasicTextBox*	  CreateStaticControl ( const char* szControlKeyword, CD3DFontPar* pFont, int nAlign, const UIGUID& cID = NO_ID );
	CBasicTextButton*	CreateTextButton ( char* szButton, UIGUID ControlID, char* szText );

};