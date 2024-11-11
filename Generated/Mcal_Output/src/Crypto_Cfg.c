/*==================================================================================================
*   Project              : RTD AUTOSAR 4.7
*   Platform             : CORTEXM
*   Peripheral           : HSE
*   Dependencies         : none
*
*   Autosar Version      : 4.7.0
*   Autosar Revision     : ASR_REL_4_7_REV_0000
*   Autosar Conf.Variant :
*   SW Version           : 3.0.0
*   Build Version        : S32K3_RTD_3_0_0_P01_D2303_ASR_REL_4_7_REV_0000_20230331
*
*   Copyright 2020 - 2023 NXP Semiconductors
*
*   NXP Confidential. This software is owned or controlled by NXP and may only be
*   used strictly in accordance with the applicable license terms. By expressly
*   accepting such terms or by downloading, installing, activating and/or otherwise
*   using the software, you are agreeing that you have read, and that you agree to
*   comply with and are bound by, such license terms. If you do not agree to be
*   bound by the applicable license terms, then you may not retain, install,
*   activate or otherwise use the software.
==================================================================================================*/

/**
*   @file
*
*   @addtogroup CRYPTO
*   @{
*/

#ifdef __cplusplus
extern "C"{
#endif

/*==================================================================================================
*                                          INCLUDE FILES
* 1) system and project includes
* 2) needed interfaces from external units
* 3) internal and external interfaces from this unit
==================================================================================================*/
#include "Crypto_Cfg.h"
#include "Crypto_Private.h"
#include "Crypto.h"

/*==================================================================================================
*                                 SOURCE FILE VERSION INFORMATION
==================================================================================================*/
#define CRYPTO_VENDOR_ID_CFG_C                      43
#define CRYPTO_AR_RELEASE_MAJOR_VERSION_CFG_C       4
#define CRYPTO_AR_RELEASE_MINOR_VERSION_CFG_C       7
#define CRYPTO_AR_RELEASE_REVISION_VERSION_CFG_C    0
#define CRYPTO_SW_MAJOR_VERSION_CFG_C               3
#define CRYPTO_SW_MINOR_VERSION_CFG_C               0
#define CRYPTO_SW_PATCH_VERSION_CFG_C               0

/*==================================================================================================
*                                       FILE VERSION CHECKS
==================================================================================================*/
/* Check if Crypto configuration source file and Crypto configuration header file are of the same vendor */
#if (CRYPTO_VENDOR_ID_CFG_C != CRYPTO_VENDOR_ID_CFG)
    #error "Crypto_Cfg.c and Crypto_Cfg.h have different vendor ids"
#endif

/* Check if Crypto configuration source file and Crypto configuration header file are of the same Autosar version */
#if ((CRYPTO_AR_RELEASE_MAJOR_VERSION_CFG_C    != CRYPTO_AR_RELEASE_MAJOR_VERSION_CFG) || \
     (CRYPTO_AR_RELEASE_MINOR_VERSION_CFG_C    != CRYPTO_AR_RELEASE_MINOR_VERSION_CFG) || \
     (CRYPTO_AR_RELEASE_REVISION_VERSION_CFG_C != CRYPTO_AR_RELEASE_REVISION_VERSION_CFG) \
    )
    #error "AutoSar Version Numbers of Crypto_Cfg.c and Crypto_Cfg.h are different"
#endif

/* Check if Crypto configuration source file and Crypto configuration header file are of the same Software version */
#if ((CRYPTO_SW_MAJOR_VERSION_CFG_C != CRYPTO_SW_MAJOR_VERSION_CFG) || \
     (CRYPTO_SW_MINOR_VERSION_CFG_C != CRYPTO_SW_MINOR_VERSION_CFG) || \
     (CRYPTO_SW_PATCH_VERSION_CFG_C != CRYPTO_SW_PATCH_VERSION_CFG)    \
    )
    #error "Software Version Numbers of Crypto_Cfg.c and Crypto_Cfg.h are different"
#endif

/* Check if Crypto configuration source file and Crypto private header file are of the same vendor */
#if (CRYPTO_VENDOR_ID_CFG_C != CRYPTO_VENDOR_ID_PRIVATE)
    #error "Crypto_Cfg.c and Crypto_Private.h have different vendor ids"
#endif

/* Check if Crypto configuration source file and Crypto private header file are of the same Autosar version */
#if ((CRYPTO_AR_RELEASE_MAJOR_VERSION_CFG_C    != CRYPTO_AR_RELEASE_MAJOR_VERSION_PRIVATE) || \
     (CRYPTO_AR_RELEASE_MINOR_VERSION_CFG_C    != CRYPTO_AR_RELEASE_MINOR_VERSION_PRIVATE) || \
     (CRYPTO_AR_RELEASE_REVISION_VERSION_CFG_C != CRYPTO_AR_RELEASE_REVISION_VERSION_PRIVATE) \
    )
    #error "AutoSar Version Numbers of Crypto_Cfg.c and Crypto_Private.h are different"
#endif

/* Check if Crypto configuration source file and Crypto private header file are of the same Software version */
#if ((CRYPTO_SW_MAJOR_VERSION_CFG_C != CRYPTO_SW_MAJOR_VERSION_PRIVATE) || \
     (CRYPTO_SW_MINOR_VERSION_CFG_C != CRYPTO_SW_MINOR_VERSION_PRIVATE) || \
     (CRYPTO_SW_PATCH_VERSION_CFG_C != CRYPTO_SW_PATCH_VERSION_PRIVATE)    \
    )
    #error "Software Version Numbers of Crypto_Cfg.c and Crypto_Private.h are different"
#endif

/* Check if Crypto configuration source file and Crypto header file are of the same vendor */
#if (CRYPTO_VENDOR_ID_CFG_C != CRYPTO_VENDOR_ID)
    #error "Crypto_Cfg.c and Crypto.h have different vendor ids"
#endif

/* Check if Crypto configuration source file and Crypto header file are of the same Autosar version */
#if ((CRYPTO_AR_RELEASE_MAJOR_VERSION_CFG_C    != CRYPTO_AR_RELEASE_MAJOR_VERSION) || \
     (CRYPTO_AR_RELEASE_MINOR_VERSION_CFG_C    != CRYPTO_AR_RELEASE_MINOR_VERSION) || \
     (CRYPTO_AR_RELEASE_REVISION_VERSION_CFG_C != CRYPTO_AR_RELEASE_REVISION_VERSION) \
    )
    #error "AutoSar Version Numbers of Crypto_Cfg.c and Crypto.h are different"
