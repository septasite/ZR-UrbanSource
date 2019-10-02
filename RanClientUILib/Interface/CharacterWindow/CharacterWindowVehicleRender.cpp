#include "StdAfx.h"
#include "CharacterWindowVehicleRender.h"

#include "../DxCommon/DxBackUpRendTarget.h"
#include "GLGaeaClient.h"
#include "DxGlobalStage.h"
#include "GLogic.h"
#include "../enginelib/Meshs/DxSkinPieceData.h"
#include "../enginelib/Meshs/DxSkinCharPiece.h"
#include "../enginelib/Meshs/DxSkinPieceRootData.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCharacterWindowVehicleRender::CCharacterWindowVehicleRender () 
	: m_pSkinChar( NULL )
	, m_wLastFace(0)
	, m_wLastHair(0)
	, bRenderVehicle( false )
	, m_vTrans( 0.0f,0.0f,0.0f )
	, m_vRot( 0.0f,0.0f,0.0f )
	, m_fDelay(0.0f)
	, m_fScale(0.0f)
	, m_fFarZ( -50.0f )
{
	D3DXMatrixIdentity ( &m_matTrans );
	sVehicleInfo = SVEHICLEITEMINFO();
}

CCharacterWindowVehicleRender::~CCharacterWindowVehicleRender ()
{
}

void CCharacterWindowVehicleRender::CreateSubControl ()
{
}

void CCharacterWindowVehicleRender::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

HRESULT CCharacterWindowVehicleRender::RestoreDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	HRESULT hr = S_OK;

	if ( m_pSkinChar )
		m_pSkinChar->RestoreDeviceObjects( pd3dDevice );

	hr = CUIGroup::RestoreDeviceObjects( pd3dDevice );
	return hr;
}

HRESULT CCharacterWindowVehicleRender::DeleteDeviceObjects ()
{
	HRESULT hr = S_OK;

	if ( m_pSkinChar )
		m_pSkinChar->DeleteDeviceObjects ();

	hr = CUIGroup::DeleteDeviceObjects ();

	return hr;
}

