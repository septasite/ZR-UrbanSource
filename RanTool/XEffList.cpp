// XEffList.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "XEffList.h"
#include "xEffTab.h"
#include ".\xefflist.h"
#include "StringUtils.h"
#include "EtcFunction.h"
#include "DummyData.h"


// CEffList dialog

IMPLEMENT_DYNAMIC(CEffList, CPropertyPage)
CEffList::CEffList(LOGFONT logfont)
	: CPropertyPage(CEffList::IDD)
	,m_pFont( NULL )
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
	bAddEffect = false;
}

CEffList::~CEffList()
{
}

void CEffList::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_COMBO_EFFECT, m_cEffectType);
	DDX_Control(pDX, IDC_LIST_EFFECT, m_list_effect );
}


BEGIN_MESSAGE_MAP(CEffList, CPropertyPage)
	ON_BN_CLICKED(IDC_EFF_ADD, OnBnClickedEffAdd)
	ON_BN_CLICKED(IDC_EFF_EDIT, OnBnClickedEffEdit)
	ON_BN_CLICKED(IDC_EFF_DEL, OnBnClickedEffDel)
	ON_BN_CLICKED(IDC_EFF_SELECT, OnBnClickedEffSelect)
	ON_BN_CLICKED(IDC_EFF_CANCEL, OnBnClickedEffCancel)
	ON_BN_CLICKED(IDC_EFF_CLEAR, OnBnClickedEffClear)
	ON_BN_CLICKED(IDC_EFF_COPY, OnBnClickedEffCopy)
END_MESSAGE_MAP()


// CEffList message handlers
BOOL CEffList::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	for ( int i = 0; i < EFFCHAR_SIZE; ++i )
	{
		m_cEffectType.InsertString( i, DUMMYDATA::m_EffCharType[i].c_str() );

	}
	m_cEffectType.SetCurSel( 0 );

	SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );

	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}

void CEffList::SetPieceData( GLEFFCHAR_VEC	m_vecEFFECTX )
{
	m_vecEFFECT = m_vecEFFECTX;
	UpdateListEffect();
}

void CEffList::SetEffSingle( DxEffCharSingle* EffSingleX )
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffSingleX->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffSingleX->GetProperty() );
		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();

		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}
void CEffList::SetEffBlur( DxEffCharBlur* EffBlurX )
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffBlurX->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffBlurX->GetProperty() );
		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();

		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}
void CEffList::SetEffCloneBlur( DxEffCharCloneBlur* EffCloneBlurX )
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffCloneBlurX->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffCloneBlurX->GetProperty() );
		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();

		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}
void CEffList::SetEffDust( DxEffCharDust* EffDustX )
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffDustX->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffDustX->GetProperty() );
		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();

		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}
void CEffList::SetEffShock( DxEffCharShock* EffShockX )
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffShockX->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffShockX->GetProperty() );
		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();
		
		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}
void CEffList::SetEffAttribute( DxEffCharAttribute* EffAttributeX )
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffAttributeX->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffAttributeX->GetProperty() );
		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();
		
		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}

void CEffList::SetEffArrow ( DxEffCharArrow* EffArrowX )
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffArrowX->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffArrowX->GetProperty() );
		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();
		
		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}

void CEffList::SetEffSpecular ( DxEffCharSpecular* EffSpecularX )
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffSpecularX->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffSpecularX->GetProperty() );
		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();
		
		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}

void CEffList::SetEffLevel ( DxEffCharLevel* EffLevelX ,int nSize )
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffLevelX->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffLevelX->GetProperty() );
		pEffChar->SetMaterials ( NULL, nSize , EffLevelX->GetMaterials() );

		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();
		
		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}

void CEffList::SetEffEmit ( DxEffCharEmit* EffEmitX )
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffEmitX->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffEmitX->GetProperty() );
		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();
		
		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}

