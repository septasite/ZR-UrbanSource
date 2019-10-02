// RanEditLevelView.cpp : implementation of the CRanEditLevelView class
//

#include "stdafx.h"
#include "RanEditLevel.h"

#include "RanEditLevelDoc.h"
#include "RanEditLevelView.h"

#include "DxGlobalStage.h"
#include "GLogicData.h"
#include "DxEffectMan.h"
#include "GLogic.h"

#include ".\raneditlevelview.h"
#include "dxparamset.h"
#include "./GLLevelFile.h"
#include "../../EngineSoundLib/DxSound/BgmSound.h"
#include "../../EngineSoundLib/DxSound/DxSoundMan.h"
#include "MainFrm.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

extern int g_nITEMLEVEL;
extern BOOL g_bCHAR_EDIT_RUN;

// CRanEditLevelView

IMPLEMENT_DYNCREATE(CRanEditLevelView, CView)

BEGIN_MESSAGE_MAP(CRanEditLevelView, CView)
	// Standard printing commands
	ON_WM_SETCURSOR()
	ON_WM_SIZE()
	ON_COMMAND(ID_FILE_PRINT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_DIRECT, CView::OnFilePrint)
	ON_COMMAND(ID_FILE_PRINT_PREVIEW, CView::OnFilePrintPreview)
	ON_COMMAND(ID_FILE_OPEN, OnFileOpen)
	ON_COMMAND(ID_FILE_SAVE, OnFileSave)
	ON_COMMAND(ID_FILE_NEW, OnFileNew)
	ON_COMMAND(ID_CAMERACONTROLS_RESETCAMERAPOS, OnCameracontrolsResetcamerapos)
	ON_COMMAND(ID_CAMERACONTROLS_CAMERASPEED300, OnCameracontrolsCameraspeed300)
	ON_COMMAND(ID_CAMERACONTROLS_CAMERASPEED600, OnCameracontrolsCameraspeed600)
	ON_COMMAND(ID_CAMERACONTROLS_CAMERASPEED900, OnCameracontrolsCameraspeed900)
	ON_COMMAND(ID_RENDEROPTIONS_RENDERQUADTREE, OnRenderoptionsRenderquadtree)
	ON_COMMAND(ID_RENDEROPTIONS_RENDERCROWMODELS, OnRenderoptionsRendercrowmodels)
	ON_COMMAND(ID_RENDEROPTIONS_RENDERCROWSCHED, OnRenderoptionsRendercrowsched)
	ON_COMMAND(ID_RENDEROPTIONS_RENDERDEBUGINFO, OnRenderoptionsRenderdebuginfo)
	ON_UPDATE_COMMAND_UI(ID_RENDEROPTIONS_RENDERQUADTREE, OnUpdateRenderoptionsRenderquadtree)
	ON_UPDATE_COMMAND_UI(ID_RENDEROPTIONS_RENDERCROWMODELS, OnUpdateRenderoptionsRendercrowmodels)
	ON_UPDATE_COMMAND_UI(ID_RENDEROPTIONS_RENDERCROWSCHED, OnUpdateRenderoptionsRendercrowsched)
	ON_UPDATE_COMMAND_UI(ID_RENDEROPTIONS_RENDERDEBUGINFO, OnUpdateRenderoptionsRenderdebuginfo)
	ON_COMMAND(ID_RENDEROPTIONS_RENDERGATE, OnRenderoptionsRendergate)
	ON_UPDATE_COMMAND_UI(ID_RENDEROPTIONS_RENDERGATE, OnUpdateRenderoptionsRendergate)
	ON_COMMAND(ID_RENDEROPTIONS_RENDERLANDEFFECT, OnRenderoptionsRenderlandeffect)
	ON_UPDATE_COMMAND_UI(ID_RENDEROPTIONS_RENDERLANDEFFECT, OnUpdateRenderoptionsRenderlandeffect)
	ON_COMMAND(ID_WLD_WLDLOAD, OnWldWldload)
	ON_COMMAND(ID_WLD_WLDSAVE, OnWldWldsave)
	ON_COMMAND(ID_WLD_WLDCLEAR, OnWldWldclear)
	ON_COMMAND(ID_MOUSECONTROL_NONE, OnMousecontrolNone)
	ON_COMMAND(ID_MOUSECONTROL_MOVE, OnMousecontrolMove)
	ON_COMMAND(ID_MOUSECONTROL_ROTATE, OnMousecontrolRotate)
	ON_COMMAND(ID_MOUSECONTROL_SCALE, OnMousecontrolScale)
	ON_COMMAND(ID_MOUSECONTROL_BOXMOVE, OnMousecontrolBoxmove)
	ON_COMMAND(ID_MOUSECONTROL_BOXSCALE, OnMousecontrolBoxscale)
	ON_COMMAND(ID_MOUSECONTROL_BOXSELSCALE, OnMousecontrolBoxselscale)
	ON_COMMAND(ID_MOUSECONTROL_DETECTOBJECT, OnMousecontrolDetectobject)
	ON_UPDATE_COMMAND_UI(ID_MOUSECONTROL_NONE, OnUpdateMousecontrolNone)
	ON_UPDATE_COMMAND_UI(ID_MOUSECONTROL_MOVE, OnUpdateMousecontrolMove)
	ON_UPDATE_COMMAND_UI(ID_MOUSECONTROL_ROTATE, OnUpdateMousecontrolRotate)
	ON_UPDATE_COMMAND_UI(ID_MOUSECONTROL_SCALE, OnUpdateMousecontrolScale)
	ON_UPDATE_COMMAND_UI(ID_MOUSECONTROL_BOXMOVE, OnUpdateMousecontrolBoxmove)
	ON_UPDATE_COMMAND_UI(ID_MOUSECONTROL_BOXSCALE, OnUpdateMousecontrolBoxscale)
	ON_UPDATE_COMMAND_UI(ID_MOUSECONTROL_BOXSELSCALE, OnUpdateMousecontrolBoxselscale)
	ON_UPDATE_COMMAND_UI(ID_MOUSECONTROL_DETECTOBJECT, OnUpdateMousecontrolDetectobject)
	ON_COMMAND(ID_RENDEROPTIONS_RENDERSPHERE, OnRenderoptionsRendersphere)
	ON_UPDATE_COMMAND_UI(ID_RENDEROPTIONS_RENDERSPHERE, OnUpdateRenderoptionsRendersphere)
	ON_COMMAND(ID_RENDEROPTIONS_RENDERCROWGENPOS, OnRenderoptionsRendercrowgenpos)
	ON_UPDATE_COMMAND_UI(ID_RENDEROPTIONS_RENDERCROWGENPOS, OnUpdateRenderoptionsRendercrowgenpos)
	ON_COMMAND(ID_SOUND_BGMSOUND, OnSoundBgmsound)
	ON_UPDATE_COMMAND_UI(ID_SOUND_BGMSOUND, OnUpdateSoundBgmsound)
	ON_COMMAND(ID_SOUND_ENVSOUND, OnSoundEnvsound)
	ON_UPDATE_COMMAND_UI(ID_SOUND_ENVSOUND, OnUpdateSoundEnvsound)
	ON_COMMAND(ID_SOUND_SFXSOUND, OnSoundSfxsound)
	ON_UPDATE_COMMAND_UI(ID_SOUND_SFXSOUND, OnUpdateSoundSfxsound)
	ON_COMMAND(ID_MOUSECONTROL_EFFMATRIXMOVE, OnMousecontrolEffmatrixmove)
	ON_COMMAND(ID_MOUSECONTROL_EFFMATRIXROTATE, OnMousecontrolEffmatrixrotate)
	ON_COMMAND(ID_MOUSECONTROL_EFFMATRIXSCALE, OnMousecontrolEffmatrixscale)
	ON_UPDATE_COMMAND_UI(ID_MOUSECONTROL_EFFMATRIXMOVE, OnUpdateMousecontrolEffmatrixmove)
	ON_UPDATE_COMMAND_UI(ID_MOUSECONTROL_EFFMATRIXROTATE, OnUpdateMousecontrolEffmatrixrotate)
	ON_UPDATE_COMMAND_UI(ID_MOUSECONTROL_EFFMATRIXSCALE, OnUpdateMousecontrolEffmatrixscale)
	ON_COMMAND(ID_FILE_OPENEX, OnFileOpenex)
