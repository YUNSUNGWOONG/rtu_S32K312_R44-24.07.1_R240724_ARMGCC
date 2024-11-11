/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_Hash.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Hash service of Csm                                           **
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
**                       Global Data                                          **
*******************************************************************************/

/*******************************************************************************
**                       Function Definitions                                 **
*******************************************************************************/
/*******************************************************************************
** Function Name        : Csm_Hash                                            **
**                                                                            **
** Service ID           : 0x5D                                                **
**                                                                            **
** Description          : Uses the given data to perform the hash calculation **
**                        and stores the hash                                 **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on the job configuration   **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : jobId : Holds the identifier of the job using the   **
**                                CSM service                                 **
**                        mode : Indicates which operation mode(s) to perfom  **
**                        dataPtr : Contains the pointer to the data for      **
**                                  which the hash shall be computed          **
**                        dataLength : Contains the number of bytes to be     **
**                                     hashed                                 **
**                                                                            **
** InOut parameter      : resultLengthPtr : Holds a pointer to the memory     **
**                          location in which the output length in bytes is   **
**                          stored. On calling this function, this parameter  **
**                          shall contain the size of the buffer provided by  **
**                          resultPtr. When the request has finished, the     **
**                          actual length of the returned value shall be      **
**                          stored                                            **
**                                                                            **
** Output Parameters    : resultPtr : Contains the pointer to the data where  **
**                                    the hash value shall be stored          **
**                                                                            **
** Return parameter     : E_OK : Request successful                           **
**                        E_NOT_OK: Request failed                            **
**                        CRYPTO_E_BUSY: Request failed, service is still busy**
**                          the key's state is "invalid"                      **
**                                                                            **
** Preconditions        : Csm module should be initialized                    **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) invoked :                               **
**                        Csm_PrvServiceGenerate                              **
*******************************************************************************/
/* @Trace: SRS_CryptoStack_00007 */
#if ((CSM_JOB_PROCESSING_ENABLE == STD_ON) && \
     (CSM_PRIMITIVE_HASH_ENABLE == STD_ON))
#define CSM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_CryptoStack_00024 SRS_CryptoStack_00006 */
FUNC(Std_ReturnType, CSM_CODE) Csm_Hash
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(Crypto_OperationModeType, AUTOMATIC) mode,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) dataPtr,
  VAR(uint32, AUTOMATIC) dataLength,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) resultPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) resultLengthPtr
)
{
  /* @Trace: Csm_SUD_FUNC_005 */
  Std_ReturnType retVal;
  retVal = Csm_PrvServiceGenerate(jobId, mode, dataPtr, dataLength, resultPtr,
                          resultLengthPtr, CSM_HASH_SID);
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
