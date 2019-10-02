// TabVCF.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "TabVCF.h"
#include "ToolTab.h"

#include "StringUtils.h"
#include "EtcFunction.h"
#include "DxSkinAniMan.h"
#include ".\tabvcf.h"

// CTabVCF dialog

IMPLEMENT_DYNAMIC(CTabVCF, CPropertyPage)
CTabVCF::CTabVCF(LOGFONT logfont)
	: CPropertyPage(CTabVCF::IDD)
	,m_pFont( NULL )
{
	m_bActive = FALSE;
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	bAddBone = false;
	bADD = false;
	strFileName ="";
}

CTabVCF::~CTabVCF()
{
}

void CTabVCF::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ANI, m_list_Ani);
	DDX_Control(pDX, IDC_LIST_BONE, m_list_Bone);
}


BEGIN_MESSAGE_MAP(CTabVCF, CPropertyPage)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ANI, OnNMDblclkListAni)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_ADD, OnBnClickedButtonAnilistAdd)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_DELETE, OnBnClickedButtonAnilistDelete)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_EDIT, OnBnClickedButtonAnilistEdit)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_OK, OnBnClickedButtonAnilistOk)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BONE, OnNMDblclkListBone)
	ON_BN_CLICKED(IDC_BUTTON_BONELIST_ADD, OnBnClickedButtonBonelistAdd)
	ON_BN_CLICKED(IDC_BUTTON_BONELIST_DEL, OnBnClickedButtonBonelistDel)
	ON_BN_CLICKED(IDC_BUTTON_BONELIST_EDIT, OnBnClickedButtonBonelistEdit)
	ON_BN_CLICKED(IDC_BUTTON_BONELIST_OK, OnBnClickedButtonBonelistOk)
	ON_BN_CLICKED(IDC_BUTTON_HEAD_VCF, OnBnClickedButtonHead)
	ON_BN_CLICKED(IDC_BUTTON_BODY_VCF, OnBnClickedButtonBody)
	ON_BN_CLICKED(IDC_BUTTON_PANT_VCF, OnBnClickedButtonPant)
	ON_BN_CLICKED(IDC_BUTTON_GLOVE_VCF, OnBnClickedButtonGlove)
	ON_BN_CLICKED(IDC_BUTTON_RHAND_VCF, OnBnClickedButtonRhand)
	ON_BN_CLICKED(IDC_BUTTON_LHAND_VCF, OnBnClickedButtonLhand)
	ON_BN_CLICKED(IDC_BUTTON_FOOT_VCF, OnBnClickedButtonFoot)
	ON_BN_CLICKED(IDC_BUTTON_HAIR_VCF, OnBnClickedButtonHair)
	ON_BN_CLICKED(IDC_BUTTON_ACC_VCF, OnBnClickedButtonAcc)
	ON_BN_CLICKED(IDC_BUTTON_VEHICLE_VCF, OnBnClickedButtonVehicle)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_SEARCH, OnBnClickedButtonAnilistSearch)
	ON_BN_CLICKED(IDC_BUTTON_VCF_LOAD, OnBnClickedButtonVcfLoad)
	ON_BN_CLICKED(IDC_BUTTON_VCF_SAVE, OnBnClickedButtonVcfSave)
	ON_BN_CLICKED(IDC_BUTTON_NECK_VCF, OnBnClickedButtonNeckVcf)
	ON_BN_CLICKED(IDC_BUTTON_WRIST_VCF, OnBnClickedButtonWristVcf)
	ON_BN_CLICKED(IDC_BUTTON_RFINGER_VCF, OnBnClickedButtonRfingerVcf)
	ON_BN_CLICKED(IDC_BUTTON_LFINGER_VCF, OnBnClickedButtonLfingerVcf)
	ON_BN_CLICKED(IDC_BUTTON_WING_VCF, OnBnClickedButtonWingVcf)
	ON_BN_CLICKED(IDC_BUTTON_AURA_VCF, OnBnClickedButtonAuraVcf)
	ON_BN_CLICKED(IDC_BUTTON_BELT_VCF, OnBnClickedButtonBeltVcf)
	ON_BN_CLICKED(IDC_BUTTON_EAR_VCF, OnBnClickedButtonEarVcf)
	ON_BN_CLICKED(IDC_BUTTON_ACCE_VCF, OnBnClickedButtonAcceVcf)
	ON_BN_CLICKED(IDC_BUTTON_CON_VCF, OnBnClickedButtonConVcf)
	ON_BN_CLICKED(IDC_BUTTON_BONELIST_CANCEL, OnBnClickedButtonBonelistCancel)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_FOLDER2, OnBnClickedButtonAnilistFolder2)
	ON_BN_CLICKED(IDC_BUTTON_CHF_NEW2, OnBnClickedButtonChfNew2)
