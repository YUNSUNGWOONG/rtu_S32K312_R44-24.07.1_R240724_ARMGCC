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
**  SRC-MODULE: NvM_IntFunc.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : Provision of Macros and API Prototype Declarations            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date           By          Description                         **
********************************************************************************
** 0.0.1       19-Dec-2019    VinhLV5     Initial version                     **
** 0.0.2       04-May-2020    VinhLV5     Update traceability, apply          **
**                                        new v cycle, Fix Misra              **
** 0.0.3       24-Jul-2020    VinhLV5     R44-Redmine #9958                   **
** 1.0.2       27-Aug-2021    JH Lim      R44-Redmine #19726                  **
** 1.1.1.1     29-Jun-2022    SH Park     Improvement mobilegence             **
**                                          Classic <CP44-221>                **
** 1.1.2       12-Aug-2022    SH Park     Improvement mobilegence             **
**                                          Classic <CP44-76>                 **
*******************************************************************************/

#ifndef NVM_INTFUNC_H
#define NVM_INTFUNC_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define NVM_START_SEC_CODE
#include "MemMap.h"

typedef union
{
  uint8   u_uint8[2];
  uint16  u_uint16;
}NvM_DataWordType;

#if((NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) || \
  (0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS) || \
  (0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS))

#if(((STD_ON == NVM_CRC16_SUPPORT) && (STD_ON == NVM_CRC_SUPPORT)) || \
  (STD_ON == NVM_STATIC_ID_CHECK))
NVM_EXTERN(FUNC(void, NVM_CODE) NvM_ByteOrderDispatch16(
  VAR(uint16, AUTOMATIC) val16);)
#if((STD_ON == NVM_CRC16_SUPPORT) && (STD_ON == NVM_CRC_SUPPORT))
NVM_EXTERN(FUNC(uint16, NVM_CODE) NvM_ReOrderByte16(
  CONSTP2CONST(uint8, AUTOMATIC, NVM_APPL_CONST) varCrcData);)
#endif
#endif

#if((STD_ON == NVM_CRC32_SUPPORT) && (STD_ON == NVM_CRC_SUPPORT))
NVM_EXTERN(FUNC(void, NVM_CODE) NvM_ByteOrderDispatch32(
  VAR(uint32, AUTOMATIC) val32);)
NVM_EXTERN(FUNC(uint32, NVM_CODE) NvM_ReOrderByte32(
  CONSTP2CONST(uint8, AUTOMATIC, NVM_APPL_CONST) varCrcData);)
#endif

#if(STD_ON == NVM_CRC_SUPPORT)
NVM_EXTERN(FUNC(void, NVM_CODE) NvM_CalculateCRC(
  P2VAR(uint8, AUTOMATIC, NVM_APPL_CONST) ptrCrcCalAddrin,
  P2VAR(uint8, AUTOMATIC, NVM_VAR_NOINIT) ptrRamBlkData);)
#endif

#if((STD_ON == NVM_STATIC_ID_CHECK) || (STD_ON == NVM_CRC_SUPPORT))
NVM_EXTERN(FUNC(void, NVM_CODE) NvM_CalculateCRCStaticID(void);)
NVM_EXTERN(FUNC(Std_ReturnType, NVM_CODE) NvM_CompareCRCSID(void);)
#endif

/* NvM_CalcBlkNumber Prototype Declarations */
NVM_EXTERN(FUNC(uint16, NVM_CODE) NvM_CalcBlkNumber(void);)
/* NvM_EndProcessBlock Prototype Declarations */
NVM_EXTERN(FUNC(void, NVM_CODE) NvM_EndProcessBlock(
  VAR(NvM_RequestResultType, AUTOMATIC) requestResult);)

#if(STD_ON == UPDATE_RAM_STATUS_ENABLE)
/* NvM_UpdateRamStateStatus Prototype Declarations */
NVM_EXTERN(FUNC(void, NVM_CODE) NvM_UpdateRamStateStatus(
  VAR(uint8, AUTOMATIC) status);)
#endif

#if((STD_ON == NVM_CRC_SUPPORT) && \
  (STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM))

#if((0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS) || \
  (0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS) || (NVM_API_CONFIG_CLASS != \
  NVM_API_CONFIG_CLASS_1))
NVM_EXTERN(FUNC(void, NVM_CODE) NvM_CalculateCrcOffset(
  VAR(NvM_BlockIdType, AUTOMATIC) blockId);)
#endif

NVM_EXTERN(FUNC(boolean, NVM_CODE) NvM_CompareCrcMechanism(
  VAR(uint8, AUTOMATIC) varCrcLength,
  VAR(uint8, AUTOMATIC) varCRCSIDIndex);)
NVM_EXTERN(FUNC(void, NVM_CODE) NvM_StoreCrcOffset(void);)
#endif

#if((STD_ON == NVM_DYNAMIC_CONFIGURATION) && \
  (0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS))
NVM_EXTERN(FUNC(void, NVM_CODE) NvM_CheckConfigId(void);)
#endif

#if (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
NVM_EXTERN(FUNC(boolean, NVM_CODE) NvM_ScanQueue(void);)
NVM_EXTERN(FUNC(boolean, NVM_CODE) NvM_StdQueueRead(
  CONSTP2VAR(NvM_JobQueue, AUTOMATIC, NVM_APPL_DATA) ptrDataPtr);)
