/*******************************************************************************
**                                                                            **
**  (C) 2021~2022 HYUNDAI AUTOEVER Co., Ltd.                                  **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fota_Diag.c                                                    **
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
** Revision    Date          By           Description                         **
********************************************************************************
** 1.0.0       30-Mar-2022   jys        Initial version                       **
** 1.1.0.0_HF1 26-Apr-2024   KJShim     #CP44-8300                            **
*******************************************************************************/

#ifndef FOTA_VERIFY_H
#define FOTA_VERIFY_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "Fota_IntTypes.h"
/*******************************************************************************
**                      Types                                                 **
*******************************************************************************/

/*******************************************************************************
**                      Macros                                                **
*******************************************************************************/
#if (CPU_BYTE_ORDER == LOW_BYTE_FIRST)
#define CRC_INIT_HIBYTE_OFF  8
#define CRC_INIT_LOBYTE_OFF  9
#else
#define CRC_INIT_HIBYTE_OFF  9
#define CRC_INIT_LOBYTE_OFF  8
#endif

#define CODE_FLASH_VERIFY_SIZE_OF_ONECYCLE                                  4096

#define SEC_SF_SIGNATURE_DELIMITER_LENGTH                                   (4U)
#define SEC_SF_SIGNATURE_SIZE_LENGTH                                        (4U)
#define SEC_SF_SIGNATURE_SIZE                                             (256U)

#define FBL_SIGN_ASIMS_DELIMITER_NUM                                         (8)
#define FBL_SIGN_FST_DELIMITER_NUM                                          (10)

#define FOTA_VERIFY_SIGNATURE_LEN                                          (256)
/*******************************************************************************
**                     Global Data Types                                      **
*******************************************************************************/

/*******************************************************************************
**                      Global Variable                                       **
*******************************************************************************/
extern FotaVerify_StatType FotaVerifyState;
/*******************************************************************************
**                        Global Function Declaration                         **
*******************************************************************************/
FUNC(Std_ReturnType, FOTA_CODE) Fota_VerifyRequest(uint32 In_MemoryArea);
FUNC(Fota_JobResultType, FOTA_CODE) Fota_VerifyJobResult(void);
FUNC(void, FOTA_CODE) Fota_JobVerifyProcess(void);

FUNC(uint16, FOTA_CODE) Fota_Crc16CoverArea(
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) data,
  VAR(uint32, AUTOMATIC) length,
  VAR(uint16, AUTOMATIC) crc
);

#endif /* End FOTA_VERIFY_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
