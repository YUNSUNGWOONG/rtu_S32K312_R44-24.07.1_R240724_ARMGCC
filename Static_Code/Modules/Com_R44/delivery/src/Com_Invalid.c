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
**  SRC-MODULE: Com_Invalid.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of invalidate and update functions                  **
**              functionality.                                                **
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
** 1.1.3.1   21-Jun-2022   SMKwon      CP44-109                               **
** 1.1.1     25-Mar-2022   PhuPV10     R44-Redmine #25573 #25073              **
** 1.1.0     10-Feb-2022   PhucNHM     R44-Redmine #19316 #23495 #23725       **
**                                                 #23982 #24211              **
** 1.0.1     28-Sep-2021   DuyNGB      R44-Redmine #20139                     **
** 1.0.0     04-Dec-2020   SMKwon      Initial Version                        **
*******************************************************************************/
/* polyspace-begin RTE:IDP [Not a defect:Low] "NULL pointer was checked by generator" */
/* polyspace-begin MISRA-C3:D4.14 [Not a defect:Low] "Tainted pointer is assured by caller which was checked by generator" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Com.h"          /* Com header file */
#include "Com_Invalid.h"  /* Com Invalid header file */

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Com_Invalid_8                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs invalidation check on the    **
**                        signal and returns true if signal is invalid.       **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpSource, LpTarget, LddSize                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_Invalid_8
(P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
  P2CONST(void, AUTOMATIC, COM_CONST) LpTarget,
  PduLengthType LddSize)
{
  /* @Trace: Com_SUD_API_00169 */
  boolean LblReturnValue;
  /* Initialize return value to true */
  LblReturnValue = COM_TRUE;
  /* Check whether invalid data is not equal to signal data */
  if((*(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpTarget) !=
                      (*(P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSource))
  {
    /* @Trace: Com_SUD_API_00170 */
    /* Set return value to false */
    LblReturnValue = COM_FALSE;
  }

  /* @Trace: Com_SUD_API_00171 */
  COM_UNUSED(LddSize);
  /* Return value */
  return(LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Invalid_16                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs invalidation check on the    **
**                        signal and returns true if signal is invalid.       **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpSource, LpTarget, LddSize                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_Invalid_16
(P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
  P2CONST(void, AUTOMATIC, COM_CONST) LpTarget,
  PduLengthType LddSize)
{
  /* @Trace: Com_SUD_API_00172 */
  boolean LblReturnValue;
  /* Initialize return value to true */
  LblReturnValue = COM_TRUE;
  /* Check whether invalid data is not equal to signal data */
  if((*(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpTarget) !=
                     (*(P2CONST(uint16, AUTOMATIC, COM_CONST)) LpSource))
  {
    /* @Trace: Com_SUD_API_00173 */
    /* Set return value to false */
    LblReturnValue = COM_FALSE;
  }

  /* @Trace: Com_SUD_API_00174 */
  COM_UNUSED(LddSize);
  /* Return value */
  return(LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Invalid_32                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs invalidation check on the    **
**                        signal and returns true if signal is invalid.       **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpSource, LpTarget, LddSize                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_Invalid_32
(P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
  P2CONST(void, AUTOMATIC, COM_CONST) LpTarget,
  PduLengthType LddSize)
{
  /* @Trace: Com_SUD_API_00175 */
  boolean LblReturnValue;
  /* Initialize return value to true */
  LblReturnValue = COM_TRUE;
  /* Check whether invalid data is not equal to signal data */
  if((*(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpTarget) !=
                     (*(P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSource))
  {
    /* @Trace: Com_SUD_API_00176 */
    /* Set return value to false */
    LblReturnValue = COM_FALSE;
  }

  /* @Trace: Com_SUD_API_00177 */
  COM_UNUSED(LddSize);
  /* Return value */
  return(LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Invalid_64                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs invalidation check on the    **
**                        signal and returns true if signal is invalid.       **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpSource, LpTarget, LddSize                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(boolean, COM_CODE) Com_Invalid_64
(P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
  P2CONST(void, AUTOMATIC, COM_CONST) LpTarget,
  PduLengthType LddSize)
{
  /* @Trace: Com_SUD_API_00178 */
  P2CONST(uint32, AUTOMATIC, COM_CONST) LpDest;
  P2CONST(uint32, AUTOMATIC, COM_CONST) LpSrc;
  boolean LblReturnValue;
  uint16 LusBufferIndex;

  LusBufferIndex = (uint16)COM_ZERO;
  LpDest = (P2CONST(uint32, AUTOMATIC, COM_CONST)) LpTarget;
  LpSrc = (P2CONST(uint32, AUTOMATIC, COM_CONST)) LpSource;
  /* Set return value to false */
  LblReturnValue = COM_FALSE;

  /* Check whether invalid data is not equal to signal data */
  if((LpDest[LusBufferIndex]) == (LpSrc[LusBufferIndex]))
  {
    /* @Trace: Com_SUD_API_00179 */
    LusBufferIndex++;
    if((LpDest[LusBufferIndex]) == (LpSrc[LusBufferIndex]))
    {
      /* @Trace: Com_SUD_API_00180 */
      LblReturnValue = COM_FALSE;
    }
  }

  /* @Trace: Com_SUD_API_00181 */
  COM_UNUSED(LddSize);
  /* Return value */
  return(LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_Invalid_NBytes                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function performs invalidation check on the    **
**                        signal and returns true if signal is invalid.       **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : LpSource, LpTarget, LddSize                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LblReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : None                       **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(boolean, COM_CODE) Com_Invalid_NBytes
(P2CONST(void, AUTOMATIC, COM_CONST) LpSource,
                        P2CONST(void, AUTOMATIC, COM_CONST) LpTarget,
                                                          PduLengthType LddSize)
{
  /* @Trace: Com_SUD_API_00182 */
  boolean LblReturnValue;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpTargetPtr;
  P2CONST(uint8, AUTOMATIC, COM_CONST) LpSourcePtr;
  uint16 LusBufferIndex;
  PduLengthType LddSigSize;

  LusBufferIndex = (uint16)COM_ZERO;
  /* Initialize return value to true */
  LblReturnValue = COM_TRUE;
  /* Get the pointer to destination buffer */
  LpTargetPtr = (P2CONST(uint8, AUTOMATIC, COM_CONST)) LpTarget;
  /* Get the pointer to source buffer */
  LpSourcePtr = (P2CONST(uint8, AUTOMATIC, COM_CONST)) LpSource;
  /* Get the size of this signal */
  LddSigSize = LddSize;
  
  /* Loop to check whether the data is invalid or not, based on signal size */
  do
  {
    /* @Trace: Com_SUD_API_00183 */
    /* Decrement signal size */
    LddSigSize--;
    /* Check whether invalid data is not equal to signal data */
    if(LpTargetPtr[LusBufferIndex] != LpSourcePtr[LusBufferIndex])
    {
      /* @Trace: Com_SUD_API_00184 */
      /* Set return value to false */
      LblReturnValue = COM_FALSE;
      /* Set signal size to zero */
      LddSigSize = (PduLengthType)COM_ZERO;
    }
    /* @Trace: Com_SUD_API_00185 */
    LusBufferIndex++;
  }while(LddSigSize != (PduLengthType)COM_ZERO);

  /* Return value */
  /* @Trace: Com_SUD_API_00186 */
  return(LblReturnValue);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace-end RTE:IDP [Not a defect:Low] "NULL pointer was checked by generator" */
/* polyspace-end MISRA-C3:D4.14 [Not a defect:Low] "Tainted pointer is assured by caller which was checked by generator" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
