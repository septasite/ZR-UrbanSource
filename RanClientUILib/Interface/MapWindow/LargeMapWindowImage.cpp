#include "StdAfx.h"
#include "LargeMapWindow.h"
#include "LargeMapWindowImage.h"
#include "LargeMapWindowRadio.h"
#include "LargeMapWindowSlotRender.h"

#include "../RanClientUILib/Interface/UITextControl.h"
#include "../RanClientUILib/Interface/InnerInterface.h"
#include "../RanClientUILib/Interface/GameTextControl.h"
#include "../RanClientUILib/Interface/BasicScrollBarEx.h"

#include "../RanClientLib/DxGlobalStage.h"
#include "../RanClientLib/G-Logic/GLGaeaClient.h"
#include "../RanClientLib/G-Logic/GLPartyClient.h"
#include "../RanClientLib/G-Logic/GLMapAxisInfo.h"
#include "../RanClientLib/G-Logic/GLContrlServerMsg.h"

#include "DxViewPort.h"

#include "../EngineLib/DxCommon/d3dfont.h"
#include "../EngineLib/DxCommon/DxFontMan.h"

#include "../EngineUILib/GUInterface/BasicButton.h"
#include "../EngineUILib/GUInterface/BasicScrollThumbFrame.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CLargeMapWindowImage::CLargeMapWindowImage ()
	: m_pMousePosText( NULL )
	, m_pMousePosBack( NULL )
	, m_pScrollBarH( NULL )
	, m_pScrollBarV( NULL )
	, m_pMap( NULL )
	, m_pPlayerMark( NULL )
	, m_pTargetMark( NULL )
	, m_iTargetX( INT_MIN )
	, m_iTargetY( INT_MIN )
	, m_NEWID(1000)
{
	SecureZeroMemory( m_pMark, sizeof(m_pMark) );
	Initialize();
}

CLargeMapWindowImage::~CLargeMapWindowImage ()
{
}

void CLargeMapWindowImage::Initialize()
{
	m_fPercentH_BACK = 2.0f;
	m_fPercentV_BACK = 2.0f;
	m_nWORLD_START_X = 1;
	m_nWORLD_START_Y = 1;
	m_nWORLD_SIZE_X = 1;
	m_nWORLD_SIZE_Y = 1;
	m_nMAP_TEXSIZE_X = 1;
	m_nMAP_TEXSIZE_Y = 1;
	m_nVIEW_START_X = 1;
	m_nVIEW_START_Y = 1;
	m_nVIEW_SIZE_X = 1;
	m_nVIEW_SIZE_Y = 1;
	m_bFirstGap = FALSE;
	m_bAUTO_MOVE = true;

	ConvIntDataFloatData();
}

void CLargeMapWindowImage::ConvIntDataFloatData()
{
	m_vWORLD_START = D3DXVECTOR2( (float)m_nWORLD_START_X, (float)m_nWORLD_START_Y );
	m_vWORLD_SIZE = D3DXVECTOR2( (float)m_nWORLD_SIZE_X, (float)m_nWORLD_SIZE_Y );
	m_vMAP_TEXSIZE = D3DXVECTOR2( (float)m_nMAP_TEXSIZE_X, (float)m_nMAP_TEXSIZE_Y );
}

void CLargeMapWindowImage::CreateSubControl ()
{
	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, D3DFONT_SHADOW | D3DFONT_ASCII );

	{	
		CBasicScrollBarEx* pScrollBar = new CBasicScrollBarEx;
		pScrollBar->CreateSub ( this, "BASIC_SCROLLBAR_H", UI_FLAG_BOTTOM | UI_FLAG_XSIZE, LARGEMAP_SCROLLBAR_H );
		pScrollBar->CreateBaseScrollBar ( "LARGEMAP_SCROLLBAR_H", false );
		RegisterControl ( pScrollBar );
		m_pScrollBarH = pScrollBar;
		m_pScrollBarH->SetVisibleSingle ( FALSE );
	}

	{
		CBasicScrollBarEx* pScrollBar = new CBasicScrollBarEx;
		pScrollBar->CreateSub ( this, "BASIC_SCROLLBAR", UI_FLAG_RIGHT | UI_FLAG_YSIZE, LARGEMAP_SCROLLBAR_V );
		pScrollBar->CreateBaseScrollBar ( "LARGEMAP_SCROLLBAR_V" );
		RegisterControl ( pScrollBar );
		m_pScrollBarV = pScrollBar;
		m_pScrollBarV->SetVisibleSingle ( FALSE );
	}

	CUIControl*	pMapImage = new CUIControl;
	pMapImage->CreateSub ( this, "LARGEMAP_IMAGE", UI_FLAG_XSIZE | UI_FLAG_YSIZE, LARGEMAP_IMAGE );
	RegisterControl ( pMapImage );
	m_pMap = pMapImage;

	CUIControl* pPlayerMark = new CUIControl;
	pPlayerMark->CreateSub ( this, "LARGEMAP_MARK", UI_FLAG_DEFAULT, PLAYER_MARK );		
	RegisterControl ( pPlayerMark );
	m_pPlayerMark = pPlayerMark;

	CUIControl* pMousePosBack = new CUIControl;
	pMousePosBack->CreateSub ( this, "LARGEMAP_MOUSEPOS_BACK", UI_FLAG_BOTTOM | UI_FLAG_RIGHT );
	RegisterControl ( pMousePosBack );		
	m_pMousePosBack = pMousePosBack;

	CBasicTextBox*	pTextBox = new CBasicTextBox;
	pTextBox->CreateSub ( this, "LARGEMAP_MOUSEPOS_TEXT", UI_FLAG_BOTTOM | UI_FLAG_RIGHT );
	pTextBox->SetFont ( pFont );
	pTextBox->SetTextAlign ( TEXT_ALIGN_CENTER_X | TEXT_ALIGN_CENTER_Y );
	RegisterControl ( pTextBox );
	m_pMousePosText = pTextBox;

	CUIControl* pDirection = new CUIControl;
	pDirection->CreateSub ( this, "LARGEMAP_DIRECTION", UI_FLAG_BOTTOM, LARGEMAP_DIRECTION );		
	RegisterControl ( pDirection );

	CString strMark[MAXPARTY] =
	{
		"TEST_MARK0", 
		"TEST_MARK1", 
		"TEST_MARK2", 
		"TEST_MARK3",
		"TEST_MARK4", 
		"TEST_MARK5", 
		"TEST_MARK6", 
		"TEST_MARK7"
	};

	for ( int i = 0; i < MAXPARTY; ++i )
	{
		CUIControl* pMark = new CUIControl;
		pMark->CreateSub( this, strMark[i].GetString() );
		pMark->SetVisibleSingle( FALSE );
		RegisterControl( pMark );
		m_pMark[i] = pMark;
	}

	m_pTargetMark = new CUIControl;
	m_pTargetMark->CreateSub( this, "TARGET_MARK" );
	m_pTargetMark->SetVisibleSingle( FALSE );
	RegisterControl( m_pTargetMark );
}

