#include "stdafx.h"
#include "./GLogicEx.h"
#include "./GLItemMan.h"
#include "./GLGaeaServer.h"
#include "./GLChar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void GLCROWLOGIC::RESET_DATA ()
{
	int i(0);

	m_sNativeID = SNATIVEID(0,0);
	m_pCrowData = NULL;

	for ( i=0; i< SCROWDATA::EMMAXATTACK; ++i )
		m_fACTIONDELAY[i] = 0.0f;

	for ( i=0; i< SKILLFACT_SIZE; ++i )
		m_sSKILLFACT[i] = SSKILLFACT();

	m_dwHOLDBLOW = NULL;

	for ( i=0; i< EMBLOW_MULTI; ++i )
		m_sSTATEBLOWS[i] = SSTATEBLOW();
	
	m_fSTATE_MOVE = 1.0f;
	m_fSTATE_DELAY = 1.0f;
	m_fSTATE_DAMAGE = 1.0f;
	
	m_bSTATE_PANT = false;
	m_bSTATE_STUN = false;
	m_bINVISIBLE = false;
	m_bRECVISIBLE = false;

	m_fATTVELO = 0.0f;
	m_fSKILL_MOVE = 0.0f;

	m_nSUM_HIT = 0;
	m_nSUM_AVOID = 0;

	m_nSUM_DEFENSE = 0;
	m_nDX_DAMAGE = 0;

	m_nSUM_PIERCE = 0;
	m_fSUM_TARRANGE = 0;

	m_fDamageRate = 1.0f;
	m_fDefenseRate = 1.0f;

	m_dwAType = 0;
	
	m_dwNowHP = 0;
	m_wNowMP = 0;
	m_wNowSP = 0;

	m_idACTIVESKILL = false;
	m_wACTIVESKILL_LVL = 0;

	m_fIncHP = 0.0f;
	m_fIncMP = 0.0f;
	m_fIncSP = 0.0f;

	m_sDamageSpec.RESET();
	m_sDefenseSkill.RESET();
	m_sSUMRESIST.RESET();
	m_dwNowHPSG = 0;
	m_dwNowHPMP = 0;
	m_dwNowHPPHX = 0;

	m_bImmune = false;
}

const char* GLCROWLOGIC::GETNAME ()
{
	GASSERT(m_pCrowData);
	return m_pCrowData->GetName();
}

int GLCROWLOGIC::GETFORCE_LOW () const
{
	int nDamage = ( m_pCrowData->m_sCrowAttack[m_dwAType].sDamage.dwLow );
	
	if ( (nDamage+m_nDX_DAMAGE) < 0 )	return 0;
	return nDamage + m_nDX_DAMAGE;
}

int GLCROWLOGIC::GETFORCE_HIGH () const
{
	int nDamage = ( m_pCrowData->m_sCrowAttack[m_dwAType].sDamage.dwHigh );

	if ( (nDamage+m_nDX_DAMAGE) < 0 )	return 0;
	return nDamage + m_nDX_DAMAGE;
}

WORD GLCROWLOGIC::GETSKILLRANGE_APPLY ( const GLSKILL &sSKILL, const WORD dwLEVEL ) const
{
	const SKILL::CDATA_LVL &sDATA_LVL = sSKILL.m_sAPPLY.sDATA_LVL[dwLEVEL];

	WORD dwRANGE = sDATA_LVL.wAPPLYRANGE;
	if ( sSKILL.m_sBASIC.emAPPLY==SKILL::EMAPPLY_PHY_LONG )		dwRANGE += (WORD) GETSUM_TARRANGE();
	return dwRANGE;
}

BOOL GLCROWLOGIC::INIT_DATA ()
{
	m_sNativeID = m_pCrowData->sNativeID;
	m_dwNowHP = m_pCrowData->m_dwHP;
	m_wNowMP = m_pCrowData->m_wMP;

	m_dwNowHPSG = m_pCrowData->m_dwHP;
	m_dwNowHPMP = m_pCrowData->m_dwHP;
	m_dwNowHPPHX = m_pCrowData->m_dwHP;
	return TRUE;
}

