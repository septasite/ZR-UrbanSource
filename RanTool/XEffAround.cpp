// XEffAround.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffAround.h"
#include "xEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"
#include ".\xeffaround.h"
#include "GLDefine.h"

// CEffAround dialog

IMPLEMENT_DYNAMIC(CEffAround, CPropertyPage)
CEffAround::CEffAround(LOGFONT logfont)
	: CPropertyPage(CEffAround::IDD)
	,m_pFont( NULL )
	,EffAroundEdit(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	EffAroundEdit = new DxCharAroundEff;
}

CEffAround::~CEffAround()
{
}

void CEffAround::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_AR, m_list_ar );
}


BEGIN_MESSAGE_MAP(CEffAround, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_ARADD, OnBnClickedButtonAradd)
	ON_BN_CLICKED(IDC_BUTTON_AREDIT, OnBnClickedButtonAredit)
	ON_BN_CLICKED(IDC_BUTTON_ARDEL, OnBnClickedButtonArdel)
	ON_BN_CLICKED(IDC_BUTTON_ARCLR, OnBnClickedButtonArclr)
	ON_BN_CLICKED(IDC_BUTTON_AROK, OnBnClickedButtonArok)
	ON_BN_CLICKED(IDC_BUTTON_ARCAN, OnBnClickedButtonArcan)
	ON_BN_CLICKED(IDC_BUTTON_VPOS, OnBnClickedButtonVpos)
END_MESSAGE_MAP()


// CEffAround message handlers
BOOL CEffAround::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffAround::SetEffAround ( DxCharAroundEff*	EffAroundX)
{ 
	EffAroundEdit = EffAroundX; 
	Update();
}

void CEffAround::OnBnClickedButtonOk()
{
	if (Save())
	{
		m_pEffTab->ActiveEffAroundReturn( EffAroundEdit );
	}
}

void CEffAround::OnBnClickedButtonCancel()
{
	m_pEffTab->ActiveEffListNormal();
}

BOOL CEffAround::Update()
{
	EFFCHAR_PROPERTY_CHAR_AROUND EffEdit = *((EFFCHAR_PROPERTY_CHAR_AROUND*)EffAroundEdit->GetProperty() );
	SetWin_Check ( this, IDC_ARFLAG1, EffEdit.m_dwFlag&USE_SEQUENCE );
	SetWin_Text ( this, IDC_EDIT_ARTEX, EffEdit.m_szTexture );

	D3DCOLOR color = EffEdit.m_dwColor;
	DWORD a = color >> 24;
	DWORD r = (color >> 16) & 0xFF;
	DWORD g = (color >> 8 ) & 0xFF;
	DWORD b = color & 0xFF;
	SetWin_Num_int ( this, IDC_EDIT_ARCOLOR1,  a );
	SetWin_Num_int ( this, IDC_EDIT_ARCOLOR2,  r );
	SetWin_Num_int ( this, IDC_EDIT_ARCOLOR3,  g );
	SetWin_Num_int ( this, IDC_EDIT_ARCOLOR4,  b );
	SetWin_Num_int ( this, IDC_EDIT_ARSEC_COL,  EffEdit.m_dwSequenceCol );
	SetWin_Num_int ( this, IDC_EDIT_ARSEC_ROW,  EffEdit.m_dwSequenceRow );
	SetWin_Num_float ( this, IDC_EDIT_TSPD_1, EffEdit.m_fMinTextureSpeed);
	SetWin_Num_float ( this, IDC_EDIT_TSPD_2, EffEdit.m_fMaxTextureSpeed);
	SetWin_Num_float ( this, IDC_EDIT_MVSIZE_MIN_1, EffEdit.m_vMinSize.x );
	SetWin_Num_float ( this, IDC_EDIT_MVSIZE_MIN_2, EffEdit.m_vMinSize.y );
	SetWin_Num_float ( this, IDC_EDIT_MVSIZE_MAX_1, EffEdit.m_vMaxSize.x );
	SetWin_Num_float ( this, IDC_EDIT_MVSIZE_MAX_2, EffEdit.m_vMaxSize.y );
	SetWin_Num_float ( this, IDC_EDIT_LTIME_1, EffEdit.m_fMinLifeTime );
	SetWin_Num_float ( this, IDC_EDIT_LTIME_2, EffEdit.m_fMaxLifeTime );
	SetWin_Num_float ( this, IDC_EDIT_RTIME_1, EffEdit.m_fMinRivalTime );
	SetWin_Num_float ( this, IDC_EDIT_RTIME_2, EffEdit.m_fMaxRivalTime );

	UpdateList();
	return TRUE;
}

