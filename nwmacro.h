//
//  NW MACRO
//
//  Copyright (c) 2006-2014 Alexandr Kavalchuk (nWaves).
//  All rights reserved.
//

#ifndef __NW_MACRO__
#define __NW_MACRO__

#ifndef NULL
    #define NULL 0
#endif

#if __cplusplus
    #define EXTERN_C extern "C"
#else
    #define EXTERN_C
#endif

#if NW_COMPILER_MSVC
	#define INLINE __inline
#elif __cplusplus
    #define INLINE inline
#else
    #define INLINE
#endif

#if NW_COMPILER_MSVC
    #define INLINE_FORCE __forceinline
#elif NW_COMPILER_CLANG || NW_COMPILER_GCC
    #define INLINE_FORCE __inline__ __attribute__((always_inline))
#else
    #define INLINE_FORCE INLINE
#endif

#define OPTION_IS_SET(VALUE, OPTION)   (((VALUE) & (OPTION)) != 0)
#define OPTION_IS_UNSET(VALUE, OPTION) (((VALUE) & (OPTION)) == 0)

#define OPTION_SET(VALUE, OPTION)   (VALUE) = ((VALUE)|(OPTION))
#define OPTION_RESET(VALUE, OPTION) (VALUE) = ((VALUE)&(~(OPTION)))

#if __cplusplus
	//For VS
	#include <initializer_list>
	#define ARRAY_WITH_TYPE(type, ...) (std::initializer_list<type>({__VA_ARGS__}).begin()) 
#else
    #define ARRAY_WITH_TYPE(type, ...) ((type[]){__VA_ARGS__})
#endif

#define ARRAY_LENGTH(x)            (sizeof(x) / sizeof((x)[0]))

#ifndef MAX
    #define MAX(_V1_, _V2_) ((_V1_)>(_V2_)?(_V1_):(_V2_))
#endif

#ifndef MIN
    #define MIN(_V1_, _V2_) ((_V1_)>(_V2_)?(_V2_):(_V1_))
#endif


#define ZERO_MEM(mem, size) memset((mem), 0, (size))
#define ZERO_STRUCT(structure) memset(&structure, 0, sizeof(structure))

#if __cplusplus
    #define DELETE_OBJECT_AND_ZERO(pointer) {delete (pointer); (pointer) = 0;}
    #define DELETE_BLOCK_AND_ZERO(pointer) {delete [] (pointer); (pointer) = 0;}
#endif

#define FREE_BLOCK_AND_ZERO(pointer)   {free(pointer); (pointer) = 0;}
#define ELEMENTS_IN_ARRAY(arr)         ((int) (sizeof (arr) / sizeof ((arr)[0])))


#endif /* __NW_MACRO__ */
