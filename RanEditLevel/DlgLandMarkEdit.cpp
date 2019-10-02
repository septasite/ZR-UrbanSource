// DlgLandMarkEdit.cpp : implementation file
//

#include "stdafx.h"
#include "RanEditLevel.h"
#include "DlgLandMarkEdit.h"
#include ".\dlglandmarkedit.h"
#include "EtcFunction.h"
#include "GenerateName.h"
#include "RanEditLevelView.h"
#include "ToolTab.h"

// CDlgLandMarkEdit dialog

IMPLEMENT_DYNAMIC(CDlgLandMarkEdit, CPropertyPage)
CDlgLandMarkEdit::CDlgLandMarkEdit(LOGFONT logfont)
	: CPropertyPage(CDlgLandMarkEdit::IDD)
	, m_pFont( NULL )
	, pGLLand( NULL )
	, pLMEdit( NULL )
{
}

CDlgLandMarkEdit::~CDlgLandMarkEdit()
{
}

void CDlgLandMarkEdit::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CDlgLandMarkEdit, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_SAVE, OnBnClickedButtonBasicSave)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_BACK, OnBnClickedButtonBasicBack)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_APPLY, OnBnClickedButtonBasicApply)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_REG, OnBnClickedButtonBasicReg)
	ON_BN_CLICKED(IDC_BUTTON_LM_NAME_CHECK, OnBnClickedButtonLmNameCheck)
	ON_BN_CLICKED(IDC_BUTTON_LM_NAME_NEW, OnBnClickedButtonLmNameNew)
	ON_BN_CLICKED(IDC_BUTTON_LM_POS_EDIT, OnBnClickedButtonLmPosEdit)
	ON_BN_CLICKED(IDC_BUTTON_LM_POS_SAVE, OnBnClickedButtonLmPosSave)
	ON_BN_CLICKED(IDC_BUTTON_LM_POS_NEW, OnBnClickedButtonLmPosNew)
END_MESSAGE_MAP()


// CDlgLandMarkEdit message handlers
BOOL CDlgLandMarkEdit::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	return TRUE;
}

void CDlgLandMarkEdit::SetData( GLLandMan*	pLand, PLANDMARK pLM )
{
	if ( pLand && pLM ) 
	{
		pGLLand = pLand;
		pLMEdit = NULL;
		pLMEdit = pLM;

		if ( pGLLand && pLMEdit )
		{
			CHECKUI( true );
			ShowData();
			SetWin_Enable( this, IDC_BUTTON_BASIC_REG, FALSE );

			D3DXVECTOR3 vPOS = pLMEdit->m_pAffineParts->vTrans;
			vPOS.y += 10.0f;
			DxViewPort::GetInstance().CameraJump( vPOS );
		}
	}
	else if ( pLand ) 
	{
		pGLLand = pLand;
		pLMEdit = NULL;
		CHECKUI( false );
		SetWin_Enable( this, IDC_BUTTON_BASIC_REG, TRUE );
		SetWin_Text( this, IDC_EDIT_LM_NAME, "" );
		OnBnClickedButtonLmNameNew();
	}
}

void CDlgLandMarkEdit::ShowData()
{
	if ( pGLLand && pLMEdit )
	{
		SetWin_Text( this, IDC_EDIT_LM_NAME, pLMEdit->m_strMARK.c_str() );
	}
}

BOOL CDlgLandMarkEdit::GetData()
{
	if ( pGLLand && pLMEdit )
	{
		return TRUE;
	}

	return FALSE;
}

void CDlgLandMarkEdit::OnBnClickedButtonBasicSave()
{
	if ( pGLLand && pLMEdit && GetData() )
	{
		if ( m_pToolTab )
			m_pToolTab->ActiveDlgPage( DLG_LMLIST );
	}
}

void CDlgLandMarkEdit::OnBnClickedButtonBasicBack()
{
	if ( m_pToolTab )
		m_pToolTab->ActiveDlgPage( DLG_LMLIST );
}

void CDlgLandMarkEdit::OnBnClickedButtonBasicApply()
{
	GetData();
}

