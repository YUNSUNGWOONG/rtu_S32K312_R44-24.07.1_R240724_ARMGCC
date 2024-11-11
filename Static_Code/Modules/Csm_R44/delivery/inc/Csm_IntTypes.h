/*******************************************************************************
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Csm_IntTypes.h                                                **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CSM                                                   **
**                                                                            **
**  PURPOSE   : Internal type header file for Csm module                      **
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
** 1.0.1.0   10-Mar-2021   TamTV6       Fix #17725, #17942, Add trace SUD     **
** 1.0.3.0   12-Aug-2022   DienTC1      #594                                  **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
#ifndef CSM_INT_TYPES_H
#define CSM_INT_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Csm.h"
#include "CryIf.h"
#include "Det.h"
#include "Rte_Csm.h"
#include "SchM_Csm.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      File version check                                    **
*******************************************************************************/

/*******************************************************************************
**                         Global Data Types                                  **
*******************************************************************************/
/* Csm port type */
typedef enum
{
  /* Port is not used */
  CRYPTO_USE_FNC = 0x0U,
  /* Port is used */
  CRYPTO_USE_PORT,
  /* DATA_REFERENCE is used */
  CRYPTO_USE_PORT_OPTIMIZED
} Csm_JobInterfaceUsePortType;

/* @Trace: Csm_SUD_DATATYPE_018 */
/* CSM job type data structure */
typedef struct
{
  /* Respective CryIf channel ID */
  const uint32 JobCryIfChannelId;
  /* Pointer to Crypto job */
  CONSTP2VAR(Crypto_JobType, AUTOMATIC, CSM_APPL_DATA) CryptoJob;
  /* Indicate this job is passed to driver */
  boolean InDriver;
  /* CsmJobInterfaceUsePort */
  const Csm_JobInterfaceUsePortType PortType;
  /* Pointer to Rte callback notification */
  Csm_RteCallbackType RteCallbackNotification;
  /* pointer to JobRedirectionInfo located in ROM */
  CONSTP2CONST(Crypto_JobRedirectionInfoType, AUTOMATIC, CSM_APPL_CONST) \
                                                      PtrJobRedirectionInfoRef;
} Csm_JobType;

/* @Trace: Csm_SUD_DATATYPE_019 */
/* CSM queue slot data structure */
typedef struct
{
  /* Serial number */
  uint32 SerialNo;
  /* Pointer to Csm job */
  P2VAR(Csm_JobType, AUTOMATIC, CSM_APPL_DATA) CsmJob;
} Csm_QueueSlotType;

/* @Trace: Csm_SUD_DATATYPE_020 */
/* CSM queue type data structure */
typedef struct
{
  /* Respective CryIf channel ID */
  const uint32 CryIfChannelId;
  /* CSM queue maximum size */
  const uint32 MaxQueueSize;
  /* CSM queue current size */
  uint32 CurrentQueueSize;
  /* CSM queue counter */
  uint32 Counter;
  /* Pointer to CSM queue buffer array */
  CONSTP2VAR(Csm_QueueSlotType, AUTOMATIC, CSM_APPL_DATA) QueueBuf;
} Csm_QueueType;

/* @Trace: Csm_SUD_DATATYPE_021 */
/* CSM key type data structure */
typedef struct
{
  /* Identifier of the Csm key */
  const uint32 CsmKeyId;
  /* Identifier of the corresponding CryIf key */
  const uint32 CryIfKeyId;
} Csm_KeyType;

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if (CSM_JOB_PROCESSING_ENABLE == STD_ON)
#define CSM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* @Trace: Csm_SUD_GLOBALVAR_002 */
extern VAR(Csm_JobType, CSM_VAR_INIT) Csm_JobList[CSM_TOTAL_CONFIGURED_JOB];
#define CSM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#if (CSM_QUEUE_OPERATION_ENABLE == STD_ON)
#define CSM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* @Trace: Csm_SUD_GLOBALVAR_003 */
/* By passed "80 columns" coding rule due to fix Polyspace defect */
extern VAR(Csm_QueueType, CSM_VAR_INIT) Csm_QueueList [CSM_TOTAL_CONFIGURED_QUEUE];
#define CSM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#if (CSM_APPLICATION_CALLBACK_ENABLE == STD_ON)
#define CSM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* @Trace: Csm_SUD_GLOBALVAR_005 */
/* By passed "80 columns" coding rule due to fix Polyspace defect */
extern VAR(Csm_ApplicationCallbackType, CSM_VAR_INIT) Csm_ApplicationCallback[CSM_TOTAL_APPLICATION_CALLBACK];
#define CSM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#define CSM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* @Trace: Csm_SUD_GLOBALVAR_001 */
extern VAR(boolean, CSM_VAR_INIT) Csm_Initialisation;
#define CSM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#if (CSM_KEY_MANAGEMENT_ENABLE == STD_ON)
#define CSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* @Trace: Csm_SUD_GLOBALDATA_001 SRS_CryptoStack_00008 */
extern CONST(Csm_KeyType, CSM_CONST) Csm_KeyList[CSM_TOTAL_CONFIGURED_KEY];
#define CSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if (CSM_KEY_MANAGEMENT_ENABLE == STD_ON)
#define CSM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* @Trace: Csm_SUD_GLOBALVAR_004 */
extern VAR(uint16, CSM_VAR_INIT) Csm_KeyManIsProcessing;
#define CSM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"
#endif

#endif

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
