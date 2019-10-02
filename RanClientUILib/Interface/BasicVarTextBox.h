//	기본 정보 표시
//
//	최초 작성자 : 성기엽
//	이후 수정자 : 
//	로그
//		[2003.11.27]
//			@ 작성
//

#pragma	once

#include "../EngineUIlib/GUInterface/UIGroup.h"
#include "../Interface/UIWindowEx.h"
#include "GLItem.h"

class	CBasicTextBox;
class	CBasicLineBoxEx;
class	CD3DFontPar;
struct	SNATIVEID;
class	GLItem;
class 	CItemImage;
class	CBasicVarTextBox : public CUIWindowEx//public CUIGroup
{
	enum
	{
		ITEM_IMAGE_RENDER
	};
private:
static	const	float	fMOUSEPOINT_GAP;

public:
	CBasicVarTextBox ();
	virtual	~CBasicVarTextBox ();

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

private:
	CD3DFontPar*	m_pFont;
	CD3DFontPar*	m_pFont10;
	CUIControl*			m_pWrap;
public:
	//Item Image Render by NjD :: 07 / 08 / 2014
	void	ResetItemRender (SITEMCUSTOM sCustom);
	void SetItemRender ( SNATIVEID sICONINDEX, const char* szTexture, SITEMCUSTOM sCustom );
	CItemImage*			m_pItemImageRender; 
	
	//Name Render by NjD 08 / 15 / 2014
	CBasicTextBox*		m_pTextBoxName; 
	CBasicTextBox*		m_pTextBoxResist; 
	//Item Box Rendering
	CItemImage*	CreateItemImage ( const char* szControl );
	CItemImage*	m_pItemImage[ITEM::SBOX::ITEM_SIZE];
	void	SetItemWrapRender();//add wrap ejsayaaa
	void	ResetItemWrapRender();//add wrap ejsayaaa

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
};