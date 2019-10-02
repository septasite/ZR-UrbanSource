#include "StdAfx.h"
#include "ItemImageRecipe.h"
#include "GLGaeaClient.h"
#include "GLItemMan.h"
#include "../SkillFunc.h"
#include "../EngineUiLib/GUInterface/BasicProgressBar.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const DWORD	RECHARGECOLOR = D3DCOLOR_ARGB(150,0,0,0);

CItemImageRecipe::CItemImageRecipe () 
	: m_pItemImageRecipe ( NULL )
	, m_pd3dDevice ( NULL )
	, m_sICONINDEX ( NATIVEID_NULL () )
	, m_TotElapsedTime(0.0f)
	, m_bItemUsed(false)
	, m_bItemEnd(false)
	, m_bTwinkle(true)
	, m_pItemProcess( NULL )
	, m_sNativeID(false)
	, m_pItemImageFlip( NULL )
{
	sItem = SITEMCUSTOM( NATIVEID_NULL() );
}

CItemImageRecipe::~CItemImageRecipe ()
{
}

HRESULT CItemImageRecipe::InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	HRESULT hr = S_OK;
	hr = CUIGroup::InitDeviceObjects ( pd3dDevice );
	if ( FAILED ( hr ) ) return hr;

	m_pd3dDevice = pd3dDevice;

	return S_OK;
}

void	CItemImageRecipe::CreateSubControl ()
{
	m_pItemImageRecipe = new CUIControl;
	m_pItemImageRecipe->CreateSub ( this, "ITEM_IMAGE" );	
	m_pItemImageRecipe->SetUseRender ( TRUE );
	m_pItemImageRecipe->SetVisibleSingle ( FALSE );
	RegisterControl ( m_pItemImageRecipe );

	CBasicProgressBar* pItemProcess = new CBasicProgressBar;
	pItemProcess->CreateSub ( this, "ITEM_IMAGE_PROGRESS" );
	pItemProcess->CreateOverImage ( "ITEM_IMAGE_PROGRESS_OVER" );
	pItemProcess->SetType ( CBasicProgressBar::VERTICAL );
	pItemProcess->SetOverImageUseRender ( TRUE );
	pItemProcess->SetOverImageDiffuse ( RECHARGECOLOR );
	pItemProcess->SetControlNameEx ( "프로그래스바" );	
	RegisterControl ( pItemProcess );
	m_pItemProcess = pItemProcess;

	m_pItemImageFlip = new CUIControl;
	m_pItemImageFlip->CreateSub ( this, "ITEM_MOUSE_OVER" );	
	m_pItemImageFlip->SetVisibleSingle ( FALSE );
	RegisterControl ( m_pItemImageFlip );

}

void CItemImageRecipe::Update( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	if( m_bItemUsed && m_bItemEnd )
	{
		m_TotElapsedTime += fElapsedTime;

		if( m_TotElapsedTime < 0.3f )		m_pItemProcess->SetPercent(0);
		else if( m_TotElapsedTime < 0.6f )	m_pItemProcess->SetPercent(1);
		else if( m_TotElapsedTime < 0.9f )	m_pItemProcess->SetPercent(0);
		else if( m_TotElapsedTime < 1.2f )	m_pItemProcess->SetPercent(1);
		else
		{
			m_pItemProcess->SetPercent(0);
			m_TotElapsedTime = 0.0f;
			m_bItemEnd = false;
			m_bItemUsed = false;
		}
	}

    if ( !m_pItemProcess )
	{
		GASSERT ( 0 && "프로그래스바가 만들어지지 않았습니다." );
		return ;
	}

	SITEM* pItem = GLItemMan::GetInstance().GetItem( m_sNativeID );
	if ( !pItem )	return ;

	if ( !GLGaeaClient::GetInstance().GetCharacter()->IsCoolTime( m_sNativeID ) )
	{
		m_bItemEnd = true;
		return;
	}	

	ITEM_COOLTIME* pItemCoolTime = GLGaeaClient::GetInstance().GetCharacter()->GetCoolTime( m_sNativeID );
	if ( !pItemCoolTime )
	{
		m_bItemEnd = true;
		return;
	}

	m_bItemEnd = false;

	__time64_t tCurTime = GLGaeaClient::GetInstance().GetCurrentTime().GetTime();
	__time64_t tUseTime = pItemCoolTime->tUseTime;
	__time64_t tCoolTime = pItemCoolTime->tCoolTime;

	float fCoolTime = (float)tCoolTime - tUseTime;
	float fCurTime = fCoolTime - ( tCurTime - tUseTime );
	
	if ( fCoolTime == 0.0f )
	{
		fCoolTime = 1.0f;
	}

	const float fPercent = fCurTime / fCoolTime;
	m_pItemProcess->SetPercent ( fPercent );
	m_bItemUsed = true;
}

