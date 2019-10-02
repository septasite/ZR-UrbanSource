#include "stdafx.h"
#include "RanViewer.h"
#include "GLOGIC.h"
#include "DxEffectMan.h"
#include "RANPARAM.h"
#include "DxResponseMan.h"
#include "DxViewPort.h"
#include "DxGlowMan.h"
#include "DxShadowMap.h"
#include "DxPostProcess.h"
#include "DxInputDevice.h"
#include "profile.h"
#include "dxparamset.h"
#include "SUBPATH.h"
#include "GLChar.h"
#include "DxServerInstance.h"
#include "DxGlobalStage.h"
#include "RanDoc.h"
#include "RanView.h"
#include "D3DFont.h"
#include "../EngineUILib/GUInterface/Cursor.h"
#include "../EngineLib/DxCommon/DxFontMan.h"
#include "../RanClientUILib/Interface/GameTextControl.h"
#include ".\Ranview.h"
#include "DxSkinMeshMan.h"
#include "DxDynamicVB.h"
#include "DxCubeMap.h"
#include "MainFrm.h"
#include "ToolComment.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

/*extern*/ BOOL g_bCHAR_VIEW_RUN; 
extern BOOL g_bCHAR_EDIT_RUN;
extern int g_nITEMLEVEL;


HRESULT CRanView::SkinLoad( LPDIRECT3DDEVICEQ pd3dDevice, const char* szFile )
{
	DxSkinCharData* pSkinChar = DxSkinCharDataContainer::GetInstance().LoadData( szFile, pd3dDevice, TRUE );
	if ( !pSkinChar )	
	{
		MessageBox("Cannot Load CHF","Error",MB_OK);
		return E_FAIL;
	}

	SAFE_DELETE(m_pSkinChar);
	m_pSkinChar = new DxSkinChar;

	m_pSkinChar->SetCharData ( pSkinChar, pd3dDevice, TRUE );

	m_pSkinChar->GetAABBBox( m_vMaxOrg, m_vMinOrg );
	m_fHeight = m_vMaxOrg.y - m_vMinOrg.y;

	m_pSkinChar->InitDeviceObjects( m_pd3dDevice );
	m_pSkinChar->RestoreDeviceObjects(m_pd3dDevice);

	g_bCHAR_EDIT_RUN  = TRUE ;
	g_bCHAR_VIEW_RUN  = TRUE ;
	g_nITEMLEVEL = 5;

	return S_OK;
}

void CRanView::CHFLOAD()
{
	CString szFilter = "Container (*.chf,*.vcf,*.abf)|*.chf;*.vcf;*.abf|";
	CFileDialog dlg ( TRUE,".CHF",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter, this );

	dlg.m_ofn.lpstrInitialDir = DxSkinPieceContainer::GetInstance().GetPath ();
	if ( dlg.DoModal() == IDOK )
	{
		m_strCHF = dlg.GetFileName();
		SkinLoad( m_pd3dDevice, m_strCHF.GetString() );
	}
}

void CRanView::OnChfDefaultmale()
{
	m_strCHF = "o_m.chf";
	SkinLoad( m_pd3dDevice, m_strCHF.GetString() );
}

void CRanView::OnChfDefaultfemale()
{
	m_strCHF = "o_w.chf";
	SkinLoad( m_pd3dDevice, m_strCHF.GetString() );
}

void CRanView::OnChfApplypiece()
{

	CString szFilter = "CPS|*.cps|";

	CFileDialog dlg ( TRUE,".CPS",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter, this );

	dlg.m_ofn.lpstrInitialDir = DxSkinPieceContainer::GetInstance().GetPath ();
	if ( dlg.DoModal() == IDOK )
	{
		m_pSkinChar->SetPiece ( dlg.GetFileName(), m_pd3dDevice, NULL, nGrind, TRUE );
	}
}

