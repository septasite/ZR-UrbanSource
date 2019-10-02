// DlgEffEdit.cpp : implementation file
//

#include "stdafx.h"
#include "RanEditLevel.h"
#include "DlgEffEdit.h"
#include ".\dlgeffedit.h"
#include "ToolTab.h"
#include "EtcFunction.h"
#include "RanEditLevelView.h"
#include "GenerateName.h"

// CDlgEffEdit dialog

IMPLEMENT_DYNAMIC(CDlgEffEdit, CPropertyPage)
CDlgEffEdit::CDlgEffEdit(LOGFONT logfont)
	: CPropertyPage(CDlgEffEdit::IDD)
	, m_pFont( NULL )
	, pGLLand( NULL )
	, pEffEdit( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CDlgEffEdit::~CDlgEffEdit()
{
}

void CDlgEffEdit::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgEffEdit, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_APPLY, OnBnClickedButtonBasicApply)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_SAVE, OnBnClickedButtonBasicSave)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_BACK, OnBnClickedButtonBasicBack)
	ON_BN_CLICKED(IDC_BUTTON_EFF_OPEN, OnBnClickedButtonEffOpen)
	ON_BN_CLICKED(IDC_BUTTON_EFF_EDITMAT, OnBnClickedButtonEffEditmat)
	ON_BN_CLICKED(IDC_BUTTON_EFF_MATNEW, OnBnClickedButtonEffMatnew)
	ON_BN_CLICKED(IDC_BUTTON_EDIT_EFFMATRIX_CANCEL, OnBnClickedButtonEditEffmatrixCancel)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_REGISTERNEWEFF, OnBnClickedButtonBasicRegisterneweff)
	ON_BN_CLICKED(IDC_BUTTON_NAME_CHECK, OnBnClickedButtonNameCheck)
	ON_BN_CLICKED(IDC_BUTTON_NAME_NEW, OnBnClickedButtonNameNew)
END_MESSAGE_MAP()


// CDlgEffEdit message handlers
BOOL CDlgEffEdit::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;
}

void CDlgEffEdit::SetData( GLLandMan*	pLand, PLANDEFF pEff )
{
	if ( pLand && pEff ) 
	{
		pGLLand = pLand;
		pEffEdit = NULL;
		pEffEdit = pEff;

		if ( pGLLand && pEffEdit )
		{
			CHECKUI( true );
			ShowData();
			SetWin_Enable( this, IDC_BUTTON_BASIC_REGISTERNEWEFF, false );
		}
	}
	else if ( pLand ) 
	{
		pGLLand = pLand;
		pEffEdit = NULL;
		SetWin_Enable( this, IDC_BUTTON_BASIC_REGISTERNEWEFF, true );
		CHECKUI( false );
		OnBnClickedButtonNameNew();
		SetWin_Text( this, IDC_EDIT_EFF_FILENAME, "" );
	}
}

void CDlgEffEdit::ShowData()
{
	if ( pGLLand && pEffEdit )
	{
		SetWin_Text( this, IDC_EDIT_EFF_NAME, pEffEdit->m_szName );
		SetWin_Text( this, IDC_EDIT_EFF_FILENAME, pEffEdit->m_szFileName );
	}
}

BOOL CDlgEffEdit::GetData()
{
	if ( pGLLand && pEffEdit )
	{
		std::string strName = GetWin_Text( this, IDC_EDIT_EFF_NAME );
		std::string strFileName = GetWin_Text( this, IDC_EDIT_EFF_FILENAME );

		if ( strcmp( pEffEdit->m_szName, strName.c_str() ) )
		{
			bool bDuplicate = EffectNameCheck( pGLLand, strName.c_str() );
			if ( bDuplicate )
			{
				MessageBox("Name is already used, You can create an available name by clicking new Button" );
				return FALSE;
			}
		}

		pEffEdit->SetEffect( (char*)strName.c_str(), pEffEdit->m_matWorld, strFileName.c_str(), CRanEditLevelView::GetView()->Get3DDevice() );
		pGLLand->BuildSingleEffTree();

		return TRUE;
	}

	return FALSE;
}

void CDlgEffEdit::OnBnClickedButtonBasicApply()
{
	GetData();
}

void CDlgEffEdit::OnBnClickedButtonBasicSave()
{
	if ( GetData() )
	{
		OnBnClickedButtonBasicBack();
	}
}

void CDlgEffEdit::OnBnClickedButtonBasicBack()
{
	if ( m_pToolTab )
		m_pToolTab->ActiveDlgPage( DLG_EFFLIST );

	CRanEditLevelView::GetView()->SetEffToAdjust( NULL );
}

