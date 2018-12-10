#ifndef FLAC__EXPORT_H
#define FLAC__EXPORT_H

/**
 * include/FLAC/export.h
 * This module contains #define and symbols for exporting function
 * calls, and providing version information and compiled-in features.
 * 
 * If you are compiling with MSVC and will link to the static library
 * (libFLAC.lib) you should define FLAC__NO_DLL in your project to 
 * make sure the symbols are exported properly.
 */

// 定义一个变量，和Ogg容器相关。

#if defined(FLAC__NO_DLL)
#define FLAC_API

#elif defined(_MSC_VER)
#ifdef FLAC_API_EXPORTS
#define	FLAC_API __declspec(dllexport)
#else
#define FLAC_API __declspec(dllimport)
#endif

#elif defined(FLAC__USE_VISIBILITY_ATTR)
#define FLAC_API __attribute__ ((visibility ("default")))

#else
#define FLAC_API

#endif

#define FLAC_API_VERSION_CURRENT 11
#define FLAC_API_VERSION_REVISION 0 /**< see above */
#define FLAC_API_VERSION_AGE 3 /**< see above */


#ifdef __cplusplus
extern "C" {
#endif

/** 1 if the library has been compiled with support for Ogg FLAC, else 0. */
extern FLAC_API int FLAC_API_SUPPORTS_OGG_FLAC;

#ifdef __cplusplus
}
#endif

#endif // !FLAC__EXPORT_H