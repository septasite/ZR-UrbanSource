#include "StdAfx.h"
#include "./DxCharSham.h"
#include "./G-Logic/GLogicData.h"
#include "./G-Logic/GLItemMan.h"
#include "DxEffectMan.h"
#include "DxEffcharData.h"

#include "../EngineLib/DxCommon/DxMethods.h"
#include "../EngineLib/DxCommon/DxShadowMap.h"
#include "../EngineLib/DxCommon/EditMeshs.h"
#include "../EngineLib/DxEffect/DxEffectMan.h"
#include "../EngineLib/DxEffect/Single/DxEffGroupPlayer.h"
#include "../enginelib/Meshs/DxSkinPieceData.h"
#include "../enginelib/Meshs/DxSkinCharPiece.h"
#include "../enginelib/Meshs/DxSkinPieceRootData.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

DxCharSham::DxCharSham(void) :
	m_pd3dDevice(NULL),
	m_pSkinChar(NULL),

	m_vDir(D3DXVECTOR3(0,0,-1)),
	m_vDirOrig(D3DXVECTOR3(0,0,-1)),
	m_vPos(D3DXVECTOR3(0,0,0)),

	m_nID(0),
	m_bSelect(FALSE),
	m_bEffect(FALSE),

	m_fAge(),
	m_Action(GLAT_IDLE),
	m_fIdleTime(0.0f),
	m_bPeaceZone(TRUE),
	m_bIdleReserv(FALSE),

	m_vMaxOrg(3,18,3),
	m_vMinOrg(-3,0,-3),

	m_vMax(3,18,3),
	m_vMin(-3,0,-3),

	m_dwRevData(NULL),
	m_bNeedData(FALSE),

	m_fDelayFreeAnim(0.0f)//add vcf
{
}

DxCharSham::~DxCharSham(void)
{
	SAFE_DELETE(m_pSkinChar);
}

void DxCharSham::GetAABB ( D3DXVECTOR3 &vMax, D3DXVECTOR3 &vMin )
{
	vMax = m_vMax;
	vMin = m_vMin;
}

HRESULT DxCharSham::SetCharInfo ( const SCHARINFO_LOBBY &CharInfo, const BOOL bThread )
{
	m_dwRevData |= RECEIVE_CHARDATA;

	m_CharInfo = CharInfo;

	//	Note : 케릭터의 외형을 설정.
	StringCchCopy ( GLCHARLOGIC::m_szName, CHAR_SZNAME, m_CharInfo.m_szName );
	GLCHARLOGIC::m_emClass = m_CharInfo.m_emClass;
	GLCHARLOGIC::m_wSchool = m_CharInfo.m_wSchool;
	GLCHARLOGIC::m_wHair = m_CharInfo.m_wHair;
	GLCHARLOGIC::m_wHairColor = m_CharInfo.m_wHairColor;
	GLCHARLOGIC::m_wFace = m_CharInfo.m_wFace;

	GLCHARLOGIC::m_wLevel = m_CharInfo.m_wLevel;
	GLCHARLOGIC::m_sStats = m_CharInfo.m_sStats;

//  LOBY data 수정
//	memcpy ( GLCHARLOGIC::m_PutOnItems, m_CharInfo.m_PutOnItems, sizeof(SITEMCUSTOM)*SLOT_TSIZE );

	for ( int i = 0; i < SLOT_TSIZE; ++i )
	{
		GLCHARLOGIC::m_PutOnItems[i].Assign(  m_CharInfo.m_PutOnItems[i] );
	}


	GLCHARLOGIC::INIT_DATA ( FALSE, FALSE );

	//	Note : 케릭터의 외형을 설정.
	EMCHARINDEX emIndex = CharClassToIndex(m_CharInfo.m_emClass);

	DxSkinCharData* pSkinChar = DxSkinCharDataContainer::GetInstance().LoadData( GLCONST_CHAR::szCharSkin[emIndex], m_pd3dDevice, bThread );
	if ( !pSkinChar )	return E_FAIL;

	SAFE_DELETE(m_pSkinChar);
	m_pSkinChar = new DxSkinChar;
	m_pSkinChar->SetCharData ( pSkinChar, m_pd3dDevice );
	if ( m_pd3dDevice )	UpdateSuit ();

	//	Note : 에니메이션 초기화.
	//
	m_pSkinChar->SELECTANI ( AN_PLACID, AN_SUB_NONE );

	return S_OK;
}

