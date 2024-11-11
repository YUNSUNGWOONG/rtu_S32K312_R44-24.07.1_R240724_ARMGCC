/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**                                                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  SRC-MODULE: E2E_SM.c                                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR E2E Module                                            **
**                                                                            **
**  PURPOSE   : To implement specification of E2E State machine driver        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision Date           By              Description                        **
********************************************************************************
** 1.0.1.1  27-Jun-2022    Gongbin Lim     #CP44-320                          **
** 0.0.1    10-Sep-2019    CuongLX         Initial Version                    **
** 0.0.2    20-Feb-2020    CuongLX         Remove marcro less meaning         **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* Include file for State Machine implementation */
#include "E2E.h"

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
static FUNC(void, E2E_CODE) E2E_SMAddStatus(
    VAR(E2E_PCheckStatusType, AUTOMATIC) ProfileStatus,
    P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr);

static FUNC(void, E2E_CODE) E2E_SMClearStatus(
    P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr);

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define E2E_START_SEC_CODE_ASIL_D /*polyspace MISRA2012:2.5 [Justified:Low] "This macro is necessary for Memory mapping"*/
#include "MemMap.h"  /*polyspace MISRA2012:20.1 [Justified:Low] "This include directive is necessary for Memory mapping"*/

/*******************************************************************************
** Function Name        : E2E_SMCheck                                         **
**                                                                            **
** Service ID           : 0x30                                                **
**                                                                            **
** Description          : This function Checks the communication channel.     **
**                        It determines if the data can be used for           **
**                        safety-related application, based on history of     **
**                        checks performed by a corresponding E2E_P0XCheck()  **
**                        function.                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ProfileStatus, ConfigPtr                            **
**                                                                            **
** InOut Parameters     : StatePtr                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Value         : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : E2E_SMAddStatus            **
*******************************************************************************/
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337 */

