/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CryIf_Cfg.c                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CRYIF                                                 **
**                                                                            **
**  PURPOSE   : Define configuration data                                     **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: yes                                       **
**                                                                            **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Framework version : 1.1.5                                          **
**                                                                            **
**  Module version : 1.0.5.0                                         **
**                                                                            **
**  Tool Version: 4.4.7                                              **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/
/*
* INPUT FILE:      Configuration\Definition\Crypto_s32k312_mqfp172.epd
*                  Configuration\Definition\ECUConfigurationParameters.arxml
*                  Configuration\Ecu\Ecud_CryIf.arxml           
*                  Configuration\Ecu\Ecud_Crypto_76_HaeModule.arxml
*                  Configuration\Ecu\Mcal\Ecud_Crypto.arxml     
*                  Configuration\System\Bswmd\Bswmd_Crypto.arxml
*                  Generated\Bsw_Output\bswmd\Bswmd_CryIf.arxml 
*                  Generated\Bsw_Output\bswmd\Bswmd_Crypto_76_HaeModule.arxml
*                  Static_Code\Modules\CryIf_R44\generator\CryIf_ECU_Configuration_PDF.arxml
*                  Static_Code\Modules\Crypto_76_HaeModule_R44\generator\AUTOSAR_Crypto_76_HaeModule_ECU_Configuration_PDF.arxml
* GENERATED ON: The time-stamp is removed
*/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* For header file */
#include "CryIf_Cfg.h"
/* For configured data declare */
#include "CryIf_Globals.h"
/* For Crypto Driver 0 */
#include "Crypto_76_HaeModule.h"
/* For Crypto Driver 1 */
#include "Crypto.h"

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
/* Dependent module files version information */
#define CRYIF_CRYPTO_AR_RELEASE_MAJOR_VERSION              (0x04U)
#define CRYIF_CRYPTO_AR_RELEASE_MINOR_VERSION              (0x04U)
/* Check AUTOSAR version module Crypto_76_HaeModule */
#if (CRYPTO_76_HAEMODULE_AR_RELEASE_MAJOR_VERSION != \
  CRYIF_CRYPTO_AR_RELEASE_MAJOR_VERSION)
  #error "Crypto_76_HaeModule.h : Mismatch in Specification Major Version"
#endif
#if (CRYPTO_76_HAEMODULE_AR_RELEASE_MINOR_VERSION != \
  CRYIF_CRYPTO_AR_RELEASE_MINOR_VERSION)
  #error "Crypto_76_HaeModule.h : Mismatch in Specification Minor Version"
#endif
/* Check AUTOSAR version module Crypto */
#if (CRYPTO_AR_RELEASE_MAJOR_VERSION != \
  CRYIF_CRYPTO_AR_RELEASE_MAJOR_VERSION)
  #error "Crypto.h : Mismatch in Specification Major Version"
#endif
#if (CRYPTO_AR_RELEASE_MINOR_VERSION != \
  CRYIF_CRYPTO_AR_RELEASE_MINOR_VERSION)
  #error "Crypto.h : Mismatch in Specification Minor Version"
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CRYIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array provides a list of channel information */
CONST(CryIf_ChannelType, CRYIF_CONFIG_DATA) \
  CryIf_ChannelList[CRYIF_TOTAL_CHANNEL_ID_NUMBER] = \
{
  /* Element 0 */
  {
    /* Crypto interface channel Id */
    (uint32)0,
    /* Crypto Driver object ID */
    (uint32)0,
    /* Index of array Crypto Driver function pointer */
    (uint8)0
  },
  /* Element 1 */
  {
    /* Crypto interface channel Id */
    (uint32)1,
    /* Crypto Driver object ID */
    (uint32)0,
    /* Index of array Crypto Driver function pointer */
    (uint8)1
  }
};

