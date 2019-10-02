// XEffTexDiff.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffTexDiff.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"


// CEffTexDiff dialog

IMPLEMENT_DYNAMIC(CEffTexDiff, CPropertyPage)
CEffTexDiff::CEffTexDiff(LOGFONT logfont)
	: CPropertyPage(CEffTexDiff::IDD)
	,m_pFont( NULL )
	,EffTexDiffEdit(NULL)
	,m_pMaterials(NULL)
	,nMaterialSize(0)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffTexDiffEdit = new DxEffCharTexDiff;
}

CEffTexDiff::~CEffTexDiff()
{
}

void CEffTexDiff::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MAT, m_list_mat );
}


BEGIN_MESSAGE_MAP(CEffTexDiff, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_ADD, OnBnClickedButtonAdd)
	ON_BN_CLICKED(IDC_BUTTON_EDIT, OnBnClickedButtonEdit)
	ON_BN_CLICKED(IDC_BUTTON_DEL, OnBnClickedButtonDel)
	ON_BN_CLICKED(IDC_BUTTON_COPY, OnBnClickedButtonCopy)
	ON_BN_CLICKED(IDC_BUTTON_CLEAR, OnBnClickedButtonClear)
	ON_BN_CLICKED(IDC_BUTTON_AOK, OnBnClickedButtonAok)
	ON_BN_CLICKED(IDC_BUTTON_ACAN, OnBnClickedButtonAcan)
END_MESSAGE_MAP()


// CEffTexDiff message handlers
BOOL CEffTexDiff::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffTexDiff::SetEffTexDiff ( DxEffCharTexDiff*	EffTexDiffX)
{ 
	EffTexDiffEdit = EffTexDiffX; 
	Update();
}

void CEffTexDiff::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffTexDiffReturn( EffTexDiffEdit ,nMaterialSize);
	}
}

void CEffTexDiff::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

BOOL CEffTexDiff::Update()
{
	EFFCHAR_PROPERTY_TEXDIFF EffEdit = *((EFFCHAR_PROPERTY_TEXDIFF*)EffTexDiffEdit->GetProperty() );
	SetWin_Check ( this, IDC_CHECK_BFLAGS1, EffEdit.m_dwFlag&ISTEXTURE1 );
	SetWin_Check ( this, IDC_CHECK_BFLAGS2, EffEdit.m_dwFlag&ISTEXTURE2 );
	SetWin_Check ( this, IDC_CHECK_BFLAGS3, EffEdit.m_dwFlag&ISTEXTURE3 );
	SetWin_Check ( this, IDC_CHECK_BFLAGS4, EffEdit.m_dwFlag&ISTEXTURE4 );
	SetWin_Check ( this, IDC_CHECK_BFLAGS5, EffEdit.m_dwFlag&USETEXTURE1 );
	SetWin_Check ( this, IDC_CHECK_BFLAGS6, EffEdit.m_dwFlag&USETEXTURE2 );
	SetWin_Check ( this, IDC_CHECK_BFLAGS7, EffEdit.m_dwFlag&USETEXTURE3 );
	SetWin_Check ( this, IDC_CHECK_BFLAGS8, EffEdit.m_dwFlag&USETEXTURE4 );
	SetWin_Check ( this, IDC_CHECK_BFLAGS9, EffEdit.m_dwFlag&NO_UPDOWN );
	SetWin_Num_int ( this, IDC_EDIT_INTE,  EffEdit.m_dwIntensity );
	SetWin_Num_float( this, IDC_EDIT_SPE,  EffEdit.m_fSpeed );
	SetWin_Text ( this, IDC_EDIT_TEX,  EffEdit.m_strTex.c_str() );

	DXMATERIAL_CHAR_EFF* m_pMaterialsX = new DXMATERIAL_CHAR_EFF[EffEdit.m_dwMaterials];
	m_pMaterialsX = EffTexDiffEdit->GetMaterials();
	m_pVecMatX.clear();

	for ( DWORD i=0; i<EffEdit.m_dwMaterials; ++i )
	{
		m_pVecMatX.push_back(m_pMaterialsX[i]);
	}

	UpdateList();

	return TRUE;
}

