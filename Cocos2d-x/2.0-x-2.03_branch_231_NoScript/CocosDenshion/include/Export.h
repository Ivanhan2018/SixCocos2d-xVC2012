#ifndef __EXPORT_COMMON__
#define __EXPORT_COMMON__

#if defined(SHP)
    #include <FBaseConfig.h>
    #define EXPORT_DLL  _EXPORT_
#elif defined(_WIN32)
    #if defined(_USRDLL)
    #define EXPORT_DLL     __declspec(dllexport)
    #elif defined(_USRLIB)
    #define EXPORT_DLL
    #else         /* use a DLL library */
    #define EXPORT_DLL     __declspec(dllimport)
    #endif
#else
    #if defined(_SHARED_)
    #define EXPORT_DLL     __attribute__((visibility("default")))
    #elif defined(IGNORE_EXPORT)
    #define EXPORT_DLL
    #else
    #define EXPORT_DLL
    #endif
#endif 

// 使用DirectSound实现
// Cool.Cat
#ifdef WIN32
#define USING_DSOUND
#endif

#endif    // end of __EXPORT_COMMON__
