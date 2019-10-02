#include "StdAfx.h"
#include "UIInfoLoader.h"
#include "GLGaeaClient.h"
#include "GLItemMan.h"
#include "GLItemDef.h"
#include "GLItem.h"
#include "GameTextControl.h"
#include "UITextControl.h"
#include "InnerInterface.h"
#include "ItemImage.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

namespace NS_ITEMINFO
{
    SITEMCUSTOM	m_sItemCustomBACK;
	BOOL		m_bShopOpenBACK;
    BOOL		m_bInMarketBACK;
	BOOL		m_bInPrivateMarketBACK;
	BOOL		m_bIsWEAR_ITEMBACK;
	WORD		m_wPosXBACK;
	WORD		m_wPosYBACK;
	BOOL		m_bITEMLINK;

	//Item Name Render by NjD
	void AddTextNoSplitBig ( CString strText, D3DCOLOR dwColor )
	{
		CInnerInterface::GetInstance().ADDTEXT_NOSPLIT_BIG ( strText, dwColor );
	}

	//Item Render by NjD
	void AddItemRender ( SNATIVEID sICONINDEX, const char* szTexture, SITEMCUSTOM sCustom )
	{
		CInnerInterface::GetInstance().ADDITEM_RENDER ( sICONINDEX, szTexture, sCustom );
	}

	void ResetItemRender (SITEMCUSTOM sCustom )
	{
		CInnerInterface::GetInstance().RESETITEM_RENDER ( sCustom );	
	}
	//Item Images in Box by NjD
	void AddItemBoxRender ( SNATIVEID sICONINDEX, const char* szTexture, int nIndex )
	{
		CInnerInterface::GetInstance().ADDITEMBOX_RENDER ( sICONINDEX, szTexture, nIndex );
	}

	//Item Images in Random Box by NjD
	void AddItemBoxRandomRender ( SNATIVEID sICONINDEX, const char* szTexture, int nIndex )
	{
		CInnerInterface::GetInstance().ADDITEMBOXRANDOM_RENDER_BOXINFO ( sICONINDEX, szTexture, nIndex );
	}

	void ResetItemBoxRandomRender ()
	{
		CInnerInterface::GetInstance().RESETITEMBOXRANDOM_RENDER_BOXINFO ();	
	}

	void ResetItemBoxRender ()
	{
		CInnerInterface::GetInstance().RESETITEMBOX_RENDER ();	
	}
	//Resi Icons by NjD
	void SetResiIcons ()
	{
		CInnerInterface::GetInstance().SETRESIICON ();	
	}

	void AddTextNoSplit ( CString strText, D3DCOLOR dwColor )
	{
		CInnerInterface::GetInstance().ADDTEXT_NOSPLIT ( strText, dwColor );
	}

	void AddTextLongestLineSplit ( CString strText, D3DCOLOR dwColor )
	{
		CInnerInterface::GetInstance().ADDTEXT_LONGESTLINE_SPLIT ( strText, dwColor );
	}

	void AddTextMultiColorSplit ( CString strText , D3DCOLOR dwColor, CString strText2 , D3DCOLOR dwColor2 )
	{
		CInnerInterface::GetInstance().ADDTEXT_MULTICOLORSPLIT ( strText, dwColor ,  strText2 , dwColor2 );
	}
	void AddTextMultiColorSplit4 ( CString strText , D3DCOLOR dwColor , CString strText2 , D3DCOLOR dwColor2 ,CString strText3 , D3DCOLOR dwColor3 ,CString strText4 , D3DCOLOR dwColor4 )
	{
		CInnerInterface::GetInstance().ADDTEXT_MULTICOLORSPLIT4 ( strText, dwColor , strText2 , dwColor2 , strText3, dwColor3 ,strText4 , dwColor4 );
	}
	void AddTextMultiColorSplit2 ( CString strText , D3DCOLOR dwColor , CString strText2 , D3DCOLOR dwColor2 ,CString strText3 , D3DCOLOR dwColor3 ,CString strText4 , D3DCOLOR dwColor4 )
	{
		CInnerInterface::GetInstance().ADDTEXT_MULTICOLORSPLIT2 ( strText, dwColor , strText2 , dwColor2 , strText3, dwColor3 ,strText4 , dwColor4 );
	}
	void AddTextMultiColorSplit3 ( CString strText , D3DCOLOR dwColor , CString strText2 , D3DCOLOR dwColor2 ,CString strText3 , D3DCOLOR dwColor3 )
	{
		CInnerInterface::GetInstance().ADDTEXT_MULTICOLORSPLIT3 ( strText, dwColor , strText2 , dwColor2 , strText3, dwColor3 );
	}
	void AddTextMultiColorSplit6 ( CString strText , D3DCOLOR dwColor , CString strText2 , D3DCOLOR dwColor2 ,CString strText3, D3DCOLOR dwColor3,CString strText4, D3DCOLOR dwColor4,CString strText5, D3DCOLOR dwColor5,CString strText6, D3DCOLOR dwColor6)
	{
		CInnerInterface::GetInstance().ADDTEXT_MULTICOLORSPLIT6 ( strText, dwColor , strText2 , dwColor2 , strText3, dwColor3 , strText4, dwColor4 , strText5, dwColor5 , strText6, dwColor6 );
	}
	void AddTextMultiColorSplit5 ( CString strText , D3DCOLOR dwColor , CString strText2 , D3DCOLOR dwColor2 ,CString strText3 , D3DCOLOR dwColor3 ,CString strText4 , D3DCOLOR dwColor4 , CString strText5 , D3DCOLOR dwColor5 )
	{
		CInnerInterface::GetInstance().ADDTEXT_MULTICOLORSPLIT5 ( strText, dwColor , strText2 , dwColor2 , strText3, dwColor3 ,strText4 , dwColor4 , strText5 , dwColor5 );
	}
	int AddTextMultiColorSplit11 ( CString strText , D3DCOLOR dwColor , CString strText2 , D3DCOLOR dwColor2 ,CString strText3 , D3DCOLOR dwColor3 ,CString strText4 , D3DCOLOR dwColor4 , CString strText5 , D3DCOLOR dwColor5 , CString strText6 , D3DCOLOR dwColor6 , CString strText7 , D3DCOLOR dwColor7 , CString strText8 , D3DCOLOR dwColor8 , CString strText9 , D3DCOLOR dwColor9 , CString strText10 , D3DCOLOR dwColor10 , CString strText11 , D3DCOLOR dwColor11 )
	{
		CInnerInterface::GetInstance().ADDTEXT_MULTICOLORSPLIT11 ( strText, dwColor , strText2 , dwColor2 , strText3, dwColor3 ,strText4 , dwColor4 , strText5 , dwColor5 , strText6 , dwColor6, strText7 , dwColor7, strText8 , dwColor8, strText9 , dwColor9, strText10 , dwColor10, strText11 , dwColor11 );
		return -1;
	}
	
	void ResetResiIcons ()
	{
		CInnerInterface::GetInstance().RESETRESIICON ();	
	}

	void	RESET ()
	{
		m_sItemCustomBACK.sNativeID = NATIVEID_NULL ();
		m_bShopOpenBACK = FALSE;
		m_bInMarketBACK = FALSE;
		m_bInPrivateMarketBACK = FALSE;
		m_bIsWEAR_ITEMBACK = FALSE;
		m_bITEMLINK = FALSE;
		SITEMCUSTOM sCUSTOM;
		ResetItemRender (sCUSTOM);
		ResetItemBoxRender();
		//ResetNameRender ();
		ResetResiIcons ();
	}

	void RemoveAllInfo ()
	{
		CInnerInterface::GetInstance().CLEAR_TEXT ();
	}

	char*	GetNumberWithSign ( int nValue )
	{
		static	char szNumber[128];

		if ( 0 < nValue )
		{
			StringCchPrintf ( szNumber, 128, "(+%d)", nValue );
		}
		else if ( nValue < 0 )
		{
			StringCchPrintf ( szNumber, 128, "(%d)", nValue );
		}

		return szNumber;
	}

	char*	GetNumberWithSign2 ( int nValue )
	{
		static	char szNumber[128];

		if ( 0 < nValue )
		{
			StringCchPrintf ( szNumber, 128, " +%d", nValue );
		}
		else if ( nValue < 0 )
		{
			StringCchPrintf ( szNumber, 128, " %d", nValue );
		}

		return szNumber;
	}
	void AddInfoItemAddon ( int nBasic, int nAddon, CString strFormat )
	{
		CString Text;
		CString sText;
		if ( nAddon )
		{
			//Text.Format ( "%s: %d%s", strFormat, nBasic, GetNumberWithSign ( nAddon ) );
			//AddTextNoSplit ( Text, NS_UITEXTCOLOR::WHITE );
			Text.Format ( "%s:%d", strFormat, nBasic );
			sText.Format ( "%s",GetNumberWithSign ( nAddon ) );
			AddTextMultiColorSplit( Text ,NS_UITEXTCOLOR::WHITE, sText , NS_UITEXTCOLOR::GOLD );
			//AddTextNoSplit ( Text, NS_UITEXTCOLOR::WHITE );
			//AddTextMultiColorSplit( Text , sText );
		}
		else if ( nBasic )
		{
			Text.Format ( "%s:%d", strFormat, nBasic );
			AddTextNoSplit ( Text, NS_UITEXTCOLOR::WHITE );
		}
	}

	void AddInfoItemAddon ( int nBasic, float nRandomValue, CString strFormat )
	{
		CString Text;
		CString sText;
		if ( nRandomValue )
		{
			//Text.Format ( "%s: %d%s", strFormat, nBasic, GetNumberWithSign ( nAddon ) );
			//AddTextNoSplit ( Text, NS_UITEXTCOLOR::WHITE );
			Text.Format ( "%s:%d", strFormat, nBasic );
			sText.Format ( "%s",GetNumberWithSign ( nRandomValue ) );
			AddTextMultiColorSplit( Text ,NS_UITEXTCOLOR::WHITE, sText , NS_UITEXTCOLOR::AQUA );
			//AddTextNoSplit ( Text, NS_UITEXTCOLOR::WHITE );
			//AddTextMultiColorSplit( Text , sText );
		}
		else if ( nBasic )
		{
			Text.Format ( "%s:%d", strFormat, nBasic );
			AddTextNoSplit ( Text, NS_UITEXTCOLOR::WHITE );
		}
	}

	void AddInfoItemAddon ( int nBasic, int nAddon, float nRandomValue, CString strFormat )
	{
		CString Text;
		CString sRandomValue;
		CString sText;

		if ( nRandomValue )
		{
			//Text.Format ( "%s: %d%s", strFormat, nBasic, GetNumberWithSign ( nAddon ) );
			//AddTextNoSplit ( Text, NS_UITEXTCOLOR::WHITE );
			Text.Format ( "%s:%d", strFormat, nBasic );
			sRandomValue.Format ( "%s",GetNumberWithSign ( nRandomValue ) );
			sText.Format ( "%s",GetNumberWithSign ( nAddon ) );
			AddTextMultiColorSplit3( Text ,NS_UITEXTCOLOR::WHITE, sRandomValue , NS_UITEXTCOLOR::AQUA, sText , NS_UITEXTCOLOR::GOLD );
			//AddTextNoSplit ( Text, NS_UITEXTCOLOR::WHITE );
			//AddTextMultiColorSplit( Text , sText );
		}
		else if ( nBasic )
		{
			Text.Format ( "%s:%d", strFormat, nBasic );
			AddTextNoSplit ( Text, NS_UITEXTCOLOR::WHITE );
		}
	}

	void APPEND_ITEM_GRADE ( CString& strOrigin, BYTE uGRADE )
	{
		if ( !uGRADE ) return ;

		CString strGRADE;
		strGRADE.Format ( "+%d ", uGRADE );
		strOrigin += strGRADE;
	}

	void APPEND_ITEM_GRADE2 ( CString& strOrigin, BYTE uGRADE )
	{
		if ( !uGRADE ) return ;

		CString strGRADE;
		strGRADE.Format ( "(+%d) ", uGRADE );
		strOrigin += strGRADE;
	}

	void AddInfoItemAddon ( int nBasic, int nAddon, BYTE uGRADE, CString strFormat )
	{
		CString Text;
		CString sText;
		if ( nAddon )
		{
			//Text.Format ( "%s: %d%s", strFormat, nBasic, GetNumberWithSign( nAddon ) );
			//APPEND_ITEM_GRADE ( Text, uGRADE );
			//AddTextNoSplit ( Text, NS_UITEXTCOLOR::WHITE );

			Text.Format ( "%s:%d", strFormat, nBasic );
			sText.Format ( "%s",GetNumberWithSign ( nAddon ) );
			APPEND_ITEM_GRADE ( sText, uGRADE );
			AddTextMultiColorSplit( Text , NS_UITEXTCOLOR::WHITE , sText , NS_UITEXTCOLOR::GOLD );
			//AddTextNoSplit ( Text, NS_UITEXTCOLOR::WHITE );
		}
		else if ( nBasic )
		{
			Text.Format ( "%s: %d", strFormat, nBasic );
			APPEND_ITEM_GRADE ( Text, uGRADE );
			AddTextNoSplit ( Text, NS_UITEXTCOLOR::WHITE );
		}
	}

	void AddInfoItemAddonRange ( int nBasicMin, int nBasicMax, int nAddon, BYTE uGRADE, CString strFormat )
	{
		CString Text;
		CString sText;
		CString ssText;
		CString sssText;
		if ( nAddon )
		{
			//Text.Format ( "%s: %d%s~%d%s", strFormat, nBasicMin, GetNumberWithSign( nAddon ) );
			Text.Format ( "%s: %d", strFormat, nBasicMin );
			sText.Format ( "%s", GetNumberWithSign( nAddon ) );

			ssText.Format ( "~%d",  nBasicMax );
			sssText.Format ( "%s", GetNumberWithSign( nAddon ) );
			
			AddTextMultiColorSplit2( Text , NS_UITEXTCOLOR::WHITE , sText , NS_UITEXTCOLOR::GOLD , ssText , NS_UITEXTCOLOR::WHITE , sssText , NS_UITEXTCOLOR::GOLD );
			//AddTextMultiColorSplit( ssText , sssText );
            //APPEND_ITEM_GRADE ( Text, uGRADE );
			//AddTextNoSplit ( Text, NS_UITEXTCOLOR::WHITE );
		}
		else if ( nBasicMin || nBasicMax )
		{
			Text.Format ( "%s: %d~%d",strFormat, nBasicMin, nBasicMax );
			AddTextNoSplit ( Text, NS_UITEXTCOLOR::WHITE );
		}
	}
	
	void AddInfoItemAddonRange ( int nBasicMin, int nBasicMax, float nRandomValue, CString strFormat )
	{
		CString Text;
		CString ssText;
		CString sRandomVal1;
		CString sRandomVal2;

		if ( nRandomValue )
		{
			//Text.Format ( "%s: %d%s~%d%s", strFormat, nBasicMin, GetNumberWithSign( nAddon ) );
			Text.Format ( "%s: %d", strFormat, nBasicMin );
			sRandomVal1.Format ("%s", GetNumberWithSign ( nRandomValue ));

			ssText.Format ( "~%d",  nBasicMax );
			sRandomVal2.Format ("%s", GetNumberWithSign ( nRandomValue ));
			
			AddTextMultiColorSplit4( Text , NS_UITEXTCOLOR::WHITE , sRandomVal1, NS_UITEXTCOLOR::AQUA , ssText , NS_UITEXTCOLOR::WHITE, sRandomVal2, NS_UITEXTCOLOR::AQUA );
			//AddTextMultiColorSplit( ssText , sssText );
            //APPEND_ITEM_GRADE ( Text, uGRADE );
			//AddTextNoSplit ( Text, NS_UITEXTCOLOR::WHITE );
		}
		else if ( nBasicMin || nBasicMax )
		{
			Text.Format ( "%s: %d~%d",strFormat, nBasicMin, nBasicMax );
			AddTextNoSplit ( Text, NS_UITEXTCOLOR::WHITE );
		}
	}

	void AddInfoItemAddonRange ( int nBasicMin, int nBasicMax, int nAddon, float nRandomValue, CString strFormat )
	{
		CString Text;
		CString sText;
		CString ssText;
		CString sssText;
		CString sRandomVal1;
		CString sRandomVal2;

		if ( nRandomValue )
		{
			//Text.Format ( "%s: %d%s~%d%s", strFormat, nBasicMin, GetNumberWithSign( nAddon ) );
			Text.Format ( "%s: %d", strFormat, nBasicMin );
			sRandomVal1.Format ("%s", GetNumberWithSign ( nRandomValue ));
			sText.Format ( "%s", GetNumberWithSign( nAddon ) );

			ssText.Format ( "~%d",  nBasicMax );
			sRandomVal2.Format ("%s", GetNumberWithSign ( nRandomValue ));
			sssText.Format ( "%s", GetNumberWithSign( nAddon ) );
			
			AddTextMultiColorSplit6( Text , NS_UITEXTCOLOR::WHITE , sRandomVal1, NS_UITEXTCOLOR::AQUA, sText , NS_UITEXTCOLOR::GOLD , ssText , NS_UITEXTCOLOR::WHITE, sRandomVal2, NS_UITEXTCOLOR::AQUA, sssText , NS_UITEXTCOLOR::GOLD );
			//AddTextMultiColorSplit( ssText , sssText );
            //APPEND_ITEM_GRADE ( Text, uGRADE );
			//AddTextNoSplit ( Text, NS_UITEXTCOLOR::WHITE );
		}
		else if ( nBasicMin || nBasicMax )
		{
			Text.Format ( "%s: %d~%d",strFormat, nBasicMin, nBasicMax );
			AddTextNoSplit ( Text, NS_UITEXTCOLOR::WHITE );
		}
	}