END_MESSAGE_MAP()

// CRanEditLevelView construction/destruction

CRanEditLevelView::CRanEditLevelView() :
	CD3DApplication(),
	m_bCreated(FALSE),
	m_hCursorDefault(NULL),
	m_pGLLandServer( NULL ),
	m_pDxLandMan( NULL ),
	bRenderQuad( TRUE ),
	bRenderCrow( TRUE ),
	bRenderSched( TRUE ),
	bDebugInfo( TRUE ),
	bRenderGate( TRUE ),
	bRenderLandEff( TRUE ),
	bRenderCollisionSphere( FALSE ),
	bRenderGenPos( TRUE ),
	bEditNone( TRUE ),
	bEditDetect( FALSE ),
	emEditBox( DxEditBox::EM_MOVE ),
	emEditMat( TRANS_MAT ),
	nMRSMODE(0),
	bEditBOX( FALSE ),
	bEditMAT( FALSE ),
	bEditMRS( FALSE ),
	bSoundBGM( TRUE ),
	bSoundENV( TRUE ),
	bSoundSFX( TRUE ),
	pEffAdjust( NULL ),
	m_vPos( 0.0f, 0.0f, 0.0f )
{
	// TODO: add construction code here
	memset(szAppPath, 0, sizeof(char) * (MAX_PATH));

	m_bUseDepthBuffer	= TRUE;

}