void CRanView::OnChfApplyablnormal()
{
	CString szFilter = "ABL|*.abl|";

	CFileDialog dlg ( TRUE,".CPS",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter, this );

	dlg.m_ofn.lpstrInitialDir = DxSkinPieceContainer::GetInstance().GetPath ();
	if ( dlg.DoModal() == IDOK )
	{
		DxSkinPieceRootData* pPieceDataRoot; 
		pPieceDataRoot = DxSkinPieceRootDataContainer::GetInstance().LoadData( dlg.GetFileName() , m_pd3dDevice , TRUE );
				
		if ( pPieceDataRoot )
		{
			if ( pPieceDataRoot->GetUseCPS() )
			{
				m_pSkinChar->SetPiece( pPieceDataRoot->GetCpsName().c_str(), m_pd3dDevice, NULL, nGrind, TRUE );
			}
			
			m_pSkinChar->SetCharPieceData( pPieceDataRoot->GetData()
										, m_pd3dDevice
										, pPieceDataRoot->GetBoneLink()
										, pPieceDataRoot->GetWeaponSlot()
										, pPieceDataRoot->GetType()
										, NULL
										, nGrind
										, TRUE );
		}
	}
}

void CRanView::OnChfApplyablleft()
{
	CString szFilter = "ABL|*.abl|";

	CFileDialog dlg ( TRUE,".CPS",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter, this );

	dlg.m_ofn.lpstrInitialDir = DxSkinPieceContainer::GetInstance().GetPath ();
	if ( dlg.DoModal() == IDOK )
	{
		DxSkinPieceRootData* pPieceDataRoot;
		pPieceDataRoot = DxSkinPieceRootDataContainer::GetInstance().LoadData( dlg.GetFileName() , m_pd3dDevice , TRUE );
		if ( pPieceDataRoot )
		{
			if ( pPieceDataRoot->GetUseCPS() )
			{
				m_pSkinChar->SetPiece( pPieceDataRoot->GetCpsName().c_str(), m_pd3dDevice, NULL,nGrind, TRUE );
			}
			else
			{
				m_pSkinChar->ResetCPS ( PIECE_LHAND );
			}

			m_pSkinChar->SetCharPieceData( pPieceDataRoot->GetData()
											, m_pd3dDevice
											, pPieceDataRoot->GetBoneLink()
											, pPieceDataRoot->GetWeaponSlot()
											, (DWORD) PIECE_LHAND
											, NULL
											, nGrind
											, TRUE );
			m_pSkinChar->Clear( PIECE_RHAND );
		}
	}
}

void CRanView::OnChfApplyablright()
{
	CString szFilter = "ABL|*.abl|";

	CFileDialog dlg ( TRUE,".CPS",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter, this );

	dlg.m_ofn.lpstrInitialDir = DxSkinPieceContainer::GetInstance().GetPath ();
	if ( dlg.DoModal() == IDOK )
	{
		DxSkinPieceRootData* pPieceDataRoot;
		pPieceDataRoot = DxSkinPieceRootDataContainer::GetInstance().LoadData( dlg.GetFileName() , m_pd3dDevice , TRUE );
		if ( pPieceDataRoot )
		{
			if ( pPieceDataRoot->GetUseCPS() )
			{
				m_pSkinChar->SetPiece( pPieceDataRoot->GetCpsName().c_str(), m_pd3dDevice, NULL, nGrind, TRUE );
			}
			else
			{
				m_pSkinChar->ResetCPS ( PIECE_RHAND );
			}

			m_pSkinChar->SetCharPieceData( pPieceDataRoot->GetData()
											, m_pd3dDevice
											, pPieceDataRoot->GetBoneLink()
											, pPieceDataRoot->GetWeaponSlot()
											, (DWORD) PIECE_RHAND
											, NULL
											, nGrind
											, TRUE );
			m_pSkinChar->Clear( PIECE_LHAND );
		}
	}
}

