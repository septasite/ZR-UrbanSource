#include "StdAfx.h"
#include "./PetWindow.h"

#include "BasicLineBox.h"
#include "d3dfont.h"
#include "GameTextControl.h"
#include "ItemImage.h"
#include "InnerInterface.h"
#include "ItemMove.h"
#include "BasicComboBox.h"
#include "BasicComboBoxRollOver.h"
#include "UITextControl.h"
#include "GLGaeaClient.h"
#include "BasicTextButton.h"
#include "PetQuickSkillSlot.h"
#include "GLItemMan.h"

#include "../EngineUIlib/GUInterface/BasicTextBox.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "../EngineUIlib/GUInterface/BasicProgressBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CPetWindow::CPetWindow ()
	: m_pPetName(NULL)
	, m_pPetType(NULL)
	, m_pMouseOver(NULL)
	, m_pSatietyText(NULL)
	, m_pLoyaltyText(NULL)
	, m_pSatiety(NULL)
	, m_pLoyalty(NULL)
	, m_pcbSkill_A(NULL)
	, m_pcbSkillRollOver_A(NULL)
	, m_pcbSkill_B(NULL)
	, m_pcbSkillRollOver_B(NULL)
	, pTextBoxSkill_B(NULL)
	, m_RollOverID(NO_ID)
	, m_nSatietyBack(0)
	, m_wLoyaltyBack(USHRT_MAX)
{
	SecureZeroMemory( m_pSlotDisplay, sizeof(m_pSlotDisplay) );
	SecureZeroMemory( m_pSlotImage, sizeof(m_pSlotImage) );
}

CPetWindow::~CPetWindow ()
{
}