CRanEditLevelView::~CRanEditLevelView()
{
}

BOOL CRanEditLevelView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CRanEditLevelView drawing

void CRanEditLevelView::OnDraw(CDC* /*pDC*/)
{
	//CRanEditLevelDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//if (!pDoc)
	//	return;

	// TODO: add draw code for native data here
}


// CRanEditLevelView printing

BOOL CRanEditLevelView::OnPreparePrinting(CPrintInfo* pInfo)
{
	// default preparation
	return DoPreparePrinting(pInfo);
}

void CRanEditLevelView::OnBeginPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add extra initialization before printing
}

void CRanEditLevelView::OnEndPrinting(CDC* /*pDC*/, CPrintInfo* /*pInfo*/)
{
	// TODO: add cleanup after printing
}


// CRanEditLevelView diagnostics

#ifdef _DEBUG
void CRanEditLevelView::AssertValid() const
{
	CView::AssertValid();
}

void CRanEditLevelView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

//CRanEditLevelDoc* CRanEditLevelView::GetDocument() const // non-debug version is inline
//{
//	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRanEditLevelDoc)));
//	return (CRanEditLevelDoc*)m_pDocument;
//}
#endif //_DEBUG


// CRanEditLevelView message handlers
CRanEditLevelView * CRanEditLevelView::GetView()
{
    CFrameWnd * pFrame = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);

    CView * pView = pFrame->GetActiveView();

    if ( !pView )
        return NULL;

    // Fail if view is of wrong kind
    // (this could occur with splitter windows, or additional
    // views on a single document
    if ( ! pView->IsKindOf( RUNTIME_CLASS(CRanEditLevelView) ) )
        return NULL;

    return (CRanEditLevelView *) pView;
}

void CRanEditLevelView::ResetToolTab()
{
	CMainFrame	*pMainFrame = (CMainFrame*) AfxGetMainWnd();
	if ( pMainFrame )
	{
		pMainFrame->ResetToolTab();
	}
}

void CRanEditLevelView::EnableSphere( bool bEnable )
{
	CRanEditLevelView::GetView()->bRenderCollisionSphere = bEnable;
}

void CRanEditLevelView::SetEffToAdjust( PLANDEFF pEff )
{
	if ( pEff )
	{
		pEffAdjust = pEff;
		m_DxEditMRS.SetMatrix( &pEffAdjust->m_matWorld );
		OnMousecontrolEffmatrixmove();
	}
	else
	{
		pEffAdjust = NULL;
		m_DxEditMRS.SetMatrix( NULL );
		OnMousecontrolNone();
	} 
}