HRESULT CLargeMapWindowImage::InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	GASSERT( pd3dDevice );
	m_pd3dDevice = pd3dDevice;

	HRESULT hr = S_OK;
	hr = CUIWindowEx::InitDeviceObjects ( pd3dDevice );
	if ( FAILED ( hr ) ) return hr;

	return S_OK;
}

//void CLargeMapWindowImage::SetDefaultPosition()
//{
//	const UIRECT& rcGlobalPos = GetGlobalPos ();
//	UIRECT rcTemp;
//
//	WORD wAlignFlag = GetAlignFlag ();			
//	SetAlignFlag ( UI_FLAG_XSIZE | UI_FLAG_YSIZE );
//	{
//		AlignSubControl( rcGlobalPos, rcTemp );
//
//		long lResolution = CUIMan::GetResolution ();
//		rcTemp.left = HIWORD(lResolution) - rcTemp.sizeX;
//
//		SetGlobalPos( rcTemp );
//	}
//	SetAlignFlag( wAlignFlag );
//}

void CLargeMapWindowImage::SetMapAxisInfo ( GLMapAxisInfo& sInfo, const CString& strMapName )
{
	Initialize();

	m_pMap->UnLoadTexture ();
	m_pMap->SetTextureName ( NULL );
	m_pMap->SetUseRender ( FALSE );

	//SetDefaultPosition();

	const D3DXVECTOR4 vMapTex = sInfo.GetMiniMapTexPos();	 
	const UIRECT& rcGlobalPos = m_pMap->GetGlobalPos ();

	{	
		const D3DXVECTOR2 vMinimapTexSize = sInfo.GetMiniMapTexSize();
		m_nMAP_TEXSIZE_X = static_cast<int>(vMinimapTexSize.x);
		m_nMAP_TEXSIZE_Y = static_cast<int>(vMinimapTexSize.y);
	}

	{	
		CBasicScrollThumbFrame* pThumbFrame = m_pScrollBarH->GetThumbFrame ();
		pThumbFrame->SetState ( m_nMAP_TEXSIZE_X, static_cast<int>(rcGlobalPos.sizeX) );
		pThumbFrame->SetPercent ( 0.0f );
	}

	{
		CBasicScrollThumbFrame* pThumbFrame = m_pScrollBarV->GetThumbFrame ();
		pThumbFrame->SetState ( m_nMAP_TEXSIZE_Y, static_cast<int>(rcGlobalPos.sizeY) );
		pThumbFrame->SetPercent ( 0.0f );
	}

	{
		m_nWORLD_START_X = sInfo.GetMapStartX ();
		m_nWORLD_START_Y = sInfo.GetMapStartY ();
		m_nWORLD_SIZE_X = sInfo.GetMapSizeX ();
		m_nWORLD_SIZE_Y = sInfo.GetMapSizeY ();
	}

	{
		m_nMAP_TEXSIZE_X = (m_nMAP_TEXSIZE_X) ? m_nMAP_TEXSIZE_X : 1;
		m_nMAP_TEXSIZE_Y = (m_nMAP_TEXSIZE_Y) ? m_nMAP_TEXSIZE_Y : 1;

		m_nWORLD_SIZE_X = (m_nWORLD_SIZE_X) ? m_nWORLD_SIZE_X : 1;
		m_nWORLD_SIZE_Y = (m_nWORLD_SIZE_Y) ? m_nWORLD_SIZE_Y : 1;
	}

	m_vRenderSize.x = rcGlobalPos.sizeX / m_nMAP_TEXSIZE_X;
	m_vRenderSize.y = rcGlobalPos.sizeY / m_nMAP_TEXSIZE_Y;

	m_vRenderSize.x *= 10000;
	m_vRenderSize.x = floor(m_vRenderSize.x);
	m_vRenderSize.x *= 0.0001f;

	m_vRenderSize.y *= 10000;
	m_vRenderSize.y = floor(m_vRenderSize.y);
	m_vRenderSize.y *= 0.0001f;

	UIRECT rcTexture( 0.0f, 0.0f, m_vRenderSize.x, m_vRenderSize.y );
	m_pMap->SetTextureName ( sInfo.GetMinMapTex() );
	m_pMap->SetTexturePos ( rcTexture );

	m_pMap->LoadTexture ( m_pd3dDevice );
	m_pMap->SetUseRender ( TRUE );

	m_vScrollGap.x = m_nMAP_TEXSIZE_X - rcGlobalPos.sizeX;
	m_vScrollGap.y = m_nMAP_TEXSIZE_Y - rcGlobalPos.sizeY;
	
	m_nVIEW_SIZE_X = static_cast<int>(rcGlobalPos.sizeX);
	m_nVIEW_SIZE_Y = static_cast<int>(rcGlobalPos.sizeY);

	ConvIntDataFloatData();
}