END_MESSAGE_MAP()


// CTabVCF message handlers
BOOL CTabVCF::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	if (!m_bActive)
	{
		RECT rectCtrl;
		LONG lnWidth;
		LV_COLUMN lvColumn;

		m_list_Ani.SetExtendedStyle ( m_list_Ani.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
		m_list_Ani.GetClientRect ( &rectCtrl );
		lnWidth = rectCtrl.right - rectCtrl.left;

		const int nColumnCount = 2;	
		char* szColumnName1[nColumnCount] = { "No", "Animation Cfg" };
		int nColumnWidthPercent1[nColumnCount] = { 20, 80 };

		for ( int i = 0; i < nColumnCount; i++ )
		{		
			lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
			lvColumn.fmt = LVCFMT_LEFT;
			lvColumn.pszText = szColumnName1[i];
			lvColumn.iSubItem = i;
			lvColumn.cx = ( lnWidth*nColumnWidthPercent1[i] ) / 100;
			m_list_Ani.InsertColumn (i, &lvColumn );
		}

		RECT rectCtrl1;
		LONG lnWidth1;
		LV_COLUMN lvColumn1;

		m_list_Bone.SetExtendedStyle ( m_list_Bone.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
		m_list_Bone.GetClientRect ( &rectCtrl1 );
		lnWidth1 = rectCtrl1.right - rectCtrl1.left;

		const int nColumnCount1 = 5;	
		char* szColumnName2[nColumnCount1] = { "No", "Bone 1", "Bone 2", "Bone 3", "Bone Name" };
		int nColumnWidthPercent2[nColumnCount1] = { 7, 16, 16, 16, 45 };

		for ( int i = 0; i < nColumnCount1; i++ )
		{		
			lvColumn1.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
			lvColumn1.fmt = LVCFMT_LEFT;
			lvColumn1.pszText = szColumnName2[i];
			lvColumn1.iSubItem = i;
			lvColumn1.cx = ( lnWidth1*nColumnWidthPercent2[i] ) / 100;
			m_list_Bone.InsertColumn (i, &lvColumn1 );
		}

		SetWin_ShowWindow ( this, IDC_BUTTON_VCF_SAVE, SW_HIDE );
	}

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CTabVCF::OnBnClickedButtonVcfLoad()
{
	CString szFilterInput = "VCF|*.VCf|";
	CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
	dlgInput.m_ofn.lpstrInitialDir = DxSkinCharDataContainer::GetInstance().GetPath();
	if ( dlgInput.DoModal() != IDOK ) return;

	Reset();
	BOOL bOK = m_pVcfCode.LoadFile ( dlgInput.GetFileName() );
	if ( bOK )
	{
		SetWin_Text ( this, IDC_EDIT_FILENAME, dlgInput.GetFileName() );
		strFileName = dlgInput.GetFileName();
		UpdateData();
		m_bActive = TRUE;
		SetWin_ShowWindow ( this, IDC_BUTTON_VCF_SAVE, SW_SHOW );
		m_pToolTab->AddHistoryOpen( "VCF Editor",dlgInput.GetFileName().GetString() );
	}
	else
	{
		MessageBox ( "Failure to Load :(" );
		m_pToolTab->AddHistoryOpenFail( "VCF Editor",dlgInput.GetFileName().GetString() );
	}
}

void CTabVCF::OnBnClickedButtonVcfSave()
{
	if ( SaveData () )
	{
		CString szFilter = "VCF File (*.vcf)|*.vcf|";
		CFileDialog dlg(FALSE,".vcf",strFileName.GetString(),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
		(CTabVCF*)this);

		dlg.m_ofn.lpstrInitialDir = DxSkinVehicleDataContainer::GetInstance().GetPath();
		if ( dlg.DoModal() == IDOK )
		{
			BOOL bOK = m_pVcfCode.SaveFile ( dlg.GetFileName() );
			if ( bOK )
			{
				SetWin_Text ( this, IDC_EDIT_FILENAME, dlg.GetFileName() );
				MessageBox ( "Save Done :P" );
				m_pToolTab->AddHistorySave( "VCF Editor",dlg.GetFileName().GetString() );
			}
			else
			{
				MessageBox ( "Failure to Save :(" );
				m_pToolTab->AddHistorySaveFail( "VCF Editor",dlg.GetFileName().GetString() );
			}
		}
	}
}

void CTabVCF::OnBnClickedButtonChfNew2()
{
	Reset();
	SetWin_ShowWindow ( this, IDC_BUTTON_VCF_SAVE, SW_SHOW );
	SetWin_Text ( this, IDC_EDIT_FILENAME, "" );
	m_bActive = TRUE;
}

BOOL CTabVCF::UpdateData()
{
	SetWin_Text ( this, IDC_EDIT_BONE_FILE, m_pVcfCode.m_strSkeleton.c_str() );
	SetWin_Num_float ( this, IDC_EDIT_SCALE, m_pVcfCode.m_fScale );
	SetWin_Num_float ( this, IDC_EDIT_FIRST_ROT_X, m_pVcfCode.m_vRotation_Font.x );
	SetWin_Num_float ( this, IDC_EDIT_FIRST_ROT_Y, m_pVcfCode.m_vRotation_Font.y );
	SetWin_Num_float ( this, IDC_EDIT_FIRST_ROT_Z, m_pVcfCode.m_vRotation_Font.z );
	SetWin_Num_float ( this, IDC_EDIT_FIRST_POS_X, m_pVcfCode.m_vTransform_Font.x );
	SetWin_Num_float ( this, IDC_EDIT_FIRST_POS_Y, m_pVcfCode.m_vTransform_Font.y );
	SetWin_Num_float ( this, IDC_EDIT_FIRST_POS_Z, m_pVcfCode.m_vTransform_Font.z );
	SetWin_Text ( this, IDC_EDIT_FIRST_STR, m_pVcfCode.m_strChar_Font.c_str() );
	SetWin_Num_float ( this, IDC_EDIT_SECOND_ROT_X, m_pVcfCode.m_vRotation_Back.x );
	SetWin_Num_float ( this, IDC_EDIT_SECOND_ROT_Y, m_pVcfCode.m_vRotation_Back.y );
	SetWin_Num_float ( this, IDC_EDIT_SECOND_ROT_Z, m_pVcfCode.m_vRotation_Back.z );
	SetWin_Num_float ( this, IDC_EDIT_SECOND_POS_X, m_pVcfCode.m_vTransform_Back.x );
	SetWin_Num_float ( this, IDC_EDIT_SECOND_POS_Y, m_pVcfCode.m_vTransform_Back.y );
	SetWin_Num_float ( this, IDC_EDIT_SECOND_POS_Z, m_pVcfCode.m_vTransform_Back.z );
	SetWin_Text ( this, IDC_EDIT_SECOND_STR, m_pVcfCode.m_strChar_Back.c_str() );

	SetWin_Text ( this, IDC_EDIT_HEAD_VCF, m_pVcfCode.m_strPIECE[0].c_str() );
	SetWin_Text ( this, IDC_EDIT_BODY_VCF, m_pVcfCode.m_strPIECE[1].c_str() );
	SetWin_Text ( this, IDC_EDIT_PANT_VCF, m_pVcfCode.m_strPIECE[2].c_str() );
	SetWin_Text ( this, IDC_EDIT_GLOVE_VCF, m_pVcfCode.m_strPIECE[3].c_str() );
	SetWin_Text ( this, IDC_EDIT_RHAND_VCF, m_pVcfCode.m_strPIECE[4].c_str() );
	SetWin_Text ( this, IDC_EDIT_LHAND_VCF, m_pVcfCode.m_strPIECE[5].c_str() );
	SetWin_Text ( this, IDC_EDIT_FOOT_VCF, m_pVcfCode.m_strPIECE[6].c_str() );
	SetWin_Text ( this, IDC_EDIT_HAIR_VCF, m_pVcfCode.m_strPIECE[7].c_str() );
	SetWin_Text ( this, IDC_EDIT_ACC_VCF, m_pVcfCode.m_strPIECE[8].c_str() );
	SetWin_Text ( this, IDC_EDIT_VEHICLE_VCF, m_pVcfCode.m_strPIECE[9].c_str() );

	SetWin_Text ( this, IDC_EDIT_NECK_VCF, m_pVcfCode.m_strPIECE[10].c_str() );
	SetWin_Text ( this, IDC_EDIT_WRIST_VCF, m_pVcfCode.m_strPIECE[11].c_str() );
	SetWin_Text ( this, IDC_EDIT_RFINGER_VCF, m_pVcfCode.m_strPIECE[12].c_str() );
	SetWin_Text ( this, IDC_EDIT_LFINGER_VCF, m_pVcfCode.m_strPIECE[13].c_str() );
	SetWin_Text ( this, IDC_EDIT_WING_VCF, m_pVcfCode.m_strPIECE[14].c_str() );
	SetWin_Text ( this, IDC_EDIT_AURA_VCF, m_pVcfCode.m_strPIECE[15].c_str() );
	SetWin_Text ( this, IDC_EDIT_BELT_VCF, m_pVcfCode.m_strPIECE[16].c_str() );
	SetWin_Text ( this, IDC_EDIT_EAR_VCF, m_pVcfCode.m_strPIECE[17].c_str() );
	SetWin_Text ( this, IDC_EDIT_ACCE_VCF, m_pVcfCode.m_strPIECE[18].c_str() );
	SetWin_Text ( this, IDC_EDIT_CON_VCF, m_pVcfCode.m_strPIECE[19].c_str() );


	InitAniList();
	InitBoneList();

	return TRUE;
}

BOOL CTabVCF::SaveData()
{
	m_pVcfCode.m_strSkeleton = GetWin_Text ( this, IDC_EDIT_BONE_FILE ).GetString();
	m_pVcfCode.m_fScale = GetWin_Num_float ( this, IDC_EDIT_SCALE );
	m_pVcfCode.m_vRotation_Font.x = GetWin_Num_float ( this, IDC_EDIT_FIRST_ROT_X );
	m_pVcfCode.m_vRotation_Font.y = GetWin_Num_float ( this, IDC_EDIT_FIRST_ROT_Y );
	m_pVcfCode.m_vRotation_Font.z = GetWin_Num_float ( this, IDC_EDIT_FIRST_ROT_Z );
	m_pVcfCode.m_vTransform_Font.x = GetWin_Num_float ( this, IDC_EDIT_FIRST_POS_X );
	m_pVcfCode.m_vTransform_Font.y = GetWin_Num_float ( this, IDC_EDIT_FIRST_POS_Y );
	m_pVcfCode.m_vTransform_Font.z = GetWin_Num_float ( this, IDC_EDIT_FIRST_POS_Z );
	m_pVcfCode.m_strChar_Font = GetWin_Text ( this, IDC_EDIT_FIRST_STR ).GetString();
	m_pVcfCode.m_vRotation_Back.x = GetWin_Num_float ( this, IDC_EDIT_SECOND_ROT_X );
	m_pVcfCode.m_vRotation_Back.y = GetWin_Num_float ( this, IDC_EDIT_SECOND_ROT_Y );
	m_pVcfCode.m_vRotation_Back.z = GetWin_Num_float ( this, IDC_EDIT_SECOND_ROT_Z );
	m_pVcfCode.m_vTransform_Back.x = GetWin_Num_float ( this, IDC_EDIT_SECOND_POS_X );
	m_pVcfCode.m_vTransform_Back.y = GetWin_Num_float ( this, IDC_EDIT_SECOND_POS_Y );
	m_pVcfCode.m_vTransform_Back.z = GetWin_Num_float ( this, IDC_EDIT_SECOND_POS_Z );
	m_pVcfCode.m_strChar_Back = GetWin_Text ( this, IDC_EDIT_SECOND_STR ).GetString();

	m_pVcfCode.m_strPIECE[0] = GetWin_Text ( this, IDC_EDIT_HEAD_VCF ).GetString();
	m_pVcfCode.m_strPIECE[1] = GetWin_Text ( this, IDC_EDIT_BODY_VCF ).GetString();
	m_pVcfCode.m_strPIECE[2] = GetWin_Text ( this, IDC_EDIT_PANT_VCF ).GetString();
	m_pVcfCode.m_strPIECE[3] = GetWin_Text ( this, IDC_EDIT_GLOVE_VCF ).GetString();
	m_pVcfCode.m_strPIECE[4] = GetWin_Text ( this, IDC_EDIT_RHAND_VCF ).GetString();
	m_pVcfCode.m_strPIECE[5] = GetWin_Text ( this, IDC_EDIT_LHAND_VCF ).GetString();
	m_pVcfCode.m_strPIECE[6] = GetWin_Text ( this, IDC_EDIT_FOOT_VCF ).GetString();
	m_pVcfCode.m_strPIECE[7] = GetWin_Text ( this, IDC_EDIT_HAIR_VCF ).GetString();
	m_pVcfCode.m_strPIECE[8] = GetWin_Text ( this, IDC_EDIT_ACC_VCF ).GetString();
	m_pVcfCode.m_strPIECE[9] = GetWin_Text ( this, IDC_EDIT_VEHICLE_VCF ).GetString();
	m_pVcfCode.m_strPIECE[10] = GetWin_Text ( this, IDC_EDIT_NECK_VCF ).GetString();
	m_pVcfCode.m_strPIECE[11] = GetWin_Text ( this, IDC_EDIT_WRIST_VCF ).GetString();
	m_pVcfCode.m_strPIECE[12] = GetWin_Text ( this, IDC_EDIT_RFINGER_VCF ).GetString();
	m_pVcfCode.m_strPIECE[13] = GetWin_Text ( this, IDC_EDIT_LFINGER_VCF ).GetString();
	m_pVcfCode.m_strPIECE[14] = GetWin_Text ( this, IDC_EDIT_WING_VCF ).GetString();
	m_pVcfCode.m_strPIECE[15] = GetWin_Text ( this, IDC_EDIT_AURA_VCF ).GetString();
	m_pVcfCode.m_strPIECE[16] = GetWin_Text ( this, IDC_EDIT_BELT_VCF ).GetString();
	m_pVcfCode.m_strPIECE[17] = GetWin_Text ( this, IDC_EDIT_EAR_VCF ).GetString();
	m_pVcfCode.m_strPIECE[18] = GetWin_Text ( this, IDC_EDIT_ACCE_VCF ).GetString();
	m_pVcfCode.m_strPIECE[19] = GetWin_Text ( this, IDC_EDIT_CON_VCF ).GetString();

	return TRUE;
}

void CTabVCF::InitAniList()
{
	m_list_Ani.DeleteAllItems();

	int iAniSize = (int)m_pVcfCode.m_vecANIFILE.size();
	char szTempChar[256];

	for ( int i = 0; i < iAniSize; i++ )
	{
		sprintf( szTempChar, "%d", i );
		m_list_Ani.InsertItem( i, szTempChar );
		sprintf( szTempChar, "%s", m_pVcfCode.m_vecANIFILE[i].c_str() );
		m_list_Ani.SetItemText( i, 1, szTempChar );
	}

	SetWin_ShowWindow ( this, IDC_EDIT_ANILIST_NAME, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_OK, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_SEARCH, SW_HIDE );
}

void CTabVCF::OnBnClickedButtonAnilistAdd()
{
	bADD = true;
	SetWin_ShowWindow ( this, IDC_EDIT_ANILIST_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_OK, SW_SHOW );	
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_SEARCH, SW_SHOW );
}

void CTabVCF::OnBnClickedButtonAnilistDelete()
{
	int nSelect = m_list_Ani.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;
	m_pVcfCode.m_vecANIFILE.erase ( m_pVcfCode.m_vecANIFILE.begin()+nSelect );
	InitAniList();
}

void CTabVCF::OnNMDblclkListAni(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	int nSelect = m_list_Ani.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	SetWin_Text ( this, IDC_EDIT_ANILIST_NAME, m_pVcfCode.m_vecANIFILE[nSelect].c_str() );
	bADD = false;
	SetWin_ShowWindow ( this, IDC_EDIT_ANILIST_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_OK, SW_SHOW );	
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_SEARCH, SW_SHOW );
}

