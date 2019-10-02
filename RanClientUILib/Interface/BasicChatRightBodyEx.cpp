#include "StdAfx.h"
#include "BasicChatRightBody.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "../EngineUILib/GUInterface/UIEditBox.h"
#include "DxInputDevice.h"
#include "BasicTextBoxEx.h"
#include "BasicScrollBarEx.h"
#include "../EngineUILib/GUInterface/BasicScrollThumbFrame.h"
#include "DxGlobalStage.h"
#include "GLGaeaClient.h"
#include "UITextControl.h"
#include "dxincommand.h"
#include "InnerInterface.h"
#include "HeadChatDisplayMan.h"
#include "DxViewPort.h"
#include "SystemMessageDisplay.h"
#include "GLPartyClient.h"
#include "GameTextControl.h"
#include "DxInputString.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "RanFilter.h"
#include "GLFriendClient.h"
#include "../EngineUILib/GUInterface/UIKeyCheck.h"
#include "Emoticon.h"
#include "../EngineLib/Common/SubPath.h"
#include "shlobj.h"
#include "../enginelib/Common/StringUtils.h"
#include "InnerInterface.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

void CBasicChatRightBody::ADD_CHATLOG ( const CString& strChat, SITEMLINK sItemLink )
{
	if( strChat.IsEmpty() ) return;

	NORMAL_CHAT_LOG_ITER iter = m_ChatLog.begin ();
	NORMAL_CHAT_LOG_ITER iter_end = m_ChatLog.end ();
	for ( ; iter != iter_end; ++iter )	//	혹시 중간에 있다면...
	{
		if( (*iter).strChat == strChat )
		{
			m_ChatLog.erase( iter );
			m_ChatPos = OUT_OF_RANGE;
			break;
		}
	}

	SCHATLOG sLOG;
	sLOG.strChat = strChat.GetString();
	sLOG.sItemLink = sItemLink;

	m_ChatLog.push_front ( sLOG );

	if ( m_ChatLog.size () > 50 )
	{
		m_ChatLog.pop_back ();
	}
}

VOID CBasicChatRightBody::DecreaseTime( float fElapsedTime )			
{ 
	if( m_bPapering && ( m_fLifeTime > 0.0f ) ) 
	{
		m_fLifeTime -= fElapsedTime;
	}
}

BOOL CBasicChatRightBody::IsPapering( const CString& strOrigin )
{
	if( GetLifeTime() > 0.0f ) 
		return TRUE;
	else 
		m_bPapering = FALSE;

	//	Memo :	같은 메세지 중복 처리
	if( m_strLastMsg == strOrigin )
	{
		++m_nInputCount;

		if( m_nInputCount > nCOUNT_INPUT)
		{
			m_bPapering = TRUE;
		}
	}
	else 
	{
		m_nInputCount = 0;			// 연속되지 않을 경우 초기화
		m_strLastMsg = strOrigin;	// 이전 메세지 저장
	}

	//	Memo :	연속된 메세지 중복 처리
	static FLOAT s_fStartTime = 0.f;
	static FLOAT s_fEndTime = 0.f;
	static BOOL bStart(TRUE);

	if( bStart )
	{
		s_fStartTime = DXUtil_Timer( TIMER_GETAPPTIME );
		bStart = FALSE;
	}
	else
	{
		s_fEndTime = DXUtil_Timer( TIMER_GETAPPTIME );

		if( (s_fEndTime-s_fStartTime) <= fINTERVAL_INPUT)
		{
			// 2초안에 메세지가 들어왔다.
			++m_nTimeCount;

			if( m_nTimeCount >= nCOUNT_INPUT)
			{
				m_bPapering = TRUE;
			}
			else
			{
				s_fStartTime = s_fEndTime;
			}
		}
		else
		{
			m_nTimeCount = 0;	// 연속되지 않을 경우 초기화
			bStart = TRUE;
		}
	}

	if( m_bPapering )
	{
		AddStringToNORMAL( ID2GAMEINTEXT("CHAT_PAPERING_MODE"), GLCONST_CHAR::dwCHAT_TOALL_COLOR, NULL );
		SetLifeTime( fLIMIT_TIME );

		//	Memo :	모든 체크 변수들을 초기화 한다.
		m_nInputCount = 0;
		m_strLastMsg.Empty();
		m_nTimeCount = 0;
		bStart = TRUE;

		return TRUE;
	}

	return FALSE;
}

bool CBasicChatRightBody::SEND_COMMON_MESSAGE ( const CString& strOrigin )
{
	CNetClient*	pNetClient = DxGlobalStage::GetInstance().GetNetClient();
	GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();

	//	필터링
	//std::string strTemp = strOrigin.GetString();
	CString strTemp( strOrigin );
	if ( CRanFilter::GetInstance().ChatFilter( strTemp ) )
		strTemp = CRanFilter::GetInstance().GetProverb();
	//	메시지 전송
	CheckItemLink( strOrigin.GetString() );

	if ( pNetClient ) pNetClient->SndChatNormal ( pCharacter->m_szName, strOrigin.GetString(), &sITEMLINK );

	ADD_CHATLOG ( strTemp.GetString(), sITEMLINK );

	CString strCombine;
	strCombine.Format ( "[%s]( %s ):%s",ID2GAMEWORD("CHAT_OPTION",0), pCharacter->m_szName, strTemp.GetString () );
	AddStringToChatEx ( strCombine, CHAT_NORMAL, &sITEMLINK );

	ShowSelfMessageOnHead ( strTemp );

	return true;
}

