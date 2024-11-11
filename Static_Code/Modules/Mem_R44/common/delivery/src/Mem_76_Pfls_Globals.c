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
**  SRC-MODULE: Mem_76_Pfls_Globals.c                                         **
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

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Std_Types.h"
#include "Mem_76_Pfls_Cfg.h"
#include "Mem_76_Pfls_Types.h"
#include "Mem_76_Pfls_Globals.h"
#include "Mem_76_Pfls.h"
/*******************************************************************************
**                     Global Data                                            **
*******************************************************************************/
#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
VAR(FunctionRamPtr, MEM_76_PFLS_VAR_INIT) Mem_76_Pfls_InternalReadRamFunction = NULL_PTR;
VAR(WriteFunctionRamPtr, MEM_76_PFLS_VAR_INIT) Mem_76_Pfls_InternalWriteRamFunction = NULL_PTR;
VAR(FunctionRamPtr, MEM_76_PFLS_VAR_INIT) Mem_76_Pfls_InternalEraseRamFunction = NULL_PTR;

#if (MEM_76_PFLS_WDG_CALLOUT_FUNCTION_SUPPORT == STD_ON)
VAR(Mem_WDTriggerFct, MEM_76_PFLS_VAR_INIT) Mem_76_Pfls_WDTriggerFct = NULL_PTR;
#endif /* MEM_76_PFLS_WDG_CALLOUT_FUNCTION_SUPPORT */

#endif

#define MEM_76_PFLS_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
VAR(uint8, MEM_76_PFLS_VAR) Mem_76_Pfls_InitDone;

#if (MEM_76_PFLS_RAMCODE_USED == STD_ON)
VAR(boolean, MEM_76_PFLS_VAR) Mem_76_Pfls_ToolBox_Active;
#endif /* FOTA_MODE */

#define MEM_76_PFLS_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define MEM_76_PFLS_START_FUNCTION_POINTER_TABLE
#include "MemMap.h"
CONST(Mem_76_Pfls_FuncPtrTableType, MEM_76_PFLS_CONST) Mem_76_Pfls_FuncPtrTable = \
{
  &Mem_76_Pfls_Init,
  &Mem_76_Pfls_DeInit,
  &Mem_76_Pfls_GetJobResult,
  &Mem_76_Pfls_Read,
  &Mem_76_Pfls_Write,
  &Mem_76_Pfls_Erase,
  &Mem_76_Pfls_PropagateError,
  &Mem_76_Pfls_BlankCheck,
  &Mem_76_Pfls_Suspend,
  &Mem_76_Pfls_Resume,
  &Mem_76_Pfls_HwSpecificService
};
#define MEM_76_PFLS_STOP_FUNCTION_POINTER_TABLE
#include "MemMap.h"


#define MEM_76_PFLS_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if (MEM_76_PFLS_NUMBER_OF_INSTANCES != MEM_76_PFLS_ZERO)
VAR(Mem_76_Pfls_InstanceInfoType, AUTOMATIC) Mem_76_Pfls_InstanceInfo[\
  MEM_76_PFLS_NUMBER_OF_INSTANCES];
#endif /* MEM_76_PFLS_NUMBER_OF_INSTANCES != MEM_76_PFLS_ZERO */

#define MEM_76_PFLS_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
