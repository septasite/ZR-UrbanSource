#include "stdafx.h"
#include "GLCrowClient.h"
#include "GLSkill.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL GLCrowClient::DoTransform(PGLSKILL pSkill)
{
	if ( GetHp().dwNow == 0 ) return TRUE;

	if( GLCONST_CHAR::strTRANSFORM_SKIN[pSkill->m_sBASIC.sNATIVEID.wMainID][pSkill->m_sBASIC.sNATIVEID.wSubID] != "" )
	{
		m_bSkinUpdate = true;
		SAFE_DELETE(m_pSkinChar);
		DxSkinCharData* pSkinChar = DxSkinCharDataContainer::GetInstance().LoadData( GLCONST_CHAR::strTRANSFORM_SKIN[pSkill->m_sBASIC.sNATIVEID.wMainID][pSkill->m_sBASIC.sNATIVEID.wSubID].c_str(), m_pd3dDevice, TRUE );
		m_pSkinChar = new DxSkinChar;
		m_pSkinChar->SetCharData ( pSkinChar, m_pd3dDevice, TRUE);
		m_pSkinChar->GetAABBBox( m_vMaxOrg, m_vMinOrg );
		m_fHeight = m_vMaxOrg.y - m_vMinOrg.y;
		
		if ( GLCONST_CHAR::bDANCE[pSkill->m_sBASIC.sNATIVEID.wMainID][pSkill->m_sBASIC.sNATIVEID.wSubID] ) TurnAction(GLAT_IDLE);
	}

	return TRUE;
}

void GLCrowClient::ResetTransform()
{
	if ( m_bSkinUpdate )
	{
		DxSkinCharData* pCharData = DxSkinCharDataContainer::GetInstance().LoadData( m_pCrowData->GetSkinObjFile(), m_pd3dDevice, TRUE );
		SAFE_DELETE(m_pSkinChar);
		m_pSkinChar = new DxSkinChar;
		m_pSkinChar->SetCharData ( pCharData, m_pd3dDevice, TRUE);
		m_pSkinChar->GetAABBBox( m_vMaxOrg, m_vMinOrg );
		m_fHeight = m_vMaxOrg.y - m_vMinOrg.y;
		m_bSkinUpdate = false;
	}
}

BOOL GLCrowClient::IsHit()
{
	for ( int _k = 0; _k < SKILLFACT_SIZE; _k++ )
	{
		SNATIVEID sSkillID = m_sSKILLFACT[_k].sNATIVEID;
		if ( sSkillID != NATIVEID_NULL())
		{
			if ( GLCONST_CHAR::bHIT[sSkillID.wMainID][sSkillID.wSubID] ) 
			{
				if ( GLCONST_CHAR::strTRANSFORM_SKIN[sSkillID.wMainID][sSkillID.wSubID] != "" )
				{
					DISABLESKEFF(_k); 
					return TRUE;
				}
				return GLCONST_CHAR::bHIT[sSkillID.wMainID][sSkillID.wSubID];
				break;
			}
		}
	}

	return FALSE;
}