bool CBasicChatRightBody::SEND_PRIVATE_MESSAGE( const CString& strOrigin )
{
	CNetClient*	pNetClient = DxGlobalStage::GetInstance().GetNetClient();
	GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();

	CString strTemp;
	strTemp = strOrigin.Right ( strOrigin.GetLength () - 1 );

	int nFirstBlankPos = strTemp.Find ( BLANK_SYMBOL );

	CString strName;
	CString strMsg;

	//	메시지가 없는 경우
	if ( nFirstBlankPos < 0 )
	{
		strName = strTemp;
	}
	else
	{
		//	@ 캐릭명.. @와 캐릭명 사이의 공백을 무시하게 한다.
		if ( 0 == nFirstBlankPos )
		{
			while ( nFirstBlankPos < strTemp.GetLength () )
			{
				if ( strTemp[nFirstBlankPos] != BLANK_SYMBOL )
					break;
				nFirstBlankPos++;
			}

			strTemp = strTemp.Right ( strTemp.GetLength () - nFirstBlankPos );
			nFirstBlankPos = strTemp.Find ( BLANK_SYMBOL );					
		}

		strName = strTemp.Left ( nFirstBlankPos );			
		strMsg = strTemp.Right ( strTemp.GetLength () - nFirstBlankPos - 1 );
	}

	if ( strName.GetLength () )
	{
		ADD_FRIEND ( strName );
		CInnerInterface::GetInstance().ADD_FRIEND_NAME_TO_EDITBOX ( strName );
	}

	CString strTrim = strMsg;
	strTrim.Trim ( BLANK_SYMBOL );
	if ( !strName.GetLength () || !strTrim.GetLength () ) return false;

	CString srtTemp = strMsg;

    //	필터링
	if ( CRanFilter::GetInstance().ChatFilter ( srtTemp ) )
		srtTemp = CRanFilter::GetInstance().GetProverb();

	//ItemLink
	CheckItemLink( strOrigin.GetString() );
	if ( pNetClient ) pNetClient->SndChatPrivate ( strName.GetString(), strMsg.GetString (), &sITEMLINK );

	CString strCombine;
	strCombine.Format ( "[%s] to ( %s ):%s",ID2GAMEWORD("CHAT_OPTION",1), strName, srtTemp.GetString () );
	AddStringToChatEx ( strCombine, CHAT_PRIVATE, &sITEMLINK );

	//strCombine.Format ( "(%s)%s:%s", strName, ID2GAMEINTEXT("CHAT_PRIVATE_TO_MSG"), strMsg.GetString () );
	//AddStringToChatEx ( strCombine, CHAT_PRIVATE );

	return true;
}

bool CBasicChatRightBody::SEND_PARTY_MESSAGE ( const CString& strOrigin )
{
	CNetClient*	pNetClient = DxGlobalStage::GetInstance().GetNetClient();
	GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();

	CString strMsg;
	strMsg = strOrigin.Right ( strOrigin.GetLength () - 1 );

	CString strTrim = strMsg;
	strTrim.Trim ( BLANK_SYMBOL );
	if ( !strTrim.GetLength () ) return false;

	CString strTemp = strMsg;

	//	필터링
	if ( CRanFilter::GetInstance().ChatFilter ( strTemp ) )
		strTemp = CRanFilter::GetInstance().GetProverb();
	//}

	//ItemLink
	CheckItemLink( strOrigin.GetString() );
	if ( pNetClient ) pNetClient->SndChatParty ( strMsg.GetString (), &sITEMLINK  );			

	CString strCombine;
	strCombine.Format ( "[%s]( %s ):%s",ID2GAMEWORD("CHAT_OPTION",2), pCharacter->m_szName, strTemp.GetString () );
	AddStringToChatEx ( strCombine, CHAT_PARTY, &sITEMLINK  );

	return true;
}

bool CBasicChatRightBody::SEND_TOALL_MESSAGE ( const CString& strOrigin )
{
	CNetClient*	pNetClient = DxGlobalStage::GetInstance().GetNetClient();
	GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();

	CString strMsg;
	strMsg = strOrigin.Right ( strOrigin.GetLength () - 1 );

	CString strTrim = strMsg;
	strTrim.Trim ( BLANK_SYMBOL );
	if ( !strTrim.GetLength () ) return false;

//	받을때 필터링
//	CString strTemp = strMsg;
//	if ( CRanFilter::GetInstance().ChatFilter ( strTemp ) )
//		strTemp = CRanFilter::GetInstance().GetProverb();

	CheckItemLink( strOrigin.GetString() );
	pCharacter->ReqLoudSpeaker ( strMsg.GetString (), &sITEMLINK );

	return true;
}

bool CBasicChatRightBody::SEND_GUILD_MESSAGE ( const CString& strOrigin )
{
	CNetClient*	pNetClient = DxGlobalStage::GetInstance().GetNetClient();
	GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();

	CString strMsg;
	strMsg = strOrigin.Right ( strOrigin.GetLength () - 1 );

	CString strTrim = strMsg;
	strTrim.Trim ( BLANK_SYMBOL );
	if ( !strTrim.GetLength () ) return false;

//	받을때 필터링
//	CString strTemp = strMsg;
//	if ( CRanFilter::GetInstance().ChatFilter ( strTemp ) )
//		strTemp = CRanFilter::GetInstance().GetProverb();

	CheckItemLink( strOrigin.GetString() );
	if ( pNetClient ) pNetClient->SndChatGuild ( strMsg.GetString (), &sITEMLINK );			

	return true;
}

//add region chat by AnFire16 ( 7/31/2017)
bool CBasicChatRightBody::SEND_REGION_MESSAGE ( const CString& strOrigin )
{
	CNetClient*	pNetClient = DxGlobalStage::GetInstance().GetNetClient();
	GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();

	CString strMsg;
	strMsg = strOrigin.Right ( strOrigin.GetLength () - 1 );

	CString strTrim = strMsg;
	strTrim.Trim ( BLANK_SYMBOL );
	if ( !strTrim.GetLength () ) return false;

//	받을때 필터링
//	CString strTemp = strMsg;
//	if ( CRanFilter::GetInstance().ChatFilter ( strTemp ) )
//		strTemp = CRanFilter::GetInstance().GetProverb();

	CheckItemLink( strOrigin.GetString() );
	if ( pNetClient ) pNetClient->SndChatRegion ( strMsg.GetString (), &sITEMLINK );			

	return true;
}

bool CBasicChatRightBody::SEND_ALLIANCE_MESSAGE ( const CString& strOrigin )
{
	CNetClient*	pNetClient = DxGlobalStage::GetInstance().GetNetClient();
	GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();

	CString strMsg;
	strMsg = strOrigin.Right ( strOrigin.GetLength () - 1 );

	CString strTrim = strMsg;
	strTrim.Trim ( BLANK_SYMBOL );
	if ( !strTrim.GetLength () ) return false;

//	받을때 필터링
//	CString strTemp = strMsg;
//	if ( CRanFilter::GetInstance().ChatFilter ( strTemp ) )
//		strTemp = CRanFilter::GetInstance().GetProverb();

	CheckItemLink( strOrigin.GetString() );
	if ( pNetClient ) pNetClient->SndChatAlliance( strMsg.GetString(), &sITEMLINK );			

	return true;
}