HRESULT CCharacterWindowVehicleRender::Render ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	HRESULT hr = S_OK;

	if ( !m_pSkinChar )
	{
		CreateModel( pd3dDevice );
	}else{

		if ( m_fDelay < 0.2 ) return S_OK;

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

		D3DXVECTOR3 vFromPt		= D3DXVECTOR3( 0.0f, 0.3f, m_fFarZ );
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

HRESULT CCharacterWindowVehicleRender::FrameMove( LPDIRECT3DDEVICEQ pd3dDevice, float fTime, float fElapsedTime )
{
	HRESULT hr = S_OK;

	m_fDelay += fElapsedTime;

	if ( m_pSkinChar )
	{
		m_pSkinChar->FrameMove ( fTime, fElapsedTime, TRUE, FALSE, FALSE );
	}

	GLCharacter* pChar = GLGaeaClient::GetInstance().GetCharacter();
	if ( pChar )
	{
		if( pChar->m_bNeedUISuitUpdate )
		{
			UpdateSuit( pd3dDevice );
		}
	}

	UpdateAnimation();

	hr = CUIGroup::FrameMove( pd3dDevice, fTime, fElapsedTime );
	return hr;
}

void CCharacterWindowVehicleRender::CreateModel( LPDIRECT3DDEVICEQ pd3dDevice )
{
	if ( !bRenderVehicle )	return;

	GLCharacter* pChar = GLGaeaClient::GetInstance().GetCharacter();
	if ( !pChar )		return;

	EMCHARINDEX emIndex = CharClassToIndex( DxGlobalStage::GetInstance().GetGameStage()->GetCharJoinData().m_CharData2.m_emClass );
	DxSkinCharData* pSkinChar = DxSkinCharDataContainer::GetInstance().LoadData ( GLCONST_CHAR::szCharSkin[emIndex], pd3dDevice, true  );

	if ( !pSkinChar )	return;

	SAFE_DELETE(m_pSkinChar);
	m_pSkinChar = new DxSkinChar;
	m_pSkinChar->InitDeviceObjects( pd3dDevice );
	m_pSkinChar->SetCharData ( pSkinChar, pd3dDevice );
	m_pSkinChar->SELECTANI( AN_PLACID, AN_SUB_NONE );

	UpdateSuit( pd3dDevice );

	m_fDelay = 0.0f;
}

void CCharacterWindowVehicleRender::RenderModel( LPDIRECT3DDEVICEQ pd3dDevice )
{
	if ( !bRenderVehicle )	return;

	if ( m_pSkinChar )
	{
		D3DXMATRIX matTrans, matScale, matRot;

		D3DXMatrixScaling( &matScale, m_fScale, m_fScale, m_fScale );
		D3DXMatrixTranslation( &matTrans, m_vTrans.x, m_vTrans.y, m_vTrans.z );
		D3DXMatrixRotationYawPitchRoll ( &matRot, m_vRot.x, m_vRot.y, m_vRot.z );

		m_matTrans = matScale*matRot*matTrans;

		if ( sVehicleInfo.m_emTYPE == VEHICLE_TYPE_BOARD ||  !m_pSkinChar->m_pSkinVehicle )
		{
			m_pSkinChar->Render( pd3dDevice, m_matTrans );
		}
		else if ( m_pSkinChar->m_pSkinVehicle )
		{
			m_pSkinChar->RenderVehicle( pd3dDevice, m_matTrans );
			DxBoneTrans *pBoneCur = NULL;
			pBoneCur = m_pSkinChar->m_pSkinVehicle->GetSkeleton()->FindBone( m_pSkinChar->m_pSkinVehicle->m_strChar_Font.c_str() );
			if ( pBoneCur )
			{
				D3DXVECTOR3			vRotation_Font, vTransform_Font;

				vRotation_Font = m_pSkinChar->m_pSkinVehicle->m_vRotation_Font;
				vTransform_Font = m_pSkinChar->m_pSkinVehicle->m_vTransform_Font;

				D3DXMATRIXA16	matLocalRot, matScale, matRot;
				matRot = pBoneCur->matCombined;
				D3DXMatrixIdentity( &matScale );

				D3DXMatrixRotationYawPitchRoll( &matScale, vRotation_Font.x, vRotation_Font.y, vRotation_Font.z );

				D3DXMatrixMultiply( &matLocalRot, &matScale, &matRot );

				D3DXVECTOR3	vVelocity;
				D3DXVec3TransformNormal ( &vVelocity, &vTransform_Font, &matRot );
				matLocalRot._41 += vVelocity.x;
				matLocalRot._42 += vVelocity.y;
				matLocalRot._43 += vVelocity.z;

				m_pSkinChar->Render ( pd3dDevice, matLocalRot );
			}
		}
	}
}

void CCharacterWindowVehicleRender::UpdateSuit( LPDIRECT3DDEVICEQ pd3dDevice )
{
	if ( !m_pSkinChar )	return;

	GLCharacter* pChar = GLGaeaClient::GetInstance().GetCharacter();
	if ( !pChar )		return;

	EMCHARINDEX emIndex = CharClassToIndex( pChar->m_emClass );
	DxSkinCharData* pSkinChar = DxSkinCharDataContainer::GetInstance().FindData ( GLCONST_CHAR::szCharSkin[emIndex] );
	if ( !pSkinChar )	return;

	const GLCONST_CHARCLASS &sCONST = GLCONST_CHAR::cCONSTCLASS[emIndex];

	WORD m_wFace = pChar->m_wFace;
	WORD m_wHair = pChar->m_wHair;
	WORD m_wHairColor = pChar->m_wHairColor;

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
		if( !pChar->IsCurUseArm( EMSLOT(i) ) ) continue;

		SITEMCUSTOM ItemCustom = pChar->m_PutOnItems[i];
		if ( i == SLOT_LHAND  )	ItemCustom = pChar->m_PutOnItems[SLOT_RHAND];
		if ( i == SLOT_LHAND_S  )	ItemCustom = pChar->m_PutOnItems[SLOT_RHAND_S];

		SNATIVEID nidITEM = ItemCustom.nidDISGUISE;
		if ( nidITEM==SNATIVEID(false) )	nidITEM = ItemCustom.sNativeID;

		if ( i == SLOT_VEHICLE )
			nidITEM = sVehicleID;

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

						EMSLOT emRHand = GLGaeaClient::GetInstance().GetCharacter()->GetCurRHand();
						SITEM* pRHAND = GLGaeaClient::GetInstance().GetCharacter()->GET_SLOT_ITEMDATA ( emRHand );
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
						m_pSkinChar->SetGradeEffect(0,emIndex,ItemCustom.GETGRADE_EFFECT(), pd3dDevice, TRUE);
					if (  EMSLOT(i) == SLOT_LOWER )
						m_pSkinChar->SetGradeEffect(1,emIndex,ItemCustom.GETGRADE_EFFECT(), pd3dDevice, TRUE);
					if (  EMSLOT(i) == SLOT_HAND )
						m_pSkinChar->SetGradeEffect(2,emIndex,ItemCustom.GETGRADE_EFFECT(), pd3dDevice, TRUE);
					if (  EMSLOT(i) == SLOT_FOOT )
						m_pSkinChar->SetGradeEffect(3,emIndex,ItemCustom.GETGRADE_EFFECT(), pd3dDevice, TRUE);
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
							m_pSkinChar->SetPiece( pPieceDataRoot->GetCpsName().c_str(), pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), TRUE );
						}else{
							m_pSkinChar->ResetCPS (  PIECE_RHAND );
						}

						m_pSkinChar->SetCharPieceData( pPieceDataRoot->GetData(), pd3dDevice, pPieceDataRoot->GetBoneLink(), pPieceDataRoot->GetWeaponSlot(),
							(DWORD) PIECE_RHAND, NULL, ItemCustom.GETGRADE_EFFECT(), TRUE );
						m_pSkinChar->Clear( PIECE_LHAND );
					}else{
						m_pSkinChar->SetPiece ( pItem->GetCpsFile(emRight), pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), TRUE );
					}
				}

				{
					DxSkinPieceRootData* pPieceDataRoot;
					pPieceDataRoot = DxSkinPieceRootDataContainer::GetInstance().LoadData( pItem->GetCpsFile(emLeft) , pd3dDevice , TRUE );
					if ( pPieceDataRoot )
					{
						if ( pPieceDataRoot->GetUseCPS() )
						{
							m_pSkinChar->SetPiece( pPieceDataRoot->GetCpsName().c_str(), pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), TRUE );
						}else{
							m_pSkinChar->ResetCPS (  PIECE_LHAND );
						}
						m_pSkinChar->SetCharPieceData( pPieceDataRoot->GetData(), pd3dDevice, pPieceDataRoot->GetBoneLink(), pPieceDataRoot->GetWeaponSlot()
							, (DWORD) PIECE_LHAND, NULL, ItemCustom.GETGRADE_EFFECT(), TRUE );
					}else{
						m_pSkinChar->SetPiece ( pItem->GetCpsFile(emLeft), pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), TRUE );
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
								m_pSkinChar->SetPiece( pPieceDataRoot->GetCpsName().c_str(), pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), TRUE );
							}
							m_pSkinChar->SetCharPieceData( pPieceDataRoot->GetData(), pd3dDevice, pPieceDataRoot->GetBoneLink(), pPieceDataRoot->GetWeaponSlot()
								, pPieceDataRoot->GetType(), NULL, ItemCustom.GETGRADE_EFFECT(), TRUE );
						}else{
							m_pSkinChar->SetPiece ( pItem->GetWearingFile(emIndex), pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), TRUE );
						}
					}
					else
					{
						if ( pItem->sVehicle.emVehicleType == VEHICLE_TYPE_BOARD )
						{
							m_pSkinChar->m_fLengthSRC = 150.0f;
						}
						else
						{
							m_pSkinChar->m_fLengthSRC = 30.0f;
						}
						DxSkinVehicleData* pVehicleData;
						pVehicleData = DxSkinVehicleDataContainer::GetInstance().LoadData( pItem->GetWearingFile(emIndex), pd3dDevice, TRUE );
						if ( pVehicleData )
						{
							m_pSkinChar->SetVehicleData( pVehicleData, pd3dDevice, TRUE );
							for( DWORD iLoopPart = ACCE_TYPE_SKIN ; iLoopPart < ACCE_TYPE_SIZE ; iLoopPart++ )
							{
								SITEM* pItemPart = GLItemMan::GetInstance().GetItem ( sVehicleInfo.m_PutOnItems[iLoopPart].sNativeID );

								if ( pItemPart )
								{
									if ( m_pSkinChar->m_pSkinVehicle )
									{
										m_pSkinChar->m_pSkinVehicle->SetPiece( pItemPart->GetVpsFile(), pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), TRUE );
									}
								}
							}
							//m_pSkinChar->m_pSkinVehicle->SetColor( sVehicleInfo. );
							m_pSkinChar->SetColorAll( 32767 );
						}
						else
						{
							m_pSkinChar->SetPiece ( pItem->GetWearingFile(emIndex), pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), TRUE );
						}
					}
				}

				m_pSkinChar->SetColorAll( 0 );
			}
		}
	}


	GLGaeaClient::GetInstance().GetCharacter()->m_bNeedUISuitUpdate = false;
}

