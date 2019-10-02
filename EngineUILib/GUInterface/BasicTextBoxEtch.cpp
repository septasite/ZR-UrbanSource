#include "StdAfx.h"
#include "BasicTextBox.h"
#include "UIRenderQueue.h"
#include "../DxCommon/DxFontMan.h"

#include "../RanClientLib/G-Logic/GLItem.h"
#include "../RanClientLib/G-Logic/GLItemMan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


int	CBasicTextBox::AddText ( const CString& strText, SITEMLINK* pItemLink , const D3DCOLOR& TextColor /*= NS_UITEXTUTIL::ENABLE*/ )
{
	if ( !m_pFont )
	{
		GASSERT ( 0 && "폰트가 널입니다. SetFont()를 이용하여 폰트부터 값을 넣으십시오." );
		return 0;
	}

	//	문자열 자르기
	NS_UITEXTUTIL::ClearCRLFText ();
	NS_UITEXTUTIL::MULTILINETEXT& MLText = NS_UITEXTUTIL::GetMLTextWithoutCRLF ( strText, GetLocalPos().sizeX, m_pFont );

	int nSplitLine = (int)MLText.size ();

	STEXTPART sTextPart;
	
	if ( pItemLink )
	{
		SITEM* pITEMFIND = GLItemMan::GetInstance().GetItem( pItemLink->sNativeID );
		if ( pITEMFIND )
		{
			CString strKEY = pItemLink->GetFilter();
			BOOL bLINKEXIST = FALSE;
			int nSTART = 0;
			{
				//verify if itemlink text does really exist in input text
				std::string strSEARCH = strText.GetString();
				int nFIND = strSEARCH.find( strKEY.GetString() );
				if (nFIND!=std::string::npos)	
				{
					//found it now itemlink is really valid
					bLINKEXIST = TRUE;
					nSTART = nFIND;
					sTextPart.m_sItemLink = *pItemLink;
				}
			}

			if ( bLINKEXIST )
			{
				BOOL bFOUNDLINK = FALSE;

				//now we verify if itemlink text is not being split to lines
				for ( int i = 0; i < nSplitLine; ++i )
				{
					std::string strSEARCH = MLText[i].strLine.GetString();
					int nFIND = strSEARCH.find( strKEY.GetString() );
					if (nFIND!=std::string::npos)	
					{
						bFOUNDLINK = TRUE;
					}
				}

				if ( !bFOUNDLINK )
				{
					//damn problem text got split need to fix
					CString strNewKEY;
					strNewKEY += "\r\n";
					strNewKEY += pItemLink->GetFilter();

					CString strTEXTNEW = strText;
					strTEXTNEW.Replace( strKEY.GetString(), strNewKEY.GetString() );
					NS_UITEXTUTIL::ClearCRLFText ();
					MLText = NS_UITEXTUTIL::GetMLTextWithoutCRLF ( strTEXTNEW, GetLocalPos().sizeX, m_pFont );
				}
			}
		}		
	}





	//	데이타로 집어넣기
	for ( int i = 0; i < nSplitLine; ++i )
	{		
		STEXTLINE sTextLine;

		if ( (i - 1 == nSplitLine) && !MLText[i].strLine.GetLength () )
		{
			//	마지막라인이 빈 경우.
		}
		else
		{
			SIZE strSize;
			m_pFont->GetTextExtent ( MLText[i].strLine.GetString(), strSize );

			sTextLine.strSize = strSize;
			sTextLine.bLASTLINE = MLText[i].bLASTLINE;
			if ( m_nAlign == TEXT_ALIGN_BOTH_X )
			{				
				NS_UITEXTUTIL::ClearWordText ();
				NS_UITEXTUTIL::STRINGVECTOR& WordText = NS_UITEXTUTIL::GetWordText ( MLText[i].strLine );

				for ( int k = 0; k < (int)WordText.size(); ++k )
				{
					STEXTWORD sTextWord;

					sTextWord.strWord = WordText[k];
					sTextWord.dwColor = TextColor;

					if ( WordText[k].GetLength () )
					{
						m_pFont->GetTextExtent ( WordText[k].GetString(), strSize );
						m_pFont->PushText( WordText[k].GetString() );
					}
					else
					{
						strSize.cx = 0;
						strSize.cy = BLANKSIZE.cy;
					}

					sTextWord.strSize = strSize;

					sTextLine.vectorWord.push_back ( sTextWord );
				}

				m_nTotalLine++;
				sTextPart.dequeLine.push_back ( sTextLine );
			}
			else
			{
				STEXTWORD sTextWord;
				sTextWord.strWord = MLText[i].strLine;
				sTextWord.dwColor = TextColor;

				sTextWord.strSize = strSize;

				if( MLText[i].strLine.GetLength() )
					m_pFont->PushText( MLText[i].strLine.GetString() );

				sTextLine.vectorWord.push_back ( sTextWord );
				sTextPart.dequeLine.push_back ( sTextLine );

				m_nTotalLine++;
			}
		}
	}	

	m_TextBox.push_back ( sTextPart );

	//	제한 라인 범위가 넘을 경우, 잘라냄
	for ( ; m_nLimitLine < m_nTotalLine; --m_nTotalLine )
	{		
		STEXTPART& sDelTextPart = m_TextBox.front ();
		DEQUETEXTLINE& dequeLine = sDelTextPart.dequeLine;

		dequeLine.pop_front ();

		//	만약, 문단에 실제 글이 없을 경우,
		//	문단을 날린다.
		if ( dequeLine.size () < 1 )
		{
			if ( m_ImageList.size () )
			{
				DeleteControl ( m_ImageList[0], 0 );
				m_ImageList.pop_front ();
			}
			m_TextBox.pop_front ();
		}
	}

	ReCalcRenderPos ();

	return (int)m_TextBox.size () - 1;
}