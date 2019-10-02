// TabCPS.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "TabCPS.h"
#include "ToolTab.h"
#include ".\tabcps.h"
#include "StringUtils.h"
#include "EtcFunction.h"
#include "DummyData.h"
#include "DxEffChar.h"
#include "XEffTab.h"


// CTabCPS dialog

IMPLEMENT_DYNAMIC(CTabCPS, CPropertyPage)
CTabCPS::CTabCPS(LOGFONT logfont)
	: CPropertyPage(CTabCPS::IDD)
	,m_pFont( NULL )
{
	m_bActive = FALSE;
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	bAdd = false;
	bAddBone = false;
	bAddBone_b = false;
	strFileName = "";
}

CTabCPS::~CTabCPS()
{
}

void CTabCPS::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MATERIAL, m_list_material );
	DDX_Control(pDX, IDC_LIST_TRACE, m_list_trace );
	DDX_Control(pDX, IDC_LIST_TRACE_BONE, m_list_trace_b );
}


BEGIN_MESSAGE_MAP(CTabCPS, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_CPS_LOAD, OnBnClickedButtonCpsLoad)
	ON_BN_CLICKED(IDC_BUTTON_CPS_SAVE, OnBnClickedButtonCpsSave)
	ON_BN_CLICKED(IDC_MAT_ADD, OnBnClickedMatAdd)
	ON_BN_CLICKED(IDC_MAT_EDIT, OnBnClickedMatEdit)
	ON_BN_CLICKED(IDC_MAT_DEL, OnBnClickedMatDel)
	ON_BN_CLICKED(IDC_MAT_OK, OnBnClickedMatOk)
	ON_BN_CLICKED(IDC_MAT_CANCEL, OnBnClickedMatCancel)
	ON_BN_CLICKED(IDC_TRACE_ADD, OnBnClickedTraceAdd)
	ON_BN_CLICKED(IDC_TRACE_EDIT, OnBnClickedTraceEdit)
	ON_BN_CLICKED(IDC_TRACE_DEL, OnBnClickedTraceDel)
	ON_BN_CLICKED(IDC_TRACE_CAN, OnBnClickedTraceCan)
	ON_BN_CLICKED(IDC_TRACE_OK, OnBnClickedTraceOk)
	ON_BN_CLICKED(IDC_EFF_T_ADD, OnBnClickedEffTAdd)
	ON_BN_CLICKED(IDC_EFF_T_EDIT, OnBnClickedEffTEdit)
	ON_BN_CLICKED(IDC_EFF_T_DEL, OnBnClickedEffTDel)
	ON_BN_CLICKED(IDC_EFF_T_OK, OnBnClickedEffTOk)
	ON_BN_CLICKED(IDC_EFF_T_CAN, OnBnClickedEffTCan)
	ON_BN_CLICKED(IDC_BUTTON_CPS_LOADRAN2, OnBnClickedButtonCpsLoadran2)
	ON_BN_CLICKED(IDC_BUTTON_CPS_NEW, OnBnClickedButtonCpsNew)
END_MESSAGE_MAP()


