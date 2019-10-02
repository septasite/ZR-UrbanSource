#pragma once
#include <map>
#include <hash_map>
#include <string>

namespace GLUPGRADECOLOR
{
	struct	UPGRADE_COLOR
	{
		 DWORD	A0010_G_A;
	 DWORD	A0010_G_R;
	 DWORD	A0010_G_G;
	 DWORD	A0010_G_B;

	 DWORD	A0010_A_A;
	 DWORD	A0010_A_R;
	 DWORD	A0010_A_G;
	 DWORD	A0010_A_B;

	 DWORD	A0010_R_A;
	 DWORD	A0010_R_R;
	 DWORD	A0010_R_G;
	 DWORD	A0010_R_B;
//////////////
//////////////(+11)
	 DWORD	A0011_G_A;
	 DWORD	A0011_G_R;
	 DWORD	A0011_G_G;
	 DWORD	A0011_G_B;

	 DWORD	A0011_A_A;
	 DWORD	A0011_A_R;
	 DWORD	A0011_A_G;
	 DWORD	A0011_A_B;

	 DWORD	A0011_R_A;
	 DWORD	A0011_R_R;
	 DWORD	A0011_R_G;
	 DWORD	A0011_R_B;
//////////////
//////////////(+12)
	 DWORD	A0012_G_A;
	 DWORD	A0012_G_R;
	 DWORD	A0012_G_G;
	 DWORD	A0012_G_B;

	 DWORD	A0012_A_A;
	 DWORD	A0012_A_R;
	 DWORD	A0012_A_G;
	 DWORD	A0012_A_B;

	 DWORD	A0012_R_A;
	 DWORD	A0012_R_R;
	 DWORD	A0012_R_G;
	 DWORD	A0012_R_B;
//////////////
//////////////(+13)
	 DWORD	A0013_G_A;
	 DWORD	A0013_G_R;
	 DWORD	A0013_G_G;
	 DWORD	A0013_G_B;

	 DWORD	A0013_A_A;
	 DWORD	A0013_A_R;
	 DWORD	A0013_A_G;
	 DWORD	A0013_A_B;

	 DWORD	A0013_R_A;
	 DWORD	A0013_R_R;
	 DWORD	A0013_R_G;
	 DWORD	A0013_R_B;
//////////////
//////////////(+14)
	 DWORD	A0014_G_A;
	 DWORD	A0014_G_R;
	 DWORD	A0014_G_G;
	 DWORD	A0014_G_B;

	 DWORD	A0014_A_A;
	 DWORD	A0014_A_R;
	 DWORD	A0014_A_G;
	 DWORD	A0014_A_B;

	 DWORD	A0014_R_A;
	 DWORD	A0014_R_R;
	 DWORD	A0014_R_G;
	 DWORD	A0014_R_B;
//////////////
//////////////(+15)
	 DWORD	A0015_G_A;
	 DWORD	A0015_G_R;
	 DWORD	A0015_G_G;
	 DWORD	A0015_G_B;

	 DWORD	A0015_A_A;
	 DWORD	A0015_A_R;
	 DWORD	A0015_A_G;
	 DWORD	A0015_A_B;

	 DWORD	A0015_R_A;
	 DWORD	A0015_R_R;
	 DWORD	A0015_R_G;
	 DWORD	A0015_R_B;
//////////////
//////////////(+16)
	 DWORD	A0016_G_A;
	 DWORD	A0016_G_R;
	 DWORD	A0016_G_G;
	 DWORD	A0016_G_B;

	 DWORD	A0016_A_A;
	 DWORD	A0016_A_R;
	 DWORD	A0016_A_G;
	 DWORD	A0016_A_B;

	 DWORD	A0016_R_A;
	 DWORD	A0016_R_R;
	 DWORD	A0016_R_G;
	 DWORD	A0016_R_B;
//////////////
//////////////(+17)
	 DWORD	A0017_G_A;
	 DWORD	A0017_G_R;
	 DWORD	A0017_G_G;
	 DWORD	A0017_G_B;

	 DWORD	A0017_A_A;
	 DWORD	A0017_A_R;
	 DWORD	A0017_A_G;
	 DWORD	A0017_A_B;

