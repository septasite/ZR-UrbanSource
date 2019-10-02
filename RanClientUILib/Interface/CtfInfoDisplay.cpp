#include "StdAfx.h"
#include "CtfInfoDisplay.h"
#include "InnerInterface.h"
#include "DxViewPort.h"

#include "GameTextControl.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "UITextControl.h"

#include "BasicTextBoxEx.h"
#include "GLCharDefine.h"

#include "GLGaeaClient.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCtfInfoDisplay::CCtfInfoDisplay ()
	:	m_pCTFThermal			( NULL )
	,	m_pCTFFacility			( NULL )
	,	m_pCTFNuclear			( NULL )
	,	m_pClubTimeLabel		( NULL )
	,	m_pClubTimeText			( NULL )
{
}

CCtfInfoDisplay::~CCtfInfoDisplay ()
{
}

void CCtfInfoDisplay::CreateSubControl ()
{
	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 9, _DEFAULT_FONT_SHADOW_FLAG );
	int	nTextAlign = TEXT_ALIGN_LEFT;

	CString strSchoolMark[] = 
	{
		"INFO_CTF_DISPLAY_AUTH_INFO_MARK_0",
		"INFO_CTF_DISPLAY_AUTH_INFO_MARK_1",
		"INFO_CTF_DISPLAY_AUTH_INFO_MARK_2"
	};

	{
		m_pCtfBack_B = new CUIControl;
		m_pCtfBack_B->CreateSub ( this, "INFO_CTF_DISPLAY_BACKGROUND_BODY", UI_FLAG_DEFAULT);	
		m_pCtfBack_B->SetVisibleSingle ( TRUE );
		RegisterControl ( m_pCtfBack_B );

		m_pCtfBack_L = new CUIControl;
		m_pCtfBack_L->CreateSub ( this, "INFO_CTF_DISPLAY_BACKGROUND_LEFT", UI_FLAG_DEFAULT);	
		m_pCtfBack_L->SetVisibleSingle ( TRUE );
		RegisterControl ( m_pCtfBack_L );

		m_pCtfBack_R = new CUIControl;
		m_pCtfBack_R->CreateSub ( this, "INFO_CTF_DISPLAY_BACKGROUND_RIGHT", UI_FLAG_DEFAULT);	
		m_pCtfBack_R->SetVisibleSingle ( TRUE );
		RegisterControl ( m_pCtfBack_R );

		m_pCtfMark0[0] = new CUIControl;
		m_pCtfMark0[0]->CreateSub ( this, "INFO_CTF_DISPLAY_AUTH_INFO_MARK_NONE0", UI_FLAG_DEFAULT);	
		m_pCtfMark0[0]->SetVisibleSingle ( TRUE );
		RegisterControl ( m_pCtfMark0[0] );

		m_pCtfMark1[0] = new CUIControl;
		m_pCtfMark1[0]->CreateSub ( this, "INFO_CTF_DISPLAY_AUTH_INFO_MARK_NONE1", UI_FLAG_DEFAULT);	
		m_pCtfMark1[0]->SetVisibleSingle ( TRUE );
		RegisterControl ( m_pCtfMark1[0] );

		m_pCtfMark2[0] = new CUIControl;
		m_pCtfMark2[0]->CreateSub ( this, "INFO_CTF_DISPLAY_AUTH_INFO_MARK_NONE2", UI_FLAG_DEFAULT);	
		m_pCtfMark2[0]->SetVisibleSingle ( TRUE );
		RegisterControl ( m_pCtfMark2[0] );
		
		for ( int i = 1; i < 4; ++i )
		{
			m_pCtfMark0[i] = CreateControl ( strSchoolMark[i-1].GetString(), nTextAlign );
			m_pCtfMark0[i]->SetLocalPos( m_pCtfMark0[0]->GetLocalPos() );
			m_pCtfMark0[i]->SetVisibleSingle ( FALSE );

			m_pCtfMark1[i] = CreateControl ( strSchoolMark[i-1].GetString(), nTextAlign );
			m_pCtfMark1[i]->SetLocalPos( m_pCtfMark1[0]->GetLocalPos() );
			m_pCtfMark1[i]->SetVisibleSingle ( FALSE );

			m_pCtfMark2[i] = CreateControl ( strSchoolMark[i-1].GetString(), nTextAlign );
			m_pCtfMark2[i]->SetLocalPos( m_pCtfMark2[0]->GetLocalPos() );
			m_pCtfMark2[i]->SetVisibleSingle ( FALSE );
		}

		m_pCtfLine0 = new CUIControl;
		m_pCtfLine0->CreateSub ( this, "INFO_CTF_DISPLAY_LINE0", UI_FLAG_DEFAULT);	
		m_pCtfLine0->SetVisibleSingle ( TRUE );
		RegisterControl ( m_pCtfLine0 );

		m_pCtfLine1 = new CUIControl;
		m_pCtfLine1->CreateSub ( this, "INFO_CTF_DISPLAY_LINE1", UI_FLAG_DEFAULT);	
		m_pCtfLine1->SetVisibleSingle ( TRUE );
		RegisterControl ( m_pCtfLine1 );

		m_pCTFThermal		= CreateStaticControl ( "INFO_CTF_DISPLAY_AUTH_INFO_LABEL0", pFont, NS_UITEXTCOLOR::WHITE, nTextAlign );
		m_pCTFFacility		= CreateStaticControl ( "INFO_CTF_DISPLAY_AUTH_INFO_LABEL1", pFont, NS_UITEXTCOLOR::WHITE, nTextAlign );
		m_pCTFNuclear		= CreateStaticControl ( "INFO_CTF_DISPLAY_AUTH_INFO_LABEL2", pFont, NS_UITEXTCOLOR::WHITE, nTextAlign );
	
		m_pClubTimeLabel = CreateStaticControl ( "INFO_CTF_DISPLAY_TEXT_TIME", pFont, NS_UITEXTCOLOR::YELLOW, TEXT_ALIGN_CENTER_X );
		m_pClubTimeText = CreateStaticControl ( "INFO_CTF_DISPLAY_TEXT_TIMER", pFont, NS_UITEXTCOLOR::YELLOW, TEXT_ALIGN_CENTER_X );
	}
	
}

