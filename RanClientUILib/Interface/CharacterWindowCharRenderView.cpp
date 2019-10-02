#include "StdAfx.h"
#include "CharacterWindowCharRenderView.h"

#include "../DxCommon/DxBackUpRendTarget.h"
#include "GLGaeaClient.h"
#include "DxGlobalStage.h"
#include "DxEffcharData.h"
#include "../enginelib/Meshs/DxSkinPieceData.h"
#include "../enginelib/Meshs/DxSkinCharPiece.h"
#include "../enginelib/Meshs/DxSkinPieceRootData.h"



#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCharacterWindowCharRenderView::CCharacterWindowCharRenderView () 
	: m_pSkinChar( NULL )
	, m_wLastFace(0)
	, m_wLastHair(0)
	//, m_fDelay(0.0f)
{
	D3DXMatrixIdentity ( &m_matTrans );
}

CCharacterWindowCharRenderView::~CCharacterWindowCharRenderView ()
{
}

void CCharacterWindowCharRenderView::CreateSubControl ()
{
}

void CCharacterWindowCharRenderView::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

HRESULT CCharacterWindowCharRenderView::RestoreDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	HRESULT hr = S_OK;

	if ( m_pSkinChar )
		m_pSkinChar->RestoreDeviceObjects( pd3dDevice );

	hr = CUIGroup::RestoreDeviceObjects( pd3dDevice );
	return hr;
}

HRESULT CCharacterWindowCharRenderView::DeleteDeviceObjects ()
{
	HRESULT hr = S_OK;

	if ( m_pSkinChar )
		m_pSkinChar->DeleteDeviceObjects ();

	hr = CUIGroup::DeleteDeviceObjects ();

	return hr;
}