bool CBasicChatRightBody::SEND_CHAT_MESSAGE ( const CString& strOrigin )
{
	PLANDMANCLIENT pLand = GLGaeaClient::GetInstance().GetActiveMap();
	if ( !pLand->m_bTowerWars && m_nCHATTYPE == CHAT_REGION)
	{
		CInnerInterface::GetInstance().PrintConsoleText ( "You can only use Regional Chat in Tyranny Wars." );
		return FALSE;
	}
	if( ( m_nCHATTYPE == CHAT_NORMAL || m_nCHATTYPE == CHAT_TOALL || m_nCHATTYPE == CHAT_REGION) && IsPapering( strOrigin ) ) return FALSE;

#if defined( TH_PARAM )
	if ( !IsThaiCheck( strOrigin ) ) return FALSE;
#endif 

#if defined( VN_PARAM )
	if ( !IsVnCheck( strOrigin ) ) return FALSE;
#endif 


	switch ( m_nCHATTYPE )
	{
	case CHAT_PRIVATE:	return SEND_PRIVATE_MESSAGE( strOrigin );
	case CHAT_PARTY:	return SEND_PARTY_MESSAGE( strOrigin );
	case CHAT_TOALL:	return SEND_TOALL_MESSAGE( strOrigin );
	case CHAT_GUILD:	return SEND_GUILD_MESSAGE( strOrigin );
	case CHAT_ALLIANCE:	return SEND_ALLIANCE_MESSAGE( strOrigin );
	case CHAT_REGION:	return SEND_REGION_MESSAGE( strOrigin ); //add region chat by AnFire16 ( 7/31/2017)
	default:
		{
			//	Note : 제스쳐.
			int nMOTION = CEmoticon::GetInstance().GetEmoticonOfTerm ( strOrigin.GetString() );
			if ( nMOTION!=UINT_MAX )
			{
				GLGaeaClient::GetInstance().GetCharacter()->ReqGESTURE ( nMOTION );
			}

			return SEND_COMMON_MESSAGE ( strOrigin );
		}
		break;
	}
}

HRESULT CBasicChatRightBody::RestoreDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	HRESULT hr = S_OK;
	hr = CUIGroup::RestoreDeviceObjects ( pd3dDevice );
	if ( FAILED ( hr ) ) return hr;

	m_pScrollBar_ALL->GetThumbFrame()->SetPercent ( CBasicScrollThumbFrame::fHUNDRED_PERCENT );

	return hr;
}

