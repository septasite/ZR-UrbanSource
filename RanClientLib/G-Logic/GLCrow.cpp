#include "stdafx.h"
#include "./GLCrow.h"
#include "./GLGaeaServer.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

#define BOX_R	(4)

GLCrow::GLCrow(void) :
	m_nSkillReActionError( 0 ),
	m_pd3dDevice(NULL),
	m_pSkinChar(NULL),
	m_vDir(0,0,-1),

	m_vMaxOrg(BOX_R,20,BOX_R),
	m_vMinOrg(-BOX_R,0,-BOX_R),

	m_vMax(BOX_R,20,BOX_R),
	m_vMin(-BOX_R,0,-BOX_R),

	m_wTARNUM(0),
	m_vTARPOS(0,0,0),

	m_dwGlobID(0),

	m_dwCeID(0),
	m_pLandMan(NULL),

	m_pGlobNode(NULL),
	m_pQuadNode(NULL),
	m_pCellNode(NULL),

	m_fAge(0.0f),
	m_Action(GLAT_IDLE),
	m_dwActState(NULL),
	m_dwCFlag(NULL),
	m_vPos(0,0,0),
	m_vGenPos(0,0,0),
	m_vOrgTarPos(0,0,0),

	m_fScale( 0.0f ),

	m_vStartPos(0,0,0),

	m_dwAttPosSlot(GLARoundSlot::SLOT_SIZE),

	m_emReAction(EMREACT_NUNE),
	m_pAttackProp(0),

	m_fattTIMER(0.0f),

	m_sAssault(CROW_PC,GAEAID_NULL),

	m_fIdleTime(0.0f),
	m_fStayTimer(0.0f),

	m_fTargetTimer(0.0f),

	m_pCurAct(NULL),
	m_pMobSchedule(NULL),

	m_dwPC_AMOUNT(0),
	m_bNpcRecall(false),
	m_dwCallCharID(0),
	m_dwCallUserID(0),
	m_tGenTime(0),
	m_lnCommission(0),
	m_bGroup(false),
	m_bFirstTime(false),
	m_bOnce(false),
	m_bCHECK(FALSE)
{	
}

GLCrow::~GLCrow(void)
{
	SAFE_DELETE(m_pSkinChar);
}

void GLCrow::RESET_DATA ()
{
	int i=0;

	GLCROWLOGIC::RESET_DATA();

	m_pd3dDevice = NULL;
	
	m_actorMove.ResetMovedData();
	m_actorMove.Stop();
	m_actorMove.Release();

	m_pSkinChar = NULL;

	m_vDir = D3DXVECTOR3(0,0,0);
	
	D3DXMatrixIdentity ( &m_matTrans );

	m_vMaxOrg = D3DXVECTOR3(0,0,0);
	m_vMinOrg = D3DXVECTOR3(0,0,0);

	m_vMax = D3DXVECTOR3(0,0,0);
	m_vMin = D3DXVECTOR3(0,0,0);

	m_dwGlobID = 0;

	m_sMapID = SNATIVEID(0,0);
	m_dwCeID = 0;
	
	m_pLandMan = NULL;
	m_pGlobNode = NULL;
	m_pQuadNode = NULL;
	m_pCellNode = NULL;

	m_fAge = 0.0f;
	m_Action = GLAT_IDLE;
	m_dwActState = NULL;
	m_dwCFlag = NULL;
	m_vPos = D3DXVECTOR3(0,0,0);
	m_vGenPos = D3DXVECTOR3(0,0,0);
	m_vOrgTarPos = D3DXVECTOR3(0,0,0);

	m_fScale = 0.0f;

	m_vStartPos = D3DXVECTOR3(0,0,0);

	m_dwAttPosSlot = GLARoundSlot::SLOT_SIZE;
	m_TargetID = STARGETID(CROW_PC,GAEAID_NULL);

	m_emReAction = EMREACT_NUNE;
	m_pAttackProp = NULL;
	m_fattTIMER = 0.0f;
	m_sHITARRAY.clear();

	m_wTARNUM = 0;
	
	for ( i=0; i<EMTARGET_NET; ++i )
		m_sTARIDS[i] = STARID(CROW_PC,GAEAID_NULL);
	m_vTARPOS = D3DXVECTOR3(0,0,0);

	m_sAssault = STARGETID(CROW_PC,GAEAID_NULL);

	m_cDamageLog.clear();
	m_cDamageLogParty.clear();

	m_fIdleTime = 0.0f;
	m_fStayTimer = 0.0f;

	m_fTargetTimer = 0.0f;

	m_pCurAct = NULL;
	m_pMobSchedule = NULL;

	m_nSkillReActionError = 0;

	m_bNpcRecall = false;
	m_dwCallCharID = 0;
	m_dwCallUserID = 0;
	m_tGenTime = 0;
	m_lnCommission = 0;
	m_bGroup	= false;
	m_bFirstTime = false;
	m_bOnce = false;
	m_bCHECK	= FALSE;
}

HRESULT GLCrow::CreateCrow ( GLMobSchedule *pMobSchedule, GLLandMan* pLandMan, SNATIVEID sCROWID,
							LPDIRECT3DDEVICEQ pd3dDevice, LPD3DXVECTOR3 pPos, FLOAT fScale )
{
	GASSERT(pLandMan);

	m_bGroup = false;
	m_pLandMan = pLandMan;
	m_pd3dDevice = pd3dDevice;

	//	Note : ∏˜¿« º≥¡§ ¡§∫∏∏¶ ∞°¡Æø».
	m_pCrowData = GLCrowDataMan::GetInstance().GetCrowData ( sCROWID );
	if( !m_pCrowData )
	{
		DEBUGMSG_WRITE ( _T("GLCrow::CreateMob, Mob Create Failed. nativeid [%d/%d]"), sCROWID.wMainID, sCROWID.wSubID );
		return E_FAIL;
	}
	
	//	Note : ∏ÅE∑Œ¡ÅEµ•¿Ã≈Õ √ ±‚»≠.
	GLCROWLOGIC::INIT_DATA ();


	//	Note : Ω∫ƒ…¡ÅEØ √ ±‚»≠.
	m_pMobSchedule = pMobSchedule;

	//	¿ßƒ° √ ±‚»≠.
	if ( pPos )					m_vPos = *pPos;
	else if ( m_pMobSchedule )	m_vPos = m_pMobSchedule->m_pAffineParts->vTrans;
	
	m_vGenPos = m_vPos;
	m_vOrgTarPos = m_vPos;
	
	m_fScale = fScale;

	//	πÊ«ÅE√ ±‚»≠.
	D3DXMATRIX matY, matScale;
	D3DXMatrixIdentity ( &matY );
	D3DXMatrixIdentity ( &matScale );

	if ( m_pMobSchedule )
		D3DXMatrixRotationY ( &matY, m_pMobSchedule->m_pAffineParts->vRotate.x );

	D3DXVec3TransformCoord ( &m_vDir, &vDIRORIG, &matY );

	if ( m_pMobSchedule )
		m_pCurAct = m_pMobSchedule->m_sMobActList.m_pHead;

	//	Note : ¿Ãµø ¡¶æÅE√ ±‚»≠.
	ToWalk ();	

	if ( m_actorMove.PathIsActive() )		m_actorMove.Stop();
	m_actorMove.Create ( pLandMan->GetNavi(), m_vPos, -1 );

	//	Note : ¡÷∫Ø ƒ…∏Ø≈Õ ¿ŒΩƒ.
	//
	UpdateViewAround ();

	if ( m_pd3dDevice )
	{
		DxSkinCharData* pCharData = DxSkinCharDataContainer::GetInstance().LoadData( m_pCrowData->GetSkinObjFile(), m_pd3dDevice, TRUE );
		if ( !pCharData )	return E_FAIL;

		SAFE_DELETE(m_pSkinChar);
		m_pSkinChar = new DxSkinChar;
		m_pSkinChar->SetCharData ( pCharData, pd3dDevice );
	}

	return S_OK;
}

void GLCrow::SetPosition ( D3DXVECTOR3 &vPos )
{
	ToWalk ();
	m_actorMove.SetPosition ( vPos, -1 );
	if ( m_actorMove.PathIsActive() )		m_actorMove.Stop();

	return;
}

inline HRESULT GLCrow::MoveTo ( const D3DXVECTOR3 &vTarPos )
{
	if ( m_pCrowData->IsPosHold() )		return S_FALSE;

	m_TargetID.vPos = vTarPos;
	TurnAction ( GLAT_MOVE );

	return S_OK;
}

BOOL GLCrow::IsVisibleDetect ( const BOOL bRECVISIBLE )
{
	if ( IsSTATE(EM_REQ_VISIBLENONE) || IsSTATE(EM_REQ_VISIBLEOFF) )	return FALSE;

	if ( m_bINVISIBLE && !bRECVISIBLE )									return FALSE;

	return TRUE;
}

