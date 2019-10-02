#include "StdAfx.h"
#include "killTimeDisplay.h"
#include "GLGaeaClient.h"
#include "killTimeUnit.h"
#include "ModalWindow.h"
#include "ModalCallerID.h"
#include "GameTextControl.h"
#include "InnerInterface.h"
#include "d3dfont.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CkillTimeDisplay::CkillTimeDisplay () :
	m_NEWID ( KILLTIME_UNIT ),
		m_fTimer(0.0f)
{
}

CkillTimeDisplay::~CkillTimeDisplay ()
{
}

void CkillTimeDisplay::CreateSubControl ()
{	
	const CString strKeyword = "KILL_TIME_UNIT";
	CString strCombine;

	for ( int i = 0; i < KILLFACT_SIZE; i++ )
	{
		strCombine.Format ( "%s%d", strKeyword, i );
		CUIControl* pDummyControl = new CUIControl;
		pDummyControl->CreateSub ( this, strCombine.GetString(), UI_FLAG_DEFAULT, KILLTIME_DUMMY_BASE + i );
		RegisterControl ( pDummyControl );

		m_pkillUnitDummy[i] = pDummyControl;
	}
}

void CkillTimeDisplay::Update ( int x, int y, BYTE LB, BYTE MB, BYTE RB, int nScroll, float fElapsedTime, BOOL bFirstControl )
{
	if ( !IsVisible () ) return ;

	GLCharacter* const pCharacter = GLGaeaClient::GetInstance().GetCharacter();
	if ( !pCharacter ) return;
	
	int nPLAY_KILL = 0;
	int nKillCount = 0;
	//	삭제
	if ( !m_killPlayList.empty () )
	{
		KILLTIME_DISPLAY_LIST_ITER iter = m_killPlayList.begin ();
		KILLTIME_DISPLAY_LIST_ITER iter_end = m_killPlayList.end ();
		
		for ( ; iter != iter_end; )
		{
			nKillCount++;
			const KILLTIME_PAIR& kill_pair = (*iter);
			const DWORD& dwID = kill_pair.first;
			const UIGUID& cID = kill_pair.second;

			if ( m_fTimer >= 2.0f )
			{
				DeleteControl ( cID, 0 );
				iter = m_killPlayList.erase ( iter );
				m_fTimer = 0.0f;

			}else if ( nKillCount >= 4 )
			{
				DeleteControl ( cID, 0 );
				iter = m_killPlayList.erase ( iter );
				nKillCount = 0;
			}
			else ++iter;
			
		}
	}

	if ( m_killPlayList.empty () ) return ;
	
	//	업데이트
	KILLTIME_DISPLAY_LIST_ITER iter = m_killPlayList.begin ();
	KILLTIME_DISPLAY_LIST_ITER iter_end = m_killPlayList.end ();

	for ( ; iter != iter_end; ++iter )
	{
		const KILLTIME_PAIR& kill_pair = (*iter);
		const DWORD& dwID = kill_pair.first;
		const UIGUID& cID = kill_pair.second;			

		CkillTimeUnit* pControl = (CkillTimeUnit*) FindControl ( cID );
		if ( !pControl )
		{
			GASSERT ( 0 && "컨트롤 찾기 실패" );
			continue;
		}

		const float& fAGE = 5.0f;

		pControl->SetGlobalPos ( m_pkillUnitDummy[nPLAY_KILL]->GetGlobalPos () );
		pControl->SetLeftTime ( fAGE );

		nPLAY_KILL++;
	}
	m_fTimer += fElapsedTime;
	CUIGroup::Update ( x, y, LB, MB, RB, nScroll, fElapsedTime, bFirstControl );
}



HRESULT CkillTimeDisplay::InitDeviceObjects ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	m_pd3dDevice = pd3dDevice;
	return CUIGroup::InitDeviceObjects ( pd3dDevice );
}

bool CkillTimeDisplay::NEW_PLAY_KILL (const DWORD& dwID ,  const DWORD& nClassType,const DWORD& nMClassType , const CString &strKilled , const CString &strKiller , const DWORD& nSchoolKilled , const DWORD& nSchoolKiller )
{
	CString str1,str2,str3;
	str1.Format("%s",strKilled);
	str2.Format("%s",strKiller);
	str3.Format("***SLAYED***");
	//if ( dwID < 0 ) return false;

	m_NEWID++;
	if ( KILLTIME_UNIT_END <= m_NEWID ) m_NEWID = KILLTIME_UNIT;
	float fLifeTime = 10.0f;
	CkillTimeUnit* pkillTimeUnit = new CkillTimeUnit;
	pkillTimeUnit->CreateSub ( this, "KILLTIME_UNIT", UI_FLAG_DEFAULT, m_NEWID );
	pkillTimeUnit->CreateSubControl (nClassType,nMClassType , nSchoolKilled , nSchoolKiller );
	pkillTimeUnit->InitDeviceObjects ( m_pd3dDevice );
	pkillTimeUnit->RestoreDeviceObjects ( m_pd3dDevice );	
	pkillTimeUnit->Setkill ( fLifeTime,str2,str1,str3 );
	RegisterControl ( pkillTimeUnit );	

	KILLTIME_PAIR pair ( dwID, m_NEWID );
	m_killPlayList.push_back ( pair );

	return true;
}

