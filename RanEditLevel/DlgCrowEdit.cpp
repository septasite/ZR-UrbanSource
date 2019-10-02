// DlgCrowEdit.cpp : implementation file
//

#include "stdafx.h"
#include "RanEditLevel.h"
#include "RanEditLevelView.h"
#include "DlgCrowEdit.h"
#include "ToolTab.h"
#include ".\dlgcrowedit.h"

#include "EtcFunction.h"


#include "DlgListCrow.h"
#include "GenerateName.h"

// CDlgCrowEdit dialog

IMPLEMENT_DYNAMIC(CDlgCrowEdit, CPropertyPage)
CDlgCrowEdit::CDlgCrowEdit(LOGFONT logfont)
	: CPropertyPage(CDlgCrowEdit::IDD)
	, m_pFont( NULL )
	, pGLLand( NULL )
	, pSched( NULL )
	, bEditACTION( FALSE )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CDlgCrowEdit::~CDlgCrowEdit()
{
}

void CDlgCrowEdit::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control( pDX, IDC_LIST_CROWACTION, m_list_SCHED );
}


BEGIN_MESSAGE_MAP(CDlgCrowEdit, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_SAVE, OnBnClickedButtonBasicSave)
	ON_BN_CLICKED(IDC_BUTTON_OPENBUSLOC, OnBnClickedButtonOpenbusloc)
	ON_BN_CLICKED(IDC_BUTTON_MOD_MAT, OnBnClickedButtonModMat)
	ON_BN_CLICKED(IDC_BUTTON_MOD_MAT2, OnBnClickedButtonModMat2)
	ON_BN_CLICKED(IDC_BUTTON_REGISTER, OnBnClickedButtonRegister)
	ON_BN_CLICKED(IDC_BUTTON_SCHED_ADD, OnBnClickedButtonSchedAdd)
	ON_BN_CLICKED(IDC_BUTTON_SCHED_EDIT, OnBnClickedButtonSchedEdit)
	ON_BN_CLICKED(IDC_BUTTON_SCHED_DEL, OnBnClickedButtonSchedDel)
	ON_BN_CLICKED(IDC_BUTTON_POS_GET, OnBnClickedButtonPosGet)
	ON_BN_CLICKED(IDC_BUTTON_ACTION_OK, OnBnClickedButtonActionOk)
	ON_CBN_SELCHANGE(IDC_COMBO_MAT_TYPE, OnCbnSelchangeComboMatType)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_CROWACTION, OnNMDblclkListCrowaction)
	ON_BN_CLICKED(IDC_BUTTON_CROW, OnBnClickedButtonCrow)
	ON_BN_CLICKED(IDC_BUTTON_APPLY, OnBnClickedButtonApply)
	ON_BN_CLICKED(IDC_BUTTON_NAME_CHECK, OnBnClickedButtonNameCheck)
	ON_BN_CLICKED(IDC_BUTTON_NAME_NEW, OnBnClickedButtonNameNew)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_CLOSE, OnBnClickedButtonBasicClose)
	ON_BN_CLICKED(IDC_BUTTON_LM_POS_NEW, OnBnClickedButtonLmPosNew)
	ON_BN_CLICKED(IDC_BUTTON_LM_POS_REBUILD, OnBnClickedButtonLmPosRebuild)
END_MESSAGE_MAP()


