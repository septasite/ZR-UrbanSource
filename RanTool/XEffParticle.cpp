// XEffParticle.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffParticle.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"
#include ".\xeffparticle.h"


// CEffParticle dialog

IMPLEMENT_DYNAMIC(CEffParticle, CPropertyPage)
CEffParticle::CEffParticle(LOGFONT logfont)
	: CPropertyPage(CEffParticle::IDD)
	,m_pFont( NULL )
	,EffParticleEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);

	EffParticleEdit = new DxEffCharParticle;

	bAdd = false;
}

CEffParticle::~CEffParticle()
{
}

void CEffParticle::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_VEC, m_list_vec );
}


BEGIN_MESSAGE_MAP(CEffParticle, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_PADD, OnBnClickedButtonPadd)
	ON_BN_CLICKED(IDC_BUTTON_PEDIT, OnBnClickedButtonPedit)
	ON_BN_CLICKED(IDC_BUTTON_PDEL, OnBnClickedButtonPdel)
	ON_BN_CLICKED(IDC_BUTTON_PCLR, OnBnClickedButtonPclr)
	ON_BN_CLICKED(IDC_BUTTON_PMUP, OnBnClickedButtonPmup)
	ON_BN_CLICKED(IDC_BUTTON_PMDN, OnBnClickedButtonPmdn)
	ON_BN_CLICKED(IDC_BUTTON_POK, OnBnClickedButtonPok)
	ON_BN_CLICKED(IDC_BUTTON_PCAN, OnBnClickedButtonPcan)
END_MESSAGE_MAP()


// CEffParticle message handlers
BOOL CEffParticle::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffParticle::SetEffParticle ( DxEffCharParticle*	EffParticleX)
{ 
	EffParticleEdit = EffParticleX; 
	Update();
}

void CEffParticle::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffParticleReturn( EffParticleEdit );
	}
}

void CEffParticle::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

BOOL CEffParticle::Update()
{
	EFFCHAR_PROPERTY_PARTICLE EffEdit = *((EFFCHAR_PROPERTY_PARTICLE*)EffParticleEdit->GetProperty() );

	SetWin_Check ( this, IDC_CHECK_PSIZE1, EffEdit.m_dwFlag&USE_REMAIN );
	SetWin_Check ( this, IDC_CHECK_PSIZE2, EffEdit.m_dwFlag&USE_ABSOLUTE );
	SetWin_Check ( this, IDC_CHECK_PSIZE3, EffEdit.m_dwFlag&USE_RANDOMRANGE );
	SetWin_Check ( this, IDC_CHECK_PSIZE4, EffEdit.m_dwFlag&USE_SEQUENCE );
	SetWin_Check ( this, IDC_CHECK_PSIZE5, EffEdit.m_dwFlag&USE_ROTATE );
	SetWin_Check ( this, IDC_CHECK_PSIZE6, EffEdit.m_dwFlag&USE_PLAY );
	SetWin_Check ( this, IDC_CHECK_PSIZE7, EffEdit.m_dwFlag&USE_POS1 );
	SetWin_Num_int ( this, IDC_EDIT_PPEC,  EffEdit.m_dwParticlePec );
	SetWin_Num_float ( this, IDC_EDIT_RRANGE,  EffEdit.m_fRandomRange );

	D3DCOLOR color = EffEdit.m_dwColor;
	DWORD a = color >> 24;
	DWORD r = (color >> 16) & 0xFF;
	DWORD g = (color >> 8 ) & 0xFF;
	DWORD b = color & 0xFF;
	SetWin_Num_int ( this, IDC_EDIT_PCOLOR1,  a );
	SetWin_Num_int ( this, IDC_EDIT_PCOLOR2,  r );
	SetWin_Num_int ( this, IDC_EDIT_PCOLOR3,  g );
	SetWin_Num_int ( this, IDC_EDIT_PCOLOR4,  b );

	SetWin_Num_float ( this, IDC_EDIT_VSIZE1,  EffEdit.m_vSize.x );
	SetWin_Num_float ( this, IDC_EDIT_VSIZE2,  EffEdit.m_vSize.y );
	SetWin_Num_float ( this, IDC_EDIT_VSIZE3,  EffEdit.m_vSize.z );
	SetWin_Num_float ( this, IDC_EDIT_LMIN,  EffEdit.m_fLifeMin );
	SetWin_Num_float ( this, IDC_EDIT_LMAX,  EffEdit.m_fLifeMax );
	SetWin_Num_float ( this, IDC_EDIT_ROT1,  EffEdit.m_vRotate.x );
	SetWin_Num_float ( this, IDC_EDIT_ROT2,  EffEdit.m_vRotate.y );
	SetWin_Num_float ( this, IDC_EDIT_VEL1,  EffEdit.m_vVelocity.x );
	SetWin_Num_float ( this, IDC_EDIT_VEL2,  EffEdit.m_vVelocity.y );
	SetWin_Num_int ( this, IDC_EDIT_SCOL,  EffEdit.m_dwSequenceCol );
	SetWin_Num_int ( this, IDC_EDIT_SROW,  EffEdit.m_dwSequenceRow );
	SetWin_Text ( this, IDC_EDIT_PTEXT,  EffEdit.m_szTexture );

	UpdateList();
	return TRUE;
}

