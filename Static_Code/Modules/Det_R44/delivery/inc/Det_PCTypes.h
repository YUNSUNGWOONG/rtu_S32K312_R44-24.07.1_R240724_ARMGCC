/*******************************************************************************
**                                                                            **
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  SRC-MODULE: Det_PCTypes.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Default Error Tracer Module                           **
**                                                                            **
**  PURPOSE   : Provision of callback functions and their functionality.      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 0.0.1     30-Sep-2019   DanhLT2      Initial Version                       **
*******************************************************************************/
#ifndef DET_PCTYPES_H
#define DET_PCTYPES_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Det_Cfg.h"                /* Det Cfg header file */

/*******************************************************************************
**                      Type definition                                       **
*******************************************************************************/
/* DET macros */
/* @Trace: Det_SUD_MACRO_004*/
#define DET_ZERO                             ((uint8)0x00)
#define DET_ONE                              ((uint8)0x01)
#define DET_TWO                              ((uint8)0x02)
#define DET_TRUE                             ((boolean)0x01)
#define DET_FALSE                            ((boolean)0x00)
#define DET_UNINITIALIZED                    ((boolean)0x00)
#define DET_INITIALIZED                      ((boolean)0x01)

#define DET_INSTANCE_ID                      ((uint8)0)

/* Enum of Error Hook Status */
/* @Trace: Det_SUD_DATATYPE_004 Det_ErrorHookStatusType*/
typedef enum
{
  DET_ERROR_HOOK_IDLE = 0,
  DET_ERROR_HOOK_BUSY
}Det_ErrorHookStatusType;

/* Det Error Hook Function Pointer */
/* @Trace: Det_SUD_DATATYPE_003 Det_FuncPtrType*/
typedef P2FUNC(Std_ReturnType, DET_CODE, Det_FuncPtrType)
  (uint16 LusModuleId, uint8 LucInstanceId, uint8 LucApiId, uint8 LucErrorId);

/* Structure to store the parameters of DET Report Error function */
/* @Trace: Det_SUD_DATATYPE_006 STag_Det_ErrorType*/
/* polyspace +1 MISRA-C3:2.4 [Justified:Low] "Not a Defect" */
typedef struct STag_Det_ErrorType
{
  /* To store the ModuleId of the reporting module */
  uint16 usModuleId;
  /* To store the index based InstanceId of the reporting module */
  uint8 ucInstanceId;
  /* To store the ApiId of the reporting function */
  uint8 ucApiId;
  /* To store the ErrorId of the reporting error */
  uint8 ucErrorId;
}Det_ErrorType;

/* Structure to store the status of DET */
/* @Trace: Det_SUD_DATATYPE_007 STag_Det_ErrorStatusType*/
/* polyspace +1 MISRA-C3:2.4 [Justified:Low] "Not a Defect" */
typedef struct STag_Det_ErrorStatusType
{
  #if (DET_RAM_BUFFER == STD_ON)
  /* Global variable used to store index of array of structure */
  VAR(uint8, DET_VAR_NOINIT) ErrorCount;
  #endif /* DET_RAM_BUFFER == STD_ON */

  #if((DET_ERROR_HOOK == STD_ON)||\
             (DET_FORWARD_TO_DLT == STD_ON))
  /* Check to skip Invoke configured Error Hook Functions*/
  VAR(Det_ErrorHookStatusType, DET_VAR_NOINIT) ErrorHook;
  #endif /* DET_ERROR_HOOK == STD_ON */
  
  #if((DET_ERROR_RUNTIME == STD_ON)||\
             (DET_FORWARD_TO_DLT == STD_ON))
  /* Check to skip Invoke configured ReportRuntimeErrorCallout Functions*/
  VAR(Det_ErrorHookStatusType, DET_VAR_NOINIT) RuntimeError;
  #endif /* DET_ERROR_RUNTIME == STD_ON */
  
  #if((DET_ERROR_FAULT_TRANSIENT == STD_ON)||\
             (DET_FORWARD_TO_DLT == STD_ON))
  /* Check to skip Invoke configured ReportTransientFault Functions*/
  VAR(Det_ErrorHookStatusType, DET_VAR_NOINIT) TransientFault;
  #endif /* DET_ERROR_FAULT_TRANSIENT == STD_ON */
}Det_ErrorStatusType;

/* Configuration data structure of the Det module. */
/* @Trace: Det_SUD_DATATYPE_005 Stag_Det_ConfigType*/
/* polyspace +1 MISRA-C3:2.4 [Justified:Low] "Not a Defect" */
typedef struct STagTdd_Det_ConfigType
{
  uint8 dummy;
}Det_ConfigType;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/* @Trace: Det_SUD_CONSTVAR_001*/
/* Array of Function Pointers */
#define DET_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#if(DET_ERROR_HOOK == STD_ON)
/* Array of Function Pointers for Error Hook */
extern CONST(Det_FuncPtrType, DET_CONST)
		Det_GaaErrorHook[DET_TOTAL_ERROR_HOOKS];
#endif /* DET_ERROR_HOOK == STD_ON */

#if(DET_ERROR_RUNTIME == STD_ON)
extern CONST(Det_FuncPtrType, DET_CONST)
		Det_GaaRuntimeErrorCallout[DET_TOTAL_ERROR_RUNTIME];
#endif /* DET_ERROR_RUNTIME == STD_ON */

#if(DET_ERROR_FAULT_TRANSIENT == STD_ON)
extern CONST(Det_FuncPtrType, DET_CONST)
		Det_GaaTransientFaultCallout[DET_TOTAL_ERROR_FAULT_TRANSIENT];
#endif /* DET_ERROR_FAULT_TRANSIENT == STD_ON */

#define DET_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/*******************************************************************************
**                           Function Prototypes                              **
*******************************************************************************/

#endif /* DET_PCTYPES_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
