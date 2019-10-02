#include "stdafx.h"

#include <algorithm>
#include "../Common/SerialFile.h"
#include "../G-Logic/GLogic.h"
#include "../DxCommon/DxViewPort.h"
#include "../DxCommon/RENDERPARAM.h"
#include "DxSkinMesh9.h"
#include "DxSkinMeshMan.h"
#include "../Common/StlFunctions.h"
#include "DxSkinEffResult.h"
#include "../DxEffect/char/DxEffChar.h"
#include "../DxCommon/EDITMESHS.h"
#include "./DxCommon/TextureManager.h"
#include "DxSkinPieceContainer.h"
#include "../DxEffect/char/DxEffCharLine2BoneEff.h"

#include "Crypt.h"

//#include "../RanClientLib/G-Logic/GLUpgradeColor.h" //add upgradecolor

#ifdef _DEBUG
#define new DEBUG_NEW
#endif



DxSkinPiece* DxSkinPieceContainer::GrindData ( int nSex,int nType,int nUpgradeLevel,LPDIRECT3DDEVICEQ pd3dDevice, const BOOL bThread )
{
	HRESULT hr;
	//GASSERT(szFile);

	DxSkinPiece* pSkinPiece = NULL;
	pSkinPiece = new DxSkinPiece;

	hr = pSkinPiece->GrindPiece( nSex, nType, nUpgradeLevel , pd3dDevice , bThread);
	if ( FAILED(hr) )
	{
		SAFE_DELETE(pSkinPiece);
		return NULL;
	}
	return pSkinPiece;
}

HRESULT DxSkinPiece::GrindPiece ( int nSex,int nType,int nUpgradeLevel,LPDIRECT3DDEVICEQ pd3dDevice, const BOOL bThread )
{
	bool bEnable = GLUpgradeColor::GetInstance().bEnable[nUpgradeLevel];

	if ( bEnable )
	{
		HRESULT hr;
		m_dwRef = 0;

		switch  ( nSex )
		{
		case 0:
			{
				hr = SetSkinMesh ( "s_w_hide_box.X", "b_w.X", pd3dDevice, bThread );
				if ( FAILED(hr) )	return hr;
				m_pmcMesh = m_pSkinMesh->FindMeshContainer ( "Box01[Mesh]" );
				if ( !m_pmcMesh )	return E_FAIL;
			}break;
		case 1:
			{
				hr = SetSkinMesh ( "hide_box.X", "b_m.X", pd3dDevice, bThread );
				if ( FAILED(hr) )	return hr;
				m_pmcMesh = m_pSkinMesh->FindMeshContainer ( "Box01[Mesh]" );
				if ( !m_pmcMesh )	return E_FAIL;
			}break;
		default:
			{
				CDebugSet::ToLogFile("Invalid Sex GrindPiece");
			}break;
		};

		m_dwMaterialNum = 1;
		if ( m_dwMaterialNum!=0 )
		{
			SAFE_DELETE_ARRAY(m_pMaterialPiece);

			m_pMaterialPiece = new SMATERIAL_PIECE[m_dwMaterialNum];
			for ( DWORD i=0; i<m_dwMaterialNum; ++i )
			{
				m_pMaterialPiece[i].GrindMaterial( pd3dDevice );
			}
		}

		m_emWeaponWhereBack = (EMPEACEZONEWEAPON) 0;
		//0 = PIECE_EFF_UPBODY
		//1 = PIECE_EFF_LOBODY
		//2 = PIECE_EFF_GLOVE
		//3 = PIECE_EFF_FOOT
		switch  ( nType )
		{
		case 0:	m_emType = PIECE_EFF_UPBODY;	break;
		case 1:	m_emType = PIECE_EFF_LOBODY;	break;
		case 2:	m_emType = PIECE_EFF_GLOVE;		break;
		case 3:	m_emType = PIECE_EFF_FOOT;		break;
		default:	CDebugSet::ToLogFile("Invalid Type GrindPiece");	break;
		};

		{
			DxEffCharLine2BoneEff* pEff = new DxEffCharLine2BoneEff;
			hr = pEff->NewGrind_A ( nType,nUpgradeLevel, pd3dDevice );
			if (FAILED(hr))
			{
				SAFE_DELETE(pEff);
			}

			m_vecEFFECT.push_back ( pEff );
		}
		{
			DxEffCharLine2BoneEff* pEff = new DxEffCharLine2BoneEff;
			hr = pEff->NewGrind_B ( nType,nUpgradeLevel, pd3dDevice );
			if (FAILED(hr))
			{
				SAFE_DELETE(pEff);
			}

			m_vecEFFECT.push_back ( pEff );
		}

		std::sort ( m_vecEFFECT.begin(), m_vecEFFECT.end(), DXEFFCHAR_OPER() );
		m_dwFlag = 1;
			
		if ( m_dwMaterialNum!=m_pmcMesh->GetNumMaterials() )
		{
			m_dwMaterialNum = m_pmcMesh->GetNumMaterials();

			SAFE_DELETE_ARRAY(m_pMaterialPiece);
			m_pMaterialPiece = new SMATERIAL_PIECE[m_dwMaterialNum];
		}

		m_dwVertexNUM = m_pmcMesh->m_dwVertexNUM;

		m_pSkinMesh->Load( m_szXFileName, pd3dDevice );
	}
	return S_OK;
}


void SMATERIAL_PIECE::GrindMaterial ( LPDIRECT3DDEVICEQ pd3dDevice )
{
	m_dwFlags = 0;
	m_dwZBias = 0;
	m_strTexture = "";

	m_fZBias = (float)m_dwZBias*0.00001f;
	LoadTexture ( pd3dDevice );
}