void CBasicChatRightBody::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	if ( m_bFREEZE ) return ;

	switch ( ControlID )
	{
	case CHAT_EDITBOX:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				//	캐릭터 움직임 막기
				AddMessageEx ( UIMSG_MOUSEIN_RIGHTBODY );

				if ( UIMSG_LB_DOWN & dwMsg )
				{
					ADD_FRIEND_LIST();
					EDIT_BEGIN ();
				}
			}
			else
			{
				if ( m_pEditBox->IsMODE_NATIVE () )
				{
					DWORD dwNativeMsg = m_pNativeButton->GetMessageEx ();					
					if ( CHECK_MOUSE_IN ( dwNativeMsg ) ) return ;
				}
				else
				{
					DWORD dwEnglishMsg = m_pEnglishButton->GetMessageEx ();
					if ( CHECK_MOUSE_IN ( dwEnglishMsg ) ) return ;
				}

				if ( m_pEditBox->IsBegin () )
				{
					if ( (UIMSG_LB_DOWN & dwMsg) ||
						 (UIMSG_MB_DOWN & dwMsg) ||
						 (UIMSG_RB_DOWN & dwMsg)
						)
					{
						EDIT_END ();
					}
				}
			}
		}
		break;
		
	case CHAT_LEFT_BAR_TOP:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( CHECK_LB_DOWN_LIKE ( dwMsg ) )
				{
					AddMessageEx ( UIMSG_MOUSEIN_LEFTBAR_DRAG );
				}
			}
		}
	break;
	case CHAT_NATIVE_BUTTON:
	case CHAT_ENGLISH_BUTTON:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				//	캐릭터 움직임 막기
				AddMessageEx ( UIMSG_MOUSEIN_RIGHTBODY );
			}

			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				m_pEditBox->DoMODE_TOGGLE ();
			}
		}
		break;

	case CHAT_CHANNEL_TOTAL:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				//	캐릭터 움직임 막기
				AddMessageEx ( UIMSG_MOUSEIN_RIGHTBODY );
			}

			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				m_wDISPLAYTYPE = CHAT_CHANNEL_TOTAL;
			}
		}
		break;

	case CHAT_CHANNEL_PRIVATE:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				//	캐릭터 움직임 막기
				AddMessageEx ( UIMSG_MOUSEIN_RIGHTBODY );
			}

			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				m_wDISPLAYTYPE = CHAT_CHANNEL_PRIVATE;
			}
		}
		break;

	case CHAT_CHANNEL_PARTY:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				//	캐릭터 움직임 막기
				AddMessageEx ( UIMSG_MOUSEIN_RIGHTBODY );
			}

			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				m_wDISPLAYTYPE = CHAT_CHANNEL_PARTY;
			}
		}
		break;

	case CHAT_CHANNEL_CLUB:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				//	캐릭터 움직임 막기
				AddMessageEx ( UIMSG_MOUSEIN_RIGHTBODY );
			}

			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				m_wDISPLAYTYPE = CHAT_CHANNEL_CLUB;
			}
		}
		break;

	case CHAT_CHANNEL_ALLIANCE:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				//	캐릭터 움직임 막기
				AddMessageEx ( UIMSG_MOUSEIN_RIGHTBODY );
			}

			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				m_wDISPLAYTYPE = CHAT_CHANNEL_ALLIANCE;
			}
		}
		break;

	case CHAT_CHANNEL_SYSTEM:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				//	캐릭터 움직임 막기
				AddMessageEx ( UIMSG_MOUSEIN_RIGHTBODY );
			}

			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{
				m_wDISPLAYTYPE = CHAT_CHANNEL_SYSTEM;
			}
		}
		break;

		case CHAT_TEXTBOX_ALL:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( UIMSG_LB_DUP & dwMsg )
				{
					const int nIndex = m_pTextBox_ALL->GetSelectPos ();
					if ( nIndex < 0 || m_pTextBox_ALL->GetCount () <= nIndex ) return ;

					int PositionText = 0 ;
					int PositionText2 = 0 ;
					CString strCharName = m_pTextBox_ALL->GetText( nIndex );
					for(int i = 1; i < strlen(strCharName); i++)
					{
					if( strCharName[i] == _T('(') )
					{
					PositionText = i;
					}
					if( strCharName[i] == _T(')') )
					{
					PositionText2 = i;
					}
					}
					if ( PositionText || PositionText2 ){
					BEGIN_PRIVATE_CHAT( strCharName.Mid( PositionText+ 1, PositionText2 - PositionText - 1 ) );
					}
				}

				if ( UIMSG_LB_UP & dwMsg )
				{
					const int nIndex = m_pTextBox_ALL->GetSelectPos ();
					if ( nIndex < 0 || m_pTextBox_ALL->GetCount () <= nIndex ) return ;

					SITEMLINK sITEM = m_pTextBox_ALL->GetItemLink( nIndex );
					CString strText = m_pTextBox_ALL->GetText( nIndex );
					CheckItemLink( strText.GetString(), sITEM );	

					if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LMENU  ) & DXKEY_DOWNED )
					{
						CheckPreviewItemLink( strText.GetString(), sITEM ); //ItemLink
					}
				}
			}
		}
		break;
		//ItemLink
		case CHAT_TEXTBOX_PARTY:
			{
				if ( CHECK_MOUSE_IN ( dwMsg ) )
				{
					if ( UIMSG_LB_UP & dwMsg )
					{
						const int nIndex = m_pTextBox_PARTY->GetSelectPos ();
						if ( nIndex < 0 || m_pTextBox_PARTY->GetCount () <= nIndex ) return ;

						SITEMLINK sITEM = m_pTextBox_PARTY->GetItemLink( nIndex );
						CString strText = m_pTextBox_PARTY->GetText( nIndex );
						CheckItemLink( strText.GetString(), sITEM );	

						if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LMENU  ) & DXKEY_DOWNED )
						{
							CheckPreviewItemLink( strText.GetString(), sITEM );
						}
					}
				}
			}break;
		case CHAT_TEXTBOX_CLUB:
			{
				if ( CHECK_MOUSE_IN ( dwMsg ) )
				{
					if ( UIMSG_LB_UP & dwMsg )
					{
						const int nIndex = m_pTextBox_CLUB->GetSelectPos ();
						if ( nIndex < 0 || m_pTextBox_CLUB->GetCount () <= nIndex ) return ;

						SITEMLINK sITEM = m_pTextBox_CLUB->GetItemLink( nIndex );
						CString strText = m_pTextBox_CLUB->GetText( nIndex );
						CheckItemLink( strText.GetString(), sITEM );	

						if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LMENU  ) & DXKEY_DOWNED )
						{
							CheckPreviewItemLink( strText.GetString(), sITEM );
						}
					}
				}
			}break;

		//add region chat by AnFire16 ( 7/31/2017)
		case CHAT_TEXTBOX_REGION:
			{
				if ( CHECK_MOUSE_IN ( dwMsg ) )
				{
					if ( UIMSG_LB_UP & dwMsg )
					{
						const int nIndex = m_pTextBox_REGION->GetSelectPos ();
						if ( nIndex < 0 || m_pTextBox_REGION->GetCount () <= nIndex ) return ;

						SITEMLINK sITEM = m_pTextBox_REGION->GetItemLink( nIndex );
						CString strText = m_pTextBox_REGION->GetText( nIndex );
						CheckItemLink( strText.GetString(), sITEM );	

						if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LMENU  ) & DXKEY_DOWNED )
						{
							CheckPreviewItemLink( strText.GetString(), sITEM );
						}
					}
				}
			}break;

		case CHAT_TEXTBOX_ALLIANCE:
			{
				if ( CHECK_MOUSE_IN ( dwMsg ) )
				{
					if ( UIMSG_LB_UP & dwMsg )
					{
						const int nIndex = m_pTextBox_ALLIANCE->GetSelectPos ();
						if ( nIndex < 0 || m_pTextBox_ALLIANCE->GetCount () <= nIndex ) return ;

						SITEMLINK sITEM = m_pTextBox_ALLIANCE->GetItemLink( nIndex );
						CString strText = m_pTextBox_ALLIANCE->GetText( nIndex );
						CheckItemLink( strText.GetString(), sITEM );	

						if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LMENU  ) & DXKEY_DOWNED )
						{
							CheckPreviewItemLink( strText.GetString(), sITEM );
						}
					}
				}
			}break;
		case CHAT_TEXTBOX_PRIVATE:
			{
				if ( CHECK_MOUSE_IN ( dwMsg ) )
				{
					if ( UIMSG_LB_UP & dwMsg )
					{
						const int nIndex = m_pTextBox_PRIVATE->GetSelectPos ();
						if ( nIndex < 0 || m_pTextBox_PRIVATE->GetCount () <= nIndex ) return ;

						SITEMLINK sITEM = m_pTextBox_PRIVATE->GetItemLink( nIndex );
						CString strText = m_pTextBox_PRIVATE->GetText( nIndex );
						CheckItemLink( strText.GetString(), sITEM );	

						if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LMENU  ) & DXKEY_DOWNED )
						{
							CheckPreviewItemLink( strText.GetString(), sITEM );
						}
					}
				}
			}break;

		case CHAT_TEXTBOX_SYSTEM:
			{
				if ( CHECK_MOUSE_IN ( dwMsg ) )
				{
					if ( UIMSG_LB_UP & dwMsg )
					{
						const int nIndex = m_pTextBox_SYSTEM->GetSelectPos ();
						if ( nIndex < 0 || m_pTextBox_SYSTEM->GetCount () <= nIndex ) return ;

						SITEMLINK sITEM = m_pTextBox_SYSTEM->GetItemLink( nIndex );
						CString strText = m_pTextBox_SYSTEM->GetText( nIndex );
						CheckItemLink( strText.GetString(), sITEM );	

						if ( DxInputDevice::GetInstance().GetKeyState ( DIK_LMENU  ) & DXKEY_DOWNED )
						{
							CheckPreviewItemLink( strText.GetString(), sITEM );
						}
					}
				}
			}break;
	}
}

void CBasicChatRightBody::AddStringToNORMAL ( CString strTemp, D3DCOLOR dwColor, SITEMLINK* pItemLink )
{
	if ( m_pTextBox_ALL && m_pScrollBar_ALL )
	{
		m_pTextBox_ALL->AddText ( strTemp, pItemLink, dwColor );

		{
			CBasicScrollThumbFrame* const pThumbFrame = m_pScrollBar_ALL->GetThumbFrame ();
			if ( !pThumbFrame )
			{
				GASSERT ( 0 && "썸이 만들어지지 않았습니다.");
				return ;
			}

			int nTotal, nView;
			pThumbFrame->GetState ( nTotal, nView );	

			const int nTotalLine = m_pTextBox_ALL->GetTotalLine ();
			pThumbFrame->SetState ( nTotalLine, nView );
			pThumbFrame->SetPercent ( CBasicScrollThumbFrame::fHUNDRED_PERCENT );
		}
	}
}