void CRanEditLevelView::OnFileOpen()
{	
	CString szFilter = "lev|*.LEV|";
	CFileDialog dlg ( TRUE,".LEV",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter, this );
	dlg.m_ofn.lpstrInitialDir = GLOGIC::GetPath ();
	if ( dlg.DoModal() == IDOK )
	{
		GLLevelFile sLev;
		BOOL bOk = sLev.LoadFile ( dlg.GetFileName(), FALSE, m_pd3dDevice );
		if ( bOk )
		{
			SAFE_DELETE( m_pGLLandServer );
			SAFE_DELETE( m_pDxLandMan );

			m_pGLLandServer = new GLLandMan;
			m_pDxLandMan = new DxLandMan;

			m_pGLLandServer->SetD3dDevice( m_pd3dDevice );
			m_pGLLandServer->SetEmulator( TRUE );

			m_pGLLandServer->CleanUp();
			m_pDxLandMan->CleanUp();

			GLMobSchedule::m_bRENDACT = TRUE;

			BOOL bOK = m_pGLLandServer->LoadFile( dlg.GetFileName() );
			if ( !bOK )	
			{
				SAFE_DELETE( m_pGLLandServer );
				SAFE_DELETE( m_pDxLandMan );
				return;
			}

			bOK = m_pDxLandMan->LoadFile( m_pGLLandServer->GetWldFileName(), m_pd3dDevice, FALSE );
			if ( !bOK )
			{
				SAFE_DELETE( m_pGLLandServer );
				SAFE_DELETE( m_pDxLandMan );
				return;
			}

			m_pDxLandMan->ActiveMap();
			m_pDxLandMan->LoadBasicPos ( m_pd3dDevice, D3DXVECTOR3( 0.0f, 0.0f, 0.0f ));
			m_pDxLandMan->InitDeviceObjects ( m_pd3dDevice );
			m_pDxLandMan->RestoreDeviceObjects ( m_pd3dDevice );
			ResetToolTab();

			DxBgmSound::GetInstance().SetMute ( !bSoundBGM );
			DxSoundMan::GetInstance().SetMapMute ( !bSoundENV );
			DxSoundMan::GetInstance().SetSfxMute ( !bSoundSFX );

			CFrameWnd * pFrame = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);
			pFrame->SetWindowText( dlg.GetFileName() );
		}
	}
}

void CRanEditLevelView::OnFileSave()
{
	if ( m_pGLLandServer )
	{
		CString szFilter = "lev|*.LEV|";
		CFileDialog dlg ( false,".LEV",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter, this );
		dlg.m_ofn.lpstrInitialDir = GLOGIC::GetPath ();
		if ( dlg.DoModal() == IDOK )
		{
			BOOL bOk = m_pGLLandServer->SaveFile( dlg.GetFileName() );
			if ( bOk )
			{
				CFrameWnd * pFrame = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);
				pFrame->SetWindowText( dlg.GetFileName() );
				MessageBox( "Done Save File" );
			}else{
				MessageBox( "Error Save File" );
			}
		}
	}
}

void CRanEditLevelView::OnFileNew()
{
	SAFE_DELETE( m_pGLLandServer );
	SAFE_DELETE( m_pDxLandMan );

	m_pGLLandServer = new GLLandMan;
	m_pDxLandMan = new DxLandMan;

	m_pGLLandServer->SetD3dDevice( m_pd3dDevice );
	m_pGLLandServer->SetEmulator( TRUE );

	m_pGLLandServer->CleanUp();
	m_pDxLandMan->CleanUp();

	GLMobSchedule::m_bRENDACT = TRUE;

	m_pGLLandServer->InitDeviceObjects( m_pd3dDevice );
	m_pGLLandServer->RestoreDeviceObjects( m_pd3dDevice );
	m_pDxLandMan->ActiveMap();
	m_pDxLandMan->LoadBasicPos ( m_pd3dDevice, D3DXVECTOR3( 0.0f, 0.0f, 0.0f ));
	m_pDxLandMan->InitDeviceObjects ( m_pd3dDevice );
	m_pDxLandMan->RestoreDeviceObjects ( m_pd3dDevice );
	ResetToolTab();

	DxBgmSound::GetInstance().SetMute ( !bSoundBGM );
	DxSoundMan::GetInstance().SetMapMute ( !bSoundENV );
	DxSoundMan::GetInstance().SetSfxMute ( !bSoundSFX );
}

