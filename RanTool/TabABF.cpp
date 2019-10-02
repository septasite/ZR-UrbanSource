// TabABF.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "TabABF.h"
#include "ToolTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"
#include "DxSkinAniMan.h"
#include ".\tababf.h"

// CTabABF dialog

IMPLEMENT_DYNAMIC(CTabABF, CPropertyPage)
CTabABF::CTabABF(LOGFONT logfont)
	: CPropertyPage(CTabABF::IDD)
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

CTabABF::~CTabABF()
{
}

void CTabABF::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ANI, m_list_Ani);
	DDX_Control(pDX, IDC_LIST_BONE, m_list_Bone);
}


BEGIN_MESSAGE_MAP(CTabABF, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_ADD, OnBnClickedButtonAnilistAdd)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_DELETE, OnBnClickedButtonAnilistDelete)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_ANI, OnNMDblclkListAni)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_EDIT, OnBnClickedButtonAnilistEdit)
	ON_BN_CLICKED(IDC_BUTTON_BONELIST_ADD, OnBnClickedButtonBonelistAdd)
	ON_BN_CLICKED(IDC_BUTTON_BONELIST_DEL, OnBnClickedButtonBonelistDel)
	ON_NOTIFY(NM_DBLCLK, IDC_LIST_BONE, OnNMDblclkListBone)
	ON_BN_CLICKED(IDC_BUTTON_BONELIST_EDIT, OnBnClickedButtonBonelistEdit)
	ON_BN_CLICKED(IDC_BUTTON_BONELIST_OK, OnBnClickedButtonBonelistOk)
	ON_BN_CLICKED(IDC_BUTTON_HEAD_ABF, OnBnClickedButtonHead)
	ON_BN_CLICKED(IDC_BUTTON_BODY_ABF, OnBnClickedButtonBody)
	ON_BN_CLICKED(IDC_BUTTON_PANT_ABF, OnBnClickedButtonPant)
	ON_BN_CLICKED(IDC_BUTTON_GLOVE_ABF, OnBnClickedButtonGlove)
	ON_BN_CLICKED(IDC_BUTTON_RHAND_ABF, OnBnClickedButtonRhand)
	ON_BN_CLICKED(IDC_BUTTON_LHAND_ABF, OnBnClickedButtonLhand)
	ON_BN_CLICKED(IDC_BUTTON_FOOT_ABF, OnBnClickedButtonFoot)
	ON_BN_CLICKED(IDC_BUTTON_HAIR_ABF, OnBnClickedButtonHair)
	ON_BN_CLICKED(IDC_BUTTON_ACC_ABF, OnBnClickedButtonAcc)
	ON_BN_CLICKED(IDC_BUTTON_VEHICLE_ABF, OnBnClickedButtonVehicle)
	ON_BN_CLICKED(IDC_BUTTON_WING_ABF, OnBnClickedButtonWing)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_SEARCH, OnBnClickedButtonAnilistSearch)
	ON_BN_CLICKED(IDC_BUTTON_ABF_LOAD, OnBnClickedButtonAbfLoad)
	ON_BN_CLICKED(IDC_BUTTON_ABF_SAVE, OnBnClickedButtonAbfSave)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_OK, OnBnClickedButtonAnilistOk)
	ON_BN_CLICKED(IDC_BUTTON_NECK_ABF, OnBnClickedButtonNeck)
	ON_BN_CLICKED(IDC_BUTTON_WRIST_ABF, OnBnClickedButtonWrist)
	ON_BN_CLICKED(IDC_BUTTON_RFINGER_ABF, OnBnClickedButtonRfinger)
	ON_BN_CLICKED(IDC_BUTTON_AURA_ABF, OnBnClickedButtonAura)
	ON_BN_CLICKED(IDC_BUTTON_BELT_ABF, OnBnClickedButtonBelt)
	ON_BN_CLICKED(IDC_BUTTON_EAR_ABF, OnBnClickedButtonEar)
	ON_BN_CLICKED(IDC_BUTTON_ACCE_ABF, OnBnClickedButtonAcce)
	ON_BN_CLICKED(IDC_BUTTON_CON_ABF, OnBnClickedButtonCon)
	ON_BN_CLICKED(IDC_BUTTON_LFINGER_ABF, OnBnClickedButtonLfinger)
	ON_BN_CLICKED(IDC_BUTTON_BONELIST_CAN, OnBnClickedButtonBonelistCan)
	ON_BN_CLICKED(IDC_BUTTON_ANILIST_FOLDER, OnBnClickedButtonAnilistFolder)
	ON_BN_CLICKED(IDC_BUTTON_CHF_NEW, OnBnClickedButtonChfNew)
	ON_BN_CLICKED(IDC_BUTTON_ABF_LOAD2, OnBnClickedButtonAbfLoad2)
