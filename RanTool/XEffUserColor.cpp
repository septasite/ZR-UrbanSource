// XEffUserColor.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffUserColor.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"


// CEffUserColor dialog

IMPLEMENT_DYNAMIC(CEffUserColor, CPropertyPage)
CEffUserColor::CEffUserColor(LOGFONT logfont)
	: CPropertyPage(CEffUserColor::IDD)
	,m_pFont( NULL )
	,EffUserColorEdit(NULL)
	,m_pMaterials(NULL)
	,nMaterialSize(0)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffUserColorEdit = new DxEffCharUserColor;
}

CEffUserColor::~CEffUserColor()
{
}

void CEffUserColor::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MAT, m_list_mat );
}


BEGIN_MESSAGE_MAP(CEffUserColor, CPropertyPage)
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


// CEffUserColor message handlers
BOOL CEffUserColor::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffUserColor::SetEffUserColor ( DxEffCharUserColor*	EffUserColorX)
{ 
	EffUserColorEdit = EffUserColorX; 
	Update();
}

void CEffUserColor::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffUserColorReturn( EffUserColorEdit ,nMaterialSize);
	}
}

void CEffUserColor::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

BOOL CEffUserColor::Update()
{
	EFFCHAR_PROPERTY_USERCOLOR EffEdit = *((EFFCHAR_PROPERTY_USERCOLOR*)EffUserColorEdit->GetProperty() );
	SetWin_Check ( this, IDC_CHECK_UCFLAG1, EffEdit.m_dwFlage&USETEXTURE );
	SetWin_Num_float ( this, IDC_EDIT_UCOL1,  EffEdit.m_cColor.r );
	SetWin_Num_float ( this, IDC_EDIT_UCOL2,  EffEdit.m_cColor.g );
	SetWin_Num_float ( this, IDC_EDIT_UCOL3,  EffEdit.m_cColor.b );
	SetWin_Num_float ( this, IDC_EDIT_UCOL4,  EffEdit.m_cColor.a );

	DXMATERIAL_CHAR_EFF* m_pMaterialsX = new DXMATERIAL_CHAR_EFF[EffEdit.m_dwMaterials];
	m_pMaterialsX = EffUserColorEdit->GetMaterials();
	m_pVecMatX.clear();

	for ( DWORD i=0; i<EffEdit.m_dwMaterials; ++i )
	{
		m_pVecMatX.push_back(m_pMaterialsX[i]);
	}

	UpdateList();

	return TRUE;
}

BOOL CEffUserColor::Save()
{
	EFFCHAR_PROPERTY_USERCOLOR* EffEdit = new EFFCHAR_PROPERTY_USERCOLOR;
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_UCFLAG1 ), EffEdit->m_dwFlage,USETEXTURE );
	EffEdit->m_cColor.r = GetWin_Num_float ( this, IDC_EDIT_UCOL1 );
	EffEdit->m_cColor.g = GetWin_Num_float ( this, IDC_EDIT_UCOL2 );
	EffEdit->m_cColor.b = GetWin_Num_float ( this, IDC_EDIT_UCOL3 );
	EffEdit->m_cColor.a = GetWin_Num_float ( this, IDC_EDIT_UCOL4 );
	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffUserColorEdit->SetProperty(EffEditProp);

	int nSize = (int)m_pVecMatX.size();
	m_pMaterials = new DXMATERIAL_CHAR_EFF[nSize];
	EffEdit->m_dwMaterials = nSize;
	nMaterialSize = nSize;
	for ( int i=0; i<nSize; ++i )
	{
		m_pMaterials[i] = m_pVecMatX[i];
	}
	EffUserColorEdit->SetMaterials(NULL,nSize,m_pMaterials);
	m_pVecMatX.clear();


	return TRUE;
}

BOOL CEffUserColor::UpdateList()
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

void CEffUserColor::OnBnClickedButtonAdd()
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

void CEffUserColor::OnBnClickedButtonEdit()
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

void CEffUserColor::OnBnClickedButtonDel()
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

void CEffUserColor::OnBnClickedButtonCopy()
{
	int nIndex = m_list_mat.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		m_pVecMatX.push_back(m_pVecMatX[nIndex]);
		UpdateList();
	}
}

void CEffUserColor::OnBnClickedButtonClear()
{
	if ( MessageBox ( "Are you sure you want to Delete All?", "Question", MB_YESNO ) == IDYES )
	{
		m_pVecMatX.clear();
		UpdateList();
	}
}

void CEffUserColor::OnBnClickedButtonAok()
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

void CEffUserColor::OnBnClickedButtonAcan()
{
	UpdateList();

	SetWin_ShowWindow ( this, IDC_BUTTON_CANCEL, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_OK, SW_SHOW );
}
