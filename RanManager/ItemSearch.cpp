// ItemSearch.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "ItemSearch.h"
#include "EtcFunction.h"
#include "GLDefine.h"

#include ".\itemsearch.h"
#include "RanManagerComments.h"



// CItemSearch dialog

IMPLEMENT_DYNAMIC(CItemSearch, CDialog)
CItemSearch::CItemSearch(CWnd* pParent /*=NULL*/)
	: CDialog(CItemSearch::IDD, pParent),
	bMultiple(false)
{
	m_VecSearchResult.clear();
	nFilter = 0;
}

CItemSearch::~CItemSearch()
{
}

void CItemSearch::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_LIST_ITEM, m_list_Item );
	DDX_Control(pDX, IDC_COMBO_SEARCH_TYPE, m_cSearchType1 );
	DDX_Control(pDX, IDC_COMBO_SEARCH_ITEM_TYPE, m_cItemType1 );
	DDX_Control(pDX, IDC_COMBO_SEARCH_SUIT_TYPE, m_cSuitType1 );
	DDX_Control(pDX, IDC_COMBO_SEARCH_ARMS_TYPE, m_cArmsType1 );
	DDX_Control(pDX, IDC_COMBO_SEARCH_ITEM_LEVEL, m_cItemLevel1 );

	DDX_Control(pDX, IDC_COMBO_SEARCH_TYPE2, m_cSearchType2 );
	DDX_Control(pDX, IDC_COMBO_SEARCH_ITEM_TYPE2, m_cItemType2 );
	DDX_Control(pDX, IDC_COMBO_SEARCH_SUIT_TYPE2, m_cSuitType2 );
	DDX_Control(pDX, IDC_COMBO_SEARCH_ARMS_TYPE2, m_cArmsType2 );
	DDX_Control(pDX, IDC_COMBO_SEARCH_ITEM_LEVEL2, m_cItemLevel2 );
}


BEGIN_MESSAGE_MAP(CItemSearch, CDialog)
	ON_BN_CLICKED(IDC_BUTTON_OK, OnBnClickedButtonOk)
	ON_BN_CLICKED(IDC_BUTTON_CANCEL, OnBnClickedButtonCancel)
	ON_BN_CLICKED(IDC_BUTTON_ITEM_SEARCH, OnBnClickedButtonItemSearch)
	ON_CBN_SELCHANGE(IDC_COMBO_SEARCH_TYPE, OnCbnSelchangeComboSearchType)
	ON_CBN_SELCHANGE(IDC_COMBO_SEARCH_TYPE2, OnCbnSelchangeComboSearchType2)
	ON_BN_CLICKED(IDC_BUTTON_SHOWALL, OnBnClickedButtonShowall)
END_MESSAGE_MAP()