HRESULT GLCrow::ESCAPE ( STARGETID &sTARID, const DWORD dwDamage )
{
	if ( m_pCrowData->IsPosHold() )		return S_FALSE;

	EMCROWACT_UP emCROWACT = GetActPattern();
	BOOL bESCAPE = ( EMCROWACT_UP_ESCAPE == emCROWACT ) && ( dwDamage > DWORD ( m_pCrowData->m_dwHP * 0.10f ) );
    if ( !bESCAPE )		return S_FALSE;

	GLACTOR* pACTOR = GLGaeaServer::GetInstance().GetTarget ( m_pLandMan, sTARID );
	if ( pACTOR && pACTOR->IsValidBody() )
	{
		const D3DXVECTOR3 &vACTOR_POS = pACTOR->GetPosition();

		D3DXVECTOR3 vDir = ( GetPosition() - vACTOR_POS );		//	Attack -> Receive πÊ«‚¿« πÈ≈Õ.
		vDir.y = 0.0f;
		D3DXVec3Normalize (  &vDir, &vDir );

		enum { EMROTSIZE = 5, EMESCAPE_RANGE = 60 };
		static D3DXMATRIX _matROT000, _matROT045, _matROT315, _matROT090, _matROT270;
		static D3DXMATRIX matROT000 = *D3DXMatrixRotationY ( &_matROT000, 0 );
		static D3DXMATRIX matROT045 = *D3DXMatrixRotationY ( &_matROT045, D3DX_PI/4.0f );
		static D3DXMATRIX matROT315 = *D3DXMatrixRotationY ( &_matROT315, -D3DX_PI/4.0f );
		static D3DXMATRIX matROT090 = *D3DXMatrixRotationY ( &_matROT045, D3DX_PI/2.0f );
		static D3DXMATRIX matROT270 = *D3DXMatrixRotationY ( &_matROT045, -D3DX_PI/2.0f );
		static D3DXMATRIX *pmatROT[EMROTSIZE] = { &matROT000, &matROT045, &matROT315, &matROT090, &matROT270 };

		BOOL bCoB(FALSE);
		DWORD dwCoB(0);
		D3DXVECTOR3 vCoB(0,0,0);

		for ( int i=0; i<EMROTSIZE; ++i )
		{
			D3DXVECTOR3 vDirRot;
			D3DXVec3TransformCoord ( &vDirRot, &vDir, pmatROT[i] );

			D3DXVECTOR3 vPosB = GetPosition() + vDirRot * EMESCAPE_RANGE;
			NavigationMesh* pNavi = m_pLandMan->GetNavi();

			pNavi->IsCollision ( D3DXVECTOR3(vPosB.x,vPosB.y+20.0f,vPosB.z), D3DXVECTOR3(vPosB.x,vPosB.y-30.0f,vPosB.z), vCoB, dwCoB, bCoB );
			if ( bCoB )
			{
				if ( m_pCrowData->m_sAction.m_bRun )	ToRun();
				MoveTo ( vCoB );
				return S_OK;
			}
		}
	}

	return S_FALSE;
}

void GLCrow::ToRun ()
{
	GASSERT(m_pCrowData);

	SetSTATE(EM_ACT_RUN);
	m_actorMove.SetMaxSpeed ( m_pCrowData->m_sAction.m_fRunVelo );
}

void GLCrow::ToWalk ()
{
	GASSERT(m_pCrowData);

	ReSetSTATE(EM_ACT_RUN);
	m_actorMove.SetMaxSpeed ( m_pCrowData->m_sAction.m_fWalkVelo );
}

INT GLCrow::IsLowerHP ()							
{ 
	float fRate = 0.0f;
	for( int i = 0; i < m_pCrowData->m_sAction.m_vecPatternList.size(); i++ )
	{
		fRate = m_pCrowData->m_sAction.m_vecPatternList[ i ].m_fPatternDNRate;
		if( GETHP() >= (int)( (float)GETMAXHP() * fRate ) / 100.0f )
		{
			return i;
		}
	}
	return -1;
}

EMCROWACT_UP GLCrow::GetActPattern ()
{
	INT nIndex = IsLowerHP();

	EMCROWACT_UP emACT_UP;

	if( nIndex >= 0 )
	{
		emACT_UP = m_pCrowData->m_sAction.m_vecPatternList[ nIndex ].m_emActPattern;
	}
	else if( nIndex < 0 )
	{
		emACT_UP = EMCROWACT_UP_IDLE;
	}

	return emACT_UP;
}


void GLCrow::TurnAction ( EMACTIONTYPE toAction, bool bMsg )
{
	//	Note : ¿Ã¿ÅEæ◊º« √ÅE“.
	//
	switch ( m_Action )
	{
	case GLAT_IDLE:
		break;

	case GLAT_ATTACK:
		m_emReAction = EMREACT_NUNE;

		//	Note : ∞¯∞›ºˆ«‡¿Ã ≥°≥Ø∂ß µÙ∑π¿Ã µ˚”œ.
		if ( m_pAttackProp )
		{
			m_fACTIONDELAY[m_dwAType] = m_pAttackProp->fDelay + 0.3f;
		}
		m_bINVISIBLE=false;
		break;

	case GLAT_SKILL:
		{
			m_idACTIVESKILL = NATIVEID_NULL();
			m_wTARNUM = 0;
			m_emReAction = EMREACT_NUNE;
			m_bINVISIBLE=false;

			if ( m_pAttackProp )
			{
				SNATIVEID sRunSkill = m_pAttackProp->skill_id;
				WORD wLevel = m_pAttackProp->skill_lev;

				//	Note : Ω∫≈≥ ¡§∫∏ ∞°¡Æø».
				PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( sRunSkill );
				if ( !pSkill )								break;
				if ( wLevel >= SKILL::MAX_LEVEL )			break;

				float fSkillDelay = pSkill->m_sAPPLY.sDATA_LVL[wLevel].fDELAYTIME;
				m_fACTIONDELAY[m_dwAType] = fSkillDelay + 0.1f;
			}
		}
		break;

	default:
		break;
	};

	//	Note : æ◊º« √ ±‚»≠.
	//
	EMACTIONTYPE emOldAction = m_Action;
	m_Action = toAction;

	switch ( m_Action )
	{
	case GLAT_IDLE:
		{
			m_fIdleTime = 0.0f;

			if ( !bMsg ) break;

			GLMSG::SNET_ACTION_BRD NetMsg;
			NetMsg.emCrow	= m_pCrowData->m_emCrow;
			NetMsg.dwID		= m_dwGlobID;
			NetMsg.emAction	= m_Action;

			SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsg );
		}
		break;

	case GLAT_MOVE:
		{
			D3DXVECTOR3 vDist = m_vPos - m_TargetID.vPos;
			float fDist = D3DXVec3Length ( &vDist );
			if ( fDist < 1.0f )
			{
				TurnAction(GLAT_IDLE,(emOldAction!=GLAT_IDLE));
				break;
			}

			BOOL bSucceed = m_actorMove.GotoLocation
			(
				m_TargetID.vPos+D3DXVECTOR3(0,+10,0),
				m_TargetID.vPos+D3DXVECTOR3(0,-10,0)
			);


			if ( !bMsg ) break;

			if ( bSucceed )
			{
				m_vStartPos = m_vPos;

				//	Note : ¿Ãµø ∏ﬁºº¡ÅEπﬂª˝.
				//
				GLMSG::SNETCROW_MOVETO NetMsg;
				NetMsg.dwGlobID		= m_dwGlobID;
				NetMsg.dwActState	= m_dwActState;
				//NetMsg.vCurPos	= m_vPos;					 m_actorMove.GotoLocation() »£√‚»ƒ 
				NetMsg.vCurPos		= m_actorMove.Position(); // m_vPos∞° ∫Ø∞Êµ… ºÅE¿÷±‚∂ßπÆø° ∫Ø∞Ê«‘.
				NetMsg.vTarPos		= m_TargetID.vPos;
				NetMsg.bTrace		= IsFLAG(EMTRACING);
				SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsg );
			}
		}
		break;

	case GLAT_ATTACK:
		{
			m_fattTIMER = 0.0f;
			PreStrikeProc ( FALSE, FALSE );
			m_bINVISIBLE=false;

			if ( !bMsg ) break;

			//	Note : ∞¯∞› ∏ﬁºº¡ÅEπﬂª˝.
			//
			GLMSG::SNETCROW_ATTACK NetMsg;
			NetMsg.dwGlobID		= m_dwGlobID;
			NetMsg.dwTarID		= m_TargetID.dwID;
			NetMsg.emTarCrow	= m_TargetID.emCrow;
			NetMsg.dwAType		= m_dwAType;

			SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsg );

			STARGETID sTargetID = STARGETID ( CROW_MOB, m_dwGlobID, m_vPos );
			
			
			if( m_TargetID.emCrow == CROW_PC )
			{
				PGLCHAR pCHAR = GLGaeaServer::GetInstance().GetChar ( m_TargetID.dwID );
				if ( pCHAR )
				{
					// PET Attack √≥∏Æ
					PGLPETFIELD pEnemyPet = GLGaeaServer::GetInstance().GetPET ( pCHAR->m_dwPetGUID );
					if ( pEnemyPet && pEnemyPet->IsValid () && !pEnemyPet->IsSTATE ( EM_PETACT_ATTACK ) )
					{
						D3DXVECTOR3 vOwnerPos, vDist;
						float fDist;
						vOwnerPos = pCHAR->GetPosition ();
						vDist = pEnemyPet->m_vPos - vOwnerPos;
						fDist = D3DXVec3Length(&vDist);

						// ¿œ¡§∞≈∏Æ æ»ø° ¿÷¿∏∏ÅE
						if ( fDist <= GLCONST_PET::fWalkArea )
						{
							pEnemyPet->ReSetAllSTATE ();
							pEnemyPet->SetSTATE ( EM_PETACT_ATTACK );

							GLMSG::SNETPET_ATTACK NetMsg;
							NetMsg.sTarID = sTargetID;
							GLGaeaServer::GetInstance().SENDTOCLIENT ( pCHAR->m_dwClientID, &NetMsg );
							
							GLMSG::SNETPET_ATTACK_BRD NetMsgBRD;
							NetMsgBRD.dwGUID = pEnemyPet->m_dwGUID;
							NetMsgBRD.sTarID = sTargetID;
							pCHAR->SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBRD );
						}
					}
					// Summon Attack √≥∏Æ
					PGLSUMMONFIELD pEnemySummon = GLGaeaServer::GetInstance().GetSummon ( pCHAR->m_dwSummonGUID );
					if ( pEnemySummon && pEnemySummon->IsValid () && !pEnemySummon->IsSTATE ( EM_SUMMONACT_ATTACK ) && 
						pEnemySummon->GetAttackTarget( sTargetID ) )
					{
						/*D3DXVECTOR3 vOwnerPos, vDist;
						float fDist;
						vOwnerPos = pCHAR->GetPosition ();
						vDist = pEnemySummon->m_vPos - vOwnerPos;
						fDist = D3DXVec3Length(&vDist);

						if ( fDist <= pEnemySummon->m_fWalkArea )*/
						{
							pEnemySummon->SetAttackTarget( sTargetID );
						}
					}
				}
			}else if( m_TargetID.emCrow == CROW_SUMMON )
			{
				// Summon Attack √≥∏Æ
				PGLSUMMONFIELD pEnemySummon = GLGaeaServer::GetInstance().GetSummon ( m_TargetID.dwID );
				if ( pEnemySummon && pEnemySummon->IsValid () && !pEnemySummon->IsSTATE ( EM_SUMMONACT_ATTACK ) && 
					pEnemySummon->GetAttackTarget( sTargetID ) )
				{
					//D3DXVECTOR3 vOwnerPos, vDist;
					//float fDist;
					//vOwnerPos = pCHAR->GetPosition ();
					//vDist = pEnemySummon->m_vPos - vOwnerPos;
					//fDist = D3DXVec3Length(&vDist);

					//// ¿œ¡§∞≈∏Æ æ»ø° ¿÷¿∏∏ÅE
					//if ( fDist <= GLCONST_SUMMON::fWalkArea )
					//{
					

					pEnemySummon->SetAttackTarget( sTargetID );
				}				
			}
		}
		break;

	case GLAT_SKILL:
		m_fattTIMER = 0.0f;
		PreStrikeProc ( TRUE, FALSE );

		StartSkillProc ();
		m_bINVISIBLE=false;
		break;

	case GLAT_SHOCK:
		m_fIdleTime = 0.0f;
		break;

	case GLAT_PUSHPULL:
		m_fIdleTime = 0.0f;
		break;

	case GLAT_FALLING:
		{
			m_fIdleTime = 0.0f;
			if ( !bMsg ) break;

			//	Note : ¡÷∫Ø Charø°∞‘ æ≤∑Ø¡ÅEª æÀ∏≤.
			GLMSG::SNET_ACTION_BRD NetMsg;
			NetMsg.emCrow	= m_pCrowData->m_emCrow;
			NetMsg.dwID		= m_dwGlobID;
			NetMsg.emAction	= m_Action;

			SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsg );
		}
		break;

	default:
		break;
	};

	if ( m_actorMove.PathIsActive() ){
		if ( !IsACTION(GLAT_MOVE) && !IsACTION(GLAT_PUSHPULL))		m_actorMove.Stop();
	}
}