void CTabVCF::OnBnClickedButtonAnilistEdit()
{
	int nSelect = m_list_Ani.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	SetWin_Text ( this, IDC_EDIT_ANILIST_NAME, m_pVcfCode.m_vecANIFILE[nSelect].c_str());
	bADD = false;
	SetWin_ShowWindow ( this, IDC_EDIT_ANILIST_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_OK, SW_SHOW );	
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_SEARCH, SW_SHOW );
}

void CTabVCF::OnBnClickedButtonAnilistSearch()
{
	CString szFilter = "Animation File (*.bin)|*.bin|";
	CFileDialog dlg(TRUE,".bin",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
		(CTabVCF*)this);

	dlg.m_ofn.lpstrInitialDir = DxSkinAniMan::GetInstance().GetPath();
	if ( dlg.DoModal() == IDOK )
	{
		std::string strAniName = dlg.GetFileName().GetString();
		SetWin_Text ( this, IDC_EDIT_ANILIST_NAME, strAniName.c_str() );
	}
}

void CTabVCF::OnBnClickedButtonAnilistOk()
{
	if ( !bADD )
	{
		int nSelect = m_list_Ani.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
		if( nSelect == -1 ) return;
		m_pVcfCode.m_vecANIFILE.erase ( m_pVcfCode.m_vecANIFILE.begin()+nSelect );	
	}

	CString strBinName = "";
	CString strFileName = "";
	strFileName = GetWin_Text ( this, IDC_EDIT_ANILIST_NAME ).GetString();
	int nIndex = strFileName.ReverseFind ( '.' );
	strBinName = strFileName.Left(nIndex) + ".x";
	m_pVcfCode.m_vecANIFILE.push_back ( strBinName.GetString() );

	InitAniList();
	SetWin_ShowWindow ( this, IDC_EDIT_ANILIST_NAME, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_OK, SW_HIDE );	
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_SEARCH, SW_HIDE );
}

