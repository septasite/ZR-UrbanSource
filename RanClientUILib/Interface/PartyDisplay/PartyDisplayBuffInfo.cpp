#include "StdAfx.h"
#include "PartyDisplayBuffInfo.h"
#include "GLGaeaClient.h"
#include "PartyDisplayBuffInfoUnit.h"
#include "GLSkill.h"
#include "GLPartyClient.h"
#include "../RanClientUILib/Interface/BasicLineBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPartyDisplayBuffInfo::CPartyDisplayBuffInfo () :
	m_NEWID ( SKILLTIME_UNIT )
{
}

CPartyDisplayBuffInfo::~CPartyDisplayBuffInfo ()
{
}

void CPartyDisplayBuffInfo::CreateSubControl ()
{
	const CString strKeyword = "PARTYDISPLAYBUFF_UNIT";
	CString strCombine;

	for ( int i = 0; i < SKILLFACT_SIZE; i++ )
	{
		strCombine.Format ( "%s%d", strKeyword, i );
		CUIControl* pDummyControl = new CUIControl;
		pDummyControl->CreateSub ( this, strCombine.GetString() );
		RegisterControl ( pDummyControl );

		m_pSkillUnitDummy[i] = pDummyControl;
	}
}

UIGUID CPartyDisplayBuffInfo::GET_EXIST_PLAY_SKILL_CONTROL ( const DWORD& dwSkillID )
{
	SKILLTIME_DISPLAY_LIST_ITER iter = m_SkillPlayList.begin ();
	SKILLTIME_DISPLAY_LIST_ITER iter_end = m_SkillPlayList.end ();
	for ( ; iter != iter_end; ++iter )
	{
		const SKILLTIME_PAIR& pair = (*iter);
		const DWORD& dwID = pair.first;
		const UIGUID& cID = pair.second;
		if ( dwID == dwSkillID ) return cID;
	}

	return NO_ID;
}

void CPartyDisplayBuffInfo::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	if ( !m_SkillPlayList.empty () )
	{
		SKILLTIME_DISPLAY_LIST_ITER iter = m_SkillPlayList.begin ();
		SKILLTIME_DISPLAY_LIST_ITER iter_end = m_SkillPlayList.end ();

		for ( ; iter != iter_end; )
		{
			const SKILLTIME_PAIR& skill_pair = (*iter);
			const DWORD& dwID = skill_pair.first;
			const UIGUID& cID = skill_pair.second;
		
			SSKILLFACT sSKILLFACT;
			if ( !GET_PLAY_SKILLFACT ( dwID, sSKILLFACT ) )
			{				
				DeleteControl ( cID, 0 );
				iter = m_SkillPlayList.erase ( iter );
			}
			else ++iter;
		}
	}

	{
		GLPARTY_CLIENT *pMember = NULL;
		if ( m_nPartyID == 0 )
			pMember = GLPartyClient::GetInstance().GetMaster ();
		else
			pMember = GLPartyClient::GetInstance().GetMember ( m_nPartyID-1 );

		if ( pMember )	
		{
			bool bSELF = false;
			if ( pMember == FindSelfClient () ) bSELF = true;

			PGLCHARCLIENT pCHAR = NULL;
			if ( !bSELF )
			{
				pCHAR = GLGaeaClient::GetInstance().GetChar ( pMember->m_dwGaeaID );
				if ( pCHAR )
				{
					for ( int i = 0; i < SKILLFACT_SIZE; i++ )
					{
						const SSKILLFACT* pSKILLFACT = pCHAR->GET_SKILLFACT ( i );
						if ( !pSKILLFACT ) continue;
						const DWORD& dwID = pSKILLFACT->sNATIVEID.dwID;		

						if ( dwID == NATIVEID_NULL().dwID ) continue;

						UIGUID cID = GET_EXIST_PLAY_SKILL_CONTROL ( dwID );
						if ( cID == NO_ID )	NEW_PLAY_SKILL ( dwID, pSKILLFACT->wLEVEL );
					}
				}
			}
			else
			{
				for ( int i = 0; i < SKILLFACT_SIZE; i++ )
				{
					const SSKILLFACT* pSKILLFACT = &(GLGaeaClient::GetInstance().GetCharacter()->m_sSKILLFACT[i]);
					if ( !pSKILLFACT ) continue;
					const DWORD& dwID = pSKILLFACT->sNATIVEID.dwID;		

					if ( dwID == NATIVEID_NULL().dwID ) continue;

					UIGUID cID = GET_EXIST_PLAY_SKILL_CONTROL ( dwID );
					if ( cID == NO_ID )	NEW_PLAY_SKILL ( dwID, pSKILLFACT->wLEVEL );
				}
			}
		}
	}

	if ( m_SkillPlayList.empty () )
	{
		SetVisibleSingle ( FALSE );
		return ;
	}

	int nPLAY_SKILL = 0;
	if ( !m_SkillPlayList.empty () )
	{		
		SKILLTIME_DISPLAY_LIST_ITER iter = m_SkillPlayList.begin ();
		SKILLTIME_DISPLAY_LIST_ITER iter_end = m_SkillPlayList.end ();

		for ( ; iter != iter_end; ++iter )
		{
			const SKILLTIME_PAIR& skill_pair = (*iter);
			const DWORD& dwID = skill_pair.first;
			const UIGUID& cID = skill_pair.second;			

			CPartyDisplayBuffInfoUnit* pControl = (CPartyDisplayBuffInfoUnit*) FindControl ( cID );
			if ( !pControl )
			{
				GASSERT ( 0 && "ÄÁÆ®·Ñ Ã£±â ½ÇÆÐ" );
				continue;
			}

			SSKILLFACT sSKILLFACT;
			if ( !GET_PLAY_SKILLFACT ( dwID, sSKILLFACT ) )
			{
				GASSERT ( 0 && "½ºÅ³ µ¥ÀÌÅ¸ Ã£±â ½ÇÆÐ" );
				continue;
			}

			const float& fAGE = sSKILLFACT.fAGE;

			pControl->SetGlobalPos ( m_pSkillUnitDummy[nPLAY_SKILL]->GetGlobalPos () );
			pControl->SetLocalPos ( m_pSkillUnitDummy[nPLAY_SKILL]->GetLocalPos () );
			pControl->SetLeftTime ( fAGE );

			nPLAY_SKILL++;
		}
	}

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}

