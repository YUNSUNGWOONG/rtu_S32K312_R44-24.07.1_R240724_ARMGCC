/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_Callback.c                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Callback notification of Csm                                  **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0.0   15-Jan-2021   JH Lim       Initial version                       **
** 1.0.1.0   10-Mar-2021   TamTV6       Fix #17725, Add trace SUD             **
** 1.0.3.0   12-Aug-2022   DienTC1      #594                                  **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_IntFunc.h"

/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/
/*******************************************************************************
** Function Name        : Csm_CallbackNotification                            **
**                                                                            **
** Service ID           : 0x70                                                **
**                                                                            **
** Description          : This service provides callback notification to a    **
**                        pre-comfigured callback function                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : job : Holds the indentifier of the job              **
**                              to be canceled                                **
**                        result : Contains the result of the cryptographic   **
**                                 operation.                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Csm module should be initialized                    **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Csm_Initialisation                                  **
**                        Csm_ApplicationCallback                             **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Det_ReportError                                     **
*******************************************************************************/
#if ((CSM_JOB_PROCESSING_ENABLE == STD_ON) && \
     (CSM_PROCESSING_MODE_ASYNC_ENABLE == STD_ON))
#define CSM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00359 SRS_BSW_00360 SRS_CryptoStack_00082 */
FUNC(void, CSM_CODE) Csm_CallbackNotification
(
  P2CONST(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job,
  VAR(Csm_ResultType, AUTOMATIC) result
)
{
  if (FALSE == Csm_Initialisation)
  {
    /* @Trace: Csm_SUD_FUNC_150 */
    #if CSM_DEV_ERROR_DETECT == STD_ON
    (void)Det_ReportError(CSM_MODULE_ID, CSM_INSTANCE_ID,
    CSM_CALLBACK_NOTIFICATION_SID, CSM_E_UNINIT);
    #endif
  }
  else
  {
    /* @Trace: Csm_SUD_FUNC_151 */
    Csm_PrvCallbackNotification(CSM_CALLBACK_NOTIFICATION_SID, job, result);
  }
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
