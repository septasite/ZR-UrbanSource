#include "StdAfx.h"
#include "UIInfoLoader.h"
#include "InnerInterface.h"
#include "GLGaeaClient.h"
#include "UITextControl.h"
#include "GameTextControl.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace NS_SKILLINFO
{
	SNATIVEID	m_sNativeIDBack;
	BOOL		m_bNextLevel_BEFORE_FRAME = FALSE;

	//Item Name Render by NjD
	void SetNameItem ( CString strText, D3DCOLOR dwColor )
	{
		CInnerInterface::GetInstance().ADDNAME_RENDER ( strText, dwColor );
	}

	void AddItemRender ( SNATIVEID sICONINDEX, const char* szTexture )
	{
		CInnerInterface::GetInstance().ADDITEM_RENDER ( sICONINDEX, szTexture, SITEMCUSTOM() );
	}

	void ResetItemRender ()
	{
		CInnerInterface::GetInstance().RESETITEM_RENDER (SITEMCUSTOM());	
	}

	void RESET ()
	{
		m_sNativeIDBack = NATIVEID_NULL();
		m_bNextLevel_BEFORE_FRAME = FALSE;
	}

	void AddTextNoSplit ( CString strText, D3DCOLOR dwColor )
	{
		CInnerInterface::GetInstance().ADDTEXT_NOSPLIT ( strText, dwColor );
	}
	     
	void AddTextLongestLineSplit ( CString strText, D3DCOLOR dwColor )
	{
		CInnerInterface::GetInstance().ADDTEXT_LONGESTLINE_SPLIT ( strText, dwColor );
	}

	void RemoveAllInfo ()
	{
		CInnerInterface::GetInstance().CLEAR_TEXT ();
	}

	void LOAD ( GLSKILL* const pSkill, SCHARSKILL* const pCharSkill, BOOL bNextLevel, bool bLink )
	{
		CString	strText;

		//	?? ?? ??

		WORD wDispLevel = 0;			
		if ( pCharSkill && !bLink )	//	?? ??
		{
			wDispLevel = pCharSkill->wLevel + 1;				
		}
		if ( !pSkill )
		{	
			return ;
			ResetItemRender ();
		}

		AddItemRender ( pSkill->m_sEXT_DATA.sICONINDEX, pSkill->m_sEXT_DATA.strICONFILE.c_str() );
		{
			strText.Format("         %s", pSkill->GetName());
			if ( pSkill->m_sBASIC.emROLE == SKILL::EMROLE_PASSIVE )
			{
				CString strDescText;
				strDescText.Format( " [%s]",COMMENT::SKILL_ROLE[SKILL::EMROLE_PASSIVE].c_str() );
				strText += strDescText;
			}
			SetNameItem(strText,NS_UITEXTCOLOR::LIGHTCYAN);
			if( !bLink )
			{
				//Allow Spaces
				AddTextNoSplit ( " ", NS_UITEXTCOLOR::BLACK );
				
				strText.Format ("           %s" );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_FIGHTER_M )		strText.AppendFormat ( "%s", COMMENT::CHARCLASS[0].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_FIGHTER_W )		strText.AppendFormat ( "%s", COMMENT::CHARCLASS[6].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_ARMS_M )			strText.AppendFormat ( "%s", COMMENT::CHARCLASS[1].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_ARMS_W )			strText.AppendFormat ( "%s", COMMENT::CHARCLASS[7].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_ARCHER_M )		strText.AppendFormat ( "%s", COMMENT::CHARCLASS[8].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_ARCHER_W )		strText.AppendFormat ( "%s", COMMENT::CHARCLASS[2].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_SPIRIT_M )		strText.AppendFormat ( "%s", COMMENT::CHARCLASS[9].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_SPIRIT_W )		strText.AppendFormat ( "%s", COMMENT::CHARCLASS[3].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_EXTREME_M )	strText.AppendFormat ( "%s", COMMENT::CHARCLASS[4].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_EXTREME_W )	strText.AppendFormat ( "%s", COMMENT::CHARCLASS[5].c_str() );
				//add class
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_SCIENCE_M )	strText.AppendFormat ( "%s", COMMENT::CHARCLASS[10].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_SCIENCE_W )	strText.AppendFormat ( "%s", COMMENT::CHARCLASS[11].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_ASSASSIN_M )	strText.AppendFormat ( "%s", COMMENT::CHARCLASS[12].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_ASSASSIN_W )	strText.AppendFormat ( "%s", COMMENT::CHARCLASS[13].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_TESTING_M )	strText.AppendFormat ( "%s", COMMENT::CHARCLASS[14].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_TESTING_W )	strText.AppendFormat ( "%s", COMMENT::CHARCLASS[15].c_str() );
				AddTextNoSplit(strText,NS_UITEXTCOLOR::WHITE);
	
				{
					CString strRank;
					AddTextNoSplit( "\n", NS_UITEXTCOLOR::BLACK );
					strRank.Format ("Rank:%d", pSkill->m_sBASIC.dwGRADE );
	
	
					//add skill info for melee,messile,magic
					CString szSKillFlag;
					CString	strText1;
	
					if ( pSkill->m_sBASIC.emAPPLY == SKILL::EMAPPLY_PHY_SHORT )
					{
						szSKillFlag+=( ID2GAMEWORD( "SKILL_FLAG_INFO", 0 ));
					}
					if ( pSkill->m_sBASIC.emAPPLY == SKILL::EMAPPLY_PHY_LONG )
					{
						szSKillFlag+=( ID2GAMEWORD( "SKILL_FLAG_INFO", 1 ));
					}
					if ( pSkill->m_sBASIC.emAPPLY == SKILL::EMAPPLY_MAGIC )
					{
						szSKillFlag+=( ID2GAMEWORD( "SKILL_FLAG_INFO", 2 ));
					}
	
					strText1.Format( "%s", szSKillFlag.GetString() );
	
					strText.Format("%s / %s / %s", strRank, COMMENT::BRIGHT[pSkill->m_sLEARN.emBRIGHT].c_str(),strText1 );
					AddTextNoSplit(strText,NS_UITEXTCOLOR::WHITE);
				}
				if ( pCharSkill )
				{
					const SKILL::SAPPLY& sAPPLY = pSkill->m_sAPPLY;
					WORD wLevel = pCharSkill->wLevel;
					const SKILL::CDATA_LVL& sDATA_LVL = sAPPLY.sDATA_LVL[wLevel];
					if ( pSkill->m_sBASIC.emROLE != SKILL::EMROLE_PASSIVE )
					{
						//	?? ??
						if ( 0 < sDATA_LVL.wUSE_ARROWNUM )
						{
							
							strText.Format("%s:%d",ID2GAMEWORD( "SKILL_CDATA_CVL_BASIC_USE_VALUE", 0), sDATA_LVL.wUSE_ARROWNUM);
							
							AddTextNoSplit(strText, NS_UITEXTCOLOR::WHITE );
						}
	
						//	?? ??
						/*if ( 0 < sDATA_LVL.wUSE_CHARMNUM )
						{
							strText.Format("%s:%d",ID2GAMEWORD( "SKILL_CDATA_CVL_BASIC_USE_VALUE", 1), sDATA_LVL.wUSE_CHARMNUM);
							AddTextNoSplit(strText, NS_UITEXTCOLOR::WHITE );
						}*/
	
						//	EXP ???
						//if ( 0 < sDATA_LVL.wUSE_EXP )
						//{
						//	strText.Format("%s:%d",ID2GAMEWORD( "SKILL_CDATA_CVL_BASIC_USE_VALUE", 2), sDATA_LVL.wUSE_EXP);
						//	AddTextNoSplit(strText, NS_UITEXTCOLOR::DEFAULT );
						//}
	
						//	HP ???
						if ( 0 < sDATA_LVL.wUSE_HP )
						{
							strText.Format("%s:%d",ID2GAMEWORD( "SKILL_CDATA_CVL_BASIC_USE_VALUE", 3), sDATA_LVL.wUSE_HP);
							AddTextNoSplit(strText, NS_UITEXTCOLOR::WHITE );
						}
	
						//	MP ???
						if ( 0 < sDATA_LVL.wUSE_MP )
						{
							strText.Format("%s:%d",ID2GAMEWORD( "SKILL_CDATA_CVL_BASIC_USE_VALUE", 4), sDATA_LVL.wUSE_MP);
							AddTextNoSplit(strText, NS_UITEXTCOLOR::WHITE );
						}
	
						//	SP ???
						if ( 0 < sDATA_LVL.wUSE_SP )
						{
							strText.Format("%s:%d",ID2GAMEWORD( "SKILL_CDATA_CVL_BASIC_USE_VALUE", 5), sDATA_LVL.wUSE_SP);
							AddTextNoSplit(strText, NS_UITEXTCOLOR::WHITE );
						}
	
						if ( 0 < sDATA_LVL.wUSE_CP )
						{
							strText.Format("%s:%d",ID2GAMEWORD( "SKILL_CDATA_CVL_BASIC_USE_VALUE", 6), sDATA_LVL.wUSE_CP);
							AddTextNoSplit(strText, NS_UITEXTCOLOR::WHITE );
						}
	
	/*					if ( 0 < sDATA_LVL.wUSE_BULLET )
						{
							strText.Format("%s:%d",ID2GAMEWORD( "SKILL_CDATA_CVL_BASIC_USE_VALUE", 10), sDATA_LVL.wUSE_BULLET);
							AddTextNoSplit(strText, NS_UITEXTCOLOR::WHITE );
						}
	
						if ( 0 < sDATA_LVL.wUSE_EXTRA )
						{
							strText.Format("%s:%d",ID2GAMEWORD( "SKILL_CDATA_CVL_BASIC_USE_VALUE", 11), sDATA_LVL.wUSE_EXTRA);
							AddTextNoSplit(strText, NS_UITEXTCOLOR::WHITE );
						} */
					}
				}
			}
		}
		
		BOOL bMaster = FALSE;
		if( !bLink )
		{
			BOOL bMASTER = GLGaeaClient::GetInstance().GetCharacter()->ISMASTER_SKILL ( pSkill->m_sBASIC.sNATIVEID );
			WORD wLevel = pCharSkill->wLevel;
			if ( bNextLevel ) wLevel = pCharSkill->wLevel + 1;
			if ( bMASTER )
			{
				AddTextNoSplit(ID2GAMEWORD("SKILL_ETC_MASTER"), NS_UITEXTCOLOR::ENABLE);
				bMaster = TRUE;
			}
			else
			{
				if ( wDispLevel )
				{			
					if( !bNextLevel ) 
						strText.Format ("%s:%d", ID2GAMEWORD("SKILL_BASIC_INFO", 4), wDispLevel );
	
					AddTextNoSplit(strText, NS_UITEXTCOLOR::ENABLE);
				}
			}
			{
				if ( pCharSkill )
				{
					const SKILL::SAPPLY& sAPPLY = pSkill->m_sAPPLY;
					WORD wLevel = pCharSkill->wLevel;
					const SKILL::CDATA_LVL& sDATA_LVL = sAPPLY.sDATA_LVL[wLevel];
					const SKILL::SBASIC& sBASIC = pSkill->m_sBASIC;	
	
					if ( sBASIC.emUSE_LITEM )
					{
						if ( sBASIC.emUSE_LITEM != ITEMATT_NOCARE )
						{
							strText.Format ( "%s:%s",	ID2GAMEWORD( "SKILL_ADVANCED_USE_ITEM_LR_HAND", 0), 
														ID2GAMEWORD( "SKILL_ADVANCED_USE_ITEM", sBASIC.emUSE_LITEM - 1 ) );
	
							AddTextNoSplit(strText, NS_UITEXTCOLOR::WHITE );
						}
					}	
	
					if ( sBASIC.emUSE_RITEM )
					{
						if ( sBASIC.emUSE_RITEM != ITEMATT_NOCARE )
						{
							strText.Format ( "%s:%s",	ID2GAMEWORD( "SKILL_ADVANCED_USE_ITEM_LR_HAND", 1), 
														ID2GAMEWORD( "SKILL_ADVANCED_USE_ITEM", sBASIC.emUSE_RITEM - 1 ) );
	
							AddTextNoSplit(strText, NS_UITEXTCOLOR::WHITE );
						}
					}
					
					if ( 0 < sDATA_LVL.fDELAYTIME )
					{
						strText.Format("%s:%2.1f Seconds(s)",ID2GAMEWORD( "SKILL_CDATA_CVL_BASIC", 0), sDATA_LVL.fDELAYTIME);
						AddTextNoSplit(strText, NS_UITEXTCOLOR::WHITE );
					}
					
					if ( 0 < sDATA_LVL.fLIFE )
					{
						strText.Format("%s:%2.1f",ID2GAMEWORD( "SKILL_CDATA_CVL_BASIC", 1), sDATA_LVL.fLIFE);
						AddTextNoSplit(strText, NS_UITEXTCOLOR::DEFAULT );
					}
				}
			}
		}
		else
		{
		CString szSKillFlag;
		CString strBright;
		CString	strText1;

		if ( pSkill->m_sBASIC.emROLE == SKILL::EMROLE_NORMAL ) szSKillFlag+= "Physical Attack skills";
		else szSKillFlag+= COMMENT::SKILL_ROLE[SKILL::EMROLE_PASSIVE].c_str();
		
		AddTextNoSplit ( "", NS_UITEXTCOLOR::PALEGREEN );
		strText1.Format( "            %s/ %s", szSKillFlag.GetString(), COMMENT::ELEMENT[pSkill->m_sAPPLY.emELEMENT].c_str());
		AddTextNoSplit ( strText1, NS_UITEXTCOLOR::WHITE );
		AddTextNoSplit ( "", NS_UITEXTCOLOR::PALEGREEN );
		}

		//	?? ??
		if ( pCharSkill || !pCharSkill || bLink )	//	?? ??? ???...
		{		
			const SKILL::SAPPLY& sAPPLY = pSkill->m_sAPPLY;
			WORD wLevel = 0;
			if( !bLink && pCharSkill )	wLevel = pCharSkill->wLevel;
			const SKILL::CDATA_LVL& sDATA_LVL = sAPPLY.sDATA_LVL[wLevel];
			const SKILL::SSTATE_BLOW& sSTATE_BLOW = sAPPLY.sSTATE_BLOW[wLevel];
			//ID2GAMEWORD("SKILL_CATEGORY", 2),NS_UITEXTCOLOR::LIGHTSKYBLUE);

			//	?? ??

		//Skill Range
		{
			AddTextNoSplit("", NS_UITEXTCOLOR::ADMIN_COLOR); //spacer para gwapo si Art hahaha.
			WORD wLevel = 0;
			if ( pCharSkill ) 
				wLevel = !bNextLevel ? pCharSkill->wLevel : pCharSkill->wLevel + 1;

			AddTextNoSplit("[The Range Of Skill]", NS_UITEXTCOLOR::WHITE );
			
			const SKILL::CDATA_LVL& sDATA_LVL = sAPPLY.sDATA_LVL[wLevel];
			const SKILL::SBASIC& sBASIC = pSkill->m_sBASIC;	

				
			if ((pSkill->m_sBASIC.emIMPACT_TAR == TAR_SPEC || pSkill->m_sBASIC.emIMPACT_TAR == TAR_SELF_TOSPEC) || 
				(pSkill->m_sBASIC.emIMPACT_TAR == TAR_SELF || pSkill->m_sBASIC.emIMPACT_TAR == REALM_ZONE))
			{
					CString strText1;
					strText.Format("Within %dm range from target and %dm radius in target-centered, ",sDATA_LVL.wAPPLYRANGE, sBASIC.wTARRANGE );
					AddTextNoSplit(strText, NS_UITEXTCOLOR::AQUABLUE );
					strText1.Format("%d enemies/friend..",sDATA_LVL.wAPPLYRANGE, sBASIC.wTARRANGE );
					AddTextNoSplit(strText1, NS_UITEXTCOLOR::AQUABLUE );
			}
			else if (pSkill->m_sBASIC.emIMPACT_TAR == TAR_ZONE_SPEC || pSkill->m_sBASIC.emIMPACT_TAR == TAR_ZONE)
			{
					strText.Format("The %dm within %dm and %d of attack range.",
					sDATA_LVL.wTARNUM, sDATA_LVL.wAPPLYRANGE, sBASIC.wTARRANGE );
					AddTextNoSplit(strText, NS_UITEXTCOLOR::AQUABLUE );
			}
			else
				strText.Format("Self / Friend");
		}

			/*{
				const SKILL::SBASIC& sBASIC = pSkill->m_sBASIC;	
				if ( sBASIC.wTARRANGE && 0 < sDATA_LVL.wAPPLYANGLE && 0 < sDATA_LVL.wTARNUM )
				{
					AddTextNoSplit( " ", NS_UITEXTCOLOR::BLACK );
					CString strText;
					AddTextNoSplit("[Skill Range]", NS_UITEXTCOLOR::WHITE );
					strText.Format("%d Target/s within %dm and %d angle of",sDATA_LVL.wTARNUM, sBASIC.wTARRANGE, sDATA_LVL.wAPPLYANGLE );
					AddTextNoSplit(strText, NS_UITEXTCOLOR::WHITE );
					AddTextNoSplit(" attack range.", NS_UITEXTCOLOR::WHITE );
				}

			}*/

			AddTextNoSplit(" ", NS_UITEXTCOLOR::WHITE );
			if ( 0 != sDATA_LVL.fBASIC_VAR )
			{
				float fBASIC_VAR_SCALE = sDATA_LVL.fBASIC_VAR * COMMENT::SKILL_TYPES_SCALE[sAPPLY.emBASIC_TYPE];
				CString strCombine;
				strCombine.Format ( "Let target's HP decrease %2.1f",  fBASIC_VAR_SCALE);
				AddTextNoSplit( strCombine, NS_UITEXTCOLOR::LIME );
			}

			{
				for( unsigned s=0;s<SKILL::SAPPLY::MAX_DESCRIPTOR;++s)
				{
					const SKILL::SSPEC_DESCRIPTOR &desc = sAPPLY.spec[s];
					if( pSkill->m_sAPPLY.GetSpec( desc.emSPEC ) != &desc ) continue;
					const SKILL::SSPEC& sSPEC = desc.sSPEC[wLevel];
					if ( desc.emSPEC != EMSPECA_NULL && desc.emSPEC != EMSPECA_LINKSKILL )
					{
						AddTextNoSplit("[Skill Effect]", NS_UITEXTCOLOR::GOLD);
						strText.Format ( "%s:%s", ID2GAMEWORD("SKILL_SPEC_TYPE", 0), COMMENT::SPEC_ADDON[desc.emSPEC].c_str() );
						AddTextNoSplit(strText, NS_UITEXTCOLOR::LIME );
						
						strText.Empty();
						CString strTemp;


						if ( desc.emSPEC == EMSPECA_NONBLOW || desc.emSPEC == EMSPECA_RECBLOW )
						{

							if ( sSPEC.dwFLAG & DIS_NUMB )
							{
								strTemp.Format ( "%s ", COMMENT::BLOW[EMBLOW_NUMB].c_str() );
								strText += strTemp;
							}
							if ( sSPEC.dwFLAG & DIS_STUN )
							{
								strTemp.Format ( "%s ", COMMENT::BLOW[EMBLOW_STUN].c_str() );
								strText += strTemp;
							}
							if ( sSPEC.dwFLAG & DIS_STONE )
							{
								strTemp.Format ( "%s ", COMMENT::BLOW[EMBLOW_STONE].c_str() );
								strText += strTemp;
							}
							if ( sSPEC.dwFLAG & DIS_BURN )
							{
								strTemp.Format ( "%s ", COMMENT::BLOW[EMBLOW_BURN].c_str() );
								strText += strTemp;
							}
							if ( sSPEC.dwFLAG & DIS_FROZEN )
							{
								strTemp.Format ( "%s ", COMMENT::BLOW[EMBLOW_FROZEN].c_str() );
								strText += strTemp;
							}
							if ( sSPEC.dwFLAG & DIS_MAD )
							{
								strTemp.Format ( "%s ", COMMENT::BLOW[EMBLOW_MAD].c_str() );
								strText += strTemp;
							}
							if ( sSPEC.dwFLAG & DIS_POISON )
							{
								strTemp.Format ( "%s ", COMMENT::BLOW[EMBLOW_POISON].c_str() );
								strText += strTemp;
							}
							if ( sSPEC.dwFLAG & DIS_CURSE )
							{
								strTemp.Format ( "%s ", COMMENT::BLOW[EMBLOW_CURSE].c_str() );
								strText += strTemp;
							}
						}
						// ?? ??
						else if ( desc.emSPEC == EMSPECA_DEFENSE_SKILL_ACTIVE )
						{
							GLSKILL* pSkillTemp = GLSkillMan::GetInstance().GetData( sSPEC.dwNativeID );
							if ( pSkillTemp )
							{
								strTemp.Format ( "%s Lv%d", pSkillTemp->GetName(),sSPEC.dwFLAG );
								strText += strTemp;
							}
						}

						if ( strText.GetLength () )
						{
							AddTextNoSplit(strText, NS_UITEXTCOLOR::LIME );
						}

						// ????? ?? ??? ??? ???? ??? ?? ??~
						// ????? ?? ??? ??? ?? ?? 0? ??? ???? ?? ( ?? )
						if ( 0 != sSPEC.fVAR1 )
						{
							if( COMMENT::SPEC_ADDON_VAR1[EMSPECA_NULL] != COMMENT::SPEC_ADDON_VAR1[desc.emSPEC] )
							{
								float fVAR1_SCALE = sSPEC.fVAR1 * COMMENT::SPEC_ADDON_VAR1_SCALE[desc.emSPEC];

								if ( COMMENT::IsSPEC_ADDON1_PER(desc.emSPEC) )
									strText.Format ( "%s:%2.2f%%", COMMENT::SPEC_ADDON_VAR1[desc.emSPEC].c_str(), fVAR1_SCALE );
								else
									strText.Format ( "%s:%2.2f", COMMENT::SPEC_ADDON_VAR1[desc.emSPEC].c_str(), fVAR1_SCALE );
									
								AddTextNoSplit(strText, NS_UITEXTCOLOR::LIME );
							}
						}
						if ( 0 != sSPEC.fVAR2 )
						{
							if( COMMENT::SPEC_ADDON_VAR2[EMSPECA_NULL] != COMMENT::SPEC_ADDON_VAR2[desc.emSPEC] )
							{
								float fVAR2_SCALE = sSPEC.fVAR2 * COMMENT::SPEC_ADDON_VAR2_SCALE[desc.emSPEC];

								if ( COMMENT::IsSPEC_ADDON2_PER(desc.emSPEC) )
									strText.Format ( "%s:%2.1f%%", COMMENT::SPEC_ADDON_VAR2[desc.emSPEC].c_str(), fVAR2_SCALE );
								else
									strText.Format ( "%s:%2.1f", COMMENT::SPEC_ADDON_VAR2[desc.emSPEC].c_str(), fVAR2_SCALE );

								AddTextNoSplit(strText, NS_UITEXTCOLOR::LIME );
							}
						}
					}		
				}
			}


			///////////////////////////////////////////////////////////////////////
			//	??? ???
			
		}

		//	????
		if ( pCharSkill || bLink )	//	?? ??? ???...
		{	
			const SKILL::SAPPLY& sAPPLY = pSkill->m_sAPPLY;
			WORD wLevel = 0;
			if( !bLink )	wLevel = pCharSkill->wLevel;
			const SKILL::CDATA_LVL& sDATA_LVL = sAPPLY.sDATA_LVL[wLevel];
			if ( sAPPLY.emSTATE_BLOW != EMBLOW_NONE )
			{
				//AddTextNoSplit( " ", NS_UITEXTCOLOR::BLACK );//ID2GAMEWORD("SKILL_CATEGORY", 4),NS_UITEXTCOLOR::LIGHTSKYBLUE);
				//AddTextNoSplit( "[Side Effect]", NS_UITEXTCOLOR::GOLD );//ID2GAMEWORD("SKILL_CATEGORY", 4),NS_UITEXTCOLOR::LIGHTSKYBLUE);
				AddTextNoSplit(COMMENT::BLOW [ sAPPLY.emSTATE_BLOW ].c_str(), NS_UITEXTCOLOR::PRIVATE );

				WORD wLevel = 0;
				if( !bLink )	wLevel = pCharSkill->wLevel;
				if ( bNextLevel && !bLink ) wLevel = pCharSkill->wLevel + 1;
				const SKILL::SSTATE_BLOW& sSTATE_BLOW = sAPPLY.sSTATE_BLOW[wLevel];

				if ( 0 < sSTATE_BLOW.fVAR1 )
				{
					strText.Format ( "%s:%2.1f", COMMENT::BLOW_VAR1[sAPPLY.emSTATE_BLOW].c_str(), sSTATE_BLOW.fVAR1 );
					AddTextNoSplit(strText, NS_UITEXTCOLOR::PRIVATE );
				}

				if ( 0 < sSTATE_BLOW.fVAR2 )
				{
					strText.Format ( "%s:%2.1f", COMMENT::BLOW_VAR2[sAPPLY.emSTATE_BLOW].c_str(), sSTATE_BLOW.fVAR2 );
					AddTextNoSplit(strText, NS_UITEXTCOLOR::PRIVATE );
				}
			}
		}

		//	????
		if ( pCharSkill || bLink )	//	?? ??? ???...
		{
			const SKILL::SAPPLY& sAPPLY = pSkill->m_sAPPLY;
			WORD wLevel = 0;
			if( !bLink )	wLevel = pCharSkill->wLevel;
			for( unsigned s=0;s<SKILL::SAPPLY::MAX_DESCRIPTOR;++s)
			{
				const SKILL::SIMPACT_DESCRIPTOR &desc = sAPPLY.sadon[s];
				if( pSkill->m_sAPPLY.GetImpact( desc.emADDON ) != &desc )	continue; 
				const SKILL::CDATA_LVL& sDATA_LVL = sAPPLY.sDATA_LVL[wLevel];
				if ( desc.emADDON != EMIMPACTA_NONE )
				{
					WORD wLevel = 0;
					if( !bLink )	wLevel = pCharSkill->wLevel;
					if ( bNextLevel && !bLink ) wLevel = pCharSkill->wLevel + 1;

					const float fADDON_VAR = desc.fADDON_VAR[wLevel];
					if ( 0 < fADDON_VAR )
					{
						AddTextNoSplit( " ", NS_UITEXTCOLOR::BLACK );//ID2GAMEWORD("SKILL_CATEGORY", 4),NS_UITEXTCOLOR::LIGHTSKYBLUE);
						AddTextNoSplit( "[Side Effect]", NS_UITEXTCOLOR::GOLD );//ID2GAMEWORD("SKILL_CATEGORY", 4),NS_UITEXTCOLOR::LIGHTSKYBLUE);

						float fADDON_VAR_SCALE = fADDON_VAR * COMMENT::IMPACT_ADDON_SCALE[desc.emADDON];
						
						if ( COMMENT::IsIMPACT_ADDON_PER(desc.emADDON) )
						{
							strText.Format ( "%s:%2.2f%%", COMMENT::IMPACT_ADDON[desc.emADDON].c_str(), fADDON_VAR_SCALE );
						}
						else
						{
							strText.Format ( "%s:%2.2f", COMMENT::IMPACT_ADDON[desc.emADDON].c_str(), fADDON_VAR_SCALE );
						}

						AddTextNoSplit(strText, NS_UITEXTCOLOR::PRIVATE );
					}
				}
			}
		}

		if( !bLink )
		{
			BOOL bNOT_LEARN = wDispLevel==0;

			//	??? ??
			if ( (!bMaster && bNextLevel) || bNOT_LEARN )
			{
				AddTextNoSplit( " ", NS_UITEXTCOLOR::BLACK );//ID2GAMEWORD("SKILL_CATEGORY", 7),NS_UITEXTCOLOR::LIGHTSKYBLUE);
				AddTextNoSplit( "Skill Prerequisites", NS_UITEXTCOLOR::WHITE );
	
				WORD wNextLevel = wDispLevel;
				GLCharacter* const pCharacter = GLGaeaClient::GetInstance().GetCharacter();
				SKILL::SLEARN& sLEARN = pSkill->m_sLEARN;
				SKILL::SLEARN_LVL& sLVL = sLEARN.sLVL_STEP[wNextLevel];			
	
			
				//	1. ??????
				SNATIVEID NeedSkillID = pSkill->m_sLEARN.sSKILL;			
				if ( NeedSkillID != NATIVEID_NULL() )
				{
					BOOL bVALID = FALSE;
					BOOL bNeedSkillLevel = FALSE;
	
					CString strNeedSkillName;
					CString strNeedSkillLevel;
	
					PGLSKILL pNeedSkill = GLSkillMan::GetInstance().GetData ( NeedSkillID.wMainID, NeedSkillID.wSubID );
					if( pNeedSkill ) strNeedSkillName.Format("%s:%s", ID2GAMEWORD( "SKILL_ADVANCED_INFO", 0), pNeedSkill->GetName() );
					bVALID = pCharacter->ISLEARNED_SKILL ( NeedSkillID );			
	
					//	2. ????????
					if ( 0 < sLVL.dwSKILL_LVL )
					{
						strNeedSkillLevel.Format("%s:%d",ID2GAMEWORD( "SKILL_ADVANCED_INFO", 1), (sLVL.dwSKILL_LVL + 1) );
						bNeedSkillLevel = TRUE;
	
						SCHARDATA2::SKILL_MAP& map = pCharacter->m_ExpSkills;				
						SCHARDATA2::SKILL_MAP_ITER iter = map.find ( NeedSkillID.dwID );
						if ( iter != map.end() )
						{
							SCHARSKILL& rCharSkill = (*iter).second;
	
							//	? ??
							bVALID = rCharSkill.wLevel >= sLVL.dwSKILL_LVL;						
						}
					}
	
					AddTextNoSplit(strNeedSkillName,NS_UITEXTCONTROL::GetEvaluateColor ( bVALID ));
	
					if ( bNeedSkillLevel )
						AddTextNoSplit(strNeedSkillLevel, NS_UITEXTCONTROL::GetEvaluateColor ( bVALID ) );
				}
	
				//	3. ?????
				if ( 0 < sLVL.dwSKP )
				{
					strText.Format("%s:%d",ID2GAMEWORD( "SKILL_ADVANCED_INFO", 2), sLVL.dwSKP);				
					AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( pCharacter->m_dwSkillPoint >= sLVL.dwSKP ) );
				}
	
				//	4. ????
				if ( 0 < sLVL.dwLEVEL )
				{
					strText.Format("%s:%d",ID2GAMEWORD( "SKILL_ADVANCED_INFO", 3), sLVL.dwLEVEL);
					AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( pCharacter->GETLEVEL () >= int(sLVL.dwLEVEL) ) );
				}
	
	/*			if ( 0 < sLVL.dwREBORN )
				{
					strText.Format("%s:%d",ID2GAMEWORD( "SKILL_ADVANCED_INFO", 4), sLVL.dwREBORN);
					AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( pCharacter->GETREBORN () >= int(sLVL.dwREBORN) ) );
				}
	
				if ( 0 < sLVL.dwMoneyReq )
				{
					strText.Format("%s:%d",ID2GAMEWORD( "SKILL_ADVANCED_INFO", 5), sLVL.dwMoneyReq );
					AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( pCharacter->m_lnMoney >= int(sLVL.dwMoneyReq ) ) );
				}
	
				if ( 0 < sLVL.dwPremPoint )
				{
					strText.Format("%s:%d",ID2GAMEWORD( "SKILL_ADVANCED_INFO", 6), sLVL.dwPremPoint );
					AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( pCharacter->m_lnPremP >= int(sLVL.dwPremPoint ) ) );
				}
	
				if ( 0 < sLVL.dwVotePoint )
				{
					strText.Format("%s:%d",ID2GAMEWORD( "SKILL_ADVANCED_INFO", 7), sLVL.dwVotePoint );
					AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( pCharacter->m_lnVoteP >= int(sLVL.dwVotePoint ) ) );
				}
	*/
				//	?? - ??
				//BOOL bValue = TRUE;
				//strText.Format ( "%s", COMMENT::BRIGHT[sLEARN.emBRIGHT].c_str() );
				//if ( sLEARN.emBRIGHT != BRIGHT_BOTH )
				//{
				//	if ( pCharacter->GETBRIGHT() != sLEARN.emBRIGHT )
				//	{
				//		bValue = FALSE;
				//	}
				//}
				//AddTextNoSplit ( strText, NS_UITEXTCONTROL::GetEvaluateColor ( bValue ) );
	
	
				//	Stats
				//	1. ???
				if ( 0 < sLVL.sSTATS.dwPow )
				{
					strText.Format("%s:%d",ID2GAMEWORD( "SKILL_ADVANCED_INFO_STATS", 0), sLVL.sSTATS.dwPow);
					AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( pCharacter->m_sSUMSTATS.dwPow >= sLVL.sSTATS.dwPow ) );
				}
	
				//	2. ????
				if ( 0 < sLVL.sSTATS.dwStr )
				{
					strText.Format("%s:%d",ID2GAMEWORD( "SKILL_ADVANCED_INFO_STATS", 1), sLVL.sSTATS.dwStr);
					AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( pCharacter->m_sSUMSTATS.dwStr >= sLVL.sSTATS.dwStr ) );
				}
	
				//	3. ????
				if ( 0 < sLVL.sSTATS.dwSpi )
				{
					strText.Format("%s:%d",ID2GAMEWORD( "SKILL_ADVANCED_INFO_STATS", 2), sLVL.sSTATS.dwSpi);
					AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( pCharacter->m_sSUMSTATS.dwSpi >= sLVL.sSTATS.dwSpi ));
				}
	
				//	4. ????
				if ( 0 < sLVL.sSTATS.dwDex )
				{
					strText.Format("%s:%d",ID2GAMEWORD( "SKILL_ADVANCED_INFO_STATS", 3), sLVL.sSTATS.dwDex);
					AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( pCharacter->m_sSUMSTATS.dwDex >= sLVL.sSTATS.dwDex ) );
				}
	
				//	5. ????
				if ( 0 < sLVL.sSTATS.dwInt )
				{
					strText.Format("%s:%d",ID2GAMEWORD( "SKILL_ADVANCED_INFO_STATS", 4), sLVL.sSTATS.dwInt);
					AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( pCharacter->m_sSUMSTATS.dwInt >= sLVL.sSTATS.dwInt ) );
				}
	
				//	6. ????
				if ( 0 < sLVL.sSTATS.dwSta )
				{
					strText.Format("%s:%d",ID2GAMEWORD( "SKILL_ADVANCED_INFO_STATS", 5), sLVL.sSTATS.dwSta);
					AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( pCharacter->m_sSUMSTATS.dwSta >= sLVL.sSTATS.dwSta ) );
				}
			}
	
			if ( bNextLevel ) return ;
	
			//	??? ??
			if( !pSkill->GetDesc() )	return;
	
			int StrLength = static_cast<int>( strlen( pSkill->GetDesc() ) );
			if ( StrLength )
			{
				AddTextNoSplit ( " ",NS_UITEXTCOLOR::BLACK );//ID2GAMEWORD ( "SKILL_CATEGORY", 8 ), NS_UITEXTCOLOR::LIGHTSKYBLUE );
				
				AddTextLongestLineSplit ( pSkill->GetDesc(), NS_UITEXTCOLOR::DEFAULT );
			}
			BOOL bMASTER2 = GLGaeaClient::GetInstance().GetCharacter()->ISMASTER_SKILL ( pSkill->m_sBASIC.sNATIVEID );
			if ( bNextLevel )
			{
				if ( bMASTER2 )
				{
					//	NOTE
					//		??, ?????
					//		?? ??? ????? ???,
					//		?? ??? ??? ???? ??.
					bNextLevel = FALSE;
				}
				else
				{
					if ( wDispLevel )
					{				
						strText.Format ("%s:%d", ID2GAMEWORD("SKILL_NEXTLEVEL"), wDispLevel + 1 );
						AddTextNoSplit(strText, NS_UITEXTCOLOR::RED);
					}
				}
			}
		}
	}

	void LOAD ( const SNATIVEID& sNativeID, const BOOL bNextLevel, bool bLink )
	{
		if ( sNativeID != NATIVEID_NULL() )
		{
			BOOL bUPDATE = FALSE;
			if (( bNextLevel != m_bNextLevel_BEFORE_FRAME ) ||
				( sNativeID != m_sNativeIDBack) )
			{			
				bUPDATE = TRUE;
			}

			if ( bUPDATE )
			{
				PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( sNativeID.wMainID, sNativeID.wSubID );
				if ( pSkill )	//	??? ??? ??
				{
					RemoveAllInfo ();

					SCHARSKILL* pCharSkill = GLGaeaClient::GetInstance().GetCharacter()->GETLEARNED_SKILL ( sNativeID );					
					LOAD ( pSkill, pCharSkill, bNextLevel, bLink );
				}

				m_sNativeIDBack = sNativeID;
				m_bNextLevel_BEFORE_FRAME = bNextLevel;
			}		
		}
	}
};