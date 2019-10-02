#pragma	once

#include "UIWindowEx.h"
#include "GLItem.h"
#include "GlogicData.h"

class CItemImage;
class CBasicTextButton;
class CBasicAnimationBox;
class CBasicTextBox;
class CBasicButtonText;
class CBasicTextBoxEx;
class CBasicScrollBarEx;
class CCompoundWindowCheckBox;
class CCompoundWindowMenu;
class CItemImageRecipe;
class CBasicProgressBar;
//--------------------------------------------------------------------
// CItemMixWindow : //
//--------------------------------------------------------------------
class CItemMixWindow : public CUIWindowEx	
{
protected:
	enum
	{
		CHECK_CHECKLIST = ET_CONTROL_NEXT,
		ITEM_LIST_TEXTBOX,
		ITEM_LIST_SCROLLBAR,
		ITEM_COMPOUND_MONEY_BUTTON,
		ITEM_COMPOUND_GENERATE_BUTTON,
		RECIPE_IMAGE00, RECIPE_IMAGE01, RECIPE_IMAGE02, RECIPE_IMAGE03, RECIPE_IMAGE04,
		RESULT_IMAGE,

		SLOT_RECIPE_SIZE = 5
	};

protected:
	CItemImageRecipe*	m_pMeterialItemImage[SLOT_RECIPE_SIZE];
	CUIControl*     	m_pMeterialItemImageSlot[SLOT_RECIPE_SIZE];
	CUIControl*			m_pMeterialBackImage[ITEMMIX_ITEMNUM];
	
	CBasicAnimationBox*	m_pAniBox;
	CBasicTextButton*	m_pOkButton;
	CUIControl*			m_pBackImage;

	CUIControl*			m_pSuccessImage;
	CUIControl*			m_pFailImage;

	CBasicTextBox*		m_pMsgBox;

	bool	m_bOK;
	bool    m_bIsOK;
	bool	m_bResult;
	float	m_fTime;
	CBasicProgressBar*	m_pResult;
	CString	m_strResultMsg;
	CString m_strBasicMsg;
private:
	CCompoundWindowCheckBox*			m_pCheckBoxCheckList;

	CCompoundWindowCheckBox*			CreateCheckBox ( CString strKeyword, UIGUID ControlID );
	CItemImageRecipe*	                CreateItemImageRecipe( const char* szControl, UIGUID ControlID );
	CCompoundWindowMenu*				m_pMenu;
	CBasicButtonText*					m_pGenerateBtn;
	CBasicTextBox*						m_pTypeText;
	CBasicTextBox*						m_pTitleText;
	CBasicTextBox*						m_pRateText;
	CBasicTextBox*						m_pCostText;
	CBasicTextBox*						m_pAmountText;
	CBasicTextBox*						m_pGoldText;
	CBasicTextBox*						m_pResourceText;
	CBasicTextBox*						m_pTitleTextProgressBar;
	CBasicTextBox*						m_pRecipeNumText[5];
	CBasicTextBox*						m_pRecipeNumText2[5];
	CBasicTextBox*						CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, int nAlign );

	CBasicTextBoxEx*					m_pListText;
	CBasicScrollBarEx*					m_pListScrollBar;

	void								LoadItemList( WORD wType, bool bRefresh );

	WORD								m_wType;

	int									m_nSelectIndex;

	bool								m_bRefresh;
	bool								m_bMaterial;
	bool								m_bValid;

	CItemImage*							m_pItemResultImage;
	CItemImage*							m_pItemRecipeImage[5];

protected:
	SNATIVEID							m_sNativeID;
	SNATIVEID							m_sRecipeNativeID[5];

public:
	DWORD	m_dwNpcID;
	DWORD	m_dwKey;

public:
	CItemMixWindow();
	virtual	~CItemMixWindow();

public:
	VOID CreateSubControl();
	VOID CreateSubControlEx();
	VOID DoItemMix();
	void InitRecipe(int nIndex);
	void LoadRecipeList( int nPage );
	void Reset();
	void SetAnimation();
	bool SetItemMixResult( CString strMsg, bool bSuccess = false, bool bFail = false );

protected:
	CBasicTextBox*	CreateTextBox ( const char* szTextBox );


public:
	virtual	VOID Update( INT x, INT y, BYTE LB, BYTE MB, BYTE RB, INT nScroll, FLOAT fElapsedTime, BOOL bFirstControl );
	virtual	VOID TranslateUIMessage( UIGUID ControlID, DWORD dwMsg );
	virtual void SetVisibleSingle( BOOL bVisible );
};