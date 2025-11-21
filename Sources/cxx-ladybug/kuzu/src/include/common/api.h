#pragma once

// Helpers
#if defined _WIN32 || defined __CYGWIN__
#define LADYBUG_HELPER_DLL_IMPORT __declspec(dllimport)
#define LADYBUG_HELPER_DLL_EXPORT __declspec(dllexport)
#define LADYBUG_HELPER_DLL_LOCAL
#define LADYBUG_HELPER_DEPRECATED __declspec(deprecated)
#else
#define LADYBUG_HELPER_DLL_IMPORT __attribute__((visibility("default")))
#define LADYBUG_HELPER_DLL_EXPORT __attribute__((visibility("default")))
#define LADYBUG_HELPER_DLL_LOCAL __attribute__((visibility("hidden")))
#define LADYBUG_HELPER_DEPRECATED __attribute__((__deprecated__))
#endif

#ifdef LADYBUG_STATIC_DEFINE
#define LADYBUG_API
#else
#ifndef LADYBUG_API
#ifdef LADYBUG_EXPORTS
/* We are building this library */
#define LADYBUG_API LADYBUG_HELPER_DLL_EXPORT
#else
/* We are using this library */
#define LADYBUG_API LADYBUG_HELPER_DLL_IMPORT
#endif
#endif
#endif

#ifndef LADYBUG_DEPRECATED
#define LADYBUG_DEPRECATED LADYBUG_HELPER_DEPRECATED
#endif

#ifndef LADYBUG_DEPRECATED_EXPORT
#define LADYBUG_DEPRECATED_EXPORT LADYBUG_API LADYBUG_DEPRECATED
#endif