BOOL CEffParticle::UpdateList()
{
	int nNum = EffParticleEdit->GetPoistionSize();

	CString strTemp;
	m_list_vec.ResetContent();

	for ( int i=0; i<nNum; i++ )
	{
		strTemp.Format ("%d---[%s]"
		,i
		,EffParticleEdit->GetPositionString(i).c_str()
		);
		m_list_vec.InsertString(i, strTemp);
	}

	SetWin_ShowWindow ( this, IDC_EDIT_PX, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_PY, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_PZ, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_PCAN, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_POK, SW_HIDE );

	return TRUE;
}

BOOL CEffParticle::Save()
{
	EFFCHAR_PROPERTY_PARTICLE* EffEdit = new EFFCHAR_PROPERTY_PARTICLE;

	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_PSIZE1 ), EffEdit->m_dwFlag,USE_REMAIN );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_PSIZE2 ), EffEdit->m_dwFlag,USE_ABSOLUTE );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_PSIZE3 ), EffEdit->m_dwFlag,USE_RANDOMRANGE );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_PSIZE4 ), EffEdit->m_dwFlag,USE_SEQUENCE );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_PSIZE5 ), EffEdit->m_dwFlag,USE_ROTATE );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_PSIZE6 ), EffEdit->m_dwFlag,USE_PLAY );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_PSIZE7 ), EffEdit->m_dwFlag,USE_POS1 );
	EffEdit->m_dwParticlePec = GetWin_Num_int ( this, IDC_EDIT_PPEC );	
	EffEdit->m_fRandomRange = GetWin_Num_float ( this, IDC_EDIT_RRANGE );	

	BYTE a,r,g,b;
	a = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_PCOLOR1 );
	r = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_PCOLOR2 );
	g = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_PCOLOR3 );
	b = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_PCOLOR4 );
	EffEdit->m_dwColor= D3DCOLOR_ARGB(a,r,g,b);
	
	EffEdit->m_vSize.x = GetWin_Num_float ( this, IDC_EDIT_VSIZE1 );
	EffEdit->m_vSize.y = GetWin_Num_float ( this, IDC_EDIT_VSIZE2 );	
	EffEdit->m_vSize.z = GetWin_Num_float ( this, IDC_EDIT_VSIZE3 );	
	EffEdit->m_fLifeMin = GetWin_Num_float ( this, IDC_EDIT_LMIN );	
	EffEdit->m_fLifeMax = GetWin_Num_float ( this, IDC_EDIT_LMAX );	
	EffEdit->m_vRotate.x = GetWin_Num_float ( this, IDC_EDIT_ROT1 );
	EffEdit->m_vRotate.y = GetWin_Num_float ( this, IDC_EDIT_ROT2 );	
	EffEdit->m_vVelocity.x = GetWin_Num_float ( this, IDC_EDIT_VEL1 );	
	EffEdit->m_vVelocity.y = GetWin_Num_float ( this, IDC_EDIT_VEL2 );	
	EffEdit->m_dwSequenceCol = GetWin_Num_int ( this, IDC_EDIT_SCOL );	
	EffEdit->m_dwSequenceRow = GetWin_Num_int ( this, IDC_EDIT_SROW );	
	StringCchCopy( EffEdit->m_szTexture, TEX_SIZE_64, GetWin_Text( this, IDC_EDIT_PTEXT ).GetString() );
	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffParticleEdit->SetProperty(EffEditProp);

	return TRUE;
}

