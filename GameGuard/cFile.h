#include "Stdafx.h"

#ifndef cFile_H
#define cFile_H

class cFile
{
public:
	cFile();
	~cFile();
	bool		iCheckFileSize(char* cFile,int Size);
	int			iGetFileSize(char* FileName);


};
#endif