inline DWORD GLCrow::ToDamage ( const STARGETID &sTargetID, const int nDAMAGE, const BOOL bShock )
{
	GLACTOR* pACTOR_TAR = GLGaeaServer::GetInstance().GetTarget ( m_pLandMan, sTargetID );
	if ( !pACTOR_TAR )	return 0;

	//	Note : ≈∏∞Ÿ¿Ã ¡§ªÅEªÛ≈¬¿œ ∞ÊøÅE° damage ¡ŸºÅE¿÷¿Ω.
	//
	if ( (CROW_PC==sTargetID.emCrow || CROW_SUMMON==sTargetID.emCrow) && !pACTOR_TAR->IsValidBody() )	return 0;

	return pACTOR_TAR->ReceiveDamage ( GETCROW(), m_dwGlobID, nDAMAGE, bShock );
}

void GLCrow::AvoidProc ( )
{
	//	Note : ¡÷∫Ø ≈¨∂Û¿Ãæ∆ÆµÈø°∞‘ ∏ﬁºº¡ÅE¿ÅE€.
	//
	GLMSG::SNETCROW_AVOID NetMsg;
	NetMsg.dwGlobID		= m_dwGlobID;
	NetMsg.emTarCrow	= m_TargetID.emCrow;
	NetMsg.dwTarID		= m_TargetID.dwID;

	SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsg );

	GLACTOR* pACTOR_TAR = GLGaeaServer::GetInstance().GetTarget ( m_pLandMan, m_TargetID );
	if ( !pACTOR_TAR )	return;

	//	Note : ≈∏∞Ÿ¿Ã ¡§ªÅEªÛ≈¬¿œ ∞ÊøÅE° damage ¡ŸºÅE¿÷¿Ω.
	//
	if ( CROW_PC==m_TargetID.emCrow && pACTOR_TAR->IsValidBody() )
	{
		pACTOR_TAR->ReceiveDamage ( GETCROW(), m_dwGlobID, 0, false );
	}
}

void GLCrow::DamageProc ( const int nDAMAGE, const DWORD dwDamageFlag )
{
	//	Note : ¥ÅEÛ¿⁄ø°∞‘ ¥ÅEÃ¡ˆ∞™ ¿˚øÅE
	bool bShock = ( dwDamageFlag & DAMAGE_TYPE_SHOCK );
	DWORD dwNowHP = ToDamage ( m_TargetID, nDAMAGE, bShock );

	//	Note : ¡÷∫Ø ≈¨∂Û¿Ãæ∆ÆµÈø°∞‘ ∏ﬁºº¡ÅE¿ÅE€.
	//
	GLMSG::SNETCROW_DAMAGE NetMsg;
	NetMsg.dwGlobID		= m_dwGlobID;
	NetMsg.emTarCrow	= m_TargetID.emCrow;
	NetMsg.dwTarID		= m_TargetID.dwID;
	NetMsg.nDamage		= nDAMAGE;
	NetMsg.dwNowHP		= dwNowHP;
	NetMsg.dwDamageFlag	= dwDamageFlag;

	SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsg );

	GLACTOR* pACTOR = GLGaeaServer::GetInstance().GetTarget ( m_pLandMan, m_TargetID );

	//	Note : ªÛ≈¬ ¿ÃªÅE¿Øπﬂ.
	//
	if ( pACTOR && m_pAttackProp->emBLOW_TYPE!=EMBLOW_NONE )
	{
		//	Note : πﬂª˝ »Æ¿≤ ∞ËªÅE
		//
		short nBLOWRESIST = pACTOR->GETRESIST().GetElement ( STATE_TO_ELEMENT(m_pAttackProp->emBLOW_TYPE) );
		if ( nBLOWRESIST>99 )	nBLOWRESIST = 99;

//		float fPOWER = GLOGICEX::WEATHER_BLOW_POW ( m_pAttackProp->emBLOW_TYPE, GLPeriod::GetInstance().GetWeather(), m_pLandMan->IsWeatherActive() );
		DWORD dwWeather = GLPeriod::GetInstance().GetMapWeather( m_pLandMan->GetMapID().wMainID, m_pLandMan->GetMapID().wSubID );
		float fPOWER = GLOGICEX::WEATHER_BLOW_POW ( m_pAttackProp->emBLOW_TYPE, dwWeather, m_pLandMan->IsWeatherActive() );

		BOOL bBLOW = FALSE;
		if ( !(pACTOR->GETHOLDBLOW()&STATE_TO_DISORDER(m_pAttackProp->emBLOW_TYPE)) )
		{
			bBLOW = GLOGICEX::CHECKSTATEBLOW ( m_pAttackProp->fBLOW_RATE*fPOWER, GETLEVEL(), pACTOR->GetLevel(), nBLOWRESIST );
		}

		if ( bBLOW )
		{
			//	Note : ªÛ≈¬¿ÃªÅEπﬂª˝.
			//	
			SSTATEBLOW sSTATEBLOW;
			float fLIFE = m_pAttackProp->fBLOW_LIFE * fPOWER;
			fLIFE = ( fLIFE - (fLIFE*nBLOWRESIST*0.01f*GLCONST_CHAR::fRESIST_G ) );

			sSTATEBLOW.emBLOW = m_pAttackProp->emBLOW_TYPE;
			sSTATEBLOW.fAGE = fLIFE;
			sSTATEBLOW.fSTATE_VAR1 = m_pAttackProp->fBLOW_VAR1;
			sSTATEBLOW.fSTATE_VAR2 = m_pAttackProp->fBLOW_VAR2;

			pACTOR->STATEBLOW ( sSTATEBLOW );

			//	Note : ªÛ≈¬¿ÃªÅEπﬂª˝ Msg.
			//
			GLMSG::SNETPC_STATEBLOW_BRD NetMsgState;
			NetMsgState.emCrow = m_TargetID.emCrow;
			NetMsgState.dwID = m_TargetID.dwID;
			NetMsgState.emBLOW = sSTATEBLOW.emBLOW;
			NetMsgState.fAGE = fLIFE;
			NetMsgState.fSTATE_VAR1 = sSTATEBLOW.fSTATE_VAR1;
			NetMsgState.fSTATE_VAR2 = sSTATEBLOW.fSTATE_VAR2;

			//	Note : 'Ω∫≈≥¥ÅEÅE¿« ¡÷∫Ø ≈¨∂Û¿Ãæ∆ÆµÈø°∞‘ ∏ﬁºº¡ÅE¿ÅE€.
			//
			pACTOR->SNDMSGAROUND ( (NET_MSG_GENERIC*) &NetMsgState );

			//	Note : Ω∫≈≥ ¥ÅEÛø°∞‘ ∏ﬁºº¡ÅE¿ÅE€.
			if ( m_TargetID.emCrow==CROW_PC )	GLGaeaServer::GetInstance().SENDTOCLIENT ( pACTOR->GETCLIENTID (), &NetMsgState );
		}
	}
}