END_MESSAGE_MAP()


// CTabABF message handlers
BOOL CTabABF::OnInitDialog()
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

		SetWin_ShowWindow ( this, IDC_BUTTON_ABF_SAVE, SW_HIDE );
	}
	return TRUE;  // return TRUE unless you set the focus to a control
}

void CTabABF::OnBnClickedButtonAbfLoad()
{
	CString szFilterInput = "ABF|*.abf|";
	CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
	dlgInput.m_ofn.lpstrInitialDir = DxSkinAniMan::GetInstance().GetPath();
	if ( dlgInput.DoModal() != IDOK ) return;

	Reset();
	BOOL bOK = m_pAbfCode.LoadFile( dlgInput.GetFileName() );
	if ( bOK )
	{
		SetWin_Text ( this, IDC_EDIT_FILENAME, dlgInput.GetFileName() );
		strFileName = dlgInput.GetFileName();
		UpdateData();
		m_bActive = TRUE;
		SetWin_ShowWindow ( this, IDC_BUTTON_ABF_SAVE, SW_SHOW );
		m_pToolTab->AddHistoryOpen( "ABF Editor",dlgInput.GetFileName().GetString() );
	}
	else
	{
		MessageBox ( "Failure to Load :(" );
		m_pToolTab->AddHistoryOpenFail( "ABF Editor",dlgInput.GetFileName().GetString() );
	}
}

void CTabABF::OnBnClickedButtonAbfLoad2()
{
	CString szFilterInput = "ABF|*.abf|";
	CFileDialog dlgInput(true,"*.*",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterInput,this);
	dlgInput.m_ofn.lpstrInitialDir = DxSkinAniMan::GetInstance().GetPath();
	if ( dlgInput.DoModal() != IDOK ) return;

	Reset();
	BOOL bOK = m_pAbfCode.LoadFile_PH( dlgInput.GetFileName() );
	if ( bOK )
	{
		SetWin_Text ( this, IDC_EDIT_FILENAME, dlgInput.GetFileName() );
		strFileName = dlgInput.GetFileName();
		UpdateData();
		m_bActive = TRUE;
		SetWin_ShowWindow ( this, IDC_BUTTON_ABF_SAVE, SW_SHOW );
		m_pToolTab->AddHistoryOpen( "ABF Editor(PH)",dlgInput.GetFileName().GetString() );
	}
	else
	{
		MessageBox ( "Failure to Load :(" );
		m_pToolTab->AddHistoryOpenFail( "ABF Editor(PH)",dlgInput.GetFileName().GetString() );
	}
}


void CTabABF::OnBnClickedButtonAbfSave()
{
	if ( SaveData () )
	{
		CString szFilter = "ABF File (*.abf)|*.abf|";
		CFileDialog dlg(FALSE,".abf",strFileName.GetString(),OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
		(CTabABF*)this);

		dlg.m_ofn.lpstrInitialDir = DxSkinPieceDataContainer::GetInstance().GetPath();
		if ( dlg.DoModal() == IDOK )
		{
			BOOL bOK = m_pAbfCode.SaveFile ( dlg.GetFileName() );
			if ( bOK )
			{
				MessageBox ( "Save Done :P" );
				SetWin_Text ( this, IDC_EDIT_FILENAME, dlg.GetFileName() );
				m_pToolTab->AddHistorySave( "ABF Editor",dlg.GetFileName().GetString() );
			}
			else
			{
				MessageBox ( "Failure to Save :(" );
				m_pToolTab->AddHistorySaveFail( "ABF Editor",dlg.GetFileName().GetString() );
			}
		}
	}
}

void CTabABF::OnBnClickedButtonChfNew()
{
	Reset();
	SetWin_ShowWindow ( this, IDC_BUTTON_ABF_SAVE, SW_SHOW );
	SetWin_Text ( this, IDC_EDIT_FILENAME, "" );
	m_bActive = TRUE;
}


