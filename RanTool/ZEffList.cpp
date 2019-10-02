// ZEffList.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "ZEffList.h"
#include "ZEffTab.h"
#include "StringUtils.h"
#include "EtcFunction.h"
#include ".\zefflist.h"
#include "DummyData.h"


// AEffList dialog

IMPLEMENT_DYNAMIC(AEffList, CPropertyPage)
AEffList::AEffList(LOGFONT logfont)
	: CPropertyPage(AEffList::IDD)
	,m_pFont( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	bAddEffect = false;
}

AEffList::~AEffList()
{
}

void AEffList::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_EFFECT, m_cEffectType);
	DDX_Control(pDX, IDC_LIST_EFFECT, m_list_effect );
}


BEGIN_MESSAGE_MAP(AEffList, CPropertyPage)
	ON_BN_CLICKED(IDC_EFF_ADD, OnBnClickedEffAdd)
	ON_BN_CLICKED(IDC_EFF_EDIT, OnBnClickedEffEdit)
	ON_BN_CLICKED(IDC_EFF_DEL, OnBnClickedEffDel)
	ON_BN_CLICKED(IDC_EFF_CLEAR, OnBnClickedEffClear)
	ON_BN_CLICKED(IDC_EFF_COPY, OnBnClickedEffCopy)
	ON_BN_CLICKED(IDC_EFF_SELECT, OnBnClickedEffSelect)
	ON_BN_CLICKED(IDC_EFF_CANCEL, OnBnClickedEffCancel)
END_MESSAGE_MAP()


// AEffList message handlers
BOOL AEffList::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	for ( int i = 0; i < EFFANI_SIZE; ++i )
	{
		m_cEffectType.InsertString( i, DUMMYDATA::m_EffAniType[i].c_str() );
	}
	m_cEffectType.SetCurSel( 0 );

	SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}
void AEffList::SetEffectData( SANIMCONINFO::EFFANILIST	m_ListEFFECTX )
{
	m_ListEFFECT = m_ListEFFECTX;
	UpdateListEffect();
}

void AEffList::UpdateListEffect()
{
	CString strTemp;
	m_list_effect.ResetContent();

	SANIMCONINFO::EFFANILIST_ITER iter = m_ListEFFECT.begin();
	SANIMCONINFO::EFFANILIST_ITER iter_end = m_ListEFFECT.end();
	for ( int i=0 ; iter!=iter_end; ++iter , ++i)
	{
		strTemp.Format ("%d-Type:%d-Name:%s"
			,i
			,(*iter)->GetTypeID()
			,DUMMYDATA::m_EffAniType[(*iter)->GetTypeID()].c_str()
			);

		m_list_effect.InsertString(i, strTemp);
	}
}

void AEffList::OnBnClickedEffAdd()
{
	SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_SHOW );
	bAddEffect = true;
}

void AEffList::OnBnClickedEffEdit()
{
	int nIndex = m_list_effect.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		DxEffAniData* pEffAni;

		SANIMCONINFO::EFFANILIST_ITER iter = m_ListEFFECT.begin();
		SANIMCONINFO::EFFANILIST_ITER iter_end = m_ListEFFECT.end();
		for ( int i=0 ; iter!=iter_end; ++iter , ++i)
		{
			if ( i == nIndex ) pEffAni = (*iter);
		}

		int nType = pEffAni->GetTypeID();
		switch ( nType )
		{
		case EFFANI_SINGLE:
			{
				m_pEffTab->ActiveEffSingle((DxEffAniData_Single*)pEffAni);
			}break;
		case EFFANI_GHOSTING:
			{
				m_pEffTab->ActiveEffGhosting((DxEffAniData_Ghosting*)pEffAni);
			}break;
		case EFFANI_TRACE:
			{
				m_pEffTab->ActiveEffTrace((DxEffAniData_Trace*)pEffAni);
			}break;
		case EFFANI_FACEOFF:
			{
				m_pEffTab->ActiveEffFaceOff((DxEffAniData_FaceOff*)pEffAni);
			}break;
		};

		nLastEdit = nIndex;
		bAddEffect = false;
		SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
	}
}

void AEffList::OnBnClickedEffDel()
{
	int nIndex = m_list_effect.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		if ( MessageBox ( "Are you sure you want to Delete?", "Question", MB_YESNO ) == IDYES )
		{
			SANIMCONINFO::EFFANILIST_ITER iter = m_ListEFFECT.begin();
			SANIMCONINFO::EFFANILIST_ITER iter_end = m_ListEFFECT.end();
			for ( int i=0 ; iter!=iter_end; ++iter , ++i)
			{
				if ( i == nIndex ) iter =  m_ListEFFECT.erase(iter);
			}

			UpdateListEffect();
		}
	}
}

void AEffList::OnBnClickedEffClear()
{
	if ( MessageBox ( "Are you sure you want to Delete All?", "Question", MB_YESNO ) == IDYES )
	{
		m_ListEFFECT.clear();
		UpdateListEffect();
	}
}

