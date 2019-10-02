// DlgGateEdit.cpp : implementation file
//

#include "stdafx.h"
#include "RanEditLevel.h"
#include "DlgGateEdit.h"
#include ".\dlggateedit.h"
#include "ToolTab.h"
#include "EtcFunction.h"
#include "DlgListMap.h"
#include "GenerateName.h"
#include "RanEditLevelView.h"

// CDlgGateEdit dialog

IMPLEMENT_DYNAMIC(CDlgGateEdit, CPropertyPage)
CDlgGateEdit::CDlgGateEdit(LOGFONT logfont)
	: CPropertyPage(CDlgGateEdit::IDD)
	, m_pFont( NULL )
	, pGLLand( NULL )
	, pGate( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CDlgGateEdit::~CDlgGateEdit()
{
}

void CDlgGateEdit::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgGateEdit, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_SAVE, OnBnClickedButtonBasicSave)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_BACK, OnBnClickedButtonBasicBack)
	ON_BN_CLICKED(IDC_BUTTON_GATE_TOMAP, OnBnClickedButtonGateTomap)
	ON_BN_CLICKED(IDC_BUTTON_GATE_NAME_CHECK, OnBnClickedButtonGateNameCheck)
	ON_BN_CLICKED(IDC_BUTTON_GATE_NAME_NEW, OnBnClickedButtonGateNameNew)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_APPLY, OnBnClickedButtonBasicApply)
	ON_BN_CLICKED(IDC_BUTTON_GATE_REGNEW, OnBnClickedButtonGateRegnew)
	ON_BN_CLICKED(IDC_BUTTON_GATE_MAT_EDIT, OnBnClickedButtonGateMatEdit)
	ON_BN_CLICKED(IDC_BUTTON_GATE_MAT_SAVE, OnBnClickedButtonGateMatSave)
	ON_BN_CLICKED(IDC_BUTTON_GATE_MAT_SCREENPOS, OnBnClickedButtonGateMatScreenpos)
	ON_BN_CLICKED(IDC_BUTTON_GATE_ID_CHECK, OnBnClickedButtonGateIdCheck)
	ON_BN_CLICKED(IDC_BUTTON_GATE_ID_NEW, OnBnClickedButtonGateIdNew)
END_MESSAGE_MAP()


// CDlgGateEdit message handlers
BOOL CDlgGateEdit::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;
}

void CDlgGateEdit::SetData( GLLandMan*	pLand, PDXLANDGATE pLandGate )
{
	if ( pLand && pLandGate ) 
	{
		pGLLand = pLand;
		pGate = NULL;
		pGate = pLandGate;

		if ( pGLLand && pGate )
		{
			m_sMap.LoadMapList( "mapslist.ini" );
			CHECKUI( true );
			ShowData();
			SetWin_Enable( this, IDC_BUTTON_GATE_REGNEW, false );
			JumpTo( pGate->GetMax(), pGate->GetMin() );
		}
	}
	else if ( pLand )
	{
		pGLLand = pLand;
		pGate = NULL;

		CHECKUI( false );
		ResetData();
		SetWin_Enable( this, IDC_BUTTON_GATE_REGNEW, true );

		OnBnClickedButtonGateNameNew();
		OnBnClickedButtonGateIdNew();
	}	
}

