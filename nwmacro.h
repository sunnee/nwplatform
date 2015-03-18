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

#define VALUE_IN_ARRAY(value, type, array)  arritem(array, sizeof(array), &value, sizeof(value))

#define VALUE_IN_LIST(value, type, ...)     (VALUE_IN_ARRAY((value),type,ARRAY_WITH_TYPE(type,__VA_ARGS__)) != NULL)
#define VALUE_NOT_IN_LIST(value, type, ...) (VALUE_IN_ARRAY((value),type,ARRAY_WITH_TYPE(type,__VA_ARGS__)) == NULL)

#ifndef MAX
    #define MAX(_V1_, _V2_) ((_V1_)>(_V2_)?(_V1_):(_V2_))
#endif

#ifndef MIN
    #define MIN(_V1_, _V2_) ((_V1_)>(_V2_)?(_V2_):(_V1_))
#endif


#define FLOAT_COMPARE(value1, value2) comparef(value1, value2)
#define FLOAT_COMPARE_ABSOLUTE(value1, value2, precision) ( ((value1) >= (value2)-precision) && ((value1) <= (value2)+precision) )
#define FLOAT_COMPARE_RELATIVE(value1, value2, precision) FLOAT_COMPARE_ABSOLUTE(value1, value2, (value2)*precision)

#define VALUE_IN_RANGE(value, min, max) (((value) >= (min)) && ((value) <= (max)))
#define VALUE_CLIP_TO_RANGE(value, min, max) MAX((min), MIN((max), (value)))

#define VALUE_INC_IN_RANGE(value, min, max) ((value)>=(max))?(max):((value)+1)
#define VALUE_DEC_IN_RANGE(value, min, max) ((value)<=(min))?(min):((value)-1)

#define VALUE_LOOP_IN_RANGE(value, min, max) (value)>(max)?(value)-(max):((value)<(min)?(value)+(max):(value))


#define VALUE_IN_INTERVAL(low, val, high)	   ( ((val) >  (low)) && ((val) <  (high)) )
#define VALUE_IN_INTERVAL_INCL(low, val, high) ( ((val) >= (low)) && ((val) <= (high)) )

#define ZERO_MEM(mem, size) memset((mem), 0, (size))
#define ZERO_STRUCT(structure) memset(&structure, 0, sizeof(structure))

#if __cplusplus
    #define DELETE_OBJECT_AND_ZERO(pointer) {delete (pointer); (pointer) = 0;}
    #define DELETE_BLOCK_AND_ZERO(pointer) {delete [] (pointer); (pointer) = 0;}
#endif

#define FREE_BLOCK_AND_ZERO(pointer)   {free(pointer); (pointer) = 0;}


#define ELEMENTS_IN_ARRAY(arr)   ((int) (sizeof (arr) / sizeof ((arr)[0])))


#endif /* __NW_MACRO__ */
