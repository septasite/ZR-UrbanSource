// DlgEtcFunction.cpp : implementation file
//

#include "stdafx.h"
#include "RanEditLevel.h"
#include "DlgEtcFunction.h"
#include "ToolTab.h"
#include "RanEditLevelView.h"
#include "EtcFunction.h"
#include ".\dlgetcfunction.h"
#include "DxEffMouseChar.h"
// CDlgEtcFunction dialog

IMPLEMENT_DYNAMIC(CDlgEtcFunction, CPropertyPage)
CDlgEtcFunction::CDlgEtcFunction(LOGFONT logfont)
	: CPropertyPage(CDlgEtcFunction::IDD)
	, m_pFont( NULL )
	, pGLLand( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CDlgEtcFunction::~CDlgEtcFunction()
{
}

void CDlgEtcFunction::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_LANDEFF, m_list_Eff );
}


BEGIN_MESSAGE_MAP(CDlgEtcFunction, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_BACK, OnBnClickedButtonBasicBack)
	ON_BN_CLICKED(IDC_BUTTON_BASIC_SAVE, OnBnClickedButtonBasicSave)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_LANDEFF, OnNMDblclkListLandeff)
	ON_BN_CLICKED(IDC_BUTTON_ETC_EFF_ADD, OnBnClickedButtonEtcEffAdd)
	ON_BN_CLICKED(IDC_BUTTON_ETC_EFF_EDIT, OnBnClickedButtonEtcEffEdit)
	ON_BN_CLICKED(IDC_BUTTON_ETC_EFF_DEL, OnBnClickedButtonEtcEffDel)
	ON_BN_CLICKED(IDC_BUTTON_ETCH_CAPTURE_CAM, OnBnClickedButtonEtchCaptureCam)
	ON_BN_CLICKED(IDC_BUTTON_ETCH_EFF_OK, OnBnClickedButtonEtchEffOk)
	ON_BN_CLICKED(IDC_BUTTON_ETCH_EFF_POS_EDIT, OnBnClickedButtonEtchEffPosEdit)
	ON_BN_CLICKED(IDC_BUTTON_ETCH_EFF_POS_SAVE, OnBnClickedButtonEtchEffPosSave)
	ON_BN_CLICKED(IDC_BUTTON_ETCH_EFF_POS_GET, OnBnClickedButtonEtchEffPosGet)
	ON_BN_CLICKED(IDC_BUTTON_ETCH_EFF_CANCEL, OnBnClickedButtonEtchEffCancel)
END_MESSAGE_MAP()


// CDlgEtcFunction message handlers
BOOL CDlgEtcFunction::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_bDlgInit = TRUE;

	{
		RECT rectCtrl;
		LONG lnWidth;
		LV_COLUMN lvColumn;

		m_list_Eff.SetExtendedStyle ( m_list_Eff.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES /*| LVS_SHOWSELALWAYS*/ );
		m_list_Eff.GetClientRect ( &rectCtrl );
		lnWidth = rectCtrl.right - rectCtrl.left;

		const int nColumnCount = 7;	
		char* szColumnName1[nColumnCount] = { "#", "Type", "Var", "Min-X", "Min-Y", "Max-X", "Max-Y"};
		int nColumnWidthPercent[nColumnCount] = { 10, 25, 13, 13, 13, 13, 13  };

		for ( int i = 0; i < nColumnCount; i++ )
		{		
			lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
			lvColumn.fmt = LVCFMT_LEFT;
			lvColumn.pszText = szColumnName1[i];
			lvColumn.iSubItem = i;
			lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
			m_list_Eff.InsertColumn (i, &lvColumn );
		}
	}

	SetWin_Combo_Init( this, IDC_COMBO_ETCH_EFF_TYPE, COMMENT::LANDEFFECT_TYPE, EMLANDEFFECT_SIZE );

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CDlgEtcFunction::SetData( GLLandMan*	pLand )
{
	if ( pLand )
	{
		pGLLand = pLand;
		pEtcFunction = NULL;
		pEtcFunction = pLand->GetLevelEtcFunc();

		if ( pLand && pEtcFunction )
		{
			ShowData();
			CRanEditLevelView::GetView()->EnableSphere( true );
		}
	}
}

