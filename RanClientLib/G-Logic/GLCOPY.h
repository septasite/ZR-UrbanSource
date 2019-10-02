#ifndef GLCOPY_H_
#define GLCOPY_H_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "./GLCharDefine.h"
#include "../../NetClientLib/s_NetGlobal.h"
#include "../../EngineLib/G-Logic/GLDefine.h"

// struct NET_MSG_GENERIC;

class GLCOPY
{
public:
	virtual EMCROW GetCrow () const = 0;
	virtual DWORD GetCtrlID () const = 0;
	virtual DWORD GetCharID () const { return 0; }
	virtual const char* GetName () const = 0;

public:
	virtual BOOL IsACTION ( EMACTIONTYPE emCur ) = 0;
	virtual BOOL IsPartyMaster ()	{ return FALSE; }
	virtual BOOL IsPartyMem ()		{ return FALSE; }
	virtual BOOL IsClubMaster ()	{ return FALSE; }
	virtual BOOL IsCDCertify ()		{ return FALSE; }
	virtual bool IsSafeZone ()	const { return false; }

public:
	virtual WORD GetBodyRadius () = 0;
	virtual float GetBodyHeight () = 0;
	//Added by   | 18-7-2012 | add mouse effect code
	virtual float GetScale () = 0;
	virtual DxSkinChar* GetSkinCharF () = 0;
	virtual const D3DXVECTOR3 &GetPosition () = 0;
	virtual D3DXVECTOR3 GetPosBodyHeight () = 0;
	virtual GLPWDATA GetHp () const = 0;
	virtual GLPWDATA GetHpSg () const = 0;
	virtual GLPWDATA GetHpMp () const = 0;
	virtual GLPWDATA GetHpPhx () const = 0;
	virtual WORD GetSchool() const = 0;
public:
	//Added by   | 21-6-2012 | Bypass damage
	//virtual void ReceiveDamage ( WORD wDamage, DWORD dwDamageFlag, STARGETID sACTOR ) = 0;
	virtual void ReceiveDamage ( DWORD wDamage, DWORD dwDamageFlag, STARGETID sACTOR ) = 0;
	virtual void ReceiveAVoid () = 0;
	virtual void ReceiveSwing () = 0;

public:
	virtual void MsgProcess ( NET_MSG_GENERIC* nmg ) = 0;
};

#endif // GLCOPY_H_