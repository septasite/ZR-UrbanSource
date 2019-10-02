#include "StdAfx.h"

#include "CountMsgCD.h"
#include "InnerInterface.h"
#include "GameTextControl.h"
#include "UITextControl.h"
#include "../../EngineLib/DxCommon/DxFontMan.h"
#include "../../EngineLib/DxCommon/d3dfont.h"
#include "../EngineUILib/GUInterface/BasicTextBox.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCountMsgCD::CCountMsgCD()
	: m_nCount(0)
	, m_nRandomNumber(0)
	, m_fElapsedTime(0.0)
	, m_pCoolDownText( NULL )
{
	memset ( m_pTEN, 0, sizeof( m_pTEN ) );
	memset ( m_pONE, 0, sizeof( m_pONE ) );
}

CCountMsgCD::~CCountMsgCD ()
{
}

void CCountMsgCD::CreateSubControl()
{
	CD3DFontPar* pFont13 = DxFontMan::GetInstance().LoadDxFont ( _DEFAULT_FONT, 15, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );

	m_pCoolDownText	= CreateStaticControl( "SLOTEVENT_COOLDOWN_TEXT", pFont13 , NS_UITEXTCOLOR::DARKORANGE, TEXT_ALIGN_CENTER_X | TEXT_ALIGN_CENTER_Y );

	CString strNUMBER;
	for ( int i = 0; i < 10; ++i )
	{
		strNUMBER.Format( "CD_DISPLAY_NUMBER_RED_%d", i );
		m_pTEN[i] = CreateControl ( strNUMBER.GetString() );
		m_pONE[i] = CreateControl ( strNUMBER.GetString() );
	}
}

CUIControl*	CCountMsgCD::CreateControl( CONST TCHAR* szControl )
{
	GASSERT( szControl );

	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	pControl->SetVisibleSingle ( FALSE );
	RegisterControl ( pControl );

	return pControl;
}

CBasicTextBox* CCountMsgCD::CreateStaticControl ( char* szControlKeyword, CD3DFontPar* pFont, D3DCOLOR dwColor, int nAlign )
{
	CBasicTextBox* pStaticText = new CBasicTextBox;
	pStaticText->CreateSub ( this, szControlKeyword );
	pStaticText->SetFont ( pFont );
	pStaticText->SetTextAlign ( nAlign );
	RegisterControl ( pStaticText );
	return pStaticText;
}

void CCountMsgCD::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );

	if( m_nCount >= 0 )
	{
		if( m_fElapsedTime <= 1.0f )
		{
			m_fElapsedTime += fElapsedTime;
		}
		else
		{
			for( int i=0; i<10; ++i )
			{
				m_pTEN[i]->SetVisibleSingle( FALSE );
				m_pONE[i]->SetVisibleSingle( FALSE );
			}

			// 남은 시간으로 숫자를 구성하고 출력한다.
			int nTen = m_nCount / 10;
			int nOne = m_nCount % 10;
			
			const UIRECT & tenLRect = m_pTEN[nTen]->GetLocalPos();
			const UIRECT & tenGRect = m_pTEN[nTen]->GetGlobalPos();
			UIRECT oneRect = m_pONE[nOne]->GetGlobalPos();
			oneRect.left = tenGRect.left + tenLRect.sizeX;
			m_pONE[nOne]->SetGlobalPos( oneRect );

			//m_pTEN[nTen]->SetVisibleSingle( TRUE );
			//m_pONE[nOne]->SetVisibleSingle( TRUE );

			m_pCoolDownText->SetVisibleSingle(TRUE);
			--m_nCount;
			CString strCombine;
			strCombine.Format("%d seconds(s) to select your slot!", m_nCount+1);
			m_pCoolDownText->SetText(strCombine, NS_UITEXTCOLOR::DARKORANGE);
			m_fElapsedTime = 0.0;
		}

	}
	//else CInnerInterface::GetInstance().HideGroup( GetWndID() );
}

void CCountMsgCD::SetCount( bool bVisible )
{
	//if( nCount < 0 ) m_nCount = 0;
	//if( nCount > 99 ) m_nCount = 99;

	//m_nCount = rand() % 100;

	if ( bVisible )
	{
		m_nCount = 10;
	}
	//m_nCount = nCount;
}