// CItemSearch message handlers
BOOL CItemSearch::OnInitDialog()
{
	CDialog::OnInitDialog();

	RECT rectCtrl;
	LONG lnWidth;
	LV_COLUMN lvColumn;

	if (bMultiple)	m_list_Item.SetExtendedStyle ( m_list_Item.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES | LVS_EX_CHECKBOXES);
	else	m_list_Item.SetExtendedStyle ( m_list_Item.GetExtendedStyle() | LVS_EX_FULLROWSELECT | LVS_EX_GRIDLINES );
	
	m_list_Item.GetClientRect ( &rectCtrl );
	lnWidth = rectCtrl.right - rectCtrl.left;

	const int nColumnCount = 5;	
	char* szColumnName1[nColumnCount] = { "Num","MID", "SID" , "Item Name", "Item Description"};
	int nColumnWidthPercent[nColumnCount] = { 10, 5,5,35,45 };

	for ( int i = 0; i < nColumnCount; i++ )
	{		
		lvColumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
		lvColumn.fmt = LVCFMT_LEFT;
		lvColumn.pszText = szColumnName1[i];
		lvColumn.iSubItem = i;
		lvColumn.cx = ( lnWidth*nColumnWidthPercent[i] ) / 100;
		m_list_Item.InsertColumn (i, &lvColumn );
	}


	for ( int i = 0; i < SEARCH_ITEMSIZE; ++i )
	{
		m_cSearchType1.InsertString( i, RMComments::m_SearchItemType[i].c_str() );
		m_cSearchType2.InsertString( i, RMComments::m_SearchItemType[i].c_str() );
	}
	
	for ( int i = 0; i < ITEM_NSIZE; ++i )
	{
		m_cItemType1.InsertString( i, COMMENT::ITEMTYPE[i].c_str() );
		m_cItemType2.InsertString( i, COMMENT::ITEMTYPE[i].c_str() );
	}
	
	for ( int i = 0; i < SUIT_NSIZE; ++i )
	{
		m_cSuitType1.InsertString( i, COMMENT::ITEMSUIT[i].c_str() );
		m_cSuitType2.InsertString( i, COMMENT::ITEMSUIT[i].c_str() );
	}
	
	for ( int i = 0; i < ITEMATT_NSIZE; ++i )
	{
		m_cArmsType1.InsertString( i, COMMENT::ITEMATTACK[i].c_str() );
		m_cArmsType2.InsertString( i, COMMENT::ITEMATTACK[i].c_str() );
	}
	
	for ( int i = 0; i < LEVEL_NSIZE; ++i )
	{
		m_cItemLevel1.InsertString( i, COMMENT::ITEMLEVEL[i].c_str() );
		m_cItemLevel2.InsertString( i, COMMENT::ITEMLEVEL[i].c_str() );
	}


	m_cSearchType1.SetCurSel( 0 );
	m_cItemType1.SetCurSel( 0 );
	m_cSuitType1.SetCurSel( 0 );
	m_cArmsType1.SetCurSel( 0 );
	m_cItemLevel1.SetCurSel( 0 );

	m_cSearchType2.SetCurSel( 0 );
	m_cItemType2.SetCurSel( 0 );
	m_cSuitType2.SetCurSel( 0 );
	m_cArmsType2.SetCurSel( 0 );
	m_cItemLevel2.SetCurSel( 0 );

	InitFilterInfo();
	SearchItem();
	OnCbnSelchangeComboSearchType();
	OnCbnSelchangeComboSearchType2();

	return TRUE;  
}

void CItemSearch::SearchItem()
{
	m_list_Item.DeleteAllItems();
	int nNum = 0;
	char szTempChar[4096];
	for ( int MID = 0; MID < GLItemMan::MAX_MID; MID++ )
	{
		for ( int SID = 0; SID < GLItemMan::MAX_SID; SID++ )
		{        		
			SITEM* pItem = GLItemMan::GetInstance().GetItem ( MID, SID );

			if ( pItem )
			{	
				bool bFound = false;
				switch (nFilter)
				{
				case	SEARCH_FILTER_NONE:	bFound = true;	break;
				case	SEARCH_FILTER_POTS:	
					{
						if ( pItem->sBasicOp.emItemType == ITEM_CURE )	bFound = true;
					}break;
				case	SEARCH_FILTER_VEHICLE:	
					{
						if ( pItem->sBasicOp.emItemType == ITEM_VEHICLE )	bFound = true;
					}break;
				};

				if ( bFound )
				{
					sprintf( szTempChar, "%d", nNum );
					m_list_Item.InsertItem( nNum, szTempChar );

					sprintf( szTempChar, "%d", pItem->sBasicOp.sNativeID.wMainID );
					m_list_Item.SetItemText(nNum,1,szTempChar);

					sprintf( szTempChar, "%d", pItem->sBasicOp.sNativeID.wSubID );
					m_list_Item.SetItemText(nNum,2,szTempChar);

					sprintf( szTempChar, "%s", pItem->GetName() );
					m_list_Item.SetItemText(nNum,3,szTempChar);

					sprintf( szTempChar, "%s", pItem->GetComment() );
					m_list_Item.SetItemText(nNum,4,szTempChar);
					nNum++;
				}
			}
		}
	}
}