// CTabCPS message handlers
BOOL CTabCPS::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	if (!m_bActive)
	{
		SetWin_ShowWindow ( this, IDC_BUTTON_CPS_SAVE, SW_HIDE );
		SetWin_Combo_Init ( this, IDC_COMBO_PIECE, DUMMYDATA::m_CharType, PIECE_SIZE );
		SetWin_Combo_Init ( this, IDC_COMBO_WEPBACK, DUMMYDATA::m_SlotType, EMPEACE_WEAPON_SIZE );

		CRect SheetRect;
		CWnd *pWnd;
		pWnd = GetDlgItem ( IDC_STATIC_EFFECT );
		pWnd->GetWindowRect ( SheetRect );
		ScreenToClient ( &SheetRect );

		LOGFONT logfont = {0};

		CFont* pFont = GetFont();
		if ( pFont ) pFont->GetLogFont( &logfont );

		m_pEffTab = new CEffTab ( SheetRect, logfont, this );
		m_pEffTab->Create( this, WS_CHILD|WS_VISIBLE|WS_TABSTOP, 0 );
		m_pEffTab->ModifyStyleEx (0, WS_EX_CONTROLPARENT);
	}
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CTabCPS::OnBnClickedButtonCpsLoad()
{
	CString szFilterInput = "Piece (*.cps,*.aps,*.vps)|*.cps;*.aps;*.vps|";
	CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
	dlgInput.m_ofn.lpstrInitialDir = DxSkinPieceContainer::GetInstance().GetPath();
	if ( dlgInput.DoModal() != IDOK ) return;

	Reset();
	HRESULT hr = m_pPiece.LoadPieceTool ( dlgInput.GetFileName(),NULL,TRUE );

	if ( FAILED(hr) )
	{
		MessageBox ( "Failure to Load :(" );	
		m_pToolTab->AddHistoryOpenFail( "CPS-APS-VPS Editor",dlgInput.GetFileName().GetString() );
	}
	else
	{
		SetWin_Text ( this, IDC_EDIT_FILENAME, dlgInput.GetFileName() );
		UpdateData();
		m_bActive = TRUE;
		SetWin_ShowWindow ( this, IDC_BUTTON_CPS_SAVE, SW_SHOW );	
		m_pToolTab->AddHistoryOpen( "CPS-APS-VPS Editor",dlgInput.GetFileName().GetString() );
		strFileName = dlgInput.GetFileName().GetString();
	}
}

void CTabCPS::OnBnClickedButtonCpsLoadran2()
{
	CString szFilterInput = "Piece (*.cps,*.aps,*.vps)|*.cps;*.aps;*.vps|";
	CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
	dlgInput.m_ofn.lpstrInitialDir = DxSkinPieceContainer::GetInstance().GetPath();
	if ( dlgInput.DoModal() != IDOK ) return;

	Reset();
	HRESULT hr = m_pPiece.LoadPieceToolRan2 ( dlgInput.GetFileName(),NULL,TRUE );

	if ( FAILED(hr) )
	{
		MessageBox ( "Failure to Load :(" );	
		m_pToolTab->AddHistoryOpenFail( "CPS-APS-VPS Editor(Ran2)",dlgInput.GetFileName().GetString() );
	}
	else
	{
		SetWin_Text ( this, IDC_EDIT_FILENAME, dlgInput.GetFileName() );
		UpdateData();
		m_bActive = TRUE;
		SetWin_ShowWindow ( this, IDC_BUTTON_CPS_SAVE, SW_SHOW );	
		m_pToolTab->AddHistoryOpen( "CPS-APS-VPS Editor(Ran2)",dlgInput.GetFileName().GetString() );
		strFileName = dlgInput.GetFileName().GetString();
	}
}

void CTabCPS::OnBnClickedButtonCpsNew()
{
	Reset();
	SetWin_ShowWindow ( this, IDC_BUTTON_CPS_SAVE, SW_SHOW );	
	SetWin_Text ( this, IDC_EDIT_FILENAME, "" );
	m_bActive = TRUE;
}

void CTabCPS::OnBnClickedButtonCpsSave()
{
	if ( SaveData () )
	{
		CString szFilter = "Piece (*.cps,*.aps,*.vps)|*.cps;*.aps;*.vps|";
		CFileDialog dlg(FALSE,"",strFileName.GetString(),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
		(CTabCPS*)this);

		dlg.m_ofn.lpstrInitialDir = DxSkinPieceContainer::GetInstance().GetPath();
		if ( dlg.DoModal() == IDOK )
		{
			HRESULT hr = m_pPiece.SavePieceTool( dlg.GetFileName() );
			if ( FAILED(hr))
			{
				MessageBox ( "Failure to Save :(" );
				m_pToolTab->AddHistorySaveFail( "CPS-APS-VPS Editor",dlg.GetFileName().GetString() );
			}
			else
			{
				SetWin_Text ( this, IDC_EDIT_FILENAME, dlg.GetFileName() );
				MessageBox ( "Save Done :P" );
				m_pToolTab->AddHistorySave( "CPS-APS-VPS Editor",dlg.GetFileName().GetString() );
			}
		}
	}
}