HRESULT CCharacterWindowCharRenderView::Render ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	HRESULT hr = S_OK;

	if ( !m_pSkinChar )
	{
		CreateModel( pd3dDevice );
	}else{

		//if ( m_fDelay < 0.2 ) return S_OK;

		DWORD dwAlphaBlendEnable, dwSrcBlend, dwDestBlend, dwZWriteEnable, dwZEnable, dwZFunc, dwClipPlaneEnable, dwFogEnable, dwAmbient, dwLighting;
		DWORD dwColorOP, dwAlphaOP, dwMinFilter, dwMagFilter, dwMipFilter;
		D3DXMATRIX		matOrgView, matOrgProj, matOrgWorld;
		D3DVIEWPORTQ OrgViewPort;

		pd3dDevice->GetViewport(&OrgViewPort);

		pd3dDevice->GetTransform ( D3DTS_VIEW, &matOrgView );
		pd3dDevice->GetTransform ( D3DTS_PROJECTION, &matOrgProj );
		pd3dDevice->GetTransform ( D3DTS_WORLD, &matOrgWorld );

		DxBackUpRendTarget sBackupTarget ( pd3dDevice );

		pd3dDevice->GetRenderState( D3DRS_ALPHABLENDENABLE,	&dwAlphaBlendEnable );
		pd3dDevice->GetRenderState( D3DRS_SRCBLEND,			&dwSrcBlend );
		pd3dDevice->GetRenderState( D3DRS_DESTBLEND,		&dwDestBlend );
		pd3dDevice->GetRenderState( D3DRS_ZWRITEENABLE,		&dwZWriteEnable );
		pd3dDevice->GetRenderState( D3DRS_ZENABLE,			&dwZEnable );
		pd3dDevice->GetRenderState( D3DRS_ZFUNC,			&dwZFunc);
		pd3dDevice->GetRenderState( D3DRS_CLIPPLANEENABLE,	&dwClipPlaneEnable );
		pd3dDevice->GetRenderState( D3DRS_FOGENABLE,		&dwFogEnable );
		pd3dDevice->GetRenderState( D3DRS_AMBIENT,			&dwAmbient );
		pd3dDevice->GetRenderState( D3DRS_LIGHTING,			&dwLighting );

		pd3dDevice->GetTextureStageState( 0, D3DTSS_COLOROP,	&dwColorOP );
		pd3dDevice->GetTextureStageState( 0, D3DTSS_ALPHAOP,	&dwAlphaOP );

		pd3dDevice->GetSamplerState( 0, D3DSAMP_MINFILTER,	&dwMinFilter );
		pd3dDevice->GetSamplerState( 0, D3DSAMP_MAGFILTER,	&dwMagFilter );
		pd3dDevice->GetSamplerState( 0, D3DSAMP_MIPFILTER,	&dwMipFilter );
		
		pd3dDevice->Clear(0, NULL, D3DCLEAR_ZBUFFER, 0xffa08080, 1.0f, 0 ) ;

		pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,		TRUE );
		pd3dDevice->SetRenderState( D3DRS_ZENABLE,			D3DZB_TRUE );
		pd3dDevice->SetRenderState( D3DRS_ZFUNC,			D3DCMP_LESSEQUAL);
		pd3dDevice->SetRenderState( D3DRS_AMBIENT,			D3DCOLOR_XRGB(220,220,220) );
		pd3dDevice->SetRenderState( D3DRS_LIGHTING,			FALSE );

		D3DXMATRIX		matView, matProj, matWorld;

		D3DVIEWPORTQ ViewPort;
		ViewPort.X      = (DWORD)GetGlobalPos().left;
		ViewPort.Y      = (DWORD)GetGlobalPos().top;
		ViewPort.Width  = (DWORD)GetGlobalPos().sizeX;
		ViewPort.Height = (DWORD)GetGlobalPos().sizeY;
		ViewPort.MinZ = 0.0f;
		ViewPort.MaxZ = 1.0f;
		pd3dDevice->SetViewport(&ViewPort);

		D3DXVECTOR3 vFromPt		= D3DXVECTOR3( 0.0f, 0.3f, -35.0f );
		D3DXVECTOR3 vLookatPt	= D3DXVECTOR3( -0.02f, 0.0f, 5.0f );
		D3DXVECTOR3 vUpVec		= D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
		D3DXMatrixLookAtLH ( &matView, &vFromPt, &vLookatPt, &vUpVec );
		pd3dDevice->SetTransform ( D3DTS_VIEW, &matView );

		float fFieldOfView = D3DX_PI/4.0f;
		float fAspectRatio = ((float)ViewPort.Width) / (float)ViewPort.Height;
		D3DXMatrixPerspectiveFovLH ( &matProj, fFieldOfView, fAspectRatio, 1.0f, 80.0f );
		pd3dDevice->SetTransform ( D3DTS_PROJECTION, &matProj );
		
		D3DXMatrixIdentity ( &matWorld );
		pd3dDevice->SetTransform ( D3DTS_WORLD, &matWorld );

		RenderModel( pd3dDevice );

		sBackupTarget.RestoreTarget ( pd3dDevice );

		pd3dDevice->SetTransform ( D3DTS_VIEW, &matOrgView );
		pd3dDevice->SetTransform ( D3DTS_PROJECTION, &matOrgProj );
		pd3dDevice->SetTransform ( D3DTS_WORLD, &matOrgWorld );

		pd3dDevice->SetRenderState( D3DRS_ALPHABLENDENABLE,	dwAlphaBlendEnable );
		pd3dDevice->SetRenderState( D3DRS_SRCBLEND,			dwSrcBlend );
		pd3dDevice->SetRenderState( D3DRS_DESTBLEND,		dwDestBlend );
		pd3dDevice->SetRenderState( D3DRS_ZWRITEENABLE,		dwZWriteEnable );
		pd3dDevice->SetRenderState( D3DRS_ZENABLE,			dwZEnable );
		pd3dDevice->SetRenderState( D3DRS_ZFUNC,			dwZFunc);
		pd3dDevice->SetRenderState( D3DRS_CLIPPLANEENABLE,	dwClipPlaneEnable );
		pd3dDevice->SetRenderState( D3DRS_FOGENABLE,		dwFogEnable );
		pd3dDevice->SetRenderState( D3DRS_AMBIENT,			dwAmbient );
		pd3dDevice->SetRenderState( D3DRS_LIGHTING,			dwLighting );

		pd3dDevice->SetTextureStageState( 0, D3DTSS_COLOROP,	dwColorOP );
		pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,	dwAlphaOP );

		pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER,	dwMinFilter );
		pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER,	dwMagFilter );
		pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER,	dwMipFilter );

		pd3dDevice->SetViewport(&OrgViewPort);	
	}

	hr = CUIGroup::Render ( pd3dDevice );
	return hr;
}