void CBasicChatRightBody::AddStringToChatEx ( CString strTemp, WORD wType, SITEMLINK* pItemLink  )
{
	D3DCOLOR dwTempColor = NS_UITEXTCOLOR::DEFAULT;
	switch ( wType )
	{
	case CHAT_NORMAL:			//일반 채팅 모드
		dwTempColor = GLCONST_CHAR::dwCHAT_NORMAL_COLOR;
		break;

	case CHAT_PRIVATE:
		{
			dwTempColor = GLCONST_CHAR::dwCHAT_PRIVATE_COLOR;
			ADD_CHAT_PAGE_TEXTBOX ( strTemp, dwTempColor, m_pTextBox_PRIVATE, m_pScrollBar_PRIVATE, pItemLink );
		}
		break;	

	case CHAT_GUILD:
		{
			dwTempColor = GLCONST_CHAR::dwCHAT_GUILD_COLOR;
			ADD_CHAT_PAGE_TEXTBOX ( strTemp, dwTempColor, m_pTextBox_CLUB, m_pScrollBar_CLUB, pItemLink );
		}
		break;

	//add region chat by AnFire16 ( 7/31/2017)
	case CHAT_REGION:
		{
			dwTempColor = NS_UITEXTCOLOR::DODGERBLUE;
			ADD_CHAT_PAGE_TEXTBOX ( strTemp, dwTempColor, m_pTextBox_REGION, m_pScrollBar_REGION, pItemLink );
		}
		break;

	case CHAT_TOALL:
		{
			dwTempColor = GLCONST_CHAR::dwCHAT_TOALL_COLOR;			
		}
		break;

	case CHAT_PARTY:
		{
			dwTempColor = GLCONST_CHAR::dwCHAT_PARTY_COLOR;
			ADD_CHAT_PAGE_TEXTBOX ( strTemp, dwTempColor, m_pTextBox_PARTY, m_pScrollBar_PARTY, pItemLink );
		}
		break;

	case CHAT_ALLIANCE:
		{
			dwTempColor = GLCONST_CHAR::dwCHAT_ALLIANCE_COLOR;
			ADD_CHAT_PAGE_TEXTBOX ( strTemp, dwTempColor, m_pTextBox_ALLIANCE, m_pScrollBar_ALLIANCE, pItemLink );
		}
		break;

	case CHAT_SYSTEM:			//에러 또는 시스템 메시지
		{
			dwTempColor = GLCONST_CHAR::dwCHAT_SYSTEM_COLOR;
			ADD_CHAT_PAGE_TEXTBOX ( strTemp, dwTempColor, m_pTextBox_SYSTEM, m_pScrollBar_SYSTEM, pItemLink );
		}
		break;
	}

	if ( !m_bIgnoreState && !(m_wDisplayState & wType) ) return ;

	AddStringToNORMAL ( strTemp, dwTempColor, pItemLink );

	if ( m_bChatLog ) SAVE_CHATLOG( strTemp, wType );
	RECORD_CHAT( strTemp, wType );
}

void CBasicChatRightBody::AddStringToSystemMessage ( CString strTemp, D3DCOLOR dwColor )
{
	ADD_CHAT_PAGE_TEXTBOX ( strTemp, dwColor, m_pTextBox_SYSTEM, m_pScrollBar_SYSTEM, NULL );

	if ( m_wDisplayState & CHAT_SYSTEM )
	{
		AddStringToNORMAL ( strTemp, dwColor, NULL  );
		
		if ( m_bChatLog ) SAVE_CHATLOG( strTemp, CHAT_SYSTEM );
		RECORD_CHAT( strTemp, CHAT_SYSTEM );
	}
}

void CBasicChatRightBody::AddItemLinkGlobalGrind( SITEMCUSTOM* pITEM )
{
	if ( !pITEM )	return;
	SITEM* pITEMDATA = GLItemMan::GetInstance().GetItem( pITEM->sNativeID );
	if ( !pITEMDATA )	return;
	if ( !m_pEditBox )	return;

	bool bLinkNonTrade = GLCONST_CHAR::bLINKNONTRADE;
	if( !bLinkNonTrade )
	{
		if ( !pITEMDATA->sBasicOp.IsSALE() )	
		{
			CInnerInterface::GetInstance().PrintConsoleText ( ID2GAMEINTEXT("LINK_NONSELL") );
			return;
		}

		if ( !pITEMDATA->sBasicOp.IsEXCHANGE() )
		{
			CInnerInterface::GetInstance().PrintConsoleText ( ID2GAMEINTEXT("LINK_NONTRADE") );
			return;
		}
	}

	SITEMLINK sLINK;
	SITEMCUSTOM sITEMCUSTOM;
	sITEMCUSTOM = *pITEM;
	sITEMCUSTOM.Convert( sLINK );
	BYTE uGRADE = sITEMCUSTOM.GETGRADE(EMGRINDING_NUNE);
	CString strTemp;
	if ( uGRADE != 0 )
	strTemp.Format("+%d %s",uGRADE,pITEMDATA->GetName());
	else
	strTemp.Format("%s",pITEMDATA->GetName());

if ( sITEMCUSTOM.IsWrap() ) sLINK.BuildFilter( strTemp, true );
	else sLINK.BuildFilter( strTemp, false );

	//sLINK.BuildFilter( strTemp );

	SITEM* SITEMCHECK = GLItemMan::GetInstance().GetItem( sITEMLINK.sNativeID );
	if ( SITEMCHECK )
	{

		sITEMLINK = sLINK;

		return;
	}

	sITEMLINK = sLINK;
}