BOOL CTabCPS::UpdateData()
{
	SetWin_Text ( this, IDC_EDIT_SKELETON, m_pPiece.m_szSkeleton );
	SetWin_Text ( this, IDC_EDIT_SKIN, m_pPiece.m_szXFileName );
	SetWin_Text ( this, IDC_EDIT_MESH, m_pPiece.m_szMeshName );
	SetWin_Combo_Sel ( this, IDC_COMBO_PIECE, (int)m_pPiece.m_emType );
	SetWin_Combo_Sel ( this, IDC_COMBO_WEPBACK, (int)m_pPiece.m_emWeaponWhereBack );
	SetWin_Num_int ( this, IDC_EDIT_REF, m_pPiece.m_dwRef );
	SetWin_Num_int ( this, IDC_EDIT_FLAG, m_pPiece.m_dwFlag );

	UpdateListMaterial();
	UpdateListTrace();
	m_pEffTab->ActiveEffList( m_pPiece.m_vecEFFECT );
	return TRUE;
}

BOOL CTabCPS::SaveData()
{
	StringCchCopy( m_pPiece.m_szSkeleton,GetWin_Text( this, IDC_EDIT_SKELETON ).GetLength()+1, GetWin_Text( this, IDC_EDIT_SKELETON ).GetString() );
	StringCchCopy( m_pPiece.m_szXFileName,GetWin_Text( this, IDC_EDIT_SKIN ).GetLength()+1, GetWin_Text( this, IDC_EDIT_SKIN ).GetString() );
	StringCchCopy( m_pPiece.m_szMeshName,GetWin_Text( this, IDC_EDIT_MESH ).GetLength()+1, GetWin_Text( this, IDC_EDIT_MESH ).GetString() );
	m_pPiece.m_emType =  (EMPIECECHAR ) GetWin_Combo_Sel ( this, IDC_COMBO_PIECE );
	m_pPiece.m_emWeaponWhereBack = ( EMPEACEZONEWEAPON ) GetWin_Combo_Sel ( this, IDC_COMBO_WEPBACK);
	m_pPiece.m_dwRef = GetWin_Num_int ( this, IDC_EDIT_REF ); 
	m_pPiece.m_dwFlag = GetWin_Num_int ( this, IDC_EDIT_FLAG ); 
	m_pPiece.m_vecEFFECT = m_pEffTab->GetVecEffect();

	return TRUE;
}

BOOL CTabCPS::UpdateListMaterial()
{
	CString strTemp;
	m_list_material.ResetContent();
	int nNum = m_pPiece.m_dwMaterialNum;

	for ( int i = 0; i < nNum; i++ )
	{
		strTemp.Format ("%d--Tex:%s--Flag:%d--Bias:%d"
			,i
			,m_pPiece.m_pMaterialPiece[i].m_strTexture.c_str()
			,m_pPiece.m_pMaterialPiece[i].m_dwFlags
			,m_pPiece.m_pMaterialPiece[i].m_dwZBias
			);

		int nData = m_list_material.InsertString(i, strTemp);
	}

	SetWin_Num_int ( this, IDC_EDIT_MATNUM ,nNum );

	SetWin_ShowWindow ( this, IDC_EDIT_MAT_TEX, SW_HIDE);
	SetWin_ShowWindow ( this, IDC_EDIT_MAT_FLAG, SW_HIDE);
	SetWin_ShowWindow ( this, IDC_EDIT_MAT_BIAS, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_MAT_OK, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_MAT_CANCEL, SW_HIDE );

	return TRUE;
}

void CTabCPS::OnBnClickedMatAdd()
{
	SetWin_ShowWindow ( this, IDC_EDIT_MAT_TEX, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_MAT_FLAG, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_MAT_BIAS, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_MAT_OK, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_MAT_CANCEL, SW_SHOW );
	bAdd = true;
}

void CTabCPS::OnBnClickedMatEdit()
{
	int nIndex = m_list_material.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		SetWin_ShowWindow ( this, IDC_EDIT_MAT_TEX, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_MAT_FLAG, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_MAT_BIAS, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_MAT_OK, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_MAT_CANCEL, SW_SHOW );
		bAdd = false;

		SetWin_Num_int ( this, IDC_EDIT_MAT_FLAG ,m_pPiece.m_pMaterialPiece[nIndex].m_dwFlags );
		SetWin_Num_int ( this, IDC_EDIT_MAT_BIAS ,m_pPiece.m_pMaterialPiece[nIndex].m_dwZBias );
		SetWin_Text ( this, IDC_EDIT_MAT_TEX, m_pPiece.m_pMaterialPiece[nIndex].m_strTexture.c_str() );

		nEditID = nIndex;
	}
}