void CPetWindow::CreateSubControl ()
{
	CD3DFontPar* pFont9 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, _DEFAULT_FONT_FLAG );
	CD3DFontPar* pFont8 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 8, D3DFONT_SHADOW | D3DFONT_ASCII );

	{
		CBasicLineBox* pBasicLineBox = new CBasicLineBox;
		pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_LIST", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		pBasicLineBox->CreateBaseBoxQuestList ( "PET_BG_LLINEBOX" );
		RegisterControl ( pBasicLineBox );

		pBasicLineBox = new CBasicLineBox;
		pBasicLineBox->CreateSub ( this, "BASIC_LINE_BOX_QUEST_LIST", UI_FLAG_XSIZE | UI_FLAG_YSIZE );
		pBasicLineBox->CreateBaseBoxQuestList ( "PET_BG_RLINEBOX" );
		RegisterControl ( pBasicLineBox );
	}

	{
		CString strPetSlot[SLOT_IMAGE_SIZE] = 
		{
			"PET_SLOT_IMAGE0",
			"PET_SLOT_IMAGE1",
		};

		CString strPetSlotOver[SLOT_IMAGE_SIZE] = 
		{
			"PET_SLOT_OVER_IMAGE0",
			"PET_SLOT_OVER_IMAGE1",
		};

		for ( int i = 0; i < SLOT_IMAGE_SIZE; i++ )
		{
			m_pSlotImage[i] = CreateItemImage( strPetSlot[i].GetString(), SLOT_IMAGE_TYPE1 + i );
			m_pSlotDisplay[i] = CreateControl( strPetSlotOver[i].GetString() );
			m_pSlotDisplay[i]->SetVisibleSingle( FALSE );
		}

		m_pMouseOver = CreateControl( "ITEM_MOUSE_OVER" );
		m_pMouseOver->SetVisibleSingle( FALSE );
	}

	{
		CBasicTextBox* pTextBox(NULL);

		// 펫 이름
		pTextBox = CreateTextBox ( "PET_NAME_STATIC", pFont9 );
		pTextBox->AddText ( ID2GAMEWORD("PET_TEXT_STATIC",0) );

		m_pPetName = CreateTextBox ( "PET_NAME_TEXTBOX", pFont9 );
	
		// 펫 종류
		pTextBox = CreateTextBox ( "PET_TYPE_STATIC", pFont9 );
		pTextBox->AddText ( ID2GAMEWORD("PET_TEXT_STATIC",1) );

		m_pPetType = CreateTextBox ( "PET_TYPE_TEXTBOX", pFont9 );

		// 포만
		pTextBox = CreateTextBox ( "PET_SATIETY_STATIC", pFont9 );
		pTextBox->AddText ( ID2GAMEWORD("PET_TEXT_STATIC",2) );

		pTextBox = CreateTextBox ( "PET_SKILL_A_STATIC", pFont9 );
		pTextBox->AddText ( ID2GAMEWORD("PET_TEXT_STATIC",6) );

		pTextBoxSkill_B = CreateTextBox ( "PET_SKILL_B_STATIC", pFont9 );
		pTextBoxSkill_B->AddText ( ID2GAMEWORD("PET_TEXT_STATIC",7) );

		CBasicProgressBar* pSatiety = new CBasicProgressBar;
		pSatiety->CreateSub ( this, "PET_SATIETY_PROGRESSBAR" );
		pSatiety->CreateOverImage ( "PET_SATIETY_PROGRESSBAR_OVERIMAGE" );
		RegisterControl ( pSatiety );
		m_pSatiety = pSatiety;

		CBasicTextBox* pSatietyText = new CBasicTextBox;
		pSatietyText->CreateSub( this, "PET_SATIETY_TEXT", UI_FLAG_DEFAULT, SATIETY_TEXT );
		pSatietyText->SetFont( pFont8 );
		pSatietyText->SetTextAlign ( TEXT_ALIGN_CENTER_X );
		RegisterControl ( pSatietyText );
		m_pSatietyText = pSatietyText;
	
		CBasicTextButton* pButton = new CBasicTextButton;
		pButton->CreateSub ( this, "BASIC_TEXT_BUTTON23", UI_FLAG_XSIZE, SKILL_BUTTON );
		pButton->CreateBaseButton ( "PET_SKILL_BUTTON", CBasicTextButton::SIZE23_NEW, CBasicButton::CLICK_FLIP, ID2GAMEWORD("PET_TEXT_STATIC",4) );
		RegisterControl ( pButton );

		CBasicComboBox * pComboBox_A = new CBasicComboBox;
		pComboBox_A->CreateSub( this, "BASIC_COMBOBOX", UI_FLAG_XSIZE, SKILL_COMBO_OPEN_A );
		pComboBox_A->CreateBaseComboBox( "PET_SKILL_COMBO_OPEN_A" );			
		RegisterControl( pComboBox_A );
		m_pcbSkill_A = pComboBox_A;

		CBasicComboBox * pComboBox_B = new CBasicComboBox;
		pComboBox_B->CreateSub( this, "BASIC_COMBOBOX", UI_FLAG_XSIZE, SKILL_COMBO_OPEN_B );
		pComboBox_B->CreateBaseComboBox( "PET_SKILL_COMBO_OPEN_B" );			
		RegisterControl( pComboBox_B );
		m_pcbSkill_B = pComboBox_B;

		CBasicComboBoxRollOver * pComboBoxRollOver_A = new CBasicComboBoxRollOver;
		pComboBoxRollOver_A->CreateSub( this, "BASIC_COMBOBOX_ROLLOVER", UI_FLAG_XSIZE | UI_FLAG_YSIZE, SKILL_COMBO_ROLLOVER_A );
		pComboBoxRollOver_A->CreateBaseComboBoxRollOver( "PET_SKILL_COMBO_ROLLOVER_A" );
		pComboBoxRollOver_A->SetVisibleSingle( FALSE );
		RegisterControl( pComboBoxRollOver_A );
		m_pcbSkillRollOver_A = pComboBoxRollOver_A;

		CBasicComboBoxRollOver * pComboBoxRollOver_B = new CBasicComboBoxRollOver;
		pComboBoxRollOver_B->CreateSub( this, "BASIC_COMBOBOX_ROLLOVER", UI_FLAG_XSIZE | UI_FLAG_YSIZE, SKILL_COMBO_ROLLOVER_B );
		pComboBoxRollOver_B->CreateBaseComboBoxRollOver( "PET_SKILL_COMBO_ROLLOVER_B" );
		pComboBoxRollOver_B->SetVisibleSingle( FALSE );
		RegisterControl( pComboBoxRollOver_B );
		m_pcbSkillRollOver_B = pComboBoxRollOver_B;


		pPetSkillSlot_A = new CPetQuickSkillSlot;
		pPetSkillSlot_A->CreateSub( this, "PET_SKILL_SLOT_A", UI_FLAG_DEFAULT, PET_SKILL_SLOT_A );
		pPetSkillSlot_A->CreateSubControl();
		RegisterControl ( pPetSkillSlot_A );

		pPetSkillSlot_B = new CPetQuickSkillSlot;
		pPetSkillSlot_B->CreateSub( this, "PET_SKILL_SLOT_B", UI_FLAG_DEFAULT, PET_SKILL_SLOT_B );
		pPetSkillSlot_B->CreateSubControl();
		RegisterControl ( pPetSkillSlot_B );
	}
}