// CDlgCrowEdit message handlers
BOOL CDlgCrowEdit::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	{
		RECT rectCtrl;
		LONG lnWidth;
		LV_COLUMN lvColumn;

		m_list_SCHED.SetExtendedStyle ( m_list_SCHED.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES /*| LVS_EX_CHECKBOXES*/ );
		m_list_SCHED.GetClientRect ( &rectCtrl );
		lnWidth = rectCtrl.right - rectCtrl.left;

		const int nColumnCount = 4;	
		char* szColumnName1[nColumnCount] = { "#", "Type", "Val"  };
		int nColumnWidthPercent[nColumnCount] = { 10, 30, 60 };

		for ( int i = 0; i < nColumnCount; i++ )
		{		
			lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
			lvColumn.fmt = LVCFMT_LEFT;
			lvColumn.pszText = szColumnName1[i];
			lvColumn.iSubItem = i;
			lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
			m_list_SCHED.InsertColumn (i, &lvColumn );
		}
	}

	SetWin_Combo_Init( this, IDC_COMBO_MAT_TYPE, COMMENT::MOBACTIONS, EMACTION_SIZE );

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlgCrowEdit::SetData( GLLandMan*	pLand, std::string strName, bool bEdit )
{
	if ( pLand && bEdit ) //edit mode
	{
		pGLLand = pLand;

		SGLNODE<GLMobSchedule*>* pSchedule = pGLLand->GetMobSchMan()->FindMobSch( strName.c_str() );
		if ( pSchedule )
		{
			pSched = pSchedule->Data;
		}else{
			pSched = NULL;
		}

		if ( pGLLand && pSched )
		{
			UICHECK( true );
			ShowData();
			SetWin_Enable( this, IDC_BUTTON_MOD_MAT, TRUE );
			SetWin_Enable( this, IDC_BUTTON_MOD_MAT2, TRUE );
			SetWin_Enable( this, IDC_BUTTON_REGISTER, FALSE );	
		}
	}
	else if ( pLand && !bEdit ) //add mode
	{
		pSched = NULL;
		pGLLand = pLand;
		ResetData();
		UICHECK( false );
		SetWin_Enable( this, IDC_BUTTON_REGISTER, TRUE );
		OnBnClickedButtonNameNew();
	}
}

void CDlgCrowEdit::ShowData()
{
	if ( pGLLand && pSched )
	{
		SetWin_Text( this, IDC_EDIT_CROWNAME, pSched->m_szName );
		SetWin_Num_int( this, IDC_EDIT_CROWMID, pSched->m_CrowID.wMainID );
		SetWin_Num_int( this, IDC_EDIT_CROWSID, pSched->m_CrowID.wSubID );

		PCROWDATA pCrowData = GLCrowDataMan::GetInstance().GetCrowData( pSched->m_CrowID );
		if ( pCrowData )
		{
			SetWin_Text( this, IDC_EDIT_CROWREALNAME, pCrowData->GetName() );
		}else{
			SetWin_Text( this, IDC_EDIT_CROWREALNAME, "Unknown Crow" );
		}

		SetWin_Num_float( this, IDC_EDIT_CROW_REGENTIME, pSched->m_fReGenTime );
		SetWin_Num_int( this, IDC_EDIT_CROW_REGENMIN, pSched->m_nRegenMin );
		SetWin_Num_int( this, IDC_EDIT_CROW_REGENHOUR, pSched->m_nRegenHour );
		SetWin_Check( this, IDC_CHECK_DAYOFWEEK_0, pSched->m_bDayOfWeek[0] );
		SetWin_Check( this, IDC_CHECK_DAYOFWEEK_1, pSched->m_bDayOfWeek[1] );
		SetWin_Check( this, IDC_CHECK_DAYOFWEEK_2, pSched->m_bDayOfWeek[2] );
		SetWin_Check( this, IDC_CHECK_DAYOFWEEK_3, pSched->m_bDayOfWeek[3] );
		SetWin_Check( this, IDC_CHECK_DAYOFWEEK_4, pSched->m_bDayOfWeek[4] );
		SetWin_Check( this, IDC_CHECK_DAYOFWEEK_5, pSched->m_bDayOfWeek[5] );
		SetWin_Check( this, IDC_CHECK_DAYOFWEEK_6, pSched->m_bDayOfWeek[6] );
		SetWin_Check( this, IDC_CHECK_CROW_RANDOMPOS, pSched->m_bRendGenPos );
		SetWin_Num_int( this, IDC_EDIT_CROW_RANDOMGEN_POSNUM, pSched->m_wRendGenPosNum );
		SetWin_Num_int( this, IDC_EDIT_CROW_RANDOMGEN_POSDIST, pSched->m_wRendGenPosDist );
		SetWin_Check( this, IDC_CHECK_GROUPLEADER, pSched->m_bLeaderMonster );
		SetWin_Text( this, IDC_EDIT_CROW_GROUP, pSched->m_strGroupName.c_str() );
		SetWin_Text( this, IDC_EDIT_CROW_BUSLOCATION, pSched->m_strBUSLOCATION.c_str() );
		SetWin_Num_int( this, IDC_EDIT_CROW_REVIVEGATE, pSched->m_dwPC_REGEN_GATEID );

		UpdateList();

		JumpTo( pSched->m_pAffineParts->vTrans );
		CRanEditLevelView::GetView()->m_DxEditMat.SetAffineMatrix( pSched );
	}
}