void CRanEditLevelView::OnCameracontrolsResetcamerapos()
{
	DxViewPort::GetInstance().CameraJump( D3DXVECTOR3( 0.0f, 0.0f, 0.0f ) );
}

void CRanEditLevelView::OnCameracontrolsCameraspeed300()
{
	DxViewPort::GetInstance().SetMoveVelocity( 300.0f );
}

void CRanEditLevelView::OnCameracontrolsCameraspeed600()
{
	DxViewPort::GetInstance().SetMoveVelocity( 600.0f );
}

void CRanEditLevelView::OnCameracontrolsCameraspeed900()
{
	DxViewPort::GetInstance().SetMoveVelocity( 900.0f );
}

void CRanEditLevelView::OnRenderoptionsRenderquadtree()
{
	bRenderQuad = !bRenderQuad;
}

void CRanEditLevelView::OnRenderoptionsRendercrowmodels()
{
	bRenderCrow = !bRenderCrow;
}

void CRanEditLevelView::OnRenderoptionsRendercrowsched()
{
	bRenderSched = !bRenderSched;
}

void CRanEditLevelView::OnRenderoptionsRenderdebuginfo()
{
	bDebugInfo = !bDebugInfo;
}

void CRanEditLevelView::OnUpdateRenderoptionsRenderquadtree(CCmdUI *pCmdUI)
{
	if ( pCmdUI )	pCmdUI->SetCheck( bRenderQuad );
}

void CRanEditLevelView::OnUpdateRenderoptionsRendercrowmodels(CCmdUI *pCmdUI)
{
	if ( pCmdUI )	pCmdUI->SetCheck( bRenderCrow );
}

void CRanEditLevelView::OnUpdateRenderoptionsRendercrowsched(CCmdUI *pCmdUI)
{
	if ( pCmdUI )	pCmdUI->SetCheck( bRenderSched );
}

void CRanEditLevelView::OnUpdateRenderoptionsRenderdebuginfo(CCmdUI *pCmdUI)
{
	if ( pCmdUI )	pCmdUI->SetCheck( bDebugInfo );
}

void CRanEditLevelView::OnRenderoptionsRendergate()
{
	bRenderGate = !bRenderGate;
}

void CRanEditLevelView::OnUpdateRenderoptionsRendergate(CCmdUI *pCmdUI)
{
	if ( pCmdUI )	pCmdUI->SetCheck( bRenderGate );
}

void CRanEditLevelView::OnRenderoptionsRenderlandeffect()
{
	bRenderLandEff = !bRenderLandEff;
}

void CRanEditLevelView::OnUpdateRenderoptionsRenderlandeffect(CCmdUI *pCmdUI)
{
	if ( pCmdUI )	pCmdUI->SetCheck( bRenderLandEff );
}

void CRanEditLevelView::OnWldWldload()
{
	CString szFilter = "WLD|*.wld|";
	CFileDialog dlg ( TRUE,".WLD",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter, this );
	dlg.m_ofn.lpstrInitialDir = DxLandMan::GetPath ();
	if ( dlg.DoModal() == IDOK )
	{
		SAFE_DELETE( m_pDxLandMan );
		m_pDxLandMan = new DxLandMan;
		BOOL bOK = m_pDxLandMan->LoadFile( dlg.GetFileName(), m_pd3dDevice, FALSE );
		if ( !bOK )
		{
			SAFE_DELETE( m_pDxLandMan );
			return;
		}

		m_pDxLandMan->ActiveMap();
		m_pDxLandMan->LoadBasicPos ( m_pd3dDevice, D3DXVECTOR3( 0.0f, 0.0f, 0.0f ));
		m_pDxLandMan->InitDeviceObjects ( m_pd3dDevice );
		m_pDxLandMan->RestoreDeviceObjects ( m_pd3dDevice );
	}
}

void CRanEditLevelView::OnWldWldsave()
{
	if ( m_pDxLandMan )
	{
		CString szFilter = "WLD|*.wld|";
		CFileDialog dlg ( TRUE,".WLD",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter, this );
		dlg.m_ofn.lpstrInitialDir = DxLandMan::GetPath ();

		if ( dlg.DoModal() == IDOK )
		{
			BOOL bOK = m_pDxLandMan->SaveFile( dlg.GetFileName() );
			if ( !bOK )
			{
				MessageBox( "Error Save WLD ");
			}
		}
	}
}