/* Array provides a list of crypto interface key information */
CONST(CryIf_KeyType, CRYIF_CONFIG_DATA) \
  CryIf_CryIfKeyList[CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER] = \
{
  /* Element 0 */
  {
    /* Crypto Interface key ID */
    (uint32)0,
    /* Crypto Driver key ID */
    (uint32)0,
    /* Index of array Crypto Driver function pointer */
    (uint8)0,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)0
  },
  /* Element 1 */
  {
    /* Crypto Interface key ID */
    (uint32)1,
    /* Crypto Driver key ID */
    (uint32)0,
    /* Index of array Crypto Driver function pointer */
    (uint8)1,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)1
  },
  /* Element 2 */
  {
    /* Crypto Interface key ID */
    (uint32)2,
    /* Crypto Driver key ID */
    (uint32)2,
    /* Index of array Crypto Driver function pointer */
    (uint8)1,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)2
  },
  /* Element 3 */
  {
    /* Crypto Interface key ID */
    (uint32)3,
    /* Crypto Driver key ID */
    (uint32)3,
    /* Index of array Crypto Driver function pointer */
    (uint8)1,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)7
  },
  /* Element 4 */
  {
    /* Crypto Interface key ID */
    (uint32)4,
    /* Crypto Driver key ID */
    (uint32)4,
    /* Index of array Crypto Driver function pointer */
    (uint8)1,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)8
  },
  /* Element 5 */
  {
    /* Crypto Interface key ID */
    (uint32)5,
    /* Crypto Driver key ID */
    (uint32)5,
    /* Index of array Crypto Driver function pointer */
    (uint8)1,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)9
  },
  /* Element 6 */
  {
    /* Crypto Interface key ID */
    (uint32)6,
    /* Crypto Driver key ID */
    (uint32)6,
    /* Index of array Crypto Driver function pointer */
    (uint8)1,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)11
  },
  /* Element 7 */
  {
    /* Crypto Interface key ID */
    (uint32)7,
    /* Crypto Driver key ID */
    (uint32)7,
    /* Index of array Crypto Driver function pointer */
    (uint8)1,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)12
  },
  /* Element 8 */
  {
    /* Crypto Interface key ID */
    (uint32)8,
    /* Crypto Driver key ID */
    (uint32)8,
    /* Index of array Crypto Driver function pointer */
    (uint8)1,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)13
  },
  /* Element 9 */
  {
    /* Crypto Interface key ID */
    (uint32)9,
    /* Crypto Driver key ID */
    (uint32)9,
    /* Index of array Crypto Driver function pointer */
    (uint8)1,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)18
  },
  /* Element 10 */
  {
    /* Crypto Interface key ID */
    (uint32)10,
    /* Crypto Driver key ID */
    (uint32)10,
    /* Index of array Crypto Driver function pointer */
    (uint8)1,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)23
  },
  /* Element 11 */
  {
    /* Crypto Interface key ID */
    (uint32)11,
    /* Crypto Driver key ID */
    (uint32)11,
    /* Index of array Crypto Driver function pointer */
    (uint8)1,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)28
  },
  /* Element 12 */
  {
    /* Crypto Interface key ID */
    (uint32)12,
    /* Crypto Driver key ID */
    (uint32)12,
    /* Index of array Crypto Driver function pointer */
    (uint8)1,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)33
  },
  /* Element 13 */
  {
    /* Crypto Interface key ID */
    (uint32)13,
    /* Crypto Driver key ID */
    (uint32)13,
    /* Index of array Crypto Driver function pointer */
    (uint8)1,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)38
  },
  /* Element 14 */
  {
    /* Crypto Interface key ID */
    (uint32)14,
    /* Crypto Driver key ID */
    (uint32)14,
    /* Index of array Crypto Driver function pointer */
    (uint8)1,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)43
  },
  /* Element 15 */
  {
    /* Crypto Interface key ID */
    (uint32)15,
    /* Crypto Driver key ID */
    (uint32)15,
    /* Index of array Crypto Driver function pointer */
    (uint8)1,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)48
  },
  /* Element 16 */
  {
    /* Crypto Interface key ID */
    (uint32)16,
    /* Crypto Driver key ID */
    (uint32)16,
    /* Index of array Crypto Driver function pointer */
    (uint8)1,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)53
  },
  /* Element 17 */
  {
    /* Crypto Interface key ID */
    (uint32)17,
    /* Crypto Driver key ID */
    (uint32)17,
    /* Index of array Crypto Driver function pointer */
    (uint8)1,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)58
  },
  /* Element 18 */
  {
    /* Crypto Interface key ID */
    (uint32)18,
    /* Crypto Driver key ID */
    (uint32)1,
    /* Index of array Crypto Driver function pointer */
    (uint8)0,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)63
  },
  /* Element 19 */
  {
    /* Crypto Interface key ID */
    (uint32)19,
    /* Crypto Driver key ID */
    (uint32)2,
    /* Index of array Crypto Driver function pointer */
    (uint8)0,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)64
  },
  /* Element 20 */
  {
    /* Crypto Interface key ID */
    (uint32)20,
    /* Crypto Driver key ID */
    (uint32)3,
    /* Index of array Crypto Driver function pointer */
    (uint8)0,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)65
  },
  /* Element 21 */
  {
    /* Crypto Interface key ID */
    (uint32)21,
    /* Crypto Driver key ID */
    (uint32)4,
    /* Index of array Crypto Driver function pointer */
    (uint8)0,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)67
  },
  /* Element 22 */
  {
    /* Crypto Interface key ID */
    (uint32)22,
    /* Crypto Driver key ID */
    (uint32)5,
    /* Index of array Crypto Driver function pointer */
    (uint8)0,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)69
  },
  /* Element 23 */
  {
    /* Crypto Interface key ID */
    (uint32)23,
    /* Crypto Driver key ID */
    (uint32)23,
    /* Index of array Crypto Driver function pointer */
    (uint8)1,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)70
  },
  /* Element 24 */
  {
    /* Crypto Interface key ID */
    (uint32)24,
    /* Crypto Driver key ID */
    (uint32)24,
    /* Index of array Crypto Driver function pointer */
    (uint8)1,
    /* Index of array Crypto driver key element holds start value of a key */
    (uint32)71
  }
};

