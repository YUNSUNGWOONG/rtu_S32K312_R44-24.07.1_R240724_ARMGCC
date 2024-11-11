/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: CryIf_IntTypes.h                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CRYIF                                                 **
**                                                                            **
**  PURPOSE   : Define all internal types and macros for module               **
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

#ifndef CRYIF_INTTYPES_H
#define CRYIF_INTTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* For AUTOSAR standard types and Crypto general types */
#include "CryIf_Cfg.h"

/*******************************************************************************
**                     Internal macros                                        **
*******************************************************************************/
/* @Trace: CryIf_SUD_MACRO_006 */
/* Macro defines instance id of module */
#define CRYIF_INSTANCE_ID                       ((uint8)0x00U)
/* This macro defines zero value */
#define CRYIF_ZERO_VALUE                        0x00U
/* This macro defines one value */
#define CRYIF_ONE_VALUE                         0x01U
/* This macro defines two value */
#define CRYIF_TWO_VALUE                         0x02U
/* This macro defines unused parameters */
#define CRYIF_UNUSED(param)                     ((void)(param))

/*******************************************************************************
**                     Internal Data Types                                    **
*******************************************************************************/

/* @Trace: CryIf_SUD_DATATYPE_021 */
/* Type defines Crypto Driver key element */
typedef struct
{
  /* Key element ID */
  uint32 ElementId;
  /* Key element maximum size */
  uint32 MaxSize;
}
CryIf_KeyElementType;

/* @Trace: CryIf_SUD_DATATYPE_020 */
/* Type defines information about channel of Crypto Interface */
typedef struct
{
  /* Crypto interface channel Id */
  uint32 ChannelId;
  /* Crypto driver object Id */
  uint32 ObjectId;
  /* Index of array crypto driver function pointer */
  uint8 IndexFunc;
}
CryIf_ChannelType;

/* @Trace: CryIf_SUD_DATATYPE_022 */
/* Type defines information about channel of Crypto Interface */
typedef struct
{
  /* Crypto interface key Id */
  uint32 CryIfKeyId;
  /* Crypto driver key Id */
  uint32 CryptoKeyId;
  /* Index of array crypto driver function pointer */
  uint8 IndexFunc;
  /* Index of array Crypto driver key element holds start value of a key */
  uint32 IndexStart;
}
CryIf_KeyType;

/* @Trace: CryIf_SUD_DATATYPE_018 */
/* Type defines Crypto_ProcessJob() function pointer */
typedef P2FUNC(Std_ReturnType, CRYIF_APPL_CODE, CryIf_ProcessJobFncPtrType)(\
  uint32 objectId, Crypto_JobType* job);

/* @Trace: CryIf_SUD_DATATYPE_006 */
/* Type defines Crypto_CancelJob() function pointer */
typedef P2FUNC(Std_ReturnType, CRYIF_APPL_CODE, CryIf_CancelJobFncPtrType)(\
  uint32 objectId, Crypto_JobType* job);

/* @Trace: CryIf_SUD_DATATYPE_013 */
/* Type defines Crypto_KeyElementSet() function pointer */
typedef P2FUNC(Std_ReturnType, CRYIF_APPL_CODE, CryIf_KeyElementSetFncPtrType)(\
  uint32 cryptoKeyId, uint32 keyElementId, \
  const uint8* keyPtr, uint32 keyLength);

/* @Trace: CryIf_SUD_DATATYPE_017 */
/* Type defines Crypto_KeySetValid() function pointer */
typedef P2FUNC(Std_ReturnType, CRYIF_APPL_CODE, CryIf_KeySetValidFncPtrType)(\
  uint32 cryptoKeyId);

/* @Trace: CryIf_SUD_DATATYPE_011 */
/* Type defines Crypto_KeyElementGet() function pointer */
typedef P2FUNC(Std_ReturnType, CRYIF_APPL_CODE, CryIf_KeyElementGetFncPtrType)(\
  uint32 cryptoKeyId, uint32 keyElementId, \
  uint8* resultPtr, uint32* resultLengthPtr);

/* @Trace: CryIf_SUD_DATATYPE_009 */
/* Type defines Crypto_KeyElementCopy() function pointer */
typedef P2FUNC(Std_ReturnType, CRYIF_APPL_CODE,\
  CryIf_KeyElementCopyFncPtrType)(uint32 cryptoKeyId, uint32 keyElementId, \
  uint32 targetCryptoKeyId, uint32 targetKeyElementId);

/* @Trace: CryIf_SUD_DATATYPE_010 */
/* Type defines Crypto_KeyElementCopyPartial() function pointer */
typedef P2FUNC(Std_ReturnType, CRYIF_APPL_CODE,\
  CryIf_KeyElementCopyPartialFncPtrType)(uint32 cryptoKeyId, \
  uint32 keyElementId, uint32 keyElementSourceOffset, \
  uint32 keyElementTargetOffset, uint32 keyElementCopyLength, \
  uint32 targetCryptoKeyId, uint32 targetKeyElementId);

/* @Trace: CryIf_SUD_DATATYPE_007 */
/* Type defines Crypto_KeyCopy() function pointer */
typedef P2FUNC(Std_ReturnType, CRYIF_APPL_CODE, CryIf_KeyCopyFncPtrType)(\
  uint32 cryptoKeyId, uint32 targetCryptoKeyId);

/* @Trace: CryIf_SUD_DATATYPE_012 */
/* Type defines Crypto_KeyElementIdsGet() function pointer */
typedef P2FUNC(Std_ReturnType, CRYIF_APPL_CODE, \
  CryIf_KeyElementIdsGetFncPtrType)(\
  uint32 cryptoKeyId, \
  uint32* keyElementIdsPtr, \
  uint32* keyElementIdsLengthPtr);

/* @Trace: CryIf_SUD_DATATYPE_019 */
/* Type defines Crypto_RandomSeed() function pointer */
typedef P2FUNC(Std_ReturnType, CRYIF_APPL_CODE, CryIf_RandomSeedFncPtrType)(\
  uint32 cryptoKeyId, const uint8* seedPtr, uint32 seedLength);

/* @Trace: CryIf_SUD_DATATYPE_016 */
/* Type defines Crypto_KeyGenerate() function pointer */
typedef P2FUNC(Std_ReturnType, CRYIF_APPL_CODE, CryIf_KeyGenerateFncPtrType)(\
  uint32 cryptoKeyId);

/* @Trace: CryIf_SUD_DATATYPE_008 */
/* Type defines Crypto_KeyDerive() function pointer */
typedef P2FUNC(Std_ReturnType, CRYIF_APPL_CODE, CryIf_KeyDeriveFncPtrType)(\
  uint32 cryptoKeyId, uint32 targetCryptoKeyId);

/* @Trace: CryIf_SUD_DATATYPE_014 */
/* Type defines Crypto_KeyExchangeCalcPubVal() function pointer */
typedef P2FUNC(Std_ReturnType, CRYIF_APPL_CODE,\
  CryIf_KeyExchangeCalcPubValFncPtrType)(uint32 cryptoKeyId, \
  uint8* publicValuePtr, uint32* publicValueLengthPtr);

/* @Trace: CryIf_SUD_DATATYPE_015 */
/* Type defines Crypto_KeyExchangeCalcSecret() function pointer */
typedef P2FUNC(Std_ReturnType, CRYIF_APPL_CODE,\
  CryIf_KeyExchangeCalcSecretFncPtrType)(uint32 cryptoKeyId, \
  const uint8* partnerPublicValuePtr, uint32 partnerPublicValueLength);

#endif /* CRYIF_INTTYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