void CTabCPS::OnBnClickedMatDel()
{
	m_VecMaterial.clear();
	int nIndex = m_list_material.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		if ( MessageBox ( "Are you sure you want to Delete?", "Question", MB_YESNO ) == IDYES )
		{
			int nNumMat = m_pPiece.m_dwMaterialNum;
			for ( int i = 0; i < nNumMat; i++ )
			{
				if ( i!= nIndex )
				{
					m_VecMaterial.push_back(m_pPiece.m_pMaterialPiece[i]);
				}
			}

			MAT_VEC_ITER iter = m_VecMaterial.begin();
			MAT_VEC_ITER iter_end = m_VecMaterial.end();

			int nSize  = (int)m_VecMaterial.size();
			SMATERIAL_PIECE*	m_pMaterialx;
			m_pMaterialx = new SMATERIAL_PIECE[nSize];

			for ( int i=0; iter!=iter_end; ++iter, ++i )
			{
				m_pMaterialx[i] = (*iter);
			}

			m_pPiece.m_pMaterialPiece = m_pMaterialx;
			m_pPiece.m_dwMaterialNum = nSize;

			m_VecMaterial.clear();
			UpdateListMaterial();
		}
	}
}

void CTabCPS::OnBnClickedMatOk()
{
	m_VecMaterial.clear();

	int nNumMat = m_pPiece.m_dwMaterialNum;
	for ( int i = 0; i < nNumMat; i++ )
	{
		m_VecMaterial.push_back(m_pPiece.m_pMaterialPiece[i]);
	}

	if ( !bAdd)
	{
		m_VecMaterial.erase(m_VecMaterial.begin()+nEditID );
	}

	SMATERIAL_PIECE	m_pMaterialx;
	m_pMaterialx.m_dwFlags = GetWin_Num_int ( this, IDC_EDIT_MAT_FLAG);
	m_pMaterialx.m_dwZBias = GetWin_Num_int ( this, IDC_EDIT_MAT_BIAS);
	m_pMaterialx.m_strTexture = GetWin_Text ( this, IDC_EDIT_MAT_TEX ).GetString();
	m_VecMaterial.push_back(m_pMaterialx);

	MAT_VEC_ITER iter = m_VecMaterial.begin();
	MAT_VEC_ITER iter_end = m_VecMaterial.end();

	int nSize  = (int)m_VecMaterial.size();
	SMATERIAL_PIECE*	m_pMaterialc;
	m_pMaterialc = new SMATERIAL_PIECE[nSize];

	for ( int i=0; iter!=iter_end; ++iter, ++i )
	{
		m_pMaterialc[i] = (*iter);
	}

	m_pPiece.m_pMaterialPiece = m_pMaterialc;
	m_pPiece.m_dwMaterialNum = nSize;
	m_VecMaterial.clear();
	UpdateListMaterial();
}

void CTabCPS::OnBnClickedMatCancel()
{
	UpdateListMaterial();
}

BOOL CTabCPS::UpdateListTrace()
{
	CString strTemp;
	m_list_trace.ResetContent();

	int nNum = (int)m_pPiece.m_vecTrace.size();
	for ( int i = 0; i < nNum; i++ )
	{
		strTemp.Format ("%d--Name:%s"
			,i
			,m_pPiece.m_vecTrace[i].m_szName
			);

		int nData = m_list_trace.InsertString(i, strTemp);
	}

	SetWin_ShowWindow ( this, IDC_EDIT_T_NAME, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_T_INDEX, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_T_VEC_X, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_T_VEC_Y, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_T_VEC_Z, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_T_NOR_X, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_T_NOR_Y, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_T_NOR_Z, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_LIST_TRACE_BONE, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_T_NUM, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EFF_T_ADD, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EFF_T_EDIT, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EFF_T_DEL, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_TRACE_CAN, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_TRACE_OK, SW_HIDE );

	SetWin_ShowWindow ( this, IDC_EDIT_T_B, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_T_W, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EFF_T_OK, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EFF_T_CAN, SW_HIDE );

	return TRUE;
}