HRESULT DxCharSham::Create ( D3DXVECTOR3 pvPos, LPDIRECT3DDEVICEQ pd3dDevice, const BOOL bThread, BOOL bNeedData, int nID )
{
	m_pd3dDevice = pd3dDevice;

	m_nID = nID;
	m_bNeedData = bNeedData;

	//	Note : 케릭터의 외형을 설정.
	EMCHARINDEX emIndex = CharClassToIndex(m_CharInfo.m_emClass);
	DxSkinCharData* pSkinChar = DxSkinCharDataContainer::GetInstance().LoadData( GLCONST_CHAR::szCharSkin[emIndex], pd3dDevice, bThread );
	GASSERT(pSkinChar&&"DxCharSham::Create()->DxSkinCharData::Load()");
	if ( !pSkinChar )	return E_FAIL;

	SAFE_DELETE(m_pSkinChar);
	m_pSkinChar = new DxSkinChar;

	m_pSkinChar->SetCharData( pSkinChar, pd3dDevice );
	UpdateSuit ();

	//	Note : 이동 제어 초기화.
	if ( pvPos )	m_vPos = pvPos;

	return S_OK;
}
// added by   | 8-18-2012 | ABL-ABF-SELECTCHARPAGE
HRESULT DxCharSham::UpdateSuit ()
{
	GASSERT(m_pd3dDevice);

	if ( !m_pSkinChar )										
		return S_FALSE;

	EMCHARINDEX emIndex = CharClassToIndex(m_emClass);
	DxSkinCharData* pSkinChar = DxSkinCharDataContainer::GetInstance().FindData ( GLCONST_CHAR::szCharSkin[emIndex] );
	if ( !pSkinChar )	return E_FAIL;

	const GLCONST_CHARCLASS &sCONST = GLCONST_CHAR::cCONSTCLASS[emIndex];

		if ( sCONST.dwHEADNUM > m_wFace )
		{
			std::string strHEAD_CPS = sCONST.strHEAD_CPS[m_wFace];
		
			PDXCHARPART pCharPart = NULL;
			pCharPart = m_pSkinChar->GetPiece(PIECE_HEAD);		//	현재 장착 스킨.

			if ( pCharPart && strcmp(strHEAD_CPS.c_str(),pCharPart->m_szFileName) )
			{
				DxSkinPieceRootData* pPieceDataRoot;
				pPieceDataRoot = DxSkinPieceRootDataContainer::GetInstance().LoadData( strHEAD_CPS.c_str() , m_pd3dDevice , TRUE );
				if ( pPieceDataRoot )
				{
					if ( pPieceDataRoot->GetUseCPS() )
					{
						m_pSkinChar->SetPiece( pPieceDataRoot->GetCpsName().c_str(), m_pd3dDevice, 0x0, 0, TRUE );
					}
					m_pSkinChar->SetCharPieceData( pPieceDataRoot->GetData()
													, m_pd3dDevice
													, pPieceDataRoot->GetBoneLink()
													, pPieceDataRoot->GetWeaponSlot()
													, pPieceDataRoot->GetType()
													, 0x0
													, 0
													, TRUE );
				}else{
					m_pSkinChar->SetPiece ( strHEAD_CPS.c_str(), m_pd3dDevice, 0x0, 0, TRUE );
				}
			}
		}

	if ( sCONST.dwHAIRNUM > m_wHair )
		{
			std::string strHAIR_CPS = sCONST.strHAIR_CPS[m_wHair];
		
			PDXCHARPART pCharPart = NULL;
			pCharPart = m_pSkinChar->GetPiece(PIECE_HAIR);		//	현재 장착 스킨.

			if ( pCharPart && strcmp(strHAIR_CPS.c_str(),pCharPart->m_szFileName) )
			{
				DxSkinPieceRootData* pPieceDataRoot;
				pPieceDataRoot = DxSkinPieceRootDataContainer::GetInstance().LoadData( strHAIR_CPS.c_str() , m_pd3dDevice , TRUE );
				if ( pPieceDataRoot )
				{
					if ( pPieceDataRoot->GetUseCPS() )
					{
						m_pSkinChar->SetPiece( pPieceDataRoot->GetCpsName().c_str(), m_pd3dDevice, 0x0, 0, TRUE );
					}
					m_pSkinChar->SetCharPieceData( pPieceDataRoot->GetData()
													, m_pd3dDevice
													, pPieceDataRoot->GetBoneLink()
													, pPieceDataRoot->GetWeaponSlot()
													, pPieceDataRoot->GetType()
													, 0x0
													, 0
													, TRUE );
				}else{
					m_pSkinChar->SetPiece ( strHAIR_CPS.c_str(), m_pd3dDevice, 0x0, 0, TRUE );
				}
			}
		}

	// 헤어컬러 세팅
		m_pSkinChar->SetHairColor( m_wHairColor );

	// 장착한 아이템 업데이트
	for ( int i=0; i<SLOT_NSIZE_S_2; i++ )
	{	
		// 현재 장착중인 무기가 아니면 넘어간다.
		if( !IsCurUseArm( EMSLOT(i) ) ) continue;

		SITEMCUSTOM &ItemCustom = m_PutOnItems[i];

		// 복장 아이템
		SNATIVEID nidITEM = ItemCustom.nidDISGUISE;
		if ( nidITEM==SNATIVEID(false) )	nidITEM = ItemCustom.sNativeID;

		if ( !m_bVehicle && i == SLOT_VEHICLE  ) nidITEM = SNATIVEID(false);

		if ( nidITEM == SNATIVEID(false) )
		{
			//	Note : 기본 스킨과 지금 장착된 스킨이 틀릴 경우.
			//	SLOT->PIECE.
			PDXSKINPIECE pSkinPiece = NULL;	//	기본 스킨.
			PDXCHARPART pCharPart = NULL;	//	현재 장착 스킨.

			EMPIECECHAR emPiece = SLOT_2_PIECE(EMSLOT(i));
			if ( emPiece!=PIECE_SIZE )
			{
				pSkinPiece = pSkinChar->GetPiece(emPiece);	//	기본 스킨.
				pCharPart = m_pSkinChar->GetPiece(emPiece);	//	현재 장착 스킨.
			}

			if ( pSkinPiece )
			{
				if ( pCharPart && strcmp(pSkinPiece->m_szFileName,pCharPart->m_szFileName) )
					{
					//MessageBox(0,pSkinPiece->m_szFileName,pCharPart->m_szFileName,0);
					DxSkinPieceRootData* pPieceDataRoot;
					pPieceDataRoot = DxSkinPieceRootDataContainer::GetInstance().LoadData( pSkinPiece->m_szFileName , m_pd3dDevice , TRUE );
					if ( pPieceDataRoot )
					{
						if ( pPieceDataRoot->GetUseCPS() )
						{
							m_pSkinChar->SetPiece( pPieceDataRoot->GetCpsName().c_str(), m_pd3dDevice, 0X0, 0, TRUE );
						}
						else
						{
							EMPIECECHAR emPiece_a = SLOT_2_PIECE(EMSLOT(i));
							if ( emPiece_a!=PIECE_SIZE )
							{
								if (  pSkinChar->GetPiece(emPiece_a) ) m_pSkinChar->SetPiece ( pSkinChar->GetPiece(emPiece_a )->m_szFileName, m_pd3dDevice, NULL, 0, TRUE );
							}
						}
						m_pSkinChar->SetCharPieceData( pPieceDataRoot->GetData()
														, m_pd3dDevice
														, pPieceDataRoot->GetBoneLink()
														, pPieceDataRoot->GetWeaponSlot()
														, pPieceDataRoot->GetType()
														, 0x0
														, 0
														, TRUE );
					}
					else
					{
						m_pSkinChar->SetPiece ( pSkinPiece->m_szFileName, m_pd3dDevice, 0X0, 0, TRUE );
						m_pSkinChar->ResetABL ( emPiece ); //clear abl when you remove an item
					}
				}
				else
				{
					m_pSkinChar->ResetABL ( emPiece ); //clear abl when you remove an item
				}
				if (  emPiece == PIECE_UPBODY )
				{
					m_pSkinChar->ResetPiece(PIECE_EFF_UPBODY);
				}
				else if (  emPiece == PIECE_LOBODY )
				{
					m_pSkinChar->ResetPiece(PIECE_EFF_LOBODY);
				}
				else if (  emPiece == PIECE_GLOVE )
				{
					m_pSkinChar->ResetPiece(PIECE_EFF_GLOVE);
				}
				else if (  emPiece == PIECE_FOOT )
				{
					m_pSkinChar->ResetPiece(PIECE_EFF_FOOT);
				}
			}
			else
			{
				if ( pCharPart ) //add abl
				{
					if ( m_pSkinChar->m_pSkinCharPiece[PIECE_RHAND] && emPiece != PIECE_LHAND )
					{
						m_pSkinChar->ResetPiece(emPiece);
					}
					else
					{
						if ( emPiece != PIECE_LHAND )
							m_pSkinChar->ResetPiece(emPiece);

						EMSLOT emRHand = GetCurRHand();
						SITEM* pRHAND = GET_SLOT_ITEMDATA ( emRHand );
						if ( pRHAND )// dual cps fix
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
						}
						else
						{
							if ( !m_pSkinChar->m_pSkinCharPiece[PIECE_RHAND] && emPiece == PIECE_LHAND )
								m_pSkinChar->ResetPiece(emPiece);
						}
						//add upgradeeffectniwadark
						if (  emPiece == PIECE_UPBODY )
						{
						m_pSkinChar->ResetPiece(PIECE_EFF_UPBODY);
						}
						else if (  emPiece == PIECE_LOBODY )
						{
						m_pSkinChar->ResetPiece(PIECE_EFF_LOBODY);
						}
						else if (  emPiece == PIECE_GLOVE )
						{
						m_pSkinChar->ResetPiece(PIECE_EFF_GLOVE);
						}
						else if (  emPiece == PIECE_FOOT )
						{
						m_pSkinChar->ResetPiece(PIECE_EFF_FOOT);
						}
					}
				}
			}
		}
		// 유효하면
		else
		{
			SITEM* pItem = GLItemMan::GetInstance().GetItem ( nidITEM );
			if ( pItem ) 
			{
				EMCHARCLASS emSex = CharClassGetSex( emIndex );
				EMCPSINDEX	emLeft = CPSIND_NULL;
				EMCPSINDEX	emRight = CPSIND_NULL;

				{//add upgradeeffect
					if (  EMSLOT(i) == SLOT_UPPER )
					{
						m_pSkinChar->SetGradeEffect(0,emIndex,ItemCustom.GETGRADE_EFFECT(),m_pd3dDevice,TRUE);
					}
					if (  EMSLOT(i) == SLOT_LOWER )
					{
						m_pSkinChar->SetGradeEffect(1,emIndex,ItemCustom.GETGRADE_EFFECT(),m_pd3dDevice,TRUE);
					}
					if (  EMSLOT(i) == SLOT_HAND )
					{
						m_pSkinChar->SetGradeEffect(2,emIndex,ItemCustom.GETGRADE_EFFECT(),m_pd3dDevice,TRUE);
					}
					if (  EMSLOT(i) == SLOT_FOOT )
					{
						m_pSkinChar->SetGradeEffect(3,emIndex,ItemCustom.GETGRADE_EFFECT(),m_pd3dDevice,TRUE);
					}
				}

				if ( emSex == GLCC_MAN )
				{
					emLeft = CPSIND_M_LEFT;
					emRight = CPSIND_M_RIGHT;
				}else{
					emLeft = CPSIND_W_LEFT;
					emRight = CPSIND_W_RIGHT;
				}
				//if ( emRight != CPSIND_NULL )
				{
					DxSkinPieceRootData* pPieceDataRoot;
					pPieceDataRoot = DxSkinPieceRootDataContainer::GetInstance().LoadData( pItem->GetCpsFile(emRight) , m_pd3dDevice , TRUE );
					if ( pPieceDataRoot )
					{
						if ( pPieceDataRoot->GetUseCPS() )
						{
							m_pSkinChar->SetPiece( pPieceDataRoot->GetCpsName().c_str(), m_pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), TRUE );
						}
						else
						{
							m_pSkinChar->ResetCPS (  PIECE_RHAND );//remove existing cps when the abl data dont have cps
						}
						m_pSkinChar->SetCharPieceData( pPieceDataRoot->GetData()
														, m_pd3dDevice
														, pPieceDataRoot->GetBoneLink()
														, pPieceDataRoot->GetWeaponSlot()
														, (DWORD) PIECE_RHAND
														, NULL
														, ItemCustom.GETGRADE_EFFECT()
														, TRUE );
						m_pSkinChar->Clear( PIECE_LHAND );
					}else{
						m_pSkinChar->SetPiece ( pItem->GetCpsFile(emRight), m_pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), TRUE );
					}
				}
				//if ( emLeft != CPSIND_NULL )
				{
					DxSkinPieceRootData* pPieceDataRoot;
					pPieceDataRoot = DxSkinPieceRootDataContainer::GetInstance().LoadData( pItem->GetCpsFile(emLeft) , m_pd3dDevice , TRUE );
					if ( pPieceDataRoot )
					{
						if ( pPieceDataRoot->GetUseCPS() )
						{
							m_pSkinChar->SetPiece( pPieceDataRoot->GetCpsName().c_str(), m_pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), TRUE );
						}
						{
							m_pSkinChar->ResetCPS (  PIECE_LHAND );//remove existing cps when the abl data dont have cps
						}
						m_pSkinChar->SetCharPieceData( pPieceDataRoot->GetData()
														, m_pd3dDevice
														, pPieceDataRoot->GetBoneLink()
														, pPieceDataRoot->GetWeaponSlot()
														, (DWORD) PIECE_LHAND
														, NULL
														, ItemCustom.GETGRADE_EFFECT()
														, TRUE );
					}else{
						m_pSkinChar->SetPiece ( pItem->GetCpsFile(emLeft), m_pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), TRUE );
					}
				}

				//if ( !m_pSkinChar->m_pSkinCharPiece[ PIECE_LHAND ] && !m_pSkinChar->m_pSkinCharPiece[ PIECE_RHAND ] )
				{
					if ( pItem->sBasicOp.emItemType != ITEM_VEHICLE )
					{
						DxSkinPieceRootData* pPieceDataRoot;
						pPieceDataRoot = DxSkinPieceRootDataContainer::GetInstance().LoadData( pItem->GetWearingFile(emIndex) , m_pd3dDevice , TRUE );
						if ( pPieceDataRoot )
						{
							if ( pPieceDataRoot->GetUseCPS() )
							{
								m_pSkinChar->SetPiece( pPieceDataRoot->GetCpsName().c_str(), m_pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), TRUE );
							}
							else
							{
								EMPIECECHAR emPiece_a = SLOT_2_PIECE(EMSLOT(i));
								if ( emPiece_a!=PIECE_SIZE )
								{
									if (  pSkinChar->GetPiece(emPiece_a) ) m_pSkinChar->SetPiece ( pSkinChar->GetPiece(emPiece_a )->m_szFileName, m_pd3dDevice, NULL, 0, TRUE );
								}	
							}
							m_pSkinChar->SetCharPieceData( pPieceDataRoot->GetData()
															, m_pd3dDevice
															, pPieceDataRoot->GetBoneLink()
															, pPieceDataRoot->GetWeaponSlot()
															, pPieceDataRoot->GetType()
															, NULL
															, ItemCustom.GETGRADE_EFFECT()
															, TRUE );
						}
						else
						{
							m_pSkinChar->SetPiece ( pItem->GetWearingFile(emIndex), m_pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), TRUE );
						}
					}

					else
					{
					m_pSkinChar->SetPiece ( pItem->GetWearingFile(emIndex), m_pd3dDevice, NULL, ItemCustom.GETGRADE_EFFECT(), TRUE );
					}

					}
						// Mike915 Element on ABL Fixed
						{
						SITEM* pItemData = GLItemMan::GetInstance().GetItem ( ItemCustom.sNativeID );
						std::string strSelfBodyEffect = "";
						strSelfBodyEffect = pItemData->GetSelfBodyEffect();

						/*if ( strSelfBodyEffect.empty() ){
							EMSTATE_BLOW emBLOW = pItemData->sSuitOp.sBLOW.emTYPE;
							if ( emBLOW == 1 )  strSelfBodyEffect = "elect.effskin";
							else if ( emBLOW == 3 ) strSelfBodyEffect = "special.effskin";
							else if ( emBLOW == 4 ) strSelfBodyEffect = "fire.effskin";
							else if ( emBLOW == 5 ) strSelfBodyEffect = "ice.effskin";
							else if ( emBLOW == 7 ) strSelfBodyEffect = "poison.effskin";
						}*/

					if ( !strSelfBodyEffect.empty())
						{
						if ( m_pSkinChar->m_pSkinCharPiece[PIECE_LHAND] )
						{
							DxEffcharDataMan::GetInstance().PutEffect ( m_pSkinChar->m_pSkinCharPiece[PIECE_LHAND]->GetPiece(0), strSelfBodyEffect.c_str(), &m_vDir );
						}
						if ( m_pSkinChar->m_pSkinCharPiece[PIECE_RHAND] )
						{
							DxEffcharDataMan::GetInstance().PutEffect ( m_pSkinChar->m_pSkinCharPiece[PIECE_RHAND]->GetPiece(0), strSelfBodyEffect.c_str(), &m_vDir );
						}
					}
				}
			}
		}
	}

	return S_OK;
}

