#include "StdAfx.h"
#include "GLGaeaClient.h"
#include "GLContrlMsg.h"
#include "DxGlobalStage.h"
#include "GLItemMan.h"
#include "./GLFactEffect.h"
#include "./GLStrikeM.h"

#include "../RanClientUILib/Interface/DamageDisplay.h"
#include "../RanClientUILib/Interface/InnerInterface.h"
#include "../RanClientUILib/Interface/UITextcontrol.h"
#include "../RanClientUILib/Interface/GameTextcontrol.h"

#include "../../EngineLib/DxEffect/Char/DxEffCharData.h"
#include "DxEffGroupPlayer.h"
#include "DxShadowMap.h"
#include "DxEnvironment.h"
#include "GLStrikeM.h"

#include "GLSummonClient.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void GLSummonClient::ReqSummonSetPosion()
{
	if ( GLTradeClient::GetInstance().Valid() )		return;

	//	Note : ∞¯∞›¡ﬂ¿Ã≥™ Ω∫≈≥ Ω√¿ÅE¡ﬂø° ΩΩ∑‘ ∫Ø∞Ê¿ª ºˆ«ÅE«“ ºÅEæ¯¥Ÿ∞ÅE∫Ω.
	//
	if ( IsACTION(GLAT_ATTACK) || IsACTION(GLAT_SKILL) ) return;

	SITEMCUSTOM sHoldItemCustom = m_pOwner->GET_HOLD_ITEM ();
	SITEMCUSTOM	sSlotItemCustom = GetPosionItem();

	//	SLOT <-> HOLD
	if ( sHoldItemCustom.sNativeID != NATIVEID_NULL() && sSlotItemCustom.sNativeID != NATIVEID_NULL() )
	{
		SITEM* pHoldItem = GLItemMan::GetInstance().GetItem ( sHoldItemCustom.sNativeID );
		if ( !pHoldItem ) 
		{
			// ¿œπ› ø¿∑ÅE
			return;
		}

		if ( !CheckPosionItem( pHoldItem->sBasicOp.sNativeID ) ) return;

		SITEM* pSlotItem = GLItemMan::GetInstance().GetItem ( sSlotItemCustom.sNativeID );
		if ( !pSlotItem ) 
		{
			// ¿œπ› ø¿∑ÅE
			return;
		}

		if ( !GLGaeaClient::GetInstance().GetCharacter()->ACCEPT_ITEM ( sHoldItemCustom.sNativeID ) )
		{
			return;
		}

		// ≈∏¿‘¿Ã ¥Ÿ∏£∏ÅE
		if ( pHoldItem->sSuitOp.emSuit != pSlotItem->sSuitOp.emSuit ) return;

		GLMSG::SNET_SUMMON_REQ_SLOT_EX_HOLD NetMsg;
		NETSENDTOFIELD ( &NetMsg );
	}
	// HOLD -> SLOT
	else if ( sHoldItemCustom.sNativeID != NATIVEID_NULL() )
	{
		SITEM* pHoldItem = GLItemMan::GetInstance().GetItem ( sHoldItemCustom.sNativeID );
		if ( !pHoldItem ) 
		{
			// ¿œπ› ø¿∑ÅE
			return;
		}

		if ( !CheckPosionItem( pHoldItem->sBasicOp.sNativeID ) ) return;

		if ( !GLGaeaClient::GetInstance().GetCharacter()->ACCEPT_ITEM ( sHoldItemCustom.sNativeID ) )
		{
			return;
		}

		// ≈∏¿‘¿Ã ¥Ÿ∏£∏ÅE
		//if ( pHoldItem->sSuitOp.emSuit != emSUIT ) return;

		GLMSG::SNET_SUMMON_REQ_HOLD_TO_SLOT NetMsg;
		NETSENDTOFIELD ( &NetMsg );
	}
	// SLOT -> HOLD
	/*else if ( sSlotItemCustom.sNativeID != NATIVEID_NULL() )
	{
		GLMSG::SNET_SUMMON_REQ_SLOT_TO_HOLD NetMsg;
		NETSENDTOFIELD ( &NetMsg );
	}*/

		return;

}