void CTabVCF::InitBoneList()
{
	m_list_Bone.DeleteAllItems();

	int iBoneSize = (int)m_pVcfCode.m_dwBONE;
	char szTempChar[256];

	for ( int i = 0; i < iBoneSize; i++ )
	{
		sprintf( szTempChar, "%d", i );
		m_list_Bone.InsertItem( i, szTempChar );
		sprintf( szTempChar, "%.2f%%", m_pVcfCode.m_fBONE1[i] );
		m_list_Bone.SetItemText( i, 1, szTempChar );
		sprintf( szTempChar, "%.2f%%", m_pVcfCode.m_fBONE2[i] );
		m_list_Bone.SetItemText( i, 2, szTempChar );
		sprintf( szTempChar, "%.2f%%", m_pVcfCode.m_fBONE3[i] );
		m_list_Bone.SetItemText( i, 3, szTempChar );
		sprintf( szTempChar, "%s", m_pVcfCode.m_strBONE[i].c_str() );
		m_list_Bone.SetItemText( i, 4, szTempChar );
	}

	SetWin_ShowWindow ( this, IDC_EDIT_BONE1, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE2, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE3, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE_NAME, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_OK, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_CANCEL, SW_HIDE );
}

void CTabVCF::OnNMDblclkListBone(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	SetWin_ShowWindow ( this, IDC_EDIT_BONE1, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE2, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE3, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_OK, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_CANCEL, SW_SHOW );

	int nSelect = m_list_Bone.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	SetWin_Num_float ( this, IDC_EDIT_BONE1, m_pVcfCode.m_fBONE1[nSelect] );
	SetWin_Num_float ( this, IDC_EDIT_BONE2, m_pVcfCode.m_fBONE2[nSelect] );
	SetWin_Num_float ( this, IDC_EDIT_BONE3, m_pVcfCode.m_fBONE3[nSelect] );
	SetWin_Text ( this, IDC_EDIT_BONE_NAME, m_pVcfCode.m_strBONE[nSelect].c_str() );
	bAddBone = false;
}

