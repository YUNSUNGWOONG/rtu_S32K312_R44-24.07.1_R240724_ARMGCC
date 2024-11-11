/*==================================================================================================
* Project : RTD AUTOSAR 4.7
* Platform : CORTEXM
* Peripheral : S32K3XX
* Dependencies : none
*
* Autosar Version : 4.7.0
* Autosar Revision : ASR_REL_4_7_REV_0000
* Autosar Conf.Variant :
* SW Version : 3.0.0
* Build Version : S32K3_RTD_3_0_0_P01_D2303_ASR_REL_4_7_REV_0000_20230331
*
* Copyright 2020 - 2023 NXP Semiconductors
*
* NXP Confidential. This software is owned or controlled by NXP and may only be
* used strictly in accordance with the applicable license terms. By expressly
* accepting such terms or by downloading, installing, activating and/or otherwise
* using the software, you are agreeing that you have read, and that you agree to
* comply with and are bound by, such license terms. If you do not agree to be
* bound by the applicable license terms, then you may not retain, install,
* activate or otherwise use the software.
==================================================================================================*/
/**
*   @file           Platform_Types.h
*   @implements     Platform_Types.h_Artifact
*   @version 3.0.0
*
*   @brief   AUTOSAR BaseNXP - Platform dependend data type definitions.
*   @details AUTOSAR platform types header file. It contains all
*            platform dependent types and symbols. Those types must be abstracted in order to
*            become platform and compiler independent.
*
*   @addtogroup BASENXP_COMPONENT
*   @{
*/


/**
* @note         It is not allowed to add any extension to this file. Any extension invalidates the
*               AUTOSAR conformity
*/

#ifndef PLATFORMTYPES_H
#define PLATFORMTYPES_H

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                         INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#if !defined(NO_STDINT_H)
#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#endif /* !defined(NO_STDINT_H) */

/*==================================================================================================
*                               SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define PLATFORM_TYPES_VENDOR_ID                      43
#define PLATFORM_TYPES_AR_RELEASE_MAJOR_VERSION       4
#define PLATFORM_TYPES_AR_RELEASE_MINOR_VERSION       7
#define PLATFORM_TYPES_AR_RELEASE_REVISION_VERSION    0
#define PLATFORM_TYPES_SW_MAJOR_VERSION               3
#define PLATFORM_TYPES_SW_MINOR_VERSION               0
#define PLATFORM_TYPES_SW_PATCH_VERSION               0

/*==================================================================================================
*                                      FILE VERSION CHECKS
==================================================================================================*/

/*==================================================================================================
*                                           CONSTANTS
==================================================================================================*/

/*==================================================================================================
*                                       DEFINES AND MACROS
==================================================================================================*/
/**
* @brief          8bit Type Processor
* @implements     CPU_TYPE_enum
*/
#define CPU_TYPE_8 8

/**
* @brief          16bit Type Processor
* @implements     CPU_TYPE_enum
*/
#define CPU_TYPE_16 16

/**
* @brief          32bit Type Processor
* @implements     CPU_TYPE_enum
*/
#define CPU_TYPE_32 32

/**
* @brief          64bit Type Processor
* @implements     CPU_TYPE_enum
*/
#define CPU_TYPE_64 64

/**
* @brief          MSB First Processor
* @implements     CPU_BIT_ORDER_enum
*/
#define MSB_FIRST 0

/**
* @brief          LSB First Processor
* @implements     CPU_BIT_ORDER_enum
*/
#define LSB_FIRST 1

/**
* @brief          HIGH_BYTE_FIRST Processor
* @implements     CPU_BYTE_ORDER_enum
*/
#define HIGH_BYTE_FIRST 0

/**
* @brief          LOW_BYTE_FIRST Processor
* @implements     CPU_BYTE_ORDER_enum
*/
#define LOW_BYTE_FIRST 1

/**
* @brief          Processor type
* @implements     CPU_TYPE_enum
*/
#define CPU_TYPE (CPU_TYPE_32)
        
    

 
/**
* @brief          Bit order on register level.
* @implements     CPU_BIT_ORDER_enum
*/
#define CPU_BIT_ORDER (LSB_FIRST)