void CBasicChatRightBody::AddItemLink( SITEMCUSTOM* pITEM )
{
	if ( !pITEM )	return;
	SITEM* pITEMDATA = GLItemMan::GetInstance().GetItem( pITEM->sNativeID );
	if ( !pITEMDATA )	return;
	if ( !m_pEditBox )	return;

	bool bLinkNonTrade = GLCONST_CHAR::bLINKNONTRADE;
	if( !bLinkNonTrade )
	{
		//if ( !pITEMDATA->sBasicOp.IsSALE() )	
		//{
		//	CInnerInterface::GetInstance().PrintConsoleText ( ID2GAMEINTEXT("LINK_NONSELL") );
		//	return;
		//}

		//if ( !pITEMDATA->sBasicOp.IsEXCHANGE() )
		//{
		//	CInnerInterface::GetInstance().PrintConsoleText ( ID2GAMEINTEXT("LINK_NONTRADE") );
		//	return;
		//}
	}

	SITEMLINK sLINK;
	SITEMCUSTOM sITEMCUSTOM;
	sITEMCUSTOM = *pITEM;
	sITEMCUSTOM.Convert( sLINK );
	BYTE uGRADE = sITEMCUSTOM.GETGRADE(EMGRINDING_NUNE);
	/*CString strTemp;
	if ( uGRADE != 0 )
	strTemp.Format("+%d %s",uGRADE,pITEMDATA->GetName());
	else
	strTemp.Format("%s",pITEMDATA->GetName());*/

	//sLINK.BuildFilter( strTemp );
	if ( sITEMCUSTOM.IsWrap() ) sLINK.BuildFilter( pITEMDATA->GetName(), true );
	else sLINK.BuildFilter( pITEMDATA->GetName(), false );
	//sLINK.BuildFilter( pITEMDATA->GetName());

	SITEM* SITEMCHECK = GLItemMan::GetInstance().GetItem( sITEMLINK.sNativeID );
	if ( SITEMCHECK )
	{
		//old item exist
		//since we only allow 1 item for now we need to replace the itemlink text
		//but chat type must remain the same 
		CString strTEXT = m_pEditBox->GetEditString();
		CString strOLDLINKTEXT = sITEMLINK.GetFilter();
		strTEXT.Replace( strOLDLINKTEXT.GetString(), sLINK.GetFilter() );

		EDIT_CLEAR ();
		EDIT_BEGIN ( strTEXT.GetString() );

		sITEMLINK = sLINK;

		return;
	}

	if ( m_pEditBox->IsEmpty() )
	{
		//TODO
		//adjust to active chattype
		BEGIN_NORMAL_CHAT ( sLINK.GetFilter() );
	}
	else
	{
		CString strOLDTEXT = m_pEditBox->GetEditString();
		strOLDTEXT += sLINK.GetFilter();

		EDIT_CLEAR ();
		EDIT_BEGIN ( strOLDTEXT.GetString() );
	}

	sITEMLINK = sLINK;
}

void	CBasicChatRightBody::BEGIN_NORMAL_CHAT ( const CString& strMessage )
{	
	m_pEditBox->SetTextColor ( GLCONST_CHAR::dwCHAT_NORMAL_COLOR );

	CString strCombine;
	strCombine.Format ( "[%s]%s",ID2GAMEWORD("CHAT_OPTION",8), ID2GAMEINTEXT("CHAT_NORMAL_MODE") );

	AddStringToNORMAL ( strCombine, GLCONST_CHAR::dwCHAT_NORMAL_COLOR, NULL );	

	EDIT_CLEAR ();
	EDIT_BEGIN ( strMessage );
}

void	CBasicChatRightBody::BEGIN_PRIVATE_CHAT ( const CString& strName, const CString strMessage )
{	
	m_pEditBox->SetTextColor ( GLCONST_CHAR::dwCHAT_PRIVATE_COLOR );
		
	CString strCombine2;
	strCombine2.Format ( "[%s]%s",ID2GAMEWORD("CHAT_OPTION",8), ID2GAMEINTEXT("CHAT_PRIVATE_MODE") );
	
	AddStringToNORMAL ( strCombine2, GLCONST_CHAR::dwCHAT_PRIVATE_COLOR, NULL );

	CString strCombine( PRIVATE_SYMBOL + strName + BLANK_SYMBOL + strMessage );
	if ( !strName.GetLength () ) strCombine = PRIVATE_SYMBOL;
	EDIT_CLEAR ();
	EDIT_BEGIN ( strCombine );
}

void	CBasicChatRightBody::BEGIN_PARTY_CHAT ( const CString& strMessage )
{
	m_pEditBox->SetTextColor ( GLCONST_CHAR::dwCHAT_PARTY_COLOR );
	
	CString strCombine2;
	strCombine2.Format ( "[%s]%s",ID2GAMEWORD("CHAT_OPTION",8), ID2GAMEINTEXT("CHAT_PARTY_MODE") );
	
	AddStringToNORMAL ( strCombine2, GLCONST_CHAR::dwCHAT_PARTY_COLOR, NULL );

	CString strCombine = PARTY_SYMBOL + strMessage;
	EDIT_CLEAR ();
	EDIT_BEGIN ( strCombine );
}

void	CBasicChatRightBody::BEGIN_TOALL_CHAT ( const CString& strMessage )
{
	m_pEditBox->SetTextColor ( GLCONST_CHAR::dwCHAT_TOALL_COLOR );

	CString strCombine2;
	strCombine2.Format ( "[%s]%s",ID2GAMEWORD("CHAT_OPTION",8), ID2GAMEINTEXT("CHAT_TOALL_MODE") );

	AddStringToNORMAL ( strCombine2, GLCONST_CHAR::dwCHAT_TOALL_COLOR, NULL );

	CString strCombine = TOALL_SYMBOL + strMessage;
	EDIT_CLEAR ();
	EDIT_BEGIN ( strCombine );
}

void	CBasicChatRightBody::BEGIN_GUILD_CHAT ( const CString& strMessage )
{
	m_pEditBox->SetTextColor ( GLCONST_CHAR::dwCHAT_GUILD_COLOR );
		
	CString strCombine2;
	strCombine2.Format ( "[%s]%s",ID2GAMEWORD("CHAT_OPTION",8), ID2GAMEINTEXT("CHAT_GUILD_MODE") );

	AddStringToNORMAL ( strCombine2, GLCONST_CHAR::dwCHAT_GUILD_COLOR, NULL );

	CString strCombine = GUILD_SYMBOL + strMessage;
	EDIT_CLEAR ();
	EDIT_BEGIN ( strCombine );
}

//add region chat by AnFire16 ( 7/31/2017)
void	CBasicChatRightBody::BEGIN_REGION_CHAT ( const CString& strMessage )
{
	m_pEditBox->SetTextColor ( NS_UITEXTCOLOR::DODGERBLUE );
		
	CString strCombine2;
	strCombine2.Format ( "[%s]%s",ID2GAMEWORD("CHAT_OPTION",8), ID2GAMEINTEXT("CHAT_REGION_MODE") );

	AddStringToNORMAL ( strCombine2, NS_UITEXTCOLOR::DODGERBLUE, NULL );

	CString strCombine = REGION_SYMBOL + strMessage;
	EDIT_CLEAR ();
	EDIT_BEGIN ( strCombine );
}

void	CBasicChatRightBody::BEGIN_ALLIANCE_CHAT( const CString& strMessage )
{
	m_pEditBox->SetTextColor ( GLCONST_CHAR::dwCHAT_ALLIANCE_COLOR );
		
	CString strCombine2;
	strCombine2.Format ( "[%s]%s",ID2GAMEWORD("CHAT_OPTION",8), ID2GAMEINTEXT("CHAT_ALLIANCE_MODE") );

	AddStringToNORMAL ( strCombine2, GLCONST_CHAR::dwCHAT_ALLIANCE_COLOR, NULL );

	CString strCombine = ALLIANCE_SYMBOL + strMessage;
	EDIT_CLEAR ();
	EDIT_BEGIN ( strCombine );
}