void CLargeMapWindowImage::Update ( int x ,int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	m_PosX = x;
	m_PosY = y;

	nScroll = 0;
	CUIWindowEx::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	if ( bFirstControl )
	{
		if ( m_pMap->IsExclusiveSelfControl() ) 
		{	
			D3DXVECTOR2 vMOVE ( m_vMOUSE_BACK.x - x, m_vMOUSE_BACK.y - y );

			if ( 0.0f != vMOVE.x )
			{	
				const float fMovePercent = vMOVE.x / m_vScrollGap.x;
				CBasicScrollThumbFrame* pThumbFrame = m_pScrollBarH->GetThumbFrame ();
				const float& fPercent = pThumbFrame->GetPercent ();
				float fNewPercent = fPercent + fMovePercent;
				fNewPercent = max ( 0.0f, fNewPercent );
				fNewPercent = min ( 1.0f, fNewPercent );
				pThumbFrame->SetPercent ( fNewPercent );
			}

			if ( 0.0f != vMOVE.y )
			{
				const float fMovePercent = vMOVE.y / m_vScrollGap.y;
				CBasicScrollThumbFrame* pThumbFrame = m_pScrollBarV->GetThumbFrame ();
				const float& fPercent = pThumbFrame->GetPercent ();
				float fNewPercent = fPercent + fMovePercent;
				fNewPercent = max ( 0.0f, fNewPercent );
				fNewPercent = min ( 1.0f, fNewPercent );
				pThumbFrame->SetPercent ( fNewPercent );
			}

			SetAutoMove ( false );

			m_vMOUSE_BACK.x = (float)x;
			m_vMOUSE_BACK.y = (float)y;
		}

		{	
			CBasicScrollThumbFrame* pThumbFrame = m_pScrollBarV->GetThumbFrame ();		
			const float fPercentV = pThumbFrame->GetPercent ();		
			if ( fPercentV != m_fPercentV_BACK )
			{
				const float fMOVE = m_vScrollGap.y * fPercentV;
				m_vRenderPos.y = fMOVE / m_nMAP_TEXSIZE_Y;

				m_vRenderPos.y *= 10000.0f;
				m_vRenderPos.y = floor(m_vRenderPos.y);
				m_vRenderPos.y *= 0.0001f;

				UIRECT rcTexture( m_vRenderPos.x, m_vRenderPos.y, m_vRenderSize.x, m_vRenderSize.y );
				m_pMap->SetTexturePos ( rcTexture );				

				m_fPercentV_BACK = fPercentV;

				m_nVIEW_START_Y = static_cast<int>(fMOVE);

				if ( m_nVIEW_START_Y < 0 ) m_nVIEW_START_Y = 0;
				if ( m_nVIEW_START_Y + m_nVIEW_SIZE_Y > m_nMAP_TEXSIZE_Y ) m_nVIEW_START_Y = m_nMAP_TEXSIZE_Y - m_nVIEW_SIZE_Y;
			}
		}

		{	
			CBasicScrollThumbFrame* pThumbFrame = m_pScrollBarH->GetThumbFrame ();
			const float fPercentH = pThumbFrame->GetPercent ();
			if ( fPercentH != m_fPercentH_BACK )
			{
				const float fMOVE = m_vScrollGap.x * fPercentH;
				m_vRenderPos.x = fMOVE / m_nMAP_TEXSIZE_X;

				m_vRenderPos.x *= 10000.0f;
				m_vRenderPos.x = floor(m_vRenderPos.x);
				m_vRenderPos.x *= 0.0001f;

				UIRECT rcTexture( m_vRenderPos.x, m_vRenderPos.y, m_vRenderSize.x, m_vRenderSize.y );
				m_pMap->SetTexturePos ( rcTexture );

				m_fPercentH_BACK = fPercentH;

				m_nVIEW_START_X = static_cast<int>(fMOVE);
				if ( m_nVIEW_START_X < 0 ) m_nVIEW_START_X = 0;
				if ( m_nVIEW_START_X + m_nVIEW_SIZE_X > m_nMAP_TEXSIZE_X ) m_nVIEW_START_X = m_nMAP_TEXSIZE_X - m_nVIEW_SIZE_X;
			}
		}

		{
			const D3DXVECTOR3 &vPlayerPos = GLGaeaClient::GetInstance().GetCharacterPos ();		

			m_pPlayerMark->SetVisibleSingle( FALSE );
			UPDATE_CHAR_POS( m_pPlayerMark, vPlayerPos );

			D3DXVECTOR3 vLookatPt = DxViewPort::GetInstance().GetLookatPt();
			D3DXVECTOR3 vFromPt = DxViewPort::GetInstance().GetFromPt();
			D3DXVECTOR3 vCameraDir = vLookatPt - vFromPt;

			UPDATE_CHAR_ROTATE ( vCameraDir );

			UPDATE_PARTY ();
			UPDATE_MOUSE_POS ( x, y );
		
			if ( !m_CrowList.empty())
			{
				CROW_LIST_ITER iter = m_CrowList.begin ();
				CROW_LIST_ITER iter_end = m_CrowList.end ();
				for( ; iter != iter_end; ++iter )
				{
					if ( !m_NEWID ) break;

					D3DXVECTOR3 vPos = iter->first;
					CLargeMapWindowSlotRender* pSlot = iter->second;
					pSlot->SetVisibleSingle(FALSE);

					if ( pSlot->GetType()>TYPE_MOB || pSlot->GetType()< TYPE_GATE) continue;

					if ( pSlot->GetType() < TYPE_MOB && !CInnerInterface::GetInstance().GetLargeMapWindow()->m_bSUBSETTING[pSlot->GetType()]) continue;

					bool bHide = false;
					for( int i = 0; i < MAXCROW; i++ )
					{
						SNATIVEID sID = CInnerInterface::GetInstance().GetLargeMapWindow()->m_sNativeID[i];
						if ( sID == NATIVEID_NULL()) continue;

						BOOL bOK = CInnerInterface::GetInstance().GetLargeMapWindow()->m_bMOB[i];
						if ( pSlot->GetID() == sID && !bOK ) bHide = true;
					}

					if ( bHide ) continue;

					CInnerInterface::GetInstance().GetLargeMapWindow()->m_bSUBSETTING[2] ? pSlot->SetDispName(true) : pSlot->SetDispName(false);

					UPDATE_CROW_POS( pSlot, vPos );
				}
			}
		}
	}

	{
		CBasicScrollThumbFrame* pThumbFrame = m_pScrollBarH->GetThumbFrame ();
		const float& fPercent = pThumbFrame->GetPercent ();
		pThumbFrame->SetPercent ( fPercent );
	}

	{
		CBasicScrollThumbFrame* pThumbFrame = m_pScrollBarV->GetThumbFrame ();
		const float& fPercent = pThumbFrame->GetPercent ();
		pThumbFrame->SetPercent ( fPercent );
	}

	if ( m_bAUTO_MOVE )
	{
		const D3DXVECTOR3 &vPlayerPos = GLGaeaClient::GetInstance().GetCharacterPos ();

		int nMAP_X(0), nMAP_Y(0);
		CONVERT_WORLD2MAP ( vPlayerPos, nMAP_X, nMAP_Y );
		DoCHARPOS_OnCENTER_InVIEW ( nMAP_X, nMAP_Y );
	}

	UPDATE_TARGET_POS( m_iTargetX, m_iTargetY );
}

