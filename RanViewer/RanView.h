// RanView.h : interface of the CRanView class
//
#include "D3DApp.h"
#include "DxSkinChar.h"
#include "DxSkinPieceRootData.h"
#include "DxSkinPieceContainer.h"
#include "./dxeffchardata.h"
#include "DxTaregetEffect.h"

#pragma once


class CRanView : public CView, public CD3DApplication
{
protected:
	DxSkinChar*			m_pSkinChar;

public:
	D3DXVECTOR3			m_vMaxOrg;
	D3DXVECTOR3			m_vMinOrg;
	D3DXVECTOR3			m_vMax;
	D3DXVECTOR3			m_vMin;
	float				m_fHeight;
	D3DXVECTOR3			m_vDir;
	D3DXVECTOR3			m_vDirOrig;
	D3DXVECTOR3			m_vPos;
	D3DXMATRIX			m_matTrans;
	D3DXVECTOR3			m_vMousePos;

	char				szAppPath[MAX_PATH];

	EMANI_MAINTYPE		m_AniMain;
	EMANI_SUBTYPE		m_AniSub;
	EMANI_MAINTYPE		m_ABLAniMain;
	EMANI_SUBTYPE		m_ABLAniSub;
	EMANI_MAINTYPE		m_VCFAniMain;
	EMANI_SUBTYPE		m_VCFAniSub;
	DWORD				dwAniSelect;
	bool				bSAttack;
	int					nGrind;

	void				SetAnim( int nType, int nMain , int nSub ,bool bAttack);
	void				SetGrind( int nLevel );

	void				EditMatrix ( int nKey );
	int					nEditType;
	int					nEditPiece;
	int					nEditMode;
	int					nEditStance;
	float				fDevider;

	void				SetType ( int nType ) { nEditType = nType; }
	void				SetPieceType ( int nPiece ) { nEditPiece = nPiece; }
	void				SetMode ( int nMode ) { nEditMode = nMode; }
	void				SetStance ( int nStance ) { nEditStance = nStance; }
	void				SetDevider ( int nDevide );
	void				SetColor ( int nType, WORD wColor );
	//void				SetUpgradeEffect ( int nType , int nSex );

	static				CRanView * GetView();



private:
	BOOL		m_bCreated;
	CString		m_strCHF;
	HCURSOR		m_hCursorDefault;

private:
	HRESULT ConfirmDevice( D3DCAPSQ*,DWORD,D3DFORMAT );
	HRESULT OneTimeSceneInit();
	HRESULT CreateObjects();
	HRESULT InitDeviceObjects();	
	HRESULT RestoreDeviceObjects();
	HRESULT FrameMove();
	HRESULT Render();
	HRESULT InvalidateDeviceObjects();
	HRESULT DeleteDeviceObjects();
	HRESULT FinalCleanup();

	HRESULT RenderText();
	HRESULT ReSizeWindow ( int cx, int cy )
	{
		if ( cx < 10 )	cx = 10;
		if ( cy < 10 )	cy = 10;

		m_d3dpp.BackBufferWidth  = cx;
		m_d3dpp.BackBufferHeight = cy;

		return Resize3DEnvironment();
	}

public:
	void SetActive ( BOOL bActive );
	void UpdateAnimation();

public:
	virtual HRESULT FrameMove3DEnvironment();
	virtual HRESULT Render3DEnvironment();
	HRESULT SkinLoad ( LPDIRECT3DDEVICEQ pd3dDevice, const char* szFile );

protected: // create from serialization only
	CRanView();
	DECLARE_DYNCREATE(CRanView)

// Attributes
//public:
//	CRanDoc* GetDocument() const;

// Operations
public:

// Overrides
	public:
	virtual void OnDraw(CDC* pDC);  // overridden to draw this view
virtual BOOL PreCreateWindow(CREATESTRUCT& cs);
protected:

// Implementation
public:
	virtual ~CRanView();
#ifdef _DEBUG
	virtual void AssertValid() const;
	virtual void Dump(CDumpContext& dc) const;
#endif

protected:

// Generated message map functions
protected:
	DECLARE_MESSAGE_MAP()

public:
	virtual void OnInitialUpdate();
protected:
	virtual void PostNcDestroy();
	virtual void OnActivateView(BOOL bActivate, CView* pActivateView, CView* pDeactiveView);
public:
	afx_msg void OnSize(UINT nType, int cx, int cy);
	afx_msg BOOL OnSetCursor(CWnd* pWnd, UINT nHitTest, UINT message);	

	afx_msg void CHFLOAD();
	afx_msg void OnChfDefaultmale();
	afx_msg void OnChfDefaultfemale();
	afx_msg void OnChfApplypiece();
	afx_msg void OnChfApplyablnormal();
	afx_msg void OnChfApplyablleft();
	afx_msg void OnChfApplyablright();
	afx_msg void OnChfApplyvcf();
	afx_msg void OnChfClearpiece();
	afx_msg void OnChfApplyvcfpiece();
	afx_msg void OnChfApplybothhandabl();
	afx_msg void OnCameraResetcamera();
};

//#ifndef _DEBUG  // debug version in RanView.cpp
//inline CRanDoc* CRanView::GetDocument() const
//   { return reinterpret_cast<CRanDoc*>(m_pDocument); }
//#endif

