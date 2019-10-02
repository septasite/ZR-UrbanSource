#pragma	once

#include "UIWindowEx.h"

class CItemImage;
class CBasicTextButton;
class CItemRebuildOption;
class CItemRebuild : public CUIWindowEx	
{
protected:
	enum
	{
		ITEM_REBUILD_ITEM_SLOT = ET_CONTROL_NEXT,
		ITEM_REBUILD_COAST_TEXT_STATIC,
		ITEM_REBUILD_COAST_TEXT,
		ITEM_REBUILD_MONEY_BACK,
		ITEM_REBUILD_MONEY_IMAGE,
		ITEM_REBUILD_MONEY_TEXT,
		ITEM_REBUILD_OK_BUTTON,
		ITEM_REBUILD_CANCEL_BUTTON,
		ITEM_REBUILD_ITEM_OPTION00,
		ITEM_REBUILD_ITEM_OPTION01,
		ITEM_REBUILD_ITEM_OPTION02,
		ITEM_REBUILD_ITEM_OPTION03,
		ITEM_REBUILD_SEALED_CARD_SLOT,
	};

protected:
	CItemImage*		m_pItemImage;
	CItemImage*		m_pSealedCardImage;

	CBasicTextBox*	m_pCostTextBoxStatic;
	CBasicTextBox*	m_pCostTextBox;
	CBasicTextBox*	m_pMoneyTextBox;

	CBasicTextButton* m_pOkButton;

	CItemRebuildOption* m_pItemOption[4];

	int	m_nOption;

	bool m_bSEAL;

public:
	CItemRebuild();
	virtual	~CItemRebuild();

public:
	VOID CreateSubControl();

public:
	virtual	VOID Update( INT x, INT y, BYTE LB, BYTE MB, BYTE RB, INT nScroll, FLOAT fElapsedTime, BOOL bFirstControl );
	virtual	VOID TranslateUIMessage( UIGUID ControlID, DWORD dwMsg );

	CUIControl*		m_pWrap;

	CItemRebuildOption* CreateCheckBox ( CString strKeyword, UIGUID ControlID );

	void	SetOption(int nOpt) { m_nOption = nOpt; }
	int		GetOption() { return m_nOption; }

	void	ResetOption();
};