BOOL CEffTexDiff::Save()
{
	EFFCHAR_PROPERTY_TEXDIFF* EffEdit = new EFFCHAR_PROPERTY_TEXDIFF;

	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_BFLAGS1 ), EffEdit->m_dwFlag,ISTEXTURE1 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_BFLAGS2 ), EffEdit->m_dwFlag,ISTEXTURE2 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_BFLAGS3 ), EffEdit->m_dwFlag,ISTEXTURE3 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_BFLAGS4 ), EffEdit->m_dwFlag,ISTEXTURE4 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_BFLAGS5 ), EffEdit->m_dwFlag,USETEXTURE1 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_BFLAGS6 ), EffEdit->m_dwFlag,USETEXTURE2 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_BFLAGS7 ), EffEdit->m_dwFlag,USETEXTURE3 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_BFLAGS8 ), EffEdit->m_dwFlag,USETEXTURE4 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_BFLAGS9 ), EffEdit->m_dwFlag,NO_UPDOWN );
	EffEdit->m_dwIntensity = GetWin_Num_int ( this, IDC_EDIT_INTE );
	EffEdit->m_fSpeed = GetWin_Num_float ( this, IDC_EDIT_SPE );
	EffEdit->m_strTex = GetWin_Text( this, IDC_EDIT_TEX ).GetString();

	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffTexDiffEdit->SetProperty(EffEditProp);

	int nSize = (int)m_pVecMatX.size();
	m_pMaterials = new DXMATERIAL_CHAR_EFF[nSize];
	EffEdit->m_dwMaterials = nSize;
	nMaterialSize = nSize;
	for ( int i=0; i<nSize; ++i )
	{
		m_pMaterials[i] = m_pVecMatX[i];
	}
	EffTexDiffEdit->SetMaterials(NULL,nSize,m_pMaterials);
	m_pVecMatX.clear();

	return TRUE;
}

BOOL CEffTexDiff::UpdateList()
{
	CString strTemp;
	m_list_mat.ResetContent();

	for ( DWORD i=0; i<m_pVecMatX.size(); i++ )
	{
		strTemp.Format ("%d-MainTex:%s---EffTex:%s"
		,i
		,m_pVecMatX[i].szTexture
		,m_pVecMatX[i].szEffTex
		);
		m_list_mat.InsertString(i, strTemp);
	}

	SetWin_ShowWindow ( this, IDC_EFFUSE, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_D1, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_D2, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_D3, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_D4, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_A1, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_A2, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_A3, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_A4, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_S1, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_S2, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_S3, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_S4, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_E1, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_E2, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_E3, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_E4, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_APOWER, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_ATEX, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_AEFF, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_AOK, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_ACAN, SW_HIDE );

	return TRUE;
}

void CEffTexDiff::OnBnClickedButtonAdd()
{
	SetWin_ShowWindow ( this, IDC_EFFUSE, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_D1, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_D2, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_D3, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_D4, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_A1, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_A2, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_A3, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_A4, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_S1, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_S2, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_S3, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_S4, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_E1, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_E2, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_E3, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_E4, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_APOWER, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_ATEX, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_AEFF, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_AOK, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_ACAN, SW_SHOW );

	DXMATERIAL_CHAR_EFF* m_pMat = new DXMATERIAL_CHAR_EFF;

	SetWin_Check ( this, IDC_EFFUSE, m_pMat->bEffUse );
	SetWin_Num_float ( this, IDC_EDIT_D1, m_pMat->d3dMaterial.Diffuse.r );
	SetWin_Num_float ( this, IDC_EDIT_D2, m_pMat->d3dMaterial.Diffuse.g );
	SetWin_Num_float ( this, IDC_EDIT_D3, m_pMat->d3dMaterial.Diffuse.b );
	SetWin_Num_float ( this, IDC_EDIT_D4, m_pMat->d3dMaterial.Diffuse.a );
	SetWin_Num_float ( this, IDC_EDIT_A1, m_pMat->d3dMaterial.Ambient.r );
	SetWin_Num_float ( this, IDC_EDIT_A2, m_pMat->d3dMaterial.Ambient.g );
	SetWin_Num_float ( this, IDC_EDIT_A3, m_pMat->d3dMaterial.Ambient.b );
	SetWin_Num_float ( this, IDC_EDIT_A4, m_pMat->d3dMaterial.Ambient.a );
	SetWin_Num_float ( this, IDC_EDIT_S1, m_pMat->d3dMaterial.Specular.r );
	SetWin_Num_float ( this, IDC_EDIT_S2, m_pMat->d3dMaterial.Specular.g );
	SetWin_Num_float ( this, IDC_EDIT_S3, m_pMat->d3dMaterial.Specular.b );
	SetWin_Num_float ( this, IDC_EDIT_S4, m_pMat->d3dMaterial.Specular.a );
	SetWin_Num_float ( this, IDC_EDIT_E1, m_pMat->d3dMaterial.Emissive.r );
	SetWin_Num_float ( this, IDC_EDIT_E2, m_pMat->d3dMaterial.Emissive.g );
	SetWin_Num_float ( this, IDC_EDIT_E3, m_pMat->d3dMaterial.Emissive.b );
	SetWin_Num_float ( this, IDC_EDIT_E4, m_pMat->d3dMaterial.Emissive.a );
	SetWin_Num_float ( this, IDC_EDIT_APOWER, m_pMat->d3dMaterial.Power );
	SetWin_Text ( this, IDC_EDIT_ATEX, m_pMat->szTexture );
	SetWin_Text ( this, IDC_EDIT_AEFF, m_pMat->szEffTex );
	bAdd = true;

	SetWin_ShowWindow ( this, IDC_BUTTON_CANCEL, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_OK, SW_HIDE );
}

