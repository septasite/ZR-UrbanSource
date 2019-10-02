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


HRESULT CRanView::RenderText()
{
	D3DCOLOR fontColor        = D3DCOLOR_ARGB(255,255,0,0);
	D3DCOLOR fontWarningColor = D3DCOLOR_ARGB(255,255,0,0);
	TCHAR szMsg[MAX_PATH] = TEXT("");

	CD3DFontPar* pD3dFont = DxFontMan::GetInstance().FindFont ( _DEFAULT_FONT, 9, _DEFAULT_FONT_FLAG );
	if ( !pD3dFont )	return S_OK;

	FLOAT fNextLine = 40.0f; 

	lstrcpy( szMsg, m_strDeviceStats );
	fNextLine -= 20.0f;
	pD3dFont->DrawText( 2, fNextLine, fontColor, szMsg );

	lstrcpy( szMsg, m_strFrameStats );
	fNextLine -= 20.0f;
	pD3dFont->DrawText( 2, fNextLine, fontColor, szMsg );

	CDebugSet::Render ();

	CDebugSet::ToView ( 1, "Mouse: %4.1f, %4.1f, %4.1f",m_vMousePos.x, m_vMousePos.y,m_vMousePos.z );
	CDebugSet::ToView ( 2, "CH0(CTRL+1)(Basic Info)" );
	CDebugSet::ToView ( 3, "CH1(CTRL+2)(Skin Info)" );
	CDebugSet::ToView ( 4, "CH2(CTRL+3)(ABL-VCF Matrix)" );
	CDebugSet::ToView ( 5, "CH2(CTRL+4)(Camera Matrix)" );

	CDebugSet::ToView ( 1,1, "Mouse: %4.1f, %4.1f, %4.1f",m_vMousePos.x, m_vMousePos.y,m_vMousePos.z );


	D3DXVECTOR3 vFromPt = DxViewPort::GetInstance().GetFromPt();
	D3DXVECTOR3 vLookAtPt = DxViewPort::GetInstance().GetLookatPt();
	D3DXVECTOR3 vLookDir = DxViewPort::GetInstance().GetLookDir();
	CDebugSet::ToView ( 3,1, "vFromPt: %4.1f, %4.1f, %4.1f",vFromPt.x, vFromPt.y,vFromPt.z );
	CDebugSet::ToView ( 3,2, "vLookAtPt: %4.1f, %4.1f, %4.1f",vLookAtPt.x, vLookAtPt.y,vLookAtPt.z );
	CDebugSet::ToView ( 3,3, "vLookDir: %4.1f, %4.1f, %4.1f",vLookDir.x, vLookDir.y,vLookDir.z );

	if ( m_pSkinChar )
	{
		CString strName;
		CDebugSet::ToView ( 1,2, m_pSkinChar->GetFileName()  );
		CDebugSet::ToView ( 1,3, COMMENT::ANI_MAINTYPE[m_pSkinChar->GETCURMTYPE()].c_str()  );
		strName.Format ("Weapon Sub:%s",COMMENT::ANI_SUBTYPE[m_pSkinChar->GETCURSTYPE()].c_str() );
		CDebugSet::ToView ( 1,4, strName.GetString() );
		strName.Format ("Skill Sub:%s",COMMENT::ANI_SUBTYPE_00[m_pSkinChar->GETCURSTYPE()].c_str() );
		CDebugSet::ToView ( 1,5, strName.GetString() );
		strName.Format ("Vehicle Sub:%s",COMMENT::ANI_SUBTYPE_01[m_pSkinChar->GETCURSTYPE()].c_str() );
		CDebugSet::ToView ( 1,6, strName.GetString() );

		if ( m_pSkinChar->m_pSkinVehicle ) 
		{
			strName.Format ("VCF Main:%s",COMMENT::ANI_MAINTYPE_00[m_pSkinChar->m_pSkinVehicle->GETCURMTYPE()].c_str() );
			CDebugSet::ToView ( 1,7, strName.GetString() );
			strName.Format ("VCF Sub:%s",COMMENT::ANI_SUBTYPE_00[m_pSkinChar->m_pSkinVehicle->GETCURSTYPE()].c_str() );
			CDebugSet::ToView ( 1,8, strName.GetString() );
			strName.Format ("VCF:%s ",m_pSkinChar->m_pSkinVehicle->GetFileName() );
			CDebugSet::ToView ( 1,9, strName.GetString() );
		}

		int nNum = 9;
		for ( int i=0; i<PIECE_SIZE; ++i )
		{
			if ( m_pSkinChar->m_pSkinCharPiece[i] ) 
			{
				nNum++;
				strName.Format ("ABL:[%s] Type:[%s] Main:%s--Sub:%s",
					m_pSkinChar->m_pSkinCharPiece[i]->m_szFileName,
					ToolComment::m_ABLType[i].c_str(),
					COMMENT::ANI_MAINTYPE_01[ m_pSkinChar->m_pSkinCharPiece[i]->GETCURMTYPE() ].c_str(),
					COMMENT::ANI_SUBTYPE_00[ m_pSkinChar->m_pSkinCharPiece[i]->GETCURSTYPE() ].c_str() 
					);

				CDebugSet::ToView ( 1,nNum, strName.GetString() );
			}
		}

		for ( int i=0; i<PIECE_SIZE; ++i )
		{
			if ( m_pSkinChar->m_PartArray[i].m_pSkinMesh )
			{
				nNum++;
				strName.Format ("Piece:[%s] Type:[%s]",
					m_pSkinChar->m_PartArray[i].GetFileName(),
					ToolComment::m_ABLType[i].c_str()
					);
				CDebugSet::ToView ( 1,nNum, strName.GetString() );
			}	
		}
	}

	if ( m_pSkinChar )
	{
		CString strTemp2;
		float	fRotX,fRotY,fRotZ,fPosX,fPosY,fPosZ ;

		switch ( nEditType )
		{
		case 1: //abl edit
			{
				CDebugSet::ToView ( 2,1, "Edit Type:ABL" );

				if ( m_pSkinChar->m_pSkinCharPiece[ nEditPiece ] ) 
				{
					CDebugSet::ToView ( 2,2, ToolComment::m_ABLType[nEditPiece].c_str() );

					switch ( nEditStance )
					{
					case 0: //free stance
						{
							fRotX = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRot_F.x;
							fRotY = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRot_F.y;
							fRotZ = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRot_F.z;

							fPosX = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRoot_F.x;
							fPosY = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRoot_F.y;
							fPosZ = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRoot_F.z;

							CDebugSet::ToView ( 2,3, "ABL Stance:Free" );
						}break;
					case 1: //attack stance
						{
							fRotX = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRot.x;
							fRotY = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRot.y;
							fRotZ = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRot.z;

							fPosX = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRoot.x;
							fPosY = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRoot.y;
							fPosZ = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRoot.z;

							CDebugSet::ToView ( 2,3, "ABL Stance:Attack" );
						}break;
					};	

					CDebugSet::ToView ( 2,4, "Rotation: X:%4.4f, Y:%4.4f, Z:%4.4f",fRotX, fRotY,fRotZ );
					CDebugSet::ToView ( 2,5, "Position: X:%4.4f, Y:%4.4f, Z:%4.4f",fPosX, fPosY,fPosZ );
					CDebugSet::ToView ( 2,7, "Devider:%4.4f",fDevider);
				}
				else
				{
					CDebugSet::ToView ( 2,2, "" );
					CDebugSet::ToView ( 2,3, "" );
					CDebugSet::ToView ( 2,4, "" );
					CDebugSet::ToView ( 2,5, "" );
					CDebugSet::ToView ( 2,7, "" );
				}
			}break;
		case 2: //vcf edit
			{
				CDebugSet::ToView ( 2,1, "Edit Type:VCF" );

				if ( m_pSkinChar->m_pSkinVehicle ) 
				{
					switch ( nEditStance )
					{
					case 0: //Char 01
						{
							CDebugSet::ToView ( 2,2, "Vcf Slot:Front" );
							CDebugSet::ToView ( 2,3, "Bone:%s",m_pSkinChar->m_pSkinVehicle->m_strChar_Font.c_str() );
							fRotX = m_pSkinChar->m_pSkinVehicle->m_vRotation_Font.x;
							fRotY = m_pSkinChar->m_pSkinVehicle->m_vRotation_Font.y;
							fRotZ = m_pSkinChar->m_pSkinVehicle->m_vRotation_Font.z;
							fPosX = m_pSkinChar->m_pSkinVehicle->m_vTransform_Font.x;
							fPosY = m_pSkinChar->m_pSkinVehicle->m_vTransform_Font.y;
							fPosZ = m_pSkinChar->m_pSkinVehicle->m_vTransform_Font.z;
						}break;
					case 1: //Char 02
						{
							CDebugSet::ToView ( 2,2, "Vcf Slot:Back" );
							CDebugSet::ToView ( 2,3, "Bone:%s",m_pSkinChar->m_pSkinVehicle->m_strChar_Back.c_str() );
							fRotX = m_pSkinChar->m_pSkinVehicle->m_vRotation_Back.x;
							fRotY = m_pSkinChar->m_pSkinVehicle->m_vRotation_Back.y;
							fRotZ = m_pSkinChar->m_pSkinVehicle->m_vRotation_Back.z;
							fPosX = m_pSkinChar->m_pSkinVehicle->m_vTransform_Back.x;
							fPosY = m_pSkinChar->m_pSkinVehicle->m_vTransform_Back.y;
							fPosZ = m_pSkinChar->m_pSkinVehicle->m_vTransform_Back.z;
						}break;
					};
					CDebugSet::ToView ( 2,4, "Rotation: X:%4.4f, Y:%4.4f, Z:%4.4f",fRotX, fRotY,fRotZ );
					CDebugSet::ToView ( 2,5, "Position: X:%4.4f, Y:%4.4f, Z:%4.4f",fPosX, fPosY,fPosZ );
					CDebugSet::ToView ( 2,7, "Devider:%4.4f",fDevider);
				}
				else
				{
					CDebugSet::ToView ( 2,2, "" );
					CDebugSet::ToView ( 2,3, "" );
					CDebugSet::ToView ( 2,4, "" );
					CDebugSet::ToView ( 2,5, "" );
					CDebugSet::ToView ( 2,7, "" );
				}
			}break;
		};

		switch ( nEditMode )
		{
		case 0:	CDebugSet::ToView ( 2,6, "Edit Mode:Rotation" );	break;
		case 1:	CDebugSet::ToView ( 2,6, "Edit Mode:Position" );	break;
		};
	}
	else
	{
		CDebugSet::ToView ( 2,1, "" );
		CDebugSet::ToView ( 2,2, "" );
		CDebugSet::ToView ( 2,3, "" );
		CDebugSet::ToView ( 2,4, "" );
		CDebugSet::ToView ( 2,5, "" );
		CDebugSet::ToView ( 2,6, "" );
		CDebugSet::ToView ( 2,7, "" );
	}

	CDebugSet::ToView ( 2,9, "Key S(X--)-W(X++)" );
	CDebugSet::ToView ( 2,10, "Key A(Y--)-D(Y++)" );
	CDebugSet::ToView ( 2,11, "Key Q(Z--)-E(Z++)" );
    return S_OK;
}