void GLCrow::DamageReflectionProc ( int nDAMAGE, STARGETID sACTOR )
{
	//	Note : ¥ÅEÛ¿⁄ø°∞‘ ¥ÅEÃ¡ˆ∞™ ¿˚øÅE
	DWORD dwNowHP = ToDamage ( sACTOR, nDAMAGE, FALSE );

	//	Note : ¡÷∫Ø ≈¨∂Û¿Ãæ∆ÆµÈø°∞‘ ∏ﬁºº¡ÅE¿ÅE€.
	//
	GLMSG::SNETCROW_DAMAGE NetMsg;
	NetMsg.dwGlobID		= m_dwGlobID;
	NetMsg.emTarCrow	= sACTOR.emCrow;
	NetMsg.dwTarID		= sACTOR.dwID;
	NetMsg.nDamage		= nDAMAGE;
	NetMsg.dwNowHP		= dwNowHP;
	NetMsg.dwDamageFlag	= DAMAGE_TYPE_NONE;

	SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsg );
}

void GLCrow::PreAttackProc ()
{
	SANIATTACK &sAniAttack = m_pAttackProp->sAniAttack;

	m_sHITARRAY.clear ();

	for ( int i = 0; i < sAniAttack.m_wDivCount; i++ )
	{
		bool bhit = CHECKHIT(m_TargetID,m_pLandMan) ? true : false;
		m_sHITARRAY.push_back ( SSTRIKE(sAniAttack.m_wDivFrame[i],bhit) );
	}
}

void GLCrow::PreStrikeProc ( BOOL bSkill, BOOL bLowSP )
{
	SANIATTACK &sAniAttack = m_pAttackProp->sAniAttack;

	m_sHITARRAY.clear ();

	STARGETID sTargetID;
	BOOL bCheckHit = FALSE;

	if ( !bSkill )
	{
		sTargetID = m_TargetID;
		bCheckHit = TRUE;
	}
	else
	{
		//	Note : Ω∫≈≥ ¡§∫∏ ∞°¡Æø».
		//
		PGLSKILL pSkill = NULL;
		pSkill = GLSkillMan::GetInstance().GetData ( m_idACTIVESKILL.wMainID, m_idACTIVESKILL.wSubID );
		if ( pSkill->m_sBASIC.emAPPLY != SKILL::EMAPPLY_MAGIC )
		{
			//	Note : Ω∫≈≥ ≈∏∞Ÿ¿ª «œ≥™∏∏ ¿Ø»ø«œ∞‘ »Æ¿Œ¿ª «œ∞ÅE¿÷¿Ω.
			//	NEED : ¥Ÿ¡ﬂ ≈∏∞Ÿ¿œ ∞ÊøÅE¥ŸΩ√ »Æ¿Œ«ÿæﬂ«‘.
			sTargetID = STARGETID(static_cast<EMCROW>(m_sTARIDS[0].wCrow),static_cast<DWORD>(m_sTARIDS[0].wID));
			bCheckHit = TRUE;
		}
		else
		{
			sTargetID.dwID = EMTARGET_NULL;
		}
	}

	//	≈• √ ±‚»≠
	m_sHITARRAY.clear ();

	for ( int i = 0; i < sAniAttack.m_wDivCount; i++ )
	{
		bool bhit = true;
		if ( bCheckHit && (sTargetID.dwID!=EMTARGET_NULL) )
		{
			if ( !CHECKHIT(sTargetID,m_pLandMan) )		bhit = false;
		}

		m_sHITARRAY.push_back ( SSTRIKE(sAniAttack.m_wDivFrame[i],bhit) );
	}
}

BOOL GLCrow::AttackProcess ( float fElapsedTime )
{
	GASSERT(m_pAttackProp);
	m_fattTIMER += fElapsedTime * GETATTVELO();

	SANIATTACK &sAniAttack = m_pAttackProp->sAniAttack;
	int wTotalKeys = int(sAniAttack.m_dwETime) - int(sAniAttack.m_dwSTime);
	int wThisKey = int(m_fattTIMER*UNITANIKEY_PERSEC);

	if ( GetAttackRangeType()==EMATT_SHORT )
	{
		GLACTOR *pTARGET = GLGaeaServer::GetInstance().GetTarget ( m_pLandMan, m_TargetID );
		if ( !pTARGET )
		{
			TurnAction ( GLAT_IDLE, false );
			return FALSE;
		}

		D3DXVECTOR3 vDist = m_vPos - pTARGET->GetPosition();
		float fTarLength = D3DXVec3Length(&vDist);

		WORD wAttackRange = pTARGET->GetBodyRadius() + GETBODYRADIUS() + GETATTACKRANGE() + 2;
		if ( wAttackRange*GLCONST_CHAR::fREACT_VALID_SCALE < (WORD)(fTarLength) )
		{
			TurnAction ( GLAT_IDLE, false );
			return FALSE;
		}
	}

	if ( !m_sHITARRAY.empty() )
	{
		SSTRIKE sStrike = *m_sHITARRAY.begin();

		if ( wThisKey >= sStrike.wDivKey )
		{
			if ( sStrike.bHit )
			{
				int nDamage = 0;
				DWORD dwDamageFlag = DAMAGE_TYPE_NONE;
				dwDamageFlag = CALCDAMAGE ( nDamage, m_dwGlobID, m_TargetID, m_pLandMan );
				DamageProc ( nDamage, dwDamageFlag );
			}
			else					AvoidProc ();

			//	≈• µ•¿Ã≈∏∞° √≥∏Æµ» ∞ÊøÅEªË¡¶«—¥Ÿ.
			m_sHITARRAY.pop_front ();
		}	
	}

	//	¿ÃªÛ¡ıªÛø° ¿««ÿ µ•¿Ã≈∏∞° ¿ÅEÅE√≥∏Æµ«¡ÅEæ ¿∫∞ÊøÅE
	//	∏∂¡ˆ∏∑ø° «—≤®π¯ø° √≥∏Æ«œ∞ÅE FALSE∏¶ ∏Æ≈œ«—¥Ÿ.
	if ( wThisKey >= wTotalKeys )
	{
		if ( !m_sHITARRAY.empty() )
		{
			while ( !m_sHITARRAY.empty() )
			{
				SSTRIKE sStrike = *m_sHITARRAY.begin();
				
				if ( sStrike.bHit )
				{
					int nDamage = 0;
					DWORD dwDamageFlag = DAMAGE_TYPE_NONE;
					dwDamageFlag = CALCDAMAGE ( nDamage, m_dwGlobID, m_TargetID, m_pLandMan );
					DamageProc ( nDamage, dwDamageFlag );
				}
				else					AvoidProc ();

				//	≈• µ•¿Ã≈∏∞° √≥∏Æµ» ∞ÊøÅEªË¡¶«—¥Ÿ.
				m_sHITARRAY.pop_front ();
			}
		}

		return FALSE;
	}

	return TRUE;
}

BOOL GLCrow::ShockProcess ( float fElapsedTime )
{
	VECANIATTACK &vecShock = m_pCrowData->GetAnimation(AN_SHOCK,AN_SUB_NONE);
	if ( vecShock.empty() )	return FALSE;

	m_fIdleTime += fElapsedTime * GETATTVELO();
			
	SANIATTACK &sAniShock = vecShock[0];

	int wTotalKeys = int(sAniShock.m_dwETime) - int(sAniShock.m_dwSTime);
	int wThisKey = int(m_fIdleTime*UNITANIKEY_PERSEC);
	
	if ( wThisKey >= wTotalKeys )	return FALSE;

	return TRUE;
}

NET_MSG_GENERIC* GLCrow::ReqNetMsg_Drop ()
{
	static GLMSG::SNETDROP_CROW NetMsg;
	NetMsg = GLMSG::SNETDROP_CROW();

	SDROP_CROW &dropCrow	= NetMsg.Data;
	dropCrow.sNativeID		= m_sNativeID;

	dropCrow.sMapID			= m_sMapID;
	dropCrow.dwCeID			= m_dwCeID;
	dropCrow.dwGlobID		= m_dwGlobID;
	dropCrow.vPos			= m_vPos;
	dropCrow.vDir			= m_vDir;

	dropCrow.dwNowHP		= m_dwNowHP;
	dropCrow.wNowMP			= m_wNowMP;

	dropCrow.dwNowHPSG		= m_dwNowHPSG;
	dropCrow.dwNowHPMP		= m_dwNowHPMP;
	dropCrow.dwNowHPPHX		= m_dwNowHPPHX;
	dropCrow.emOWNER		= m_emOWNER;

	dropCrow.fScale			= m_fScale;

	if ( m_fAge < 0.6f )
		dropCrow.dwFLAGS	|= SDROP_CROW::CROW_GEM;

	dropCrow.emAction		= m_Action;
	dropCrow.dwActState		= m_dwActState;
	dropCrow.TargetID		= m_TargetID;

	dropCrow.wOWNER			= m_wOWNER;
	
	if ( dropCrow.emAction==GLAT_MOVE )
	{
		if ( m_actorMove.PathIsActive() )
		{
			dropCrow.TargetID.vPos = m_actorMove.GetTargetPosition();

			// º≠πÅE≈¨∂Û¿Ãæ∆Æ∞£ ∏˜¿« ¿ßƒ° µø±‚»≠∏¶ ¿ß«ÿ
			dropCrow.vStartPos		= m_vStartPos;
			dropCrow.sNextWaypoint  = m_actorMove.GetNextWayPoint ();
		}
		else
		{
			dropCrow.emAction = GLAT_IDLE;
		}
	}

	int i;
	for ( i=0; i<SKILLFACT_SIZE; ++i )	dropCrow.sSKILLFACT[i].Assign ( m_sSKILLFACT[i], i );
	for ( i=0; i<EMBLOW_MULTI; ++i )	dropCrow.sSTATEBLOWS[i] = m_sSTATEBLOWS[i];

	return (NET_MSG_GENERIC*) &NetMsg;
}