/* Array provides a list of crypto driver key elements */
CONST(CryIf_KeyElementType, CRYIF_CONFIG_DATA) \
  CryIf_KeyElementList[CRYIF_TOTAL_KEY_ELEMENT_NUMBER] = \
{
  /* Element 0 */
  {
    /* Crypto key element ID */
    (uint32)4,
    /* Crypto key element maximum size */
    (uint32)4
  },
  /* Element 1 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)32
  },
  /* Element 2 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)16
  },
  /* Element 3 */
  {
    /* Crypto key element ID */
    (uint32)13,
    /* Crypto key element maximum size */
    (uint32)48
  },
  /* Element 4 */
  {
    /* Crypto key element ID */
    (uint32)14,
    /* Crypto key element maximum size */
    (uint32)4
  },
  /* Element 5 */
  {
    /* Crypto key element ID */
    (uint32)15,
    /* Crypto key element maximum size */
    (uint32)1
  },
  /* Element 6 */
  {
    /* Crypto key element ID */
    (uint32)100,
    /* Crypto key element maximum size */
    (uint32)1
  },
  /* Element 7 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)32
  },
  /* Element 8 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)16
  },
  /* Element 9 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)32
  },
  /* Element 10 */
  {
    /* Crypto key element ID */
    (uint32)99,
    /* Crypto key element maximum size */
    (uint32)32
  },
  /* Element 11 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)16
  },
  /* Element 12 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)16
  },
  /* Element 13 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)16
  },
  /* Element 14 */
  {
    /* Crypto key element ID */
    (uint32)13,
    /* Crypto key element maximum size */
    (uint32)48
  },
  /* Element 15 */
  {
    /* Crypto key element ID */
    (uint32)14,
    /* Crypto key element maximum size */
    (uint32)4
  },
  /* Element 16 */
  {
    /* Crypto key element ID */
    (uint32)15,
    /* Crypto key element maximum size */
    (uint32)1
  },
  /* Element 17 */
  {
    /* Crypto key element ID */
    (uint32)100,
    /* Crypto key element maximum size */
    (uint32)1
  },
  /* Element 18 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)16
  },
  /* Element 19 */
  {
    /* Crypto key element ID */
    (uint32)13,
    /* Crypto key element maximum size */
    (uint32)48
  },
  /* Element 20 */
  {
    /* Crypto key element ID */
    (uint32)14,
    /* Crypto key element maximum size */
    (uint32)4
  },
  /* Element 21 */
  {
    /* Crypto key element ID */
    (uint32)15,
    /* Crypto key element maximum size */
    (uint32)1
  },
  /* Element 22 */
  {
    /* Crypto key element ID */
    (uint32)100,
    /* Crypto key element maximum size */
    (uint32)1
  },
  /* Element 23 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)16
  },
  /* Element 24 */
  {
    /* Crypto key element ID */
    (uint32)13,
    /* Crypto key element maximum size */
    (uint32)48
  },
  /* Element 25 */
  {
    /* Crypto key element ID */
    (uint32)14,
    /* Crypto key element maximum size */
    (uint32)4
  },
  /* Element 26 */
  {
    /* Crypto key element ID */
    (uint32)15,
    /* Crypto key element maximum size */
    (uint32)1
  },
  /* Element 27 */
  {
    /* Crypto key element ID */
    (uint32)100,
    /* Crypto key element maximum size */
    (uint32)1
  },
  /* Element 28 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)16
  },
  /* Element 29 */
  {
    /* Crypto key element ID */
    (uint32)13,
    /* Crypto key element maximum size */
    (uint32)48
  },
  /* Element 30 */
  {
    /* Crypto key element ID */
    (uint32)14,
    /* Crypto key element maximum size */
    (uint32)4
  },
  /* Element 31 */
  {
    /* Crypto key element ID */
    (uint32)15,
    /* Crypto key element maximum size */
    (uint32)1
  },
  /* Element 32 */
  {
    /* Crypto key element ID */
    (uint32)100,
    /* Crypto key element maximum size */
    (uint32)1
  },
  /* Element 33 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)16
  },
  /* Element 34 */
  {
    /* Crypto key element ID */
    (uint32)13,
    /* Crypto key element maximum size */
    (uint32)48
  },
  /* Element 35 */
  {
    /* Crypto key element ID */
    (uint32)14,
    /* Crypto key element maximum size */
    (uint32)4
  },
  /* Element 36 */
  {
    /* Crypto key element ID */
    (uint32)15,
    /* Crypto key element maximum size */
    (uint32)1
  },
  /* Element 37 */
  {
    /* Crypto key element ID */
    (uint32)100,
    /* Crypto key element maximum size */
    (uint32)1
  },
  /* Element 38 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)16
  },
  /* Element 39 */
  {
    /* Crypto key element ID */
    (uint32)13,
    /* Crypto key element maximum size */
    (uint32)48
  },
  /* Element 40 */
  {
    /* Crypto key element ID */
    (uint32)14,
    /* Crypto key element maximum size */
    (uint32)4
  },
  /* Element 41 */
  {
    /* Crypto key element ID */
    (uint32)15,
    /* Crypto key element maximum size */
    (uint32)1
  },
  /* Element 42 */
  {
    /* Crypto key element ID */
    (uint32)100,
    /* Crypto key element maximum size */
    (uint32)1
  },
  /* Element 43 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)16
  },
  /* Element 44 */
  {
    /* Crypto key element ID */
    (uint32)13,
    /* Crypto key element maximum size */
    (uint32)48
  },
  /* Element 45 */
  {
    /* Crypto key element ID */
    (uint32)14,
    /* Crypto key element maximum size */
    (uint32)4
  },
  /* Element 46 */
  {
    /* Crypto key element ID */
    (uint32)15,
    /* Crypto key element maximum size */
    (uint32)1
  },
  /* Element 47 */
  {
    /* Crypto key element ID */
    (uint32)100,
    /* Crypto key element maximum size */
    (uint32)1
  },
  /* Element 48 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)16
  },
  /* Element 49 */
  {
    /* Crypto key element ID */
    (uint32)13,
    /* Crypto key element maximum size */
    (uint32)48
  },
  /* Element 50 */
  {
    /* Crypto key element ID */
    (uint32)14,
    /* Crypto key element maximum size */
    (uint32)4
  },
  /* Element 51 */
  {
    /* Crypto key element ID */
    (uint32)15,
    /* Crypto key element maximum size */
    (uint32)1
  },
  /* Element 52 */
  {
    /* Crypto key element ID */
    (uint32)100,
    /* Crypto key element maximum size */
    (uint32)1
  },
  /* Element 53 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)16
  },
  /* Element 54 */
  {
    /* Crypto key element ID */
    (uint32)13,
    /* Crypto key element maximum size */
    (uint32)48
  },
  /* Element 55 */
  {
    /* Crypto key element ID */
    (uint32)14,
    /* Crypto key element maximum size */
    (uint32)4
  },
  /* Element 56 */
  {
    /* Crypto key element ID */
    (uint32)15,
    /* Crypto key element maximum size */
    (uint32)1
  },
  /* Element 57 */
  {
    /* Crypto key element ID */
    (uint32)100,
    /* Crypto key element maximum size */
    (uint32)1
  },
  /* Element 58 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)16
  },
  /* Element 59 */
  {
    /* Crypto key element ID */
    (uint32)13,
    /* Crypto key element maximum size */
    (uint32)48
  },
  /* Element 60 */
  {
    /* Crypto key element ID */
    (uint32)14,
    /* Crypto key element maximum size */
    (uint32)4
  },
  /* Element 61 */
  {
    /* Crypto key element ID */
    (uint32)15,
    /* Crypto key element maximum size */
    (uint32)1
  },
  /* Element 62 */
  {
    /* Crypto key element ID */
    (uint32)100,
    /* Crypto key element maximum size */
    (uint32)1
  },
  /* Element 63 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)32
  },
  /* Element 64 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)260
  },
  /* Element 65 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)16
  },
  /* Element 66 */
  {
    /* Crypto key element ID */
    (uint32)5,
    /* Crypto key element maximum size */
    (uint32)16
  },
  /* Element 67 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)16
  },
  /* Element 68 */
  {
    /* Crypto key element ID */
    (uint32)5,
    /* Crypto key element maximum size */
    (uint32)16
  },
  /* Element 69 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)16
  },
  /* Element 70 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)32
  },
  /* Element 71 */
  {
    /* Crypto key element ID */
    (uint32)1,
    /* Crypto key element maximum size */
    (uint32)32
  }
};
#define CRYIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CRYIF_START_SEC_CONST_PTR
#include "MemMap.h"