/**
* @brief The byte order on memory level shall be indicated in the platform types header file using
*        the symbol CPU_BYTE_ORDER.
* @implements     CPU_BYTE_ORDER_enum
*/
#define CPU_BYTE_ORDER (LOW_BYTE_FIRST)

#ifndef TRUE
#if !defined(NO_STDINT_H)
    /**
    * @brief Boolean true value
    * @implements TRUE_FALSE_enum
    */
    #define TRUE true
#else
    /**
    * @brief Boolean true value
    * @implements TRUE_FALSE_enum
    */
    #define TRUE 1
#endif /* !defined(NO_STDINT_H) */
#endif
#ifndef FALSE
#if !defined(NO_STDINT_H)
    /**
    * @brief Boolean false value
    * @implements TRUE_FALSE_enum
    */
    #define FALSE false
#else
    /**
    * @brief Boolean false value
    * @implements TRUE_FALSE_enum
    */
    #define FALSE 0
#endif /* !defined(NO_STDINT_H) */
#endif

/*==================================================================================================
                                             ENUMS
==================================================================================================*/

/*==================================================================================================
                                 STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
#if !defined(NO_STDINT_H)
#if (CPU_TYPE == CPU_TYPE_64) || (CPU_TYPE == CPU_TYPE_32) || (CPU_TYPE == CPU_TYPE_16)

/**
* @brief The standard AUTOSAR type boolean shall be implemented on basis of an eight bits long
*        unsigned integer.
* @implements boolean_type
*/
#define boolean_defined
typedef bool boolean;


/**
* @brief Unsigned 8 bit integer with range of 0 ..+255 (0x00..0xFF) -
*        8 bit
* @implements uint8_type
*/
typedef uint8_t uint8;

/**
* @brief Unsigned 16 bit integer with range of 0 ..+65535 (0x0000..0xFFFF) -
*        16 bit
* @implements uint16_type
*/
typedef uint16_t uint16;

/**
* @brief Unsigned 32 bit integer with range of 0 ..+4294967295 (0x00000000..0xFFFFFFFF) -
*        32 bit
* @implements uint32_type
*/
typedef uint32_t uint32;

/**
* @brief Unsigned 64 bit integer with range of 0..18446744073709551615 (0x0000000000000000..0xFFFFFFFFFFFFFFFF)-
*        64 bit
*
*/
typedef uint64_t uint64;


/**
* @brief Signed 8 bit integer with range of -128 ..+127 (0x80..0x7F) -
*        7 bit + 1 sign bit
* @implements sint8_type
*/
typedef int8_t sint8;

/**
* @brief Signed 16 bit integer with range of -32768 ..+32767 (0x8000..0x7FFF) -
*        15 bit + 1 sign bit
* @implements sint16_type
*/
typedef int16_t sint16;

/**
* @brief Signed 32 bit integer with range of -2147483648.. +2147483647 (0x80000000..0x7FFFFFFF) -
*        31 bit + 1 sign bit
* @implements sint32_type
*/
typedef int32_t sint32;

/**
* @brief Signed 64 bit integer with range of -9223372036854775808..9223372036854775807 (0x8000000000000000..0x7FFFFFFFFFFFFFFF )-
*        63 bit + 1 sign bit
*
*/
typedef int64_t sint64;

/**
* @brief Unsigned integer at least 8 bit long. Range of at least 0 ..+255 (0x00..0xFF) -
*        8 bit
* @implements uint8_least_type
*/
typedef uint_least8_t uint8_least;

/**
* @brief  Unsigned integer at least 16 bit long. Range of at least 0 ..+65535 (0x0000..0xFFFF) -
*         16 bit
* @implements uint16_least_type
*/
typedef uint_least16_t uint16_least;

/**
* @brief Unsigned integer at least 32 bit long. Range of at least 0 ..+4294967295
*       (0x00000000..0xFFFFFFFF) - 32 bit
* @implements uint32_least_type
*/
typedef uint_least32_t uint32_least;

/**
* @brief Signed integer at least 8 bit long. Range - at least -128 ..+127.
*        At least 7 bit + 1 bit sign
* @implements sint8_least_type
*/
typedef int_least8_t sint8_least;

