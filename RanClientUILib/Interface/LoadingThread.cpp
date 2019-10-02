#include "StdAfx.h"
#include <process.h>
#include "LoadingThread.h"

#include "SubPath.h"
#include "DxGrapUtils.h"
#include "DxResponseMan.h"
#include "UITextControl.h"
#include "GameTextControl.h"
#include "./InnerInterface.h"
#include "d3dfont.h"

#include "..\ranclientlib\dxglobalstage.h"
#include "..\enginelib\Common\BaseString.h"
#include "..\ranclientlib\g-logic\glogicdata.h"



#include "../../EngineLib/DxCommon/TextureManager.h"
#include "../../EngineLib/DxCommon/DxFontMan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

using namespace NLOADINGTHREAD;
std::vector<CString> m_vecMESSAGE2;
int nIndex = NULL;
int MAX_INDEX =NULL;

//	-------------------- [ CUSTOM VERTEX ¼³Á¤ ] --------------------
const	DWORD TEXTUREVERTEXFVF2 = D3DFVF_XYZRHW | D3DFVF_DIFFUSE | D3DFVF_TEX1;
struct TEXTUREVERTEX2
{
	union
	{
		struct { D3DXVECTOR4 vPos; };
		struct { float x, y, z, rhw; };
	};

	DWORD Diffuse;

	union
	{
		struct { D3DXVECTOR2 vUV; };
		struct { float tu, tv; };
	};

	TEXTUREVERTEX2 () :
		x(0.0f),
		y(0.0f),
		z(0.0f),
		rhw(1.0f),
		Diffuse(0xFFFFFFFF),
		tu(0.0f),
		tv(0.0f)
	{		
	}

	TEXTUREVERTEX2 ( float _x, float _y, float _tu, float _tv ) :
		x(_x),
		y(_y),
		z(0.0f),
		rhw(1.0f),
		Diffuse(0xFFFFFFFF),
		tu(_tu),
		tv(_tv)
	{		
	}

	void	SetPos ( float _x, float _y )
	{
		x = _x;
		y = _y;
	}

	void	SetTexPos ( float _tu, float _tv )
	{
		tu = _tu;
		tv = _tv;
	}
};


//	-------------------- [ CUSTOM VERTEX Á¦¾î ¸Þ¼Òµå ¼³Á¤ ] --------------------

static HRESULT	CreateVB ( LPDIRECT3DDEVICEQ pd3dDevice, LPDIRECT3DVERTEXBUFFERQ& pTextureVB, TEXTUREVERTEX2 VertexArray[6] )
{	
	HRESULT hr = S_OK;
	hr = pd3dDevice->CreateVertexBuffer( 6*sizeof(TEXTUREVERTEX2), 0, TEXTUREVERTEXFVF2,
											D3DPOOL_MANAGED, &pTextureVB, NULL );
    if( FAILED ( hr ) )	return hr;    

    VOID* pVertices;
	hr = pTextureVB->Lock( 0, sizeof ( TEXTUREVERTEX2 ) * 6, (VOID**)&pVertices, 0 );
    if( FAILED ( hr ) ) return hr;

    memmove( pVertices, VertexArray, sizeof ( TEXTUREVERTEX2 ) * 6 );

    hr = pTextureVB->Unlock();
	if ( FAILED ( hr ) ) return hr;

	return S_OK;
}

static void SetVertexPos ( TEXTUREVERTEX2 VertexArray[6], float LEFT, float TOP, float SIZEX, float SIZEY )
{
	float RIGHT = LEFT + SIZEX;
	float BOTTOM = TOP + SIZEY;

	VertexArray[0].SetPos ( LEFT,	TOP );
	VertexArray[1].SetPos ( RIGHT,	TOP);
	VertexArray[2].SetPos ( LEFT,	BOTTOM );

	VertexArray[3].SetPos ( LEFT,	BOTTOM );
	VertexArray[4].SetPos ( RIGHT,	TOP);
	VertexArray[5].SetPos ( RIGHT,	BOTTOM );
}

