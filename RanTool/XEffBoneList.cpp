// XEffBoneList.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffBoneList.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"
#include ".\xeffbonelist.h"



// CEffBoneList dialog

IMPLEMENT_DYNAMIC(CEffBoneList, CPropertyPage)
CEffBoneList::CEffBoneList(LOGFONT logfont)
	: CPropertyPage(CEffBoneList::IDD)
	,m_pFont( NULL )
	,EffBoneListEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffBoneListEdit = new DxEffCharBoneListEff;
	bAdd = false;
}

CEffBoneList::~CEffBoneList()
{
}

void CEffBoneList::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_VEC, m_list_vec );
}


BEGIN_MESSAGE_MAP(CEffBoneList, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_BLADD, OnBnClickedButtonBladd)
	ON_BN_CLICKED(IDC_BUTTON_BLEDIT, OnBnClickedButtonBledit)
	ON_BN_CLICKED(IDC_BUTTON_BLDEL, OnBnClickedButtonBldel)
	ON_BN_CLICKED(IDC_BUTTON_BLCLR, OnBnClickedButtonBlclr)
	ON_BN_CLICKED(IDC_BUTTON_BLUP, OnBnClickedButtonBlup)
	ON_BN_CLICKED(IDC_BUTTON_BLDN, OnBnClickedButtonBldn)
	ON_BN_CLICKED(IDC_BUTTON_BLCAN, OnBnClickedButtonBlcan)
	ON_BN_CLICKED(IDC_BUTTON_BLOK, OnBnClickedButtonBlok)
END_MESSAGE_MAP()


// CEffBoneList message handlers
BOOL CEffBoneList::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffBoneList::SetEffBoneList ( DxEffCharBoneListEff*	EffBoneListX)
{ 
	EffBoneListEdit = EffBoneListX; 
	Update();
}

void CEffBoneList::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffBoneListReturn( EffBoneListEdit );
	}
}

void CEffBoneList::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

BOOL CEffBoneList::Update()
{
	EFFCHAR_PROPERTY_BONELISTEFF EffEdit = *((EFFCHAR_PROPERTY_BONELISTEFF*)EffBoneListEdit->GetProperty() );

	SetWin_Check ( this, IDC_CHECK_BPFLAG1, EffEdit.m_dwFlag&USE_REMAIN );
	SetWin_Check ( this, IDC_CHECK_BPFLAG2, EffEdit.m_dwFlag&USE_ABSOLUTE );
	SetWin_Check ( this, IDC_CHECK_BPFLAG3, EffEdit.m_dwFlag&USE_RANDOMRANGE );
	SetWin_Check ( this, IDC_CHECK_BPFLAG4, EffEdit.m_dwFlag&USE_SEQUENCE );
	SetWin_Check ( this, IDC_CHECK_BPFLAG5, EffEdit.m_dwFlag&USE_ROTATE );
	SetWin_Check ( this, IDC_CHECK_BPFLAG6, EffEdit.m_dwFlag&USE_PLAY );
	SetWin_Check ( this, IDC_CHECK_BPFLAG7, EffEdit.m_dwFlag&USE_POS1 );
	SetWin_Num_int ( this, IDC_EDIT_PPEC,  EffEdit.m_dwParticlePec );

	D3DCOLOR color = EffEdit.m_dwColor;
	DWORD a = color >> 24;
	DWORD r = (color >> 16) & 0xFF;
	DWORD g = (color >> 8 ) & 0xFF;
	DWORD b = color & 0xFF;
	SetWin_Num_int ( this, IDC_EDIT_DCOL1,  a );
	SetWin_Num_int ( this, IDC_EDIT_DCOL2,  r );
	SetWin_Num_int ( this, IDC_EDIT_DCOL3,  g );
	SetWin_Num_int ( this, IDC_EDIT_DCOL4,  b );

	SetWin_Num_float ( this, IDC_EDIT_VLIFE1,  EffEdit.m_vLife.x );
	SetWin_Num_float ( this, IDC_EDIT_VLIFE2,  EffEdit.m_vLife.y );
	SetWin_Num_float ( this, IDC_EDIT_VROT1,  EffEdit.m_vRotate.x );
	SetWin_Num_float ( this, IDC_EDIT_VROT2,  EffEdit.m_vRotate.y );
	SetWin_Num_float ( this, IDC_EDIT_VVEL1,  EffEdit.m_vVelocity.x );
	SetWin_Num_float ( this, IDC_EDIT_VVEL2,  EffEdit.m_vVelocity.y );
	SetWin_Num_float ( this, IDC_EDIT_VSIZE1_1,  EffEdit.m_vSize.x );
	SetWin_Num_float ( this, IDC_EDIT_VSIZE1_2,  EffEdit.m_vSize.y );
	SetWin_Num_float ( this, IDC_EDIT_VSIZE1_3,  EffEdit.m_vSize.z );
	SetWin_Num_int ( this, IDC_EDIT_SCOL,  EffEdit.m_dwSequenceCol );
	SetWin_Num_int ( this, IDC_EDIT_SROW,  EffEdit.m_dwSequenceRow );
	SetWin_Num_float ( this, IDC_EDIT_CLE,  EffEdit.m_fCreateLength );
	SetWin_Text ( this, IDC_EDIT_TXTEXT,  EffEdit.m_szTexture );

	UpdateList();

	return TRUE;
}