void GLSummonClient::ReqPosionRemove()
{
	WORD wPosX(0), wPosY(0);
	SITEMCUSTOM	sSlotItemCustom = GetPosionItem();

	SITEM* pSlotItem = GLItemMan::GetInstance().GetItem ( sSlotItemCustom.sNativeID );
	if ( !pSlotItem ) 
	{
		// ¿œπ› ø¿∑ÅE
		return;
	}

	//BOOL bOk = m_pOwner->m_cInventory.FindInsrtable ( pSlotItem->sBasicOp.wInvenSizeX, pSlotItem->sBasicOp.wInvenSizeY, wPosX, wPosY );
	//if ( !bOk )
	//{
	//	//	¿ŒπÅEÃ ∞°µÊ¬˛¿Ω.
	//	return;
	//}

	GLMSG::SNET_SUMMON_REQ_REMOVE_SLOTITEM NetMsg;

	NETSENDTOFIELD ( &NetMsg );
}


void GLSummonClient::ReqGoto ( D3DXVECTOR3 vTarPos, bool bTracing )
{
	GLMSG::SNET_SUMMON_REQ_GOTO NetMsg;

	D3DXVECTOR3 vPos(vTarPos);

	// «√∑°±◊ ∏Æº¬
	ReSetAllSTATE ();


	// ¡÷¿Œ¿« ¿Ãµø≈∏∞Ÿ
	STARGETID sTarget = m_pOwner->GetTargetID ();

	// ¡÷¿Œ∫∏¥Ÿ æ’º≠¿÷¿∏∏ÅE
	D3DXVECTOR3 vOwnerPos = m_pOwner->GetPosition ();
	D3DXVECTOR3 vDist = m_vPos - sTarget.vPos;
	float fSummonToTar = D3DXVec3Length(&vDist);
	vDist = vOwnerPos - sTarget.vPos;
	float fOwnerToTar = D3DXVec3Length(&vDist);

	vDist = vOwnerPos - m_vPos;
	float fDist = D3DXVec3Length(&vDist);

	/*STARGETID sTargetID;
	if( bTracing )
	{
		sTargetID = m_sTargetID;
	}
	m_sTargetID.RESET();*/


		// ¿Ãµø¡ﬂ¿œ∂ß∏∏ ±‚¥Ÿ∑¡¡ÿ¥Ÿ
		if ( fDist < m_fWalkArea && m_pOwner->IsACTION ( GLAT_MOVE ) )
		{
			m_actorMove.Stop ();
			m_pSkinChar->SELECTANI ( AN_GUARD_N, AN_SUB_NONE );
			SetSTATE ( EM_SUMMONACT_WAIT );
			TurnAction( GLAT_IDLE );

			GLMSG::SNET_SUMMON_REQ_STOP NetMsg;
			NetMsg.dwGUID = m_dwGUID;
			NetMsg.dwFlag = m_dwActionFlag;
			NetMsg.vPos	  = m_vPos;
			NETSENDTOFIELD ( &NetMsg );
			return;
		}

		BOOL bGoto = m_actorMove.GotoLocation ( vTarPos+D3DXVECTOR3(0,+10,0),
			vTarPos+D3DXVECTOR3(0,-10,0) );

		// »§Ω√ ∏¯∞°¥¬ ∞˜¿Ã∏ÅE
		if ( !bGoto )
		{
			for ( WORD i = 0; i < 8; ++i )
			{
				D3DXVECTOR3 vRandPos = m_RandPos[i];

				vTarPos = vPos + vRandPos;
				bGoto = m_actorMove.GotoLocation ( vTarPos+D3DXVECTOR3(0,+10,0),
					vTarPos+D3DXVECTOR3(0,-10,0) );
				if ( bGoto ) break;
			}
		}

		if ( !bGoto ) 
		{
			m_actorMove.Stop ();
			m_pSkinChar->SELECTANI ( AN_GUARD_N, AN_SUB_NONE );
			SetSTATE ( EM_SUMMONACT_STOP );
			TurnAction( GLAT_IDLE );
			return;
		}

		// [¡÷¿«] 
		// ¿Ãµø∏ﬁΩ√¡ÅE¿ÅE€Ω√ «◊ªÅE¡÷¿Œ¿« Run ªÛ≈¬∏¶ µ˚∂Ûæﬂ «—¥Ÿ.
		if( bTracing )
		{
			ReSetAllSTATE();
			SetSTATE ( EM_SUMMONACT_TRACING );
			SetMoveState ( TRUE );
		}else{
			SetSTATE ( EM_SUMMONACT_MOVE );
			SetMoveState ( m_pOwner->IsSTATE ( EM_ACT_RUN ) );
		}

		NetMsg.dwGUID  = m_dwGUID;
		NetMsg.vCurPos = m_vPos;
		NetMsg.vTarPos = vTarPos;
		NetMsg.dwFlag  = m_dwActionFlag;


		//	m_sTargetID = sTargetID;

		NETSENDTOFIELD ( &NetMsg );
}