void CTabVCF::OnBnClickedButtonBonelistAdd()
{
	SetWin_ShowWindow ( this, IDC_EDIT_BONE1, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE2, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE3, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_OK, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_CANCEL, SW_SHOW );
	bAddBone = true;
}

void CTabVCF::OnBnClickedButtonBonelistDel()
{
	int nSelect = m_list_Bone.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	int iBoneSize = (int)m_pVcfCode.m_dwBONE;
	for ( int i = nSelect; i < iBoneSize; i++ )
	{
		m_pVcfCode.m_fBONE1[i] = m_pVcfCode.m_fBONE1[i+1];
		m_pVcfCode.m_fBONE2[i] = m_pVcfCode.m_fBONE2[i+1];
		m_pVcfCode.m_fBONE3[i] = m_pVcfCode.m_fBONE3[i+1];
		m_pVcfCode.m_strBONE[i] = m_pVcfCode.m_strBONE[i+1].c_str();
	}

	m_pVcfCode.m_dwBONE = m_pVcfCode.m_dwBONE - 1;
	InitBoneList();
}

void CTabVCF::OnBnClickedButtonBonelistEdit()
{
	int nSelect = m_list_Bone.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	SetWin_ShowWindow ( this, IDC_EDIT_BONE1, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE2, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE3, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_OK, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_CANCEL, SW_SHOW );

	SetWin_Num_float ( this, IDC_EDIT_BONE1, m_pVcfCode.m_fBONE1[nSelect] );
	SetWin_Num_float ( this, IDC_EDIT_BONE2, m_pVcfCode.m_fBONE2[nSelect] );
	SetWin_Num_float ( this, IDC_EDIT_BONE3, m_pVcfCode.m_fBONE3[nSelect] );
	SetWin_Text ( this, IDC_EDIT_BONE_NAME, m_pVcfCode.m_strBONE[nSelect].c_str() );

	bAddBone = false;
}

