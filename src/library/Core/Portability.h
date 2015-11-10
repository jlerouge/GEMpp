#ifndef __PORTABILITY_H__
#define __PORTABILITY_H__

// Cross-platform compilation
#if defined(WIN32) || defined(WIN64) // Windows platform
    #ifdef DLL_BUILD
            #define DLL_EXPORT __declspec(dllexport)
    #else
            #define DLL_EXPORT
    #endif
    #define GETPID _getpid
    #ifndef INFINITY
        #define INFINITY HUGE_VAL
    #endif
#elif defined(LINUX) && (__GNUC__ >= 4) // Linux platform
	#define DLL_EXPORT __attribute__ ((visibility ("default")))
	#define GETPID getpid
#else
	#define DLL_EXPORT
	#define GETPID getpid
#endif

#endif /* __PORTABILITY_H__ */