void DxCharSham::SetSelect ( BOOL bSel, BOOL bReserv )	
{ 
	m_bSelect = bSel;

	if ( m_bSelect )
	{
		if( m_Action == GLAT_IDLE )
			TurnAction ( GLAT_CONFT_END );

		m_bIdleReserv = FALSE;
	}
	else
	{
		if( bReserv )
			m_bIdleReserv = TRUE;
		else
			TurnAction ( GLAT_IDLE );
	}
}

void DxCharSham::TurnAction ( EMACTIONTYPE toAction )
{
	//	Note : 이전 액션 취소.
	//
	//switch ( m_Action )
	//{
	//case GLAT_IDLE:			break;
	//case GLAT_CONFT_END:	break;
	//case GLAT_ATTACK:		break;
	//default:				break;
	//};

	m_Action = toAction;

	//	Note : 액션 초기화.
	//
	switch ( m_Action )
	{
	case GLAT_IDLE:
		m_bIdleReserv = FALSE;
		m_bPeaceZone = TRUE;
		break;

	case GLAT_CONFT_END:
		m_bPeaceZone = FALSE;
		break;

	case GLAT_ATTACK:
		m_bPeaceZone = FALSE;
		m_fIdleTime = 0.0f;
		break;

	default:
		break;
	};
}