BOOL CEffAround::Save()
{
	EFFCHAR_PROPERTY_CHAR_AROUND* EffEdit = new EFFCHAR_PROPERTY_CHAR_AROUND;

	SetCheck_Flags ( GetWin_Check ( this, IDC_ARFLAG1 ), EffEdit->m_dwFlag,USE_SEQUENCE );
	StringCchCopy( EffEdit->m_szTexture, AROUNDEFFECT_TEXNAME_SIZE, GetWin_Text( this, IDC_EDIT_ARTEX ).GetString() );

	BYTE a,r,g,b;
	a = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_ARCOLOR1 );
	r = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_ARCOLOR2 );
	g = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_ARCOLOR3 );
	b = ( BYTE )GetWin_Num_int ( this, IDC_EDIT_ARCOLOR4 );
	EffEdit->m_dwColor = D3DCOLOR_ARGB(a,r,g,b);

	EffEdit->m_dwSequenceCol = GetWin_Num_int ( this, IDC_EDIT_ARSEC_COL );
	EffEdit->m_dwSequenceRow = GetWin_Num_int ( this, IDC_EDIT_ARSEC_ROW );
	EffEdit->m_fMinTextureSpeed = GetWin_Num_float ( this, IDC_EDIT_TSPD_1 );
	EffEdit->m_fMaxTextureSpeed = GetWin_Num_float ( this, IDC_EDIT_TSPD_2 );
	EffEdit->m_vMinSize.x = GetWin_Num_float ( this, IDC_EDIT_MVSIZE_MIN_1 );
	EffEdit->m_vMinSize.y = GetWin_Num_float ( this, IDC_EDIT_MVSIZE_MIN_2 );
	EffEdit->m_vMaxSize.x = GetWin_Num_float ( this, IDC_EDIT_MVSIZE_MAX_1 );
	EffEdit->m_vMaxSize.y = GetWin_Num_float ( this, IDC_EDIT_MVSIZE_MAX_2 );
	EffEdit->m_fMinLifeTime = GetWin_Num_float ( this, IDC_EDIT_LTIME_1 );
	EffEdit->m_fMaxLifeTime = GetWin_Num_float ( this, IDC_EDIT_LTIME_2 );
	EffEdit->m_fMinRivalTime = GetWin_Num_float ( this, IDC_EDIT_RTIME_1 );
	EffEdit->m_fMaxRivalTime = GetWin_Num_float ( this, IDC_EDIT_RTIME_2 );

	EFFCHAR_PROPERTY* EffEditProp = ((EFFCHAR_PROPERTY*)EffEdit );
	EffAroundEdit->SetProperty(EffEditProp);

	return TRUE;
}

BOOL CEffAround::UpdateList()
{
	CString strTemp;
	m_list_ar.ResetContent();

	for ( DWORD i=0; i<EffAroundEdit->GetAroundEffectSize(); i++ )
	{
		strTemp.Format ("[%d]-[Bone:%s---X:%f--Y:%f--Z:%f--]"
		,i
		,EffAroundEdit->GetAroundEffect()[i].strBoneName.c_str()
		,EffAroundEdit->GetAroundEffect()[i].vPos.x
		,EffAroundEdit->GetAroundEffect()[i].vPos.y
		,EffAroundEdit->GetAroundEffect()[i].vPos.z
		);
		m_list_ar.InsertString(i, strTemp);
	}

	SetWin_ShowWindow ( this, IDC_EDIT_RVPOS1, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_RVPOS2, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_RVPOS3, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_RB_ALIVE, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_RBONE, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_RMESH, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_RNOR1, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_RNOR2, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_RNOR3, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_RSIZE_1, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_RSIZE_2, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_RLTIME, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_RRTIME, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_TEXSPEED, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_RROT, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_RTIME, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_RTEXTIME, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_AROK, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_ARCAN, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_VPOS, SW_HIDE );

	return TRUE;
}

