#include "StdAfx.h"
#include "GLCaptureTheFieldMan.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

bool GLCaptureTheFieldMan::Load ( std::vector<std::string> &vecFiles )
{
	std::vector<std::string>::size_type i = 0, j = vecFiles.size();
	for( ; i < j; ++i )
	{
		GLCaptureTheField sCTF;
		bool bOK = sCTF.Load( vecFiles[i] );
		if( !bOK )
		{
			CDebugSet::ToLogFile ( "GLCaptureTheField.Load() fail, %s", vecFiles[i].c_str() );
		}

		m_vecCTF.push_back ( sCTF );
	}

	std::sort( m_vecCTF.begin(), m_vecCTF.end() );

	return true;
}

GLCaptureTheField* GLCaptureTheFieldMan::FindCTF ( DWORD dwID, BOOL bCHECK, BOOL bINIT )
{
	GLCaptureTheField cObj;
	cObj.m_dwID = dwID;

	CTF_VEC_ITER pos = std::lower_bound ( m_vecCTF.begin(), m_vecCTF.end(), cObj );
	if ( pos==m_vecCTF.end() )
	{
		return NULL;
	}else{
		return &(*pos);
	}
}

bool GLCaptureTheFieldMan::IsBattle ()
{
	for ( CTF_VEC::size_type i=0; i<m_vecCTF.size(); ++i )
	{
		GLCaptureTheField &sCTF = m_vecCTF[i];
		if ( sCTF.IsBattle() )		return true;
	}

	return false;
}