void CEffParticle::OnBnClickedButtonPadd()
{
	SetWin_ShowWindow ( this, IDC_EDIT_PX, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_PY, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_PZ, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_PCAN, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_POK, SW_SHOW );
	//SetWin_Num_float_f ( this, IDC_EDIT_PX, 0.0f );
	//SetWin_Num_float_f ( this, IDC_EDIT_PY, 0.0f );
	//SetWin_Num_float_f ( this, IDC_EDIT_PZ, 0.0f );
	bAdd = true;

	SetWin_ShowWindow ( this, IDC_BUTTON_CANCEL, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_OK, SW_HIDE );
}

void CEffParticle::OnBnClickedButtonPedit()
{
	int nIndex = m_list_vec.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		SetWin_ShowWindow ( this, IDC_EDIT_PX, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_PY, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_PZ, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_BUTTON_PCAN, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_BUTTON_POK, SW_SHOW );
		//SetWin_Num_float_f ( this, IDC_EDIT_PX, EffParticleEdit->GetSelectedVec(nIndex).x );
		//SetWin_Num_float_f ( this, IDC_EDIT_PY, EffParticleEdit->GetSelectedVec(nIndex).y );
		//SetWin_Num_float_f ( this, IDC_EDIT_PZ, EffParticleEdit->GetSelectedVec(nIndex).z );
		bAdd = false;
		nLastEdit = nIndex;

		SetWin_ShowWindow ( this, IDC_BUTTON_CANCEL, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_BUTTON_OK, SW_HIDE );
	}
}

void CEffParticle::OnBnClickedButtonPdel()
{
	int nIndex = m_list_vec.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		if ( MessageBox ( "Are you sure you want to Delete?", "Question", MB_YESNO ) == IDYES )
		{
			EffParticleEdit->DeletePoint(nIndex);
			UpdateList();
		}
	}
}

void CEffParticle::OnBnClickedButtonPclr()
{
	if ( MessageBox ( "Are you sure you want to Delete All?", "Question", MB_YESNO ) == IDYES )
	{
		EffParticleEdit->ClearPositionVec();
		UpdateList();
	}
}

void CEffParticle::OnBnClickedButtonPmup()
{
	int nIndex = m_list_vec.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		EffParticleEdit->DataUp(nIndex);
		UpdateList();
	}
}

void CEffParticle::OnBnClickedButtonPmdn()
{
	int nIndex = m_list_vec.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		EffParticleEdit->DataDown(nIndex);
		UpdateList();
	}
}

void CEffParticle::OnBnClickedButtonPok()
{
	D3DXVECTOR3 NewVec;
	NewVec.x = GetWin_Num_float ( this, IDC_EDIT_PX );
	NewVec.y = GetWin_Num_float ( this, IDC_EDIT_PY );
	NewVec.z = GetWin_Num_float ( this, IDC_EDIT_PZ );
	if (!bAdd)	EffParticleEdit->DeletePoint(nLastEdit);
	EffParticleEdit->InsertPoint(NewVec);
	UpdateList();

	SetWin_ShowWindow ( this, IDC_BUTTON_CANCEL, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_OK, SW_SHOW );
}

void CEffParticle::OnBnClickedButtonPcan()
{
	UpdateList();
	SetWin_ShowWindow ( this, IDC_BUTTON_CANCEL, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_OK, SW_SHOW );
}