CBasicTextBox*	CPetWindow::CreateTextBox ( char* szKeyword, CD3DFontPar* pFont )
{
	CBasicTextBox* pTextBox = new CBasicTextBox;
	pTextBox->CreateSub ( this, szKeyword );
	pTextBox->SetFont ( pFont );
	RegisterControl ( pTextBox );

	return pTextBox;
}

CUIControl*	CPetWindow::CreateControl ( const char* szControl )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	RegisterControl ( pControl );

	return pControl;
}

CItemImage*	CPetWindow::CreateItemImage ( const char* szControl, UIGUID ControlID )
{
	CItemImage* pItemImage = new CItemImage;
	pItemImage->CreateSub ( this, szControl, UI_FLAG_DEFAULT, ControlID );
	pItemImage->CreateSubControl ();
	RegisterControl ( pItemImage );

	return pItemImage;
}

EMSUIT CPetWindow::IMAGE2EMSLOT ( UIGUID ControlID )
{
	switch ( ControlID )
	{	
	case SLOT_IMAGE_TYPE1:	return SUIT_PET_A;
	case SLOT_IMAGE_TYPE2:	return SUIT_PET_B;
	}

	GASSERT ( 0 && "CPetWindow::IMAGE2EMSLOT(), 범위를 벗어납니다." );
	return SUIT_NSIZE;
}

