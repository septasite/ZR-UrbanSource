#include "StdAfx.h"

#include "CountMsg.h"
#include "InnerInterface.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CCountMsg::CCountMsg()
	: m_nCount(0)
	, m_nRandomNumber(0)
	, m_nRandomNumberResult(0)
	, m_fElapsedTime(0.0)
{
	memset ( m_pTEN, 0, sizeof( m_pTEN ) );
	memset ( m_pONE, 0, sizeof( m_pONE ) );
	memset ( m_pTENResult, 0, sizeof( m_pTENResult ) );
	memset ( m_pONEResult, 0, sizeof( m_pONEResult ) );
}

CCountMsg::~CCountMsg ()
{
}

void CCountMsg::CreateSubControl()
{
	CString strNUMBER;
	for ( int i = 0; i < 10; ++i )
	{
		strNUMBER.Format( "DAMAGE_DISPLAY_NUMBER_RED_%d", i );
		m_pTEN[i] = CreateControl ( strNUMBER.GetString() );
		m_pONE[i] = CreateControl ( strNUMBER.GetString() );
	}
	CString strNUMBERResult;
	for ( int i = 0; i < 10; ++i )
	{
		strNUMBERResult.Format( "DAMAGE_DISPLAY_NUMBER_RED_%d", i );
		m_pTENResult[i] = CreateControl ( strNUMBERResult.GetString() );
		m_pONEResult[i] = CreateControl ( strNUMBERResult.GetString() );
	}
}

CUIControl*	CCountMsg::CreateControl( CONST TCHAR* szControl )
{
	GASSERT( szControl );

	CUIControl* pControl = new CUIControl;
	pControl->CreateSub ( this, szControl );
	pControl->SetVisibleSingle ( FALSE );
	RegisterControl ( pControl );

	return pControl;
}

void CCountMsg::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
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
				m_pTENResult[i]->SetVisibleSingle( FALSE );
				m_pONEResult[i]->SetVisibleSingle( FALSE );
			}

			for( int i=0; i<10; ++i )
			{
				m_pTEN[i]->SetVisibleSingle( FALSE );
				m_pONE[i]->SetVisibleSingle( FALSE );
			}

			// 남은 시간으로 숫자를 구성하고 출력한다.
			int nTen = m_nRandomNumber / 10;
			int nOne = m_nRandomNumber % 10;
			
			const UIRECT & tenLRect = m_pTEN[nTen]->GetLocalPos();
			const UIRECT & tenGRect = m_pTEN[nTen]->GetGlobalPos();
			UIRECT oneRect = m_pONE[nOne]->GetGlobalPos();
			oneRect.left = tenGRect.left + tenLRect.sizeX;
			m_pONE[nOne]->SetGlobalPos( oneRect );

			m_pTEN[nTen]->SetVisibleSingle( TRUE );
			m_pONE[nOne]->SetVisibleSingle( TRUE );

			int nRandomNumber = rand() % 100;
			m_nRandomNumber = nRandomNumber;
			--m_nCount;
			m_fElapsedTime = 0.0;
		}
	}
	else
	{
			for( int i=0; i<10; ++i )
			{
				m_pTEN[i]->SetVisibleSingle( FALSE );
				m_pONE[i]->SetVisibleSingle( FALSE );
			}

			for( int i=0; i<10; ++i )
			{
				m_pTENResult[i]->SetVisibleSingle( FALSE );
				m_pONEResult[i]->SetVisibleSingle( FALSE );
			}

			// 남은 시간으로 숫자를 구성하고 출력한다.
			int nTenResult = m_nRandomNumberResult / 10;
			int nOneResult = m_nRandomNumberResult % 10;
			
			const UIRECT & tenLRectResult = m_pTENResult[nTenResult]->GetLocalPos();
			const UIRECT & tenGRectResult = m_pTENResult[nTenResult]->GetGlobalPos();
			UIRECT oneRectResult = m_pONEResult[nOneResult]->GetGlobalPos();
			oneRectResult.left = tenGRectResult.left + tenLRectResult.sizeX;
			m_pONEResult[nOneResult]->SetGlobalPos( oneRectResult );

			m_pTENResult[nTenResult]->SetVisibleSingle( TRUE );
			m_pONEResult[nOneResult]->SetVisibleSingle( TRUE );
			--m_nCount;
			m_fElapsedTime = 0.0;
	}
}

void CCountMsg::SetCount( bool bVisible, int nRandomNumber )
{
	if ( bVisible )
	{
		m_nRandomNumberResult = nRandomNumber;
		m_nCount = 10;
	}
}