/*
 * GMtypes.h
 *
 */


#ifndef GMTYPES_H_
#define GMTYPES_H_

// 需要C99以上语言标准支持
#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include "../driver/config.h"
//#include <port.h>

#ifndef TRUE
    #define TRUE    1           // true
#endif

#ifndef FALSE
    #define FALSE   0           // true
#endif

#ifndef true
    #define true    1           // true
#endif

#ifndef false
    #define false   0           // false
#endif

typedef unsigned char           BYTE;
typedef unsigned char           BOOL;
typedef signed char             S8;
typedef signed short            S16;
// 注意：不同平台一般int类型字节长度不一样：
//      8/16位MCU，int一般是2byte；32位及以上，int一般是4字节。
//#if (CFG_MCU_BIT_SYS == 8) || (CFG_MCU_BIT_SYS == 16)
//    typedef signed long int     S32;
//#elif (CFG_MCU_BIT_SYS == 32)
//    typedef signed int          S32;
//#else
//    #error configure MCU xbit!
//#endif
typedef signed long long        S64;
typedef unsigned char           U8;
typedef unsigned short          U16;
// 注意：不同平台一般int类型字节长度不一样：
//      8/16位MCU，int一般是2byte；32位及以上，int一般是4字节。
//#if (CFG_MCU_BIT_SYS == 8) || (CFG_MCU_BIT_SYS == 16)
//    typedef unsigned long int   U32;
//#elif (CFG_MCU_BIT_SYS == 32)
//    typedef unsigned int        U32;
//#else
//    #error configure MCU xbit!
//#endif
typedef unsigned long long      U64; // 8 bytes
typedef unsigned short          MAPI_WORD;  // 2 bytes

/// Font handle, handle to font table in memory
typedef signed char             FONTHANDLE;
/// Bitmap handle, handle to bitmap buffer
typedef signed short            BMPHANDLE;
/// definition for DBHANDLE
typedef signed char             DBHANDLE;

#define UNUSED(v) (void)(v)


#endif /* GMTYPES_H_ */