BOOL CTabABF::UpdateData()
{
	SetWin_Text ( this, IDC_EDIT_BONE_FILE, m_pAbfCode.m_strSkeleton.c_str() );
	SetWin_Num_float ( this, IDC_EDIT_SCALE, m_pAbfCode.m_fScale );
	SetWin_Num_float ( this, IDC_EDIT_HEIGHT, m_pAbfCode.m_fHeight );
	SetWin_Num_float ( this, IDC_EDIT_RADIUS, m_pAbfCode.m_fRadius );
	SetWin_Num_float ( this, IDC_EDIT_MIN_X, m_pAbfCode.m_vMin.x );
	SetWin_Num_float ( this, IDC_EDIT_MIN_Y, m_pAbfCode.m_vMin.y );
	SetWin_Num_float ( this, IDC_EDIT_MIN_Z, m_pAbfCode.m_vMin.z );
	SetWin_Num_float ( this, IDC_EDIT_MAX_X, m_pAbfCode.m_vMax.x );
	SetWin_Num_float ( this, IDC_EDIT_MAX_Y, m_pAbfCode.m_vMax.y );
	SetWin_Num_float ( this, IDC_EDIT_MAX_Z, m_pAbfCode.m_vMax.z );

	SetWin_Text ( this, IDC_EDIT_HEAD_ABF, m_pAbfCode.m_strPIECE[0].c_str() );
	SetWin_Text ( this, IDC_EDIT_BODY_ABF, m_pAbfCode.m_strPIECE[1].c_str() );
	SetWin_Text ( this, IDC_EDIT_PANT_ABF, m_pAbfCode.m_strPIECE[2].c_str() );
	SetWin_Text ( this, IDC_EDIT_GLOVE_ABF, m_pAbfCode.m_strPIECE[3].c_str() );
	SetWin_Text ( this, IDC_EDIT_RHAND_ABF, m_pAbfCode.m_strPIECE[4].c_str() );
	SetWin_Text ( this, IDC_EDIT_LHAND_ABF, m_pAbfCode.m_strPIECE[5].c_str() );
	SetWin_Text ( this, IDC_EDIT_FOOT_ABF, m_pAbfCode.m_strPIECE[6].c_str() );
	SetWin_Text ( this, IDC_EDIT_HAIR_ABF, m_pAbfCode.m_strPIECE[7].c_str() );
	SetWin_Text ( this, IDC_EDIT_ACC_ABF, m_pAbfCode.m_strPIECE[8].c_str() );
	SetWin_Text ( this, IDC_EDIT_VEHICLE_ABF, m_pAbfCode.m_strPIECE[9].c_str() );
	SetWin_Text ( this, IDC_EDIT_NECK_ABF, m_pAbfCode.m_strPIECE[10].c_str() );
	SetWin_Text ( this, IDC_EDIT_WRIST_ABF, m_pAbfCode.m_strPIECE[11].c_str() );
	SetWin_Text ( this, IDC_EDIT_RFINGER_ABF, m_pAbfCode.m_strPIECE[12].c_str() );
	SetWin_Text ( this, IDC_EDIT_LFINGER_ABF, m_pAbfCode.m_strPIECE[13].c_str() );
	SetWin_Text ( this, IDC_EDIT_WING_ABF, m_pAbfCode.m_strPIECE[14].c_str() );
	SetWin_Text ( this, IDC_EDIT_AURA_ABF, m_pAbfCode.m_strPIECE[15].c_str() );
	SetWin_Text ( this, IDC_EDIT_BELT_ABF, m_pAbfCode.m_strPIECE[16].c_str() );
	SetWin_Text ( this, IDC_EDIT_EAR_ABF, m_pAbfCode.m_strPIECE[17].c_str() );
	SetWin_Text ( this, IDC_EDIT_ACCE_ABF, m_pAbfCode.m_strPIECE[18].c_str() );
	SetWin_Text ( this, IDC_EDIT_CON_ABF, m_pAbfCode.m_strPIECE[19].c_str() );


	InitAniList();
	InitBoneList();

	return TRUE;
}