void CDlgEtcFunction::ShowData()
{
	if ( pGLLand && pEtcFunction )	
	{
		SetWin_Check( this, IDC_CHECK_USE_FUNC_0, pEtcFunction->m_bUseFunction[ EMETCFUNC_LIMITTIME ] );
		SetWin_Check( this, IDC_CHECK_USE_FUNC_1, pEtcFunction->m_bUseFunction[ EMETCFUNC_CONTROLCAM ] );
		SetWin_Check( this, IDC_CHECK_USE_FUNC_2, pEtcFunction->m_bUseFunction[ EMETCFUNC_LANDEFFECT ] );
		SetWin_Check( this, IDC_CHECK_USE_FUNC_3, pEtcFunction->m_bUseFunction[ EMETCFUNC_DIFFICULTY ] );
		SetWin_Check( this, IDC_CHECK_USE_FUNC_4, pEtcFunction->m_bUseFunction[ EMETCFUNC_AROUNDREGEN ] );
		SetWin_Check( this, IDC_CHECK_USE_FUNC_5, pEtcFunction->m_bUseFunction[ EMETCFUNC_MOBCHASE ] );

		SetWin_Num_int( this, IDC_EDIT_ETC_LIMITTIME, pEtcFunction->m_sLimitTime.nLimitMinute );
		SetWin_Num_int( this, IDC_EDIT_ETC_LIMITTIMETERM, pEtcFunction->m_sLimitTime.nTellTermMinute );

		SetWin_Num_float( this, IDC_EDIT_ETC_UP, pEtcFunction->m_sControlCam.fUp );
		SetWin_Num_float( this, IDC_EDIT_ETC_DOWN, pEtcFunction->m_sControlCam.fDown );
		SetWin_Num_float( this, IDC_EDIT_ETC_LEFT, pEtcFunction->m_sControlCam.fLeft );
		SetWin_Num_float( this, IDC_EDIT_ETC_RIGHT, pEtcFunction->m_sControlCam.fRight );
		SetWin_Num_float( this, IDC_EDIT_ETC_NEAR, pEtcFunction->m_sControlCam.fNear );
		SetWin_Num_float( this, IDC_EDIT_ETC_FAR, pEtcFunction->m_sControlCam.fFar );
		SetWin_Num_float( this, IDC_EDIT_ETC_POS_X, pEtcFunction->m_sControlCam.vCamPos.x );
		SetWin_Num_float( this, IDC_EDIT_ETC_POS_Y, pEtcFunction->m_sControlCam.vCamPos.y );
		SetWin_Num_float( this, IDC_EDIT_ETC_POS_Z, pEtcFunction->m_sControlCam.vCamPos.z );
	}

	UpdateEffList();
}

BOOL CDlgEtcFunction::GetData()
{
	if ( pGLLand && pEtcFunction )
	{
		pEtcFunction->m_bUseFunction[ EMETCFUNC_LIMITTIME ] = (GetWin_Check( this, IDC_CHECK_USE_FUNC_0 ) )?	TRUE:FALSE;
		pEtcFunction->m_bUseFunction[ EMETCFUNC_CONTROLCAM ] = (GetWin_Check( this, IDC_CHECK_USE_FUNC_1 ) )?	TRUE:FALSE;
		pEtcFunction->m_bUseFunction[ EMETCFUNC_LANDEFFECT ] = (GetWin_Check( this, IDC_CHECK_USE_FUNC_2 ) )?	TRUE:FALSE;
		pEtcFunction->m_bUseFunction[ EMETCFUNC_DIFFICULTY ] = (GetWin_Check( this, IDC_CHECK_USE_FUNC_3 ) )?	TRUE:FALSE;
		pEtcFunction->m_bUseFunction[ EMETCFUNC_AROUNDREGEN ] = (GetWin_Check( this, IDC_CHECK_USE_FUNC_4 ) )?	TRUE:FALSE;
		pEtcFunction->m_bUseFunction[ EMETCFUNC_MOBCHASE ] = (GetWin_Check( this, IDC_CHECK_USE_FUNC_5 ) )?	TRUE:FALSE;

		pEtcFunction->m_sLimitTime.nLimitMinute = GetWin_Num_int( this, IDC_EDIT_ETC_LIMITTIME );
		pEtcFunction->m_sLimitTime.nTellTermMinute = GetWin_Num_int( this, IDC_EDIT_ETC_LIMITTIMETERM );

		pEtcFunction->m_sControlCam.fUp = GetWin_Num_float( this, IDC_EDIT_ETC_UP );
		pEtcFunction->m_sControlCam.fDown = GetWin_Num_float( this, IDC_EDIT_ETC_DOWN );
		pEtcFunction->m_sControlCam.fLeft = GetWin_Num_float( this, IDC_EDIT_ETC_LEFT );
		pEtcFunction->m_sControlCam.fRight = GetWin_Num_float( this, IDC_EDIT_ETC_RIGHT );
		pEtcFunction->m_sControlCam.fNear = GetWin_Num_float( this, IDC_EDIT_ETC_NEAR );
		pEtcFunction->m_sControlCam.fFar = GetWin_Num_float( this, IDC_EDIT_ETC_FAR );
		pEtcFunction->m_sControlCam.vCamPos.x = GetWin_Num_float( this, IDC_EDIT_ETC_POS_X );
		pEtcFunction->m_sControlCam.vCamPos.y = GetWin_Num_float( this, IDC_EDIT_ETC_POS_Y );
		pEtcFunction->m_sControlCam.vCamPos.z = GetWin_Num_float( this, IDC_EDIT_ETC_POS_Z );

		return TRUE;
	}

	return FALSE;
}

