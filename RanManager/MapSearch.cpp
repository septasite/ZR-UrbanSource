// MapSearch.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "MapSearch.h"
#include ".\mapsearch.h"
#include "EtcFunction.h"
#include "RanManagerComments.h"

// CMapSearch dialog
GLMapList CMapSearch::m_sMapList;

IMPLEMENT_DYNAMIC(CMapSearch, CDialog)
CMapSearch::CMapSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CMapSearch::IDD, pParent)
{
	nSelectMID = 65535;
	nSelectSID = 65535;
}

CMapSearch::~CMapSearch()
{
}

void CMapSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_MAP, m_list_Map );
	DDX_Control(pDX, IDC_COMBO_SEARCH_TYPE, m_cSearchType );
}


BEGIN_MESSAGE_MAP(CMapSearch, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_MAPSEARCH, OnBnClickedButtonMapsearch)
	ON_CBN_SELCHANGE(IDC_COMBO_SEARCH_TYPE, OnCbnSelchangeComboSearchType)
END_MESSAGE_MAP()


// CMapSearch message handlers
BOOL CMapSearch::OnInitDialog()
{
	CDialog::OnInitDialog();

	RECT rectCtrl;
	LONG lnWidth;
	LV_COLUMN lvColumn;

	m_list_Map.SetExtendedStyle ( m_list_Map.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	m_list_Map.GetClientRect ( &rectCtrl );
	lnWidth = rectCtrl.right - rectCtrl.left;

	const int nColumnCount = 20;	
	char* szColumnName1[nColumnCount] = { "Num","MID", "SID" , "Field", "Name", "Battle","Peace","Comm","PKZone","FreePK","ItemDrop","Move","Restart","Pet","DecExp","Vehicle","Club","CDM","AllRed","Instant"};
	int nColumnWidthPercent[nColumnCount] = { 4,4,4,4,13,5,5,5,5,5,6,5,5,5,5,4,4,4,4,4 };

	for ( int i = 0; i < nColumnCount; i++ )
	{		
		lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvColumn.fmt = LVCFMT_LEFT;
		lvColumn.pszText = szColumnName1[i];
		lvColumn.iSubItem = i;
		lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
		m_list_Map.InsertColumn (i, &lvColumn );
	}

	for ( int i = 0; i < SEARCH_MAP_SIZE; ++i )
	{
		m_cSearchType.InsertString( i, RMComments::m_SearchMapType[i].c_str() );
	}
	
	m_cSearchType.SetCurSel( 0 );

	m_sMapList.LoadMapList ( "mapslist.ini" );
	LoadMap();

	return TRUE;  // return TRUE unless you set the focus to a control	
}

void CMapSearch::LoadMap()
{
	GLMapList::FIELDMAP_ITER iter = m_sMapList.GetMapList().begin();
	GLMapList::FIELDMAP_ITER iter_end = m_sMapList.GetMapList().end();
	int nNum = 0;
	char szTempChar[256];
	m_list_Map.DeleteAllItems();
	for ( ; iter!=iter_end; ++iter )
	{
		const SMAPNODE &sNODE = (*iter).second;

		sprintf( szTempChar, "%d", nNum );
		m_list_Map.InsertItem( nNum, szTempChar );
		sprintf( szTempChar, "%d", sNODE.sNativeID.wMainID );
		m_list_Map.SetItemText(nNum,1,szTempChar);
		sprintf( szTempChar, "%d",  sNODE.sNativeID.wSubID );
		m_list_Map.SetItemText(nNum,2,szTempChar);
		sprintf( szTempChar, "%d",  sNODE.dwFieldSID );
		m_list_Map.SetItemText(nNum,3,szTempChar);
		sprintf( szTempChar, "%s", sNODE.strMapName.c_str() );
		m_list_Map.SetItemText(nNum,4,szTempChar);

		if (sNODE.bBattleZone)	sprintf( szTempChar, "%s", "yes" );
		else	sprintf( szTempChar, "%s", "no" );
		m_list_Map.SetItemText(nNum,5,szTempChar);

		if (sNODE.bPeaceZone)	sprintf( szTempChar, "%s", "yes" );
		else	sprintf( szTempChar, "%s", "no" );
		m_list_Map.SetItemText(nNum,6,szTempChar);

		if (sNODE.bCommission)	sprintf( szTempChar, "%s", "yes" );
		else	sprintf( szTempChar, "%s", "no" );
		m_list_Map.SetItemText(nNum,7,szTempChar);

		if (sNODE.bPKZone)	sprintf( szTempChar, "%s", "yes" );
		else	sprintf( szTempChar, "%s", "no" );
		m_list_Map.SetItemText(nNum,8,szTempChar);

		if (sNODE.bFreePK)	sprintf( szTempChar, "%s", "yes" );
		else	sprintf( szTempChar, "%s", "no" );
		m_list_Map.SetItemText(nNum,9,szTempChar);

		if (sNODE.bItemDrop)	sprintf( szTempChar, "%s", "yes" );
		else	sprintf( szTempChar, "%s", "no" );
		m_list_Map.SetItemText(nNum,10,szTempChar);

		if (sNODE.bMove)	sprintf( szTempChar, "%s", "yes" );
		else	sprintf( szTempChar, "%s", "no" );
		m_list_Map.SetItemText(nNum,11,szTempChar);

		if (sNODE.bRestart)	sprintf( szTempChar, "%s", "yes" );
		else	sprintf( szTempChar, "%s", "no" );
		m_list_Map.SetItemText(nNum,12,szTempChar);

		if (sNODE.bPetActivity)	sprintf( szTempChar, "%s", "yes" );
		else	sprintf( szTempChar, "%s", "no" );
		m_list_Map.SetItemText(nNum,13,szTempChar);

		if (sNODE.bDECEXP)	sprintf( szTempChar, "%s", "yes" );
		else	sprintf( szTempChar, "%s", "no" );
		m_list_Map.SetItemText(nNum,14,szTempChar);

		if (sNODE.bVehicleActivity)	sprintf( szTempChar, "%s", "yes" );
		else	sprintf( szTempChar, "%s", "no" );
		m_list_Map.SetItemText(nNum,15,szTempChar);

		if (sNODE.bClubBattleZone)	sprintf( szTempChar, "%s", "yes" );
		else	sprintf( szTempChar, "%s", "no" );
		m_list_Map.SetItemText(nNum,16,szTempChar);

		if (sNODE.bCDMZone)	sprintf( szTempChar, "%s", "yes" );
		else	sprintf( szTempChar, "%s", "no" );
		m_list_Map.SetItemText(nNum,17,szTempChar);

		if (sNODE.bRedZone)	sprintf( szTempChar, "%s", "yes" );
		else	sprintf( szTempChar, "%s", "no" );
		m_list_Map.SetItemText(nNum,18,szTempChar);

		if (sNODE.bInstantMap)	sprintf( szTempChar, "%s", "yes" );
		else	sprintf( szTempChar, "%s", "no" );
		m_list_Map.SetItemText(nNum,19,szTempChar);

		nNum++;
	}
}

void CMapSearch::OnBnClickedButtonMapsearch()
{
	GLMapList::FIELDMAP_ITER iter = m_sMapList.GetMapList().begin();
	GLMapList::FIELDMAP_ITER iter_end = m_sMapList.GetMapList().end();
	int nNum = 0;
	char szTempChar[256];
	m_list_Map.DeleteAllItems();
	int nSelect = m_cSearchType.GetCurSel();
	int nVal = GetWin_Num_int(this,IDC_EDIT_SEARCH);
	std::string strSearch = GetWin_Text(this,IDC_EDIT_SEARCH);
	for ( ; iter!=iter_end; ++iter )
	{
		bool	bFind = false;
		const SMAPNODE &sNODE = (*iter).second;
		switch (nSelect)
		{
		case SEARCH_MAP_ALL:	bFind = true;	break;
		case SEARCH_MAP_MID:	if (sNODE.sNativeID.wMainID == nVal ) bFind = true;	break;
		case SEARCH_MAP_SID:	if (sNODE.sNativeID.wSubID == nVal ) bFind = true;	break;
		case SEARCH_MAP_FIELD:	if (sNODE.dwFieldSID == nVal ) bFind = true;	break;
		case SEARCH_MAP_NAME:	
			{
				std::string strMapName = sNODE.strMapName.c_str();
				unsigned found = strMapName.find(strSearch);
				if (found!=std::string::npos)	bFind = true;	break;
			}
		case SEARCH_MAP_BATTLEZONE:	if (sNODE.bBattleZone ) bFind = true;	break;
		case SEARCH_MAP_PEACEZONE:	if (sNODE.bPeaceZone ) bFind = true;	break;
		case SEARCH_MAP_COMMISSION:	if (sNODE.bCommission ) bFind = true;	break;
		case SEARCH_MAP_PKZONE:	if (sNODE.bPKZone ) bFind = true;	break;
		case SEARCH_MAP_FREEPK:	if (sNODE.bFreePK ) bFind = true;	break;
		case SEARCH_MAP_ITEMDROP:	if (sNODE.bItemDrop ) bFind = true;	break;
		case SEARCH_MAP_MOVE:	if (sNODE.bMove ) bFind = true;	break;
		case SEARCH_MAP_RESTART:	if (sNODE.bRestart ) bFind = true;	break;
		case SEARCH_MAP_PETACTIVITY:	if (sNODE.bPetActivity ) bFind = true;	break;
		case SEARCH_MAP_DECREASEEXP:	if (sNODE.bDECEXP ) bFind = true;	break;
		case SEARCH_MAP_VEHICLE:	if (sNODE.bVehicleActivity ) bFind = true;	break;
		case SEARCH_MAP_CLUBBATTLEZONE:	if (sNODE.bClubBattleZone ) bFind = true;	break;
		case SEARCH_MAP_CDM:	if (sNODE.bCDMZone ) bFind = true;	break;
		case SEARCH_MAP_REDZONE:	if (sNODE.bRedZone ) bFind = true;	break;
		case SEARCH_MAP_INSTANT:	if (sNODE.bInstantMap ) bFind = true;	break;

		};
		
		if (bFind)
		{
			sprintf( szTempChar, "%d", nNum );
			m_list_Map.InsertItem( nNum, szTempChar );
			sprintf( szTempChar, "%d", sNODE.sNativeID.wMainID );
			m_list_Map.SetItemText(nNum,1,szTempChar);
			sprintf( szTempChar, "%d",  sNODE.sNativeID.wSubID );
			m_list_Map.SetItemText(nNum,2,szTempChar);
			sprintf( szTempChar, "%d",  sNODE.dwFieldSID );
			m_list_Map.SetItemText(nNum,3,szTempChar);
			sprintf( szTempChar, "%s", sNODE.strMapName.c_str() );
			m_list_Map.SetItemText(nNum,4,szTempChar);

			if (sNODE.bBattleZone)	sprintf( szTempChar, "%s", "yes" );
			else	sprintf( szTempChar, "%s", "no" );
			m_list_Map.SetItemText(nNum,5,szTempChar);

			if (sNODE.bPeaceZone)	sprintf( szTempChar, "%s", "yes" );
			else	sprintf( szTempChar, "%s", "no" );
			m_list_Map.SetItemText(nNum,6,szTempChar);

			if (sNODE.bCommission)	sprintf( szTempChar, "%s", "yes" );
			else	sprintf( szTempChar, "%s", "no" );
			m_list_Map.SetItemText(nNum,7,szTempChar);

			if (sNODE.bPKZone)	sprintf( szTempChar, "%s", "yes" );
			else	sprintf( szTempChar, "%s", "no" );
			m_list_Map.SetItemText(nNum,8,szTempChar);

			if (sNODE.bFreePK)	sprintf( szTempChar, "%s", "yes" );
			else	sprintf( szTempChar, "%s", "no" );
			m_list_Map.SetItemText(nNum,9,szTempChar);

			if (sNODE.bItemDrop)	sprintf( szTempChar, "%s", "yes" );
			else	sprintf( szTempChar, "%s", "no" );
			m_list_Map.SetItemText(nNum,10,szTempChar);

			if (sNODE.bMove)	sprintf( szTempChar, "%s", "yes" );
			else	sprintf( szTempChar, "%s", "no" );
			m_list_Map.SetItemText(nNum,11,szTempChar);

			if (sNODE.bRestart)	sprintf( szTempChar, "%s", "yes" );
			else	sprintf( szTempChar, "%s", "no" );
			m_list_Map.SetItemText(nNum,12,szTempChar);

			if (sNODE.bPetActivity)	sprintf( szTempChar, "%s", "yes" );
			else	sprintf( szTempChar, "%s", "no" );
			m_list_Map.SetItemText(nNum,13,szTempChar);

			if (sNODE.bDECEXP)	sprintf( szTempChar, "%s", "yes" );
			else	sprintf( szTempChar, "%s", "no" );
			m_list_Map.SetItemText(nNum,14,szTempChar);

			if (sNODE.bVehicleActivity)	sprintf( szTempChar, "%s", "yes" );
			else	sprintf( szTempChar, "%s", "no" );
			m_list_Map.SetItemText(nNum,15,szTempChar);

			if (sNODE.bClubBattleZone)	sprintf( szTempChar, "%s", "yes" );
			else	sprintf( szTempChar, "%s", "no" );
			m_list_Map.SetItemText(nNum,16,szTempChar);

			if (sNODE.bCDMZone)	sprintf( szTempChar, "%s", "yes" );
			else	sprintf( szTempChar, "%s", "no" );
			m_list_Map.SetItemText(nNum,17,szTempChar);

			if (sNODE.bRedZone)	sprintf( szTempChar, "%s", "yes" );
			else	sprintf( szTempChar, "%s", "no" );
			m_list_Map.SetItemText(nNum,18,szTempChar);

			if (sNODE.bInstantMap)	sprintf( szTempChar, "%s", "yes" );
			else	sprintf( szTempChar, "%s", "no" );
			m_list_Map.SetItemText(nNum,19,szTempChar);

			nNum++;
		}
	}
}

void CMapSearch::OnBnClickedButtonCancel()
{
	OnCancel();
}

void CMapSearch::OnBnClickedButtonOk()
{
	int nSelect = m_list_Map.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
	if( nSelect == -1 ) return;
	nSelectMID = atoi ( m_list_Map.GetItemText(nSelect,1).GetString() ); 
	nSelectSID = atoi ( m_list_Map.GetItemText(nSelect,2).GetString() ); 
	OnOK();
}

void CMapSearch::OnCbnSelchangeComboSearchType()
{
	int nSelect = m_cSearchType.GetCurSel();
	switch (nSelect)
	{
	case SEARCH_MAP_ALL:
	case SEARCH_MAP_MID:
	case SEARCH_MAP_SID:
	case SEARCH_MAP_FIELD:
	case SEARCH_MAP_NAME:	SetWin_Enable(this,IDC_EDIT_SEARCH,TRUE);	break;
	case SEARCH_MAP_BATTLEZONE:
	case SEARCH_MAP_PEACEZONE:
	case SEARCH_MAP_COMMISSION:
	case SEARCH_MAP_PKZONE:
	case SEARCH_MAP_FREEPK:
	case SEARCH_MAP_ITEMDROP:
	case SEARCH_MAP_MOVE:
	case SEARCH_MAP_RESTART:
	case SEARCH_MAP_PETACTIVITY:
	case SEARCH_MAP_DECREASEEXP:
	case SEARCH_MAP_VEHICLE:
	case SEARCH_MAP_CLUBBATTLEZONE:
	case SEARCH_MAP_CDM:
	case SEARCH_MAP_REDZONE:
	case SEARCH_MAP_INSTANT:		SetWin_Enable(this,IDC_EDIT_SEARCH,FALSE);	break;
	};
}