void CLargeMapWindowImage::TranslateUIMessage ( UIGUID cID, DWORD dwMsg )
{
	CUIWindowEx::TranslateUIMessage ( cID, dwMsg );

	switch ( cID )
	{
	case LARGEMAP_IMAGE:	TranslateMeg( cID, dwMsg, m_pMap );				break;
	}
}

void CLargeMapWindowImage::TranslateMeg( UIGUID cID, DWORD dwMsg, CUIControl * pUIControl )
{
	GASSERT( pUIControl );

	if ( CHECK_MOUSE_IN ( dwMsg ) )					
	{
		if ( CHECK_RB_DOWN_LIKE ( dwMsg ) || CHECK_MB_DOWN_LIKE ( dwMsg ) )
		{
			pUIControl->SetExclusiveControl();		
			if ( !m_bFirstGap )						
			{
				UIRECT rcPos = pUIControl->GetGlobalPos ();
				m_vGap.x = m_PosX - rcPos.left;
				m_vGap.y = m_PosY - rcPos.top;

				if( cID == LARGEMAP_IMAGE )
				{
					m_vMOUSE_BACK.x = (float)m_PosX;
					m_vMOUSE_BACK.y = (float)m_PosY;
				}

				m_bFirstGap = TRUE;
			}
		}
		else if ( CHECK_RB_UP_LIKE ( dwMsg ) || CHECK_MB_UP_LIKE ( dwMsg ) )
		{
			pUIControl->ResetExclusiveControl();
			m_bFirstGap = FALSE;					
		}

		if( CHECK_LB_UP_LIKE( dwMsg ) )				
			OnLButtonUp();
	}
	else if ( CHECK_RB_UP_LIKE ( dwMsg ) || CHECK_MB_UP_LIKE ( dwMsg ) )
	{												
		pUIControl->ResetExclusiveControl();		
		m_bFirstGap = FALSE;						
	}
}

void CLargeMapWindowImage::TranslateMegThumb( UIGUID cID, DWORD dwMsg, CUIControl * pUIControl )
{
	GASSERT( pUIControl );

	if ( CHECK_MOUSE_IN ( dwMsg ) )	
	{
		if ( CHECK_LB_DOWN_LIKE ( dwMsg ) )			
		{
			if( CHECK_MOUSE_IN( m_pMap->GetMessageEx() ) )
				return;

			pUIControl->SetExclusiveControl();		
			if ( !m_bFirstGap )						
			{
				UIRECT rcPos = pUIControl->GetGlobalPos ();
				m_vGap.x = m_PosX - rcPos.left;
				m_vGap.y = m_PosY - rcPos.top;

				m_bFirstGap = TRUE;
			}
		}
		else if ( CHECK_LB_UP_LIKE ( dwMsg ) )		
		{
			pUIControl->ResetExclusiveControl();	
			m_bFirstGap = FALSE;					
		}
	}
	else if ( CHECK_LB_UP_LIKE ( dwMsg ) )		
	{												
		pUIControl->ResetExclusiveControl();		
		m_bFirstGap = FALSE;						
	}
}

