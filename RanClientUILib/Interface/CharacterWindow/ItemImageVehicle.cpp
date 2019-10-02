#include "StdAfx.h"
#include "ItemImageVehicle.h"
#include "GLGaeaClient.h"
#include "GLItemMan.h"
#include "../SkillFunc.h"
#include "../EngineUiLib/GUInterface/BasicProgressBar.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const DWORD	RECHARGECOLOR = D3DCOLOR_ARGB(150,0,0,0);

CItemImageVehicle::CItemImageVehicle () 
	: m_pItemImageVehicle ( NULL )
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

CItemImageVehicle::~CItemImageVehicle ()
{
}

HRESULT CItemImageVehicle::InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	HRESULT hr = S_OK;
	hr = CUIGroup::InitDeviceObjects ( pd3dDevice );
	if ( FAILED ( hr ) ) return hr;

	m_pd3dDevice = pd3dDevice;

	return S_OK;
}

void	CItemImageVehicle::CreateSubControl ()
{
	m_pItemImageVehicle = new CUIControl;
	m_pItemImageVehicle->CreateSub ( this, "ITEM_IMAGE" );	
	m_pItemImageVehicle->SetUseRender ( TRUE );
	m_pItemImageVehicle->SetVisibleSingle ( FALSE );
	RegisterControl ( m_pItemImageVehicle );

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

void CItemImageVehicle::Update( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
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

	float fCoolTime = tCoolTime - tUseTime;
	float fCurTime = fCoolTime - ( tCurTime - tUseTime );
	
	if ( fCoolTime == 0.0f )
	{
		fCoolTime = 1.0f;
	}

	const float fPercent = fCurTime / fCoolTime;
	m_pItemProcess->SetPercent ( fPercent );
	m_bItemUsed = true;
}

void CItemImageVehicle::SetItem ( SITEMCUSTOM sItemCustom )
{	
	SITEM* pItemSet = GLItemMan::GetInstance().GetItem( sItemCustom.sNativeID );
	if ( !pItemSet )	return;

	if ( !m_pItemImageVehicle )	return;

	if( m_sNativeID == pItemSet->sBasicOp.sNativeID && pItemSet->sBasicOp.sNativeID != NATIVEID_NULL() )	return;

	if ( ( pItemSet->sBasicOp.sICONID == m_sICONINDEX) && ( pItemSet->GetInventoryFile() == m_pItemImageVehicle->GetTextureName ()) )	return ;


	ResetItem ();
	SetItemProcess( pItemSet->sBasicOp.sNativeID );

	if ( m_pItemImageVehicle )
	{
		m_pItemImageVehicle->SetTexturePos ( NS_SKILL::GetIconTexurePos ( pItemSet->sBasicOp.sICONID ) );
		m_pItemImageVehicle->SetTextureName ( pItemSet->GetInventoryFile() );	

		if ( m_pd3dDevice )
		{	
			m_pItemImageVehicle->InitDeviceObjects ( m_pd3dDevice );
			m_pItemImageVehicle->SetVisibleSingle ( TRUE );

			m_sICONINDEX = pItemSet->sBasicOp.sICONID;
			m_strTextureName = pItemSet->GetInventoryFile();
			sItem = sItemCustom;
		}
	}
}

SITEMCUSTOM&	 CItemImageVehicle::GetItem ()
{
	return sItem;
}

void CItemImageVehicle::ResetItem ()
{
	if ( m_pItemImageVehicle )
	{
		if ( m_sICONINDEX != NATIVEID_NULL () )
		{
			m_pItemImageVehicle->DeleteDeviceObjects ();
			m_pItemImageVehicle->SetTextureName ( NULL );
			m_pItemImageVehicle->SetVisibleSingle ( FALSE );
			m_sICONINDEX = NATIVEID_NULL ();
			ReSetItemProcess();
			m_strTextureName.Empty ();
			sItem = SITEMCUSTOM( NATIVEID_NULL() );
		}		
	}
}

const CString&	CItemImageVehicle::GetItemTextureName () const
{
	return m_strTextureName;
}

void CItemImageVehicle::SetItemProcess( SNATIVEID sNativeID )
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

void CItemImageVehicle::ReSetItemProcess()
{
	m_bItemUsed = false;
	m_sNativeID = NATIVEID_NULL();
	m_pItemProcess->SetVisibleSingle( FALSE );
	m_pItemProcess->SetPercent( 0.0f );
	
	return;
}

void CItemImageVehicle::SetDiffuse(D3DCOLOR _diffuse)
{
	CUIGroup::SetDiffuse( _diffuse );

	m_pItemProcess->SetOverImageDiffuse ( RECHARGECOLOR );
}

void CItemImageVehicle::VisibleFlipImage( bool bVisible )
{
	if ( m_pItemImageFlip )
	{
		m_pItemImageFlip->SetDiffuse( D3DXCOLOR( 255,0,0,255 ));
		m_pItemImageFlip->SetVisibleSingle( bVisible );
	}
}