#include "StdAfx.h"
#include "BasicSkillTray.h"

#include "BasicQuickSkillSlotEx.h"
#include "GLGaeaClient.h"
#include "../../EngineLib/DxCommon/DxFontMan.h"
#include "InnerInterface.h"
#include "SkillWindowToTray.h"
#include "BasicVarTextBox.h"
#include "UITextControl.h"
#include "GameTextControl.h"
#include "d3dfontx.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

const	int	CBasicSkillTray::nLBUPSKIP = 1;

CBasicSkillTray::CBasicSkillTray ()
	: m_nLBUPSKIP(0)
	, m_pSkillInfo(NULL)
{
	memset ( m_pSlotEx, 0, sizeof ( m_pSlotEx ) );
}

CBasicSkillTray::~CBasicSkillTray ()
{
}

void CBasicSkillTray::CreateSubControl( INT nTabIndex )
{
	GASSERT( ( 0 <= nTabIndex ) && ( nTabIndex < MAX_TAB_INDEX ) );

	CD3DFontPar * m_pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, _DEFAULT_FONT_FLAG );

	for ( int nNumber = 0; nNumber < QUICK_SKILL_SLOT_MAX; ++nNumber )
	{
		CString strKeyword;
		strKeyword.Format ( "BASIC_QUICK_SKILL_TRAY_SLOT%d", nNumber );

		CBasicQuickSkillSlotEx*	pSlot = new CBasicQuickSkillSlotEx;
		pSlot->CreateSub( this, strKeyword.GetString(), UI_FLAG_DEFAULT, QUICK_SKILL_SLOT1 + nNumber );
		pSlot->CreateSubControl( nTabIndex );
		pSlot->CreateNumberText( m_pFont8, nNumber );		
		RegisterControl( pSlot );
		m_pSlotEx[nNumber] = pSlot;
	}

	CUIControl* pSlotEnd = new CUIControl;
	pSlotEnd->CreateSub ( this, "BASIC_QUICK_SKILL_TRAY_SLOT_END" );
	pSlotEnd->SetControlNameEx ( "슬롯 엔드" );
    RegisterControl ( pSlotEnd );

	CBasicVarTextBox* pSkillInfo = new CBasicVarTextBox;
	pSkillInfo->CreateSub ( this, "BASIC_VAR_TEXT", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
	pSkillInfo->CreateSubControl ();
	pSkillInfo->SetVisibleSingle ( FALSE );
	RegisterControl ( pSkillInfo );
	m_pSkillInfo = pSkillInfo;
}

