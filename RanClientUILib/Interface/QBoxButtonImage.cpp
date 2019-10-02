#include "StdAfx.h"
#include "QBoxButtonImage.h"
#include "../EngineUILib/GUInterface/BasicButton.h"
#include "../EngineUILib/GUInterface/BasicProgressBar.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

CQBoxButtonImage::CQBoxButtonImage()
{
}

CQBoxButtonImage::~CQBoxButtonImage()
{
}

void CQBoxButtonImage::CreateSubControl()
{
	CString strQBox[QBOX_SIZE] =
	{
		"QBOX_BUTTON_BUTTON",
		"Q_BOX_CRAZY_TIME",
		"Q_BOX_EXP_TIME",
		"Q_BOX_LUCKY",
		"Q_BOX_MADNESS_TIME",
		"Q_BOX_POWER_UP",
		"Q_BOX_POWER_UP_MAX",
		"Q_BOX_SPEED_UP",
		"Q_BOX_SPEED_UP_MAX",
	};

	CString strQBoxF[QBOX_SIZE] =
	{
		"QBOX_BUTTON_BUTTON_F",
		"Q_BOX_CRAZY_TIME_F",
		"Q_BOX_EXP_TIME_F",
		"Q_BOX_LUCKY_F",
		"Q_BOX_MADNESS_TIME_F",
		"Q_BOX_POWER_UP_F",
		"Q_BOX_POWER_UP_MAX_F",
		"Q_BOX_SPEED_UP_F",
		"Q_BOX_SPEED_UP_MAX_F",
	};

	for ( int i = 0; i < QBOX_SIZE; ++i )
	{
		m_pQBoxImage[i] = new CUIControl;
		m_pQBoxImage[i]->CreateSub ( this, strQBox[i].GetString() );
		m_pQBoxImage[i]->SetVisibleSingle ( FALSE );
		RegisterControl ( m_pQBoxImage[i] );

		m_pQBoxImageflip[i] = new CUIControl;
		m_pQBoxImageflip[i]->CreateSub ( this, strQBoxF[i].GetString() );
		m_pQBoxImageflip[i]->SetVisibleSingle ( FALSE );