HRESULT	CLargeMapWindowImage::Render ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	GASSERT( pd3dDevice );

	if( !IsVisible() ) return S_OK;

	HRESULT hr = S_OK;

	BOOL bPlayerMarkVisible = m_pPlayerMark->IsVisible ();
	m_pPlayerMark->SetVisibleSingle ( FALSE );
	{
		hr = CUIWindowEx::Render ( pd3dDevice );
		if ( FAILED ( hr ) ) return hr;
	}
	m_pPlayerMark->SetVisibleSingle ( bPlayerMarkVisible );	

	DWORD dwMinFilter(0), dwMagFilter(0), dwMipFilter(0);
	pd3dDevice->GetSamplerState( 0, D3DSAMP_MINFILTER, &dwMinFilter );
	pd3dDevice->GetSamplerState( 0, D3DSAMP_MAGFILTER, &dwMagFilter );
	pd3dDevice->GetSamplerState( 0, D3DSAMP_MIPFILTER, &dwMipFilter );

	pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR );
	pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR );
	pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR );

	hr = m_pPlayerMark->Render ( pd3dDevice );

	pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER, dwMinFilter );
	pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER, dwMagFilter );
	pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER, dwMipFilter );

	return hr;
}

void CLargeMapWindowImage::SetVisibleSingle ( BOOL bVisible )
{
	CUIWindowEx::SetVisibleSingle ( bVisible );

	if ( bVisible )
	{
		m_pPlayerMark->SetVisibleSingle ( TRUE );

		const D3DXVECTOR3 &vPlayerPos = GLGaeaClient::GetInstance().GetCharacterPos ();

		int nMAP_X(0), nMAP_Y(0);
		CONVERT_WORLD2MAP ( vPlayerPos, nMAP_X, nMAP_Y );
		DoCHARPOS_OnCENTER_InVIEW ( nMAP_X, nMAP_Y );

		UPDATE_CHAR_POS ( m_pPlayerMark, vPlayerPos );
		UPDATE_CHAR_ROTATE ( CInnerInterface::GetInstance().GetCharDir () );

		SetAutoMove ( true );		
	}
}

void CLargeMapWindowImage::OnLButtonUp()
{
	if( CInnerInterface::GetInstance().IsOpenWindowToMoveBlock() )
		return;

	INT iMapX( 0 ), iMapY( 0 );
	CONVERT_MOUSE2MAP( m_PosX, m_PosY, iMapX, iMapY );

	D3DXVECTOR3 vWorldPos( 0.0f, 0.0f, 0.0f );
	CONVERT_MAP2WORLD( iMapX, iMapY, vWorldPos );

	GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();
	if( !pCharacter )
		return;

	if( !pCharacter->LargeMapMoveTo( &vWorldPos ) )
		return;

	if ( CInnerInterface::GetInstance().GetLargeMapWindow()->m_bSUBMOTION ) 
	{
		if ( !pCharacter->m_bVehicle ) pCharacter->ReqSetVehicle(true);
	}

	m_iTargetX = iMapX;
	m_iTargetY = iMapY;

	UPDATE_TARGET_POS( m_iTargetX, m_iTargetY );
}

void CLargeMapWindowImage::UPDATE_CHAR_POS ( CUIControl * pControl, const D3DXVECTOR3& vPlayerPos )
{
	GASSERT( pControl );

	int nMapPosX(0), nMapPosY(0);
	CONVERT_WORLD2MAP ( vPlayerPos, nMapPosX, nMapPosY );

	int nPOINT_X = nMapPosX - m_nVIEW_START_X;
	int nPOINT_Y = nMapPosY - m_nVIEW_START_Y;

    if ( nPOINT_X < 0 || nPOINT_Y < 0 ) return ;
	if ( m_nVIEW_SIZE_X < nPOINT_X || m_nVIEW_SIZE_Y < nPOINT_Y ) return ;

	const UIRECT& rcGlobalPos = m_pMap->GetGlobalPos ();
	const UIRECT& rcMarkPos = pControl->GetGlobalPos ();
	D3DXVECTOR2 vNewMarkPos ( nPOINT_X + rcGlobalPos.left - (rcMarkPos.sizeX/2.f), nPOINT_Y + rcGlobalPos.top - (rcMarkPos.sizeY/2.f) );
	pControl->SetGlobalPos ( vNewMarkPos );
	pControl->SetVisibleSingle ( TRUE );
}

void CLargeMapWindowImage::UPDATE_CROW_POS ( CLargeMapWindowSlotRender * pSlot, const D3DXVECTOR3& vPos )
{
	GASSERT( pSlot );

	int nMapPosX(0), nMapPosY(0);
	CONVERT_WORLD2MAP ( vPos, nMapPosX, nMapPosY );

	int nPOINT_X = nMapPosX - m_nVIEW_START_X;
	int nPOINT_Y = nMapPosY - m_nVIEW_START_Y;

    if ( nPOINT_X < 0 || nPOINT_Y < 0 ) return ;
	if ( m_nVIEW_SIZE_X < nPOINT_X || m_nVIEW_SIZE_Y < nPOINT_Y ) return ;

	const UIRECT& rcGlobalPos = m_pMap->GetGlobalPos ();
	const UIRECT& rcMarkPos = pSlot->GetGlobalPos ();
	D3DXVECTOR2 vNewMarkPos ( nPOINT_X + rcGlobalPos.left - (rcMarkPos.sizeX/2.f), nPOINT_Y + rcGlobalPos.top - (rcMarkPos.sizeY/2.f) );
	pSlot->SetGlobalPos ( vNewMarkPos );
	pSlot->SetVisibleSingle ( TRUE );
}