void CDlgEtcFunction::UpdateEffList()
{
	if ( pGLLand && pEtcFunction )
	{
		char szTempChar[512];
		m_list_Eff.DeleteAllItems();

		for( int i = 0; i < (int)pEtcFunction->m_vecLandEffect.size(); i++ )
		{
			SLANDEFFECT landEffect = pEtcFunction->m_vecLandEffect[i];

			sprintf( szTempChar, "%d", i );
			m_list_Eff.InsertItem( i, szTempChar );

			sprintf( szTempChar, "%s", COMMENT::LANDEFFECT_TYPE[landEffect.emLandEffectType].c_str() );
			m_list_Eff.SetItemText( i, 1, szTempChar );

			sprintf( szTempChar, "%g", landEffect.fValue );
			m_list_Eff.SetItemText( i, 2, szTempChar );

			sprintf( szTempChar, "%g", landEffect.vMinPos.x );
			m_list_Eff.SetItemText( i, 3, szTempChar );

			sprintf( szTempChar, "%g", landEffect.vMinPos.y );
			m_list_Eff.SetItemText( i, 4, szTempChar );

			sprintf( szTempChar, "%g", landEffect.vMaxPos.x );
			m_list_Eff.SetItemText( i, 5, szTempChar );

			sprintf( szTempChar, "%g", landEffect.vMaxPos.y );
			m_list_Eff.SetItemText( i, 6, szTempChar );
		}

		SetWin_Enable( this, IDC_COMBO_ETCH_EFF_TYPE, FALSE );
		SetWin_Enable( this, IDC_EDIT_ETCH_EFF_VAR, FALSE );
		SetWin_Enable( this, IDC_EDIT_ETCH_EFF_MIN_X, FALSE );
		SetWin_Enable( this, IDC_EDIT_ETCH_EFF_MIN_Y, FALSE );
		SetWin_Enable( this, IDC_EDIT_ETCH_EFF_MAX_X, FALSE );
		SetWin_Enable( this, IDC_EDIT_ETCH_EFF_MAX_Y, FALSE );
		SetWin_Enable( this, IDC_BUTTON_ETCH_EFF_OK, FALSE );
		SetWin_Enable( this, IDC_BUTTON_ETCH_EFF_POS_EDIT, FALSE );
		SetWin_Enable( this, IDC_BUTTON_ETCH_EFF_POS_SAVE, FALSE );
		SetWin_Enable( this, IDC_BUTTON_ETCH_EFF_POS_GET, FALSE );
	}
}

void CDlgEtcFunction::OnBnClickedButtonBasicBack()
{
	if ( m_pToolTab )
		m_pToolTab->ActiveDlgPage( DLG_MAIN );

	CRanEditLevelView::GetView()->EnableSphere( false );
}

void CDlgEtcFunction::OnBnClickedButtonBasicSave()
{
	if ( GetData() )
	{
		if ( m_pToolTab )
			m_pToolTab->ActiveDlgPage( DLG_MAIN );
	}

	CRanEditLevelView::GetView()->EnableSphere( false );
}

