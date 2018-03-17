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

#ifndef __NW_PLATFORM_OS_VERSION__
#define __NW_PLATFORM_OS_VERSION__

#if NW_SYSTEM_LITTLE_ENDIAN
NW_PACKET_START_DEF struct NW_PACKET_ATTR os_version_parts_t
{
    uint16_t patch;
    uint8_t  minor;
    uint8_t  major;
};
NW_PACKET_END_DEF
#elif NW_SYSTEM_BIG_ENDIAN
NW_PACKET_START_DEF struct NW_PACKET_ATTR os_version_parts_t
{
    uint8_t  major;
    uint8_t  minor;
    uint16_t patch;
};
NW_PACKET_END_DEF
#endif

NW_PACKET_START_DEF struct NW_PACKET_ATTR os_version_t
{
    union
    {
        uint32_t value;
        struct os_version_parts_t parts;
    };
};
NW_PACKET_END_DEF

#if NW_SYSTEM_LITTLE_ENDIAN
#define OS_VERSION_MAKE(MAJOR,MINOR,PATCH)  (struct os_version_t){((PATCH)<<0)&0x0000FFFF | ((MINOR)<<16)&0x00FF0000 | ((MAJOR)<<24)&0xFF000000}
#elif NW_SYSTEM_BIG_ENDIAN
#define OS_VERSION_MAKE(MAJOR,MINOR,PATCH)  (struct os_version_t){((MAJOR)<<0)&0xFF000000 | ((MINOR)<< 8)&0x00FF0000 | ((PATCH)<<16)&0x0000FFFF}
#endif

EXTERN_C struct os_version_t os_version();

#endif //__NW_OS_VERSION__
