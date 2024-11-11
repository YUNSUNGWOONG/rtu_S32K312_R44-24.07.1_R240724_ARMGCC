/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Mem_76_Pfls_Globals.h                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Memory Driver                                         **
**                                                                            **
**  PURPOSE   : Provides all the Global Variables of a Mem Driver module      **
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
#ifndef MEM_76_PFLS_GLOBALS_H
#define MEM_76_PFLS_GLOBALS_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Mem_76_Pfls_Cfg.h"
/*******************************************************************************
**                     Global Data                                            **
*******************************************************************************/
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
extern VAR(FunctionRamPtr, MEM_76_PFLS_VAR_INIT) Mem_76_Pfls_InternalReadRamFunction;
extern VAR(WriteFunctionRamPtr, MEM_76_PFLS_VAR_INIT) Mem_76_Pfls_InternalWriteRamFunction;
extern VAR(FunctionRamPtr, MEM_76_PFLS_VAR_INIT) Mem_76_Pfls_InternalEraseRamFunction;

#if (MEM_76_PFLS_WDG_CALLOUT_FUNCTION_SUPPORT == STD_ON)
extern VAR(Mem_WDTriggerFct, MEM_76_PFLS_VAR_INIT) Mem_76_Pfls_WDTriggerFct;
#endif /* MEM_76_PFLS_WDG_CALLOUT_FUNCTION_SUPPORT */

#endif /* FOTA_MCU_MEMORY_ACCESS_TYPE */

#define MEM_76_PFLS_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
extern VAR(uint8, MEM_76_PFLS_VAR) Mem_76_Pfls_InitDone;


#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
extern VAR(boolean, MEM_76_PFLS_VAR) Mem_76_Pfls_ToolBox_Active;
#endif

#define MEM_76_PFLS_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define MEM_76_PFLS_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* @Trace: Mem_76_Pfls_SUD_MACRO_008 */
#if (MEM_76_PFLS_NUMBER_OF_BURST_SETTINGS != MEM_76_PFLS_ZERO)
extern CONST(Mem_76_Pfls_BurstSettingsType, MEM_76_PFLS_CONST) Mem_76_Pfls_BurstSettings[\
    MEM_76_PFLS_NUMBER_OF_BURST_SETTINGS];
#endif /* MEM_76_PFLS_NUMBER_OF_BURST_SETTINGS != MEM_76_PFLS_ZERO */
/* @Trace: Mem_76_Pfls_SUD_MACRO_009 */
#if (MEM_76_PFLS_NUMBER_OF_SECTOR_SETTINGS != MEM_76_PFLS_ZERO)
extern CONST(Mem_76_Pfls_SectorBatchType, MEM_76_PFLS_CONST) Mem_76_Pfls_SectorBatches[\
    MEM_76_PFLS_NUMBER_OF_SECTOR_SETTINGS];
#endif /* MEM_76_PFLS_NUMBER_OF_SECTOR_SETTINGS != MEM_76_PFLS_ZERO */

#if (MEM_76_PFLS_NUMBER_OF_INSTANCES != MEM_76_PFLS_ZERO)
extern CONST(Mem_76_Pfls_InstanceType, MEM_76_PFLS_CONST) Mem_76_Pfls_InstancesConfiguration[\
    MEM_76_PFLS_NUMBER_OF_INSTANCES];
#endif /* MEM_76_PFLS_NUMBER_OF_INSTANCES != MEM_76_PFLS_ZERO */

#if (MEM_76_PFLS_PRE_CALLOUT_FUNCTION_SUPPORT == STD_ON)
extern CONST(Mem_76_Pfls_PreCalloutType, MEM_76_PFLS_CONST) Mem_76_Pfls_PreCallout[\
    MEM_76_PFLS_NUMBER_OF_INSTANCES];
#endif /* MEM_76_PFLS_PRE_CALLOUT_FUNCTION_SUPPORT == STD_ON */

#if (MEM_76_PFLS_POST_CALLOUT_FUNCTION_SUPPORT == STD_ON)
extern CONST(Mem_76_Pfls_PostCalloutType, MEM_76_PFLS_CONST) Mem_76_Pfls_PostCallout[\
    MEM_76_PFLS_NUMBER_OF_INSTANCES];
#endif /* MEM_76_PFLS_POST_CALLOUT_FUNCTION_SUPPORT == STD_ON */

#if (MEM_76_PFLS_NUMBER_OF_SECTOR_SETTINGS != MEM_76_PFLS_ZERO)
extern CONST(uint32, MEM_76_PFLS_CONST) Mem_76_Pfls_SectorLookupTable[\
    MEM_76_PFLS_NUMBER_OF_SECTOR_SETTINGS];
#endif

#define MEM_76_PFLS_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define MEM_76_PFLS_START_FUNCTION_POINTER_TABLE
#include "MemMap.h"
extern CONST(Mem_76_Pfls_FuncPtrTableType, MEM_76_PFLS_CONST) Mem_76_Pfls_FuncPtrTable;
#define MEM_76_PFLS_STOP_FUNCTION_POINTER_TABLE
#include "MemMap.h"



#define MEM_76_PFLS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if (MEM_76_PFLS_NUMBER_OF_INSTANCES != MEM_76_PFLS_ZERO)
extern VAR(Mem_76_Pfls_InstanceInfoType, AUTOMATIC) Mem_76_Pfls_InstanceInfo[\
  MEM_76_PFLS_NUMBER_OF_INSTANCES];
#endif /* MEM_76_PFLS_NUMBER_OF_INSTANCES != MEM_76_PFLS_ZERO */

#define MEM_76_PFLS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"


#endif /* MEM_76_PFLS_GLOBALS_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
