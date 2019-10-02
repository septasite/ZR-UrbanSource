//	?? ?? ??
//
//	?? ??? : ???
//	?? ??? : 
//	??
//		[2003.11.27]
//			@ ??
//

#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"
#include "../Interface/UIWindowEx.h"
#include "GLItem.h"

class	CBasicButton;
class	CBasicTextBox;
class	CBasicLineBoxEx;
class	CD3DFontPar;
struct	SNATIVEID;
class	GLItem;
class CItemImage;
class	CBoxItemInfo : public CUIWindowEx//public CUIGroup
{
	enum
	{
		ITEM_IMAGE0 = ET_CONTROL_NEXT,
		ITEM_IMAGE1,
		ITEM_IMAGE2,
		ITEM_IMAGE3,
		ITEM_IMAGE4,
		ITEM_IMAGE5,
		ITEM_IMAGE6,
		ITEM_IMAGE7,
		ITEM_IMAGE8,
		ITEM_IMAGE9,

		ITEM_IMAGERANDOM0,
		ITEM_IMAGERANDOM1,
		ITEM_IMAGERANDOM2,
		ITEM_IMAGERANDOM3,
		ITEM_IMAGERANDOM4,
		ITEM_IMAGERANDOM5,
		ITEM_IMAGERANDOM6,
		ITEM_IMAGERANDOM7,
		ITEM_IMAGERANDOM8,
		ITEM_IMAGERANDOM9,
		ITEM_IMAGERANDOM10,
		ITEM_IMAGERANDOM11,
		ITEM_IMAGERANDOM12,
		ITEM_IMAGERANDOM13,
		ITEM_IMAGERANDOM14,
		ITEM_IMAGERANDOM15,
		ITEM_IMAGERANDOM16,
		ITEM_IMAGERANDOM17,
		ITEM_IMAGERANDOM18,
		ITEM_IMAGERANDOM19,
		ITEM_IMAGERANDOM20,
		ITEM_IMAGERANDOM21,
		ITEM_IMAGERANDOM22,
		ITEM_IMAGERANDOM23,
		ITEM_IMAGERANDOM24,
		ITEM_IMAGERANDOM25,
		ITEM_IMAGERANDOM26,
		ITEM_IMAGERANDOM27,
		ITEM_IMAGERANDOM28,
		ITEM_IMAGERANDOM29,
		BOXINFO_CLOSE_BUTTON,
	};
private:
static	const	float	fMOUSEPOINT_GAP;

public:
	CBoxItemInfo ();
	virtual	~CBoxItemInfo ();

public:
	void	CreateSubControl ();

public:
	void	ClearText ();
	int		AddTextNoSplit ( CString strText, D3DCOLOR dwColor );
	int		SetTextNoSplit ( CString strText, D3DCOLOR dwColor );
	void	SetText( CString strText, D3DCOLOR	dwColor );
	void	AddString ( int nIndex, const CString& strText, const D3DCOLOR& dwColor );
	int		AddText ( CString strText, D3DCOLOR dwColor );
	void	AddTextLongestLineSplit ( CString strText, D3DCOLOR dwColor );

public:
	void	SetUseOverColor ( bool bUseColor );
	void	SetOverColor ( const D3DCOLOR& dwColor );
	void	SetLineInterval ( const float fLineInterval );

public:
	int		GetCount ();

	void	RePosControl ( int x, int y );

public:
	void	SetBlockMouseTracking ( bool bBlock );

public:
	void	SetMousePointGap ( D3DXVECTOR2 vGap );

public:
	float	GetLongestLine ();

	void	SetTextAlign ( int nALIGN );

public:
	virtual	void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );

private:
	bool	m_bBLOCK_MOUSETRACKING;

private:
	CBasicTextBox*		m_pTextBox;
	CBasicLineBoxEx*	m_pLineBox;
	D3DXVECTOR2			m_vMousePointGap;

private:
	CUIControl*			m_pSelfDummy;
	CUIControl*			m_pSelfDummyGray;

private:
	CD3DFontPar*	m_pFont;
	CD3DFontPar*	m_pFont10;
public:
	//Item Image Render by NjD :: 07 / 08 / 2014
	void	ResetItemRender ();
	void	SetItemRender ( SNATIVEID sICONINDEX, const char* szTexture );
	CItemImage*			m_pItemImageRender; 
	
	//Name Render by NjD 08 / 15 / 2014
	CBasicTextBox*		m_pTextBoxName; 
	//Item Box Rendering
	CItemImage*	CreateItemImage ( const char* szControl, UIGUID ControlID );
	CItemImage*	m_pItemImage[ITEM::SBOX::ITEM_SIZE];
	CItemImage*	m_pItemImageRandom[30];

	void SetItemBoxRender ( SNATIVEID sICONINDEX, const char* szTexture, int nIndex );
	void ResetItemBoxRender ();
	void SetResiIcon();
	void HideResiIcon();

	int		AddTextNoSplitBig ( CString strText, D3DCOLOR dwColor );

	
	CUIControl*		m_pResiIcon[5];
	
	void SetItemBoxRandomRender ( SNATIVEID sICONINDEX, const char* szTexture, int nIndex );
	void ResetItemBoxRandomRender ();
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );
	
	CBasicButton*	CreateFlipButton ( char* szButton, char* szButtonFlip, char* szMouseOver, UIGUID ControlID );
	CBasicButton*	m_pCloseButton;

	void	CloseAlign ();

	bool		m_bCHECK_MOUSE_STATE;
	int			m_PosX;
	int			m_PosY;
	D3DXVECTOR2	m_vGap;

	void	CheckMouseState ();
};