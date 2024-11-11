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
**  SRC-MODULE: Os_Arch_PowerManagerment.c                                    **
**                                                                            **
**  TARGET    : TriCore 1.6.2 (AURIX 2G)                                      **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of power management specific functionality          **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
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
** 1.1.1     23-Nov-2023    HJ.Kim       Jira    CP44-3306                    **
** 1.0.2     11-Jen-2023    HGKim        Jira    CP44-1488                    **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace:begin<RTE: ABS_ADDR : Not a defect : Justify with annotations > Absolute address is needed to access MCU register */
/* polyspace-begin RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-begin RTE:OBAI [Not a defect:Low] "configured array index" */
/* polyspace:begin<MISRA-C:10.1:Not a defect:Justify with annotations> It is used for consistency */
/* polyspace:begin<MISRA-C:11.3:Not a defect:Justify with annotations> For implementation, conversion from function pointer to void pointer is needed to represent function address */
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"     /* Os InternalTypes header file */
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Arch_Multicore.h"    /* Os Multi-core header file */
#include "Os_Arch_Context.h"
#include "Os_Arch_Idle.h" /* Os Power management header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
/***************************************************************************//**
** Function             : Os_EnterIdle
**
** Service ID           : NA
**
** Description          : This function used to perform idle mode
**
** Sync/Async           : Synchronous
**
** Re-entrancy          : Re-entrant
**
** @param [in]            IdleMode
**
** @return              : NA
**
**
** @remarks             : Global Variable(s)     :
**                        None
**
**                        Function(s) invoked    :
**                        Os_Halt()
*******************************************************************************/
FUNC(void, OS_CODE) Os_EnterIdle(IdleModeType IdleMode)
{
  /* Checking the real of Idle Mode */
  switch(IdleMode)
  {
    case IDLE_NO_HALT:
      /* Do Nothing */
      break;

    case IDLE_CS_HALT:
    /* @Trace : SafeOs_SUD_API_50302 */
      Os_Halt();
      break;

    default:
    /* @Trace : SafeOs_SUD_API_50303 */
      /* Do Nothing */
      break;
  }
}
#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace:end<RTE: ABS_ADDR : Not a defect : Justify with annotations > Absolute address is needed to access MCU register */
/* polyspace-end RTE:IDP [Not a defect:Low] "configured memory access index" */
/* polyspace-end RTE:OBAI [Not a defect:Low] "configured array index" */
/* polyspace:end<MISRA-C:10.1:Not a defect:Justify with annotations> It is used for consistency */
/* polyspace:end<MISRA-C:11.3:Not a defect:Justify with annotations> For implementation, conversion from function pointer to void pointer is needed to represent function address */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
