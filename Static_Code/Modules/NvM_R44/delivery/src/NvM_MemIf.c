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
**  SRC-MODULE: NvM_MemIf.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : Callback Function Definitions of NVRAM module                 **
**              NvM_JobEndNotification                                        **
**              NvM_JobErrorNotification                                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date          By          Description                          **
********************************************************************************
** 0.0.1       06-Dec-2019    KienHT11    Initial version                     **
** 0.0.2       04-May-2020    VinhLV5     Update traceability, apply          **
**                                        new v cycle, Fix Misra              **
** 0.0.3       24-Jul-2020    VinhLV5     R44-Redmine #9958                   **
** 1.0.2       27-Aug-2021    JH Lim      R44-Redmine #19726                  **
** 1.1.1.1     29-Jun-2022    SH Park     Improvement mobilegence             **
**                                          Classic <CP44-221>                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "NvM.h"
#include "NvM_IntTypes.h"
#include "NvM_MemIf.h"
#include "NvM_Globals.h"
/* @Trace: NvM_SUD_MACRO_033 */
#if(STD_OFF == NVM_POLLING_MODE)

#define NVM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : NvM_JobEndNotification                                **
**                                                                            **
** Service ID         : 0x11                                                  **
**                                                                            **
** Description        : Function to be used by the subsequent memory driver   **
**                      to signal end of job without error.                   **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Reentrancy         : Non-Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s)  : NvM_JobResultLowLevel           **
**                                                                            **
**                      Function(s) invoked : None                            **
*******************************************************************************/
/* @Trace: SRS_BSW_00333 SRS_BSW_00360 */
/* The callback function is used by the underlaying memory abstraction 
 * to signal end of job without error
 */
FUNC(void, NVM_CODE) NvM_JobEndNotification(void)
{
  /* @Trace: NvM_SUD_FUNC_334 */
  /* Indicate job is completed without error */
  NvM_JobResultLowLevel = NVM_REQ_OK;
}

/*******************************************************************************
** Function Name      : NvM_JobErrorNotification                              **
**                                                                            **
** Service ID         : 0x12                                                  **
**                                                                            **
** Description        : Function to be used by the subsequent memory driver   **
**                      to signal end of job with error.                      **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Reentrancy         : Non-Reentrant                                         **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return parameter   : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s)  : NvM_JobResultLowLevel           **
**                                                                            **
**                      Function(s) invoked : None                            **
*******************************************************************************/
/* @Trace: SRS_BSW_00333 SRS_BSW_00360 */
/* The callback function is used by the underlaying memory abstraction 
 * to signal end of job with error
 */
FUNC(void, NVM_CODE) NvM_JobErrorNotification(void)
{
  /* @Trace: NvM_SUD_FUNC_335 */
  /* Indicate job is completed with error */
  NvM_JobResultLowLevel = NVM_REQ_NOT_OK;
}

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

#endif