BOOL GLCROWLOGIC::CHECKHIT ( const STARGETID &cTargetID, const GLLandMan* pLandMan )
{
	int nAVOID = 0;
	EMBRIGHT emBright;
	if ( cTargetID.emCrow==CROW_PC )
	{
		PGLCHAR pChar = GLGaeaServer::GetInstance().GetChar ( cTargetID.dwID );
		nAVOID = pChar->GETAVOID ();
		emBright = pChar->GETBRIGHT();
	}
	else if ( cTargetID.emCrow==CROW_MOB || cTargetID.emCrow==CROW_NPC )
	{
		PGLCROW pCrow = pLandMan->GetCrow ( cTargetID.dwID );
		nAVOID = pCrow->GETAVOID ();
		emBright = pCrow->GETBRIGHT();
	}
	else if ( cTargetID.emCrow==CROW_PET )	// PetData
	{
	}
	else if ( cTargetID.emCrow==CROW_SUMMON )
	{
		PGLSUMMONFIELD pSummon = GLGaeaServer::GetInstance().GetSummon ( cTargetID.dwID );
		nAVOID = pSummon->GETAVOID ();
		emBright = pSummon->GETBRIGHT();
	}
	else
	{
		GASSERT(0&&"∞˙”¡µ«¡ÅEæ ¿∫ CROW");
	}

	EM_BRIGHT_FB bFB = GLOGICEX::GLSPACEGAP ( GETBRIGHT(), emBright, pLandMan->GETBRIGHT() );
	int nHitRate = GLOGICEX::GLHITRATE ( GETHIT(), nAVOID, bFB );

	return ( nHitRate > (RANDOM_POS*100) );
}

