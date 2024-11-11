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
**  SRC-MODULE: Os_IocInternalTypes.h                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of IOC type internally used macros,                 **
**              structure declarations and extern declarations of variables   **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/* @Trace: SRS_BSW_00003 SRS_BSW_00006 SRS_BSW_00007 SRS_BSW_00009 SRS_BSW_00301 SRS_BSW_00302 SRS_BSW_00305
 SRS_BSW_00415 SRS_BSW_00305 SRS_BSW_00307 SRS_BSW_00308 SRS_BSW_00310 SRS_BSW_00328 SRS_BSW_00441 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.1     07-Jan-2022   TinHV1           R44-Redmine #23444/#23536         **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.2     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Fixed Misra-C 2.4                 **
** 1.0.1     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:8.11 [Justified:Low] "External linkage with array size makes error because of compiler optimization" */
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-begin MISRA-C3:D4.8 [Justified:Low] "Not request the object should be hidden" */
#ifndef OS_IOCINTERNALTYPES_H
#define OS_IOCINTERNALTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* @Trace: SRS_BSW_00357 SRS_BSW_00410 */
/* IOC Internal buffer Status*/
#if (OS_APPLICATION == STD_ON)

typedef struct
{
  P2VAR(uint32, AUTOMATIC, OS_VAR) pIocBuf;
  uint32 ulDataSize;
} Os_IocBufType;

typedef struct
{
  P2CONST(Os_IocBufType, AUTOMATIC, OS_CONST) pBuffer;
  /* Count of parameters for Ioc[Write/Read]Group */
  uint32 ulDataCount;
} Os_IocUnqueuedCfgType;

typedef struct
{
  P2CONST(Os_IocBufType, AUTOMATIC, OS_CONST) pBuffer;
  /* Count of parameters for Ioc[Send/Receive]Group */
  uint32 ulDataCount;
  /* Internal transmission buffer size */
  uint32 ulQueueLen;
  /* Queue read Index */
  uint32 ulQueueRead;
  /* Queue Write Index */
  uint32 ulQueueWrite;
  /* Current Queue Count */
  uint32 ulQueueCount;
  /* Data Lost */
  boolean blDataLost;
} Os_IocQueuedCfgType;

/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
/* @Trace: SRS_BSW_00309 */
extern CONST(Os_IocBufType, OS_CONST) Os_GaaIocQueuedBuf[];
#define OS_STOP_SEC_CONST_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

#define OS_START_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"
extern VAR(Os_IocQueuedCfgType, OS_VAR)Os_GaaIocQueuedCfg[];
extern CONST(Os_IocUnqueuedCfgType, OS_CONST)Os_GaaIocUnqueuedCfg[];
#define OS_STOP_SEC_VAR_INIT_ASIL_D_GLOBAL_UNSPECIFIED
#include "MemMap.h"

#endif /* if (OS_APPLICATION == STD_ON) */

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

#endif /* OS_IOCINTERNALTYPES_H */

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end MISRA-C3:8.11 [Justified:Low] "External linkage with array size makes error because of compiler optimization" */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-end MISRA-C3:D4.8 [Justified:Low] "Not request the object should be hidden" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