CUIControl*	CCtfInfoDisplay::CreateControl ( const char* szControl, WORD wAlignFlag )
{
	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl, wAlignFlag );
	RegisterControl ( pControl );
	return pControl;
}

CBasicTextBoxEx* CCtfInfoDisplay::CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign )
{
	CBasicTextBoxEx* pStaticText = new CBasicTextBoxEx;
	pStaticText->CreateSub ( this, szControlKeyword );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );
	RegisterControl ( pStaticText );
	return pStaticText;
}

void CCtfInfoDisplay::UpdateIcon()
{	
	SCHOOLWAR_TOWER_STATUS_VEC& vecTower = GLGaeaClient::GetInstance().m_vecSwTower;

	int size = vecTower.size();
	for( int j=0;j<size;++j)
	{
		SW_SCHOOL_DATA emOWNER = vecTower[j].emHOLDER;
		switch( vecTower[j].sCROWID.wSubID )
		{
			case 1:
				{
					for( int i=0;i<4;i++)
					{
						m_pCtfMark0[i]->SetVisibleSingle ( FALSE );
					}
					switch( emOWNER )
					{
						default: m_pCtfMark0[0]->SetVisibleSingle ( TRUE );	break;
						case 0:	m_pCtfMark0[1]->SetVisibleSingle ( TRUE );	break;
						case 1:	m_pCtfMark0[2]->SetVisibleSingle ( TRUE );	break;
						case 2:	m_pCtfMark0[3]->SetVisibleSingle ( TRUE );	break;
					}		
				}break;
			case 2:
				{
					for( int i=0;i<4;i++)
					{
						m_pCtfMark1[i]->SetVisibleSingle ( FALSE );
					}
					switch( emOWNER )
					{
						default: m_pCtfMark1[0]->SetVisibleSingle ( TRUE );	break;
						case 0:	m_pCtfMark1[1]->SetVisibleSingle ( TRUE );	break;
						case 1:	m_pCtfMark1[2]->SetVisibleSingle ( TRUE );	break;
						case 2:	m_pCtfMark1[3]->SetVisibleSingle ( TRUE );	break;
					}		
				}break;
			case 3:
				{
					for( int i=0;i<4;i++)
					{
						m_pCtfMark2[i]->SetVisibleSingle ( FALSE );
					}
					switch( emOWNER )
					{
						default: m_pCtfMark2[0]->SetVisibleSingle ( TRUE );	break;
						case 0:	m_pCtfMark2[1]->SetVisibleSingle ( TRUE );	break;
						case 1:	m_pCtfMark2[2]->SetVisibleSingle ( TRUE );	break;
						case 2:	m_pCtfMark2[3]->SetVisibleSingle ( TRUE );	break;
					}		
				}break;
		}
	}
}

void CCtfInfoDisplay::ResetIcon()
{
	for( int i=0;i<4;i++)
	{
		m_pCtfMark0[i]->SetVisibleSingle ( FALSE );
		m_pCtfMark1[i]->SetVisibleSingle ( FALSE );
		m_pCtfMark2[i]->SetVisibleSingle ( FALSE );
	}

	m_pCtfMark0[0]->SetVisibleSingle ( TRUE );
	m_pCtfMark1[0]->SetVisibleSingle ( TRUE );
	m_pCtfMark2[0]->SetVisibleSingle ( TRUE );
}

void CCtfInfoDisplay::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	m_pCTFThermal->SetText("Thermal",NS_UITEXTCOLOR::WHITE);
	m_pCTFFacility->SetText("Facility",NS_UITEXTCOLOR::WHITE);
	m_pCTFNuclear->SetText("Nuclear",NS_UITEXTCOLOR::WHITE);

	m_pClubTimeLabel->SetText("Tyranny Under Way",NS_UITEXTCOLOR::YELLOW);
}

void CCtfInfoDisplay::UpdateClubTime( float fBATTLETime )
{
	CString strCombine;

	m_pClubTimeText->ClearText();
	strCombine.Format ( ID2GAMEWORD( "CTF_RESULT_TEXT", 2 ), (DWORD)fBATTLETime/3600,(DWORD)fBATTLETime/60, (DWORD)fBATTLETime%60 );
	m_pClubTimeText->SetText(strCombine, NS_UITEXTCOLOR::YELLOW);
	
	m_pClubTimeText->SetVisibleSingle( TRUE );
}