HRESULT DxCharSham::FrameMove ( float fTime, float fElapsedTime )
{
	if ( !m_pSkinChar )										
		return S_FALSE;

	switch ( m_Action )
	{
	case GLAT_IDLE:
		{
			m_fIdleTime += fElapsedTime;

			if ( m_pSkinChar->GETCURMTYPE() == AN_GESTURE )//add vcf
			{
				if ( m_pSkinChar->ISENDANIM() )
					m_pSkinChar->SELECTANI ( AN_PLACID, AN_SUB_NONE );
			}else{
				if( m_pSkinChar->GETCURMTYPE() != AN_PLACID )
					m_pSkinChar->SELECTANI ( AN_PLACID, AN_SUB_NONE );
			}
		}
		break;

	case GLAT_CONFT_END:
		{
			if( m_pSkinChar->GETCURMTYPE() != AN_CONFT_WIN && 
				m_pSkinChar->GETCURMTYPE() != AN_GUARD_N )
				m_pSkinChar->SELECTANI ( AN_CONFT_WIN, AN_SUB_NONE );

			if( m_pSkinChar->ISENDANIM() )
				TurnAction ( GLAT_ATTACK );
		}
		break;

	case GLAT_ATTACK:
		{
			if( m_pSkinChar->GETCURMTYPE() != AN_GUARD_N )		
				m_pSkinChar->SELECTANI ( AN_GUARD_N, GLCHARLOGIC::m_emANISUBTYPE );

			if( m_fIdleTime == m_pSkinChar->GETENDTIME() && m_bIdleReserv )
			{
				TurnAction ( GLAT_IDLE );
				break;
			}

			if( (m_fIdleTime*1000.0f) > (m_pSkinChar->GETENDTIME()/2.0f) )
			{
				m_fIdleTime = m_pSkinChar->GETENDTIME();
			}
			else
			{
				m_fIdleTime += fElapsedTime;
			}
		}
		break;
	};

	if ( m_fDelayFreeAnim > 500 && m_bSelect == FALSE )//add vcf
	{
		switch( RandomNumber( 0 , 10 ) )
		{
		case 0:
			GetSkinChar()->SELECTANI( AN_GESTURE , (EMANI_SUBTYPE) 38 );
			break;
		case 1:
			GetSkinChar()->SELECTANI( AN_GESTURE , (EMANI_SUBTYPE) 46 );
			break;
		case 2:
			GetSkinChar()->SELECTANI( AN_GESTURE , (EMANI_SUBTYPE) 41 );
			break;
		}
		m_fDelayFreeAnim = 0;
	}

	if ( m_bSelect )
	{
		STARGETID sTARID(CROW_PC,m_nID);
		DxEffGroupPlayer::GetInstance().PassiveEffect ( GLCONST_CHAR::strSELECT_CHAR.c_str(), m_matTrans, sTARID );
	}
	else
	{
		if( m_pSkinChar->GETCURMTYPE() == AN_PLACID )//add vcf
			m_fDelayFreeAnim += RandomNumber( 0.0f , 10.0f );
		m_bEffect = FALSE;
		STARGETID sTARID(CROW_PC,m_nID);
		DxEffGroupPlayer::GetInstance().DeletePassiveEffect ( GLCONST_CHAR::strSELECT_CHAR.c_str(), sTARID );
	}

	//	Note : 스킨 업데이트.
	//
	m_pSkinChar->SetPosition ( m_vPos );
	m_pSkinChar->FrameMove ( fTime, fElapsedTime, TRUE, FALSE, !m_bPeaceZone );

	//	Note : 현제 위치와 방향으로 Transform 메트릭스 계산.
	//
	D3DXMATRIX matTrans, matYRot;
	D3DXMatrixTranslation ( &matTrans, m_vPos.x, m_vPos.y, m_vPos.z );
	float fThetaY = DXGetThetaYFromDirection ( m_vDir, m_vDirOrig );
	D3DXMatrixRotationY ( &matYRot, fThetaY );

	m_matTrans = matYRot * matTrans;

	//	Note : AABB 계산.
	//
	m_vMax = m_vPos + m_vMaxOrg;
	m_vMin = m_vPos + m_vMinOrg;

	return S_OK;
}