void CPetWindow::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if( !GLGaeaClient::GetInstance().GetPetClient()->IsVALID() )
	{
		CInnerInterface::GetInstance().HideGroup( GetWndID() );
		return ;
	}

	if( m_RollOverID == NO_ID )
	{
		if( m_pMouseOver ) m_pMouseOver->SetVisibleSingle ( FALSE );

		//	스냅, 스킬 이미지 붙이기
		CItemMove* pItemMove = CInnerInterface::GetInstance().GetItemMove ();
		SNATIVEID sHOLD_ITEM_ID(false);
		if ( pItemMove ) sHOLD_ITEM_ID = pItemMove->GetItem();

		for( int i=0; i<SLOT_IMAGE_SIZE; ++i )
		{
			SITEMCUSTOM & sItemCustomOld = m_ItemCustomArray[i];
			SITEMCUSTOM & sItemCustom = GLGaeaClient::GetInstance().GetPetClient()->m_PutOnItems[i];

			if ( sItemCustom != sItemCustomOld )
			{		
				if ( sItemCustom.sNativeID != NATIVEID_NULL() )
				{
					LoadItem ( i, sItemCustom );
				}
				else
				{
					UnLoadItem ( i );
				}
			}

			m_pSlotDisplay[i]->SetVisibleSingle ( FALSE );

			if( sHOLD_ITEM_ID != NATIVEID_NULL() )
			{
				// 장착될 위치 표시
				if( GLGaeaClient::GetInstance().GetPetClient()->CheckSlotItem( sHOLD_ITEM_ID, IMAGE2EMSLOT( i + SLOT_IMAGE_TYPE1 ) ) )
				{
					const UIRECT& rcImagePos = m_pSlotImage[i]->GetGlobalPos ();
					D3DXVECTOR2 vPos( rcImagePos.left, rcImagePos.top );

					m_pSlotDisplay[i]->SetVisibleSingle( TRUE );
				}
			}
		}

		CUIWindowEx::Update( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
	}
	else
	{
		ResetMessageEx ();

		CUIControl::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

		CUIControl* pControl = m_ControlContainer.FindControl ( m_RollOverID );
		if ( !pControl )
		{
			GASSERT ( 0 && "심각한 오류, 노드가 널입니다." );
			return ;
		}

		pControl->Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

		DWORD dwControlMsg = pControl->GetMessageEx ();
		NS_UIDEBUGSET::BlockBegin ();
		if ( dwControlMsg ) TranslateUIMessage ( m_RollOverID, dwControlMsg );
		NS_UIDEBUGSET::BlockEnd ();

		//	스크롤바에 관계된 메시지가 아니고		
		if ( !(dwControlMsg & UI_MSG_COMBOBOX_ROLLOVER_SCROLL) )
		{
			DWORD dwMsg = GetMessageEx ();
			if ( dwMsg & UIMSG_LB_UP )
			{
				if ( !m_bFirstLBUP )
				{
					m_RollOverID = NO_ID;
					pControl->SetVisibleSingle ( FALSE );					
				}
				m_bFirstLBUP = FALSE;
			}
		}
	}

	for( unsigned s=0; s<PETSLOT_SIZE;++s){
		SNATIVEID sNativeID = GLGaeaClient::GetInstance().GetPetClient()->m_sActiveSkillID[s];
		if(s==0)pPetSkillSlot_A->UpdateSlot( sNativeID );
		if(s==1)pPetSkillSlot_B->UpdateSlot( sNativeID );
	}

	int nFull = GLGaeaClient::GetInstance().GetPetClient()->m_nFull;
	SetSatiety( nFull );
}