static void SetTexturePos ( TEXTUREVERTEX2 VertexArray[6], float LEFT, float TOP, float SIZEX, float SIZEY, float TEX_SIZEX, float TEX_SIZEY )
{
	float RIGHT = LEFT + SIZEX;
	float BOTTOM = TOP + SIZEY;

	VertexArray[0].SetTexPos ( LEFT / TEX_SIZEX,	TOP / TEX_SIZEY );
	VertexArray[1].SetTexPos ( RIGHT / TEX_SIZEX,	TOP / TEX_SIZEY);
	VertexArray[2].SetTexPos ( LEFT / TEX_SIZEX,	BOTTOM / TEX_SIZEY );

	VertexArray[3].SetTexPos ( LEFT / TEX_SIZEX,	BOTTOM / TEX_SIZEY );
	VertexArray[4].SetTexPos ( RIGHT / TEX_SIZEX,	TOP / TEX_SIZEY );
	VertexArray[5].SetTexPos ( RIGHT / TEX_SIZEX,	BOTTOM / TEX_SIZEY );
}

static HRESULT Render ( LPDIRECT3DDEVICEQ pd3dDevice, LPDIRECT3DTEXTUREQ pLoadingTexture, LPDIRECT3DVERTEXBUFFERQ pTextureVB )
{
	HRESULT hr = S_OK;

	hr = pd3dDevice->SetTexture ( 0, pLoadingTexture );
	if ( FAILED ( hr ) ) return hr;

    hr = pd3dDevice->SetStreamSource( 0, pTextureVB, 0, sizeof(TEXTUREVERTEX2) );
	if ( FAILED ( hr ) ) return hr;

	hr = pd3dDevice->SetFVF( TEXTUREVERTEXFVF2 );
	if ( FAILED ( hr ) ) return hr;

	hr = pd3dDevice->DrawPrimitive( D3DPT_TRIANGLELIST, 0, 2 );
	if ( FAILED ( hr ) ) return hr;

	hr = pd3dDevice->SetTexture ( 0, NULL );
	if ( FAILED ( hr ) ) return hr;

	return S_OK;
}

struct Vertex
{
	float x, y, z;
	float tu, tv;
};

Vertex g_quadVertices[] =
{
	{-1.0f, 1.0f, 0.0f,  0.0f,0.0f },
	{ 1.0f, 1.0f, 0.0f,  1.0f,0.0f },
	{-1.0f,-1.0f, 0.0f,  0.0f,1.0f },
	{ 1.0f,-1.0f, 0.0f,  1.0f,1.0f }
};

BOOL MessagePump()
{
   MSG msg;

   while(::PeekMessage(&msg, NULL, 0, 0, PM_NOREMOVE))
   {
       if(AfxGetApp() -> PumpMessage())
       {
             ::PostQuitMessage(0);
             return FALSE;
       }
   }

   return TRUE;
}