NVM_EXTERN(FUNC(void, NVM_CODE) NvM_StdQueuePosClear(void);)
#endif

#if(STD_ON == NVM_JOB_PRIO)
NVM_EXTERN(FUNC(void, NVM_CODE) NvM_ImmQueuePosClear(void);)
NVM_EXTERN(FUNC(boolean, NVM_CODE) NvM_ImmQueueRead(
  CONSTP2VAR(NvM_JobQueue, AUTOMATIC, NVM_APPL_DATA) ptrDataPtr);)
NVM_EXTERN(FUNC(void, NVM_CODE) NvM_ProcessImmdWrite(void);)
#endif

#if((NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS) && \
  (0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS))
NVM_EXTERN(FUNC(void, NVM_CODE) NvM_FirstInitAllProcess(void);)
#endif

#if(0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS)
NVM_EXTERN(FUNC(void, NVM_CODE) NvM_ReadAllProcess(void);)
#endif

#if(0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS)
NVM_EXTERN(FUNC(void, NVM_CODE) NvM_WriteAllProcess(void);)
#endif

#if(STD_ON == NVM_WRITE_VERIFICATION)
NVM_EXTERN(FUNC(void, NVM_CODE) NvM_ProcessWriteVerify(void);)
#endif

NVM_EXTERN(FUNC(void, NVM_CODE) NvM_WriteProcessNvBlock(void);)
NVM_EXTERN(FUNC(void, NVM_CODE) NvM_SubWriteProcessNvBlock(void);)
NVM_EXTERN(FUNC(void, NVM_CODE) NvM_WriteNvBlockProcess(void);)

NVM_EXTERN(FUNC(void, NVM_CODE) NvM_RestoreBlockProcess(void);)

NVM_EXTERN(FUNC(void, NVM_CODE) NvM_ProcessReadStart(void);)
NVM_EXTERN(FUNC(void, NVM_CODE) NvM_ProcessReadNvBlock(void);)
NVM_EXTERN(FUNC(void, NVM_CODE) NvM_ProcessReadNotOkJob(
  VAR(Std_ReturnType, AUTOMATIC) status,
  VAR(MemIf_JobResultType, AUTOMATIC) memStatusin);)
NVM_EXTERN(FUNC(void, NVM_CODE) NvM_ProcessReadOkJob(void);)

#if((0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS) || \
  (0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS) || (NVM_API_CONFIG_CLASS != \
  NVM_API_CONFIG_CLASS_1))
/* NvM_UpdateGlobalVars Prototype Declarations */
NVM_EXTERN(FUNC(void, NVM_CODE) NvM_UpdateGlobalVars(void);)
#endif

#if (NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS)
/* NvM_ProcessEraseInvalidBlk Prototype Declarations*/
extern FUNC(void, NVM_CODE) NvM_ProcessEraseInvalidBlk(void);
#endif  /* (NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS) */

#if((NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS) && \
  (0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS))
extern FUNC(void, NVM_CODE) NvM_ProcessFirstInitAllBlocks(void);
#endif

#if(0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS)
extern FUNC(void, NVM_CODE) NvM_ProcessReadAllBlocks(void);
#endif

extern FUNC(void, NVM_CODE) NvM_ProcessReadBlock(void);
extern FUNC(void, NVM_CODE) NvM_ProcessRestoreBlock(void);
extern FUNC(void, NVM_CODE) NvM_ProcessWriteBlock(void);

#if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)

extern FUNC(Std_ReturnType, NVM_CODE) NvM_StdQueueWrite(
  CONSTP2CONST(NvM_JobQueue, AUTOMATIC, NVM_APPL_DATA) ptrDataPtr);

extern FUNC(Std_ReturnType, NVM_CODE) NvM_StdQueueCancel(
  VAR(NvM_BlockIdType, AUTOMATIC) blockId);

#endif

#if((NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) && \
  (STD_ON == NVM_JOB_PRIORITIZATION) && (STD_ON == NVM_IMM_JOB_PRIORITY))

extern FUNC(Std_ReturnType, NVM_CODE) NvM_ImmQueueCancel(
  VAR(NvM_BlockIdType, AUTOMATIC) blockId);

extern FUNC(Std_ReturnType, NVM_CODE) NvM_ImmQueueWrite(
  CONSTP2CONST(NvM_JobQueue, AUTOMATIC, NVM_APPL_DATA) ptrDataPtr);

#endif

#if(0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS)
extern FUNC(void, NVM_CODE) NvM_ProcessWriteAllBlocks(void);
#endif

#endif /* end of if((NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) || \
  (0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS) || \
  (0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS)) */

#if((0 < NVM_TOTAL_NUM_OF_VALIDATEALL_BLOCKS) && \
    (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS))
NVM_EXTERN(FUNC(void, NVM_CODE) NvM_ValidateAllProcess(void);)
#endif

#if((0 < NVM_TOTAL_NUM_OF_VALIDATEALL_BLOCKS) && \
  (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS))
extern FUNC(void, NVM_CODE) NvM_ProcessValidateAllBlocks(void);
#endif

extern FUNC(void, NVM_CODE) NvM_MainFunctionMultiProcess(void);
#if(STD_ON == NVM_JOB_PRIO)
extern FUNC(boolean, NVM_CODE) NvM_MainFunctionProcessImmediate(
  VAR(uint8, AUTOMATIC) jobSwitch);
#endif

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

#endif  /* NVM_INTFUNC_H */
