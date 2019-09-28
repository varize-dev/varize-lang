#ifndef JUDGE_SYSTEM_H
#define JUDGE_SYSTEM_H
#if defined(__linux__) || defined(__linux)  // Linux
#define OS_LINUX
#elif !defined(SAG_COM) &&                                                     \
    (!defined(WINAPI_FAMILY) || WINAPI_FAMILY == WINAPI_FAMILY_DESKTOP_APP) && \
    (defined(WIN64) || defined(_WIN64) || defined(__WIN64__))  // Windows
#define OS_WIN32
#define OS_WIN64
#elif !defined(SAG_COM) && (defined(WIN32) || defined(_WIN32) || \
                            defined(__WIN32__) || defined(__NT__))
#if defined(WINAPI_FAMILY)
#ifndef WINAPI_FAMILY_PC_APP
#define WINAPI_FAMILY_PC_APP WINAPI_FAMILY_APP
#endif
#if defined(WINAPI_FAMILY_PHONE_APP) && WINAPI_FAMILY == WINAPI_FAMILY_PHONE_APP
#define OS_WINRT
#elif WINAPI_FAMILY == WINAPI_FAMILY_PC_APP
#define OS_WINRT
#else
#define OS_WIN32
#endif
#else
#define OS_WIN32
#endif
#else
#error "OS not supported"
#endif