void GLSummonClient::ReqStop ( bool bStopAttack )
{
	if( !IsSTATE(EM_SUMMONACT_TRACING) )
		ReSetAllSTATE ();
	SetSTATE ( EM_SUMMONACT_STOP );
	TurnAction( GLAT_IDLE );

	m_actorMove.Stop ();
	m_pSkinChar->SELECTANI ( AN_GUARD_N, AN_SUB_NONE );
	m_sSkillTARGET.RESET ();

	GLMSG::SNET_SUMMON_REQ_STOP NetMsg;
	NetMsg.dwGUID      = m_dwGUID;
	NetMsg.dwFlag      = m_dwActionFlag;
	NetMsg.vPos	       = m_vPos;
	NetMsg.bStopAttack = bStopAttack;
	NETSENDTOFIELD ( &NetMsg );
}


void GLSummonClient::MsgHpUpdate( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_SUMMON_UPDATE_HP *pNetMsg = (GLMSG::SNET_SUMMON_UPDATE_HP *)nmg;
	m_dwNowHP = pNetMsg->dwHP;
}

void GLSummonClient::MsgProcess ( NET_MSG_GENERIC* nmg )
{
	switch ( nmg->nType )
	{
	case NET_MSG_SUMMON_ATTACK:				 MsgAttack ( nmg );	break;
	case NET_MSG_SUMMON_REQ_SLOT_EX_HOLD_FB: MsgSlotExHold ( nmg ); break;
	case NET_MSG_SUMMON_REQ_HOLD_TO_SLOT_FB: MsgHoldToSlot ( nmg ); break;
	case NET_MSG_SUMMON_REMOVE_SLOTITEM_FB:  MsgRemoveSlotItem ( nmg ); break;
	case NET_MSG_SUMMON_UPDATE_HP:			 MsgHpUpdate ( nmg ); break;

	case NET_MSG_GCTRL_SKILLFACT_BRD:		 MsgSkillFact ( nmg ); break;
	case NET_MSG_GCTRL_SKILLHOLD_BRD:
		{
			GLMSG::SNETPC_SKILLHOLD_BRD *pNetMsg = (GLMSG::SNETPC_SKILLHOLD_BRD *)nmg;

			//	¡ˆº”«ÅEΩ∫≈≥¿« ∞ÊøÅEΩ∫≈≥ ∆—≈Õ √ﬂ∞°µ .
			if ( pNetMsg->skill_id != SNATIVEID(false) )
			{
				RECEIVE_SKILLFACT ( pNetMsg->skill_id, pNetMsg->wLEVEL, pNetMsg->wSELSLOT );
				FACTEFF::NewSkillFactEffect ( STARGETID(CROW_SUMMON,m_dwGUID,m_vPos), m_pSkinChar, pNetMsg->skill_id, m_matTrans, m_vDir );
			}
		}
		break;

	case NET_MSG_GCTRL_SKILLHOLD_RS_BRD:
		{
			GLMSG::SNETPC_SKILLHOLD_RS_BRD *pNetMsg = (GLMSG::SNETPC_SKILLHOLD_RS_BRD *)nmg;

			//	Note : Ω∫≈≥ fact µÈ¿ª ¡æ∑ÅE
			//		πŸ∑Œ ∏ÆªÅE«œ¡ÅEæ ∞ÅEø©±‚º≠ Ω√∞£ ¡∂¡æ«œø© ¡§ªÅE¡æ∑·µ«∞‘ «‘. ( ¿Ã∆—∆Æ ¡æ∑ÅE∂ßπÆ. )
			for ( int i=0; i<SKILLFACT_SIZE; ++i )
			{
				if ( pNetMsg->bRESET[i] )
				{
					FACTEFF::DeleteSkillFactEffect ( STARGETID(CROW_SUMMON,m_dwGUID,m_vPos), m_pSkinChar, m_sSKILLFACT[i].sNATIVEID );

					DISABLESKEFF(i);
				}
			}
		}
		break;

	case NET_MSG_GCTRL_STATEBLOW_BRD:
		{
			GLMSG::SNETPC_STATEBLOW_BRD *pNetMsg = (GLMSG::SNETPC_STATEBLOW_BRD *)nmg;

			//	Note : "¥‹µ∂ªÛ≈¬¿ÃªÅE¿œ ∞ÊøÅE¥‹µ∂ »ø∞ÅE∏µŒ ≤Ù±ÅE
			if ( pNetMsg->emBLOW <= EMBLOW_SINGLE )
				FACTEFF::DeleteBlowSingleEffect ( STARGETID(CROW_SUMMON,m_dwGUID,m_vPos), m_pSkinChar, m_sSTATEBLOWS );

			//	Note : ªÛ≈¬ ¿ÃªÅE√ﬂ∞°.
			SSTATEBLOW *pSTATEBLOW = NULL;
			if ( pNetMsg->emBLOW <= EMBLOW_SINGLE )		pSTATEBLOW = &m_sSTATEBLOWS[0];
			else										pSTATEBLOW = &m_sSTATEBLOWS[pNetMsg->emBLOW-EMBLOW_SINGLE];
			pSTATEBLOW->emBLOW = pNetMsg->emBLOW;
			pSTATEBLOW->fAGE = pNetMsg->fAGE;
			pSTATEBLOW->fSTATE_VAR1 = pNetMsg->fSTATE_VAR1;
			pSTATEBLOW->fSTATE_VAR2 = pNetMsg->fSTATE_VAR2;

			//	Note : »ø∞ÅEª˝º∫.
			FACTEFF::NewBlowEffect ( STARGETID(CROW_SUMMON,m_dwGUID,m_vPos), m_pSkinChar, pSTATEBLOW->emBLOW, m_matTrans, m_vDir );
		}
		break;

	case NET_MSG_GCTRL_CURESTATEBLOW_BRD:
		{
			GLMSG::SNETPC_CURESTATEBLOW_BRD *pNetMsg = (GLMSG::SNETPC_CURESTATEBLOW_BRD *)nmg;

			for ( int i=0; i<EMBLOW_MULTI; ++i )
			{
				EMSTATE_BLOW emBLOW = m_sSTATEBLOWS[i].emBLOW;
				if ( emBLOW==EMBLOW_NONE )		continue;

				EMDISORDER emDIS = STATE_TO_DISORDER(emBLOW);
				if ( !(pNetMsg->dwCUREFLAG&emDIS) )				continue;

				DISABLEBLOW(i);
				FACTEFF::DeleteBlowEffect ( STARGETID(CROW_SUMMON,m_dwGUID,m_vPos), m_pSkinChar, emBLOW );
			}
		}
		break;

	case NET_MSG_GCTRL_PUSHPULL_BRD:
		{
			GLMSG::SNET_PUSHPULL_BRD *pNetMsg = (GLMSG::SNET_PUSHPULL_BRD *)nmg;
			const D3DXVECTOR3 &vMovePos = pNetMsg->vMovePos;

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
				m_sTargetID.vPos = vMovePos;
				TurnAction ( GLAT_PUSHPULL );


				//	Note : π–∏Æ¥¬ º”µµ º≥¡§.
				//
				m_actorMove.SetMaxSpeed ( GLCONST_CHAR::fPUSHPULL_VELO );//add dash - SeiferXIII 6/30/13
			}
		}
		break;

	case NET_MSG_GCTRL_POSITIONCHK_BRD:
		{
			GLMSG::SNET_POSITIONCHK_BRD *pNetNsg = (GLMSG::SNET_POSITIONCHK_BRD *)nmg;
			m_vServerPos = pNetNsg->vPOS;
		}
		break;

	default:
		CDebugSet::ToListView ( "[WARNING]GLSummonField::MsgProcess Illigal Message(%d)", nmg->nType );
		break;
	};
}