void CRanEditLevelView::LoadWLD( std::string strName )
{	
	SAFE_DELETE( m_pDxLandMan );

	m_pDxLandMan = new DxLandMan;
	m_pDxLandMan->CleanUp();

	GLMobSchedule::m_bRENDACT = TRUE;

	HRESULT	hr = S_OK;

	hr = m_pDxLandMan->LoadFile( strName.c_str(), m_pd3dDevice, FALSE );
	if ( FAILED(hr) )	
	{
		SAFE_DELETE( m_pDxLandMan );
		return;
	}

	m_pDxLandMan->ActiveMap();
	m_pDxLandMan->LoadBasicPos ( m_pd3dDevice, D3DXVECTOR3( 0.0f, 0.0f, 0.0f ));
	m_pDxLandMan->InitDeviceObjects ( m_pd3dDevice );
	m_pDxLandMan->RestoreDeviceObjects ( m_pd3dDevice );
	
	DxBgmSound::GetInstance().SetMute ( !bSoundBGM );
	DxSoundMan::GetInstance().SetMapMute ( !bSoundENV );
	DxSoundMan::GetInstance().SetSfxMute ( !bSoundSFX );
}

void CRanEditLevelView::OnWldWldclear()
{
	SAFE_DELETE( m_pDxLandMan );
}

void CRanEditLevelView::OnMousecontrolNone()
{
	bEditNone = true;
	bEditDetect = false;
	bEditMAT = false;
	bEditBOX = false;
	bEditMRS = false;
}

void CRanEditLevelView::OnMousecontrolMove()
{
	bEditNone = false;
	bEditDetect = false;
	bEditBOX = false;
	bEditMAT = true;
	bEditMRS = false;
	emEditMat = TRANS_MAT;
	m_DxEditMat.SetType( emEditMat );
}

void CRanEditLevelView::OnMousecontrolRotate()
{
	bEditNone = false;
	bEditDetect = false;
	bEditBOX = false;
	bEditMAT = true;
	bEditMRS = false;
	emEditMat = ROTATE_MAT;
	m_DxEditMat.SetType( emEditMat );
}

void CRanEditLevelView::OnMousecontrolScale()
{
	bEditNone = false;
	bEditDetect = false;
	bEditBOX = false;
	bEditMAT = true;
	bEditMRS = false;
	emEditMat = SCALE_MAT;
	m_DxEditMat.SetType( emEditMat );
}

void CRanEditLevelView::OnMousecontrolBoxmove()
{
	bEditNone = false;
	bEditDetect = false;
	bEditMAT = false;
	bEditBOX = true;
	bEditMRS = false;
	emEditBox = DxEditBox::EM_MOVE;
	m_DxEditBox.SetEdit( emEditBox );
}

void CRanEditLevelView::OnMousecontrolBoxscale()
{
	bEditNone = false;
	bEditDetect = false;
	bEditMAT = false;
	bEditBOX = true;
	bEditMRS = false;
	emEditBox = DxEditBox::EM_SCALE;
	m_DxEditBox.SetEdit( emEditBox );
}

void CRanEditLevelView::OnMousecontrolBoxselscale()
{
	bEditNone = false;
	bEditDetect = false;
	bEditMAT = false;
	bEditBOX = true;
	bEditMRS = false;
	emEditBox = DxEditBox::EM_SELECTSCALE;
	m_DxEditBox.SetEdit( emEditBox );
}

void CRanEditLevelView::OnMousecontrolDetectobject()
{
	bEditNone = false;
	bEditDetect = true;
	bEditMAT = false;
	bEditBOX = false;
	bEditMRS = false;
}

void CRanEditLevelView::OnUpdateMousecontrolNone(CCmdUI *pCmdUI)
{
	if ( pCmdUI )	pCmdUI->SetCheck( bEditNone && !bEditDetect );
}

void CRanEditLevelView::OnUpdateMousecontrolMove(CCmdUI *pCmdUI)
{
	if ( pCmdUI )	pCmdUI->SetCheck( ( bEditMAT && emEditMat==TRANS_MAT) );
}