void CLargeMapWindowImage::UPDATE_CHAR_ROTATE ( const D3DXVECTOR3& vCharDir )
{
	float LengthXZ;
	float thetaY;

	LengthXZ = (float) sqrt ( vCharDir.x*vCharDir.x + vCharDir.z*vCharDir.z );			
	
	if ( LengthXZ == 0 )	LengthXZ = 0.001f;

	thetaY = (float) acos ( vCharDir.x / LengthXZ );
	if ( vCharDir.z>0 )	thetaY = -thetaY;

	thetaY += D3DX_PI / 2.f;

	{
		UIRECT	rcGlobalPosDir = m_pPlayerMark->GetGlobalPos();
		D3DXVECTOR2	vCenterPos( floor(rcGlobalPosDir.left + (rcGlobalPosDir.sizeX)/2.f), floor(rcGlobalPosDir.top + (rcGlobalPosDir.sizeY)/2.f) );
		
		D3DXVECTOR2 vGlobalPosDir[4];
		vGlobalPosDir[0].x = rcGlobalPosDir.left - vCenterPos.x;
		vGlobalPosDir[0].y = rcGlobalPosDir.top - vCenterPos.y;
		vGlobalPosDir[1].x = rcGlobalPosDir.right - vCenterPos.x;
		vGlobalPosDir[1].y = rcGlobalPosDir.top - vCenterPos.y;
		vGlobalPosDir[2].x = rcGlobalPosDir.right - vCenterPos.x;
		vGlobalPosDir[2].y = rcGlobalPosDir.bottom - vCenterPos.y;
		vGlobalPosDir[3].x = rcGlobalPosDir.left - vCenterPos.x;
		vGlobalPosDir[3].y = rcGlobalPosDir.bottom - vCenterPos.y;
		
		for ( int i = 0; i < 4; ++i )
		{
			D3DXVECTOR2 vOutPos;
			vOutPos.x = (float) (cos(-thetaY) * vGlobalPosDir[i].x + sin(-thetaY)* vGlobalPosDir[i].y) + vCenterPos.x;
			vOutPos.y = (float) (-sin(-thetaY) * vGlobalPosDir[i].x + cos(-thetaY)* vGlobalPosDir[i].y)  + vCenterPos.y;
			m_pPlayerMark->SetGlobalPos(i , vOutPos);		
		}		
	}
}

void CLargeMapWindowImage::UPDATE_TARGET_POS( int iX, int iY )
{
	if( !m_pTargetMark )
		return;

	m_pTargetMark->SetVisibleSingle( FALSE );

	if( m_iTargetX == INT_MIN || m_iTargetY == INT_MIN )
		return;

	int nPOINT_X = iX - m_nVIEW_START_X;
	int nPOINT_Y = iY - m_nVIEW_START_Y;

    if( nPOINT_X < 0 || nPOINT_Y < 0 )
		return;

	if( m_nVIEW_SIZE_X < nPOINT_X || m_nVIEW_SIZE_Y < nPOINT_Y )
		return;

	{
		const D3DXVECTOR3& vPlayerPos = GLGaeaClient::GetInstance().GetCharacterPos();

		int nMAP_X( 0 ), nMAP_Y( 0 );
		CONVERT_WORLD2MAP( vPlayerPos, nMAP_X, nMAP_Y );

		if( abs( nMAP_X - m_iTargetX ) < 18 && abs( nMAP_Y - m_iTargetY ) < 18 )
		{
            VISIBLE_TARGET_POS();
			return;
		}
	}

	{
		const UIRECT& rcGlobalPos = m_pMap->GetGlobalPos();
		const UIRECT& rcMarkPos = m_pTargetMark->GetGlobalPos();
		D3DXVECTOR2 vNewMarkPos( nPOINT_X + rcGlobalPos.left - (rcMarkPos.sizeX/2.f), nPOINT_Y + rcGlobalPos.top - (rcMarkPos.sizeY/2.f) );
		m_pTargetMark->SetGlobalPos( vNewMarkPos );
	}

	m_pTargetMark->SetVisibleSingle( TRUE );
}

void CLargeMapWindowImage::VISIBLE_TARGET_POS( BOOL bVisible )
{
	if( !m_pTargetMark )
		return;

	if( !bVisible )
	{
		m_iTargetX = INT_MIN;
		m_iTargetY = INT_MIN;
	}

	m_pTargetMark->SetVisibleSingle( bVisible );
}

