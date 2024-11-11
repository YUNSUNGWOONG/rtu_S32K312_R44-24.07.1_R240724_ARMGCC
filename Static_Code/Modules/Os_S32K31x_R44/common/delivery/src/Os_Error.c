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
**  SRC-MODULE: Os_Error.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of Error functionality                              **
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
** 1.5.3     16-Feb-2024   HG.Kim           Jira CP44-3828                    **
** 1.5.0     26-Apr-2023   SH.Yoo           Jira CP44-2028                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.3     23-Dec-2021   DatNXT           R44-Redmine #22670                **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.6.0   23-Mar-2021   Thao             Redmine #18032                    **
** 1.0.3     16-Sep-2020   Thao             R44-Redmine #13398 Change access  **
**                                          rights of specific Os application **
**                                          Hooks                             **
** 1.0.2     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Fixed Misra-C 16.1                **
** 1.0.1     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/
/* @Trace: SRS_Os_80027 SRS_Os_80001 SRS_Os_80026 SRS_Os_11002 */

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os_InternalTypes.h"     /* Os InternalTypes header file */
#include "Os_PortTypes.h"         /* Os PortTypes header file */
#include "Os_Ram.h"               /* Os Ram header file */
#include "Os_Error.h"             /* Os Error header file */
/* @Trace: SRS_BSW_00410 */
#if (OS_MEMORY_PROTECTION == STD_ON)
#include "Os_Application.h"       /* Os Application header file */
#endif
#include "Os_Definition.h"

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
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Os_ErrorHook                                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Service is used to service the error.          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : Error                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : StartOS() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        Os_GaaStaticAppHook, Os_GddAppId,                   **
**                        Os_GusCallevelCheck                                 **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ErrorHook(), LpAppErrorHook()                       **
*******************************************************************************/
/* @Trace: SRS_Os_00097 SRS_Os_11013 SRS_Os_00097 */
#if ((OS_ERROR_HOOK == STD_ON) || (OS_APP_ERROR_HOOK == STD_ON))
/* polyspace +1 CODE-METRICS:CALLING [Justified:Low] "Function is used to serve in case error happen" */
FUNC(void, OS_CODE) Os_ErrorHook(StatusType Error)
{
  #if (OS_APP_ERROR_HOOK == STD_ON)
  P2FUNC(void, OS_VAR, LpAppErrorHook) (StatusType Error);
  #endif
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif
  /* @Trace: SafeOs_SUD_API_20801 */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* Check if status of Error hook is OS_FALSE */
  /* polyspace +4 MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
  /* polyspace +3 MISRA-C3:18.1 [Justified:Low] "Array index alway inside bounds and code is manually checked" */
  /* polyspace +2 RTE:OBAI [Not a defect:Low] "configured array index" */
  #if (OS_ERROR_HOOK == STD_ON)
  /* polyspace +3 MISRA-C3:18.1 [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +2 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +1 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  if ((Os_GusCallevelCheck[OS_CORE_ID]&OS_CONTEXT_ERRORHOOK) == OS_ZERO)
  #endif
  {
    /* @Trace: SafeOs_SUD_API_20802 */
    /* Make status of Error hook to true */
    /* polyspace +3 MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
    /* polyspace +2 MISRA-C3:18.1 [Justified:Low] "Array index alway inside bounds and code is manually checked" */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "configured array index" */
    Os_GusCallevelCheck[OS_CORE_ID] |= OS_CONTEXT_ERRORHOOK;

    OS_SET_KERNEL_FLAG();
    #if (OS_ERROR_HOOK == STD_ON)
    /* Call ErrorHook function : Run in Supervisor mode */
    ErrorHook(Error);
    #endif
    #if (OS_APP_ERROR_HOOK == STD_ON)
    if( INVALID_OSAPPLICATION != Os_GddAppId[OS_CORE_ID] )
    {
      /* @Trace: SafeOs_SUD_API_20803 */
      /* Save Application specific ErrorHook in a local */
      /* polyspace +3 MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
      /* polyspace +2 MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array is operated in predefined range" */
      LpAppErrorHook = Os_GaaStaticAppHook[Os_GddAppId[OS_CORE_ID]].pErrorHook;
      /* Check if Application specific ErrorHook is not a null pointer */
      /* polyspace +1 RTE:UNR [Not a defect:Low] "Check NULL_PTR is done" */
	  if (LpAppErrorHook != NULL_PTR)
      {
        /* @Trace: SafeOs_SUD_API_20804 */
        /* Invoke the application Specific ErrorHook */
		/* polyspace +2 RTE:UNR [Not a defect:Low] "function ptr points to a valid function and code is manually checked" */
        /* polyspace<RTE:COR:Not a defect:No Action Planned> function ptr points to a valid function and code is manually checked*/
        OS_PROCESS_APP_ERRORHOOK((Os_GddAppId[OS_CORE_ID]), LpAppErrorHook, Error);
      } /* End of if (LpAppErrorHook != NULL_PTR) */
    }
    #endif /* End of if (OS_APP_ERROR_HOOK == STD_ON) */
    OS_CLEAR_KERNEL_FLAG();

    /* Make status of Error hook to false */
    Os_GusCallevelCheck[OS_CORE_ID] &= (uint16)((uint16)0xFFFF & ~(uint16)OS_CONTEXT_ERRORHOOK);
  } /* End of if (Os_GusCallevelCheck... ) */
} /* End of Os_ErrorHook(StatusType Error) */
#endif /* End of if ((OS_ERROR_HOOK == STD_ON) || (OS_APP_ERROR_HOOK == STD_ON))
        **/