void CRanView::OnChfApplybothhandabl()
{
	CString szFilterL = "LHAND ABL|*.abl|";
	CString szFilterR = "RHAND ABL|*.abl|";

	CFileDialog dlgR ( TRUE,".CPS",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterR, this );
	CFileDialog dlgL ( TRUE,".CPS",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilterL, this );

	dlgR.m_ofn.lpstrInitialDir = DxSkinPieceContainer::GetInstance().GetPath ();
	dlgL.m_ofn.lpstrInitialDir = DxSkinPieceContainer::GetInstance().GetPath ();

	if ( dlgR.DoModal() == IDOK )
	{
		DxSkinPieceRootData* pPieceDataRoot;
		pPieceDataRoot = DxSkinPieceRootDataContainer::GetInstance().LoadData( dlgR.GetFileName() , m_pd3dDevice , TRUE );
		if ( pPieceDataRoot )
		{
			if ( pPieceDataRoot->GetUseCPS() )
			{
				m_pSkinChar->SetPiece( pPieceDataRoot->GetCpsName().c_str(), m_pd3dDevice, NULL, nGrind, TRUE );
			}
			else
			{
				m_pSkinChar->ResetCPS ( PIECE_RHAND );
			}

			m_pSkinChar->SetCharPieceData( pPieceDataRoot->GetData()
											, m_pd3dDevice
											, pPieceDataRoot->GetBoneLink()
											, pPieceDataRoot->GetWeaponSlot()
											, (DWORD) PIECE_RHAND
											, NULL
											, nGrind
											, TRUE );
		}
	}

	if ( dlgL.DoModal() == IDOK )
	{
		DxSkinPieceRootData* pPieceDataRoot;
		pPieceDataRoot = DxSkinPieceRootDataContainer::GetInstance().LoadData( dlgL.GetFileName() , m_pd3dDevice , TRUE );
		if ( pPieceDataRoot )
		{
			if ( pPieceDataRoot->GetUseCPS() )
			{
				m_pSkinChar->SetPiece( pPieceDataRoot->GetCpsName().c_str(), m_pd3dDevice, NULL,nGrind, TRUE );
			}
			else
			{
				m_pSkinChar->ResetCPS ( PIECE_LHAND );
			}

			m_pSkinChar->SetCharPieceData( pPieceDataRoot->GetData()
											, m_pd3dDevice
											, pPieceDataRoot->GetBoneLink()
											, pPieceDataRoot->GetWeaponSlot()
											, (DWORD) PIECE_LHAND
											, NULL
											, nGrind
											, TRUE );
		}
	}	
}

void CRanView::OnChfApplyvcf()
{
	CString szFilter = "VCF|*.vcf|";

	CFileDialog dlg ( TRUE,".CPS",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter, this );

	dlg.m_ofn.lpstrInitialDir = DxSkinPieceContainer::GetInstance().GetPath ();
	if ( dlg.DoModal() == IDOK )
	{
		DxSkinVehicleData* pVehicleData;
		pVehicleData = DxSkinVehicleDataContainer::GetInstance().LoadData( dlg.GetFileName() , m_pd3dDevice , TRUE );
		if ( pVehicleData )
		{
			m_pSkinChar->SetVehicleData( pVehicleData
										, m_pd3dDevice
										, TRUE );
			m_pSkinChar->m_pSkinVehicle->SetColor( 32767 );
		}
	}
}

void CRanView::OnChfClearpiece()
{
	DxSkinPieceRootDataContainer::GetInstance().CleanUp ();
	DxSkinVehicleDataContainer::GetInstance().CleanUp ();
	DxSkinCharDataContainer::GetInstance().CleanUp ();
	DxSkinPieceContainer::GetInstance().FinalCleanup ();

	SkinLoad( m_pd3dDevice, m_strCHF.GetString() );
}

void CRanView::OnChfApplyvcfpiece()
{
	CString szFilter = "VPS|*.vps|";

	CFileDialog dlg ( TRUE,".VPS",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter, this );

	dlg.m_ofn.lpstrInitialDir = DxSkinPieceContainer::GetInstance().GetPath ();
	if ( dlg.DoModal() == IDOK )
	{
		m_pSkinChar->m_pSkinVehicle->SetPiece(  dlg.GetFileName(), m_pd3dDevice, NULL, nGrind, TRUE );
	}
}

void CRanView::OnCameraResetcamera()
{
	m_vPos.x = 0 ;
	m_vPos.y = 0 ;
	m_vPos.z = 0 ;

	DxViewPort::GetInstance().SetCameraType ((CAMERA_TYPE)2);

	D3DXVECTOR3 vFromPt		= D3DXVECTOR3( 0.0f, 70.0f, -70.0f );
	D3DXVECTOR3 vLookatPt	= D3DXVECTOR3( 0.0f, 0.0f, 0.0f );
	D3DXVECTOR3 vUpVec		= D3DXVECTOR3( 0.0f, 1.0f, 0.0f );
	DxViewPort::GetInstance().SetViewTrans ( vFromPt, vLookatPt, vUpVec );

	D3DXVECTOR3 vCamera = m_vPos;
	vCamera.y += 10.0f;
	DxViewPort::GetInstance().CameraJump ( vCamera );

	CCursor::GetInstance().InitDeviceObjects ();
	DxResponseMan::GetInstance().SetRenderState ();
}
