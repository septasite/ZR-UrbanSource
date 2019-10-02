

/* this ALWAYS GENERATED file contains the definitions for the interfaces */


 /* File created by MIDL compiler version 6.00.0361 */
/* at Fri Oct 19 18:36:19 2012
 */
/* Compiler settings for .\MinWebLauncher.idl:
    Oicf, W1, Zp8, env=Win32 (32b run)
    protocol : dce , ms_ext, c_ext, robust
    error checks: allocation ref bounds_check enum stub_data 
    VC __declspec() decoration level: 
         __declspec(uuid()), __declspec(selectany), __declspec(novtable)
         DECLSPEC_UUID(), MIDL_INTERFACE()
*/
//@@MIDL_FILE_HEADING(  )

#pragma warning( disable: 4049 )  /* more than 64k source lines */


/* verify that the <rpcndr.h> version is high enough to compile this file*/
#ifndef __REQUIRED_RPCNDR_H_VERSION__
#define __REQUIRED_RPCNDR_H_VERSION__ 475
#endif

#include "rpc.h"
#include "rpcndr.h"

#ifndef __RPCNDR_H_VERSION__
#error this stub requires an updated version of <rpcndr.h>
#endif // __RPCNDR_H_VERSION__


#ifndef __MinWebLauncheridl_h__
#define __MinWebLauncheridl_h__

#if defined(_MSC_VER) && (_MSC_VER >= 1020)
#pragma once
#endif

/* Forward Declarations */ 

#ifndef ___DMinWebLauncher_FWD_DEFINED__
#define ___DMinWebLauncher_FWD_DEFINED__
typedef interface _DMinWebLauncher _DMinWebLauncher;
#endif 	/* ___DMinWebLauncher_FWD_DEFINED__ */


#ifndef ___DMinWebLauncherEvents_FWD_DEFINED__
#define ___DMinWebLauncherEvents_FWD_DEFINED__
typedef interface _DMinWebLauncherEvents _DMinWebLauncherEvents;
#endif 	/* ___DMinWebLauncherEvents_FWD_DEFINED__ */


#ifndef __MinWebLauncher_FWD_DEFINED__
#define __MinWebLauncher_FWD_DEFINED__

#ifdef __cplusplus
typedef class MinWebLauncher MinWebLauncher;
#else
typedef struct MinWebLauncher MinWebLauncher;
#endif /* __cplusplus */

#endif 	/* __MinWebLauncher_FWD_DEFINED__ */