void CBasicSkillTray::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	switch ( ControlID )
	{
	case QUICK_SKILL_SLOT1:
	case QUICK_SKILL_SLOT2:
	case QUICK_SKILL_SLOT3:
	case QUICK_SKILL_SLOT4:
	case QUICK_SKILL_SLOT5:
	case QUICK_SKILL_SLOT6:
	case QUICK_SKILL_SLOT7:
	case QUICK_SKILL_SLOT8:
	case QUICK_SKILL_SLOT9:
	case QUICK_SKILL_SLOT0:
		{			
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{	
				int nG_Index = m_pSlotEx[0]->GetTabIndex() * QUICK_SKILL_SLOT_MAX;
				int nIndex = ControlID - QUICK_SKILL_SLOT1;
				nG_Index += nIndex;

				SNATIVEID sOverSkill = GLGaeaClient::GetInstance().GetCharacter()->GetCharData().m_sSKILLQUICK[nG_Index];
                if ( sOverSkill != NATIVEID_NULL () )
				{
					PGLSKILL pSkill = GLSkillMan::GetInstance().GetData( sOverSkill.wMainID, sOverSkill.wSubID );
					SCHARSKILL* pCharSkill = GLGaeaClient::GetInstance().GetCharacter()->GETLEARNED_SKILL ( sOverSkill );
					const SKILL::SAPPLY& sAPPLY = pSkill->m_sAPPLY;
					WORD wLevel = pCharSkill->wLevel;
					const SKILL::CDATA_LVL& sDATA_LVL = sAPPLY.sDATA_LVL[wLevel];
					if ( CInnerInterface::GetInstance().BEGIN_COMMON_LINEINFO_MULTI () )
					{
						CString strCombine;
						strCombine.Format("%s(Lv.%d)", pSkill->GetName(), wLevel);
						CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI ( strCombine.GetString(), NS_UITEXTCOLOR::PALEGREEN );

						CString strText;
						if ( 0 != sDATA_LVL.fBASIC_VAR )
						{
							if ( 0 > sDATA_LVL.fBASIC_VAR )
							{
								float fBASIC_VAR_SCALE = sDATA_LVL.fBASIC_VAR * COMMENT::SKILL_TYPES_SCALE[sAPPLY.emBASIC_TYPE];
								if ( pSkill->m_sBASIC.emIMPACT_TAR == TAR_SELF )
								{
									if ( COMMENT::IsSKILL_PER(sAPPLY.emBASIC_TYPE) )
										strText.Format("Let %s decrease %2.1f%%", COMMENT::SKILL_TYPES[sAPPLY.emBASIC_TYPE].c_str(), fBASIC_VAR_SCALE );
									else
										strText.Format("Let %s decrease %2.1f", COMMENT::SKILL_TYPES[sAPPLY.emBASIC_TYPE].c_str(), fBASIC_VAR_SCALE );

									CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI(strText, NS_UITEXTCOLOR::GREEN );
								}
								else
								{
									if ( COMMENT::IsSKILL_PER(sAPPLY.emBASIC_TYPE) )
										strText.Format("Let target's %s decrease %2.1f%%", COMMENT::SKILL_TYPES[sAPPLY.emBASIC_TYPE].c_str(), fBASIC_VAR_SCALE );
									else
										strText.Format("Let target's %s decrease %2.1f", COMMENT::SKILL_TYPES[sAPPLY.emBASIC_TYPE].c_str(), fBASIC_VAR_SCALE );

									CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI(strText, NS_UITEXTCOLOR::GREEN );
								}
							}
							else
							{
								CString strText;
								float fBASIC_VAR_SCALE = sDATA_LVL.fBASIC_VAR * COMMENT::SKILL_TYPES_SCALE[sAPPLY.emBASIC_TYPE];
								if ( pSkill->m_sBASIC.emIMPACT_TAR == TAR_SELF )
								{
									if ( COMMENT::IsSKILL_PER(sAPPLY.emBASIC_TYPE) )
										strText.Format("Let %s increase %2.1f%%", COMMENT::SKILL_TYPES[sAPPLY.emBASIC_TYPE].c_str(), fBASIC_VAR_SCALE );
									else
										strText.Format("Let %s increase %2.1f", COMMENT::SKILL_TYPES[sAPPLY.emBASIC_TYPE].c_str(), fBASIC_VAR_SCALE );
									CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI(strText, NS_UITEXTCOLOR::GREEN );
								}
								else
								{
									if ( COMMENT::IsSKILL_PER(sAPPLY.emBASIC_TYPE) )
										strText.Format("Let target's %s increase %2.1f%%", COMMENT::SKILL_TYPES[sAPPLY.emBASIC_TYPE].c_str(), fBASIC_VAR_SCALE );
									else
										strText.Format("Let target's %s increase %2.1f", COMMENT::SKILL_TYPES[sAPPLY.emBASIC_TYPE].c_str(), fBASIC_VAR_SCALE );
									CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI(strText, NS_UITEXTCOLOR::GREEN );
								}
							}
						}

						CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI("", NS_UITEXTCOLOR::GREEN); //Spacer moto
						//Skill Range
						{
							CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI("[The Range Of Skill]", NS_UITEXTCOLOR::WHITE );
							
							const SKILL::CDATA_LVL& sDATA_LVL = sAPPLY.sDATA_LVL[wLevel];
							const SKILL::SBASIC& sBASIC = pSkill->m_sBASIC;	

								
							if ((pSkill->m_sBASIC.emIMPACT_TAR == TAR_SPEC || pSkill->m_sBASIC.emIMPACT_TAR == TAR_SELF_TOSPEC) || 
								(pSkill->m_sBASIC.emIMPACT_TAR == TAR_SELF || pSkill->m_sBASIC.emIMPACT_TAR == REALM_ZONE))
							{
									CString strText1;
									strText.Format("Within %dm range from target and %dm radius in target-centered, ",sDATA_LVL.wAPPLYRANGE, sBASIC.wTARRANGE );
									CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI(strText, NS_UITEXTCOLOR::AQUABLUE );
									strText1.Format("%d enemies/friend..",sDATA_LVL.wAPPLYRANGE, sBASIC.wTARRANGE );
									CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI(strText1, NS_UITEXTCOLOR::AQUABLUE );
							}
							else if (pSkill->m_sBASIC.emIMPACT_TAR == TAR_ZONE_SPEC || pSkill->m_sBASIC.emIMPACT_TAR == TAR_ZONE)
							{
									strText.Format("The %dm within %dm and %d of attack range.",
									sDATA_LVL.wTARNUM, sDATA_LVL.wAPPLYRANGE, sBASIC.wTARRANGE );
									CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI(strText, NS_UITEXTCOLOR::AQUABLUE );
							}
							else
								strText.Format("Self / Friend");
						}

						for( unsigned s=0;s<SKILL::SAPPLY::MAX_DESCRIPTOR;++s)
								{
									const SKILL::SSPEC_DESCRIPTOR &desc = sAPPLY.spec[s];
									if( pSkill->m_sAPPLY.GetSpec( desc.emSPEC ) != &desc ) continue;
									const SKILL::SSPEC& sSPEC = desc.sSPEC[wLevel];
									if ( desc.emSPEC != EMSPECA_NULL && desc.emSPEC != EMSPECA_LINKSKILL )
									{
										CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI("", NS_UITEXTCOLOR::GREEN); //Spacer moto
										CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI("[Skill Effects]", NS_UITEXTCOLOR::GOLD);
										strText.Format ( "%s:%s", ID2GAMEWORD("SKILL_SPEC_TYPE", 0), COMMENT::SPEC_ADDON[desc.emSPEC].c_str() );
										CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI(strText, NS_UITEXTCOLOR::GREEN );
										
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
//											CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI(strText, NS_UITEXTCOLOR::GREEN );
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
													
												CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI(strText, NS_UITEXTCOLOR::GREEN );
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

												CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI(strText, NS_UITEXTCOLOR::GREEN );
											}
										}
									}		
								}

						CInnerInterface::GetInstance().END_COMMON_LINEINFO_MULTI ();
					}
				}				

				//	스냅, 스킬 이미지 붙이기
				CSkillWindowToTray* pSkillWindowToTray = CInnerInterface::GetInstance().GetSkillWindowToTray ();
				if ( !pSkillWindowToTray )
				{
					GASSERT ( 0 && "CSkillWindowToTray가 널입니다." );
					return ;
				}

				if ( pSkillWindowToTray->GetSkill () != NATIVEID_NULL () )
				{
					const UIRECT& rcSlotPos = m_pSlotEx[nIndex]->GetAbsPosSkillImage ();
					pSkillWindowToTray->SetGlobalPos ( rcSlotPos );						

					AddMessageEx ( UIMSG_MOUSEIN_SKILLSLOT );
				}		

				if ( dwMsg & UIMSG_LB_UP )
				{	
					SNATIVEID sNativeID = pSkillWindowToTray->GetSkill ();

					//	스킬 등록
					if ( sNativeID != NATIVEID_NULL () )
					{						
						GLGaeaClient::GetInstance().GetCharacter()->ReqSkillQuickSet ( sNativeID, nG_Index );
						pSkillWindowToTray->ResetSkill ();
						m_nLBUPSKIP = 0;
					}
					else
					{
						//	( 등록할 스킬이 없을 경우 ) 현제슬롯의 스킬을 사용할 스킬로 설정.
						GLGaeaClient::GetInstance().GetCharacter()->ReqSkillRunSet( nG_Index );
					}					
				}

				//	스킬 해제
				if ( dwMsg & UIMSG_RB_UP )
				{					
					GLGaeaClient::GetInstance().GetCharacter()->ReqSkillQuickReSet ( nG_Index );
				}
			}
		}
		break;
	}
}

