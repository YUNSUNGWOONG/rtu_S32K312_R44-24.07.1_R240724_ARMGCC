/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_IntFunc.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Internal function header file of CSM                          **
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
** 1.0.1.0   10-Mar-2021   TamTV6       Fix #17725                            **
** 1.0.3.0   12-Aug-2022   DienTC1      #594                                  **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/

#ifndef CSM_INT_FUNC_H
#define CSM_INT_FUNC_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm_IntTypes.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      File version check                                    **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                         Global Data Types                                  **
*******************************************************************************/

/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/
/* Get queue by channel ID */
#define CSM_START_SEC_CODE
#include "MemMap.h"
extern Csm_QueueType* Csm_PrvGetQueueByChannelId(uint32 channelId);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* To check whether queue is empty */
#define CSM_START_SEC_CODE
#include "MemMap.h"
extern boolean Csm_PrvIsQueueEmpty(const Csm_QueueType *ptrQueue);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* Put job to queue, return CRYPTO_E_QUEUE_FULL if queue is full */
#define CSM_START_SEC_CODE
#include "MemMap.h"
extern Std_ReturnType Csm_PrvEnqueue
(
  Csm_QueueType *ptrQueue, 
  Csm_JobType *ptrJob
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* Get the highest priority job and remove it from queue, return NULL_PTR if
   queue is empty */
#define CSM_START_SEC_CODE
#include "MemMap.h"
extern Csm_JobType* Csm_PrvDequeue(Csm_QueueType *ptrQueue);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* Return TRUE if job is already presence in queue, otherwise return FALSE */
#define CSM_START_SEC_CODE
#include "MemMap.h"
extern boolean Csm_PrvJobQueueExist
(
  const Csm_QueueType *ptrQueue, 
  const Csm_JobType *ptrJob, 
  uint32 *indexPtr
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* To remove job from queue */
#define CSM_START_SEC_CODE
#include "MemMap.h"
extern void Csm_PrvJobQueueRemove
(
  Csm_QueueType *ptrQueue, 
  const Csm_JobType *ptrJob
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* Check if job has the highest priority in queue */
#define CSM_START_SEC_CODE
#include "MemMap.h"
extern boolean Csm_PrvIsHighestPrio
(
  const Csm_QueueType *ptrQueue, 
  const Csm_JobType *ptrJob
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* Validate mode paramameter before passing to
   Crypto_JobPrimitiveInputOutputType */
#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_PrvJobModeValidate
(
  CONSTP2CONST(Csm_JobType, AUTOMATIC, CSM_APPL_CONST) ptrCsmJob,
  Crypto_OperationModeType mode
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* Clear job state (buffer, length, etc...) in
   Crypto_JobPrimitiveInputOutputType */
#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CSM_CODE) Csm_PrvClearJobState
(
  CONSTP2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) ptrCryptoJob
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* To provide general behaviour for all Csm_<Service> function */
#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_PrvProcessService
(
  CONSTP2VAR(Csm_JobType, AUTOMATIC, CSM_APPL_DATA) ptrCsmJob,
  uint8 serviceId
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* To get Job Pointer from list of configured jobs */
#define CSM_START_SEC_CODE
#include "MemMap.h"
/* polyspace-begin MISRA-C3:20.7 [Justified:Low] "Marco P2VAR is defined in Generic source. It is out of scope." */
extern FUNC(P2VAR(Csm_JobType, AUTOMATIC, CSM_APPL_DATA), CSM_CODE) \
                                        Csm_PrvGetCsmJobPtr(uint32 jobId);
/* polyspace-end MISRA-C3:20.7 */
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* Common function for Csm_Hash, Csm_MacGenerate, Csm_Encrypt, Csm_Decrypt,
   Csm_SignatureGenerate */
#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_PrvServiceGenerate
(
  uint32 jobId, Crypto_OperationModeType mode,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) ptrInput, uint32 inputLength,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) ptrOutput,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) ptrOutputLength,
  uint8 serviceId
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* Common function for Csm_MacVerify, Csm_SignatureVerify */
#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_PrvServiceVerify
(
  uint32 jobId, Crypto_OperationModeType mode,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) ptrInput, uint32 inputLength,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) ptrSecondaryInput,
  const uint32 secondaryInputLength,
  P2VAR(Crypto_VerifyResultType, AUTOMATIC, CSM_APPL_DATA) ptrVerify,
  uint8 serviceId
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* To validate input pointers and their respective data lengths */
#define CSM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_CryptoStack_00088 */
extern FUNC(Std_ReturnType, CSM_CODE) Csm_PrvValidateInputPtr
(
  P2CONST(Crypto_JobRedirectionInfoType, AUTOMATIC, CSM_APPL_DATA) \
                                                      ptrJobRedirectionInfoRef,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) ptrInput, uint32 inputLength,
  uint8 serviceId,
  Crypto_InputOutputRedirectionConfigType inOutRedirectionConfig
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* To validate output pointers and their respective data lengths */
#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_PrvValidateOutputPtr
(
  P2CONST(Crypto_JobRedirectionInfoType, AUTOMATIC, CSM_APPL_DATA) \
                                                      ptrJobRedirectionInfoRef,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) ptrOutput,
  P2CONST(uint32, AUTOMATIC, CSM_APPL_DATA) ptrOutputLength, uint8 serviceId,
  Crypto_InputOutputRedirectionConfigType inOutRedirectionConfig
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* Common development error checking for key management interface */
#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_PrvKeyManComDevErrCheck
(
  VAR(uint8, AUTOMATIC) serviceId,
  VAR(uint32, AUTOMATIC) keyId,
  VAR(uint32, AUTOMATIC) targetKeyId,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) ptrInput,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_DATA) ptrOutput,
  P2CONST(uint32, AUTOMATIC, CSM_APPL_DATA) ptrOutputLength
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* Common processing function for job-based key management interface */
#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CSM_CODE) Csm_PrvJobKeyManComProcess
(
  VAR(uint8, AUTOMATIC) serviceId,
  VAR(uint32, AUTOMATIC) jobId,
  VAR(uint32, AUTOMATIC) keyId,
  VAR(uint32, AUTOMATIC) targetKeyId,
  P2CONST(uint8, AUTOMATIC, CSM_APPL_CONST) ptrInput,
  VAR(uint32, AUTOMATIC) inputLength,
  P2VAR(uint8, AUTOMATIC, CSM_APPL_DATA) ptrOutput,
  P2VAR(uint32, AUTOMATIC, CSM_APPL_DATA) ptrOutputLength
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"
/* Copy JobRedirectionInfo from ROM to RAM */
#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CSM_CODE) Csm_PrvCopyJobRedirectionInfo
(
  P2VAR(Crypto_JobRedirectionInfoType, AUTOMATIC, CSM_APPL_DATA) ptrDest,
  P2CONST(Crypto_JobRedirectionInfoType, AUTOMATIC, CSM_APPL_CONST) ptrSource
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#define CSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CSM_CODE) Csm_PrvCallbackNotification
(
  VAR(uint8, AUTOMATIC) serviceId,
  P2CONST(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) job,
  VAR(Csm_ResultType, AUTOMATIC) result
);
#define CSM_STOP_SEC_CODE
#include "MemMap.h"

#endif
/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