void GLSummonClient::MsgSkillFact( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNETPC_SKILLFACT_BRD *pNetMsg = (GLMSG::SNETPC_SKILLFACT_BRD *)nmg;

	if( pNetMsg->emCrow != CROW_SUMMON ) return;

	GLOGICEX::VARIATION ( m_dwNowHP, m_pSummonCrowData->m_dwHP, pNetMsg->nVAR_HP );
	GLOGICEX::VARIATION ( m_wNowMP, m_pSummonCrowData->m_wMP, pNetMsg->nVAR_MP );
	GLOGICEX::VARIATION ( m_wNowSP, m_pSummonCrowData->m_wSP, pNetMsg->nVAR_SP );

	//	µ•πÃ¡ÅE∏ﬁΩ√¡ÅE
	if ( pNetMsg->nVAR_HP < 0 )
	{
		if ( pNetMsg->dwDamageFlag & DAMAGE_TYPE_SHOCK )	
		{
			TurnAction( GLAT_SHOCK );
		}
		else					ReceiveSwing ();

		D3DXVECTOR3 vPos = GetPosBodyHeight();
		//Added by   | 21-6-2012 | Bypass damage
		//CInnerInterface::GetInstance().SetDamage( vPos, static_cast<WORD>(-pNetMsg->nVAR_HP), pNetMsg->dwDamageFlag, UI_ATTACK );
		CInnerInterface::GetInstance().SetDamage( vPos, static_cast<DWORD>(-pNetMsg->nVAR_HP), pNetMsg->dwDamageFlag, UI_ATTACK );

		//	Note : πÊæ˚Ÿ∫≈≥¿« ¿Ã∆Â∆Æ∞° ¿÷¿ª∂ß πﬂµøΩ√≈¥.
		STARGETID sACTOR(pNetMsg->sACTOR.GETCROW(),pNetMsg->sACTOR.GETID());
		sACTOR.vPos = GLGaeaClient::GetInstance().GetTargetPos ( sACTOR );

		SKT_EFF_HOLDOUT ( sACTOR, pNetMsg->dwDamageFlag );

		if ( pNetMsg->dwDamageFlag & DAMAGE_TYPE_CRUSHING_BLOW )
		{
			// ∞≠«—≈∏∞› ¿Ã∆Â∆Æ

			D3DXVECTOR3 vDIR = sACTOR.vPos - m_vPos;

			D3DXVECTOR3 vDIR_ORG(1,0,0);
			float fdir_y = DXGetThetaYFromDirection ( vDIR, vDIR_ORG );

			D3DXMATRIX matTrans;
			D3DXMatrixRotationY ( &matTrans, fdir_y );
			matTrans._41 = m_vPos.x;
			matTrans._42 = m_vPos.y + 10.0f;
			matTrans._43 = m_vPos.z;

			//	Note : ¿⁄±ÅE¿ßƒ° ¿Ã∆Â∆Æ πﬂª˝Ω√≈¥.
			DxEffGroupPlayer::GetInstance().NewEffGroup ( GLCONST_CHAR::strCRUSHING_BLOW_EFFECT.c_str(), matTrans, &sACTOR );
		}


	}

	//	»˙∏µ ∏ﬁΩ√¡ÅE
	//if ( pNetMsg->nVAR_HP > 0 )
	//{
	//	CPlayInterface::GetInstance().InsertText ( GetPosition(), static_cast<WORD>(pNetMsg->nVAR_HP), pNetMsg->bCRITICAL, 1 );
	//}
}