HRESULT CCharacterWindowCharRenderView::FrameMove( LPDIRECT3DDEVICEQ pd3dDevice, float fTime, float fElapsedTime )
{
	HRESULT hr = S_OK;

	//m_fDelay += fElapsedTime;

	if ( m_pSkinChar )
	{
		m_pSkinChar->FrameMove ( fTime, fElapsedTime, TRUE, FALSE, FALSE );
	}

	hr = CUIGroup::FrameMove( pd3dDevice, fTime, fElapsedTime );
	return hr;
}

void CCharacterWindowCharRenderView::CreateModel( LPDIRECT3DDEVICEQ pd3dDevice )
{

	EMCHARINDEX emIndex = CharClassToIndex(m_CharData.emClass);
	DxSkinCharData* pSkinChar = DxSkinCharDataContainer::GetInstance().LoadData ( GLCONST_CHAR::szCharSkin[emIndex], pd3dDevice, true  );

	if ( !pSkinChar )	return;

	SAFE_DELETE(m_pSkinChar);
	m_pSkinChar = new DxSkinChar;
	m_pSkinChar->InitDeviceObjects( pd3dDevice );
	m_pSkinChar->SetCharData ( pSkinChar, pd3dDevice );
	m_pSkinChar->SELECTANI( AN_PLACID, AN_SUB_NONE );
	UpdateSuit( pd3dDevice );

	//m_fDelay = 0.0f;
}

void CCharacterWindowCharRenderView::RenderModel( LPDIRECT3DDEVICEQ pd3dDevice )
{
	if ( m_pSkinChar )
	{
		float fScale = 1.0f;
		D3DXMATRIX matTrans, matScale;

		D3DXMatrixScaling( &matScale, fScale, fScale, fScale );
		D3DXMatrixTranslation( &matTrans, 0.0f, -12.0f, 0.0f );

		m_matTrans = matScale*matTrans;

		m_pSkinChar->Render( pd3dDevice, m_matTrans/*, FALSE, FALSE, FALSE */);
	}
}