void CTabVCF::OnBnClickedButtonBonelistOk()
{
	if (bAddBone)
	{
		DWORD dwSize(m_pVcfCode.m_dwBONE);
		m_pVcfCode.m_dwBONE = dwSize + 1;
		m_pVcfCode.m_fBONE1[dwSize] = GetWin_Num_float ( this, IDC_EDIT_BONE1 );
		m_pVcfCode.m_fBONE2[dwSize] = GetWin_Num_float ( this, IDC_EDIT_BONE2 );
		m_pVcfCode.m_fBONE3[dwSize] = GetWin_Num_float ( this, IDC_EDIT_BONE3 );
		m_pVcfCode.m_strBONE[dwSize] = GetWin_Text ( this, IDC_EDIT_BONE_NAME ).GetString();
	}
	else
	{
		int nSelect = m_list_Bone.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
		if( nSelect == -1 ) return;

		m_pVcfCode.m_fBONE1[nSelect] = GetWin_Num_float ( this, IDC_EDIT_BONE1 );
		m_pVcfCode.m_fBONE2[nSelect] = GetWin_Num_float ( this, IDC_EDIT_BONE2 );
		m_pVcfCode.m_fBONE3[nSelect] = GetWin_Num_float ( this, IDC_EDIT_BONE3 );
		m_pVcfCode.m_strBONE[nSelect] = GetWin_Text ( this, IDC_EDIT_BONE_NAME ).GetString();
	}
	InitBoneList();
}