	 DWORD	A0017_R_A;
	 DWORD	A0017_R_R;
	 DWORD	A0017_R_G;
	 DWORD	A0017_R_B;
//////////////

	 UPGRADE_COLOR():
	 A0010_G_A (0),
	 A0010_G_R (0),
	 A0010_G_G (0),
	 A0010_G_B (0),
	
	 A0010_A_A (0),
	 A0010_A_R (0),
	 A0010_A_G (0),
	 A0010_A_B (0),
	
	 A0010_R_A (0),
	 A0010_R_R (0),
	 A0010_R_G (0),
	 A0010_R_B (0),
	//
	//11
	 A0011_G_A (0),
	 A0011_G_R (0),
	 A0011_G_G (0),
	 A0011_G_B (0),

	 A0011_A_A (0),
	 A0011_A_R (0),
	 A0011_A_G (0),
	 A0011_A_B (0),

	 A0011_R_A (0),
	 A0011_R_R (0),
	 A0011_R_G (0),
	 A0011_R_B (0),
	//
	//12
	 A0012_G_A (0),
	 A0012_G_R (0),
	 A0012_G_G (0),
	 A0012_G_B (0),

	 A0012_A_A (0),
	 A0012_A_R (0),
	 A0012_A_G (0),
	 A0012_A_B (0),

	 A0012_R_A (0),
	 A0012_R_R (0),
	 A0012_R_G (0),
	 A0012_R_B (0),
	//
	//13
	 A0013_G_A (0),
	 A0013_G_R (0),
	 A0013_G_G (0),
	 A0013_G_B (0),

	 A0013_A_A (0),
	 A0013_A_R (0),
	 A0013_A_G (0),
	 A0013_A_B (0),

	 A0013_R_A (0),
	 A0013_R_R (0),
	 A0013_R_G (0),
	 A0013_R_B (0),
	//
	//14
	 A0014_G_A (0),
	 A0014_G_R (0),
	 A0014_G_G (0),
	 A0014_G_B (0),

	 A0014_A_A (0),
	 A0014_A_R (0),
	 A0014_A_G (0),
	 A0014_A_B (0),

	 A0014_R_A (0),
	 A0014_R_R (0),
	 A0014_R_G (0),
	 A0014_R_B (0),
	//
	//15
	 A0015_G_A (0),
	 A0015_G_R (0),
	 A0015_G_G (0),
	 A0015_G_B (0),

	 A0015_A_A (0),
	 A0015_A_R (0),
	 A0015_A_G (0),
	 A0015_A_B (0),

	 A0015_R_A (0),
	 A0015_R_R (0),
	 A0015_R_G (0),
	 A0015_R_B (0),
	//
	//16
	 A0016_G_A (0),
	 A0016_G_R (0),
	 A0016_G_G (0),
	 A0016_G_B (0),

	 A0016_A_A (0),
	 A0016_A_R (0),
	 A0016_A_G (0),
	 A0016_A_B (0),

	 A0016_R_A (0),
	 A0016_R_R (0),
	 A0016_R_G (0),
	 A0016_R_B (0),
	//
	//17
	 A0017_G_A (0),
	 A0017_G_R (0),
	 A0017_G_G (0),
	 A0017_G_B (0),

	 A0017_A_A (0),
	 A0017_A_R (0),
	 A0017_A_G (0),
	 A0017_A_B (0),

	 A0017_R_A (0),
	 A0017_R_R (0),
	 A0017_R_G (0),
	 A0017_R_B (0)
	//
		
		{
		}
	};

	 extern DWORD	A0010_G_A;
	 extern DWORD	A0010_G_R;
	 extern DWORD	A0010_G_G;
	 extern DWORD	A0010_G_B;

	 extern DWORD	A0010_A_A;
	 extern DWORD	A0010_A_R;
	 extern DWORD	A0010_A_G;
	 extern DWORD	A0010_A_B;

	 extern DWORD	A0010_R_A;
	 extern DWORD	A0010_R_R;
	 extern DWORD	A0010_R_G;
	 extern DWORD	A0010_R_B;
//////////////
//////////////(+11)
	 extern DWORD	A0011_G_A;
	 extern DWORD	A0011_G_R;
	 extern DWORD	A0011_G_G;
	 extern DWORD	A0011_G_B;