void	CBasicChatRightBody::ADD_FRIEND_LIST ()
{
	GLFriendClient::FRIENDMAP& FriendMap = GLFriendClient::GetInstance().GetFriend ();
	if ( FriendMap.size () == m_nFRIENDSIZE_BACK ) return ;

	GLFriendClient::FRIENDMAP_ITER iter = FriendMap.begin ();
	GLFriendClient::FRIENDMAP_ITER iter_end = FriendMap.end ();

	for ( ; iter != iter_end; ++iter )
	{
		SFRIEND& sFriend = (*iter).second;

		if( sFriend.bONLINE ) ADD_FRIEND ( sFriend.szCharName ); // 온라인이면 리스트에 추가한다.
	}

	m_nFRIENDSIZE_BACK = (int)FriendMap.size ();
}

void	CBasicChatRightBody::ADD_FRIEND ( const CString& strName )
{
	if ( !strName.GetLength () ) return ;

	//	삽입
	NAMELIST_ITER iter = m_NameList.begin ();
	NAMELIST_ITER iter_end = m_NameList.end ();
	for ( ; iter != iter_end; ++iter )	//	혹시 중간에 있다면...
	{
		if( (*iter) == strName )
		{
			m_NameList.erase( iter );
			m_NamePos = 0; // 삭제된 이름이 있다면 다시 포지션을 0으로 설정
			break;
		}
	}

	m_NameList.push_front( strName );

	if ( m_NameList.size () > 30 )
	{
		m_NameList.pop_back();
	}
}

void CBasicChatRightBody::DEL_FRIEND( const CString& strName )
{
	if ( !strName.GetLength () ) return ;

	if( !m_NameList.empty() ) m_NameList.remove( strName );
}

void CBasicChatRightBody::EDIT_BEGIN ( const CString& strMessage )
{
	if ( strMessage.GetLength () ) m_pEditBox->SetEditString ( strMessage );

	m_pEditBox->BeginEdit ();
}

bool CBasicChatRightBody::SEND_CHAT_MESSAGE ()
{
	bool no_message = false;   
	
	CString strInput = m_pEditBox->GetEditString ();
	strInput.TrimLeft ( BLANK_SYMBOL );	//	좌측 공백 무시
	if ( strInput.GetLength () )
	{
		bool bincmd(false);
		CheckItemLink( strInput.GetString() ); //ItemLink
		bincmd = dxincommand::command ( strInput.GetString (), &sITEMLINK );
		if ( !bincmd )
		{						
			if ( !SEND_CHAT_MESSAGE ( strInput ) )
			{
				no_message = true;
			}
		}
	}
	else
	{
		no_message = true;
	}

	EDIT_CLEAR ();
	KEEP_LAST_STATE ();

	if ( no_message ) EDIT_END ();

	return true;
}

void CBasicChatRightBody::KEEP_LAST_STATE ()
{
	switch ( m_nCHATTYPE )
	{
	case CHAT_PRIVATE:
		{
			if ( m_NameList.size () )
			{
				NAMELIST_ITER iter = m_NameList.begin ();
				CString strName = (*iter);
				m_pEditBox->SetEditString ( PRIVATE_SYMBOL + strName + BLANK_SYMBOL );
			}
			else
			{
				m_pEditBox->SetEditString ( CString(PRIVATE_SYMBOL) );
			}	
		}
		break;

	case CHAT_PARTY:
		{
			m_pEditBox->SetEditString ( CString(PARTY_SYMBOL) );
		}
		break;

	case CHAT_TOALL:
		{
			m_pEditBox->SetEditString ( CString(TOALL_SYMBOL) );
		}
		break;

	case CHAT_GUILD:
		{
			m_pEditBox->SetEditString ( CString(GUILD_SYMBOL) );
		}
		break;

	//add region chat by AnFire16 ( 7/31/2017)
	case CHAT_REGION:
		{
			m_pEditBox->SetEditString ( CString(REGION_SYMBOL) );
		}
		break;

	case CHAT_ALLIANCE:
		{
			m_pEditBox->SetEditString ( CString(ALLIANCE_SYMBOL) );
		}
		break;
	}
}

void CBasicChatRightBody::EDIT_END ()
{
	m_pEditBox->EndEdit ();
	m_nCHATTYPE = CHAT_NO;
}

void	CBasicChatRightBody::ShowSelfMessageOnHead ( const CString& strOrigin )
{
	GLCharacter* pCharacter = GLGaeaClient::GetInstance().GetCharacter();
	CHeadChatDisplayMan* pHeadChatDisplayMan = CInnerInterface::GetInstance().GetHeadChatDisplayMan ();

	if( pHeadChatDisplayMan && pCharacter )
	{
		D3DXVECTOR3 *pPos = GLGaeaClient::GetInstance().FindCharHeadPos( pCharacter->m_szName );
		if ( pPos )
		{
			D3DXVECTOR3 vPos = *pPos;
			D3DXVECTOR3 vScreen = DxViewPort::GetInstance().ComputeVec3Project ( &vPos, NULL );

			int nPosX = (int)( vScreen.x);
			int nPosY = (int)( vScreen.y);

			D3DXVECTOR2 vCharPos = D3DXVECTOR2 ( float(nPosX), float(nPosY ) );

			DWORD dwIDColor = NS_UITEXTCOLOR::IDCOLOR;
			GLPARTY_CLIENT* pMaster = GLPartyClient::GetInstance().GetMaster();
			if ( pMaster ) dwIDColor = NS_UITEXTCOLOR::GREENYELLOW;
			pHeadChatDisplayMan->AddChat ( pCharacter->m_szName, dwIDColor, strOrigin, NS_UITEXTCOLOR::DEFAULT, vCharPos );
		}
	}
}

void CBasicChatRightBody::ChatLog( bool bChatLog, int nChatLogType )
{
	if ( bChatLog ) 
	{
		m_bChatLog = true;
		m_nChatLogType |= nChatLogType;
		
		// CreteDirectory...
		TCHAR szChatLogDir[MAX_PATH]={0};
		SHGetSpecialFolderPath( NULL, szChatLogDir, CSIDL_PERSONAL, FALSE );

		std::string strChatLogDir(szChatLogDir);
		strChatLogDir += SUBPATH::CHATLOG;

		CreateDirectory( strChatLogDir.c_str() , NULL );

	}
	else 
	{
		m_nChatLogType &= ~(nChatLogType);
		if ( !m_nChatLogType ) m_bChatLog = false;
	}
}