void CTabVCF::OnBnClickedButtonBonelistCancel()
{
	SetWin_ShowWindow ( this, IDC_EDIT_BONE1, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE2, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE3, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE_NAME, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_OK, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_CANCEL, SW_HIDE );
	SetWin_Num_float ( this, IDC_EDIT_BONE1, 0.0f );
	SetWin_Num_float ( this, IDC_EDIT_BONE2, 0.0f );
	SetWin_Num_float ( this, IDC_EDIT_BONE3, 0.0f );
	SetWin_Text ( this, IDC_EDIT_BONE_NAME, "" );
}


void CTabVCF::LoadCpsfile ( int nID )
{
	CString szFilter = "Wearing File (*.cps; *.aps; *.vps)|*.cps; *.aps; *.vps|";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
		(CTabVCF*)this);

	dlg.m_ofn.lpstrInitialDir = DxSkinPieceDataContainer::GetInstance().GetPath ();
	if ( dlg.DoModal() == IDOK )
	{
		SetWin_Text ( this, nID, dlg.GetFileName().GetString() );
	}
}

void CTabVCF::OnBnClickedButtonHead(){			LoadCpsfile ( IDC_EDIT_HEAD_VCF );}
void CTabVCF::OnBnClickedButtonBody(){			LoadCpsfile ( IDC_EDIT_BODY_VCF );}
void CTabVCF::OnBnClickedButtonPant(){			LoadCpsfile ( IDC_EDIT_PANT_VCF );}
void CTabVCF::OnBnClickedButtonGlove(){			LoadCpsfile ( IDC_EDIT_GLOVE_VCF );}
void CTabVCF::OnBnClickedButtonRhand(){			LoadCpsfile ( IDC_EDIT_RHAND_VCF );}
void CTabVCF::OnBnClickedButtonLhand(){			LoadCpsfile ( IDC_EDIT_LHAND_VCF );}
void CTabVCF::OnBnClickedButtonFoot(){			LoadCpsfile ( IDC_EDIT_FOOT_VCF );}
void CTabVCF::OnBnClickedButtonHair(){			LoadCpsfile ( IDC_EDIT_HAIR_VCF );}
void CTabVCF::OnBnClickedButtonAcc(){			LoadCpsfile ( IDC_EDIT_ACC_VCF );}
void CTabVCF::OnBnClickedButtonVehicle(){		LoadCpsfile ( IDC_EDIT_VEHICLE_VCF );}