void CDlgCrowEdit::ResetData()
{
	SetWin_Text( this, IDC_EDIT_CROWNAME, "" );
	SetWin_Num_int( this, IDC_EDIT_CROWMID, 65535 );
	SetWin_Num_int( this, IDC_EDIT_CROWSID, 65535 );
	SetWin_Text( this, IDC_EDIT_CROWREALNAME, "" );
	SetWin_Num_float( this, IDC_EDIT_CROW_REGENTIME, 0.0f );
	SetWin_Num_int( this, IDC_EDIT_CROW_REGENMIN, 0 );
	SetWin_Num_int( this, IDC_EDIT_CROW_REGENHOUR, 0 );
	SetWin_Check( this, IDC_CHECK_DAYOFWEEK_0, 0 );
	SetWin_Check( this, IDC_CHECK_DAYOFWEEK_1, 0 );
	SetWin_Check( this, IDC_CHECK_DAYOFWEEK_2, 0 );
	SetWin_Check( this, IDC_CHECK_DAYOFWEEK_3, 0 );
	SetWin_Check( this, IDC_CHECK_DAYOFWEEK_4, 0 );
	SetWin_Check( this, IDC_CHECK_DAYOFWEEK_5, 0 );
	SetWin_Check( this, IDC_CHECK_DAYOFWEEK_6, 0 );
	SetWin_Check( this, IDC_CHECK_CROW_RANDOMPOS, 0 );
	SetWin_Num_int( this, IDC_EDIT_CROW_RANDOMGEN_POSNUM, 0 );
	SetWin_Num_int( this, IDC_EDIT_CROW_RANDOMGEN_POSDIST, 0 );
	SetWin_Check( this, IDC_CHECK_GROUPLEADER, 0 );
	SetWin_Text( this, IDC_EDIT_CROW_GROUP, "" );
	SetWin_Text( this, IDC_EDIT_CROW_BUSLOCATION, "" );
	SetWin_Num_int( this, IDC_EDIT_CROW_REVIVEGATE, 0 );

	m_list_SCHED.DeleteAllItems();
}

BOOL CDlgCrowEdit::GetData()
{
	if ( pGLLand && pSched )
	{
		std::string str = GetWin_Text( this, IDC_EDIT_CROWNAME );

		if ( !strcmp( pSched->m_szName, str.c_str() ) )
		{
			StringCchCopy( pSched->m_szName, GLMobSchedule::EM_MAXSZNAME, str.c_str() );
		}
		else
		{
			bool bDuplicate = CrowNameCheck( pGLLand, str.c_str() );
			if ( bDuplicate )
			{
				MessageBox( "Name is already used, You can create an available name by clicking new Button" );
				return FALSE;
			}
			else
			{
				StringCchCopy( pSched->m_szName, GLMobSchedule::EM_MAXSZNAME, str.c_str() );
			}
		}

		pSched->m_CrowID.wMainID = GetWin_Num_int( this, IDC_EDIT_CROWMID );
		pSched->m_CrowID.wSubID = GetWin_Num_int( this, IDC_EDIT_CROWSID );

		PCROWDATA pCROW = GLCrowDataMan::GetInstance().GetCrowData( pSched->m_CrowID );
		if ( !pCROW )
		{
			MessageBox( "Invalid Crow ID!" );
			return FALSE;
		}

		pSched->m_fReGenTime = GetWin_Num_float( this, IDC_EDIT_CROW_REGENTIME );
		pSched->m_nRegenMin = GetWin_Num_int( this, IDC_EDIT_CROW_REGENMIN );
		pSched->m_nRegenHour = GetWin_Num_int( this, IDC_EDIT_CROW_REGENHOUR );
		pSched->m_bDayOfWeek[0] = (GetWin_Check( this, IDC_CHECK_DAYOFWEEK_0 ))? true:false;
		pSched->m_bDayOfWeek[1] = (GetWin_Check( this, IDC_CHECK_DAYOFWEEK_1 ))? true:false;
		pSched->m_bDayOfWeek[2] = (GetWin_Check( this, IDC_CHECK_DAYOFWEEK_2 ))? true:false;
		pSched->m_bDayOfWeek[3] = (GetWin_Check( this, IDC_CHECK_DAYOFWEEK_3 ))? true:false;
		pSched->m_bDayOfWeek[4] = (GetWin_Check( this, IDC_CHECK_DAYOFWEEK_4 ))? true:false;
		pSched->m_bDayOfWeek[5] = (GetWin_Check( this, IDC_CHECK_DAYOFWEEK_5 ))? true:false;
		pSched->m_bDayOfWeek[6] = (GetWin_Check( this, IDC_CHECK_DAYOFWEEK_6 ))? true:false;

		pSched->m_bRendGenPos = GetWin_Check( this, IDC_CHECK_CROW_RANDOMPOS );
		pSched->m_wRendGenPosNum = GetWin_Num_int( this, IDC_EDIT_CROW_RANDOMGEN_POSNUM );
		pSched->m_wRendGenPosDist = GetWin_Num_int( this, IDC_EDIT_CROW_RANDOMGEN_POSDIST );
		pSched->m_bLeaderMonster = GetWin_Check( this, IDC_CHECK_GROUPLEADER );
		pSched->m_strGroupName = GetWin_Text( this, IDC_EDIT_CROW_GROUP );
		pSched->m_strBUSLOCATION = GetWin_Text( this, IDC_EDIT_CROW_BUSLOCATION );
		pSched->m_dwPC_REGEN_GATEID = GetWin_Num_int( this, IDC_EDIT_CROW_REVIVEGATE );

		if ( pSched->m_bRendGenPos )
		{
			pSched->GenerateRendGenPos( pGLLand->GetNavi() );
		}
		else
		{
			pSched->m_vectorRendGenPos.clear();
		}

		return TRUE;
	}

	return FALSE;
}