BOOL CEffBoneList::Save()
{
	EFFCHAR_PROPERTY_BONELISTEFF* EffEdit = new EFFCHAR_PROPERTY_BONELISTEFF;
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_BPFLAG1 ), EffEdit->m_dwFlag,USE_REMAIN );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_BPFLAG2 ), EffEdit->m_dwFlag,USE_ABSOLUTE );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_BPFLAG3 ), EffEdit->m_dwFlag,USE_RANDOMRANGE );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_BPFLAG4 ), EffEdit->m_dwFlag,USE_SEQUENCE );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_BPFLAG5 ), EffEdit->m_dwFlag,USE_ROTATE );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_BPFLAG6 ), EffEdit->m_dwFlag,USE_PLAY );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_BPFLAG7 ), EffEdit->m_dwFlag,USE_POS1 );
	EffEdit->m_dwParticlePec = GetWin_Num_int ( this, IDC_EDIT_PPEC );	

	BYTE a,r,g,b;
	a = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_DCOL1 );
	r = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_DCOL2 );
	g = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_DCOL3 );
	b = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_DCOL4 );
	EffEdit->m_dwColor = D3DCOLOR_ARGB(a,r,g,b);

	EffEdit->m_vLife.x = GetWin_Num_float ( this, IDC_EDIT_VLIFE1 );	
	EffEdit->m_vLife.y = GetWin_Num_float ( this, IDC_EDIT_VLIFE2 );	
	EffEdit->m_vRotate.x = GetWin_Num_float ( this, IDC_EDIT_VROT1 );	
	EffEdit->m_vRotate.y = GetWin_Num_float ( this, IDC_EDIT_VROT2 );	
	EffEdit->m_vVelocity.x = GetWin_Num_float ( this, IDC_EDIT_VVEL1 );	
	EffEdit->m_vVelocity.y = GetWin_Num_float ( this, IDC_EDIT_VVEL2 );	
	EffEdit->m_vSize.x = GetWin_Num_float ( this, IDC_EDIT_VSIZE1_1 );	
	EffEdit->m_vSize.y = GetWin_Num_float ( this, IDC_EDIT_VSIZE1_2 );	
	EffEdit->m_vSize.z = GetWin_Num_float ( this, IDC_EDIT_VSIZE1_3 );	
	EffEdit->m_dwSequenceCol = GetWin_Num_int ( this,  IDC_EDIT_SCOL );	
	EffEdit->m_dwSequenceRow = GetWin_Num_int ( this,  IDC_EDIT_SROW );	
	EffEdit->m_fCreateLength = GetWin_Num_float ( this, IDC_EDIT_CLE );	
	StringCchCopy( EffEdit->m_szTexture, BONELISTEFF_TEXNAME_SIZE, GetWin_Text( this, IDC_EDIT_TXTEXT ).GetString() );

	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffBoneListEdit->SetProperty(EffEditProp);

	return TRUE;
}

BOOL CEffBoneList::UpdateList()
{
	int nNum = EffBoneListEdit->GetCustomBoneSize();

	CString strTemp;
	m_list_vec.ResetContent();

	for ( int i=0; i<nNum; i++ )
	{
		strTemp.Format ("%d---[%s]"
		,i
		,EffBoneListEdit->GetBoneString(i).c_str()
		);
		m_list_vec.InsertString(i, strTemp);
	}

	SetWin_ShowWindow ( this, IDC_EDIT_BONEN, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_CHECK_BVERT, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_VVR1, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_VVR2, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_VVR3, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_BLOK, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_BLCAN, SW_HIDE );

	return TRUE;
}

void CEffBoneList::OnBnClickedButtonBladd()
{
	SetWin_ShowWindow ( this, IDC_EDIT_BONEN, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_CHECK_BVERT, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_VVR1, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_VVR2, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_VVR3, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_BLOK, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_BLCAN, SW_SHOW );
	SetWin_Num_float ( this, IDC_EDIT_VVR1,  0.0f );
	SetWin_Num_float ( this, IDC_EDIT_VVR2,  0.0f );
	SetWin_Num_float ( this, IDC_EDIT_VVR3,  0.0f );
	SetWin_Text ( this, IDC_EDIT_BONEN,   "" );
	bAdd = true;

	SetWin_ShowWindow ( this, IDC_BUTTON_CANCEL, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_OK, SW_HIDE );
}