FUNC(Std_ReturnType, E2E_CODE) E2E_SMCheck(
    VAR(E2E_PCheckStatusType, AUTOMATIC) ProfileStatus,
    P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr,
    P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr)
{
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  
  returnValue = E2E_E_OK;

  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/  
  /* Verify inputs of the function */
  if ((NULL_PTR == StatePtr) || (NULL_PTR == ConfigPtr))
  /* @Trace: SafeE2E_SUD_MF_800 */
  {
    returnValue = E2E_E_INPUTERR_NULL;
  }
  else if (NULL_PTR == (StatePtr->ProfileStatusWindow))
  /* @Trace: SafeE2E_SUD_MF_800 */
  {
    returnValue = E2E_E_INPUTERR_NULL;
  }
  else if ((StatePtr->WindowTopIndex) >= (ConfigPtr->WindowSize)) 
  /* @Trace: SafeE2E_SUD_MF_802 */
  {
    returnValue = E2E_E_INPUTERR_WRONG;
  }
  else
  /* @Trace: SafeE2E_SUD_MF_801 */
  {
    switch (StatePtr->SMState)
    {
      case E2E_SM_DEINIT:
      {
        returnValue = E2E_E_WRONGSTATE;

        break;
      } /* End case E2E_SM_DEINIT: */

      case E2E_SM_NODATA:
      {
        /* Check transition condition */
        if ((ProfileStatus != E2E_P_ERROR) && (ProfileStatus != E2E_P_NONEWDATA))
        {
          /* Make transition */
          StatePtr->SMState = E2E_SM_INIT;
        }
        else
        {
          /* Do nothing*/
        }

        break;
      } /* End case E2E_SM_NODATA: */

      case E2E_SM_INIT:
      {
        /* Execute E2E_SMAddStatus() */
        E2E_SMAddStatus(ProfileStatus, StatePtr, ConfigPtr);

        /* Check transition condition */
        if (((StatePtr->ErrorCount) <= (ConfigPtr->MaxErrorStateInit)) &&
            ((StatePtr->OkCount) >= (ConfigPtr->MinOkStateInit)))
        {
          /* Make transition */
          StatePtr->SMState = E2E_SM_VALID;
        }
        /* Check transition condition */
        else if ((StatePtr->ErrorCount) > (ConfigPtr->MaxErrorStateInit))
        {
          /* Make transition */
          StatePtr->SMState = E2E_SM_INVALID;
        }
        else
        {
          /* Do nothing*/
        }

        break;
      }

        /* End case E2E_SM_INIT: */

      case E2E_SM_INVALID:
      {
        /* Execute E2ESMAddStatus() */
        E2E_SMAddStatus(ProfileStatus, StatePtr, ConfigPtr);

        /* Check transition condition */
        if (((StatePtr->ErrorCount) <= (ConfigPtr->MaxErrorStateInvalid)) &&
            ((StatePtr->OkCount) >= (ConfigPtr->MinOkStateInvalid)))
        {
          /* Make transition */
          StatePtr->SMState = E2E_SM_VALID;
        }
        else
        {
          /* Do nothing*/
        }
        
        break;
      } /* End case E2E_SM_INVALID: */

      case E2E_SM_VALID:
      {
        /* Execute E2ESMAddStatus() */
        E2E_SMAddStatus(ProfileStatus, StatePtr, ConfigPtr);

        /* Check transition condition */
        if (((StatePtr->ErrorCount) <= (ConfigPtr->MaxErrorStateValid)) &&
            ((StatePtr->OkCount) >= (ConfigPtr->MinOkStateValid)))
        {
          /* Do nothing */
        }
        else
        {
          /* Make transition */
          StatePtr->SMState = E2E_SM_INVALID;
        }

        break;
      } /* End case E2E_SM_VALID: */

      default:
      {
        /* Do nothing*/
        break;
      }
    }
  }/* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/

  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_SMCheckInit                                     **
**                                                                            **
** Service ID           : 0x31                                                **
**                                                                            **
** Description          : This function shall initializes the State machine.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ConfigPtr                                           **
**                                                                            **
** InOut Parameters     : StatePtr                                            **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Value         : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : E2E_SMClearStatus          **
*******************************************************************************/
/* @Trace: SRS_E2E_08527 SRS_E2E_08528 RS_E2E_08540 SRS_BSW_00337 */

FUNC(Std_ReturnType, E2E_CODE) E2E_SMCheckInit(
    P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr)
{
  /* Local variable to store return value */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  returnValue = E2E_E_OK;
  
  /* @Trace: SafeE2E_SUD_MF_803 */
  /* Verify inputs of the function */
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  if ((NULL_PTR == StatePtr) || (NULL_PTR == ConfigPtr))
  {
    returnValue = E2E_E_INPUTERR_NULL;
  }
  else if (NULL_PTR == (StatePtr->ProfileStatusWindow))
  {
    returnValue = E2E_E_INPUTERR_NULL;
  }
  else
  {
    /* Do E2E_SMClearStatus() */
    E2E_SMClearStatus(StatePtr, ConfigPtr);

    StatePtr->SMState = E2E_SM_NODATA;

  } /* End of if-else */
  /* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/

  return returnValue;
}

/*******************************************************************************
** Function Name        : E2E_SMAddStatus                                     **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function shall process E2E_SMCheck's           **
**                        ProfileStatus.                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ProfileStatus, StatePtr, ConfigPtr                  **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Value         : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace:  */

static FUNC(void, E2E_CODE) E2E_SMAddStatus(
    VAR(E2E_PCheckStatusType, AUTOMATIC) ProfileStatus,
    P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr)
{
  /* Local variable to store index of loop */
  VAR(uint8, AUTOMATIC) idx;
  /* Local variable to store count value */
  VAR(uint8, AUTOMATIC) count;

  /* @Trace: SafeE2E_SUD_MF_805 */
  /* Write ProfileStatus to ProfileStatusWindow */
  StatePtr->ProfileStatusWindow[StatePtr->WindowTopIndex] = (uint8)ProfileStatus;

  /* Initialize Loop_Index value */
  idx = 0x00U;

  /* Initialize Count value */
  count = 0x00U;

  /* Check the number of elements in ProfileStatusWindow[] with values
  * E2E_P_OK
  */
  while (idx < (ConfigPtr->WindowSize))
  {
    if ((uint8)E2E_P_OK == (StatePtr->ProfileStatusWindow[idx]))
    {
      count++;
    }
    else
    {
      /* Do nothing*/
    }

    idx++;
  }

  /* Write the number of elements in ProfileStatusWindow[] with values
  * E2E_P_OK
  */
  StatePtr->OkCount = count;

  /* Initialize Loop_Index value */
  idx = 0x00U;

  /* Initialize Count value */
  count = 0x00U;

  /* Check the number of elements in ProfileStatusWindow[] with values
* E2E_P_ERROR
*/
  while (idx < (ConfigPtr->WindowSize))
  {
    if ((uint8)E2E_P_ERROR == (StatePtr->ProfileStatusWindow[idx])) /* polyspace MISRA2012:10.4 RTE:IDP [Justified:Low] "Range check by while-condition" */
    {
      count++;
    }
    else
    {
      /* Do nothing*/
    }
    idx++;
  }

  /* Write the number of elements in ProfileStatusWindow[] with values
  * E2E_P_ERROR
  */
  StatePtr->ErrorCount = count;

  /* Adjust WindowTopIndex */
  if ((StatePtr->WindowTopIndex) == ((ConfigPtr->WindowSize) - 0x01U))
  {
    StatePtr->WindowTopIndex = 0x00U;
  }
  else
  {
    StatePtr->WindowTopIndex++;
  }
  /* End of if-else */

  return;
}

/*******************************************************************************
** Function Name        : E2E_SMClearStatus                                   **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : This function shall clear E2E_SMCheck's             **
**                        ProfileStatus.                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : StatePtr , ConfigPtr                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return Value         : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace:  */

static FUNC(void, E2E_CODE) E2E_SMClearStatus(
    P2VAR(E2E_SMCheckStateType, AUTOMATIC, E2E_APPL_DATA) StatePtr,
    P2CONST(E2E_SMConfigType, AUTOMATIC, E2E_APPL_CONST) ConfigPtr)
{
  /* Local variable to store index of loop */  
  VAR(uint8, AUTOMATIC) idx;

  /* @Trace: SafeE2E_SUD_MF_804 */
  idx = 0x00U;

  /* Clear each element of the ProfileStatusWindow[] array */
  /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  while (idx < (ConfigPtr->WindowSize))
  {
    StatePtr->ProfileStatusWindow[idx] = (uint8)E2E_P_NOTAVAILABLE;
    idx++;
  }

  /* Set OKCount to 0 */
  StatePtr->OkCount = 0x00U;

  /* Set ErrorCount to 0 */
  StatePtr->ErrorCount = 0x00U;

  /* Set WindowTopIndex to 0 */
  StatePtr->WindowTopIndex = 0x00U;
  /* polyspace-end MISRA2012:D4.14 [Justified:Low] "the pointer is check for not null previous branch"*/
  return;
}

#define E2E_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"  /*polyspace MISRA2012:20.1 [Justified:Low] "This include directive is necessary for Memory mapping"*/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
