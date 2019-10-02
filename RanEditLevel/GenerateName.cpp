//lordx
//project level editor
//find and generate new name

#include "stdafx.h"
#include "GenerateName.h"
#include "EtcFunction.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//create a valid name for new crow schedule
std::string CrowNameNew( GLLandMan*	pLand )
{
	if ( pLand )
	{
		char szTempChar[GLMobSchedule::EM_MAXSZNAME];
		sprintf( szTempChar, "CROW_%04d", 0 );

		SGLNODE<GLMobSchedule*>* p = pLand->GetMobSchMan()->FindMobSch( szTempChar );

		int i = 1;
		while ( p )
		{
			sprintf( szTempChar, "CROW_%04d", i );
		
			p = pLand->GetMobSchMan()->FindMobSch( szTempChar );
			i++;
		}

		return szTempChar;
	}

	return "";
}

//checks if name already exist
bool		CrowNameCheck( GLLandMan*	pLand, const char* szName )
{
	if ( pLand && szName )
	{
		SGLNODE<GLMobSchedule*>* p = pLand->GetMobSchMan()->FindMobSch( szName );
		if ( p )	return TRUE;

		return FALSE;
	}
	else
	{
		MessageBox( NULL,"Namecheck error invalid input parameter","Error", MB_OK );
	}

	return TRUE;
}

std::string GateNameNew( GLLandMan*	pLand )
{
	if ( pLand )
	{
		char szTempChar[DxLandGate::MAX_SZNAME];
		sprintf( szTempChar, "GATE_%04d", 0 );

		PDXLANDGATE p = pLand->GetLandGateMan().FindLandGate( szTempChar );
		int i = 1;

		while ( p )
		{
			sprintf( szTempChar, "GATE_%04d", i );
			
			p = pLand->GetLandGateMan().FindLandGate( szTempChar );
			i++;
		}

		return szTempChar;
	}

	return "";
}

DWORD GateNewID( GLLandMan* pLand )
{
	DWORD i = 0;

	if ( pLand )
	{
		
		PDXLANDGATE p = pLand->GetLandGateMan().FindLandGate( i );

		while ( p )
		{
			i++;
			p = pLand->GetLandGateMan().FindLandGate( i );
		}
	}

	return i;
}

bool		GateNameCheck( GLLandMan*	pLand, const char* szName )
{
	if ( pLand && szName )
	{
		PDXLANDGATE p = pLand->GetLandGateMan().FindLandGate( szName );
		if ( p )	return TRUE;

		return FALSE;
	}
	else
	{
		MessageBox( NULL,"Namecheck error invalid input parameter","Error", MB_OK );
	}

	return TRUE;
}

bool		GateIDCheck( GLLandMan*	pLand, DWORD dwID )
{
	if ( pLand  )
	{
		PDXLANDGATE p = pLand->GetLandGateMan().FindLandGate( dwID );
		if ( p )	return TRUE;

		return FALSE;
	}
	
	return TRUE;
}

std::string EffectNameNew( GLLandMan*	pLand )
{
	if ( pLand )
	{
		char szTempChar[DXLANDEFF::LANDEFF_MAXSZ];
		sprintf( szTempChar, "LANDEFF_%04d", 0 );

		PLANDEFF p = pLand->FindLandEff( szTempChar );

		int i = 1;
		while ( p )
		{
			sprintf( szTempChar, "LANDEFF_%04d", i );
		
			p = pLand->FindLandEff( szTempChar );
			i++;
		}

		return szTempChar;
	}

	return "";
}

bool		EffectNameCheck( GLLandMan*	pLand, const char* szName )
{
	if ( pLand && szName )
	{
		PLANDEFF p = pLand->FindLandEff( (char*)szName );
		if ( p )	return TRUE;

		return FALSE;
	}
	else
	{
		MessageBox( NULL,"Namecheck error invalid input parameter","Error", MB_OK );
	}

	return TRUE;
}

std::string LMNameNew( GLLandMan*	pLand )
{
	if ( pLand )
	{
		char szTempChar[DXLANDEFF::LANDEFF_MAXSZ];
		sprintf( szTempChar, "LANDMARK_%04d", 0 );

		PLANDMARK p = pLand->FindLandMark( szTempChar );

		int i = 1;
		while ( p )
		{
			sprintf( szTempChar, "LANDMARK_%04d", i );
		
			p = pLand->FindLandMark( szTempChar );
			i++;
		}

		return szTempChar;
	}

	return "";
}

bool		LMNameCheck( GLLandMan*	pLand, const char* szName )
{
	if ( pLand && szName )
	{
		PLANDMARK p = pLand->FindLandMark( (char*)szName );
		if ( p )	return TRUE;

		return FALSE;
	}
	else
	{
		MessageBox( NULL,"Namecheck error invalid input parameter","Error", MB_OK );
	}

	return TRUE;
}