#endif

/* Check if Crypto configuration source file and Crypto header file are of the same Software version */
#if ((CRYPTO_SW_MAJOR_VERSION_CFG_C != CRYPTO_SW_MAJOR_VERSION) || \
     (CRYPTO_SW_MINOR_VERSION_CFG_C != CRYPTO_SW_MINOR_VERSION) || \
     (CRYPTO_SW_PATCH_VERSION_CFG_C != CRYPTO_SW_PATCH_VERSION)    \
    )
    #error "Software Version Numbers of Crypto_Cfg.c and Crypto.h are different"
#endif

/*==================================================================================================
*                           LOCAL TYPEDEFS (STRUCTURES, UNIONS, ENUMS)
==================================================================================================*/

/*==================================================================================================
*                                          LOCAL MACROS
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL CONSTANTS
==================================================================================================*/
#define CRYPTO_START_SEC_CONST_8
#include "Crypto_MemMap.h"

/* Array storing the indexes of the Crypto Driver Objects */
static const uint8 Crypto_au8CDOs[] =
{
    0U
};

#define CRYPTO_STOP_SEC_CONST_8
#include "Crypto_MemMap.h"

#define CRYPTO_START_SEC_CONFIG_DATA_8_NO_CACHEABLE
#include "Crypto_MemMap.h"

#define CRYPTO_STOP_SEC_CONFIG_DATA_8_NO_CACHEABLE
#include "Crypto_MemMap.h"

#define CRYPTO_START_SEC_CONST_32
#include "Crypto_MemMap.h"

