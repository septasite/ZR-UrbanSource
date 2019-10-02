// XEffLine2Bone.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffLine2Bone.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"
#include ".\xeffline2bone.h"


// CEffLine2Bone dialog

IMPLEMENT_DYNAMIC(CEffLine2Bone, CPropertyPage)
CEffLine2Bone::CEffLine2Bone(LOGFONT logfont)
	: CPropertyPage(CEffLine2Bone::IDD)
	,m_pFont( NULL )
	,EffLine2BoneEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffLine2BoneEdit = new DxEffCharLine2BoneEff;
}

CEffLine2Bone::~CEffLine2Bone()
{
}

void CEffLine2Bone::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LINE, m_list_line );
}


BEGIN_MESSAGE_MAP(CEffLine2Bone, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_L2ADD, OnBnClickedButtonL2add)
	ON_BN_CLICKED(IDC_BUTTON_L2EDIT, OnBnClickedButtonL2edit)
	ON_BN_CLICKED(IDC_BUTTON_L2DEL, OnBnClickedButtonL2del)
	ON_BN_CLICKED(IDC_BUTTON_L2CLR, OnBnClickedButtonL2clr)
	ON_BN_CLICKED(IDC_BUTTON_L2OK, OnBnClickedButtonL2ok)
	ON_BN_CLICKED(IDC_BUTTON_L2CAN, OnBnClickedButtonL2can)
END_MESSAGE_MAP()


// CEffLine2Bone message handlers
BOOL CEffLine2Bone::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffLine2Bone::SetEffLine2Bone ( DxEffCharLine2BoneEff*	EffLine2BoneX )
{ 
	EffLine2BoneEdit = EffLine2BoneX; 
	Update();
}

void CEffLine2Bone::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffLine2BoneReturn( EffLine2BoneEdit );
	}
}

void CEffLine2Bone::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

BOOL CEffLine2Bone::Update()
{
	EFFCHAR_PROPERTY_LINE2BONEEFF EffEdit = *((EFFCHAR_PROPERTY_LINE2BONEEFF*)EffLine2BoneEdit->GetProperty() );
	SetWin_Check ( this, IDC_CHECK_L2FLAG1, EffEdit.m_dwFlag&USE_REMAIN );
	SetWin_Check ( this, IDC_CHECK_L2FLAG2, EffEdit.m_dwFlag&USE_RANDOMRANGE );
	SetWin_Check ( this, IDC_CHECK_L2FLAG3, EffEdit.m_dwFlag&USE_SEQUENCE );
	SetWin_Check ( this, IDC_CHECK_L2FLAG4, EffEdit.m_dwFlag&USE_ROTATE );
	SetWin_Num_int ( this, IDC_EDIT_OCOLOR,  EffEdit.m_dwOtherColor );
	SetWin_Num_int ( this, IDC_EDIT_PPEC,  EffEdit.m_dwParticlePec );

	D3DCOLOR color = EffEdit.m_dwColor;
	D3DCOLOR color2 = EffEdit.m_dwColor2;

	DWORD a = color >> 24;
	DWORD r = (color >> 16) & 0xFF;
	DWORD g = (color >> 8 ) & 0xFF;
	DWORD b = color & 0xFF;

	DWORD a2 = color2 >> 24;
	DWORD r2 = (color2 >> 16) & 0xFF;
	DWORD g2 = (color2 >> 8 ) & 0xFF;
	DWORD b2 = color2 & 0xFF;

	SetWin_Num_int ( this, IDC_EDIT_LCOL1_1,  a );
	SetWin_Num_int ( this, IDC_EDIT_LCOL1_2,  r );
	SetWin_Num_int ( this, IDC_EDIT_LCOL1_3,  g );
	SetWin_Num_int ( this, IDC_EDIT_LCOL1_4,  b );
	SetWin_Num_int ( this, IDC_EDIT_LCOL2_1,  a2 );
	SetWin_Num_int ( this, IDC_EDIT_LCOL2_2,  r2 );
	SetWin_Num_int ( this, IDC_EDIT_LCOL2_3,  g2 );
	SetWin_Num_int ( this, IDC_EDIT_LCOL2_4,  b2 );

	SetWin_Num_float ( this, IDC_EDIT_LVLIFE1, EffEdit.m_vLife.x );
	SetWin_Num_float ( this, IDC_EDIT_LVLIFE2, EffEdit.m_vLife.y );
	SetWin_Num_float ( this, IDC_EDIT_LVSIZE1, EffEdit.m_vSize.x );
	SetWin_Num_float ( this, IDC_EDIT_LVSIZE2, EffEdit.m_vSize.y );
	SetWin_Num_float ( this, IDC_EDIT_LVSIZE3, EffEdit.m_vSize.z );
	SetWin_Num_float ( this, IDC_EDIT_SCALE_X1, EffEdit.m_vScaleX.x );
	SetWin_Num_float ( this, IDC_EDIT_SCALE_X2, EffEdit.m_vScaleX.y );
	SetWin_Num_float ( this, IDC_EDIT_SCALE_Y1, EffEdit.m_vScaleY.x );
	SetWin_Num_float ( this, IDC_EDIT_SCALE_Y2, EffEdit.m_vScaleY.y );
	SetWin_Num_float ( this, IDC_EDIT_SCALE_Y3, EffEdit.m_vScaleY.z );
	//SetWin_Num_float_f ( this, IDC_EDIT_LSHAKE, EffEdit.m_fShake );
	SetWin_Num_int ( this, IDC_EDIT_LSEQ_COL, EffEdit.m_dwSequenceCol );
	SetWin_Num_int ( this, IDC_EDIT_LSEQ_ROW, EffEdit.m_dwSequenceRow );
	//SetWin_Num_float_f ( this, IDC_EDIT_LCLEN, EffEdit.m_fCreateLength );
	SetWin_Num_float ( this, IDC_EDIT_DIST_MIN, EffEdit.m_fMinMaxDist.min );
	SetWin_Num_float ( this, IDC_EDIT_DIST_MAX, EffEdit.m_fMinMaxDist.max );
	SetWin_Num_float ( this, IDC_EDIT_TEXR_MIN, EffEdit.m_fMinMaxTexRotate.min );
	SetWin_Num_float ( this, IDC_EDIT_TEXR_MAX, EffEdit.m_fMinMaxTexRotate.max );
	SetWin_Check ( this, IDC_CHECK_BCAM, EffEdit.m_bWithCamMove );
	SetWin_Text ( this, IDC_EDIT_L2TEX1, EffEdit.m_szTexture );
	SetWin_Text ( this, IDC_EDIT_L2TEX2, EffEdit.m_szTexture2 );
	UpdateList();
	return TRUE;
}