DWORD GLCROWLOGIC::CALCDAMAGE ( int& rResultDAMAGE, const DWORD dwGaeaID, const STARGETID &cTargetID, const GLLandMan* pLandMan,
							 const GLSKILL* pSkill, DWORD dwskill_lev, DWORD dwWeatherFlag, DWORD dwDivCount )
{
	GLACTOR *pActor = GLGaeaServer::GetInstance().GetTarget ( pLandMan, cTargetID );
	if ( !pActor )	return FALSE;

	int nDEFENSE = pActor->GetDefense ();
	int nDEFAULT_DEFENSE = pActor->GetBodyDefense ();
	int nITEM_DEFENSE = pActor->GetItemDefense ();

	int nLEVEL = pActor->GetLevel ();
	float fSTATE_DAMAGE = pActor->GETSTATE_DAMAGE ();
	const SRESIST &sRESIST = pActor->GETRESIST ();

	GLPADATA gdDamage;
	gdDamage.dwLow = GETFORCE_LOW();
	gdDamage.dwHigh = GETFORCE_HIGH();

	DWORD dwDamageFlag = DAMAGE_TYPE_NONE;
	bool bShock = false;
	bool bCrushingBlow = false;
	bool bCritical = false; 
	bool bPsyDamage = true;

	DAMAGE_SPEC	sDamageSpec = pActor->GetDamageSpec();
	float fDamageReduce = sDamageSpec.m_fPsyDamageReduce;
	float fDamageReflection = sDamageSpec.m_fPsyDamageReflection;
	float fDamageReflectionRate = sDamageSpec.m_fPsyDamageReflectionRate;

	DEFENSE_SKILL sDefenseSkill = pActor->GetDefenseSkill();

	if ( pSkill )
	{
		const SKILL::CDATA_LVL &sSKILL_DATA = pSkill->m_sAPPLY.sDATA_LVL[dwskill_lev];

		float fRESIST_G = 0;
		switch ( pSkill->m_sBASIC.emAPPLY )
		{
			//	±Ÿ¡¢ ∞¯∞›.
		case SKILL::EMAPPLY_PHY_SHORT:
			fRESIST_G = GLCONST_CHAR::fRESIST_PHYSIC_G;
			break;

			//	¿Â∞≈∏Æ ∞¯∞›.
		case SKILL::EMAPPLY_PHY_LONG:
			fRESIST_G = GLCONST_CHAR::fRESIST_PHYSIC_G;
			
			fDamageReflection = 0.0f;
			fDamageReflectionRate = 0.0f;
			break;

			//	∏∂π˝ ∞¯∞›.
    	case SKILL::EMAPPLY_MAGIC:
			nDEFENSE = 0;						//	∏∂π˝ ∞¯∞›¿œ∂ß¥¬ ¿œπ› πÊæ˚”¬ π´Ω√µ .
			nDEFAULT_DEFENSE = 0;				//	∏∂π˝ ∞¯∞›¿œ∂ß¥¬ ¿œπ› πÊæ˚”¬ π´Ω√µ .
			nITEM_DEFENSE = 0;					//	∏∂π˝ ∞¯∞›¿œ∂ß¥¬ ¿œπ› πÊæ˚”¬ π´Ω√µ .
			fRESIST_G = GLCONST_CHAR::fRESIST_G;
			
			fDamageReduce = sDamageSpec.m_fMagicDamageReduce;
			fDamageReflection = sDamageSpec.m_fMagicDamageReflection;
			fDamageReflectionRate = sDamageSpec.m_fMagicDamageReflectionRate;
			bPsyDamage = false;
			break;
		};

		short nRESIST = sRESIST.GetElement ( pSkill->m_sAPPLY.emELEMENT );
		if ( nRESIST>99 )	nRESIST = 99;

		float fPOWER = GLOGICEX::WEATHER_ELEMENT_POW ( pSkill->m_sAPPLY.emELEMENT, dwWeatherFlag, pLandMan->IsWeatherActive() );
		int nVAR = abs ( int(sSKILL_DATA.fBASIC_VAR*fPOWER) );
		nVAR = nVAR - (int) ( nVAR*nRESIST*0.01f*fRESIST_G );
		if ( nVAR<0 )	nVAR = 0;

		gdDamage.VAR_PARAM ( nVAR );
	}

	//	∞¯∞›∑¬. ∫Ø»≠¿≤ π›øµ.
	gdDamage.dwLow = int ( gdDamage.dwLow * m_fDamageRate );
	gdDamage.dwHigh = int ( gdDamage.dwHigh * m_fDamageRate );

	//	Note : √ﬂ∞° ∫∏¡§ƒ° ªÅEÅE
	int nExtFORCE = 0;
	int ndxLvl = nLEVEL - GETLEVEL();
	if ( ndxLvl > 0 )		nExtFORCE = int(RANDOM_POS*ndxLvl*0.1f);

	if ( ndxLvl > 5 )		ndxLvl = 5;
	if ( ndxLvl < -5 )		ndxLvl = -5;

	//	Note : Critical πﬂª˝ »Æ¿≤.
	int nPerHP = ((GETHP()*100)/GETMAXHP());
	if ( nPerHP <= 10 )	nPerHP = 10;
	int nPercentCri = 1000 / nPerHP - 10 + ndxLvl;
	if ( nPercentCri > (int)GLCONST_CHAR::dwCRITICAL_MAX )		nPercentCri = GLCONST_CHAR::dwCRITICAL_MAX;
	if ( nPercentCri < 0 )	nPercentCri = 0;

	//	≈©∏Æ∆ºƒ√ πﬂª˝ ø©∫Œ ∆«¥‹.
	if ( nPercentCri > (RANDOM_POS*100) )	bCritical = true;


	//	¥ÅEÃ¡ÅE√÷¥ÅE√÷º“∞™ ªÁ¿Ã¿« ∑£¥˝ ¥ÅEÃ¡ÅE∞·¡§.
	int  nDAMAGE_NOW = 0;
	nDAMAGE_NOW = int ( gdDamage.dwLow + (gdDamage.dwHigh-gdDamage.dwLow)*RANDOM_POS );

	int nDAMAGE_OLD = ( nDAMAGE_NOW + nExtFORCE );
	
	//	√÷¿ÅEºˆøÅE¥ÅEÃ¡ÅEªÅEÅE
	int nNetDAMAGE = int ( nDAMAGE_OLD*(1.0f-GLCONST_CHAR::fLOW_SEED_DAMAGE) - nDEFENSE );
	if ( nNetDAMAGE < 0 )	nNetDAMAGE = 0;

	if ( nNetDAMAGE > 0 )	rResultDAMAGE = int ( nDAMAGE_OLD - nDEFENSE );
	else					rResultDAMAGE = int ( nNetDAMAGE + (nDAMAGE_OLD*GLCONST_CHAR::fLOW_SEED_DAMAGE)*RANDOM_POS );
	rResultDAMAGE = int(rResultDAMAGE*fSTATE_DAMAGE);

	//	πÊæ˚Õ∏ ¥ÅEÃ¡ÅE»˙ÿˆ¿≤ π›øµ.
	float fRATE = ( 1.0f - nDEFAULT_DEFENSE*nITEM_DEFENSE / GLCONST_CHAR::fDAMAGE_DEC_RATE );
	if ( fRATE > 1.0f )		fRATE = 1.0f;
	if ( fRATE < 0.0f )		fRATE = 0.0f;
	rResultDAMAGE = int(rResultDAMAGE*fRATE);

	if ( bCritical )	rResultDAMAGE = int ( rResultDAMAGE * GLCONST_CHAR::dwCRITICAL_DAMAGE * 0.01f );

	//	µ•πÃ¡ÅE»˙ÿÅE
	if ( fDamageReduce > 0.0f ) 
	{
		int nDamageReduce = (int) ( ( (rResultDAMAGE * fDamageReduce) * nLEVEL ) / GLCONST_CHAR::wMAX_LEVEL );
		rResultDAMAGE -= nDamageReduce;
		
		if ( bPsyDamage ) dwDamageFlag += DAMAGE_TYPE_PSY_REDUCE;
		else dwDamageFlag += DAMAGE_TYPE_MAGIC_REDUCE;
	}


	//	µ•πÃ¡ÅEπ›ªÅE∞ËªÅE
	if ( fDamageReflectionRate > 0.0f )
	{
		if ( fDamageReflectionRate > (RANDOM_POS*1) )
		{
			int nDamageReflection = (int) ( ( (rResultDAMAGE * fDamageReflection) * nLEVEL ) / GLCONST_CHAR::wMAX_LEVEL );

			if ( nDamageReflection > 0 ) 
			{
				if ( bPsyDamage ) dwDamageFlag += DAMAGE_TYPE_PSY_REFLECTION;
				else dwDamageFlag += DAMAGE_TYPE_MAGIC_REFLECTION;


				// ««∞›¿⁄ ¿‘¿Âø°º≠ µ•πÃ¡ˆ∏¶ ¥ŸΩ√ ∫∏≥Ω¥Ÿ.
				STARGETID sActor(GETCROW(),dwGaeaID);
				pActor->DamageReflectionProc( nDamageReflection, sActor );
			}
		}
	}

	//	πﬂµø Ω∫≈≥
	if ( sDefenseSkill.m_dwSkillID != NATIVEID_NULL() )
	{
		if ( sDefenseSkill.m_fRate > (RANDOM_POS*1) )
		{
			STARGETID sActor(GETCROW(),dwGaeaID);
			pActor->DefenseSkill( sDefenseSkill.m_dwSkillID, 
								  sDefenseSkill.m_wLevel, 
								  sActor );
		}
	}

	

	if ( rResultDAMAGE <= 1 )
	{
		bCritical = false;
		rResultDAMAGE = 1;
	}

	if ( dwDivCount>1 )
	{
		rResultDAMAGE /= dwDivCount;
	}

	bShock = GLOGICEX::CHECKSHOCK ( GETLEVEL(), nLEVEL, rResultDAMAGE, bCritical );

	if ( bShock )			dwDamageFlag += DAMAGE_TYPE_SHOCK;
	if ( bCritical )		dwDamageFlag += DAMAGE_TYPE_CRITICAL;

	return dwDamageFlag;
}

