/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CryIf_Globals.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CRYIF                                                 **
**                                                                            **
**  PURPOSE   : Declare all global data for module                            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date               By           Description                      **
********************************************************************************
** 1.0.0.0   15-Jan-2021        JH Lim       Initial version                  **
** 1.0.1.0   20-Mar-2021        TamTV6       Add trace SUD                    **
** 1.0.3.0   12-Aug-2022        DienTC1      #595                             **
*******************************************************************************/

#ifndef CRYIF_GLOBALS_H
#define CRYIF_GLOBALS_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* For required types */
#include "CryIf_IntTypes.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define CRYIF_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* Variable holds the state initialization of module */
extern VAR(boolean, CRYIF_VAR_CLEARED) CryIf_ModuleInitialized;

#define CRYIF_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define CRYIF_START_SEC_VAR_CLEARED_32
#include "MemMap.h"

/* Array holds key element Id of a Crypto interface key */
extern VAR(uint32, AUTOMATIC) CryIf_SourceElementArray[CRYIF_MAX_KEY_ELEMENT_NUMBER];
extern VAR(uint32, AUTOMATIC) CryIf_TargetElementArray[CRYIF_MAX_KEY_ELEMENT_NUMBER];

#define CRYIF_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#define CRYIF_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

/* Array is key pointer buffer */
extern VAR(uint8, AUTOMATIC) CryIf_KeySourceData[CRYIF_MAX_KEY_ELEMENT_SIZE];
/* Array is target key pointer buffer */
extern VAR(uint8, AUTOMATIC) CryIf_KeyTargetData[CRYIF_MAX_KEY_ELEMENT_SIZE];

#define CRYIF_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define CRYIF_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* @Trace: CryIf_SUD_GLOBALDATA_001 */
/* Array provides a list of channel information */
extern CONST(CryIf_ChannelType, CRYIF_CONFIG_DATA) CryIf_ChannelList[CRYIF_TOTAL_CHANNEL_ID_NUMBER];
/* @Trace: CryIf_SUD_GLOBALDATA_002 */
/* Array provides a list of crypto interface key information */
extern CONST(CryIf_KeyType, CRYIF_CONFIG_DATA) CryIf_CryIfKeyList[CRYIF_TOTAL_CRYIF_KEY_ID_NUMBER];
/* @Trace: CryIf_SUD_GLOBALDATA_003 */
/* Array provides a list of crypto driver key elements */
extern CONST(CryIf_KeyElementType, CRYIF_CONFIG_DATA) CryIf_KeyElementList[CRYIF_TOTAL_KEY_ELEMENT_NUMBER];

#define CRYIF_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define CRYIF_START_SEC_CONST_PTR
#include "MemMap.h"

/* @Trace: CryIf_SUD_GLOBALDATA_004 */
/* Array provides a list of Crypto_ProcessJob() function pointers */
extern CONST(CryIf_ProcessJobFncPtrType, CRYIF_CONFIG_DATA) CryIf_ProcessJobPtr[CRYIF_TOTAL_CRYPTO_DRIVER];

/* @Trace: CryIf_SUD_GLOBALDATA_005 */
/* Array provides a list of Crypto_CancelJob() function pointers */
extern CONST(CryIf_CancelJobFncPtrType, CRYIF_CONFIG_DATA) CryIf_CancelJobPtr[CRYIF_TOTAL_CRYPTO_DRIVER];

/* @Trace: CryIf_SUD_GLOBALDATA_006 */
/* Array provides a list of Crypto_KeyElementSet() function pointers */
extern CONST(CryIf_KeyElementSetFncPtrType, CRYIF_CONFIG_DATA) CryIf_KeyElementSetPtr[CRYIF_TOTAL_CRYPTO_DRIVER];

/* @Trace: CryIf_SUD_GLOBALDATA_007 */
/* Array provides a list of Crypto_KeySetValid() function pointers */
extern CONST(CryIf_KeySetValidFncPtrType, CRYIF_CONFIG_DATA) CryIf_KeySetValidPtr[CRYIF_TOTAL_CRYPTO_DRIVER];