void CEffList::SetEffAlpha ( DxEffCharAlpha* EffAlphaX )
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffAlphaX->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffAlphaX->GetProperty() );
		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();
		
		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}

void CEffList::SetEffNeon ( DxEffCharNeon* EffNeonX ,int nSize )
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffNeonX->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffNeonX->GetProperty() );
		pEffChar->SetMaterials ( NULL, nSize , EffNeonX->GetMaterials() );

		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();
		
		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}

void CEffList::SetEffMark ( DxEffCharMark* EffMarkX )
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffMarkX->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffMarkX->GetProperty() );
		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();
		
		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}

void CEffList::SetEffNoAlpha ( DxEffCharNoAlpha* EffNoAlphaX )
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffNoAlphaX->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffNoAlphaX->GetProperty() );
		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();
		
		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}

void CEffList::SetEffReflection2 ( DxEffCharReflection2* EffReflection2X ,int nSize)
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffReflection2X->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffReflection2X->GetProperty() );
		pEffChar->SetMaterials ( NULL, nSize , EffReflection2X->GetMaterials() );

		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();
		
		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}

void CEffList::SetEffAmbient ( DxEffCharAmbient* EffAmbientX )
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffAmbientX->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffAmbientX->GetProperty() );
		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();
		
		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}

void CEffList::SetEffDot3 ( DxEffCharDot3* EffDot3X )
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffDot3X->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffDot3X->GetProperty() );
		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();
		
		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}

void CEffList::SetEffMultiTex ( DxEffCharMultiTex* EffMultiTexX  ,int nSize)
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffMultiTexX->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffMultiTexX->GetProperty() );
		pEffChar->SetMaterials ( NULL, nSize , EffMultiTexX->GetMaterials() );

		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();
		
		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}

void CEffList::SetEffGhosting ( DxEffCharGhosting* EffGhostingX )
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffGhostingX->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffGhostingX->GetProperty() );
		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();
		
		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}

void CEffList::SetEffSpecular2 ( DxEffCharSpecular2* EffSpecular2X ,int nSize)
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffSpecular2X->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffSpecular2X->GetProperty() );
		pEffChar->SetMaterials ( NULL, nSize , EffSpecular2X->GetMaterials() );

		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();
		
		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}

void CEffList::SetEffToon ( DxEffCharToon* EffToonX )
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffToonX->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffToonX->GetProperty() );
		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();
		
		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}

void CEffList::SetEffTexDiff ( DxEffCharTexDiff* EffTexDiffX ,int nSize)
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffTexDiffX->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffTexDiffX->GetProperty() );
		pEffChar->SetMaterials ( NULL, nSize , EffTexDiffX->GetMaterials() );

		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();
		
		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}

void CEffList::SetEffParticle ( DxEffCharParticle* EffParticleX )
{
	DxEffCharParticle*	EffNew = new DxEffCharParticle;
	EffNew->SetProperty ( EffParticleX->GetProperty() );
	EffNew->ClearPositionVec();

	int nNum = EffParticleX->GetPoistionSize();
	for ( int i=0; i<nNum; i++ )
	{
		EffNew->InsertPoint(EffParticleX->GetSelectedVec(i) );
	}

	if ( EffNew->EditApplyResetData() )
	{
		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back( EffNew );
		UpdateListEffect();
	}
	else
	{
		MessageBox("Must have Particle Data Minimun of 2","Error",MB_OK);
	}

	if (bAddEffect )
	{
		SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
	}
}

void CEffList::SetEffBonePos ( DxEffCharBonePosEff* EffBonePosX )
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffBonePosX->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffBonePosX->GetProperty() );
		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();
		
		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}