inline void GLCrow::INSERT_PC_VIEW ( DWORD dwGAEAID )
{
	if ( m_vecPC_VIEW.size() < m_dwPC_AMOUNT+16 )
		m_vecPC_VIEW.resize(m_dwPC_AMOUNT+16);

	m_vecPC_VIEW[m_dwPC_AMOUNT++] = dwGAEAID;
}

HRESULT GLCrow::UpdateViewAround ()
{
	int nX, nZ;

	m_dwPC_AMOUNT = 0;

	//	Note : «ˆ¿ÅEΩ√æﬂø° µÈæ˚€¿¥¬ CELL ∏µŒ ≈ΩªÅE
	//
	nX = int ( m_vPos.x );
	nZ = int ( m_vPos.z );
	LANDQUADNODE* pQuadHead = NULL;
	int nRANGE = MAX_VIEWRANGE;

	if( IsGroup() && IsGroupLeader() || IsGroupMember() )
	{
		nRANGE = MAX_VIEWRANGE * 5000;
	}

	BOUDRECT bRect(nX+nRANGE,nZ+nRANGE,nX-nRANGE,nZ-nRANGE);
	m_pLandMan->GetLandTree()->FindNodes ( bRect, m_pLandMan->GetLandTree()->GetRootNode(), &pQuadHead );

	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();

	LANDQUADNODE* pQuadNode = pQuadHead;
	for ( ; pQuadNode; pQuadNode = pQuadNode->pFindNext )
	{
		GLLandNode *pLandNode = pQuadNode->pData;
		if( !pLandNode ) continue;
		if ( pQuadNode->pData->m_PCList.m_dwAmount==0 )						continue;
		
		//	Note : - Char - 
		//
		GLCHARNODE *pCharNode = pQuadNode->pData->m_PCList.m_pHead;
		for ( ; pCharNode; pCharNode = pCharNode->pNext )
		{
			GLChar *pPChar = pCharNode->Data;
			if( !pPChar ) continue;

			//	Note : ƒ≥∏Ø≈Õ¿« ªË¡¶ Ω√¡°∞ÅEUpdateViewAround ()∞˙¿« ∫“¿œƒ°∑Œ ƒ≥∏Ø≈Õ∞° ¡∏¿Á«œ¡ÅEæ ¿ª ºÅE¿÷¿Ω.
			if ( !pPChar )													
				continue;

			if ( !glGaeaServer.GetChar ( pPChar->m_dwGaeaID ) )	
				continue;

			if ( bRect.IsWithIn(nX,nZ) )
			{
				INSERT_PC_VIEW ( pPChar->m_dwGaeaID );
			}
		}
	}

	return S_OK;
}

HRESULT GLCrow::SendMsgViewAround ( NET_MSG_GENERIC* nmg )
{
	DWORD dwGAEAID = 0;
	GLChar* pPChar = NULL;

	GLGaeaServer & glGaeaServer = GLGaeaServer::GetInstance();
	DWORD wSize = (DWORD)m_vecPC_VIEW.size();

	for ( DWORD i=0; i<m_dwPC_AMOUNT && i<wSize; ++i )
	{
		//	Memo :	m_vecPC_VIEW[i] is GaeaID
		pPChar = glGaeaServer.GetChar ( m_vecPC_VIEW[i] );
		if ( pPChar )
		{
			glGaeaServer.SENDTOCLIENT ( pPChar->m_dwClientID, nmg );
		}
	}

	return S_OK;
}

BOOL GLCrow::IsValidBody () const
{
	return ( m_Action < GLAT_FALLING );
}

BOOL GLCrow::IsDie () const
{
	if ( m_Action==GLAT_DIE )		
		return TRUE;

	return FALSE;
}


HRESULT GLCrow::UpateAnimation ( float fTime, float fElapsedTime )
{
	HRESULT hr=S_OK;

	float fAnimation = fElapsedTime;

	EMANI_MAINTYPE MType = m_pSkinChar->GETCURMTYPE();
	EMANI_SUBTYPE SType = m_pSkinChar->GETCURSTYPE();
	float fLIFETIME = m_pSkinChar->GETCURANITIME();

	switch ( m_Action )
	{
	case GLAT_IDLE:
		m_pSkinChar->SELECTANI ( AN_GUARD_N, AN_SUB_NONE );
		break;

	case GLAT_TALK:
		m_pSkinChar->SELECTANI ( AN_TALK, AN_SUB_NONE );
		if ( m_pSkinChar->ISENDANIM() )			TurnAction ( GLAT_IDLE );
		break;

	case GLAT_MOVE:
		if ( IsSTATE(EM_ACT_RUN) )				m_pSkinChar->SELECTANI ( AN_RUN, AN_SUB_NONE );
		else									m_pSkinChar->SELECTANI ( AN_WALK, AN_SUB_NONE );
		break;

	case GLAT_ATTACK:
		m_pSkinChar->SELECTANI ( AN_ATTACK, AN_SUB_NONE );
		if ( m_pSkinChar->ISENDANIM() )			TurnAction ( GLAT_IDLE );
		break;

	case GLAT_SHOCK:
		if ( !ShockProcess ( fElapsedTime ) )	TurnAction ( GLAT_IDLE );
		break;

	case GLAT_FALLING:
		m_pSkinChar->SELECTANI ( AN_DIE, AN_SUB_NONE, EMANI_ENDFREEZE );
		if ( m_pSkinChar->ISENDANIM() )			TurnAction ( GLAT_DIE );
		break;

	case GLAT_DIE:
		fAnimation = 0.0f;
		m_pSkinChar->TOENDTIME();
		break;
	case GLAT_GATHERING:
		m_pSkinChar->SELECTANI ( AN_GATHERING, AN_SUB_NONE );
		if ( m_pSkinChar->ISENDANIM() )			TurnAction ( GLAT_IDLE );
		break;
	};

	//	Note : Mob Ω∫≈≤ æ˜µ•¿Ã∆Æ.
	//
	float fSkinAniElap = fElapsedTime;

	switch ( m_Action )
	{
	case GLAT_MOVE:
		fSkinAniElap *= GLCROWLOGIC::GETMOVEVELO();
		break;

	case GLAT_ATTACK:
	case GLAT_SKILL:
		fSkinAniElap *= GETATTVELO();
		break;
	};

	m_pSkinChar->SetPosition ( m_vPos );
	m_pSkinChar->FrameMove ( fTime, fSkinAniElap );

	return S_OK;
}

float GLCrow::GetMoveVelo ()
{
	float fDefaultVelo = IsSTATE(EM_ACT_RUN) ? m_pCrowData->m_sAction.m_fRunVelo : m_pCrowData->m_sAction.m_fWalkVelo;
	return fDefaultVelo * GLCROWLOGIC::GETMOVEVELO();
}