void CCharacterWindowCharRenderView::UpdateSuit( LPDIRECT3DDEVICEQ pd3dDevice  )
{

	if ( !m_pSkinChar )	return;

	EMCHARINDEX emIndex = CharClassToIndex( m_CharData.emClass );
	DxSkinCharData* pSkinChar = DxSkinCharDataContainer::GetInstance().FindData ( GLCONST_CHAR::szCharSkin[emIndex] );
	if ( !pSkinChar )	return;

	const GLCONST_CHARCLASS &sCONST = GLCONST_CHAR::cCONSTCLASS[emIndex];

	WORD m_wFace = m_CharData.wFace;
	WORD m_wHair = m_CharData.wHair;
	WORD m_wHairColor = m_CharData.wHairColor;

	//if ( m_wLastHair != m_wHair )
	{
		if ( sCONST.dwHEADNUM > m_wFace )
		{
			std::string strHEAD_CPS = sCONST.strHEAD_CPS[m_wFace];
		
			PDXCHARPART pCharPart = NULL;
			pCharPart = m_pSkinChar->GetPiece(PIECE_HEAD);

			if ( pCharPart && strcmp(strHEAD_CPS.c_str(),pCharPart->m_szFileName) )
				m_pSkinChar->SetPiece ( strHEAD_CPS.c_str(), pd3dDevice, 0x0, 0, TRUE );

			//m_wLastHair = m_wHair;
		}
	}

	//if( m_wLastFace != m_wFace )
	{
		if ( sCONST.dwHAIRNUM > m_wHair )
		{
			std::string strHAIR_CPS = sCONST.strHAIR_CPS[m_wHair];
		
			PDXCHARPART pCharPart = NULL;
			pCharPart = m_pSkinChar->GetPiece(PIECE_HAIR);

			if ( pCharPart && strcmp(strHAIR_CPS.c_str(),pCharPart->m_szFileName) )
				m_pSkinChar->SetPiece ( strHAIR_CPS.c_str(), pd3dDevice, 0x0, 0, TRUE );

			//m_wLastFace = m_wFace;
		}
	}

	m_pSkinChar->SetHairColor( m_wHairColor );


	for ( int i=0; i<SLOT_NSIZE_S_2; i++ )
	{	
		EMSLOT emSLOT = static_cast<EMSLOT>(i);
		if ( !VALID_SLOT_ITEMa(emSLOT) )					continue;
		
		SITEMCLIENT &ItemClient = m_CharData.m_PutOnItems[i];
		if ( i == SLOT_LHAND  )	ItemClient = m_CharData.m_PutOnItems[SLOT_RHAND];
		if ( i == SLOT_LHAND_S  )	ItemClient = m_CharData.m_PutOnItems[SLOT_RHAND_S];

		SNATIVEID nidITEM = ItemClient.nidDISGUISE;
		if ( nidITEM==SNATIVEID(false) )	nidITEM = ItemClient.sNativeID;
		
		if ( i == SLOT_VEHICLE )	continue;

		if ( nidITEM == SNATIVEID(false) )
		{
			PDXSKINPIECE pSkinPiece = NULL;
			PDXCHARPART pCharPart = NULL;

			EMPIECECHAR emPiece = SLOT_2_PIECE(EMSLOT(i));

			if ( emPiece!=PIECE_SIZE )
			{
				pSkinPiece = pSkinChar->GetPiece(emPiece);
				pCharPart = m_pSkinChar->GetPiece(emPiece);
			}

			if ( pSkinPiece ) 
			{ 
				if ( pCharPart && strcmp(pSkinPiece->m_szFileName,pCharPart->m_szFileName) )
				{
					DxSkinPieceRootData* pPieceDataRoot;
					pPieceDataRoot = DxSkinPieceRootDataContainer::GetInstance().LoadData( pSkinPiece->m_szFileName, pd3dDevice, TRUE );
					if ( pPieceDataRoot )
					{
						if ( pPieceDataRoot->GetUseCPS() )
						{
							m_pSkinChar->SetPiece( pPieceDataRoot->GetCpsName().c_str(), pd3dDevice, 0X0, 0, TRUE );
						}else{
							EMPIECECHAR emPiece_a = SLOT_2_PIECE(EMSLOT(i));
							PDXSKINPIECE pSkinPiece_a  = NULL;	
							if ( emPiece_a!=PIECE_SIZE )
							{
								pSkinPiece_a  = pSkinChar->GetPiece(emPiece_a );
							}
							m_pSkinChar->SetPiece ( pSkinPiece_a->m_szFileName, pd3dDevice, 0X0, 0, TRUE );
						}
						m_pSkinChar->SetCharPieceData( pPieceDataRoot->GetData(), pd3dDevice, pPieceDataRoot->GetBoneLink(), pPieceDataRoot->GetWeaponSlot(), pPieceDataRoot->GetType(), 0x0, 0, TRUE );
					}else{
						m_pSkinChar->SetPiece ( pSkinPiece->m_szFileName, pd3dDevice, 0X0, 0, TRUE );
						m_pSkinChar->ResetABL ( emPiece );
					}
				}else{
					m_pSkinChar->ResetABL ( emPiece );
				}

				if (  emPiece == PIECE_UPBODY )
				{
					m_pSkinChar->ResetPiece(PIECE_EFF_UPBODY);
				}else if (  emPiece == PIECE_LOBODY ){
					m_pSkinChar->ResetPiece(PIECE_EFF_LOBODY);
				}else if (  emPiece == PIECE_GLOVE ){
					m_pSkinChar->ResetPiece(PIECE_EFF_GLOVE);
				}else if (  emPiece == PIECE_FOOT ){
					m_pSkinChar->ResetPiece(PIECE_EFF_FOOT);
				}
			}
			else
			{
				if ( pCharPart )
				{
					if ( m_pSkinChar->m_pSkinCharPiece[PIECE_RHAND] && emPiece != PIECE_LHAND )
					{
						m_pSkinChar->ResetPiece(emPiece);
					}else{
						if ( emPiece != PIECE_LHAND )	m_pSkinChar->ResetPiece(emPiece);

						EMSLOT emRHand = GetCurRHandd();
						SITEM* pRHAND = GET_SLOT_ITEMDATAa ( emRHand );
						if ( pRHAND )
						{
							EMCHARCLASS emSex = CharClassGetSex( emIndex );
							EMCPSINDEX	emLeft = CPSIND_NULL;
							if ( emSex == GLCC_MAN )
							{
								emLeft = CPSIND_M_LEFT;
							}else{
								emLeft = CPSIND_W_LEFT;
							}

							if (strcmp(pRHAND->GetCpsFile(emLeft), "") == 0)
							{
								m_pSkinChar->ResetPiece(emPiece);
							}
						}else{
							if ( !m_pSkinChar->m_pSkinCharPiece[PIECE_RHAND] && emPiece == PIECE_LHAND )
								m_pSkinChar->ResetPiece(emPiece);
						}
					}

					if (  emPiece == PIECE_UPBODY )
					{
						m_pSkinChar->ResetPiece(PIECE_EFF_UPBODY);
					}else if (  emPiece == PIECE_LOBODY ){
						m_pSkinChar->ResetPiece(PIECE_EFF_LOBODY);
					}else if (  emPiece == PIECE_GLOVE ){
						m_pSkinChar->ResetPiece(PIECE_EFF_GLOVE);
					}else if (  emPiece == PIECE_FOOT ){
						m_pSkinChar->ResetPiece(PIECE_EFF_FOOT);
					}
				}
			}
		}
		else
		{
			SITEM* pItem = GLItemMan::GetInstance().GetItem ( nidITEM );
			if ( pItem ) 
			{

				EMCHARCLASS emSex = CharClassGetSex( emIndex );
				EMCPSINDEX	emLeft = CPSIND_NULL;
				EMCPSINDEX	emRight = CPSIND_NULL;

				{
					if (  EMSLOT(i) == SLOT_UPPER )
						m_pSkinChar->SetGradeEffect(0,emIndex,ItemClient.GETGRADE_EFFECT(), pd3dDevice, TRUE);
					if (  EMSLOT(i) == SLOT_LOWER )
						m_pSkinChar->SetGradeEffect(1,emIndex,ItemClient.GETGRADE_EFFECT(), pd3dDevice, TRUE);
					if (  EMSLOT(i) == SLOT_HAND )
						m_pSkinChar->SetGradeEffect(2,emIndex,ItemClient.GETGRADE_EFFECT(), pd3dDevice, TRUE);
					if (  EMSLOT(i) == SLOT_FOOT )
						m_pSkinChar->SetGradeEffect(3,emIndex,ItemClient.GETGRADE_EFFECT(), pd3dDevice, TRUE);
				}

				if ( emSex == GLCC_MAN )
				{
					emLeft = CPSIND_M_LEFT;
					emRight = CPSIND_M_RIGHT;
				}else{
					emLeft = CPSIND_W_LEFT;
					emRight = CPSIND_W_RIGHT;
				}

				{
					DxSkinPieceRootData* pPieceDataRoot;
					pPieceDataRoot = DxSkinPieceRootDataContainer::GetInstance().LoadData( pItem->GetCpsFile(emRight) , pd3dDevice , TRUE );
					if ( pPieceDataRoot )
					{
						if ( pPieceDataRoot->GetUseCPS() )
						{
							m_pSkinChar->SetPiece( pPieceDataRoot->GetCpsName().c_str(), pd3dDevice, NULL, ItemClient.GETGRADE_EFFECT(), TRUE );
						}else{
							m_pSkinChar->ResetCPS (  PIECE_RHAND );
						}

						m_pSkinChar->SetCharPieceData( pPieceDataRoot->GetData(), pd3dDevice, pPieceDataRoot->GetBoneLink(), pPieceDataRoot->GetWeaponSlot(),
							(DWORD) PIECE_RHAND, NULL, ItemClient.GETGRADE_EFFECT(), TRUE );
						m_pSkinChar->Clear( PIECE_LHAND );
					}else{
						m_pSkinChar->SetPiece ( pItem->GetCpsFile(emRight), pd3dDevice, NULL, ItemClient.GETGRADE_EFFECT(), TRUE );
					}
				}
				
				{
					DxSkinPieceRootData* pPieceDataRoot;
					pPieceDataRoot = DxSkinPieceRootDataContainer::GetInstance().LoadData( pItem->GetCpsFile(emLeft) , pd3dDevice , TRUE );
					if ( pPieceDataRoot )
					{
						if ( pPieceDataRoot->GetUseCPS() )
						{
							m_pSkinChar->SetPiece( pPieceDataRoot->GetCpsName().c_str(), pd3dDevice, NULL, ItemClient.GETGRADE_EFFECT(), TRUE );
						}else{
							m_pSkinChar->ResetCPS (  PIECE_LHAND );
						}
						m_pSkinChar->SetCharPieceData( pPieceDataRoot->GetData(), pd3dDevice, pPieceDataRoot->GetBoneLink(), pPieceDataRoot->GetWeaponSlot()
							, (DWORD) PIECE_LHAND, NULL, ItemClient.GETGRADE_EFFECT(), TRUE );
					}else{
						m_pSkinChar->SetPiece ( pItem->GetCpsFile(emLeft), pd3dDevice, NULL, ItemClient.GETGRADE_EFFECT(), TRUE );
					}
				}

				{
					if ( pItem->sBasicOp.emItemType != ITEM_VEHICLE )
					{
						DxSkinPieceRootData* pPieceDataRoot;
						pPieceDataRoot = DxSkinPieceRootDataContainer::GetInstance().LoadData( pItem->GetWearingFile(emIndex) , pd3dDevice , TRUE );
						if ( pPieceDataRoot )
						{
							if ( pPieceDataRoot->GetUseCPS() )
							{
								m_pSkinChar->SetPiece( pPieceDataRoot->GetCpsName().c_str(), pd3dDevice, NULL, ItemClient.GETGRADE_EFFECT(), TRUE );
							}
							m_pSkinChar->SetCharPieceData( pPieceDataRoot->GetData(), pd3dDevice, pPieceDataRoot->GetBoneLink(), pPieceDataRoot->GetWeaponSlot()
								, pPieceDataRoot->GetType(), NULL, ItemClient.GETGRADE_EFFECT(), TRUE );
						}else{
							m_pSkinChar->SetPiece ( pItem->GetWearingFile(emIndex), pd3dDevice, NULL, ItemClient.GETGRADE_EFFECT(), TRUE );
						}
					}
				}

				m_pSkinChar->SetColorAll( 0 );
			}
		}
	}
}
EMSLOT CCharacterWindowCharRenderView::GetCurRHandd()
{
	if( IsUseArmSub() ) return SLOT_RHAND_S;
	else				return SLOT_RHAND;
}
EMSLOT CCharacterWindowCharRenderView::GetCurLHandd()
{
	if( IsUseArmSub() ) return SLOT_LHAND_S;
	else				return SLOT_LHAND;
}
SITEM* CCharacterWindowCharRenderView::GET_SLOT_ITEMDATAa ( EMSLOT _slot )
{
	if ( VALID_SLOT_ITEMa(_slot) )
	{
		const SITEMCLIENT &sITEMCLIENT = GET_SLOT_ITEMa ( _slot );

		SITEM* pITEM = GLItemMan::GetInstance().GetItem ( sITEMCLIENT.sNativeID );
		return pITEM;
	}

	return NULL;
}
BOOL CCharacterWindowCharRenderView::VALID_SLOT_ITEMa ( EMSLOT _slot )							
{ 
	if( m_CharData.m_PutOnItems[_slot].sNativeID==NATIVEID_NULL() ) return FALSE;

	if( IsUseArmSub() )
	{
		if( _slot == SLOT_RHAND || _slot == SLOT_LHAND ) return FALSE;
	}
	else
	{
		if( _slot == SLOT_RHAND_S || _slot == SLOT_LHAND_S ) return FALSE;
	}

	return TRUE;
}
void CCharacterWindowCharRenderView::ClearRender()
{
	if ( m_pSkinChar )
		SAFE_DELETE ( m_pSkinChar );

	//m_fDelay = 0.0f;
}