#ifndef DXINCOMMAND_H_
#define DXINCOMMAND_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

struct SITEMLINK;

namespace dxincommand
{
	extern bool bDISP_FPS;
	extern bool bDISP_CONSOLE;

	bool command( const char* szcommand, SITEMLINK* pItemLink );
};


#endif // DXINCOMMAND_H_