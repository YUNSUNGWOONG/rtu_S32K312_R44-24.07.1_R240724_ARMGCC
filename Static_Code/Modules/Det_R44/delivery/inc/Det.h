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
**  SRC-MODULE: Det.h                                                         **
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
** 0.0.2     13-Oct-2020   DanhLT2      Add unuse macro, #16382               **
*******************************************************************************/
#ifndef DET_H
#define DET_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* This header file includes all the standard data types, platform dependent
  header file and common return types */
#include "Std_Types.h"              /* standard AUTOSAR types */
/* @Trace: Det_SUD_DATATYPE_001 Std_ReturnType*/
/* @Trace: Det_SUD_DATATYPE_002 Std_VersionInfoType*/
#include "Det_PCTypes.h"            /* Det types */
#include "Det_Cfg.h"                /* Det Cfg header file */
/* @Trace: Det_SUD_MACRO_002*/
/* @Trace: Det_SUD_MACRO_005*/
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/*******************************************************************************
**                      Service IDs                                           **
*******************************************************************************/
/* Service id for Det_GetVersionInfo */
/* @Trace: Det_SUD_MACRO_003*/
#define DET_GETVERSIONINFO_SID                   ((uint8)0x03)

/*******************************************************************************
**                      DET Error Codes                                       **
*******************************************************************************/
/* DET Error Codes */
/* @Trace: Det_SUD_MACRO_006*/
#define DET_E_PARAM_POINTER                      ((uint8)0x01)

/*******************************************************************************
**                                  Macros                                    **
*******************************************************************************/
/* polyspace +1 MISRA-C3:D4.9 [Justified:Low] "A function should be used in preference to a function-like macro where they are interchangeable." */
#define DET_UNUSED_PTR(x)                        do { \
                                                    if((void *)(x) != NULL_PTR) {} \
                                                  } while(0)

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define DET_START_SEC_CODE
#include "MemMap.h"

/* This function is used to send the version information of Det
  to other modules*/
#if (DET_VERSION_INFO_API == STD_ON)
extern FUNC(void, DET_CODE)Det_GetVersionInfo
  (P2VAR(Std_VersionInfoType, AUTOMATIC, DET_APPL_DATA) versioninfo);
#endif /* DET_VERSION_INFO_API == STD_ON */

/* This Det_Init declaration for initialization function */
extern FUNC(void, DET_CODE) Det_Init(const Det_ConfigType* ConfigPtr);

/* This function is used to log the reported errors and count the reported
  errors */
/* polyspace<MISRA-C:8.8:Not a defect:Justify with annotations> No Impact of this rule violation */
extern FUNC(Std_ReturnType, DET_CODE) Det_ReportError
  (uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);

/* This function is the service for sending development error stored in RAM
  via communication interface */
extern FUNC(void, DET_CODE) Det_Start(void);

/* This function is used to Service to report runtime errors */
/* polyspace<MISRA-C:8.8:Not a defect:Justify with annotations> No Impact of this rule violation */
extern FUNC(Std_ReturnType, DET_CODE) Det_ReportRuntimeError
  (uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);

extern FUNC(Std_ReturnType, DET_CODE) Det_ReportTransientFault
  (uint16 ModuleId, uint8 InstanceId, uint8 ApiId, uint8 ErrorId);



#define DET_STOP_SEC_CODE
#include "MemMap.h"

#endif /* DET_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
