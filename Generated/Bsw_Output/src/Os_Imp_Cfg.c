/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  FILE-NAME: Os_Imp_Cfg.c                                                   **
**                                                                            **
**  MODULE-NAME: AUTOSAR OS Improvement Code                                  **
**                                                                            **
**  NOTE: This file is auto generated, do not edit this file manually.        **
**                                                                            **
********************************************************************************

********************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  Tool Version: 1.1.0                                                       **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            **
********************************************************************************
**                      File Generation Information                           **
*******************************************************************************/

/*
 * INPUT FILE:    Configuration\Ecu\Ecud_OsImp.arxml
 * GENERATED ON: The time-stamp is removed
 */

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<MISRA-C:11.3:Not a defect:Justify with annotations> This is usage constraints of symbol defined in .ld file. */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_Imp_Cfg.h"

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#define OS_START_SEC_CONST_32
#include "MemMap.h"
CONST(uint32, OS_CONST) Os_Ram_Sector_Por_Count =
                                                (uint32)OS_RAM_SECTOR_POR_COUNT;
CONST(uint32, OS_CONST) Os_Ram_Sector_Wakeup_Count =
                                             (uint32)OS_RAM_SECTOR_WAKEUP_COUNT;
CONST(uint32, OS_CONST) Os_Ram_Sector_Stack_Count =
                                              (uint32)OS_RAM_SECTOR_STACK_COUNT;
#define OS_STOP_SEC_CONST_32
#include "MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Ram Sectors to be initialized when power on reset */
CONST(Os_RamSectorType, OS_CONST) Os_GaaRamSectorInitPowerOnReset[] =
{
  /* Ram Sector: 0 - MEM_ITCM */
  {
    /* ulDefaultValue */
    0x00000000u,

    /* ulBaseAddress */
    0x00000000u,

    /* ulSize */
    32768
  },

  /* Ram Sector: 1 - MEM_DTCM */
  {
    /* ulDefaultValue */
    0x00000000u,

    /* ulBaseAddress */
    0x20000000u,

    /* ulSize */
    65536
  },

  /* Ram Sector: 2 - RAM_RETENTION */
  {
    /* ulDefaultValue */
    0x00000000u,

    /* ulBaseAddress */
    0x20400200u,

    /* ulSize */
    15872
  },

  /* Ram Sector: 3 - RAM_SYSTEM */
  {
    /* ulDefaultValue */
    0x00000000u,

    /* ulBaseAddress */
    0x20404000u,

    /* ulSize */
    81920
  }
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define OS_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Ram Sectors to be initialized when wake-up from Low Power Mode */
CONST(Os_RamSectorType, OS_CONST) Os_GaaRamSectorInitWakeUp[] =
{
  /* Ram Sector: 0 - MEM_ITCM_Wakeup */
  {
    /* ulDefaultValue */
    0x00000000u,

    /* ulBaseAddress */
    0x00000000u,

    /* ulSize */
    32768
  },

  /* Ram Sector: 1 - MEM_DTCM_Wakeup */
  {
    /* ulDefaultValue */
    0x00000000u,

    /* ulBaseAddress */
    0x20000000u,

    /* ulSize */
    65536
  },

  /* Ram Sector: 2 - RAM_SYSTEM_Wakeup */
  {
    /* ulDefaultValue */
    0x00000000u,

    /* ulBaseAddress */
    0x20404000u,

    /* ulSize */
    81920
  }
};

#define OS_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* CONST(Os_RamSectorType, OS_CONST) Os_GaaRamSectorInitStack[]; */

/*******************************************************************************
**                      Function definition                                   **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace:end<MISRA-C:11.3:Not a defect:Justify with annotations> This is usage constraints of symbol defined in .ld file. */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