void CBasicChatRightBody::SAVE_CHATLOG( CString strTemp, WORD wType )
{

	int nType = wType;
	
	if ( !(m_nChatLogType & nType) ) return;

	// 현재시각

	const int nServerYear = (int) GLGaeaClient::GetInstance().GetCurrentTime().GetYear ();
	const int nServerMonth = (int) GLGaeaClient::GetInstance().GetCurrentTime().GetMonth ();
	const int nServerDay = (int) GLGaeaClient::GetInstance().GetCurrentTime().GetDay ();
	const int nServerHour = (int) GLGaeaClient::GetInstance().GetCurrentTime().GetHour ();
	const int nServerMinute = (int) GLGaeaClient::GetInstance().GetCurrentTime().GetMinute();
//	const int nServerYear = (int) CInnerInterface::GetInstance().GetCurrentTime().GetYear ();
//	const int nServerMonth = (int) CInnerInterface::GetInstance().GetCurrentTime().GetMonth ();
//	const int nServerDay = (int) CInnerInterface::GetInstance().GetCurrentTime().GetDay ();
//	const int nServerHour = (int) CInnerInterface::GetInstance().GetCurrentTime().GetHour ();
//	const int nServerMinute = (int) CInnerInterface::GetInstance().GetCurrentTime().GetMinute();

	CString strChatLog;
	strChatLog.Format("%02d::%02d\t ", nServerHour, nServerMinute );

	switch ( wType )
	{
	case CHAT_NORMAL:
		break;
	case CHAT_PRIVATE:
		strChatLog += PRIVATE_SYMBOL;
		break;
	case CHAT_GUILD:
		strChatLog += GUILD_SYMBOL + GUILD_SYMBOL;
		break;
	case CHAT_REGION:
		strChatLog += REGION_SYMBOL;
		break;
	case CHAT_TOALL:
		strChatLog += TOALL_SYMBOL;
		break;
	case CHAT_PARTY:
		strChatLog += PARTY_SYMBOL;
		break;
	case CHAT_ALLIANCE:
		strChatLog += ALLIANCE_SYMBOL;
		break;
	case CHAT_SYSTEM:
		strChatLog += SYSTEM_SYMBOL;
		break;
	}

	strChatLog += "\t";

	strChatLog += strTemp;
	strChatLog += '\n';


	// 로그파일 로드 및 저장

	TCHAR szChatLogDir[MAX_PATH]={0};
	SHGetSpecialFolderPath( NULL, szChatLogDir, CSIDL_PERSONAL, FALSE );

	CString strChatLogDir(szChatLogDir);
	strChatLogDir += SUBPATH::CHATLOG;
	
	CString strChatLogFile;
	
	strChatLogFile.Format( "%s%d%02d%02d.txt", strChatLogDir, nServerYear, nServerMonth, nServerDay );

	FILE* file=NULL;
	file = fopen ( strChatLogFile, "a" );
	if ( !file )	return;

	fprintf( file, strChatLog );

	fclose( file );

}

void CBasicChatRightBody::RECORD_CHAT( const CString strChatMsg, WORD wType  )
{
	SRecordChatMsg recordChatMsg;
	CTime curTime = GLGaeaClient::GetInstance().GetCurrentTime();

	// 2분의 시간이 지난 메시지 삭제를 위해 지난 메시지를 체크한다.
	{		
		RECORD_CHAT_LOG_ITER iter = m_vecRecordChatMsg.begin();
		int i = 0;
		// 최대 10개까지만 검사
		for( ; i < 10 &&  iter != m_vecRecordChatMsg.end(); ++iter, i++ )
		{
			recordChatMsg = *iter;
			CTimeSpan timeSpan = curTime - recordChatMsg.recordTime;
			if( timeSpan.GetMinutes() >= 2 ) m_vecRecordChatMsg.erase(iter--);
		}
	}

	// 메시지 추가
	{
		recordChatMsg.recordTime = curTime;
		recordChatMsg.strChatMsg = "";
		switch ( wType )
		{
		case CHAT_PRIVATE:
			recordChatMsg.strChatMsg = "@";
			break;
		case CHAT_GUILD:
			recordChatMsg.strChatMsg = GUILD_SYMBOL + GUILD_SYMBOL;
			break;
		case CHAT_TOALL:
			recordChatMsg.strChatMsg = TOALL_SYMBOL;
			break;
		case CHAT_PARTY:
			recordChatMsg.strChatMsg = PARTY_SYMBOL;
			break;
		case CHAT_ALLIANCE:
			recordChatMsg.strChatMsg =ALLIANCE_SYMBOL;
			break;
		case CHAT_SYSTEM:
			recordChatMsg.strChatMsg =SYSTEM_SYMBOL;
			break;
		}

		recordChatMsg.strChatMsg += strChatMsg;
		m_vecRecordChatMsg.push_back( recordChatMsg );
	}
}

CString CBasicChatRightBody::GET_RECORD_CHAT()
{
	SRecordChatMsg recordChatMsg;
	RECORD_CHAT_LOG_ITER iter = m_vecRecordChatMsg.begin();
	CString strLine, strReturn;
	for( ; iter != m_vecRecordChatMsg.end(); ++iter )
	{
		recordChatMsg = *iter;
		strLine = "";
		strLine.Format( "[%d:%d:%d:%d:%d] %s \n", recordChatMsg.recordTime.GetYear(), 
												  recordChatMsg.recordTime.GetMonth(),
												  recordChatMsg.recordTime.GetHour(),
												  recordChatMsg.recordTime.GetMinute(),
												  recordChatMsg.recordTime.GetSecond(),
												  recordChatMsg.strChatMsg.GetString() );

		strReturn += strLine;
											   
	}

	return strReturn;
}

BOOL CBasicChatRightBody::IsThaiCheck( const CString& strOrigin )
{
#if defined( TH_PARAM )
	// 태국 문자 조합 체크 
	if ( !m_pCheckString ) return FALSE;

	if ( !m_pCheckString( strOrigin ) )
	{
		AddStringToSystemMessage( ID2GAMEINTEXT("CHAT_THAI_CHECK_ERROR") , NS_UITEXTCOLOR::NEGATIVE );
		return FALSE;
	}
#endif 
	return TRUE;
}

BOOL CBasicChatRightBody::IsVnCheck( const CString& strOrigin )
{
#if defined( VN_PARAM )
	// 베트남 문자 조합 체크 
	if ( STRUTIL::CheckVietnamString( strOrigin ) )
	{
		AddStringToSystemMessage( ID2GAMEINTEXT("CHAT_VN_CHECK_ERROR") , NS_UITEXTCOLOR::NEGATIVE );
		return FALSE;
	}
#endif 
	return TRUE;
}