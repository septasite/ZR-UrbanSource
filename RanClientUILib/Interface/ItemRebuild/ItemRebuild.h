#pragma	once

#include "../UIWindowEx.h"
#include "GLDefine.h"
#include "../RanClientLib/G-Logic/GLItem.h"

class CItemImage;
class CItemRebuildOption;
class CBasicTextButton;

//--------------------------------------------------------------------
// ItemRebuild : √÷¡ÿ«ı
//--------------------------------------------------------------------
class CItemRebuild : public CUIWindowEx	// ITEMREBUILD_MARK
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
	CItemImage*		m_pSealImage; //sealed card
	CBasicTextBox*	m_pCostTextBoxStatic;
	CBasicTextBox*	m_pCostTextBox;
	CBasicTextBox*	m_pMoneyTextBox;
	CBasicTextButton* m_pOkButton;

public:
	CItemRebuild();
	virtual	~CItemRebuild();

public:
	VOID CreateSubControl();

public:
	virtual	VOID Update( INT x, INT y, BYTE LB, BYTE MB, BYTE RB, INT nScroll, FLOAT fElapsedTime, BOOL bFirstControl );
	virtual	VOID TranslateUIMessage( UIGUID ControlID, DWORD dwMsg );

	CItemRebuildOption* CreateCheckBox ( CString strKeyword, UIGUID ControlID );

protected: //sealed card
	CItemRebuildOption*		m_pOption[4];
	int m_nSelOption[2];

public:
	void SetOption( BOOL bOPT );

	SITEMSEALDATA	m_SealData01;
	SITEMSEALDATA	m_SealData02;

	int GetOption1() { return m_nSelOption[0]; }
	int GetOption2() { return m_nSelOption[1]; }

};