void CDlgGateEdit::ShowData()
{
	if ( pGLLand && pGate )
	{
		SetWin_Text( this, IDC_EDIT_GATE_NAME, pGate->GetName() );
		SetWin_Num_int( this, IDC_EDIT_GATE_ID, pGate->GetGateID() );
		SetWin_Num_int( this, IDC_EDIT_GATE_TOMAP_MID, pGate->GetToMapID().wMainID );
		SetWin_Num_int( this, IDC_EDIT_GATE_TOMAP_SID, pGate->GetToMapID().wSubID );
		SetWin_Num_int( this, IDC_EDIT_GATE_TOGATEID, pGate->GetToGateID() );
		SetWin_Check( this, IDC_CHECK_GATE_IN, pGate->GetFlags() & DxLandGate::GATE_IN );
		SetWin_Check( this, IDC_CHECK_GATE_OUT, pGate->GetFlags() & DxLandGate::GATE_OUT );
		SMAPNODE* pMap = m_sMap.FindMapNode( pGate->GetToMapID() );
		SetWin_Text( this, IDC_EDIT_GATE_TOMAP_NAME, ( pMap )? pMap->strMapName.c_str(): "Unknown Map" );
		SetWin_Num_float( this, IDC_EDIT_GATE_DIV_X, pGate->GetDiv().x );
		SetWin_Num_float( this, IDC_EDIT_GATE_DIV_Y, pGate->GetDiv().y );

		SetWin_Num_float( this, IDC_EDIT_GATE_MIN_X, pGate->GetMin().x );
		SetWin_Num_float( this, IDC_EDIT_GATE_MIN_Y, pGate->GetMin().y );
		SetWin_Num_float( this, IDC_EDIT_GATE_MIN_Z, pGate->GetMin().z );
		SetWin_Num_float( this, IDC_EDIT_GATE_MAX_X, pGate->GetMax().x );
		SetWin_Num_float( this, IDC_EDIT_GATE_MAX_Y, pGate->GetMax().y );
		SetWin_Num_float( this, IDC_EDIT_GATE_MAX_Z, pGate->GetMax().z );
	}
}

void CDlgGateEdit::ResetData()
{
	SetWin_Text( this, IDC_EDIT_GATE_NAME, "" );
	SetWin_Num_int( this, IDC_EDIT_GATE_ID, 0 );
	SetWin_Num_int( this, IDC_EDIT_GATE_TOMAP_MID, 0 );
	SetWin_Num_int( this, IDC_EDIT_GATE_TOMAP_SID, 0 );
	SetWin_Num_int( this, IDC_EDIT_GATE_TOGATEID, 0 );
	SetWin_Check( this, IDC_CHECK_GATE_IN, false );
	SetWin_Check( this, IDC_CHECK_GATE_OUT, false );
	SetWin_Text( this, IDC_EDIT_GATE_TOMAP_NAME, "");
	SetWin_Num_float( this, IDC_EDIT_GATE_DIV_X, 0.0f );
	SetWin_Num_float( this, IDC_EDIT_GATE_DIV_Y, 0.0f );
}

BOOL CDlgGateEdit::GetData()
{
	if ( pGLLand && pGate )
	{
		std::string str = GetWin_Text( this, IDC_EDIT_GATE_NAME );
		
		if ( strcmp( pGate->GetName(), str.c_str() ) )
		{
			bool bDuplicate = GateNameCheck( pGLLand, str.c_str() );
			if ( bDuplicate )
			{
				MessageBox( "Name is already used, You can create an available name by clicking New Button" );
				return FALSE;
			}
		}

		DWORD dwGateID = GetWin_Num_int( this, IDC_EDIT_GATE_ID );
		if ( dwGateID != pGate->GetGateID() )
		{
			bool bDuplicate = GateIDCheck( pGLLand, dwGateID );
			if ( bDuplicate )
			{
				MessageBox( "Gate ID is already used, You can create an available name by clicking New Button" );
				return FALSE;
			}
		}

		SNATIVEID sID;
		sID.wMainID = GetWin_Num_int( this, IDC_EDIT_GATE_TOMAP_MID );
		sID.wSubID = GetWin_Num_int( this, IDC_EDIT_GATE_TOMAP_SID );
		DWORD dwToGateID = GetWin_Num_int( this, IDC_EDIT_GATE_TOGATEID );

		DWORD dwFLAG;
		SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_GATE_IN ), dwFLAG, DxLandGate::GATE_IN );
		SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_GATE_OUT ), dwFLAG, DxLandGate::GATE_OUT );

		D3DXVECTOR2 vDiv;
		vDiv.x = GetWin_Num_float( this, IDC_EDIT_GATE_DIV_X );
		vDiv.y = GetWin_Num_float( this, IDC_EDIT_GATE_DIV_Y );

		D3DXVECTOR3 vMax,vMin;
		vMin.x = GetWin_Num_float( this, IDC_EDIT_GATE_MIN_X );
		vMin.y = GetWin_Num_float( this, IDC_EDIT_GATE_MIN_Y );
		vMin.z = GetWin_Num_float( this, IDC_EDIT_GATE_MIN_Z );
		vMax.x = GetWin_Num_float( this, IDC_EDIT_GATE_MAX_X );
		vMax.y = GetWin_Num_float( this, IDC_EDIT_GATE_MAX_Y );
		vMax.z = GetWin_Num_float( this, IDC_EDIT_GATE_MAX_Z );

		pGate->SetName( str.c_str() );
		pGate->SetGate( dwFLAG, dwGateID, sID, dwToGateID, vDiv );
		pGate->SetBox( vMax,vMin );
		pGate->MakeStartPos( pGLLand->GetNavi() );

		return TRUE;
	}

	return FALSE;
}

