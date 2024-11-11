/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_Mac.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Mac service of Csm                                            **
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
**                       Function Definitions                                 **
*******************************************************************************/
/*******************************************************************************
** Function Name        : Csm_MacGenerate                                     **
**                                                                            **
** Service ID           : 0x60                                                **
**                                                                            **
** Description          : Uses the given data to perform a MAC generation and **
**                        stores the MAC in the memory location pointed to by **
**                        the MAC pointer                                     **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on the job configuration   **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : jobId : Holds the identifier of the job using the   **
**                                CSM service                                 **
**                        mode : Indicates which operation mode(s) to perfom  **
**                        dataPtr : Contains the pointer to the data for which**
**                                  the MAC shall be computed.                **
**                        dataLength: Contains the number of bytes to be      **
**                                    hashed                                  **
**                                                                            **
** InOut parameter      : macLengthPtr : Holds a pointer to the memory        **
**                          location in which the output length in bytes is   **
**                          stored. On calling this function, this parameter  **
**                          shall contain the size of the buffer provided by  **
**                          macPtr. When the request has finished, the actual **
**                          length of the returned MAC shall be stored        **
**                                                                            **
** Output Parameters    : macPtr : Contains the pointer to the data where the **
**                                 MAC shall be stored                        **
**                                                                            **
** Return parameter     : E_OK : Request successful                           **
**                        E_NOT_OK: Request failed                            **
**                        CRYPTO_E_BUSY: Request failed, service is still busy**
**                        CRYPTO_E_KEY_NOT_VALID: Request failed,             **
**                          the key's state is "invalid"                      **
**                        CRYPTO_E_KEY_SIZE_MISMATCH: Request failed, a key   **
**                          element has the wrong size                        **
**                        CRYPTO_E_KEY_EMPTY: Request failed because of       **
**                          uninitialized source key element                  **
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
     (CSM_PRIMITIVE_MAC_GENERATE_ENABLE == STD_ON))
#define CSM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_CryptoStack_00022 SRS_CryptoStack_00084 SRS_CryptoStack_00100 SRS_CryptoStack_00006 */
FUNC(Std_ReturnType, CSM_CODE) Csm_MacGenerate
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(Crypto_OperationModeType, AUTOMATIC) mode,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) dataPtr,
  VAR(uint32, AUTOMATIC) dataLength,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) macPtr,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) macLengthPtr
)
{
  /* @Trace: Csm_SUD_FUNC_006 */
  Std_ReturnType retVal;
  retVal = Csm_PrvServiceGenerate(jobId, mode, dataPtr, dataLength, macPtr,
    macLengthPtr, CSM_MAC_GENERATE_SID);
  return retVal;
}
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Csm_MacVerify                                       **
**                                                                            **
** Service ID           : 0x61                                                **
**                                                                            **
** Description          : Verifies the given MAC by comparing if the MAC is   **
**                        generated with the given data                       **
**                                                                            **
** Sync/Async           : Sync or Async, dependent on the job configuration   **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : jobId : Holds the identifier of the job using the   **
**                                CSM service                                 **
**                        mode : Indicates which operation mode(s) to perfom  **
**                        dataPtr : Contains the pointer to the data for which**
**                                  the MAC shall be verified                 **
**                        dataLength: Contains the number of data bytes for   **
**                                    which the MAC shall be verified.        **
**                        macPtr: Holds a pointer to the MAC to be verified   **
**                        macLength: Contains the MAC length in BITS to be    **
**                                   verified                                 **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : verifyPtr : Holds a pointer to the memory location, **
**                                    which will hold the result of the MAC   **
**                                    verification                            **
**                                                                            **
** Return parameter     : E_OK : Request successful                           **
**                        E_NOT_OK: Request failed                            **
**                        CRYPTO_E_BUSY: Request failed, service is still busy**
**                        CRYPTO_E_KEY_NOT_VALID: Request failed,             **
**                          the key's state is "invalid"                      **
**                        CRYPTO_E_KEY_SIZE_MISMATCH: Request failed, a key   **
**                          element has the wrong size                        **
**                        CRYPTO_E_KEY_EMPTY: Request failed because of       **
**                          uninitialized source key element                  **
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
     (CSM_PRIMITIVE_MAC_VERIFY_ENABLE == STD_ON))
#define CSM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_CryptoStack_00022 */
FUNC(Std_ReturnType, CSM_CODE) Csm_MacVerify
(
  VAR(uint32, AUTOMATIC) jobId,
  VAR(Crypto_OperationModeType, AUTOMATIC) mode,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) dataPtr,
  VAR(uint32, AUTOMATIC) dataLength,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) macPtr,
  VAR(uint32, CSM_CONST) macLength,
  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA) verifyPtr
)
{
  /* @Trace: Csm_SUD_FUNC_007 */
  Std_ReturnType retVal;
  retVal = Csm_PrvServiceVerify(jobId, mode, dataPtr, dataLength, macPtr,
    macLength, verifyPtr, CSM_MAC_VERIFY_SID);
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
