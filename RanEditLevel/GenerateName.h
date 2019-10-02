#ifndef _GENERATENAME_
#define _GENERATENAME_

#include "GLLandMan.h"
#include "GLLandMan.h"

std::string CrowNameNew( GLLandMan*	pLand );
bool		CrowNameCheck( GLLandMan*	pLand, const char* szName );

std::string GateNameNew( GLLandMan*	pLand );
DWORD		GateNewID( GLLandMan* pLand );
bool		GateNameCheck( GLLandMan*	pLand, const char* szName );
bool		GateIDCheck( GLLandMan*	pLand, DWORD dwID );

std::string EffectNameNew( GLLandMan*	pLand );
bool		EffectNameCheck( GLLandMan*	pLand, const char* szName );

std::string LMNameNew( GLLandMan*	pLand );
bool		LMNameCheck( GLLandMan*	pLand, const char* szName );

#endif // _GENERATENAME_