BOOL CTabABF::SaveData()
{
	m_pAbfCode.m_strSkeleton = GetWin_Text ( this, IDC_EDIT_BONE_FILE ).GetString();
	m_pAbfCode.m_fScale = GetWin_Num_float ( this, IDC_EDIT_SCALE );
	m_pAbfCode.m_fHeight = GetWin_Num_float ( this, IDC_EDIT_HEIGHT );
	m_pAbfCode.m_fRadius = GetWin_Num_float ( this, IDC_EDIT_RADIUS );
	m_pAbfCode.m_vMin.x = GetWin_Num_float ( this, IDC_EDIT_MIN_X );
	m_pAbfCode.m_vMin.y = GetWin_Num_float ( this, IDC_EDIT_MIN_Y );
	m_pAbfCode.m_vMin.z = GetWin_Num_float ( this, IDC_EDIT_MIN_Z );
	m_pAbfCode.m_vMax.x = GetWin_Num_float ( this, IDC_EDIT_MAX_X );
	m_pAbfCode.m_vMax.y = GetWin_Num_float ( this, IDC_EDIT_MAX_Y );
	m_pAbfCode.m_vMax.z = GetWin_Num_float ( this, IDC_EDIT_MAX_Z );

	m_pAbfCode.m_strPIECE[0] = GetWin_Text ( this, IDC_EDIT_HEAD_ABF ).GetString();
	m_pAbfCode.m_strPIECE[1] = GetWin_Text ( this, IDC_EDIT_BODY_ABF ).GetString();
	m_pAbfCode.m_strPIECE[2] = GetWin_Text ( this, IDC_EDIT_PANT_ABF ).GetString();
	m_pAbfCode.m_strPIECE[3] = GetWin_Text ( this, IDC_EDIT_GLOVE_ABF ).GetString();
	m_pAbfCode.m_strPIECE[4] = GetWin_Text ( this, IDC_EDIT_RHAND_ABF ).GetString();
	m_pAbfCode.m_strPIECE[5] = GetWin_Text ( this, IDC_EDIT_LHAND_ABF ).GetString();
	m_pAbfCode.m_strPIECE[6] = GetWin_Text ( this, IDC_EDIT_FOOT_ABF ).GetString();
	m_pAbfCode.m_strPIECE[7] = GetWin_Text ( this, IDC_EDIT_HAIR_ABF ).GetString();
	m_pAbfCode.m_strPIECE[8] = GetWin_Text ( this, IDC_EDIT_ACC_ABF ).GetString();
	m_pAbfCode.m_strPIECE[9] = GetWin_Text ( this, IDC_EDIT_VEHICLE_ABF ).GetString();
	m_pAbfCode.m_strPIECE[10] = GetWin_Text ( this, IDC_EDIT_NECK_ABF ).GetString();
	m_pAbfCode.m_strPIECE[11] = GetWin_Text ( this, IDC_EDIT_WRIST_ABF ).GetString();
	m_pAbfCode.m_strPIECE[12] = GetWin_Text ( this, IDC_EDIT_RFINGER_ABF ).GetString();
	m_pAbfCode.m_strPIECE[13] = GetWin_Text ( this, IDC_EDIT_LFINGER_ABF ).GetString();
	m_pAbfCode.m_strPIECE[14] = GetWin_Text ( this, IDC_EDIT_WING_ABF ).GetString();
	m_pAbfCode.m_strPIECE[15] = GetWin_Text ( this, IDC_EDIT_AURA_ABF ).GetString();
	m_pAbfCode.m_strPIECE[16] = GetWin_Text ( this, IDC_EDIT_BELT_ABF ).GetString();
	m_pAbfCode.m_strPIECE[17] = GetWin_Text ( this, IDC_EDIT_EAR_ABF ).GetString();
	m_pAbfCode.m_strPIECE[18] = GetWin_Text ( this, IDC_EDIT_ACCE_ABF ).GetString();
	m_pAbfCode.m_strPIECE[19] = GetWin_Text ( this, IDC_EDIT_CON_ABF ).GetString();


	return TRUE;
}

void CTabABF::InitAniList()
{
	m_list_Ani.DeleteAllItems();

	int iAniSize = (int)m_pAbfCode.m_vecANIFILE.size();
	char szTempChar[256];

	for ( int i = 0; i < iAniSize; i++ )
	{
		sprintf( szTempChar, "%d", i );
		m_list_Ani.InsertItem( i, szTempChar );
		sprintf( szTempChar, "%s", m_pAbfCode.m_vecANIFILE[i].c_str() );
		m_list_Ani.SetItemText( i, 1, szTempChar );
	}

	SetWin_ShowWindow ( this, IDC_EDIT_ANILIST_NAME, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_OK, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_SEARCH, SW_HIDE );
}

