// RanEditLevelView.h : interface of the CRanEditLevelView class
//

#include "D3DApp.h"
#include "GLLandMan.h"
#include "DxLandMan.h"
#include "DxSkinChar.h"

#include "DxEditBox.h"
#include "DxEditMat.h"
#include "DxObjectMRS.h"

#pragma once


class CRanEditLevelView : public CView, public CD3DApplication
{
protected: // create from serialization only
	CRanEditLevelView();
	DECLARE_DYNCREATE(CRanEditLevelView)

// Attributes
public:
	//CRanEditLevelDoc* GetDocument() const;
	static				CRanEditLevelView * GetView();
// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:
	virtual BOOL OnPreparePrinting(CPrintInfo* pInfo);
	virtual void OnBeginPrinting(CDC* pDC, CPrintInfo* pInfo);
	virtual void OnEndPrinting(CDC* pDC, CPrintInfo* pInfo);

// Implementation
public:
	virtual ~CRanEditLevelView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif


private:
	char	szAppPath[MAX_PATH];
	BOOL	m_bCreated;
	HCURSOR	m_hCursorDefault;

public:
	GLLandMan*		m_pGLLandServer;	
	DxLandMan*		m_pDxLandMan;

public:
	BOOL bRenderQuad;
	BOOL bRenderCrow;
	BOOL bRenderSched;
	BOOL bRenderGate;
	BOOL bRenderLandEff;
	BOOL bRenderCollisionSphere;
	BOOL bRenderGenPos;
	BOOL bDebugInfo;

	DxEditBox		m_DxEditBox;
	DxEditMat		m_DxEditMat;
	DxObjectMRS		m_DxEditMRS;


	BOOL bSoundBGM;
	BOOL bSoundENV;
	BOOL bSoundSFX;

	BOOL	bEditNone;
	BOOL	bEditDetect;
	BOOL	bEditBOX;
	BOOL	bEditMAT;
	BOOL	bEditMRS;

	DxEditBox::EMEDIT	emEditBox;
	EDITMAT_TYPE	emEditMat;
	int				nMRSMODE;

	D3DXVECTOR3		m_vPos;

protected:
	PLANDEFF pEffAdjust;

public:
	LPDIRECT3DDEVICEQ Get3DDevice()	{	return m_pd3dDevice;	}

public:
	void SetActive ( BOOL bActive );

	HRESULT ReSizeWindow ( int cx, int cy )
	{
		if ( cx < 10 )	cx = 10;
		if ( cy < 10 )	cy = 10;

		m_d3dpp.BackBufferWidth  = cx;
		m_d3dpp.BackBufferHeight = cy;

		return Resize3DEnvironment();
	}

	HRESULT OneTimeSceneInit();
	HRESULT ConfirmDevice( D3DCAPSQ*,DWORD,D3DFORMAT );
	HRESULT CreateObjects();
	HRESULT InitDeviceObjects();
	HRESULT FrameMove();
	HRESULT Render();
	HRESULT RenderText();
	HRESULT InvalidateDeviceObjects();
	HRESULT RestoreDeviceObjects();
	HRESULT DeleteDeviceObjects();
	HRESULT FinalCleanup();

public:
	virtual void OnInitialUpdate();
	virtual HRESULT FrameMove3DEnvironment();
	virtual HRESULT Render3DEnvironment();

protected:
	virtual void PostNcDestroy();
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);

public:
	void	ResetToolTab();
	void	EnableSphere( bool bEnable );
	void	SetEffToAdjust( PLANDEFF pEff );
	void	LoadWLD( std::string strName );
// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);	
	afx_msg void OnFileOpen();
	afx_msg void OnFileSave();
	afx_msg void OnFileNew();
	afx_msg void OnCameracontrolsResetcamerapos();
	afx_msg void OnCameracontrolsCameraspeed300();
	afx_msg void OnCameracontrolsCameraspeed600();
	afx_msg void OnCameracontrolsCameraspeed900();
	afx_msg void OnRenderoptionsRenderquadtree();
	afx_msg void OnRenderoptionsRendercrowmodels();
	afx_msg void OnRenderoptionsRendercrowsched();
	afx_msg void OnRenderoptionsRenderdebuginfo();
	afx_msg void OnUpdateRenderoptionsRenderquadtree(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRenderoptionsRendercrowmodels(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRenderoptionsRendercrowsched(CCmdUI *pCmdUI);
	afx_msg void OnUpdateRenderoptionsRenderdebuginfo(CCmdUI *pCmdUI);
	afx_msg void OnRenderoptionsRendergate();
	afx_msg void OnUpdateRenderoptionsRendergate(CCmdUI *pCmdUI);
	afx_msg void OnRenderoptionsRenderlandeffect();
	afx_msg void OnUpdateRenderoptionsRenderlandeffect(CCmdUI *pCmdUI);
	afx_msg void OnWldWldload();
	afx_msg void OnWldWldsave();
	afx_msg void OnWldWldclear();
	afx_msg void OnMousecontrolNone();
	afx_msg void OnMousecontrolMove();
	afx_msg void OnMousecontrolRotate();
	afx_msg void OnMousecontrolScale();
	afx_msg void OnMousecontrolBoxmove();
	afx_msg void OnMousecontrolBoxscale();
	afx_msg void OnMousecontrolBoxselscale();
	afx_msg void OnMousecontrolDetectobject();
	afx_msg void OnUpdateMousecontrolNone(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMousecontrolMove(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMousecontrolRotate(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMousecontrolScale(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMousecontrolBoxmove(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMousecontrolBoxscale(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMousecontrolBoxselscale(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMousecontrolDetectobject(CCmdUI *pCmdUI);
	afx_msg void OnRenderoptionsRendersphere();
	afx_msg void OnUpdateRenderoptionsRendersphere(CCmdUI *pCmdUI);
	afx_msg void OnRenderoptionsRendercrowgenpos();
	afx_msg void OnUpdateRenderoptionsRendercrowgenpos(CCmdUI *pCmdUI);
	afx_msg void OnSoundBgmsound();
	afx_msg void OnUpdateSoundBgmsound(CCmdUI *pCmdUI);
	afx_msg void OnSoundEnvsound();
	afx_msg void OnUpdateSoundEnvsound(CCmdUI *pCmdUI);
	afx_msg void OnSoundSfxsound();
	afx_msg void OnUpdateSoundSfxsound(CCmdUI *pCmdUI);
	afx_msg void OnMousecontrolEffmatrixmove();
	afx_msg void OnMousecontrolEffmatrixrotate();
	afx_msg void OnMousecontrolEffmatrixscale();
	afx_msg void OnUpdateMousecontrolEffmatrixmove(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMousecontrolEffmatrixrotate(CCmdUI *pCmdUI);
	afx_msg void OnUpdateMousecontrolEffmatrixscale(CCmdUI *pCmdUI);
	afx_msg void OnFileOpenex();
};

//#ifndef _DEBUG  // debug version in RanEditLevelView.cpp
//inline CRanEditLevelDoc* CRanEditLevelView::GetDocument() const
//   { return reinterpret_cast<CRanEditLevelDoc*>(m_pDocument); }
//#endif