void CDlgCrowEdit::UpdateList()
{
	std::string strAct[2] = 
	{
		"Move",
		"Stay",
	};

	if ( pGLLand && pSched )
	{
		char szTempChar[512];
		int i = 0;
		m_list_SCHED.DeleteAllItems();

		SGLNODE<SMOBACTION>* pCur = pSched->m_sMobActList.m_pHead;
		for ( ; pCur; pCur = pCur->pNext )
		{
			sprintf( szTempChar, "%d", i );
			m_list_SCHED.InsertItem( i, szTempChar );

			sprintf( szTempChar, "%s", strAct[pCur->Data.emAction].c_str() );
			m_list_SCHED.SetItemText( i, 1, szTempChar );

			if ( pCur->Data.emAction == EMACTION_MOVE )
			{
				sprintf( szTempChar, "%g~%g~%g", pCur->Data.vPos.x, pCur->Data.vPos.y, pCur->Data.vPos.z );
				m_list_SCHED.SetItemText( i, 2, szTempChar );

			}
			else if ( pCur->Data.emAction == EMACTION_ACTSTAY )
			{
				sprintf( szTempChar, "%g", pCur->Data.fLife );
				m_list_SCHED.SetItemText( i, 2, szTempChar );
			}

			m_list_SCHED.SetItemData( i, (DWORD_PTR)pCur );
			i++;
		}

		SetWin_Enable( this, IDC_EDIT_CROW_MAT_X, FALSE );
		SetWin_Enable( this, IDC_EDIT_CROW_MAT_Y, FALSE );
		SetWin_Enable( this, IDC_EDIT_CROW_MAT_Z, FALSE );
		SetWin_Enable( this, IDC_EDIT_CROW_MAT_TIME, FALSE );
		SetWin_Enable( this, IDC_COMBO_MAT_TYPE, FALSE );
		SetWin_Enable( this, IDC_BUTTON_ACTION_OK, FALSE );
		SetWin_Enable( this, IDC_BUTTON_POS_GET, FALSE );
	}

	bEditACTION = FALSE;
}

void CDlgCrowEdit::OnBnClickedButtonBasicSave()
{
	if ( !GetData() )	return;

	CRanEditLevelView::GetView()->OnMousecontrolNone();
	CRanEditLevelView::GetView()->bRenderCrow = true;

	if ( pGLLand && pSched )
	{
		pGLLand->DropOutCrow( pSched->m_dwGlobID );
	}

	if ( m_pToolTab )
		m_pToolTab->ActiveDlgPage( DLG_CROWLIST );
}