void CTabABF::OnBnClickedButtonAnilistAdd()
{ 
	bADD = true;
	SetWin_ShowWindow ( this, IDC_EDIT_ANILIST_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_OK, SW_SHOW );	
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_SEARCH, SW_SHOW );
}

void CTabABF::OnBnClickedButtonAnilistDelete()
{
	int nSelect = m_list_Ani.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;
	m_pAbfCode.m_vecANIFILE.erase ( m_pAbfCode.m_vecANIFILE.begin()+nSelect );
	InitAniList();
}

void CTabABF::OnNMDblclkListAni(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	int nSelect = m_list_Ani.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	SetWin_Text ( this, IDC_EDIT_ANILIST_NAME, m_pAbfCode.m_vecANIFILE[nSelect].c_str() );
	bADD = false;
	SetWin_ShowWindow ( this, IDC_EDIT_ANILIST_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_OK, SW_SHOW );	
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_SEARCH, SW_SHOW );
}

void CTabABF::OnBnClickedButtonAnilistEdit()
{
	int nSelect = m_list_Ani.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	SetWin_Text ( this, IDC_EDIT_ANILIST_NAME, m_pAbfCode.m_vecANIFILE[nSelect].c_str());
	bADD = false;
	SetWin_ShowWindow ( this, IDC_EDIT_ANILIST_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_OK, SW_SHOW );	
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_SEARCH, SW_SHOW );
}

void CTabABF::OnBnClickedButtonAnilistSearch()
{
	CString szFilter = "Animation File (*.bin)|*.bin|";
	CFileDialog dlg(TRUE,".bin",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
		(CTabABF*)this);

	dlg.m_ofn.lpstrInitialDir = DxSkinAniMan::GetInstance().GetPath();
	if ( dlg.DoModal() == IDOK )
	{
		std::string strAniName = dlg.GetFileName().GetString();
		SetWin_Text ( this, IDC_EDIT_ANILIST_NAME, strAniName.c_str() );
	}
}

void CTabABF::OnBnClickedButtonAnilistOk()
{
	if ( !bADD )
	{
		int nSelect = m_list_Ani.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
		if( nSelect == -1 ) return;

		m_pAbfCode.m_vecANIFILE.erase ( m_pAbfCode.m_vecANIFILE.begin()+nSelect );	
	}

	CString strBinName = "";
	CString strFileName = "";
	strFileName = GetWin_Text ( this, IDC_EDIT_ANILIST_NAME ).GetString();
	int nIndex = strFileName.ReverseFind ( '.' );
	strBinName = strFileName.Left(nIndex) + ".x";
	m_pAbfCode.m_vecANIFILE.push_back ( strBinName.GetString() );

	InitAniList();
	SetWin_ShowWindow ( this, IDC_EDIT_ANILIST_NAME, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_OK, SW_HIDE );	
	SetWin_ShowWindow ( this, IDC_BUTTON_ANILIST_SEARCH, SW_HIDE );
}


void CTabABF::InitBoneList()
{
	m_list_Bone.DeleteAllItems();

	int iBoneSize = (int)m_pAbfCode.m_dwBONE;
	char szTempChar[256];

	for ( int i = 0; i < iBoneSize; i++ )
	{
		sprintf( szTempChar, "%d", i );
		m_list_Bone.InsertItem( i, szTempChar );
		sprintf( szTempChar, "%.2f%%", m_pAbfCode.m_fBONE1[i] );
		m_list_Bone.SetItemText( i, 1, szTempChar );
		sprintf( szTempChar, "%.2f%%", m_pAbfCode.m_fBONE2[i] );
		m_list_Bone.SetItemText( i, 2, szTempChar );
		sprintf( szTempChar, "%.2f%%", m_pAbfCode.m_fBONE3[i] );
		m_list_Bone.SetItemText( i, 3, szTempChar );
		sprintf( szTempChar, "%s", m_pAbfCode.m_strBONE[i].c_str() );
		m_list_Bone.SetItemText( i, 4, szTempChar );
	}

	SetWin_ShowWindow ( this, IDC_EDIT_BONE1, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE2, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE3, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE_NAME, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_OK, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_CAN, SW_HIDE );
}