void CDlgEtcFunction::OnNMDblclkListLandeff(NMHDR *pNMHDR, LRESULT *pResult)
{
	// TODO: Add your control notification handler code here
	*pResult = 0;

	int nSelect = m_list_Eff.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	float fminX = static_cast<float> ( atof( m_list_Eff.GetItemText( nSelect, 3 ) ) );
	float fminY = static_cast<float> ( atof( m_list_Eff.GetItemText( nSelect, 4 ) ) );

	float fmaxX = static_cast<float> ( atof( m_list_Eff.GetItemText( nSelect, 5 ) ) );
	float fmaxY = static_cast<float> ( atof( m_list_Eff.GetItemText( nSelect, 6 ) ) );

	float fDistX = fmaxX-fminX;
	float fDistY = fmaxY-fminY;

	float fCenterX = fminX + ( fDistX / 2.0f );
	float fCenterY = fminY + ( fDistY / 2.0f );

	DxViewPort::GetInstance().CameraJump( D3DXVECTOR3( fCenterX, 0.0f, fCenterY ) );

}

void CDlgEtcFunction::OnBnClickedButtonEtcEffAdd()
{
	if ( pGLLand && pEtcFunction )
	{
		SetWin_Enable( this, IDC_COMBO_ETCH_EFF_TYPE, TRUE );
		SetWin_Enable( this, IDC_EDIT_ETCH_EFF_VAR, TRUE );
		SetWin_Enable( this, IDC_EDIT_ETCH_EFF_MIN_X, TRUE );
		SetWin_Enable( this, IDC_EDIT_ETCH_EFF_MIN_Y, TRUE );
		SetWin_Enable( this, IDC_EDIT_ETCH_EFF_MAX_X, TRUE );
		SetWin_Enable( this, IDC_EDIT_ETCH_EFF_MAX_Y, TRUE );
		SetWin_Enable( this, IDC_BUTTON_ETCH_EFF_OK, TRUE );
		SetWin_Enable( this, IDC_BUTTON_ETCH_EFF_POS_EDIT, TRUE );
		SetWin_Enable( this, IDC_BUTTON_ETCH_EFF_POS_SAVE, TRUE );
		SetWin_Enable( this, IDC_BUTTON_ETCH_EFF_POS_GET, TRUE );

		SetWin_Combo_Sel( this, IDC_COMBO_ETCH_EFF_TYPE, 0 );
		SetWin_Num_float( this, IDC_EDIT_ETCH_EFF_VAR, 0.0f );
		SetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MIN_X, 0.0f );
		SetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MIN_Y, 0.0f );
		SetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MAX_X, 0.0f );
		SetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MAX_Y, 0.0f );

		SetWin_Num_int( this, IDC_EDIT_ETCH_EFFLIST_NUM, -1 );
	}
}

void CDlgEtcFunction::OnBnClickedButtonEtcEffEdit()
{
	if ( pGLLand && pEtcFunction )
	{
		int nSelect = m_list_Eff.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
		if( nSelect == -1 ) return;
		if ( nSelect >= (int)pEtcFunction->m_vecLandEffect.size() )	return;

		SetWin_Enable( this, IDC_COMBO_ETCH_EFF_TYPE, TRUE );
		SetWin_Enable( this, IDC_EDIT_ETCH_EFF_VAR, TRUE );
		SetWin_Enable( this, IDC_EDIT_ETCH_EFF_MIN_X, TRUE );
		SetWin_Enable( this, IDC_EDIT_ETCH_EFF_MIN_Y, TRUE );
		SetWin_Enable( this, IDC_EDIT_ETCH_EFF_MAX_X, TRUE );
		SetWin_Enable( this, IDC_EDIT_ETCH_EFF_MAX_Y, TRUE );
		SetWin_Enable( this, IDC_BUTTON_ETCH_EFF_OK, TRUE );
		SetWin_Enable( this, IDC_BUTTON_ETCH_EFF_POS_EDIT, TRUE );
		SetWin_Enable( this, IDC_BUTTON_ETCH_EFF_POS_SAVE, TRUE );
		SetWin_Enable( this, IDC_BUTTON_ETCH_EFF_POS_GET, TRUE );

		SLANDEFFECT landEffect = pEtcFunction->m_vecLandEffect[nSelect];

		SetWin_Combo_Sel( this, IDC_COMBO_ETCH_EFF_TYPE, landEffect.emLandEffectType );
		SetWin_Num_float( this, IDC_EDIT_ETCH_EFF_VAR, landEffect.fValue );
		SetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MIN_X, landEffect.vMinPos.x );
		SetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MIN_Y, landEffect.vMinPos.y );
		SetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MAX_X, landEffect.vMaxPos.x );
		SetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MAX_Y, landEffect.vMaxPos.y );

		SetWin_Num_int( this, IDC_EDIT_ETCH_EFFLIST_NUM, nSelect );

		JumpTo( landEffect.vMinPos.x, landEffect.vMinPos.y, landEffect.vMaxPos.x, landEffect.vMaxPos.y );
	}
}