void CItemSearch::OnCbnSelchangeComboSearchType()
{
	SetWin_Enable(this,IDC_EDIT_SEARCH,FALSE);
	SetWin_Enable(this,IDC_COMBO_SEARCH_ITEM_TYPE,FALSE);
	SetWin_Enable(this,IDC_COMBO_SEARCH_SUIT_TYPE,FALSE);
	SetWin_Enable(this,IDC_COMBO_SEARCH_ARMS_TYPE,FALSE);
	SetWin_Enable(this,IDC_COMBO_SEARCH_ITEM_LEVEL,FALSE);
	SetWin_Enable(this,IDC_CHECK_FIGHTER_M,FALSE);
	SetWin_Enable(this,IDC_CHECK_FIGHTER_W,FALSE);
	SetWin_Enable(this,IDC_CHECK_ARMS_M,FALSE);
	SetWin_Enable(this,IDC_CHECK_ARMS_W,FALSE);
	SetWin_Enable(this,IDC_CHECK_ARCHER_M,FALSE);
	SetWin_Enable(this,IDC_CHECK_ARCHER_W,FALSE);
	SetWin_Enable(this,IDC_CHECK_SPIRIT_M,FALSE);
	SetWin_Enable(this,IDC_CHECK_SPIRIT_W,FALSE);
	SetWin_Enable(this,IDC_CHECK_EXTREME_M,FALSE);
	SetWin_Enable(this,IDC_CHECK_EXTREME_W,FALSE);
	SetWin_Enable(this,IDC_CHECK_SCIENCE_M,FALSE);
	SetWin_Enable(this,IDC_CHECK_SCIENCE_W,FALSE);
	SetWin_Enable(this,IDC_CHECK_ASSASIN_M,FALSE);
	SetWin_Enable(this,IDC_CHECK_ASSASIN_W,FALSE);
	SetWin_Enable(this,IDC_CHECK_TESTING_M,FALSE);
	SetWin_Enable(this,IDC_CHECK_TESTING_W,FALSE);

	int nSelect = m_cSearchType1.GetCurSel();
	switch (nSelect)
	{
	case SEARCH_NAME:
	case SEARCH_MID:
	case SEARCH_SID:		SetWin_Enable(this,IDC_EDIT_SEARCH,TRUE);	break;
	case SEARCH_ITEMTYPE:	SetWin_Enable(this,IDC_COMBO_SEARCH_ITEM_TYPE,TRUE);	break;
	case SEARCH_SUITTYPE:	SetWin_Enable(this,IDC_COMBO_SEARCH_SUIT_TYPE,TRUE);	break;
	case SEARCH_ARMSTYPE:	SetWin_Enable(this,IDC_COMBO_SEARCH_ARMS_TYPE,TRUE);	break;
	case SEARCH_ITEMLVL:	SetWin_Enable(this,IDC_COMBO_SEARCH_ITEM_LEVEL,TRUE);	break;
	case SEARCH_CLASSREQ:	
		{
			SetWin_Enable(this,IDC_CHECK_FIGHTER_M,TRUE);
			SetWin_Enable(this,IDC_CHECK_FIGHTER_W,TRUE);
			SetWin_Enable(this,IDC_CHECK_ARMS_M,TRUE);
			SetWin_Enable(this,IDC_CHECK_ARMS_W,TRUE);
			SetWin_Enable(this,IDC_CHECK_ARCHER_M,TRUE);
			SetWin_Enable(this,IDC_CHECK_ARCHER_W,TRUE);
			SetWin_Enable(this,IDC_CHECK_SPIRIT_M,TRUE);
			SetWin_Enable(this,IDC_CHECK_SPIRIT_W,TRUE);
			SetWin_Enable(this,IDC_CHECK_EXTREME_M,TRUE);
			SetWin_Enable(this,IDC_CHECK_EXTREME_W,TRUE);
			SetWin_Enable(this,IDC_CHECK_SCIENCE_M,TRUE);
			SetWin_Enable(this,IDC_CHECK_SCIENCE_W,TRUE);
			SetWin_Enable(this,IDC_CHECK_ASSASIN_M,TRUE);
			SetWin_Enable(this,IDC_CHECK_ASSASIN_W,TRUE);
			SetWin_Enable(this,IDC_CHECK_TESTING_M,TRUE);
			SetWin_Enable(this,IDC_CHECK_TESTING_W,TRUE);
		}break;
	};
}