void CLargeMapWindowImage::DoCHARPOS_OnCENTER_InVIEW ( int nMapPosX, int nMapPosY )
{
	m_nVIEW_START_X = nMapPosX - static_cast<int>((static_cast<float>(m_nVIEW_SIZE_X)/2.0f));
	m_nVIEW_START_Y = nMapPosY - static_cast<int>((static_cast<float>(m_nVIEW_SIZE_Y)/2.0f));

	if ( m_nVIEW_START_X < 0 ) m_nVIEW_START_X = 0;
	if ( m_nVIEW_START_Y < 0 ) m_nVIEW_START_Y = 0;
	if ( m_nMAP_TEXSIZE_X - m_nVIEW_SIZE_X < m_nVIEW_START_X ) m_nVIEW_START_X = m_nMAP_TEXSIZE_X - m_nVIEW_SIZE_X;
	if ( m_nMAP_TEXSIZE_Y - m_nVIEW_SIZE_Y < m_nVIEW_START_Y ) m_nVIEW_START_Y = m_nMAP_TEXSIZE_Y - m_nVIEW_SIZE_Y;
	
	{
		CBasicScrollThumbFrame* pThumbFrame = m_pScrollBarH->GetThumbFrame ();
		const float& fPercent = pThumbFrame->GetPercent ();

		if ( m_vScrollGap.x == 0.0f )	pThumbFrame->SetPercent ( 0.0f );
		else							pThumbFrame->SetPercent ( m_nVIEW_START_X/m_vScrollGap.x );
	}

	{
		CBasicScrollThumbFrame* pThumbFrame = m_pScrollBarV->GetThumbFrame ();
		const float& fPercent = pThumbFrame->GetPercent ();

		if ( m_vScrollGap.y == 0.0f )	pThumbFrame->SetPercent ( 0.0f );
		else							pThumbFrame->SetPercent ( m_nVIEW_START_Y/m_vScrollGap.y );
	}
}

void CLargeMapWindowImage::CONVERT_WORLD2MAP ( const D3DXVECTOR3& vPos, int& nPosX, int& nPosY )
{
	int nCur_X = static_cast<int>(vPos.x) - m_nWORLD_START_X;
	int nCur_Y = (m_nWORLD_SIZE_Y-static_cast<int>(vPos.z)) + m_nWORLD_START_Y;

	nPosX = static_cast<int>(m_nMAP_TEXSIZE_X * nCur_X / m_nWORLD_SIZE_X);
	nPosY = static_cast<int>(m_nMAP_TEXSIZE_Y * nCur_Y / m_nWORLD_SIZE_Y);
}

void CLargeMapWindowImage::CONVERT_MOUSE2MAP ( const int nMousePosX, const int nMousePosY, int& nPosX, int& nPosY )
{
	const UIRECT& rcMapGlobalPos = m_pMap->GetGlobalPos ();
	const int nMouseX_RELATIVE = nMousePosX - static_cast<int>(rcMapGlobalPos.left);
	const int nMouseY_RELATIVE = nMousePosY - static_cast<int>(rcMapGlobalPos.top);	

	nPosX = nMouseX_RELATIVE + m_nVIEW_START_X;
	nPosY = nMouseY_RELATIVE + m_nVIEW_START_Y;
}

void CLargeMapWindowImage::CONVERT_MAP2WORLD ( const int nPosX, const int nPosY, D3DXVECTOR3& vPos )
{
	float fPosX = m_vWORLD_SIZE.x / m_vMAP_TEXSIZE.x * (float)nPosX;
	float fPosY = m_vWORLD_SIZE.y / m_vMAP_TEXSIZE.y * (float)nPosY;

	vPos.x = fPosX + m_vWORLD_START.x;
	vPos.z = m_vWORLD_SIZE.y - ( fPosY - m_vWORLD_START.y );
}

void CLargeMapWindowImage::UPDATE_MOUSE_POS ( const int nMouseX, const int nMouseY )
{
	if ( !CHECK_MOUSE_IN ( m_pMap->GetMessageEx () ) )
	{
		m_pMousePosText->SetVisibleSingle ( FALSE );
		m_pMousePosBack->SetVisibleSingle ( FALSE );
		return ;
	}

	const UIRECT& rcMapGlobalPos = m_pMap->GetGlobalPos ();
	const int nMouseX_RELATIVE = nMouseX - static_cast<int>(rcMapGlobalPos.left);
	const int nMouseY_RELATIVE = nMouseY - static_cast<int>(rcMapGlobalPos.top);	

	const int nX = nMouseX_RELATIVE + m_nVIEW_START_X;
	const int nY = m_nMAP_TEXSIZE_Y - (nMouseY_RELATIVE + m_nVIEW_START_Y);

	int PosX = (int)(((m_nWORLD_SIZE_X * nX) / m_nMAP_TEXSIZE_X) / 50.f);
	int PosY = (int)(((m_nWORLD_SIZE_Y * nY) / m_nMAP_TEXSIZE_Y) / 50.f);	
    
	CString strMousePos;
	strMousePos.Format ( "%03d %03d", PosX, PosY );
	m_pMousePosText->SetOneLineText ( strMousePos, NS_UITEXTCOLOR::WHITE );
	m_pMousePosText->SetVisibleSingle ( TRUE );
	m_pMousePosBack->SetVisibleSingle ( TRUE );
}

void CLargeMapWindowImage::UPDATE_PARTY ()
{
	UPDATE_PARTY_DEL();

	GLPARTY_CLIENT* pSelf = FindSelfClient ();

	if( pSelf ) UPDATE_PARTY_INS( pSelf ); 
}

void CLargeMapWindowImage::UPDATE_PARTY_DEL()
{
	for( INT i=0; i<MAXPARTY; ++i ) m_pMark[i]->SetVisibleSingle( FALSE );
}