void CTabABF::OnNMDblclkListBone(NMHDR *pNMHDR, LRESULT *pResult)
{
	*pResult = 0;

	SetWin_ShowWindow ( this, IDC_EDIT_BONE1, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE2, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE3, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_OK, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_CAN, SW_SHOW );

	int nSelect = m_list_Bone.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	SetWin_Num_float ( this, IDC_EDIT_BONE1, m_pAbfCode.m_fBONE1[nSelect] );
	SetWin_Num_float ( this, IDC_EDIT_BONE2, m_pAbfCode.m_fBONE2[nSelect] );
	SetWin_Num_float ( this, IDC_EDIT_BONE3, m_pAbfCode.m_fBONE3[nSelect] );
	SetWin_Text ( this, IDC_EDIT_BONE_NAME, m_pAbfCode.m_strBONE[nSelect].c_str() );
	bAddBone = false;
}

void CTabABF::OnBnClickedButtonBonelistAdd()
{
	SetWin_ShowWindow ( this, IDC_EDIT_BONE1, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE2, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE3, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_OK, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_CAN, SW_SHOW );
	bAddBone = true;
}

void CTabABF::OnBnClickedButtonBonelistDel()
{
	int nSelect = m_list_Bone.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	int iBoneSize = (int)m_pAbfCode.m_dwBONE;
	for ( int i = nSelect; i < iBoneSize; i++ )
	{
		m_pAbfCode.m_fBONE1[i] = m_pAbfCode.m_fBONE1[i+1];
		m_pAbfCode.m_fBONE2[i] = m_pAbfCode.m_fBONE2[i+1];
		m_pAbfCode.m_fBONE3[i] = m_pAbfCode.m_fBONE3[i+1];
		m_pAbfCode.m_strBONE[i] = m_pAbfCode.m_strBONE[i+1].c_str();
	}

	m_pAbfCode.m_dwBONE = m_pAbfCode.m_dwBONE - 1;
	InitBoneList();
}



void CTabABF::OnBnClickedButtonBonelistEdit()
{
	int nSelect = m_list_Bone.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;

	SetWin_ShowWindow ( this, IDC_EDIT_BONE1, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE2, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE3, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE_NAME, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_OK, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_CAN, SW_SHOW );

	SetWin_Num_float ( this, IDC_EDIT_BONE1, m_pAbfCode.m_fBONE1[nSelect] );
	SetWin_Num_float ( this, IDC_EDIT_BONE2, m_pAbfCode.m_fBONE2[nSelect] );
	SetWin_Num_float ( this, IDC_EDIT_BONE3, m_pAbfCode.m_fBONE3[nSelect] );
	SetWin_Text ( this, IDC_EDIT_BONE_NAME, m_pAbfCode.m_strBONE[nSelect].c_str() );

	bAddBone = false;
}

void CTabABF::OnBnClickedButtonBonelistOk()
{
	if (bAddBone)
	{
		DWORD dwSize(m_pAbfCode.m_dwBONE);
		m_pAbfCode.m_dwBONE = dwSize + 1;
		m_pAbfCode.m_fBONE1[dwSize] = GetWin_Num_float ( this, IDC_EDIT_BONE1 );
		m_pAbfCode.m_fBONE2[dwSize] = GetWin_Num_float ( this, IDC_EDIT_BONE2 );
		m_pAbfCode.m_fBONE3[dwSize] = GetWin_Num_float ( this, IDC_EDIT_BONE3 );
		m_pAbfCode.m_strBONE[dwSize] = GetWin_Text ( this, IDC_EDIT_BONE_NAME ).GetString();
	}
	else
	{
		int nSelect = m_list_Bone.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
		if( nSelect == -1 ) return;

		m_pAbfCode.m_fBONE1[nSelect] = GetWin_Num_float ( this, IDC_EDIT_BONE1 );
		m_pAbfCode.m_fBONE2[nSelect] = GetWin_Num_float ( this, IDC_EDIT_BONE2 );
		m_pAbfCode.m_fBONE3[nSelect] = GetWin_Num_float ( this, IDC_EDIT_BONE3 );
		m_pAbfCode.m_strBONE[nSelect] = GetWin_Text ( this, IDC_EDIT_BONE_NAME ).GetString();
	}
	InitBoneList();
}

