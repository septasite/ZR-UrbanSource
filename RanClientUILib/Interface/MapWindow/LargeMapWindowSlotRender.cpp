#include "StdAfx.h"
#include "LargeMapWindowSlotRender.h"

#include "../EngineLib/DxCommon/DxFontMan.h"

#include "../EngineUILib/GUInterface/BasicTextBox.h"
#include "../EngineUILib/GUInterface/BasicButton.h"

#include "../RanClientUILib/Interface/InnerInterface.h"
#include "../RanClientUILib/Interface/GameTextControl.h"
#include "../RanClientUILib/Interface/UITextControl.h"

#include "../RanClientLib/G-Logic/GLGaeaClient.h"
#include "../RanClientLib/G-Logic/GLCrowData.h"
#include "../RanClientLib/G-Logic/GLQuestPlay.h"
#include "../RanClientLib/G-Logic/GLQuest.h"
#include "../RanClientLib/G-Logic/GLQuestMan.h"

#include "../RanClientLib/NpcTalk/NpcDialogueSet.h"
#include "../RanClientLib/NpcTalk/NpcDialogue.h"
#include "../RanClientLib/NpcTalk/NpcDialogueCase.h"
#include "../RanClientLib/NpcTalk/NpcTalkControl.h"
#include "../RanClientLib/NpcTalk/NpcTalk.h"
#include "../RanClientLib/NpcTalk/NpcTalkCondition.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CLargeMapWindowSlotRender::CLargeMapWindowSlotRender ():
	m_pText(NULL)
{
	SecureZeroMemory ( m_pSlot, sizeof( m_pSlot ) );
}

CLargeMapWindowSlotRender::~CLargeMapWindowSlotRender ()
{
}

void CLargeMapWindowSlotRender::CreateSubControl()
{
	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 10, TRUE, _DEFAULT_FONT_SHADOW_FLAG );
	
	CString strKeyword[SLOT_SIZE] = 
	{
		"MAP_WINDOW_MONSTER_ICON_A",
		"MAP_WINDOW_MONSTER_ICON_B",
		"MAP_WINDOW_MONSTER_ICON_C",
		"MAP_WINDOW_MONSTER_ICON_D",
		"MAP_WINDOW_MONSTER_ICON_E",
		"MAP_WINDOW_MONSTER_ICON_F",
		"MAP_WINDOW_MONSTER_ICON_G",
		"MAP_WINDOW_MONSTER_ICON_H"
	};

	for( int i = 0; i < SLOT_SIZE; i++ )
	{
		m_pSlot[i] = new CUIControl;
		m_pSlot[i]->CreateSub ( this, strKeyword[i].GetString(), UI_FLAG_DEFAULT, MAP_WINDOW_MONSTER_ICON0 + i );
		m_pSlot[i]->SetTransparentOption( TRUE );
		RegisterControl ( m_pSlot[i] );
	}

	m_pGate = new CUIControl;
	m_pGate->CreateSub ( this, "MAP_WINDOW_MONSTER_ICON_GATE", UI_FLAG_DEFAULT, MAP_WINDOW_MONSTER_ICON_GATE );
	m_pGate->SetTransparentOption( TRUE );
	RegisterControl ( m_pGate );

	m_pText = new CBasicTextBox;
	m_pText->CreateSub ( this, "MAP_WINDOW_MONSTER_ICON_TEXT" );
	m_pText->SetFont ( pFont );
	m_pText->SetTextAlign ( TEXT_ALIGN_CENTER_X );	
	m_pText->SetVisibleSingle(FALSE);
	RegisterControl ( m_pText );
}

int CLargeMapWindowSlotRender::SetText(CString strText)
{
	if ( m_pText ) return m_pText->AddTextNoSplit( strText, NS_UITEXTCOLOR::DARKORANGE );
	return -1;
}

void CLargeMapWindowSlotRender::UnLoadAll()
{
	for( int i = 0; i < SLOT_SIZE; i++ )
	{
		m_pSlot[i]->SetVisibleSingle(FALSE);
		m_pSlot[i]->UnLoadTexture();
	}

    m_pGate->SetVisibleSingle(FALSE);
	m_pGate->UnLoadTexture();

	m_pText->ClearText();
}