HRESULT GLCrow::FrameMove ( float fTime, float fElapsedTime )
{
	HRESULT hr;
	GASSERT(m_pCrowData);
	GASSERT(m_pLandMan);

	//	Note : ∑£µÂø°º≠ µ˚”œµ» ºø¿ª æ˜µ•¿Ã∆Æ «œ±ÅE¿ß«ÿº≠ »£√‚«‘.
	//
	m_pLandMan->MoveCrow ( m_dwGlobID, m_vPos );
	UpdateViewAround ();

	//	«ˆ¿ÅE¡÷¿ßø° ƒ…∏Ø≈Õ∞° æ¯∞ÅE skinchar∞° π´»ø¿œ∂ß(ø°πƒ∑π¿Ã≈Õ,level edit)∞° æ∆¥“∂ß. & ∫∏Ω∫∏˜¿Ã æ∆¥“∂ß
	if ( m_dwPC_AMOUNT==0 && !m_pSkinChar && (m_pCrowData->m_sAction.m_dwActFlag&EMCROWACT_BOSS)==NULL) return S_OK;

	GASSERT(m_dwAType<SCROWDATA::EMMAXATTACK);
	m_pAttackProp = &(m_pCrowData->m_sCrowAttack[m_dwAType]);

	m_fAge += fElapsedTime;
	for ( int i=0; i<SCROWDATA::EMMAXATTACK; ++i )
	{
		if ( m_fACTIONDELAY[i] > 0.0f )
			m_fACTIONDELAY[i] -= fElapsedTime;
	}

	//	Note : AABB ∞ËªÅE
	//
	m_vMax = m_vPos + m_vMaxOrg;
	m_vMin = m_vPos + m_vMinOrg;

	//	Note : ∞¯∞› ∏Ò«•¿« ¿Ø»øº∫ ∞ÀªÅE
	//		(¡÷¿«) ≈∏∞π¡§∫∏ ªÁøÅEÅEπ›µÂΩ√ »£√‚«œø© ¿Ø»øº∫ ∞ÀªÅE« øÅE
	//
	bool bVALID_TAR(true);

	BOOL bCHECK_TAR = GLGaeaServer::GetInstance().ValidCheckTarget(m_pLandMan,m_TargetID);
	if ( !bCHECK_TAR )	bCHECK_TAR = false;

	if ( bCHECK_TAR && m_TargetID.emCrow==CROW_PC )
	{
		PGLCHAR pCHAR = GLGaeaServer::GetInstance().GetChar ( m_TargetID.dwID );
		if ( pCHAR )
		{
			// ¥ÅE√¡ﬂ¿Œ∞°?
			if ( pCHAR->GETCONFTING()->IsCONFRONTING() )	bVALID_TAR = false;

            // ƒ≥∏Ø≈Õ∞° º˚±ËªÛ≈¬¿Œ∞°? GM ¿∫ visible off ∂«¥¬ none ¿Ã ∞°¥…«œ¥Ÿ.
			if ( !pCHAR->IsVisibleDetect(m_bRECVISIBLE) )	bVALID_TAR = false;

			// SafeZone ¿œ∞ÊøÅE∞¯∞› ∫“∞°
			if ( pCHAR->IsSafeZone() ) bVALID_TAR = false;

			// ∏ÛΩ∫≈Õ∞° ≥°±˚›ÅE√ﬂ¿˚¿ª «œ¥¬ ∞ÊøÅE∏˜∏Ù¿Ã∏¶ πÊ¡ˆ«œ¡ÅEæ ¥¬¥Ÿ.
			SLEVEL_ETC_FUNC *pLevelEtcFunc = m_pLandMan->GetLevelEtcFunc();
			if( !(pLevelEtcFunc && pLevelEtcFunc->m_bUseFunction[EMETCFUNC_MOBCHASE]) )
			{
				//	Note : ∞˙µµ«— ∏˜∏Ù¿Ã πÊ¡ÅE
				//
				// ∂Ÿ±‚∞°¥…«— ∏˜¿Œ∞°?
				if ( bVALID_TAR && m_pCrowData->m_sAction.m_bRun )
				{
					// «ˆ¿ÅEƒ≥∏Ø≈Õ ¡÷∫Øø° ∏Ù∑¡¿÷¥¬ ∏˜¿« º˝¿⁄
					DWORD dwAmount = pCHAR->GetARoundSlot().GetAmount();
					// «ˆ¿Á ƒ≥∏Ø≈Õ ¡÷∫Øø° ∏Ù∑¡¿÷¥¬ ∏˜¿« º˝¿⁄∞° º≥¡§µ» ∞πºˆ∫∏¥Ÿ ≈©¥Ÿ∏È...
					WORD wAmount = GLCONST_CHAR::wMAXMOB_TRACKING;
					if ( IsGroup() && IsGroupLeader() || IsGroupMember() )
						wAmount = 1000;

					if ( dwAmount > wAmount )//GLCONST_CHAR::wMAXMOB_TRACKING)
					{
						// ∏˜∞ÅE≈∏∞Ÿ∞˙¿« ∞≈∏Æ∏¶ ∞ËªÅE—¥Ÿ.
						D3DXVECTOR3 vDist = m_vPos - m_vOrgTarPos;
						float fDist = D3DXVec3Length(&vDist);
						
						// ∞ËªÅE» ∞≈∏Æ∞° ∏ÅE∆Æ∑°≈∑ ∞≈∏Æ∫∏¥Ÿ ≈©¥Ÿ∏ÅE..
						if ( fDist > GLCONST_CHAR::fMOB_TRACING )
						{
							bVALID_TAR = false;

							// ∂€ºÅE¿÷¥¬ ∏˜¿Ã∂Û∏ÅE
							if ( m_pCrowData->m_sAction.m_bRun )
							{
								// ∂Ÿæ˚“ÅE
								ToRun();
							}
							
							// ª˝º∫¿ßƒ°∑Œ µπæ∆∞°∂ÅE
							MoveTo ( m_vGenPos );
						}
					}
				}
			}
		}
	}

	if ( bCHECK_TAR && m_TargetID.emCrow==CROW_SUMMON )
	{
		PGLSUMMONFIELD pSummon = GLGaeaServer::GetInstance().GetSummon( m_TargetID.dwID );		
		PGLCHAR		   pCHAR   = GLGaeaServer::GetInstance().GetChar  ( pSummon->m_dwOwner );
		if ( pCHAR )
		{
			// ¥ÅE√¡ﬂ¿Œ∞°?
			if ( pCHAR->GETCONFTING()->IsCONFRONTING() )	bVALID_TAR = false;

			// ƒ≥∏Ø≈Õ∞° º˚±ËªÛ≈¬¿Œ∞°? GM ¿∫ visible off ∂«¥¬ none ¿Ã ∞°¥…«œ¥Ÿ.
			if ( !pCHAR->IsVisibleDetect(m_bRECVISIBLE) )	bVALID_TAR = false;

			// ∏ÛΩ∫≈Õ∞° ≥°±˚›ÅE√ﬂ¿˚¿ª «œ¥¬ ∞ÊøÅE∏˜∏Ù¿Ã∏¶ πÊ¡ˆ«œ¡ÅEæ ¥¬¥Ÿ.
			SLEVEL_ETC_FUNC *pLevelEtcFunc = m_pLandMan->GetLevelEtcFunc();
			if( !(pLevelEtcFunc && pLevelEtcFunc->m_bUseFunction[EMETCFUNC_MOBCHASE]) )
			{
				//	Note : ∞˙µµ«— ∏˜∏Ù¿Ã πÊ¡ÅE
				//
				// ∂Ÿ±‚∞°¥…«— ∏˜¿Œ∞°?
				if ( bVALID_TAR && m_pCrowData->m_sAction.m_bRun )
				{
					DWORD dwAmount = pCHAR->GetARoundSlot().GetAmount();
					// ?? ??? ??? ???? ?? ??? ??? ???? ???...
					WORD wAmount = GLCONST_CHAR::wMAXMOB_TRACKING;
					if ( IsGroup() && IsGroupLeader() || IsGroupMember() )
						wAmount = 1000;

					if ( dwAmount > wAmount )//GLCONST_CHAR::wMAXMOB_TRACKING)
					{
						// ∏˜∞ÅE≈∏∞Ÿ∞˙¿« ∞≈∏Æ∏¶ ∞ËªÅE—¥Ÿ.
						D3DXVECTOR3 vDist = m_vPos - m_vOrgTarPos;
						float fDist = D3DXVec3Length(&vDist);

						// ∞ËªÅE» ∞≈∏Æ∞° ∏ÅE∆Æ∑°≈∑ ∞≈∏Æ∫∏¥Ÿ ≈©¥Ÿ∏ÅE..
						if ( fDist > GLCONST_CHAR::fMOB_TRACING )
						{
							bVALID_TAR = false;

							// ∂€ºÅE¿÷¥¬ ∏˜¿Ã∂Û∏ÅE
							if ( m_pCrowData->m_sAction.m_bRun )
							{
								// ∂Ÿæ˚“ÅE
								ToRun();
							}

							// ª˝º∫¿ßƒ°∑Œ µπæ∆∞°∂ÅE
							MoveTo ( m_vGenPos );
						}
					}
				}
			}
		}
	}
	
	// ≈∏∞Ÿ¿Ã º≠πˆªÛø°º≠ ¿Ø»ø«œ¡ÅEæ ∞≈≥™ ¥ı¿ÃªÅE√ﬂ¿˚«“ « ø‰∞° æ¯¥¬ PC ¿œ ∞ÊøÅE
	if ( !bCHECK_TAR || !bVALID_TAR )
	{
		m_bGroup = false;

		if ( m_bOnce )
		{
			GLMSG::SNETPC_REQ_TARGET_ACQUIRE NetMsg;
			NetMsg.dwGlobID = GetGlobID();
			NetMsg.dwID = EMTARGET_NULL;
			SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsg );
			m_bOnce = false;
		}
		m_dwAttPosSlot = GLARoundSlot::SLOT_SIZE;
		
		// ≈∏∞‘∆√¿ª π´»ø»≠«—¥Ÿ.
		ReSetFLAG(EMTARGET);
		m_TargetID = STARGETID(CROW_PC,GAEAID_NULL);

		// ±◊∑ÅE≈∏∞Ÿ¿Ã æ∆¡ÅE¡∏¿Á«œ∏ÅE±◊∑ÅE≈∏∞Ÿ¿ª ∞¯∞›«—¥Ÿ.
		if( IsGroupMember() )
		{
			if( m_pLandMan->GET_GROUPTARGET( GetGroupName() ).dwID != EMTARGET_NULL )
			{
				NewTarget( m_pLandMan->GET_GROUPTARGET( GetGroupName() ) );
			}
		}
	}


	// ¥Ø¡ÅEæ æ“¿∏∏ÅE
	if ( IsValidBody() )
	{
		if ( IsGroupMember())
		{
			PGLCROW pGLLeader = m_pLandMan->GET_GROUPLEADER(GetGroupName());
			if ( pGLLeader && pGLLeader->GetTargetID().dwID != EMTARGET_NULL && pGLLeader->IsValidBody() )
			{
				SetFirstTime(true);
			}
		}

		if ( m_dwNowHP==0 || m_dwNowHPSG==0 || m_dwNowHPMP==0|| m_dwNowHPPHX==0 )
		{
			//	Note : æ≤∑Ø¡˙∂ß ∫∏ªÅEπﬂª˝. ( ∞Ê«Ëƒ° + æ∆¿Ã≈€ + ±›æ◊ )
			GenerateReward ();

			//	«‡¿ß ∫Ø»≠.
			TurnAction ( GLAT_FALLING );
		}
		// ≈∏∞Ÿ¿Ã π´»ø»≠ µ«æ˙¥¬µ• ∞¯∞›æ◊º« ¡ﬂ¿Ã∏ÅE
		else if ( !IsACTION(GLAT_SHOCK) && !IsACTION(GLAT_PUSHPULL) )
		{
			if ( !IsFLAG(EMTARGET) && IsACTION(GLAT_ATTACK) )
			{
				// ¿Ø»ﬁªÛ≈¬∑Œ ∫Ø∞ÅE
				TurnAction ( GLAT_IDLE, false );
			}

			// Crow ¿« «ˆ¿ÅEªÛ≈¬∞™µÈ¿ª Update «—¥Ÿ
			GLCROWLOGIC::UPDATE_DATA ( fTime, fElapsedTime );

			if ( !m_bSTATE_STUN )
			{
				//	Note : Ω∫ƒ…¡ÅEΩ««ÅE
				RunSchedule ( fTime, fElapsedTime);
			}
		}
	}

	//	Note : æ◊º«∫∞ √≥∏Æ¿€æÅE
	//
	switch ( m_Action )
	{
	case GLAT_IDLE:
		m_fIdleTime += fElapsedTime;
		break;

	case GLAT_TALK:
		break;

	case GLAT_MOVE:
		{
			//	Note : ƒ…∏Ø¿« ¿Ãµø æ˜µ•¿Ã∆Æ.
			//
			m_actorMove.SetMaxSpeed ( GetMoveVelo() );
			hr = m_actorMove.Update ( fElapsedTime );
			if ( FAILED(hr) )	return E_FAIL;
		
			if ( !m_actorMove.PathIsActive() )
			{
				m_actorMove.Stop ();
				TurnAction ( GLAT_IDLE, false );
			}

			//	Note : Mob¿« «ˆ¿ÅE¿ßƒ° æ˜µ•¿Ã∆Æ.
			//
			m_vPos = m_actorMove.Position();

			//	Note : Mob¿« «ˆ¿ÅEπÊ«ÅEæ˜µ•¿Ã∆Æ.
			//
			D3DXVECTOR3 vMovement = m_actorMove.NextPosition();
			if ( vMovement.x != FLT_MAX && vMovement.y != FLT_MAX && vMovement.z != FLT_MAX )
			{
				D3DXVECTOR3 vDirection = vMovement - m_vPos;
				if ( !DxIsMinVector(vDirection,0.2f) )
				{
					D3DXVec3Normalize ( &vDirection, &vDirection );
					m_vDir = vDirection;
				}
			}
		}
		break;

	case GLAT_ATTACK:
		{
			if ( !AttackProcess ( fElapsedTime ) )
			{
				TurnAction ( GLAT_IDLE, false );
			}

			//	Note : ∞¯∞› πÊ«‚¿∏∑Œ »∏¿ÅE
			//
			GLACTOR* pACTOR = GLGaeaServer::GetInstance().GetTarget ( m_pLandMan, m_TargetID );
			if ( pACTOR )
			{
				D3DXVECTOR3 vDirection = pACTOR->GetPosition() - m_vPos;
				D3DXVec3Normalize ( &vDirection, &vDirection );
				m_vDir = vDirection;
			}
		}
		break;

	case GLAT_SKILL:
		{
			if ( !SkillProcess ( fElapsedTime ) )
			{
				TurnAction ( GLAT_IDLE, false );
			}
		}
		break;

	case GLAT_SHOCK:
		if ( !ShockProcess ( fElapsedTime ) )		TurnAction ( GLAT_IDLE, false );
		break;

	case GLAT_FALLING:
		{
			m_fIdleTime += fElapsedTime;

			if( m_pCrowData->m_sAction.m_bMobLink )
			{
				if ( m_fIdleTime > m_pCrowData->m_sAction.m_fMobLinkDelay )	
				{
					TurnAction ( GLAT_DIE );
					m_pLandMan->DropCrow( 
						m_pMobSchedule, 
						m_pCrowData->m_sAction.m_sMobLinkID, 
						m_vPos.x, 
						m_vPos.z,
						m_pCrowData->m_sAction.m_fMobLinkScale );
				}

			}
			else
			{
				if( m_fIdleTime > 2.0f && m_pCrowData->m_sAction.m_dwActFlag&EMCROWACT_CTFTOWER )
				{
					TurnAction ( GLAT_DIE );
				}
				else if ( m_fIdleTime > 4.0f )
				{
					TurnAction ( GLAT_DIE );
				}
			}
		}
		break;

	case GLAT_PUSHPULL:
		{
			//m_actorMove.SetMaxSpeed ( GLCONST_CHAR::fPUSHPULL_VELO );
			m_actorMove.Update ( fElapsedTime );
			if ( !m_actorMove.PathIsActive() )
			{
				m_actorMove.Stop ();
				TurnAction ( GLAT_IDLE, false );
			}

			//	Note : Mob¿« «ˆ¡¶ ¿ßƒ° æ˜µ•¿Ã∆Æ.
			//
			m_vPos = m_actorMove.Position();
		}
		break;

	case GLAT_DIE:
		{
		}
		break;
	case GLAT_GATHERING:
		break;
	};

	//	Note : Mob¿« «ˆ¡¶ ¿ßƒ° æ˜µ•¿Ã∆Æ.
	//
	m_vPos = m_actorMove.Position();

	//	Note : m_pd3dDevice ∞° ¿Ø»ø«“ ∞ÊøÅE∏ æ∆∑ß ƒ⁄µÂ∞° Ω««‡µ»¥Ÿ. ( Level Editor ø°º≠ ≈¬Ω∫∆ÆøÅE )
	//
	if ( !m_pd3dDevice )	return S_OK;

	//	Note : ø°¥œ∏ﬁ¿Ãº«, Ω∫≈≤ æ˜µ•¿Ã∆Æ.
	//
		UpateAnimation( fTime, fElapsedTime );

	//	Note : «ˆ¡¶ ¿ßƒ°øÕ πÊ«‚¿∏∑Œ Transform ∏ﬁ∆Æ∏ØΩ∫ ∞ËªÅE
	//
	D3DXMATRIX matTrans, matYRot;
	D3DXMatrixTranslation ( &matTrans, m_vPos.x, m_vPos.y, m_vPos.z );
	float fThetaY = DXGetThetaYFromDirection ( m_vDir, vDIRORIG );
	D3DXMatrixRotationY ( &matYRot, fThetaY );

	m_matTrans = matYRot * matTrans;

	return S_OK;
}

