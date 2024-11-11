/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Com_Filter.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision filter functions and their functionality.           **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 1.1.9.0   28-Mar-2023   PhucNHM     CP44-267                               **
** 1.1.5.0   12-Oct-2022   PhucNHM     CP44-872                               **
** 1.1.3.1   21-Jun-2022   SMKwon      CP44-109                               **
** 1.1.2     25-Apr-2022   PhucNHM     R44-Redmine #25654                     **
** 1.1.1     25-Mar-2022   PhuPV10     R44-Redmine #25573 #25073              **
** 1.1.0     10-Feb-2022   PhucNHM     R44-Redmine #19316 #23495 #23725       **
**                                                 #23982 #24211              **
** 1.0.1     28-Sep-2021   DuyNGB      R44-Redmine #20139                     **
** 1.0.0     04-Dec-2020   SMKwon      Initial Version                        **
*******************************************************************************/
/* polyspace-begin MISRA2012:5.1 [Justified:Low] "This violation depends naming, that is defined by system configuration" */
/* polyspace-begin MISRA2012:11.5 [Not a defect:Low] "Following Com_SWS_00197 and Com_SWS_00198, data pointer of Com_Send/ReceiveSignal is void, so the casting to another type is inevitable." */
/* polyspace-begin RTE:IDP [Not a defect:Low] "NULL pointer was checked by generator" */
/* polyspace-begin CERT-C:EXP36-C [Justified:Low] "Following Com_SWS_00197 and Com_SWS_00198, data pointer of Com_Send/ReceiveSignal is void, so the casting to another type is inevitable, so the casting to another type is inevitable for filtering function in this API." */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Com.h"          /* Com header file */
#include "Com_Filter.h"   /* Com Filter header file */
#include "SchM_Com.h"     /* Scheduler Manager Com header file */
#if (COM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"          /* Det header file */
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/


