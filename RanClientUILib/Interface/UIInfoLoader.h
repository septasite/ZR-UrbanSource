#pragma	once

struct	SITEMCUSTOM;
struct  SNATIVEID;

namespace	NS_ITEMINFO
{
	void	RESET ();
	void	LOAD ( const SITEMCUSTOM &sItemCustom, const BOOL bShopOpen, const BOOL bInMarket, const BOOL bInPrivateMarket, const BOOL bIsWEAR_ITEM, WORD wPosX, WORD wPosY, SNATIVEID sNpcNativeID, BOOL bITEMLINK );
	void	LOAD_SIMPLE ( const SITEMCUSTOM &sItemCustom );
	void    ResetItemRender ();  
};

struct	GLSKILL;
struct	SCHARSKILL;
struct	SNATIVEID;

namespace	NS_SKILLINFO
{
	void	RESET ();
	void	LOAD ( const SNATIVEID& sNativeID, const BOOL bNextLevel, bool bLink = false );
};

struct STARGETID;
namespace	NS_CROWINFO
{
	void	RESET();
	void	LOADCROW ( STARGETID sTargetID );
};

namespace	NS_ITEMINFO_BOXINFO
{
	void	RESET ();
	void	LOAD ( const SITEMCUSTOM &sItemCustom, const BOOL bShopOpen, const BOOL bInMarket, const BOOL bInPrivateMarket, const BOOL bIsWEAR_ITEM, WORD wPosX, WORD wPosY, SNATIVEID sNpcNativeID );
	void	LOAD_SIMPLE ( const SITEMCUSTOM &sItemCustom );
	void    ResetItemRender ();  
};