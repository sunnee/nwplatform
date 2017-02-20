//
//  NW PLATFORM
//
//  Copyright (c) 2006-2014 Alexandr Kavalchuk (nWaves).
//  All rights reserved.
//

#ifndef __NW_PLATFORM__
#define __NW_PLATFORM__

//==========================COMPILER=================================
#if   (defined(__clang__) || (__APPLE_CC__ >= 6000))
    #define NW_COMPILER_CLANG 1
#elif (defined(_MSC_VER))
	#define NW_COMPILER_MSVC 1
#elif (defined(__INTEL_COMPILER)
    #define NW_COMPILER_INTEL 1
#elif (defined(__GNUC__))
    #define NW_COMPILER_GCC 1
#else
	#error unknown compiler
#endif

//==========================TARGET_SYSTEM============================
#if (defined(_WIN32) || defined(__WIN32__) || defined(WIN32) || defined (_WIN64))

	#define NW_SYSTEM_WIN32   1
    #define NW_SYSTEM_WINDOWS 1

#elif (defined(__APPLE__) || defined(__OSX__) || TARGET_OS_MAC)

    #define NW_SYSTEM_APPLE 1
    #define NW_SYSTEM_UNIX  1

#elif (defined(__FreeBSD__) || defined(__OpenBSD__))

    #define NW_SYSTEM_BSD  1
    #define NW_SYSTEM_UNIX 1

#elif (defined(__linux) || defined(__linux__))

    #define NW_SYSTEM_LINUX 1
    #define NW_SYSTEM_UNIX  1

#else
    #error unknown system
#endif

//===============================WIN32==================================
#if NW_SYSTEM_WIN32

  #ifdef _MSC_VER
    #ifdef _WIN64
      #define NW_SYSTEM_64BIT 1
    #else
      #define NW_SYSTEM_32BIT 1
    #endif
  #endif

  #define NW_SYSTEM_LITTLE_ENDIAN 1
#endif

//===============================APPLE==================================
#if NW_SYSTEM_APPLE

    #if (!defined(NDEBUG) || defined(_DEBUG))
        #define NW_DEBUG 1
    #endif

    #include <machine/endian.h>
    #include <CoreFoundation/CoreFoundation.h>

    #if (TARGET_IPHONE_SIMULATOR || TARGET_OS_IPHONE)
        #define NW_SYSTEM_IOS 1
    #else
        #define NW_SYSTEM_OSX 1
    #endif

    #include <AvailabilityMacros.h>
    #include <Availability.h>

#endif

//=============================BSD=====================================
#if NW_SYSTEM_BSD
    #include <sys/endian.h>
#endif

//=============================LINUX=====================================
#if NW_SYSTEM_LINUX
  #include <endian.h>
#endif

//=============================*NUX=====================================
#if NW_SYSTEM_UNIX

    #ifdef BYTE_ORDER
        #if (BYTE_ORDER == LITTLE_ENDIAN)
            #define NW_SYSTEM_LITTLE_ENDIAN 1
        #elif (BYTE_ORDER == BIG_ENDIAN)
            #define NW_SYSTEM_BIG_ENDIAN 1
        #endif
    #endif

    #if (defined(__LP64__))
        #define NW_SYSTEM_64BIT 1
    #else
        #define NW_SYSTEM_32BIT 1
    #endif

#endif

//=============================ALL=====================================
#if (!defined(NW_DEBUG) || defined(_DEBUG))
    #define NW_DEBUG 1
#endif

#if (NW_SYSTEM_LITTLE_ENDIAN)
    #define NW_SYSTEM_BIG_ENDIAN 0
#elif (NW_SYSTEM_BIG_ENDIAN)
    #define NW_SYSTEM_LITTLE_ENDIAN 0
#elif (!defined(NW_SYSTEM_LITTLE_ENDIAN) && !defined(NW_SYSTEM_BIG_ENDIAN))

    #define NW_ENDIAN_TEST          (*((const uint32_t*)((const uint8_t*)"\x01\x02\x03\x04")))

    #define NW_SYSTEM_BIG_ENDIAN    (NW_ENDIAN_TEST == (uint32_t)0x01020304)
    #define NW_SYSTEM_LITTLE_ENDIAN (NW_ENDIAN_TEST == (uint32_t)0x04030201)
#endif




#if (NW_SYSTEM_64BIT)
    #define NW_SYSTEM_32BIT 0
#elif (NW_SYSTEM_32BIT)
    #define NW_SYSTEM_64BIT 0
#elif (!defined(NW_SYSTEM_64BIT) && !defined(NW_SYSTEM_32BIT))
    #define NW_SYSTEM_64BIT (sizeof(void*) >= 8)
    #define NW_SYSTEM_32BIT (sizeof(void*) <= 4)
#endif

#if __cplusplus
# define THREAD_LOCAL _Thread_local
#else
# if (NW_SYSTEM_WINDOWS || NW_COMPILER_MSVC)
#  define THREAD_LOCAL __declspec(thread)
# else
#  define THREAD_LOCAL __thread
# endif
#endif

#include "nwtypes.h"

#if (NW_COMPILER_CLANG || NW_COMPILER_GCC)

    #define NW_PACKET_START_DEF
    #define NW_PACKET_ATTR      __attribute__((aligned(1), packed))
    #define NW_PACKET_END_DEF

#elif (NW_COMPILER_MSVC)

    #define NW_PACKET_START_DEF  __pragma(pack(push, 1))
    #define NW_PACKET_ATTR       __attribute__((aligned(1), packed))
    #define NW_PACKET_END_DEF    __pragma(pack(pop))

#else
    #error not supported packed struct for using compiler
#endif

#define NW_PACKET_START NW_PACKET_START_DEF typedef struct NW_PACKET_ATTR
#define NW_PACKET_END(_NW_PACKET_NAME_) _NW_PACKET_NAME_ NW_PACKET_END_DEF

#include "nwstdheaders.h"
#include "nwmacro.h"
#include "nwosversion.h"

#define NW_PLATFORM_MAKE_VERSION(MAJOR,MINOR,PATCH)       ((MAJOR*1000*1000) + (MINOR*1000) + PATCH)

#define NW_PLATFORM_VERSION_1_0_1      NW_PLATFORM_MAKE_VERSION(1,0,1)
#define NW_PLATFORM_VERSION_1_0_2      NW_PLATFORM_MAKE_VERSION(1,0,2)

#define NW_PLATFORM_CURRENT_VERSION    NW_PLATFORM_VERSION_1_0_2

#endif /* __NW_PLATFORM__ */