/* Array of indexes for each Crypto Key Element referred by Crypto Key Dummy */
static const uint32 Crypto_au32KeyElementList_Dummy[1U] =
{
    0U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key Dummy2 */
static const uint32 Crypto_au32KeyElementList_Dummy2[1U] =
{
    0U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key PBKDF2_Source_Key */
static const uint32 Crypto_au32KeyElementList_PBKDF2_Source_Key[5U] =
{
    3U,
    1U,
    2U,
    5U,
    6U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key PBKDF2_Target_Key */
static const uint32 Crypto_au32KeyElementList_PBKDF2_Target_Key[1U] =
{
    4U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key PBKDF2_Extracted_Key */
static const uint32 Crypto_au32KeyElementList_PBKDF2_Extracted_Key[1U] =
{
    7U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key PBKDF2_ExtractedKey */
static const uint32 Crypto_au32KeyElementList_PBKDF2_ExtractedKey[2U] =
{
    8U,
    9U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key PBKDF2_Encrypt_Key */
static const uint32 Crypto_au32KeyElementList_PBKDF2_Encrypt_Key[1U] =
{
    10U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key PBKDF2_Decrypt_Key */
static const uint32 Crypto_au32KeyElementList_PBKDF2_Decrypt_Key[1U] =
{
    11U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key PBKDF2_Source_Key_PSK0 */
static const uint32 Crypto_au32KeyElementList_PBKDF2_Source_Key_PSK0[5U] =
{
    5U,
    6U,
    3U,
    2U,
    12U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key PBKDF2_Source_Key_PSK1 */
static const uint32 Crypto_au32KeyElementList_PBKDF2_Source_Key_PSK1[5U] =
{
    5U,
    6U,
    3U,
    2U,
    13U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key PBKDF2_Source_Key_PSK2 */
static const uint32 Crypto_au32KeyElementList_PBKDF2_Source_Key_PSK2[5U] =
{
    5U,
    6U,
    3U,
    2U,
    14U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key PBKDF2_Source_Key_PSK3 */
static const uint32 Crypto_au32KeyElementList_PBKDF2_Source_Key_PSK3[5U] =
{
    5U,
    6U,
    3U,
    2U,
    15U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key PBKDF2_Source_Key_PSK4 */
static const uint32 Crypto_au32KeyElementList_PBKDF2_Source_Key_PSK4[5U] =
{
    5U,
    6U,
    3U,
    2U,
    16U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key PBKDF2_Source_Key_PSK5 */
static const uint32 Crypto_au32KeyElementList_PBKDF2_Source_Key_PSK5[5U] =
{
    5U,
    6U,
    3U,
    2U,
    17U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key PBKDF2_Source_Key_PSK6 */
static const uint32 Crypto_au32KeyElementList_PBKDF2_Source_Key_PSK6[5U] =
{
    5U,
    6U,
    3U,
    2U,
    18U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key PBKDF2_Source_Key_PSK7 */
static const uint32 Crypto_au32KeyElementList_PBKDF2_Source_Key_PSK7[5U] =
{
    5U,
    6U,
    3U,
    2U,
    19U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key PBKDF2_Source_Key_PSK8 */
static const uint32 Crypto_au32KeyElementList_PBKDF2_Source_Key_PSK8[5U] =
{
    5U,
    6U,
    3U,
    2U,
    20U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key PBKDF2_Source_Key_PSK9 */
static const uint32 Crypto_au32KeyElementList_PBKDF2_Source_Key_PSK9[5U] =
{
    5U,
    6U,
    3U,
    2U,
    21U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key Dummy3 */
static const uint32 Crypto_au32KeyElementList_Dummy3[1U] =
{
    0U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key Dummy4 */
static const uint32 Crypto_au32KeyElementList_Dummy4[1U] =
{
    0U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key Dummy5 */
static const uint32 Crypto_au32KeyElementList_Dummy5[1U] =
{
    0U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key Dummy6 */
static const uint32 Crypto_au32KeyElementList_Dummy6[1U] =
{
    0U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key Dummy7 */
static const uint32 Crypto_au32KeyElementList_Dummy7[1U] =
{
    0U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key MacGen_Sha256_HMAC_key */
static const uint32 Crypto_au32KeyElementList_MacGen_Sha256_HMAC_key[1U] =
{
    22U
};

/* Array of indexes for each Crypto Key Element referred by Crypto Key MacVer_Sha256_HMAC_key */
static const uint32 Crypto_au32KeyElementList_MacVer_Sha256_HMAC_key[1U] =
{
    23U
};

#define CRYPTO_STOP_SEC_CONST_32
#include "Crypto_MemMap.h"

#define CRYPTO_START_SEC_CONST_UNSPECIFIED
#include "Crypto_MemMap.h"

/* Array storing the Crypto primitives in the Crypto Driver Object HaeHSE */
static const Crypto_PrimitiveType Crypto_aPrimitives_HaeHSE[5U] =
{
    {
        HASH,
        (uint8)CRYPTO_ALGOFAM_SHA2_256,
        (uint8)CRYPTO_ALGOMODE_NOT_SET,
        (uint8)CRYPTO_ALGOFAM_NOT_SET
    },
    {
        ENCRYPT,
        (uint8)CRYPTO_ALGOFAM_AES,
        (uint8)CRYPTO_ALGOMODE_ECB,
        (uint8)CRYPTO_ALGOFAM_NOT_SET
    },
    {
        DECRYPT,
        (uint8)CRYPTO_ALGOFAM_AES,
        (uint8)CRYPTO_ALGOMODE_ECB,
        (uint8)CRYPTO_ALGOFAM_NOT_SET
    },
    {
        MAC_GENERATE,
        (uint8)CRYPTO_ALGOFAM_SHA2_256,
        (uint8)CRYPTO_ALGOMODE_HMAC,
        (uint8)CRYPTO_ALGOFAM_NOT_SET
    },
    {
        MAC_VERIFY,
        (uint8)CRYPTO_ALGOFAM_SHA2_256,
        (uint8)CRYPTO_ALGOMODE_HMAC,
        (uint8)CRYPTO_ALGOFAM_NOT_SET
    }
};

                                                                /* Structure needed for encrypted symmetric key export of the HSE key associated with the Key Element PBKDF2_ExtractedKey */
static const Crypto_ExportCipherSchemeType Crypto_ExportCipherScheme_PBKDF2_ExtractedKey =
{
    /* Cipher algorithm */
    HSE_CIPHER_ALGO_AES,
    /* Cipher block mode in case a symmetric cipher is used */
    HSE_CIPHER_BLOCK_MODE_ECB,
    /* Initialization Vector length in case a symmetric cipher is used */
    0U,
    /* Pointer to array storing the Initialization Vector in case a symmetric cipher is used */
    NULL_PTR,
    /* Authenticated cipher mode in case a Authenticated cipher is used */
    (hseAuthCipherMode_t)0U,
    /* Initialization Vector length in case a Authenticated cipher is used */
    0U,
    /* Pointer to array storing the Initialization Vector in case a Authenticated cipher is used */
    NULL_PTR,
    /* Additional Data length in case a Authenticated cipher is used */
    0U,
    /* Pointer to array storing the Additional Data in case a Authenticated cipher is used */
    NULL_PTR,
    /* Hash algorithm in case a RSA OAEP cipher is used */
    HSE_HASH_ALGO_NULL,
    /* Label length in case a RSA OAEP cipher is used */
    0U,
    /* Pointer to array storing the Label in case a RSA OAEP cipher is used */
    NULL_PTR
};

                                                                                                                                #define CRYPTO_STOP_SEC_CONST_UNSPECIFIED
#include "Crypto_MemMap.h"

/*==================================================================================================
*                                         LOCAL VARIABLES
==================================================================================================*/
#define CRYPTO_START_SEC_VAR_INIT_8_NO_CACHEABLE
#include "Crypto_MemMap.h"

/* Array storing the key element information that is volatile (no need to be persistent across resets) */
static uint8 Crypto_au8VolatileKeyElemValues[126U] =
{
    /* Offset 0 - The following 4 bytes store the actual length of the key element Dummy */
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    /* Offset 4 - The following 4 bytes store the actual length of the key element PBKDF2_Source_Key_Password */
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    /* Offset 8 - The following 4 bytes store the actual length of the key element PBKDF2_Source_Key_Salt */
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    /* Offset 12 - The following 48 bytes store the buffer of the key element PBKDF2_Source_Key_Salt */
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    /* Offset 60 - The following 4 bytes store the actual length of the key element PBKDF2_Source_Key_Iteration */
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    /* Offset 64 - The following 4 bytes store the buffer of the key element PBKDF2_Source_Key_Iteration */
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    /* Offset 68 - The following 4 bytes store the actual length of the key element PBKDF2_Target_Key */
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    /* Offset 72 - The following 4 bytes store the actual length of the key element PBKDF2_Source_Key_Algorithm */
    0x01U,
    0x00U,
    0x00U,
    0x00U,
    /* Offset 76 - The following 1 bytes store the buffer of the key element PBKDF2_Source_Key_Algorithm */
    0x24U,
    /* Offset 77 - The following 4 bytes store the actual length of the key element PBKDF2_Source_Key_Algorithm_Secondary */
    0x01U,
    0x00U,
    0x00U,
    0x00U,
    /* Offset 81 - The following 1 bytes store the buffer of the key element PBKDF2_Source_Key_Algorithm_Secondary */
    0x03U,
    /* Offset 82 - The following 4 bytes store the actual length of the key element PBKDF2_Extracted_Key */
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    /* Offset 86 - The following 4 bytes store the actual length of the key element PBKDF2_ExtractedKey */
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    /* Offset 90 - The following 4 bytes store the actual length of the key element PBKDF2_ExtractedKey_forExport */
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    /* Offset 94 - The following 32 bytes store the buffer of the key element PBKDF2_ExtractedKey_forExport */
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U,
    0x00U
};

#define CRYPTO_STOP_SEC_VAR_INIT_8_NO_CACHEABLE
#include "Crypto_MemMap.h"

#define CRYPTO_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Crypto_MemMap.h"

/* Array storing the queued jobs for the Crypto Driver Object HaeHSE */
static Crypto_QueueElementType Crypto_aQueuedJobs_HaeHSE[3U];

#define CRYPTO_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Crypto_MemMap.h"

/*==================================================================================================
*                                        GLOBAL CONSTANTS
==================================================================================================*/
#define CRYPTO_START_SEC_CONST_8
#include "Crypto_MemMap.h"

/* Array storing the mapping of the MU instance per partition */
const Crypto_PartitionToMuMappingType Crypto_aPartitionToMuMapping[CRYPTO_MAX_NUMBER_PARTITIONS_U8] =
{
    {CRYPTO_MU_0_U8, 0x00U}
};

#define CRYPTO_STOP_SEC_CONST_8
#include "Crypto_MemMap.h"


#define CRYPTO_START_SEC_CONST_UNSPECIFIED
#include "Crypto_MemMap.h"

/* Array of structures storing the information of the Crypto Driver Objects mapped on partitions */
const Crypto_PartitionToCdoMappingType Crypto_aPartitionToCdoMapping[CRYPTO_MAX_NUMBER_PARTITIONS_U8] =
{
    /* Structure storing the information of the Crypto Driver Objects */
    {
        /* Number of Crypto Driver Objects */
        1U,
        /* Reference to array storing the indexes of the Crypto Driver Objects */
        Crypto_au8CDOs
    }
};

/* Array of structures storing the information about the Crypto Driver Objects */
const Crypto_ObjectType Crypto_aDriverObjectList[CRYPTO_NUMBER_OF_DRIVER_OBJECTS_U32] =
{
    /* Structure storing the information about Crypto Driver Object HaeHSE */
    {
        /* Reference to the jobs queue */
        Crypto_aQueuedJobs_HaeHSE,
        /* Jobs queue size */
        3U,
        /* Reference to the Crypto primitives list */
        Crypto_aPrimitives_HaeHSE,
        /* Number of crypto primitives */
        5U
    }
};

/* Array of structures storing the information about the Crypto Keys */
const Crypto_KeyType Crypto_aKeyList[CRYPTO_NUMBER_OF_KEYS_U32] =
{
    {
        /* Number of key elements in the key Dummy */
        1U,
        /* Reference to the list of key elements in the key Dummy */
        Crypto_au32KeyElementList_Dummy
    },
    {
        /* Number of key elements in the key Dummy2 */
        1U,
        /* Reference to the list of key elements in the key Dummy2 */
        Crypto_au32KeyElementList_Dummy2
    },
    {
        /* Number of key elements in the key PBKDF2_Source_Key */
        5U,
        /* Reference to the list of key elements in the key PBKDF2_Source_Key */
        Crypto_au32KeyElementList_PBKDF2_Source_Key
    },
    {
        /* Number of key elements in the key PBKDF2_Target_Key */
        1U,
        /* Reference to the list of key elements in the key PBKDF2_Target_Key */
        Crypto_au32KeyElementList_PBKDF2_Target_Key
    },
    {
        /* Number of key elements in the key PBKDF2_Extracted_Key */
        1U,
        /* Reference to the list of key elements in the key PBKDF2_Extracted_Key */
        Crypto_au32KeyElementList_PBKDF2_Extracted_Key
    },
    {
        /* Number of key elements in the key PBKDF2_ExtractedKey */
        2U,
        /* Reference to the list of key elements in the key PBKDF2_ExtractedKey */
        Crypto_au32KeyElementList_PBKDF2_ExtractedKey
    },
    {
        /* Number of key elements in the key PBKDF2_Encrypt_Key */
        1U,
        /* Reference to the list of key elements in the key PBKDF2_Encrypt_Key */
        Crypto_au32KeyElementList_PBKDF2_Encrypt_Key
    },
    {
        /* Number of key elements in the key PBKDF2_Decrypt_Key */
        1U,
        /* Reference to the list of key elements in the key PBKDF2_Decrypt_Key */
        Crypto_au32KeyElementList_PBKDF2_Decrypt_Key
    },
    {
        /* Number of key elements in the key PBKDF2_Source_Key_PSK0 */
        5U,
        /* Reference to the list of key elements in the key PBKDF2_Source_Key_PSK0 */
        Crypto_au32KeyElementList_PBKDF2_Source_Key_PSK0
    },
    {
        /* Number of key elements in the key PBKDF2_Source_Key_PSK1 */
        5U,
        /* Reference to the list of key elements in the key PBKDF2_Source_Key_PSK1 */
        Crypto_au32KeyElementList_PBKDF2_Source_Key_PSK1
    },
    {
        /* Number of key elements in the key PBKDF2_Source_Key_PSK2 */
        5U,
        /* Reference to the list of key elements in the key PBKDF2_Source_Key_PSK2 */
        Crypto_au32KeyElementList_PBKDF2_Source_Key_PSK2
    },
    {
        /* Number of key elements in the key PBKDF2_Source_Key_PSK3 */
        5U,
        /* Reference to the list of key elements in the key PBKDF2_Source_Key_PSK3 */
        Crypto_au32KeyElementList_PBKDF2_Source_Key_PSK3
    },
    {
        /* Number of key elements in the key PBKDF2_Source_Key_PSK4 */
        5U,
        /* Reference to the list of key elements in the key PBKDF2_Source_Key_PSK4 */
        Crypto_au32KeyElementList_PBKDF2_Source_Key_PSK4
    },
    {
        /* Number of key elements in the key PBKDF2_Source_Key_PSK5 */
        5U,
        /* Reference to the list of key elements in the key PBKDF2_Source_Key_PSK5 */
        Crypto_au32KeyElementList_PBKDF2_Source_Key_PSK5
    },
    {
        /* Number of key elements in the key PBKDF2_Source_Key_PSK6 */
        5U,
        /* Reference to the list of key elements in the key PBKDF2_Source_Key_PSK6 */
        Crypto_au32KeyElementList_PBKDF2_Source_Key_PSK6
    },
    {
        /* Number of key elements in the key PBKDF2_Source_Key_PSK7 */
        5U,
        /* Reference to the list of key elements in the key PBKDF2_Source_Key_PSK7 */
        Crypto_au32KeyElementList_PBKDF2_Source_Key_PSK7
    },
    {
        /* Number of key elements in the key PBKDF2_Source_Key_PSK8 */
        5U,
        /* Reference to the list of key elements in the key PBKDF2_Source_Key_PSK8 */
        Crypto_au32KeyElementList_PBKDF2_Source_Key_PSK8
    },
    {
        /* Number of key elements in the key PBKDF2_Source_Key_PSK9 */
        5U,
        /* Reference to the list of key elements in the key PBKDF2_Source_Key_PSK9 */
        Crypto_au32KeyElementList_PBKDF2_Source_Key_PSK9
    },
    {
        /* Number of key elements in the key Dummy3 */
        1U,
        /* Reference to the list of key elements in the key Dummy3 */
        Crypto_au32KeyElementList_Dummy3
    },
    {
        /* Number of key elements in the key Dummy4 */
        1U,
        /* Reference to the list of key elements in the key Dummy4 */
        Crypto_au32KeyElementList_Dummy4
    },
    {
        /* Number of key elements in the key Dummy5 */
        1U,
        /* Reference to the list of key elements in the key Dummy5 */
        Crypto_au32KeyElementList_Dummy5
    },
    {
        /* Number of key elements in the key Dummy6 */
        1U,
        /* Reference to the list of key elements in the key Dummy6 */
        Crypto_au32KeyElementList_Dummy6
    },
    {
        /* Number of key elements in the key Dummy7 */
        1U,
        /* Reference to the list of key elements in the key Dummy7 */
        Crypto_au32KeyElementList_Dummy7
    },
    {
        /* Number of key elements in the key MacGen_Sha256_HMAC_key */
        1U,
        /* Reference to the list of key elements in the key MacGen_Sha256_HMAC_key */
        Crypto_au32KeyElementList_MacGen_Sha256_HMAC_key
    },
    {
        /* Number of key elements in the key MacVer_Sha256_HMAC_key */
        1U,
        /* Reference to the list of key elements in the key MacVer_Sha256_HMAC_key */
        Crypto_au32KeyElementList_MacVer_Sha256_HMAC_key
    }
};

/* Array of structures storing the information about the Crypto Key Elements */
const Crypto_KeyElementType Crypto_aKeyElementList[CRYPTO_NUMBER_OF_KEY_ELEMENTS_U32] =
{
    /* Structure containing information for Key Element Dummy */
    {
        /* KeyElementId */
        1U,
        /* Allow partial access */
        (boolean)FALSE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)FALSE,
        /* Read access type */
        CRYPTO_RA_ALLOWED,
        /* Key element max size */
        32U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8VolatileKeyElemValues[0U],
        /* Pointer to location storing the Key Element value */
        NULL_PTR,
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        NULL_PTR,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        HSE_EC_CURVE_NONE,
        /* Flags of the HSE key */
        ((uint16)(HSE_KF_USAGE_ENCRYPT | 0U)),
        /* HSE key SMR flags */
        0x00000000U,
        /* HSE key type */
        (uint8)HSE_KEY_TYPE_AES,
        /* Identifier of the HSE key in the key catalogs */
        0x00020000U
    },
    /* Structure containing information for Key Element PBKDF2_Source_Key_Password */
    {
        /* KeyElementId */
        1U,
        /* Allow partial access */
        (boolean)FALSE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)FALSE,
        /* Read access type */
        CRYPTO_RA_ALLOWED,
        /* Key element max size */
        16U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8VolatileKeyElemValues[4U],
        /* Pointer to location storing the Key Element value */
        NULL_PTR,
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        NULL_PTR,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        HSE_EC_CURVE_NONE,
        /* Flags of the HSE key */
        ((uint16)(HSE_KF_USAGE_ENCRYPT | HSE_KF_USAGE_DERIVE | 0U)),
        /* HSE key SMR flags */
        0x00000000U,
        /* HSE key type */
        (uint8)HSE_KEY_TYPE_AES,
        /* Identifier of the HSE key in the key catalogs */
        0x00020100U
    },
    /* Structure containing information for Key Element PBKDF2_Source_Key_Salt */
    {
        /* KeyElementId */
        13U,
        /* Allow partial access */
        (boolean)TRUE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)FALSE,
        /* Read access type */
        CRYPTO_RA_ALLOWED,
        /* Key element max size */
        48U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8VolatileKeyElemValues[8U],
        /* Pointer to location storing the Key Element value */
        &Crypto_au8VolatileKeyElemValues[12U],
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        NULL_PTR,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        0U,
        /* Flags of the HSE key */
        0U,
        /* HSE key SMR flags */
        0U,
        /* HSE key type */
        0U,
        /* Identifier of the HSE key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE
    },
    /* Structure containing information for Key Element PBKDF2_Source_Key_Iteration */
    {
        /* KeyElementId */
        14U,
        /* Allow partial access */
        (boolean)TRUE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)FALSE,
        /* Read access type */
        CRYPTO_RA_ALLOWED,
        /* Key element max size */
        4U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8VolatileKeyElemValues[60U],
        /* Pointer to location storing the Key Element value */
        &Crypto_au8VolatileKeyElemValues[64U],
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        NULL_PTR,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        0U,
        /* Flags of the HSE key */
        0U,
        /* HSE key SMR flags */
        0U,
        /* HSE key type */
        0U,
        /* Identifier of the HSE key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE
    },
    /* Structure containing information for Key Element PBKDF2_Target_Key */
    {
        /* KeyElementId */
        1U,
        /* Allow partial access */
        (boolean)FALSE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)FALSE,
        /* Read access type */
        CRYPTO_RA_ALLOWED,
        /* Key element max size */
        32U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8VolatileKeyElemValues[68U],
        /* Pointer to location storing the Key Element value */
        NULL_PTR,
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        NULL_PTR,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        HSE_EC_CURVE_NONE,
        /* Flags of the HSE key */
        ((uint16)(HSE_KF_USAGE_ENCRYPT | 0U)),
        /* HSE key SMR flags */
        0x00000000U,
        /* HSE key type */
        (uint8)HSE_KEY_TYPE_SHARED_SECRET,
        /* Identifier of the HSE key in the key catalogs */
        0x00020200U
    },
    /* Structure containing information for Key Element PBKDF2_Source_Key_Algorithm */
    {
        /* KeyElementId */
        15U,
        /* Allow partial access */
        (boolean)FALSE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)FALSE,
        /* Read access type */
        CRYPTO_RA_ALLOWED,
        /* Key element max size */
        1U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8VolatileKeyElemValues[72U],
        /* Pointer to location storing the Key Element value */
        &Crypto_au8VolatileKeyElemValues[76U],
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        NULL_PTR,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        0U,
        /* Flags of the HSE key */
        0U,
        /* HSE key SMR flags */
        0U,
        /* HSE key type */
        0U,
        /* Identifier of the HSE key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE
    },
    /* Structure containing information for Key Element PBKDF2_Source_Key_Algorithm_Secondary */
    {
        /* KeyElementId */
        100U,
        /* Allow partial access */
        (boolean)FALSE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)FALSE,
        /* Read access type */
        CRYPTO_RA_ALLOWED,
        /* Key element max size */
        1U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8VolatileKeyElemValues[77U],
        /* Pointer to location storing the Key Element value */
        &Crypto_au8VolatileKeyElemValues[81U],
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        NULL_PTR,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        0U,
        /* Flags of the HSE key */
        0U,
        /* HSE key SMR flags */
        0U,
        /* HSE key type */
        0U,
        /* Identifier of the HSE key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE
    },
    /* Structure containing information for Key Element PBKDF2_Extracted_Key */
    {
        /* KeyElementId */
        1U,
        /* Allow partial access */
        (boolean)TRUE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)FALSE,
        /* Read access type */
        CRYPTO_RA_ALLOWED,
        /* Key element max size */
        16U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8VolatileKeyElemValues[82U],
        /* Pointer to location storing the Key Element value */
        NULL_PTR,
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        NULL_PTR,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        HSE_EC_CURVE_NONE,
        /* Flags of the HSE key */
        ((uint16)(HSE_KF_USAGE_ENCRYPT | 0U)),
        /* HSE key SMR flags */
        0x00000000U,
        /* HSE key type */
        (uint8)HSE_KEY_TYPE_AES,
        /* Identifier of the HSE key in the key catalogs */
        0x00020300U
    },
    /* Structure containing information for Key Element PBKDF2_ExtractedKey */
    {
        /* KeyElementId */
        1U,
        /* Allow partial access */
        (boolean)TRUE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)FALSE,
        /* Read access type */
        CRYPTO_RA_ENCRYPTED,
        /* Key element max size */
        32U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8VolatileKeyElemValues[86U],
        /* Pointer to location storing the Key Element value */
        NULL_PTR,
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        0x00010100U,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        &Crypto_ExportCipherScheme_PBKDF2_ExtractedKey,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        HSE_EC_CURVE_NONE,
        /* Flags of the HSE key */
        ((uint16)(HSE_KF_USAGE_ENCRYPT | HSE_KF_ACCESS_EXPORTABLE | 0U)),
        /* HSE key SMR flags */
        0x00000000U,
        /* HSE key type */
        (uint8)HSE_KEY_TYPE_AES,
        /* Identifier of the HSE key in the key catalogs */
        0x00020400U
    },
    /* Structure containing information for Key Element PBKDF2_ExtractedKey_forExport */
    {
        /* KeyElementId */
        99U,
        /* Allow partial access */
        (boolean)FALSE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)FALSE,
        /* Read access type */
        CRYPTO_RA_ALLOWED,
        /* Key element max size */
        32U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8VolatileKeyElemValues[90U],
        /* Pointer to location storing the Key Element value */
        &Crypto_au8VolatileKeyElemValues[94U],
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        NULL_PTR,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        0U,
        /* Flags of the HSE key */
        0U,
        /* HSE key SMR flags */
        0U,
        /* HSE key type */
        0U,
        /* Identifier of the HSE key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE
    },
    /* Structure containing information for Key Element PBKDF2_Encrypt_Key */
    {
        /* KeyElementId */
        1U,
        /* Allow partial access */
        (boolean)FALSE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)TRUE,
        /* Read access type */
        CRYPTO_RA_ALLOWED,
        /* Key element max size */
        16U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8NvramBlob1[0U],
        /* Pointer to location storing the Key Element value */
        NULL_PTR,
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        NULL_PTR,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        HSE_EC_CURVE_NONE,
        /* Flags of the HSE key */
        ((uint16)(HSE_KF_USAGE_KEY_PROVISION | HSE_KF_USAGE_ENCRYPT | HSE_KF_USAGE_SIGN | 0U)),
        /* HSE key SMR flags */
        0x00000000U,
        /* HSE key type */
        (uint8)HSE_KEY_TYPE_AES,
        /* Identifier of the HSE key in the key catalogs */
        0x00010100U
    },
    /* Structure containing information for Key Element PBKDF2_Decrypt_Key */
    {
        /* KeyElementId */
        1U,
        /* Allow partial access */
        (boolean)FALSE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)TRUE,
        /* Read access type */
        CRYPTO_RA_ALLOWED,
        /* Key element max size */
        16U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8NvramBlob1[4U],
        /* Pointer to location storing the Key Element value */
        NULL_PTR,
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        NULL_PTR,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        HSE_EC_CURVE_NONE,
        /* Flags of the HSE key */
        ((uint16)(HSE_KF_USAGE_DECRYPT | HSE_KF_USAGE_VERIFY | 0U)),
        /* HSE key SMR flags */
        0x00000000U,
        /* HSE key type */
        (uint8)HSE_KEY_TYPE_AES,
        /* Identifier of the HSE key in the key catalogs */
        0x00010101U
    },
    /* Structure containing information for Key Element PBKDF2_Source_Key_PSK0 */
    {
        /* KeyElementId */
        1U,
        /* Allow partial access */
        (boolean)FALSE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)TRUE,
        /* Read access type */
        CRYPTO_RA_ALLOWED,
        /* Key element max size */
        16U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8NvramBlob1[8U],
        /* Pointer to location storing the Key Element value */
        NULL_PTR,
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        NULL_PTR,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        HSE_EC_CURVE_NONE,
        /* Flags of the HSE key */
        ((uint16)(HSE_KF_USAGE_ENCRYPT | HSE_KF_USAGE_DERIVE | 0U)),
        /* HSE key SMR flags */
        0x00000000U,
        /* HSE key type */
        (uint8)HSE_KEY_TYPE_AES,
        /* Identifier of the HSE key in the key catalogs */
        0x00010400U
    },
    /* Structure containing information for Key Element PBKDF2_Source_Key_PSK1 */
    {
        /* KeyElementId */
        1U,
        /* Allow partial access */
        (boolean)FALSE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)TRUE,
        /* Read access type */
        CRYPTO_RA_ALLOWED,
        /* Key element max size */
        16U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8NvramBlob1[12U],
        /* Pointer to location storing the Key Element value */
        NULL_PTR,
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        NULL_PTR,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        HSE_EC_CURVE_NONE,
        /* Flags of the HSE key */
        ((uint16)(HSE_KF_USAGE_ENCRYPT | HSE_KF_USAGE_DERIVE | 0U)),
        /* HSE key SMR flags */
        0x00000000U,
        /* HSE key type */
        (uint8)HSE_KEY_TYPE_AES,
        /* Identifier of the HSE key in the key catalogs */
        0x00010401U
    },
    /* Structure containing information for Key Element PBKDF2_Source_Key_PSK2 */
    {
        /* KeyElementId */
        1U,
        /* Allow partial access */
        (boolean)FALSE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)TRUE,
        /* Read access type */
        CRYPTO_RA_ALLOWED,
        /* Key element max size */
        16U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8NvramBlob1[16U],
        /* Pointer to location storing the Key Element value */
        NULL_PTR,
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        NULL_PTR,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        HSE_EC_CURVE_NONE,
        /* Flags of the HSE key */
        ((uint16)(HSE_KF_USAGE_ENCRYPT | HSE_KF_USAGE_DERIVE | 0U)),
        /* HSE key SMR flags */
        0x00000000U,
        /* HSE key type */
        (uint8)HSE_KEY_TYPE_AES,
        /* Identifier of the HSE key in the key catalogs */
        0x00010402U
    },
    /* Structure containing information for Key Element PBKDF2_Source_Key_PSK3 */
    {
        /* KeyElementId */
        1U,
        /* Allow partial access */
        (boolean)FALSE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)TRUE,
        /* Read access type */
        CRYPTO_RA_ALLOWED,
        /* Key element max size */
        16U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8NvramBlob1[20U],
        /* Pointer to location storing the Key Element value */
        NULL_PTR,
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        NULL_PTR,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        HSE_EC_CURVE_NONE,
        /* Flags of the HSE key */
        ((uint16)(HSE_KF_USAGE_ENCRYPT | HSE_KF_USAGE_DERIVE | 0U)),
        /* HSE key SMR flags */
        0x00000000U,
        /* HSE key type */
        (uint8)HSE_KEY_TYPE_AES,
        /* Identifier of the HSE key in the key catalogs */
        0x00010403U
    },
    /* Structure containing information for Key Element PBKDF2_Source_Key_PSK4 */
    {
        /* KeyElementId */
        1U,
        /* Allow partial access */
        (boolean)FALSE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)TRUE,
        /* Read access type */
        CRYPTO_RA_ALLOWED,
        /* Key element max size */
        16U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8NvramBlob1[24U],
        /* Pointer to location storing the Key Element value */
        NULL_PTR,
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        NULL_PTR,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        HSE_EC_CURVE_NONE,
        /* Flags of the HSE key */
        ((uint16)(HSE_KF_USAGE_ENCRYPT | HSE_KF_USAGE_DERIVE | 0U)),
        /* HSE key SMR flags */
        0x00000000U,
        /* HSE key type */
        (uint8)HSE_KEY_TYPE_AES,
        /* Identifier of the HSE key in the key catalogs */
        0x00010404U
    },
    /* Structure containing information for Key Element PBKDF2_Source_Key_PSK5 */
    {
        /* KeyElementId */
        1U,
        /* Allow partial access */
        (boolean)FALSE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)TRUE,
        /* Read access type */
        CRYPTO_RA_ALLOWED,
        /* Key element max size */
        16U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8NvramBlob1[28U],
        /* Pointer to location storing the Key Element value */
        NULL_PTR,
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        NULL_PTR,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        HSE_EC_CURVE_NONE,
        /* Flags of the HSE key */
        ((uint16)(HSE_KF_USAGE_ENCRYPT | HSE_KF_USAGE_DERIVE | 0U)),
        /* HSE key SMR flags */
        0x00000000U,
        /* HSE key type */
        (uint8)HSE_KEY_TYPE_AES,
        /* Identifier of the HSE key in the key catalogs */
        0x00010405U
    },
    /* Structure containing information for Key Element PBKDF2_Source_Key_PSK6 */
    {
        /* KeyElementId */
        1U,
        /* Allow partial access */
        (boolean)FALSE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)TRUE,
        /* Read access type */
        CRYPTO_RA_ALLOWED,
        /* Key element max size */
        16U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8NvramBlob1[32U],
        /* Pointer to location storing the Key Element value */
        NULL_PTR,
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        NULL_PTR,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        HSE_EC_CURVE_NONE,
        /* Flags of the HSE key */
        ((uint16)(HSE_KF_USAGE_ENCRYPT | HSE_KF_USAGE_DERIVE | 0U)),
        /* HSE key SMR flags */
        0x00000000U,
        /* HSE key type */
        (uint8)HSE_KEY_TYPE_AES,
        /* Identifier of the HSE key in the key catalogs */
        0x00010406U
    },
    /* Structure containing information for Key Element PBKDF2_Source_Key_PSK7 */
    {
        /* KeyElementId */
        1U,
        /* Allow partial access */
        (boolean)FALSE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)TRUE,
        /* Read access type */
        CRYPTO_RA_ALLOWED,
        /* Key element max size */
        16U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8NvramBlob1[36U],
        /* Pointer to location storing the Key Element value */
        NULL_PTR,
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        NULL_PTR,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        HSE_EC_CURVE_NONE,
        /* Flags of the HSE key */
        ((uint16)(HSE_KF_USAGE_ENCRYPT | HSE_KF_USAGE_DERIVE | 0U)),
        /* HSE key SMR flags */
        0x00000000U,
        /* HSE key type */
        (uint8)HSE_KEY_TYPE_AES,
        /* Identifier of the HSE key in the key catalogs */
        0x00010407U
    },
    /* Structure containing information for Key Element PBKDF2_Source_Key_PSK8 */
    {
        /* KeyElementId */
        1U,
        /* Allow partial access */
        (boolean)FALSE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)TRUE,
        /* Read access type */
        CRYPTO_RA_ALLOWED,
        /* Key element max size */
        16U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8NvramBlob1[40U],
        /* Pointer to location storing the Key Element value */
        NULL_PTR,
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        NULL_PTR,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        HSE_EC_CURVE_NONE,
        /* Flags of the HSE key */
        ((uint16)(HSE_KF_USAGE_ENCRYPT | HSE_KF_USAGE_DERIVE | 0U)),
        /* HSE key SMR flags */
        0x00000000U,
        /* HSE key type */
        (uint8)HSE_KEY_TYPE_AES,
        /* Identifier of the HSE key in the key catalogs */
        0x00010408U
    },
    /* Structure containing information for Key Element PBKDF2_Source_Key_PSK9 */
    {
        /* KeyElementId */
        1U,
        /* Allow partial access */
        (boolean)FALSE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)TRUE,
        /* Read access type */
        CRYPTO_RA_ALLOWED,
        /* Key element max size */
        16U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8NvramBlob1[44U],
        /* Pointer to location storing the Key Element value */
        NULL_PTR,
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        NULL_PTR,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        HSE_EC_CURVE_NONE,
        /* Flags of the HSE key */
        ((uint16)(HSE_KF_USAGE_ENCRYPT | HSE_KF_USAGE_DERIVE | 0U)),
        /* HSE key SMR flags */
        0x00000000U,
        /* HSE key type */
        (uint8)HSE_KEY_TYPE_AES,
        /* Identifier of the HSE key in the key catalogs */
        0x00010409U
    },
    /* Structure containing information for Key Element MacGen_Sha256_HMAC_key */
    {
        /* KeyElementId */
        1U,
        /* Allow partial access */
        (boolean)FALSE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)TRUE,
        /* Read access type */
        CRYPTO_RA_ALLOWED,
        /* Key element max size */
        32U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8NvramBlob1[48U],
        /* Pointer to location storing the Key Element value */
        NULL_PTR,
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        NULL_PTR,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        HSE_EC_CURVE_NONE,
        /* Flags of the HSE key */
        ((uint16)(HSE_KF_USAGE_SIGN | 0U)),
        /* HSE key SMR flags */
        0x00000000U,
        /* HSE key type */
        (uint8)HSE_KEY_TYPE_HMAC,
        /* Identifier of the HSE key in the key catalogs */
        0x00010300U
    },
    /* Structure containing information for Key Element MacVer_Sha256_HMAC_key */
    {
        /* KeyElementId */
        1U,
        /* Allow partial access */
        (boolean)FALSE,
        /* Key element format */
        CRYPTO_KE_FORMAT_BIN_OCTET,
        /* Key element persistent */
        (boolean)TRUE,
        /* Read access type */
        CRYPTO_RA_ALLOWED,
        /* Key element max size */
        32U,
        /* Write access type */
        CRYPTO_WA_ALLOWED,
        /* Pointer to location storing the Key Element actual size */
        (uint32*)&Crypto_au8NvramBlob1[52U],
        /* Pointer to location storing the Key Element value */
        NULL_PTR,
        /* Identifier of the cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key import */
        NULL_PTR,
        /* Identifier of the authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the authentication MAC scheme for key import */
        NULL_PTR,
        /* Reference to the authentication signature scheme for key import */
        NULL_PTR,
        /* Reference to the authentication container for key import */
        NULL_PTR,
        /* HSE key counter */
        0U,
        /* Identifier of the export cipher key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the cipher scheme for key export, only for symmetric key export */
        NULL_PTR,
        /* Identifier of the export authentication key in the key catalogs */
        (uint32)HSE_INVALID_KEY_HANDLE,
        /* Reference to the MAC authentication scheme for key export */
        NULL_PTR,
        /* Reference to the signature authentication scheme for key export */
        NULL_PTR,
        /* ECC curve id */
        HSE_EC_CURVE_NONE,
        /* Flags of the HSE key */
        ((uint16)(HSE_KF_USAGE_VERIFY | 0U)),
        /* HSE key SMR flags */
        0x00000000U,
        /* HSE key type */
        (uint8)HSE_KEY_TYPE_HMAC,
        /* Identifier of the HSE key in the key catalogs */
        0x00010301U
    }
};

/* Table containing NVM key catalog entries */
const hseKeyGroupCfgEntry_t aHseNvmKeyCatalog[] =
{
    /* NvmKeyCatalog0 */
    {(HSE_MU0_MASK), HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_AES, 10U, 128U, {0U, 0U}},
    /* NvmKeyCatalog_AES */
    {(HSE_MU0_MASK), HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_AES, 2U, 128U, {0U, 0U}},
    /* NvmKeyCatalog_FST_PSK */
    {(HSE_MU0_MASK), HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_AES, 10U, 128U, {0U, 0U}},
    /* NvmKeyCatalog_Sha256_HMAC */
    {(HSE_MU0_MASK), HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_HMAC, 2U, 256U, {0U, 0U}},
    /* NvmKeyCatalog_Tier_PSK */
    {(HSE_MU0_MASK), HSE_KEY_OWNER_CUST, HSE_KEY_TYPE_AES, 10U, 128U, {0U, 0U}},
    /* Marker to end the key catalog */
    {0U, 0U, 0U, 0U, 0U, {0U, 0U}}
};

/* Table containing RAM key catalog entries */
const hseKeyGroupCfgEntry_t aHseRamKeyCatalog[] =
{
    /* RamKeyCatalog0 */
    {(HSE_MU0_MASK), HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_AES, 3U, 128U, {0U, 0U}},
    /* RamKeyCatalog1 */
    {(HSE_MU0_MASK), HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_AES, 3U, 128U, {0U, 0U}},
    /* RamKeyCatalog2 */
    {(HSE_MU0_MASK), HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_SHARED_SECRET, 3U, 256U, {0U, 0U}},
    /* RamKeyCatalog3 */
    {(HSE_MU0_MASK), HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_AES, 3U, 128U, {0U, 0U}},
    /* RamKeyCatalog_PBKDF2 */
    {(HSE_MU0_MASK), HSE_KEY_OWNER_ANY, HSE_KEY_TYPE_AES, 4U, 256U, {0U, 0U}},
    /* Marker to end the key catalog */
    {0U, 0U, 0U, 0U, 0U, {0U, 0U}}
};

#define CRYPTO_STOP_SEC_CONST_UNSPECIFIED
#include "Crypto_MemMap.h"

/*==================================================================================================
*                                        GLOBAL VARIABLES
==================================================================================================*/
#define CRYPTO_START_SEC_VAR_CLEARED_8
#include "Crypto_MemMap.h"

/* Array of 8 bit blocks storing a bit map of valid flags for each Crypto key */
uint8 Crypto_au8NvramBlob0[CRYPTO_SIZEOF_NVRAM_BLOB_0];

#define CRYPTO_STOP_SEC_VAR_CLEARED_8
#include "Crypto_MemMap.h"

#define CRYPTO_START_SEC_VAR_CLEARED_8_NO_CACHEABLE
#include "Crypto_MemMap.h"

/* Array storing blob 1 containing information that should be persistent between resets */
uint8 Crypto_au8NvramBlob1[CRYPTO_SIZEOF_NVRAM_BLOB_1];

#define CRYPTO_STOP_SEC_VAR_CLEARED_8_NO_CACHEABLE
#include "Crypto_MemMap.h"

#define CRYPTO_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Crypto_MemMap.h"

Crypto_ObjectQueueType Crypto_aObjectQueueList[CRYPTO_NUMBER_OF_DRIVER_OBJECTS_U32];

#define CRYPTO_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Crypto_MemMap.h"

/*==================================================================================================
*                                    LOCAL FUNCTION PROTOTYPES
==================================================================================================*/

/*==================================================================================================
*                                         LOCAL FUNCTIONS
==================================================================================================*/

/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/

#ifdef __cplusplus
}
#endif

/** @} */

