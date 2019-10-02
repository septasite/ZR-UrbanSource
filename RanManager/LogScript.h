#pragma once
#include "stdafx.h"

namespace LOGSCRIPT
{
	extern void	InitLog(const char *szAppPath);
	extern void	LogToFile( const char *szFileName, const char *szFormat, ... );

};