BOOL CEffLine2Bone::Save()
{
	EFFCHAR_PROPERTY_LINE2BONEEFF* EffEdit = new EFFCHAR_PROPERTY_LINE2BONEEFF;
	
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_L2FLAG1 ), EffEdit->m_dwFlag,USE_REMAIN );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_L2FLAG2 ), EffEdit->m_dwFlag,USE_RANDOMRANGE );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_L2FLAG3 ), EffEdit->m_dwFlag,USE_SEQUENCE );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_L2FLAG4 ), EffEdit->m_dwFlag,USE_ROTATE );
	EffEdit->m_dwOtherColor = GetWin_Num_int ( this, IDC_EDIT_OCOLOR );
	EffEdit->m_dwParticlePec = GetWin_Num_int ( this, IDC_EDIT_PPEC );

	BYTE a,r,g,b;
	BYTE a2,r2,g2,b2;
	a = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_LCOL1_1 );
	r = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_LCOL1_2 );
	g = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_LCOL1_3 );
	b = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_LCOL1_4 );
	EffEdit->m_dwColor = D3DCOLOR_ARGB(a,r,g,b);
	a2 = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_LCOL2_1 );
	r2 = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_LCOL2_2 );
	g2 = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_LCOL2_3 );
	b2 = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_LCOL2_4 );
	EffEdit->m_dwColor2 = D3DCOLOR_ARGB(a2,r2,g2,b2);

	EffEdit->m_vLife.x = GetWin_Num_float ( this, IDC_EDIT_LVLIFE1 );
	EffEdit->m_vLife.y = GetWin_Num_float ( this, IDC_EDIT_LVLIFE2 );
	EffEdit->m_vSize.x = GetWin_Num_float ( this, IDC_EDIT_LVSIZE1 );
	EffEdit->m_vSize.y = GetWin_Num_float ( this, IDC_EDIT_LVSIZE2 );
	EffEdit->m_vSize.z = GetWin_Num_float ( this, IDC_EDIT_LVSIZE3 );
	EffEdit->m_vScaleX.x = GetWin_Num_float ( this, IDC_EDIT_SCALE_X1 );
	EffEdit->m_vScaleX.y = GetWin_Num_float ( this, IDC_EDIT_SCALE_X2 );
	EffEdit->m_vScaleY.x = GetWin_Num_float ( this, IDC_EDIT_SCALE_Y1 );
	EffEdit->m_vScaleY.y = GetWin_Num_float ( this, IDC_EDIT_SCALE_Y2 );
	EffEdit->m_vScaleY.z = GetWin_Num_float ( this, IDC_EDIT_SCALE_Y3 );
	EffEdit->m_fShake = GetWin_Num_float ( this, IDC_EDIT_LSHAKE );
	EffEdit->m_dwSequenceCol = GetWin_Num_int ( this, IDC_EDIT_LSEQ_COL );
	EffEdit->m_dwSequenceRow = GetWin_Num_int ( this, IDC_EDIT_LSEQ_ROW );
	EffEdit->m_fCreateLength = GetWin_Num_float ( this, IDC_EDIT_LCLEN );
	EffEdit->m_fMinMaxDist.min = GetWin_Num_float ( this, IDC_EDIT_DIST_MIN );
	EffEdit->m_fMinMaxDist.max = GetWin_Num_float ( this, IDC_EDIT_DIST_MAX );
	EffEdit->m_fMinMaxTexRotate.min = GetWin_Num_float ( this, IDC_EDIT_TEXR_MIN );
	EffEdit->m_fMinMaxTexRotate.max = GetWin_Num_float ( this, IDC_EDIT_TEXR_MAX );
	EffEdit->m_bWithCamMove = (bool)GetWin_Check ( this, IDC_CHECK_BCAM );
	StringCchCopy( EffEdit->m_szTexture, BONELISTEFF_TEXNAME_SIZE, GetWin_Text( this, IDC_EDIT_L2TEX1 ).GetString() );
	StringCchCopy( EffEdit->m_szTexture2, BONELISTEFF_TEXNAME_SIZE, GetWin_Text( this, IDC_EDIT_L2TEX2 ).GetString() );

	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffLine2BoneEdit->SetProperty(EffEditProp);

	return TRUE;
}