void CLargeMapWindowImage::UPDATE_PARTY_INS( GLPARTY_CLIENT * pSelf )
{
	GLPARTY_CLIENT* pMaster = GLPartyClient::GetInstance().GetMaster();	
	if( !pMaster ) return ;

	if( ( pSelf != pMaster ) && IsSameMap( pSelf, pMaster ) ) UPDATE_CHAR_POS ( m_pMark[0], pMaster->m_vPos );

	DWORD nMEMBER_NUM = GLPartyClient::GetInstance().GetMemberNum();
	if( nMEMBER_NUM > 1 )
	{
		nMEMBER_NUM -= 1; 
		for ( DWORD nIndex = 0; nIndex < nMEMBER_NUM; ++nIndex )
		{
			GLPARTY_CLIENT *pMember = GLPartyClient::GetInstance().GetMember( nIndex );

			if( !pMember )						continue;
			if( !IsSameMap( pSelf, pMember ) )	continue;
			if( pSelf == pMember )				continue;

			UPDATE_CHAR_POS( m_pMark[nIndex+1], pMember->m_vPos );
		}
	}
}

BOOL CLargeMapWindowImage::IsSameMap ( GLPARTY_CLIENT *pSelf, GLPARTY_CLIENT *pMember )
{
	if ( !pSelf || !pMember ) return FALSE;
	
	return pSelf->m_sMapID.dwID == pMember->m_sMapID.dwID;
}

GLPARTY_CLIENT*	CLargeMapWindowImage::FindSelfClient ()
{
	GLPARTY_CLIENT *pMaster = GLPartyClient::GetInstance().GetMaster();	

	if( pMaster && pMaster->ISONESELF() ) return pMaster;
	else
	{
		DWORD nMEMBER_NUM = GLPartyClient::GetInstance().GetMemberNum();
		if( nMEMBER_NUM > 1 )
		{
			nMEMBER_NUM -= 1; 
			for ( DWORD i = 0; i < nMEMBER_NUM; ++i )
			{
				GLPARTY_CLIENT *pMember = GLPartyClient::GetInstance().GetMember( i );

				if( pMember && pMember->ISONESELF() ) return pMember;				
			}
		}
	}

	return NULL;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////////
void CLargeMapWindowImage::LoadMob(NET_MSG_GENERIC* nmg, GLCHARLOGIC *pCHAR )
{
	GLMSG::SNETPC_REQ_CROWLIST_FB* pNetMsg = (GLMSG::SNETPC_REQ_CROWLIST_FB*)nmg;
	if ( pNetMsg->bRender )
	{
		PCROWDATA pCrow = GLCrowDataMan::GetInstance().GetCrowData( pNetMsg->sCrowID.wMainID, pNetMsg->sCrowID.wSubID );
		if ( !pCrow ) return;

		m_NEWID++;
		CLargeMapWindowSlotRender* pSlot = new CLargeMapWindowSlotRender;
		pSlot->CreateSub( this, "MAP_WINDOW_MONSTER_ICON_MAIN", UI_FLAG_DEFAULT, m_NEWID );
		pSlot->CreateSubControl();
		pSlot->SetCrow( pCrow, pCHAR );
		pSlot->InitDeviceObjects ( m_pd3dDevice );
		pSlot->RestoreDeviceObjects ( m_pd3dDevice );
		pSlot->SetVisibleSingle( FALSE );
		RegisterControl( pSlot );

		CROW_PAIR pair(pNetMsg->vPos, pSlot);
		m_CrowList.push_back(pair);
	}
}

void CLargeMapWindowImage::ClearMobList()
{
	if ( !m_CrowList.empty())
	{
		CROW_LIST_ITER iter = m_CrowList.begin ();
		CROW_LIST_ITER iter_end = m_CrowList.end ();
		for( ; iter != iter_end; ++iter )
		{
			D3DXVECTOR3 vPos = iter->first;
			CLargeMapWindowSlotRender* pSlot = iter->second;
			pSlot->SetVisibleSingle(FALSE);
			pSlot->UnLoadAll();
		}
	}
	
	m_CrowList.clear();
	DeleteControl( m_NEWID, 0 );

	SetGateList();
}

void CLargeMapWindowImage::SetGateList()
{
	PLANDMANCLIENT pLand = GLGaeaClient::GetInstance().GetActiveMap();
	if ( !pLand ) return;

	DxLandGateMan* pGateMan = &pLand->GetLandGateMan();
	if ( !pGateMan ) return;

	PDXLANDGATE pLandGate = pGateMan->GetListLandGate();
	while ( pLandGate )
	{
		if ( pLandGate->GetFlags() & DxLandGate::GATE_OUT )
		{
			const char *szMAPNAME = GLGaeaClient::GetInstance().GetMapName ( pLandGate->GetToMapID() );

			m_NEWID++;
			CLargeMapWindowSlotRender* pSlot = new CLargeMapWindowSlotRender;
			pSlot->CreateSub( this, "MAP_WINDOW_MONSTER_ICON_MAIN", UI_FLAG_DEFAULT, m_NEWID );
			pSlot->CreateSubControl();
			pSlot->SetGate(szMAPNAME);
			pSlot->InitDeviceObjects ( m_pd3dDevice );
			pSlot->RestoreDeviceObjects ( m_pd3dDevice );
			pSlot->SetVisibleSingle(FALSE);
			RegisterControl( pSlot );

			CROW_PAIR pair(pLandGate->GetGenPos(DxLandGate::GEN_RENDUM), pSlot);
			m_CrowList.push_back(pair);
		}
		
		pLandGate = pLandGate->m_pNext;
	}
}