void CDlgEffEdit::OnBnClickedButtonEffOpen()
{
	CString szFilter = "Effect File (*.egp)|*.egp|";
	CFileDialog dlg(TRUE,".egp",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter, this);
	dlg.m_ofn.lpstrInitialDir = DxEffSinglePropGMan::GetInstance().GetPath ();
	if ( dlg.DoModal() == IDOK )
	{
		SetWin_Text ( this, IDC_EDIT_EFF_FILENAME, dlg.GetFileName().GetString() );
	}
}

void CDlgEffEdit::OnBnClickedButtonEffEditmat()
{
	if ( pGLLand && pEffEdit )
	{
		matOrig = pEffEdit->m_matWorld;
		CRanEditLevelView::GetView()->SetEffToAdjust( pEffEdit );
	}
}

void CDlgEffEdit::OnBnClickedButtonEffMatnew()
{
	if ( pGLLand && pEffEdit )
	{
		D3DXVECTOR3 vPOS = CRanEditLevelView::GetView()->m_vPos;
		D3DXMATRIX matNew;
		D3DXMatrixIdentity( &matNew );
		D3DXMatrixTranslation ( &matNew, vPOS.x, vPOS.y, vPOS.z );
		matOrig = pEffEdit->m_matWorld;
		pEffEdit->m_matWorld = matNew;
		CRanEditLevelView::GetView()->SetEffToAdjust( pEffEdit );
	}
}

void CDlgEffEdit::OnBnClickedButtonEditEffmatrixCancel()
{
	if ( pGLLand && pEffEdit )
	{
		pEffEdit->m_matWorld = matOrig;
		CRanEditLevelView::GetView()->SetEffToAdjust( NULL );
	}
}

void CDlgEffEdit::OnBnClickedButtonBasicRegisterneweff()
{
	if ( pGLLand )
	{
		std::string strName = GetWin_Text( this, IDC_EDIT_EFF_NAME );
		std::string strFileName = GetWin_Text( this, IDC_EDIT_EFF_FILENAME );
		HRESULT hr;
		bool bDuplicate = EffectNameCheck( pGLLand, strName.c_str() );
		if ( bDuplicate )
		{
			MessageBox("Name is already used, You can create an available name by clicking new Button" );
			return;
		}

		if ( strFileName.size() == 0 )
		{
			MessageBox( "Blank Effect!" );
			return;
		}

		PLANDEFF pEFF = new DXLANDEFF;

		D3DXVECTOR3 vPOS = CRanEditLevelView::GetView()->m_vPos;
		D3DXMATRIX matNew;
		D3DXMatrixIdentity( &matNew );
		D3DXMatrixTranslation ( &matNew, vPOS.x, vPOS.y, vPOS.z );

		hr = pEFF->SetEffect( (char*)strName.c_str(), matNew, strFileName.c_str(), CRanEditLevelView::GetView()->Get3DDevice() );

		if ( FAILED( hr ) )
		{
			SAFE_DELETE( pEFF );
			MessageBox( "Error Register New Eff SetEffect" );
			return;
		}

		pGLLand->AddLandEff( pEFF );
		pGLLand->BuildSingleEffTree();

		pEffEdit = pGLLand->FindLandEff( pEFF->m_szName );

		if ( pGLLand && pEffEdit )
		{
			SetWin_Enable( this, IDC_BUTTON_BASIC_REGISTERNEWEFF, false );
			CHECKUI( true );
			ShowData();
		}
		else
		{
			pGLLand->DelLandEff( pEFF );
			MessageBox( "Error Register New Eff Cant find" );
			return;
		}
	}
}

void CDlgEffEdit::CHECKUI( bool bEnable )
{
	SetWin_Enable( this, IDC_BUTTON_EFF_EDITMAT, bEnable );
	SetWin_Enable( this, IDC_BUTTON_EDIT_EFFMATRIX_CANCEL, bEnable );
	SetWin_Enable( this, IDC_BUTTON_EFF_MATNEW, bEnable );
	SetWin_Enable( this, IDC_BUTTON_BASIC_APPLY, bEnable );
	SetWin_Enable( this, IDC_BUTTON_BASIC_SAVE, bEnable );
}

void CDlgEffEdit::OnBnClickedButtonNameCheck()
{
	if ( pGLLand && pEffEdit )
	{
		std::string str = GetWin_Text( this, IDC_EDIT_EFF_NAME );

		if ( !strcmp( pEffEdit->m_szName, str.c_str() ) )
		{
			MessageBox( "Name Valid" );
		}else{
			bool bDuplicate = EffectNameCheck( pGLLand, str.c_str() );
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

void CDlgEffEdit::OnBnClickedButtonNameNew()
{
	if ( pGLLand )
	{
		std::string str = EffectNameNew( pGLLand );
		SetWin_Text( this, IDC_EDIT_EFF_NAME, str.c_str() );
	}
}