void CDlgCrowEdit::OnBnClickedButtonOpenbusloc()
{
	if ( pGLLand && pSched )
	{
		CString szFilter = "busloc|*.BUSLOC|";
		CFileDialog dlg ( TRUE,".BUSLOC",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter, this );
		dlg.m_ofn.lpstrInitialDir = GLOGIC::GetPath ();
		if ( dlg.DoModal() == IDOK )
		{
			pSched->m_strBUSLOCATION = dlg.GetFileName();
		}
	}
}

void CDlgCrowEdit::OnBnClickedButtonModMat()
{
	if ( pGLLand && pSched )
	{
		DxViewPort::GetInstance().CameraJump( pSched->m_pAffineParts->vTrans );
		CRanEditLevelView::GetView()->m_DxEditMat.SetAffineMatrix( pSched );
		CRanEditLevelView::GetView()->OnMousecontrolMove();
		CRanEditLevelView::GetView()->bRenderCrow = false;
	}
}

void CDlgCrowEdit::OnBnClickedButtonModMat2()
{
	if ( pGLLand && pSched )
	{
		CRanEditLevelView::GetView()->m_DxEditMat.GetAffineParts( pSched->m_pAffineParts );
		CRanEditLevelView::GetView()->OnMousecontrolNone();
		CRanEditLevelView::GetView()->bRenderCrow = true;
		BOOL bOK = pGLLand->DropOutCrow( pSched->m_dwGlobID );
	}
}

void CDlgCrowEdit::OnBnClickedButtonRegister()
{
	if ( pGLLand  )
	{
		D3DXVECTOR3 vPOS = CRanEditLevelView::GetView()->m_vPos;
		SNATIVEID sID;
		sID.wMainID = GetWin_Num_int( this, IDC_EDIT_CROWMID );
		sID.wSubID = GetWin_Num_int( this, IDC_EDIT_CROWSID );

		PCROWDATA pCROW = GLCrowDataMan::GetInstance().GetCrowData( sID );
		if ( pCROW )
		{
		
			GLMobSchedule sSched = GLMobSchedule();
			
			std::string strName = GetWin_Text( this, IDC_EDIT_CROWNAME );

			bool bDuplicate = CrowNameCheck( pGLLand, strName.c_str() );
			if ( bDuplicate )
			{
				MessageBox("Name is already used, You can create an available name by clicking new Button" );
				return;
			}

			StringCchCopy( sSched.m_szName, GLMobSchedule::EM_MAXSZNAME, strName.c_str() );

			sSched.m_CrowID = pCROW->sNativeID;
			sSched.m_pAffineParts->vTrans = vPOS; 

			pGLLand->GetMobSchMan()->AddMobSch( sSched );

			pSched = NULL;
			pSched = pGLLand->GetMobSchMan()->FindMobSch( sSched.m_szName )->Data;
	
			if ( pGLLand && pSched )
			{
				SetWin_Enable( this, IDC_BUTTON_REGISTER, FALSE );
				UICHECK( true );
				ShowData();
			}
		}
		else
		{
			MessageBox( "Register New Schedule error. Invalid crow id. Recheck Crow ID" );
		}
	}
}

void CDlgCrowEdit::OnBnClickedButtonSchedAdd()
{
	if ( !pSched )	return;
	if ( !pGLLand  )	return;

	SetWin_Num_float( this, IDC_EDIT_CROW_MAT_X, 0.0f );
	SetWin_Num_float( this, IDC_EDIT_CROW_MAT_Y, 0.0f );
	SetWin_Num_float( this, IDC_EDIT_CROW_MAT_Z, 0.0f );
	SetWin_Num_float( this, IDC_EDIT_CROW_MAT_TIME, 4.0f );
	SetWin_Combo_Sel( this, IDC_COMBO_MAT_TYPE, 0 );

	OnCbnSelchangeComboMatType();
	bEditACTION = FALSE;
}

void CDlgCrowEdit::OnBnClickedButtonSchedEdit()
{
	if ( !pSched )	return;
	if ( !pGLLand  )	return;

	int nSelect = m_list_SCHED.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	SGLNODE<SMOBACTION>* pAction = (SGLNODE<SMOBACTION>*)m_list_SCHED.GetItemData( nSelect );
	if ( pAction )
	{
		SetWin_Num_float( this, IDC_EDIT_CROW_MAT_X, pAction->Data.vPos.x );
		SetWin_Num_float( this, IDC_EDIT_CROW_MAT_Y, pAction->Data.vPos.y );
		SetWin_Num_float( this, IDC_EDIT_CROW_MAT_Z, pAction->Data.vPos.z );
		SetWin_Num_float( this, IDC_EDIT_CROW_MAT_TIME, pAction->Data.fLife );
		SetWin_Combo_Sel( this, IDC_COMBO_MAT_TYPE, pAction->Data.emAction );

		SetWin_Num_int( this, IDC_EDIT_CROW_MAT_NUM, nSelect );

		OnCbnSelchangeComboMatType();
		bEditACTION = TRUE;
	}	
}