#ifdef __cplusplus
extern "C"{
#endif 

void * __RPC_USER MIDL_user_allocate(size_t);
void __RPC_USER MIDL_user_free( void * ); 


#ifndef __MinWebLauncherLib_LIBRARY_DEFINED__
#define __MinWebLauncherLib_LIBRARY_DEFINED__

/* library MinWebLauncherLib */
/* [control][helpstring][helpfile][version][uuid] */ 


EXTERN_C const IID LIBID_MinWebLauncherLib;

#ifndef ___DMinWebLauncher_DISPINTERFACE_DEFINED__
#define ___DMinWebLauncher_DISPINTERFACE_DEFINED__

/* dispinterface _DMinWebLauncher */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DMinWebLauncher;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("B0242861-6F9F-499F-8A8D-9B53F2A80568")
    _DMinWebLauncher : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMinWebLauncherVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMinWebLauncher * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMinWebLauncher * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMinWebLauncher * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMinWebLauncher * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMinWebLauncher * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMinWebLauncher * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMinWebLauncher * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DMinWebLauncherVtbl;

    interface _DMinWebLauncher
    {
        CONST_VTBL struct _DMinWebLauncherVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMinWebLauncher_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DMinWebLauncher_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DMinWebLauncher_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DMinWebLauncher_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DMinWebLauncher_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DMinWebLauncher_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DMinWebLauncher_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMinWebLauncher_DISPINTERFACE_DEFINED__ */


#ifndef ___DMinWebLauncherEvents_DISPINTERFACE_DEFINED__
#define ___DMinWebLauncherEvents_DISPINTERFACE_DEFINED__

/* dispinterface _DMinWebLauncherEvents */
/* [helpstring][uuid] */ 


EXTERN_C const IID DIID__DMinWebLauncherEvents;

#if defined(__cplusplus) && !defined(CINTERFACE)

    MIDL_INTERFACE("55FE2265-552A-4624-A71A-BDA0B966DA9C")
    _DMinWebLauncherEvents : public IDispatch
    {
    };
    
#else 	/* C style interface */

    typedef struct _DMinWebLauncherEventsVtbl
    {
        BEGIN_INTERFACE
        
        HRESULT ( STDMETHODCALLTYPE *QueryInterface )( 
            _DMinWebLauncherEvents * This,
            /* [in] */ REFIID riid,
            /* [iid_is][out] */ void **ppvObject);
        
        ULONG ( STDMETHODCALLTYPE *AddRef )( 
            _DMinWebLauncherEvents * This);
        
        ULONG ( STDMETHODCALLTYPE *Release )( 
            _DMinWebLauncherEvents * This);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfoCount )( 
            _DMinWebLauncherEvents * This,
            /* [out] */ UINT *pctinfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetTypeInfo )( 
            _DMinWebLauncherEvents * This,
            /* [in] */ UINT iTInfo,
            /* [in] */ LCID lcid,
            /* [out] */ ITypeInfo **ppTInfo);
        
        HRESULT ( STDMETHODCALLTYPE *GetIDsOfNames )( 
            _DMinWebLauncherEvents * This,
            /* [in] */ REFIID riid,
            /* [size_is][in] */ LPOLESTR *rgszNames,
            /* [in] */ UINT cNames,
            /* [in] */ LCID lcid,
            /* [size_is][out] */ DISPID *rgDispId);
        
        /* [local] */ HRESULT ( STDMETHODCALLTYPE *Invoke )( 
            _DMinWebLauncherEvents * This,
            /* [in] */ DISPID dispIdMember,
            /* [in] */ REFIID riid,
            /* [in] */ LCID lcid,
            /* [in] */ WORD wFlags,
            /* [out][in] */ DISPPARAMS *pDispParams,
            /* [out] */ VARIANT *pVarResult,
            /* [out] */ EXCEPINFO *pExcepInfo,
            /* [out] */ UINT *puArgErr);
        
        END_INTERFACE
    } _DMinWebLauncherEventsVtbl;

    interface _DMinWebLauncherEvents
    {
        CONST_VTBL struct _DMinWebLauncherEventsVtbl *lpVtbl;
    };

    

#ifdef COBJMACROS


#define _DMinWebLauncherEvents_QueryInterface(This,riid,ppvObject)	\
    (This)->lpVtbl -> QueryInterface(This,riid,ppvObject)

#define _DMinWebLauncherEvents_AddRef(This)	\
    (This)->lpVtbl -> AddRef(This)

#define _DMinWebLauncherEvents_Release(This)	\
    (This)->lpVtbl -> Release(This)


#define _DMinWebLauncherEvents_GetTypeInfoCount(This,pctinfo)	\
    (This)->lpVtbl -> GetTypeInfoCount(This,pctinfo)

#define _DMinWebLauncherEvents_GetTypeInfo(This,iTInfo,lcid,ppTInfo)	\
    (This)->lpVtbl -> GetTypeInfo(This,iTInfo,lcid,ppTInfo)

#define _DMinWebLauncherEvents_GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)	\
    (This)->lpVtbl -> GetIDsOfNames(This,riid,rgszNames,cNames,lcid,rgDispId)

#define _DMinWebLauncherEvents_Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)	\
    (This)->lpVtbl -> Invoke(This,dispIdMember,riid,lcid,wFlags,pDispParams,pVarResult,pExcepInfo,puArgErr)

#endif /* COBJMACROS */


#endif 	/* C style interface */


#endif 	/* ___DMinWebLauncherEvents_DISPINTERFACE_DEFINED__ */


EXTERN_C const CLSID CLSID_MinWebLauncher;

#ifdef __cplusplus

class DECLSPEC_UUID("5FFFA267-0B81-42B4-BE64-77B5C9FE287F")
MinWebLauncher;
#endif
#endif /* __MinWebLauncherLib_LIBRARY_DEFINED__ */

/* Additional Prototypes for ALL interfaces */

/* end of Additional Prototypes */

#ifdef __cplusplus
}
#endif

#endif