void CTabCPS::OnBnClickedTraceAdd()
{
	SetWin_ShowWindow ( this, IDC_EDIT_T_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_T_INDEX, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_T_VEC_X, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_T_VEC_Y, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_T_VEC_Z, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_T_NOR_X, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_T_NOR_Y, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_T_NOR_Z, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_LIST_TRACE_BONE, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_T_NUM, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EFF_T_ADD, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EFF_T_EDIT, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EFF_T_DEL, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_TRACE_CAN, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_TRACE_OK, SW_SHOW );
	bAddBone = true;
	m_VecBone.clear();
	UpdateBoneList();
}

void CTabCPS::OnBnClickedTraceEdit()
{
	int nIndex = m_list_trace.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		SetWin_ShowWindow ( this, IDC_EDIT_T_NAME, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_T_INDEX, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_T_VEC_X, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_T_VEC_Y, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_T_VEC_Z, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_T_NOR_X, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_T_NOR_Y, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_T_NOR_Z, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_LIST_TRACE_BONE, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_T_NUM, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EFF_T_ADD, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EFF_T_EDIT, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EFF_T_DEL, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_TRACE_CAN, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_TRACE_OK, SW_SHOW );
		bAddBone = false;

		SetWin_Text ( this, IDC_EDIT_T_NAME ,m_pPiece.m_vecTrace[nIndex].m_szName );
		SetWin_Num_int ( this, IDC_EDIT_T_INDEX ,m_pPiece.m_vecTrace[nIndex].m_sVertexInflu.m_dwIndex );
		/*SetWin_Num_float_f ( this, IDC_EDIT_T_VEC_X ,m_pPiece.m_vecTrace[nIndex].m_sVertexInflu.m_vVector.x );
		SetWin_Num_float_f ( this, IDC_EDIT_T_VEC_Y ,m_pPiece.m_vecTrace[nIndex].m_sVertexInflu.m_vVector.y );
		SetWin_Num_float_f ( this, IDC_EDIT_T_VEC_Z ,m_pPiece.m_vecTrace[nIndex].m_sVertexInflu.m_vVector.z );
		SetWin_Num_float_f ( this, IDC_EDIT_T_NOR_X ,m_pPiece.m_vecTrace[nIndex].m_sVertexInflu.m_vNormal.x );
		SetWin_Num_float_f ( this, IDC_EDIT_T_NOR_Y ,m_pPiece.m_vecTrace[nIndex].m_sVertexInflu.m_vNormal.y );
		SetWin_Num_float_f ( this, IDC_EDIT_T_NOR_Z ,m_pPiece.m_vecTrace[nIndex].m_sVertexInflu.m_vNormal.z );*/
		SetWin_Num_int ( this, IDC_EDIT_T_NUM ,m_pPiece.m_vecTrace[nIndex].m_sVertexInflu.m_dwNumBone );
		
		m_VecBone.clear();

		int nNumBone = m_pPiece.m_vecTrace[nIndex].m_sVertexInflu.m_dwNumBone;
		for ( int i = 0; i < nNumBone; i++ )
		{
			TRACE_BONE_INFO	m_pBoneInfoX;
			m_pBoneInfoX.m_pBoneX = m_pPiece.m_vecTrace[nIndex].m_sVertexInflu.m_pBone[i];
			m_pBoneInfoX.m_pWeightsX = m_pPiece.m_vecTrace[nIndex].m_sVertexInflu.m_pWeights[i];
			m_VecBone.push_back( m_pBoneInfoX );
		}
		
		UpdateBoneList();
		nEditTraceID = nIndex;
	}
}

void CTabCPS::OnBnClickedTraceDel()
{
	int nIndex = m_list_trace.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		if ( MessageBox ( "Are you sure you want to Delete?", "Question", MB_YESNO ) == IDYES )
		{
			m_pPiece.m_vecTrace.erase(m_pPiece.m_vecTrace.begin()+nIndex );	
			UpdateListTrace();
		}
	}
}

void CTabCPS::OnBnClickedTraceCan()
{
	if (bAddBone) bAddBone = false;
	UpdateListTrace();
}

