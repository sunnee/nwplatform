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

#include "nwplatform.h"

#if __NW_PLATFORM_IMPLEMENTATION
//#error Use only "nwplatform.h" and "nwplatform.c". Don't compile/include other files directly!

#ifndef __NW_PLATFORM_OS_VERSION_IMPLEMENTATION__
#define __NW_PLATFORM_OS_VERSION_IMPLEMENTATION__

#if NW_SYSTEM_IOS
#define _os_version_internal os_version_ios
#elif NW_SYSTEM_OSX
#define _os_version_internal os_version_osx
#elif NW_SYSTEM_WINDOWS
#define _os_version_internal os_version_windows
#else
#define _os_version_internal os_version_empty
#endif

EXTERN_C struct os_version_t _os_version_internal();

EXTERN_C struct os_version_t os_version()
{
    //static struct OS_VERSION_COMPONENTS components = {1,2,3};
    static struct os_version_t os_version = OS_VERSION_MAKE(0,0,0);

    if (os_version.value == 0)
    {
        os_version = _os_version_internal();
    }
    
    return os_version;
};

#if NW_SYSTEM_IOS
//-------------------- IOS ----------------------

#include <objc/NSObjCRuntime.h>
#include <objc/runtime.h>
#include <objc/message.h>
#include <CoreFoundation/CoreFoundation.h>
#include <CoreFoundation/CFString.h>

#define GET_CLASS_METHOD_IMP(CLASS,SEL)    method_getImplementation(class_getClassMethod(CLASS,    SEL))
#define GET_INSTANCE_METHOD_IMP(CLASS,SEL) method_getImplementation(class_getInstanceMethod(CLASS, SEL))

EXTERN_C struct os_version_t os_version_ios()
{
    Class uiDevice       = objc_getClass("UIDevice");
    SEL currentDeviceSel = sel_registerName("currentDevice");
    
    IMP currentDeviceImp = GET_CLASS_METHOD_IMP(uiDevice, currentDeviceSel);
    CFTypeRef currentDevice = ((CFTypeRef(*)(id, SEL))currentDeviceImp)((id)uiDevice, currentDeviceSel);
    SEL systemVersionSel = sel_registerName("systemVersion");
    
    IMP systemVersionImp      =  GET_INSTANCE_METHOD_IMP(uiDevice, systemVersionSel);
    CFStringRef systemVersion = ((CFStringRef(*)(id, SEL))systemVersionImp)((id)currentDevice, systemVersionSel);
    
    const char* systemVersionStr = CFStringGetCStringPtr(systemVersion, kCFStringEncodingASCII);
    
    if (systemVersionStr == NULL)
    {
        systemVersionStr = CFStringGetCStringPtr(systemVersion, kCFStringEncodingUTF8);
        
        if (systemVersionStr == NULL)
        {
            SEL UTF8StringSel = sel_registerName("UTF8String");
            systemVersionStr = ((const char*(*)(id, SEL))objc_msgSend)((id)systemVersion, UTF8StringSel);
        }
    }
    
    int major = 0, minor = 0, patch = 0;
    struct os_version_t result = {0};
    
    if (sscanf(systemVersionStr, "%d.%d.%d", &major, &minor, &patch) >= 2)
    {
        result = OS_VERSION_MAKE(major, minor, patch);
    }
    
    //Do not release non-retained objects
    //CFRelease(systemVersion);
    //CFRelease(currentDevice);

    return result;
}

#elif NW_SYSTEM_OSX

//-------------------- OS X ----------------------
#include <errno.h>
#include <sys/sysctl.h>
#include <CoreServices/CoreServices.h>

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wdeprecated-declarations"
EXTERN_C struct os_version_t os_version_osx()
{
    
    //char str[256];
    //size_t size = sizeof(str);
    //int ret = sysctlbyname("kern.osrelease", str, &size, NULL, 0);
    
    /*
     14.x.x  OS X 10.10.x Yosemite
     13.x.x  OS X 10.9.x Mavericks
     12.x.x  OS X 10.8.x Mountain Lion
     11.x.x  OS X 10.7.x Lion
     10.x.x  OS X 10.6.x Snow Leopard
     9.x.x  OS X 10.5.x Leopard
     8.x.x  OS X 10.4.x Tiger
     7.x.x  OS X 10.3.x Panther
     6.x.x  OS X 10.2.x Jaguar
     5.x    OS X 10.1.x Puma
     */
    
    
    struct os_version_t result = {0};
    SInt32 major = 0, minor = 0, patch = 0;
    
    if (Gestalt(gestaltSystemVersionMajor, &major)  != noErr) return result;
    if (Gestalt(gestaltSystemVersionMinor, &minor)  != noErr) return result;
    if (Gestalt(gestaltSystemVersionBugFix, &patch) != noErr) return result;
    
    result = OS_VERSION_MAKE(major, minor, patch);

    return result;
}
#pragma clang diagnostic pop

