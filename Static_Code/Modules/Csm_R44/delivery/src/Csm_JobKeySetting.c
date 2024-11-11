/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_JobKeySetting.c                                           **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Job key setting interface of Csm                              **
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
** 1.0.1.0   10-Mar-2021   TamTV6       Add trace SUD                         **
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
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : Csm_JobKeySetValid                                  **
**                                                                            **
** Service ID           : 0x7a                                                **
**                                                                            **
** Description          : Stores the key if necessary and sets the key state  **
**                        of the key identified by keyId to valid             **
**                                                                            **
** Sync/Async           : Sync or Async, depending on the job configuration   **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : jobId: Holds the identifier of the job using the    **
**                               CSM service                                  **
**                        keyId: Holds the identifier of the key for which a  **
**                               new material shall be validated              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : E_OK: Request successful                            **
**                        E_NOT_OK: Request failed                            **
**                        CRYPTO_E_BUSY: Request failed, Crypro Driver Object **
**                                       is busy                              **
**                                                                            **
** Preconditions        : Csm module should be initialized                    **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_PrvJobKeyManComProcess                          **
**                                                                            **
*******************************************************************************/
#if ((CSM_JOB_PROCESSING_ENABLE == STD_ON) && \
     (CSM_PRIMITIVE_JOB_KEY_SET_VALID_ENABLE == STD_ON))
#define CSM_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CSM_CODE) Csm_JobKeySetValid
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(uint32, AUTOMATIC) keyId
)
{
  /* @Trace: Csm_SUD_FUNC_130 */
  Std_ReturnType retVal;
  /* Target CryIf key ID set to 0. Input pointer and input length set to
    NULL_PTR and 0 respectively. Output pointer and output length pointer set
    to NULL_PTR */
  retVal = Csm_PrvJobKeyManComProcess(CSM_JOB_KEY_SET_VALID_SID, jobId, keyId, \
    0U, NULL_PTR, 0U, NULL_PTR, NULL_PTR);
  return retVal;
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