void CCharacterWindowVehicleRender::ClearRender()
{
	if ( m_pSkinChar )
	{
		SAFE_DELETE ( m_pSkinChar );
		bRenderVehicle = false;
		m_fDelay = 0.0f;
	}
}

void CCharacterWindowVehicleRender::RenderVehicle( SNATIVEID sID, SVEHICLEITEMINFO sInfo )
{
	SITEM* pItem = GLItemMan::GetInstance().GetItem( sID );
	if ( pItem )
	{
		if ( sVehicleID != sID )
		{
			ClearRender();
		}

		sVehicleInfo = sInfo;
		sVehicleID = pItem->sBasicOp.sNativeID;
		bRenderVehicle = true;
	}else{
		ClearRender();
	}
}

void CCharacterWindowVehicleRender::UpdateAnimation()
{
	SITEM* pItem = GLItemMan::GetInstance().GetItem( sVehicleID );
	if ( pItem && m_pSkinChar )
	{
		EMANI_MAINTYPE emMain = AN_PLACID;
		EMANI_SUBTYPE emSub = AN_SUB_NONE;
		BOOL bRun = RANPARAM::bVehicleRenderMove;

		switch ( pItem->sVehicle.emVehicleType )
		{
		case VEHICLE_TYPE_BOARD:
			{
				emMain = bRun? AN_RUN : AN_PLACID;
				emSub = AN_SUB_HOVERBOARD;

				m_vTrans = D3DXVECTOR3( 0.0f, -17.0f, 0.0f );
				m_vRot = D3DXVECTOR3( -0.8f, -0.1f, 0.1f );
				m_fScale = 1.0f;
				m_fFarZ = -38.0f;
			}break;
		case VEHICLE_TYPE_SCUTER:
		case VEHICLE_TYPE_BIKE_BT5:
		case VEHICLE_TYPE_BIKE_BT7:
		case VEHICLE_TYPE_BIKE_BT9:
		case VEHICLE_TYPE_BIKE_RARE:
		case VEHICLE_TYPE_BIKE_JOKER:
		case VEHICLE_TYPE_BIKE_XMAS:
		case VEHICLE_TYPE_BIKE_GHOST:
			{
				GLCharacter* pChar = GLGaeaClient::GetInstance().GetCharacter();
				if ( pChar )
				{
					emMain = pChar->m_sVehicle.GetVehicleMainAni( pItem->sVehicle.emVehicleType );
					emSub = pChar->m_sVehicle.GetVehicleSubAni( bRun? AN_RUN : AN_PLACID, false );
				}
				
				m_vTrans = D3DXVECTOR3( 0.0f, -8.0f, 12.0f );
				m_vRot = D3DXVECTOR3( 0.8f, -0.2f, -0.2f );
				m_fScale = 1.0f;
				m_fFarZ = -38.0f;
			}break;

		case VEHICLE_TYPE_BIKE_FERRARI:
		case VEHICLE_TYPE_BIKE_REAR:
			{
				GLCharacter* pChar = GLGaeaClient::GetInstance().GetCharacter();
				if ( pChar )
				{
					emMain = pChar->m_sVehicle.GetVehicleMainAni( pItem->sVehicle.emVehicleType );
					emSub = pChar->m_sVehicle.GetVehicleSubAni( bRun? AN_RUN : AN_PLACID, false );
				}

				m_vTrans = D3DXVECTOR3( 0.0f, -8.0f, 22.0f );
				m_vRot = D3DXVECTOR3( 0.8f, -0.2f, -0.2f );
				m_fScale = 1.0f;
				m_fFarZ = -45.0f;
			}break;
		};

		if ( m_pSkinChar && ( m_pSkinChar->GETCURMTYPE() != emMain || m_pSkinChar->GETCURSTYPE() != emSub ) )
		{
			m_pSkinChar->SELECTANI( emMain, emSub );

			if ( m_pSkinChar->m_pSkinVehicle )	
			{
				m_pSkinChar->m_pSkinVehicle->SELECTANI( bRun? ANI_VEHICLE_RUN : ANI_VEHICLE_STAY , AN_SUB_NONE );
			}
		}

		EMANI_MAINTYPE emMainVehicle = bRun? ANI_VEHICLE_RUN : ANI_VEHICLE_STAY;
		EMANI_SUBTYPE emSubVehicle = AN_SUB_NONE;

		if ( m_pSkinChar->m_pSkinVehicle && ( m_pSkinChar->m_pSkinVehicle->GETCURMTYPE() != emMainVehicle || m_pSkinChar->m_pSkinVehicle->GETCURSTYPE() != emSubVehicle ) )	
		{
			m_pSkinChar->m_pSkinVehicle->SELECTANI( emMainVehicle, emSubVehicle );
		}

	};
}