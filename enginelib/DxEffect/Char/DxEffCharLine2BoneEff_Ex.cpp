#include "stdafx.h"

#include <string>
//#include <strstream>

#include <algorithm>
#include "../Common/StlFunctions.h"
#include "../DxCommon/DxInputDevice.h"
#include "../../DxCommon/TextureManager.h"
#include "../Common/SerialFile.h"
#include "../DxCommon/DxDynamicVB.h"
#include "../G-Logic/GLDefine.h"
#include "../DxCommon/EDITMESHS.h"
#include "../DxCommon/DxViewPort.h"
#include "./DxEffCharLine2BoneEff.h"
#include "Crypt.h"
//#include "../RanClientLib/G-Logic/GLUpgradeColor.h" //add upgradecolor

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern BOOL			g_bOBJECT100;
extern std::string	g_strPICK_BONE;
extern BOOL			g_bCHAR_EDIT_RUN;
extern int			g_nITEMLEVEL;

HRESULT	DxEffCharLine2BoneEff::NewGrind_A ( int nType,int nGrind, LPDIRECT3DDEVICEQ pd3dDevice )
{
	if( g_bCHAR_EDIT_RUN )	nGrind = g_nITEMLEVEL;

	HRESULT hr;
	m_dwFlag = USE_SEQUENCE;
	m_dwOtherColor = 0;
	m_dwParticlePec = 7;
	m_dwColor = D3DCOLOR_ARGB(
		GLUpgradeColor::GetInstance().R_A[nGrind],
		GLUpgradeColor::GetInstance().R_R[nGrind],
		GLUpgradeColor::GetInstance().R_G[nGrind],
		GLUpgradeColor::GetInstance().R_B[nGrind]
		);

	m_dwColor2 = D3DCOLOR_ARGB(
		GLUpgradeColor::GetInstance().A_A[nGrind],
		GLUpgradeColor::GetInstance().A_R[nGrind],
		GLUpgradeColor::GetInstance().A_G[nGrind],
		GLUpgradeColor::GetInstance().A_B[nGrind]
		);

	m_dwSequenceCol = 3;
	m_dwSequenceRow = 3;
	m_fCreateLength = 0.0f;
	
	m_vLife.x = 0.5f;
	m_vLife.y = 0.5f;
	m_vSize.x = 1.0f;
	m_vSize.y = 1.0f;
	m_vSize.z = 1.0f;
	m_vScaleX.x = 1.0f;
	m_vScaleX.y = 2.0f;
	m_vScaleY.x = 3.0f;
	m_vScaleY.y = 1.0f;
	m_vScaleY.z = -0.5f;
	m_fShake = 0.0f;

	m_fMinMaxDist.min = -3.0f;
	m_fMinMaxDist.max = -1.0f;
	m_fMinMaxTexRotate.min = 0.3f;
	m_fMinMaxTexRotate.max = 0.5f;

	StringCchCopy( m_szTexture, BONELISTEFF_TEXNAME_SIZE, "lightning_new03.dds" );
	StringCchCopy( m_szTexture2, BONELISTEFF_TEXNAME_SIZE, "lightning_new02.dds" );

	switch ( nType ){
	case 0:{ //BODY
			const DWORD dwLines = 4;
			DWORD	dwNewBone1[dwLines] = {3,2,1,5};
			DWORD	dwNewBone2[dwLines] = {2,0,0,4};

			for( DWORD i=0; i<dwLines; ++i ){
				BONELINE* pNew = new BONELINE;
				pNew->m_dwBONEID[0] = dwNewBone1[i];
				pNew->m_dwBONEID[1] = dwNewBone2[i];
				m_vecBoneLINE.push_back( pNew );}

			const DWORD dwBones = 12;
			CString strBoneName [dwBones] =	{
				"Bip01_L_UpperArm",
				"Bip01_L_Forearm",
				"Bip01_R_UpperArm",
				"Bip01_R_Forearm",
				"Bip01_Neck",
				"Bip01_Spine",
				"Bip01_L_Hand",
				"Bip01_R_Hand",
				"Bip01_R_Foot",
				"Bip01_R_Thigh",
				"Bip01_L_Foot",
				"Bip01_L_Thigh",	};

			for( DWORD i=0; i<dwBones; ++i ){
				BONEINF* pNew = new BONEINF;
				pNew->m_strName = strBoneName[i].GetString();
				m_vecBoneINF.push_back( pNew );}
		}break;

	case 1:{ //LEG
			const DWORD dwLines = 4;
			DWORD	dwNewBone1[dwLines] = {8,12,10,13};
			DWORD	dwNewBone2[dwLines] = {12,9,13,11};

			for( DWORD i=0; i<dwLines; ++i ){
				BONELINE* pNew = new BONELINE;
				pNew->m_dwBONEID[0] = dwNewBone1[i];
				pNew->m_dwBONEID[1] = dwNewBone2[i];
				m_vecBoneLINE.push_back( pNew );}
			
			const DWORD dwBones = 14;
			CString strBoneName [dwBones] =	{
				"Bip01_L_UpperArm",
				"Bip01_L_Forearm",
				"Bip01_R_UpperArm",
				"Bip01_R_Forearm",
				"Bip01_Neck",
				"Bip01_Spine",
				"Bip01_L_Hand",
				"Bip01_R_Hand",
				"Bip01_R_Foot",
				"Bip01_R_Thigh",
				"Bip01_L_Foot",
				"Bip01_L_Thigh",
				"Bip01_R_Calf",
				"Bip01_L_Calf",	};

			for( DWORD i=0; i<dwBones; ++i ){
				BONEINF* pNew = new BONEINF;
				pNew->m_strName = strBoneName[i].GetString();
				m_vecBoneINF.push_back( pNew );}
		}break;
	case 2:{ //gloves
			const DWORD dwLines = 4;
			DWORD	dwNewBone1[dwLines] = {13,7,14,6};
			DWORD	dwNewBone2[dwLines] = {7,3,6,1};

			for( DWORD i=0; i<dwLines; ++i ){
				BONELINE* pNew = new BONELINE;
				pNew->m_dwBONEID[0] = dwNewBone1[i];
				pNew->m_dwBONEID[1] = dwNewBone2[i];
				m_vecBoneLINE.push_back( pNew );}
			
			const DWORD dwBones = 15;
			CString strBoneName [dwBones] =	{
				"Bip01_L_UpperArm",
				"Bip01_L_Forearm",
				"Bip01_R_UpperArm",
				"Bip01_R_Forearm",
				"Bip01_Neck",
				"Bip01_Spine",
				"Bip01_L_Hand",
				"Bip01_R_Hand",
				"Bip01_R_Foot",
				"Bip01_R_Thigh",
				"Bip01_L_Foot",
				"Bip01_L_Thigh",
				"Bip01_R_Finger22",
				"Bip01_R_Finger2",
				"Bip01_L_Finger2",};

			for( DWORD i=0; i<dwBones; ++i ){
				BONEINF* pNew = new BONEINF;
				pNew->m_strName = strBoneName[i].GetString();
				m_vecBoneINF.push_back( pNew );}
		}break;
	case 3:{ //shoes
			const DWORD dwLines = 2;
			DWORD	dwNewBone1[dwLines] = {15,16};
			DWORD	dwNewBone2[dwLines] = {10,8};

			for( DWORD i=0; i<dwLines; ++i ){
				BONELINE* pNew = new BONELINE;
				pNew->m_dwBONEID[0] = dwNewBone1[i];
				pNew->m_dwBONEID[1] = dwNewBone2[i];
				m_vecBoneLINE.push_back( pNew );}
			
			const DWORD dwBones = 17;
			CString strBoneName [dwBones] =	{
				"Bip01_L_UpperArm",
				"Bip01_L_Forearm",
				"Bip01_R_UpperArm",
				"Bip01_R_Forearm",
				"Bip01_Neck",
				"Bip01_Spine",
				"Bip01_L_Hand",
				"Bip01_R_Hand",
				"Bip01_R_Foot",
				"Bip01_R_Thigh",
				"Bip01_L_Foot",
				"Bip01_L_Thigh",
				"Bip01_R_Finger22",
				"Bip01_R_Finger2",
				"Bip01_L_Finger2",
				"Bip01_L_Toe0",
				"Bip01_R_Toe0",};

			for( DWORD i=0; i<dwBones; ++i ){
				BONEINF* pNew = new BONEINF;
				pNew->m_strName = strBoneName[i].GetString();
				m_vecBoneINF.push_back( pNew );}
		}break;
	};

	hr = Create( pd3dDevice );
	if ( FAILED(hr) )	
	{
		CDebugSet::ToLogFile("NewGrind_A Cannot Create pd3dDevice");
		return hr;
	}


	return S_OK;
}