void GLSummonClient::MsgSlotExHold ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_SUMMON_REQ_SLOT_EX_HOLD_FB* pNetMsg = ( GLMSG::SNET_SUMMON_REQ_SLOT_EX_HOLD_FB* ) nmg;

	switch ( pNetMsg->emFB )
	{
	case EMSUMMON_REQ_SLOT_EX_HOLD_FB_FAIL:
		CInnerInterface::GetInstance().PrintMsgText ( 
			NS_UITEXTCOLOR::NEGATIVE, ID2GAMEINTEXT("EMSUMMON_REQ_SLOT_EX_HOLD_FB_FAIL") );

		break;

	case EMSUMMON_REQ_SLOT_EX_HOLD_FB_OK:
		{
			// ¿Â¬¯µ» æ∆¿Ã≈€ BackUp
			SITEMCUSTOM sSlotItemCustom = GetPosionItem();

			// º’ø°µÅEæ∆¿Ã≈€¿ª ∆÷ø°∞‘ ¿Â¬¯Ω√≈∞∞ÅE
			SetPosionItem ( m_pOwner->GET_HOLD_ITEM ().sNativeID );

			// ¿Â¬¯µ∆¥ÅEæ∆¿Ã≈€¿ª º’ø° µÁ¥Ÿ
			//			m_pOwner->HOLD_ITEM ( sSlotItemCustom );
			m_pOwner->RELEASE_HOLD_ITEM();
		}
		break;

	case EMSUMMON_REQ_SLOT_EX_HOLD_FB_NOMATCH:
		CInnerInterface::GetInstance().PrintMsgText ( 
			NS_UITEXTCOLOR::NEGATIVE, ID2GAMEINTEXT("EMSUMMON_REQ_SLOT_EX_HOLD_FB_NOMATCH") );
		break;

	case EMSUMMON_REQ_SLOT_EX_HOLD_FB_INVALIDITEM:
		CInnerInterface::GetInstance().PrintMsgText ( 
			NS_UITEXTCOLOR::NEGATIVE, ID2GAMEINTEXT("EMSUMMON_REQ_SLOT_EX_HOLD_FB_INVALIDITEM") );
		break;
	};
}