void CTabVCF::OnBnClickedButtonNeckVcf(){		LoadCpsfile ( IDC_EDIT_NECK_VCF );}
void CTabVCF::OnBnClickedButtonWristVcf(){		LoadCpsfile ( IDC_EDIT_WRIST_VCF );}
void CTabVCF::OnBnClickedButtonRfingerVcf(){	LoadCpsfile ( IDC_EDIT_RFINGER_VCF );}
void CTabVCF::OnBnClickedButtonLfingerVcf(){	LoadCpsfile ( IDC_EDIT_LFINGER_VCF );}
void CTabVCF::OnBnClickedButtonWingVcf(){		LoadCpsfile ( IDC_EDIT_WING_VCF );}
void CTabVCF::OnBnClickedButtonAuraVcf(){		LoadCpsfile ( IDC_EDIT_AURA_VCF );}
void CTabVCF::OnBnClickedButtonBeltVcf(){		LoadCpsfile ( IDC_EDIT_BELT_VCF );}
void CTabVCF::OnBnClickedButtonEarVcf(){		LoadCpsfile ( IDC_EDIT_EAR_VCF );}
void CTabVCF::OnBnClickedButtonAcceVcf(){		LoadCpsfile ( IDC_EDIT_ACCE_VCF );}
void CTabVCF::OnBnClickedButtonConVcf(){		LoadCpsfile ( IDC_EDIT_CON_VCF );}


void CTabVCF::Reset()
{
	SetWin_Text ( this, IDC_EDIT_FILENAME, "" );
	m_pVcfCode.Reset();
	SetWin_ShowWindow ( this, IDC_BUTTON_VCF_SAVE, SW_HIDE );
	m_bActive = FALSE;
	UpdateData();
}

void CTabVCF::OnBnClickedButtonAnilistFolder2()
{
	BROWSEINFO biInput;
	ZeroMemory(&biInput, sizeof(BROWSEINFO));
	biInput.hwndOwner = m_hWnd;
	biInput.lpszTitle = "Select Folder";
	biInput.pidlRoot = NULL;
	biInput.ulFlags = BIF_DONTGOBELOWDOMAIN | BIF_NEWDIALOGSTYLE | BIF_EDITBOX | BIF_NONEWFOLDERBUTTON | BIF_RETURNFSANCESTORS | BIF_RETURNONLYFSDIRS;

	LPITEMIDLIST pidlFolderInput = SHBrowseForFolder(&biInput);
	
	if (pidlFolderInput == NULL) return;

	TCHAR szPathInput[_MAX_PATH] = {0};
	SHGetPathFromIDList(pidlFolderInput, szPathInput);

	CString strFind = szPathInput;
	strFind += "\\*";
	CString strFile;

	CFileFind finder;	
	BOOL bFind ( TRUE );

	if ( !finder.FindFile( strFind ) )
	{
		bFind = FALSE;
	}

	int nCntSuccess = 0;
	CString strTemp;

	while( bFind )
	{
		bFind = finder.FindNextFile();
		strFile = finder.GetFileName();

		std::string strFileName = strFile.GetString();
		std::string::size_type idx = strFileName.find( ".bin" );

		if ( idx != std::string::npos )
		{
			CString strTempFile = strFileName.c_str();
			CString strBinName;
			int nIndex = strTempFile.ReverseFind ( '.' );
			strBinName = strTempFile.Left(nIndex) + ".x";
			m_pVcfCode.m_vecANIFILE.push_back ( strBinName.GetString() );
			nCntSuccess++;
		}
	}
	InitAniList();

	CString strTempMessage;
	strTempMessage.Format("Added:%d Animation File",nCntSuccess);
	MessageBox(strTempMessage,"JDev",MB_OK);
}

