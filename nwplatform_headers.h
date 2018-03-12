//
//  NW PLATFORM
//
//  Copyright (c) 2006-2018 Alexandr Kavalchuk (nWaves).
//  All rights reserved.
//
//  This software is provided 'as-is', without any express or implied
//  warranty. In no event will the authors be held liable for any damages
//  arising from the use of this software. Permission is granted to anyone to
//  use this software for any purpose, including commercial applications, and to
//  alter it and redistribute it freely, subject to the following restrictions:
//
//  1. The origin of this software must not be misrepresented; you must not
//     claim that you wrote the original software. If you use this software
//     in a product, an acknowledgment in the product documentation would be
//     appreciated but is not required.
//  2. Altered source versions must be plainly marked as such, and must not be
//     misrepresented as being the original software.
//  3. This notice may not be removed or altered from any source
//     distribution.
//

#ifndef __NW_PLATFORM_HEADERS__
#define __NW_PLATFORM_HEADERS__

#if NW_COMPILER_MSVC
	//Map standart library to secure library
	#ifndef NW_MSVC_SECURE_MAPPING
		#define NW_MSVC_SECURE_MAPPING
		#define _CRT_SECURE_NO_DEPRECATE
		#define _CRT_SECURE_CPP_OVERLOAD_STANDARD_NAMES 1
		#define _CRT_SECURE_CPP_OVERLOAD_SECURE_NAMES 1
	#endif
#endif

#ifndef _FILE_OFFSET_BITS
    #define _FILE_OFFSET_BITS 64
#endif

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdarg.h>

#if NW_COMPILER_MSVC
	#define _USE_MATH_DEFINES
	#include <math.h>
#else
	#include <math.h>
#endif

#include <time.h>
#include <float.h>
#include <setjmp.h>

#ifdef _WIN32
    #include <io.h>
    #include <fcntl.h>
#else
    #include <unistd.h>
    #include <sys/fcntl.h>
#endif

#include <errno.h>
#include <assert.h>

//System librares
#ifdef _WIN32
	#define _WINSOCKAPI_ //For resolve probelem with include <windows.h> before <winsock2.h>

    #pragma warning(disable : 4996) //Disable warning on strcpy and ets.

	#define NOMINMAX
	#include <windows.h>
	#include <commdlg.h>

	#include <mmreg.h>
#endif


#endif /* #ifndef __NW_PLATFORM_HEADERS__ */