void GLSummonClient::MsgHoldToSlot ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_SUMMON_REQ_HOLD_TO_SLOT_FB* pNetMsg = ( GLMSG::SNET_SUMMON_REQ_HOLD_TO_SLOT_FB* ) nmg;

	switch ( pNetMsg->emFB )
	{
	case EMSUMMON_REQ_SLOT_EX_HOLD_FB_FAIL:
		CInnerInterface::GetInstance().PrintMsgText ( 
			NS_UITEXTCOLOR::NEGATIVE, ID2GAMEINTEXT("EMSUMMON_REQ_SLOT_EX_HOLD_FB_FAIL") );
		break;

	case EMSUMMON_REQ_SLOT_EX_HOLD_FB_OK:
		{
			// º’ø°µÅEæ∆¿Ã≈€¿ª ∆÷ø°∞‘ ¿Â¬¯Ω√≈∞∞ÅE
			SetPosionItem ( m_pOwner->GET_HOLD_ITEM ().sNativeID );

			// ∆÷ƒ´µÂ¿« ¡§∫∏µµ ∞ªΩ≈«ÿ¡ÿ¥Ÿ.
			// º’ø°µÅEæ∆¿Ã≈€¿ª ¡¶∞≈«œ∞ÅE
			m_pOwner->RELEASE_HOLD_ITEM ();
		}
		break;

	case EMSUMMON_REQ_SLOT_EX_HOLD_FB_NOMATCH:
		CInnerInterface::GetInstance().PrintMsgText ( 
			NS_UITEXTCOLOR::NEGATIVE, ID2GAMEINTEXT("EMSUMMON_REQ_SLOT_EX_HOLD_FB_NOMATCH") );
		break;

	case EMSUMMON_REQ_SLOT_EX_HOLD_FB_INVALIDITEM:
		CInnerInterface::GetInstance().PrintMsgText ( 
			NS_UITEXTCOLOR::NEGATIVE, ID2GAMEINTEXT("EMSUMMON_REQ_SLOT_EX_HOLD_FB_INVALIDITEM") );
		break;
	};
}


void GLSummonClient::MsgRemoveSlotItem ( NET_MSG_GENERIC* nmg )
{
	GLMSG::SNET_SUMMON_REQ_REMOVE_SLOTITEM_FB* pNetMsg = ( GLMSG::SNET_SUMMON_REQ_REMOVE_SLOTITEM_FB* ) nmg;

	WORD wPosX(0), wPosY(0);

	SITEMCUSTOM	sSlotItemCustom = GetPosionItem();

	SITEM* pSlotItem = GLItemMan::GetInstance().GetItem ( sSlotItemCustom.sNativeID );
	if ( !pSlotItem ) 
	{
		// ¿œπ› ø¿∑ÅE
		return;
	}

	// ΩΩ∑‘æ∆¿Ã≈€ ¡¶∞≈
	ReSetPosionItem();

}