void	CBasicSkillTray::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	m_pSkillInfo->SetVisibleSingle ( FALSE );

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	DWORD dwMsg = GetMessageEx ();
	if ( dwMsg & UIMSG_LB_UP )
	{
		CSkillWindowToTray* pSkillWindowToTray = CInnerInterface::GetInstance().GetSkillWindowToTray ();
		if ( !pSkillWindowToTray )	return ;

		//	스킬이 손에 들려져있고...
		//	첫번째 왼쪽클릭메시지는 무시한다.
		BOOL bExist = ( pSkillWindowToTray->GetSkill () != NATIVEID_NULL () );
		if ( bExist )
		{
			if ( nLBUPSKIP <= m_nLBUPSKIP )
			{
				pSkillWindowToTray->ResetSkill ();
				m_nLBUPSKIP = 0;
			}
			else
			{
				m_nLBUPSKIP++;
			}
		}		
	}
}

void CBasicSkillTray::UpdateSkillInfo ( SNATIVEID sNativeID )
{
	if ( sNativeID != NATIVEID_NULL() )
	{
		static SNATIVEID sNativeIDBack = NATIVEID_NULL();

		BOOL bUPDATE = FALSE;
		if ( sNativeID != sNativeIDBack )
		{			
			bUPDATE = TRUE;
		}

		if ( bUPDATE )
		{
			PGLSKILL pSkill = GLSkillMan::GetInstance().GetData ( sNativeID.wMainID, sNativeID.wSubID );
			if ( pSkill )	//	스킬이 존재할 경우
			{
				SCHARSKILL* pCharSkill = GLGaeaClient::GetInstance().GetCharacter()->GETLEARNED_SKILL ( sNativeID );
				LoadSkillInfo ( pSkill, pCharSkill );
			}

			sNativeIDBack = sNativeID;
		}		
	}
}

void CBasicSkillTray::LoadSkillInfo ( PGLSKILL const pSkill, SCHARSKILL* const pCharSkill )
{
	m_pSkillInfo->SetTextNoSplit( pSkill->GetName(), NS_UITEXTCOLOR::PALEGREEN );
}
void CBasicSkillTray::SetShotcutText ( DWORD nID, CString& strTemp )
{
	m_pSlotEx[nID]->SetShotcutText(strTemp);	
}
