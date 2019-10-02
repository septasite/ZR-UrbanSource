// RanManagerGuildImage.cpp : implementation file
//

#include "stdafx.h"
#include "RanManager.h"
#include "RanManagerGuildImage.h"
#include ".\ranmanagerguildimage.h"
#include "RanManagerGuildTab.h"
#include "RanManagerComments.h"


// CRanManagerGuildImage dialog

IMPLEMENT_DYNAMIC(CRanManagerGuildImage, CPropertyPage)
CRanManagerGuildImage::CRanManagerGuildImage(LOGFONT logfont)
	: CPropertyPage(CRanManagerGuildImage::IDD)
	,m_pFont(NULL)
{
	m_bDlgInit = FALSE;
	m_pFont = new CFont();
	m_pFont->CreateFontIndirect(&logfont);
}

CRanManagerGuildImage::~CRanManagerGuildImage()
{
}

void CRanManagerGuildImage::DoDataExchange(CDataExchange* pDX)
{
	CPropertyPage::DoDataExchange(pDX);
}


BEGIN_MESSAGE_MAP(CRanManagerGuildImage, CPropertyPage)
	ON_BN_CLICKED(IDC_BTN_IMAGE_CANCEL, OnBnClickedBtnImageCancel)
END_MESSAGE_MAP()


// CRanManagerGuildImage message handlers
BOOL CRanManagerGuildImage::OnInitDialog()
{
	CPropertyPage::OnInitDialog();
	m_bDlgInit = TRUE;

	return TRUE;  // return TRUE unless you set the focus to a control	
}

void CRanManagerGuildImage::SetGuild(int nGuildNum)
{

}
void CRanManagerGuildImage::OnBnClickedBtnImageCancel()
{
	m_pToolTab->ActivePage(GUILDPAGE_MAIN,0);
}