void CLargeMapWindowSlotRender::Update ( int x ,int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	if ( m_bDispName ) m_pText->SetVisibleSingle(TRUE);
	else m_pText->SetVisibleSingle(FALSE);
}
void CLargeMapWindowSlotRender::TranslateUIMessage ( UIGUID cID, DWORD dwMsg )
{
	CUIGroup::TranslateUIMessage ( cID, dwMsg );

	switch(cID)
	{
	case MAP_WINDOW_MONSTER_ICON0:
	case MAP_WINDOW_MONSTER_ICON1:
	case MAP_WINDOW_MONSTER_ICON2:
	case MAP_WINDOW_MONSTER_ICON3:
	case MAP_WINDOW_MONSTER_ICON4:
	case MAP_WINDOW_MONSTER_ICON5:
	case MAP_WINDOW_MONSTER_ICON6:
	case MAP_WINDOW_MONSTER_ICON7:
		{
			if ( CHECK_MOUSE_IN(dwMsg))
			{
				if ( CInnerInterface::GetInstance().BEGIN_COMMON_LINEINFO_MULTI () )
				{
					CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI ( m_pCrowData->GetName(), NS_UITEXTCOLOR::GREEN );
					CInnerInterface::GetInstance().ADD_COMMON_LINEINFO_MULTI ( m_strDesc.GetString(), NS_UITEXTCOLOR::WHITE );
					CInnerInterface::GetInstance().END_COMMON_LINEINFO_MULTI ();
				}
			}
		}
		break;
	case MAP_WINDOW_MONSTER_ICON_GATE:
		{
			if ( CHECK_MOUSE_IN(dwMsg))
			{
				if ( m_szMapName ) CInnerInterface::GetInstance().SHOW_COMMON_LINEINFO( m_szMapName, NS_UITEXTCOLOR::WHITE );
			}
		}
		break;
	}
}

