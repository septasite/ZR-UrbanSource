
#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"
#include "../Interface/UIWindowEx.h"
#include "GLItem.h"

class	CBasicTextBox;
class	CBasicLineBoxEx;
class	CBasicButton;
class	CD3DFontPar;

struct	SNATIVEID;
class	GLItem;
class 	CItemImage;

const DWORD UIMSG_UIVARTEXT_BUTTON_CLOSE_CLICK = UIMSG_USER1;
const DWORD UIMSG_UIVARTEXT_BUTTON_CLOSE_MOUSEIN = UIMSG_USER2;

class	CBasicVarTextBoxEx : public CUIWindowEx
{
private:
static	const	float	fMOUSEPOINT_GAP;

protected:
	enum
	{
		BUTTON_CLOSE = NO_ID + 1,
		ITEM_IMAGE_RENDER
	};

public:
	CBasicVarTextBoxEx ();
	virtual	~CBasicVarTextBoxEx ();

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

	void	ShowCloseButton( bool bSHOW );

public:
	virtual	void Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl );
	virtual	void TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg );

private:
	bool	m_bBLOCK_MOUSETRACKING;

private:
	CBasicTextBox*		m_pTextBox;
	CBasicLineBoxEx*	m_pLineBox;
	CBasicButton*		m_pCloseButton;
	D3DXVECTOR2			m_vMousePointGap;

private:
	CUIControl*			m_pSelfDummy;

private:
	CD3DFontPar*	m_pFont;
	CD3DFontPar*	m_pFont10;
public:

	void	SetItemWrapRender();//add wrap ejsayaaa
	void	ResetItemWrapRender();//add wrap ejsayaaa

	//Item Image Render by NjD :: 07 / 08 / 2014
	void	ResetItemRender ( SITEMCUSTOM sCustom );
	void SetItemRender ( SNATIVEID sICONINDEX, const char* szTexture, SITEMCUSTOM sCustom );
	CItemImage*			m_pItemImageRender; 
	
	//Name Render by NjD 08 / 15 / 2014
	CBasicTextBox*		m_pTextBoxName; 
	CBasicTextBox*		m_pTextBoxResist; 
	//Item Box Rendering
	CItemImage*	CreateItemImage ( const char* szControl );
	CItemImage*	m_pItemImage[ITEM::SBOX::ITEM_SIZE];

	void SetItemBoxRender ( SNATIVEID sICONINDEX, const char* szTexture, int nIndex );
	void ResetItemBoxRender ();
	void SetResiIcon();
	void HideResiIcon();

	int		AddTextNoSplitBig ( CString strText, D3DCOLOR dwColor );
	int		AddTextNoSplitBigResist ( CString strText, D3DCOLOR dwColor );

	
	CUIControl*		m_pElecIcon;
	CUIControl*		m_pFireIcon;
	CUIControl*		m_pIceIcon;
	CUIControl*		m_pPoiIcon;
	CUIControl*		m_pSpiIcon;
	CUIControl* m_pWrap;
};