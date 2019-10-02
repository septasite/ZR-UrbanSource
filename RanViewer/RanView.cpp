// RanView.cpp : implementation of the CRanView class
//

#include "stdafx.h"
#include "RanViewer.h"

#include "RanDoc.h"
#include "RanView.h"

#include "DxGlobalStage.h"
#include "GLogicData.h"
#include "GLogic.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CRanView

IMPLEMENT_DYNCREATE(CRanView, CView)

BEGIN_MESSAGE_MAP(CRanView, CView)
	ON_COMMAND(ID__LOAD, CHFLOAD)
	ON_WM_SETCURSOR()
	ON_WM_SIZE()
	ON_COMMAND(ID_CHF_DEFAULTMALE, OnChfDefaultmale)
	ON_COMMAND(ID_CHF_DEFAULTFEMALE, OnChfDefaultfemale)
	ON_COMMAND(ID_CHF_APPLYPIECE, OnChfApplypiece)
	ON_COMMAND(ID_CHF_APPLYABLNORMAL, OnChfApplyablnormal)
	ON_COMMAND(ID_CHF_APPLYABLLEFT, OnChfApplyablleft)
	ON_COMMAND(ID_CHF_APPLYABLRIGHT, OnChfApplyablright)
	ON_COMMAND(ID_CHF_APPLYVCF, OnChfApplyvcf)
	ON_COMMAND(ID_CHF_CLEARPIECE, OnChfClearpiece)
	ON_COMMAND(ID_CHF_APPLYVCFPIECE, OnChfApplyvcfpiece)
	ON_COMMAND(ID_CHF_APPLYBOTHHANDABL, OnChfApplybothhandabl)
	ON_COMMAND(ID_CAMERA_RESETCAMERA, OnCameraResetcamera)
END_MESSAGE_MAP()

// CRanView construction/destruction

CRanView::CRanView():
	CD3DApplication(),
	m_bCreated(FALSE),
	m_hCursorDefault(NULL),
	m_pSkinChar(NULL),
	dwAniSelect(0),
	bSAttack(false),
	nGrind(5),
	nEditType(0),
	nEditPiece(0),
	nEditMode(0),
	nEditStance(0),
	fDevider(1)
{
	m_bUseDepthBuffer	= TRUE;
	GLOGIC::bGLOGIC_PACKFILE = FALSE;
	GLOGIC::bGLOGIC_ZIPFILE = TRUE;
	GLOGIC::bENGLIB_ZIPFILE = FALSE;

	D3DXMatrixIdentity ( &m_matTrans );

	m_AniMain = AN_PLACID;
	m_AniSub = AN_SUB_NONE;
	m_ABLAniMain = ANI_ABL_STAY;
	m_ABLAniSub = AN_SUB_NONE;
	m_VCFAniMain = ANI_VEHICLE_STAY;
	m_VCFAniSub = AN_SUB_NONE;

	nEditType = 0;
	nEditPiece = 0;
}

CRanView::~CRanView()
{
}

BOOL CRanView::PreCreateWindow(CREATESTRUCT& cs)
{
	// TODO: Modify the Window class or styles here by modifying
	//  the CREATESTRUCT cs

	return CView::PreCreateWindow(cs);
}

// CRanView drawing

void CRanView::OnDraw(CDC* /*pDC*/)
{
	//CRanDoc* pDoc = GetDocument();
	//ASSERT_VALID(pDoc);
	//if (!pDoc)
	//	return;

	// TODO: add draw code for native data here
}


// CRanView diagnostics

#ifdef _DEBUG
void CRanView::AssertValid() const
{
	CView::AssertValid();
}

void CRanView::Dump(CDumpContext& dc) const
{
	CView::Dump(dc);
}

//CRanDoc* CRanView::GetDocument() const // non-debug version is inline
//{
//	ASSERT(m_pDocument->IsKindOf(RUNTIME_CLASS(CRanDoc)));
//	return (CRanDoc*)m_pDocument;
//}
#endif //_DEBUG


// CRanView message handlers
CRanView * CRanView::GetView()
{
    CFrameWnd * pFrame = (CFrameWnd *)(AfxGetApp()->m_pMainWnd);

    CView * pView = pFrame->GetActiveView();

    if ( !pView )
        return NULL;

    // Fail if view is of wrong kind
    // (this could occur with splitter windows, or additional
    // views on a single document
    if ( ! pView->IsKindOf( RUNTIME_CLASS(CRanView) ) )
        return NULL;

    return (CRanView *) pView;
}