void CEffTexDiff::OnBnClickedButtonEdit()
{
	int nIndex = m_list_mat.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		SetWin_ShowWindow ( this, IDC_EFFUSE, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_D1, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_D2, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_D3, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_D4, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_A1, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_A2, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_A3, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_A4, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_S1, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_S2, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_S3, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_S4, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_E1, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_E2, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_E3, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_E4, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_APOWER, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_ATEX, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_AEFF, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_BUTTON_AOK, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_BUTTON_ACAN, SW_SHOW );

		SetWin_Check ( this, IDC_EFFUSE, m_pVecMatX[nIndex].bEffUse );
		SetWin_Num_float ( this, IDC_EDIT_D1, m_pVecMatX[nIndex].d3dMaterial.Diffuse.r );
		SetWin_Num_float ( this, IDC_EDIT_D2, m_pVecMatX[nIndex].d3dMaterial.Diffuse.g );
		SetWin_Num_float ( this, IDC_EDIT_D3, m_pVecMatX[nIndex].d3dMaterial.Diffuse.b );
		SetWin_Num_float ( this, IDC_EDIT_D4, m_pVecMatX[nIndex].d3dMaterial.Diffuse.a );
		SetWin_Num_float ( this, IDC_EDIT_A1, m_pVecMatX[nIndex].d3dMaterial.Ambient.r );
		SetWin_Num_float ( this, IDC_EDIT_A2, m_pVecMatX[nIndex].d3dMaterial.Ambient.g );
		SetWin_Num_float ( this, IDC_EDIT_A3, m_pVecMatX[nIndex].d3dMaterial.Ambient.b );
		SetWin_Num_float ( this, IDC_EDIT_A4, m_pVecMatX[nIndex].d3dMaterial.Ambient.a );
		SetWin_Num_float ( this, IDC_EDIT_S1, m_pVecMatX[nIndex].d3dMaterial.Specular.r );
		SetWin_Num_float ( this, IDC_EDIT_S2, m_pVecMatX[nIndex].d3dMaterial.Specular.g );
		SetWin_Num_float ( this, IDC_EDIT_S3, m_pVecMatX[nIndex].d3dMaterial.Specular.b );
		SetWin_Num_float ( this, IDC_EDIT_S4, m_pVecMatX[nIndex].d3dMaterial.Specular.a );
		SetWin_Num_float ( this, IDC_EDIT_E1, m_pVecMatX[nIndex].d3dMaterial.Emissive.r );
		SetWin_Num_float ( this, IDC_EDIT_E2, m_pVecMatX[nIndex].d3dMaterial.Emissive.g );
		SetWin_Num_float ( this, IDC_EDIT_E3, m_pVecMatX[nIndex].d3dMaterial.Emissive.b );
		SetWin_Num_float ( this, IDC_EDIT_E4, m_pVecMatX[nIndex].d3dMaterial.Emissive.a );
		SetWin_Num_float ( this, IDC_EDIT_APOWER, m_pVecMatX[nIndex].d3dMaterial.Power );
		SetWin_Text ( this, IDC_EDIT_ATEX, m_pVecMatX[nIndex].szTexture );
		SetWin_Text ( this, IDC_EDIT_AEFF, m_pVecMatX[nIndex].szEffTex );
		nLastEdit = nIndex;
		bAdd = false;

		SetWin_ShowWindow ( this, IDC_BUTTON_CANCEL, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_BUTTON_OK, SW_HIDE );
	}
}

