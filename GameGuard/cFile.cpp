#include "Stdafx.h"
#include "cFile.h"

cFile::cFile() // constractor
{
}

int		cFile::iGetFileSize(char* FileName)
{
		HANDLE hFile = CreateFileA(FileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING,FILE_ATTRIBUTE_NORMAL, NULL);            
		return GetFileSize(hFile,NULL); 
}


bool	cFile::iCheckFileSize(char* cFile,int Size)
{

		int iSize = this->iGetFileSize(cFile);
		if(iSize == Size)
			return true;
		return false;
}


cFile::~cFile() // desratactor
{

}