void CItemSearch::OnCbnSelchangeComboSearchType2()
{
	SetWin_Enable(this,IDC_EDIT_SEARCH2,FALSE);
	SetWin_Enable(this,IDC_COMBO_SEARCH_ITEM_TYPE2,FALSE);
	SetWin_Enable(this,IDC_COMBO_SEARCH_SUIT_TYPE2,FALSE);
	SetWin_Enable(this,IDC_COMBO_SEARCH_ARMS_TYPE2,FALSE);
	SetWin_Enable(this,IDC_COMBO_SEARCH_ITEM_LEVEL2,FALSE);
	SetWin_Enable(this,IDC_CHECK_FIGHTER_M2,FALSE);
	SetWin_Enable(this,IDC_CHECK_FIGHTER_W2,FALSE);
	SetWin_Enable(this,IDC_CHECK_ARMS_M2,FALSE);
	SetWin_Enable(this,IDC_CHECK_ARMS_W2,FALSE);
	SetWin_Enable(this,IDC_CHECK_ARCHER_M2,FALSE);
	SetWin_Enable(this,IDC_CHECK_ARCHER_W2,FALSE);
	SetWin_Enable(this,IDC_CHECK_SPIRIT_M2,FALSE);
	SetWin_Enable(this,IDC_CHECK_SPIRIT_W2,FALSE);
	SetWin_Enable(this,IDC_CHECK_EXTREME_M2,FALSE);
	SetWin_Enable(this,IDC_CHECK_EXTREME_W2,FALSE);
	SetWin_Enable(this,IDC_CHECK_SCIENCE_M2,FALSE);
	SetWin_Enable(this,IDC_CHECK_SCIENCE_W2,FALSE);
	SetWin_Enable(this,IDC_CHECK_ASSASIN_M2,FALSE);
	SetWin_Enable(this,IDC_CHECK_ASSASIN_W2,FALSE);
	SetWin_Enable(this,IDC_CHECK_TESTING_M2,FALSE);
	SetWin_Enable(this,IDC_CHECK_TESTING_W2,FALSE);

	int nSelect = m_cSearchType2.GetCurSel();
	switch (nSelect)
	{
	case SEARCH_NAME:
	case SEARCH_MID:
	case SEARCH_SID:		SetWin_Enable(this,IDC_EDIT_SEARCH2,TRUE);	break;
	case SEARCH_ITEMTYPE:	SetWin_Enable(this,IDC_COMBO_SEARCH_ITEM_TYPE2,TRUE);	break;
	case SEARCH_SUITTYPE:	SetWin_Enable(this,IDC_COMBO_SEARCH_SUIT_TYPE2,TRUE);	break;
	case SEARCH_ARMSTYPE:	SetWin_Enable(this,IDC_COMBO_SEARCH_ARMS_TYPE2,TRUE);	break;
	case SEARCH_ITEMLVL:	SetWin_Enable(this,IDC_COMBO_SEARCH_ITEM_LEVEL2,TRUE);	break;
	case SEARCH_CLASSREQ:	
		{
			SetWin_Enable(this,IDC_CHECK_FIGHTER_M2,TRUE);
			SetWin_Enable(this,IDC_CHECK_FIGHTER_W2,TRUE);
			SetWin_Enable(this,IDC_CHECK_ARMS_M2,TRUE);
			SetWin_Enable(this,IDC_CHECK_ARMS_W2,TRUE);
			SetWin_Enable(this,IDC_CHECK_ARCHER_M2,TRUE);
			SetWin_Enable(this,IDC_CHECK_ARCHER_W2,TRUE);
			SetWin_Enable(this,IDC_CHECK_SPIRIT_M2,TRUE);
			SetWin_Enable(this,IDC_CHECK_SPIRIT_W2,TRUE);
			SetWin_Enable(this,IDC_CHECK_EXTREME_M2,TRUE);
			SetWin_Enable(this,IDC_CHECK_EXTREME_W2,TRUE);
			SetWin_Enable(this,IDC_CHECK_SCIENCE_M2,TRUE);
			SetWin_Enable(this,IDC_CHECK_SCIENCE_W2,TRUE);
			SetWin_Enable(this,IDC_CHECK_ASSASIN_M2,TRUE);
			SetWin_Enable(this,IDC_CHECK_ASSASIN_W2,TRUE);
			SetWin_Enable(this,IDC_CHECK_TESTING_M2,TRUE);
			SetWin_Enable(this,IDC_CHECK_TESTING_W2,TRUE);
		}break;
	};
}


