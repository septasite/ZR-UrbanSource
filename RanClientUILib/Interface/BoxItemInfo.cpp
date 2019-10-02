#include "StdAfx.h"

#include "./BoxItemInfo.h"
#include "../EngineUIlib/GUInterface/BasicTextBox.h"
#include "./BasicLineBoxEx.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "./UITextControl.h"
#include "../EngineUIlib/GUInterface/UIDebugSet.h"
#include "ItemImage.h"
#include "GLItemMan.h"
#include "GLItem.h"
#include "GLGaeaClient.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "InnerInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const	float	CBoxItemInfo::fMOUSEPOINT_GAP = 20.0f;

CBoxItemInfo::CBoxItemInfo () :
	m_pTextBox ( NULL ),
	m_pTextBoxName ( NULL ),
	m_pLineBox ( NULL ),
	m_pFont ( NULL ),
	m_pSelfDummy ( NULL ),
	m_pItemImageRender ( NULL ),
	m_vMousePointGap (fMOUSEPOINT_GAP,fMOUSEPOINT_GAP),
	m_bBLOCK_MOUSETRACKING ( false ),
	m_pCloseButton(NULL),
	m_pSelfDummyGray(NULL)

{
	memset ( m_pItemImage, 0, sizeof ( CUIControl* ) * ITEM::SBOX::ITEM_SIZE );	
	memset ( m_pItemImageRandom, 0, sizeof ( CUIControl* ) * 30 );	
	memset ( m_pResiIcon, 0, sizeof ( CUIControl* ) * 5 );
}

CBoxItemInfo::~CBoxItemInfo ()
{
}

CBasicButton* CBoxItemInfo::CreateFlipButton ( char* szButton, char* szButtonFlip, char* szMouseOver, UIGUID ControlID )
{
	CBasicButton* pButton = new CBasicButton;
	pButton->CreateSub ( this, szButton, UI_FLAG_DEFAULT, ControlID );
	pButton->CreateFlip ( szButtonFlip, CBasicButton::CLICK_FLIP );
	pButton->CreateMouseOver ( szMouseOver );
	RegisterControl ( pButton );
	return pButton;
}

CItemImage*	CBoxItemInfo::CreateItemImage ( const char* szControl, UIGUID ControlID )
{
	CItemImage* pItemImage = new CItemImage;
	pItemImage->CreateSub ( this, szControl, UI_FLAG_DEFAULT, ControlID );
	pItemImage->CreateSubControl ();
	pItemImage->SetUseRender ( TRUE );
	pItemImage->SetVisibleSingle ( FALSE );
	RegisterControl ( pItemImage );

	return pItemImage;
}

