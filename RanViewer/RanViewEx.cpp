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


void CRanView::SetAnim( int nType, int nMain , int nSub ,bool bAttack )
{
	EMANI_MAINTYPE mType = (EMANI_MAINTYPE)nMain;
	EMANI_SUBTYPE sType = (EMANI_SUBTYPE)nSub;
	bSAttack = bAttack;
	switch ( nType )
	{
	case 0 :
		{
			m_AniMain = mType;
			m_AniSub = sType;
		}break;
	case 1 :
		{
			m_ABLAniMain = mType;
			m_ABLAniSub = sType;
		}break;
	case 2 :
		{
			m_VCFAniMain = mType;
			m_VCFAniSub = sType;
		}break;
	};	
}

void CRanView::SetGrind( int nLevel )
{
	nGrind = nLevel;
}

void CRanView::SetActive ( BOOL bActive )
{
	DxInputDevice::GetInstance().OnActivate ( bActive );
}

void CRanView::EditMatrix ( int nKey )
{
	//if( DxInputDevice::GetInstance().GetKeyState(DIK_W) & DXKEY_DOWN )	EditMatrix ( 0 );
	//if( DxInputDevice::GetInstance().GetKeyState(DIK_S) & DXKEY_DOWN )	EditMatrix ( 1 );
	//if( DxInputDevice::GetInstance().GetKeyState(DIK_A) & DXKEY_DOWN )	EditMatrix ( 2 );
	//if( DxInputDevice::GetInstance().GetKeyState(DIK_D) & DXKEY_DOWN )	EditMatrix ( 3 );
	//if( DxInputDevice::GetInstance().GetKeyState(DIK_Q) & DXKEY_DOWN )	EditMatrix ( 4 );
	//if( DxInputDevice::GetInstance().GetKeyState(DIK_E) & DXKEY_DOWN )	EditMatrix ( 5 );

	if ( m_pSkinChar )
	{
		switch ( nEditType )
		{
		case 1: //abl edit
			{
				if ( m_pSkinChar->m_pSkinCharPiece[ nEditPiece ] ) 
				{
					D3DXVECTOR3		m_vEdit;

					switch ( nEditStance )
					{
					case 0: //free stance
						{
							switch ( nEditMode )
							{
							case 0: //rotate
								{
									m_vEdit.x = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRot_F.x * fDevider;
									m_vEdit.y = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRot_F.y * fDevider;
									m_vEdit.z = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRot_F.z * fDevider;

									switch  ( nKey )
									{
										case 0 :	m_vEdit.x ++;		break;
										case 1 :	m_vEdit.x --;		break;
										case 2 :	m_vEdit.y ++;		break;
										case 3 :	m_vEdit.y --;		break;
										case 4 :	m_vEdit.z ++;		break;
										case 5 :	m_vEdit.z --;		break;
									};

									m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRot_F.x = m_vEdit.x / fDevider;
									m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRot_F.y = m_vEdit.y / fDevider;
									m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRot_F.z = m_vEdit.z / fDevider;

								}break;
							case 1:	//position
								{
									m_vEdit.x = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRoot_F.x * fDevider;
									m_vEdit.y = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRoot_F.y * fDevider;
									m_vEdit.z = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRoot_F.z * fDevider;

									switch  ( nKey )
									{
										case 0 :	m_vEdit.x ++;		break;
										case 1 :	m_vEdit.x --;		break;
										case 2 :	m_vEdit.y ++;		break;
										case 3 :	m_vEdit.y --;		break;
										case 4 :	m_vEdit.z ++;		break;
										case 5 :	m_vEdit.z --;		break;
									};

									m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRoot_F.x = m_vEdit.x / fDevider;
									m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRoot_F.y = m_vEdit.y / fDevider;
									m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRoot_F.z = m_vEdit.z / fDevider;

								}break;
							};
						}break;
					case 1: //attack stance
						{
							switch ( nEditMode )
							{
							case 0: //rotate
								{
									m_vEdit.x = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRot.x * fDevider;
									m_vEdit.y = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRot.y * fDevider;
									m_vEdit.z = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRot.z * fDevider;

									switch  ( nKey )
									{
										case 0 :	m_vEdit.x ++;		break;
										case 1 :	m_vEdit.x --;		break;
										case 2 :	m_vEdit.y ++;		break;
										case 3 :	m_vEdit.y --;		break;
										case 4 :	m_vEdit.z ++;		break;
										case 5 :	m_vEdit.z --;		break;
									};

									m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRot.x = m_vEdit.x / fDevider;
									m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRot.y = m_vEdit.y / fDevider;
									m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRot.z = m_vEdit.z / fDevider;

								}break;
							case 1:	//position
								{
									m_vEdit.x = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRoot.x * fDevider;
									m_vEdit.y = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRoot.y * fDevider;
									m_vEdit.z = m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRoot.z * fDevider;

									switch  ( nKey )
									{
										case 0 :	m_vEdit.x ++;		break;
										case 1 :	m_vEdit.x --;		break;
										case 2 :	m_vEdit.y ++;		break;
										case 3 :	m_vEdit.y --;		break;
										case 4 :	m_vEdit.z ++;		break;
										case 5 :	m_vEdit.z --;		break;
									};

									m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRoot.x = m_vEdit.x / fDevider;
									m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRoot.y = m_vEdit.y / fDevider;
									m_pSkinChar->m_pSkinCharPiece[nEditPiece]->m_vRoot.z = m_vEdit.z / fDevider;

								}break;
							};

						}break;
					};	
				}
			}break;
		case 2: //vcf edit
			{
				if ( m_pSkinChar->m_pSkinVehicle ) 
				{
					D3DXVECTOR3		m_vEdit;

					switch ( nEditStance )
					{
					case 0: //Char 01
						{
							switch ( nEditMode )
							{
							case 0: //rotate
								{
									m_vEdit = m_pSkinChar->m_pSkinVehicle->m_vRotation_Font * fDevider;
									switch  ( nKey )
									{
										case 0 :	m_vEdit.x ++;		break;
										case 1 :	m_vEdit.x --;		break;
										case 2 :	m_vEdit.y ++;		break;
										case 3 :	m_vEdit.y --;		break;
										case 4 :	m_vEdit.z ++;		break;
										case 5 :	m_vEdit.z --;		break;
									};
									m_pSkinChar->m_pSkinVehicle->m_vRotation_Font = m_vEdit / fDevider;
								}break;
							case 1:	//position
								{
									m_vEdit = m_pSkinChar->m_pSkinVehicle->m_vTransform_Font * fDevider;
									switch  ( nKey )
									{
										case 0 :	m_vEdit.x ++;		break;
										case 1 :	m_vEdit.x --;		break;
										case 2 :	m_vEdit.y ++;		break;
										case 3 :	m_vEdit.y --;		break;
										case 4 :	m_vEdit.z ++;		break;
										case 5 :	m_vEdit.z --;		break;
									};
									m_pSkinChar->m_pSkinVehicle->m_vTransform_Font = m_vEdit / fDevider;
								}break;
							};
						}break;
					case 1: //Char 02
						{
							switch ( nEditMode )
							{
							case 0: //rotate
								{
									m_vEdit = m_pSkinChar->m_pSkinVehicle->m_vRotation_Back * fDevider;
									switch  ( nKey )
									{
										case 0 :	m_vEdit.x ++;		break;
										case 1 :	m_vEdit.x --;		break;
										case 2 :	m_vEdit.y ++;		break;
										case 3 :	m_vEdit.y --;		break;
										case 4 :	m_vEdit.z ++;		break;
										case 5 :	m_vEdit.z --;		break;
									};
									m_pSkinChar->m_pSkinVehicle->m_vRotation_Back = m_vEdit / fDevider;
								}break;
							case 1:	//position
								{
									m_vEdit = m_pSkinChar->m_pSkinVehicle->m_vTransform_Back * fDevider;
									switch  ( nKey )
									{
										case 0 :	m_vEdit.x ++;		break;
										case 1 :	m_vEdit.x --;		break;
										case 2 :	m_vEdit.y ++;		break;
										case 3 :	m_vEdit.y --;		break;
										case 4 :	m_vEdit.z ++;		break;
										case 5 :	m_vEdit.z --;		break;
									};
									m_pSkinChar->m_pSkinVehicle->m_vTransform_Back = m_vEdit / fDevider;
								}break;
							};
						}break;
					}break;
				}
			}break;
		};
	}
}