void CItemImageRecipe::SetItem ( SITEMCUSTOM sItemCustom )
{	
	SITEM* pItemSet = GLItemMan::GetInstance().GetItem( sItemCustom.sNativeID );
	if ( !pItemSet )	return;

	if ( !m_pItemImageRecipe )	return;

	if( m_sNativeID == pItemSet->sBasicOp.sNativeID && pItemSet->sBasicOp.sNativeID != NATIVEID_NULL() )	return;

	if ( ( pItemSet->sBasicOp.sICONID == m_sICONINDEX) && ( pItemSet->GetInventoryFile() == m_pItemImageRecipe->GetTextureName ()) )	return ;


	ResetItem ();
	SetItemProcess( pItemSet->sBasicOp.sNativeID );

	if ( m_pItemImageRecipe )
	{
		m_pItemImageRecipe->SetTexturePos ( NS_SKILL::GetIconTexurePos ( pItemSet->sBasicOp.sICONID ) );
		m_pItemImageRecipe->SetTextureName ( pItemSet->GetInventoryFile() );	

		if ( m_pd3dDevice )
		{	
			m_pItemImageRecipe->InitDeviceObjects ( m_pd3dDevice );
			m_pItemImageRecipe->SetVisibleSingle ( TRUE );

			m_sICONINDEX = pItemSet->sBasicOp.sICONID;
			m_strTextureName = pItemSet->GetInventoryFile();
			sItem = sItemCustom;
		}
	}
}

SITEMCUSTOM&	 CItemImageRecipe::GetItem ()
{
	return sItem;
}

void CItemImageRecipe::ResetItem ()
{
	if ( m_pItemImageRecipe )
	{
		if ( m_sICONINDEX != NATIVEID_NULL () )
		{
			m_pItemImageRecipe->DeleteDeviceObjects ();
			m_pItemImageRecipe->SetTextureName ( NULL );
			m_pItemImageRecipe->SetVisibleSingle ( FALSE );
			m_sICONINDEX = NATIVEID_NULL ();
			ReSetItemProcess();
			m_strTextureName.Empty ();
			sItem = SITEMCUSTOM( NATIVEID_NULL() );
		}		
	}
}

const CString&	CItemImageRecipe::GetItemTextureName () const
{
	return m_strTextureName;
}

void CItemImageRecipe::SetItemProcess( SNATIVEID sNativeID )
{
	m_bItemUsed = false;	
	m_sNativeID = sNativeID;

	if ( sNativeID == NATIVEID_NULL() )
	{
		m_pItemProcess->SetVisibleSingle( FALSE );
	}else{
		m_pItemProcess->SetVisibleSingle( TRUE );
	}

	return;
}

void CItemImageRecipe::ReSetItemProcess()
{
	m_bItemUsed = false;
	m_sNativeID = NATIVEID_NULL();
	m_pItemProcess->SetVisibleSingle( FALSE );
	m_pItemProcess->SetPercent( 0.0f );
	
	return;
}

void CItemImageRecipe::SetDiffuse(D3DCOLOR _diffuse)
{
	CUIGroup::SetDiffuse( _diffuse );

	m_pItemProcess->SetOverImageDiffuse ( RECHARGECOLOR );
}

void CItemImageRecipe::VisibleFlipImage( bool bVisible )
{
	if ( m_pItemImageFlip )
	{
		m_pItemImageFlip->SetDiffuse( D3DXCOLOR( 255,0,0,255 ));
		m_pItemImageFlip->SetVisibleSingle( bVisible );
	}
}