void CBoxItemInfo::CreateSubControl ()
{
	m_pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, _DEFAULT_FONT_SHADOW_FLAG );
	m_pFont10 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 12, _DEFAULT_FONT_SHADOW_FLAG );

	CUIControl* pSelfDummy = new CUIControl;
	pSelfDummy->CreateSub ( this, "BASIC_VAR_LINE_BOX_GRAY" );
	pSelfDummy->SetVisibleSingle ( FALSE );
	RegisterControl ( pSelfDummy );
	m_pSelfDummyGray = pSelfDummy;

	CBasicLineBoxEx* pLineBox = new CBasicLineBoxEx;
	pLineBox->CreateSub ( this, "BASIC_VAR_LINE_BOX", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pLineBox->CreateBaseBoxDialogueDarkGray ( "BASIC_VAR_LINE_BOX" );
	pLineBox->SetNoUpdate ( true );
	pLineBox->SetDiffuse ( D3DCOLOR_ARGB (50,0xFF,0xFF,0xFF) );
	RegisterControl ( pLineBox );
	m_pLineBox = pLineBox;

	CUIControl* pSelfDummy2 = new CUIControl;
	pSelfDummy2->CreateSub ( this, "BASIC_VAR_LINE_BOX" );
	pSelfDummy2->SetVisibleSingle ( FALSE );
	RegisterControl ( pSelfDummy2 );
	m_pSelfDummy = pSelfDummy2;

	CBasicTextBox* pTextBox = new CBasicTextBox;
	pTextBox->CreateSub ( this, "VAR_TEXT_BOX", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pTextBox->SetFont ( m_pFont );
	pTextBox->SetTextAlign ( TEXT_ALIGN_LEFT );
	pTextBox->SetNoUpdate ( true );
	RegisterControl ( pTextBox );
	m_pTextBox = pTextBox;

	//Name Render by NjD
	CBasicTextBox* pTextBoxName = new CBasicTextBox;
	pTextBoxName->CreateSub ( this, "VAR_TEXT_BOX", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pTextBoxName->SetFont ( m_pFont10 );
	pTextBoxName->SetTextAlign ( TEXT_ALIGN_LEFT );
	pTextBoxName->SetNoUpdate ( true );
	RegisterControl ( pTextBoxName );
	m_pTextBoxName = pTextBoxName;

	{

		for ( int i = 0; i < ITEM::SBOX::ITEM_SIZE; i++ )
		{
			CString strBox;
			strBox.Format ( "ITEM_BOX_IMAGE%d", i );
			m_pItemImage[i] = CreateItemImage ( strBox.GetString (), ITEM_IMAGE0 +i );
		}

		for ( int i = 0; i < 30; i++ )
		{
			CString strRandomBox;
			strRandomBox.Format ( "ITEM_BOXRANDOM_IMAGE%d", i );
			m_pItemImageRandom[i] = CreateItemImage ( strRandomBox.GetString (), ITEM_IMAGERANDOM0 + i );
		}
	}

	{

		for ( int i = 0; i < 5; i++ )
		{
			CString strResiIcons;
			strResiIcons.Format ( "RESI_IMAGE%d", i );
			m_pResiIcon[i] = CreateControl ( strResiIcons.GetString() );
		}
	}

	{
		CItemImage* pItemImage = new CItemImage;
		pItemImage->CreateSub ( this, "ITEM_IMAGE_RENDER" );
		pItemImage->CreateSubControl ();
		pItemImage->SetUseRender ( TRUE );
		pItemImage->SetVisibleSingle ( FALSE );
		RegisterControl ( pItemImage );
		m_pItemImageRender = pItemImage;
	}

	{
		m_pCloseButton = CreateFlipButton ( "BOXINFO_CLOSE_BUTTON", "BOXINFO_CLOSE_BUTTON_F", "BOXINFO_CLOSE_BUTTON_OVER", BOXINFO_CLOSE_BUTTON );
	}
}

void CBoxItemInfo::CloseAlign ()
{
	if ( m_pCloseButton )
	{
		const UIRECT& rcOriginPos = m_pCloseButton->GetLocalPos ();
		const float rcLineBoxPos = m_pLineBox->GetLocalPos().sizeX;

		UIRECT rcLocalNewPos = UIRECT ( rcLineBoxPos - 20, rcOriginPos.top , rcOriginPos.sizeX, rcOriginPos.sizeY );

		AlignSubControl ( rcOriginPos, rcLocalNewPos );
		m_pCloseButton->SetLocalPos ( rcLocalNewPos );	
	}
}

void CBoxItemInfo::SetTextAlign ( int nALIGN )
{
	m_pTextBox->SetTextAlign ( nALIGN );
}

void CBoxItemInfo::ClearText ()
{
	if ( m_pTextBox ) m_pTextBox->ClearText ();
	if ( m_pTextBoxName ) m_pTextBoxName->ClearText ();
}

int CBoxItemInfo::AddTextNoSplit ( CString strText, D3DCOLOR dwColor )
{
	if ( m_pTextBox ) return m_pTextBox->AddTextNoSplit ( strText, dwColor );

	return -1;
}

int CBoxItemInfo::AddTextNoSplitBig ( CString strText, D3DCOLOR dwColor )
{
	if ( m_pTextBoxName ) return m_pTextBoxName->AddTextNoSplitBig ( strText, dwColor );
								 m_pTextBoxName->SetFont ( m_pFont10 );
	return -1;
}

int	CBoxItemInfo::SetTextNoSplit ( CString strText, D3DCOLOR dwColor )
{
	if ( m_pTextBox ) return m_pTextBox->SetTextNoSplit ( strText, dwColor );

	return -1;
}

void CBoxItemInfo::SetText( CString strText, D3DCOLOR dwColor )
{
	if ( m_pTextBox ) m_pTextBox->SetText( strText, dwColor );
}

void CBoxItemInfo::AddString ( int nIndex, const CString& strText, const D3DCOLOR& dwColor )
{
	if ( m_pTextBox ) m_pTextBox->AddString ( nIndex, strText, dwColor );
}

int CBoxItemInfo::AddText ( CString strText, D3DCOLOR dwColor )
{
	if ( m_pTextBox ) return m_pTextBox->AddText ( strText, dwColor );

	return -1;
}

void CBoxItemInfo::SetUseOverColor ( bool bUseColor )
{
	m_pTextBox->SetUseOverColor ( (bUseColor)?TRUE:FALSE );
}

void CBoxItemInfo::SetOverColor ( const D3DCOLOR& dwColor )
{
	int nIndex = m_pTextBox->GetCount () - 1;
	m_pTextBox->SetOverColor ( nIndex, dwColor );
}

void CBoxItemInfo::RePosControl ( int x, int y )
{
	const float fTextBoxGapX_ = (float)m_pTextBox->GetLongestLine ();
	const float fTextBoxGapXName_ = (float)m_pTextBoxName->GetLongestLine ();

	if ( fTextBoxGapXName_ > fTextBoxGapX_ )
	{
		const UIRECT& rcTextBoxLocalPos = m_pTextBoxName->GetLocalPos ();
		const UIRECT& rcLocalPosDummy = m_pSelfDummy->GetLocalPos ();
		const UIRECT& rcOriginPos = GetLocalPos ();

		AlignSubControl ( rcOriginPos, rcLocalPosDummy );

		if ( m_pTextBoxName )
		{
			int nTotalLine = m_pTextBox->GetTotalLine ();
			const float fAllLine = m_pTextBox->CalcMaxHEIGHT ( 0, nTotalLine );
			const float fTextBoxGapX = (float)m_pTextBoxName->GetLongestLine () - rcTextBoxLocalPos.sizeX;
			const float fTextBoxGapY = fAllLine - rcTextBoxLocalPos.sizeY;
			
			UIRECT rcLocalNewPos = UIRECT ( rcOriginPos.left,rcOriginPos.top,
				rcOriginPos.sizeX + fTextBoxGapX, rcOriginPos.sizeY + fTextBoxGapY );

			AlignSubControl ( rcLocalPosDummy, rcLocalNewPos );

			SetGlobalPos ( rcLocalNewPos );		
		}
	}
	else
	{
		const UIRECT& rcTextBoxLocalPos = m_pTextBox->GetLocalPos ();
		const UIRECT& rcLocalPosDummy = m_pSelfDummy->GetLocalPos ();
		const UIRECT& rcOriginPos = GetLocalPos ();

		AlignSubControl ( rcOriginPos, rcLocalPosDummy );

		if ( m_pTextBox )
		{
			int nTotalLine = m_pTextBox->GetTotalLine ();
			const float fAllLine = m_pTextBox->CalcMaxHEIGHT ( 0, nTotalLine );
			const float fTextBoxGapX = (float)m_pTextBox->GetLongestLine () - rcTextBoxLocalPos.sizeX;
			const float fTextBoxGapY = fAllLine - rcTextBoxLocalPos.sizeY;
			
			UIRECT rcLocalNewPos = UIRECT ( rcOriginPos.left,rcOriginPos.top,
				rcOriginPos.sizeX + fTextBoxGapX, rcOriginPos.sizeY + fTextBoxGapY );

			AlignSubControl ( rcLocalPosDummy, rcLocalNewPos );

			SetGlobalPos ( rcLocalNewPos );		
		}
	}
}

void CBoxItemInfo::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	SetUseOverColor ( false );
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	CloseAlign ();
	if ( m_pSelfDummyGray )
	{
		const UIRECT& rcOriginPos = m_pSelfDummyGray->GetLocalPos ();
		const UIRECT& rcLineBoxPos = m_pLineBox->GetLocalPos();

		UIRECT rcLocalNewPos = UIRECT ( rcLineBoxPos.left + 2, rcLineBoxPos.top + 2 , rcLineBoxPos.sizeX + 2, rcLineBoxPos.sizeY + 2 );

		AlignSubControl ( rcOriginPos, rcLocalNewPos );
			m_pSelfDummyGray->SetLocalPos ( rcLocalNewPos );	
	}

	m_bCHECK_MOUSE_STATE = false;

	m_PosX = x;
	m_PosY = y;

	if ( IsExclusiveSelfControl() )
	{
		SetLocalPos ( D3DXVECTOR2 ( x - m_vGap.x, y - m_vGap.y ) );
	}

	if ( !m_bBLOCK_MOUSETRACKING ) RePosControl ( x, y ); 

	m_pLineBox->SetDiffuse (  D3DCOLOR_ARGB(190,0xFF,0xFF,0xFF) );
}

void CBoxItemInfo::CheckMouseState()
{
	const DWORD dwMsg = GetMessageEx ();
	if ( CHECK_MOUSE_IN ( dwMsg ) )
	{	
		if ( dwMsg & UIMSG_LB_DOWN )
		{
			SetExclusiveControl();	

			UIRECT rcPos = GetGlobalPos ();
			m_vGap.x = m_PosX - rcPos.left;
			m_vGap.y = m_PosY - rcPos.top;
		}
		else if ( CHECK_LB_UP_LIKE ( dwMsg ) )
		{
			ResetExclusiveControl();			
		}
	}
	else if ( CHECK_LB_UP_LIKE ( dwMsg ) )		
	{								
		ResetExclusiveControl();				
	}
}

void CBoxItemInfo::SetMousePointGap ( D3DXVECTOR2 vGap )
{
	m_vMousePointGap = vGap;
}

float CBoxItemInfo::GetLongestLine ()
{
	if ( m_pTextBox )
	{
		return (float)m_pTextBox->GetLongestLine ();
	}
	return 0.0f;
}

void CBoxItemInfo::AddTextLongestLineSplit ( CString strText, D3DCOLOR dwColor )
{
	float fLongestLine = GetLongestLine ();
	float fLongLine = float(m_pTextBoxName->GetLongestLine());

	if ( fLongLine > fLongestLine )
	{
		NS_UITEXTCONTROL::MULTILINETEXT& MLTextSet = NS_UITEXTCONTROL::GetMLTextWithoutCRLF ( strText, fLongLine, m_pFont );

		for ( int i = 0; i < (int)MLTextSet.size(); ++i )
		{
			CString strTemp = MLTextSet[i].strLine;
			if ( strTemp.GetLength() )
			{
				AddTextNoSplit ( strTemp, NS_UITEXTCOLOR::DEFAULT );		
			}
		}	
	}
	else
	{
		NS_UITEXTCONTROL::MULTILINETEXT& MLTextSet = NS_UITEXTCONTROL::GetMLTextWithoutCRLF ( strText, fLongestLine, m_pFont );

		for ( int i = 0; i < (int)MLTextSet.size(); ++i )
		{
			CString strTemp = MLTextSet[i].strLine;
			if ( strTemp.GetLength() )
			{
				AddTextNoSplit ( strTemp, NS_UITEXTCOLOR::DEFAULT );		
			}
		}
	}
}

int	CBoxItemInfo::GetCount ()
{
	return m_pTextBox->GetCount ();
}

void CBoxItemInfo::SetLineInterval ( const float fLineInterval )
{
	m_pTextBox->SetLineInterval ( fLineInterval );
}

void CBoxItemInfo::SetBlockMouseTracking ( bool bBlock )
{
	m_bBLOCK_MOUSETRACKING = bBlock;
}
//Item Image Render by NjD :: 07 / 08 / 2014
void CBoxItemInfo::SetItemRender ( SNATIVEID sICONINDEX, const char* szTexture )
{
	SITEM* pItem = GLItemMan::GetInstance().GetItem ( sICONINDEX );
	if ( !pItem ) m_pItemImageRender->SetVisibleSingle ( FALSE );

	if ( m_pItemImageRender )
	{
		m_pItemImageRender->SetItem( sICONINDEX, szTexture );
		m_pItemImageRender->SetVisibleSingle ( TRUE );
	}
}
//Item Image Render by NjD :: 07 / 08 / 2014
void CBoxItemInfo::ResetItemRender ()
{
	if ( m_pItemImageRender )
	{
		m_pItemImageRender->ResetItem();
		m_pItemImageRender->SetVisibleSingle ( FALSE );
	}
}

void CBoxItemInfo::SetItemBoxRender ( SNATIVEID sICONINDEX, const char* szTexture, int nIndex )
{		
	if ( m_pItemImage[nIndex] )
	{
		m_pItemImage[nIndex]->SetItem( sICONINDEX, szTexture );
		m_pItemImage[nIndex]->SetVisibleSingle ( TRUE );
	}
}
//Item Image Render by NjD :: 07 / 08 / 2014
void CBoxItemInfo::ResetItemBoxRender ()
{
	for ( int i = 0; i < ITEM::SBOX::ITEM_SIZE; i++ )
	{
		if ( m_pItemImage[i] )
		{
			m_pItemImage[i]->ResetItem();
			m_pItemImage[i]->SetVisibleSingle ( FALSE );
		}
	}
}

void CBoxItemInfo::SetResiIcon()
{
	for ( int i = 0; i < 5; i++ )
	{
		m_pResiIcon[i]->SetVisibleSingle ( TRUE );
	}
}

void CBoxItemInfo::HideResiIcon()
{
	for ( int i = 0; i < 5; i++ )
	{
		m_pResiIcon[i]->SetVisibleSingle ( FALSE );
	}
}

void CBoxItemInfo::SetItemBoxRandomRender ( SNATIVEID sICONINDEX, const char* szTexture, int nIndex )
{		
	if ( m_pItemImageRandom[nIndex] )
	{
		m_pItemImageRandom[nIndex]->SetItem( sICONINDEX, szTexture );
		m_pItemImageRandom[nIndex]->SetVisibleSingle ( TRUE );
	}
}

void CBoxItemInfo::ResetItemBoxRandomRender ()
{
	for ( int i = 0; i < 30; i++ )
	{
		if ( m_pItemImageRandom[i] )
		{
			m_pItemImageRandom[i]->ResetItem();
			m_pItemImageRandom[i]->SetVisibleSingle ( FALSE );
		}
	}
}
void CBoxItemInfo::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{

	CUIWindowEx::TranslateUIMessage ( ControlID, dwMsg );

	if ( !m_bCHECK_MOUSE_STATE )
	{
		CheckMouseState ();
		m_bCHECK_MOUSE_STATE = true;
	}

	switch ( ControlID )
	{
	case ET_CONTROL_TITLE:
	case ET_CONTROL_TITLE_F:
		{
			if ( (dwMsg & UIMSG_LB_DUP) && CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SetDefaultPosInterface( BOXINFO_DISPLAY );
			}
		}
		break;
	case ITEM_IMAGE0:
	case ITEM_IMAGE1:
	case ITEM_IMAGE2:
	case ITEM_IMAGE3:
	case ITEM_IMAGE4:
	case ITEM_IMAGE5:
	case ITEM_IMAGE6:
	case ITEM_IMAGE7:
	case ITEM_IMAGE8:
	case ITEM_IMAGE9:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nSelect = ControlID - ITEM_IMAGE0;
				BOOL bMarketOpen = CInnerInterface::GetInstance().IsDialogueWindowOpen ();
				SITEMCUSTOM sCUSTOM = CInnerInterface::GetInstance().sBOXINFOCUSTOM[nSelect];
				CInnerInterface::GetInstance().SHOW_ITEM_INFO ( sCUSTOM, bMarketOpen, FALSE, FALSE, USHRT_MAX, USHRT_MAX );
			}
		}
		break;
	case ITEM_IMAGERANDOM0:
	case ITEM_IMAGERANDOM1:
	case ITEM_IMAGERANDOM2:
	case ITEM_IMAGERANDOM3:
	case ITEM_IMAGERANDOM4:
	case ITEM_IMAGERANDOM5:
	case ITEM_IMAGERANDOM6:
	case ITEM_IMAGERANDOM7:
	case ITEM_IMAGERANDOM8:
	case ITEM_IMAGERANDOM9:
	case ITEM_IMAGERANDOM10:
	case ITEM_IMAGERANDOM11:
	case ITEM_IMAGERANDOM12:
	case ITEM_IMAGERANDOM13:
	case ITEM_IMAGERANDOM14:
	case ITEM_IMAGERANDOM15:
	case ITEM_IMAGERANDOM16:
	case ITEM_IMAGERANDOM17:
	case ITEM_IMAGERANDOM18:
	case ITEM_IMAGERANDOM19:
	case ITEM_IMAGERANDOM20:
	case ITEM_IMAGERANDOM21:
	case ITEM_IMAGERANDOM22:
	case ITEM_IMAGERANDOM23:
	case ITEM_IMAGERANDOM24:
	case ITEM_IMAGERANDOM25:
	case ITEM_IMAGERANDOM26:
	case ITEM_IMAGERANDOM27:
	case ITEM_IMAGERANDOM28:
	case ITEM_IMAGERANDOM29:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nSelect = ControlID - ITEM_IMAGERANDOM0;
				BOOL bMarketOpen = CInnerInterface::GetInstance().IsDialogueWindowOpen ();
				SITEMCUSTOM sCUSTOM = CInnerInterface::GetInstance().sRANDOMBOXINFOCUSTOM[nSelect];
				CInnerInterface::GetInstance().SHOW_ITEM_INFO ( sCUSTOM, bMarketOpen, FALSE, FALSE, USHRT_MAX, USHRT_MAX );
			}
		}
		break;
	case BOXINFO_CLOSE_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( dwMsg & UIMSG_LB_UP )
				{
					CInnerInterface::GetInstance().RESET_INFO_BOXINFO ();
					CInnerInterface::GetInstance().RESETRESIICON_BOXINFO ();
					CInnerInterface::GetInstance().RESETITEMBOX_RENDER_BOXINFO ();
					CInnerInterface::GetInstance().RESETITEM_RENDER_BOXINFO ();
					CInnerInterface::GetInstance().HideGroup ( BOXINFO_DISPLAY );
				}
			}
		}
		break;
	}
}