void CEffAround::OnBnClickedButtonAradd()
{
	SetWin_ShowWindow ( this, IDC_EDIT_RVPOS1, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_RVPOS2, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_RVPOS3, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_RB_ALIVE, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_RBONE, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_RMESH, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_RNOR1, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_RNOR2, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_RNOR3, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_RSIZE_1, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_RSIZE_2, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_RLTIME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_RRTIME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_TEXSPEED, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_RROT, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_RTIME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_RTEXTIME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_AROK, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_ARCAN, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_VPOS, SW_SHOW );
	bAdd = true;

	SAROUNDEFF_DATA*	Data = new SAROUNDEFF_DATA;
	Data->CreateParticleData(*(EFFCHAR_PROPERTY_CHAR_AROUND*)EffAroundEdit->GetProperty());
	Data->fRunTime = RandomNumber( 0.0f, (Data->fRenderLifeTime + Data->fRenderRivalTime) );

	//SetWin_Num_float_f ( this, IDC_EDIT_RVPOS1,  Data->vPos.x );
	//SetWin_Num_float_f ( this, IDC_EDIT_RVPOS2,  Data->vPos.y );
	//SetWin_Num_float_f ( this, IDC_EDIT_RVPOS3,  Data->vPos.z );
	SetWin_Text ( this, IDC_EDIT_RBONE, Data->strBoneName.c_str() );
	//SetWin_Num_float_f ( this, IDC_EDIT_RNOR1,  Data->vNormal.x );
	//SetWin_Num_float_f ( this, IDC_EDIT_RNOR2,  Data->vNormal.y );
	//SetWin_Num_float_f ( this, IDC_EDIT_RNOR3,  Data->vNormal.z );
	SetWin_Num_float ( this, IDC_EDIT_RMESH,  Data->fMeshDist );
	//SetWin_Num_float_f ( this, IDC_EDIT_RSIZE_1,  Data->vRenderSize.x );
	//SetWin_Num_float_f ( this, IDC_EDIT_RSIZE_2,  Data->vRenderSize.y );
	//SetWin_Num_float_f ( this, IDC_EDIT_RLTIME,  Data->fRenderLifeTime );
	//SetWin_Num_float_f ( this, IDC_EDIT_RRTIME,  Data->fRenderRivalTime );
	//SetWin_Num_float_f ( this, IDC_EDIT_TEXSPEED,  Data->fRunTexAnimateSpeed );
	//SetWin_Num_float_f ( this, IDC_EDIT_RROT,  Data->fRenderRotate );
	//SetWin_Num_float_f ( this, IDC_EDIT_RTIME,  Data->fRunTime );
	//SetWin_Num_float_f ( this, IDC_EDIT_RTEXTIME,  Data->fRunTextureNum );
	SetWin_Check ( this, IDC_RB_ALIVE, Data->bAlive );
	bInit = false;

	SetWin_ShowWindow ( this, IDC_BUTTON_CANCEL, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_OK, SW_HIDE );
}