void CEffList::SetEffBoneList ( DxEffCharBoneListEff* EffBoneListX )
{
	DxEffCharBoneListEff*	EffNew = new DxEffCharBoneListEff;
	EffNew->SetProperty ( EffBoneListX->GetProperty() );
	EffNew->ClearAllBone();

	int nNum = EffBoneListX->GetCustomBoneSize();
	for ( int i=0; i<nNum; i++ )
	{
		EffNew->InsertBoneTool(EffBoneListX->GetSelectedBoneData(i) );
	}

	if ( EffNew->EditApplyResetData() )
	{
		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back( EffNew );
		UpdateListEffect();

		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
	else
	{
		MessageBox("Must have BoneList Data Minimun of 2","Error",MB_OK);
		return;	
	}
}

void CEffList::SetEffUserColor ( DxEffCharUserColor* EffUserColorX ,int nSize)
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffUserColorX->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffUserColorX->GetProperty() );
		pEffChar->SetMaterials ( NULL, nSize , EffUserColorX->GetMaterials() );

		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();
		
		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}

void CEffList::SetEffNormal ( DxEffCharNormal* EffNormalX )
{
	DxEffChar* pEffChar = DxEffCharMan::GetInstance().CreateEffInstance ( EffNormalX->GetTypeID() );
	if ( pEffChar )
	{
		pEffChar->SetProperty ( EffNormalX->GetProperty() );
		if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
		m_vecEFFECT.push_back(pEffChar);
		UpdateListEffect();
		
		if (bAddEffect )
		{
			SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
			SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
		}
	}
}

void CEffList::SetEffLine2Bone ( DxEffCharLine2BoneEff* EffLine2BoneX )
{
	DxEffCharLine2BoneEff*	EffNew = new DxEffCharLine2BoneEff;
	EffNew->SetProperty ( EffLine2BoneX->GetProperty() );
	EffNew->ClearAllBoneLine();

	CString strTemp1,strTemp2;
	int nNum = EffLine2BoneX->GetLineSize();
	for ( int i=0; i<nNum; i++ )
	{
		strTemp1.Format("%s",EffLine2BoneX->GetLine2BoneInf()[EffLine2BoneX->GetLine2BoneLine()[i]->m_dwBONEID[0] ]->m_strName.c_str() );
		strTemp2.Format("%s",EffLine2BoneX->GetLine2BoneInf()[EffLine2BoneX->GetLine2BoneLine()[i]->m_dwBONEID[1] ]->m_strName.c_str() );

		EffNew->InsertLine(strTemp1.GetString(),strTemp2.GetString() );
	}

	if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
	m_vecEFFECT.push_back( EffNew );
	UpdateListEffect();

	if (bAddEffect )
	{
		SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
	}
}

void CEffList::SetEffAround ( DxCharAroundEff* EffAroundX )
{
	DxCharAroundEff*	EffNew = new DxCharAroundEff;
	EffNew->SetProperty ( EffAroundX->GetProperty() );
	EffNew->ClearAroundEffect();

	int nNum = EffAroundX->GetAroundEffectSize();
	for ( int i=0; i<nNum; i++ )
	{

		EffNew->InsertAroundEffectTool( EffAroundX->GetAroundEffect()[i] );
	}

	if (! bAddEffect )m_vecEFFECT.erase(m_vecEFFECT.begin()+nLastEdit );
	m_vecEFFECT.push_back( EffNew );
	UpdateListEffect();

	if (bAddEffect )
	{
		SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
	}
}


BOOL CEffList::UpdateListEffect()
{
	CString strTemp;
	m_list_effect.ResetContent();

	int nNum = (int) m_vecEFFECT.size();
	for ( int i = 0; i < nNum; i++ )
	{
		DxEffChar* pEffChar = m_vecEFFECT[i];

		strTemp.Format ("%d-Type:%d-Name:%s"
			,i
			,pEffChar->GetTypeID()
			,DUMMYDATA::m_EffCharType[pEffChar->GetTypeID()].c_str()
			);

		m_list_effect.InsertString(i, strTemp);
	}
	return TRUE;
}