void CDlgGateEdit::OnBnClickedButtonBasicSave()
{
	if ( pGLLand && pGate && GetData() )
	{
		if ( m_pToolTab )
			m_pToolTab->ActiveDlgPage( DLG_GATELIST );
	}
}

void CDlgGateEdit::OnBnClickedButtonBasicBack()
{
	if ( m_pToolTab )
		m_pToolTab->ActiveDlgPage( DLG_GATELIST );
}

void CDlgGateEdit::OnBnClickedButtonGateTomap()
{
	if ( pGLLand && pGate )
	{
		CDlgListMap dlg;
		if ( dlg.DoModal() == IDOK )
		{
			SMAPNODE* pMap = m_sMap.FindMapNode( dlg.sIDSELECT );
			if ( pMap )
			{
				SetWin_Num_int( this, IDC_EDIT_GATE_TOMAP_MID, pMap->sNativeID.wMainID );
				SetWin_Num_int( this, IDC_EDIT_GATE_TOMAP_SID, pMap->sNativeID.wSubID );
				SetWin_Text( this, IDC_EDIT_GATE_TOMAP_NAME, pMap->strMapName.c_str() );
			}
		}
	}
}

void CDlgGateEdit::OnBnClickedButtonGateNameCheck()
{
	if ( pGLLand && pGate )
	{
		std::string str  = GetWin_Text( this, IDC_EDIT_GATE_NAME );

		if ( !strcmp( pGate->GetName(), str.c_str() ) )
		{
			MessageBox( "Name Valid" );
		}else{
			bool bDuplicate = GateNameCheck( pGLLand, str.c_str() );
			if ( bDuplicate )
			{
				MessageBox("Name is already used, You can create an available name by clicking new Button" );
				return;
			}else{
				MessageBox( "Name Valid" );
			}
		}
	}
}

void CDlgGateEdit::OnBnClickedButtonGateNameNew()
{
	if ( pGLLand )
	{
		std::string str = GateNameNew( pGLLand );
		if ( str.size() != 0 )
		{
			SetWin_Text( this, IDC_EDIT_GATE_NAME, str.c_str() );
		}
	}
}

void CDlgGateEdit::OnBnClickedButtonBasicApply()
{
	GetData();
}

