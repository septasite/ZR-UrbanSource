// XEffNeon.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffNeon.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"


// CEffNeon dialog

IMPLEMENT_DYNAMIC(CEffNeon, CPropertyPage)
CEffNeon::CEffNeon(LOGFONT logfont)
	: CPropertyPage(CEffNeon::IDD)
	,m_pFont( NULL )
	,EffNeonEdit(NULL)
	,m_pMaterials(NULL)
	,nMaterialSize(0)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffNeonEdit = new DxEffCharNeon;
}

CEffNeon::~CEffNeon()
{
}

void CEffNeon::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MAT, m_list_mat );
}


BEGIN_MESSAGE_MAP(CEffNeon, CPropertyPage)
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


// CEffNeon message handlers
BOOL CEffNeon::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffNeon::SetEffNeon ( DxEffCharNeon*	EffNeonX)
{ 
	EffNeonEdit = EffNeonX; 
	Update();
}

void CEffNeon::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffNeonReturn( EffNeonEdit ,nMaterialSize);
	}
}

void CEffNeon::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

BOOL CEffNeon::Update()
{
	EFFCHAR_PROPERTY_NEON EffEdit = *((EFFCHAR_PROPERTY_NEON*)EffNeonEdit->GetProperty() );

	SetWin_Check ( this, IDC_CHECK_NFLAG1, EffEdit.m_dwFlag&ISTEXTURE1 );
	SetWin_Check ( this, IDC_CHECK_NFLAG2, EffEdit.m_dwFlag&ISTEXTURE2 );
	SetWin_Check ( this, IDC_CHECK_NFLAG3, EffEdit.m_dwFlag&ISTEXTURE3 );
	SetWin_Check ( this, IDC_CHECK_NFLAG4, EffEdit.m_dwFlag&USETEXTURE1 );
	SetWin_Check ( this, IDC_CHECK_NFLAG5, EffEdit.m_dwFlag&USETEXTURE2 );
	SetWin_Check ( this, IDC_CHECK_NFLAG6, EffEdit.m_dwFlag&USETEXTURE3 );
	SetWin_Check ( this, IDC_CHECK_NFLAG7, EffEdit.m_dwFlag&USEDIFFUSE );
	SetWin_Check ( this, IDC_CHECK_NFLAG8, EffEdit.m_dwFlag&USEDIFFUSE2 );
	SetWin_Check ( this, IDC_CHECK_NFLAG9, EffEdit.m_dwFlag&USEDIFFUSE3 );
	SetWin_Check ( this, IDC_CHECK_NFLAG10, EffEdit.m_dwFlag&USE_ALL_TEX );
	SetWin_Check ( this, IDC_CHECK_NFLAG11, EffEdit.m_dwFlag&USE_SELECT_TEX );
	SetWin_Check ( this, IDC_CHECK_NFLAG12, EffEdit.m_dwFlag&USE_GLOW_SRCTEX );
	SetWin_Check ( this, IDC_CHECK_NFLAG13, EffEdit.m_dwFlag&USE_GLOW_USER );
	SetWin_Check ( this, IDC_CHECK_NFLAG14, EffEdit.m_dwFlag&USE_GENERAL );
	SetWin_Check ( this, IDC_CHECK_NFLAG15, EffEdit.m_dwFlag&USE_BURN );

	D3DCOLOR color = EffEdit.m_cColor;
	DWORD a = color >> 24;
	DWORD r = (color >> 16) & 0xFF;
	DWORD g = (color >> 8 ) & 0xFF;
	DWORD b = color & 0xFF;
	SetWin_Num_int ( this, IDC_EDIT_COL1,  a );
	SetWin_Num_int ( this, IDC_EDIT_COL2,  r );
	SetWin_Num_int ( this, IDC_EDIT_COL3,  g );
	SetWin_Num_int ( this, IDC_EDIT_COL4,  b );

	SetWin_Text ( this, IDC_EDIT_TEXTURE, EffEdit.m_szTexture );

	DXMATERIAL_CHAR_EFF* m_pMaterialsX = new DXMATERIAL_CHAR_EFF[EffEdit.m_dwMaterials];
	m_pMaterialsX = EffNeonEdit->GetMaterials();
	m_pVecMatX.clear();

	for ( DWORD i=0; i<EffEdit.m_dwMaterials; ++i )
	{
		m_pVecMatX.push_back(m_pMaterialsX[i]);
	}

	UpdateList();

	return TRUE;
}