void CRanEditLevelView::OnUpdateMousecontrolRotate(CCmdUI *pCmdUI)
{
	if ( pCmdUI )	pCmdUI->SetCheck( ( bEditMAT && emEditMat==ROTATE_MAT) );
}

void CRanEditLevelView::OnUpdateMousecontrolScale(CCmdUI *pCmdUI)
{
	if ( pCmdUI )	pCmdUI->SetCheck( ( bEditMAT && emEditMat==SCALE_MAT) );
}

void CRanEditLevelView::OnUpdateMousecontrolBoxmove(CCmdUI *pCmdUI)
{
	if ( pCmdUI )	pCmdUI->SetCheck( ( bEditBOX && emEditBox==DxEditBox::EM_MOVE) );
}

void CRanEditLevelView::OnUpdateMousecontrolBoxscale(CCmdUI *pCmdUI)
{
	if ( pCmdUI )	pCmdUI->SetCheck( ( bEditBOX && emEditBox==DxEditBox::EM_SCALE) );
}

void CRanEditLevelView::OnUpdateMousecontrolBoxselscale(CCmdUI *pCmdUI)
{
	if ( pCmdUI )	pCmdUI->SetCheck( ( bEditBOX && emEditBox==DxEditBox::EM_SELECTSCALE) );
}

void CRanEditLevelView::OnUpdateMousecontrolDetectobject(CCmdUI *pCmdUI)
{
	if ( pCmdUI )	pCmdUI->SetCheck( bEditDetect && !bEditNone );
}

void CRanEditLevelView::OnRenderoptionsRendersphere()
{
	bRenderCollisionSphere = !bRenderCollisionSphere;
	if (!bRenderCollisionSphere)
	{
	}
}

void CRanEditLevelView::OnUpdateRenderoptionsRendersphere(CCmdUI *pCmdUI)
{
	if ( pCmdUI )	pCmdUI->SetCheck( bRenderCollisionSphere );
}

void CRanEditLevelView::OnRenderoptionsRendercrowgenpos()
{
	bRenderGenPos = !bRenderGenPos;
}

void CRanEditLevelView::OnUpdateRenderoptionsRendercrowgenpos(CCmdUI *pCmdUI)
{
	if ( pCmdUI )	pCmdUI->SetCheck( bRenderGenPos );
}

void CRanEditLevelView::OnSoundBgmsound()
{
	bSoundBGM = !bSoundBGM;
	DxBgmSound::GetInstance().SetMute ( !bSoundBGM );
}

void CRanEditLevelView::OnUpdateSoundBgmsound(CCmdUI *pCmdUI)
{
	if ( pCmdUI )	pCmdUI->SetCheck( bSoundBGM );
}

void CRanEditLevelView::OnSoundEnvsound()
{
	bSoundENV = !bSoundENV;
	DxSoundMan::GetInstance().SetMapMute ( !bSoundENV );
}

void CRanEditLevelView::OnUpdateSoundEnvsound(CCmdUI *pCmdUI)
{
	if ( pCmdUI )	pCmdUI->SetCheck( bSoundENV );
}

void CRanEditLevelView::OnSoundSfxsound()
{
	bSoundSFX = !bSoundSFX;
	DxSoundMan::GetInstance().SetSfxMute ( !bSoundSFX );
}

void CRanEditLevelView::OnUpdateSoundSfxsound(CCmdUI *pCmdUI)
{
	if ( pCmdUI )	pCmdUI->SetCheck( bSoundSFX );
}

void CRanEditLevelView::OnMousecontrolEffmatrixmove()
{
	if ( pEffAdjust )
	{
		bEditNone = false;
		bEditDetect = false;
		bEditMAT = false;
		bEditBOX = false;
		bEditMRS = true;
		nMRSMODE = OBECTMRS_M;
		m_DxEditMRS.SetMode( nMRSMODE );
		DxViewPort::GetInstance().CameraJump( m_DxEditMRS.GetPosition() );
	}
}

void CRanEditLevelView::OnMousecontrolEffmatrixrotate()
{
	if ( pEffAdjust )
	{
		bEditNone = false;
		bEditDetect = false;
		bEditMAT = false;
		bEditBOX = false;
		bEditMRS = true;
		nMRSMODE = OBECTMRS_R;
		m_DxEditMRS.SetMode( nMRSMODE );
		DxViewPort::GetInstance().CameraJump( m_DxEditMRS.GetPosition() );
	}
}