//added by   | 21-6-2012 | Bypass damage
//DWORD GLCROWLOGIC::RECEIVE_DAMAGE ( const WORD wDamage )
DWORD GLCROWLOGIC::RECEIVE_DAMAGE ( const DWORD wDamage )
{
	DWORD dwOLD = m_dwNowHP;

	DECREASE(m_dwNowHP,(DWORD)wDamage);
	
	return (dwOLD>m_dwNowHP) ? (dwOLD-m_dwNowHP) : 0;
}

DWORD GLCROWLOGIC::RECEIVE_DAMAGE ( const DWORD wDamage,const WORD wSchool )
{
	DWORD dwOLD = m_dwNowHP;
	switch( wSchool )
	{
		case 0: 
		{
			dwOLD = m_dwNowHPSG;
			DECREASE(m_dwNowHPSG,(DWORD)wDamage);
			return (dwOLD>m_dwNowHPSG) ? (dwOLD-m_dwNowHPSG) : 0;
		}
		break;
		case 1:
		{
			dwOLD = m_dwNowHPMP;
			DECREASE(m_dwNowHPMP,(DWORD)wDamage);
			return (dwOLD>m_dwNowHPMP) ? (dwOLD-m_dwNowHPMP) : 0;
		}
		break;
		case 2:
		{
			dwOLD = m_dwNowHPPHX;
			DECREASE(m_dwNowHPPHX,(DWORD)wDamage);
			return (dwOLD>m_dwNowHPPHX) ? (dwOLD-m_dwNowHPPHX) : 0;
		}
		break;
		default:
		{
			dwOLD = m_dwNowHP;	
			DECREASE(m_dwNowHP,(DWORD)wDamage);
			return (dwOLD>m_dwNowHP) ? (dwOLD-m_dwNowHP) : 0;
		}
		break;
	}
}
void GLCROWLOGIC::UPDATE_DATA ( float fTime, float fElapsedTime, BOOL bClient )
{
	const float fUNIT_TIME = 1.0f;		//	»∏∫π ¥‹¿ß Ω√∞£.
	float m_fINCR_HP = 0.3f * 0.01f;	//	¥‹¿ßΩ√∞£¥ÅEHP »∏∫π¿≤(%)
	float m_fINCR_MP = 0.3f * 0.01f;	//	¥‹¿ßΩ√∞£¥ÅEMP »∏∫π¿≤(%)
	float m_fINCR_SP = 0.5f;			//	¥‹¿ßΩ√∞£¥ÅEMP »∏∫π¿≤(%)

	m_nSUM_HIT = static_cast<int>(m_pCrowData->m_wHitRate);
	m_nSUM_AVOID = static_cast<int>(m_pCrowData->m_wAvoidRate);

	m_nSUM_DEFENSE = static_cast<int>(m_pCrowData->m_wDefense);

	m_fSTATE_MOVE = 1.0f;
	m_fSTATE_DELAY = 1.0f;

	m_fSTATE_DAMAGE = 1.0f;

	m_bSTATE_PANT = false;
	m_bSTATE_STUN = false;
	m_bINVISIBLE = false;
	m_bRECVISIBLE = false;

	m_fATTVELO = 0.0f;
	m_fSKILL_MOVE = 0.0f;

	m_nDX_DAMAGE = 0;

	m_fSUM_TARRANGE = 0;
	m_nSUM_PIERCE = 0;

	m_fDamageRate = 1.0f;
	m_fDefenseRate = 1.0f;

	m_sDamageSpec.RESET();
	m_sDefenseSkill.RESET();

	m_sSUMRESIST = m_pCrowData->m_sResist;

	m_bImmune = false;

	for ( int i=0; i<SKILLFACT_SIZE; ++i )
	{
		SSKILLFACT &sSKEFF = m_sSKILLFACT[i];
		if ( sSKEFF.sNATIVEID==NATIVEID_NULL() )	continue;

		sSKEFF.fAGE -= fElapsedTime;

		//	≈¨∂Û¿Ãæ∆Æ∞° æ∆¥“ ∞ÊøÅEø©±‚º≠ Ω∫≈≥ ¿Ã∆Â∆Æ∏¶ ∫Ò»∞º∫»≠, ≈¨∂Û¿Ãæ∆Æ¥¬ UpdateSkillEffect()ø°º≠ «‘.
		if ( !bClient && sSKEFF.fAGE <= 0.0f )		DISABLESKEFF(i);

		switch ( sSKEFF.emTYPE )
		{
		case SKILL::EMFOR_VARHP:
			m_fIncHP += (fElapsedTime/fUNIT_TIME) * (sSKEFF.fMVAR);
			break;

		case SKILL::EMFOR_VARMP:
			m_fIncMP += (fElapsedTime/fUNIT_TIME) * (sSKEFF.fMVAR);
			break;

		case SKILL::EMFOR_VARSP:
			m_fIncSP += (fElapsedTime/fUNIT_TIME) * (sSKEFF.fMVAR);
			break;

		case SKILL::EMFOR_VARAP:
			m_fIncHP += (fElapsedTime/GLCONST_CHAR::fUNIT_TIME) * (sSKEFF.fMVAR);
			m_fIncMP += (fElapsedTime/GLCONST_CHAR::fUNIT_TIME) * (sSKEFF.fMVAR);
			m_fIncSP += (fElapsedTime/GLCONST_CHAR::fUNIT_TIME) * (sSKEFF.fMVAR);
			break;

		case SKILL::EMFOR_DEFENSE:
			m_nSUM_DEFENSE += (int) sSKEFF.fMVAR;
			break;

		case SKILL::EMFOR_HITRATE:
			m_nSUM_HIT += int(sSKEFF.fMVAR);
			break;

		case SKILL::EMFOR_AVOIDRATE:
			m_nSUM_AVOID += int(sSKEFF.fMVAR);
			break;

		case SKILL::EMFOR_VARDAMAGE:
			m_nDX_DAMAGE += int(sSKEFF.fMVAR);
			break;

		case SKILL::EMFOR_VARDEFENSE:
			m_nSUM_DEFENSE += int(sSKEFF.fMVAR);
			break;

		case SKILL::EMFOR_RESIST:
			m_sSUMRESIST += int(sSKEFF.fMVAR);
			break;
		};

		for( unsigned s=0;s<SKILL::SAPPLY::MAX_DESCRIPTOR;++s)
		{
			const SSKILLFACT::IMPACT_DESCRIPTOR &desc = sSKEFF.adon[s];
			if( sSKEFF.GetAdon( desc.emADDON ) != &desc )	continue;

			switch ( desc.emADDON )
			{
			case EMIMPACTA_HITRATE:
				m_nSUM_HIT += int(desc.fADDON_VAR);
				break;

			case EMIMPACTA_AVOIDRATE:
				m_nSUM_AVOID += int(desc.fADDON_VAR);
				break;

			case EMIMPACTA_DAMAGE:
				m_nDX_DAMAGE += int(desc.fADDON_VAR);
				break;

			case EMIMPACTA_DEFENSE:
				m_nSUM_DEFENSE += int(desc.fADDON_VAR);
				break;

			case EMIMPACTA_VARHP:
				m_fIncHP += desc.fADDON_VAR*fElapsedTime;
				break;

			case EMIMPACTA_VARMP:
				m_fIncMP += desc.fADDON_VAR*fElapsedTime;
				break;

			case EMIMPACTA_VARSP:
				m_fIncSP += desc.fADDON_VAR*fElapsedTime;
				break;

			case EMIMPACTA_VARAP:
				m_fIncHP += desc.fADDON_VAR*fElapsedTime;
				m_fIncMP += desc.fADDON_VAR*fElapsedTime;
				m_fIncSP += desc.fADDON_VAR*fElapsedTime;
				break;

			case EMIMPACTA_DAMAGE_RATE:
				m_fDamageRate += desc.fADDON_VAR;
				break;

			case EMIMPACTA_DEFENSE_RATE:
				m_fDefenseRate += desc.fADDON_VAR;
				break;

			case EMIMPACTA_RESIST:
				m_sSUMRESIST += int(desc.fADDON_VAR);
				break;
			};
		}
		
		m_dwHOLDBLOW = NULL;
		for( unsigned s=0;s<SKILL::SAPPLY::MAX_DESCRIPTOR;++s)
		{
			const SSKILLFACT::SPEC_DESCRIPTOR &desc = sSKEFF.spec[s];
			if( sSKEFF.GetSpec( desc.emSPEC ) != &desc )	continue;
			switch ( desc.emSPEC )
			{
			case EMSPECA_NONBLOW:
				m_dwHOLDBLOW = desc.dwSPECFLAG;
				break;
			case EMSPECA_IMMUNE:		//dmk14 | 9-11-16 | immune
				m_bImmune = true;
				break;

			case EMSPECA_MOVEVELO:
				m_fSKILL_MOVE += desc.fSPECVAR1;
				break;

			case EMSPECA_INVISIBLE:
				m_bINVISIBLE = true;
				break;

			case EMSPECA_RECVISIBLE:
				m_bRECVISIBLE = true;
				break;

			case EMSPECA_ATTACKVELO:
				//	∞¯∞› º”µµ ∞Ë≥‰¿Ãπ«∑Œ ( ∞¯∞› Ω√∞£¿ª -0.1 (-10%) ∞®º“ Ω√≈∞±ÅE¿ß«ÿº≠¥¬ ∫Œ»£ π›¿ÅEª «œø©æﬂ«‘. )
				m_fATTVELO -= desc.fSPECVAR1;
				break;
			
			case EMSPECA_PSY_DAMAGE_REDUCE:
				if ( m_sDamageSpec.m_fPsyDamageReduce < desc.fSPECVAR1 )
					m_sDamageSpec.m_fPsyDamageReduce = desc.fSPECVAR1;
				break;
			
			case EMSPECA_MAGIC_DAMAGE_REDUCE:
				if ( m_sDamageSpec.m_fMagicDamageReduce < desc.fSPECVAR1 )
					m_sDamageSpec.m_fMagicDamageReduce = desc.fSPECVAR1;
				break;
			
			case EMSPECA_PSY_DAMAGE_REFLECTION:
				if ( m_sDamageSpec.m_fPsyDamageReflection < desc.fSPECVAR1 )
				{
					m_sDamageSpec.m_fPsyDamageReflection = desc.fSPECVAR1;
					m_sDamageSpec.m_fPsyDamageReflectionRate = desc.fSPECVAR2;
				}
				break;
			
			case EMSPECA_MAGIC_DAMAGE_REFLECTION:
				if ( m_sDamageSpec.m_fMagicDamageReflection < desc.fSPECVAR1 )
				{
					m_sDamageSpec.m_fMagicDamageReflection = desc.fSPECVAR1;
					m_sDamageSpec.m_fMagicDamageReflectionRate = desc.fSPECVAR2;
				}
				break;
			case EMSPECA_DEFENSE_SKILL_ACTIVE:
				{
					m_sDefenseSkill.m_dwSkillID = desc.dwNativeID;
					m_sDefenseSkill.m_wLevel = desc.dwSPECFLAG;
					m_sDefenseSkill.m_fRate = desc.fSPECVAR1;
				}
				break;

			case EMSPECA_STUN:
				{
					m_fATTVELO = 0.0f;
					m_bSTATE_STUN = true;
				}
				break;
			};
		}
	}

	for ( i=0; i<EMBLOW_MULTI; ++i )
	{
		SSTATEBLOW &sSTATEBLOW = m_sSTATEBLOWS[i];
		if ( sSTATEBLOW.emBLOW == EMBLOW_NONE )		continue;

		sSTATEBLOW.fAGE -= fElapsedTime;
		if ( !bClient && sSTATEBLOW.fAGE <= 0.0f )	DISABLEBLOW(i);

		switch ( sSTATEBLOW.emBLOW )
		{
		case EMBLOW_NUMB:
			m_fSTATE_MOVE += sSTATEBLOW.fSTATE_VAR1;			//	¿Ãµøº”µµ ∞®º“.
			m_fSTATE_DELAY += sSTATEBLOW.fSTATE_VAR2;			//	µÙ∑°¿Ã ¡ı∞°.
			break;

		case EMBLOW_STUN:
			m_fSTATE_MOVE = 0.0f;								//	±‚¿˝.
			m_bSTATE_PANT = true;
			m_bSTATE_STUN = true;
			break;

		case EMBLOW_STONE:
			m_fSTATE_MOVE += sSTATEBLOW.fSTATE_VAR1;			//	¿Ãµøº”µµ ∞®º“.
			m_fIncHP += (sSTATEBLOW.fSTATE_VAR2*fElapsedTime);
			break;

		case EMBLOW_BURN:
			m_fIncHP += (sSTATEBLOW.fSTATE_VAR2*fElapsedTime);	//	¡ˆº”≈∏∞›
			break;

		case EMBLOW_FROZEN:
			m_fSTATE_MOVE += sSTATEBLOW.fSTATE_VAR1;			//	¿Ãµøº”µµ ∞®º“.
			m_fSTATE_DAMAGE += sSTATEBLOW.fSTATE_VAR2;			//	≈∏∞›¡ı∆ÅE
			break;

		case EMBLOW_MAD:
			m_nSUM_HIT = 30;
			m_nSUM_AVOID = 30;
			m_bSTATE_PANT = true;
			break;

		case EMBLOW_POISON:
			m_fIncHP += (sSTATEBLOW.fSTATE_VAR2*fElapsedTime);	//	¡ˆº”≈∏∞›
			break;

		case EMBLOW_CURSE:
			m_fIncHP += (sSTATEBLOW.fSTATE_VAR2*fElapsedTime);	//	¡ˆº”≈∏∞›
			m_fINCR_MP = 0.0f;
			break;
		};
	}

	m_fATTVELO += m_fSTATE_MOVE;

	if ( m_pCrowData->IsInVisible() )	m_bINVISIBLE = true;
	if ( m_pCrowData->IsRecVisible() )	m_bRECVISIBLE = true;

	//	πÊæ˚”¬. ∫Ø»≠¿≤ π›øµ.
	m_nSUM_DEFENSE = int ( m_nSUM_DEFENSE * m_fDefenseRate );
	//	πÊæ˚”¬¿Ã - ∞™¿ª ∞°¡ˆ¡ÅEæ ∞‘.
	if ( m_nSUM_DEFENSE < 0 )			m_nSUM_DEFENSE = 1;

	m_sSUMRESIST.LIMIT();

	//	MP ¡ı∞°¿≤¿Ã æ¯¿ª∂ß.
	if ( (m_fINCR_MP==0.0f) && (m_fIncMP>0) )		m_fIncMP = 0;

	//	Note : √º∑¬ ∫Ø»≠.
	//
	float fElap = (fElapsedTime/fUNIT_TIME);
	GLOGICEX::UPDATE_POINT ( m_dwNowHP, m_fIncHP, GETMAXHP(), fElap*(GETMAXHP()*m_fINCR_HP), 1 );
	GLOGICEX::UPDATE_POINT ( m_wNowMP, m_fIncMP, GETMAXMP(), fElap*(GETMAXMP()*m_fINCR_MP), 0 );
	GLOGICEX::UPDATE_POINT ( m_wNowSP, m_fIncSP, GETMAXSP(), fElap*(GETMAXSP()*m_fINCR_SP), 0 );
}