HRESULT GLCrow::Render ( LPDIRECT3DDEVICEQ pd3dDevice, CLIPVOLUME &cv, BOOL bRendAABB )
{
	HRESULT hr;

	if ( !COLLISION::IsCollisionVolume ( cv, m_vMax, m_vMin ) )	return S_OK;
	if ( bRendAABB ) EDITMESHS::RENDERAABB ( pd3dDevice, m_vMax, m_vMin );	//	≈◊Ω∫∆ÆøÅE
	
	hr = m_pSkinChar->Render ( pd3dDevice, m_matTrans );
	if ( FAILED(hr) )	return hr;

	return S_OK;
}

void GLCrow::ReceivePushPull ( const D3DXVECTOR3 &vMovePos, const bool bReact , const bool bAdjustSpeed , const float fSpeed, const  bool  bDash, const  bool  bTeleport ) //add pushpull
{
	if ( !IsValidBody () )		return;
	if ( m_pCrowData->IsIgnoreShock()) return;

//	if ( m_pCrowData->IsChip() ) return;

	if ( m_pCrowData->IsKnock() ) return; //All Boss must be unable to Pull or Push -- Ocram Networks

	SNATIVEID sID(8,21);
	PCROWDATA pCrowData = GLCrowDataMan::GetInstance().GetCrowData ( sID );
	if ( pCrowData ) return;

	//	Note : π–∑¡≥Ø ¿ßƒ°∑Œ ¿Ãµø Ω√µµ.
	//
	BOOL bSucceed = m_actorMove.GotoLocation
	(
		D3DXVECTOR3(vMovePos.x,vMovePos.y+5,vMovePos.z),
		D3DXVECTOR3(vMovePos.x,vMovePos.y-5,vMovePos.z)
	);

	if ( bSucceed )
	{
		//	Note : π–∑¡≥™¥¬ ø¢º« Ω√¿€.
		//
		m_TargetID.vPos = vMovePos;
		if ( bReact && !m_pCrowData->m_sAction.m_dwActFlag&EMCROWACT_CTFTOWER )  //add pushpull
		{
			TurnAction ( GLAT_PUSHPULL );
		}

		if ( bDash || bTeleport ) SetPosition ( m_TargetID.vPos );

		//	Note : π–∏Æ¥¬ º”µµ º≥¡§.
		//
		if  ( bAdjustSpeed ){ m_actorMove.SetMaxSpeed ( fSpeed );  //add pushpull
		}else{
			m_actorMove.SetMaxSpeed ( GLCONST_CHAR::fPUSHPULL_VELO );
		}

		//	Note : ∏ﬁΩ√¡ˆ ≥ªøÎ º≥¡§.
		//
		GLMSG::SNET_PUSHPULL_BRD NetMsgBRD;
		NetMsgBRD.emCrow = GETCROW();
		NetMsgBRD.dwID = m_dwGlobID;
		NetMsgBRD.vMovePos = vMovePos;
		NetMsgBRD.fSpeed = fSpeed;

		//	Note : [¿⁄Ω≈¿« ¡÷∫Ø Char] ø°∞‘ Msg∏¶ ¿¸¥ﬁ.
		//
		SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsgBRD );
	}
}