void CItemSearch::OnBnClickedButtonItemSearch()
{
	SetFilter(SEARCH_FILTER_NONE);
	InitFilterInfo();
	m_VecSearch1.clear();
	m_VecSearch2.clear();
	
	if ( Search_1() && Search_2() )
	{
		int nNum = 0;
		char szTempChar[4096];
		m_list_Item.DeleteAllItems();

		VEC_ITEM_SEARCH_ITER2 iter = m_VecSearch2.begin();
		VEC_ITEM_SEARCH_ITER2 iter_end = m_VecSearch2.end();
		for ( ; iter!=iter_end; ++iter )
		{
			sprintf( szTempChar, "%d", nNum );
			m_list_Item.InsertItem( nNum, szTempChar );

			sprintf( szTempChar, "%d", (*iter)->sBasicOp.sNativeID.wMainID );
			m_list_Item.SetItemText(nNum,1,szTempChar);

			sprintf( szTempChar, "%d", (*iter)->sBasicOp.sNativeID.wSubID );
			m_list_Item.SetItemText(nNum,2,szTempChar);

			sprintf( szTempChar, "%s", (*iter)->GetName() );
			m_list_Item.SetItemText(nNum,3,szTempChar);

			sprintf( szTempChar, "%s", (*iter)->GetComment() );
			m_list_Item.SetItemText(nNum,4,szTempChar);

			nNum++;	
		}
	}
}

BOOL CItemSearch::Search_1()
{
	int nSearchType = m_cSearchType1.GetCurSel();
	std::string strSearchKey  = GetWin_Text(this,IDC_EDIT_SEARCH);
	int nID = GetWin_Num_int(this,IDC_EDIT_SEARCH);
	int nItemType = m_cItemType1.GetCurSel();
	int nSuitType = m_cSuitType1.GetCurSel();
	int nArmsType = m_cArmsType1.GetCurSel();
	int nItemLevel = m_cItemLevel1.GetCurSel();

	DWORD dwFlag = 0;
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_FIGHTER_M ),dwFlag, GLCC_FIGHTER_M );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_ARMS_M ),   dwFlag, GLCC_ARMS_M );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_ARCHER_W ), dwFlag, GLCC_ARCHER_W );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_SPIRIT_W ), dwFlag, GLCC_SPIRIT_W );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_FIGHTER_W ),dwFlag, GLCC_FIGHTER_W );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_ARMS_W ),   dwFlag, GLCC_ARMS_W );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_ARCHER_M ), dwFlag, GLCC_ARCHER_M );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_SPIRIT_M ), dwFlag, GLCC_SPIRIT_M );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_EXTREME_M ), dwFlag, GLCC_EXTREME_M );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_EXTREME_W ), dwFlag, GLCC_EXTREME_W );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_SCIENCE_M ), dwFlag, GLCC_SCIENCE_M ); 
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_SCIENCE_W ), dwFlag, GLCC_SCIENCE_W ); 
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_ASSASIN_M ), dwFlag, GLCC_ASSASSIN_M ); 
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_ASSASIN_W ), dwFlag, GLCC_ASSASSIN_W ); 



	for ( int MID = 0; MID < GLItemMan::MAX_MID; MID++ )
	{
		for ( int SID = 0; SID < GLItemMan::MAX_SID; SID++ )
		{        		
			SITEM* pItem = GLItemMan::GetInstance().GetItem ( MID, SID );

			if ( pItem )
			{	
				bool bFound = false;
				switch (nSearchType)
				{
				case SEARCH_NONE:	return TRUE;	break;
				case SEARCH_NAME:
					{
						std::string strItemName = pItem->GetName();
						unsigned found = strItemName.find(strSearchKey);
						if (found!=std::string::npos)	bFound = true;
					}break;
				case SEARCH_MID:	if ( pItem->sBasicOp.sNativeID.wMainID == nID )		bFound = true;	break;		
				case SEARCH_SID:	if ( pItem->sBasicOp.sNativeID.wSubID == nID )		bFound = true;	break;			
				case SEARCH_ITEMTYPE:	if ( pItem->sBasicOp.emItemType == nItemType )		bFound = true;		break;
				case SEARCH_SUITTYPE:	if ( pItem->sSuitOp.emSuit == nSuitType )		bFound = true;	break;
				case SEARCH_ARMSTYPE:	if ( pItem->sSuitOp.emAttack == nArmsType )		bFound = true;	break;
				case SEARCH_ITEMLVL:	if ( pItem->sBasicOp.emLevel == nItemLevel )		bFound = true;	break;
				case SEARCH_CLASSREQ:	if ( pItem->sBasicOp.dwReqCharClass == dwFlag )		bFound = true;	break;
				};

				if (bFound)	m_VecSearch1.push_back(pItem); 
			}
		}
	}
	return TRUE;
}