void CDlgCrowEdit::OnBnClickedButtonSchedDel()
{
	if ( !pSched )	return;
	if ( !pGLLand  )	return;

	int nSelect = m_list_SCHED.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	SGLNODE<SMOBACTION>* pAction = (SGLNODE<SMOBACTION>*)m_list_SCHED.GetItemData( nSelect );
	if ( pAction )
	{
		pSched->m_sMobActList.DELNODE( pAction );
		bEditACTION = FALSE;
		UpdateList();
		pGLLand->DropOutCrow( pSched->m_dwGlobID );
	}
}

void CDlgCrowEdit::OnBnClickedButtonPosGet()
{
	if ( !pSched )	return;

	D3DXVECTOR3 vPOS = CRanEditLevelView::GetView()->m_vPos;

	SetWin_Num_float( this, IDC_EDIT_CROW_MAT_X, vPOS.x );
	SetWin_Num_float( this, IDC_EDIT_CROW_MAT_Y, vPOS.y );
	SetWin_Num_float( this, IDC_EDIT_CROW_MAT_Z, vPOS.z );
}

void CDlgCrowEdit::OnBnClickedButtonActionOk()
{
	if ( !pSched )	return;

	if ( bEditACTION )
	{
		int nNum = GetWin_Num_int( this, IDC_EDIT_CROW_MAT_NUM );

		SGLNODE<SMOBACTION>* pAction = (SGLNODE<SMOBACTION>*)m_list_SCHED.GetItemData( nNum );
		if ( pAction )
		{
			SMOBACTION sMobAction;
			sMobAction.emAction = (EMMOBACTIONS) GetWin_Combo_Sel( this, IDC_COMBO_MAT_TYPE );

			bool bMove = ( sMobAction.emAction == EMACTION_MOVE );
			bool bStay = ( sMobAction.emAction == EMACTION_ACTSTAY );

			if ( bStay )
			{
				sMobAction.fLife = GetWin_Num_float( this, IDC_EDIT_CROW_MAT_TIME );
			}
			
			if ( bMove )
			{
				sMobAction.vPos.x = GetWin_Num_float( this, IDC_EDIT_CROW_MAT_X );
				sMobAction.vPos.y = GetWin_Num_float( this, IDC_EDIT_CROW_MAT_Y );
				sMobAction.vPos.z = GetWin_Num_float( this, IDC_EDIT_CROW_MAT_Z );
			}

			pAction->Data.emAction = sMobAction.emAction;
			pAction->Data.fLife = sMobAction.fLife;
			pAction->Data.vPos = sMobAction.vPos;
			pGLLand->DropOutCrow( pSched->m_dwGlobID );
		}
	}
	else
	{
		SMOBACTION sMobAction;
		sMobAction.emAction = (EMMOBACTIONS) GetWin_Combo_Sel( this, IDC_COMBO_MAT_TYPE );

		bool bMove = ( sMobAction.emAction == EMACTION_MOVE );
		bool bStay = ( sMobAction.emAction == EMACTION_ACTSTAY );

		if ( bStay )
		{
			sMobAction.fLife = GetWin_Num_float( this, IDC_EDIT_CROW_MAT_TIME );
		}
		
		if ( bMove )
		{
			sMobAction.vPos.x = GetWin_Num_float( this, IDC_EDIT_CROW_MAT_X );
			sMobAction.vPos.y = GetWin_Num_float( this, IDC_EDIT_CROW_MAT_Y );
			sMobAction.vPos.z = GetWin_Num_float( this, IDC_EDIT_CROW_MAT_Z );
		}

		pSched->m_sMobActList.ADDTAIL ( sMobAction );
		pGLLand->DropOutCrow( pSched->m_dwGlobID );
	}		

	UpdateList();
}