void GLSummonClient::MsgAttack ( NET_MSG_GENERIC* nmg )
{
	// ¿Ãµø¡ﬂ¿Ã∏ÅE¿Ãµø¿ª ∏∂ƒ£»ƒ ∞¯∞› ∏º«¿ª √ÅE—¥Ÿ.
	if ( m_actorMove.PathIsActive () ) 
	{
		/*if( IsSTATE( EM_SUMMONACT_TRACING ) )
		{
			m_actorMove.Stop();
		}else*/{
			return;
		}
	}

	GLMSG::SNET_SUMMON_ATTACK* pNetMsg = ( GLMSG::SNET_SUMMON_ATTACK* ) nmg;

	m_dwAType   = pNetMsg->dwAType;

	if ( pNetMsg->sTarID.emCrow == CROW_PC )
	{
		GLLandManClient* pLandMan = GLGaeaClient::GetInstance().GetActiveMap ();
		PGLCHARCLIENT pChar = pLandMan->GetChar ( pNetMsg->sTarID.dwID );
		if ( pChar )
		{
			// πÊ«ÅE¿ÅEØ
			D3DXVECTOR3 vDirection = pChar->GetPosition () - m_vPos;
			D3DXVec3Normalize ( &m_vDir, &vDirection );
			m_vDir = vDirection;

			ReSetAllSTATE ();
			SetSTATE ( EM_SUMMONACT_ATTACK );
			TurnAction( GLAT_ATTACK );
			m_pSkinChar->SELECTANI ( AN_ATTACK, AN_SUB_NONE );
		}

		// PC∞° ∞¯∞›«ﬂ¿ª ∞ÊøÅE° ∏ﬁΩ√¡ˆ∞° «•Ω√µ»¥Ÿ.
		if( m_sTargetID != pNetMsg->sTarID )
		{
			CInnerInterface::GetInstance().PrintConsoleTextDlg ( ID2GAMEINTEXT("PK_SUMMON_PLAYHOSTILE_ADD"), pChar->GetName() );
		}
	}
	else if ( pNetMsg->sTarID.emCrow == CROW_MOB )
	{
		GLLandManClient* pLandMan = GLGaeaClient::GetInstance().GetActiveMap ();
		PGLCROWCLIENT pCrow = pLandMan->GetCrow ( pNetMsg->sTarID.dwID );
		if ( pCrow )
		{
			// πÊ«ÅE¿ÅEØ
			D3DXVECTOR3 vDirection = pCrow->GetPosition () - m_vPos;
			D3DXVec3Normalize ( &m_vDir, &vDirection );
			m_vDir = vDirection;

			ReSetAllSTATE ();
			SetSTATE ( EM_SUMMONACT_ATTACK );
			TurnAction( GLAT_ATTACK );
			m_pSkinChar->SELECTANI ( AN_ATTACK, AN_SUB_NONE );
		}
	}
	else if ( pNetMsg->sTarID.emCrow == CROW_SUMMON )
	{
		GLLandManClient* pLandMan = GLGaeaClient::GetInstance().GetActiveMap ();
		PGLANYSUMMON pSummon = pLandMan->GetSummon ( pNetMsg->sTarID.dwID );
		if ( pSummon )
		{
			// πÊ«ÅE¿ÅEØ
			D3DXVECTOR3 vDirection = pSummon->GetPosition () - m_vPos;
			D3DXVec3Normalize ( &m_vDir, &vDirection );
			m_vDir = vDirection;

			ReSetAllSTATE ();
			SetSTATE ( EM_PETACT_ATTACK );
			TurnAction( GLAT_ATTACK );
			m_pSkinChar->SELECTANI ( AN_ATTACK, AN_SUB_NONE );
		}
	}

	m_sTargetID = pNetMsg->sTarID;

	// ≈∏¿Ã∏” √ ±‚»≠
	m_fAttackTimer = 0.0f;
}