#ifndef NEOEASYCRYPTION_TEST_
#define NEOEASYCRYPTION_TEST_

#pragma once

namespace CCrypt
{
	enum
	{
		//EN = 12321354543531,
		//EN2 = 54543523223223,
		EN = 48648942123145,
		EN2 = 87545124673131,
		//EN = 0x5FFF2AFA, Old Crypt Code | 7-22-2013
		//EN = 0x50E1ADF2,
		//EN2 = 0x1AEDAA0A,
		END = 0x03,
	};
	enum
	{
		ENTYPE_ALL,
	};
	enum
	{
		ENCRY_VER = 0x100,
		ENCRY_HEADER_SIZE = 12,
	};

	enum 
	{
		TEXTURE_DDS,
		TEXTURE_TGA,

		TEXTURE_TYPE,
	};

	enum 
	{
		TEX_HEADER_SIZE = 12,
		TEX_VERSION		= 0x100,
		TEX_XOR_DATA	= 0x48,
		TEX_DIFF_DATA	= 0x05,
	};

	extern BOOL	bCryptRCC;
	extern BOOL	bEngineDebug;
	extern BOOL	bEngineDebugLog;

	void Encryption(BYTE* B,int dwSize);
	void Decryption(BYTE* B,int dwSize);
	void LoadSetting( const TCHAR *szRootPath );

};

#endif