unsigned int WINAPI	LoadingThread( LPVOID pData )
{

	if(n_mapname.IsEmpty() || n_strTextureName.IsEmpty() || n_strTextureName == _T("null"))
	{
	n_strTextureName.Format( "loading_000.dds", nIndex );	
	}

	TCHAR szTexture[256] = {0};
	StringCchPrintf ( szTexture, 256, n_strTextureName.GetString(), n_szAppPath, SUBPATH::TEXTURE_FILE_ROOT );

	LPDIRECT3DDEVICEQ& pd3dDevice = *n_ppd3dDevice;
	LPDIRECT3DTEXTUREQ pLoadingTexture = NULL;
	LPDIRECT3DTEXTUREQ pdds = NULL;
	LPDIRECT3DTEXTUREQ beijingtu = NULL;
	LPDIRECT3DTEXTUREQ pOVER15Tex = NULL;
	LPDIRECT3DTEXTUREQ pCopyRightTex = NULL;
	LPDIRECT3DTEXTUREQ mapnameds = NULL;
	LPDIRECT3DTEXTUREQ xiaotu = NULL;

	LPDIRECT3DTEXTUREQ pTopImageTex = NULL;
	LPDIRECT3DTEXTUREQ pBotImageTex = NULL;

	LPDIRECT3DVERTEXBUFFER9 g_pVB         = NULL; 
	LPD3DXSPRITE pSprite = NULL;    // ¾«Áé
	int          tupian = NULL;


	HRESULT hr = S_OK;
	std::string	  m_strNumberTEX = "loading_st.dds"; //Ðý×ªÍ¼
	std::string   m_strName  = "ld_back.dds";
	std::string   m_mapname  ="mapnameback.dds";
	std::string   m_xiaotu  ="HintIcon.dds";

	std::string   m_ldtop  ="ld_top.dds";
	std::string   m_ldbot  ="ld_under.dds";

	hr = TextureManager::LoadTexture( szTexture, pd3dDevice, pLoadingTexture, 0, 0 );
    hr = TextureManager::LoadTexture(m_strNumberTEX.c_str(), pd3dDevice, pdds, 0, 0);
	hr = TextureManager::LoadTexture(m_strName.c_str(), pd3dDevice, beijingtu, 0, 0);
	hr = TextureManager::LoadTexture(m_mapname.c_str(), pd3dDevice, mapnameds, 0, 0);
	hr = TextureManager::LoadTexture(m_xiaotu.c_str(), pd3dDevice, xiaotu, 0, 0);
	hr = TextureManager::LoadTexture(m_ldtop.c_str(), pd3dDevice, pTopImageTex, 0, 0 );
	hr = TextureManager::LoadTexture(m_ldbot.c_str(), pd3dDevice, pBotImageTex, 0, 0 );
	
	//MessageBoxA(NULL,n_strTextureName,0,0);

	if ( FAILED ( hr ) )
	{		
		DeWait ();
		n_ExitState = eERROR;
		return 0;
	}

	std::string szOver15Name = "OVER15.tga";
	
	if ( n_bOVER15 )
	{
		hr = TextureManager::LoadTexture( szOver15Name.c_str(), pd3dDevice, pOVER15Tex, 0, 0 );

		if ( FAILED ( hr ) )
		{		
			DeWait ();
			n_ExitState = eERROR;
			return 0;
		}
	}

	///////////////////////////////////////////////////////////////////////////////
	//	[TOGGLE SWITCH] ÅØ½ºÃÄ ·Îµù¿Ï·á
	DeWait ();
	///////////////////////////////////////////////////////////////////////////////

	RECT rect;
	GetClientRect ( n_hWnd, &rect );
	const float fWidth = float(rect.right - rect.left);
	const float fHeight = float(rect.bottom - rect.top);

	const float	fRealImageX = 1024.0f;
	const float	fRealImageY = 768.0f;
	const float	fImageSize = 1023.0f;

	const float fWidthRatio = fRealImageX / fImageSize;
	const float fHeightRatio = fRealImageY / fImageSize;

	const float LeftPos  = 0.0f;
	const float TopPos   = 0.0f;
	const float RightPos = fWidth;
	const float BottomPos= fHeight;

	float ROOT_LEFT		= LeftPos;
	float ROOT_TOP		= TopPos;
	float ROOT_SIZEX	= fWidth;
	float ROOT_SIZEY	= fHeight;

	const D3DXVECTOR2 vProgressBarTex ( 0, 769 );
	const D3DXVECTOR2 TextureRenderPos ( 215, 584 );


	const D3DXVECTOR2 vOver15 ( 940, 20 );
	const D3DXVECTOR2 vOver15Size ( 64, 64 );
	const D3DXVECTOR2 SizeTopAndBot ( fWidth, 256 );

	const D3DXVECTOR2 SizeLoadingMap ( fWidth, fHeight - 280 );

	const D3DXVECTOR2 vOver15Tex ( 0, 0 );	
	const D3DXVECTOR2 vOver15_800 ( 716, 20 );
	const D3DXVECTOR2 vProgressBarSize( 616,200);
	const D3DXVECTOR2 BackNameImage(350,80);

	D3DXVECTOR2 MapNamePosition;
	MapNamePosition.x = (fWidth/2) - 180;
	MapNamePosition.y = 70;

	D3DXVECTOR2 vProgressBarAlignSize;
	vProgressBarAlignSize.x = static_cast<float>(floor(vProgressBarSize.x * fWidth / fRealImageX));
	vProgressBarAlignSize.y = static_cast<float>(floor(vProgressBarSize.y * fHeight/ fRealImageX));

	D3DXVECTOR2 vProgressBarAlign;
	vProgressBarAlign.x = ((fWidth - vProgressBarAlignSize.x)/0.5f);
	vProgressBarAlign.y = fHeight - 133.0f;

	D3DXVECTOR2 vHintAlign;
	vHintAlign.x = 120.0f;
	vHintAlign.y = fHeight - 100.0f;

	D3DXVECTOR2 vCopyrightAlign;
	vCopyrightAlign.x = 15;
	vCopyrightAlign.y = fHeight - 60.0f;
	
	D3DXVECTOR2 vOver15Align;
	vOver15Align.x = fWidth - (vOver15Size.x+15.0f);
	vOver15Align.y = 15.0f;

	//	¹Ø ¹è°æ
	LPDIRECT3DVERTEXBUFFERQ pTextureVB        = NULL; // Buffer to hold vertices
	{
		TEXTUREVERTEX2 VertexArray[6];
		SetVertexPos ( VertexArray, ROOT_LEFT, ROOT_TOP+140, SizeLoadingMap.x, SizeLoadingMap.y );
		SetTexturePos( VertexArray, 0.0f, 0.0f, SizeLoadingMap.x, SizeLoadingMap.y, SizeLoadingMap.x, SizeLoadingMap.y );

		if ( FAILED ( CreateVB (pd3dDevice, pTextureVB, VertexArray ) ) )
		{
			n_ExitState = eERROR;
			return 0;
		}
	}
	//	15±ÝÇ¥½Ã
	LPDIRECT3DVERTEXBUFFERQ pOver15VB;
	{
		TEXTUREVERTEX2 VertexArray[6];
		SetVertexPos ( VertexArray, ROOT_LEFT + vOver15Align.x, ROOT_TOP + vOver15Align.y, vOver15Size.x, vOver15Size.y );
		SetTexturePos( VertexArray, vOver15Tex.x, vOver15Tex.y, vOver15Size.x, vOver15Size.y, vOver15Size.x, vOver15Size.y );

		if ( FAILED ( CreateVB ( pd3dDevice, pOver15VB, VertexArray ) ) )
		{
			n_ExitState = eERROR;
			return 0;
		}
	}

	LPDIRECT3DVERTEXBUFFERQ pTopImage;
	{
		TEXTUREVERTEX2 VertexArray[6];
		SetVertexPos ( VertexArray, ROOT_LEFT, ROOT_TOP, SizeTopAndBot.x, SizeTopAndBot.y );
		SetTexturePos( VertexArray, 0.0f, 0.0f, SizeTopAndBot.x, SizeTopAndBot.y, SizeTopAndBot.x, SizeTopAndBot.y );

		if ( FAILED ( CreateVB ( pd3dDevice, pTopImage, VertexArray ) ) )
		{
			n_ExitState = eERROR;
			return 0;
		}
	}

	LPDIRECT3DVERTEXBUFFERQ pBotImage;
	{
		TEXTUREVERTEX2 VertexArray[6];
		SetVertexPos ( VertexArray, ROOT_LEFT, BottomPos-146, SizeTopAndBot.x, SizeTopAndBot.y );
		SetTexturePos( VertexArray, 0.0f, 0.0f, SizeTopAndBot.x, SizeTopAndBot.y, SizeTopAndBot.x, SizeTopAndBot.y );

		if ( FAILED ( CreateVB ( pd3dDevice, pBotImage, VertexArray ) ) )
		{
			n_ExitState = eERROR;
			return 0;
		}
	}



	pd3dDevice->CreateVertexBuffer( 4*sizeof(Vertex), D3DUSAGE_WRITEONLY, 
		(D3DFVF_XYZ | D3DFVF_TEX1), D3DPOOL_DEFAULT, 
		&g_pVB, NULL );
	void *pVertices = NULL;

	g_pVB->Lock( 0, sizeof(g_quadVertices), (void**)&pVertices, 0 );
	memcpy( pVertices, g_quadVertices, sizeof(g_quadVertices) );
	g_pVB->Unlock();

	CD3DFontPar* pFont = DxFontMan::GetInstance().LoadDxFont( _DEFAULT_FONT, 9, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );
	CD3DFontPar* pFont12 = DxFontMan::GetInstance().LoadDxFont( _DEFAULT_FONT , 13, TRUE, D3DFONT_SHADOW | D3DFONT_ASCII );
	//CD3DFontPar* pFont12 = DxFontMan::GetInstance().LoadDxFont( _DEFAULT_FONT, 13, _DEFAULT_FONT_FLAG );
	if( pFont )
		pFont->UsageCS( TRUE );
	if( pFont12 )
		pFont12->UsageCS( TRUE );

	while ( n_bRender )
	{
		char MapNameLoad[200];
		if(!n_mapname.IsEmpty())
		{
			sprintf(MapNameLoad,"< %s >",n_mapname);
		}
		if(pSprite == NULL)
		if( pSprite == NULL )
		{
			if ( FAILED (D3DXCreateSprite(pd3dDevice,&pSprite)))
			{
				MessageBoxA(NULL,"´´½¨¾«ÁéÊ§°Ü",0,0);
			}

		}
		HRESULT hr;

		if(m_vecMESSAGE2.size ()==0)
		{
					tiptext(n_szAppPath);
		}
        MAX_INDEX = static_cast<int>(m_vecMESSAGE2.size ());
			if(MAX_INDEX>0)
			{
				srand ( (UINT)time( NULL ) );
				if(nIndex==NULL)
				{
					nIndex = rand () % MAX_INDEX;
				}
			}

		if( FAILED( hr = pd3dDevice->TestCooperativeLevel() ) )
		{
			
			if( D3DERR_DEVICELOST == hr )
			{
				CDebugSet::ToListView ( "[ERROR] D3DERR_DEVICELOST _ LoadingThread() FAILED" );
				continue;
			}

			// Check if the device needs to be resized.
			if( D3DERR_DEVICENOTRESET == hr )
				continue;
		}

		hr = pd3dDevice->Clear( 0L, NULL, D3DCLEAR_TARGET, D3DCOLOR_XRGB(0,0,0), 1.0f, 0L );

		// Begin the scene
		if( SUCCEEDED( pd3dDevice->BeginScene() ) )
		{

			//	¹Ø ¹Ù´Ú
			hr = Render( pd3dDevice,pLoadingTexture,pTextureVB);
			DWORD dwAlphaBlendEnable;
			pd3dDevice->GetRenderState ( D3DRS_ALPHABLENDENABLE, &dwAlphaBlendEnable );

			pd3dDevice->SetRenderState ( D3DRS_ALPHABLENDENABLE, TRUE );
			pd3dDevice->SetRenderState ( D3DRS_SRCBLEND, D3DBLEND_SRCALPHA );
			pd3dDevice->SetRenderState ( D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA );

			DWORD dwAlphaOP;
			pd3dDevice->GetTextureStageState( 0, D3DTSS_ALPHAOP,   &dwAlphaOP );
			pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   D3DTOP_SELECTARG1 );

			DWORD dwMin, dwMag, dwMip;
			pd3dDevice->GetSamplerState( 0, D3DSAMP_MINFILTER,	&dwMin );
			pd3dDevice->GetSamplerState( 0, D3DSAMP_MAGFILTER,	&dwMag );
			pd3dDevice->GetSamplerState( 0, D3DSAMP_MIPFILTER,	&dwMip );

			pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER,	D3DTEXF_POINT );
			pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER,	D3DTEXF_POINT );
			pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER,	D3DTEXF_NONE );
			
			hr = Render ( pd3dDevice, pBotImageTex, pBotImage );
			hr = Render( pd3dDevice,pdds,g_pVB);
			hr = Render ( pd3dDevice, pTopImageTex, pTopImage );	
	

			RECT srcRect;
			///Ðý×ªÍ¼Æ¬´óÐ¡¼ÆËã£¨ÕÅÊý£©
			srcRect.top    = (( tupian / 4 ) * 105);
			srcRect.left   = (( tupian % 4 ) * 105);
			srcRect.bottom = (( tupian / 4 ) * 105) + 105;
			srcRect.right  = (( tupian % 4 ) * 105) + 105;

			D3DXVECTOR3 vCenter( 0.0f, 0.0f, 0.0f );
			D3DXVECTOR3 vPosition(vProgressBarAlign.x,vProgressBarAlign.y, 0.0f );
			pSprite->Begin( D3DXSPRITE_ALPHABLEND );
			RECT srcRect2;
			/////Ðý×ª±³¾°Í¼´óÐ¡¼ÆËã
			srcRect2.top    = (( 0 / 4 ) * 128);
			srcRect2.left   = (( 0 % 4 ) * 128);
			srcRect2.bottom = (( 0 / 4 ) * 128) + 128;
			srcRect2.right  = (( 0 % 4 ) * 128) + 128;
			pSprite->Draw(beijingtu,&srcRect2,&vCenter,&vPosition,D3DCOLOR_COLORVALUE(1.0f,1.0f,1.0f,1.0f));//»­³öÐý×ª±³¾°
			vPosition.x += 12;
			vPosition.y += 12;
			pSprite->Draw( pdds,&srcRect,&vCenter,&vPosition,D3DCOLOR_COLORVALUE(1.0f,1.0f,1.0f,1.0f) );//»­³öÐý×ªÍ¼

			D3DXVECTOR3 vMapPosition(MapNamePosition.x,MapNamePosition.y, 0.0f );

			if(!n_mapname.IsEmpty()){
			RECT srcRect3;
			/////Ðý×ª±³¾°Í¼´óÐ¡¼ÆËã
			srcRect3.top    = (( 0 / 4 ) * 352);
			srcRect3.left   = (( 0 % 4 ) * 352);
			srcRect3.bottom = (( 0 / 4 ) * 352) + 352;
			srcRect3.right  = (( 0 % 4 ) * 352) + 352;
			pSprite->Draw(mapnameds,&srcRect3,&vCenter,&vMapPosition,D3DCOLOR_COLORVALUE(1.0f,1.0f,1.0f,1.0f));
			RECT srcRect4;
			//Ð¡Í¼±ê
			srcRect4.top    = (( 0 / 4 ) * 128);
			srcRect4.left   = (( 0 % 4 ) * 128);
			srcRect4.bottom = (( 0 / 4 ) * 128) + 128;
			srcRect4.right  = (( 0 % 4 ) * 128) + 128;
			D3DXVECTOR3 vPosition2(vHintAlign.x,vHintAlign.y, 0.0f );
			pSprite->Draw(xiaotu,&srcRect4,&vCenter,&vPosition2,D3DCOLOR_COLORVALUE(1.0f,1.0f,1.0f,1.0f));
			}
			



			pSprite->End();

			if( pFont )
			{
				if(!n_mapname.IsEmpty())
				{
				if(nIndex>NULL)
				{
					pFont->DrawText(vHintAlign.x+85.0f,vHintAlign.y+15.0f,NS_UITEXTCOLOR::WHITE,m_vecMESSAGE2[nIndex]);
				}
					pFont12->DrawText( vMapPosition.x+70.0f, vMapPosition.y+20.0f, NS_UITEXTCOLOR::WHITE,MapNameLoad);
				}else{
					pFont->DrawText( vCopyrightAlign.x, vCopyrightAlign.y, NS_UITEXTCOLOR::WHITE, ID2GAMEWORD("COPYRIGHT_COMPANY_LOAD") );
				}


			}

			//	15±Ý Ç¥½Ã
			if ( n_bOVER15 ) hr = Render ( pd3dDevice, pOVER15Tex, pOver15VB );			
			
			pd3dDevice->SetTextureStageState( 0, D3DTSS_ALPHAOP,   dwAlphaOP );
			pd3dDevice->SetRenderState ( D3DRS_ALPHABLENDENABLE, dwAlphaBlendEnable );

			pd3dDevice->SetSamplerState( 0, D3DSAMP_MINFILTER,	dwMin );
			pd3dDevice->SetSamplerState( 0, D3DSAMP_MAGFILTER,	dwMag );
			pd3dDevice->SetSamplerState( 0, D3DSAMP_MIPFILTER,	dwMip );

			// End the scene.
			pd3dDevice->EndScene();
			pd3dDevice->Present( NULL, NULL, NULL, NULL );
		}
		{
			++tupian;
			if( tupian > 3 )
				tupian = 0;

		}
		Sleep(800);
	}

	if( pFont )
		pFont->UsageCS( FALSE );
	if( pFont12 )
		pFont12->UsageCS( FALSE );

	SAFE_RELEASE ( pTextureVB );
	SAFE_RELEASE ( pOver15VB );
	SAFE_RELEASE ( pTopImage );
	SAFE_RELEASE ( pBotImage );
	SAFE_RELEASE ( pSprite );
	SAFE_RELEASE ( g_pVB );

	TextureManager::ReleaseTexture( szTexture, pLoadingTexture );
	TextureManager::ReleaseTexture( szOver15Name.c_str(), pOVER15Tex );
	TextureManager::ReleaseTexture( m_ldtop.c_str(), pTopImageTex );
	TextureManager::ReleaseTexture( m_ldbot.c_str(), pBotImageTex );
	TextureManager::ReleaseTexture( m_strNumberTEX.c_str(), pdds );
	TextureManager::ReleaseTexture( m_strName.c_str(), beijingtu );
	nIndex = rand () % MAX_INDEX;
	n_mapname = _T("");
	///////////////////////////////////////////////////////////////////////////////
	//	[TOGGLE SWITCH] ·Î´õ ½º·¹µå Á¾·á
	DeWait ();
	//////////////////////////////////////////////////////////////////////////////
	n_ExitState = eNORMAL;

	return 0;
}