void CTabCPS::OnBnClickedTraceOk()
{
	STRACOR		TraceX;
	StringCchCopy( TraceX.m_szName, 32, GetWin_Text( this, IDC_EDIT_T_NAME ).GetString() );
	TraceX.m_sVertexInflu.m_dwIndex = GetWin_Num_int ( this, IDC_EDIT_T_INDEX);
	TraceX.m_sVertexInflu.m_vVector.x = GetWin_Num_float ( this, IDC_EDIT_T_VEC_X );
	TraceX.m_sVertexInflu.m_vVector.y = GetWin_Num_float ( this, IDC_EDIT_T_VEC_Y );
	TraceX.m_sVertexInflu.m_vVector.z = GetWin_Num_float ( this, IDC_EDIT_T_VEC_Z );
	TraceX.m_sVertexInflu.m_vNormal.x = GetWin_Num_float ( this, IDC_EDIT_T_NOR_X );
	TraceX.m_sVertexInflu.m_vNormal.y = GetWin_Num_float ( this, IDC_EDIT_T_NOR_Y );
	TraceX.m_sVertexInflu.m_vNormal.z = GetWin_Num_float ( this, IDC_EDIT_T_NOR_Z );

	BONE_VEC_ITER iter = m_VecBone.begin();
	BONE_VEC_ITER iter_end = m_VecBone.end();

	int nSize  = (int)m_VecBone.size();
	TRACE_BONE_INFO*	m_pBoneInfoX;
	m_pBoneInfoX = new TRACE_BONE_INFO[nSize];

	TraceX.m_sVertexInflu.m_dwNumBone = nSize;
	for ( int i=0; iter!=iter_end; ++iter, ++i )
	{
		m_pBoneInfoX[i] = (*iter);
		TraceX.m_sVertexInflu.m_pBone[i] = m_pBoneInfoX[i].m_pBoneX;
		TraceX.m_sVertexInflu.m_pWeights[i] = m_pBoneInfoX[i].m_pWeightsX;
	}
	m_VecBone.clear();

	if ( !bAddBone )
	{
		m_pPiece.m_vecTrace.erase(m_pPiece.m_vecTrace.begin()+nEditTraceID );
	}
	m_pPiece.m_vecTrace.push_back(TraceX);

	UpdateListTrace();
}

void CTabCPS::UpdateBoneList()
{
	CString strTemp;
	m_list_trace_b.ResetContent();

	int nNum = (int)m_VecBone.size();
	for ( int i = 0; i < nNum; i++ )
	{
		strTemp.Format ("%d--Bone:%d--Weights:%f"
		,i
		,m_VecBone[i].m_pBoneX
		,m_VecBone[i].m_pWeightsX
		);

		m_list_trace_b.InsertString(i, strTemp);
	}

	SetWin_ShowWindow ( this, IDC_EDIT_T_B, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_T_W, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EFF_T_OK, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EFF_T_CAN, SW_HIDE );
}

void CTabCPS::OnBnClickedEffTAdd()
{
	SetWin_ShowWindow ( this, IDC_EDIT_T_B, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_T_W, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EFF_T_OK, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EFF_T_CAN, SW_SHOW );
	bAddBone_b = true;

	SetWin_ShowWindow ( this, IDC_TRACE_CAN, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_TRACE_OK, SW_HIDE );
}

void CTabCPS::OnBnClickedEffTEdit()
{
	int nIndex = m_list_trace_b.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		SetWin_ShowWindow ( this, IDC_EDIT_T_B, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_T_W, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EFF_T_OK, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EFF_T_CAN, SW_SHOW );
		bAddBone_b = false;
		nEditBoneTraceID = nIndex;

		SetWin_Num_int ( this, IDC_EDIT_T_B ,m_VecBone[nIndex].m_pBoneX );
		SetWin_Num_float ( this, IDC_EDIT_T_W ,m_VecBone[nIndex].m_pWeightsX );

		SetWin_ShowWindow ( this, IDC_TRACE_CAN, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_TRACE_OK, SW_HIDE );
	}
}