/**
* @brief Signed integer at least 16 bit long. Range - at least -32768 ..+32767.
*        At least 15 bit + 1 bit sign
* @implements sint16_least_type
*/
typedef int_least16_t sint16_least;

/**
* @brief Signed integer at least 32 bit long. Range - at least -2147483648.. +2147483647.
*       At least 31 bit + 1 bit sign
* @implements sint32_least_type
*/
typedef int_least32_t sint32_least;

/**
* @brief 32bit long floating point data type
* @implements float32_type
*/
typedef float float32;

/**
* @brief 64bit long floating point data type
* @implements float64_type
*/
typedef double float64;

#endif /* (CPU_TYPE == CPU_TYPE_64) || (CPU_TYPE == CPU_TYPE_32) || (CPU_TYPE == CPU_TYPE_16) */

#else /* !defined(NO_STDINT_H) */
#if (CPU_TYPE == CPU_TYPE_64)
/**
* @brief The standard AUTOSAR type boolean shall be implemented on basis of an eight bits long
*        unsigned integer.
* @implements boolean_type
*/
typedef unsigned char boolean;

/**
* @brief Unsigned 8 bit integer with range of 0 ..+255 (0x00..0xFF) -
*        8 bit
* @implements uint8_type
*/
typedef unsigned char uint8;

/**
* @brief Unsigned 16 bit integer with range of 0 ..+65535 (0x0000..0xFFFF) -
*        16 bit
* @implements uint16_type
*/
typedef unsigned short uint16;

/**
* @brief Unsigned 32 bit integer with range of 0 ..+4294967295 (0x00000000..0xFFFFFFFF) -
*        32 bit
* @implements uint32_type
*/
typedef unsigned int uint32;

/**
* @brief Unsigned 64 bit integer with range of 0..18446744073709551615 (0x0000000000000000..0xFFFFFFFFFFFFFFFF)-
*        64 bit
*
*/
typedef unsigned long long uint64;

/**
* @brief Signed 8 bit integer with range of -128 ..+127 (0x80..0x7F) -
*        7 bit + 1 sign bit
* @implements sint8_type
*/
typedef signed char sint8;

/**
* @brief Signed 16 bit integer with range of -32768 ..+32767 (0x8000..0x7FFF) -
*        15 bit + 1 sign bit
* @implements sint16_type
*/
typedef signed short sint16;

/**
* @brief Signed 32 bit integer with range of -2147483648.. +2147483647 (0x80000000..0x7FFFFFFF) -
*        31 bit + 1 sign bit
* @implements sint32_type
*/
typedef signed int sint32;


/**
* @brief Signed 64 bit integer with range of -9223372036854775808..9223372036854775807 (0x8000000000000000..0x7FFFFFFFFFFFFFFF )-
*        63 bit + 1 sign bit
*
*/
typedef signed long long sint64;


/**
* @brief Unsigned integer at least 8 bit long. Range of at least 0 ..+255 (0x00..0xFF) -
*        8 bit
* @implements uint8_least_type
*/
typedef unsigned int uint8_least;

/**
* @brief  Unsigned integer at least 16 bit long. Range of at least 0 ..+65535 (0x0000..0xFFFF) -
*         16 bit
* @implements uint16_least_type
*/
typedef unsigned int uint16_least;

/**
* @brief Unsigned integer at least 32 bit long. Range of at least 0 ..+4294967295
*       (0x00000000..0xFFFFFFFF) - 32 bit
* @implements uint32_least_type
*/
typedef unsigned int uint32_least;

/**
* @brief Signed integer at least 8 bit long. Range - at least -128 ..+127.
*        At least 7 bit + 1 bit sign
* @implements sint8_least_type
*/
typedef signed int sint8_least;

/**
* @brief Signed integer at least 16 bit long. Range - at least -32768 ..+32767.
*        At least 15 bit + 1 bit sign
* @implements sint16_least_type
*/
typedef signed int sint16_least;

/**
* @brief Signed integer at least 32 bit long. Range - at least -2147483648.. +2147483647.
*       At least 31 bit + 1 bit sign
* @implements sint32_least_type
*/
typedef signed int sint32_least;

/**
* @brief 32bit long floating point data type
* @implements float32_type
*/
typedef float float32;

/**
* @brief 64bit long floating point data type
* @implements float64_type
*/
typedef double float64;