namespace	NLOADINGTHREAD
{
	DWORD				n_dwThreadID;
	LPDIRECT3DDEVICEQ*	n_ppd3dDevice;
	HWND				n_hWnd;
	BOOL				n_bWait;
	BOOL				n_bRender;
	bool				n_bOVER15;
	char				n_szAppPath[MAX_PATH] = {0};
	int					n_ExitState;
	int					n_Step = 0;
	HANDLE				n_hThread = NULL;
	CString				n_strTextureName;
	CString             n_mapname;


	HRESULT	StartThreadLOAD(LPDIRECT3DDEVICEQ* ppd3dDevice, 
							HWND hWnd, 
							char* szAppPath, 
							const CString & strTextureName, 
							bool bOVER15 )
	{
		n_bOVER15 = bOVER15;
		n_ppd3dDevice = ppd3dDevice;
		n_hWnd = hWnd;
		StringCchCopy ( n_szAppPath, MAX_PATH, szAppPath );
		n_strTextureName = strTextureName;
		
		n_bRender = TRUE;	//	·»´õ
		EnWait ();
		n_ExitState = eNORMAL;

		//n_hThread = CreateThread( NULL, 0, LoadingThread, NULL, 0, &n_dwThreadID );
		n_hThread = (HANDLE) ::_beginthreadex(
									NULL,
									0,
									LoadingThread,
									NULL,
									0,
									(unsigned int*) &n_dwThreadID );
		if ( !n_hThread )
		{
			DeWait();
			return E_FAIL;
		}

		return S_OK;
	}