void CRanView::SetDevider ( int nDevide )
{
	switch (nDevide)
	{
	case 0:	fDevider = 1.0f;	break;
	case 1:	fDevider = 10.0f;	break;
	case 2:	fDevider = 100.0f;	break;
	};
}

void CRanView::SetColor ( int nType, WORD wColor )
{
	switch (nType)
	{
	case 0:	if ( m_pSkinChar )	m_pSkinChar->SetHairColor(wColor);	break; //hair color
	case 1:	if ( m_pSkinChar )	m_pSkinChar->SetColorAll(wColor);	break; //piece color
	case 2:	if ( m_pSkinChar->m_pSkinVehicle ) m_pSkinChar->m_pSkinVehicle->SetColor(wColor);	break; //bike color
	case 3:
		{
			for ( int i=0; i<PIECE_SIZE; ++i ) //abl color
			{
				if ( m_pSkinChar->m_pSkinCharPiece[i] ) m_pSkinChar->m_pSkinCharPiece[i]->SetColor(wColor);
			}
		}break;
	};
}

/*void CRanView::SetUpgradeEffect ( int nType , int nSex )
{
	if ( m_pSkinChar )
	{
		m_pSkinChar->SetGradeEffect( nType,nSex,nGrind,m_pd3dDevice,TRUE);
	}
}
*/