BOOL CItemSearch::Search_2()
{
	int nSearchType = m_cSearchType2.GetCurSel();
	std::string strSearchKey  = GetWin_Text(this,IDC_EDIT_SEARCH2);
	int nID = GetWin_Num_int(this,IDC_EDIT_SEARCH2);
	int nItemType = m_cItemType2.GetCurSel();
	int nSuitType = m_cSuitType2.GetCurSel();
	int nArmsType = m_cArmsType2.GetCurSel();
	int nItemLevel = m_cItemLevel2.GetCurSel();

	DWORD dwFlag = 0;
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_FIGHTER_M2 ),dwFlag, GLCC_FIGHTER_M );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_ARMS_M2 ),   dwFlag, GLCC_ARMS_M );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_ARCHER_W2 ), dwFlag, GLCC_ARCHER_W );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_SPIRIT_W2 ), dwFlag, GLCC_SPIRIT_W );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_FIGHTER_W2 ),dwFlag, GLCC_FIGHTER_W );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_ARMS_W2 ),   dwFlag, GLCC_ARMS_W );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_ARCHER_M2 ), dwFlag, GLCC_ARCHER_M );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_SPIRIT_M2 ), dwFlag, GLCC_SPIRIT_M );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_EXTREME_M2 ), dwFlag, GLCC_EXTREME_M );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_EXTREME_W2 ), dwFlag, GLCC_EXTREME_W );
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_SCIENCE_M2 ), dwFlag, GLCC_SCIENCE_M ); 
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_SCIENCE_W2 ), dwFlag, GLCC_SCIENCE_W ); 
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_ASSASIN_M2 ), dwFlag, GLCC_ASSASSIN_M ); 
	SetCheck_Flags ( GetWin_Check ( this, IDC_CHECK_ASSASIN_W2 ), dwFlag, GLCC_ASSASSIN_W ); 


	VEC_ITEM_SEARCH_ITER1 iter = m_VecSearch1.begin();
	VEC_ITEM_SEARCH_ITER1 iter_end = m_VecSearch1.end();
	for ( ; iter!=iter_end; ++iter )
	{
		SITEM* pItem = GLItemMan::GetInstance().GetItem ((*iter)->sBasicOp.sNativeID.wMainID, (*iter)->sBasicOp.sNativeID.wSubID );
		if ( pItem )
		{
			bool bFound = false;
			switch (nSearchType)
			{
			case SEARCH_NONE:	bFound = true;	break;
			case SEARCH_NAME:
				{
					std::string strItemName = pItem->GetName();
					unsigned found = strItemName.find(strSearchKey);
					if (found!=std::string::npos)	bFound = true;
				}break;
			case SEARCH_MID:	if ( pItem->sBasicOp.sNativeID.wMainID == nID )		bFound = true;	break;		
			case SEARCH_SID:	if ( pItem->sBasicOp.sNativeID.wSubID == nID )		bFound = true;	break;			
			case SEARCH_ITEMTYPE:	if ( pItem->sBasicOp.emItemType == nItemType )		bFound = true;		break;
			case SEARCH_SUITTYPE:	if ( pItem->sSuitOp.emSuit == nSuitType )		bFound = true;	break;
			case SEARCH_ARMSTYPE:	if ( pItem->sSuitOp.emAttack == nArmsType )		bFound = true;	break;
			case SEARCH_ITEMLVL:	if ( pItem->sBasicOp.emLevel == nItemLevel )		bFound = true;	break;
			case SEARCH_CLASSREQ:	if ( pItem->sBasicOp.dwReqCharClass == dwFlag )		bFound = true;	break;
			};

			if (bFound)	m_VecSearch2.push_back(pItem); 
		}
	}
	return TRUE;
}

