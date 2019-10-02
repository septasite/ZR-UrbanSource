#include "StdAfx.h"
#include "./CharacterWindow.h"

#include "../G-Logic/GLGaeaClient.h"

#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "InventoryPageWear.h"
#include "InventoryPageWearEx.h"

#include "../Interface/ModalCallerID.h"
#include "../Interface/ModalWindow.h"
#include "../Interface/InnerInterface.h"
#include "../Interface/UITextControl.h"
#include "../Interface/GameTextControl.h"
#include "BasicComboBox.h"
#include "BasicComboBoxRollOver.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CCharacterWindow::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIWindowEx::TranslateUIMessage ( ControlID, dwMsg );

	const GLCHARLOGIC& sCharData = GLGaeaClient::GetInstance().GetCharacterLogic ();

	const float fBUTTON_CLICK = CBasicButton::fBUTTON_CLICK;
	//Added by NjD
	if ( m_pNewPow == 0 )
	{
		m_pButtonMinus[0]->SetVisibleSingle ( FALSE );
		m_pButtonPlus[0]->SetVisibleSingle ( FALSE );
		m_pButtonOk->SetVisibleSingle ( FALSE );
		m_pButtonCancel->SetVisibleSingle ( FALSE );
		//m_pButtonOk_F->SetVisibleSingle ( TRUE );
		//m_pButtonCancel_F->SetVisibleSingle ( TRUE );

	}
	if ( m_pNewDex == 0 )
	{
		m_pButtonMinus[1]->SetVisibleSingle ( FALSE );
		m_pButtonPlus[1]->SetVisibleSingle ( FALSE );
		m_pButtonOk->SetVisibleSingle ( FALSE );
		m_pButtonCancel->SetVisibleSingle ( FALSE );
		//m_pButtonOk_F->SetVisibleSingle ( TRUE );
		//m_pButtonCancel_F->SetVisibleSingle ( TRUE );
	}
	if ( m_pNewSpi == 0 )
	{
		m_pButtonMinus[2]->SetVisibleSingle ( FALSE );
		m_pButtonPlus[2]->SetVisibleSingle ( FALSE );
		m_pButtonOk->SetVisibleSingle ( FALSE );
		m_pButtonCancel->SetVisibleSingle ( FALSE );
		//m_pButtonOk_F->SetVisibleSingle ( TRUE );
		//m_pButtonCancel_F->SetVisibleSingle ( TRUE );
	}
	if ( m_pNewStr == 0 )
	{
		m_pButtonMinus[3]->SetVisibleSingle ( FALSE );
		m_pButtonPlus[3]->SetVisibleSingle ( FALSE );
		m_pButtonOk->SetVisibleSingle ( FALSE );
		m_pButtonCancel->SetVisibleSingle ( FALSE );
		//m_pButtonOk_F->SetVisibleSingle ( TRUE );
		//m_pButtonCancel_F->SetVisibleSingle ( TRUE );
	}
	if ( m_pNewSta == 0 )
	{
		m_pButtonMinus[4]->SetVisibleSingle ( FALSE );
		m_pButtonPlus[4]->SetVisibleSingle ( FALSE );
		m_pButtonOk->SetVisibleSingle ( FALSE );
		m_pButtonCancel->SetVisibleSingle ( FALSE );
		//m_pButtonOk_F->SetVisibleSingle ( TRUE );
		//m_pButtonCancel_F->SetVisibleSingle ( TRUE );
	}

	if ( sCharData.m_wStatsPoint > 0 )
	{		
		
		//m_pButtonOk_F->SetVisibleSingle ( FALSE );
		//m_pButtonCancel_F->SetVisibleSingle ( FALSE);
		for ( int i = 0; i < 5; i++ )
		{
			m_pButtonPlus[i]->SetVisibleSingle ( TRUE );
		}
	}
	if ( m_pNewPow > 0 )
	{
			m_pButtonOk->SetVisibleSingle ( TRUE );
			m_pButtonCancel->SetVisibleSingle ( TRUE );
	}
	if ( m_pNewDex > 0 )
	{
			m_pButtonOk->SetVisibleSingle ( TRUE );
			m_pButtonCancel->SetVisibleSingle ( TRUE );
	}
	if ( m_pNewSpi > 0 )
	{
			m_pButtonOk->SetVisibleSingle ( TRUE );
			m_pButtonCancel->SetVisibleSingle ( TRUE );
	}
	if ( m_pNewStr > 0 )
	{
			m_pButtonOk->SetVisibleSingle ( TRUE );
			m_pButtonCancel->SetVisibleSingle ( TRUE );
	}
	if ( m_pNewSta > 0 )
	{
			m_pButtonOk->SetVisibleSingle ( TRUE );
			m_pButtonCancel->SetVisibleSingle ( TRUE );
	}

	switch ( ControlID )
	{
	case ET_CONTROL_TITLE:
	case ET_CONTROL_TITLE_F:
		{
			if ( (dwMsg & UIMSG_LB_DUP) && CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SetDefaultPosInterface( CHARACTER_WINDOW );
			}
		}
		break;
	case CHARACTER_WINDOW_STAT_POW_PLUS_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				m_pPowText->SetUseTextColor ( 0, TRUE );
				m_pPowText->SetTextColor ( 0, NS_UITEXTCOLOR::GOLD );

				m_pPowTextStatic->SetUseTextColor ( 0, TRUE );
				m_pPowTextStatic->SetTextColor ( 0, NS_UITEXTCOLOR::GOLD );

				if ( CHECK_LB_DOWN_LIKE ( dwMsg ) )
				{				
				}

				if ( CHECK_LB_UP_LIKE ( dwMsg ) )
				{					
					if ( sCharData.m_wStatsPoint > 0 ) //Added by NjD
					{	
						m_pButtonMinus[0]->SetVisibleSingle	( TRUE );
						m_pButtonOk->SetVisibleSingle ( TRUE );
						m_pButtonCancel->SetVisibleSingle ( TRUE );
						
						m_pNewPow++;
						GLGaeaClient::GetInstance().GetCharacter()->SetStatusPointDown();
						//m_pNewPoint--;
					}
				}
			}
		}
		break;
	case CHARACTER_WINDOW_STAT_DEX_PLUS_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				m_pDexText->SetUseTextColor ( 0, TRUE );
				m_pDexText->SetTextColor ( 0, NS_UITEXTCOLOR::GOLD  );

				m_pDexTextStatic->SetUseTextColor ( 0, TRUE );
				m_pDexTextStatic->SetTextColor ( 0, NS_UITEXTCOLOR::GOLD  );

				if ( CHECK_LB_DOWN_LIKE ( dwMsg ) )
				{			
				}

				if ( CHECK_LB_UP_LIKE ( dwMsg ) )
				{					
					if ( sCharData.m_wStatsPoint > 0)
					{
						m_pButtonMinus[1]->SetVisibleSingle	( TRUE ); //Added by NjD
						m_pButtonOk->SetVisibleSingle ( TRUE );
						m_pButtonCancel->SetVisibleSingle ( TRUE );

						m_pNewDex++;
						GLGaeaClient::GetInstance().GetCharacter()->SetStatusPointDown();
					}
					if ( m_pNewSta > 0 )
					{
					m_pButtonMinus[1]->SetVisibleSingle	( TRUE );
					m_pButtonOk->SetVisibleSingle ( TRUE );
					}
				}
			}
		}
		break;
	case CHARACTER_WINDOW_STAT_SPI_PLUS_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				m_pSpiText->SetUseTextColor ( 0, TRUE );
				m_pSpiText->SetTextColor ( 0, NS_UITEXTCOLOR::GOLD  );

				m_pSpiTextStatic->SetUseTextColor ( 0, TRUE );
				m_pSpiTextStatic->SetTextColor ( 0, NS_UITEXTCOLOR::GOLD  );

				if ( CHECK_LB_DOWN_LIKE ( dwMsg ) )
				{	
				}

				if ( CHECK_LB_UP_LIKE ( dwMsg ) )
				{					
					if ( sCharData.m_wStatsPoint > 0)
					{
						m_pButtonMinus[2]->SetVisibleSingle	( TRUE ); //Added by NjD
						m_pButtonOk->SetVisibleSingle ( TRUE );
						m_pButtonCancel->SetVisibleSingle ( TRUE );

						m_pNewSpi++;
						GLGaeaClient::GetInstance().GetCharacter()->SetStatusPointDown();
						//m_pNewPoint--;
					}
				}
			}
		}
		break;
	case CHARACTER_WINDOW_STAT_STR_PLUS_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				m_pStrText->SetUseTextColor ( 0, TRUE );
				m_pStrText->SetTextColor ( 0, NS_UITEXTCOLOR::GOLD  );

				m_pStrTextStatic->SetUseTextColor ( 0, TRUE );
				m_pStrTextStatic->SetTextColor ( 0, NS_UITEXTCOLOR::GOLD  );

				if ( CHECK_LB_DOWN_LIKE ( dwMsg ) )
				{
				}

				if ( CHECK_LB_UP_LIKE ( dwMsg ) )
				{					
					if ( sCharData.m_wStatsPoint > 0 )
					{
						m_pButtonMinus[3]->SetVisibleSingle	( TRUE ); //Added by NjD
						m_pButtonOk->SetVisibleSingle ( TRUE );
						m_pButtonCancel->SetVisibleSingle ( TRUE );

						m_pNewStr++;
						GLGaeaClient::GetInstance().GetCharacter()->SetStatusPointDown();
						//m_pNewPoint--;
					}
				}
			}
		}
		break;
	case CHARACTER_WINDOW_STAT_STA_PLUS_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				m_pStaText->SetUseTextColor ( 0, TRUE );
				m_pStaText->SetTextColor ( 0, NS_UITEXTCOLOR::GOLD  );

				m_pStaTextStatic->SetUseTextColor ( 0, TRUE );
				m_pStaTextStatic->SetTextColor ( 0, NS_UITEXTCOLOR::GOLD  );

				if ( CHECK_LB_DOWN_LIKE ( dwMsg ) )
				{
				}

				if ( CHECK_LB_UP_LIKE ( dwMsg ) )
				{					
					//GLGaeaClient::GetInstance().GetCharacter()->ReqStatsUp ( EMSTA );
					if ( sCharData.m_wStatsPoint > 0)
					{
						m_pButtonMinus[4]->SetVisibleSingle	( TRUE ); //Added by NjD
						m_pButtonOk->SetVisibleSingle ( TRUE );
						m_pButtonCancel->SetVisibleSingle ( TRUE );

						m_pNewSta++;
						GLGaeaClient::GetInstance().GetCharacter()->SetStatusPointDown();
						//m_pNewPoint--;
					}
				}
			}
		}
		break;
	case CHARACTER_WINDOW_STAT_POW_MINUS_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				m_pPowText2->SetUseTextColor ( 0, TRUE );
				m_pPowText2->SetTextColor ( 0, NS_UITEXTCOLOR::GOLD );

				m_pPowTextStatic->SetUseTextColor ( 0, TRUE );
				m_pPowTextStatic->SetTextColor ( 0, NS_UITEXTCOLOR::GOLD  );

				if ( CHECK_LB_DOWN_LIKE ( dwMsg ) )
				{
				}

				if ( CHECK_LB_UP_LIKE ( dwMsg ) )
				{			
					if ( m_pNewPow < 1 )
					{
						m_pButtonMinus[0]->SetVisibleSingle( TRUE ); //Added by NjD
					}
					if ( m_pNewPow > 0)
					{
						m_pNewPow--;
						GLGaeaClient::GetInstance().GetCharacter()->SetStatusPointUp();
						//m_pNewPoint++;
					}
				}
			}
		}
		break;
	case CHARACTER_WINDOW_STAT_DEX_MINUS_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				m_pDexText2->SetUseTextColor ( 0, TRUE );
				m_pDexText2->SetTextColor ( 0, NS_UITEXTCOLOR::GOLD  );

				m_pDexTextStatic->SetUseTextColor ( 0, TRUE );
				m_pDexTextStatic->SetTextColor ( 0, NS_UITEXTCOLOR::GOLD  );

				if ( CHECK_LB_DOWN_LIKE ( dwMsg ) )
				{
				}

				if ( CHECK_LB_UP_LIKE ( dwMsg ) )
				{	
					if ( m_pNewDex < 1 )
					{
						m_pButtonMinus[1]->SetVisibleSingle( TRUE ); //Added by NjD
					}

					if ( m_pNewDex > 0)
					{
						m_pNewDex--;
						GLGaeaClient::GetInstance().GetCharacter()->SetStatusPointUp();
						//m_pNewPoint++;
					}
				}
			}
		}
		break;
	case CHARACTER_WINDOW_STAT_SPI_MINUS_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				m_pSpiText2->SetUseTextColor ( 0, TRUE );
				m_pSpiText2->SetTextColor ( 0, NS_UITEXTCOLOR::GOLD  );

				m_pSpiTextStatic->SetUseTextColor ( 0, TRUE );
				m_pSpiTextStatic->SetTextColor ( 0, NS_UITEXTCOLOR::GOLD  );

				if ( CHECK_LB_DOWN_LIKE ( dwMsg ) )
				{
				}

				if ( CHECK_LB_UP_LIKE ( dwMsg ) )
				{			
					if ( m_pNewSpi < 1 )
					{
						m_pButtonMinus[2]->SetVisibleSingle( TRUE ); //Added by NjD
					} 
					if ( m_pNewSpi > 0)
					{
						m_pNewSpi--;
						GLGaeaClient::GetInstance().GetCharacter()->SetStatusPointUp();
						//m_pNewPoint++;
					}
				}
			}
		}
		break;
	case CHARACTER_WINDOW_STAT_STR_MINUS_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				m_pStrText2->SetUseTextColor ( 0, TRUE );
				m_pStrText2->SetTextColor ( 0, NS_UITEXTCOLOR::GOLD  );

				m_pStrTextStatic->SetUseTextColor ( 0, TRUE );
				m_pStrTextStatic->SetTextColor ( 0, NS_UITEXTCOLOR::GOLD  );

				if ( CHECK_LB_DOWN_LIKE ( dwMsg ) )
				{		
					if ( m_pNewStr < 1 )
					{
						m_pButtonMinus[3]->SetVisibleSingle( TRUE ); //Added by NjD
					}
					if ( m_pNewStr > 0)
					{
						m_pNewStr--;
						GLGaeaClient::GetInstance().GetCharacter()->SetStatusPointUp();
						//m_pNewPoint++;
					}
				}
			}
		}
		break;
	case CHARACTER_WINDOW_STAT_STA_MINUS_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				m_pStaText2->SetUseTextColor ( 0, TRUE );
				m_pStaText2->SetTextColor ( 0, NS_UITEXTCOLOR::GOLD  );

				m_pStaTextStatic->SetUseTextColor ( 0, TRUE );
				m_pStaTextStatic->SetTextColor ( 0, NS_UITEXTCOLOR::GOLD  );

				if ( CHECK_LB_DOWN_LIKE ( dwMsg ) )
				{
				}

				if ( CHECK_LB_UP_LIKE ( dwMsg ) )
				{			
					if ( m_pNewSta < 1 )
					{
						m_pButtonMinus[4]->SetVisibleSingle( TRUE ); //Added by NjD
					}
					if ( m_pNewSta > 0)
					{
						m_pNewSta--;
						GLGaeaClient::GetInstance().GetCharacter()->SetStatusPointUp();
						//m_pNewPoint++;
					}
				}
			}
		}
		break;
	case CHARACTER_WINDOW_STAT_OK:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				//Added by NjD
				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( "Click here to apply stats changes.", NS_UITEXTCOLOR::DEFAULT );	
				if ( CHECK_LB_DOWN_LIKE ( dwMsg ) )
				{
				}

				if ( CHECK_LB_UP_LIKE ( dwMsg ) )
				{	
					int num = m_pNewPow + m_pNewDex + m_pNewSpi + m_pNewStr + m_pNewSta;
					for (int i = 0; i < num; i++)
					{
						GLGaeaClient::GetInstance().GetCharacter()->SetStatusPointUp();
					}
					if ( m_pNewPow > 0)
					{
						//sCharData.m_sSUMSTATS.wPow += m_pNewPow;
						for ( int i = 0; i < m_pNewPow; i++)
						{
							//GLGaeaClient::GetInstance().GetCharacter()->ReqStatsUp ( EMPOW );
							//m_pNewPoint--;
						}
					}
					if ( m_pNewDex > 0)
					{
						//sCharData.m_sSUMSTATS.wDex += m_pNewDex;
						for ( int i = 0; i < m_pNewDex; i++)
						{
							//GLGaeaClient::GetInstance().GetCharacter()->ReqStatsUp ( EMDEX );
							//m_pNewPoint--;
						}
					}
					if ( m_pNewSpi > 0)
					{
						//sCharData.m_sSUMSTATS.wSpi += m_pNewSpi;
						for ( int i = 0; i < m_pNewSpi; i++)
						{
							//GLGaeaClient::GetInstance().GetCharacter()->ReqStatsUp ( EMSPI );
							//m_pNewPoint--;
						}
					}
					if ( m_pNewStr > 0)
					{
						//sCharData.m_sSUMSTATS.wStr += m_pNewStr;
						for ( int i = 0; i < m_pNewStr; i++)
						{
							//GLGaeaClient::GetInstance().GetCharacter()->ReqStatsUp ( EMSTR );
							//m_pNewPoint--;
						}
					}
					if ( m_pNewSta > 0)
					{
						//sCharData.m_sSUMSTATS.wSta += m_pNewSta;
						for ( int i = 0; i < m_pNewSta; i++)
						{
							//GLGaeaClient::GetInstance().GetCharacter()->ReqStatsUp ( EMSTA );
							//m_pNewPoint--;
						}
					}
					m_pNewPow = 0;
					m_pNewDex = 0;
					m_pNewSpi = 0;
					m_pNewStr = 0;
					m_pNewSta = 0;
					
				}
			}
		}

		break;
	case CHARACTER_WINDOW_STAT_CANCEL:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( CHECK_LB_UP_LIKE ( dwMsg ) )
				{					
					int num = m_pNewPow + m_pNewDex + m_pNewSpi + m_pNewStr + m_pNewSta;
					for (int i = 0; i < num; i++)
					{
						GLGaeaClient::GetInstance().GetCharacter()->SetStatusPointUp();
					}
					m_pNewPow = 0;
					m_pNewDex = 0;
					m_pNewSpi = 0;
					m_pNewStr = 0;
					m_pNewSta = 0;
				}
			}
		}
		break;

	case CHARACTER_PREMIUM_TEXT:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				bool bPREMIUM = GLGaeaClient::GetInstance().GetCharacter()->m_bPREMIUM;
				if ( bPREMIUM )
				{
					if ( CInnerInterface::GetInstance().BEGIN_COMMON_LINEINFO_MULTI () )
					{
						CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI ( ID2GAMEWORD("CHARACTER_PREMIUM_EXPIRE_DATE_STATIC"), NS_UITEXTCOLOR::DARKORANGE );

						__time64_t tPREMIUM = GLGaeaClient::GetInstance().GetCharacter()->m_tPREMIUM;
						CTime cTime ( tPREMIUM );
						CString strExpireDate = CInnerInterface::GetInstance().MakeString ( ID2GAMEWORD("CHARACTER_PREMIUM_EXPIRE_DATE"),
							cTime.GetYear(), cTime.GetMonth(), cTime.GetDay (), cTime.GetHour (), cTime.GetMinute () );

						CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI ( strExpireDate, NS_UITEXTCOLOR::WHITE );

						CInnerInterface::GetInstance().END_COMMON_LINEINFO_MULTI ();
					}					
				}
			}
		}
		break;

	case CHARACTER_BIRGHTER:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter ();

				CString strTemp;				
				strTemp.Format ( "%d", pCharacter->m_nBright );

				CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO ( strTemp, NS_UITEXTCOLOR::WHITE );
			}
		}
		break;
	case CHARACTER_MOBILE_BUTTON:
		{
			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				DoModal( ID2GAMEINTEXT( "MODAL_MOBILE_NUMBER" ), MODAL_INPUT, EDITBOX_NUMBER, MODAL_MOBILE_NUMBER );
			}
		}
		break;
	case INVENTORY_PAGEWEAR:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nIndex = m_pPageWear->GetItemIndex ();
				if ( nIndex < 0 ) return ;				

				//if ( CUIMan::GetFocusControl () == this )
				{
					SITEMCUSTOM sItemCustom = m_pPageWear->GetItem ( nIndex );
					if ( sItemCustom.sNativeID != NATIVEID_NULL () )
					{
						CInnerInterface::GetInstance().SHOW_ITEM_INFO ( sItemCustom, FALSE, FALSE, FALSE, USHRT_MAX, USHRT_MAX );
					}
				}

				if ( dwMsg & UIMSG_LB_UP )
				{
					EMSLOT emSlot = m_pPageWear->GetItemSlot ();
					GLGaeaClient::GetInstance().GetCharacter()->ReqSlotTo ( emSlot );
				}
			}
		}
		break;
	case INVENTORY_PAGEWEAR_EX:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				int nIndex = m_pPageWearEx->GetItemIndex ();
				if ( nIndex < 0 ) return ;				

				//if ( CUIMan::GetFocusControl () == this )
				{
					SITEMCUSTOM sItemCustom = m_pPageWearEx->GetItem ( nIndex );
					if ( sItemCustom.sNativeID != NATIVEID_NULL () )
					{
						CInnerInterface::GetInstance().SHOW_ITEM_INFO ( sItemCustom, FALSE, FALSE, FALSE, USHRT_MAX, USHRT_MAX );
					}
				}

				if ( dwMsg & UIMSG_LB_UP )
				{
					EMSLOT emSlot = m_pPageWearEx->GetItemSlot ();
					GLGaeaClient::GetInstance().GetCharacter()->ReqSlotTo ( emSlot );
				}
			}
		}
		break;
	case NICKNAME_COMBO_OPEN:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( dwMsg & UIMSG_LB_DOWN )
				{
					m_pComboBoxNickNameRollOver->SetVisibleSingle ( TRUE );
					//m_pComboBoxNickNameRollOver->SetScrollPercent ( 0.0f );					
				}
			}
		}
		break;
	case NICKNAME_COMBO_ROLLOVER:
		{

			

			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{				
				nIndex = m_pComboBoxNickNameRollOver->GetSelectIndex ();
				if ( nIndex < 0 ) return ;
				LoadItem ();
				m_pComboBoxNickNameRollOver->SetVisibleSingle ( FALSE );
			}
		}
		break;
	}
}