// 2006-04-03 Jgkim
DWORD GLCrow::ReceiveDamage ( const EMCROW emACrow, const DWORD dwAID, const DWORD dwDamage, const BOOL bShock )
{
	//	Note : Damage ∞™¿Ã ¿÷¿ª∂ß. 0 ¿œ∂ß¥¬ miss πﬂª˝ ( ≈∏∞Ÿ ¡ˆ¡§¿ª ¿ß«ÿ »£√‚µ . )
	if ( m_dwNowHP > 0 )
	{
		DWORD dwDxHp;

		//	Damage ±‚∑œ.
		if ( emACrow == CROW_PC )
		{
			PGLCHAR pChar = GLGaeaServer::GetInstance().GetChar ( dwAID );
			if( pChar && m_pCrowData->m_sAction.m_dwActFlag&EMCROWACT_CTFTOWER )
				dwDxHp = GLCROWLOGIC::RECEIVE_DAMAGE ( (WORD)dwDamage,pChar->GETCHARDATA().m_wSchool );
			else dwDxHp = GLCROWLOGIC::RECEIVE_DAMAGE ( (WORD)dwDamage );

			if ( m_pLandMan->m_bTowerWarsMap )
			{
				GLTowerWars* pSW = GLTowerWarsFieldMan::GetInstance().Find( m_pLandMan->m_dwTowerWarsMapID );
				if( pSW && pChar && pSW->IsBattle() )
				{
					pSW->AddSWPDamageScore( pChar->m_dwGaeaID, dwDxHp );

					/*GLMSG::SNET_TOWERWARS_CTFPOINT_UPDATE NetMsg;
					NetMsg.bDamagePoint = true;
					NetMsg.bHealPoint = false;
					NetMsg.bResuPoint = false;
					NetMsg.bKillPoint = false;		
					NetMsg.dwDamage = dwDxHp;
					NetMsg.dwHeal = 0;
					GLGaeaServer::GetInstance().SENDTOPLAYERCLIENT_ONMAP ( pChar->m_pLandMan->GetMapID().dwID,pChar->m_dwCharID, &NetMsg);*/
				}
			}

			AddDamageLog      ( m_cDamageLog, dwAID, pChar->GetUserID(), dwDxHp );
			AddDamageLogParty ( m_cDamageLogParty, pChar->m_dwPartyID, dwDxHp );
		}
		else
		{
			dwDxHp = GLCROWLOGIC::RECEIVE_DAMAGE ( (WORD)dwDamage );
		}

		//  º“»ØºÅE∞¯∞›¿œ ∞ÊøÅESummonDamageLogø° ±‚∑œ«—¥Ÿ.
		if ( emACrow == CROW_SUMMON )
		{
			PGLSUMMONFIELD pSummon = GLGaeaServer::GetInstance().GetSummon ( dwAID );
			if( pSummon )
			{
				AddDamageLog      ( m_cSummonDamageLog, dwAID, pSummon->GetCtrlID(), dwDxHp );
				AddDamageLogParty ( m_cDamageLogParty, pSummon->m_pOwner->m_dwPartyID, dwDxHp );
			}
		}

		//	Note : √Ê∞› πﬁ¿Ω.
		if( !m_pCrowData->IsIgnoreShock() )
		{
			if ( bShock )	
			{
				TurnAction ( GLAT_SHOCK );
			}
		}

		m_sAssault.emCrow = emACrow;
		m_sAssault.dwID = dwAID;
	}

	//	Note :≈∏∞Ÿ¿Ã ¡∏¡¶«œ¡ÅEæ ¿ª∂ß ∞¯∞›¿⁄∞° ¿÷¿∏∏ÅE≈∏∞Ÿ¿∏∑Œ µ˚”œ Ω√µµ.
	//		¡æ¿ÅE≈∏∞Ÿ¿Ã ∞¯∞› πÅEß π€ø° ¿÷¿ª ∂ß¥¬ ≈∏∞Ÿ πŸ≤ﬁ.
	//
	HRESULT hrESCAPE = S_OK;
	EMCROWACT_UP emCROWACT = GetActPattern();

	if ( EMCROWACT_UP_ESCAPE == emCROWACT )
		hrESCAPE = ESCAPE ( STARGETID(emACrow,dwAID), dwDamage );
	
	if ( EMCROWACT_UP_ESCAPE != emCROWACT || hrESCAPE!=S_OK )
	{
		BOOL bChangeTar = FALSE;
		if ( !IsFLAG(EMTARGET) )											bChangeTar = TRUE;
		else if ( m_pCrowData->IsTarShort() && (!IsFLAG(EMATTACKABLE)) )	bChangeTar = TRUE;

		if ( bChangeTar || CheckGroupAttack() )
		{
			PGLCHAR pTarget = NULL;
			if ( emACrow==CROW_PC )		pTarget = GLGaeaServer::GetInstance().GetChar(dwAID);
			if ( pTarget )
			{
				STARGETID sTARID(CROW_PC,pTarget->GetCtrlID(),pTarget->GetPosition());
				NewTarget ( sTARID, TRUE );
			}
		}
	}

	if ( emACrow == CROW_PC )
	{
		PGLCHAR pChar = GLGaeaServer::GetInstance().GetChar ( dwAID );
		if(pChar)
		{
			switch(pChar->GetSchool())
			{
				case 0: return m_dwNowHPSG;	break;
				case 1: return m_dwNowHPMP;	break;
				case 2: return m_dwNowHPPHX;	break;
			}
		}
	}
	else
	return m_dwNowHP;
}


// Original Code
/*
DWORD GLCrow::ReceiveDamage ( const EMCROW emACrow, const DWORD dwAID, const DWORD dwDamage, const BOOL bShock )
{
	//	Note : ¥ÅEÃ¡ÅE∞™¿Ã ¿÷¿ª∂ß. 0 ¿œ∂ß¥¬ miss πﬂª˝ ( ≈∏∞Ÿ ¡ˆ¡§¿ª ¿ß«ÿ »£√‚µ . )
	//
	if ( m_dwNowHP > 0 )
	{
		//	Note : ¥ÅEÃ¡ÅE¿˚øÅE
		DWORD dwDxHp = GLCROWLOGIC::RECEIVE_DAMAGE ( (WORD)dwDamage );

		//	¥ÅEÃ¡ÅE±‚∑œ.
		if ( emACrow == CROW_PC )
		{
			PGLCHAR pChar = GLGaeaServer::GetInstance().GetChar ( dwAID );
			AddDamageLog ( m_cDamageLog, dwAID, pChar->m_dwUserID, dwDxHp );
		}

		//	Note : √Ê∞› πﬁ¿Ω.
		if( !m_pCrowData->IsIgnoreShock() )
		{
			if ( bShock )	
			{
				TurnAction ( GLAT_SHOCK );
			}
		}

		m_sAssault.emCrow = emACrow;
		m_sAssault.dwID = dwAID;
	}

	//	Note :≈∏∞Ÿ¿Ã ¡∏¡¶«œ¡ÅEæ ¿ª∂ß ∞¯∞›¿⁄∞° ¿÷¿∏∏ÅE≈∏∞Ÿ¿∏∑Œ µ˚”œ Ω√µµ.
	//		¡æ¿ÅE≈∏∞Ÿ¿Ã ∞¯∞› πÅEß π€ø° ¿÷¿ª ∂ß¥¬ ≈∏∞Ÿ πŸ≤ﬁ.
	//
	HRESULT hrESCAPE = S_OK;
	EMCROWACT_UP emCROWACT = GetActPattern();

	if ( EMCROWACT_UP_ESCAPE == emCROWACT )
		hrESCAPE = ESCAPE ( STARGETID(emACrow,dwAID), dwDamage );
	
	if ( EMCROWACT_UP_ESCAPE != emCROWACT || hrESCAPE!=S_OK )
	{
		BOOL bChangeTar = FALSE;
		if ( !IsFLAG(EMTARGET) )											bChangeTar = TRUE;
		else if ( m_pCrowData->IsTarShort() && (!IsFLAG(EMATTACKABLE)) )	bChangeTar = TRUE;

		if ( bChangeTar )
		{
			PGLCHAR pTarget = NULL;
			if ( emACrow==CROW_PC )		pTarget = GLGaeaServer::GetInstance().GetChar(dwAID);
			if ( pTarget )
			{
				STARGETID sTARID(CROW_PC,pTarget->GetCtrlID(),pTarget->GetPosition());
				NewTarget ( sTARID );
			}
		}
	}

	return m_dwNowHP;
}
*/


void GLCrow:: SetOwner( SW_SCHOOL_DATA emOWNER )
{
	m_emOWNER = emOWNER;

	GLMSG::SNETCROW_OWNER NetMsg;
	NetMsg.emOWNER	= m_emOWNER;
	NetMsg.dwGlobID = m_dwGlobID;
	SendMsgViewAround ( (NET_MSG_GENERIC*) &NetMsg );
}