void CEffAround::OnBnClickedButtonAredit()
{
	int nIndex = m_list_ar.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		SetWin_ShowWindow ( this, IDC_EDIT_RVPOS1, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_RVPOS2, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_RVPOS3, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_RB_ALIVE, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_RBONE, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_RMESH, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_RNOR1, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_RNOR2, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_RNOR3, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_RSIZE_1, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_RSIZE_2, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_RLTIME, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_RRTIME, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_TEXSPEED, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_RROT, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_RTIME, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_EDIT_RTEXTIME, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_BUTTON_AROK, SW_SHOW );
		SetWin_ShowWindow ( this, IDC_BUTTON_ARCAN, SW_SHOW );
		bAdd = false;
		bInit = true;
		nLastEdit =  nIndex;

		//SetWin_Num_float_f ( this, IDC_EDIT_RVPOS1,  EffAroundEdit->GetAroundEffect()[nIndex].vPos.x );
		//SetWin_Num_float_f ( this, IDC_EDIT_RVPOS2, EffAroundEdit->GetAroundEffect()[nIndex].vPos.y );
		//SetWin_Num_float_f ( this, IDC_EDIT_RVPOS3,  EffAroundEdit->GetAroundEffect()[nIndex].vPos.z );
		SetWin_Text ( this, IDC_EDIT_RBONE, EffAroundEdit->GetAroundEffect()[nIndex].strBoneName.c_str() );
		//SetWin_Num_float_f ( this, IDC_EDIT_RNOR1,  EffAroundEdit->GetAroundEffect()[nIndex].vNormal.x );
		//SetWin_Num_float_f ( this, IDC_EDIT_RNOR2,  EffAroundEdit->GetAroundEffect()[nIndex].vNormal.y );
		//SetWin_Num_float_f ( this, IDC_EDIT_RNOR3,  EffAroundEdit->GetAroundEffect()[nIndex].vNormal.z );
		//SetWin_Num_float ( this, IDC_EDIT_RMESH,  EffAroundEdit->GetAroundEffect()[nIndex].fMeshDist );
		//SetWin_Num_float_f ( this, IDC_EDIT_RSIZE_1,  EffAroundEdit->GetAroundEffect()[nIndex].vRenderSize.x );
		//SetWin_Num_float_f ( this, IDC_EDIT_RSIZE_2, EffAroundEdit->GetAroundEffect()[nIndex].vRenderSize.y );
		//SetWin_Num_float_f ( this, IDC_EDIT_RLTIME, EffAroundEdit->GetAroundEffect()[nIndex].fRenderLifeTime );
		//SetWin_Num_float_f ( this, IDC_EDIT_RRTIME,  EffAroundEdit->GetAroundEffect()[nIndex].fRenderRivalTime );
		//SetWin_Num_float_f ( this, IDC_EDIT_TEXSPEED,  EffAroundEdit->GetAroundEffect()[nIndex].fRunTexAnimateSpeed );
		//SetWin_Num_float_f ( this, IDC_EDIT_RROT,  EffAroundEdit->GetAroundEffect()[nIndex].fRenderRotate );
		//SetWin_Num_float_f ( this, IDC_EDIT_RTIME,  EffAroundEdit->GetAroundEffect()[nIndex].fRunTime );
		//SetWin_Num_float_f ( this, IDC_EDIT_RTEXTIME,  EffAroundEdit->GetAroundEffect()[nIndex].fRunTextureNum );
		SetWin_Check ( this, IDC_RB_ALIVE, EffAroundEdit->GetAroundEffect()[nIndex].bAlive );

		SetWin_ShowWindow ( this, IDC_BUTTON_CANCEL, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_BUTTON_OK, SW_HIDE );
	}
}

void CEffAround::OnBnClickedButtonArdel()
{
	int nIndex = m_list_ar.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		if ( MessageBox ( "Are you sure you want to Delete?", "Question", MB_YESNO ) == IDYES )
		{
			EffAroundEdit->DeleteAroundEffect(nIndex);
		}
	}
}

void CEffAround::OnBnClickedButtonArclr()
{
	if ( MessageBox ( "Are you sure you want to Delete All?", "Question", MB_YESNO ) == IDYES )
	{
		EffAroundEdit->ClearAroundEffect();
	}
}

