//
//  nwos_version.h
//  iTube
//
//  Created by Alexandr Kavalchuk on 18.03.15.
//  Copyright (c) 2015 Alpari Group Ltd... All rights reserved.
//

#ifndef __NW_OS_VERSION__
#define __NW_OS_VERSION__

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

EXTERN_C struct os_version_t os_verion();

#endif //__NW_OS_VERSION__