	void AddItemTurnInfo ( const SITEMCUSTOM &sItemCustom, const BOOL bInMarket, const BOOL bInPrivateMarket )
	{
		SITEM* pItemData = GLItemMan::GetInstance().GetItem ( sItemCustom.sNativeID );

		CString strText;

		//switch ( pItemData->sBasicOp.emItemType )
		//{
		//case ITEM_CHARM:
		//case ITEM_ARROW:
		//case ITEM_CURE:
		//case ITEM_GRINDING:
			if ( pItemData->sDrugOp.wPileNum > 1 )
			{
				WORD wPileNum = pItemData->sDrugOp.wPileNum;
				WORD wTurnNum = sItemCustom.wTurnNum;				
				if ( bInPrivateMarket )	//	개인 상점
				{
					strText.Format("%s:%d", ID2GAMEWORD("ITEM_TURN_INFO", 0 ), wTurnNum);
					AddTextNoSplit(strText,NS_UITEXTCOLOR::CHARTREUSE);

					return ;
				}

				if ( bInMarket )	wTurnNum = pItemData->GETAPPLYNUM();
				strText.Format("%s:%d/%d", ID2GAMEWORD("ITEM_TURN_INFO", 0 ), wTurnNum, wPileNum);
				AddTextNoSplit(strText,NS_UITEXTCOLOR::WHITE);
			}
			//break;
		//}
	}

	void AddInfoPetSkillItem( const SITEMCUSTOM &sItemCustom )
	{
		CString strText;

		SNATIVEID sNativeID = sItemCustom.sNativeID;
		GLPetClient* pPetClient = GLGaeaClient::GetInstance().GetPetClient();
		SITEM* pItemData = GLItemMan::GetInstance().GetItem ( sNativeID );
		SNATIVEID sSkillID = pItemData->sSkillBookOp.sSkill_ID;

		//	Note : 스킬 정보 가져옴.
		PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( sSkillID.wMainID, sSkillID.wSubID );
		if ( pSkill )
		{
			if ( pPetClient->ISLEARNED_SKILL( sSkillID ) )
			{
				AddTextNoSplit ( ID2GAMEWORD ( "ITEM_SKILL_CONDITION", 0 ), NS_UITEXTCOLOR::RED );	
				return ;
			}
		}
	}

	void AddInfoSkillItem ( const SITEMCUSTOM &sItemCustom )
	{
		CString strText;

		SNATIVEID sNativeID = sItemCustom.sNativeID;
		GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();	
		SITEM* pItemData = GLItemMan::GetInstance().GetItem ( sNativeID );
		SNATIVEID sSkillID = pItemData->sSkillBookOp.sSkill_ID;

		//	Note : 스킬 정보 가져옴.
		PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( sSkillID.wMainID, sSkillID.wSubID );
		if ( pSkill )
		{
			//	기본 정보
			{
				//	2. 등급
				strText.Format("%s:%d",ID2GAMEWORD("SKILL_BASIC_INFO", 1), pSkill->m_sBASIC.dwGRADE);
				AddTextNoSplit(strText,NS_UITEXTCOLOR::WHITE);

				//	3. 속성
				strText.Format("%s:%s",ID2GAMEWORD("SKILL_BASIC_INFO", 2), COMMENT::BRIGHT[pSkill->m_sLEARN.emBRIGHT].c_str());
				AddTextNoSplit(strText,NS_UITEXTCOLOR::WHITE);

				//	4. 직업
				strText.Format ("%s:", ID2GAMEWORD("SKILL_BASIC_INFO", 3) );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_FIGHTER_M )	strText.AppendFormat ( "%s", COMMENT::CHARCLASS[0].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_ARMS_M )		strText.AppendFormat ( "%s", COMMENT::CHARCLASS[1].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_ARCHER_W )		strText.AppendFormat ( "%s", COMMENT::CHARCLASS[2].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_SPIRIT_W )		strText.AppendFormat ( "%s", COMMENT::CHARCLASS[3].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_FIGHTER_W )	strText.AppendFormat ( "%s", COMMENT::CHARCLASS[4].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_EXTREME_M )	strText.AppendFormat ( "%s", COMMENT::CHARCLASS[5].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_EXTREME_W )	strText.AppendFormat ( "%s", COMMENT::CHARCLASS[6].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_ARMS_W )		strText.AppendFormat ( "%s", COMMENT::CHARCLASS[7].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_ARCHER_M )		strText.AppendFormat ( "%s", COMMENT::CHARCLASS[8].c_str() );				
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_SPIRIT_M )		strText.AppendFormat ( "%s", COMMENT::CHARCLASS[9].c_str() );				
				//added by tobets | 14-7-2012 | add new class
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_SCIENCE_M )	strText.AppendFormat ( "%s", COMMENT::CHARCLASS[10].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_SCIENCE_W )	strText.AppendFormat ( "%s", COMMENT::CHARCLASS[11].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_ASSASSIN_M )	strText.AppendFormat ( "%s", COMMENT::CHARCLASS[12].c_str() );
				if ( pSkill->m_sLEARN.dwCLASS & GLCC_ASSASSIN_W )	strText.AppendFormat ( "%s", COMMENT::CHARCLASS[13].c_str() );