void CEffTexDiff::OnBnClickedButtonDel()
{
	int nIndex = m_list_mat.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		if ( MessageBox ( "Are you sure you want to Delete?", "Question", MB_YESNO ) == IDYES )
		{
			m_pVecMatX.erase(m_pVecMatX.begin()+nIndex );
			UpdateList();
		}
	}
}

void CEffTexDiff::OnBnClickedButtonCopy()
{
	int nIndex = m_list_mat.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		m_pVecMatX.push_back(m_pVecMatX[nIndex]);
		UpdateList();
	}
}

void CEffTexDiff::OnBnClickedButtonClear()
{
	if ( MessageBox ( "Are you sure you want to Delete All?", "Question", MB_YESNO ) == IDYES )
	{
		m_pVecMatX.clear();
		UpdateList();
	}
}

void CEffTexDiff::OnBnClickedButtonAok()
{
	DXMATERIAL_CHAR_EFF* m_pMat = new DXMATERIAL_CHAR_EFF;

	m_pMat->bEffUse = GetWin_Check( this, IDC_EFFUSE );
	m_pMat->d3dMaterial.Diffuse.r = GetWin_Num_float( this, IDC_EDIT_D1 );
	m_pMat->d3dMaterial.Diffuse.g = GetWin_Num_float( this, IDC_EDIT_D2 );
	m_pMat->d3dMaterial.Diffuse.b = GetWin_Num_float( this, IDC_EDIT_D3 );
	m_pMat->d3dMaterial.Diffuse.a = GetWin_Num_float( this, IDC_EDIT_D4 );
	m_pMat->d3dMaterial.Ambient.r = GetWin_Num_float( this, IDC_EDIT_A1 );
	m_pMat->d3dMaterial.Ambient.g = GetWin_Num_float( this, IDC_EDIT_A2 );
	m_pMat->d3dMaterial.Ambient.b = GetWin_Num_float( this, IDC_EDIT_A3 );
	m_pMat->d3dMaterial.Ambient.a = GetWin_Num_float( this, IDC_EDIT_A4 );
	m_pMat->d3dMaterial.Specular.r = GetWin_Num_float( this, IDC_EDIT_S1 );
	m_pMat->d3dMaterial.Specular.g = GetWin_Num_float( this, IDC_EDIT_S2 );
	m_pMat->d3dMaterial.Specular.b = GetWin_Num_float( this, IDC_EDIT_S3 );
	m_pMat->d3dMaterial.Specular.a = GetWin_Num_float( this, IDC_EDIT_S4 );
	m_pMat->d3dMaterial.Emissive.r = GetWin_Num_float( this, IDC_EDIT_E1 );
	m_pMat->d3dMaterial.Emissive.g = GetWin_Num_float( this, IDC_EDIT_E2 );
	m_pMat->d3dMaterial.Emissive.b = GetWin_Num_float( this, IDC_EDIT_E3 );
	m_pMat->d3dMaterial.Emissive.a = GetWin_Num_float( this, IDC_EDIT_E4 );
	m_pMat->d3dMaterial.Power = GetWin_Num_float( this, IDC_EDIT_APOWER );
	StringCchCopy( m_pMat->szTexture, MAX_PATH, GetWin_Text( this, IDC_EDIT_ATEX ).GetString() );
	StringCchCopy( m_pMat->szEffTex, MAX_PATH, GetWin_Text( this, IDC_EDIT_AEFF ).GetString() );

	if (!bAdd )	m_pVecMatX.erase(m_pVecMatX.begin()+nLastEdit );

	m_pVecMatX.push_back(*m_pMat);
	UpdateList();

	SetWin_ShowWindow ( this, IDC_BUTTON_CANCEL, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_OK, SW_SHOW );
}

void CEffTexDiff::OnBnClickedButtonAcan()
{
	UpdateList();
	SetWin_ShowWindow ( this, IDC_BUTTON_CANCEL, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_OK, SW_SHOW );
}