void CDlgLandMarkEdit::OnBnClickedButtonBasicReg()
{
	if ( pGLLand  )
	{
		D3DXVECTOR3 vPOS = CRanEditLevelView::GetView()->m_vPos;
		std::string strName = GetWin_Text( this, IDC_EDIT_LM_NAME );
		
		if ( strName.size() == 0 )
		{
			MessageBox( "Blank Input!" );
			return;
		}

		bool bDuplicate = LMNameCheck( pGLLand, strName.c_str() );
		if ( bDuplicate )
		{
			MessageBox("Name is already used, You can create an available name by clicking new Button" );
			return;
		}

		PLANDMARK	pLM  = new GLLANDMARK;
		pLM->m_pAffineParts->vTrans = vPOS;
		pLM->m_strMARK = strName.c_str();
		pLM->CALC_BOX();

		pGLLand->AddLandMark( pLM );
		pGLLand->BuildLandMarkTree();

		pLMEdit = NULL;
		pLMEdit = pGLLand->FindLandMark( (char*)pLM->m_strMARK.c_str() );
	
		if ( pGLLand && pLMEdit )
		{
			SetWin_Enable( this, IDC_BUTTON_BASIC_REG, FALSE );
			CHECKUI( true );
			ShowData();
		}
		else
		{
			pGLLand->DelLandMark( pLMEdit );
			MessageBox( "Register New Schedule error. Invalid crow id. Recheck Crow ID" );
		}
	}
}

void CDlgLandMarkEdit::OnBnClickedButtonLmNameCheck()
{
	if ( pGLLand && pLMEdit )
	{
		std::string str = GetWin_Text( this, IDC_EDIT_LM_NAME );

		if ( !strcmp( pLMEdit->m_strMARK.c_str(), str.c_str() ) )
		{
			MessageBox( "Name Valid" );
		}else{
			bool bDuplicate = LMNameCheck( pGLLand, str.c_str() );
			if ( bDuplicate )
			{
				MessageBox("Name is already used, You can create an available name by clicking new Button" );
				return;
			}else{
				MessageBox( "Name Valid" );
			}
		}
	}
	else if ( pGLLand )
	{
		std::string str = GetWin_Text( this, IDC_EDIT_LM_NAME );

		bool bDuplicate = LMNameCheck( pGLLand, str.c_str() );
		if ( bDuplicate )
		{
			MessageBox("Name is already used, You can create an available name by clicking new Button" );
		}else{
			MessageBox( "Name Valid" );
		}
	}
}

void CDlgLandMarkEdit::OnBnClickedButtonLmNameNew()
{
	if ( pGLLand )
	{
		std::string str = LMNameNew( pGLLand );
		if ( str.size() != 0 )
		{
			SetWin_Text( this, IDC_EDIT_LM_NAME, str.c_str() );
		}
	}
}

void CDlgLandMarkEdit::OnBnClickedButtonLmPosEdit()
{
	if ( pGLLand && pLMEdit )
	{
		DxViewPort::GetInstance().CameraJump( pLMEdit->m_pAffineParts->vTrans );
		CRanEditLevelView::GetView()->m_DxEditMat.SetAffineMatrix( pLMEdit );
		CRanEditLevelView::GetView()->OnMousecontrolMove();
	}
}

void CDlgLandMarkEdit::OnBnClickedButtonLmPosSave()
{
	if ( pGLLand && pLMEdit )
	{
		CRanEditLevelView::GetView()->m_DxEditMat.GetAffineParts( pLMEdit->m_pAffineParts );
		CRanEditLevelView::GetView()->OnMousecontrolNone();
	}
}

void CDlgLandMarkEdit::OnBnClickedButtonLmPosNew()
{
	if ( pGLLand && pLMEdit )
	{
		D3DXVECTOR3 vPOS = CRanEditLevelView::GetView()->m_vPos;
		pLMEdit->m_pAffineParts->vTrans = vPOS;
		OnBnClickedButtonLmPosEdit();
	}
}

void CDlgLandMarkEdit::CHECKUI( bool bEnable )
{
	SetWin_Enable( this, IDC_BUTTON_LM_POS_EDIT, bEnable );
	SetWin_Enable( this, IDC_BUTTON_LM_POS_SAVE, bEnable );
	SetWin_Enable( this, IDC_BUTTON_LM_POS_NEW, bEnable );
	SetWin_Enable( this, IDC_BUTTON_BASIC_APPLY, bEnable );
	SetWin_Enable( this, IDC_BUTTON_BASIC_SAVE, bEnable );
}