void CDlgEtcFunction::OnBnClickedButtonEtcEffDel()
{
	if ( pGLLand && pEtcFunction )
	{
		int nSelect = m_list_Eff.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
		if( nSelect == -1 ) return;
		if ( nSelect >= (int)pEtcFunction->m_vecLandEffect.size() )	return;

		pEtcFunction->m_vecLandEffect.erase( pEtcFunction->m_vecLandEffect.begin() + nSelect );
		UpdateEffList();
	}
}

void CDlgEtcFunction::OnBnClickedButtonEtchCaptureCam()
{
	D3DXVECTOR3 vFrom = DxViewPort::GetInstance().GetFromPt();

	SetWin_Num_float( this, IDC_EDIT_ETC_UP, 1.0f );
	SetWin_Num_float( this, IDC_EDIT_ETC_DOWN, 1.0f );
	SetWin_Num_float( this, IDC_EDIT_ETC_LEFT, 1.0f );
	SetWin_Num_float( this, IDC_EDIT_ETC_RIGHT, 1.0f );
	SetWin_Num_float( this, IDC_EDIT_ETC_NEAR, 1.0f );
	SetWin_Num_float( this, IDC_EDIT_ETC_FAR, 1.0f );
	SetWin_Num_float( this, IDC_EDIT_ETC_POS_X, vFrom.x );
	SetWin_Num_float( this, IDC_EDIT_ETC_POS_Y, vFrom.y );
	SetWin_Num_float( this, IDC_EDIT_ETC_POS_Z, vFrom.z );
}

void CDlgEtcFunction::OnBnClickedButtonEtchEffOk()
{
	if ( pGLLand && pEtcFunction )
	{
		SetWin_Enable( this, IDC_COMBO_ETCH_EFF_TYPE, FALSE );
		SetWin_Enable( this, IDC_EDIT_ETCH_EFF_VAR, FALSE );
		SetWin_Enable( this, IDC_EDIT_ETCH_EFF_MIN_X, FALSE );
		SetWin_Enable( this, IDC_EDIT_ETCH_EFF_MIN_Y, FALSE );
		SetWin_Enable( this, IDC_EDIT_ETCH_EFF_MAX_X, FALSE );
		SetWin_Enable( this, IDC_EDIT_ETCH_EFF_MAX_Y, FALSE );
		SetWin_Enable( this, IDC_BUTTON_ETCH_EFF_OK, FALSE );
		SetWin_Enable( this, IDC_BUTTON_ETCH_EFF_POS_EDIT, FALSE );
		SetWin_Enable( this, IDC_BUTTON_ETCH_EFF_POS_SAVE, FALSE );
		SetWin_Enable( this, IDC_BUTTON_ETCH_EFF_POS_GET, FALSE );

		int nEdit = GetWin_Num_int( this, IDC_EDIT_ETCH_EFFLIST_NUM );
		SetWin_Num_int( this, IDC_EDIT_ETCH_EFFLIST_NUM, -1 );

		SLANDEFFECT landEffect;
		landEffect.emLandEffectType = (EMLANDEFFECT_TYPE)GetWin_Combo_Sel( this, IDC_COMBO_ETCH_EFF_TYPE );
		landEffect.fValue = GetWin_Num_float( this, IDC_EDIT_ETCH_EFF_VAR );
		landEffect.vMinPos.x = GetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MIN_X );
		landEffect.vMinPos.y = GetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MIN_Y );
		landEffect.vMaxPos.x = GetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MAX_X );
		landEffect.vMaxPos.y = GetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MAX_Y );

		if ( nEdit < 0 ) //add mode
		{
			pEtcFunction->m_vecLandEffect.push_back( landEffect );
			UpdateEffList();
			return;
		}
		else //edit mode
		{
			if ( nEdit < (int)pEtcFunction->m_vecLandEffect.size ()  )
			{
				pEtcFunction->m_vecLandEffect[nEdit] = landEffect;
				UpdateEffList();
				return;
			}
		}
	}
}