#elif (CPU_TYPE == CPU_TYPE_32)
/* Changed by mobilgene - Start : #18848 */
/**
* @brief The standard AUTOSAR type boolean shall be implemented on basis of an eight bits long
*        unsigned integer.
* @implements boolean_type
*/
#ifndef boolean_defined
typedef unsigned char boolean;
#define boolean_defined
#endif


/**
* @brief Unsigned 8 bit integer with range of 0 ..+255 (0x00..0xFF) -
*        8 bit
* @implements uint8_type
*/
#ifndef uint8_defined
typedef unsigned char uint8;
#define uint8_defined
#endif

/**
* @brief Unsigned 16 bit integer with range of 0 ..+65535 (0x0000..0xFFFF) -
*        16 bit
* @implements uint16_type
*/
#ifndef uint16_defined
typedef unsigned short uint16;
#define uint16_defined
#endif

/**
* @brief Unsigned 32 bit integer with range of 0 ..+4294967295 (0x00000000..0xFFFFFFFF) -
*        32 bit
* @implements uint32_type
*/
#ifndef uint32_defined
typedef unsigned long uint32;
#define uint32_defined
#endif

/**
* @brief Unsigned 64 bit integer with range of 0..18446744073709551615 (0x0000000000000000..0xFFFFFFFFFFFFFFFF)-
*        64 bit
*
*/
#ifndef uint64_defined
typedef unsigned long long uint64;
#define uint64_defined
#endif


/**
* @brief Signed 8 bit integer with range of -128 ..+127 (0x80..0x7F) -
*        7 bit + 1 sign bit
* @implements sint8_type
*/
#ifndef sint8_defined
typedef signed char sint8;
#define sint8_defined
#endif

/**
* @brief Signed 16 bit integer with range of -32768 ..+32767 (0x8000..0x7FFF) -
*        15 bit + 1 sign bit
* @implements sint16_type
*/
#ifndef sint16_defined
typedef signed short sint16;
#define sint16_defined
#endif

/**
* @brief Signed 32 bit integer with range of -2147483648.. +2147483647 (0x80000000..0x7FFFFFFF) -
*        31 bit + 1 sign bit
* @implements sint32_type
*/
#ifndef sint32_defined
typedef signed long sint32;
#define sint32_defined
#endif

/**
* @brief Signed 64 bit integer with range of -9223372036854775808..9223372036854775807 (0x8000000000000000..0x7FFFFFFFFFFFFFFF )-
*        63 bit + 1 sign bit
*
*/
#ifndef sint64_defined
typedef signed long long sint64;
#define sint64_defined
#endif

/**
* @brief Unsigned integer at least 8 bit long. Range of at least 0 ..+255 (0x00..0xFF) -
*        8 bit
* @implements uint8_least_type
*/
#ifndef uint8_least_defined
typedef unsigned long uint8_least;
#define uint8_least_defined
#endif

/**
* @brief  Unsigned integer at least 16 bit long. Range of at least 0 ..+65535 (0x0000..0xFFFF) -
*         16 bit
* @implements uint16_least_type
*/
#ifndef uint16_least_defined
typedef unsigned long uint16_least;
#define uint16_least_defined
#endif

/**
* @brief Unsigned integer at least 32 bit long. Range of at least 0 ..+4294967295
*       (0x00000000..0xFFFFFFFF) - 32 bit
* @implements uint32_least_type
*/
#ifndef uint32_least_defined
typedef unsigned long uint32_least;
#define uint32_least_defined
#endif

/**
* @brief Signed integer at least 8 bit long. Range - at least -128 ..+127.
*        At least 7 bit + 1 bit sign
* @implements sint8_least_type
*/
#ifndef sint8_least_defined
typedef signed long sint8_least;
#define sint8_least_defined
#endif

/**
* @brief Signed integer at least 16 bit long. Range - at least -32768 ..+32767.
*        At least 15 bit + 1 bit sign
* @implements sint16_least_type
*/
#ifndef sint16_least_defined
typedef signed long sint16_least;
#define sint16_least_defined
#endif

/**
* @brief Signed integer at least 32 bit long. Range - at least -2147483648.. +2147483647.
*       At least 31 bit + 1 bit sign
* @implements sint32_least_type
*/
#ifndef sint32_least_defined
typedef signed long sint32_least;
#define sint32_least_defined
#endif

