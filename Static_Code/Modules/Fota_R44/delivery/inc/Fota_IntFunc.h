/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: FOTA_IntFunc.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR FOTA                                                  **
**                                                                            **
**  PURPOSE   :                          **
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
#ifndef FOTA_INTFUNC_H
#define FOTA_INTFUNC_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Fota_IntTypes.h"
/*******************************************************************************
**                     Macros                                                 **
*******************************************************************************/

/*******************************************************************************
**                     Global Data Types                                      **
*******************************************************************************/

/*******************************************************************************
**                     Global Data                                            **
*******************************************************************************/

/*******************************************************************************
**                     Function Prototypes                                    **
*******************************************************************************/

extern FUNC(boolean, FOTA_CODE) Fota_CheckMetadataArea(
  VAR(uint32, FOTA_VAR) metadataAddress);

extern FUNC(boolean, FOTA_CODE) Fota_CheckMetadataSize(
  VAR(uint32, FOTA_VAR) InMetadataSize);

extern FUNC(boolean, FOTA_CODE) Fota_CheckFwBlockArea(
  VAR(uint32, FOTA_VAR) firmwareBlkAddress);

extern FUNC(boolean, FOTA_CODE) Fota_CheckAddressIsSignatureArea(
  VAR(uint32, FOTA_VAR) signatureAddress);

extern FUNC(Fota_JobResultType, FOTA_CODE) Fota_GetVerifyJobResult(void);

extern FUNC(void, FOTA_CODE) Fota_SetVerifyJobResult(
  VAR(Fota_JobResultType, FOTA_VAR) Result);

extern FUNC(boolean, FOTA_CODE) Fota_CheckMetaWriteRequest(void);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_BlockProtectedCheck(
  VAR(uint32, FOTA_VAR) startProtectedAddr,
  VAR(uint32, FOTA_VAR) startProtectedSize);

extern FUNC(Std_ReturnType,FOTA_CODE) Fota_ValidateMemoryArea(
  VAR(uint8,AUTOMATIC) memoryArea
);

extern FUNC(Std_ReturnType,FOTA_CODE) Fota_GetMemInstanceBySwUnit(
  VAR(uint8,AUTOMATIC) swUnitId,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) PflsInstanceId);

extern FUNC(Std_ReturnType,FOTA_CODE) Fota_GetSoftwareModuleBlkBySwType(
  VAR(Fota_SoftwareType, AUTOMATIC) In_SwType,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) programmingSwUnitId);

extern FUNC(Std_ReturnType,FOTA_CODE) Fota_GetSoftwareModuleBlkByRunArea(
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) programmingSwUnitId);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_GetSwUnitIdByLabel(
  VAR(uint16,AUTOMATIC) swUnitLabel,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) programmingSwUnitId);

extern FUNC(Std_ReturnType,FOTA_CODE) Fota_ValidateAddressLengthAlignment(
  VAR(uint32, AUTOMATIC) startAddress,
  VAR(uint32, AUTOMATIC) eraseLen,
  VAR(Fota_AccessMemoryType, AUTOMATIC) accessType);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_MetaDataProcessing(
                                                 Fota_FlashWriteType *fotaWrite,
                                                 Fota_StateType fotaState);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_UserCallOutProcessing(
                                        Fota_FwBlockProcessingType *fwBlockPtr,
                                        Fota_StateType fotaState);

extern FUNC(void, FOTA_CODE) Fota_RequestSTDOrALTAccess(void);

extern FUNC(uint8, FOTA_CODE) Fota_FindSoftwareArea(
  VAR(Fota_SoftwareType, FOTA_VAR) softwareType);

#if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
  (FOTA_IMPLEMENTATION_RULE == FOTA_OTA_ES98765_02))
extern FUNC(Std_ReturnType, FOTA_CODE) Fota_CheckAllSwUnitVersionCheck(void);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_CheckNextSwUnitVersionCheck(
  uint8 *swUnitIndex);
#endif

#if (FOTA_MODE == FOTA_UPDATER_MODE)

extern FUNC(uint8, FOTA_CODE) Fota_FindNumberOfFblBlock(
  VAR(uint8, FOTA_VAR) swUnitIndex);

extern FUNC(void, FOTA_CODE) Fota_FindBlockInfo(
  VAR(uint8, FOTA_VAR) swUnitIndex,
  VAR(uint8, FOTA_VAR) blockIndex,
  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) startAddress,
  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) endAddress);

extern FUNC(Std_ReturnType, FOTA_CODE) Fota_CalibrationStartAddressLength(
  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) dataLength,
  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) startPflsAddress,
  VAR(uint32, FOTA_VAR) endPflsAddress);
#endif

#endif /* FOTA_INTFUNC_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