void CTabCPS::OnBnClickedEffTDel()
{
	int nIndex = m_list_trace_b.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		if ( MessageBox ( "Are you sure you want to Delete?", "Question", MB_YESNO ) == IDYES )
		{
			m_VecBone.erase(m_VecBone.begin()+nIndex );
			UpdateBoneList();
		}
	}
}

void CTabCPS::OnBnClickedEffTOk()
{
	TRACE_BONE_INFO	sTraceX;
	sTraceX.m_pBoneX = GetWin_Num_int ( this, IDC_EDIT_T_B);
	sTraceX.m_pWeightsX= GetWin_Num_float ( this, IDC_EDIT_T_W);

	if ( !bAddBone_b )
	{
		m_VecBone.erase(m_VecBone.begin()+nEditBoneTraceID  );
	}

	m_VecBone.push_back(sTraceX);

	UpdateBoneList();

	SetWin_ShowWindow ( this, IDC_TRACE_CAN, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_TRACE_OK, SW_SHOW );
}

void CTabCPS::OnBnClickedEffTCan()
{
	UpdateBoneList();
	SetWin_ShowWindow ( this, IDC_TRACE_CAN, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_TRACE_OK, SW_SHOW );
}

void CTabCPS::Reset()
{
	SetWin_Text ( this, IDC_EDIT_FILENAME, "" );
	m_pPiece.ClearAll();
	m_list_material.ResetContent();
	m_list_trace.ResetContent();
	m_list_trace_b.ResetContent();

	m_VecMaterial.clear();
	m_VecBone.clear();
	//m_pPiece.m_vecEFFECT.clear();
	//m_pPiece.m_vecTrace.clear();

	SetWin_ShowWindow ( this, IDC_BUTTON_CPS_SAVE, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_MAT_TEX, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_MAT_FLAG, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_MAT_BIAS, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_MAT_OK, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_MAT_CANCEL, SW_HIDE );

	SetWin_Text ( this, IDC_EDIT_SKELETON, "" );
	SetWin_Text ( this, IDC_EDIT_SKIN, "" );
	SetWin_Text ( this, IDC_EDIT_MESH, "" );
	SetWin_Combo_Sel ( this, IDC_COMBO_PIECE, (int)0 );
	SetWin_Combo_Sel ( this, IDC_COMBO_WEPBACK, (int)0);
	SetWin_Num_int ( this, IDC_EDIT_REF, 0 );
	SetWin_Num_int ( this, IDC_EDIT_FLAG, 0);


	SetWin_ShowWindow ( this, IDC_EDIT_T_NAME, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_T_INDEX, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_T_VEC_X, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_T_VEC_Y, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_T_VEC_Z, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_T_NOR_X, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_T_NOR_Y, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_T_NOR_Z, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_LIST_TRACE_BONE, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_T_NUM, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EFF_T_ADD, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EFF_T_EDIT, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EFF_T_DEL, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_TRACE_CAN, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_TRACE_OK, SW_HIDE );

	SetWin_Text ( this, IDC_EDIT_T_NAME ,"");
	SetWin_Num_int ( this, IDC_EDIT_T_INDEX ,0 );
	SetWin_Num_int ( this, IDC_EDIT_T_VEC_X ,0 );
	SetWin_Num_int ( this, IDC_EDIT_T_VEC_Y ,0 );
	SetWin_Num_int ( this, IDC_EDIT_T_VEC_Z ,0 );
	SetWin_Num_int ( this, IDC_EDIT_T_NOR_X ,0);
	SetWin_Num_int ( this, IDC_EDIT_T_NOR_Y ,0 );
	SetWin_Num_int ( this, IDC_EDIT_T_NOR_Z ,0 );
	SetWin_Num_int ( this, IDC_EDIT_T_NUM ,0 );

	SetWin_ShowWindow ( this, IDC_EDIT_MAT_TEX, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_MAT_FLAG, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_MAT_BIAS, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_MAT_OK, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_MAT_CANCEL, SW_HIDE );

	SetWin_Num_int ( this, IDC_EDIT_MAT_FLAG ,0 );
	SetWin_Num_int ( this, IDC_EDIT_MAT_BIAS ,0 );
	SetWin_Text ( this, IDC_EDIT_MAT_TEX, "" );

	m_bActive = FALSE;
	UpdateData();
}




