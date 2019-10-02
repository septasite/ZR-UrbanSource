///////////////////////////////////////////////////////////////////////
//	UIControl 매크로 정의
//
//	최초 작성자 : 서보건
//	이후 수정자 : 성기엽
//	로그
//		[2003.10.31] - 메시지 구조 변경 ( WORD-->DWORD )
//					 메시지 조합 함수 작성, 매시지 재정의.
//		[2003.8.6] - 메시지 및 기본 매크로 정의
//					 UIControl.h에 것을 따로 떼어서 작성
//
///////////////////////////////////////////////////////////////////////

#pragma	once

#include "DxInputDevice.h"

const BYTE BIT_8 = 8;
const BYTE BIT_16= 16;
const BYTE BIT_24= 24;

DWORD MAKE_UIMSG ( WORD HIGHMSG, WORD LOWMSG );
DWORD MAKE_UIMSG ( BYTE HIGHMSG1, BYTE HIGHMSG2, BYTE LOWMSG1, BYTE LOWMSG2 );
BOOL CHECK_LB_DOWN_LIKE ( DWORD dwMsg );
BOOL CHECK_LB_UP_LIKE ( DWORD dwMsg );
BOOL CHECK_MB_DOWN_LIKE ( DWORD dwMsg );
BOOL CHECK_MB_UP_LIKE ( DWORD dwMsg );
BOOL CHECK_RB_DOWN_LIKE ( DWORD dwMsg );
BOOL CHECK_RB_UP_LIKE ( DWORD dwMsg );
BOOL CHECK_MOUSE_IN ( DWORD dwMsg );
BOOL CHECK_MODAL_ON ( DWORD dwMsg );
BOOL CHECK_FOCUSED ( DWORD dwMsg );
BOOL CHECK_KEYFOCUSED ( DWORD dwMsg );
BOOL CHECK_MOUSEIN_LBUPLIKE ( DWORD dwMsg );
BOOL CHECK_MOUSE_IN_LBDOWNLIKE ( DWORD dwMsg );
BOOL CHECK_MOUSEIN_MBUPLIKE ( DWORD dwMsg );
BOOL CHECK_MOUSE_IN_MBDOWNLIKE ( DWORD dwMsg );
BOOL CHECK_MOUSEIN_RBUPLIKE ( DWORD dwMsg );
BOOL CHECK_MOUSE_IN_RBDOWNLIKE ( DWORD dwMsg );
BOOL CHECK_TOPARENT ( DWORD dwMsg );
DWORD CUT_LOW24BIT ( DWORD dwMsg );

//	기본키
const BYTE MOUSE_KEY_DOWN		= (DXKEY_DOWN);
const BYTE MOUSE_KEY_PRESSED	= (DXKEY_PRESSED);
const BYTE MOUSE_KEY_DRAG		= (DXKEY_DRAG);
const BYTE MOUSE_KEY_UP			= (DXKEY_UP);
const BYTE MOUSE_KEY_DUP		= (DXKEY_DUP);

//	메시지 없음
const DWORD UIMSG_NOMESSAGE	= MAKE_UIMSG ( 0x00, 0x00, 0x00, 0x00 );

//	최상위 부모까지 전달되어야하는 메시지
const DWORD UIMSG_TOTOPPARENT	= MAKE_UIMSG ( 0x00, 0x00, 0x00, 0x01 );

//	마우스 왼쪽 버튼
const DWORD UIMSG_LB_DOWN	= MAKE_UIMSG ( 0x00, 0x00, 0x00, MOUSE_KEY_DOWN );
const DWORD UIMSG_LB_PRESEED= MAKE_UIMSG ( 0x00, 0x00, 0x00, MOUSE_KEY_PRESSED );
const DWORD UIMSG_LB_DRAG	= MAKE_UIMSG ( 0x00, 0x00, 0x00, MOUSE_KEY_DRAG );
const DWORD UIMSG_LB_UP		= MAKE_UIMSG ( 0x00, 0x00, 0x00, MOUSE_KEY_UP );
const DWORD UIMSG_LB_DUP	= MAKE_UIMSG ( 0x00, 0x00, 0x00, MOUSE_KEY_DUP );