void CEffBoneList::OnBnClickedButtonBledit()
{
	int nIndex = m_list_vec.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		SetWin_ShowWindow ( this, IDC_EDIT_BONEN, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_CHECK_BVERT, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_VVR1, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_VVR2, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_VVR3, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_BUTTON_BLOK, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_BUTTON_BLCAN, SW_SHOW );
		//SetWin_Num_float_f ( this, IDC_EDIT_VVR1,  EffBoneListEdit->GetSelectedBoneData(nIndex).vVertex.x );
		//SetWin_Num_float_f ( this, IDC_EDIT_VVR2,  EffBoneListEdit->GetSelectedBoneData(nIndex).vVertex.y );
		//SetWin_Num_float_f ( this, IDC_EDIT_VVR3,  EffBoneListEdit->GetSelectedBoneData(nIndex).vVertex.z );
		SetWin_Text ( this, IDC_EDIT_BONEN,   EffBoneListEdit->GetSelectedBoneData(nIndex).strBoneName.c_str() );
		SetWin_Check ( this, IDC_CHECK_BVERT,  EffBoneListEdit->GetSelectedBoneData(nIndex).bVertex );
		bAdd = false;
		nLastEdit = nIndex;

		SetWin_ShowWindow ( this, IDC_BUTTON_CANCEL, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_BUTTON_OK, SW_HIDE );
	}
}

void CEffBoneList::OnBnClickedButtonBldel()
{
	int nIndex = m_list_vec.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		if ( MessageBox ( "Are you sure you want to Delete?", "Question", MB_YESNO ) == IDYES )
		{
			EffBoneListEdit->DeleteBone(nIndex);
			UpdateList();
		}
	}
}

void CEffBoneList::OnBnClickedButtonBlclr()
{
	if ( MessageBox ( "Are you sure you want to Delete All?", "Question", MB_YESNO ) == IDYES )
	{
		EffBoneListEdit->ClearAllBone();
		UpdateList();
	}
}

void CEffBoneList::OnBnClickedButtonBlup()
{
	int nIndex = m_list_vec.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		EffBoneListEdit->DataUp(nIndex);
		UpdateList();
	}
}

void CEffBoneList::OnBnClickedButtonBldn()
{
	int nIndex = m_list_vec.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		EffBoneListEdit->DataDown(nIndex);
		UpdateList();
	}
}

void CEffBoneList::OnBnClickedButtonBlcan()
{
	UpdateList();
	SetWin_ShowWindow ( this, IDC_BUTTON_CANCEL, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_OK, SW_SHOW );
}

void CEffBoneList::OnBnClickedButtonBlok()
{
	DXCUSTOMBONE	sCBoneNew;
	sCBoneNew.strBoneName = GetWin_Text( this, IDC_EDIT_BONEN ).GetString();

	sCBoneNew.bVertex = GetWin_Check ( this, IDC_CHECK_BVERT );
	sCBoneNew.vVertex.x = GetWin_Num_float ( this, IDC_EDIT_VVR1 );	
	sCBoneNew.vVertex.y = GetWin_Num_float ( this, IDC_EDIT_VVR2 );	
	sCBoneNew.vVertex.z = GetWin_Num_float ( this, IDC_EDIT_VVR3 );	

	CString szFilterInput = "Bone (*.x)|*.x|";
	CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
	dlgInput.m_ofn.lpstrInitialDir = DxSkinPieceContainer::GetInstance().GetPath();
	if ( dlgInput.DoModal() != IDOK ) return;

	DxSkeleton*		m_pSkeletonX =  new DxSkeleton;
	HRESULT hr = m_pSkeletonX->LoadFile( dlgInput.GetFileName(),NULL );
	if (FAILED(hr))
	{
		MessageBox("Error Loading Bone","Error",MB_OK);
	}
	else
	{
		sCBoneNew.pBoneTran = m_pSkeletonX->FindBone( sCBoneNew.strBoneName.c_str() );

		if ( sCBoneNew.pBoneTran )
		{
			if (!bAdd)	EffBoneListEdit->DeleteBone(nLastEdit);
			EffBoneListEdit->InsertBoneTool( sCBoneNew );
			UpdateList();
		}
	}

	SetWin_ShowWindow ( this, IDC_BUTTON_CANCEL, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_OK, SW_SHOW );
}