void CTabABF::OnBnClickedButtonBonelistCan()
{
	SetWin_ShowWindow ( this, IDC_EDIT_BONE1, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE2, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE3, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EDIT_BONE_NAME, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_OK, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_BUTTON_BONELIST_CAN, SW_HIDE );
	SetWin_Num_float ( this, IDC_EDIT_BONE1, 0.0f );
	SetWin_Num_float ( this, IDC_EDIT_BONE2, 0.0f );
	SetWin_Num_float ( this, IDC_EDIT_BONE3, 0.0f );
	SetWin_Text ( this, IDC_EDIT_BONE_NAME, "" );
}

void CTabABF::LoadCpsfile ( int nID )
{
	CString szFilter = "Wearing File (*.cps; *.aps; *.vps)|*.cps; *.aps; *.vps|";
	CFileDialog dlg(TRUE,NULL,NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter,
		(CTabABF*)this);

	dlg.m_ofn.lpstrInitialDir = DxSkinPieceDataContainer::GetInstance().GetPath ();
	if ( dlg.DoModal() == IDOK )
	{
		SetWin_Text ( this, nID, dlg.GetFileName().GetString() );
	}
}

void CTabABF::OnBnClickedButtonHead(){		LoadCpsfile ( IDC_EDIT_HEAD_ABF );}
void CTabABF::OnBnClickedButtonBody(){		LoadCpsfile ( IDC_EDIT_BODY_ABF );}
void CTabABF::OnBnClickedButtonPant(){		LoadCpsfile ( IDC_EDIT_PANT_ABF );}
void CTabABF::OnBnClickedButtonGlove(){		LoadCpsfile ( IDC_EDIT_GLOVE_ABF );}
void CTabABF::OnBnClickedButtonRhand(){		LoadCpsfile ( IDC_EDIT_RHAND_ABF );}
void CTabABF::OnBnClickedButtonLhand(){		LoadCpsfile ( IDC_EDIT_LHAND_ABF );}
void CTabABF::OnBnClickedButtonFoot(){		LoadCpsfile ( IDC_EDIT_FOOT_ABF );}
void CTabABF::OnBnClickedButtonHair(){		LoadCpsfile ( IDC_EDIT_HAIR_ABF );}
void CTabABF::OnBnClickedButtonAcc(){		LoadCpsfile ( IDC_EDIT_ACC_ABF );}
void CTabABF::OnBnClickedButtonVehicle(){	LoadCpsfile ( IDC_EDIT_VEHICLE_ABF );}
void CTabABF::OnBnClickedButtonWing(){		LoadCpsfile ( IDC_EDIT_WING_ABF );}

void CTabABF::OnBnClickedButtonNeck(){		LoadCpsfile ( IDC_EDIT_NECK_ABF );}
void CTabABF::OnBnClickedButtonWrist(){		LoadCpsfile ( IDC_EDIT_WRIST_ABF );}
void CTabABF::OnBnClickedButtonRfinger(){	LoadCpsfile ( IDC_EDIT_RFINGER_ABF );}
void CTabABF::OnBnClickedButtonAura(){		LoadCpsfile ( IDC_EDIT_AURA_ABF );}
void CTabABF::OnBnClickedButtonBelt(){		LoadCpsfile ( IDC_EDIT_BELT_ABF );}
void CTabABF::OnBnClickedButtonEar(){		LoadCpsfile ( IDC_EDIT_EAR_ABF );}
void CTabABF::OnBnClickedButtonAcce(){		LoadCpsfile ( IDC_EDIT_ACCE_ABF );}
void CTabABF::OnBnClickedButtonCon(){		LoadCpsfile ( IDC_EDIT_CON_ABF );}
void CTabABF::OnBnClickedButtonLfinger(){	LoadCpsfile ( IDC_EDIT_LFINGER_ABF );}

void CTabABF::Reset()
{
	SetWin_Text ( this, IDC_EDIT_FILENAME, "" );
	m_pAbfCode.Reset();
	SetWin_ShowWindow ( this, IDC_BUTTON_ABF_SAVE, SW_HIDE );
	m_bActive = FALSE;
	UpdateData();
}




void CTabABF::OnBnClickedButtonAnilistFolder()
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
			m_pAbfCode.m_vecANIFILE.push_back ( strBinName.GetString() );
			nCntSuccess++;
		}
	}
	InitAniList();

	CString strTempMessage;
	strTempMessage.Format("Added:%d Animation File",nCntSuccess);
	MessageBox(strTempMessage,"JDev",MB_OK);
}


