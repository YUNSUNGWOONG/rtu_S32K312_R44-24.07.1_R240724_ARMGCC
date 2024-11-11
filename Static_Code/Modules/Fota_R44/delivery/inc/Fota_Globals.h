/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: FOTA_Globals.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR FOTA                                                  **
**                                                                            **
**  PURPOSE   : Provides all the Global Variables of a firmware over the air  **
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
#ifndef FOTA_GLOBALS_H
#define FOTA_GLOBALS_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Fota_IntTypes.h"
/*******************************************************************************
**                     Global Data                                            **
*******************************************************************************/
#define Fota_START_SEC_VAR_CLEARED_BOOLEAN
#include "Fota_MemMap.h"

#define Fota_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Fota_MemMap.h"

#define Fota_START_SEC_VAR_CLEARED_8
#include "Fota_MemMap.h"
extern boolean Fota_SecureFlashDecryptOn;
extern uint8 Fota_MemoryInstance;
extern uint8 Fota_ProgrammingMemoryArea;
extern uint8 Fota_ProgrammingSWUnitId;
extern uint8 Fota_PreviousMetadataBlkId;
extern uint8 Fota_ProgrammingMetadataBlkId;
extern uint8 Fota_Gu8_MetadataPSKidx;
extern uint8 Fota_ProgrammingFwBlockId;
extern uint8 Fota_PreviousFwBlockId;
extern uint8 Fota_BootMode;

#if (FOTA_MODE == FOTA_UPDATER_MODE)
extern uint8 Fota_SwFblIndex;
extern uint8 Fota_SwNewFblIndex;
extern uint8 Fota_NumOfFblBlock;
#endif

#define Fota_STOP_SEC_VAR_CLEARED_8
#include "Fota_MemMap.h"

#define Fota_START_SEC_CONST_8
#include "Fota_MemMap.h"

#define Fota_STOP_SEC_CONST_8
#include "Fota_MemMap.h"

#define Fota_START_SEC_VAR_CLEARED_16
#include "Fota_MemMap.h"

#define Fota_STOP_SEC_VAR_CLEARED_16
#include "Fota_MemMap.h"

#define Fota_START_SEC_VAR_CLEARED_32
#include "Fota_MemMap.h"
extern Fota_StateType Fota_State;
extern Fota_InitStatusType Fota_InitStatus;
extern uint32 Fota_StartupCommandAddress;

extern uint8 Fota_PflsWriteAlignmentBuffer[4];
extern uint32 Fota_PflsWriteAlignmentValue;
extern uint32 Fota_PflsWriteAlignmentSize;

extern uint8 Fota_PflsEraseAlignmentBuffer[4];
extern uint32 Fota_PflsEraseAlignmentValue;
extern uint32 Fota_PflsEraseAlignmentSize;

#define Fota_STOP_SEC_VAR_CLEARED_32
#include "Fota_MemMap.h"

#define Fota_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fota_MemMap.h"
#if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
  (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
extern Fota_VerStateType Fota_VersionStatus;
#endif
#define Fota_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fota_MemMap.h"

#define Fota_START_SEC_CONST_UNSPECIFIED
#include "Fota_MemMap.h"

#define Fota_STOP_SEC_CONST_UNSPECIFIED
#include "Fota_MemMap.h"
#endif /* FOTA_GLOBALS_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