void CPetWindow::TranslateUIMessage ( UIGUID ControlID, DWORD dwMsg )
{
	CUIWindowEx::TranslateUIMessage ( ControlID, dwMsg );

	switch ( ControlID )
	{
	case ET_CONTROL_TITLE:
	case ET_CONTROL_TITLE_F:
		{
			if ( (dwMsg & UIMSG_LB_DUP) && CHECK_MOUSE_IN ( dwMsg ) )
			{
				CInnerInterface::GetInstance().SetDefaultPosInterface( PET_WINDOW );
			}
		}
		break;
	case SLOT_IMAGE_TYPE1:
	case SLOT_IMAGE_TYPE2:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{	
				int nIndex = ControlID - SLOT_IMAGE_TYPE1;

				if ( !CInnerInterface::GetInstance().IsFirstItemSlot () ) return ;

				CItemMove* pItemMove = CInnerInterface::GetInstance().GetItemMove ();
				if ( !pItemMove )
				{
					GASSERT ( 0 && "CItemMove가 널입니다." );
					return ;
				}

				if ( pItemMove->GetItem () != NATIVEID_NULL () )
				{
					const UIRECT& rcSlotPos = m_pSlotImage[nIndex]->GetGlobalPos ();
					pItemMove->SetGlobalPos ( rcSlotPos );						

					AddMessageEx ( UIMSG_MOUSEIN_WEARSLOT | UIMSG_TOTOPPARENT );
				}				

				//	마우스 표시 테두리
				if ( pItemMove->GetItem () == NATIVEID_NULL () && m_pSlotImage[nIndex]->GetItem () != NATIVEID_NULL () )
				{
					const UIRECT& rcImagePos = m_pSlotImage[nIndex]->GetGlobalPos ();
					m_pMouseOver->SetGlobalPos ( rcImagePos );
					m_pMouseOver->SetVisibleSingle ( TRUE );
				}

				if ( dwMsg & UIMSG_LB_UP )
				{
					GLGaeaClient::GetInstance().GetPetClient()->ReqChangeAccessory( IMAGE2EMSLOT(ControlID) );
				}

				if ( dwMsg & UIMSG_RB_UP )
				{
					GLGaeaClient::GetInstance().GetPetClient()->ReqRemoveSlotItem( IMAGE2EMSLOT(ControlID) );
				}

				if( m_ItemCustomArray[nIndex].sNativeID != NATIVEID_NULL () )
				{
					CInnerInterface::GetInstance().SHOW_ITEM_INFO ( m_ItemCustomArray[nIndex], FALSE, FALSE, FALSE, USHRT_MAX, USHRT_MAX );
				}
			}
		}
		break;

	case SKILL_BUTTON:
		{
			if( CHECK_MOUSEIN_LBUPLIKE( dwMsg ) )
			{
				if ( !CInnerInterface::GetInstance().IsVisibleGroup( PET_SKILL_WINDOW ) )
				{
					CInnerInterface::GetInstance().ShowGroupFocus( PET_SKILL_WINDOW );
				}
				else
				{
					CInnerInterface::GetInstance().HideGroup( PET_SKILL_WINDOW );
				}
			}
		}
		break;

	case SKILL_COMBO_OPEN_A:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( dwMsg & UIMSG_LB_DOWN )
				{
					m_pcbSkillRollOver_A->SetVisibleSingle( TRUE );
					m_pcbSkillRollOver_A->SetScrollPercent ( 0.0f );
					
					m_RollOverID = SKILL_COMBO_ROLLOVER_A;
					m_bFirstLBUP = TRUE;
				}
			}
		}
		break;

	case SKILL_COMBO_OPEN_B:
		{
			if ( CHECK_MOUSE_IN ( dwMsg ) )
			{
				if ( dwMsg & UIMSG_LB_DOWN )
				{
					m_pcbSkillRollOver_B->SetVisibleSingle( TRUE );
					m_pcbSkillRollOver_B->SetScrollPercent ( 0.0f );
					
					m_RollOverID = SKILL_COMBO_ROLLOVER_B;
					m_bFirstLBUP = TRUE;
				}
			}
		}
		break;

	case SKILL_COMBO_ROLLOVER_A:
		{
			if ( dwMsg & UI_MSG_COMBOBOX_ROLLOVER_SCROLL )
			{				
				DWORD dwMsg = GetMessageEx ();
				dwMsg &= ~UI_MSG_COMBOBOX_ROLLOVER_SCROLL;
				ResetMessageEx ();
				AddMessageEx ( dwMsg );

				break;
			}

			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{				
				int nIndex = m_pcbSkillRollOver_A->GetSelectIndex ();
				if ( nIndex < 0 ) return ;

				SNATIVEID sID( m_pcbSkillRollOver_A->GetTextData( nIndex ) );

				if (GLGaeaClient::GetInstance().GetPetClient()->m_sActiveSkillID[PETSLOT_01] == sID)
					nIndex = 0;
				if( nIndex > 0 )
				{
					// 쿨 타임이 끝나지 않은 스킬을 선택하려는지 체크
					if( !GLGaeaClient::GetInstance().GetPetClient()->CheckSkill( sID ) )
					{
						return;
					}
				}

				CString & strText = m_pcbSkillRollOver_A->GetSelectText( nIndex );
				m_pcbSkill_A->SetText( strText );

				if( nIndex == 0 ) sID = NATIVEID_NULL();

				GLGaeaClient::GetInstance().GetPetClient()->ReqChangeActiveSkill( sID, PETSLOT_01);
			}
		}
		break;

	case SKILL_COMBO_ROLLOVER_B:
		{
			if ( !GLGaeaClient::GetInstance().GetPetClient()->m_bDualSkill ) return;
			if ( dwMsg & UI_MSG_COMBOBOX_ROLLOVER_SCROLL )
			{				
				DWORD dwMsg = GetMessageEx ();
				dwMsg &= ~UI_MSG_COMBOBOX_ROLLOVER_SCROLL;
				ResetMessageEx ();
				AddMessageEx ( dwMsg );

				break;
			}

			if ( CHECK_MOUSEIN_LBUPLIKE ( dwMsg ) )
			{				
				int nIndex = m_pcbSkillRollOver_B->GetSelectIndex ();
				if ( nIndex < 0 ) return ;

				SNATIVEID sID( m_pcbSkillRollOver_B->GetTextData( nIndex ) );

				if (GLGaeaClient::GetInstance().GetPetClient()->m_sActiveSkillID[PETSLOT_02] == sID)
					nIndex = 0;
				if( nIndex > 0 )
				{
					// 쿨 타임이 끝나지 않은 스킬을 선택하려는지 체크
					if( !GLGaeaClient::GetInstance().GetPetClient()->CheckSkill( sID ) )
					{
						return;
					}
				}

				CString & strText = m_pcbSkillRollOver_B->GetSelectText( nIndex );
				m_pcbSkill_B->SetText( strText );

				if( nIndex == 0 ) sID = NATIVEID_NULL();
				
				//dmk14 | 11-21-16 | dual pet skill
				GLGaeaClient::GetInstance().GetPetClient()->ReqChangeActiveSkill( sID, PETSLOT_02 );
			}
		}
		break;
	}
}