void CRanEditLevelView::OnMousecontrolEffmatrixscale()
{
	if ( pEffAdjust )
	{
		bEditNone = false;
		bEditDetect = false;
		bEditMAT = false;
		bEditBOX = false;
		bEditMRS = true;
		nMRSMODE = OBECTMRS_S;
		m_DxEditMRS.SetMode( nMRSMODE );
		DxViewPort::GetInstance().CameraJump( m_DxEditMRS.GetPosition() );
	}
}

void CRanEditLevelView::OnUpdateMousecontrolEffmatrixmove(CCmdUI *pCmdUI)
{
	if ( pCmdUI )	pCmdUI->SetCheck( ( pEffAdjust && bEditMRS && m_DxEditMRS.GetMode()==OBECTMRS_M) );
}

void CRanEditLevelView::OnUpdateMousecontrolEffmatrixrotate(CCmdUI *pCmdUI)
{
	if ( pCmdUI )	pCmdUI->SetCheck( ( pEffAdjust && bEditMRS && m_DxEditMRS.GetMode()==OBECTMRS_R) );
}

void CRanEditLevelView::OnUpdateMousecontrolEffmatrixscale(CCmdUI *pCmdUI)
{
	if ( pCmdUI )	pCmdUI->SetCheck( ( pEffAdjust && bEditMRS && m_DxEditMRS.GetMode()==OBECTMRS_S) );
}

void CRanEditLevelView::OnFileOpenex()
{
	std::string strLEV = "";
	std::string strWLD = "";

	{
		CString szFilter = "lev|*.LEV|";
		CFileDialog dlg ( TRUE,".LEV",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter, this );
		dlg.m_ofn.lpstrInitialDir = GLOGIC::GetPath ();
		if ( dlg.DoModal() == IDOK )	strLEV = dlg.GetFileName();
	}

	{
		CString szFilter = "WLD|*.wld|";
		CFileDialog dlg ( TRUE,".WLD",NULL,OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter, this );
		dlg.m_ofn.lpstrInitialDir = DxLandMan::GetPath ();
		if ( dlg.DoModal() == IDOK )	strWLD = dlg.GetFileName();
	}

	if ( strLEV.size() == 0 || strWLD.size() == 0 )
		return;

	SAFE_DELETE( m_pGLLandServer );
	SAFE_DELETE( m_pDxLandMan );

	m_pGLLandServer = new GLLandMan;
	m_pDxLandMan = new DxLandMan;

	m_pGLLandServer->SetD3dDevice( m_pd3dDevice );
	m_pGLLandServer->SetEmulator( TRUE );

	m_pGLLandServer->CleanUp();
	m_pDxLandMan->CleanUp();

	GLMobSchedule::m_bRENDACT = TRUE;

	BOOL bOK = m_pGLLandServer->LoadFile( strLEV.c_str(), strWLD.c_str() );
	if ( !bOK )	
	{
		SAFE_DELETE( m_pGLLandServer );
		SAFE_DELETE( m_pDxLandMan );
		return;
	}

	bOK = m_pDxLandMan->LoadFile( strWLD.c_str(), m_pd3dDevice, FALSE );
	if ( !bOK )
	{
		SAFE_DELETE( m_pGLLandServer );
		SAFE_DELETE( m_pDxLandMan );
		return;
	}

	m_pDxLandMan->ActiveMap();
	m_pDxLandMan->LoadBasicPos ( m_pd3dDevice, D3DXVECTOR3( 0.0f, 0.0f, 0.0f ));
	m_pDxLandMan->InitDeviceObjects ( m_pd3dDevice );
	m_pDxLandMan->RestoreDeviceObjects ( m_pd3dDevice );
	ResetToolTab();

	DxBgmSound::GetInstance().SetMute ( !bSoundBGM );
	DxSoundMan::GetInstance().SetMapMute ( !bSoundENV );
	DxSoundMan::GetInstance().SetSfxMute ( !bSoundSFX );

	CFrameWnd * pFrame = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);
	pFrame->SetWindowText( strLEV.c_str() );
}