/* Array provides a list of Crypto_ProcessJob() function pointers */
CONST(CryIf_ProcessJobFncPtrType, CRYIF_CONFIG_DATA) \
  CryIf_ProcessJobPtr[CRYIF_TOTAL_CRYPTO_DRIVER] = \
{
  /* Function pointer of Crypto Driver 0 */
  Crypto_76_HaeModule_ProcessJob,
  /* Function pointer of Crypto Driver 1 */
  Crypto_ProcessJob
};
/* Array provides a list of Crypto_CancelJob() function pointers */
CONST(CryIf_CancelJobFncPtrType, CRYIF_CONFIG_DATA) \
  CryIf_CancelJobPtr[CRYIF_TOTAL_CRYPTO_DRIVER] = \
{
  /* Function pointer of Crypto Driver 0 */
  Crypto_76_HaeModule_CancelJob,
  /* Function pointer of Crypto Driver 1 */
  Crypto_CancelJob
};
/* Array provides a list of Crypto_KeyElementSet() function pointers */
CONST(CryIf_KeyElementSetFncPtrType, CRYIF_CONFIG_DATA) \
  CryIf_KeyElementSetPtr[CRYIF_TOTAL_CRYPTO_DRIVER] = \
{
  /* Function pointer of Crypto Driver 0 */
  Crypto_76_HaeModule_KeyElementSet,
  /* Function pointer of Crypto Driver 1 */
  Crypto_KeyElementSet
};
/* Array provides a list of Crypto_KeySetValid() function pointers */
CONST(CryIf_KeySetValidFncPtrType, CRYIF_CONFIG_DATA) \
  CryIf_KeySetValidPtr[CRYIF_TOTAL_CRYPTO_DRIVER] = \
{
  /* Function pointer of Crypto Driver 0 */
  Crypto_76_HaeModule_KeySetValid,
  /* Function pointer of Crypto Driver 1 */
  Crypto_KeySetValid
};
/* Array provides a list of Crypto_KeyElementGet() function pointers */
CONST(CryIf_KeyElementGetFncPtrType, CRYIF_CONFIG_DATA) \
  CryIf_KeyElementGetPtr[CRYIF_TOTAL_CRYPTO_DRIVER] = \
{
  /* Function pointer of Crypto Driver 0 */
  Crypto_76_HaeModule_KeyElementGet,
  /* Function pointer of Crypto Driver 1 */
  Crypto_KeyElementGet
};
/* Array provides a list of Crypto_KeyElementCopy() function pointers */
CONST(CryIf_KeyElementCopyFncPtrType, CRYIF_CONFIG_DATA) \
  CryIf_KeyElementCopyPtr[CRYIF_TOTAL_CRYPTO_DRIVER] = \
{
  /* Function pointer of Crypto Driver 0 */
  Crypto_76_HaeModule_KeyElementCopy,
  /* Function pointer of Crypto Driver 1 */
  Crypto_KeyElementCopy
};
/* Array provides a list of Crypto_KeyElementCopyPartial() function pointers */
CONST(CryIf_KeyElementCopyPartialFncPtrType, CRYIF_CONFIG_DATA) \
  CryIf_KeyElementCopyPartialPtr[CRYIF_TOTAL_CRYPTO_DRIVER] = \
{
  /* Function pointer of Crypto Driver 0 */
  Crypto_76_HaeModule_KeyElementPartialCopy,
  /* Function pointer of Crypto Driver 1 */
  Crypto_KeyElementCopyPartial
};
/* Array provides a list of Crypto_KeyCopy() function pointers */
CONST(CryIf_KeyCopyFncPtrType, CRYIF_CONFIG_DATA) \
  CryIf_KeyCopyPtr[CRYIF_TOTAL_CRYPTO_DRIVER] = \
{
  /* Function pointer of Crypto Driver 0 */
  Crypto_76_HaeModule_KeyCopy,
  /* Function pointer of Crypto Driver 1 */
  Crypto_KeyCopy
};
/* Array provides a list of Crypto_KeyElementIdsGet() function pointers */
CONST(CryIf_KeyElementIdsGetFncPtrType, CRYIF_CONFIG_DATA) \
  CryIf_KeyElementIdsGetPtr[CRYIF_TOTAL_CRYPTO_DRIVER] = \
{
  /* Function pointer of Crypto Driver 0 */
  Crypto_76_HaeModule_KeyElementIdsGet,
  /* Function pointer of Crypto Driver 1 */
  Crypto_KeyElementIdsGet
};
/* Array provides a list of Crypto_RandomSeed() function pointers */
CONST(CryIf_RandomSeedFncPtrType, CRYIF_CONFIG_DATA) \
  CryIf_RandomSeedPtr[CRYIF_TOTAL_CRYPTO_DRIVER] = \
{
  /* Function pointer of Crypto Driver 0 */
  Crypto_76_HaeModule_RandomSeed,
  /* Function pointer of Crypto Driver 1 */
  Crypto_RandomSeed
};
/* Array provides a list of Crypto_KeyGenerate() function pointers */
CONST(CryIf_KeyGenerateFncPtrType, CRYIF_CONFIG_DATA) \
  CryIf_KeyGeneratePtr[CRYIF_TOTAL_CRYPTO_DRIVER] = \
{
  /* Function pointer of Crypto Driver 0 */
  Crypto_76_HaeModule_KeyGenerate,
  /* Function pointer of Crypto Driver 1 */
  Crypto_KeyGenerate
};
/* Array provides a list of Crypto_KeyDerive() function pointers */
CONST(CryIf_KeyDeriveFncPtrType, CRYIF_CONFIG_DATA) \
  CryIf_KeyDerivePtr[CRYIF_TOTAL_CRYPTO_DRIVER] = \
{
  /* Function pointer of Crypto Driver 0 */
  Crypto_76_HaeModule_KeyDerive,
  /* Function pointer of Crypto Driver 1 */
  Crypto_KeyDerive
};
/* Array provides a list of Crypto_KeyExchangeCalcPubVal() function pointers */
CONST(CryIf_KeyExchangeCalcPubValFncPtrType, CRYIF_CONFIG_DATA) \
  CryIf_KeyExchangeCalcPubValPtr[CRYIF_TOTAL_CRYPTO_DRIVER] = \
{
  /* Function pointer of Crypto Driver 0 */
  Crypto_76_HaeModule_KeyExchangePubValCalc,
  /* Function pointer of Crypto Driver 1 */
  Crypto_KeyExchangeCalcPubVal
};
/* Array provides a list of Crypto_KeyExchangeCalcSecret() function pointers */
CONST(CryIf_KeyExchangeCalcSecretFncPtrType, CRYIF_CONFIG_DATA) \
  CryIf_KeyExchangeCalcSecretPtr[CRYIF_TOTAL_CRYPTO_DRIVER] = \
{
  /* Function pointer of Crypto Driver 0 */
  Crypto_76_HaeModule_KeyExchangeSecretCalc,
  /* Function pointer of Crypto Driver 1 */
  Crypto_KeyExchangeCalcSecret
};

#define CRYIF_STOP_SEC_CONST_PTR
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