	 extern DWORD	A0011_A_A;
	 extern DWORD	A0011_A_R;
	 extern DWORD	A0011_A_G;
	 extern DWORD	A0011_A_B;

	 extern DWORD	A0011_R_A;
	 extern DWORD	A0011_R_R;
	 extern DWORD	A0011_R_G;
	 extern DWORD	A0011_R_B;
//////////////
//////////////(+12)
	 extern DWORD	A0012_G_A;
	 extern DWORD	A0012_G_R;
	 extern DWORD	A0012_G_G;
	 extern DWORD	A0012_G_B;

	 extern DWORD	A0012_A_A;
	 extern DWORD	A0012_A_R;
	 extern DWORD	A0012_A_G;
	 extern DWORD	A0012_A_B;

	 extern DWORD	A0012_R_A;
	 extern DWORD	A0012_R_R;
	 extern DWORD	A0012_R_G;
	 extern DWORD	A0012_R_B;
//////////////
//////////////(+13)
	 extern DWORD	A0013_G_A;
	 extern DWORD	A0013_G_R;
	 extern DWORD	A0013_G_G;
	 extern DWORD	A0013_G_B;

	 extern DWORD	A0013_A_A;
	 extern DWORD	A0013_A_R;
	 extern DWORD	A0013_A_G;
	 extern DWORD	A0013_A_B;

	 extern DWORD	A0013_R_A;
	 extern DWORD	A0013_R_R;
	 extern DWORD	A0013_R_G;
	 extern DWORD	A0013_R_B;
//////////////
//////////////(+14)
	 extern DWORD	A0014_G_A;
	 extern DWORD	A0014_G_R;
	 extern DWORD	A0014_G_G;
	 extern DWORD	A0014_G_B;

	 extern DWORD	A0014_A_A;
	 extern DWORD	A0014_A_R;
	 extern DWORD	A0014_A_G;
	 extern DWORD	A0014_A_B;

	 extern DWORD	A0014_R_A;
	 extern DWORD	A0014_R_R;
	 extern DWORD	A0014_R_G;
	 extern DWORD	A0014_R_B;
//////////////
//////////////(+15)
	 extern DWORD	A0015_G_A;
	 extern DWORD	A0015_G_R;
	 extern DWORD	A0015_G_G;
	 extern DWORD	A0015_G_B;

	 extern DWORD	A0015_A_A;
	 extern DWORD	A0015_A_R;
	 extern DWORD	A0015_A_G;
	 extern DWORD	A0015_A_B;

	 extern DWORD	A0015_R_A;
	 extern DWORD	A0015_R_R;
	 extern DWORD	A0015_R_G;
	 extern DWORD	A0015_R_B;
//////////////
//////////////(+16)
	 extern DWORD	A0016_G_A;
	 extern DWORD	A0016_G_R;
	 extern DWORD	A0016_G_G;
	 extern DWORD	A0016_G_B;

	 extern DWORD	A0016_A_A;
	 extern DWORD	A0016_A_R;
	 extern DWORD	A0016_A_G;
	 extern DWORD	A0016_A_B;

	 extern DWORD	A0016_R_A;
	 extern DWORD	A0016_R_R;
	 extern DWORD	A0016_R_G;
	 extern DWORD	A0016_R_B;
//////////////
//////////////(+17)
	 extern DWORD	A0017_G_A;
	 extern DWORD	A0017_G_R;
	 extern DWORD	A0017_G_G;
	 extern DWORD	A0017_G_B;

	 extern DWORD	A0017_A_A;
	 extern DWORD	A0017_A_R;
	 extern DWORD	A0017_A_G;
	 extern DWORD	A0017_A_B;

	 extern DWORD	A0017_R_A;
	 extern DWORD	A0017_R_R;
	 extern DWORD	A0017_R_G;
	 extern DWORD	A0017_R_B;
//////////////

	BOOL	GRINDCOLOR_LOADFILE ();
};


class UpgradeColor
{
public:

public:

protected:
	UpgradeColor(void);

public:
	~UpgradeColor(void);

public:
	static UpgradeColor& GetInstance();
};
