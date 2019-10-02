// TabMMP.cpp : implementation file
//

#include "stdafx.h"
#include "RanTool.h"
#include "TabMMP.h"
#include "ToolTab.h"
#include ".\tabmmp.h"
#include "EtcFunction.h"

#include "BitmapMan.h"

inline ROUND( float fValue)
{
	return static_cast<int>( fValue + ( fValue > 0 ? 0.5 : -0.5 ) );
}

// CTabMMP dialog

IMPLEMENT_DYNAMIC(CTabMMP, CPropertyPage)
CTabMMP::CTabMMP(LOGFONT logfont)
	: CPropertyPage(CTabMMP::IDD)
	, m_pFont( NULL )
	, m_nLX(0)
	, m_nTY(0)
	, m_nRX(0)
	, m_nBY(0)
	, m_nSizeX(0)
	, m_nSizeY(0)
	, m_nCalcLX(0)
	, m_nCalcBY(0)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CTabMMP::~CTabMMP()
{
}

void CTabMMP::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT_BMP, m_csFileName);
	DDX_Text( pDX, IDC_LX, m_nLX );
	DDX_Text( pDX, IDC_TY, m_nTY );
	DDX_Text( pDX, IDC_RX, m_nRX );
	DDX_Text( pDX, IDC_BY, m_nBY );
	DDX_Control(pDX, IDC_EDIT_DDS, m_csDDSFileName);
	DDX_Control(pDX, IDC_VIEW, m_ctrlEditView);
}


BEGIN_MESSAGE_MAP(CTabMMP, CPropertyPage)
	ON_BN_CLICKED(IDC_BUTTON1, OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, OnBnClickedButton2)
	ON_BN_CLICKED(IDOK, OnBnClickedOk)
END_MESSAGE_MAP()


// CTabMMP message handlers
BOOL CTabMMP::OnInitDialog()
{
	CPropertyPage::OnInitDialog();

	m_pToolTab->ChangeDialogFont( this, m_pFont, CDF_TOPLEFT );
	
	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control
}
void CTabMMP::Reset()
{
	SetWin_Text ( this, IDC_FILENAME,"" );
	SetWin_Text ( this, IDC_VIEW,"" );
	SetWin_Text ( this, IDC_EDIT_BMP,"" );
	SetWin_Text ( this, IDC_EDIT_DDS,"" );

	SetWin_Num_int ( this, IDC_LX,0 );
	SetWin_Num_int ( this, IDC_TY,0 );
	SetWin_Num_int ( this, IDC_RX,0 );
	SetWin_Num_int ( this, IDC_BY,0 );
}

void CTabMMP::OnBnClickedButton1()
{
	CString szFilter = "BMP Image (*.bmp)|*.bmp|";
	CFileDialog dlg( TRUE, ".bmp", NULL, OFN_HIDEREADONLY, szFilter );
	if ( dlg.DoModal() == IDOK )
	{
		CString strPathName( dlg.GetPathName() );
		CBitmapMan::m_cBitmapMan.LOAD( strPathName );

		m_csFileName.SetWindowText( dlg.GetPathName() );
	}
}

void CTabMMP::OnBnClickedButton2()
{
	CString szFilter = "DDS Texture(*.dds)|*.dds|";
	CFileDialog dlg( TRUE, ".dds", NULL, OFN_HIDEREADONLY, szFilter );

	if ( dlg.DoModal() == IDOK )
	{
		CString strPathName( dlg.GetPathName() );
		m_csDDSFileName.SetWindowText( dlg.GetPathName() );
		m_strDDSFileName = dlg.GetFileName();
	}
}

void CTabMMP::OnBnClickedOk()
{
	CString szFilter = "MMP(*.mmp)|*.mmp|";

	CFileDialog dlg( FALSE, ".mmp", NULL, OFN_HIDEREADONLY|OFN_OVERWRITEPROMPT, szFilter );

	if ( dlg.DoModal() == IDOK )
	{
		BeginWaitCursor();
		{
			UpdateData();
			RECT rect = GetBitmapPosition();
			MiniMapPositionCalc( rect );
		}
		EndWaitCursor();
		CString strBUFFER;

		if( !MiniMapPositionSave( dlg.GetPathName(), strBUFFER ) )
		{
			AfxMessageBox( "Failure to Save MMP :(" );
			m_pToolTab->AddHistorySaveFail( "MMP Creator",dlg.GetFileName().GetString() );
		}
		else
		{	
			SetDlgItemText( IDC_FILENAME, dlg.GetFileName() );
			SetDlgItemText( IDC_VIEW, strBUFFER );
			m_pToolTab->AddHistorySave( "MMP Creator",dlg.GetFileName().GetString() );
		}
	}

}