	void	WaitThread ()
	{
		while ( GetWait () )
		{		
			Sleep( 1 );
		}
		EnWait ();
	}

	void	EndThread ()
	{		
		n_bRender = FALSE;

		if ( n_ExitState == eNORMAL )
		{
			WaitThread ();
		}

		CloseHandle( n_hThread );
		n_hThread = NULL;

		n_strTextureName.Empty();
	}

	BOOL	GetWait ()
	{
		return n_bWait;
	}

	void	DeWait  ()
	{
		n_bWait = FALSE;
	}

	void	EnWait ()
	{
		n_bWait = TRUE;
	}

	void	SetStep ( int step )
	{
		n_Step = step;
	}

	int		GetStep ()
	{
		return n_Step;
	}
	
	void   MapName(const CString & Name)
	{
		n_mapname = Name;
	}

	void  tiptext( char* szAppPath)
	{
		CString strFileName = szAppPath;
		strFileName += SUBPATH::GLOGIC_FILE;
		strFileName += ID2GAMEWORD("TIP_FILE");
		//LoadMessage ( strFullPath );
		//m_vecMESSAGE = name;

		char fname[_MAX_FNAME];
		char ext[_MAX_EXT];
		_splitpath( strFileName.GetString(), NULL, NULL, fname, ext );
		StringCchCat ( fname, _MAX_EXT, ext );

		//MessageBoxA(NULL,GLOGIC::strGLOGIC_ZIPFILE.c_str(),strFileName.GetString(),0);


		std::auto_ptr<CBaseString> pBString(GLOGIC::openfile_basestring(GLOGIC::bGLOGIC_ZIPFILE, 
			GLOGIC::strGLOGIC_ZIPFILE.c_str(), 
			strFileName.GetString(), 
			fname,
			false,
			GLOGIC::bGLOGIC_PACKFILE ) );

		if ( !pBString.get() )
		{
			//MessageBoxA(NULL,"1",0,0);
			//CDebugSet::ToLogFile ( "ERROR : CSimpleMessageMan::LoadMessage(), File Open %s", fname );
			return ;
		}

		CBaseString &cBString = *pBString;

		CString strLine;
		CString strFullText;
		while ( cBString.GetNextLine(strLine) )
		{
			if ( strLine == ';' )
			{
				int nLength = strFullText.GetLength ();
				if ( 2<nLength && strFullText[nLength-2] == '\r' && strFullText[nLength-1] == '\n' )
					strFullText = strFullText.Left(nLength-2);

				nLength = strFullText.GetLength ();
				if ( nLength )
				{
					m_vecMESSAGE2.push_back ( strFullText );
					strFullText.Empty ();
				}
			}
			else
			{			
				strLine += "\r\n";
				strFullText += strLine;
			}
		}
		if ( strFullText.GetLength () )	m_vecMESSAGE2.push_back ( strFullText );
	}
};