void CItemSearch::OnBnClickedButtonOk()
{
	if (bMultiple)	
	{
		m_VecSearchResult.clear();
		int nItem = 0; 
		for(nItem =0 ; nItem <  m_list_Item.GetItemCount(); nItem++)
		{
			BOOL bChecked = m_list_Item.GetCheck(nItem);
			if( bChecked)
			{
				SNATIVEID	wTempID;
				wTempID.wMainID = atoi ( m_list_Item.GetItemText(nItem, 1).GetString() );
				wTempID.wSubID = atoi ( m_list_Item.GetItemText(nItem, 2).GetString() );
				m_VecSearchResult.push_back(wTempID);
			}
		}
	}
	else	
	{
		int nSelect = m_list_Item.GetNextItem(-1, LVNI_ALL | LVNI_SELECTED);
		if( nSelect == -1 ) return;
		sSelectedItem.wMainID = atoi ( m_list_Item.GetItemText(nSelect,1).GetString() );
		sSelectedItem.wSubID = atoi ( m_list_Item.GetItemText(nSelect,2).GetString() );
	}
	OnOK();
}

void CItemSearch::OnBnClickedButtonCancel()
{
	OnCancel();
}

void CItemSearch::InitFilterInfo()
{
	switch(nFilter)
	{
	case	SEARCH_FILTER_NONE:		SetWin_Text(this,IDC_EDIT_FILTER_INFO,RMComments::m_SearchFilterType[0].c_str() );	break;
	case	SEARCH_FILTER_POTS:		SetWin_Text(this,IDC_EDIT_FILTER_INFO,RMComments::m_SearchFilterType[1].c_str() );	break;
	};
}

void CItemSearch::OnBnClickedButtonShowall()
{
	m_list_Item.DeleteAllItems();
	int nNum = 0;
	char szTempChar[4096];
	for ( int MID = 0; MID < GLItemMan::MAX_MID; MID++ )
	{
		for ( int SID = 0; SID < GLItemMan::MAX_SID; SID++ )
		{        		
			SITEM* pItem = GLItemMan::GetInstance().GetItem ( MID, SID );

			if ( pItem )
			{	
				sprintf( szTempChar, "%d", nNum );
				m_list_Item.InsertItem( nNum, szTempChar );

				sprintf( szTempChar, "%d", pItem->sBasicOp.sNativeID.wMainID );
				m_list_Item.SetItemText(nNum,1,szTempChar);

				sprintf( szTempChar, "%d", pItem->sBasicOp.sNativeID.wSubID );
				m_list_Item.SetItemText(nNum,2,szTempChar);

				sprintf( szTempChar, "%s", pItem->GetName() );
				m_list_Item.SetItemText(nNum,3,szTempChar);

				sprintf( szTempChar, "%s", pItem->GetComment() );
				m_list_Item.SetItemText(nNum,4,szTempChar);
				nNum++;
			}
		}
	}
}