BOOL CEffLine2Bone::UpdateList()
{
	CString strTemp;
	m_list_line.ResetContent();

	for ( DWORD i=0; i<EffLine2BoneEdit->GetLineSize(); i++ )
	{
		strTemp.Format ("[%d]-[Bone[0]:%s----Bone[1]:%s]"
		,i
		,EffLine2BoneEdit->GetLine2BoneInf()[EffLine2BoneEdit->GetLine2BoneLine()[i]->m_dwBONEID[0] ]->m_strName.c_str()
		,EffLine2BoneEdit->GetLine2BoneInf()[EffLine2BoneEdit->GetLine2BoneLine()[i]->m_dwBONEID[1] ]->m_strName.c_str()
		);
		m_list_line.InsertString(i, strTemp);
	}

	SetWin_ShowWindow ( this, IDC_EDIT_BONE1, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE2, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_L2OK, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_L2CAN, SW_HIDE );

	return TRUE;
}

void CEffLine2Bone::OnBnClickedButtonL2add()
{
	SetWin_ShowWindow ( this, IDC_EDIT_BONE1, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE2, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_L2OK, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_L2CAN, SW_SHOW );
	SetWin_Text ( this, IDC_EDIT_BONE1, "" );
	SetWin_Text ( this, IDC_EDIT_BONE2, "" );
	bAdd = true;

	SetWin_ShowWindow ( this, IDC_BUTTON_CANCEL, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_OK, SW_HIDE );
}

void CEffLine2Bone::OnBnClickedButtonL2edit()
{
	int nIndex = m_list_line.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		SetWin_ShowWindow ( this, IDC_EDIT_BONE1, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_BONE2, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_BUTTON_L2OK, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_BUTTON_L2CAN, SW_SHOW );
		bAdd = false;
		SetWin_Text ( this, IDC_EDIT_BONE1, EffLine2BoneEdit->GetLine2BoneInf()[EffLine2BoneEdit->GetLine2BoneLine()[nIndex]->m_dwBONEID[0] ]->m_strName.c_str() );
		SetWin_Text ( this, IDC_EDIT_BONE2, EffLine2BoneEdit->GetLine2BoneInf()[EffLine2BoneEdit->GetLine2BoneLine()[nIndex]->m_dwBONEID[1] ]->m_strName.c_str() );
		nLastEdit = nIndex;

		SetWin_ShowWindow ( this, IDC_BUTTON_CANCEL, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_BUTTON_OK, SW_HIDE );
	}
}

void CEffLine2Bone::OnBnClickedButtonL2del()
{
	int nIndex = m_list_line.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		if ( MessageBox ( "Are you sure you want to Delete?", "Question", MB_YESNO ) == IDYES )
		{
			EffLine2BoneEdit->DeleteLine(nIndex);
			UpdateList();
		}
	}
}

void CEffLine2Bone::OnBnClickedButtonL2clr()
{
	if ( MessageBox ( "Are you sure you want to Delete All?", "Question", MB_YESNO ) == IDYES )
	{
		EffLine2BoneEdit->ClearAllBoneLine();
		UpdateList();
	}
}

void CEffLine2Bone::OnBnClickedButtonL2ok()
{
	if (!bAdd )	EffLine2BoneEdit->DeleteLine(nLastEdit);
	EffLine2BoneEdit->InsertLine(GetWin_Text( this, IDC_EDIT_BONE1 ).GetString(),GetWin_Text( this, IDC_EDIT_BONE2 ).GetString() );
	UpdateList();

	SetWin_ShowWindow ( this, IDC_BUTTON_CANCEL, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_OK, SW_SHOW );
}

void CEffLine2Bone::OnBnClickedButtonL2can()
{
	UpdateList();

	SetWin_ShowWindow ( this, IDC_BUTTON_CANCEL, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_OK, SW_SHOW );
}