void CDlgEtcFunction::OnBnClickedButtonEtchEffPosEdit()
{
	if ( pGLLand && pEtcFunction )
	{
		float fminx = GetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MIN_X );
		float fminy = GetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MIN_Y );
		float fmaxx = GetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MAX_X );
		float fmaxy = GetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MAX_Y );

		D3DXVECTOR3 vMin = D3DXVECTOR3( fminx, 5.0f, fminy );
		D3DXVECTOR3 vMax = D3DXVECTOR3( fmaxx, 5.0f, fmaxy );
		CRanEditLevelView::GetView()->m_DxEditBox.SetBox( vMax, vMin );
		CRanEditLevelView::GetView()->OnMousecontrolBoxmove();

		JumpTo( fminx, fminy, fmaxx, fmaxy );
	}
}

void CDlgEtcFunction::OnBnClickedButtonEtchEffPosSave()
{
	if ( pGLLand && pEtcFunction )
	{
		D3DXVECTOR3 vMin = CRanEditLevelView::GetView()->m_DxEditBox.m_vMin;
		D3DXVECTOR3 vMax = CRanEditLevelView::GetView()->m_DxEditBox.m_vMax;

		SetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MIN_X, vMin.x );
		SetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MIN_Y, vMin.z );
		SetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MAX_X, vMax.x );
		SetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MAX_Y, vMax.z );

		CRanEditLevelView::GetView()->OnMousecontrolNone();
	}
}

void CDlgEtcFunction::JumpTo( float fMinX,float fMinY, float fMaxX, float fMaxY )
{
	float fDistX = fMaxX-fMinX;
	float fDistY = fMaxY-fMinY;

	float fCenterX = fMinX + ( fDistX / 2.0f );
	float fCenterY = fMinY + ( fDistY / 2.0f );

	DxViewPort::GetInstance().CameraJump( D3DXVECTOR3( fCenterX, 0.0f, fCenterY ) );
}

void CDlgEtcFunction::OnBnClickedButtonEtchEffPosGet()
{
	if ( pGLLand && pEtcFunction )
	{

		D3DXVECTOR3 vPOS = CRanEditLevelView::GetView()->m_vPos;

		SetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MIN_X, vPOS.x - 10.0f );
		SetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MIN_Y, vPOS.z - 10.0f);
		SetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MAX_X, vPOS.x + 10.0f);
		SetWin_Num_float( this, IDC_EDIT_ETCH_EFF_MAX_Y, vPOS.z + 10.0f);

		OnBnClickedButtonEtchEffPosEdit();
	}
}

void CDlgEtcFunction::OnBnClickedButtonEtchEffCancel()
{
	SetWin_Enable( this, IDC_COMBO_ETCH_EFF_TYPE, FALSE );
	SetWin_Enable( this, IDC_EDIT_ETCH_EFF_VAR, FALSE );
	SetWin_Enable( this, IDC_EDIT_ETCH_EFF_MIN_X, FALSE );
	SetWin_Enable( this, IDC_EDIT_ETCH_EFF_MIN_Y, FALSE );
	SetWin_Enable( this, IDC_EDIT_ETCH_EFF_MAX_X, FALSE );
	SetWin_Enable( this, IDC_EDIT_ETCH_EFF_MAX_Y, FALSE );
	SetWin_Enable( this, IDC_BUTTON_ETCH_EFF_OK, FALSE );
	SetWin_Enable( this, IDC_BUTTON_ETCH_EFF_POS_EDIT, FALSE );
	SetWin_Enable( this, IDC_BUTTON_ETCH_EFF_POS_SAVE, FALSE );
	SetWin_Enable( this, IDC_BUTTON_ETCH_EFF_POS_GET, FALSE );
	SetWin_Num_int( this, IDC_EDIT_ETCH_EFFLIST_NUM, -1 );
}