void CDlgGateEdit::OnBnClickedButtonGateRegnew()
{
	if ( pGLLand )
	{
		D3DXVECTOR3 vPOS = CRanEditLevelView::GetView()->m_vPos;

		std::string str = GetWin_Text( this, IDC_EDIT_GATE_NAME );
		bool bDuplicate0 = GateNameCheck( pGLLand, str.c_str() );
		if ( bDuplicate0 )
		{
			MessageBox( "Name is already used, You can create an available name by clicking new Button" );
			return;
		}

		DWORD dwGateID = GetWin_Num_int( this, IDC_EDIT_GATE_ID );
		bool bDuplicate1 = GateIDCheck( pGLLand, dwGateID );
		if ( bDuplicate1 )
		{
			MessageBox( "Gate ID is already used, You can create an available ID by clicking new Button" );
			return;
		}

		PDXLANDGATE pNewGate = new DxLandGate;
		pNewGate->SetGateID( dwGateID );
		pNewGate->SetName( str.c_str() );
		pNewGate->SetPos( vPOS );
		pNewGate->MakeStartPos( pGLLand->GetNavi() );

		pGLLand->GetLandGateMan().AddLandGate( pNewGate );

		pGate = pGLLand->GetLandGateMan().FindLandGate( pNewGate->GetGateID() );

		if ( pGLLand && pGate )
		{
			SetWin_Enable( this, IDC_BUTTON_GATE_REGNEW, false );
			CHECKUI( true );
			ShowData();
		}
		else
		{
			pGLLand->GetLandGateMan().DelLandGate( pNewGate->GetGateID() );
			MessageBox( "Error Register New Gate" );
			return;
		}
	}
}

void CDlgGateEdit::JumpTo( D3DXVECTOR3 vMax, D3DXVECTOR3 vMin )
{
	float fDistX = vMax.x-vMin.x;
	float fDistY = vMax.y-vMin.y;
	float fDistZ = vMax.z-vMin.z;

	float fCenterX = vMin.x + ( fDistX / 2.0f );
	float fCenterY = vMin.y + ( fDistY / 2.0f );
	float fCenterZ = vMin.z + ( fDistZ / 2.0f );

	DxViewPort::GetInstance().CameraJump( D3DXVECTOR3( fCenterX, fCenterY + 10.0f , fCenterZ ) );
}

void CDlgGateEdit::OnBnClickedButtonGateMatEdit()
{
	if ( pGLLand && pGate )
	{
		D3DXVECTOR3 vMax,vMin;
		vMin.x = GetWin_Num_float( this, IDC_EDIT_GATE_MIN_X );
		vMin.y = GetWin_Num_float( this, IDC_EDIT_GATE_MIN_Y );
		vMin.z = GetWin_Num_float( this, IDC_EDIT_GATE_MIN_Z );
		vMax.x = GetWin_Num_float( this, IDC_EDIT_GATE_MAX_X );
		vMax.y = GetWin_Num_float( this, IDC_EDIT_GATE_MAX_Y );
		vMax.z = GetWin_Num_float( this, IDC_EDIT_GATE_MAX_Z );

		JumpTo( vMax, vMin );
		CRanEditLevelView::GetView()->m_DxEditBox.SetBox( vMax, vMin );
		CRanEditLevelView::GetView()->OnMousecontrolBoxmove();
	}
}

void CDlgGateEdit::OnBnClickedButtonGateMatSave()
{
	if ( pGLLand && pGate )
	{
		D3DXVECTOR3 vMin = CRanEditLevelView::GetView()->m_DxEditBox.m_vMin;
		D3DXVECTOR3 vMax = CRanEditLevelView::GetView()->m_DxEditBox.m_vMax;

		SetWin_Num_float( this, IDC_EDIT_GATE_MIN_X, vMin.x );
		SetWin_Num_float( this, IDC_EDIT_GATE_MIN_Y, vMin.y );
		SetWin_Num_float( this, IDC_EDIT_GATE_MIN_Z, vMin.z );
		SetWin_Num_float( this, IDC_EDIT_GATE_MAX_X, vMax.x );
		SetWin_Num_float( this, IDC_EDIT_GATE_MAX_Y, vMax.y );
		SetWin_Num_float( this, IDC_EDIT_GATE_MAX_Z, vMax.z );

		CRanEditLevelView::GetView()->OnMousecontrolNone();
	}
}

