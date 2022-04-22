#pragma once

#ifdef SE_EXPORT
    #ifdef _MSC_VER
        #define SE_API __declspec(dllexport)
    #else
        #define SE_API
    #endif
#else
    #ifdef _MSC_VER
        #define SE_API __declspec(dllimport)
    #else
        #define SE_API
    #endif
#endif