HRESULT DxCharSham::Render ( LPDIRECT3DDEVICEQ pd3dDevice, CLIPVOLUME &cv, BOOL bRendAABB )
{
	if ( m_bNeedData && !(m_dwRevData&RECEIVE_CHARDATA) )	return S_FALSE;
	if ( !m_pSkinChar )										return S_FALSE;

	if ( bRendAABB ) EDITMESHS::RENDERAABB ( pd3dDevice, m_vMax, m_vMin );	//	테스트용.

	HRESULT hr;
	hr = m_pSkinChar->Render ( pd3dDevice, m_matTrans );
	if ( FAILED(hr) )	return hr;

	return S_OK;
}

HRESULT DxCharSham::RenderShadow ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	if ( m_bNeedData && !(m_dwRevData&RECEIVE_CHARDATA) )	return S_FALSE;
	if ( !m_pSkinChar )										return S_FALSE;

	//	Note : 그림자 랜더링.
	//
	DxShadowMap::GetInstance().RenderShadowCharMob ( m_pSkinChar, m_matTrans, pd3dDevice );

	return S_OK;
}

HRESULT DxCharSham::RestoreDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	if ( m_pSkinChar )	
		m_pSkinChar->RestoreDeviceObjects ( pd3dDevice );

	return S_OK;
}

HRESULT DxCharSham::InvalidateDeviceObjects ()
{
	if ( m_pSkinChar )	
		m_pSkinChar->InvalidateDeviceObjects ();

	return S_OK;
}