void CEffAround::OnBnClickedButtonArok()
{
	SAROUNDEFF_DATA*	Data = new SAROUNDEFF_DATA;

	Data->vPos.x = GetWin_Num_float ( this, IDC_EDIT_RVPOS1 );
	Data->vPos.y = GetWin_Num_float ( this, IDC_EDIT_RVPOS2 );
	Data->vPos.z = GetWin_Num_float ( this, IDC_EDIT_RVPOS3 );
	Data->strBoneName = GetWin_Text( this, IDC_EDIT_RBONE ).GetString();
	Data->vNormal.x = GetWin_Num_float ( this, IDC_EDIT_RNOR1 );
	Data->vNormal.y = GetWin_Num_float ( this, IDC_EDIT_RNOR2 );
	Data->vNormal.z = GetWin_Num_float ( this, IDC_EDIT_RNOR3 );
	Data->fMeshDist = GetWin_Num_float ( this, IDC_EDIT_RMESH );
	Data->vRenderSize.x = GetWin_Num_float ( this, IDC_EDIT_RSIZE_1 );
	Data->vRenderSize.y = GetWin_Num_float ( this, IDC_EDIT_RSIZE_2 );
	Data->fRenderLifeTime = GetWin_Num_float ( this, IDC_EDIT_RLTIME );
	Data->fRenderRivalTime = GetWin_Num_float ( this, IDC_EDIT_RRTIME );
	Data->fRunTexAnimateSpeed = GetWin_Num_float ( this, IDC_EDIT_TEXSPEED );
	Data->fRenderRotate = GetWin_Num_float ( this, IDC_EDIT_RROT );
	Data->fRunTime = GetWin_Num_float ( this, IDC_EDIT_RTIME );
	Data->fRunTextureNum = GetWin_Num_float ( this, IDC_EDIT_RTEXTIME );
	Data->bAlive = (bool)GetWin_Check ( this, IDC_RB_ALIVE );

	if (!bInit)
	{
		MessageBox("Initialize Bone First","Tip",MB_OK);
		return;
	}
	if (!bAdd )
	{
		EffAroundEdit->DeleteAroundEffect(nLastEdit);
	}
	EffAroundEdit->InsertAroundEffectTool(*Data);
	UpdateList();

	SetWin_ShowWindow ( this, IDC_BUTTON_CANCEL, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_OK, SW_SHOW );
}

void CEffAround::OnBnClickedButtonArcan()
{
	UpdateList();
	SetWin_ShowWindow ( this, IDC_BUTTON_CANCEL, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_OK, SW_SHOW );
}

void CEffAround::OnBnClickedButtonVpos()
{
	CString szFilterInput = "Bone (*.x)|*.x|";
	CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
	dlgInput.m_ofn.lpstrInitialDir = DxSkinPieceContainer::GetInstance().GetPath();
	if ( dlgInput.DoModal() != IDOK ) return;

	DxSkeleton*		m_pSkeletonX =  new DxSkeleton;
	HRESULT hr = m_pSkeletonX->LoadFile( dlgInput.GetFileName(),NULL );
	if (FAILED(hr))
	{
		MessageBox("Error Loading Bone File!","Error",MB_OK);
	}
	else
	{
		DxBoneTrans*	pBoneTran;
		pBoneTran = m_pSkeletonX->FindBone( GetWin_Text( this, IDC_EDIT_RBONE ).GetString() );

		if( !pBoneTran )
		{
			MessageBox("Bone Name Missing Or Incorrect Bone Name","Error",MB_OK);
		}
		else
		{

			//SetWin_Num_float_f ( this, IDC_EDIT_RVPOS1, GetWin_Num_float ( this, IDC_EDIT_RVPOS1 ) - pBoneTran->matCombined._41 );
			//SetWin_Num_float_f ( this, IDC_EDIT_RVPOS2,	GetWin_Num_float ( this, IDC_EDIT_RVPOS2 ) - pBoneTran->matCombined._42 );
			//SetWin_Num_float_f ( this, IDC_EDIT_RVPOS3, GetWin_Num_float ( this, IDC_EDIT_RVPOS3 ) - pBoneTran->matCombined._43 );

			bInit = true;
		}
	}	
}
