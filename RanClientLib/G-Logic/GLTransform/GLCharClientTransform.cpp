#include "stdafx.h"
#include "GLCharClient.h"
#include "GLSkill.h"
#include "GLFactEffect.h"
#ifdef _DEBUG
#define new DEBUG_NEW
#endif

BOOL GLCharClient::DoTransform(PGLSKILL pSkill)
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

void GLCharClient::ResetTransform()
{
	if ( m_bSkinUpdate )
	{
		m_bSkinUpdate = false;
		EMCHARINDEX emIndex = CharClassToIndex(m_CharData.emClass);
		DxSkinCharData* pSkinChar = DxSkinCharDataContainer::GetInstance().LoadData( GLCONST_CHAR::szCharSkin[emIndex], m_pd3dDevice, TRUE );
		SAFE_DELETE(m_pSkinChar);
		m_pSkinChar = new DxSkinChar;
		m_pSkinChar->SetCharData ( pSkinChar, m_pd3dDevice, TRUE);
		UpdateSuit();
		m_pSkinChar->GetAABBBox( m_vMaxOrg, m_vMinOrg );
		m_fHeight = m_vMaxOrg.y - m_vMinOrg.y;
	}
}

BOOL GLCharClient::IsHit()
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
					FACTEFF::DeleteSkillFactEffect ( STARGETID(CROW_PC,m_dwGaeaID,m_vPos), m_pSkinChar, m_sSKILLFACT[_k].sNATIVEID );
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