				//AddTextNoSplit(strText,NS_UITEXTCONTROL::GetEvaluateColor ( pItemData->sBasicOp.dwReqCharClass & pCharacter->m_emClass ) );
			}

			{
				//	목표 가능거리, 왼손, 오른손 도구
				const SKILL::SBASIC& sBASIC = pSkill->m_sBASIC;		

				if ( sBASIC.wTARRANGE )
				{
					strText.Format("%s:%d",ID2GAMEWORD( "SKILL_ADVANCED_TARGET_RANGE", 0), sBASIC.wTARRANGE);
					AddTextNoSplit(strText, NS_UITEXTCOLOR::WHITE );
				}

				if ( (sBASIC.emUSE_LITEM && (sBASIC.emUSE_LITEM != ITEMATT_NOCARE)) || 
					(sBASIC.emUSE_RITEM && (sBASIC.emUSE_RITEM != ITEMATT_NOCARE)) )
				{
					AddTextNoSplit(ID2GAMEWORD("SKILL_CATEGORY", 1),NS_UITEXTCOLOR::LIGHTSKYBLUE);
				}

				CString strUSEITEM;
				if ( sBASIC.emUSE_LITEM )
				{
					if ( sBASIC.emUSE_LITEM != ITEMATT_NOCARE )
					{
						strText.Format( "%s:%s", 
										ID2GAMEWORD( "SKILL_ADVANCED_USE_ITEM_LR_HAND", 0), 
										ID2GAMEWORD( "SKILL_ADVANCED_USE_ITEM", sBASIC.emUSE_LITEM - 1 ) );
						AddTextNoSplit(strText, NS_UITEXTCOLOR::WHITE );
					}
				}

				if ( sBASIC.emUSE_RITEM )
				{
					if ( sBASIC.emUSE_RITEM != ITEMATT_NOCARE )
					{
						strText.Format ( "%s:%s", 
										ID2GAMEWORD( "SKILL_ADVANCED_USE_ITEM_LR_HAND", 1), 
										ID2GAMEWORD( "SKILL_ADVANCED_USE_ITEM", sBASIC.emUSE_RITEM - 1 ) );
						AddTextNoSplit(strText, NS_UITEXTCOLOR::WHITE );
					}
				}
			}

			//	이미 배운 스킬
			if ( pCharacter->GETLEARNED_SKILL ( sSkillID ) )
			{
				AddTextNoSplit ( ID2GAMEWORD ( "ITEM_SKILL_CONDITION", 0 ), NS_UITEXTCOLOR::RED );	
				return ;
			}

			//	요구치 정보
			{
				//AddTextNoSplit( ID2GAMEWORD("SKILL_CATEGORY", 7), NS_UITEXTCOLOR::LIGHTSKYBLUE);
				AddTextNoSplit ( "\n", NS_UITEXTCOLOR::BLACK);
				const WORD wLevel = 0;
				SKILL::SLEARN& sLEARN = pSkill->m_sLEARN;
				SKILL::SLEARN_LVL& sLVL = sLEARN.sLVL_STEP[wLevel];
			
				//	1. 요구보유스킬
				SNATIVEID NeedSkillID = pSkill->m_sLEARN.sSKILL;			
				if ( NeedSkillID != NATIVEID_NULL() )
				{
					BOOL bVALID = FALSE;
					BOOL bNeedSkillLevel = FALSE;

					CString strNeedSkillName;
					CString strNeedSkillLevel;

					PGLSKILL pNeedSkill = GLSkillMan::GetInstance().GetData ( NeedSkillID.wMainID, NeedSkillID.wSubID );
					strNeedSkillName.Format("%s:%s", ID2GAMEWORD( "SKILL_ADVANCED_INFO", 0), pNeedSkill->GetName() );
					bVALID = pCharacter->ISLEARNED_SKILL ( NeedSkillID );			

					//	2. 요구보유스킬레벨
					if ( 0 < sLVL.dwSKILL_LVL )
					{
						strNeedSkillLevel.Format("%s:%d",ID2GAMEWORD( "SKILL_ADVANCED_INFO", 1), (sLVL.dwSKILL_LVL + 1) );
						bNeedSkillLevel = TRUE;

						SCHARDATA2::SKILL_MAP& map = pCharacter->m_ExpSkills;				
						SCHARDATA2::SKILL_MAP_ITER iter = map.find ( NeedSkillID.dwID );
						if ( iter != map.end() )
						{
							SCHARSKILL& rCharSkill = (*iter).second;

							//	색 조절
							bVALID = rCharSkill.wLevel >= sLVL.dwSKILL_LVL;						
						}
					}

					AddTextNoSplit(strNeedSkillName,NS_UITEXTCONTROL::GetEvaluateColor ( bVALID ));

					if ( bNeedSkillLevel )
						AddTextNoSplit(strNeedSkillLevel, NS_UITEXTCONTROL::GetEvaluateColor ( bVALID ) );
				}

				//	3. 요구경험치
				if ( 0 < sLVL.dwSKP )
				{
					strText.Format("%s:%d",ID2GAMEWORD( "SKILL_ADVANCED_INFO", 2), sLVL.dwSKP);				
					AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( pCharacter->m_dwSkillPoint >= sLVL.dwSKP ) );
				}

				//	4. 요구레벨
				if ( 0 < sLVL.dwLEVEL )
				{
					strText.Format("%s:%d",ID2GAMEWORD( "SKILL_ADVANCED_INFO", 3), sLVL.dwLEVEL);
					AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( pCharacter->GETLEVEL () >= int(sLVL.dwLEVEL) ) );
				}

				if ( 0 < sLVL.nREBORN )
				{
					strText.Format("%s:%d",ID2GAMEWORD( "SKILL_ADVANCED_INFO", 4), sLVL.nREBORN);
					AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( pCharacter->GETREBORN () >= int(sLVL.nREBORN) ) );
				}

				//	5. 조건 - 암광
				BOOL bValue = TRUE;
				strText.Format ( "%s", COMMENT::BRIGHT[pItemData->sBasicOp.emReqBright].c_str() );
				if ( pItemData->sBasicOp.emReqBright != BRIGHT_BOTH )
				{
					if ( pCharacter->GETBRIGHT() != pItemData->sBasicOp.emReqBright )
					{
						bValue = FALSE;
					}
				}
				AddTextNoSplit ( strText, NS_UITEXTCONTROL::GetEvaluateColor ( bValue ) );


				//	Stats
				//	1. 요구힘
				if ( 0 < sLVL.sSTATS.dwPow )
				{
					strText.Format("%s :%d",ID2GAMEWORD( "SKILL_ADVANCED_INFO_STATS", 0), sLVL.sSTATS.dwPow);
					AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( pCharacter->m_sSUMSTATS.dwPow >= sLVL.sSTATS.dwPow ) );
				}

				//	2. 요구체력
				if ( 0 < sLVL.sSTATS.dwStr )
				{
					strText.Format("%s :%d",ID2GAMEWORD( "SKILL_ADVANCED_INFO_STATS", 1), sLVL.sSTATS.dwStr);
					AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( pCharacter->m_sSUMSTATS.dwStr >= sLVL.sSTATS.dwStr ) );
				}

				//	3. 요구정신
				if ( 0 < sLVL.sSTATS.dwSpi )
				{
					strText.Format("%s :%d",ID2GAMEWORD( "SKILL_ADVANCED_INFO_STATS", 2), sLVL.sSTATS.dwSpi);
					AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( pCharacter->m_sSUMSTATS.dwSpi >= sLVL.sSTATS.dwSpi ));
				}

				//	4. 요구민첩
				if ( 0 < sLVL.sSTATS.dwDex )
				{
					strText.Format("%s :%d",ID2GAMEWORD( "SKILL_ADVANCED_INFO_STATS", 3), sLVL.sSTATS.dwDex);
					AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( pCharacter->m_sSUMSTATS.dwDex >= sLVL.sSTATS.dwDex ) );
				}

				//	5. 요구지력
				if ( 0 < sLVL.sSTATS.dwInt )
				{
					strText.Format("%s :%d",ID2GAMEWORD( "SKILL_ADVANCED_INFO_STATS", 4), sLVL.sSTATS.dwInt);
					AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( pCharacter->m_sSUMSTATS.dwInt >= sLVL.sSTATS.dwInt ) );
				}

				//	6. 요구근력
				if ( 0 < sLVL.sSTATS.dwSta )
				{
					strText.Format("%s :%d",ID2GAMEWORD( "SKILL_ADVANCED_INFO_STATS", 5), sLVL.sSTATS.dwSta);
					AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( pCharacter->m_sSUMSTATS.dwPow >= sLVL.sSTATS.dwSta ) );
				}
			}
		}
	}

	void AddTextAddValue( const SITEMCUSTOM & sItemCustom, const ITEM::SSUIT & sSUIT )
	{
		CString strText;
		BOOL bLEAST_HAVE_ONE(TRUE);
		BOOL bADD_HP(FALSE), bADD_MP(FALSE), bADD_SP(FALSE), bADD_MA(FALSE);
		INT arrVALUE[EMADD_SIZE];
		SecureZeroMemory( arrVALUE, sizeof(arrVALUE) );

		for ( int i = 0; i < ITEM::SSUIT::ADDON_SIZE; ++i )
		{
			EMITEM_ADDON emTYPE = sSUIT.sADDON[i].emTYPE;

			if ( emTYPE != EMADD_NONE )
			{
				//	NOTE
				//		가산효과가 존재할경우에만 타이틀을
				//		출력하기 위해, 적어도 하나가 존재할때
				//		뿌린다는 것을 체크한다.
				if ( bLEAST_HAVE_ONE )
				{
					//AddTextNoSplit( ID2GAMEWORD ( "ITEM_CATEGORY", 10 ),NS_UITEXTCOLOR::LIGHTSKYBLUE);
					AddTextNoSplit( " ",NS_UITEXTCOLOR::PRIVATE);
					bLEAST_HAVE_ONE = FALSE;
				}

				int nVALUE = sSUIT.sADDON[i].nVALUE;

				switch ( emTYPE )
				{
				case EMADD_HP:
					if( !bADD_HP )
					{
						arrVALUE[EMADD_HP] = sItemCustom.GETADDHP();
						bADD_HP = TRUE;
					}
					break;
				case EMADD_MP:
					if( !bADD_MP )
					{
						arrVALUE[EMADD_MP] = sItemCustom.GETADDMP();
						bADD_MP = TRUE;
					}
					break;
				case EMADD_SP:
					if( !bADD_SP )
					{
						arrVALUE[EMADD_SP] = sItemCustom.GETADDSP();
						bADD_SP = TRUE;
					}
					break;
				case EMADD_MA:
					if( !bADD_MA )
					{
						arrVALUE[EMADD_MA] = sItemCustom.GETADDMA();
						bADD_MA = TRUE;
					}
					break;
				case EMADD_HITRATE:		arrVALUE[EMADD_HITRATE] += nVALUE;		break;
				case EMADD_AVOIDRATE:	arrVALUE[EMADD_AVOIDRATE] += nVALUE;	break;
				case EMADD_DAMAGE:		arrVALUE[EMADD_DAMAGE] += nVALUE;		break;
				case EMADD_DEFENSE:		arrVALUE[EMADD_DEFENSE] += nVALUE;		break;
				case EMADD_STATS_POW:	arrVALUE[EMADD_STATS_POW] += nVALUE;	break;
				case EMADD_STATS_STR:	arrVALUE[EMADD_STATS_STR] += nVALUE;	break;
				case EMADD_STATS_SPI:	arrVALUE[EMADD_STATS_SPI] += nVALUE;	break;
				case EMADD_STATS_DEX:	arrVALUE[EMADD_STATS_DEX] += nVALUE;	break;
				case EMADD_STATS_INT:	arrVALUE[EMADD_STATS_INT] += nVALUE;	break;
				case EMADD_STATS_STA:	arrVALUE[EMADD_STATS_STA] += nVALUE;	break;
				case EMADD_PA:			arrVALUE[EMADD_PA] += nVALUE;			break;
				case EMADD_SA:			arrVALUE[EMADD_SA] += nVALUE;			break;
				case EMADD_CP:			arrVALUE[EMADD_CP] += nVALUE;			break; //add cp
				};
			}
		}

		for( int i=1; i<EMADD_SIZE; ++i)
		{
			if( arrVALUE[i] != 0 )
			{
				strText.Format( "%s :%s", ID2GAMEWORD( "ITEM_ADDON_INFO", i ), GetNumberWithSign( arrVALUE[i] ) );
				AddTextNoSplit( strText, NS_UITEXTCOLOR::LIME );
			}
		}

		if ( sItemCustom.nidDISGUISE!=SNATIVEID(false) )
		{
			SITEM* pJDisguiseData = GLItemMan::GetInstance().GetItem ( sItemCustom.nidDISGUISE );
			if ( pJDisguiseData )
			{
				if ( pJDisguiseData->sBasicOp.IsCostumeCombine() )
				{
					//add jitem
					BOOL bLEAST_HAVE_ONE(TRUE);
					INT arrVALUECOS[EMADD_SIZE];
					SecureZeroMemory( arrVALUECOS, sizeof(arrVALUECOS) );
	
					for ( int j = 0; j < ITEM::SSUIT::ADDON_SIZE; ++j )
					{
						EMITEM_ADDON emTYPEJ = pJDisguiseData->sSuitOp.sADDON[j].emTYPE;

						if ( emTYPEJ != EMADD_NONE )
						{
							if ( bLEAST_HAVE_ONE )
							{
								AddTextNoSplit ( "Costume Value" , NS_UITEXTCOLOR::AQUAMARINE );
								bLEAST_HAVE_ONE = FALSE;
							}

							int nVALUECOS = pJDisguiseData->sSuitOp.sADDON[j].nVALUE;
							switch ( emTYPEJ )
							{
								case EMADD_HP:			arrVALUECOS[EMADD_HP] += nVALUECOS;			break;
								case EMADD_MP:			arrVALUECOS[EMADD_MP] += nVALUECOS;			break;
								case EMADD_SP:			arrVALUECOS[EMADD_SP] += nVALUECOS;			break;
								case EMADD_MA:			arrVALUECOS[EMADD_MA] += nVALUECOS;			break;
								case EMADD_HITRATE:		arrVALUECOS[EMADD_HITRATE] += nVALUECOS;		break;
								case EMADD_AVOIDRATE:	arrVALUECOS[EMADD_AVOIDRATE] += nVALUECOS;		break;
								case EMADD_DAMAGE:		arrVALUECOS[EMADD_DAMAGE] += nVALUECOS;		break;
								case EMADD_DEFENSE:		arrVALUECOS[EMADD_DEFENSE] += nVALUECOS;		break;
								case EMADD_STATS_POW:	arrVALUECOS[EMADD_STATS_POW] += nVALUECOS;		break;
								case EMADD_STATS_STR:	arrVALUECOS[EMADD_STATS_STR] += nVALUECOS;		break;
								case EMADD_STATS_SPI:	arrVALUECOS[EMADD_STATS_SPI] += nVALUECOS;		break;
								case EMADD_STATS_DEX:	arrVALUECOS[EMADD_STATS_DEX] += nVALUECOS;		break;
								case EMADD_STATS_INT:	arrVALUECOS[EMADD_STATS_INT] += nVALUECOS;		break;
								case EMADD_STATS_STA:	arrVALUECOS[EMADD_STATS_STA] += nVALUECOS;		break;
								case EMADD_PA:			arrVALUECOS[EMADD_PA] += nVALUECOS;			break;
								case EMADD_SA:			arrVALUECOS[EMADD_SA] += nVALUECOS;			break;
								case EMADD_CP:			arrVALUECOS[EMADD_CP] += nVALUECOS;			break; //add cp
							};
						}
					}

					CString strTextCos;
					for( int i=1; i<EMADD_SIZE; ++i)
					{
						if( arrVALUECOS[i] != 0 )
						{
							strTextCos.Format( "%s :%s", ID2GAMEWORD( "ITEM_ADDON_INFO", i ), GetNumberWithSign( arrVALUECOS[i] ) );
							//AddTextNoSplit( strTextCos, NS_UITEXTCOLOR::DARKTURQUOISE );
							AddTextNoSplit( strTextCos, NS_UITEXTCOLOR::LIME );
						}		
					}
				}
			}	
		}
	}

	void LOAD_SIMPLE ( const SITEMCUSTOM &sItemCustom )
	{
		if ( m_sItemCustomBACK == sItemCustom ) return ;

		m_sItemCustomBACK = sItemCustom;

		RemoveAllInfo();

		SITEM* pItemData = GLItemMan::GetInstance().GetItem ( sItemCustom.sNativeID );
		if ( !pItemData ) return ;
		
		DWORD dwLevel = pItemData->sBasicOp.emLevel;
		//	이름
		AddTextNoSplit ( pItemData->GetName(), COMMENT::ITEMCOLOR[dwLevel] );
	}

	void LOAD ( const SITEMCUSTOM &sItemCustom, const BOOL bShopOpen, const BOOL bInMarket, const BOOL bInPrivateMarket, const BOOL bIsWEAR_ITEM, WORD wPosX, WORD wPosY, SNATIVEID sNpcNativeID, BOOL bITEMLINK )
	{	
		if ( m_sItemCustomBACK == sItemCustom && m_bShopOpenBACK == bShopOpen
			&& m_bInMarketBACK == bInMarket && m_bInPrivateMarketBACK == bInPrivateMarket
			&& m_bIsWEAR_ITEMBACK == bIsWEAR_ITEM && m_wPosXBACK == wPosX && m_wPosYBACK == wPosY && m_bITEMLINK == bITEMLINK )	return ;

		m_sItemCustomBACK = sItemCustom;
		m_bShopOpenBACK = bShopOpen;
		m_bInMarketBACK = bInMarket;
		m_bInPrivateMarketBACK = bInPrivateMarket;
		m_bIsWEAR_ITEMBACK = bIsWEAR_ITEM;
		m_wPosXBACK = wPosX;
		m_wPosYBACK = wPosY;
		m_bITEMLINK = bITEMLINK;

		RemoveAllInfo();

		if ( m_bITEMLINK )
		{
			//AddTextNoSplit ( "", NS_UITEXTCOLOR::WHITE );
		}
		CString strText, strText2;
		BOOL bValue = FALSE;
		int nExtraValue = 0;
		int nRandomValue;

		GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();
		SITEM* pItemData = GLItemMan::GetInstance().GetItem ( sItemCustom.sNativeID );
		SNATIVEID		m_sNativeID;

		{
				SITEMCUSTOM sCustomWrap = sItemCustom;
				BOOL bInsert = FALSE;
				EMITEMLEVEL emLevel = pItemData->sBasicOp.emLevel;
				if( !sCustomWrap.IsWrap() )
					strText.Format ( "%s",pItemData->GetName() );
				else
					strText.Format ( "Wrapped %s",pItemData->GetName() );
				BYTE uGRADE = sItemCustom.GETGRADE(EMGRINDING_NUNE);

					{
						CString strCombine;
						if ( uGRADE == 0 )
						{ strCombine.Format ( "         %s", strText ); }

						else

						{ strCombine.Format ( "         +%d %s", uGRADE, strText ); }

						DWORD dwLevel = (DWORD)pItemData->sBasicOp.emLevel;

						DWORD strColorName[20] = 
						{			
							NS_UITEXTCOLOR::PALEGREEN,//0
							NS_UITEXTCOLOR::PALEGREEN,//1
							NS_UITEXTCOLOR::PALEGREEN,//2
							NS_UITEXTCOLOR::PALEGREEN,//3
							NS_UITEXTCOLOR::PALEGREEN,//4
							NS_UITEXTCOLOR::SILVER,//5
							NS_UITEXTCOLOR::SILVER,//6
							NS_UITEXTCOLOR::ORANGE,//7 
							NS_UITEXTCOLOR::ORANGE,//8
							NS_UITEXTCOLOR::GOLD,//9
							NS_UITEXTCOLOR::AQUA,//10
							NS_UITEXTCOLOR::VIOLET,//11
							NS_UITEXTCOLOR::GREEN,//12
							NS_UITEXTCOLOR::RED,//13
							NS_UITEXTCOLOR::FUCHSIA,//14
							NS_UITEXTCOLOR::YELLOW,//15
							NS_UITEXTCOLOR::WHITE,//16
							NS_UITEXTCOLOR::LIGHTORANGE,//17
							NS_UITEXTCOLOR::VIOLET,//18
							NS_UITEXTCOLOR::LIME,//19
						};

						int ColorGrade = uGRADE;
						AddTextNoSplitBig( strCombine, strColorName[ColorGrade] );
						//Allow Spaces
						AddTextNoSplit ( " ", NS_UITEXTCOLOR::BLACK );
					}
	
				
				

		

		/*BOOL bInsert = FALSE;

		strText.Format ( "%s", ID2GAMEWORD ( "ITEM_BASIC_INFO", 0 ), pItemData->GetName() );
		BYTE uGRADE = sItemCustom.GETGRADE(EMGRINDING_NUNE);
		APPEND_ITEM_GRADE ( strText, uGRADE );

		DWORD dwLevel = (DWORD)pItemData->sBasicOp.emLevel;


		DWORD strColorName[GRADE_LIMIT_MAX+1] = 
		{			
			NS_UITEXTCOLOR::PALEGREEN,//0
			NS_UITEXTCOLOR::PALEGREEN,//1
			NS_UITEXTCOLOR::PALEGREEN,//2
			NS_UITEXTCOLOR::PALEGREEN,//3
			NS_UITEXTCOLOR::PALEGREEN,//4
			NS_UITEXTCOLOR::SILVER,//5
			NS_UITEXTCOLOR::SILVER,//6
			NS_UITEXTCOLOR::ORANGE,//7 
			NS_UITEXTCOLOR::ORANGE,//8
			NS_UITEXTCOLOR::GOLD,//9
			NS_UITEXTCOLOR::AQUA,//10
			NS_UITEXTCOLOR::VIOLET,//11
			NS_UITEXTCOLOR::GREEN,//12
			NS_UITEXTCOLOR::RED,//13
			NS_UITEXTCOLOR::FUCHSIA,//14
			NS_UITEXTCOLOR::YELLOW,//15
			NS_UITEXTCOLOR::WHITE,//16
			NS_UITEXTCOLOR::LIGHTORANGE,//17
			NS_UITEXTCOLOR::VIOLET,//17
		};

		int ColorGrade;

		if( uGRADE > 18 ){ 
		ColorGrade = 0;
		}else{
		ColorGrade = uGRADE;
		}
			AddTextNoSplit ( strText, strColorName[ColorGrade] );*/
				
			
				DWORD dwReqSchool = pItemData->sBasicOp.dwReqSchool;
				CString strSchool;
				if ( pItemData->sBasicOp.dwReqSchool!=GLSCHOOL_ALL )
					{
						if ( pItemData->sBasicOp.dwReqSchool & GLSCHOOL_00)
						{
							strSchool += "Sacred Gate";
						}
						if ( pItemData->sBasicOp.dwReqSchool & GLSCHOOL_01)
						{
							strSchool += "Mystic Peak";
						}
						if ( pItemData->sBasicOp.dwReqSchool & GLSCHOOL_02)
						{
							strSchool += "Phoenix";
						}						
					}
					else
					{
						strSchool = ID2GAMEWORD ( "ITEM_REQ_SCHOOL", 3 );
					}

			if( sItemCustom.nidDISGUISE != NATIVEID_NULL() )
					{
						SITEM* pItemDisguise = GLItemMan::GetInstance().GetItem ( sItemCustom.nidDISGUISE );
						DWORD dwReqCharClass_Disguise = pItemDisguise->sBasicOp.dwReqCharClass;
						DWORD dwReqCharClass = pItemData->sBasicOp.dwReqCharClass;
						CString szClass;

						if( dwReqCharClass )
						{
							//if ( (dwReqCharClass==GLCC_ALL_NEWSEX) && (dwReqCharClass_Disguise==GLCC_ALL_NEWSEX) )
							//add class
							if ( (dwReqCharClass==GLCC_ALL_NEWSEX) && (dwReqCharClass_Disguise==GLCC_ALL_NEWSEX) )
							{
								szClass = ("All Classes");
							}
							else if (((dwReqCharClass&GLCC_FIGHTER_M) && (dwReqCharClass_Disguise&GLCC_FIGHTER_M) &&
										(dwReqCharClass&GLCC_ARMS_M)  && (dwReqCharClass_Disguise&GLCC_ARMS_M) 	  &&	
									  (dwReqCharClass&GLCC_ARCHER_M)  && (dwReqCharClass_Disguise&GLCC_ARCHER_M)  &&	
									  (dwReqCharClass&GLCC_SPIRIT_M)  && (dwReqCharClass_Disguise&GLCC_SPIRIT_M)  &&	
									 (dwReqCharClass&GLCC_EXTREME_M)  && (dwReqCharClass_Disguise&GLCC_EXTREME_M) &&
									 (dwReqCharClass&GLCC_SCIENCE_M)  && (dwReqCharClass_Disguise&GLCC_SCIENCE_M) &&	
									 (dwReqCharClass&GLCC_ASSASSIN_M)  && (dwReqCharClass_Disguise&GLCC_ASSASSIN_M) ) 
																	  ||
									 ((dwReqCharClass&GLCC_FIGHTER_M) && (dwReqCharClass_Disguise&GLCC_FIGHTER_M) &&
										(dwReqCharClass&GLCC_ARMS_M)  && (dwReqCharClass_Disguise&GLCC_ARMS_M) 	  &&	
									  (dwReqCharClass&GLCC_ARCHER_M)  && (dwReqCharClass_Disguise&GLCC_ARCHER_M)  &&	
									  (dwReqCharClass&GLCC_SPIRIT_M)  && (dwReqCharClass_Disguise&GLCC_SPIRIT_M)  &&	
									 (dwReqCharClass&GLCC_EXTREME_M)  && (dwReqCharClass_Disguise&GLCC_EXTREME_M) &&
									 (dwReqCharClass&GLCC_SCIENCE_M)  && (dwReqCharClass_Disguise&GLCC_SCIENCE_M) )	)
							{
								szClass = ("All Male Classes");
							}
							else if (((dwReqCharClass&GLCC_FIGHTER_W) && (dwReqCharClass_Disguise&GLCC_FIGHTER_W) &&
										(dwReqCharClass&GLCC_ARMS_W)  && (dwReqCharClass_Disguise&GLCC_ARMS_W) 	  &&	
									  (dwReqCharClass&GLCC_ARCHER_W)  && (dwReqCharClass_Disguise&GLCC_ARCHER_W)  &&	
									  (dwReqCharClass&GLCC_SPIRIT_W)  && (dwReqCharClass_Disguise&GLCC_SPIRIT_W)  &&	
									 (dwReqCharClass&GLCC_EXTREME_W)  && (dwReqCharClass_Disguise&GLCC_EXTREME_W) &&
									 (dwReqCharClass&GLCC_SCIENCE_W)  && (dwReqCharClass_Disguise&GLCC_SCIENCE_W) &&	
									 (dwReqCharClass&GLCC_ASSASSIN_W)  && (dwReqCharClass_Disguise&GLCC_ASSASSIN_W)) 
																	  ||
									 ((dwReqCharClass&GLCC_FIGHTER_W) && (dwReqCharClass_Disguise&GLCC_FIGHTER_W) &&
										(dwReqCharClass&GLCC_ARMS_W)  && (dwReqCharClass_Disguise&GLCC_ARMS_W) 	  &&	
									  (dwReqCharClass&GLCC_ARCHER_W)  && (dwReqCharClass_Disguise&GLCC_ARCHER_W)  &&	
									  (dwReqCharClass&GLCC_SPIRIT_W)  && (dwReqCharClass_Disguise&GLCC_SPIRIT_W)  &&	
									 (dwReqCharClass&GLCC_EXTREME_W)  && (dwReqCharClass_Disguise&GLCC_EXTREME_W) &&
									 (dwReqCharClass&GLCC_SCIENCE_W)  && (dwReqCharClass_Disguise&GLCC_SCIENCE_W) )	)
							{
								szClass = ("All Female Classes");
							}
							else
							{
								if ( (dwReqCharClass&GLCC_FIGHTER_M) && (dwReqCharClass_Disguise&GLCC_FIGHTER_M) &&
									(dwReqCharClass&GLCC_FIGHTER_W) && (dwReqCharClass_Disguise&GLCC_FIGHTER_W))
								{
									szClass+="/Brawler";
								}
								if ( (dwReqCharClass&GLCC_ARMS_M)  && (dwReqCharClass_Disguise&GLCC_ARMS_M) &&
									(dwReqCharClass&GLCC_ARMS_W)  && (dwReqCharClass_Disguise&GLCC_ARMS_W))
								{
									szClass+="/Swordie";
								}
								if ( (dwReqCharClass&GLCC_ARCHER_M)  && (dwReqCharClass_Disguise&GLCC_ARCHER_M) &&
									(dwReqCharClass&GLCC_ARCHER_W)  && (dwReqCharClass_Disguise&GLCC_ARCHER_W))
								{
									szClass+="/Archer";
								}
								if ( (dwReqCharClass&GLCC_SPIRIT_M)  && (dwReqCharClass_Disguise&GLCC_SPIRIT_M) &&
									(dwReqCharClass&GLCC_SPIRIT_W)  && (dwReqCharClass_Disguise&GLCC_SPIRIT_W))
								{
									szClass+="/Shaman";
								}
								if ( (dwReqCharClass&GLCC_EXTREME_M)  && (dwReqCharClass_Disguise&GLCC_EXTREME_M) &&
									(dwReqCharClass&GLCC_EXTREME_W)  && (dwReqCharClass_Disguise&GLCC_EXTREME_W))
								{
									szClass+="/Extreme";
								}
								//add class
								if ( (dwReqCharClass&GLCC_SCIENCE_M)  && (dwReqCharClass_Disguise&GLCC_SCIENCE_M) &&
									(dwReqCharClass&GLCC_SCIENCE_W)  && (dwReqCharClass_Disguise&GLCC_SCIENCE_W))
								{
									szClass+="/Gunner";
								}
								if ( (dwReqCharClass&GLCC_ASSASSIN_M)  && (dwReqCharClass_Disguise&GLCC_ASSASSIN_M) &&
									(dwReqCharClass&GLCC_ASSASSIN_W)  && (dwReqCharClass_Disguise&GLCC_ASSASSIN_W))
								{
									szClass+="/Assassin";
								}
							}

						strText.Format( "%s", szClass.GetString() );
						//AddTextNoSplit ( strText, NS_UITEXTCONTROL::GetEvaluateColor( 
						//(dwReqCharClass&pCharacter->m_emClass) && (dwReqCharClass_Disguise&pCharacter->m_emClass) ) );
				}
			}
			else
			{
				DWORD dwReqCharClass = pItemData->sBasicOp.dwReqCharClass;
						CString szClass;
						
						if( dwReqCharClass )
						{
							//if ( dwReqCharClass==GLCC_ALL_NEWSEX)
							//add class
							if ( dwReqCharClass==GLCC_ALL_NEWSEX)
							{
								szClass = ("/All Classes");
							}
							else if ((( dwReqCharClass & GLCC_FIGHTER_M) && ( dwReqCharClass & GLCC_ARMS_M) 	&&
									   ( dwReqCharClass & GLCC_ARCHER_M) && ( dwReqCharClass & GLCC_SPIRIT_M) 	&&
									  ( dwReqCharClass & GLCC_EXTREME_M) &&	( dwReqCharClass & GLCC_SCIENCE_M) 	&&
									  ( dwReqCharClass & GLCC_ASSASSIN_M) )	
																		 ||										
									 (( dwReqCharClass & GLCC_FIGHTER_M) && ( dwReqCharClass & GLCC_ARMS_M) 	&&
									   ( dwReqCharClass & GLCC_ARCHER_M) && ( dwReqCharClass & GLCC_SPIRIT_M) 	&&
									  ( dwReqCharClass & GLCC_EXTREME_M) &&	( dwReqCharClass & GLCC_SCIENCE_M) 	&&
									  ( dwReqCharClass & GLCC_ASSASSIN_M))		)
							{
								szClass = ("/All Male Classes");
							}
							else if ((( dwReqCharClass & GLCC_FIGHTER_W) && ( dwReqCharClass & GLCC_ARMS_W) 	&&
									   ( dwReqCharClass & GLCC_ARCHER_W) && ( dwReqCharClass & GLCC_SPIRIT_W) 	&&
									  ( dwReqCharClass & GLCC_EXTREME_W) &&	( dwReqCharClass & GLCC_SCIENCE_W) 	&&
									  ( dwReqCharClass & GLCC_ASSASSIN_W))	
																		 ||										
									 (( dwReqCharClass & GLCC_FIGHTER_W) && ( dwReqCharClass & GLCC_ARMS_W) 	&&
									   ( dwReqCharClass & GLCC_ARCHER_W) && ( dwReqCharClass & GLCC_SPIRIT_W) 	&&
									  ( dwReqCharClass & GLCC_EXTREME_W) &&	( dwReqCharClass & GLCC_SCIENCE_W) 	&&
									  ( dwReqCharClass & GLCC_ASSASSIN_W))	)
							{
								szClass = ("/All Female Classes");
							}
							else
							{
								if (( dwReqCharClass & GLCC_FIGHTER_M)&&( dwReqCharClass & GLCC_FIGHTER_W))
								{
									szClass+="/Brawler";
								}
								if (( dwReqCharClass & GLCC_ARMS_M)&&( dwReqCharClass & GLCC_ARMS_W))
								{
									szClass+="/Swordie";
								}
								if (( dwReqCharClass & GLCC_ARCHER_M)&&( dwReqCharClass & GLCC_ARCHER_W))
								{
									szClass+="/Archer";
								}
								if (( dwReqCharClass & GLCC_SPIRIT_M)&&( dwReqCharClass & GLCC_SPIRIT_W))
								{
									szClass+="/Shaman";
								}
								if (( dwReqCharClass & GLCC_EXTREME_M)&&( dwReqCharClass & GLCC_EXTREME_W))
								{
									szClass+="/Extreme";
								}
								//add class
								if (( dwReqCharClass & GLCC_SCIENCE_M)&&( dwReqCharClass & GLCC_SCIENCE_W))
								{
									szClass+="/Scientist";
								}
								if (( dwReqCharClass & GLCC_ASSASSIN_M)&&( dwReqCharClass & GLCC_ASSASSIN_W))
								{
									szClass+="/Assassin";
								}
							}

					strText.Format( "%s", szClass.GetString() );
					//AddTextNoSplit ( strText, NS_UITEXTCONTROL::GetEvaluateColor ( dwReqCharClass & pCharacter->m_emClass ) );
				}
			}

			//CString strItemReq = " " + strSchool + strText;
			CString strItemReq; 
			strItemReq.Format ( "            %s", strSchool + strText);
			AddTextNoSplit ( strItemReq, NS_UITEXTCOLOR::WHITE );
			
			if ( pItemData->sBasicOp.wReqLevelDW || pItemData->sBasicOp.wReqLevelUP )
			{
				bool bReqLevel = true;
				strText.Format( "            %s %d", ID2GAMEWORD("ITEM_ADVANCED_INFO_CONDITION", 0), pItemData->sBasicOp.wReqLevelDW );
									
				if ( pItemData->sBasicOp.wReqLevelUP )
				{
					strText2.Format ( " ~ %d",pItemData->sBasicOp.wReqLevelUP );
					strText += strText2; 
					bReqLevel = (pItemData->sBasicOp.wReqLevelUP >= pCharacter->m_wLevel);
				}

				AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( pItemData->sBasicOp.wReqLevelDW <= pCharacter->m_wLevel && bReqLevel ) );
			}
			else
			{
				AddTextNoSplit( " ", NS_UITEXTCOLOR::BLACK );
			}

			if ( pItemData->sBasicOp.emItemType == ITEM_BOX  )
			{
				AddTextNoSplit( " ", NS_UITEXTCOLOR::BLACK );
				AddTextNoSplit( " ", NS_UITEXTCOLOR::BLACK );
				AddTextNoSplit( " ", NS_UITEXTCOLOR::BLACK );
				AddTextNoSplit( " ", NS_UITEXTCOLOR::BLACK );
				AddTextNoSplit( " ", NS_UITEXTCOLOR::BLACK );
			}

			const int nELEC   = sItemCustom.GETRESIST_ELEC();
			const int nFIRE   = sItemCustom.GETRESIST_FIRE();
			const int nICE    = sItemCustom.GETRESIST_ICE();
			const int nPOISON = sItemCustom.GETRESIST_POISON();
			const int nSPIRIT = sItemCustom.GETRESIST_SPIRIT();
					
			if ( (nELEC) && (nFIRE) && (nICE) && (nPOISON) && (nSPIRIT) )
			{
				//strText.Format ( "Resistance:      %d      %d      %d      %d      %d      ", nELEC, nFIRE, nICE, nPOISON, nSPIRIT );
				//strText.Format ( "Resistance: \t%d \t%d \t%d \t%d \t%d", nELEC, nFIRE, nICE, nPOISON, nSPIRIT );
				if ( (nELEC) && (nFIRE) && (nICE) && (nPOISON) && (nSPIRIT) <=9 )
				{
				strText.Format ( "      %d        %d        %d         %d        %d", nELEC, nFIRE, nICE, nPOISON, nSPIRIT );
				BYTE uGRADE = ( (sItemCustom.GETGRADE(EMGRINDING_RESIST_ELEC)) 	 && 
								(sItemCustom.GETGRADE(EMGRINDING_RESIST_FIRE)) 	 && 
								(sItemCustom.GETGRADE(EMGRINDING_RESIST_ICE)) 	 && 
								(sItemCustom.GETGRADE(EMGRINDING_RESIST_POISON)) && 
								(sItemCustom.GETGRADE(EMGRINDING_RESIST_SPIRIT)) );
				APPEND_ITEM_GRADE ( strText, uGRADE );
				AddTextNoSplit(strText,NS_UITEXTCOLOR::LIME);
				}
				else if ( (nELEC) && (nFIRE) && (nICE) && (nPOISON) && (nSPIRIT) <= 99 )
				{
				strText.Format ( "     %d       %d      %d       %d      %d", nELEC, nFIRE, nICE, nPOISON, nSPIRIT );
				BYTE uGRADE = ( (sItemCustom.GETGRADE(EMGRINDING_RESIST_ELEC)) 	 && 
								(sItemCustom.GETGRADE(EMGRINDING_RESIST_FIRE)) 	 && 
								(sItemCustom.GETGRADE(EMGRINDING_RESIST_ICE)) 	 && 
								(sItemCustom.GETGRADE(EMGRINDING_RESIST_POISON)) && 
								(sItemCustom.GETGRADE(EMGRINDING_RESIST_SPIRIT)) );
				APPEND_ITEM_GRADE ( strText, uGRADE );
				AddTextNoSplit(strText,NS_UITEXTCOLOR::LIME);
				}

				else if ( (nELEC) || (nFIRE) || (nICE) || (nPOISON) || (nSPIRIT) <= 999 )
				{
				strText.Format ( "     %d    %d     %d     %d     %d", nELEC, nFIRE, nICE, nPOISON, nSPIRIT );
				BYTE uGRADE = ( (sItemCustom.GETGRADE(EMGRINDING_RESIST_ELEC)) 	 && 
								(sItemCustom.GETGRADE(EMGRINDING_RESIST_FIRE)) 	 && 
								(sItemCustom.GETGRADE(EMGRINDING_RESIST_ICE)) 	 && 
								(sItemCustom.GETGRADE(EMGRINDING_RESIST_POISON)) && 
								(sItemCustom.GETGRADE(EMGRINDING_RESIST_SPIRIT)) );
				APPEND_ITEM_GRADE ( strText, uGRADE );
				AddTextNoSplit(strText,NS_UITEXTCOLOR::LIME);
				}

			}

				/*BYTE uGRADE = ( (sItemCustom.GETGRADE(EMGRINDING_RESIST_ELEC)) 	 && 
								(sItemCustom.GETGRADE(EMGRINDING_RESIST_FIRE)) 	 && 
								(sItemCustom.GETGRADE(EMGRINDING_RESIST_ICE)) 	 && 
								(sItemCustom.GETGRADE(EMGRINDING_RESIST_POISON)) && 
								(sItemCustom.GETGRADE(EMGRINDING_RESIST_SPIRIT)));
				APPEND_ITEM_GRADE ( strText, uGRADE );
				AddTextNoSplit(strText,NS_UITEXTCOLOR::LIME);*/
			
			
			//	쌀??죗
			if ( sItemCustom.nidDISGUISE!=SNATIVEID(false) )
			{
				SITEM* pDisguiseData = GLItemMan::GetInstance().GetItem ( sItemCustom.nidDISGUISE );

				strText.Format ( "%s:%s", ID2GAMEWORD ( "ITEM_BASIC_INFO", 3 ), pDisguiseData->GetName() );			
				AddTextNoSplit ( strText, NS_UITEXTCOLOR::GREENYELLOW );
			}

			//	코스츔 기간 표시
			if ( sItemCustom.tDISGUISE!=0 )
			{				
				CTime cTime(sItemCustom.tDISGUISE);
				if ( cTime.GetYear()!=1970 )
				{
					CString strExpireDate;
					strExpireDate = CInnerInterface::GetInstance().MakeString( ID2GAMEWORD("ITEM_EXPIRE_DATE"),
																				(cTime.GetYear ()%2000), 
																				cTime.GetMonth (), 
																				cTime.GetDay (), 
																				cTime.GetHour (), 
																				cTime.GetMinute () );

					strText.Format ( "%s:%s", ID2GAMEWORD ( "ITEM_BASIC_INFO", 7 ), strExpireDate );			
					AddTextNoSplit ( strText, NS_UITEXTCOLOR::DARKORANGE );
				}
			}

			LONGLONG dwCOMMISSION_MONEY = 0;

			//	2.가격
			if ( pItemData->sBasicOp.dwBuyPrice || bInPrivateMarket )
			{
				if ( bInPrivateMarket )
				{
					bool bOPENER;
					DWORD dwPrivateMarketID;
					CInnerInterface::GetInstance().GetPrivateMarketInfo ( bOPENER, dwPrivateMarketID );
					if ( bOPENER )	//	파는 사람
					{
						GLPrivateMarket &sPMarket = GLGaeaClient::GetInstance().GetCharacter()->m_sPMarket;

						const SSALEITEM *pSALE = sPMarket.GetItem ( SNATIVEID(wPosX,wPosY) ); 
						if ( pSALE )
						{
							CString strMoney = NS_UITEXTCONTROL::MAKE_MONEY_FORMAT ( pSALE->llPRICE, 3, "," );
							CString GetMoneyCon = NS_UITEXTCONTROL::MAKE_MONEY_FORMAT ( pSALE->llPRICE, 3, "" );
							strText.Format ( "%s:%s", ID2GAMEWORD ( "ITEM_BASIC_INFO", 5 ), strMoney );		

							LONGLONG GetMoneyColor = _ttoi64(GetMoneyCon);
							if ( GetMoneyColor >= 0 && GetMoneyColor <= 99999 ){ AddTextNoSplit ( strText, GLCONST_CHAR::dwITEM_MONEY_COLOR0 );}
							if ( GetMoneyColor >= 100000 && GetMoneyColor <= 999999 ){ AddTextNoSplit ( strText, GLCONST_CHAR::dwITEM_MONEY_COLOR1 );}
							if ( GetMoneyColor >= 1000000 && GetMoneyColor <= 9999999 ){ AddTextNoSplit ( strText, GLCONST_CHAR::dwITEM_MONEY_COLOR2 );}
							if ( GetMoneyColor >= 10000000 && GetMoneyColor <= 99999999 ){ AddTextNoSplit ( strText, GLCONST_CHAR::dwITEM_MONEY_COLOR3 );}
							if ( GetMoneyColor >= 100000000 && GetMoneyColor <= 999999999 ){ AddTextNoSplit ( strText, GLCONST_CHAR::dwITEM_MONEY_COLOR4 );}
							if ( GetMoneyColor >= 1000000000 && GetMoneyColor <= 9999999999 ){ AddTextNoSplit ( strText, GLCONST_CHAR::dwITEM_MONEY_COLOR5 );}
							if ( GetMoneyColor >= 10000000000 && GetMoneyColor <= 99999999999 ){ AddTextNoSplit ( strText, GLCONST_CHAR::dwITEM_MONEY_COLOR6 );}
							if ( GetMoneyColor >= 100000000000 && GetMoneyColor <= 999999999999 ){ AddTextNoSplit ( strText, GLCONST_CHAR::dwITEM_MONEY_COLOR7 );}
							if ( GetMoneyColor >= 1000000000000  ){ AddTextNoSplit ( strText, NS_UITEXTCOLOR::WHITE );}
						}						
					}
					else		//	사는 사람
					{
						PGLCHARCLIENT pCLIENT = GLGaeaClient::GetInstance().GetChar ( dwPrivateMarketID );
						if ( !pCLIENT ) return ;

						GLPrivateMarket &sPMarket = pCLIENT->m_sPMarket;

						const SSALEITEM *pSALE = sPMarket.GetItem ( SNATIVEID(wPosX,wPosY) ); 
						if ( pSALE )
						{
							CString strMoney = NS_UITEXTCONTROL::MAKE_MONEY_FORMAT ( pSALE->llPRICE, 3, "," );
							CString GetMoneyCon = NS_UITEXTCONTROL::MAKE_MONEY_FORMAT ( pSALE->llPRICE, 3, "" );
							strText.Format ( "%s:%s", ID2GAMEWORD ( "ITEM_BASIC_INFO", 5 ), strMoney );		

							LONGLONG GetMoneyColor = _ttoi64(GetMoneyCon);
							if ( GetMoneyColor >= 0 && GetMoneyColor <= 99999 ){ AddTextNoSplit ( strText, GLCONST_CHAR::dwITEM_MONEY_COLOR0 );}
							if ( GetMoneyColor >= 100000 && GetMoneyColor <= 999999 ){ AddTextNoSplit ( strText, GLCONST_CHAR::dwITEM_MONEY_COLOR1 );}
							if ( GetMoneyColor >= 1000000 && GetMoneyColor <= 9999999 ){ AddTextNoSplit ( strText, GLCONST_CHAR::dwITEM_MONEY_COLOR2 );}
							if ( GetMoneyColor >= 10000000 && GetMoneyColor <= 99999999 ){ AddTextNoSplit ( strText, GLCONST_CHAR::dwITEM_MONEY_COLOR3 );}
							if ( GetMoneyColor >= 100000000 && GetMoneyColor <= 999999999 ){ AddTextNoSplit ( strText, GLCONST_CHAR::dwITEM_MONEY_COLOR4 );}
							if ( GetMoneyColor >= 1000000000 && GetMoneyColor <= 9999999999 ){ AddTextNoSplit ( strText, GLCONST_CHAR::dwITEM_MONEY_COLOR5 );}
							if ( GetMoneyColor >= 10000000000 && GetMoneyColor <= 99999999999 ){ AddTextNoSplit ( strText, GLCONST_CHAR::dwITEM_MONEY_COLOR6 );}
							if ( GetMoneyColor >= 100000000000 && GetMoneyColor <= 999999999999 ){ AddTextNoSplit ( strText, GLCONST_CHAR::dwITEM_MONEY_COLOR7 );}
							if ( GetMoneyColor >= 1000000000000  ){ AddTextNoSplit ( strText, NS_UITEXTCOLOR::WHITE );}
						}
					}
				}				
				else if ( bShopOpen && bInMarket )	// 살때 가격
				{
					LONGLONG dwNpcSellPrice = 0;

					volatile LONGLONG dwPrice = 0;
					volatile float fSHOP_RATE = GLGaeaClient::GetInstance().GetCharacter()->GetBuyRate();
					volatile float fSHOP_RATE_C = fSHOP_RATE * 0.01f;

					if( sNpcNativeID.wMainID != 0 && sNpcNativeID.wSubID != 0 )
					{
						PCROWDATA pCrowData = GLCrowDataMan::GetInstance().GetCrowData ( sNpcNativeID );
						if( pCrowData != NULL )
						{
							LONGLONG dwNpcPrice = pCrowData->GetNpcSellPrice( pItemData->sBasicOp.sNativeID.dwID );
							if( dwNpcPrice == 0 )
							{								
								dwNpcSellPrice = pItemData->sBasicOp.dwBuyPrice;
								dwPrice = DWORD ( (float)dwNpcSellPrice * fSHOP_RATE_C );
							}else{
								dwNpcSellPrice = dwNpcPrice;
								dwPrice = dwNpcSellPrice;								
							}
						}

					}				

					
					CString strMoney = NS_UITEXTCONTROL::MAKE_MONEY_FORMAT ( dwPrice, 3, "," );

					strText.Format( "%s:%s", ID2GAMEWORD("ITEM_BASIC_INFO", 1), strMoney );

					//	커미션 액수
					dwCOMMISSION_MONEY = dwPrice - dwNpcSellPrice;
					
					D3DCOLOR dwColor = NS_UITEXTCOLOR::RED;
					if( dwPrice <= GLGaeaClient::GetInstance().GetCharacterLogic().m_lnMoney )
					{
						dwColor = NS_UITEXTCOLOR::PALEGREEN;
					}
					AddTextNoSplit ( strText, dwColor );
				}
				else if ( bShopOpen ) // 팔때 가격
				{
					volatile float fSHOP_RATE = GLGaeaClient::GetInstance().GetCharacter()->GetSaleRate();
					volatile float fSALE_DISCOUNT = fSHOP_RATE * 0.01f;

					volatile DWORD dwPrice = pItemData->GETSELLPRICE ( sItemCustom.wTurnNum );
					volatile DWORD dwSALE_PRICE = DWORD ( dwPrice * fSALE_DISCOUNT );					

					//	커미션 액수
					volatile DWORD dwDISPRICE = pItemData->GETSELLPRICE ( sItemCustom.wTurnNum );
					dwCOMMISSION_MONEY = dwDISPRICE - dwSALE_PRICE;

					CString strMoney = NS_UITEXTCONTROL::MAKE_MONEY_FORMAT ( dwSALE_PRICE, 3, "," );
					strText.Format( "%s:%s", ID2GAMEWORD("ITEM_BASIC_INFO", 1), strMoney );

					AddTextNoSplit ( strText, NS_UITEXTCOLOR::PALEGREEN );
				}
			}

			//	수수료 표시
			if ( dwCOMMISSION_MONEY )
			{
				CString strMoney = NS_UITEXTCONTROL::MAKE_MONEY_FORMAT ( dwCOMMISSION_MONEY, 3, "," );
				strText.Format( "%s:%s", ID2GAMEWORD("ITEM_BASIC_INFO", 6), strMoney );

				AddTextNoSplit ( strText, NS_UITEXTCOLOR::PALEGREEN );
			}

			//	수량표시
			AddItemTurnInfo ( sItemCustom, bInMarket, bInPrivateMarket );

			//	기간표시
			if ( pItemData->IsTIMELMT () )
			{
				CTime cTime(sItemCustom.tBORNTIME);
				if ( cTime.GetYear()!=1970 )
				{
					CTimeSpan sLMT(pItemData->sDrugOp.tTIME_LMT);
					cTime += sLMT;

					CString strExpireDate;
					strExpireDate = CInnerInterface::GetInstance().MakeString ( ID2GAMEWORD("ITEM_EXPIRE_DATE"),
						(cTime.GetYear ()%2000), cTime.GetMonth (), cTime.GetDay (), cTime.GetHour (), cTime.GetMinute () );

					strText.Format ( "%s:%s", ID2GAMEWORD ( "ITEM_BASIC_INFO", 4 ), strExpireDate );			
					AddTextNoSplit ( strText, NS_UITEXTCOLOR::DARKORANGE );
				}
			}

		


			//	재사용 대기시간
			if ( pItemData->sBasicOp.IsCoolTime() )
			{
				CString strTime = "";
				CTimeSpan cCoolTime( pItemData->sBasicOp.dwCoolTime );
				
				if ( cCoolTime.GetHours() > 0 )	
					strTime += CInnerInterface::GetInstance().MakeString( "%d%s ", cCoolTime.GetHours(), ID2GAMEWORD ( "ITEM_BASIC_TIME", 0 ) );
				if ( cCoolTime.GetMinutes() > 0 )	
					strTime += CInnerInterface::GetInstance().MakeString( "%d%s ", cCoolTime.GetMinutes(), ID2GAMEWORD ( "ITEM_BASIC_TIME", 1 ) );
				if ( cCoolTime.GetSeconds() > 0 )	
					strTime += CInnerInterface::GetInstance().MakeString( "%d%s ", cCoolTime.GetSeconds(), ID2GAMEWORD ( "ITEM_BASIC_TIME", 2 ) );

				strText.Format ( "%s : %s", ID2GAMEWORD ( "ITEM_BASIC_INFO", 8 ), strTime );			
				AddTextNoSplit ( strText, NS_UITEXTCOLOR::DARKORANGE );	
			}

			//	남은시간


			GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();
			if ( pCharacter && pCharacter->IsCoolTime( pItemData->sBasicOp.sNativeID ) )
			{
				CString strTime = "";
				__time64_t tCurTime =  GLGaeaClient::GetInstance().GetCurrentTime().GetTime();
				__time64_t tCoolTime = pCharacter->GetMaxCoolTime( pItemData->sBasicOp.sNativeID );				

				CTimeSpan cReTime( tCoolTime - tCurTime );

                if ( cReTime.GetHours() > 0 )	
					strTime += CInnerInterface::GetInstance().MakeString( "%d%s ", cReTime.GetHours(), ID2GAMEWORD ( "ITEM_BASIC_TIME", 0 ) );
				if ( cReTime.GetMinutes() > 0 )	
					strTime += CInnerInterface::GetInstance().MakeString( "%d%s ", cReTime.GetMinutes(), ID2GAMEWORD ( "ITEM_BASIC_TIME", 1 ) );
				if ( cReTime.GetSeconds() > 0 )	
					strTime += CInnerInterface::GetInstance().MakeString( "%d%s ", cReTime.GetSeconds(), ID2GAMEWORD ( "ITEM_BASIC_TIME", 2 ) );

				strText.Format ( "%s : %s", ID2GAMEWORD ( "ITEM_BASIC_INFO", 9 ), strTime );			
				AddTextNoSplit ( strText, NS_UITEXTCOLOR::DARKORANGE );
			}

			//////////////////////////////////////////////////////////////////////////////////////////////////////
			//	AdvInfo
			SCHARSTATS& rItemStats = pItemData->sBasicOp.sReqStats;
			SCHARSTATS& rCharStats = pCharacter->m_sSUMSTATS;
			EMITEM_TYPE emItemType = pItemData->sBasicOp.emItemType;

			switch ( emItemType )
			{
			case ITEM_SUIT:
			case ITEM_REVIVE:
			case ITEM_ANTI_DISAPPEAR:
            //case ITEM_VEHICLE:
				{
					BYTE uGRADE = 0;
					float fRandomVal;

					//	공격 속성
					if ( pItemData->sSuitOp.emAttack != ITEMATT_NOTHING )
					{
						strText.Format("%s (%s)", ID2GAMEWORD("ITEM_ADVANCED_INFO", 6), COMMENT::ITEMATTACK[pItemData->sSuitOp.emAttack].c_str() );
						AddTextNoSplit ( strText, NS_UITEXTCOLOR::WHITE );
					}

					//	착용위치
					if(pItemData->sSuitOp.emSuit!=SUIT_HANDHELD)
					{
						strText.Format("%s ", COMMENT::ITEMSUIT[pItemData->sSuitOp.emSuit].c_str() );
						AddTextNoSplit (strText, NS_UITEXTCOLOR::WHITE );
					}

					//	공격 거리
					/*if ( sItemCustom.GETATTRANGE() )
					{
						strText.Format("%s: %dm",ID2GAMEWORD("ITEM_ADVANCED_INFO", 2), sItemCustom.GETATTRANGE() );
						AddTextNoSplit ( strText, NS_UITEXTCOLOR::WHITE );
					}*/

					//	공격력
					GLPADATA &sDamage = sItemCustom.getdamage();
					nExtraValue = sItemCustom.GETGRADE_DAMAGE();
					uGRADE = sItemCustom.GETGRADE(EMGRINDING_DAMAGE);
					fRandomVal = sItemCustom.GETOptVALUE(EMR_OPT_ATTACK_VOL);
					//nRandomValue = EMR_OPT_DAMAGE;
					INT nRandOptType1 = sItemCustom.GETOptTYPE1();
					INT nRandOptType2 = sItemCustom.GETOptTYPE2();
					INT nRandOptType3 = sItemCustom.GETOptTYPE3();
					INT nRandOptType4 = sItemCustom.GETOptTYPE4();
					if( sItemCustom.IsSetRandOpt() )
					{
						if ( nRandOptType1 && nRandOptType1 == EMR_OPT_ATTACK_VOL )
						{
							if ( uGRADE == 0 )
							{
								AddInfoItemAddonRange(sDamage.dwLow, sDamage.dwHigh, fRandomVal, ID2GAMEWORD("ITEM_ADVANCED_INFO", 0) );
							}
							else
							{
								AddInfoItemAddonRange ( sDamage.dwLow, sDamage.dwHigh, nExtraValue, fRandomVal, ID2GAMEWORD("ITEM_ADVANCED_INFO", 0) );
							}
						}
						else if ( nRandOptType2 && nRandOptType2 == EMR_OPT_ATTACK_VOL ) 
						{
							if ( uGRADE == 0 )
							{
								AddInfoItemAddonRange(sDamage.dwLow, sDamage.dwHigh, fRandomVal, ID2GAMEWORD("ITEM_ADVANCED_INFO", 0) );
							}
							else
							{
								AddInfoItemAddonRange ( sDamage.dwLow, sDamage.dwHigh, nExtraValue, fRandomVal, ID2GAMEWORD("ITEM_ADVANCED_INFO", 0) );
							}
						}
						else if ( nRandOptType3 && nRandOptType3 == EMR_OPT_ATTACK_VOL ) 
						{
							if ( uGRADE == 0 )
							{
								AddInfoItemAddonRange(sDamage.dwLow, sDamage.dwHigh, fRandomVal, ID2GAMEWORD("ITEM_ADVANCED_INFO", 0) );
							}
							else
							{
								AddInfoItemAddonRange ( sDamage.dwLow, sDamage.dwHigh, nExtraValue, fRandomVal, ID2GAMEWORD("ITEM_ADVANCED_INFO", 0) );
							}
						}
						else if ( nRandOptType4 && nRandOptType4 == EMR_OPT_ATTACK_VOL ) 
						{
							if ( uGRADE == 0 )
							{
								AddInfoItemAddonRange(sDamage.dwLow, sDamage.dwHigh, fRandomVal, ID2GAMEWORD("ITEM_ADVANCED_INFO", 0) );
							}
							else
							{
								AddInfoItemAddonRange ( sDamage.dwLow, sDamage.dwHigh, nExtraValue, fRandomVal, ID2GAMEWORD("ITEM_ADVANCED_INFO", 0) );
							}
						}
						else
						{
							AddInfoItemAddonRange ( sDamage.dwLow, sDamage.dwHigh, nExtraValue, uGRADE, ID2GAMEWORD("ITEM_ADVANCED_INFO", 0) );
						}
					}
					else
					{
						AddInfoItemAddonRange ( sDamage.dwLow, sDamage.dwHigh, nExtraValue, uGRADE,ID2GAMEWORD("ITEM_ADVANCED_INFO", 0) );
					}
					
					//	???
					short nDefense = sItemCustom.getdefense();
					nExtraValue = sItemCustom.GETGRADE_DEFENSE();
					uGRADE = sItemCustom.GETGRADE(EMGRINDING_DEFENSE);
					float fRandomVal1 = sItemCustom.GETOptVALUE(EMR_OPT_DEFENSE_VOL);
					INT nRandOptType11 = sItemCustom.GETOptTYPE1();
					INT nRandOptType22 = sItemCustom.GETOptTYPE2();
					INT nRandOptType33 = sItemCustom.GETOptTYPE3();
					INT nRandOptType44 = sItemCustom.GETOptTYPE4();
					if( sItemCustom.IsSetRandOpt() )
					{
						if ( nRandOptType11 && nRandOptType11 == EMR_OPT_DEFENSE_VOL )
						{
							if ( uGRADE == 0 )
							{
								AddInfoItemAddon(nDefense, fRandomVal1, ID2GAMEWORD("ITEM_ADVANCED_INFO", 1) );
							}
							else
							{
								AddInfoItemAddon ( nDefense, nExtraValue, fRandomVal1, ID2GAMEWORD("ITEM_ADVANCED_INFO", 1) );
							}
						}
						else if ( nRandOptType22 && nRandOptType22 == EMR_OPT_DEFENSE_VOL ) 
						{
							if ( uGRADE == 0 )
							{
								AddInfoItemAddon(nDefense, fRandomVal1, ID2GAMEWORD("ITEM_ADVANCED_INFO", 1) );
							}
							else
							{
								AddInfoItemAddon ( nDefense, nExtraValue, fRandomVal1, ID2GAMEWORD("ITEM_ADVANCED_INFO", 1) );
							}
						}
						else if ( nRandOptType33 && nRandOptType33 == EMR_OPT_DEFENSE_VOL ) 
						{
							if ( uGRADE == 0 )
							{
								AddInfoItemAddon(nDefense, fRandomVal1, ID2GAMEWORD("ITEM_ADVANCED_INFO", 1) );
							}
							else
							{
								AddInfoItemAddon ( nDefense, nExtraValue, fRandomVal1, ID2GAMEWORD("ITEM_ADVANCED_INFO", 1) );
							}
						}
						else if ( nRandOptType44 && nRandOptType44 == EMR_OPT_DEFENSE_VOL ) 
						{
							if ( uGRADE == 0 )
							{
								AddInfoItemAddon(nDefense, fRandomVal1, ID2GAMEWORD("ITEM_ADVANCED_INFO", 1) );
							}
							else
							{
								AddInfoItemAddon ( nDefense, nExtraValue, fRandomVal1, ID2GAMEWORD("ITEM_ADVANCED_INFO", 1) );
							}
						}
						else
						{
							AddInfoItemAddon ( nDefense, nExtraValue, ID2GAMEWORD("ITEM_ADVANCED_INFO", 1) );
						}
					}
					else
					{
						AddInfoItemAddon ( nDefense, nExtraValue, ID2GAMEWORD("ITEM_ADVANCED_INFO", 1) );
					}
					//AddInfoItemAddon ( nDefense, nExtraValue, ID2GAMEWORD("ITEM_ADVANCED_INFO", 1) );
					
					//	???
					if ( sItemCustom.GETHITRATE() )
					{
						nExtraValue = 0;
						AddInfoItemAddon ( sItemCustom.GETHITRATE(), nExtraValue, ID2GAMEWORD("ITEM_ADVANCED_INFO", 3) );		
					}

					//	회피율
					if ( sItemCustom.GETAVOIDRATE() )
					{
						nExtraValue = 0;
						AddInfoItemAddon ( sItemCustom.GETAVOIDRATE(), nExtraValue, ID2GAMEWORD("ITEM_ADVANCED_INFO", 4) );
					}
					
					//	SP 소모
					const WORD wReqSP = sItemCustom.GETREQ_SP();
					if ( 0 < wReqSP )
					{
						strText.Format("%s :%d", ID2GAMEWORD("ITEM_ADVANCED_INFO", 7), wReqSP );
						AddTextNoSplit ( strText, NS_UITEXTCOLOR::WHITE );
					}

					//	조건 - 암광
					/*
					bValue = TRUE;
					strText.Format ( "%s", COMMENT::BRIGHT[pItemData->sBasicOp.emReqBright].c_str() );
					if ( pItemData->sBasicOp.emReqBright != BRIGHT_BOTH )
					{
						if ( pCharacter->GETBRIGHT() != pItemData->sBasicOp.emReqBright )
						{
							bValue = FALSE;
						}
					}
					AddTextNoSplit ( strText, NS_UITEXTCONTROL::GetEvaluateColor ( bValue ) );					
					*/

					//	착용조건->격투치
					if ( pItemData->sBasicOp.wReqPA )
					{
						strText.Format("%s :%d", ID2GAMEWORD("ITEM_ADVANCED_INFO_CONDITION", 1), pItemData->sBasicOp.wReqPA );
						AddTextNoSplit ( strText, NS_UITEXTCONTROL::GetEvaluateColor ( pItemData->sBasicOp.wReqPA <= pCharacter->m_wSUM_PA ) );
					}
					//	착용조건->사격치
					if ( pItemData->sBasicOp.wReqSA )
					{
						strText.Format("%s :%d", ID2GAMEWORD("ITEM_ADVANCED_INFO_CONDITION", 2 ), pItemData->sBasicOp.wReqSA );
						AddTextNoSplit(strText,NS_UITEXTCONTROL::GetEvaluateColor ( pItemData->sBasicOp.wReqSA <= pCharacter->m_wSUM_SA ));
					}

					//	Stats
					//	착용조건->힘
					if ( rItemStats.dwPow )
					{
						strText.Format( "%s :%d", ID2GAMEWORD("ITEM_ADVANCED_INFO_CONDITION_STATS", 0 ), rItemStats.dwPow );
						AddTextNoSplit ( strText, NS_UITEXTCONTROL::GetEvaluateColor ( rItemStats.dwPow <= rCharStats.dwPow ) );
					}
					//	착용조건->체력
					if ( rItemStats.dwStr )
					{
						strText.Format("%s :%d", ID2GAMEWORD("ITEM_ADVANCED_INFO_CONDITION_STATS", 1 ), rItemStats.dwStr );
						AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( rItemStats.dwStr <= rCharStats.dwStr ) );
					}
					//	착용조건->정신력
					if ( rItemStats.dwSpi)
					{
						strText.Format("%s :%d", ID2GAMEWORD("ITEM_ADVANCED_INFO_CONDITION_STATS", 2 ), rItemStats.dwSpi );
						AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( rItemStats.dwSpi <= rCharStats.dwSpi ) );
					}
					//	착용조건->민첩성
					if ( rItemStats.dwDex )
					{
						strText.Format("%s :%d", ID2GAMEWORD("ITEM_ADVANCED_INFO_CONDITION_STATS", 3 ), rItemStats.dwDex );
						AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( rItemStats.dwDex <= rCharStats.dwDex ) );
					}
					//	착용조건->지력
					if ( rItemStats.dwInt  )
					{
						strText.Format("%s :%d", ID2GAMEWORD("ITEM_ADVANCED_INFO_CONDITION_STATS", 4 ), rItemStats.dwInt );
						AddTextNoSplit(strText, NS_UITEXTCONTROL::GetEvaluateColor ( rItemStats.dwInt <= rCharStats.dwInt ) );
					}
					//	착용조건->근력
					if ( rItemStats.dwSta )
					{
						strText.Format("%s :%d", ID2GAMEWORD("ITEM_ADVANCED_INFO_CONDITION_STATS", 5 ), rItemStats.dwSta );
						AddTextNoSplit ( strText, NS_UITEXTCONTROL::GetEvaluateColor ( rItemStats.dwSta <= rCharStats.dwSta ) );
					}

					float fExpMultiple = pItemData->GetExpMultiple();
					if( fExpMultiple != 1.0f )
					{
						strText.Format("%s %2.2f", ID2GAMEWORD( "ITEM_ADVANCED_INFO_SPECIAL_EX", 0 ), fExpMultiple);
						AddTextNoSplit(strText,NS_UITEXTCOLOR::DODGERBLUE);
					}

					

					//-----------------------------------------------------------------------------------------------
					//	저항값
					/*const int nELEC   = sItemCustom.GETRESIST_ELEC();
					const int nFIRE   = sItemCustom.GETRESIST_FIRE();
					const int nICE    = sItemCustom.GETRESIST_ICE();
					const int nPOISON = sItemCustom.GETRESIST_POISON();
					const int nSPIRIT = sItemCustom.GETRESIST_SPIRIT();

					if ( nELEC || nFIRE || nICE || nPOISON || nSPIRIT )
					{
						AddTextNoSplit ( ID2GAMEWORD ( "ITEM_CATEGORY", 3 ), NS_UITEXTCOLOR::LIGHTSKYBLUE );

						if ( nELEC )
						{
							strText.Format("%s:%d", ID2GAMEWORD("ITEM_ADVANCED_INFO_RESIST", 0 ), nELEC );	
							BYTE uGRADE = sItemCustom.GETGRADE(EMGRINDING_RESIST_ELEC);
							APPEND_ITEM_GRADE ( strText, uGRADE );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::PRIVATE);
						}
						if ( nFIRE )
						{
							strText.Format("%s:%d", ID2GAMEWORD("ITEM_ADVANCED_INFO_RESIST", 1 ), nFIRE );
							BYTE uGRADE = sItemCustom.GETGRADE(EMGRINDING_RESIST_FIRE);
							APPEND_ITEM_GRADE ( strText, uGRADE );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::PRIVATE);
						}
						if ( nICE )
						{
							strText.Format("%s:%d", ID2GAMEWORD("ITEM_ADVANCED_INFO_RESIST", 2 ), nICE );
							BYTE uGRADE = sItemCustom.GETGRADE(EMGRINDING_RESIST_ICE);
							APPEND_ITEM_GRADE ( strText, uGRADE );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::PRIVATE);
						}
						if ( nPOISON )
						{
							strText.Format("%s:%d", ID2GAMEWORD("ITEM_ADVANCED_INFO_RESIST", 3 ), nPOISON );
							BYTE uGRADE = sItemCustom.GETGRADE(EMGRINDING_RESIST_POISON);
							APPEND_ITEM_GRADE ( strText, uGRADE );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::PRIVATE);
						}
						if ( nSPIRIT )
						{
							strText.Format("%s:%d", ID2GAMEWORD("ITEM_ADVANCED_INFO_RESIST", 4 ), nSPIRIT );
							BYTE uGRADE = sItemCustom.GETGRADE(EMGRINDING_RESIST_SPIRIT);
							APPEND_ITEM_GRADE ( strText, uGRADE );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::PRIVATE);
						}
					}*/
		
					//	상태이상
					EMSTATE_BLOW emBLOW = pItemData->sSuitOp.sBLOW.emTYPE;
					float fVAR1 = pItemData->sSuitOp.sBLOW.fVAR1 * COMMENT::BLOW_VAR1_SCALE[emBLOW];
					float fVAR2 = pItemData->sSuitOp.sBLOW.fVAR2 * COMMENT::BLOW_VAR2_SCALE[emBLOW];

					if ( emBLOW !=EMBLOW_NONE )
					{
						AddTextNoSplit ( " ", NS_UITEXTCOLOR::LIGHTSKYBLUE );

						if ( emBLOW == EMBLOW_NUMB )
						{
							strText.Format("%.0f", pItemData->sSuitOp.sBLOW.fRATE );
							strText += ("% chance of Paralysis effect, decreased" );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);
							strText.Format("movement and attack speed by %.0f", fVAR1 );
							strText += "%, skill";
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);
							strText.Format("cool down time is increased by %.0f for %.0f", fVAR2, pItemData->sSuitOp.sBLOW.fLIFE );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);
							AddTextNoSplit("seconds",NS_UITEXTCOLOR::LIGHTYELLOW);
						}
						else if ( emBLOW == EMBLOW_FROZEN )
						{
							strText.Format("%.0f", pItemData->sSuitOp.sBLOW.fRATE );
							strText += ("% chance of Frost effect, decreased" );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);
							strText.Format("movement and attack speed by %.0f", fVAR1 );
							strText += "% ";
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);
							strText.Format("for %.0f seconds, +%.0f", pItemData->sSuitOp.sBLOW.fLIFE, fVAR2 );
							strText += "% damage";
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);
						}
						else if ( emBLOW == EMBLOW_STUN )
						{
							strText.Format("%.0f", pItemData->sSuitOp.sBLOW.fRATE );
							strText += ( "% chance of Stun effect, unable to act");
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);
							strText.Format("for %.0f second with 0 additional damage", pItemData->sSuitOp.sBLOW.fLIFE );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);
						}
						else if ( emBLOW == EMBLOW_BURN )
						{
							strText.Format("%.0f", pItemData->sSuitOp.sBLOW.fRATE );
							strText += ( "% chance of Flame effect and");
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);
							strText.Format("%.0f seconds to give %.0f damage per", pItemData->sSuitOp.sBLOW.fLIFE, fVAR2 );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);
							strText.Format("seconds" );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);
						}
						else if ( emBLOW == EMBLOW_POISON )
						{
							strText.Format("%.0f", pItemData->sSuitOp.sBLOW.fRATE );
							strText += ( "% chance of Intoxication effect, and");
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);
							strText.Format("for %.0f seconds %.0f damage per seconds", pItemData->sSuitOp.sBLOW.fLIFE, fVAR2 );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);
							//strText.Format("" );
							//AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);
						}
						else if ( emBLOW == EMBLOW_STONE )
						{

							strText.Format("%.0f", pItemData->sSuitOp.sBLOW.fRATE );
							strText += "% chance of Fossil effect, decreased";
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);
							strText.Format("movement and attack speed by %.0f", fVAR1 );
							strText += "%";
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);
							strText.Format("and %.0f damage for %.0f seconds", fVAR2, pItemData->sSuitOp.sBLOW.fLIFE );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);
						}
						else if ( emBLOW == EMBLOW_MAD )
						{

							strText.Format("With the probability of %.0f", pItemData->sSuitOp.sBLOW.fRATE );
							strText += "% to give Fossil";
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);
							strText.Format(" effect to the opponent and attack with the " );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);
							strText.Format(" effect of attack speed and moving speed" );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);
							strText.Format(" continuous %.1f seconds to decreased %.0f", pItemData->sSuitOp.sBLOW.fLIFE, fVAR2  );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);
						}
						else {
							strText.Format("%s:%s", ID2GAMEWORD("ITEM_ADVANCED_INFO_ABNORMAL", 0 ), COMMENT::BLOW[emBLOW].c_str() );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);

							strText.Format("%s:%.2f", ID2GAMEWORD("ITEM_ADVANCED_INFO_ABNORMAL", 1 ),pItemData->sSuitOp.sBLOW.fLIFE );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);

							strText.Format("%s:%.2f%%", ID2GAMEWORD("ITEM_ADVANCED_INFO_ABNORMAL", 2 ),pItemData->sSuitOp.sBLOW.fRATE );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);

							{
								float fVAR1 = pItemData->sSuitOp.sBLOW.fVAR1 * COMMENT::BLOW_VAR1_SCALE[emBLOW];

								if( fVAR1 != 0.0f )
								{
									if ( COMMENT::IsBLOW1_PER(emBLOW) )
										strText.Format("%s:%.2f%%", COMMENT::BLOW_VAR1[emBLOW].c_str(), fVAR1 );
									else
										strText.Format("%s:%.2f", COMMENT::BLOW_VAR1[emBLOW].c_str(), fVAR1 );

									AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);
								}
							}

							{
								float fVAR2 = pItemData->sSuitOp.sBLOW.fVAR2 * COMMENT::BLOW_VAR2_SCALE[emBLOW];

								if( fVAR2 != 0.0f )
								{
									if ( COMMENT::IsBLOW2_PER(emBLOW) )
										strText.Format("%s:%.2f%%", COMMENT::BLOW_VAR2[emBLOW].c_str(), fVAR2 );
									else
										strText.Format("%s:%.2f", COMMENT::BLOW_VAR2[emBLOW].c_str(), fVAR2 );

									AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTYELLOW);
								}
							}
						}
					}


					//	NOTE
					//		가산 효과
					AddTextAddValue( sItemCustom, pItemData->sSuitOp );

					//	특수기능
					//
					{
						BOOL bSPAC = sItemCustom.GETINCHP() || sItemCustom.GETINCMP() || sItemCustom.GETINCSP() || sItemCustom.GETINCAP();
						BOOL bVAR_HP(FALSE), bVAR_MP(FALSE), bVAR_SP(FALSE), bVAR_AP(FALSE);


						EMITEM_VAR emITEM_VAR = pItemData->sSuitOp.sVARIATE.emTYPE;
						EMITEM_VAR emITEM_VOL = pItemData->sSuitOp.sVOLUME.emTYPE;
						/*
						if ( (emITEM_VAR!=EMVAR_NONE) || (emITEM_VOL!=EMVAR_NONE) || bSPAC )
						{
							AddTextNoSplit ( ID2GAMEWORD ( "ITEM_CATEGORY", 5 ), NS_UITEXTCOLOR::LIGHTSKYBLUE );
						}
						*/
						
						if ( sItemCustom.nidDISGUISE!=SNATIVEID(false) )
						{
							SITEM* pJDisguiseData = GLItemMan::GetInstance().GetItem ( sItemCustom.nidDISGUISE );
							if ( pJDisguiseData )
							{
								if ( pJDisguiseData->sBasicOp.IsCostumeCombine() )
								{
									EMITEM_VAR emITEMCOS_VAR = pJDisguiseData->sSuitOp.sVARIATE.emTYPE;
									EMITEM_VAR emITEMCOS_VOL = pJDisguiseData->sSuitOp.sVOLUME.emTYPE;
								//add jitem

									float fVAR_SCALE(0);
									if ( emITEMCOS_VAR != EMVAR_NONE )
									{			
										
										fVAR_SCALE = pJDisguiseData->sSuitOp.sVARIATE.fVariate;
										CString strText2;
										fVAR_SCALE *= COMMENT::ITEMVAR_SCALE[emITEMCOS_VAR];
										strText2.Format("%s %2.2f", ID2GAMEWORD("ITEM_ADVANCED_INFO_SPECIAL_ADD", emITEMCOS_VAR ), fVAR_SCALE );
										if ( COMMENT::IsITEMVAR_SCALE(emITEMCOS_VAR) )		strText2 += "%";
										AddTextNoSplit(strText2,NS_UITEXTCOLOR::LIME);
									}

									if ( emITEMCOS_VOL != EMVAR_NONE)
									{
										CString strText3;
										float fVOLUME = pJDisguiseData->sSuitOp.sVOLUME.fVolume;
										strText3.Format("%s %.2f", ID2GAMEWORD("ITEM_ADVANCED_INFO_SPECIAL_ADD_VOL", emITEMCOS_VOL ), fVOLUME );
										AddTextNoSplit(strText3,NS_UITEXTCOLOR::LIME);
									}
								}
							}
						}



						//	특수기능 ( 변화율 )
						//
						float fVAR_SCALE(0);
						if ( emITEM_VAR != EMVAR_NONE )
						{
							switch ( emITEM_VAR )
							{
							case EMVAR_HP:
								bVAR_HP = TRUE;
								fVAR_SCALE = sItemCustom.GETINCHP();
								break;
							case EMVAR_MP:
								bVAR_MP = TRUE;
								fVAR_SCALE = sItemCustom.GETINCMP();
								break;
							case EMVAR_SP:
								bVAR_SP = TRUE;
								fVAR_SCALE = sItemCustom.GETINCSP();
								break;
							case EMVAR_AP:
								bVAR_AP = TRUE;
								fVAR_SCALE = sItemCustom.GETINCAP();
								break;
							default:
								fVAR_SCALE = pItemData->sSuitOp.sVARIATE.fVariate;
								break;
							};

							fVAR_SCALE *= COMMENT::ITEMVAR_SCALE[emITEM_VAR];
							strText.Format("%s %2.2f", ID2GAMEWORD("ITEM_ADVANCED_INFO_SPECIAL_ADD", emITEM_VAR ), fVAR_SCALE );
							if ( COMMENT::IsITEMVAR_SCALE(emITEM_VAR) )		strText += "%";
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIME);
						}

						if ( !bVAR_HP && sItemCustom.GETINCHP() )
						{
							fVAR_SCALE = sItemCustom.GETINCHP();
							emITEM_VAR = EMVAR_HP;
							fVAR_SCALE *= COMMENT::ITEMVAR_SCALE[emITEM_VAR];
							strText.Format("%s %2.2f", ID2GAMEWORD("ITEM_ADVANCED_INFO_SPECIAL_ADD", emITEM_VAR ), fVAR_SCALE );
							if ( COMMENT::IsITEMVAR_SCALE(emITEM_VAR) )		strText += "%";
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIME);
						}

						if ( !bVAR_MP && sItemCustom.GETINCMP() )
						{
							fVAR_SCALE = sItemCustom.GETINCMP();
							emITEM_VAR = EMVAR_MP;
							fVAR_SCALE *= COMMENT::ITEMVAR_SCALE[emITEM_VAR];
							strText.Format("%s %2.2f", ID2GAMEWORD("ITEM_ADVANCED_INFO_SPECIAL_ADD", emITEM_VAR ), fVAR_SCALE );
							if ( COMMENT::IsITEMVAR_SCALE(emITEM_VAR) )		strText += "%";
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIME);
						}

						if ( !bVAR_SP && sItemCustom.GETINCSP() )
						{
							fVAR_SCALE = sItemCustom.GETINCSP();
							emITEM_VAR = EMVAR_SP;
							fVAR_SCALE *= COMMENT::ITEMVAR_SCALE[emITEM_VAR];
							strText.Format("%s %2.2f", ID2GAMEWORD("ITEM_ADVANCED_INFO_SPECIAL_ADD", emITEM_VAR ), fVAR_SCALE );
							if ( COMMENT::IsITEMVAR_SCALE(emITEM_VAR) )		strText += "%";
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIME);
						}

						if ( !bVAR_AP && sItemCustom.GETINCAP() )
						{
							fVAR_SCALE = sItemCustom.GETINCAP();
							emITEM_VAR = EMVAR_AP;
							fVAR_SCALE *= COMMENT::ITEMVAR_SCALE[emITEM_VAR];
							strText.Format("%s %2.2f", ID2GAMEWORD("ITEM_ADVANCED_INFO_SPECIAL_ADD", emITEM_VAR ), fVAR_SCALE );
							if ( COMMENT::IsITEMVAR_SCALE(emITEM_VAR) )		strText += "%";
							AddTextNoSplit(strText,NS_UITEXTCOLOR::LIME);
						}

						// 경험치 배율						

						//	특수기능 ( 변화량 )
						//
						if ( emITEM_VOL != EMVAR_NONE)
						{
							if ( emITEM_VOL == EMVAR_MOVE_SPEED )
							{
								float fVOLUME = sItemCustom.GETMOVESPEED();
								strText.Format("%s %.2f", ID2GAMEWORD("ITEM_ADVANCED_INFO_SPECIAL_ADD_VOL", emITEM_VOL ), fVOLUME );
								AddTextNoSplit(strText,NS_UITEXTCOLOR::LIME);
							}
							else
							{
								float fVOLUME = pItemData->sSuitOp.sVOLUME.fVolume;
								strText.Format("%s %.2f", ID2GAMEWORD("ITEM_ADVANCED_INFO_SPECIAL_ADD_VOL", emITEM_VOL ), fVOLUME );
								AddTextNoSplit(strText,NS_UITEXTCOLOR::LIME);
							}
							
						}
					}

					// Note : 랜덤 수치
					if( sItemCustom.IsSetRandOpt() )
					{
						CString strDescText;

						//AddTextNoSplit( ID2GAMEWORD ( "ITEM_CATEGORY", 11 ), NS_UITEXTCOLOR::LIGHTSKYBLUE );
						AddTextNoSplit( "", NS_UITEXTCOLOR::WHITE );//spacer here

						
						//Add Rate Values Random Option #1 -- Ocram Networkso
						INT nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_DAMAGE) )
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_DEFENSE) )
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_HITRATE) )
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_AVOIDRATE) )
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_HP) ) //HP Add not VIT
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_MP) ) //MP Add not INT
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_SP) ) //SP Add not STA
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_HP_INC) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_MP_INC) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_SP_INC) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_HMS_INC) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_GRIND_DAMAGE) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_GRIND_DEFENSE) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_RANGE) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_DIS_SP) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_RESIST) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_MOVE_SPEED) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						//Add Direct Values Random Option #1 -- Ocram Networkso

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_ATTACK_VOL) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_DEFENSE_VOL) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_HIT_VOL) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_AVOID_VOL) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_POWER) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_VITALITY) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_SPIRIT) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_DEXTERITY) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_STAMINA) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_MELEE) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_SHOOTING) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_ENERGY) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_HP_REC) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_MP_REC) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType1 = sItemCustom.GETOptTYPE1();
						if( (nRandOptType1 && nRandOptType1 == EMR_OPT_SP_REC) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType1 ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType1 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						//Add Rate Values Random Option #2 -- Ocram Networkso
						INT nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_DAMAGE) )
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_DEFENSE) )
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_HITRATE) )
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_AVOIDRATE) )
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_HP) ) //HP Add not VIT
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_MP) ) //MP Add not INT
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_SP) ) //SP Add not STA
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_HP_INC) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_MP_INC) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_SP_INC) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_HMS_INC) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_GRIND_DAMAGE) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_GRIND_DEFENSE) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_RANGE) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_DIS_SP) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_RESIST) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_MOVE_SPEED) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						//Add Direct Values Random Option #2 -- Ocram Networkso

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_ATTACK_VOL) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_DEFENSE_VOL) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_HIT_VOL) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_AVOID_VOL) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_POWER) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_VITALITY) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_SPIRIT) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_DEXTERITY) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_STAMINA) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_MELEE) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_SHOOTING) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_ENERGY) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_HP_REC) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_MP_REC) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType2 = sItemCustom.GETOptTYPE2();
						if( (nRandOptType2 && nRandOptType2 == EMR_OPT_SP_REC) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType2 ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType2 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						//Add Rate Values Random Option #3 -- Ocram Networkso
						INT nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_DAMAGE) )
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_DEFENSE) )
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_HITRATE) )
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_AVOIDRATE) )
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_HP) ) //HP Add not VIT
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_MP) ) //MP Add not INT
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_SP) ) //SP Add not STA
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_HP_INC) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_MP_INC) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_SP_INC) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_HMS_INC) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_GRIND_DAMAGE) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_GRIND_DEFENSE) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_RANGE) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_DIS_SP) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_RESIST) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_MOVE_SPEED) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						//Add Direct Values Random Option #3 -- Ocram Networkso

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_ATTACK_VOL) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_DEFENSE_VOL) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_HIT_VOL) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_AVOID_VOL) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_POWER) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_VITALITY) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_SPIRIT) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_DEXTERITY) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_STAMINA) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_MELEE) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_SHOOTING) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_ENERGY) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_HP_REC) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_MP_REC) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType3 = sItemCustom.GETOptTYPE3();
						if( (nRandOptType3 && nRandOptType3 == EMR_OPT_SP_REC) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType3 ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType3 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						//Add Rate Values Random Option #4 -- Ocram Networkso
						INT nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_DAMAGE) )
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_DEFENSE) )
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_HITRATE) )
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_AVOIDRATE) )
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_HP) ) //HP Add not VIT
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_MP) ) //MP Add not INT
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_SP) ) //SP Add not STA
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_HP_INC) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_MP_INC) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_SP_INC) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_HMS_INC) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_GRIND_DAMAGE) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_GRIND_DEFENSE) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_RANGE) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_DIS_SP) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_RESIST) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_MOVE_SPEED) ) //Rate of regeneration
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						//Add Direct Values Random Option #4 -- Ocram Networkso

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_ATTACK_VOL) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_DEFENSE_VOL) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_HIT_VOL) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_AVOID_VOL) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_POWER) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_VITALITY) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_SPIRIT) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_DEXTERITY) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_STAMINA) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_MELEE) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_SHOOTING) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_ENERGY) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_HP_REC) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_MP_REC) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}

						nRandOptType4 = sItemCustom.GETOptTYPE4();
						if( (nRandOptType4 && nRandOptType4 == EMR_OPT_SP_REC) ) //add direct value - Ocram Networkso
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType4 ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.f", fVal );
								if( sItemCustom.IsPerRandOpt( nRandOptType4 ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::DODGERBLUE );
							}
						}
					}
				}
				break;
			case ITEM_CHARM:
				{
					/*AddTextNoSplit ( ID2GAMEWORD ( "ITEM_CATEGORY", 1 ), NS_UITEXTCOLOR::LIGHTSKYBLUE );

					//	공격력
					GLPADATA &sDAMAGE = sItemCustom.GETDAMAGE();
					if ( sDAMAGE.dwLow || sDAMAGE.dwHigh  )
					{
						strText.Format("Talisman %s:%s~%s ", ID2GAMEWORD("ITEM_ARROW_INFO", 0 ), 
													GetNumberWithSign ( sDAMAGE.dwLow ), 
													GetNumberWithSign ( sDAMAGE.dwHigh ) );

						AddTextNoSplit(strText,NS_UITEXTCOLOR::DEFAULT);
					}
 

					//	NOTE
					//		가산 효과
					AddTextAddValue( sItemCustom, pItemData->sSuitOp );	*/

					AddTextNoSplit ( ID2GAMEWORD ( "ITEM_CATEGORY", 1 ), NS_UITEXTCOLOR::LIGHTSKYBLUE );

					BYTE uGRADE = 0;

					//	공격력
					GLPADATA &sDamage = sItemCustom.getdamage();
					nExtraValue = sItemCustom.GETGRADE_DAMAGE();
					uGRADE = sItemCustom.GETGRADE(EMGRINDING_DAMAGE);
					AddInfoItemAddonRange ( sDamage.dwLow, sDamage.dwHigh, nExtraValue, uGRADE, ID2GAMEWORD("ITEM_ADVANCED_INFO", 0) );

					//	기력치
					
				}
				break;

			case ITEM_DRUG_CP:
				{
					//AddTextNoSplit ( ID2GAMEWORD ( "ITEM_CATEGORY", 7 ), NS_UITEXTCOLOR::LIGHTSKYBLUE );

					if( pItemData->sDrugOp.wCureVolume == 0 )
					{
						strText.Format("%s",COMMENT::ITEMDRUG[pItemData->sDrugOp.emDrug].c_str());
					}
					else
					{
						strText.Format("%s:%d",COMMENT::ITEMDRUG[pItemData->sDrugOp.emDrug].c_str(), pItemData->sDrugOp.wCureVolume);
					}

					AddTextNoSplit(strText, NS_UITEXTCOLOR::WHITE);
				}
				break;

	case ITEM_ARROW:
				{
					AddTextNoSplit ( " ", NS_UITEXTCOLOR::LIGHTSKYBLUE );

					//	공격력
					GLPADATA &sDAMAGE = sItemCustom.GETDAMAGE();
					if ( sDAMAGE.dwLow || sDAMAGE.dwHigh  )
					{
						strText.Format("Arrow %s:%s~%s ", ID2GAMEWORD("ITEM_ARROW_INFO", 0 ), 
													GetNumberWithSign ( sDAMAGE.dwLow ), 
													GetNumberWithSign ( sDAMAGE.dwHigh ) );

						AddTextNoSplit(strText,NS_UITEXTCOLOR::WHITE);
					}
 

					//	NOTE
					//		가산 효과
					AddTextAddValue( sItemCustom, pItemData->sSuitOp );					
				}
				break;
				//add bullet
			case ITEM_BULLET:
				{
					AddTextNoSplit (" ", NS_UITEXTCOLOR::LIGHTSKYBLUE );

					//	공격력
					GLPADATA &sDAMAGE = sItemCustom.GETDAMAGE();
					if ( sDAMAGE.dwLow || sDAMAGE.dwHigh  )
					{
						strText.Format("Bullet %s:%s~%s ", ID2GAMEWORD("ITEM_ARROW_INFO", 0 ), 
													GetNumberWithSign ( sDAMAGE.dwLow ), 
													GetNumberWithSign ( sDAMAGE.dwHigh ) );

						AddTextNoSplit(strText,NS_UITEXTCOLOR::WHITE);
					}
 

					//	NOTE
					//		가산 효과
					AddTextAddValue( sItemCustom, pItemData->sSuitOp );					
				}
				break;

			case ITEM_CURE:
				{
					//AddTextNoSplit ( ID2GAMEWORD ( "ITEM_CATEGORY", 7 ), NS_UITEXTCOLOR::YELLOW );

					if( pItemData->sDrugOp.wCureVolume == 0 )
					{
						strText.Format("%s",COMMENT::ITEMDRUG[pItemData->sDrugOp.emDrug].c_str());
					}
					else
					{
						strText.Format("%s:%d",COMMENT::ITEMDRUG[pItemData->sDrugOp.emDrug].c_str(), pItemData->sDrugOp.wCureVolume);
					}

					AddTextNoSplit(strText, NS_UITEXTCOLOR::WHITE);
				}
				break;

			case ITEM_SKILL:
				{
					AddInfoSkillItem ( sItemCustom );
				}
				break;

			case ITEM_PET_SKILL:
				{
					AddInfoPetSkillItem( sItemCustom );
				}
				break;

			case ITEM_GRINDING:
				{
					AddTextNoSplit ( ID2GAMEWORD ( "ITEM_CATEGORY_EX", 0 ), NS_UITEXTCOLOR::LIGHTSKYBLUE );
				}
				break;

				// 경험치 획득 카드 정보
			case ITEM_VIETNAM_EXPGET:
				{
					if ( pItemData->sDrugOp.bRatio )
					{
						strText.Format(ID2GAMEWORD ("ITEM_CATEGORY_VIETNAM_EXP", 1) , pItemData->sDrugOp.wCureVolume );						
					}
					else
					{
						strText.Format(ID2GAMEWORD ("ITEM_CATEGORY_VIETNAM_EXP", 0), pItemData->sDrugOp.wCureVolume );
					}

					AddTextNoSplit(strText,NS_UITEXTCOLOR::WHITE);
				}
				break;
				// 아이템 획득 카드 정보
			case ITEM_VIETNAM_ITEMGET:
				{
					strText.Format(ID2GAMEWORD ("ITEM_CATEGORY_VIETNAM_ITEM", 0) , pItemData->sDrugOp.wCureVolume );
					AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTSKYBLUE);
				}
				break;

			case ITEM_VEHICLE:
				{
					strText.Format(ID2GAMEWORD ("ITEM_VEHICLE_TYPE_INFO", 0) , COMMENT::VEHICLE_TYPE[pItemData->sVehicle.emVehicleType].c_str() );
					AddTextNoSplit(strText,NS_UITEXTCOLOR::WHITE);

					strText.Format( "%s %s", ID2GAMEWORD ("ITEM_VEHICLE_NAME",0), COMMENT::VEHICLE_TYPE[pItemData->sVehicle.emVehicleType].c_str() );
					AddTextNoSplit(strText,NS_UITEXTCOLOR::WHITE);

					
					EMITEM_VAR emITEM_VOL = pItemData->sSuitOp.sVOLUME.emTYPE;
					//	이동속도 변화량
					AddTextAddValue( sItemCustom, pItemData->sSuitOp );					
					//
					if ( emITEM_VOL != EMVAR_NONE)
					{
						if ( emITEM_VOL == EMVAR_MOVE_SPEED )
						{
							float fVOLUME = sItemCustom.GETMOVESPEED();
							strText.Format("%s %.2f", ID2GAMEWORD("ITEM_ADVANCED_INFO_SPECIAL_ADD_VOL", emITEM_VOL ), fVOLUME );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::PRIVATE);
						}
						else
						{
							float fVOLUME = pItemData->sSuitOp.sVOLUME.fVolume;
							strText.Format("%s %.2f", ID2GAMEWORD("ITEM_ADVANCED_INFO_SPECIAL_ADD_VOL", emITEM_VOL ), fVOLUME );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::PRIVATE);
						}
					}


					bool bInfo(true);

					
					VEHICLEITEMINFO_MAP_ITER iter = GLGaeaClient::GetInstance().GetCharacter()->m_mapVEHICLEItemInfo.find ( sItemCustom.dwVehicleID );
					if ( iter == GLGaeaClient::GetInstance().GetCharacter()->m_mapVEHICLEItemInfo.end() )
					{
						iter = GLGaeaClient::GetInstance().GetCharacter()->m_mapVEHICLEItemInfoTemp.find ( sItemCustom.dwVehicleID );
						if ( iter == GLGaeaClient::GetInstance().GetCharacter()->m_mapVEHICLEItemInfoTemp.end() )	bInfo = false;
					}


					if ( bInfo ) 
					{
						SVEHICLEITEMINFO sVehicleItemInfo = (*iter).second;
						for ( int i = 0; i < ACCE_TYPE_SIZE; ++i ) 
						{
							SITEM* pItem = GLItemMan::GetInstance().GetItem ( sVehicleItemInfo.m_PutOnItems[i].sNativeID );
							if ( pItem )
							{
								strText.Format("%s %s", ID2GAMEWORD ("ITEM_VEHICLE_SLOT",i), pItem->GetName () );
								AddTextNoSplit(strText,NS_UITEXTCOLOR::WHITE);
							}
						}

						strText.Format( "%s %.2f%%", ID2GAMEWORD ("ITEM_VEHICLE_BATTERY",0), sVehicleItemInfo.m_nFull/10.0f );
						AddTextNoSplit(strText,NS_UITEXTCOLOR::WHITE);
					}


					/*AddTextNoSplit( ID2GAMEWORD ( "ITEM_CATEGORY", 2 ), NS_UITEXTCOLOR::LIGHTSKYBLUE );

					DWORD dwReqCharClass = pItemData->sBasicOp.dwReqCharClass;
					CString szClass;
					
					if( dwReqCharClass )
					{
						//if ( dwReqCharClass==GLCC_ALL_NEWSEX_NEWSEX)
						//add class
						if ( dwReqCharClass==GLCC_ALL_NEWSEX)
						{
							szClass = ID2GAMEWORD("ITEM_ALL_CLASS");
						}
						else
						{
							if ( dwReqCharClass & GLCC_FIGHTER_M)
							{
								szClass+=COMMENT::CHARCLASS[CharClassToIndex(GLCC_FIGHTER_M)].c_str();
								szClass+=" ";
							}
							if ( dwReqCharClass & GLCC_FIGHTER_W)
							{
								szClass+=COMMENT::CHARCLASS[CharClassToIndex(GLCC_FIGHTER_W)].c_str();
								szClass+=" ";
							}
							if ( dwReqCharClass & GLCC_ARMS_M)
							{
								szClass+=COMMENT::CHARCLASS[CharClassToIndex(GLCC_ARMS_M)].c_str();
								szClass+=" ";
							}
							if ( dwReqCharClass & GLCC_ARMS_W)
							{
								szClass+=COMMENT::CHARCLASS[CharClassToIndex(GLCC_ARMS_W)].c_str();
								szClass+=" ";
							}
							if ( dwReqCharClass & GLCC_ARCHER_M)
							{
								szClass+=COMMENT::CHARCLASS[CharClassToIndex(GLCC_ARCHER_M)].c_str();
								szClass+=" ";
							}
							if ( dwReqCharClass & GLCC_ARCHER_W)
							{
								szClass+=COMMENT::CHARCLASS[CharClassToIndex(GLCC_ARCHER_W)].c_str();
								szClass+=" ";
							}
							if ( dwReqCharClass & GLCC_SPIRIT_M)
							{
								szClass+=COMMENT::CHARCLASS[CharClassToIndex(GLCC_SPIRIT_M)].c_str();
								szClass+=" ";
							}
							if ( dwReqCharClass & GLCC_SPIRIT_W)
							{
								szClass+=COMMENT::CHARCLASS[CharClassToIndex(GLCC_SPIRIT_W)].c_str();
								szClass+=" ";
							}
							if ( dwReqCharClass & GLCC_EXTREME_M)
							{
								szClass+=COMMENT::CHARCLASS[CharClassToIndex(GLCC_EXTREME_M)].c_str();
								szClass+=" ";
							}
							if ( dwReqCharClass & GLCC_EXTREME_W)
							{
								szClass+=COMMENT::CHARCLASS[CharClassToIndex(GLCC_EXTREME_W)].c_str();
							}
							//add class
							if ( dwReqCharClass & GLCC_SCIENCE_M)
							{
								szClass+=COMMENT::CHARCLASS[CharClassToIndex(GLCC_SCIENCE_M)].c_str();
							}
							if ( dwReqCharClass & GLCC_SCIENCE_W)
							{
								szClass+=COMMENT::CHARCLASS[CharClassToIndex(GLCC_SCIENCE_W)].c_str();
							}
							if ( dwReqCharClass & GLCC_ASSASIN_M)
							{
								szClass+=COMMENT::CHARCLASS[CharClassToIndex(GLCC_ASSASIN_M)].c_str();
							}
							if ( dwReqCharClass & GLCC_ASSASIN_W)
							{
								szClass+=COMMENT::CHARCLASS[CharClassToIndex(GLCC_ASSASIN_W)].c_str();
							}
							if ( dwReqCharClass & GLCC_TESTING_M)
							{
								szClass+=COMMENT::CHARCLASS[CharClassToIndex(GLCC_TESTING_M)].c_str();
							}
							if ( dwReqCharClass & GLCC_TESTING_W)
							{
								szClass+=COMMENT::CHARCLASS[CharClassToIndex(GLCC_TESTING_W)].c_str();
							}
								//
						}

						strText.Format( "%s", szClass.GetString() );
						AddTextNoSplit ( strText, NS_UITEXTCONTROL::GetEvaluateColor ( dwReqCharClass & pCharacter->m_emClass ) );
					}*/	

					// Note : 랜덤 수치
					if( sItemCustom.IsSetRandOpt() )
					{
						CString strDescText;

						//AddTextNoSplit( ID2GAMEWORD ( "ITEM_CATEGORY", 11 ), NS_UITEXTCOLOR::LIGHTSKYBLUE );

						INT nRandOptType = sItemCustom.GETOptTYPE1();
						if( (EMR_OPT_NULL < nRandOptType) && (nRandOptType < EMR_OPT_SIZE) )
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType ) );

							float fVal = sItemCustom.GETOptVALUE1();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								//if( sItemCustom.IsPerRandOpt( nRandOptType ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::LIGHTSKYBLUE );
							}
						}

						nRandOptType = sItemCustom.GETOptTYPE2();
						if( (EMR_OPT_NULL < nRandOptType) && (nRandOptType < EMR_OPT_SIZE) )
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType ) );

							float fVal = sItemCustom.GETOptVALUE2();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								//if( sItemCustom.IsPerRandOpt( nRandOptType ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::LIGHTSKYBLUE );
							}
						}

						nRandOptType = sItemCustom.GETOptTYPE3();
						if( (EMR_OPT_NULL < nRandOptType) && (nRandOptType < EMR_OPT_SIZE) )
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType ) );

							float fVal = sItemCustom.GETOptVALUE3();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								//if( sItemCustom.IsPerRandOpt( nRandOptType ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::LIGHTSKYBLUE );
							}
						}

						nRandOptType = sItemCustom.GETOptTYPE4();
						if( (EMR_OPT_NULL < nRandOptType) && (nRandOptType < EMR_OPT_SIZE) )
						{
							strDescText.Format( "%s:", ID2GAMEWORD("ITEM_RANDOM_OPTION", nRandOptType ) );

							float fVal = sItemCustom.GETOptVALUE4();
							if( fVal != 0.0f )
							{
								if( fVal > 0.0f) strDescText += _T('+');

								strDescText.AppendFormat( "%.2f", fVal );
								//if( sItemCustom.IsPerRandOpt( nRandOptType ) ) strDescText += _T('%');

								AddTextNoSplit( strDescText, NS_UITEXTCOLOR::LIGHTSKYBLUE );
							}
						}
					}
				}
									AddTextNoSplit( " ", NS_UITEXTCOLOR::WHITE );

				break;

			case ITEM_PET_CARD:
				{
					if ( sItemCustom.dwPetID == 0 ) break;
					PETCARDINFO_MAP_ITER iter = GLGaeaClient::GetInstance().GetCharacter()->m_mapPETCardInfo.find ( sItemCustom.dwPetID );
					if ( iter == GLGaeaClient::GetInstance().GetCharacter()->m_mapPETCardInfo.end() )
					{
						iter = GLGaeaClient::GetInstance().GetCharacter()->m_mapPETCardInfoTemp.find ( sItemCustom.dwPetID );
						if ( iter == GLGaeaClient::GetInstance().GetCharacter()->m_mapPETCardInfoTemp.end() ) break;
					}

					SPETCARDINFO sPetCardInfo = (*iter).second;

					strText.Format(ID2GAMEWORD ("ITEM_PET_INFO", 0 ));
					AddTextNoSplit(strText,NS_UITEXTCOLOR::LIGHTSKYBLUE);

					strText.Format( "%s %s", ID2GAMEWORD ("ITEM_PET_NAME",0), sPetCardInfo.m_szName );
					AddTextNoSplit(strText,NS_UITEXTCOLOR::WHITE);

					strText.Format( "%s %s", ID2GAMEWORD ("ITEM_PET_TYPE",0), COMMENT::PET_TYPE[sPetCardInfo.m_emTYPE].c_str() );
					AddTextNoSplit(strText,NS_UITEXTCOLOR::WHITE);

					strText.Format( "%s %.2f%%", ID2GAMEWORD ("ITEM_PET_FULL",0), sPetCardInfo.m_nFull/10.0f );
					AddTextNoSplit(strText,NS_UITEXTCOLOR::WHITE);
					
					SITEM* pItem = GLItemMan::GetInstance().GetItem ( sPetCardInfo.m_PutOnItems[ACCETYPEA].sNativeID );
					if ( pItem )
					{
						strText.Format("%s %s", ID2GAMEWORD ("ITEM_PET_SLOTA",0), pItem->GetName () );
						AddTextNoSplit(strText,NS_UITEXTCOLOR::WHITE);
					}

					pItem = GLItemMan::GetInstance().GetItem ( sPetCardInfo.m_PutOnItems[ACCETYPEB].sNativeID );
					if ( pItem )
					{
						strText.Format("%s %s", ID2GAMEWORD ("ITEM_PET_SLOTB",0), pItem->GetName () );
						AddTextNoSplit(strText,NS_UITEXTCOLOR::WHITE);
					}

					if ( sItemCustom.tDISGUISE != 0 )
					{
						CTime currentTime = GLGaeaClient::GetInstance().GetCurrentTime();
						CTime startTime   = sItemCustom.tBORNTIME;
						CTimeSpan timeSpan = currentTime - startTime;
						if( timeSpan.GetTotalSeconds() < sItemCustom.tDISGUISE )
						{
							strText.Format("[%s]", ID2GAMEWORD ("ITEM_PET_USE_SKINPACK",0) );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::GOLD);
							strText.Format("%s : %dsec", ID2GAMEWORD ("CLUB_BATTLE_TIME",0), sItemCustom.tDISGUISE - timeSpan.GetTotalSeconds() );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::GOLD);
						}
					}

					AddTextNoSplit( ID2GAMEWORD ("ITEM_PET_SKILLS", 0 ), NS_UITEXTCOLOR::WHITE );

					PETSKILL_MAP_CITER pos = sPetCardInfo.m_ExpSkills.begin();
					PETSKILL_MAP_CITER pos_end = sPetCardInfo.m_ExpSkills.end();
					for ( ;pos != pos_end; ++pos )
					{
						const PETSKILL& sPetSkill = (*pos).second;
						PGLSKILL pSKILL = GLSkillMan::GetInstance().GetData( sPetSkill.sNativeID );
						if ( pSKILL )
						{
							strText.Format("%s", pSKILL->GetName() );
							AddTextNoSplit(strText,NS_UITEXTCOLOR::WHITE);
						}
					}
				}
				break;
			}
			
			if( emItemType != ITEM_PET_SKILL )
			{
				//AddTextNoSplit( ID2GAMEWORD( "ITEM_CATEGORY", 8 ), NS_UITEXTCOLOR::YELLOW );

				// Note : 시귀/직귀 카드에 맵이름 좌표 출력
				if( pItemData->sDrugOp.emDrug == ITEM_DRUG_CALL_REGEN )
				{
					GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();	

					CString strName( GLGaeaClient::GetInstance().GetMapName( pCharacter->m_sStartMapID ) );
					if( strName == _T("(null)") ) strName.Empty();

					strText.Format( "%s:%s", ID2GAMEWORD("ITEM_CALL_MAP", 0 ), strName );
					AddTextNoSplit( strText, NS_UITEXTCOLOR::WHITE);

					SMAPNODE *pMapNode = GLGaeaClient::GetInstance().FindMapNode ( pCharacter->m_sStartMapID );
					if( pMapNode )
					{
						GLLevelFile cLevelFile;
						BOOL bOk = cLevelFile.LoadFile( pMapNode->strFile.c_str(), TRUE, NULL );
						if( bOk )
						{	
							D3DXVECTOR3 vStartPos;
							PDXLANDGATE pGate = cLevelFile.GetLandGateMan().FindLandGate( pCharacter->m_dwStartGate );
							if( pGate )
							{
								vStartPos = pGate->GetGenPos ( DxLandGate::GEN_RENDUM );
							}
							else
							{
								pGate = cLevelFile.GetLandGateMan().FindLandGate( DWORD(0) );
								if( pGate ) vStartPos = pGate->GetGenPos ( DxLandGate::GEN_RENDUM );
							}

							int nPosX(0), nPosY(0);
							cLevelFile.GetMapAxisInfo().Convert2MapPos( vStartPos.x, vStartPos.z, nPosX, nPosY );

							strText.Format( "%s:%d,%d", ID2GAMEWORD("ITEM_CALL_MAP", 1 ), nPosX, nPosY );
							AddTextNoSplit( strText, NS_UITEXTCOLOR::WHITE);
						}
					}
				}
				else if( pItemData->sDrugOp.emDrug == ITEM_DRUG_CALL_LASTCALL )
				{
					GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();

					if( pCharacter->m_sLastCallMapID.IsValidNativeID() )
					{
						CString strName( GLGaeaClient::GetInstance().GetMapName( pCharacter->m_sLastCallMapID ) );
						if( strName == _T("(null)") ) strName.Empty();

						strText.Format( "%s:%s", ID2GAMEWORD("ITEM_CALL_MAP", 0 ), strName );
						AddTextNoSplit( strText, NS_UITEXTCOLOR::WHITE);

						SMAPNODE *pMapNode = GLGaeaClient::GetInstance().FindMapNode ( pCharacter->m_sLastCallMapID );
						if( pMapNode )
						{
							GLLevelFile cLevelFile;
							BOOL bOk = cLevelFile.LoadFile( pMapNode->strFile.c_str(), TRUE, NULL );
							if( bOk )
							{	
								int nPosX(0), nPosY(0);
								cLevelFile.GetMapAxisInfo().Convert2MapPos( pCharacter->m_vLastCallPos.x, pCharacter->m_vLastCallPos.z, nPosX, nPosY );

								strText.Format( "%s:%d,%d", ID2GAMEWORD("ITEM_CALL_MAP", 1 ), nPosX, nPosY );
								AddTextNoSplit( strText, NS_UITEXTCOLOR::WHITE);
							}
						}
					}
					else
					{
						AddTextNoSplit( ID2GAMEWORD("ITEM_CALL_MAP", 2 ), NS_UITEXTCOLOR::RED);
					}
				}
				else if ( pItemData->sDrugOp.emDrug == ITEM_DRUG_CALL_TELEPORT )
				{
					CString strName( GLGaeaClient::GetInstance().GetMapName( pItemData->sBasicOp.sSubID ) );
					if( strName == _T("(null)") ) strName.Empty();

					strText.Format( "%s:%s", ID2GAMEWORD("ITEM_TELEPORT_MAP", 0 ), strName );
					AddTextNoSplit( strText, NS_UITEXTCOLOR::WHITE);

					strText.Format( "%s:%d,%d", ID2GAMEWORD("ITEM_TELEPORT_MAP", 1 ), pItemData->sBasicOp.wPosX, pItemData->sBasicOp.wPosY );
					AddTextNoSplit( strText, NS_UITEXTCOLOR::WHITE);
				}

			}

			{ // 설명
				const TCHAR * pszComment(NULL);

				if ( (emItemType != ITEM_SKILL) || (emItemType != ITEM_PET_SKILL) )
				{
					pszComment = pItemData->GetComment();
				}
				else
				{
					SNATIVEID sNativeID = sItemCustom.sNativeID;
					SITEM* pItemData = GLItemMan::GetInstance().GetItem ( sNativeID );
					SITEM* pItemDataDisguise = GLItemMan::GetInstance().GetItem ( sItemCustom.nidDISGUISE );
					SNATIVEID sSkillID = pItemData->sSkillBookOp.sSkill_ID;

					//	Note : 스킬 정보 가져옴.
					PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( sSkillID.wMainID, sSkillID.wSubID );
					if ( pSkill )
					{
						pszComment = pSkill->GetDesc();
					}
				}

				AddTextNoSplit( " ", NS_UITEXTCOLOR::WHITE);

				{
				BOOL bAccept(FALSE);
				//BOOL bArmor = ( pItemData->sSuitOp.emSuit==SUIT_HANDHELD || pItemData->sBasicOp.emItemType==ITEM_SUIT);
				if( sItemCustom.nidDISGUISE != NATIVEID_NULL() )
				{
					bAccept = pCharacter->ACCEPT_ITEM( sItemCustom.sNativeID, sItemCustom.nidDISGUISE );
				}
				else
				{
					bAccept = pCharacter->ACCEPT_ITEM( sItemCustom.sNativeID );
				}


				if ( bAccept )
				{
					strText.Format ( "(%s)", ID2GAMEWORD("ITEM_USABLE", 0 ) );
					AddTextNoSplit(strText, NS_UITEXTCOLOR::WHITE );

					DWORD dwNeedSP = pCharacter->CALC_ACCEPTP ( sItemCustom.sNativeID );
					if ( 0 < dwNeedSP )
					{
						strText.Format ( "%s:%d", ID2GAMEWORD("ITEM_NEEDSP" ), dwNeedSP );
						AddTextNoSplit(strText, NS_UITEXTCOLOR::PALEGREEN );
					}
				}
				else
				{
					strText.Format ( "(%s)", ID2GAMEWORD("ITEM_USABLE", 1 ) );
					AddTextNoSplit(strText, NS_UITEXTCOLOR::RED );
				}

			
				bool bCanPreview = CInnerInterface::GetInstance().PreviewCheckSimple( pItemData->sBasicOp.sNativeID );
				if ( bCanPreview )
				{
					AddTextNoSplit( " ", NS_UITEXTCOLOR::BLACK);
					AddTextLongestLineSplit ( "Pressing Alt key + left click the mouse button to preview the item", NS_UITEXTCOLOR::WHITE );
				}

				}

				if( pszComment )
				{
					int StrLength = static_cast<int>( strlen( pszComment ) );
					if( StrLength )
					{
						//AddTextNoSplit ( ID2GAMEWORD( "ITEM_CATEGORY", 9 ), NS_UITEXTCOLOR::LIGHTSKYBLUE );
						AddTextLongestLineSplit( pszComment, NS_UITEXTCOLOR::LIGHTYELLOW );
					}
				}
			}

			{

				DWORD dwFlags = pItemData->sBasicOp.dwFlags;
				CString szFlag;
				SITEMCUSTOM sCUSTOM = sItemCustom;
					
				if( dwFlags )
				{			
					AddTextNoSplit( " ", NS_UITEXTCOLOR::WHITE);
					
					if ( dwFlags & TRADE_SALE )
					{
						AddTextNoSplit ( "Shop Trade Possible", NS_UITEXTCOLOR::WHITE);
					}
					else
					{
						AddTextNoSplit ( "Shop Trade Impossible", NS_UITEXTCOLOR::DARKGRAY);
					}
					if ( dwFlags & TRADE_EXCHANGE)
					{
						AddTextNoSplit ( "User Trade Possible", NS_UITEXTCOLOR::WHITE);
					}
					else
					{
						AddTextNoSplit ( "User Trade Impossible", NS_UITEXTCOLOR::DARKGRAY);
					}
					if ( dwFlags & TRADE_THROW && !sCUSTOM.IsNonDrop())
					{
						AddTextNoSplit ( "Ground Discard Possible", NS_UITEXTCOLOR::WHITE);
					}
					else
					{
						AddTextNoSplit ( "Ground Discard Impossible", NS_UITEXTCOLOR::DARKGRAY);
					}
					/*if ( dwFlags & TRADE_EVENT_SGL)
					{
						AddTextNoSplit ( "Event Item", NS_UITEXTCOLOR::WHITE);
					}*/
					//if ( dwFlags & TRADE_GARBAGE)
					//{
					//	AddTextNoSplit ( "Garbage Item", NS_UITEXTCOLOR::WHITE);
					//}
					if ( dwFlags & ITEM_DISGUISE)
					{
						AddTextNoSplit ( "Costume Combine", NS_UITEXTCOLOR::WHITE);
					}
					//if ( dwFlags & ITEM_OWNERSHIP)
					//{
					//	AddTextNoSplit ( "Item Owned", NS_UITEXTCOLOR::WHITE);
					//}
					strText.Format( "%s", szFlag.GetString() );
					//AddTextNoSplit ( strText, NS_UITEXTCOLOR::DEFAULT );
					}
			
			}
			
		{
			const int nELEC   = sItemCustom.GETRESIST_ELEC();
			const int nFIRE   = sItemCustom.GETRESIST_FIRE();
			const int nICE    = sItemCustom.GETRESIST_ICE();
			const int nPOISON = sItemCustom.GETRESIST_POISON();
			const int nSPIRIT = sItemCustom.GETRESIST_SPIRIT();
					
			if ( (nELEC) && (nFIRE) && (nICE) && (nPOISON) && (nSPIRIT) )
			{
				SetResiIcons();
			}
			else
			{
				ResetResiIcons();
			}
		}

		{
				bool bBox = pItemData->sBasicOp.emItemType ==ITEM_BOX || pItemData->sBasicOp.emItemType==ITEM_RANDOMITEM;
					if ( bBox )
					{
						//AddTextNoSplit ( "Shift + L-Click to show item's inside.", NS_UITEXTCOLOR::WHITE );
					}
			}
			
			if ( sNpcNativeID != sItemCustom.sNativeID ) 
			{
				sNpcNativeID = sItemCustom.sNativeID;
		
				if ( sNpcNativeID.IsValidNativeID() )
				{
					SITEM* pItem = GLItemMan::GetInstance().GetItem ( sNpcNativeID );
					if ( !pItem )
					{
						GASSERT ( 0 && " " );
						return ;
						SITEMCUSTOM sCUSTOM = sItemCustom;
						ResetItemRender (sCUSTOM);
						ResetItemBoxRender ();
						ResetItemBoxRandomRender();
					}	

					if ( pItem->sBasicOp.emItemType == ITEM_BOX  )
					{
						SITEMCUSTOM sCUSTOM = sItemCustom;
						ResetItemRender (sCUSTOM);	
						ResetItemBoxRender ();
						ResetItemBoxRandomRender();

						for ( int i=0; i<ITEM::SBOX::ITEM_SIZE; ++i )
						{
							SITEMCUSTOM sCUSTOM;
							sCUSTOM.sNativeID = pItem->sBox.sITEMS[i].nidITEM;

							if ( sCUSTOM.sNativeID==SNATIVEID(false) )				continue;

							CInnerInterface::GetInstance().sBOXINFOCUSTOM[i] = sCUSTOM;
							SITEM* pItemData = GLItemMan::GetInstance().GetItem ( sCUSTOM.sNativeID );
							if ( pItemData ) 
							{
								AddItemBoxRender ( pItemData->sBasicOp.sICONID, pItemData->GetInventoryFile(), i );
							}
						}
					
						//SITEMCUSTOM sCUSTOM = sItemCustom;
						AddItemRender ( pItem->sBasicOp.sICONID, pItem->GetInventoryFile(),  sCUSTOM );
						//AddTextNoSplit ( "Shift + Right-Click to Show Item's information inside.", NS_UITEXTCOLOR::WHITE );
						//AddTextNoSplit ( "Alt + Right-Click to Show Item Preview in your character. Items aren't Random.", NS_UITEXTCOLOR::WHITE );
					}
					else if ( pItem->sBasicOp.emItemType == ITEM_RANDOMITEM )
					{
						SITEMCUSTOM sCUSTOM = sItemCustom;
						ResetItemRender (sCUSTOM);	
						ResetItemBoxRender ();
						ResetItemBoxRandomRender();

						for ( DWORD i=0; i<pItem->sRandomBox.vecBOX.size(); ++i )
						{
							SITEMCUSTOM sCUSTOM;
							ITEM::SRANDOMITEM sITEMBOX = pItem->sRandomBox.vecBOX[i];
							sCUSTOM.sNativeID = sITEMBOX.nidITEM;

							if ( sCUSTOM.sNativeID==SNATIVEID(false) )				continue;

							CInnerInterface::GetInstance().sRANDOMBOXINFOCUSTOM[i] = sCUSTOM;
							SITEM* pItemData = GLItemMan::GetInstance().GetItem ( sCUSTOM.sNativeID );
							if ( pItemData ) 
							{
								AddItemBoxRandomRender ( pItemData->sBasicOp.sICONID, pItemData->GetInventoryFile(), i );
							}
						}
						
//						SITEMCUSTOM sCUSTOM = sItemCustom;
						AddItemRender ( pItem->sBasicOp.sICONID, pItem->GetInventoryFile(),  sCUSTOM );
						//AddTextNoSplit ( "Shift + Right-Click to Show Item's information inside.", NS_UITEXTCOLOR::WHITE );
						//AddTextNoSplit ( "Alt + Right-Click to Show Item Preview in your character. Items here are Randomized.", NS_UITEXTCOLOR::WHITE );
					}
					else
					{
						SITEMCUSTOM sCUSTOM = sItemCustom;
						ResetItemRender (sCUSTOM);	
						ResetItemBoxRender ();
						ResetItemBoxRandomRender();
//						SITEMCUSTOM sCUSTOM = sItemCustom;
						AddItemRender ( pItem->sBasicOp.sICONID, pItem->GetInventoryFile(),  sCUSTOM );
					}
				}
			}
		}
	}
};