void CDlgCrowEdit::OnCbnSelchangeComboMatType()
{
	SetWin_Enable( this, IDC_COMBO_MAT_TYPE, TRUE );
	SetWin_Enable( this, IDC_BUTTON_ACTION_OK, TRUE );

	int nSelect = GetWin_Combo_Sel( this, IDC_COMBO_MAT_TYPE );

	bool bMove = ( nSelect == EMACTION_MOVE );
	bool bStay = ( nSelect == EMACTION_ACTSTAY );

	SetWin_Enable( this, IDC_EDIT_CROW_MAT_X, bMove );
	SetWin_Enable( this, IDC_EDIT_CROW_MAT_Y, bMove );
	SetWin_Enable( this, IDC_EDIT_CROW_MAT_Z, bMove );
	SetWin_Enable( this, IDC_BUTTON_POS_GET, bMove );

	SetWin_Enable( this, IDC_EDIT_CROW_MAT_TIME, bStay );	
}

void CDlgCrowEdit::OnNMDblclkListCrowaction(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int nSelect = m_list_SCHED.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	SGLNODE<SMOBACTION>* pAction = (SGLNODE<SMOBACTION>*)m_list_SCHED.GetItemData( nSelect );
	if ( pAction && pAction->Data.emAction == EMACTION_MOVE )
	{
		JumpTo( pAction->Data.vPos );
	}
}

void CDlgCrowEdit::OnBnClickedButtonCrow()
{
	if ( pGLLand && pSched )
	{
		CDlgListCrow dlg;
		if ( dlg.DoModal() == IDOK )
		{
			PCROWDATA pCROW = GLCrowDataMan::GetInstance().GetCrowData( dlg.sIDSELECT );
			if ( pCROW )
			{
				pSched->m_CrowID = pCROW->sNativeID;
				ShowData();
				pGLLand->DropOutCrow( pSched->m_dwGlobID );
			}
		}
	}
	else if ( pGLLand )
	{
		CDlgListCrow dlg;
		if ( dlg.DoModal() == IDOK )
		{
			PCROWDATA pCROW = GLCrowDataMan::GetInstance().GetCrowData( dlg.sIDSELECT );
			if ( pCROW )
			{
				SetWin_Num_int( this, IDC_EDIT_CROWMID, pCROW->sNativeID.wMainID );
				SetWin_Num_int( this, IDC_EDIT_CROWSID, pCROW->sNativeID.wSubID );
				SetWin_Text( this, IDC_EDIT_CROWREALNAME, pCROW->GetName() );
			}
		}
	}
}

void CDlgCrowEdit::OnBnClickedButtonApply()
{
	if ( pGLLand && pSched )
	{
		if ( !GetData() )	return;

		pGLLand->DropOutCrow( pSched->m_dwGlobID );
	}
}

void CDlgCrowEdit::OnBnClickedButtonNameCheck()
{
	if ( pGLLand && pSched )
	{
		std::string str = GetWin_Text( this, IDC_EDIT_CROWNAME );

		if ( !strcmp( pSched->m_szName, str.c_str() ) )
		{
			MessageBox( "Name Valid" );
		}else{
			bool bDuplicate = CrowNameCheck( pGLLand, str.c_str() );
			if ( bDuplicate )
			{
				MessageBox("Name is already used, You can create an available name by clicking new Button" );
				return;
			}else{
				MessageBox( "Name Valid" );
			}
		}
	}
	else if ( pGLLand )
	{
		std::string str = GetWin_Text( this, IDC_EDIT_CROWNAME );

		bool bDuplicate = CrowNameCheck( pGLLand, str.c_str() );
		if ( bDuplicate )
		{
			MessageBox("Name is already used, You can create an available name by clicking new Button" );
		}else{
			MessageBox( "Name Valid" );
		}
	}
}

void CDlgCrowEdit::OnBnClickedButtonNameNew()
{
	if ( pGLLand )
	{
		std::string str = CrowNameNew( pGLLand );
		if ( str.size() != 0 )
		{
			SetWin_Text( this, IDC_EDIT_CROWNAME, str.c_str() );
		}
	}
}

void CDlgCrowEdit::OnBnClickedButtonBasicClose()
{
	if ( m_pToolTab )
		m_pToolTab->ActiveDlgPage( DLG_CROWLIST  );
}