/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Com_FNever                                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function never allows to pass any signal and   **
**                        always return false.                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_FNever
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod)
{
  /* @Trace: Com_SUD_API_01278 */
  /* @Trace: SWS_Com_00694 */
  COM_UNUSED_PTR(LpSigDataPtr);
  COM_UNUSED_PTR(LpFilter);
  COM_UNUSED(ActivateCode);
  COM_UNUSED(LdPeriod);
  /* Return filter result */
  return (COM_FALSE);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_FMaskedNewEqualsX_8                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 8 bit   **
**                        whose masked value is equal to specific value.      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_FMaskedNewEqualsX_8
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod)
{
  /* @Trace: SWS_Com_00694 */
  /* @Trace: Com_SUD_API_00080 */
  P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST) LpMaskedEqualsX;
  boolean LblFilterResult;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  COM_UNUSED(LdPeriod);
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* @Trace: Com_SUD_API_00081 */
    /* Get the pointer to Com_FilterMaskedNew filter structure */
    LpMaskedEqualsX =
         (P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)) LpFilter;
    /* Check whether "new value & mask == pX" */
    /* polyspace-begin MISRA-C3:D4.14 [Not a defect:Low] "Tainted pointer is assured by caller which was checked by generator" */
    if((uint8)(LpMaskedEqualsX->slX)
      == ((uint8)(LpMaskedEqualsX->ulFilterMask) &
                   ((*(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr))))
    {
      /* @Trace: Com_SUD_API_00082 */
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
    /* polyspace-end MISRA-C3:D4.14 [Not a defect:Low] "Tainted pointer is assured by caller which was checked by generator" */

  }
  /* @Trace: Com_SUD_API_00083 */
  /* Return filter result */
  return (LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FMaskedNewEqualsX_16                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 16 bit  **
**                        whose masked value is equal to specific value.      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FMaskedNewEqualsX_16
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod)
{
  /* @Trace: SWS_Com_00694 */
  /* @Trace: Com_SUD_API_00084 */
  P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST) LpMaskedEqualsX;
  boolean LblFilterResult;
  COM_UNUSED(LdPeriod);
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* @Trace: Com_SUD_API_00085 */
    /* Get the pointer to Com_FilterMaskedNew filter structure */
    LpMaskedEqualsX =
         (P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)) LpFilter;
    /* Check whether "new value & mask == pX" */
    /* polyspace-begin MISRA-C3:D4.14 [Not a defect:Low] "Tainted pointer is assured by caller which was checked by generator" */
    if((uint16)(LpMaskedEqualsX->slX)
      == ((uint16)(LpMaskedEqualsX->ulFilterMask) &
                  ((*(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSigDataPtr))))
    {
      /* @Trace: Com_SUD_API_00086 */
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
    /* polyspace-end MISRA-C3:D4.14 [Not a defect:Low] "Tainted pointer is assured by caller which was checked by generator" */
  }
  /* @Trace: Com_SUD_API_00087 */
  /* Return filter result */
  return (LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FMaskedNewEqualsX_32                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 32 bit  **
**                        whose masked value is equal to specific value.      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FMaskedNewEqualsX_32
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod)
{
  /* @Trace: SWS_Com_00694 */
  /* @Trace: Com_SUD_API_00088 */
  P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST) LpMaskedEqualsX;
  boolean LblFilterResult;
  COM_UNUSED(LdPeriod);
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* @Trace: Com_SUD_API_00089 */
    /* Get the pointer to Com_FilterMaskedNew filter structure */
    LpMaskedEqualsX =
         (P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)) LpFilter;
    /* Check whether "new_value & mask == pX" */
    /* polyspace +3 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
    if((NULL_PTR != LpMaskedEqualsX) && ((uint32)(LpMaskedEqualsX->slX)
      == ((uint32)(LpMaskedEqualsX->ulFilterMask)&
                  ((*(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSigDataPtr)))))
    {
      /* @Trace: Com_SUD_API_00090 */
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* @Trace: Com_SUD_API_00091 */
  /* Return filter result */
  return (LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FMaskedNewDiffersX_8                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 8 bit   **
**                        whose masked value is not equal to specific value.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FMaskedNewDiffersX_8
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod)
{
  /* @Trace: SWS_Com_00694 */
  /* @Trace: Com_SUD_API_00092 */
  P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST) LpMaskedNewDiffersX;
  boolean LblFilterResult;
  COM_UNUSED(LdPeriod);
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* @Trace: Com_SUD_API_00093 */
    /* Get the pointer to Com_FilterMaskedNew filter structure */
    LpMaskedNewDiffersX =
         (P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)) LpFilter;
    /* Check whether "new_value & mask != pX" */
    /* polyspace +3 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
    if((NULL_PTR != LpMaskedNewDiffersX) &&
      ((((uint8)(LpMaskedNewDiffersX->ulFilterMask)) &
               ((*(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr)))
                                         != (uint8)(LpMaskedNewDiffersX->slX)))
    {
      /* @Trace: Com_SUD_API_00094 */
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* @Trace: Com_SUD_API_00095 */
  /* Return filter result */
  return (LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FMaskedNewDiffersX_16                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 16 bit  **
**                        whose masked value is not equal to specific value.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FMaskedNewDiffersX_16
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod)
{
  /* @Trace: SWS_Com_00694 */
  /* @Trace: Com_SUD_API_00096 */
  P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST) LpMaskedNewDiffersX;
  boolean LblFilterResult;
  COM_UNUSED(LdPeriod);
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* @Trace: Com_SUD_API_00097 */
    /* Get the pointer to Com_FilterMaskedNew filter structure */
    LpMaskedNewDiffersX =
         (P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)) LpFilter;
    /* Check whether "new_value & mask != pX" */
    /* polyspace +3 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
    if((NULL_PTR != LpMaskedNewDiffersX) &&
      ((((uint16)(LpMaskedNewDiffersX->ulFilterMask)) &
            ((*(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSigDataPtr)))
                                      != (uint16)(LpMaskedNewDiffersX->slX)))
    {
      /* @Trace: Com_SUD_API_00098 */
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }

  }
  /* @Trace: Com_SUD_API_00099 */
  /* Return filter result */
  return (LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FMaskedNewDiffersX_32                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 32 bit  **
**                        whose masked value is not equal to specific value.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FMaskedNewDiffersX_32
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod)
{
  /* @Trace: SWS_Com_00694 */
  /* @Trace: Com_SUD_API_00100 */
  P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST) LpMaskedNewDiffersX;
  boolean LblFilterResult;
  COM_UNUSED(LdPeriod);
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* @Trace: Com_SUD_API_00101 */
    /* Get the pointer to Com_FilterMaskedNew filter structure */
    LpMaskedNewDiffersX =
         (P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)) LpFilter;
    /* Check whether "new_value & mask != pX" */
    /* polyspace +3 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
    if((NULL_PTR != LpMaskedNewDiffersX) &&
      ((((uint32)(LpMaskedNewDiffersX->ulFilterMask)) &
            ((*(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSigDataPtr)))
                                      != (uint32)(LpMaskedNewDiffersX->slX)))
    {
      /* @Trace: Com_SUD_API_00102 */
      /* Set the filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* @Trace: Com_SUD_API_00103 */
  /* Return filter result */
  return (LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FMaskedNewDiffersMaskedOld_EIGHT                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 8 bit   **
**                        when the masked value has changed.                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FMaskedNewDiffersMaskedOld_EIGHT
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod)
{
  /* @Trace: SWS_Com_00694 */
  /* @Trace: Com_SUD_API_00104 */
  P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)
                                                    LpMaskedNewDiffersMaskedOld;
  boolean LblFilterResult;
  COM_UNUSED(LdPeriod);
  /* Get the pointer to Com_FilterMaskedNew filter structure */
  LpMaskedNewDiffersMaskedOld =
       (P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)) LpFilter;

  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  if(ActivateCode == COM_ZERO)
  {
    /* Check whether "new_value & mask != old_value & mask" */
    /* polyspace-begin MISRA-C3:D4.14 [Not a defect:Low] "Tainted pointer is assured by caller which was checked by generator" */
    /* polyspace-begin RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
    if((*(LpMaskedNewDiffersMaskedOld->pFilterActivated) == COM_INVALID_PARAM)||
    (((uint8)(LpMaskedNewDiffersMaskedOld->ulFilterMask) &
               (*(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr))
                    != ((uint8)(LpMaskedNewDiffersMaskedOld->ulFilterMask) &
                             (*(P2CONST(uint8, AUTOMATIC, COM_CONST))
                             (LpMaskedNewDiffersMaskedOld->pSignalBuffer)))))
    /* polyspace-end RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
    /* polyspace-end MISRA-C3:D4.14 [Not a defect:Low] "Tainted pointer is assured by caller which was checked by generator" */
    {
      /* @Trace: Com_SUD_API_00105 */
      /* Copy the signal data to signal buffer */
      /* polyspace +3 MISRA-C3:D4.14 [Not a defect:Low] "Tainted pointer is assured by caller which was checked by generator" */
      (*(P2VAR(uint8, AUTOMATIC, COM_VAR))
                             (LpMaskedNewDiffersMaskedOld->pSignalBuffer)) =
               (*(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr);
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
      /* Set activate status as normal */
      *(LpMaskedNewDiffersMaskedOld->pFilterActivated) = COM_ZERO;
    }
  }
  else
  {
    /* @Trace: Com_SUD_API_00106 */
     /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "Tainted pointer is assured by caller which was checked by generator" */
    *(LpMaskedNewDiffersMaskedOld->pFilterActivated) = COM_INVALID_PARAM;
  }
  /* @Trace: Com_SUD_API_00107 */
  /* Return filter result */
  return (LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FMaskedNewDiffersMaskedOld_SIXTEEN              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 16 bit  **
**                        when the masked value has changed.                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FMaskedNewDiffersMaskedOld_SIXTEEN
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod)
{
  /* @Trace: SWS_Com_00694 */
  /* @Trace: Com_SUD_API_00108 */
  P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)
                                                    LpMaskedNewDiffersMaskedOld;
  boolean LblFilterResult;
  COM_UNUSED(LdPeriod);
  /* Get the pointer to Com_FilterMaskedNew filter structure */
  LpMaskedNewDiffersMaskedOld =
  (P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* polyspace-begin MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  if(ActivateCode == COM_ZERO)
  {
    /* Check whether "new_value & mask != old_value & mask" */
    /* polyspace-begin RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
    if((NULL_PTR != LpMaskedNewDiffersMaskedOld) &&
      ((*(LpMaskedNewDiffersMaskedOld->pFilterActivated) == COM_INVALID_PARAM)
      || (((uint16)(LpMaskedNewDiffersMaskedOld->ulFilterMask) &
      (*(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSigDataPtr))
           != ((uint16)(LpMaskedNewDiffersMaskedOld->ulFilterMask) &
                    (*(P2CONST(uint16, AUTOMATIC, COM_CONST))
                     (LpMaskedNewDiffersMaskedOld->pSignalBuffer))))))
    /* polyspace-end RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
    {
      /* @Trace: Com_SUD_API_00109 */
      /* Copy the signal data to signal buffer */
      (*(P2VAR(uint16, AUTOMATIC, COM_VAR))
                           (LpMaskedNewDiffersMaskedOld->pSignalBuffer)) =
            (*(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSigDataPtr);
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
      /* Set activate status as normal */
      *(LpMaskedNewDiffersMaskedOld->pFilterActivated) = COM_ZERO;
    }
  }
  else
  {
    if(NULL_PTR != LpMaskedNewDiffersMaskedOld)
    {
      /* @Trace: Com_SUD_API_00110 */
      *(LpMaskedNewDiffersMaskedOld->pFilterActivated) = COM_INVALID_PARAM;
    }
  }
  /* polyspace-end MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  /* Return filter result */
  /* @Trace: Com_SUD_API_00111 */
  return (LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FMaskedNewDiffersMaskedOld_THIRTYTWO            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 32 bit  **
**                        when the masked value has changed.                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FMaskedNewDiffersMaskedOld_THIRTYTWO
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod)
{
  /* @Trace: SWS_Com_00694 */
  /* @Trace: Com_SUD_API_00112 */
  P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)
                                                    LpMaskedNewDiffersMaskedOld;
  boolean LblFilterResult;
  COM_UNUSED(LdPeriod);
  /* Get the pointer to Com_FilterMaskedNew filter structure */
  LpMaskedNewDiffersMaskedOld =
       (P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* polyspace-begin MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  if(ActivateCode == COM_ZERO)
  {
    /* Check whether "new_value & mask != old_value & mask" */
    /* polyspace-begin RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
    if((NULL_PTR != LpMaskedNewDiffersMaskedOld) &&
      ((*(LpMaskedNewDiffersMaskedOld->pFilterActivated) == COM_INVALID_PARAM)
      || (((uint32)(LpMaskedNewDiffersMaskedOld->ulFilterMask) &
              (*(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSigDataPtr))
                   != ((uint32)(LpMaskedNewDiffersMaskedOld->ulFilterMask) &
                            (*(P2CONST(uint32, AUTOMATIC, COM_CONST))
                             (LpMaskedNewDiffersMaskedOld->pSignalBuffer))))))
    /* polyspace-end RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
    {
      /* @Trace: Com_SUD_API_00113 */
      /* Copy the signal data to signal buffer */
      (*(P2VAR(uint32, AUTOMATIC, COM_VAR))
                             (LpMaskedNewDiffersMaskedOld->pSignalBuffer)) =
              (*(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSigDataPtr);
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
      /* Set activate status as normal */
      *(LpMaskedNewDiffersMaskedOld->pFilterActivated) = COM_ZERO;
    }
  }
  else
  {
    if(NULL_PTR != LpMaskedNewDiffersMaskedOld)
    {
      /* @Trace: Com_SUD_API_00114 */
      *(LpMaskedNewDiffersMaskedOld->pFilterActivated) = COM_INVALID_PARAM;
    }
  }
  /* polyspace-end MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  /* Return filter result*/
  /* @Trace: Com_SUD_API_00115 */
  return (LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsWithin_u8                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 8 bit   **
**                        and type unsigned whose value lies within defined   **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsWithin_u8
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod)
{
  /* @Trace: SWS_Com_00694 */
  /* @Trace: Com_SUD_API_00116 */
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)
                                                                  LpNewIsWithin;
  uint8 LucData;
  boolean LblFilterResult;
  COM_UNUSED(LdPeriod);
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsWithin =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* @Trace: Com_SUD_API_00117 */
    /* Get the signal data to local variable */
    /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
    LucData = *(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether min <= new_value <= max */
    /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "Tainted pointer is assured by caller which was checked by generator" */
    if(((((uint8)(LpNewIsWithin->slMin)) <=  LucData) &&
                        (LucData <= ((uint8)(LpNewIsWithin->slMax)))))
    {
      /* @Trace: Com_SUD_API_00118 */
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* @Trace: Com_SUD_API_00119 */
  /* Return filter result */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsWithin_s8                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 8 bit   **
**                        and type signed whose value lies within defined     **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsWithin_s8
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod)
{
  /* @Trace: SWS_Com_00694 */
  /* @Trace: Com_SUD_API_00120 */
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST) LpNewIsWithin;
  sint8 LscData;
  COM_UNUSED(LdPeriod);
  boolean LblFilterResult;
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsWithin =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  /* polyspace-begin MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* @Trace: Com_SUD_API_00121 */
    /* Get the signal data to local variable */
    LscData = *(P2CONST(sint8, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether min <= new_value <= max */
    /* polyspace-begin RTE:OVFL [Not a defect:Low] "Value won't overflow. This is assured by generator" */
    if((NULL_PTR != LpNewIsWithin) &&
      (((((sint8)(LpNewIsWithin->slMin)) <=  LscData) &&
                          (LscData <= (sint8)(LpNewIsWithin->slMax)))))
    /* polyspace-end RTE:OVFL [Not a defect:Low] "Value won't overflow. This is assured by generator" */
    {
      /* @Trace: Com_SUD_API_00122 */
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* polyspace-end MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  /* Return filter result */
  /* @Trace: Com_SUD_API_00123 */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsWithin_u16                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 16 bit  **
**                        and type unsigned whose value lies within defined   **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsWithin_u16
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod)
{
  /* @Trace: SWS_Com_00694 */
  /* @Trace: Com_SUD_API_00124 */
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST) LpNewIsWithin;
  uint16 LusData;
  boolean LblFilterResult;
  COM_UNUSED(LdPeriod);
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsWithin =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* @Trace: Com_SUD_API_00125 */
    /* Get the signal data to local variable */
    /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "Tainted pointer is assured by caller which was checked by generator" */
    LusData = *(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether min <= new_value <= max */
    /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "Tainted pointer is assured by caller which was checked by generator" */
    if(((((uint16)(LpNewIsWithin->slMin)) <=  LusData) &&
                         (LusData <= ((uint16)(LpNewIsWithin->slMax)))))
    {
      /* @Trace: Com_SUD_API_00126 */
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* return filter result */
  /* @Trace: Com_SUD_API_00127 */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsWithin_s16                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 16 bit  **
**                        and type signed whose value lies within defined     **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsWithin_s16
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod)
{
  /* @Trace: SWS_Com_00694 */
  /* @Trace: Com_SUD_API_00128 */
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST) LpNewIsWithin;
  sint16 LssData;
  boolean LblFilterResult;
  COM_UNUSED(LdPeriod);
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsWithin =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  /* polyspace-begin MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* @Trace: Com_SUD_API_00129 */
    /* Get the signal data to local variable */
    LssData = *(P2CONST(sint16, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether min <= new_value <= max */
    /* polyspace-begin RTE:OVFL [Not a defect:Low] "Value won't overflow. This is assured by generator" */
    if((NULL_PTR != LpNewIsWithin) &&
      (((((sint16)(LpNewIsWithin->slMin)) <=  LssData) &&
                         (LssData <= (sint16)(LpNewIsWithin->slMax)))))
    /* polyspace-end RTE:OVFL [Not a defect:Low] "Value won't overflow. This is assured by generator" */
    {
      /* @Trace: Com_SUD_API_00130 */
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* polyspace-end MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  /* Return filter result */
  /* @Trace: Com_SUD_API_00131 */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsWithin_u32                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 32 bit  **
**                        and type unsigned whose value lies within defined   **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsWithin_u32
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod)
{
  /* @Trace: SWS_Com_00694 */
  /* @Trace: Com_SUD_API_00132 */
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST) LpNewIsWithin;
  uint32 LulData;
  boolean LblFilterResult;
  COM_UNUSED(LdPeriod);
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsWithin =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  /* polyspace-begin MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* @Trace: Com_SUD_API_00133 */
    /* Get the signal data to local variable */
    LulData = *(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether min <= new_value <= max */
    if((NULL_PTR != LpNewIsWithin) &&
      (((((uint32)(LpNewIsWithin->slMin)) <=  LulData) &&
                         (LulData <= (uint32)(LpNewIsWithin->slMax)))))
    {
      /* @Trace: Com_SUD_API_00134 */
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* polyspace-end MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  /* Return filter result */
  /* @Trace: Com_SUD_API_00135 */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsWithin_s32                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 32 bit  **
**                        and type signed whose value lies within defined     **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsWithin_s32
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod)
{
  /* @Trace: SWS_Com_00694 */
  /* @Trace: Com_SUD_API_00136 */
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST) LpNewIsWithin;
  sint32 LslData;
  boolean LblFilterResult;
  COM_UNUSED(LdPeriod);
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsWithin =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* @Trace: Com_SUD_API_00137 */
    /* Get the signal data to local variable */
    /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "Tainted pointer is assured by caller which was checked by generator" */
    LslData = *(P2CONST(sint32, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether min <= new_value <= max */
    /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "Tainted pointer is assured by caller which was checked by generator" */
    if((((LpNewIsWithin->slMin) <=  LslData) &&
                                 (LslData <= (LpNewIsWithin->slMax))))
    {
      /* @Trace: Com_SUD_API_00138 */
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* Return filter result */
  /* @Trace: Com_SUD_API_00139 */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsOutside_u8                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 8 bit   **
**                        and type unsigned whose value lies outside defined  **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsOutside_u8
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod)
{
  /* @Trace: SWS_Com_00694 */
  /* @Trace: Com_SUD_API_00140 */
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST) LpNewIsOutside;
  uint8 LucData;
  boolean LblFilterResult;
  COM_UNUSED(LdPeriod);
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsOutside =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  /* polyspace-begin MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* @Trace: Com_SUD_API_00141 */
    /* Get the signal data to local variable */
    LucData = *(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether new value < min or new value > max */
    if((NULL_PTR != LpNewIsOutside) &&
      ((((uint8)(LpNewIsOutside->slMin) >  LucData) ||
        (LucData > (uint8)(LpNewIsOutside->slMax)))))
    {
      /* @Trace: Com_SUD_API_00142 */
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* polyspace-end MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  /* Return filter result */
  /* @Trace: Com_SUD_API_00143 */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsOutside_s8                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 8 bit   **
**                        and type signed whose value lies outside defined    **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsOutside_s8
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod)
{
  /* @Trace: SWS_Com_00694 */
  /* @Trace: Com_SUD_API_00144 */
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST) LpNewIsOutside;
  sint8 LscData;
  boolean LblFilterResult;
  COM_UNUSED(LdPeriod);
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsOutside =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  /* polyspace-begin MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* @Trace: Com_SUD_API_00145 */
    /* Get the signal data to local variable */
    LscData = *(P2CONST(sint8, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether new value < min or new value > max */
    /* polyspace-begin RTE:OVFL [Not a defect:Low] "Value won't overflow. This is assured by generator" */
    if((NULL_PTR != LpNewIsOutside) &&
      ((((sint8)(LpNewIsOutside->slMin) >  LscData) ||
                          (LscData > (sint8)(LpNewIsOutside->slMax)))))
    /* polyspace-end RTE:OVFL [Not a defect:Low] "Value won't overflow. This is assured by generator" */
    {
      /* @Trace: Com_SUD_API_00146 */
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* polyspace-end MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  /* Return filter result */
  /* @Trace: Com_SUD_API_00147 */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsOutside_u16                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 16 bit  **
**                        and type unsigned whose value lies outside defined  **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsOutside_u16
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod)
{
  /* @Trace: SWS_Com_00694 */
  /* @Trace: Com_SUD_API_00148 */
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST) LpNewIsOutside;
  uint16 LusData;
  boolean LblFilterResult;
  COM_UNUSED(LdPeriod);
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsOutside =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  /* polyspace-begin MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* @Trace: Com_SUD_API_00149 */
    /* Get the signal data to local variable */
    LusData = *(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether new value < min or new value > max */
    if((NULL_PTR != LpNewIsOutside) &&
      ((((uint16)(LpNewIsOutside->slMin) >  LusData) ||
                         (LusData > (uint16)(LpNewIsOutside->slMax)))))
    {
      /* @Trace: Com_SUD_API_00150 */
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* polyspace-end MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  /* Return filter result */
  /* @Trace: Com_SUD_API_00151 */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsOutside_s16                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 16 bit  **
**                        and type signed whose value lies outside defined    **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsOutside_s16
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod)
{
  /* @Trace: SWS_Com_00694 */
  /* @Trace: Com_SUD_API_00152 */
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST) LpNewIsOutside;
  sint16 LssData;
  boolean LblFilterResult;
  COM_UNUSED(LdPeriod);
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsOutside =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  /* polyspace-begin MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* @Trace: Com_SUD_API_00153 */
    /* Get the signal data to local variable */
    LssData = *(P2CONST(sint16, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether new value < min or new value > max */
    /* polyspace-begin RTE:OVFL [Not a defect:Low] "Value won't overflow. This is assured by generator" */
    if((NULL_PTR != LpNewIsOutside) &&
      ((((sint16)(LpNewIsOutside->slMin) >  LssData) ||
                         (LssData > (sint16)(LpNewIsOutside->slMax)))))
    /* polyspace-end RTE:OVFL [Not a defect:Low] "Value won't overflow. This is assured by generator" */
    {
      /* @Trace: Com_SUD_API_00154 */
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* polyspace-end MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  /* Return filter result */
  /* @Trace: Com_SUD_API_00155 */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsOutside_u32                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 32 bit  **
**                        and type unsigned whose value lies outside defined  **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsOutside_u32
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod)
{
  /* @Trace: SWS_Com_00694 */
  /* @Trace: Com_SUD_API_00156 */
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST) LpNewIsOutside;
  uint32 LulData;
  boolean LblFilterResult;
  COM_UNUSED(LdPeriod);
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsOutside =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  /* polyspace-begin MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* @Trace: Com_SUD_API_00157 */
    /* Get the signal data to local variable */
    LulData = *(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether new value < min or new value > max */
    if((NULL_PTR != LpNewIsOutside) &&
      ((((uint32)(LpNewIsOutside->slMin) >  LulData) ||
                         (LulData > (uint32)(LpNewIsOutside->slMax)))))
    {
      /* @Trace: Com_SUD_API_00158 */
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* polyspace-end MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  /* Return filter result */
  /* @Trace: Com_SUD_API_00159 */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FNewIsOutside_s32                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function allows to pass signal of size 32 bit  **
**                        and type signed whose value lies outside defined    **
**                        limits.                                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_FNewIsOutside_s32
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod)
{
  /* @Trace: SWS_Com_00694 */
  /* @Trace: Com_SUD_API_00160 */
  P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST) LpNewIsOutside;
  sint32 LslData;
  boolean LblFilterResult;
  COM_UNUSED(LdPeriod);
  /* Get the pointer to Com_FilterNewIsInRange filter structure */
  LpNewIsOutside =
    (P2CONST(Com_FilterNewIsInRange, AUTOMATIC, COM_CONST)) LpFilter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  /* polyspace-begin MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* @Trace: Com_SUD_API_00161 */
    /* Get the signal data to local variable */
    LslData = *(P2CONST(sint32, AUTOMATIC, COM_CONST)) LpSigDataPtr;
    /* Check whether new value < min or new value > max */
    if((NULL_PTR != LpNewIsOutside) &&
      ((((LpNewIsOutside->slMin) >  LslData) ||
                                 (LslData > (LpNewIsOutside->slMax)))))
    {
      /* @Trace: Com_SUD_API_00162 */
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
  }
  /* polyspace-end MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
  /* Return filter result */
  /* @Trace: Com_SUD_API_00163 */
  return(LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_FOneEveryN                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is Com internal function. This function passes **
**                        a signal once every N signal occurrences. Each time **
**                        the signal is received or transmitted, occurrence   **
**                        is incremented by 1 after filtering. Length of      **
**                        occurrence is 8 bit.                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant for the same signal.                  **
**                        Reentrant for different signals.                    **
**                                                                            **
** Input Parameters     : LpFilter, LpSigDataPtr, ActivateCode                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblFilterResult                                     **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_FOneEveryN
(P2CONST(void, AUTOMATIC, COM_CONST) LpFilter,
                       P2CONST(void, AUTOMATIC, COM_CONST) LpSigDataPtr,
                       uint8 ActivateCode, uint16 LdPeriod)
{
  /* @Trace: SWS_Com_00694 */
  /* @Trace: Com_SUD_API_00164 */
  P2VAR(uint16, AUTOMATIC, COM_VAR) LpCounter;
  P2CONST(Com_FilterOneEveryN, AUTOMATIC, COM_CONST) LpOneEveryN;
  boolean LblFilterResult;
  uint16 LddPeriod;
  LddPeriod = LdPeriod;
  /* Get the pointer to Com_FilterOneEveryN filter structure*/
  LpOneEveryN =
      (P2CONST(Com_FilterOneEveryN, AUTOMATIC, COM_CONST)) LpFilter;
  /* Get the pointer to counter */
  /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "Tainted pointer is assured by caller which was checked by generator" */
  LpCounter = LpOneEveryN->pCounter;
  /* Set filter result to false */
  LblFilterResult = COM_FALSE;
  /* return false, when ActivateCode is invalid */
  if(ActivateCode != COM_INVALID_PARAM)
  {
    /* Pass message once every N */
    /* polyspace +1 RTE:NIV [Not a defect:Low] "Variable initialized with configuration data" */
    if((*LpCounter)  == (LpOneEveryN->usOffset))
    {
      /* @Trace: Com_SUD_API_00165 */
      /* Set filter result to true */
      LblFilterResult = COM_TRUE;
    }
    /* @Trace: Com_SUD_API_00166 */
    /* Increment the counter */
    (*LpCounter)++;
    /* Check whether counter is equal to period */
    if((*LpCounter)  == LddPeriod)
    {
      /* @Trace: Com_SUD_API_00167 */
      /* Reset the counter to zero */
      *LpCounter = (uint16)COM_ZERO;
    }
  }
  /* @Trace: Com_SUD_API_00168 */
  COM_UNUSED_PTR(LpSigDataPtr);
  /* Return filter result */
  return (LblFilterResult);
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end MISRA2012:5.1 [Justified:Low] "This violation depends naming, that is defined by system configuration" */
/* polyspace-end MISRA2012:11.5 [Not a defect:Low] "Following Com_SWS_00197 and Com_SWS_00198, data pointer of Com_Send/ReceiveSignal is void, so the casting to another type is inevitable." */
/* polyspace-end RTE:IDP [Not a defect:Low] "NULL pointer was checked by generator" */
/* polyspace-end CERT-C:EXP36-C [Justified:Low] "Following Com_SWS_00197 and Com_SWS_00198, data pointer of Com_Send/ReceiveSignal is void, so the casting to another type is inevitable, so the casting to another type is inevitable for filtering function in this API." */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