#elif NW_SYSTEM_WINDOWS

//-------------------- WINDOWS ----------------------
#include <winnt.h>

EXTERN_C struct OS_VERSION_VALUE os_version_windows()
{
    struct OSVERSIONINFOEX os_version_info;
    
    memset(&os_version_info, 0, sizeof(OSVERSIONINFOEX))
    os_version_info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
    
    struct os_version_t result = {0};
    
    if (GetVersionEx(&os_version_info) == true)
    {
        result.parts.major = os_version_info.dwMajorVersion;
        result.parts.minor = os_version_info.dwMinorVersion;
    }
    
    
    /*
     dwMajorVersion
     dwMinorVersion
     
     dwBuildNumber
     wServicePackMajor
     
     
     wSuiteMask
     VER_SUITE_EMBEDDEDNT 0x00000040 Windows XP Embedded is installed.
     VER_SUITE_PERSONAL 0x00000200 Windows Vista Home Premium, Windows Vista Home Basic, or Windows XP Home Edition is installed.
     VER_SUITE_WH_SERVER 0x00008000 Windows Home Server is installed.
     
     
     wProductType
     VER_NT_DOMAIN_CONTROLLER 0x0000002 The system is a domain controller and the operating system is Windows Server 2012 , Windows Server 2008 R2, Windows Server 2008, Windows Server 2003, or Windows 2000 Server.
     VER_NT_SERVER 0x0000003 The operating system is Windows Server 2012, Windows Server 2008 R2, Windows Server 2008, Windows Server 2003, or Windows 2000 Server. Note that a server that is also a domain controller is reported as VER_NT_DOMAIN_CONTROLLER, not VER_NT_SERVER.
     VER_NT_WORKSTATION 0x0000001 The operating system is Windows 8, Windows 7, Windows Vista, Windows XP Professional, Windows XP Home Edition, or Windows 2000 Professional.
     */
     
     
     /*
     Windows 8.1            6.3	OSVERSIONINFOEX.wProductType == VER_NT_WORKSTATION
     Windows Server 2012 R2	6.3	OSVERSIONINFOEX.wProductType != VER_NT_WORKSTATION
     
     Windows 8              6.2	OSVERSIONINFOEX.wProductType == VER_NT_WORKSTATION
     Windows Server 2012	6.2	OSVERSIONINFOEX.wProductType != VER_NT_WORKSTATION
     
     Windows 7              6.1	OSVERSIONINFOEX.wProductType == VER_NT_WORKSTATION
     Windows Server 2008 R2	6.1	OSVERSIONINFOEX.wProductType != VER_NT_WORKSTATION
     
     Windows Server 2008	6.0	OSVERSIONINFOEX.wProductType != VER_NT_WORKSTATION
     Windows Vista          6.0	OSVERSIONINFOEX.wProductType == VER_NT_WORKSTATION
     
     Windows Server 2003 R2	5.2	GetSystemMetrics(SM_SERVERR2) != 0
     Windows Home Server	5.2	OSVERSIONINFOEX.wSuiteMask & VER_SUITE_WH_SERVER
     Windows Server 2003	5.2	GetSystemMetrics(SM_SERVERR2) == 0
     
     Windows XP Professional x64 Edition	5.2	(OSVERSIONINFOEX.wProductType == VER_NT_WORKSTATION) && (SYSTEM_INFO.wProcessorArchitecture==PROCESSOR_ARCHITECTURE_AMD64)
     
     Windows XP             5.1
     Windows 2000           5.0
     */
    
    return result;
}

#else
//-------------------- EMPTY ----------------------
EXTERN_C struct OS_VERSION_VALUE os_version_empty()
{
    struct os_version_t result = {0};
    return result;
}
#endif

#endif //#ifndef __NW_PLATFORM_OS_VERSION_IMPLEMENTATION__

#endif //#if __NW_PLATFORM_IMPLEMENTATION