HRESULT	DxEffCharLine2BoneEff::NewGrind_B ( int nType,int nGrind, LPDIRECT3DDEVICEQ pd3dDevice )
{
	if( g_bCHAR_EDIT_RUN )	nGrind = g_nITEMLEVEL;

	HRESULT hr;
	m_dwFlag = USE_SEQUENCE;
	m_dwOtherColor = 0;
	m_dwParticlePec = 22;
	m_dwColor = D3DCOLOR_ARGB(
		GLUpgradeColor::GetInstance().R_A[nGrind],
		GLUpgradeColor::GetInstance().R_R[nGrind],
		GLUpgradeColor::GetInstance().R_G[nGrind],
		GLUpgradeColor::GetInstance().R_B[nGrind]
		);

	m_dwColor2 = D3DCOLOR_ARGB(
		GLUpgradeColor::GetInstance().A_A[nGrind],
		GLUpgradeColor::GetInstance().A_R[nGrind],
		GLUpgradeColor::GetInstance().A_G[nGrind],
		GLUpgradeColor::GetInstance().A_B[nGrind]
		);

	m_dwSequenceCol = 3;
	m_dwSequenceRow = 3;
	m_fCreateLength = 0.0f;
	
	m_vLife.x = 0.5f;
	m_vLife.y = 0.5f;
	m_vSize.x = 3.0f;
	m_vSize.y = 3.0f;
	m_vSize.z = 1.0f;
	m_vScaleX.x = 2.0f;
	m_vScaleX.y = 1.0f;
	m_vScaleY.x = 1.0f;
	m_vScaleY.y = 1.0f;
	m_vScaleY.z = -0.5f;
	m_fShake = 0.0f;

	m_fMinMaxDist.min = 0.0f;
	m_fMinMaxDist.max = 0.0f;
	m_fMinMaxTexRotate.min = 0.3f;
	m_fMinMaxTexRotate.max = 0.5f;

	StringCchCopy( m_szTexture, BONELISTEFF_TEXNAME_SIZE, "eff_lightning11.dds" );
	StringCchCopy( m_szTexture2, BONELISTEFF_TEXNAME_SIZE, "eff_lightning11.dds" );

	switch ( nType ){
	case 0:{ //BODY
			const DWORD dwLines = 4;
			DWORD	dwNewBone1[dwLines] = {3,2,1,5};
			DWORD	dwNewBone2[dwLines] = {2,0,0,4};

			for( DWORD i=0; i<dwLines; ++i ){
				BONELINE* pNew = new BONELINE;
				pNew->m_dwBONEID[0] = dwNewBone1[i];
				pNew->m_dwBONEID[1] = dwNewBone2[i];
				m_vecBoneLINE.push_back( pNew );}

			const DWORD dwBones = 12;
			CString strBoneName [dwBones] =	{
				"Bip01_L_UpperArm",
				"Bip01_L_Forearm",
				"Bip01_R_UpperArm",
				"Bip01_R_Forearm",
				"Bip01_Neck",
				"Bip01_Spine",
				"Bip01_L_Hand",
				"Bip01_R_Hand",
				"Bip01_R_Foot",
				"Bip01_R_Thigh",
				"Bip01_L_Foot",
				"Bip01_L_Thigh",	};

			for( DWORD i=0; i<dwBones; ++i ){
				BONEINF* pNew = new BONEINF;
				pNew->m_strName = strBoneName[i].GetString();
				m_vecBoneINF.push_back( pNew );}
		}break;

	case 1:{ //LEG
			const DWORD dwLines = 4;
			DWORD	dwNewBone1[dwLines] = {8,12,10,13};
			DWORD	dwNewBone2[dwLines] = {12,9,13,11};

			for( DWORD i=0; i<dwLines; ++i ){
				BONELINE* pNew = new BONELINE;
				pNew->m_dwBONEID[0] = dwNewBone1[i];
				pNew->m_dwBONEID[1] = dwNewBone2[i];
				m_vecBoneLINE.push_back( pNew );}
			
			const DWORD dwBones = 14;
			CString strBoneName [dwBones] =	{
				"Bip01_L_UpperArm",
				"Bip01_L_Forearm",
				"Bip01_R_UpperArm",
				"Bip01_R_Forearm",
				"Bip01_Neck",
				"Bip01_Spine",
				"Bip01_L_Hand",
				"Bip01_R_Hand",
				"Bip01_R_Foot",
				"Bip01_R_Thigh",
				"Bip01_L_Foot",
				"Bip01_L_Thigh",
				"Bip01_R_Calf",
				"Bip01_L_Calf",	};

			for( DWORD i=0; i<dwBones; ++i ){
				BONEINF* pNew = new BONEINF;
				pNew->m_strName = strBoneName[i].GetString();
				m_vecBoneINF.push_back( pNew );}
		}break;
	case 2:{ //gloves
			const DWORD dwLines = 4;
			DWORD	dwNewBone1[dwLines] = {13,7,14,6};
			DWORD	dwNewBone2[dwLines] = {7,3,6,1};

			for( DWORD i=0; i<dwLines; ++i ){
				BONELINE* pNew = new BONELINE;
				pNew->m_dwBONEID[0] = dwNewBone1[i];
				pNew->m_dwBONEID[1] = dwNewBone2[i];
				m_vecBoneLINE.push_back( pNew );}
			
			const DWORD dwBones = 15;
			CString strBoneName [dwBones] =	{
				"Bip01_L_UpperArm",
				"Bip01_L_Forearm",
				"Bip01_R_UpperArm",
				"Bip01_R_Forearm",
				"Bip01_Neck",
				"Bip01_Spine",
				"Bip01_L_Hand",
				"Bip01_R_Hand",
				"Bip01_R_Foot",
				"Bip01_R_Thigh",
				"Bip01_L_Foot",
				"Bip01_L_Thigh",
				"Bip01_R_Finger22",
				"Bip01_R_Finger2",
				"Bip01_L_Finger2",};

			for( DWORD i=0; i<dwBones; ++i ){
				BONEINF* pNew = new BONEINF;
				pNew->m_strName = strBoneName[i].GetString();
				m_vecBoneINF.push_back( pNew );}
		}break;
	case 3:{ //shoes
			const DWORD dwLines = 2;
			DWORD	dwNewBone1[dwLines] = {15,16};
			DWORD	dwNewBone2[dwLines] = {10,8};

			for( DWORD i=0; i<dwLines; ++i ){
				BONELINE* pNew = new BONELINE;
				pNew->m_dwBONEID[0] = dwNewBone1[i];
				pNew->m_dwBONEID[1] = dwNewBone2[i];
				m_vecBoneLINE.push_back( pNew );}
			
			const DWORD dwBones = 17;
			CString strBoneName [dwBones] =	{
				"Bip01_L_UpperArm",
				"Bip01_L_Forearm",
				"Bip01_R_UpperArm",
				"Bip01_R_Forearm",
				"Bip01_Neck",
				"Bip01_Spine",
				"Bip01_L_Hand",
				"Bip01_R_Hand",
				"Bip01_R_Foot",
				"Bip01_R_Thigh",
				"Bip01_L_Foot",
				"Bip01_L_Thigh",
				"Bip01_R_Finger22",
				"Bip01_R_Finger2",
				"Bip01_L_Finger2",
				"Bip01_L_Toe0",
				"Bip01_R_Toe0",};

			for( DWORD i=0; i<dwBones; ++i ){
				BONEINF* pNew = new BONEINF;
				pNew->m_strName = strBoneName[i].GetString();
				m_vecBoneINF.push_back( pNew );}
		}break;
	};

	hr = Create( pd3dDevice );
	if ( FAILED(hr) )	
	{
		CDebugSet::ToLogFile("NewGrind_A Cannot Create pd3dDevice");
		return hr;
	}

	return S_OK;
}