void CEffList::OnBnClickedEffAdd()
{
	SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_SHOW );
	SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_SHOW );
	bAddEffect = true;
}

void CEffList::OnBnClickedEffEdit()
{
	int nIndex = m_list_effect.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		DxEffChar* pEffChar = m_vecEFFECT[nIndex];
		int nType = pEffChar->GetTypeID();
		switch ( nType )
		{
		case EFFCHAR_SINGLE:
			{
				m_pEffTab->ActiveEffSingle((DxEffCharSingle*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_BLUR:
			{
				m_pEffTab->ActiveEffBlur((DxEffCharBlur*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_CLONEBLUR:
			{
				m_pEffTab->ActiveEffCloneBlur((DxEffCharCloneBlur*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_DUST:
			{
				m_pEffTab->ActiveEffDust((DxEffCharDust*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_SHOCK:
			{
				m_pEffTab->ActiveEffShock((DxEffCharShock*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_ATTRIBUTE:
			{
				m_pEffTab->ActiveEffAttribute((DxEffCharAttribute*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_ARROW:
			{
				m_pEffTab->ActiveEffArrow((DxEffCharArrow*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_SPECULAR:
			{
				m_pEffTab->ActiveEffSpecular((DxEffCharSpecular*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_LEVEL:
			{
				m_pEffTab->ActiveEffLevel((DxEffCharLevel*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_EMIT:
			{
				m_pEffTab->ActiveEffEmit((DxEffCharEmit*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_ALPHA:
			{
				m_pEffTab->ActiveEffAlpha((DxEffCharAlpha*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_NEON:
			{
				m_pEffTab->ActiveEffNeon((DxEffCharNeon*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_MARK:
			{
				m_pEffTab->ActiveEffMark((DxEffCharMark*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_NOALPHA:
			{
				m_pEffTab->ActiveEffNoAlpha((DxEffCharNoAlpha*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_REFLECTION2:
			{
				m_pEffTab->ActiveEffReflection2((DxEffCharReflection2*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_AMBIENT:
			{
				m_pEffTab->ActiveEffAmbient((DxEffCharAmbient*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_DOT3:
			{
				m_pEffTab->ActiveEffDot3((DxEffCharDot3*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_MULTITEX:
			{
				m_pEffTab->ActiveEffMultiTex((DxEffCharMultiTex*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_GHOSTING:
			{
				m_pEffTab->ActiveEffGhosting((DxEffCharGhosting*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_SPECULAR2:
			{
				m_pEffTab->ActiveEffSpecular2((DxEffCharSpecular2*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_TOON:
			{
				m_pEffTab->ActiveEffToon((DxEffCharToon*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_TEXDIFF:
			{
				m_pEffTab->ActiveEffTexDiff((DxEffCharTexDiff*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_PARTICLE:
			{
				m_pEffTab->ActiveEffParticle((DxEffCharParticle*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_BONEPOSEFF:
			{
				m_pEffTab->ActiveEffBonePos((DxEffCharBonePosEff*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_BONELISTEFF:
			{
				m_pEffTab->ActiveEffBoneList((DxEffCharBoneListEff*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_USERCOLOR:
			{
				m_pEffTab->ActiveEffUserColor((DxEffCharUserColor*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_NORMALMAP:
			{
				m_pEffTab->ActiveEffNormal((DxEffCharNormal*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_LINE2BONE:
			{
				m_pEffTab->ActiveEffLine2Bone((DxEffCharLine2BoneEff*)m_vecEFFECT[nIndex]);
			}break;
		case EFFCHAR_AROUNDEFFECT:
			{
				m_pEffTab->ActiveEffAround((DxCharAroundEff*)m_vecEFFECT[nIndex]);
			}break;
		};

		nLastEdit = nIndex;
		bAddEffect = false;
		SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
		SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
	}
}

void CEffList::OnBnClickedEffDel()
{
	int nIndex = m_list_effect.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		if ( MessageBox ( "Are you sure you want to Delete?", "Question", MB_YESNO ) == IDYES )
		{
			m_vecEFFECT.erase( m_vecEFFECT.begin()+nIndex );
			UpdateListEffect();
		}
	}
}

void CEffList::OnBnClickedEffSelect()
{
	int nSelected = m_cEffectType.GetCurSel();
	switch ( nSelected )
	{
	case EFFCHAR_SINGLE:
		{
			DxEffCharSingle* EffSingleNew = new DxEffCharSingle;
			m_pEffTab->ActiveEffSingle( EffSingleNew );
		}break;
	case EFFCHAR_BLUR:
		{
			DxEffCharBlur* EffBlurNew = new DxEffCharBlur;
			m_pEffTab->ActiveEffBlur( EffBlurNew );
		}break;
	case EFFCHAR_CLONEBLUR:
		{
			DxEffCharCloneBlur* EffCloneBlurNew = new DxEffCharCloneBlur;
			m_pEffTab->ActiveEffCloneBlur( EffCloneBlurNew );
		}break;
	case EFFCHAR_DUST:
		{
			DxEffCharDust* EffDustNew = new DxEffCharDust;
			m_pEffTab->ActiveEffDust( EffDustNew );
		}break;
	case EFFCHAR_SHOCK:
		{
			DxEffCharShock* EffShockNew = new DxEffCharShock;
			m_pEffTab->ActiveEffShock( EffShockNew );
		}break;
	case EFFCHAR_ATTRIBUTE:
		{
			DxEffCharAttribute* EffAttributeNew = new DxEffCharAttribute;
			m_pEffTab->ActiveEffAttribute( EffAttributeNew );
		}break;
	case EFFCHAR_ARROW:
		{
			DxEffCharArrow* EffArrowNew = new DxEffCharArrow;
			m_pEffTab->ActiveEffArrow( EffArrowNew );
		}break;
	case EFFCHAR_SPECULAR:
		{
			DxEffCharSpecular* EffSpecularNew = new DxEffCharSpecular;
			m_pEffTab->ActiveEffSpecular( EffSpecularNew );
		}break;
	case EFFCHAR_LEVEL:
		{
			DxEffCharLevel* EffLevelNew = new DxEffCharLevel;
			m_pEffTab->ActiveEffLevel( EffLevelNew );
		}break;
	case EFFCHAR_EMIT:
		{
			DxEffCharEmit* EffEmitNew = new DxEffCharEmit;
			m_pEffTab->ActiveEffEmit( EffEmitNew );
		}break;
	case EFFCHAR_ALPHA:
		{
			DxEffCharAlpha* EffAlphaNew = new DxEffCharAlpha;
			m_pEffTab->ActiveEffAlpha( EffAlphaNew );
		}break;
	case EFFCHAR_NEON:
		{
			DxEffCharNeon* EffNeonNew = new DxEffCharNeon;
			m_pEffTab->ActiveEffNeon( EffNeonNew );
		}break;
	case EFFCHAR_MARK:
		{
			DxEffCharMark* EffMarkNew = new DxEffCharMark;
			m_pEffTab->ActiveEffMark( EffMarkNew );
		}break;
	case EFFCHAR_NOALPHA:
		{
			DxEffCharNoAlpha* EffNoAlphaNew = new DxEffCharNoAlpha;
			m_pEffTab->ActiveEffNoAlpha( EffNoAlphaNew );
		}break;
	case EFFCHAR_REFLECTION2:
		{
			DxEffCharReflection2* EffReflection2New = new DxEffCharReflection2;
			m_pEffTab->ActiveEffReflection2( EffReflection2New );
		}break;
	case EFFCHAR_AMBIENT:
		{
			DxEffCharAmbient* EffAmbientNew = new DxEffCharAmbient;
			m_pEffTab->ActiveEffAmbient( EffAmbientNew );
		}break;
	case EFFCHAR_DOT3:
		{
			DxEffCharDot3* EffDot3New = new DxEffCharDot3;
			m_pEffTab->ActiveEffDot3( EffDot3New );
		}break;
	case EFFCHAR_MULTITEX:
		{
			DxEffCharMultiTex* EffMultiTexNew = new DxEffCharMultiTex;
			m_pEffTab->ActiveEffMultiTex( EffMultiTexNew );
		}break;
	case EFFCHAR_GHOSTING:
		{
			DxEffCharGhosting* EffGhostingNew = new DxEffCharGhosting;
			m_pEffTab->ActiveEffGhosting( EffGhostingNew );
		}break;
	case EFFCHAR_SPECULAR2:
		{
			DxEffCharSpecular2* EffSpecular2New = new DxEffCharSpecular2;
			m_pEffTab->ActiveEffSpecular2( EffSpecular2New );
		}break;
	case EFFCHAR_TOON:
		{
			DxEffCharToon* EffToonNew = new DxEffCharToon;
			m_pEffTab->ActiveEffToon( EffToonNew );
		}break;
	case EFFCHAR_TEXDIFF:
		{
			DxEffCharTexDiff* EffTexDiffNew = new DxEffCharTexDiff;
			m_pEffTab->ActiveEffTexDiff( EffTexDiffNew );
		}break;
	case EFFCHAR_PARTICLE:
		{
			DxEffCharParticle* EffParticleNew = new DxEffCharParticle;
			m_pEffTab->ActiveEffParticle( EffParticleNew );
		}break;
	case EFFCHAR_BONEPOSEFF:
		{
			DxEffCharBonePosEff* EffBonePosNew = new DxEffCharBonePosEff;
			m_pEffTab->ActiveEffBonePos( EffBonePosNew );
		}break;
	case EFFCHAR_BONELISTEFF:
		{
			DxEffCharBoneListEff* EffBoneListNew = new DxEffCharBoneListEff;
			m_pEffTab->ActiveEffBoneList( EffBoneListNew );
		}break;
	case EFFCHAR_USERCOLOR:
		{
			DxEffCharUserColor* EffUserColorNew = new DxEffCharUserColor;
			m_pEffTab->ActiveEffUserColor( EffUserColorNew );
		}break;
	case EFFCHAR_NORMALMAP:
		{
			DxEffCharNormal* EffNormalNew = new DxEffCharNormal;
			m_pEffTab->ActiveEffNormal( EffNormalNew );
		}break;
	case EFFCHAR_LINE2BONE:
		{
			DxEffCharLine2BoneEff* EffLine2BoneNew = new DxEffCharLine2BoneEff;
			m_pEffTab->ActiveEffLine2Bone( EffLine2BoneNew );
		}break;
	case EFFCHAR_AROUNDEFFECT:
		{
			DxCharAroundEff* EffAroundNew = new DxCharAroundEff;
			m_pEffTab->ActiveEffAround( EffAroundNew );
		}break;
	};
	bAddEffect = true;
}

void CEffList::OnBnClickedEffCancel()
{
	SetWin_ShowWindow ( this, IDC_COMBO_EFFECT, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EFF_SELECT, SW_HIDE );
	SetWin_ShowWindow ( this, IDC_EFF_CANCEL, SW_HIDE );
	bAddEffect = false;
}

void CEffList::OnBnClickedEffClear()
{
	if ( MessageBox ( "Are you sure you want to Delete All?", "Question", MB_YESNO ) == IDYES )
	{
		m_vecEFFECT.clear();
		UpdateListEffect();
	}
}

void CEffList::OnBnClickedEffCopy()
{
	int nIndex = m_list_effect.GetCurSel();
	if ( nIndex != LB_ERR )
	{
		m_vecEFFECT.push_back(m_vecEFFECT[nIndex]);
		UpdateListEffect();
	}
}