void CPetWindow::SetName( const std::string & strName )
{
	GASSERT( m_pPetName );
	m_pPetName->SetOneLineText( strName.c_str() );
}

void CPetWindow::SetType( const std::string & strType )
{
	GASSERT( m_pPetType );
	m_pPetType->SetOneLineText( strType.c_str() );
}

void CPetWindow::SetSkillCombo()
{
	GASSERT( m_pcbSkillRollOver_A );
	GASSERT( m_pcbSkillRollOver_B );
	m_pcbSkillRollOver_A->ClearText();
	m_pcbSkillRollOver_B->ClearText();

	int nIndex = m_pcbSkillRollOver_A->AddText( ID2GAMEWORD("PET_TEXT_STATIC",5) );
	m_pcbSkillRollOver_A->SetTextData( nIndex, SNATIVEID( false ).dwID );

	int nIndex2 = m_pcbSkillRollOver_B->AddText( ID2GAMEWORD("PET_TEXT_STATIC",5) );
	m_pcbSkillRollOver_B->SetTextData( nIndex2, SNATIVEID( false ).dwID );

	PETSKILL_MAP & mapPetSkill = GLGaeaClient::GetInstance().GetPetClient()->m_ExpSkills;
	
	PETSKILL_MAP_ITER pos = mapPetSkill.begin();
	PETSKILL_MAP_ITER end = mapPetSkill.end();
	for ( ; pos!=end; ++pos )
	{
		PETSKILL petSkill( (*pos).second );

		PGLSKILL pSKILL = GLSkillMan::GetInstance().GetData( petSkill.sNativeID );
		if( !pSKILL ) continue;

		int nIndex = m_pcbSkillRollOver_A->AddText( pSKILL->GetName() );
		m_pcbSkillRollOver_A->SetTextData( nIndex, petSkill.sNativeID.dwID );

		int nIndex2 = m_pcbSkillRollOver_B->AddText( pSKILL->GetName() );
		m_pcbSkillRollOver_B->SetTextData( nIndex2, petSkill.sNativeID.dwID );
	}

	SNATIVEID & sID = GLGaeaClient::GetInstance().GetPetClient()->m_sActiveSkillID[PETSLOT_01];
	PGLSKILL pSKILL = GLSkillMan::GetInstance().GetData( sID );
	if( !pSKILL )
	{
		m_pcbSkill_A->SetText( ID2GAMEWORD("PET_TEXT_STATIC",5) );
	}
	else
	{
		m_pcbSkill_A->SetText( pSKILL->GetName() );
	}

	SNATIVEID & sID2 = GLGaeaClient::GetInstance().GetPetClient()->m_sActiveSkillID[PETSLOT_02];
	PGLSKILL pSKILL2 = GLSkillMan::GetInstance().GetData( sID2 );
	if( !pSKILL2 )
	{
		m_pcbSkill_B->SetText( ID2GAMEWORD("PET_TEXT_STATIC",5) );
	}
	else
	{
		m_pcbSkill_B->SetText( pSKILL2->GetName() );
	}
}