//	마우스 위치
const DWORD UIMSG_MOUSEIN	= MAKE_UIMSG ( 0x00, 0x00, 0x00, 0x40 );
const DWORD UIMSG_MOUSEOUT	= MAKE_UIMSG ( 0x00, 0x00, 0x00, 0x80 );

//	컨트롤 포커스
const DWORD UIMSG_FOCUSED	= MAKE_UIMSG ( 0x00, 0x00, 0x01, 0x00 );

//	마우스 중간 버튼
const DWORD UIMSG_MB_DOWN	= MAKE_UIMSG ( 0x00, 0x00, MOUSE_KEY_DOWN, 0x00 );
const DWORD UIMSG_MB_PRESSED= MAKE_UIMSG ( 0x00, 0x00, MOUSE_KEY_PRESSED, 0x00 );
const DWORD UIMSG_MB_DRAG	= MAKE_UIMSG ( 0x00, 0x00, MOUSE_KEY_DRAG, 0x00 );
const DWORD UIMSG_MB_UP		= MAKE_UIMSG ( 0x00, 0x00, MOUSE_KEY_UP, 0x00 );
const DWORD UIMSG_MB_DUP	= MAKE_UIMSG ( 0x00, 0x00, MOUSE_KEY_DUP, 0x00 );

//	모달 메시지
const DWORD UIMSG_MODAL_ON		= MAKE_UIMSG ( 0x00, 0x00, 0x40, 0x00 );
const DWORD UIMSG_MODAL_OK		= MAKE_UIMSG ( 0x00, 0x00, 0x80, 0x00 );
const DWORD UIMSG_MODAL_CANCEL	= MAKE_UIMSG ( 0x00, 0x01, 0x00, 0x00 );

//	마우스 오른쪽 버튼
const DWORD UIMSG_RB_DOWN	= MAKE_UIMSG ( 0x00, MOUSE_KEY_DOWN, 0x00, 0x00 );
const DWORD UIMSG_RB_PRESSED= MAKE_UIMSG ( 0x00, MOUSE_KEY_PRESSED, 0x00, 0x00 );
const DWORD UIMSG_RB_DRAG	= MAKE_UIMSG ( 0x00, MOUSE_KEY_DRAG, 0x00, 0x00 );
const DWORD UIMSG_RB_UP		= MAKE_UIMSG ( 0x00, MOUSE_KEY_UP, 0x00, 0x00 );
const DWORD UIMSG_RB_DUP	= MAKE_UIMSG ( 0x00, MOUSE_KEY_DUP, 0x00, 0x00 );

//	키보드 단축키
const DWORD UIMSG_KEY_FOCUSED = MAKE_UIMSG ( 0x00, 0x40, 0x00, 0x00 );

//	예약된 메시지
const DWORD UIMSG_SCROLL	= MAKE_UIMSG ( 0x00, 0x80, 0x00, 0x00 );
//const DWORD UIMSG_INVISIBLE = MAKE_UIMSG ( 0x02, 0x00, 0x00, 0x00 );
//const DWORD UIMSG_VISIBLE	= MAKE_UIMSG ( 0x00, 0x80, 0x00, 0x00 );

//	예약된 메시지
const DWORD UIMSG_USER1	= MAKE_UIMSG ( 0x01, 0x00, 0x00, 0x00 );
const DWORD UIMSG_USER2	= MAKE_UIMSG ( 0x02, 0x00, 0x00, 0x00 );
const DWORD UIMSG_USER3 = MAKE_UIMSG ( 0x04, 0x00, 0x00, 0x00 );
const DWORD UIMSG_USER4 = MAKE_UIMSG ( 0x08, 0x00, 0x00, 0x00 );
const DWORD UIMSG_USER5 = MAKE_UIMSG ( 0x10, 0x00, 0x00, 0x00 );
const DWORD UIMSG_USER6 = MAKE_UIMSG ( 0x20, 0x00, 0x00, 0x00 );
const DWORD UIMSG_USER7 = MAKE_UIMSG ( 0x40, 0x00, 0x00, 0x00 );
const DWORD UIMSG_USER8 = MAKE_UIMSG ( 0x80, 0x00, 0x00, 0x00 );