BOOL CEffNeon::Save()
{
	EFFCHAR_PROPERTY_NEON* EffEdit = new EFFCHAR_PROPERTY_NEON;
	
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_NFLAG1 ), EffEdit->m_dwFlag,ISTEXTURE1 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_NFLAG2 ), EffEdit->m_dwFlag,ISTEXTURE2 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_NFLAG3 ), EffEdit->m_dwFlag,ISTEXTURE3 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_NFLAG4 ), EffEdit->m_dwFlag,USETEXTURE1 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_NFLAG5 ), EffEdit->m_dwFlag,USETEXTURE2 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_NFLAG6 ), EffEdit->m_dwFlag,USETEXTURE3 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_NFLAG7 ), EffEdit->m_dwFlag,USEDIFFUSE );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_NFLAG8 ), EffEdit->m_dwFlag,USEDIFFUSE2 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_NFLAG9 ), EffEdit->m_dwFlag,USEDIFFUSE3 );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_NFLAG10 ), EffEdit->m_dwFlag,USE_ALL_TEX );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_NFLAG11 ), EffEdit->m_dwFlag,USE_SELECT_TEX );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_NFLAG12 ), EffEdit->m_dwFlag,USE_GLOW_SRCTEX );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_NFLAG13 ), EffEdit->m_dwFlag,USE_GLOW_USER );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_NFLAG14 ), EffEdit->m_dwFlag,USE_GENERAL );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_NFLAG15 ), EffEdit->m_dwFlag,USE_BURN );

	BYTE a,r,g,b;
	a = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_COL1 );
	r = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_COL2 );
	g = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_COL3 );
	b = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_COL4 );
	EffEdit->m_cColor = D3DCOLOR_ARGB(a,r,g,b);

	StringCchCopy( EffEdit->m_szTexture, MAX_PATH, GetWin_Text( this, IDC_EDIT_TEXTURE ).GetString() );

	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffNeonEdit->SetProperty(EffEditProp);

	int nSize = (int)m_pVecMatX.size();
	m_pMaterials = new DXMATERIAL_CHAR_EFF[nSize];
	EffEdit->m_dwMaterials = nSize;
	nMaterialSize = nSize;
	for ( int i=0; i<nSize; ++i )
	{
		m_pMaterials[i] = m_pVecMatX[i];
	}
	EffNeonEdit->SetMaterials(NULL,nSize,m_pMaterials);
	m_pVecMatX.clear();

	return TRUE;
}

BOOL CEffNeon::UpdateList()
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

void CEffNeon::OnBnClickedButtonAdd()
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

void CEffNeon::OnBnClickedButtonEdit()
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

void CEffNeon::OnBnClickedButtonDel()
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

void CEffNeon::OnBnClickedButtonCopy()
{
	int nIndex = m_list_mat.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		m_pVecMatX.push_back(m_pVecMatX[nIndex]);
		UpdateList();
	}
}

void CEffNeon::OnBnClickedButtonClear()
{
	if ( MessageBox ( "Are you sure you want to Delete All?", "Question", MB_YESNO ) == IDYES )
	{
		m_pVecMatX.clear();
		UpdateList();
	}
}

void CEffNeon::OnBnClickedButtonAok()
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

void CEffNeon::OnBnClickedButtonAcan()
{
	UpdateList();

	SetWin_ShowWindow ( this, IDC_BUTTON_CANCEL, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_OK, SW_SHOW );
}