void CPetWindow::RefreshSkillSlot()
{
	m_pcbSkill_B->SetVisibleSingle( TRUE );
	pPetSkillSlot_B->SetVisibleSingle( TRUE );
	pTextBoxSkill_B->SetVisibleSingle( TRUE );
}

void CPetWindow::SetSatiety( int nNOW )
{
	GASSERT( m_pSatietyText && m_pSatiety );

	if ( m_nSatietyBack != nNOW )
	{
		m_nSatietyBack = nNOW;

		CString strTemp;
		strTemp.Format( "%.2f%%", nNOW/10.0f );

		m_pSatietyText->SetOneLineText( strTemp, NS_UITEXTCOLOR::WHITE );
		m_pSatiety->SetPercent( nNOW/1000.0f ); //< 입력값은 0 과 1 사이의 값이다.
	}
}

void CPetWindow::SetVisibleSingle ( BOOL bVisible )
{
	CUIWindowEx::SetVisibleSingle ( bVisible );

	if( bVisible )
	{
		std::string strPetName = GLGaeaClient::GetInstance().GetPetClient()->m_szName;
		SetName( strPetName );

		PETTYPE emTYPE = GLGaeaClient::GetInstance().GetPetClient()->m_emTYPE;

		if( emTYPE == PETTYPE_NONE )
		{
			SetType( ID2GAMEWORD("PET_TEXT_STATIC",5) );
		}
		else 
		{
			SetType( COMMENT::PET_TYPE[emTYPE] );
		}

		SetSkillCombo();

		if ( !GLGaeaClient::GetInstance().GetPetClient()->m_bDualSkill )
		{
			m_pcbSkill_B->SetVisibleSingle( FALSE );
			pPetSkillSlot_B->SetVisibleSingle( FALSE );
			pTextBoxSkill_B->SetVisibleSingle( FALSE );
		}
		else
		{
			m_pcbSkill_B->SetVisibleSingle( TRUE );
			pPetSkillSlot_B->SetVisibleSingle( TRUE );
			pTextBoxSkill_B->SetVisibleSingle( TRUE );
		}
	}
	else
	{
		m_pcbSkillRollOver_A->SetVisibleSingle ( FALSE );
		m_pcbSkillRollOver_B->SetVisibleSingle ( FALSE );
		CInnerInterface::GetInstance().HideGroup( PET_SKILL_WINDOW );
	}
}

void CPetWindow::LoadItem ( int nIndex, SITEMCUSTOM& ref_sItemCustom )
{
	m_ItemCustomArray[nIndex] = ref_sItemCustom;

	SITEM* pItemData = GLItemMan::GetInstance().GetItem ( ref_sItemCustom.sNativeID );
	m_pSlotImage[nIndex]->SetItem ( pItemData->sBasicOp.sICONID, pItemData->GetInventoryFile() );
}

void CPetWindow::UnLoadItem ( int nIndex )
{
	m_ItemCustomArray[nIndex].sNativeID = NATIVEID_NULL ();
	m_pSlotImage[nIndex]->ResetItem ();
}