void AEffList::OnBnClickedEffCopy()
{
	int nIndex = m_list_effect.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		SANIMCONINFO::EFFANILIST_ITER iter = m_ListEFFECT.begin();
		SANIMCONINFO::EFFANILIST_ITER iter_end = m_ListEFFECT.end();
		for ( int i=0 ; iter!=iter_end; ++iter , ++i)
		{
			if ( i == nIndex ) m_ListEFFECT.push_back(*iter);
		}

		UpdateListEffect();
	}
}

void AEffList::OnBnClickedEffSelect()
{
	int nSelected = m_cEffectType.GetCurSel();
	switch ( nSelected )
	{
	case EFFANI_SINGLE:
		{
			DxEffAniData_Single* EffSingleNew =  new DxEffAniData_Single;
			m_pEffTab->ActiveEffSingle( EffSingleNew );
		}break;
	case EFFANI_GHOSTING:
		{
			DxEffAniData_Ghosting* EffGhostingNew = new DxEffAniData_Ghosting;
			m_pEffTab->ActiveEffGhosting( EffGhostingNew );
		}break;
	case EFFANI_TRACE:
		{
			DxEffAniData_Trace* EffTraceNew = new DxEffAniData_Trace;
			m_pEffTab->ActiveEffTrace( EffTraceNew );
		}break;
	case EFFANI_FACEOFF:
		{
			DxEffAniData_FaceOff* EffFaceOffNew = new DxEffAniData_FaceOff;
			m_pEffTab->ActiveEffFaceOff( EffFaceOffNew );
		}break;
	};
	bAddEffect = true;
}

void AEffList::OnBnClickedEffCancel()
{
	SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
	bAddEffect = false;
}

void AEffList::SetEffSingle( DxEffAniData_Single* EffSingleX )
{
	DxEffAniData* pEffAni = DxEffAniMan::GetInstance().CreateEffInstance ( EffSingleX->GetTypeID() );
	if ( pEffAni )
	{
		pEffAni->SetProperty ( EffSingleX->GetProperty() );

		if (! bAddEffect )
		{
			SANIMCONINFO::EFFANILIST_ITER iter = m_ListEFFECT.begin();
			SANIMCONINFO::EFFANILIST_ITER iter_end = m_ListEFFECT.end();
			for ( int i=0 ; iter!=iter_end; ++iter , ++i)
			{
				if ( i == nLastEdit ) iter =  m_ListEFFECT.erase(iter);
			}
		}

		m_ListEFFECT.push_back(pEffAni);
		UpdateListEffect();

		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}


void AEffList::SetEffGhosting( DxEffAniData_Ghosting* EffGhostingX )
{
	DxEffAniData* pEffAni = DxEffAniMan::GetInstance().CreateEffInstance ( EffGhostingX->GetTypeID() );
	if ( pEffAni )
	{
		pEffAni->SetProperty ( EffGhostingX->GetProperty() );

		if (! bAddEffect )
		{
			SANIMCONINFO::EFFANILIST_ITER iter = m_ListEFFECT.begin();
			SANIMCONINFO::EFFANILIST_ITER iter_end = m_ListEFFECT.end();
			for ( int i=0 ; iter!=iter_end; ++iter , ++i)
			{
				if ( i == nLastEdit ) iter =  m_ListEFFECT.erase(iter);
			}
		}

		m_ListEFFECT.push_back(pEffAni);
		UpdateListEffect();

		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}

void AEffList::SetEffTrace( DxEffAniData_Trace* EffTraceX )
{
	DxEffAniData* pEffAni = DxEffAniMan::GetInstance().CreateEffInstance ( EffTraceX->GetTypeID() );
	if ( pEffAni )
	{
		pEffAni->SetProperty ( EffTraceX->GetProperty() );

		if (! bAddEffect )
		{
			SANIMCONINFO::EFFANILIST_ITER iter = m_ListEFFECT.begin();
			SANIMCONINFO::EFFANILIST_ITER iter_end = m_ListEFFECT.end();
			for ( int i=0 ; iter!=iter_end; ++iter , ++i)
			{
				if ( i == nLastEdit ) iter =  m_ListEFFECT.erase(iter);
			}
		}

		m_ListEFFECT.push_back(pEffAni);
		UpdateListEffect();

		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}

void AEffList::SetEffFaceOff ( DxEffAniData_FaceOff* EffFaceOffX )
{
	DxEffAniData* pEffAni = DxEffAniMan::GetInstance().CreateEffInstance ( EffFaceOffX->GetTypeID() );
	if ( pEffAni )
	{
		pEffAni->SetProperty ( EffFaceOffX->GetProperty() );

		if (! bAddEffect )
		{
			SANIMCONINFO::EFFANILIST_ITER iter = m_ListEFFECT.begin();
			SANIMCONINFO::EFFANILIST_ITER iter_end = m_ListEFFECT.end();
			for ( int i=0 ; iter!=iter_end; ++iter , ++i)
			{
				if ( i == nLastEdit ) iter =  m_ListEFFECT.erase(iter);
			}
		}

		m_ListEFFECT.push_back(pEffAni);
		UpdateListEffect();

		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}