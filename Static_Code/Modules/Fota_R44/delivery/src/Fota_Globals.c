/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: FOTA_Globals.c                                                **
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
** Revision  Date          By           Description                           **
** 1.0.0.0   30-Mar-2022   jys          Initial version                       **
** 1.0.1.0   11-Dec-2023   VuPH6        #CP44-3526                            **
********************************************************************************
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Fota_Globals.h"

/*******************************************************************************
**                     Global Data                                            **
*******************************************************************************/
#define Fota_START_SEC_VAR_CLEARED_BOOLEAN
#include "Fota_MemMap.h"

#define Fota_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "Fota_MemMap.h"

#define Fota_START_SEC_VAR_CLEARED_8
#include "Fota_MemMap.h"
boolean Fota_SecureFlashDecryptOn;
uint8 Fota_MemoryInstance;
uint8 Fota_ProgrammingMemoryArea;
uint8 Fota_ProgrammingSWUnitId;
uint8 Fota_PreviousMetadataBlkId;
uint8 Fota_ProgrammingMetadataBlkId;
uint8 Fota_Gu8_MetadataPSKidx;
uint8 Fota_ProgrammingFwBlockId = 0xFF;
uint8 Fota_PreviousFwBlockId = 0;

uint8 Fota_BootMode = FOTA_MODE;

#if (FOTA_MODE == FOTA_UPDATER_MODE)
uint8 Fota_SwFblIndex = 0;
uint8 Fota_SwNewFblIndex = 0;
uint8 Fota_NumOfFblBlock = 0;
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

Fota_StateType Fota_State;
Fota_InitStatusType Fota_InitStatus;
uint32 Fota_StartupCommandAddress = FBL_STARTUP_COMMAND_ADDRESS;

uint8 Fota_PflsWriteAlignmentBuffer[4] = {0, 0, 0, 0};
uint32 Fota_PflsWriteAlignmentValue = 0;
uint32 Fota_PflsWriteAlignmentSize = 0;

uint8 Fota_PflsEraseAlignmentBuffer[4] = {0, 0, 0, 0};
uint32 Fota_PflsEraseAlignmentValue = 0;
uint32 Fota_PflsEraseAlignmentSize = 0;

#define Fota_STOP_SEC_VAR_CLEARED_32
#include "Fota_MemMap.h"

#define Fota_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fota_MemMap.h"
#if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
  (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
Fota_VerStateType Fota_VersionStatus;
#endif
#define Fota_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "Fota_MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