float GLCROWLOGIC::GETATTVELO ()
{
	return m_fATTVELO<0.0f?0.0f:m_fATTVELO;
}

float GLCROWLOGIC::GETMOVEVELO ()
{
	float fMOVE = m_fSTATE_MOVE + m_fSKILL_MOVE;
	return fMOVE<0.0f?0.0f:fMOVE;
}

void GLCROWLOGIC::SETACTIVESKILL ( SNATIVEID skill_id, WORD wLevel )
{
	m_idACTIVESKILL = skill_id;
	m_wACTIVESKILL_LVL = wLevel;
}

EMSKILLCHECK GLCROWLOGIC::CHECHSKILL ( DWORD dwAType,  bool bNotLearn )
{
	GASSERT(dwAType<SCROWDATA::EMMAXATTACK);

	SNATIVEID skill_id;
	WORD wskill_lev = 0;
	WORD wStrikeNum = 0;
	if ( bNotLearn )
	{
		skill_id = m_sDefenseSkill.m_dwSkillID;
		wskill_lev = m_sDefenseSkill.m_wLevel;
	}
	else
	{
        const SCROWATTACK &sATTACK = m_pCrowData->m_sCrowAttack[dwAType];
		skill_id = sATTACK.skill_id;
		wskill_lev = sATTACK.skill_lev;

		//	Note : Ω∫≈≥ µÙ∑°¿Ã ≈∏¿”¿Ã ¡ˆ≥¥¥¬¡ÅE¡°∞À.
		//
		if ( m_fACTIONDELAY[dwAType] > 0.0f )	
			return EMSKILL_DELAYTIME; // Ω∫≈≥ µÙ∑°¿Ã Ω√∞£¿Ã ¡ˆ≥™¡ÅEæ ¿Ω.
	}




	//	Note : Ω∫≈≥ ¡§∫∏ ∞°¡Æø».
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( skill_id.wMainID, skill_id.wSubID );
	if ( !pSkill )															return EMSKILL_UNKNOWN;
	SKILL::CDATA_LVL &sSKILL_DATA = pSkill->m_sAPPLY.sDATA_LVL[wskill_lev];

	//	Note : ªÁøÅE“ ºÅE¿÷¥¬ Ω∫≈≥¡æ∑˘¿Œ¡ÅE∞ÀªÅE
	//if ( pSkill->m_sBASIC.emROLE!=SKILL::EMROLE_NORMAL )					return EMSKILL_UNKNOWN;

	//	Note : ±‚√  √º∑¬ º“∏∑Æ ¡°∞À.
	//if ( GETHP() <= sSKILL_DATA.wUSE_HP*wStrikeNum )						return EMSKILL_NOTHP;
	//if ( GETMP() < sSKILL_DATA.wUSE_MP*wStrikeNum )							return EMSKILL_NOTMP;

	//	NEED : «‚»ƒ ∆ƒ∆ºΩ∫≈≥¿Ã ±∏º∫µ«æ˙¿ª∂ß.
	//
	//sSKILL_DATA.wUSE_HP_PTY;
	//sSKILL_DATA.wUSE_MP_PTY;

	//WORD wDisSP = sSKILL_DATA.wUSE_SP;
	//if ( GETSP() < wDisSP*wStrikeNum )									return EMSKILL_NOTSP;

	//	NEED : «‚»ƒ ∆ƒ∆ºΩ∫≈≥¿Ã ±∏º∫µ«æ˙¿ª∂ß.
	//
	//sSKILL_DATA.wUSE_SP_PTY;

	return EMSKILL_OK;
}