void CDlgGateEdit::OnBnClickedButtonGateMatScreenpos()
{
	D3DXVECTOR3 vPOS = CRanEditLevelView::GetView()->m_vPos;

	SetWin_Num_float( this, IDC_EDIT_GATE_MIN_X, vPOS.x - 10.0f );
	SetWin_Num_float( this, IDC_EDIT_GATE_MIN_Y, vPOS.y - 10.0f );
	SetWin_Num_float( this, IDC_EDIT_GATE_MIN_Z, vPOS.z - 10.0f );
	SetWin_Num_float( this, IDC_EDIT_GATE_MAX_X, vPOS.x + 10.0f );
	SetWin_Num_float( this, IDC_EDIT_GATE_MAX_Y, vPOS.y + 10.0f );
	SetWin_Num_float( this, IDC_EDIT_GATE_MAX_Z, vPOS.z + 10.0f );

	OnBnClickedButtonGateMatEdit();
}

void CDlgGateEdit::OnBnClickedButtonGateIdCheck()
{
	if ( pGLLand && pGate )
	{
		DWORD dwGateID = GetWin_Num_int( this, IDC_EDIT_GATE_ID );

		if ( dwGateID == pGate->GetGateID() )
		{
			MessageBox( "Gate ID Valid" );
		}else{
			bool bDuplicate = GateIDCheck( pGLLand, dwGateID );
			if ( bDuplicate )
			{
				MessageBox("Gate ID is already used, You can create an available id by clicking new Button" );
				return;
			}else{
				MessageBox( "Gate ID Valid" );
			}
		}
	}
}

void CDlgGateEdit::OnBnClickedButtonGateIdNew()
{
	if ( pGLLand )
	{
		DWORD dwID = GateNewID( pGLLand );
		SetWin_Num_int( this, IDC_EDIT_GATE_ID, dwID );
	}
}

void CDlgGateEdit::CHECKUI( bool bEnable )
{
	SetWin_Enable( this, IDC_CHECK_GATE_IN, bEnable );
	SetWin_Enable( this, IDC_CHECK_GATE_OUT, bEnable );
	SetWin_Enable( this, IDC_BUTTON_GATE_TOMAP, bEnable );
	SetWin_Enable( this, IDC_EDIT_GATE_TOMAP_MID, bEnable );
	SetWin_Enable( this, IDC_EDIT_GATE_TOMAP_SID, bEnable );
	SetWin_Enable( this, IDC_EDIT_GATE_TOGATEID, bEnable );
	SetWin_Enable( this, IDC_EDIT_GATE_DIV_X, bEnable );
	SetWin_Enable( this, IDC_EDIT_GATE_DIV_Y, bEnable );
	SetWin_Enable( this, IDC_EDIT_GATE_MIN_X, bEnable );
	SetWin_Enable( this, IDC_EDIT_GATE_MIN_Y, bEnable );
	SetWin_Enable( this, IDC_EDIT_GATE_MIN_Z, bEnable );
	SetWin_Enable( this, IDC_EDIT_GATE_MAX_X, bEnable );
	SetWin_Enable( this, IDC_EDIT_GATE_MAX_Y, bEnable );
	SetWin_Enable( this, IDC_EDIT_GATE_MAX_Z, bEnable );
	SetWin_Enable( this, IDC_BUTTON_GATE_MAT_EDIT, bEnable );
	SetWin_Enable( this, IDC_BUTTON_GATE_MAT_SAVE, bEnable );
	SetWin_Enable( this, IDC_BUTTON_GATE_MAT_SCREENPOS, bEnable );
	SetWin_Enable( this, IDC_BUTTON_BASIC_APPLY, bEnable );
	SetWin_Enable( this, IDC_BUTTON_BASIC_SAVE, bEnable );
}