void CLargeMapWindowSlotRender::SetCrow( PCROWDATA pCrow,  GLCHARLOGIC *pCHAR )
{
	m_pCrowData = pCrow;

	if ( !m_pCrowData ) return;

	SetID(m_pCrowData->m_sBasic.sNativeID);

	bool bDispName = false;
	int nIndex = SLOT_SIZE;

	for( int i = 0; i < SLOT_SIZE; i++ ) m_pSlot[i]->SetVisibleSingle(FALSE);
	m_pGate->SetVisibleSingle(FALSE);

	if ( m_pCrowData->m_sBasic.m_emCrow == CROW_MOB ) 
	{
		nIndex = SLOT_MOB;
		SetType(TYPE_MOB);
	}
	else
	{
		bDispName = true;
		
		CNpcDialogueSet	pDialogueSet;
		if ( !pDialogueSet.Load(pCrow->GetTalkFile()))
		{
			nIndex = SLOT_NPC_NORMAL;
			SetType(TYPE_NPC);
		}		
		else
		{
			CNpcDialogue* pDialogue;
			pDialogue = pDialogueSet.GetDialogue(1);
			if ( pDialogue && pCHAR )
			{
				GLCHARLOGIC* pCHARLOGIC = pCHAR;
				DWORD dwIndex = pDialogue->FindConditionSatisfied(pCHARLOGIC);
				if ( dwIndex != UINT_MAX )
				{
					CNpcDialogueCase* pCase = pDialogue->GetDlgCase(dwIndex);
					CNpcDialogueCase* pDialogueCase = pCase;
					if ( pDialogueCase )
					{
						CNpcTalkControl* pNpcTalkControl = pDialogueCase->GetTalkControl ();
						if ( pNpcTalkControl )
						{
							CNpcTalkControl::NPCMAP* pMap = pNpcTalkControl->GetTalkMap ();
							CNpcTalkControl::NPCMAP_IT iter = pMap->begin();
							CNpcTalkControl::NPCMAP_IT iter_end = pMap->end();

							vector<SNpcTalk*> vecTalk;
							vecTalk.reserve( pMap->size() );

							for ( ; iter != iter_end; ++iter )
							{
								SNpcTalk* pNpcTalk = (*iter).second;
								vecTalk.push_back( pNpcTalk );
							}

							vector<SNpcTalk*>::iterator	pos = vecTalk.begin();
							vector<SNpcTalk*>::iterator	pos_end = vecTalk.end();

							bool bFound = false;
							for ( ; pos != pos_end; ++pos )
							{
								SNpcTalk* pNpcTalk = (SNpcTalk*) (*pos);
								if (!pNpcTalk->DoTEST(pCHARLOGIC))	continue;
								
								CString strAnswerTalk = pNpcTalk->GetTalk();			
								switch ( pNpcTalk->m_nACTION )
								{
									case SNpcTalk::EM_QUEST_START: 
										{
											nIndex = SLOT_NPC_QUEST_NEW;
											bFound = true;
											SetType(TYPE_NPC);
										}
										break;
									case SNpcTalk::EM_QUEST_STEP:
										{
											DWORD dwQuestID = pNpcTalk->m_dwQuestStartID[0];
											GLQUEST* pQuest = GLQuestMan::GetInstance().Find ( dwQuestID );
											if ( pQuest )
											{
												GLQuestPlay& cQuestPlay = GLGaeaClient::GetInstance().GetCharacter ()->m_cQuestPlay;
												GLQUESTPROG* pQuestProg = cQuestPlay.FindProc ( dwQuestID );
												if ( pQuestProg )
												{
													const DWORD dwSTEP = pQuestProg->m_dwSTEP;
													if ( dwSTEP == pQuest->GetSTEPNUM())
													{
														nIndex = SLOT_NPC_QUEST_DONE;
														bFound = true;
														SetType(TYPE_NPC);
													}
												}
											}
										}
										break;
									case SNpcTalk::EM_BASIC:
										{
											switch ( pNpcTalk->m_dwACTION_NO )
											{
											case SNpcTalk::EM_STORAGE:	
												{
													nIndex = SLOT_NPC_LOCKER;
													bFound = true;
													bDispName = true;
													SetType(TYPE_LOCKER);
												}
												break;
											case SNpcTalk::EM_MARKET:
												{
													nIndex = SLOT_NPC_TRADE;
													bFound = true;
													SetType(TYPE_NPC);
												}
												break;
											case SNpcTalk::EM_STARTPOINT:
												{
													nIndex = SLOT_NPC_SAVE;
													bFound = true;
													SetType(TYPE_SAVE);
												}
												break;
											case SNpcTalk::EM_BUSSTATION:
												{
													nIndex = SLOT_NPC_BUS;
													bFound = true;
													SetType(TYPE_BUS);
												}
												break;
											default:
												{
													nIndex = SLOT_NPC_NORMAL;
													SetType(TYPE_NPC);
												}
												break;
											}
										}
										break;
									default:
										{
											nIndex = SLOT_NPC_NORMAL;
											SetType(TYPE_NPC);
										}
										break;
								}

								if ( bFound ) break;
							}
						}
					}
				}
			}
		}
	}

	if ( nIndex < SLOT_SIZE && nIndex >= SLOT_MOB )	
	{
		m_pSlot[nIndex]->SetVisibleSingle(TRUE);
		m_strDesc = ID2GAMEWORD( "MAP_WINDOW_SLOT_TEXT_STATIC", nIndex);
	}

	m_bDispName = bDispName;
	SetText(m_pCrowData->GetName());
}

void CLargeMapWindowSlotRender::SetGate(const char * szMapName)
{
	for( int i = 0; i < SLOT_SIZE; i++ ) m_pSlot[i]->SetVisibleSingle(FALSE);
	m_pText->ClearText();

	m_pGate->SetVisibleSingle(TRUE);
	m_szMapName = szMapName;
	SetID(NATIVEID_NULL());
	SetType(TYPE_GATE);
}