/* @Trace: CryIf_SUD_GLOBALDATA_008 */
/* Array provides a list of Crypto_KeyElementGet() function pointers */
extern CONST(CryIf_KeyElementGetFncPtrType, CRYIF_CONFIG_DATA) CryIf_KeyElementGetPtr[CRYIF_TOTAL_CRYPTO_DRIVER];

/* @Trace: CryIf_SUD_GLOBALDATA_009 */
/* Array provides a list of Crypto_KeyElementCopy() function pointers */
extern CONST(CryIf_KeyElementCopyFncPtrType, CRYIF_CONFIG_DATA) CryIf_KeyElementCopyPtr[CRYIF_TOTAL_CRYPTO_DRIVER];

/* @Trace: CryIf_SUD_GLOBALDATA_010 */
/* Array provides a list of Crypto_KeyElementCopyPartial() function pointers */
extern CONST(CryIf_KeyElementCopyPartialFncPtrType, CRYIF_CONFIG_DATA) CryIf_KeyElementCopyPartialPtr[CRYIF_TOTAL_CRYPTO_DRIVER];

/* @Trace: CryIf_SUD_GLOBALDATA_011 */
/* Array provides a list of Crypto_KeyCopy() function pointers */
extern CONST(CryIf_KeyCopyFncPtrType, CRYIF_CONFIG_DATA) CryIf_KeyCopyPtr[CRYIF_TOTAL_CRYPTO_DRIVER];

/* @Trace: CryIf_SUD_GLOBALDATA_012 */
/* Array provides a list of Crypto_KeyElementIdsGet() function pointers */
extern CONST(CryIf_KeyElementIdsGetFncPtrType, CRYIF_CONFIG_DATA) CryIf_KeyElementIdsGetPtr[CRYIF_TOTAL_CRYPTO_DRIVER];

/* @Trace: CryIf_SUD_GLOBALDATA_013 */
/* Array provides a list of Crypto_RandomSeed() function pointers */
extern CONST(CryIf_RandomSeedFncPtrType, CRYIF_CONFIG_DATA) CryIf_RandomSeedPtr[CRYIF_TOTAL_CRYPTO_DRIVER];

/* @Trace: CryIf_SUD_GLOBALDATA_014 */
/* Array provides a list of Crypto_KeyGenerate() function pointers */
extern CONST(CryIf_KeyGenerateFncPtrType, CRYIF_CONFIG_DATA) CryIf_KeyGeneratePtr[CRYIF_TOTAL_CRYPTO_DRIVER];

/* @Trace: CryIf_SUD_GLOBALDATA_015 */
/* Array provides a list of Crypto_KeyDerive() function pointers */
extern CONST(CryIf_KeyDeriveFncPtrType, CRYIF_CONFIG_DATA) CryIf_KeyDerivePtr[CRYIF_TOTAL_CRYPTO_DRIVER];

/* @Trace: CryIf_SUD_GLOBALDATA_016 */
/* Array provides a list of Crypto_KeyExchangeCalcPubVal() function pointers */
extern CONST(CryIf_KeyExchangeCalcPubValFncPtrType, CRYIF_CONFIG_DATA) CryIf_KeyExchangeCalcPubValPtr[CRYIF_TOTAL_CRYPTO_DRIVER];

/* @Trace: CryIf_SUD_GLOBALDATA_017 */
/* Array provides a list of Crypto_KeyExchangeCalcSecret() function pointers */
extern CONST(CryIf_KeyExchangeCalcSecretFncPtrType, CRYIF_CONFIG_DATA) CryIf_KeyExchangeCalcSecretPtr[CRYIF_TOTAL_CRYPTO_DRIVER];

#define CRYIF_STOP_SEC_CONST_PTR
#include "MemMap.h"

#endif /* CRYIF_GLOBALS_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
