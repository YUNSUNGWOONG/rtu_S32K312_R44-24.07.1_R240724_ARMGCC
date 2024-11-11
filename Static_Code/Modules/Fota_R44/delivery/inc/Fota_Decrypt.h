/*******************************************************************************
**                                                                            **
**  (C) 2021~2022 HYUNDAI AUTOEVER Co., Ltd.                                  **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fota_Diag.h                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   :                                                               **
**                                                                            **
**  PURPOSE   :                                                               **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
*******************************************************************************/

#ifndef FOTA_DECRYPT_H
#define FOTA_DECRYPT_H
#include "Std_Types.h"
#include "Fota_Globals.h"
#include "Csm.h"

#if (FOTA_STD_ON == FOTA_SF20_ENABLE)

#if (HWRESOURCE_VENDOR(HWRESOURCE_NXP))
  #define FOTA_PSK_INDEX_OFFSET												(0U)
#else
  #define FOTA_PSK_INDEX_OFFSET												(1U)
#endif

extern VAR(Fota_MetaPars_Type, AUTOMATIC) rst_MetaPars;

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_ProcessMetadata(
  const uint8* MetaDataBufferPtr,
  uint32 Csm_Hash_Job_Id,
  uint32 Csm_Decrypt_Key_Id,
  uint32 Csm_Meta_Header_Length,
  uint32 Csm_Meta_SK_Length
);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_DeriveKey
(
  uint8 *Lpu8_MetaDataBuffer,
  uint8 MDBlockId
);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_DecryptStart
(
  VAR(uint32, AUTOMATIC) DecryptJobId
);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_DecryptUpdate
(
  VAR(uint32, AUTOMATIC) DecryptJobId,
  P2CONST(uint8, AUTOMATIC, FOTA_CODE) inputPtr,
  P2VAR(uint8, AUTOMATIC, FOTA_CODE) outputPtr,
  P2VAR(uint32, AUTOMATIC, FOTA_CODE) dataLenPtr
);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_DecryptFinish
(
  VAR(uint8, AUTOMATIC) apiId,
  VAR(uint32, AUTOMATIC) decryptJobId,
  P2VAR(uint8, AUTOMATIC, FOTA_CODE) outputPtr,
  P2VAR(uint32, AUTOMATIC, FOTA_CODE) dataLenPtr
);

#endif /* (FOTA_STD_ON == FOTA_SF20_ENABLE) */

#endif /* FOTA_DECRYPT_H */