bool CPartyDisplayBuffInfo::GET_PLAY_SKILLFACT ( const DWORD& dwSkillID, SSKILLFACT& sSKILLFACT )
{
	GLPARTY_CLIENT *pMember = NULL;
	if ( m_nPartyID == 0 )
		pMember = GLPartyClient::GetInstance().GetMaster ();
	else
		pMember = GLPartyClient::GetInstance().GetMember ( m_nPartyID-1 );
	if ( !pMember ) return false;

	bool bSELF = false;
	if ( pMember == FindSelfClient () ) bSELF = true;

	PGLCHARCLIENT pCHAR = NULL;
	if ( !bSELF )
	{
		pCHAR = GLGaeaClient::GetInstance().GetChar ( pMember->m_dwGaeaID );
		if ( !pCHAR ) return false;
	}

	for ( int i = 0; i < SKILLFACT_SIZE; i++ )
	{
		SSKILLFACT* pSkillFactIter = NULL;
		if ( bSELF )
			pSkillFactIter = &(GLGaeaClient::GetInstance().GetCharacter()->m_sSKILLFACT[i]);
		else
			pSkillFactIter = pCHAR->GET_SKILLFACT ( i );

		if ( !pSkillFactIter ) continue;

		if ( pSkillFactIter->sNATIVEID == dwSkillID )
		{
			sSKILLFACT = *pSkillFactIter;
			return true;
		}
	}

	return false;
}

void CPartyDisplayBuffInfo::TranslateUIMessage ( UIGUID cID, DWORD dwMsg )
{
	CUIGroup::TranslateUIMessage ( cID, dwMsg );
}

HRESULT CPartyDisplayBuffInfo::InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	m_pd3dDevice = pd3dDevice;
	return CUIGroup::InitDeviceObjects ( pd3dDevice );
}

bool CPartyDisplayBuffInfo::NEW_PLAY_SKILL ( const DWORD& dwSkillID, const WORD wLEVEL )
{
	m_NEWID++;
	if ( SKILLTIME_UNIT_END <= m_NEWID ) m_NEWID = SKILLTIME_UNIT;

	float fLifeTime = 0.0f;
	if ( !GET_SKILL_LIFE_TIME ( dwSkillID, wLEVEL, fLifeTime ) ) return false;

	SNATIVEID sNativeID ( dwSkillID );
	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( sNativeID );
	if ( !pSkill ) return false;

	CPartyDisplayBuffInfoUnit* pSkillTimeUnit = new CPartyDisplayBuffInfoUnit;
	pSkillTimeUnit->CreateSub ( this, "PARTYBUFF_UNIT", UI_FLAG_DEFAULT, m_NEWID );
	pSkillTimeUnit->CreateSubControl ();
	pSkillTimeUnit->InitDeviceObjects ( m_pd3dDevice );
	pSkillTimeUnit->RestoreDeviceObjects ( m_pd3dDevice );	
	pSkillTimeUnit->SetSkill ( dwSkillID, fLifeTime, pSkill->GetName() );
	RegisterControl ( pSkillTimeUnit );	

	SKILLTIME_PAIR pair (dwSkillID,m_NEWID);
	m_SkillPlayList.push_back ( pair );

	return true;
}

bool CPartyDisplayBuffInfo::GET_SKILL_LIFE_TIME ( const DWORD& dwSkillID, const WORD wLEVEL, float& fLifeTime )
{
	SNATIVEID sNativeID ( dwSkillID );

	PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( sNativeID );
	if ( !pSkill ) return false;

	fLifeTime = pSkill->m_sAPPLY.sDATA_LVL[wLEVEL].fLIFE;
	fLifeTime = (fLifeTime)?fLifeTime:1.0f;

	return true;
}

void CPartyDisplayBuffInfo::SetPartyID ( const int nPartyID )
{
	m_nPartyID = nPartyID;
}


GLPARTY_CLIENT*	CPartyDisplayBuffInfo::FindSelfClient ()
{
	GLPARTY_CLIENT *pMaster = GLPartyClient::GetInstance().GetMaster();
	if ( pMaster && pMaster->ISONESELF() )
	{
		return pMaster;
	}
	else
	{
		for ( int i = 0; i < 7; i++ )
		{
			GLPARTY_CLIENT *pMember = GLPartyClient::GetInstance().GetMember( i );
			if ( pMember && pMember->ISONESELF () )
			{
				return pMember;				
			}
		}
	}
	return NULL;
}
