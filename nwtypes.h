//
//  NW TYPES
//
//  Copyright (c) 2006-2014 Alexandr Kavalchuk (nWaves).
//  All rights reserved.
//

#ifndef __NW_TYPES__
#define __NW_TYPES__

#ifdef NW_COMPILER_MSVC
    #if (_MSC_VER < 1300)
        #error unsuported msvc compiler version
    #endif

    #if (_MSC_VER < 1600) //2010
        typedef signed   __int8   int8_t;
        typedef signed   __int16  int16_t;
        typedef signed   __int32  int32_t;
        typedef unsigned __int8   uint8_t;
        typedef unsigned __int16  uint16_t;
        typedef unsigned __int32  uint32_t;

        typedef signed   __int64  int64_t;
        typedef unsigned __int64  uint64_t;

        #define NW_STDINT_USE 1
    #else
        //Standart from MS
        #include <stdint.h>
        #define NW_STDINT_USE 1

        #if ((__cplusplus) && (_MSC_VER >= 1700)) //2012
            #include <cstdint>
        #endif
    #endif
#endif

#ifdef NW_COMPILER_CLANG
    #include <sys/types.h>
    #include <stdint.h>
    #define NW_STDINT_USE 1
#endif

#if (!NW_STDINT_USE)

    #if (!defined(_INT8_T) && 1)
        #define _INT8_T
        typedef signed char   int8_t;
    #endif

    #if (!defined(_UINT8_T) && 1)
        #define _UINT8_T
        typedef unsigned long uint8_t;
    #endif

    #if (!defined(_INT16_T) && 1)
        #define _INT16_T
        typedef signed short   int16_t;
    #endif

    #if (!defined(_UINT16_T) && 1)
        #define _UINT16_T
        typedef unsigned short uint16_t;
    #endif

    #if (!defined(_INT32_T) && 1)
        #define _INT32_T
        typedef signed int int32_t;
    #endif

    #if (!defined(_UINT32_T) && 1)
        #define _UINT32_T
        typedef unsigned int uint32_t;
    #endif

    #if (!defined(_INT64_T) && 1)
        #define _INT64_T
        typedef signed long long int64_t;
    #endif

    #if (!defined(_UINT64_T) && 1)
        #define _UINT64_T
        typedef unsigned int uint64_t;
    #endif
#endif

#if (NW_COMPILER_MSVC || NW_COMPILER_INTEL)

    #ifndef INT64_C
        #define INT64_C(value) (value##i64)
    #endif

    #ifndef UINT64_C
        #define UINT64_C(value) (value##ui64)
    #endif
#else
    #ifndef INT64_C
        #define INT64_C(value) (value##LL)
    #endif

    #ifndef UINT64_C
        #define UINT64_C(value) (value##ULL)
    #endif
#endif

#if NW_SYSTEM_64BIT
    typedef int64_t     platform_int_t;
    typedef uint64_t    platform_uint_t;
#else
    typedef int32_t     platform_int_t;
    typedef uint32_t    platform_uint_t;
#endif


#endif /* __NW_TYPES__ */