void GLCROWLOGIC::ACCOUNTSKILL ( WORD wStrikeNum )
{
	//	Ω∫≈≥ ¡§∫∏ ∞°¡Æø».
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( m_idACTIVESKILL.wMainID, m_idACTIVESKILL.wSubID );
	SKILL::CDATA_LVL &sSKILL_DATA = pSkill->m_sAPPLY.sDATA_LVL[m_wACTIVESKILL_LVL];

	//	Ω∫≈≥ µÙ∑°¿Ã µ˚”œ.
	float fDelayTime = GLOGICEX::SKILLDELAY(pSkill->m_sBASIC.dwGRADE,m_wACTIVESKILL_LVL,GETLEVEL(),sSKILL_DATA.fDELAYTIME);
	
	//	Note : ªÛ≈¬¿ÃªÛ¿« µÙ∑°¿Ã ∞®æ».
	m_fACTIONDELAY[m_dwAType] = fDelayTime * m_fSTATE_DELAY;

	//	±‚√  √º∑¬ º“∏ÅE
	DECREASE ( m_dwNowHP, DWORD(sSKILL_DATA.wUSE_HP*wStrikeNum) );
	DECREASE ( m_wNowMP, WORD(sSKILL_DATA.wUSE_MP*wStrikeNum) );
}

