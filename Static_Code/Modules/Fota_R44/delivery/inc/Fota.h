/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: FOTA.h                                                        **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR FOTA                                                  **
**                                                                            **
**  PURPOSE   : Provide all marcos for internal module                        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By                        Description              **
********************************************************************************
*******************************************************************************/
#ifndef FOTA_H
#define FOTA_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "Fota_IntTypes.h"
#include "Dcm_Types.h"
#include "Fota_Types.h"
#include "string.h"

#if (FOTA_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                  /* DET module header */
#endif
/*******************************************************************************
**                        Service IDs                                         **
*******************************************************************************/

#define FOTA_INSTANCE_ID                  ((uint8) 0)

#define FOTA_INIT_SID                         ((uint8)0x01)
#define FOTA_DEINIT_SID                       ((uint8)0x0B)

#define FOTA_ROUTINE_CONTROL_CPD_SID          ((uint8)0x05)
#define FOTA_REQUEST_DOWNLOAD_SID             ((uint8)0x0C)
#define FOTA_TRANSFER_DATA_SID                ((uint8)0x0D)
#define FOTA_REQUEST_TRANSFER_EXIT_SID        ((uint8)0x08)

#define FOTA_PROCESS_TRANSFER_DATA_WRITE_SID  ((uint8)0x06)
#define FOTA_MAIN_FUNCTION_SID                ((uint8)0x03)
#define FOTA_ERASE_MEMORY_SID                 ((uint8)0x0E)

#define FOTA_READ_ACTIVE_AREA_SID             ((uint8)0x0F)
#define FOTA_SWAP_ACTIVE_AREA_SID             ((uint8)0x10)
/* Service ID for Fota_GetVersionInfo */
#define FOTA_GET_VERSION_SID                  ((uint8)0x02)

/* 7DF suppression response */
#define FOTA_SYNC_PROCESS_RES_SUPPRESSION     (STD_ON)

#define FOTA_SIGNATURE_BLOCK_LENGTH           (0x108U)
/*******************************************************************************
**                      DET Error Codes                                       **
*******************************************************************************/

/*******************************************************************************
**                     Macros                                                 **
*******************************************************************************/
#define FOTA_MEMCPY(dst, src, size)              (memcpy((dst), (src), (size)))
#define FOTA_MEMSET(dst, src, size)              (memset((dst), (src), (size)))
#ifndef FOTA_UNUSED                              /* Check for unused parameter
                                                                      warnings*/
  #define FOTA_UNUSED(variable) (void) variable
#endif
/*******************************************************************************
**                     Global Data Types                                      **
*******************************************************************************/

/*******************************************************************************
**                     Global Data                                            **
*******************************************************************************/
extern Fota_RetransferType Fota_Retransfer;

/*******************************************************************************
**                     Function Prototypes                                    **
*******************************************************************************/
	
#define FOTA_START_SEC_CODE
#include "MemMap.h"

extern FUNC(void, FOTA_CODE) Fota_MainFunction(void);

#define FOTA_STOP_SEC_CODE
#include "MemMap.h"

#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"

extern FUNC(void, FOTA_CODE) Fota_Init(void);

extern FUNC(void, FOTA_CODE) Fota_DeInit(void);

extern FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessReadActiveArea
(
  VAR(uint16, AUTOMATIC) InEcuSwUnit,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpOut_MemoryArea,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
);

#if ((FOTA_IMPLEMENTATION_RULE == FOTA_OTA_ES98765_02) &&\
  (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
extern FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessActivateSingleMem
(
  VAR(uint8, AUTOMATIC) InMemArea,
  VAR(uint16, AUTOMATIC) InEcuSwUnit,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
);
#endif

#if (FOTA_MCU_MEMORY_ACCESS_TYPE!=FOTA_SINGLE_TYPE)
extern FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessActivateDualMem
(
  VAR(uint8, AUTOMATIC) InMemArea,
  VAR(uint16, AUTOMATIC) InEcuSwUnit,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
);
#endif

extern FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessEraseTargetArea
(
  VAR(uint8, AUTOMATIC) InMemArea,
  VAR(uint16, AUTOMATIC) InEcuSwUnit,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpOut_MemoryArea,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_ProcessRequestDownload(
  Dcm_OpStatusType OpStatus,
  uint8 DataFormatIdentifier,
  uint32 MemoryAddress,
  uint32 MemorySize,
  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) LpBlockLength,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
);

extern FUNC(Dcm_ReturnWriteMemoryType, FOTA_CODE) Fota_ProcessTransferDataWrite
(
  Dcm_OpStatusType OpStatus,
  uint8 MemoryIdentifier /* Not Supported Argument */,
  uint32 MemoryAddress,
  uint32 MemoryWriteLen,
  P2CONST(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) pWriteData
);

extern FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessRequestTransferExit
(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpMemoryData,
  uint32* LulParameterRecordSize,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, FOTA_PRIVATE_DATA)LpErrorCode
);

#if (FOTA_IMPLEMENTATION_RULE == FOTA_OTA_ES98765_01)
extern FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessVerifyGenOne
(
  VAR(uint8, AUTOMATIC) InMemArea,
  VAR(uint16, AUTOMATIC) InEcuSwUnit,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpOut_MemoryArea,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
);
#endif

#if (FOTA_IMPLEMENTATION_RULE == FOTA_OTA_ES98765_02)
extern FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessVerifyGenTwo
(
  VAR(uint8, AUTOMATIC) InMemArea,
  VAR(uint16, AUTOMATIC) InEcuSwUnit,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpOut_MemoryArea,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
);

extern FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessAreaDataSync
(
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
);
#endif

#if (FOTA_VERSION_INFO_API == STD_ON)
extern FUNC(void, FOTA_CODE) Fota_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC,
    FOTA_PRIVATE_DATA) versioninfo);
#endif

#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"

#endif /* FOTA_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