BOOL CTabMMP::MiniMapPositionSave( CString & strPathName, CString & strBUFFER )
{
	CFile file;

	if( !file.Open( strPathName, CFile::modeCreate|CFile::modeWrite) )
		return FALSE;

	BITMAP sBitmap = CBitmapMan::m_cBitmapMan.GetBitmap();

	strBUFFER.Format( "MINIMAPNAME\t\t%s\r\n", m_strDDSFileName );
	strBUFFER.AppendFormat( "MAPSIZE_X\t\t%d %d\r\n", m_nSizeX, m_nCalcLX );
	strBUFFER.AppendFormat( "MAPSIZE_Y\t\t%d %d\r\n", m_nSizeY, m_nCalcBY );
	strBUFFER.AppendFormat( "TEXTURE_SIZE\t\t%d %d\r\n", sBitmap.bmWidth, sBitmap.bmHeight );
	strBUFFER.AppendFormat( "TEXTURE_POS\t\t%d %d %d %d", 0, 0, sBitmap.bmWidth, sBitmap.bmHeight ); 

	file.Write( strBUFFER, strBUFFER.GetLength() );

	file.Close();

	return TRUE;
}



void CTabMMP::MiniMapPositionCalc( RECT & rect )
{
	float fRealSizeX = static_cast<float>(m_nRX - m_nLX);
	float fRealSizeY = static_cast<float>(m_nTY - m_nBY);

	BITMAP sBitmap = CBitmapMan::m_cBitmapMan.GetBitmap();

	m_nSizeX = ROUND( ( fRealSizeX * sBitmap.bmWidth ) / ( rect.right - rect.left ) );
	m_nCalcLX = m_nLX - ROUND( (float)m_nSizeX * rect.left / sBitmap.bmWidth );
	m_nSizeY = ROUND( ( fRealSizeY * sBitmap.bmHeight ) / ( rect.bottom - rect.top ) );
	m_nCalcBY = m_nBY - ROUND( (float)m_nSizeY * rect.top / sBitmap.bmHeight );
}

RECT CTabMMP::GetBitmapPosition()
{
	CClientDC WinDC(this);
	CDC MemDC;
	MemDC.CreateCompatibleDC( &WinDC );

	BITMAP sBitmap = CBitmapMan::m_cBitmapMan.GetBitmap();
	HBITMAP hBitmap = CBitmapMan::m_cBitmapMan.GetHBitmap();

	MemDC.SelectObject( (HBITMAP)hBitmap ); 
	///////////////////////////////
	INT nLEFT(0);
	INT nTOP(0);
	INT nRIGHT(sBitmap.bmWidth-1);
	INT nBOTTOM(sBitmap.bmHeight-1);

	BOOL bOut(FALSE);
	///////////////////////////////
	COLORREF colorRef = GetPixel(MemDC, nLEFT, nTOP);
	for(int i=nTOP; i<=nBOTTOM && !bOut; ++i) 
	{
		for(int j=nLEFT; j<=nRIGHT; ++j)
		{
			COLORREF color = GetPixel(MemDC, j, i);
			if(colorRef != color )
			{
				nTOP = i;
				bOut = TRUE;
				break;
			}
		}
	}
	////////////////////////////////////////////////////////////////////////////////////
	bOut = FALSE;
	colorRef = GetPixel(MemDC, nLEFT, nBOTTOM);
	for(int i=nBOTTOM; i>=nTOP && !bOut; --i)
	{
		for(int j=nLEFT; j<=nRIGHT; ++j)
		{
			COLORREF color = GetPixel(MemDC, j, i);
			if(colorRef != color)
			{
				nBOTTOM = i;
				bOut = TRUE;
				break;
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////
	bOut = FALSE;
	colorRef = GetPixel(MemDC, nLEFT, nTOP);
	for(int i=nLEFT; i<=nRIGHT && !bOut; ++i) 
	{
		for(int j=nTOP; j<=nBOTTOM; ++j)
		{
			COLORREF color = GetPixel(MemDC, i, j);
			if(colorRef != color)
			{
				nLEFT = i;
				bOut = TRUE;
				break;
			}
		}
	}

	////////////////////////////////////////////////////////////////////////////////////
	bOut = FALSE;
	colorRef = GetPixel(MemDC, nRIGHT, nTOP);
	for(int i=nRIGHT; i>=nLEFT && !bOut; --i)
	{
		for(int j=nTOP; j<=nBOTTOM; ++j)
		{
			COLORREF color = GetPixel(MemDC, i, j);
			if(colorRef != color)
			{
				nRIGHT = i;
				bOut = TRUE;
				break;
			}
		}
	}

	RECT rect;

	rect.left = nLEFT;
	rect.top = nTOP;
	rect.right = nRIGHT;
	rect.bottom = nBOTTOM;

	return rect;
}