/*******************************************************************************
** Function Name        : Os_CheckObjIDError                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is called to check object ID          **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : StartOs() function should be called                 **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        None                                                **
**                        Function(s) invoked    :                            **
**                        None                                                **
*******************************************************************************/
#if (OS_APPLICATION == STD_ON)
/* polyspace +2 DEFECT:UNUSED_PARAMETER [Not a defect:Low] "The parameter checked error before used" */
/* polyspace +1 MISRA-C3:2.7 [Not a defect:Low] "The parameter checked error before used" */
FUNC(StatusType, OS_CODE) Os_CheckObjIDError(
                            ObjectTypeType ObjectType, ObjectTypeIndex ObjectID)
{
  StatusType LenStatusReturn;

  /* Initialize the return */
  LenStatusReturn = E_OK;

  switch (ObjectType)
  {
    case OBJECT_ISR:
      /* @Trace: SafeOs_SUD_API_51101 */
      OS_CHECK_ISR_ID_ERROR(ObjectID, &LenStatusReturn);
      break;

    #if (OS_ALARM == STD_ON)
    case OBJECT_ALARM:
      /* @Trace: SafeOs_SUD_API_51102 */
      if((ObjectID) >= Os_Alarm_Count)
      {
        /* @Trace: SafeOs_SUD_API_51103 */
        LenStatusReturn = E_OS_ID;
      }
    break;
    #endif

    #if (OS_RESOURCE == STD_ON)
    case OBJECT_RESOURCE:
      /* @Trace: SafeOs_SUD_API_51104 */
      OS_CHECK_RESOURCE_ID_ERROR(ObjectID, &LenStatusReturn);
      break;
    #endif

    #if (OS_COUNTER == STD_ON)
    case OBJECT_COUNTER:
      /* @Trace: SafeOs_SUD_API_51105 */
      OS_CHECK_COUNTER_ID_ERROR(ObjectID, &LenStatusReturn);
      break;
    #endif

    #if (OS_SCHEDTABLE == STD_ON)
    case OBJECT_SCHEDULETABLE:
      /* @Trace: SafeOs_SUD_API_51106 */
      OS_CHECK_SCHEDTABLE_ID_ERROR(ObjectID, &LenStatusReturn);
      break;
    #endif

    default:
      /* @Trace: SafeOs_SUD_API_51107 */
      /* Do Nothing */
      break;
  } /* End of switch (ObjectType) */

  return (LenStatusReturn);
}
#endif /* End of #if (OS_APPLICATION == STD_ON) */
#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