/**
* @brief 32bit long floating point data type
* @implements float32_type
*/
#ifndef float32_defined
typedef float float32;
#define float32_defined
#endif

/**
* @brief 64bit long floating point data type
* @implements float64_type
*/
#ifndef float64_defined
typedef double float64;
#define float64_defined
#endif
/* Changed by mobilgene - End */


#elif (CPU_TYPE == CPU_TYPE_16)

/**
* @brief The standard AUTOSAR type boolean shall be implemented on basis of an eight bits long
*        unsigned integer.
* @implements boolean_type
*/
typedef unsigned char boolean;


/**
* @brief Unsigned 8 bit integer with range of 0 ..+255 (0x00..0xFF) -
*        8 bit
* @implements uint8_type
*/
typedef unsigned char uint8;

/**
* @brief Unsigned 16 bit integer with range of 0 ..+65535 (0x0000..0xFFFF) -
*        16 bit
* @implements uint16_type
*/
typedef unsigned short uint16;

/**
* @brief Unsigned 32 bit integer with range of 0 ..+4294967295 (0x00000000..0xFFFFFFFF) -
*        32 bit
* @implements uint32_type
*/
typedef unsigned long uint32;

/**
* @brief Unsigned 64 bit integer with range of 0..18446744073709551615 (0x0000000000000000..0xFFFFFFFFFFFFFFFF)-
*        64 bit
*
*/
typedef unsigned long long uint64;


/**
* @brief Signed 8 bit integer with range of -128 ..+127 (0x80..0x7F) -
*        7 bit + 1 sign bit
* @implements sint8_type
*/
typedef signed char sint8;

/**
* @brief Signed 16 bit integer with range of -32768 ..+32767 (0x8000..0x7FFF) -
*        15 bit + 1 sign bit
* @implements sint16_type
*/
typedef signed short sint16;

/**
* @brief Signed 32 bit integer with range of -2147483648.. +2147483647 (0x80000000..0x7FFFFFFF) -
*        31 bit + 1 sign bit
* @implements sint32_type
*/
typedef signed long sint32;

/**
* @brief Signed 64 bit integer with range of -9223372036854775808..9223372036854775807 (0x8000000000000000..0x7FFFFFFFFFFFFFFF )-
*        63 bit + 1 sign bit
*
*/
typedef signed long long sint64;

/**
* @brief Unsigned integer at least 8 bit long. Range of at least 0 ..+255 (0x00..0xFF) -
*        8 bit
* @implements uint8_least_type
*/
typedef unsigned long uint8_least;

/**
* @brief  Unsigned integer at least 16 bit long. Range of at least 0 ..+65535 (0x0000..0xFFFF) -
*         16 bit
* @implements uint16_least_type
*/
typedef unsigned long uint16_least;

/**
* @brief Unsigned integer at least 32 bit long. Range of at least 0 ..+4294967295
*       (0x00000000..0xFFFFFFFF) - 32 bit
* @implements uint32_least_type
*/
typedef unsigned long uint32_least;

/**
* @brief Signed integer at least 8 bit long. Range - at least -128 ..+127.
*        At least 7 bit + 1 bit sign
* @implements sint8_least_type
*/
typedef signed long sint8_least;

/**
* @brief Signed integer at least 16 bit long. Range - at least -32768 ..+32767.
*        At least 15 bit + 1 bit sign
* @implements sint16_least_type
*/
typedef signed long sint16_least;

/**
* @brief Signed integer at least 32 bit long. Range - at least -2147483648.. +2147483647.
*       At least 31 bit + 1 bit sign
* @implements sint32_least_type
*/
typedef signed long sint32_least;

/**
* @brief 32bit long floating point data type
* @implements float32_type
*/
typedef float float32;

/**
* @brief 64bit long floating point data type
* @implements float64_type
*/
typedef double float64;

#endif /* (CPU_TYPE == CPU_TYPE_64) */

#endif /* !defined(NO_STDINT_H) */


/*==================================================================================================
*                                 GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

#ifdef __cplusplus
}
#endif


#endif /* #ifndef PLATFORMTYPES_H */

/** @} */