void CDlgCrowEdit::JumpTo( D3DXVECTOR3 vPos )
{
	EffTo( vPos );
	vPos.y += 10.0f ;
	DxViewPort::GetInstance().CameraJump( vPos );
}

void CDlgCrowEdit::EffTo( D3DXVECTOR3 vPos )
{
}

void CDlgCrowEdit::UICHECK( bool bEnable )
{
	SetWin_Enable( this, IDC_EDIT_CROW_REGENTIME, bEnable );
	SetWin_Enable( this, IDC_EDIT_CROW_REGENMIN, bEnable );
	SetWin_Enable( this, IDC_EDIT_CROW_REGENHOUR, bEnable );
	SetWin_Enable( this, IDC_CHECK_DAYOFWEEK_0, bEnable );
	SetWin_Enable( this, IDC_CHECK_DAYOFWEEK_1, bEnable );
	SetWin_Enable( this, IDC_CHECK_DAYOFWEEK_2, bEnable );
	SetWin_Enable( this, IDC_CHECK_DAYOFWEEK_3, bEnable );
	SetWin_Enable( this, IDC_CHECK_DAYOFWEEK_4, bEnable );
	SetWin_Enable( this, IDC_CHECK_DAYOFWEEK_5, bEnable );
	SetWin_Enable( this, IDC_CHECK_DAYOFWEEK_6, bEnable );
	SetWin_Enable( this, IDC_CHECK_CROW_RANDOMPOS, bEnable );
	SetWin_Enable( this, IDC_EDIT_CROW_RANDOMGEN_POSNUM, bEnable );
	SetWin_Enable( this, IDC_EDIT_CROW_RANDOMGEN_POSDIST, bEnable );
	SetWin_Enable( this, IDC_CHECK_GROUPLEADER, bEnable );
	SetWin_Enable( this, IDC_EDIT_CROW_GROUP, bEnable );
	SetWin_Enable( this, IDC_EDIT_CROW_BUSLOCATION, bEnable );
	SetWin_Enable( this, IDC_BUTTON_OPENBUSLOC, bEnable );
	SetWin_Enable( this, IDC_EDIT_CROW_REVIVEGATE, bEnable );
	SetWin_Enable( this, IDC_BUTTON_SCHED_ADD, bEnable );
	SetWin_Enable( this, IDC_BUTTON_SCHED_EDIT, bEnable );
	SetWin_Enable( this, IDC_BUTTON_SCHED_DEL, bEnable );
	SetWin_Enable( this, IDC_BUTTON_MOD_MAT, bEnable );
	SetWin_Enable( this, IDC_BUTTON_MOD_MAT2, bEnable );
	SetWin_Enable( this, IDC_BUTTON_APPLY, bEnable );
	SetWin_Enable( this, IDC_BUTTON_BASIC_SAVE, bEnable );
	SetWin_Enable( this, IDC_EDIT_CROW_MAT_X, bEnable );
	SetWin_Enable( this, IDC_EDIT_CROW_MAT_Y, bEnable );
	SetWin_Enable( this, IDC_EDIT_CROW_MAT_Z, bEnable );
	SetWin_Enable( this, IDC_EDIT_CROW_MAT_TIME, bEnable );
	SetWin_Enable( this, IDC_COMBO_MAT_TYPE, bEnable );
	SetWin_Enable( this, IDC_BUTTON_ACTION_OK, bEnable );
	SetWin_Enable( this, IDC_BUTTON_POS_GET, bEnable );
}
void CDlgCrowEdit::OnBnClickedButtonLmPosNew()
{
	if ( pGLLand && pSched )
	{
		D3DXVECTOR3 vPOS = CRanEditLevelView::GetView()->m_vPos;
		pSched->m_pAffineParts->vTrans = vPOS;
		OnBnClickedButtonModMat();
	}
}

void CDlgCrowEdit::OnBnClickedButtonLmPosRebuild()
{
	if ( pGLLand && pSched )
	{
		D3DXVECTOR3 vPOS = CRanEditLevelView::GetView()->m_vPos;
		D3DXVECTOR3 vDis = pSched->m_pAffineParts->vTrans - vPOS;
		pSched->m_pAffineParts->vTrans = vPOS;
		pSched->ModifierSchList( &vDis, pGLLand->GetNavi() );
		pSched->GenerateRendGenPos( pGLLand->GetNavi() );
	}
}
