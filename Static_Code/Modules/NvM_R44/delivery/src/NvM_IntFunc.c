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
**  SRC-MODULE: NvM_IntFunc.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : Internal Function Definitions of NVRAM Module                 **
**              NvM_ByteOrderDispatch16                                       **
**              NvM_ReOrderByte16                                             **
**              NvM_ByteOrderDispatch32                                       **
**              NvM_ReOrderByte32                                             **
**              NvM_CalculateCRCStaticID                                      **
**              NvM_CompareCRCSID                                             **
**              NvM_CalcBlkNumber                                             **
**              NvM_EndProcessBlock                                           **
**              NvM_UpdateRamStateStatus                                      **
**              NvM_CalculateCrcOffset                                        **
**              NvM_StoreCrcOffset                                            **
**              NvM_CheckConfigId                                             **
**              NvM_StdQueueRead                                              **
**              NvM_StdQueuePosClear                                          **
**              NvM_ImmQueuePosClear                                          **
**              NvM_UpdateGlobalVars                                          **
**              NvM_ProcessEraseInvalidBlk                                    **
**              NvM_ProcessFirstInitAllBlocks                                 **
**              NvM_ProcessReadAllBlocks                                      **
**              NvM_ProcessReadBlock                                          **
**              NvM_ProcessRestoreBlock                                       **
**              NvM_ScanQueue                                                 **
**              NvM_StdQueueWrite                                             **
**              NvM_StdQueueCancel                                            **
**              NvM_ImmQueueCancel                                            **
**              NvM_ImmQueueRead                                              **
**              NvM_ImmQueueWrite                                             **
**              NvM_ProcessValidateAllBlocks                                  **
**              NvM_ProcessWriteBlock                                         **
**              NvM_ProcessWriteAllBlocks                                     **
**              NvM_ProcessImmdWrite                                          **
**              NvM_CalculateCRC                                              **
**              NvM_CompareCrcMechanism                                       **
**              NvM_FirstInitAllProcess                                       **
**              NvM_ReadAllProcess                                            **
**              NvM_WriteAllProcess                                           **
**              NvM_ValidateAllProcess                                        **
**              NvM_ProcessWriteVerify                                        **
**              NvM_WriteProcessNvBlock                                       **
**              NvM_SubWriteProcessNvBlock                                    **
**              NvM_WriteNvBlockProcess                                       **
**              NvM_RestoreBlockProcess                                       **
**              NvM_ProcessReadStart                                          **
**              NvM_ProcessReadNvBlock                                        **
**              NvM_ProcessReadNotOkJob                                       **
**              NvM_ProcessReadOkJob                                          **
**              NvM_MainFunctionMultiProcess                                  **
**              NvM_MainFunctionProcessImmediate                              **
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
** 0.0.1       19-Dec-2019    VinhLV5     Initial version                     **
** 0.0.2       04-May-2020    VinhLV5     Update traceability, apply          **
**                                        new v cycle, Fix Misra              **
** 0.0.3       24-Jul-2020    VinhLV5     R44-Redmine #9958                   **
** 1.0.2       27-Aug-2021    JH Lim      R44-Redmine #19726                  **
** 1.1.1.1     29-Jun-2022    SH Park     Improvement mobilegence             **
**                                          Classic <CP44-221>                **
** 1.1.2       12-Aug-2022    SH Park     Improvement mobilegence             **
**                                          Classic <CP44-76>                 **
** 1.3.0       20-Dec-2022    ThuanLD5    Fix MISRA-C violations              **
** 1.3.2       10-May-2022    MK Choi     Improvement mobilegence             **
**                                          Classic <CP44-8070>               **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA2012:11.5 [Not a defect:Low] "Pointer cast is valid" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "NvM.h"
#include "NvM_IntTypes.h"
#include "NvM_Globals.h"
#include "MemIf.h"                    /* MemIf header file */
#if(STD_ON == NVM_DEMERROR_REPORT)
#include "NvM_Dem_Cfg.h"              /* Dem header file */
#endif
#if(STD_ON == NVM_CRC_SUPPORT)
#include "Crc.h"                      /* Crc header file */
#endif
#if(STD_ON == NVM_DEV_ERROR_DETECT)
#include "Det.h"                      /* Det header file */
#endif
#include "BswM.h"
#include "BswM_NvM.h"                 /* BswM_NvM header header file */
#include "SchM_NvM.h"                 /* SchM_NvM header file */
#include "NvM_IntFunc.h"

#define NVM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: NvM_SUD_MACRO_043 NvM_SUD_MACRO_047 */
#if((0 < NVM_TOTAL_NUM_OF_VALIDATEALL_BLOCKS) && \
    (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS))
NVM_STATIC FUNC(void, NVM_CODE) NvM_ValidateAllProcess(void);
#endif
/* @Trace: NvM_SUD_MACRO_042 NvM_SUD_MACRO_044 NvM_SUD_MACRO_047 */
#if((NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) || \
  (0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS) || \
  (0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS))
/* @Trace: NvM_SUD_MACRO_012 NvM_SUD_MACRO_017 NvM_SUD_MACRO_040 */
#if(((STD_ON == NVM_CRC16_SUPPORT) && (STD_ON == NVM_CRC_SUPPORT)) || \
  (STD_ON == NVM_STATIC_ID_CHECK))
NVM_STATIC FUNC(void, NVM_CODE) NvM_ByteOrderDispatch16(
  VAR(uint16, AUTOMATIC) val16);
/* @Trace: NvM_SUD_MACRO_012 NvM_SUD_MACRO_017 */
#if((STD_ON == NVM_CRC16_SUPPORT) && (STD_ON == NVM_CRC_SUPPORT))
NVM_STATIC FUNC(uint16, NVM_CODE) NvM_ReOrderByte16(
  CONSTP2CONST(uint8, AUTOMATIC, NVM_APPL_CONST) varCrcData);
#endif
#endif
/* @Trace: NvM_SUD_MACRO_013 NvM_SUD_MACRO_017 */
#if((STD_ON == NVM_CRC32_SUPPORT) && (STD_ON == NVM_CRC_SUPPORT))
NVM_STATIC FUNC(void, NVM_CODE) NvM_ByteOrderDispatch32(
  VAR(uint32, AUTOMATIC) val32);
NVM_STATIC FUNC(uint32, NVM_CODE) NvM_ReOrderByte32(
  CONSTP2CONST(uint8, AUTOMATIC, NVM_APPL_CONST) varCrcData);
#endif
/* @Trace: NvM_SUD_MACRO_017 */
#if(STD_ON == NVM_CRC_SUPPORT)
NVM_STATIC FUNC(void, NVM_CODE) NvM_CalculateCRC(
  P2VAR(uint8, AUTOMATIC, NVM_APPL_CONST) ptrCrcCalAddrin,
  P2VAR(uint8, AUTOMATIC, NVM_VAR_NOINIT) ptrRamBlkData);
#endif
/* @Trace: NvM_SUD_MACRO_017 NvM_SUD_MACRO_040 */
#if((STD_ON == NVM_STATIC_ID_CHECK) || (STD_ON == NVM_CRC_SUPPORT))
NVM_STATIC FUNC(void, NVM_CODE) NvM_CalculateCRCStaticID(void);
NVM_STATIC FUNC(Std_ReturnType, NVM_CODE) NvM_CompareCRCSID(void);
#endif

/* NvM_CalcBlkNumber Prototype Declarations */
NVM_STATIC FUNC(uint16, NVM_CODE) NvM_CalcBlkNumber(void);
/* NvM_EndProcessBlock Prototype Declarations */
NVM_STATIC FUNC(void, NVM_CODE) NvM_EndProcessBlock(
  VAR(NvM_RequestResultType, AUTOMATIC) requestResult);

#if(STD_ON == UPDATE_RAM_STATUS_ENABLE)
/* NvM_UpdateRamStateStatus Prototype Declarations */
NVM_STATIC FUNC(void, NVM_CODE) NvM_UpdateRamStateStatus(
  VAR(uint8, AUTOMATIC) status);
#endif

/* @Trace: NvM_SUD_MACRO_004 NvM_SUD_MACRO_017 */
#if((STD_ON == NVM_CRC_SUPPORT) && \
  (STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM))
/* @Trace: NvM_SUD_MACRO_042 NvM_SUD_MACRO_044 NvM_SUD_MACRO_047 */
#if((0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS) || \
  (0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS) || (NVM_API_CONFIG_CLASS != \
  NVM_API_CONFIG_CLASS_1))
NVM_STATIC FUNC(void, NVM_CODE) NvM_CalculateCrcOffset(
  VAR(NvM_BlockIdType, AUTOMATIC) blockId);
#endif

NVM_STATIC FUNC(boolean, NVM_CODE) NvM_CompareCrcMechanism(
  VAR(uint8, AUTOMATIC) varCrcLength,
  VAR(uint8, AUTOMATIC) varCRCSIDIndex);
NVM_STATIC FUNC(void, NVM_CODE) NvM_StoreCrcOffset(void);
#endif
/* @Trace: NvM_SUD_MACRO_008 NvM_SUD_MACRO_042 */
#if((STD_ON == NVM_DYNAMIC_CONFIGURATION) && \
  (0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS))
NVM_STATIC FUNC(void, NVM_CODE) NvM_CheckConfigId(void);
#endif
/* @Trace: NvM_SUD_MACRO_047 */
#if (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
NVM_STATIC FUNC(boolean, NVM_CODE) NvM_ScanQueue(void);
NVM_STATIC FUNC(boolean, NVM_CODE) NvM_StdQueueRead(
  CONSTP2VAR(NvM_JobQueue, AUTOMATIC, NVM_APPL_DATA) ptrDataPtr);
NVM_STATIC FUNC(void, NVM_CODE) NvM_StdQueuePosClear(void);
#endif

#if(STD_ON == NVM_JOB_PRIO)
NVM_STATIC FUNC(void, NVM_CODE) NvM_ImmQueuePosClear(void);
NVM_STATIC FUNC(boolean, NVM_CODE) NvM_ImmQueueRead(
  CONSTP2VAR(NvM_JobQueue, AUTOMATIC, NVM_APPL_DATA) ptrDataPtr);
NVM_STATIC FUNC(void, NVM_CODE) NvM_ProcessImmdWrite(void);
#endif

/* @Trace: NvM_SUD_MACRO_041 NvM_SUD_MACRO_047 */
#if((NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS) && \
  (0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS))
NVM_STATIC FUNC(void, NVM_CODE) NvM_FirstInitAllProcess(void);
#endif
/* @Trace: NvM_SUD_MACRO_042 */
#if(0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS)
NVM_STATIC FUNC(void, NVM_CODE) NvM_ReadAllProcess(void);
#endif
/* @Trace: NvM_SUD_MACRO_044 */
#if(0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS)
NVM_STATIC FUNC(void, NVM_CODE) NvM_WriteAllProcess(void);
#endif
/* @Trace: NvM_SUD_MACRO_046 */
#if(STD_ON == NVM_WRITE_VERIFICATION)
NVM_STATIC FUNC(void, NVM_CODE) NvM_ProcessWriteVerify(void);
#endif

NVM_STATIC FUNC(void, NVM_CODE) NvM_WriteProcessNvBlock(void);
NVM_STATIC FUNC(void, NVM_CODE) NvM_SubWriteProcessNvBlock(void);
NVM_STATIC FUNC(void, NVM_CODE) NvM_WriteNvBlockProcess(void);

NVM_STATIC FUNC(void, NVM_CODE) NvM_RestoreBlockProcess(void);

NVM_STATIC FUNC(void, NVM_CODE) NvM_ProcessReadStart(void);
NVM_STATIC FUNC(void, NVM_CODE) NvM_ProcessReadNvBlock(void);
NVM_STATIC FUNC(void, NVM_CODE) NvM_ProcessReadNotOkJob(
  VAR(Std_ReturnType, AUTOMATIC) status,
  VAR(MemIf_JobResultType, AUTOMATIC) memStatusin);
NVM_STATIC FUNC(void, NVM_CODE) NvM_ProcessReadOkJob(void);
/* @Trace: NvM_SUD_MACRO_042 NvM_SUD_MACRO_044 NvM_SUD_MACRO_047 */
#if((0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS) || \
  (0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS) || (NVM_API_CONFIG_CLASS != \
  NVM_API_CONFIG_CLASS_1))
/* NvM_UpdateGlobalVars Prototype Declarations */
NVM_STATIC FUNC(void, NVM_CODE) NvM_UpdateGlobalVars(void);
#endif
/* @Trace: NvM_SUD_MACRO_012 NvM_SUD_MACRO_017 NvM_SUD_MACRO_040 */
#if(((STD_ON == NVM_CRC16_SUPPORT) && (STD_ON == NVM_CRC_SUPPORT)) || \
  (STD_ON == NVM_STATIC_ID_CHECK))
/*******************************************************************************
** Function Name        : NvM_ByteOrderDispatch16                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function returns the bytes                     **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : val16                                               **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_Msb, NvM_Lsb           **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
NVM_STATIC FUNC(void, NVM_CODE) NvM_ByteOrderDispatch16(
  VAR(uint16, AUTOMATIC) val16)
{
  /* @Trace: NvM_SUD_FUNC_427 */
  #if(HIGH_BYTE_FIRST == CPU_BYTE_ORDER)
    NvM_Msb = (uint8)(val16 & (uint16)NVM_FF);
    NvM_Lsb = (uint8)((val16 >> NVM_EIGHT) & (uint16)NVM_FF);
  #else
    NvM_Lsb = (uint8)(val16 & (uint16)NVM_FF);
    NvM_Msb = (uint8)((val16 >> NVM_EIGHT) & (uint16)NVM_FF);
  #endif
} /* End of function body */
/* @Trace: NvM_SUD_MACRO_012 NvM_SUD_MACRO_017 */
#if((STD_ON == NVM_CRC16_SUPPORT) && (STD_ON == NVM_CRC_SUPPORT))
/*******************************************************************************
** Function Name        : NvM_ReOrderByte16                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function reorder the bytes                     **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : varCrcData                                          **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : returnValue                                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                                                                            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
NVM_STATIC FUNC(uint16, NVM_CODE) NvM_ReOrderByte16(
  CONSTP2CONST(uint8, AUTOMATIC, NVM_APPL_CONST) varCrcData)
{
  /* @Trace: NvM_SUD_FUNC_428 */
  VAR(uint16, AUTOMATIC) returnValue;
  #if(HIGH_BYTE_FIRST == CPU_BYTE_ORDER)
    returnValue = (uint16)varCrcData[NVM_ZERO];
    returnValue |= (uint16)varCrcData[NVM_ONE] << NVM_EIGHT;
  #else
    returnValue = (uint16)varCrcData[NVM_ONE];
    returnValue |= (uint16)varCrcData[NVM_ZERO] << NVM_EIGHT;
  #endif
    return returnValue;
} /* End of function body */
#endif
#endif
/* @Trace: NvM_SUD_MACRO_013 NvM_SUD_MACRO_017 */
#if((STD_ON == NVM_CRC32_SUPPORT) && (STD_ON == NVM_CRC_SUPPORT))
/*******************************************************************************
** Function Name        : NvM_ByteOrderDispatch32                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function returns the bytes                     **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : val32                                               **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_Msb, NvM_MidHi,        **
**                        NvM_MidLow, NvM_Lsb                                 **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
NVM_STATIC FUNC(void, NVM_CODE) NvM_ByteOrderDispatch32(
  VAR(uint32, AUTOMATIC) val32)
{
  /* @Trace: NvM_SUD_FUNC_426 */
  #if(HIGH_BYTE_FIRST == CPU_BYTE_ORDER)
    NvM_Msb = (uint8)(val32 & (uint32)NVM_FF);
    NvM_MidHi = (uint8)((val32 >> NVM_EIGHT) & (uint32)NVM_FF);
    NvM_MidLow = (uint8)((val32 >> NVM_SIXTEEN) & (uint32)NVM_FF);
    NvM_Lsb = (uint8)((val32 >> NVM_TWENTYFOUR) & (uint32)NVM_FF);
  #else
    NvM_Lsb = (uint8)(val32 & (uint32)NVM_FF);
    NvM_MidLow = (uint8)((val32 >> NVM_EIGHT) & (uint32)NVM_FF);
    NvM_MidHi = (uint8)((val32 >> NVM_SIXTEEN) & (uint32)NVM_FF);
    NvM_Msb = (uint8)((val32 >> NVM_TWENTYFOUR) & (uint32)NVM_FF);
  #endif
} /* End of function body */
/*******************************************************************************
** Function Name        : NvM_ReOrderByte32                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function reorder the bytes                     **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : varCrcData                                          **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : returnValue                                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                                                                            **
**                        Function(s) invoked : None                          **
*******************************************************************************/
NVM_STATIC FUNC(uint32, NVM_CODE) NvM_ReOrderByte32(
  CONSTP2CONST(uint8, AUTOMATIC, NVM_APPL_CONST) varCrcData)
{
  /* @Trace: NvM_SUD_FUNC_429 */
  VAR(uint32, AUTOMATIC) returnValue;
  #if(HIGH_BYTE_FIRST == CPU_BYTE_ORDER)
    returnValue = (uint32)varCrcData[NVM_ZERO];
    returnValue |= (uint32)varCrcData[NVM_ONE] << NVM_EIGHT;
    returnValue |= (uint32)varCrcData[NVM_TWO] << NVM_SIXTEEN;
    returnValue |= (uint32)varCrcData[NVM_THREE] << NVM_TWENTYFOUR;
  #else
    returnValue = (uint32)varCrcData[NVM_THREE];
    returnValue |= (uint32)varCrcData[NVM_TWO] << NVM_EIGHT;
    returnValue |= (uint32)varCrcData[NVM_ONE] << NVM_SIXTEEN;
    returnValue |= (uint32)varCrcData[NVM_ZERO] << NVM_TWENTYFOUR;
  #endif
    return returnValue;
} /* End of function body */
#endif

/*******************************************************************************
** Function Name        : NvM_CalculateCRC                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to calculate CRC                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ptrCrcCalAddr, ptrRamBlkData                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : NvM_NvmBlkDescTbl, NvM_Msb,   **
**                        NvM_CrcStepCnt, NvM_Lsb, NvM_MidLow, NvM_MidHi      **
**                        Function(s) invoked : Crc_CalculateCRC8(),          **
**                        Crc_CalculateCRC16(), Crc_CalculateCRC32(),         **
**                        NvM_ReOrderByte16(), NvM_ReOrderByte32(),           **
**                        NvM_ByteOrderDispatch16(), NvM_ByteOrderDispatch32()**
*******************************************************************************/
/* @Trace: NvM_SUD_MACRO_017 */
#if(STD_ON == NVM_CRC_SUPPORT)
NVM_STATIC FUNC(void, NVM_CODE) NvM_CalculateCRC(
  P2VAR(uint8, AUTOMATIC, NVM_APPL_CONST) ptrCrcCalAddrin,
  P2VAR(uint8, AUTOMATIC, NVM_VAR_NOINIT) ptrRamBlkData)
{
  VAR(uint32, AUTOMATIC) startValue;
  VAR(boolean, AUTOMATIC) isFirstCall;
  VAR(uint16, AUTOMATIC) lengthData;
  VAR(uint16, AUTOMATIC) varOffset;
  VAR(uint8, AUTOMATIC) varCrcLength;
  P2VAR(uint8, AUTOMATIC, NVM_APPL_CONST) ptrCrcCalAddr;
  /* @Trace: NvM_SUD_MACRO_012 */
  #if(STD_ON == NVM_CRC16_SUPPORT)
    VAR(NvM_Word16, AUTOMATIC) varCrc16Value;
  #endif
  /* @Trace: NvM_SUD_MACRO_013 */
  #if(STD_ON == NVM_CRC32_SUPPORT)
    VAR(NvM_DWord32, AUTOMATIC) varCrc32Value;
  #endif
  /* @Trace: NvM_SUD_MACRO_014 */
  #if(STD_ON == NVM_CRC8_SUPPORT)
    VAR(uint8, AUTOMATIC) varCrc8bit;
  #endif
  /* @Trace: NvM_SUD_MACRO_012 NvM_SUD_MACRO_013 */
  #if((STD_ON == NVM_CRC16_SUPPORT) || (STD_ON == NVM_CRC32_SUPPORT))
    VAR(uint8, AUTOMATIC) varCount;
  #endif
  /* @Trace: NvM_SUD_FUNC_475 */
  ptrCrcCalAddr = ptrCrcCalAddrin;
  varCrcLength = NvM_NvmBlkDescTbl->ucCrcLength;
  startValue = NVM_ZERO;
  lengthData = NvM_NvmBlkDescTbl->usNvBlkDataLength;
  if(NVM_ZERO == NvM_CrcStepCnt)
  {
    /* @Trace: NvM_SUD_FUNC_432 */
    isFirstCall = NVM_TRUE;
    /* @Trace: NvM_SUD_MACRO_014 */
    #if(STD_ON == NVM_CRC8_SUPPORT)
      if(NVM_CRC_1BYTE == varCrcLength)
      {
        startValue = NVM_1BYECRC_STARTVALUE;
      }
    #endif
    /* @Trace: NvM_SUD_MACRO_012 */
    #if(STD_ON == NVM_CRC16_SUPPORT)
      if(NVM_CRC_2BYTE == varCrcLength)
      {
        startValue = NVM_2BYECRC_STARTVALUE;
      }
    #endif
    /* @Trace: NvM_SUD_MACRO_013 */
    #if(STD_ON == NVM_CRC32_SUPPORT)
      if(NVM_CRC_4BYTE == varCrcLength)
      {
        startValue = NVM_4BYECRC_STARTVALUE;
      }
    #endif
  } /* @End of if(NVM_ZERO == NvM_CrcStepCnt) */
  else
  {
    /* @Trace: NvM_SUD_FUNC_433 */
    isFirstCall = NVM_FALSE;
    /* @Trace: NvM_SUD_MACRO_014 */
    #if(STD_ON == NVM_CRC8_SUPPORT)
      if(NVM_CRC_1BYTE == varCrcLength)
      {
        startValue = *ptrRamBlkData;
      }
    #endif
    /* @Trace: NvM_SUD_MACRO_012 */
    #if(STD_ON == NVM_CRC16_SUPPORT)
      if(NVM_CRC_2BYTE == varCrcLength)
      {
        startValue = NvM_ReOrderByte16(ptrRamBlkData);
      }
    #endif
    /* @Trace: NvM_SUD_MACRO_013 */
    #if(STD_ON == NVM_CRC32_SUPPORT)
      if(NVM_CRC_4BYTE == varCrcLength)
      {
        startValue = NvM_ReOrderByte32(ptrRamBlkData);
      }
    #endif
  } /* End else part of if(NVM_ZERO == NvM_CrcStepCnt) */
  /* @Trace: NvM_SUD_FUNC_473 NvM_SUD_MACRO_015 */
  varOffset = NVM_CRC_NUM_OF_BYTES * NvM_CrcStepCnt;
  if(NVM_CRC_NUM_OF_BYTES >= (lengthData - varOffset))
  {
    lengthData = lengthData - varOffset;
    NvM_CrcStepCnt = NVM_ZERO;
  }
  else
  {
    /* @Trace: NvM_SUD_MACRO_015 */
    lengthData = NVM_CRC_NUM_OF_BYTES;
    NvM_CrcStepCnt++;
  }
  ptrCrcCalAddr = &ptrCrcCalAddr[varOffset];
  /* @Trace: NvM_SUD_MACRO_014 */
  #if(STD_ON == NVM_CRC8_SUPPORT)
    if(NVM_CRC_1BYTE == varCrcLength)
    {
      /* @Trace: NvM_SUD_FUNC_434 */
      /* Invoke 8-bit CRC calculation routine */
      varCrc8bit = Crc_CalculateCRC8(
        (P2CONST(void, AUTOMATIC, NVM_CONST))ptrCrcCalAddr,
        (uint32)lengthData, (uint8)startValue, isFirstCall);
      *ptrRamBlkData = varCrc8bit;
    }
  #endif
  /* @Trace: NvM_SUD_MACRO_012 */
  #if(STD_ON == NVM_CRC16_SUPPORT)
    if(NVM_CRC_2BYTE == varCrcLength)
    {
      /* @Trace: NvM_SUD_FUNC_435 */
      varCount = (uint8)NVM_ZERO;
      /* Invoke 16-bit CRC calculation routine */
      varCrc16Value.usWordReg16 = Crc_CalculateCRC16(
        (P2CONST(void, AUTOMATIC, NVM_CONST))ptrCrcCalAddr,
        (uint32)lengthData, (uint16)startValue, isFirstCall);

      NvM_ByteOrderDispatch16(varCrc16Value.usWordReg16);

      ptrRamBlkData[varCount] = NvM_Msb;
      varCount++;
      ptrRamBlkData[varCount] = NvM_Lsb;
    }
  #endif
  /* @Trace: NvM_SUD_MACRO_013 */
  #if(STD_ON == NVM_CRC32_SUPPORT)
    if(NVM_CRC_4BYTE == varCrcLength)
    {
      /* @Trace: NvM_SUD_FUNC_436 */
      varCount = (uint8)NVM_ZERO;
      /* Invoke 32-bit CRC calculation routine */
      varCrc32Value.ulLongReg32 = Crc_CalculateCRC32(
        (P2CONST(void, AUTOMATIC, NVM_CONST))ptrCrcCalAddr,
        (uint32)lengthData, (uint32)startValue, isFirstCall);

      NvM_ByteOrderDispatch32(varCrc32Value.ulLongReg32);

      ptrRamBlkData[varCount] = NvM_Msb;
      varCount++;
      ptrRamBlkData[varCount] = NvM_MidHi;
      varCount++;
      ptrRamBlkData[varCount] = NvM_MidLow;
      varCount++;
      ptrRamBlkData[varCount] = NvM_Lsb;
    } /* End of if(NVM_CRC_4BYTE == varCrcLength) */
  #endif
}
#endif

/*******************************************************************************
** Function Name        : NvM_CalculateCRCStaticID                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to calculate CRC Static ID                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : NvM_NvmBlkDescTbl, NvM_Msb,   **
**                        NvM_RamAddr, NvM_ReadCRCSID, NvM_DataBuffer,        **
**                        NvM_SubState, NvM_BlockIdx, NvM_State, NvM_Lsb      **
**                                                                            **
**                        Function(s) invoked : NvM_CalculateCRC(),           **
**                        NvM_ByteOrderDispatch16()                           **
*******************************************************************************/
/* @Trace: NvM_SUD_MACRO_017 NvM_SUD_MACRO_040 */
#if((STD_ON == NVM_STATIC_ID_CHECK) || (STD_ON == NVM_CRC_SUPPORT))
NVM_STATIC FUNC(void, NVM_CODE) NvM_CalculateCRCStaticID(void)
{
  P2VAR(uint8, AUTOMATIC, NVM_VAR_NOINIT) ptrRamBlkData;
  /* @Trace: NvM_SUD_MACRO_017 */
  #if(STD_ON == NVM_CRC_SUPPORT)
    P2VAR(uint8, AUTOMATIC, NVM_APPL_CONST) ptrCrcCalAddr;
    VAR(uint16, AUTOMATIC) varCnt;
  #endif
    VAR(uint16, AUTOMATIC) blkParams;
  /* @Trace: NvM_SUD_MACRO_040 */
  #if(STD_ON == NVM_STATIC_ID_CHECK)
    VAR(NvM_Word16, AUTOMATIC) staticID;
    VAR(uint8, AUTOMATIC) varCount;
  #endif
  NvM_DataWordType nvmBufferTmp;

    if(NULL_PTR != NvM_NvmBlkDescTbl)
    {
      /* @Trace: NvM_SUD_FUNC_472 */
      blkParams = NvM_NvmBlkDescTbl->usBlkParams;
      ptrRamBlkData = &NvM_ReadCRCSID[NVM_ZERO];
      /* @Trace: NvM_SUD_MACRO_017 */
      #if(STD_ON == NVM_CRC_SUPPORT)
        /* case read */
        if(((NVM_READBLOCK_SID == NvM_State) || 
          (NVM_READPRAMBLOCK_SID == NvM_State) || 
          (NVM_READALL_SID == NvM_State)) && 
          (NVM_READ_NVBLOCK == NvM_SubState))
        {
          /* @Trace: NvM_SUD_FUNC_430 */
          if(NVM_STATIC_BLOCK_ID_CHECK == 
            (blkParams & NVM_STATIC_BLOCK_ID_CHECK))
          {
            ptrCrcCalAddr = &NvM_DataBuffer[NVM_TWO];
          }
          else
          {
            ptrCrcCalAddr = &NvM_DataBuffer[NVM_ZERO];
          }
        }
        else if(((NVM_WRITEBLOCK_SID == NvM_State) || 
          (NVM_WRITEPRAMBLOCK_SID == NvM_State) || 
          (NVM_WRITEALL_SID == NvM_State)) && (NVM_ONE == NvM_BlockIdx))
        {
          /* polyspace-begin RTE:IDP [Justified:Low] "NvM_DataBuffer has the size greater than STATIC_ID + Crc + NvBlock length" */
          /* @Trace: NvM_SUD_FUNC_524 */
          nvmBufferTmp.u_uint16 = NVM_COMPILED_CONFIG_ID;
          NvM_DataBuffer[0] = nvmBufferTmp.u_uint8[0];
          NvM_DataBuffer[1] = nvmBufferTmp.u_uint8[1];
          /* @Trace: NvM_SUD_MACRO_011 */
          ptrCrcCalAddr = &NvM_DataBuffer[NVM_ZERO];
          if(NULL_PTR != NvM_RamAddr)
          {
            for(varCnt = NVM_TWO; varCnt < 
              NvM_NvmBlkDescTbl->usNvBlkDataLength; varCnt++)
            {
              /* move data from RamAddr to NvM_DataBuffer to calculate Crc */
              NvM_DataBuffer[varCnt] = NvM_RamAddr[varCnt];
            }
          }
        }
        else
        {
          /* @Trace: NvM_SUD_FUNC_525 */
          ptrCrcCalAddr = NvM_RamAddr;
        }
      #endif
      /* @Trace: NvM_SUD_MACRO_040 */
      #if(STD_ON == NVM_STATIC_ID_CHECK)
        /* @Trace: NvM_SUD_FUNC_431 */
        varCount = (uint8)NVM_ZERO;
        if(NVM_STATIC_BLOCK_ID_CHECK == (blkParams & NVM_STATIC_BLOCK_ID_CHECK))
        {
          staticID.usWordReg16 = NvM_BlockIdx;
          NvM_ByteOrderDispatch16(staticID.usWordReg16);

          ptrRamBlkData[varCount] = NvM_Msb;
          varCount++;
          ptrRamBlkData[varCount] = NvM_Lsb;
          varCount++;
        }
        ptrRamBlkData = &ptrRamBlkData[varCount];
      #endif
      /* @Trace: NvM_SUD_MACRO_017 */
      #if(STD_ON == NVM_CRC_SUPPORT)
        if(NVM_CALC_RAM_BLK_CRC == (blkParams & NVM_CALC_RAM_BLK_CRC))
        {
          /* @Trace: NvM_SUD_FUNC_526 */
          NvM_CalculateCRC(ptrCrcCalAddr, ptrRamBlkData);
        } /* @End of if(NVM_CALC_RAM_BLK_CRC == (blkParams & NVM_CALC_RAM_BLK_CRC)) */
      #endif
    } /* End of if(NULL_PTR != NvM_NvmBlkDescTbl) */
} /* End of function body */
#endif

/*******************************************************************************
** Function Name        : NvM_CompareCRCSID                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to compare CRC static ID                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : NvM_SubState, NvM_DataBuffer, **
**                        NvM_NvmBlkDescTbl, NvM_JobResultLowLevel,           **
**                        NvM_ReadCRCSID,  NvM_State, NvM_BlkMngmntType,      **
**                        NvM_ReStatus, NvM_RetryCount                        **
**                        Function(s) invoked : Dem_SetEventStatus()          **
*******************************************************************************/
/* @Trace: SRS_Mem_00030 NvM_SUD_MACRO_017 NvM_SUD_MACRO_040 */
#if((STD_ON == NVM_STATIC_ID_CHECK) || (STD_ON == NVM_CRC_SUPPORT))
NVM_STATIC FUNC(Std_ReturnType, NVM_CODE) NvM_CompareCRCSID(void)
{
  P2VAR(uint8, AUTOMATIC, NVM_VAR_NOINIT) ptrCRCSIDMainBlock;
  P2CONST(uint8, AUTOMATIC, NVM_VAR_NOINIT) ptrCRCSIDData;
  VAR(uint16, AUTOMATIC) blkParams;
  VAR(uint8, AUTOMATIC) indexCnt;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* @Trace: NvM_SUD_MACRO_017 */
  #if(STD_ON == NVM_CRC_SUPPORT)
    VAR(uint8, AUTOMATIC) varCrcLength;
    VAR(boolean, AUTOMATIC) varCrcMatch;
  #endif
  /* @Trace: NvM_SUD_MACRO_040 */
  #if(STD_ON == NVM_STATIC_ID_CHECK)
    VAR(boolean, AUTOMATIC) varStaticMatch;
  #endif

  ptrCRCSIDData = &NvM_DataBuffer[NVM_ZERO];
  ptrCRCSIDMainBlock = &NvM_ReadCRCSID[NVM_ZERO];
  returnValue = E_OK;

  /* @Trace: NvM_SUD_FUNC_421 */
  indexCnt = (uint8)NVM_ZERO;
  blkParams = NvM_NvmBlkDescTbl->usBlkParams;
  /* @Trace: NvM_SUD_MACRO_017 */
  #if(STD_ON == NVM_CRC_SUPPORT)
    varCrcLength = NvM_NvmBlkDescTbl->ucCrcLength;
    varCrcMatch = NVM_TRUE;
  #endif
  /* @Trace: NvM_SUD_MACRO_040 */
  #if (STD_ON == NVM_STATIC_ID_CHECK)
    /* @Trace: NvM_SUD_FUNC_422 */
    varStaticMatch = NVM_TRUE;

    if(NVM_STATIC_BLOCK_ID_CHECK == (blkParams & NVM_STATIC_BLOCK_ID_CHECK))
    {
      indexCnt = (uint8)NVM_ZERO;
      while(indexCnt < NVM_TWO)
      {
        if(ptrCRCSIDMainBlock[indexCnt] != ptrCRCSIDData[indexCnt])
        {
          varStaticMatch = NVM_FALSE;
          indexCnt = (uint8)NVM_TWO;
        }
        indexCnt++;
      }

      ptrCRCSIDMainBlock = &ptrCRCSIDMainBlock[indexCnt];

      if(NVM_TRUE != varStaticMatch)
      {
        /* @Trace: NvM_SUD_MACRO_021 */
        #if(STD_ON == NVM_DEMERROR_REPORT)
          if((NVM_BLOCK_REDUNDANT != NvM_BlkMngmntType) || 
            ((NVM_RE_CHK_NONE != NvM_ReStatus) && (NVM_ZERO == NvM_RetryCount)) 
            || (NVM_READALL_SID == NvM_State))
          {
            /* @Trace: NvM_SUD_MACRO_003 */
            (void)Dem_SetEventStatus(NVM_E_WRONG_BLOCK_ID, 
              DEM_EVENT_STATUS_FAILED);
          }
        #endif
          NvM_JobResultLowLevel = NVM_REQ_NOT_OK;
          returnValue = E_NOT_OK;
      }
    } /* @End of if(NVM_STATIC_BLOCK_ID_CHECK == (blkParams & NVM_STATIC_BLOCK_ID_CHECK)) */
    if(NVM_TRUE == varStaticMatch)
  #endif
    {
      /* @Trace: NvM_SUD_MACRO_017 */
      #if(STD_ON == NVM_CRC_SUPPORT)
        /* @Trace: NvM_SUD_FUNC_471 */
        ptrCRCSIDData = &ptrCRCSIDData[(uint16)indexCnt + NvM_BlockLength];
        if(NVM_CALC_RAM_BLK_CRC == (blkParams & NVM_CALC_RAM_BLK_CRC))
        {
          /* @Trace: NvM_SUD_FUNC_423 */
          indexCnt = (uint8)NVM_ZERO;
          while(indexCnt < varCrcLength)
          {
            if(ptrCRCSIDMainBlock[indexCnt] != ptrCRCSIDData[indexCnt])
            {
              varCrcMatch = NVM_FALSE;
              break;
            }
            indexCnt++;
          }
        } /* End of if(NVM_CALC_RAM_BLK_CRC == (blkParams & NVM_CALC_RAM_BLK_CRC)) */
        /* polyspace-end RTE:IDP */
        if(NVM_TRUE != varCrcMatch)
        {
          /* @Trace: NvM_SUD_FUNC_424 */
          returnValue = E_NOT_OK;
          NvM_JobResultLowLevel = NVM_REQ_INTEGRITY_FAILED;
          /* @Trace: NvM_SUD_MACRO_021 */
          #if(STD_ON == NVM_DEMERROR_REPORT)
            if((NVM_BLOCK_REDUNDANT != NvM_BlkMngmntType) || 
              ((NVM_RE_CHK_NONE != NvM_ReStatus) && 
              (NVM_ZERO == NvM_RetryCount)) || (NVM_READALL_SID == NvM_State))
            {
              /* @Trace: NvM_SUD_MACRO_003 */
              (void)Dem_SetEventStatus
                (NVM_E_INTEGRITY_FAILED, DEM_EVENT_STATUS_FAILED);
              (void)Dem_SetEventStatus(NVM_E_HARDWARE, DEM_EVENT_STATUS_FAILED);
            }
          #endif
        } /* End of if(NVM_TRUE != varCrcMatch) */
      #endif
    } /* @End of if(NVM_TRUE == varStaticMatch) */
  return returnValue;
} /* End of function body */
#endif
/* @Trace: NvM_SUD_MACRO_047 */
#if(NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS)
/*******************************************************************************
** Function Name        : NvM_ProcessEraseInvalidBlk                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function implemented job functions follow:     **
**                        NvM_InvalidateBlock() and NvM_EraseNvBlock()        **
**                        this function Invalidates/Erases a NV block.        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : varStatus                                           **
**                                                                            **
** Preconditions        : NvM should be initialized.                          **
**                                                                            **
** Remarks              : Global Variable(s)     :  NvM_SubState, NvM_State,  **
**                        NvM_NvmBlkDescTbl, NvM_BlkMngmntType, NvM_ReStatus, **
**                        NvM_JobResultLowLevel, NvM_BlockIdx                 **
**                        Function(s) invoked   :  NvM_CalcBlkNumber(),       **
**                        MemIf_EraseImmediateBlock(), NvM_EndProcessBlock(), **
**                        MemIf_InvalidateBlock(), Det_ReportError(),         **
**                        Dem_SetEventStatus()                                **
*******************************************************************************/
/* @Trace: SRS_BSW_00337 SRS_BSW_00386 SRS_Mem_08011 SRS_Mem_08544 SRS_Mem_00011 SRS_Mem_08000 */
FUNC(void,NVM_CODE) NvM_ProcessEraseInvalidBlk(void)
{
  VAR(Std_ReturnType, AUTOMATIC) varStatus;
  VAR(uint16, AUTOMATIC) blkNumber;

  if(NULL_PTR != NvM_NvmBlkDescTbl)
  {
    /* @Trace: NvM_SUD_MACRO_007 */
    #if(STD_ON == NVM_DEV_ERROR_DETECT)
      if((NVM_WRITE_BLOCK_ONCE == (NvM_NvmBlkDescTbl->usBlkParams & 
        NVM_WRITE_BLOCK_ONCE)) && (NVM_CHECK_READ_PRIOR != 
        (NvM_RamStatus[NvM_BlockIdx] & NVM_CHECK_READ_PRIOR)) && 
        (NVM_FIRSTINITALL_SID != NvM_State))
      {
        /* @Trace: NvM_SUD_FUNC_410 */
        (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, 
          NvM_State, NVM_E_WRITE_ONCE_STATUS_UNKNOWN);
      }
      else
    #endif
      { /* Start of block comment 1 */
        switch (NvM_SubState)
        {
          case NVM_ERASEINVALIDATE_START:
            /* @Trace: NvM_SUD_FUNC_469 */
            /* Invoke function to calculate the block number */
            blkNumber = NvM_CalcBlkNumber();
            NvM_JobResultLowLevel = NVM_REQ_PENDING;
            if(NVM_ERASENVBLOCK_SID == NvM_State)
            {
              /* @Trace: NvM_SUD_FUNC_411 */
              /* If Erase operation is to be processed */
              /* Invoke MemIf_EraseImmediateBlock to erase a NV block */
              varStatus = MemIf_EraseImmediateBlock(
                NvM_NvmBlkDescTbl->ucNvramDeviceId, blkNumber);
            } 
            else
            {
              /* @Trace: NvM_SUD_FUNC_412 */
              /* If Invalidate operation is to be processed */
              varStatus = MemIf_InvalidateBlock(
                NvM_NvmBlkDescTbl->ucNvramDeviceId, blkNumber);
            }
            if(E_OK == varStatus)
            {
              /* @Trace: NvM_SUD_FUNC_413 */
              /* If MEMIF layer accepts the request  */
              NvM_SubState = NVM_ERASEINVALIDATE_PROCESSING;
            }
            else
            {
              /*
               * If MEMIF layer does not accept the request, update RAM status as
               * unsuccessful and end the processing.
               */
              /* @Trace: NvM_SUD_MACRO_021 */
              #if(STD_ON == NVM_DEMERROR_REPORT)
                /* @Trace: NvM_SUD_FUNC_414 */
                /* @Trace: NvM_SUD_MACRO_003 */
                (void)Dem_SetEventStatus(
                  NVM_E_REQ_FAILED, DEM_EVENT_STATUS_FAILED);
              #endif
              /* @Trace: NvM_SUD_MACRO_041 */
                NvM_JobResultLowLevel = NVM_REQ_NOT_OK;
              #if(0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS)
                if(NvM_State == NVM_FIRSTINITALL_SID)
                {
                  /* @Trace: NvM_SUD_FUNC_415 */
                  NvM_SubState = NVM_SUB_IDLE;
                }
                else
              #endif
                {
                  /* @Trace: NvM_SUD_FUNC_416 */
                  NvM_EndProcessBlock(NVM_REQ_NOT_OK);
                }
            }
          break;

          case NVM_ERASEINVALIDATE_PROCESSING :
            /* Wait for the MEMIF layer to process the request 
             * by using callback from underlying layer 
             * or polling by NvM_MainFunction()
             */
            if(NVM_REQ_PENDING != NvM_JobResultLowLevel)
            {
              if(NVM_REQ_OK == NvM_JobResultLowLevel)
              {
                /*
                 * If the Block management type is Redundant block, invalidate
                 * 2nd NV block of Redundant block or erase 2nd NV block of Redundant block
                 */
                if((NVM_BLOCK_REDUNDANT == NvM_BlkMngmntType)
                  && (NVM_RE_CHK_NONE == NvM_ReStatus))
                {
                  /* @Trace: NvM_SUD_FUNC_417 */
                  /* If the Block management type is Redundant block, 
                   * SubState NVM_ERASEINVALIDATE_START shall run again with 2nd nv block
                   */
                  NvM_SubState = NVM_ERASEINVALIDATE_START;
                  NvM_ReStatus = NVM_RE_CHKED_ORIGIN;
                }
                else
                {
                  /* @Trace: NvM_SUD_FUNC_418 NvM_SUD_MACRO_041 */
                  #if(0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS)
                  if(NvM_State == NVM_FIRSTINITALL_SID)
                  {
                    NvM_SubState = NVM_SUB_IDLE;
                    NvM_JobResultLowLevel = NVM_REQ_OK;
                  }
                  else
                  #endif
                  {
                    NvM_EndProcessBlock(NVM_REQ_OK);
                  }
                }
              } /* @End of if(NVM_REQ_OK == NvM_JobResultLowLevel) */
              else
              {
                /* @Trace: NvM_SUD_MACRO_021 */
                /* If MEMIF layer returns job failure, Update the RAM status */
                #if(STD_ON == NVM_DEMERROR_REPORT)
                  /* @Trace: NvM_SUD_FUNC_419 */
                  (void)Dem_SetEventStatus(
                    NVM_E_REQ_FAILED, DEM_EVENT_STATUS_FAILED);
                  (void)Dem_SetEventStatus(
                    NVM_E_HARDWARE, DEM_EVENT_STATUS_FAILED);
                #endif
                  /* @Trace: NvM_SUD_FUNC_420 NvM_SUD_MACRO_041 */
                  #if(0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS)
                  if(NvM_State == NVM_FIRSTINITALL_SID)
                  {
                    NvM_SubState = NVM_SUB_IDLE;
                    NvM_JobResultLowLevel = NVM_REQ_NOT_OK;
                  }
                  else
                  #endif
                  {
                    NvM_EndProcessBlock(NVM_REQ_NOT_OK);
                  }
              } /* End else part of if(NVM_REQ_OK == NvM_JobResultLowLevel) */
            }  /* end if(NVM_REQ_PENDING != NvM_JobResultLowLevel) */
          break;

          default :
            /* Do nothing */
            break;
        }   /* end switch (NvM_SubState) */
      } /* End of block comment 1 */
  } /* End of (NULL_PTR != NvM_NvmBlkDescTbl) */
} /* End of function body */

#endif  /* (NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS) */

/*******************************************************************************
** Function Name        : NvM_FirstInitAllProcess                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function implemented job functions follow:     **
**                        NvM_FirstInitAll()                                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : varStatus                                           **
**                                                                            **
** Preconditions        : NvM should be initialized.                          **
**                                                                            **
** Remarks              : Global Variable(s)    : NvM_FirstInitAllCnt,        **
**                        NvM_BlockIdx, NvM_NvmBlkDescTbl, NvM_RamAddr,       **
**                        NvM_RamIndex, NvM_SubState, NvM_FirstInitAllState,  **
**                        NvM_RestoreBlockstate, NvM_NotifiedGlobalStatus,    **
**                        NvM_State, NvM_FirstInitAllRequest, NvM_MirrorCount,**
**                        NvM_JobResultLowLevel, NvM_RetryCount               **
**                                                                            **
**                        Function(s) invoked   : SchM_Exit_NvM_RAM_INDEX(),  **
**                        SchM_Enter_NvM_RAM_INDEX(), NVM_MULTI_BLOCK_CBK(),  **
**                        NvM_UpdateGlobalVars(), NvM_ProcessRestoreBlock(),  **
**                        BswM_NvM_CurrentJobMode(), NvM_CalculateCrcOffset() **
*******************************************************************************/
/* @Trace: SRS_Mem_08014 */
/* @Trace: NvM_SUD_MACRO_041 NvM_SUD_MACRO_047 */
#if((NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS) && \
  (0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS))
NVM_STATIC FUNC(void, NVM_CODE) NvM_FirstInitAllProcess(void)
{
  if (NVM_FIRSTINITALL_PROCESS == NvM_FirstInitAllState)
  {
    /* @Trace: NvM_SUD_MACRO_041 */
    if(NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS > NvM_FirstInitAllCnt)
    {
      /* @Trace: NvM_SUD_FUNC_014 NvM_SUD_GLOBALDATA_026 */
      NvM_BlockIdx = NvM_FirstInitAllBlocks[NvM_FirstInitAllCnt];
      NvM_NvmBlkDescTbl = &NvM_BlkDescTbls[NvM_BlockIdx];
      NvM_UpdateGlobalVars();
      /* @Trace: NvM_SUD_MACRO_008 */
      /* polyspace +5 DEFECT:DEAD_CODE [Not a defect:Low] "The value of NvM_BlockIdx is a configuration value, 
       * It can be changed by user" */
      /* polyspace +3 MISRA-C3:14.3 [Justified:Low] "The value of NvM_BlockIdx is a configuration value, 
       * It can be changed by user" */
      #if(STD_OFF == NVM_DYNAMIC_CONFIGURATION)
        if(NVM_ONE != NvM_BlockIdx)
      #endif
        {
          /* @Trace: NvM_SUD_MACRO_034 */
          #if(STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS)
            if(NULL_PTR != NvM_NvmBlkDescTbl->pRamBlkData)
            {
              /* polyspace-begin CERT-C:EXP36-C [Justified:Low] "Follow AUTOSAR specification, NvM does not know user data type so It need to be cast from (void*) to (uint8*) " */
              /* @Trace: NvM_SUD_FUNC_015 */
              NvM_RamAddr = NvM_NvmBlkDescTbl->pRamBlkData;
              /* polyspace-end CERT-C:EXP36-C [Justified:Low] "Follow AUTOSAR specification, NvM does not know user data type so It need to be cast from (void*) to (uint8*) " */

            }
            else
          #endif
            {
              /* @Trace: NvM_SUD_FUNC_016 */
              /* Use internal buffer or ram mirror */
              NvM_RamAddr = &NvM_MirrorBuffer[0];
            }
          /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
          #if(STD_ON == NVM_DATASET_PRESENT)
            if(NVM_BLOCK_DATASET == NvM_BlkMngmntType)
            {
              /* @Trace: NvM_SUD_FUNC_017 */
              SchM_Enter_NvM_RAM_INDEX();
              NvM_RamIndex[NvM_BlockIdx] = 
                NvM_NvmBlkDescTbl->ucNumOfNvBlks - (uint8)NVM_ONE;
              SchM_Exit_NvM_RAM_INDEX();
              NvM_SubState = NVM_ERASEINVALIDATE_START;
              NvM_FirstInitAllState = NVM_FIRSTINITALL_INVALI_PROCESS;
            }
            else
          #endif
            {
              if((NULL_PTR != NvM_NvmBlkDescTbl->pRomBlkData)
                /* @Trace: NvM_SUD_MACRO_024 */
                #if(STD_ON == NVM_INIT_CALLBACK)
                  || ((NULL_PTR != 
                    NvM_NvmBlkDescTbl->pNvMInitNotification_BlockId) &&
                    (
                      /* if NvM has permanent ram config or use explicit to get 
                       * default data from ram block after call initblock callback
                       */
                      /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
                      #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
                      ((NvM_NvmBlkDescTbl->usBlkParams & 
                      NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE) == 
                      NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE) ||
                      #endif
                      (NVM_FALSE == NVM_TRUE)
                      /* @Trace: NvM_SUD_MACRO_034 */
                      #if(STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS)
                      || (NULL_PTR != (NvM_NvmBlkDescTbl->pRamBlkData))
                      #endif
                    )
                  )
                #endif
              )
              {
                /* @Trace: NvM_SUD_FUNC_018 */
                #if(STD_ON == UPDATE_RAM_STATUS_ENABLE)
                  NvM_UpdateRamStateStatus(NVM_INVALID_UNCHANGED);
                #endif
                NvM_RestoreBlockstate = NVM_RESTORE_START;
                NvM_FirstInitAllState = NVM_FIRSTINITALL_ROMBLK_PROCESS;
              }
              else
              {
                /* @Trace: NvM_SUD_FUNC_019 */
                NvM_SubState = NVM_ERASEINVALIDATE_START;
                NvM_FirstInitAllState = NVM_FIRSTINITALL_INVALI_PROCESS;
              }
            } /* End else part of if(NVM_BLOCK_DATASET == NvM_BlkMngmntType) */
        /* polyspace +2 MISRA-C3:2.1 [Justified:Low] "The value of NvM_BlockIdx is a configuration value, 
        * It can be changed by user" */
        } /* End of if(NVM_ONE != NvM_BlockIdx) */
      /* @Trace: NvM_SUD_MACRO_008 */
      #if(STD_OFF == NVM_DYNAMIC_CONFIGURATION)
        else
        {
          NvM_FirstInitAllCnt++;
        }
      #endif
    } /* End of if(NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS > NvM_FirstInitAllCnt) */
    else
    {
      /* @Trace: NvM_SUD_FUNC_020 */
      NvM_FirstInitAllCnt = NVM_ZERO;
      NvM_NvmBlkDescTbl = &NvM_BlkDescTbls[NVM_ZERO];
      NVM_SET_JOB_RESULT(NVM_RESERVED_BLOCK_ID, NvM_NotifiedGlobalStatus);
      /* @Trace: NvM_SUD_MACRO_006 */
      #if(STD_ON == NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION)
        (void)BswM_NvM_CurrentJobMode(NVM_FIRST_INIT_ALL, 
          NvM_NotifiedGlobalStatus);
      /* @Trace: NvM_SUD_MACRO_029 NvM_SUD_MACRO_031 */
      #elif(STD_ON == NVM_MULTIBLKCBK_ENABLE)
        (void)NVM_MULTI_BLOCK_CBK(NVM_FIRST_INIT_ALL,
                            NvM_NotifiedGlobalStatus);
      #endif
        /* Reset state of nvm */
        NvM_FirstInitAllState = NVM_IDLE;
        NvM_State = NVM_IDLE;
        NvM_SubState = NVM_SUB_IDLE;
        /* Update first init all request flag */
        NvM_FirstInitAllRequest = NVM_MULTIBLK_UNREQUESTED;
    } /* End else part of if(NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS > NvM_FirstInitAllCnt) */
  } /* End of if(NVM_FIRSTINITALL_PROCESS == NvM_FirstInitAllState) */

  if (NVM_FIRSTINITALL_ROMBLK_PROCESS == NvM_FirstInitAllState)
  {
    /* @Trace: NvM_SUD_FUNC_523 */
    NvM_ProcessRestoreBlock();
    if((NVM_IDLE == NvM_RestoreBlockstate) && (NULL_PTR != NvM_NvmBlkDescTbl))
    {
      if((NULL_PTR == NvM_NvmBlkDescTbl->pRomBlkData) &&
        (NVM_REQ_RESTORED_FROM_ROM != NvM_JobResultLowLevel))
      {
        /* @Trace: NvM_SUD_FUNC_021 */
        NvM_SubState = NVM_ERASEINVALIDATE_START;
        NvM_FirstInitAllState = NVM_FIRSTINITALL_INVALI_PROCESS;
      }
      else
      { /* Start of block comment 1 */
        /* @Trace: NvM_SUD_FUNC_022 */
        NvM_RetryCount = NvM_NvmBlkDescTbl->ucMaxNumOfWriteRetries;
        NvM_SubState = NVM_WRITE_NVBLOCK;
        NvM_FirstInitAllState = NVM_FIRSTINITALL_WRITEBLK_PROCESS;
        /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
        #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
          /* @Trace: NvM_SUD_MACRO_035 */
          NvM_MirrorCount = NVM_REPEAT_MIRROR_OPERATIONS;
        #endif
        /* @Trace: NvM_SUD_MACRO_004 NvM_SUD_MACRO_017 */
        #if((STD_ON == NVM_CRC_SUPPORT) && \
          (STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM))
          if((NVM_BLOCK_USE_CRC_COMP_MASK == 
            (NvM_NvmBlkDescTbl->usBlkParams & NVM_BLOCK_USE_CRC_COMP_MASK))
            && (NVM_CALC_RAM_BLK_CRC == (NvM_NvmBlkDescTbl->usBlkParams & 
            NVM_CALC_RAM_BLK_CRC)))
          {
            NvM_CalculateCrcOffset(NvM_BlockIdx);
          }
        #endif
      } /* End of block comment 1 */
    } /* End of if(NVM_IDLE == NvM_RestoreBlockstate) */
  } /* End of if(NVM_FIRSTINITALL_ROMBLK_PROCESS == NvM_FirstInitAllState) */
}
#endif

/* @Trace: NvM_SUD_MACRO_041 NvM_SUD_MACRO_047 */
#if((NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS) && \
  (0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS))
/*******************************************************************************
** Function Name        : NvM_ProcessFirstInitAllBlocks                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function implemented job functions follow:     **
**                        NvM_FirstInitAll()                                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : varStatus                                           **
**                                                                            **
** Preconditions        : NvM should be initialized.                          **
**                                                                            **
** Remarks              : Global Variable(s)    : NvM_FirstInitAllState,      **
**                        NvM_BlockIdx, NvM_FirstInitAllCnt,                  **
**                        NvM_SubState, NvM_RamIndex, NvM_BlkMngmntType       **
**                                                                            **
**                        Function(s) invoked   : BswM_NvM_CurrentBlockMode(),**
**                        NvM_FirstInitAllProcess(), NvM_EndProcessBlock(),   **
**                        NvM_ProcessEraseInvalidBlk(),                       **
**                        SchM_Enter_NvM_RAM_INDEX(),                         **
**                        SchM_Exit_NvM_RAM_INDEX(), NvM_ProcessWriteBlock()  **
*******************************************************************************/
FUNC(void, NVM_CODE) NvM_ProcessFirstInitAllBlocks(void)
{
  VAR(uint16, AUTOMATIC) indexCnt;
  VAR(NvM_BlockIdType, AUTOMATIC) blockId;
  VAR(uint16, AUTOMATIC) blkParams;
  switch (NvM_FirstInitAllState)
  {
    case NVM_FIRSTINITALL_INIT:
      /* @Trace: NvM_SUD_FUNC_013 NvM_SUD_MACRO_041 */
      for(indexCnt = NVM_ZERO; indexCnt < 
        NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS; indexCnt++)
      {
        /* @Trace: NvM_SUD_MACRO_008 */
        #if(STD_OFF == NVM_DYNAMIC_CONFIGURATION)
          if(NVM_ONE != NvM_BlockIdx)
        #endif
          {
            blockId = NvM_FirstInitAllBlocks[indexCnt];
            blkParams = NvM_BlkDescTbls[blockId].usBlkParams;
            NVM_SET_JOB_RESULT(blockId, NVM_REQ_PENDING);
            if(NVM_BSWM_BLOCK_STATUS_INFORMATION == 
              (blkParams & NVM_BSWM_BLOCK_STATUS_INFORMATION))
            {
              BswM_NvM_CurrentBlockMode(blockId, NVM_REQ_PENDING);
            }
          }
      }

      NvM_FirstInitAllCnt = NVM_ZERO;
      NvM_FirstInitAllState = NVM_FIRSTINITALL_PROCESS;
    break;
    case NVM_FIRSTINITALL_PROCESS:
      /* @Trace: NvM_SUD_FUNC_521 */
      NvM_FirstInitAllProcess();
    break;

    case NVM_FIRSTINITALL_ROMBLK_PROCESS:
      /* @Trace: NvM_SUD_FUNC_522 */
      NvM_FirstInitAllProcess();
    break;

    case NVM_FIRSTINITALL_INVALI_PROCESS:
      if(NVM_ONE == NvM_BlockIdx)
      {
        /* @Trace: NvM_SUD_FUNC_023 */
        NvM_EndProcessBlock(NVM_REQ_NOT_OK);
        NvM_FirstInitAllCnt++;
        NvM_FirstInitAllState = NVM_FIRSTINITALL_PROCESS;
      }
      else
      {
        /* @Trace: NvM_SUD_FUNC_024 */
        NvM_ProcessEraseInvalidBlk();
        if(NVM_SUB_IDLE == NvM_SubState)
        {
          /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
          #if(STD_ON == NVM_DATASET_PRESENT)
            if(NVM_BLOCK_DATASET == NvM_BlkMngmntType)
            {
              /* End of loop NVblock and set request result if have error */
              if((NVM_REQ_NOT_OK == NvM_JobResultLowLevel) ||
                (NVM_ZERO == NvM_RamIndex[NvM_BlockIdx]))
              {
                /* @Trace: NvM_SUD_FUNC_025 */
                NvM_EndProcessBlock(NvM_JobResultLowLevel);
                NvM_FirstInitAllCnt++;
                NvM_FirstInitAllState = NVM_FIRSTINITALL_PROCESS;
              }
              else
              {
                /* @Trace: NvM_SUD_FUNC_027 */
                SchM_Enter_NvM_RAM_INDEX();
                NvM_RamIndex[NvM_BlockIdx]--;
                SchM_Exit_NvM_RAM_INDEX();
                NvM_SubState = NVM_ERASEINVALIDATE_START;
              }
            } /* End of if(NVM_BLOCK_DATASET == NvM_BlkMngmntType) */
            else
          #endif
            {
              NvM_EndProcessBlock(NvM_JobResultLowLevel);
              NvM_FirstInitAllCnt++;
              NvM_FirstInitAllState = NVM_FIRSTINITALL_PROCESS;
            }
        } /* End of if(NVM_IDLE == NvM_SubState) */
      } /* End else part of if(NVM_ONE == NvM_BlockIdx) */
    break;

    case NVM_FIRSTINITALL_WRITEBLK_PROCESS:
      /* @Trace: NvM_SUD_FUNC_026 */
      NvM_ProcessWriteBlock();
      if(NVM_IDLE == NvM_SubState)
      {
        NvM_FirstInitAllCnt++;
        NvM_FirstInitAllState = NVM_FIRSTINITALL_PROCESS;
      }
    break;

    default:
      /* Do nothing */
      break;
  } /* End of switch (NvM_FirstInitAllState) */
} /* End of function body */

#endif

/*******************************************************************************
** Function Name        : NvM_UpdateRamStateStatus                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is the internal function to change the RAM     **
**                        status                                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : status                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)    : NvM_RamStatus, NvM_RamAddr, **
**                        NvM_NvmBlkDescTbl, NvM_BlockIdx, NvM_MirrorBuffer   **
**                                                                            **
**                        Function(s) invoked   :                             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION()               **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION()              **
*******************************************************************************/
#if(STD_ON == UPDATE_RAM_STATUS_ENABLE)
NVM_STATIC FUNC(void, NVM_CODE) NvM_UpdateRamStateStatus(
  VAR(uint8, AUTOMATIC) status)
{
  P2VAR(uint16, AUTOMATIC, NVM_VAR_NOINIT) ptrRamStatus;
  if((NULL_PTR != NvM_NvmBlkDescTbl) && 
    (NVM_TOTAL_NUM_OF_NVRAM_BLOCKS > NvM_BlockIdx))
  { /* Start of block comment 1 */
    /* @Trace: NvM_SUD_FUNC_408 */
    ptrRamStatus = &NvM_RamStatus[NvM_BlockIdx];

    /*
     * Checking with NvM_RamAddr is required because RAM Address
     * pointer can be passed though the permanent block is configured and the
     * status maintained in this block is only for content of the RAM block
     */
    if(((NvM_NvmBlkDescTbl->usBlkParams & NVM_BLOCK_USE_SETRAMBLOCKSTATUS)
      == NVM_BLOCK_USE_SETRAMBLOCKSTATUS) && (
    /* @Trace: NvM_SUD_MACRO_034 */
    #if(STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS)
      (NvM_NvmBlkDescTbl->pRamBlkData == NvM_RamAddr) ||
    #endif
      (NVM_FALSE == NVM_TRUE)
    /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
    #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
      || ((&NvM_MirrorBuffer[0] == NvM_RamAddr) && 
      (NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE ==
      (NvM_NvmBlkDescTbl->usBlkParams & NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE)))
    #endif
    ))
    { /* Start of block comment 2 */
      /* @Trace: NvM_SUD_FUNC_407 */
      SchM_Enter_NvM_RAM_STATUS_PROTECTION();
      /* Set the RAM status */
      *(ptrRamStatus) = ((*ptrRamStatus) & NVM_CLEAR_RAM_INTERNAL_STATE) |
        status;
      SchM_Exit_NvM_RAM_STATUS_PROTECTION();
    } /* End of block comment 2 */
  } /* End of block comment 1 */
} /* End of function body */

#endif

/*******************************************************************************
** Function Name        : NvM_CalcBlkNumber                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to be used to calculate the block number   **
**                        based on Block Management type.                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : blkNumber                                           **
**                                                                            **
** Preconditions        : NvM should be initialized.                          **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_BlkMngmntType,         **
**                        NvM_NvmBlkDescTbl, NvM_ReStatus, NvM_FirstBlock,    **
**                        NvM_RamIndex                                        **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
/* @Trace: SRS_Mem_08528 */
NVM_STATIC FUNC(uint16, NVM_CODE) NvM_CalcBlkNumber(void)
{
  VAR(uint16, AUTOMATIC) blkNumber;
  VAR(uint8, AUTOMATIC) indexCnt;
  /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
  #if(STD_ON == NVM_DATASET_PRESENT)
    if(NVM_BLOCK_DATASET == NvM_BlkMngmntType)
    {
      /* @Trace: NvM_SUD_FUNC_403 */
      /* Update the index to value in RAM index field */
      indexCnt = NvM_RamIndex[NvM_BlockIdx];
    }
    else
  #endif
    if(NVM_BLOCK_REDUNDANT == NvM_BlkMngmntType)
    {
      /* @Trace: NvM_SUD_FUNC_404 */
      if (NVM_RE_CHK_NONE != NvM_ReStatus)
      {
        if (NVM_RE_COPY_FIRST != NvM_FirstBlock)
        {
          /* Update the index to one for 2nd NV block of Redundant block */
          indexCnt = (uint8)NVM_ONE;
        }
        else
        {
          indexCnt = (uint8)NVM_ZERO;
        }
      }
      else
      {
        if (NVM_RE_COPY_FIRST != NvM_FirstBlock)
        {
          /*
           * Update the index to one for Native block and for 1st NV block of
           * Redundant block
           */
          indexCnt = (uint8)NVM_ZERO;
        }
        else
        {
          indexCnt = (uint8)NVM_ONE;
        }
      }
    } /* @End of if(NVM_BLOCK_REDUNDANT == NvM_BlkMngmntType) */
    else /* @(NvM_BlkMngmntType == NVM_BLOCK_NATIVE) */
    {
      /* @Trace: NvM_SUD_FUNC_405 */
      indexCnt = (uint8)NVM_ZERO;
    }
    /* @Trace: NvM_SUD_FUNC_406 */
    blkNumber = NvM_NvmBlkDescTbl->usNvBlkBaseNumber + indexCnt;

  return(blkNumber);

} /* End of function body */

/*******************************************************************************
** Function Name        : NvM_UpdateGlobalVars                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to be used to update global variables.     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_BlkMngmntType,         **
**                        NvM_BlockLength, NvM_RamAddr, NvM_State,            **
**                        NvM_NvmBlkDescTbl, NvM_MirrorCount, NvM_CrcStepCnt, **
**                        NvM_WriteVerify, NvM_MirrorBuffer, NvM_ReStatus,    **
**                        NvM_FirstBlock, NvM_BackUp                          **
**                        Function(s) invoked   : None                        **
*******************************************************************************/
/* @Trace: NvM_SUD_MACRO_042 NvM_SUD_MACRO_044 NvM_SUD_MACRO_047 */
#if((0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS) || \
  (0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS) || (NVM_API_CONFIG_CLASS != \
  NVM_API_CONFIG_CLASS_1))
NVM_STATIC FUNC(void, NVM_CODE) NvM_UpdateGlobalVars(void)
{
  /* @Trace: NvM_SUD_FUNC_402 */
  /* Update the commonly used Global variables */
  NvM_BlockLength = NvM_NvmBlkDescTbl->usNvBlkDataLength;
  NvM_BlkMngmntType = NvM_NvmBlkDescTbl->enBlkMngmntType;
  /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
  #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
    /* @Trace: NvM_SUD_MACRO_035 */
    NvM_MirrorCount = NVM_REPEAT_MIRROR_OPERATIONS;
  #endif
  /* @Trace: NvM_SUD_MACRO_017 */
  #if(STD_ON == NVM_CRC_SUPPORT)
    NvM_CrcStepCnt = NVM_ZERO;
  #endif
  /* @Trace: NvM_SUD_MACRO_027 NvM_SUD_MACRO_046 */
  #if(STD_ON == NVM_WRITE_VERIFICATION)
    NvM_WriteVerify = NVM_ZERO;
  #endif

  if((NVM_READALL_SID == NvM_State) || 
    (NVM_WRITEALL_SID == NvM_State))
  { /* Start block comment 1 */
    /* @Trace: NvM_SUD_MACRO_034 */
    #if(STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS)
      if(NULL_PTR != NvM_NvmBlkDescTbl->pRamBlkData)
      {
        /* polyspace-begin CERT-C:EXP36-C [Justified:Low] "Follow AUTOSAR specification, NvM does not know user data type so It need to be cast from (void*) to (uint8*) " */
        NvM_RamAddr = (uint8*)NvM_NvmBlkDescTbl->pRamBlkData;
        /* polyspace-end CERT-C:EXP36-C [Justified:Low] "Follow AUTOSAR specification, NvM does not know user data type so It need to be cast from (void*) to (uint8*) " */
      }
    #endif
    /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
    #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
      if(NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE == 
        (NvM_NvmBlkDescTbl->usBlkParams & 
        NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE))
      {
        NvM_RamAddr = (uint8*)&NvM_MirrorBuffer[0];
      }
    #endif
  } /* End block comment 1 */
  /* Clear the Redundant status flag */
  NvM_ReStatus = NVM_RE_CHK_NONE;
  NvM_FirstBlock = NVM_RE_ORIGINAL_FIRST;
  NvM_BackUp = NVM_FALSE;
} /* End of function body */
#endif
/*******************************************************************************
** Function Name        : NvM_EndProcessBlock                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to end the processing of any request.      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : requestResult                                       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_State, NvM_ReStatus,   **
**                        NvM_RamStatus, NvM_BlockIdx, NvM_SubState,          **
**                        NvM_HighPriorityRequest, NvM_FirstInitAllState,     **
**                        NvM_NotifiedGlobalStatus, NvM_ValidateAllState,     **
**                        NvM_BlkDescTbls, NvM_FirstBlock, NvM_MirrorCount    **
**                        Function(s) invoked    :                            **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION(),              **
**                        BswM_NvM_CurrentBlockMode(), NvM_ImmQueuePosClear(),**
**                        NvM_StdQueuePosClear()                              **
*******************************************************************************/
/* @Trace: SRS_Mem_00125 */
NVM_STATIC FUNC(void, NVM_CODE) NvM_EndProcessBlock(
  VAR(NvM_RequestResultType, AUTOMATIC) requestResult)
{
  P2CONST(NvM_BlkDescTbl, AUTOMATIC, NVM_CONST) ptrBlkDescTbl;
  /* @Trace: NvM_SUD_MACRO_037 */
  #if(STD_ON == NVM_SINGLE_BLOCK_CALLBACK)
    /* @Trace: NvM_SUD_DATATYPE_011 */
    VAR(NvM_BlockRequestType, AUTOMATIC) blockRequest;
    VAR(boolean, AUTOMATIC) isCallback;
    /* @Trace: NvM_SUD_FUNC_466 */
    isCallback = NVM_TRUE;
  #endif

    /* @Trace: NvM_SUD_FUNC_397 */
    ptrBlkDescTbl = &NvM_BlkDescTbls[NvM_BlockIdx];
    /* @Trace: NvM_SUD_MACRO_041 NvM_SUD_MACRO_042 NvM_SUD_MACRO_043 NvM_SUD_MACRO_044 NvM_SUD_MACRO_047 */
    #if((0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS) || \
      (0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS) || \
      ((0 < NVM_TOTAL_NUM_OF_VALIDATEALL_BLOCKS) && \
      (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)) || \
      ((0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS) && \
      (NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS)))
    if((NVM_READALL_SID != NvM_State) && (NVM_WRITEALL_SID != NvM_State)
      && (NVM_FIRSTINITALL_SID != NvM_State) && 
      (NVM_VALIDATEALL_SID != NvM_State))
    #endif
    { /* Start block comment 1 */
      /* @Trace: NvM_SUD_MACRO_023 NvM_SUD_MACRO_025 NvM_SUD_MACRO_047 */
      #if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
        #if(STD_ON == NVM_JOB_PRIORITIZATION) && \
          (STD_ON == NVM_IMM_JOB_PRIORITY)
          if(((NVM_WRITEBLOCK_SID == NvM_State) || 
            (NVM_WRITEPRAMBLOCK_SID == NvM_State)) && 
            (NVM_IMM_PRIORITY == ptrBlkDescTbl->ucBlkJobPriority))
          {
            /* Clear the Queue for the particular request */
            NvM_ImmQueuePosClear();
          }
          else
        #endif
          {
            NvM_StdQueuePosClear();
          }
      #endif
    } /* End block comment 1 */
    /* @Trace: NvM_SUD_MACRO_041 NvM_SUD_MACRO_042 NvM_SUD_MACRO_043 NvM_SUD_MACRO_044 NvM_SUD_MACRO_047 */
    #if((0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS) || \
      (0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS) || \
      ((0 < NVM_TOTAL_NUM_OF_VALIDATEALL_BLOCKS) && \
      (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)) || \
      ((0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS) && \
      (NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS)))
    else
    {
      if(NVM_REQ_OK != requestResult)
      {
        NvM_NotifiedGlobalStatus = NVM_REQ_NOT_OK;
      }
    }
    #endif
    /* Update the block specific RAM status */
    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    {
      NvM_RamStatus[NvM_BlockIdx] =
      ((NvM_RamStatus[NvM_BlockIdx] & NVM_NOT_ERROR_BIT_MASK)
        | (requestResult));
    }
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();

    if(NVM_BSWM_BLOCK_STATUS_INFORMATION == ((ptrBlkDescTbl->usBlkParams) & 
      NVM_BSWM_BLOCK_STATUS_INFORMATION))
    {
      /* @Trace: NvM_SUD_FUNC_467 */
      BswM_NvM_CurrentBlockMode(NvM_BlockIdx, requestResult);
    }
    /* @Trace: NvM_SUD_MACRO_037 */
    #if(STD_ON == NVM_SINGLE_BLOCK_CALLBACK)
      if(NULL_PTR != ptrBlkDescTbl->pNvMNotification_BlockId)
      {
        /* @Trace: NvM_SUD_FUNC_398 */
        /* Invoke the single block callback notification, if configured */
        if((NVM_READBLOCK_SID == NvM_State) || 
          (NVM_READPRAMBLOCK_SID == NvM_State))
        {
          blockRequest = NVM_READ_BLOCK;
        }
        else if((NVM_WRITEBLOCK_SID == NvM_State) || 
          (NVM_WRITEPRAMBLOCK_SID == NvM_State))
        {
          blockRequest = NVM_WRITE_BLOCK;
        }
        else if((NVM_RESTOREBLOCKDEFAULTS_SID == NvM_State) || 
          (NVM_RESTOREPRAMBLOCKDEFAULTS_SID == NvM_State))
        {
          blockRequest = NVM_RESTORE_BLOCK_DEFAULTS;
        }
        else if(NVM_ERASENVBLOCK_SID == NvM_State)
        {
          blockRequest = NVM_ERASE_NV_BLOCK;
        }
        else if(NVM_INVALIDATENVBLOCK_SID == NvM_State)
        {
          blockRequest = NVM_INVALIDATE_NV_BLOCK;
        }
        /* @Trace: NvM_SUD_MACRO_042 */
        #if(0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS)
        else if(NVM_READALL_SID == NvM_State)
        {
          blockRequest = NVM_READ_ALL_BLOCK;
        }
        #endif
        else
        {
          blockRequest = NVM_READ_BLOCK;
          isCallback = NVM_FALSE;
        }
        if(NVM_TRUE == isCallback)
        {
          /* @Trace: NvM_SUD_FUNC_399 */
          (void)ptrBlkDescTbl->pNvMNotification_BlockId(
            blockRequest, requestResult);
        }
      } /* if(NULL_PTR != ptrBlkDescTbl->pNvMNotification_BlockId) */
    #endif
      /* @Trace: NvM_SUD_FUNC_400 */
      /* Clear the Redundant status flag  */
      NvM_ReStatus = NVM_RE_CHK_NONE;
      NvM_FirstBlock = NVM_RE_ORIGINAL_FIRST;

      /* Clear sub state */
      NvM_SubState = NVM_SUB_IDLE;

    /* @Trace: NvM_SUD_FUNC_401 NvM_SUD_MACRO_041 NvM_SUD_MACRO_042 NvM_SUD_MACRO_043 NvM_SUD_MACRO_044 NvM_SUD_MACRO_047 */
    #if((0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS) || \
      (0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS) || \
      ((0 < NVM_TOTAL_NUM_OF_VALIDATEALL_BLOCKS) && \
      (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)) || \
      ((0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS) && \
      (NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS)))
      if((NVM_READALL_SID != NvM_State) && (NVM_WRITEALL_SID != NvM_State) 
        && (NVM_FIRSTINITALL_SID != NvM_State) && 
        (NVM_VALIDATEALL_SID != NvM_State))
    #endif
      {
        /* Clear the main state only in case of single block requests */
        NvM_State = NVM_IDLE;
      }
      /* @Trace: NvM_SUD_MACRO_023 NvM_SUD_MACRO_025 NvM_SUD_MACRO_047 */
    #if((NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) && \
      (STD_ON == NVM_JOB_PRIORITIZATION) && (STD_ON == NVM_IMM_JOB_PRIORITY))
      if(NVM_TRUE == NvM_HighPriorityRequest)
      {
        /* @Trace: NvM_SUD_MACRO_041 NvM_SUD_MACRO_047 */
        #if((0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS) && \
          (NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS))
          if(NVM_IDLE != NvM_FirstInitAllState)
          {
            NvM_FirstInitAllState = NVM_FIRSTINITALL_PROCESS;
            NvM_State = NVM_FIRSTINITALL_SID;
          }
          else
        #endif
        /* @Trace: NvM_SUD_MACRO_043 NvM_SUD_MACRO_047 */
        #if((0 < NVM_TOTAL_NUM_OF_VALIDATEALL_BLOCKS) && \
          (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS))
          if(NVM_VALIDATEALL_IDLE != NvM_ValidateAllState)
          {
            NvM_State = NVM_VALIDATEALL_SID;
            /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
            #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
              /* @Trace: NvM_SUD_MACRO_035 */
              NvM_MirrorCount = NVM_REPEAT_MIRROR_OPERATIONS;
            #endif
          }
          else
        #endif
          {
            /* Else loop added to avoid QAC warning */
          }
          NvM_HighPriorityRequest = NVM_FALSE;
      } /* @End of if(NVM_TRUE == NvM_HighPriorityRequest) */
    #endif
} /* End of function body */

/* @Trace: NvM_SUD_MACRO_004 NvM_SUD_MACRO_017 */
#if((STD_ON == NVM_CRC_SUPPORT) && \
  (STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM)) 
/*******************************************************************************
** Function Name        : NvM_CalculateCrcOffset                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function implemented job functions follow:     **
**                        NvM_CalculateCrcOffset()                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : varStatus                                           **
**                                                                            **
** Preconditions        : NvM should be initialized.                          **
**                                                                            **
** Remarks              : Global Variable(s)    : NvM_CompareBlocks,          **
**                        NvM_NvmBlkDescTbl, NvM_CrcOffSet, NvM_RamIndex      **
**                        Function(s) invoked   : None                        **
*******************************************************************************/
/* @Trace: NvM_SUD_MACRO_042 NvM_SUD_MACRO_044 NvM_SUD_MACRO_047 */
#if((0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS) || \
  (0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS) || (NVM_API_CONFIG_CLASS != \
  NVM_API_CONFIG_CLASS_1))
NVM_STATIC FUNC(void, NVM_CODE) NvM_CalculateCrcOffset(
  VAR(NvM_BlockIdType, AUTOMATIC) blockId)
{
  /* @Trace: NvM_SUD_FUNC_396 */
  /* Calculate crc offset */
  VAR(uint16, AUTOMATIC) varCnt;
  VAR(NvM_BlockIdType, AUTOMATIC) varBlockIdx;
  NvM_CrcOffSet = NVM_ZERO;
  /* @Trace: NvM_SUD_MACRO_009 */
  for(varCnt = NVM_ZERO; varCnt < NVM_COMPARE_NUM_NVRAM_BLOCK; varCnt++)
  {
    varBlockIdx = NvM_CompareBlocks[varCnt];
    if(varBlockIdx == blockId)
    {
      break;
    }
    else
    {
      /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
      #if(STD_ON == NVM_DATASET_PRESENT)
        if (NVM_BLOCK_DATASET == NvM_NvmBlkDescTbl->enBlkMngmntType)
        {
          NvM_CrcOffSet += (uint32)(NvM_NvmBlkDescTbl->ucNumOfNvBlks);
        }
        else
      #endif
        {
          NvM_CrcOffSet += (uint32)NVM_ONE;
        }
    }
  } /* End of for(varCnt = NVM_ZERO; ... */
  /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
  #if(STD_ON == NVM_DATASET_PRESENT)
    if (NVM_BLOCK_DATASET == NvM_NvmBlkDescTbl->enBlkMngmntType)
    {
      NvM_CrcOffSet += NvM_RamIndex[blockId];
    }
  #endif
} /* End of function body */
#endif
/*******************************************************************************
** Function Name        : NvM_CompareCrcMechanism                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function implemented job functions follow:     **
**                        NvM_CompareCrcMechanism()                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : varCrcLength, varCRCSIDIndex                        **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : cmpMatch                                            **
**                                                                            **
** Preconditions        : NvM should be initialized.                          **
**                                                                            **
** Remarks              : Global Variable(s)    : NvM_LsbArray, NvM_CrcOffSet,**
**                        NvM_ReadCRCSID                                      **
**                        Function(s) invoked   : None                        **
*******************************************************************************/
NVM_STATIC FUNC(boolean, NVM_CODE) NvM_CompareCrcMechanism(
  VAR(uint8, AUTOMATIC) varCrcLength,
  VAR(uint8, AUTOMATIC) varCRCSIDIndex)
{
  VAR(boolean, AUTOMATIC) cmpMatch;

  cmpMatch = NVM_FALSE;
  /* @Trace: NvM_SUD_MACRO_010 */
  NvM_CrcOffSet %= NVM_COMPARE_NUM_NV_BLOCK;
  /* @Trace: NvM_SUD_MACRO_014 */
  #if(STD_ON == NVM_CRC8_SUPPORT)
    if(NVM_CRC_1BYTE == varCrcLength)
    {
      if(NvM_ReadCRCSID[varCRCSIDIndex] == NvM_LsbArray[NvM_CrcOffSet])
      {
        /* @Trace: NvM_SUD_FUNC_279 */
        cmpMatch = NVM_TRUE;
      }
    }
  #endif
  /* @Trace: NvM_SUD_MACRO_012 */
  #if(STD_ON == NVM_CRC16_SUPPORT)
    if(NVM_CRC_2BYTE == varCrcLength)
    {
      if((NvM_ReadCRCSID[varCRCSIDIndex] == NvM_MsbArray[NvM_CrcOffSet]) && (
        NvM_ReadCRCSID[varCRCSIDIndex + NVM_ONE] == 
        NvM_LsbArray[NvM_CrcOffSet]))
      {
        /* @Trace: NvM_SUD_FUNC_280 */
        cmpMatch = NVM_TRUE;
      }
    }
  #endif
  /* @Trace: NvM_SUD_MACRO_013 */
  #if(STD_ON == NVM_CRC32_SUPPORT)
    if(NVM_CRC_4BYTE == varCrcLength)
    {
      if((NvM_ReadCRCSID[varCRCSIDIndex] == NvM_MsbArray[NvM_CrcOffSet]) &&
        (NvM_ReadCRCSID[varCRCSIDIndex + NVM_ONE] == 
        NvM_MidHiArray[NvM_CrcOffSet]) &&
        (NvM_ReadCRCSID[varCRCSIDIndex + NVM_TWO] == 
        NvM_MidLowArray[NvM_CrcOffSet]) &&
        (NvM_ReadCRCSID[varCRCSIDIndex + NVM_THREE] == 
        NvM_LsbArray[NvM_CrcOffSet]))
      {
        /* @Trace: NvM_SUD_FUNC_281 */
        cmpMatch = NVM_TRUE;
      }
    }
  #endif
  return cmpMatch;
}

/*******************************************************************************
** Function Name        : NvM_StoreCrcOffset                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function implemented job functions follow:     **
**                        NvM_StoreCrcOffset()                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized.                          **
**                                                                            **
** Remarks              : Global Variable(s)    : NvM_NvmBlkDescTbl,          **
**                        NvM_ReadCRCSID, NvM_MsbArray, NvM_MidHiArray,       **
**                        NvM_MidLowArray, NvM_LsbArray                       **
**                        Function(s) invoked   : None                        **
*******************************************************************************/
NVM_STATIC FUNC(void, NVM_CODE) NvM_StoreCrcOffset(void)
{
  /* @Trace: NvM_SUD_FUNC_395 */
  VAR(uint8, AUTOMATIC) varCrcLength;
  VAR(uint8, AUTOMATIC) varCRCSIDIndex;
  /* @Trace: NvM_SUD_MACRO_040 */
  #if(STD_ON == NVM_STATIC_ID_CHECK)
    VAR(uint16, AUTOMATIC) blkParams;
  #endif

  varCRCSIDIndex = (uint8)NVM_ZERO;
  /* @Trace: NvM_SUD_MACRO_010 */
  NvM_CrcOffSet %= NVM_COMPARE_NUM_NV_BLOCK;
  /* @Trace: NvM_SUD_MACRO_040 */
  #if(STD_ON == NVM_STATIC_ID_CHECK)
    blkParams = NvM_NvmBlkDescTbl->usBlkParams;
    if(NVM_STATIC_BLOCK_ID_CHECK == (blkParams & NVM_STATIC_BLOCK_ID_CHECK))
    {
      varCRCSIDIndex = (uint8)NVM_TWO;
    }
  #endif
    varCrcLength = NvM_NvmBlkDescTbl->ucCrcLength;
  /* @Trace: NvM_SUD_MACRO_014 */
  #if(STD_ON == NVM_CRC8_SUPPORT)
    if(NVM_CRC_1BYTE == varCrcLength)
    {
      NvM_LsbArray[NvM_CrcOffSet] = NvM_ReadCRCSID[varCRCSIDIndex];
    }
  #endif
  /* @Trace: NvM_SUD_MACRO_012 */
  #if(STD_ON == NVM_CRC16_SUPPORT)
    if(NVM_CRC_2BYTE == varCrcLength)
    {
      NvM_MsbArray[NvM_CrcOffSet] = NvM_ReadCRCSID[varCRCSIDIndex];
      NvM_LsbArray[NvM_CrcOffSet] = NvM_ReadCRCSID[varCRCSIDIndex + NVM_ONE];
    }
  #endif
  /* @Trace: NvM_SUD_MACRO_013 */
  #if(STD_ON == NVM_CRC32_SUPPORT)
    if(NVM_CRC_4BYTE == varCrcLength)
    {
      NvM_MsbArray[NvM_CrcOffSet] = NvM_ReadCRCSID[varCRCSIDIndex];
      NvM_MidHiArray[NvM_CrcOffSet] = NvM_ReadCRCSID[varCRCSIDIndex + NVM_ONE];
      NvM_MidLowArray[NvM_CrcOffSet] = NvM_ReadCRCSID[varCRCSIDIndex + NVM_TWO];
      NvM_LsbArray[NvM_CrcOffSet] = NvM_ReadCRCSID[varCRCSIDIndex + NVM_THREE];
    }
  #endif
} /* End of function body */
#endif

/*******************************************************************************
** Function Name        : NvM_ReadAllProcess                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is NVRAM Manager internal function.            **
**                        This function checks and loads the RAM contents     **
**                        and reports the Global error/status                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_ReadAllState,          **
**                        NvM_ReadAllBlocks, NvM_BlockIdx, NvM_NvmBlkDescTbl, **
**                        NvM_BlkDescTbls, NvM_SubState, NvM_ReadAllCnt,      **
**                        NvM_ConfigIdMatch, NvM_NotifiedGlobalStatus,        **
**                        NvM_ReadAllRequest, NvM_RetryCount,                 **
**                        NvM_RestoreBlockstate, NvM_JobResultLowLevel,       **
**                        NvM_SetModeStatus, NvM_State                        **
**                        Function(s) invoked    : NvM_UpdateGlobalVars(),    **
**                        MemIf_SetMode(), NvM_CalculateCrcOffset(),          **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION(),              **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        BswM_NvM_CurrentJobMode(), NVM_MULTI_BLOCK_CBK()    **
*******************************************************************************/
/* @Trace: NvM_SUD_MACRO_042 */
#if(0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS)
NVM_STATIC FUNC(void, NVM_CODE) NvM_ReadAllProcess(void)
{
  if(NVM_TOTAL_NUM_OF_READALL_BLOCKS > NvM_ReadAllCnt)
  {
    /* @Trace: NvM_SUD_FUNC_194 NvM_SUD_GLOBALDATA_029 */
    NvM_BlockIdx = NvM_ReadAllBlocks[NvM_ReadAllCnt];
    NvM_NvmBlkDescTbl = &NvM_BlkDescTbls[NvM_BlockIdx];
    NvM_UpdateGlobalVars();
    if(NVM_REQ_PENDING == NVM_GET_JOB_RESULT(NvM_BlockIdx))
    {
      /* @Trace: NvM_SUD_MACRO_008 */
      #if(STD_ON == NVM_DYNAMIC_CONFIGURATION)
        /* extended runtime */
        if((NVM_ONE != NvM_BlockIdx) && (NVM_FALSE == NvM_ConfigIdMatch) && 
          (NVM_RESISTANT_TO_CHANGED_SW != (NvM_NvmBlkDescTbl->usBlkParams & 
          NVM_RESISTANT_TO_CHANGED_SW)))
        {
          /* @Trace: NvM_SUD_FUNC_192 */
          NvM_RestoreBlockstate = NVM_RESTORE_START;
          NvM_ReadAllState = NVM_READALL_ROMBLK_PROCESS;
          #if(STD_ON == UPDATE_RAM_STATUS_ENABLE)
            NvM_UpdateRamStateStatus(NVM_INVALID_UNCHANGED);
          #endif
        }
        else
      #endif
        { /* start block comment 1 */
          /* @Trace: NvM_SUD_FUNC_193 */
          /* normal runtime*/
          NvM_ReadAllState = NVM_READALL_BLKPROCESS;
          NvM_SubState = NVM_READ_START;
          NvM_RetryCount = NvM_NvmBlkDescTbl->ucMaxNumOfReadRetries;
          #if(STD_ON == UPDATE_RAM_STATUS_ENABLE)
            NvM_UpdateRamStateStatus(NVM_INVALID_UNCHANGED);
          #endif
          /* @Trace: NvM_SUD_MACRO_004 NvM_SUD_MACRO_017 */
          #if((STD_ON == NVM_CRC_SUPPORT) && \
            (STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM))
            if((NVM_BLOCK_USE_CRC_COMP_MASK == 
              (NvM_NvmBlkDescTbl->usBlkParams & NVM_BLOCK_USE_CRC_COMP_MASK)) 
              && (NVM_CALC_RAM_BLK_CRC == (NvM_NvmBlkDescTbl->usBlkParams & 
              NVM_CALC_RAM_BLK_CRC)))
            {
              NvM_CalculateCrcOffset(NvM_BlockIdx);
            }
          #endif
        } /* end block comment 1 */
    } /* @End of if(NVM_REQ_PENDING == NVM_GET_JOB_RESULT(NvM_BlockIdx)) */
  } /* end of if(NVM_TOTAL_NUM_OF_READALL_BLOCKS > NvM_ReadAllCnt) */
  else
  {
    /* @Trace: NvM_SUD_MACRO_022 */
    #if(STD_ON == NVM_DRV_MODE_SWITCH)
      /* @Trace: NvM_SUD_FUNC_582 */
      if(NVM_FALSE == NvM_SetModeStatus)
      {
        MemIf_SetMode(MEMIF_MODE_SLOW);
        NvM_JobResultLowLevel = NVM_REQ_PENDING;
        NvM_SetModeStatus = NVM_TRUE;
      }
      else
      {
        NvM_SetModeStatus = NVM_FALSE;
    #endif
        /* @Trace: NvM_SUD_FUNC_195 */
        /* If processing of all blocks is complete, update the Global status */
        NvM_BlockIdx = NVM_ZERO;
        /* Update the Global Pointer */
        NvM_NvmBlkDescTbl = &NvM_BlkDescTbls[NVM_ZERO];
        NVM_SET_JOB_RESULT(NVM_RESERVED_BLOCK_ID, NvM_NotifiedGlobalStatus);
        /* Invoke multiblock callback, if configured */
        /* @Trace: NvM_SUD_DATATYPE_012 NvM_SUD_MACRO_006 */
        #if(STD_ON == NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION)
          (void)BswM_NvM_CurrentJobMode(NVM_READ_ALL, NvM_NotifiedGlobalStatus);
        /* @Trace: NvM_SUD_MACRO_029 NvM_SUD_MACRO_031 */
        #elif(STD_ON == NVM_MULTIBLKCBK_ENABLE)
          (void)NVM_MULTI_BLOCK_CBK(NVM_READ_ALL, NvM_NotifiedGlobalStatus);
        #endif
        /*
         * Invoke function(if configured) to put the memory devices back to
         * 'Slow' mode when cancelling the WriteAll request
         */

          /* Clear the main state and flags */
          NvM_ReadAllState = NVM_IDLE;
          NvM_State = NVM_IDLE;
          NvM_SubState = NVM_SUB_IDLE;
          /* Update the ReadAll request flag */
          NvM_ReadAllRequest = NVM_MULTIBLK_UNREQUESTED;
    #if(STD_ON == NVM_DRV_MODE_SWITCH)
      }
    #endif
  } /* end else part of if(NVM_TOTAL_NUM_OF_READALL_BLOCKS > NvM_ReadAllCnt) */
}
#endif

/*******************************************************************************
** Function Name        : NvM_ProcessReadAllBlocks                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is NVRAM Manager internal function.            **
**                        This function checks and loads the RAM contents     **
**                        and reports the Global error/status                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_ReadAllState,          **
**                        NvM_ReadAllCnt, NvM_NotReadAll, NvM_ReadAllBlocks,  **
**                        NvM_NvmBlkDescTbl, NvM_JobResultLowLevel,           **
**                        NvM_BlkDescTbls, NvM_SubState, NvM_SetModeStatus    **
**                        Function(s) invoked    : MemIf_GetStatus(),         **
**                        BswM_NvM_CurrentBlockMode(), NvM_ReadAllProcess(),  **
**                        NvM_ProcessRestoreBlock(), NvM_ProcessReadBlock()   **
*******************************************************************************/
/* @Trace: SRS_Mem_08533 SRS_Mem_08549 SRS_NvM_CUS_00427 SRS_Mem_00011 */
/* @Trace: NvM_SUD_MACRO_042 */
#if(0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS)
FUNC(void, NVM_CODE) NvM_ProcessReadAllBlocks(void)
{
  VAR(uint16, AUTOMATIC) i;
  /* @Trace: NvM_SUD_MACRO_022 */
  #if(STD_ON == NVM_DRV_MODE_SWITCH)
  if((NVM_TRUE == NvM_SetModeStatus) && 
    (NVM_REQ_PENDING == NvM_JobResultLowLevel))
  {
    if(MEMIF_BUSY != MemIf_GetStatus(MEMIF_BROADCAST_ID))
    {
      /* @Trace: NvM_SUD_FUNC_528 */
      /* Finish SetMode job */
      NvM_JobResultLowLevel = NVM_REQ_OK;
    }
  }

  if((NVM_TRUE != NvM_SetModeStatus) || 
    (NVM_REQ_PENDING != NvM_JobResultLowLevel))
  #endif
  {
    switch (NvM_ReadAllState)
    {
      case NVM_READALL_INIT:
        /* @Trace: NvM_SUD_MACRO_022 */
        #if(STD_ON == NVM_DRV_MODE_SWITCH)
        NvM_SetModeStatus = NVM_FALSE;
        #endif
        /* @Trace: NvM_SUD_MACRO_048 */
        #if(NVM_BLOCKS_NOT_CONFIG_READALL > 0)
        for(i = 0; i < NVM_BLOCKS_NOT_CONFIG_READALL; i++)
        {
          /* @Trace: NvM_SUD_FUNC_188 NvM_SUD_GLOBALDATA_027 */
          NvM_NvmBlkDescTbl = &NvM_BlkDescTbls[NvM_NotReadAll[i]];
          NVM_SET_JOB_RESULT(NvM_NotReadAll[i], NVM_REQ_BLOCK_SKIPPED);
          if(NVM_BSWM_BLOCK_STATUS_INFORMATION == 
            (NvM_NvmBlkDescTbl->usBlkParams 
            & NVM_BSWM_BLOCK_STATUS_INFORMATION))
          {
            BswM_NvM_CurrentBlockMode(NvM_NotReadAll[i], NVM_REQ_BLOCK_SKIPPED);
          }
        }
        #endif
        /* @Trace: NvM_SUD_MACRO_042 */
        for(i = 0; i < NVM_TOTAL_NUM_OF_READALL_BLOCKS; i++)
        {
          /* @Trace: NvM_SUD_FUNC_190 NvM_SUD_GLOBALDATA_029 */
          NvM_NvmBlkDescTbl = &NvM_BlkDescTbls[NvM_ReadAllBlocks[i]];
          NVM_SET_JOB_RESULT(NvM_ReadAllBlocks[i], NVM_REQ_PENDING);
          if(NVM_BSWM_BLOCK_STATUS_INFORMATION == 
            (NvM_NvmBlkDescTbl->usBlkParams 
            & NVM_BSWM_BLOCK_STATUS_INFORMATION))
          {
            BswM_NvM_CurrentBlockMode(NvM_ReadAllBlocks[i], NVM_REQ_PENDING);
          }
        }
        /* @Trace: NvM_SUD_FUNC_191 */
        NvM_ReadAllState = NVM_READALL_PROCESS;
        NvM_ReadAllCnt = NVM_ZERO;
      break;

      case NVM_READALL_PROCESS:
        /* @Trace: NvM_SUD_FUNC_508 */
        NvM_ReadAllProcess();
      break;

      case NVM_READALL_BLKPROCESS:
        /* @Trace: NvM_SUD_FUNC_196 */
        NvM_ProcessReadBlock();
        if(NVM_SUB_IDLE == NvM_SubState)
        {
            /* Increment the block index to process the next block */
            NvM_ReadAllCnt++;
            NvM_ReadAllState = NVM_READALL_PROCESS;
        }
      break;
      /* @Trace: NvM_SUD_MACRO_008 */
      #if(STD_ON == NVM_DYNAMIC_CONFIGURATION)
      case NVM_READALL_ROMBLK_PROCESS:
        /*
         * Load the default values if ROM block is configured for the blocks
         * when read of the block fails or when Configuration Id mismatches and
         * Resistant to changed software is configured FALSE
         */
        /* @Trace: NvM_SUD_FUNC_197 */
        NvM_ProcessRestoreBlock();
        if(NVM_IDLE == NvM_RestoreBlockstate)
        {
          if(NULL_PTR != NvM_NvmBlkDescTbl)
          {
            SET_READ_PRIOR();
          }
          NvM_ReadAllCnt++;
          /*
           * Update the state to repeat the process until all blocks are 
           * processed
           */
          NvM_ReadAllState = NVM_READALL_PROCESS;
        }
      break;
      #endif /* end if(STD_ON == NVM_DYNAMIC_CONFIGURATION) */

      default:
        /* Do nothing */
        break;
    }  /* end switch (NvM_ReadAllState) */ 
  }

} /* End of function body */

#endif

/*******************************************************************************
** Function Name        : NvM_CheckConfigId                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is NVRAM Manager internal function.            **
**                        This function calculates the Configuration Id       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)   : NvM_RamAddr,                 **
**                        NvM_JobResultLowLevel, NvM_ConfigIdMatch            **
**                        Function(s) invoked  : None                         **
*******************************************************************************/
/* @Trace: SRS_Mem_08555 */
/* @Trace: NvM_SUD_MACRO_008 NvM_SUD_MACRO_042 */
#if((STD_ON == NVM_DYNAMIC_CONFIGURATION) && \
  (0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS))
NVM_STATIC FUNC(void, NVM_CODE) NvM_CheckConfigId(void)
{
  P2VAR(uint16, AUTOMATIC, NVM_APPL_DATA) ptrRamBlkData;

  ptrRamBlkData = (void*)NvM_RamAddr;
  if(NULL_PTR != ptrRamBlkData)
  {
    /* @Trace: NvM_SUD_MACRO_011 */
    if(NVM_COMPILED_CONFIG_ID == *ptrRamBlkData)
    {
      /* @Trace: NvM_SUD_FUNC_393 */
      NvM_ConfigIdMatch = NVM_TRUE;
    }
    else
    {
      /* @Trace: NvM_SUD_FUNC_394 */
      NvM_JobResultLowLevel = NVM_REQ_NOT_OK;
      NvM_ConfigIdMatch = NVM_FALSE;
      /* @Trace: NvM_SUD_MACRO_011 */ 
      *ptrRamBlkData = NVM_COMPILED_CONFIG_ID;
    }
  }
}
#endif

/*******************************************************************************
** Function Name        : NvM_ProcessReadOkJob                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Request to copy the data of the NV block to its     **
**                        corresponding RAM block.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : status, memStatus                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized.                          **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_SubState, NvM_State,   **
**                        NvM_BlkMngmntType, NvM_NvmBlkDescTbl, NvM_RamAddr,  **
**                        NvM_JobResultLowLevel, NvM_BlockLength,             **
**                        NvM_BlockIdx, NvM_RamStatus, NvM_ReStatus,          **
**                        NvM_DataBuffer, NvM_BackUp                          **
**                        Function(s) invoked    : NvM_CheckConfigId(),       **
**                        NvM_EndProcessBlock(),                              **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION(),              **
*******************************************************************************/
NVM_STATIC FUNC(void, NVM_CODE) NvM_ProcessReadOkJob(void)
{
  VAR(uint16, AUTOMATIC) varCnt;
  VAR(uint16, AUTOMATIC) lengthIndex;
  VAR(uint16, AUTOMATIC) blkParams;
  P2VAR(uint16, AUTOMATIC, NVM_VAR_NOINIT) ptrRamStatus;

  blkParams = NvM_NvmBlkDescTbl->usBlkParams;
  ptrRamStatus = &NvM_RamStatus[NvM_BlockIdx];

    /* @Trace: NvM_SUD_FUNC_514 NvM_SUD_MACRO_040 */
  #if(STD_ON == NVM_STATIC_ID_CHECK)
    if(NVM_STATIC_BLOCK_ID_CHECK == (blkParams & NVM_STATIC_BLOCK_ID_CHECK))
    {
      lengthIndex = NVM_TWO;
    }
    else
  #endif
    {
      lengthIndex = NVM_ZERO;
    }

    if((NULL_PTR != NvM_RamAddr) && (NULL_PTR != NvM_DataBuffer))
    {
      for(varCnt = NVM_ZERO; varCnt < NvM_BlockLength; varCnt++)
      {
        /* @Trace: NvM_SUD_FUNC_204 */
        NvM_RamAddr[varCnt] = NvM_DataBuffer[lengthIndex];
        lengthIndex++;
      }
    }

    if((NVM_BLOCK_REDUNDANT == NvM_BlkMngmntType) &&
      (NVM_RE_CHK_NONE == NvM_ReStatus))
    {
      /* @Trace: NvM_SUD_FUNC_205 */
      SchM_Enter_NvM_RAM_STATUS_PROTECTION();
      *(ptrRamStatus) |= NVM_FIR_REDUNDANT_MASK;
      *(ptrRamStatus) &= NVM_CHECK_DONE_REDUNDANT_MASK;
      SchM_Exit_NvM_RAM_STATUS_PROTECTION();
    }
    /* @Trace: NvM_SUD_FUNC_206 */
    /*If CRC matches, update RAM status and end the read process*/
    #if(STD_ON == UPDATE_RAM_STATUS_ENABLE)
      NvM_UpdateRamStateStatus(NVM_VALID_UNCHANGED);
    #endif
    if(NVM_WRITE_BLOCK_ONCE == (blkParams & NVM_WRITE_BLOCK_ONCE))
    {
      /* @Trace: NvM_SUD_FUNC_207 */
      SchM_Enter_NvM_RAM_STATUS_PROTECTION();
      /* Set write protect bit */
      NvM_RamStatus[NvM_BlockIdx] |= NVM_WRITE_PROTECT_MASK;
      SchM_Exit_NvM_RAM_STATUS_PROTECTION();
    }
    /* @Trace: NvM_SUD_FUNC_208 */
    SET_READ_PRIOR();
  /* @Trace: NvM_SUD_MACRO_008 NvM_SUD_MACRO_042 */
  #if((STD_ON == NVM_DYNAMIC_CONFIGURATION) && \
    (0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS))
    if((NVM_ONE == NvM_BlockIdx) && (NVM_READALL_SID == NvM_State))
    {
      /* @Trace: NvM_SUD_FUNC_209 */
      NvM_CheckConfigId();
    }
    if(NVM_REQ_NOT_OK == NvM_JobResultLowLevel) 
    {
      /* @Trace: NvM_SUD_FUNC_210 */
      NvM_EndProcessBlock(NvM_JobResultLowLevel);
      NvM_JobResultLowLevel = NVM_REQ_OK; /* To avoid case fail below */
    }
    else
  #endif
    {
      /* Write attemp to redundant block */
      /* Explicit */
      if(NVM_RE_CHKED_COPY == NvM_ReStatus)
      {
        /* @Trace: NvM_SUD_FUNC_211 */
        NvM_State = NVM_WRITEBLOCK_SID;
        NvM_SubState = NVM_PROCESS_WRITE_ACCEPT;
        NvM_BackUp = NVM_TRUE;
      }
      else
      /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
      #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
        if((&NvM_MirrorBuffer[0] == NvM_RamAddr) && (
          NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE 
          == (blkParams & NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE)))
        {
          /* @Trace: NvM_SUD_FUNC_213 */
          NvM_SubState = NVM_READ_REPEAT;
          #if(STD_ON == UPDATE_RAM_STATUS_ENABLE)
            NvM_UpdateRamStateStatus(NVM_INVALID_UNCHANGED);
          #endif
        }
        else
      #endif
        {
          /* @Trace: NvM_SUD_FUNC_212 */
          NvM_EndProcessBlock(NVM_REQ_OK);
        }
    } /* end else part of if(NVM_REQ_NOT_OK == NvM_JobResultLowLevel) */
}

/*******************************************************************************
** Function Name        : NvM_ProcessReadNotOkJob                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Request to copy the data of the NV block to its     **
**                        corresponding RAM block.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : status, memStatus                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized.                          **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_SubState, NvM_RamAddr, **
**                        NvM_BlkMngmntType, NvM_NvmBlkDescTbl,               **
**                        NvM_JobResultLowLevel, NvM_State, NvM_BlockIdx,     **
**                        NvM_RamStatus, NvM_RetryCount, NvM_ReStatus,        **
**                        NvM_JobResultFirstBlock, NvM_ConfigIdMatch,         **
**                        NvM_RestoreBlockstate                               **
**                        Function(s) invoked    : Dem_SetEventStatus(),      **
**                        NvM_EndProcessBlock(),                              **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION(),              **
*******************************************************************************/
NVM_STATIC FUNC(void, NVM_CODE) NvM_ProcessReadNotOkJob(
  VAR(Std_ReturnType, AUTOMATIC) status,
  VAR(MemIf_JobResultType, AUTOMATIC) memStatusin)
{
  VAR(uint8, AUTOMATIC) readRetry;
  P2VAR(uint16, AUTOMATIC, NVM_VAR_NOINIT) ptrRamStatus;
  VAR(MemIf_JobResultType, AUTOMATIC) memStatus;
  /* @Trace: NvM_SUD_MACRO_008 NvM_SUD_MACRO_042 */
  #if((STD_ON == NVM_DYNAMIC_CONFIGURATION) && \
    (0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS))
    P2VAR(uint16, AUTOMATIC, NVM_VAR_NOINIT) ptrTempBuffer;
  #endif

  readRetry = NvM_NvmBlkDescTbl->ucMaxNumOfReadRetries;
  ptrRamStatus = &NvM_RamStatus[NvM_BlockIdx];
  memStatus = memStatusin;

  if(NVM_ZERO != NvM_RetryCount)
  {
    /* @Trace: NvM_SUD_FUNC_221 */
    NvM_RetryCount--;
    NvM_SubState = NVM_READ_START;
  }
  else
  {
    if((NVM_BLOCK_REDUNDANT == NvM_BlkMngmntType) &&
      (NVM_RE_CHK_NONE == NvM_ReStatus))
    { /* start block comment 5 */
      /* @Trace: NvM_SUD_FUNC_222 */
      NvM_SubState = NVM_READ_START;
      /* Read redundant block accepted for processing */
      if(MEMIF_BLOCK_INVALID == memStatus)
      {
        NvM_ReStatus = NVM_RE_CHKED_COPY;
      }
      else
      {
        NvM_ReStatus = NVM_RE_CHKED_ORIGIN;
      }

      /* Hold previous job result */
      NvM_JobResultFirstBlock = NvM_JobResultLowLevel;
      /* Reloading Read retires counter */
      NvM_RetryCount = readRetry;
      SchM_Enter_NvM_RAM_STATUS_PROTECTION();
      /* @Trace: NvM_SUD_FUNC_223 */
      *(ptrRamStatus) &= NVM_SEC_REDUNDANT_MASK;
      *(ptrRamStatus) &= NVM_CHECK_DONE_REDUNDANT_MASK;
      *(ptrRamStatus) |= NVM_CHECK_LOSS_OF_REDUNDANCY;
      SchM_Exit_NvM_RAM_STATUS_PROTECTION();
      /* @Trace: NvM_SUD_MACRO_021 NvM_SUD_MACRO_042 */
      #if((STD_ON == NVM_DEMERROR_REPORT) && \
        (0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS))
        if((NVM_READALL_SID == NvM_State) && (E_NOT_OK == status))
        {
          /* @Trace: NvM_SUD_FUNC_224 */
          (void)Dem_SetEventStatus(NVM_E_REQ_FAILED, DEM_EVENT_STATUS_FAILED);
        }
      #endif
    } /* end block comment 5 */
    else
    { /* start block comment 6 */
      /* production  error NVM_E_LOSS_OF_REDUNDANCY */
      /* @Trace: NvM_SUD_MACRO_021 */
      #if(STD_ON == NVM_DEMERROR_REPORT)
        if((NVM_BLOCK_REDUNDANT == NvM_BlkMngmntType) && 
          (MEMIF_BLOCK_INVALID != memStatus))
        {
          /* @Trace: NvM_SUD_FUNC_225 */
          /* @Trace: NvM_SUD_MACRO_003 */
          (void)Dem_SetEventStatus(NVM_E_LOSS_OF_REDUNDANCY, 
            DEM_EVENT_STATUS_FAILED);
          /* Perform write to first block */
        }
        /* Request is rejected */
        if(E_NOT_OK == status)
        {
          /* @Trace: NvM_SUD_FUNC_226 */
          (void)Dem_SetEventStatus(NVM_E_REQ_FAILED, DEM_EVENT_STATUS_FAILED);
        }
      #endif

        /* Only 2 nv block is invalid, NVRAM block is invalid */
        if((NVM_BLOCK_REDUNDANT == NvM_BlkMngmntType) && 
          (MEMIF_BLOCK_INVALID == memStatus) &&
          (NVM_REQ_NV_INVALIDATED != NvM_JobResultFirstBlock))
        {
          /* @Trace: NvM_SUD_FUNC_227 */
          NvM_JobResultLowLevel = NvM_JobResultFirstBlock;
          memStatus = MEMIF_JOB_FAILED;
        }

      /* behave same Mismatch */
      /* @Trace: NvM_SUD_MACRO_008 NvM_SUD_MACRO_042 */
      #if((STD_ON == NVM_DYNAMIC_CONFIGURATION) && \
        (0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS))
        if((NVM_ONE == NvM_BlockIdx) && (NVM_READALL_SID == NvM_State))
        {
          /* @Trace: NvM_SUD_FUNC_228 */
          ptrTempBuffer = (void *)NvM_RamAddr;
          if(NULL_PTR != ptrTempBuffer)
          {
            /* @Trace: NvM_SUD_MACRO_011 */
            *ptrTempBuffer = NVM_COMPILED_CONFIG_ID;
          }
          /* Config ID is match in case 2 nv block is invalid */
          if(MEMIF_BLOCK_INVALID == memStatus)
          {
            /* @Trace: NvM_SUD_FUNC_229 */
            NvM_ConfigIdMatch = NVM_TRUE;
          }
          else
          {
            /* @Trace: NvM_SUD_FUNC_230 */
            NvM_ConfigIdMatch = NVM_FALSE;
          }
        }
      #endif
      /* Two block of redundant can't be read => report loss of redundancy and mark block as loss of redundancy */
      /* in case readall and block 1 not report */

        if(((MEMIF_BLOCK_INCONSISTENT == memStatus) || 
          (MEMIF_JOB_FAILED == memStatus)) &&
          (NVM_BLOCK_DATASET != NvM_BlkMngmntType)
          /* @Trace: NvM_SUD_MACRO_008 NvM_SUD_MACRO_042 */
          #if((STD_ON == NVM_DYNAMIC_CONFIGURATION) && \
            (0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS))
            && ((NVM_READALL_SID != NvM_State) || (NVM_ONE != NvM_BlockIdx))
          #endif
        )
        {
          /* @Trace: NvM_SUD_FUNC_231 */
          NvM_RestoreBlockstate = NVM_RESTORE_START;
          NvM_SubState = NVM_READ_ROM;
        }
        else
        {
          /* @Trace: NvM_SUD_FUNC_232 */
          SET_READ_PRIOR();
          NvM_EndProcessBlock(NvM_JobResultLowLevel);
        }
    } /* end block comment 6 */
  } /* end else part of  if(NVM_ZERO != NvM_RetryCount) */
}

/*******************************************************************************
** Function Name        : NvM_ProcessReadNvBlock                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Request to copy the data of the NV block to its     **
**                        corresponding RAM block.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized.                          **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_SubState, NvM_State,   **
**                        NvM_BlkMngmntType, NvM_NvmBlkDescTbl, NvM_BlockIdx, **
**                        NvM_JobResultLowLevel, NvM_ReStatus, NvM_CrcStepCnt,**
**                        NvM_BlockLength, NvM_WriteVerify, NvM_RetryCount    **
**                        Function(s) invoked    : NvM_ProcessWriteBlock(),   **
**                        NvM_CompareCRCSID(), NvM_StoreCrcOffset(),          **
**                        MemIf_GetJobResult(), NvM_CalculateCRCStaticID(),   **
**                        NvM_ProcessReadOkJob(), Dem_SetEventStatus(),       **
**                        NvM_ProcessReadNotOkJob()                           **
*******************************************************************************/
/* @Trace: SRS_Mem_00011 */
NVM_STATIC FUNC(void, NVM_CODE) NvM_ProcessReadNvBlock(void)
{
  VAR(MemIf_JobResultType, AUTOMATIC) memStatus;
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  VAR(Std_ReturnType, AUTOMATIC) status;
  VAR(uint8, AUTOMATIC) deviceID;
  /* @Trace: NvM_SUD_MACRO_017 NvM_SUD_MACRO_040 */
  #if((STD_ON == NVM_STATIC_ID_CHECK) || \
      (STD_ON == NVM_CRC_SUPPORT))
    VAR(uint16, AUTOMATIC) blkParams;
  #endif

  memStatus = MEMIF_JOB_FAILED;
  returnValue = E_OK;
  status = E_OK;
  /* @Trace: NvM_SUD_MACRO_017 NvM_SUD_MACRO_040 */
  #if((STD_ON == NVM_STATIC_ID_CHECK) || \
      (STD_ON == NVM_CRC_SUPPORT))
    /* @Trace: NvM_SUD_FUNC_511 */
    blkParams = NvM_NvmBlkDescTbl->usBlkParams;
  #endif
  deviceID = NvM_NvmBlkDescTbl->ucNvramDeviceId;
  /* Wait for the MEMIF layer to process the request */
  if(NVM_REQ_PENDING != NvM_JobResultLowLevel)
  {
    /* @Trace: NvM_SUD_MACRO_046 */
    /* If the Read of NV block is successful */
    #if(STD_ON == NVM_WRITE_VERIFICATION)
      if(NVM_ZERO != NvM_WriteVerify)
      {
        /* @Trace: NvM_SUD_FUNC_584 */
        NvM_State = NVM_WRITEBLOCK_SID;
        NvM_SubState = NVM_PROCESS_WRITE_VERIFY;
        NvM_ProcessWriteBlock();
      }
      else
    #endif
      {
        if((NVM_REQ_OK == NvM_JobResultLowLevel)
          /* @Trace: NvM_SUD_MACRO_028 */
          &&(NVM_MIRROR_BUFFER >= NvM_BlockLength))
        { /* start block comment 3 */
          /* @Trace: NvM_SUD_MACRO_017 NvM_SUD_MACRO_040 */
          #if((STD_ON == NVM_STATIC_ID_CHECK) || \
              (STD_ON == NVM_CRC_SUPPORT))
            if((NVM_CALC_RAM_BLK_CRC == (blkParams & 
              NVM_CALC_RAM_BLK_CRC)) || (NVM_STATIC_BLOCK_ID_CHECK == 
              (blkParams & NVM_STATIC_BLOCK_ID_CHECK)))
            { /* start block comment 4 */
              /* @Trace: NvM_SUD_FUNC_583 */
              /* calculate CRC and SID for Read data */
              NvM_CalculateCRCStaticID();
              /* @Trace: NvM_SUD_MACRO_017 */
              #if(STD_ON == NVM_CRC_SUPPORT)
                if(NVM_ZERO == NvM_CrcStepCnt)
              #endif
                {
                  /* @Trace: NvM_SUD_FUNC_202 */
                  returnValue = NvM_CompareCRCSID();
                  /* @Trace: NvM_SUD_MACRO_004 NvM_SUD_MACRO_017 */
                  #if((STD_ON == NVM_CRC_SUPPORT) && \
                    (STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM)) 
                    if((NVM_BLOCK_USE_CRC_COMP_MASK == (blkParams &
                      NVM_BLOCK_USE_CRC_COMP_MASK)) && 
                      (NVM_CALC_RAM_BLK_CRC ==
                      (blkParams & NVM_CALC_RAM_BLK_CRC)))
                    {
                      NvM_StoreCrcOffset();
                    }
                  #endif
                }
              /* @Trace: NvM_SUD_MACRO_017 */
              #if(STD_ON == NVM_CRC_SUPPORT)
                else
                {
                  /* @Trace: NvM_SUD_FUNC_203 */
                  returnValue = E_NOT_OK;
                }
              #endif
            } /* end block comment 4 */
            if(E_OK == returnValue)
          #endif
            {
              /* @Trace: NvM_SUD_FUNC_512 */
              NvM_ProcessReadOkJob();
            } /* @End of if(E_OK == returnValue) */
        } /* end block comment 3 */

        if(NVM_REQ_OK != NvM_JobResultLowLevel)
        {
          if(NVM_REQ_NV_INVALIDATED == NvM_JobResultLowLevel)
          {
            /* @Trace: NvM_SUD_FUNC_216 */
            NvM_JobResultLowLevel = NVM_REQ_NOT_OK;
            status = E_NOT_OK;
          }

          if((E_OK == status) && (E_OK == returnValue))
          {
            /* @Trace: NvM_SUD_FUNC_218 */
            memStatus = MemIf_GetJobResult(deviceID);
            if(MEMIF_BLOCK_INVALID == memStatus)
            {
              /* @Trace: NvM_SUD_FUNC_214 */
              NvM_JobResultLowLevel = NVM_REQ_NV_INVALIDATED;
            }
            /* @Trace: NvM_SUD_MACRO_042 */
            #if(0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS)
            else if((NVM_READALL_SID == NvM_State) && (NVM_ONE == NvM_BlockIdx))
            {
              /* @Trace: NvM_SUD_FUNC_215 */
              NvM_JobResultLowLevel = NVM_REQ_INTEGRITY_FAILED;
              /* @Trace: NvM_SUD_MACRO_021 */
              #if(STD_ON == NVM_DEMERROR_REPORT)
                (void)Dem_SetEventStatus(NVM_E_REQ_FAILED, 
                  DEM_EVENT_STATUS_FAILED);
                (void)Dem_SetEventStatus(NVM_E_HARDWARE, 
                  DEM_EVENT_STATUS_FAILED);
              #endif
            }
            #endif
            else if(MEMIF_BLOCK_INCONSISTENT == memStatus)
            {
              /* @Trace: NvM_SUD_FUNC_217 */
              NvM_JobResultLowLevel = NVM_REQ_INTEGRITY_FAILED;
              /* @Trace: NvM_SUD_MACRO_021 */
              #if(STD_ON == NVM_DEMERROR_REPORT)
                if((NVM_BLOCK_REDUNDANT != NvM_BlkMngmntType) || 
                  ((NVM_RE_CHK_NONE != NvM_ReStatus) && 
                  (NVM_ZERO == NvM_RetryCount)) ||
                  (NVM_READALL_SID == NvM_State))
                {
                  (void)Dem_SetEventStatus
                    (NVM_E_INTEGRITY_FAILED, DEM_EVENT_STATUS_FAILED);
                  (void)Dem_SetEventStatus
                    (NVM_E_HARDWARE, DEM_EVENT_STATUS_FAILED);
                }
              #endif
            } /* end of else if(MEMIF_BLOCK_INCONSISTENT == memStatus) */
            else if(MEMIF_JOB_FAILED == memStatus)
            {
              /* @Trace: NvM_SUD_FUNC_219 */
              NvM_JobResultLowLevel = NVM_REQ_NOT_OK;
              /* @Trace: NvM_SUD_MACRO_021 */
              #if(STD_ON == NVM_DEMERROR_REPORT)
                if((NVM_BLOCK_REDUNDANT != NvM_BlkMngmntType) || 
                  ((NVM_RE_CHK_NONE != NvM_ReStatus) && 
                  (NVM_ZERO == NvM_RetryCount)) ||
                  (NVM_READALL_SID == NvM_State))
                {
                  (void)Dem_SetEventStatus
                    (NVM_E_REQ_FAILED, DEM_EVENT_STATUS_FAILED);
                  (void)Dem_SetEventStatus
                    (NVM_E_HARDWARE, DEM_EVENT_STATUS_FAILED);
                }
              #endif
            } /* end of else if(MEMIF_JOB_FAILED == memStatus) */
            else
            {
            }
          } /* end of if((E_OK == status) && (E_OK == returnValue)) */
          /* @Trace: NvM_SUD_FUNC_513 */
          NvM_ProcessReadNotOkJob(status, memStatus);
        } /* end of if(NVM_REQ_OK != NvM_JobResultLowLevel) */
      } /* end else part of if(NVM_ZERO != NvM_WriteVerify) */
  } /* end of if(NVM_REQ_PENDING != NvM_JobResultLowLevel) */
}

/*******************************************************************************
** Function Name        : NvM_ProcessReadStart                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Request to copy the data of the NV block to its     **
**                        corresponding RAM block.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized.                          **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_JobResultLowLevel,     **
**                        NvM_BlkMngmntType, NvM_NvmBlkDescTbl, NvM_BlockIdx, **
**                        NvM_SubState, NvM_WriteVerify, NvM_MirrorBuffer,    **
**                        NvM_BlockLength, NvM_RamIndex, NvM_DataBuffer,      **
**                        NvM_RestoreBlockstate                               **
**                        Function(s) invoked    : NvM_CalcBlkNumber(),       **
**                        MemIf_Read()                                        **
*******************************************************************************/
/* @Trace: SRS_Mem_00011 SRS_Mem_08000 */
NVM_STATIC FUNC(void, NVM_CODE) NvM_ProcessReadStart(void)
{
  VAR(Std_ReturnType, AUTOMATIC) status;
  /* @Trace: NvM_SUD_MACRO_017 */
  #if(STD_ON == NVM_CRC_SUPPORT)
    VAR(uint8, AUTOMATIC) varCrcLength;
  #endif
    VAR(uint8, AUTOMATIC) deviceID;
    VAR(uint16, AUTOMATIC) blkNumber;
  /* @Trace: NvM_SUD_MACRO_017 NvM_SUD_MACRO_040 */
  #if((STD_ON == NVM_CRC_SUPPORT) || (STD_ON == NVM_STATIC_ID_CHECK))
    VAR(uint16, AUTOMATIC) blkParams;
  #endif
    VAR(uint16, AUTOMATIC) totalLength;
  /* @Trace: NvM_SUD_MACRO_046 */
  #if(STD_ON == NVM_WRITE_VERIFICATION)
    VAR(uint16, AUTOMATIC) verifyDataSize;
    VAR(uint16, AUTOMATIC) varOffset;
  #endif
  /* @Trace: NvM_SUD_FUNC_438 NvM_SUD_MACRO_017 NvM_SUD_MACRO_040 */
  #if((STD_ON == NVM_CRC_SUPPORT) || (STD_ON == NVM_STATIC_ID_CHECK))
    blkParams = NvM_NvmBlkDescTbl->usBlkParams;
  #endif
  deviceID = NvM_NvmBlkDescTbl->ucNvramDeviceId;
  /* @Trace: NvM_SUD_MACRO_017 */
  #if(STD_ON == NVM_CRC_SUPPORT)
    varCrcLength = NvM_NvmBlkDescTbl->ucCrcLength;
  #endif
  /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
  #if(STD_ON == NVM_DATASET_PRESENT)
    /* If atleast one Dataset block is configured */
    /*
    * RamBlock Index : RamIndex < ucNumOfNvBlks
    * RomBlock Index : RamIndex >= ucNumOfNvBlks
    */
    if((NVM_BLOCK_DATASET == NvM_BlkMngmntType) &&
      ((NvM_NvmBlkDescTbl->ucNumOfNvBlks) <= NvM_RamIndex[NvM_BlockIdx]))
    {
      /* @Trace: NvM_SUD_FUNC_198 */
      /* Index of Dataset ROM block is pointing to ROM block area */
      NvM_RestoreBlockstate = NVM_RESTORE_START;
      NvM_SubState = NVM_READ_ROM;
    }
    else
  #endif
    { /* start block comment 2 */
      /* @Trace: NvM_SUD_FUNC_199 */
      blkNumber = NvM_CalcBlkNumber();
      /* Calculate Length */
      totalLength = NVM_ZERO;
      /* @Trace: NvM_SUD_MACRO_040 */
      #if(STD_ON == NVM_STATIC_ID_CHECK)
        if(NVM_STATIC_BLOCK_ID_CHECK == (blkParams & NVM_STATIC_BLOCK_ID_CHECK))
        {
          totalLength = NVM_TWO;
        }
      #endif
      /* @Trace: NvM_SUD_MACRO_017 */
      #if(STD_ON == NVM_CRC_SUPPORT)
        if(NVM_CALC_RAM_BLK_CRC == (blkParams & NVM_CALC_RAM_BLK_CRC))
        {
          totalLength += varCrcLength;
        }
      #endif
        NvM_JobResultLowLevel = NVM_REQ_PENDING;
      /* Read NV block */
      /* @Trace: NvM_SUD_MACRO_046 */
      #if(STD_ON == NVM_WRITE_VERIFICATION)
        if(NVM_ZERO != NvM_WriteVerify)
        {
          /* @Trace: NvM_SUD_FUNC_200 */
          /* verify data size is always lower or equal NvBlock size in validate rule */
          verifyDataSize = NvM_NvmBlkDescTbl->usWriteVerificationDataSize;
          varOffset = (NvM_WriteVerify - NVM_ONE) * verifyDataSize;
          if(((NvM_BlockLength + totalLength) - varOffset) < verifyDataSize)
          {
            verifyDataSize = (NvM_BlockLength + totalLength) - varOffset;
          }
          status = MemIf_Read(deviceID, blkNumber,
            varOffset, &NvM_MirrorBuffer[0], verifyDataSize);
        } /* end of if(NVM_ZERO != NvM_WriteVerify) */
        else
      #endif
        {
          /* @Trace: NvM_SUD_FUNC_201 */
          status = MemIf_Read(deviceID, blkNumber, NVM_ZERO, NvM_DataBuffer, 
            NvM_BlockLength + totalLength);
        }

        /* If MEMIF layer accepts the request */
        if (E_OK != status)
        {
          /* @Trace: NvM_SUD_FUNC_439 */
          /* Read data is being processed */
          NvM_JobResultLowLevel = NVM_REQ_NV_INVALIDATED;
        }
        else
        {
          /* @Trace: NvM_SUD_FUNC_441 */
        }
        NvM_SubState = NVM_READ_NVBLOCK;
    } /* end block comment 2 */
}

/*******************************************************************************
** Function Name        : NvM_ProcessReadBlock                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Request to copy the data of the NV block to its     **
**                        corresponding RAM block.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized.                          **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_MirrorCount,           **
**                        NvM_BlkMngmntType, NvM_NvmBlkDescTbl, NvM_BlockIdx, **
**                        NvM_SubState, NvM_JobResultLowLevel, NvM_RamIndex,  **
**                        NvM_MirrorBuffer, NvM_RestoreBlockstate             **
**                        Function(s) invoked    : NvM_ProcessRestoreBlock(), **
**                        NvM_ProcessReadStart(), NvM_ProcessReadNvBlock(),   **
**                        NvM_EndProcessBlock(), Dem_SetEventStatus()         **
*******************************************************************************/
/* @Trace: SRS_LIBS_08533 SRS_Mem_00016 SRS_Mem_00027 SRS_Mem_00129 SRS_Mem_08547 SRS_Mem_08554 SRS_BSW_00339 SRS_Mem_08529 */
FUNC(void, NVM_CODE) NvM_ProcessReadBlock(void)
{
  /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
  #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
    VAR(Std_ReturnType, AUTOMATIC) returnValue;
  #endif
  
  if((NULL_PTR != NvM_NvmBlkDescTbl) && 
    (NVM_TOTAL_NUM_OF_NVRAM_BLOCKS > NvM_BlockIdx))
  { /* start block comment 1 */
    switch (NvM_SubState)
    {
      case NVM_READ_START:
        /* @Trace: NvM_SUD_FUNC_509 */
        NvM_ProcessReadStart();
      break;

      case NVM_READ_NVBLOCK:
        /* @Trace: NvM_SUD_FUNC_510 */
        NvM_ProcessReadNvBlock();
      break;

      case NVM_READ_ROM:
        /* @Trace: NvM_SUD_FUNC_233 */
        /* Restore from the ROM, if read request to MEMIF is unsuccessful */
        NvM_ProcessRestoreBlock();
        if(NVM_IDLE == NvM_RestoreBlockstate)
        {
          /* @Trace: NvM_SUD_FUNC_234 */
          SET_READ_PRIOR();
          /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
          #if(STD_ON == NVM_DATASET_PRESENT)
            /* If atleast one Dataset block is configured */
            /*
            * RamBlock Index : RamIndex < ucNumOfNvBlks
            * RomBlock Index : RamIndex >= ucNumOfNvBlks
            */
            if((NVM_BLOCK_DATASET == NvM_BlkMngmntType) &&
              ((NvM_NvmBlkDescTbl->ucNumOfNvBlks) <=
              NvM_RamIndex[NvM_BlockIdx]))
            {
              /* Index of Dataset ROM block is pointing to ROM block area */
              if(NVM_REQ_RESTORED_FROM_ROM == NvM_JobResultLowLevel)
              {
                NvM_EndProcessBlock(NVM_REQ_OK);
              }
              else
              {
                NvM_EndProcessBlock(NvM_JobResultLowLevel);
              }
            }
            else
          #endif
            {
              NvM_EndProcessBlock(NvM_JobResultLowLevel);
            }
        } /* @End of if(NVM_IDLE == NvM_RestoreBlockstate) */
      break;
      /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
      #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
        case NVM_READ_REPEAT:
          /* @Trace: NvM_SUD_FUNC_235 */
          returnValue = E_OK;
          if(NULL_PTR != NvM_NvmBlkDescTbl->pNvMReadRamBlockFromNvm)
          {
            returnValue = (NvM_NvmBlkDescTbl->pNvMReadRamBlockFromNvm)
              ((void *)(&NvM_MirrorBuffer[0]));
          }
          if(E_OK == returnValue)
          {
            /* @Trace: NvM_SUD_FUNC_236 */
            #if(STD_ON == UPDATE_RAM_STATUS_ENABLE)
              NvM_UpdateRamStateStatus(NVM_VALID_UNCHANGED);
            #endif
            NvM_EndProcessBlock(NVM_REQ_OK);
          }
          else
          {
            if(NVM_ZERO == NvM_MirrorCount)
            {
              /* @Trace: NvM_SUD_MACRO_021 */
              #if(STD_ON == NVM_DEMERROR_REPORT)
                /* @Trace: NvM_SUD_FUNC_237 */
                (void)Dem_SetEventStatus(NVM_E_REQ_FAILED, 
                  DEM_EVENT_STATUS_FAILED);
              #endif
                /* @Trace: NvM_SUD_FUNC_238 */
                NvM_EndProcessBlock(NVM_REQ_NOT_OK);
            }
            else
            {
              /* @Trace: NvM_SUD_FUNC_239 */
              NvM_MirrorCount--;
            }
          }
          break;
      #endif

      default:
        /* Do nothing */
      break;
    } /* end switch (NvM_SubState) */
  } /* end block comment 1 */
} /* end of function body */

/*******************************************************************************
** Function Name        : NvM_RestoreBlockProcess                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function Restore the contents of ROM in to RAM **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_RamAddr,               **
**                        NvM_BlkDescTbls, NvM_BlockIdx, NvM_State,           **
**                        NvM_JobResultLowLevel, NvM_ReadAllRequest,          **
**                        NvM_FirstInitAllRequest, NvM_ConfigIdMatch,         **
**                        NvM_RestoreBlockstate, NvM_MirrorBuffer             **
**                                                                            **
**                        Function(s) invoked    : None                       **
*******************************************************************************/
NVM_STATIC FUNC(void, NVM_CODE) NvM_RestoreBlockProcess(void)
{
  P2CONST(uint8, AUTOMATIC, NVM_CONST) ptrRomBlkDataAddrs;
  P2CONST(NvM_BlkDescTbl, AUTOMATIC, NVM_CONST) ptrBlkDescTbl;
  /* @Trace: NvM_SUD_MACRO_024 */
  #if(STD_ON == NVM_INIT_CALLBACK)
    VAR(Std_ReturnType, AUTOMATIC) status;
    /* @Trace: NvM_SUD_DATATYPE_010 */
    VAR(NvM_InitBlockRequestType, AUTOMATIC) initRequest;
  #endif
  /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
  #if(STD_ON == NVM_DATASET_PRESENT)
    VAR(uint16, AUTOMATIC) romOffset;
  #endif

  VAR(uint16, AUTOMATIC) romBlockLength;
  VAR(uint16, AUTOMATIC) count;
  /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_008 NvM_SUD_MACRO_042 NvM_SUD_MACRO_032 */
  #if(((STD_ON == NVM_DYNAMIC_CONFIGURATION) && \
    (0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS)) || \
    (STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM))
    VAR(uint16, AUTOMATIC) blkParams;
  #endif

  /* @Trace: NvM_SUD_FUNC_484 NvM_SUD_MACRO_005 NvM_SUD_MACRO_008 NvM_SUD_MACRO_042 NvM_SUD_MACRO_032 */
  ptrBlkDescTbl = &NvM_BlkDescTbls[NvM_BlockIdx];
  #if(((STD_ON == NVM_DYNAMIC_CONFIGURATION) && \
    (0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS)) || \
    (STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM))
    blkParams = ptrBlkDescTbl->usBlkParams;
  #endif
  ptrRomBlkDataAddrs = ptrBlkDescTbl->pRomBlkData;

  if(NULL_PTR == ptrRomBlkDataAddrs)
  {
    /*
     * If ROM is not configured, check if InitCallback function is
     * configured for the block
     */
    /* @Trace: NvM_SUD_MACRO_024 */
    #if(STD_ON == NVM_INIT_CALLBACK)
      if(NULL_PTR != ptrBlkDescTbl->pNvMInitNotification_BlockId)
      {
        /* @Trace: NvM_SUD_FUNC_100 */
        if((NVM_RESTOREBLOCKDEFAULTS_SID == NvM_State) || 
          (NVM_RESTOREPRAMBLOCKDEFAULTS_SID == NvM_State))
        {
          initRequest = NVM_INIT_RESTORE_BLOCK_DEFAULTS;
        }
        /* @Trace: NvM_SUD_MACRO_042 */
        #if(0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS)
          else if(NVM_MULTIBLK_IN_PROGRESS == NvM_ReadAllRequest)
          {
            initRequest = NVM_INIT_READ_ALL_BLOCK;
          }
        #endif
        /* @Trace: NvM_SUD_MACRO_041 NvM_SUD_MACRO_047 */
        #if((0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS) && \
          (NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS))
          else if(NVM_MULTIBLK_IN_PROGRESS == NvM_FirstInitAllRequest)
          {
            initRequest = NVM_INIT_FIRST_INIT_ALL;
          }
        #endif
          else
          {
            initRequest = NVM_INIT_READ_BLOCK;
          }

          /* @Trace: NvM_SUD_FUNC_101 */
          status = ptrBlkDescTbl->pNvMInitNotification_BlockId(initRequest);

          if(E_OK == status)
          {
            /*
             * If InitCallback function returns E_OK, then update the RAM
             * status
             */
            if((NVM_RESTOREBLOCKDEFAULTS_SID == NvM_State) || 
              (NVM_RESTOREPRAMBLOCKDEFAULTS_SID == NvM_State))
            {
              /* @Trace: NvM_SUD_FUNC_103 */
              NvM_JobResultLowLevel = NVM_REQ_OK;
            }
            else
            {
              /* @Trace: NvM_SUD_FUNC_104 */
              NvM_JobResultLowLevel = NVM_REQ_RESTORED_FROM_ROM;
            }
          }
          else
          {
            /* @Trace: NvM_SUD_FUNC_102 */
            NvM_JobResultLowLevel = NVM_REQ_NOT_OK;
          }
      } /* end of if(NULL_PTR != ptrBlkDescTbl->pNvMInitNotification_BlockId) */
      else
    #endif
      {
        /* @Trace: NvM_SUD_FUNC_105 */
        /* Even not INIT_CALLBACK&ROM Block, result should be NVM_REQ_NOT_OK */
        if((NVM_READBLOCK_SID != NvM_State) && 
          (NVM_READPRAMBLOCK_SID != NvM_State)
          /* @Trace: NvM_SUD_MACRO_042 */
          #if(0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS)
          && ((NVM_READALL_SID != NvM_State) 
          /* @Trace: NvM_SUD_MACRO_008 */
          #if(STD_ON == NVM_DYNAMIC_CONFIGURATION)
            || ((NVM_FALSE == NvM_ConfigIdMatch) &&
            (NVM_RESISTANT_TO_CHANGED_SW != (blkParams & 
            NVM_RESISTANT_TO_CHANGED_SW)))
          #endif
          )
          #endif
          )
        {
          NvM_JobResultLowLevel = NVM_REQ_NOT_OK;
        }
      }
      NvM_RestoreBlockstate = NVM_RESTORE_END;
  }  /* @End of if(NULL_PTR == ptrRomBlkDataAddrs) */
  else
  {
    /* Load the total number of bytes to be copied from ROM */
    romBlockLength = (ptrBlkDescTbl->usNvBlkDataLength);
    /* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
    #if(STD_ON == NVM_DATASET_PRESENT)
      if((NVM_BLOCK_DATASET == ptrBlkDescTbl->enBlkMngmntType) &&
        ((ptrBlkDescTbl->ucNumOfNvBlks) <= NvM_RamIndex[NvM_BlockIdx]))
      {
        /* @Trace: NvM_SUD_FUNC_106 */
        /* In case of dataset ROM calculate ROM Offset */
        romOffset = (uint16)NvM_RamIndex[NvM_BlockIdx] -
          (uint16)(ptrBlkDescTbl->ucNumOfNvBlks);
        ptrRomBlkDataAddrs = &ptrRomBlkDataAddrs[(uint32)romBlockLength *
          (uint32)romOffset];
      }
    #endif

      /*
       * Update the Permanent RAM (if configured) status to 'valid and
       * changed' after loading the default values
       */

      /* @Trace: NvM_SUD_FUNC_107 */
      count = NVM_ZERO;
      /* Copy ROM data to RAM block */
      if(NULL_PTR != NvM_RamAddr)
      {
        while(NVM_ZERO != romBlockLength)
        {
          NvM_RamAddr[count] = ptrRomBlkDataAddrs[count];
          count++;
          romBlockLength--;
        }
      }
    /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
    #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
      if((&NvM_MirrorBuffer[0] == NvM_RamAddr) && (
        NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE == 
        (blkParams & NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE)))
      {
        /* @Trace: NvM_SUD_FUNC_108 */
        NvM_RestoreBlockstate = NVM_RESTORE_REPEAT;
      }
      else
    #endif
      {
        /* @Trace: NvM_SUD_FUNC_109 */
        if((NVM_RESTOREBLOCKDEFAULTS_SID == NvM_State) || 
          (NVM_RESTOREPRAMBLOCKDEFAULTS_SID == NvM_State))
        {
          NvM_JobResultLowLevel = NVM_REQ_OK;
        }
        else
        {
          NvM_JobResultLowLevel = NVM_REQ_RESTORED_FROM_ROM;
        }
        NvM_RestoreBlockstate = NVM_RESTORE_END;
      }
  } /* end else part of if(NULL_PTR == ptrRomBlkDataAddrs) */
}

/*******************************************************************************
** Function Name        : NvM_ProcessRestoreBlock                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function Restore the contents of ROM in to RAM **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_BlockIdx,              **
**                        NvM_BlkDescTbls ,NvM_State, NvM_RestoreBlockstate,  **
**                        NvM_ReadAllState, NvM_JobResultLowLevel,            **
**                        NvM_MirrorBuffer, NvM_MirrorCount,                  **
**                        NvM_ConfigIdMatch, NvM_CrcStepCnt                   **
**                                                                            **
**                        Function(s) invoked    : NvM_EndProcessBlock(),     **
**                        NvM_RestoreBlockProcess(), Dem_SetEventStatus(),    **
**                        NvM_CalculateCRCStaticID()                          **
*******************************************************************************/
/* @Trace: SRS_Mem_00018 SRS_Mem_08010 SRS_Mem_08542 SRS_Mem_08548 */
FUNC(void, NVM_CODE) NvM_ProcessRestoreBlock(void)
{
  P2CONST(NvM_BlkDescTbl, AUTOMATIC, NVM_CONST) ptrBlkDescTbl;
  /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
  #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
    VAR(Std_ReturnType, AUTOMATIC) status;
  #endif
  /* @Trace: NvM_SUD_MACRO_008 NvM_SUD_MACRO_017 NvM_SUD_MACRO_042 */
  #if((STD_ON == NVM_CRC_SUPPORT) || \
    ((STD_ON == NVM_DYNAMIC_CONFIGURATION) && \
    (0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS)))
    VAR(uint16, AUTOMATIC) blkParams;
  #endif

  switch (NvM_RestoreBlockstate)
  {
    /* Check if ROM block is configured */
    case NVM_RESTORE_START:
      /* @Trace: NvM_SUD_FUNC_507 */
      NvM_RestoreBlockProcess();
    break;
    /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
    #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
      case NVM_RESTORE_REPEAT:
        /* @Trace: NvM_SUD_FUNC_110 */
        status = E_OK;
        if(NULL_PTR != NvM_NvmBlkDescTbl)
        {
          if(NULL_PTR != NvM_NvmBlkDescTbl->pNvMReadRamBlockFromNvm)
          {
            status = (NvM_NvmBlkDescTbl->pNvMReadRamBlockFromNvm)
              ((void *)&NvM_MirrorBuffer[0]);
          }
        }
        if(E_OK != status)
        {
          if(NVM_ZERO == NvM_MirrorCount)
          {
            /* @Trace: NvM_SUD_FUNC_112 */
            NvM_JobResultLowLevel = NVM_REQ_NOT_OK;
            /* @Trace: NvM_SUD_MACRO_021 */
            #if(STD_ON == NVM_DEMERROR_REPORT)
              (void)Dem_SetEventStatus(
                NVM_E_REQ_FAILED, DEM_EVENT_STATUS_FAILED);
            #endif
            NvM_RestoreBlockstate = NVM_RESTORE_END;
          }
          else
          {
            /* @Trace: NvM_SUD_FUNC_111 */
            NvM_MirrorCount--;
          }
        }
        else
        {
          /* @Trace: NvM_SUD_FUNC_113 */
          if((NVM_RESTOREBLOCKDEFAULTS_SID == NvM_State) || 
            (NVM_RESTOREPRAMBLOCKDEFAULTS_SID == NvM_State))
          {
            NvM_JobResultLowLevel = NVM_REQ_OK;
          }
          else
          {
            NvM_JobResultLowLevel = NVM_REQ_RESTORED_FROM_ROM;
          }
          NvM_RestoreBlockstate = NVM_RESTORE_END;
        }
      break;
    #endif

    case NVM_RESTORE_END:
      /* @Trace: NvM_SUD_FUNC_529 */
      ptrBlkDescTbl = &NvM_BlkDescTbls[NvM_BlockIdx];
      /* @Trace: NvM_SUD_MACRO_008 NvM_SUD_MACRO_017 NvM_SUD_MACRO_042 */
      #if((STD_ON == NVM_CRC_SUPPORT) || \
        ((STD_ON == NVM_DYNAMIC_CONFIGURATION) && \
        (0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS)))
        blkParams = ptrBlkDescTbl->usBlkParams;
      #endif

      if((NVM_REQ_OK == NvM_JobResultLowLevel) || 
        (NVM_REQ_RESTORED_FROM_ROM == NvM_JobResultLowLevel))
      { /* start block comment 1 */
      /* @Trace: NvM_SUD_MACRO_008 NvM_SUD_MACRO_042 */
        #if((STD_ON == NVM_DYNAMIC_CONFIGURATION) && \
          (0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS))
          if((NVM_FALSE == NvM_ConfigIdMatch) &&
            (NVM_RESISTANT_TO_CHANGED_SW != (blkParams & 
            NVM_RESISTANT_TO_CHANGED_SW)) && (NVM_READALL_SID == NvM_State))
          {
            /* @Trace: NvM_SUD_FUNC_115 */
            #if(STD_ON == UPDATE_RAM_STATUS_ENABLE)
              NvM_UpdateRamStateStatus(NVM_INVALID_UNCHANGED);
            #endif
            /* Switch to NVM_REQ_OK for extended runtime */
            NvM_JobResultLowLevel = NVM_REQ_OK;
          }
          else
        #endif
          {
            /* @Trace: NvM_SUD_FUNC_116 */
            #if(STD_ON == UPDATE_RAM_STATUS_ENABLE)
              NvM_UpdateRamStateStatus(NVM_VALID_CHANGED);
            #endif
          }

          if(ptrBlkDescTbl->pRomBlkData != NULL_PTR)
          {
            /* If CRC is configured to calculate CRC on ROM data */
            /* @Trace: NvM_SUD_MACRO_017 */
            #if(STD_ON == NVM_CRC_SUPPORT)
            if(NVM_CALC_RAM_BLK_CRC == (blkParams & NVM_CALC_RAM_BLK_CRC))
            {
              /* @Trace: NvM_SUD_FUNC_117 */
              NvM_CalculateCRCStaticID();
            }
            #endif
          }
      } /* end block comment 1 */
    /* Restoring the data form ROM is done in cycles */

    /*
     * If the restore operation is complete update the global variables by
     * considering from where 'restore' function was invoked
     * (Read/ReadAll/restore)
     */
      /* @Trace: NvM_SUD_MACRO_017 */
      #if(STD_ON == NVM_CRC_SUPPORT)
        if(NVM_ZERO == NvM_CrcStepCnt)
      #endif
        {
          /* @Trace: NvM_SUD_FUNC_114 */
          if((NVM_RESTOREBLOCKDEFAULTS_SID == NvM_State)
            || (NVM_READALL_ROMBLK_PROCESS == NvM_ReadAllState)
            || (NVM_RESTOREPRAMBLOCKDEFAULTS_SID == NvM_State))
          {
            NvM_EndProcessBlock(NvM_JobResultLowLevel);
          }
          NvM_RestoreBlockstate = NVM_IDLE;
        }
    break;

    default:
      /* Do nothing */
    break;
  } /* end of switch (NvM_RestoreBlockstate) */
} /* End of function body */

/*******************************************************************************
** Function Name        : NvM_ScanQueue                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function performs the scanning operation of all     **
**                        the queues and triggers the task according to the   **
**                        priority                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : status                                              **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_PrevReqImm,            **
**                        NvM_StdPrevReq, NvM_NvmBlkDescTbl, NvM_State        **
**                        NvM_BlkDescTbls, NvM_RamAddr, NvM_BlockIdx,         **
**                        NvM_SubState, NvM_RetryCount, NvM_MirrorBuffer,     **
**                        NvM_RestoreBlockstate                               **
**                        Function(s) invoked    : NvM_ProcessReadBlock(),    **
**                        NvM_UpdateGlobalVars(), NvM_CalculateCrcOffset(),   **
**                        NvM_ProcessEraseInvalidBlk(), NvM_StdQueueRead(),   **
**                        NvM_ProcessRestoreBlock()                           **
*******************************************************************************/
/* @Trace: SRS_Mem_08534 NvM_SUD_MACRO_047 */
#if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
NVM_STATIC FUNC(boolean, NVM_CODE) NvM_ScanQueue(void)
{
  VAR(NvM_JobQueue, AUTOMATIC) jobQueueVal;
  VAR(boolean, AUTOMATIC) status;
  /* @Trace: NvM_SUD_MACRO_023 NvM_SUD_MACRO_025 */
  #if((STD_ON == NVM_JOB_PRIORITIZATION) && (STD_ON == NVM_IMM_JOB_PRIORITY))
    /* If a standard request was pre-empted by a immediate priority request */
    if(NVM_TRUE == NvM_PrevReqImm)
    {
      /* @Trace: NvM_SUD_FUNC_383 */
      /* Process the previously aborted stored standard request */
      jobQueueVal = NvM_StdPrevReq;
      NvM_PrevReqImm = NVM_FALSE;
      status = NVM_TRUE;
    }
    else
  #endif
    {
      /* @Trace: NvM_SUD_FUNC_384 */
      /* Process the request in the standard queue */
      status = NvM_StdQueueRead(&jobQueueVal);
    }

    if(NVM_TRUE == status)
    {
      /* @Trace: NvM_SUD_FUNC_385 */
      /* Store the Service Id and Block Id of the current request */
      NvM_StdPrevReq.ucService_Id = (jobQueueVal.ucService_Id);
      NvM_StdPrevReq.ddBlock_Idx = (jobQueueVal.ddBlock_Idx);
      NvM_BlockIdx = jobQueueVal.ddBlock_Idx;

      /*
       * Update the global pointer to point to the block index of the block
       * to be processed
       */
      /* NvM_BlockIdx is zero, it detects when calling memif function */
      /* @Trace: NvM_SUD_FUNC_386 */
      NvM_NvmBlkDescTbl = &NvM_BlkDescTbls[NvM_BlockIdx];
      NvM_RamAddr = jobQueueVal.pTempRamBlkData;
      /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
      #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
        if((NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE == (
          NvM_NvmBlkDescTbl->usBlkParams & 
          NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE)) && (NULL_PTR == NvM_RamAddr))
        {
          NvM_RamAddr = &NvM_MirrorBuffer[0];
        }
        else
      #endif
        {
          /* If not temporary ram or using ram mirror => using permanent ram */
          if(NULL_PTR == NvM_RamAddr)
          {
            /* @Trace: NvM_SUD_MACRO_034 */
            #if(STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS)
              if(NULL_PTR != NvM_NvmBlkDescTbl->pRamBlkData)
              {
                /* polyspace-begin CERT-C:EXP36-C [Justified:Low] "Follow AUTOSAR specification, NvM does not know user data type so It need to be cast from (void*) to (uint8*) (AUTOSAR Standard : NVM455, EA087) " */
                NvM_RamAddr = (uint8*)NvM_NvmBlkDescTbl->pRamBlkData;
                /* polyspace-end CERT-C:EXP36-C [Justified:Low] "Follow AUTOSAR specification, NvM does not know user data type so It need to be cast from (void*) to (uint8*) (AUTOSAR Standard : NVM455, EA087) " */
              }
            #endif
          }
        }
        NvM_UpdateGlobalVars();
        NvM_State = NvM_StdPrevReq.ucService_Id;

        /* Based on the service request, update the main state and sub state */
        switch (NvM_State)
        {
          case NVM_WRITEBLOCK_SID:
          case NVM_WRITEPRAMBLOCK_SID:
            /* @Trace: NvM_SUD_FUNC_387 */
            /* Load the retry counter */
            NvM_RetryCount = NvM_NvmBlkDescTbl->ucMaxNumOfWriteRetries;
            NvM_SubState = NVM_WRITE_NVBLOCK;
            #if(STD_ON == UPDATE_RAM_STATUS_ENABLE)
              NvM_UpdateRamStateStatus(NVM_VALID_CHANGED);
            #endif
            /* @Trace: NvM_SUD_FUNC_389 NvM_SUD_MACRO_004 NvM_SUD_MACRO_017 */
            #if((STD_ON == NVM_CRC_SUPPORT) && \
              (STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM))
              if((NVM_BLOCK_USE_CRC_COMP_MASK == 
                (NvM_NvmBlkDescTbl->usBlkParams &
                NVM_BLOCK_USE_CRC_COMP_MASK)) && (NVM_CALC_RAM_BLK_CRC == 
                (NvM_NvmBlkDescTbl->usBlkParams & NVM_CALC_RAM_BLK_CRC)))
              {
                NvM_CalculateCrcOffset(NvM_BlockIdx);
              }
            #endif
              NvM_ProcessWriteBlock();
          break;

          case NVM_READBLOCK_SID:
          case NVM_READPRAMBLOCK_SID:
            /* @Trace: NvM_SUD_FUNC_388 */
            NvM_SubState = NVM_READ_START;
            #if(STD_ON == UPDATE_RAM_STATUS_ENABLE)
              NvM_UpdateRamStateStatus(NVM_INVALID_UNCHANGED);
            #endif
            NvM_RetryCount = NvM_NvmBlkDescTbl->ucMaxNumOfReadRetries;
            /* @Trace: NvM_SUD_FUNC_390 NvM_SUD_MACRO_004 NvM_SUD_MACRO_017 */
            #if((STD_ON == NVM_CRC_SUPPORT) && \
              (STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM))
              if((NVM_BLOCK_USE_CRC_COMP_MASK == (
                NvM_NvmBlkDescTbl->usBlkParams &
                NVM_BLOCK_USE_CRC_COMP_MASK)) && (NVM_CALC_RAM_BLK_CRC == 
                (NvM_NvmBlkDescTbl->usBlkParams & NVM_CALC_RAM_BLK_CRC)))
              {
                NvM_CalculateCrcOffset(NvM_BlockIdx);
              }
            #endif
              NvM_ProcessReadBlock();
          break;

          case NVM_RESTOREPRAMBLOCKDEFAULTS_SID:
          case NVM_RESTOREBLOCKDEFAULTS_SID:
            /* @Trace: NvM_SUD_FUNC_391 */
            /* Update ram state status before copy default data or call the callback */
            #if(STD_ON == UPDATE_RAM_STATUS_ENABLE)
              NvM_UpdateRamStateStatus(NVM_INVALID_UNCHANGED);
            #endif
            NvM_RestoreBlockstate = NVM_RESTORE_START;
            NvM_ProcessRestoreBlock();
          break;
          /* @Trace: NvM_SUD_MACRO_047 */
          #if(NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS)
            /* Update the sub states to process erase request */
            case NVM_ERASENVBLOCK_SID :
            case NVM_INVALIDATENVBLOCK_SID:
              /* @Trace: NvM_SUD_FUNC_392 */
              NvM_SubState = NVM_ERASEINVALIDATE_START;
              NvM_ProcessEraseInvalidBlk();
            break;
          #endif

          default:
            /* Do nothing */
            break;
        }  /* end switch (NvM_State) */
    }  /* @End of if(NVM_TRUE == status) */
    return (status);
} /* End of function body */

#endif  /* (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) */

/*******************************************************************************
** Function Name        : NvM_ImmQueueRead                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function performs the read operation of             **
**                        Immediate queues                                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : ptrDataPtr                                          **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_ImmFreeIndx,           **
**                        NvM_ImmQueueBuffer, NvM_ImmQueStartPos,             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION()               **
*******************************************************************************/
/* @Trace: SRS_Mem_00034 */
#if(STD_ON == NVM_JOB_PRIO)
NVM_STATIC FUNC(boolean, NVM_CODE) NvM_ImmQueueRead(
  CONSTP2VAR(NvM_JobQueue, AUTOMATIC, NVM_APPL_DATA) ptrDataPtr)
{
  VAR(boolean, AUTOMATIC) returnValue;
  VAR(uint16, AUTOMATIC) preIndex;
  VAR(uint16, AUTOMATIC) nextIndex;
  returnValue = NVM_FALSE;
  SchM_Enter_NvM_RAM_STATUS_PROTECTION();
  /* @Trace: NvM_SUD_MACRO_038 */
  if(NVM_SIZE_IMMEDIATE_JOB_QUEUE != NvM_ImmFreeIndx)
  {
    /* @Trace: NvM_SUD_FUNC_382 */
    nextIndex = NvM_ImmQueueBuffer[NvM_ImmQueStartPos].ucNextIndex;
    preIndex = NvM_ImmQueueBuffer[NvM_ImmQueStartPos].ucPreviousIndex;
    NvM_ImmQueueBuffer[preIndex].ucNextIndex = nextIndex;
    NvM_ImmQueueBuffer[nextIndex].ucPreviousIndex = preIndex;    
    *ptrDataPtr = NvM_ImmQueueBuffer[NvM_ImmQueStartPos];
    NvM_ImmQueueBuffer[NvM_ImmQueStartPos].ddBlock_Idx = NVM_ZERO;
    NvM_ImmQueStartPos = nextIndex;
    NvM_ImmFreeIndx++;
    returnValue = NVM_TRUE;
  }
  SchM_Exit_NvM_RAM_STATUS_PROTECTION();
  return(returnValue);
} /* End of function body */

#endif  /* (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) */

/*******************************************************************************
** Function Name        : NvM_StdQueueRead                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function performs the read operation of             **
**                        Standard queues                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : ptrDataPtr                                          **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_StdFreeIndx,           **
**                        NvM_StdQueueBuffer, NvM_StdQueEndPos,               **
**                        NvM_StdQueStartPos                                  **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION()               **
*******************************************************************************/
/* @Trace: SRS_Mem_00034 NvM_SUD_MACRO_047 */
#if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
NVM_STATIC FUNC(boolean, NVM_CODE) NvM_StdQueueRead(
  CONSTP2VAR(NvM_JobQueue, AUTOMATIC, NVM_APPL_DATA) ptrDataPtr)
{
  VAR(boolean, AUTOMATIC) returnValue;
  VAR(uint16, AUTOMATIC) preIndex;
  VAR(uint16, AUTOMATIC) nextIndex;
  VAR(uint16, AUTOMATIC) presentIndex;
  /* @Trace: NvM_SUD_MACRO_025 */
  #if(STD_ON == NVM_JOB_PRIORITIZATION)
    VAR(uint8, AUTOMATIC) lowPrio;
    VAR(uint16, AUTOMATIC) lowPrioIndex;
  #endif
    returnValue = NVM_FALSE;
    /* @Trace: NvM_SUD_MACRO_039 */
    if(NVM_SIZE_STANDARD_JOB_QUEUE != NvM_StdFreeIndx)
    {
      /* @Trace: NvM_SUD_FUNC_378 */
      presentIndex = NvM_StdQueStartPos;
      /* @Trace: NvM_SUD_MACRO_025 */
      #if(STD_ON == NVM_JOB_PRIORITIZATION)
        /* @Trace: NvM_SUD_FUNC_379 */
        lowPrio = NvM_StdQueueBuffer[presentIndex].ucPriority;
        lowPrioIndex = presentIndex;
        while(presentIndex != NvM_StdQueEndPos)
        {
          presentIndex = 
            NvM_StdQueueBuffer[presentIndex].ucNextIndex;
          if(NvM_StdQueueBuffer[presentIndex].ucPriority < lowPrio)
          {
            lowPrio = NvM_StdQueueBuffer[presentIndex].ucPriority;
            lowPrioIndex = presentIndex;
          }
        }
        presentIndex = lowPrioIndex;
      #endif
        /* @Trace: NvM_SUD_FUNC_380 */
        SchM_Enter_NvM_RAM_STATUS_PROTECTION();
        if(presentIndex == NvM_StdQueStartPos)
        {
          NvM_StdQueStartPos = NvM_StdQueueBuffer[presentIndex].ucNextIndex;
        }
        else if(presentIndex == NvM_StdQueEndPos)
        {
          NvM_StdQueEndPos = NvM_StdQueueBuffer[presentIndex].ucPreviousIndex;
        }
        else
        {
        }
        *ptrDataPtr = NvM_StdQueueBuffer[presentIndex];
        nextIndex = NvM_StdQueueBuffer[presentIndex].ucNextIndex;
        preIndex = NvM_StdQueueBuffer[presentIndex].ucPreviousIndex;
        NvM_StdQueueBuffer[preIndex].ucNextIndex = nextIndex;
        NvM_StdQueueBuffer[nextIndex].ucPreviousIndex = preIndex;
        NvM_StdQueueBuffer[presentIndex].ddBlock_Idx = NVM_ZERO;
        NvM_StdFreeIndx++;
        returnValue = NVM_TRUE;
        SchM_Exit_NvM_RAM_STATUS_PROTECTION();
    } /* end of if(NVM_SIZE_STANDARD_JOB_QUEUE != NvM_StdFreeIndx) */
    return(returnValue);
} /* End of function body */

#endif  /* (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) */

/*******************************************************************************
** Function Name        : NvM_ImmQueueWrite                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function performs the write operation of Immediate  **
**                        queue                                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : ptrDataPtr                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : putQueueResult                                      **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_RamStatus,             **
**                        NvM_ImmQueueBuffer, NvM_ImmFreeSlotsAvail,          **
**                        NvM_ImmQueStartPos, NvM_ImmQueEndPos,               **
**                        NvM_ImmFreeIndx                                     **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION(),              **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION()              **
*******************************************************************************/
/* @Trace: SRS_Mem_00013 */
#if(STD_ON == NVM_JOB_PRIO)
FUNC(Std_ReturnType, NVM_CODE) NvM_ImmQueueWrite(
  CONSTP2CONST(NvM_JobQueue, AUTOMATIC, NVM_APPL_DATA) ptrDataPtr)
{
  P2VAR(uint16, AUTOMATIC, NVM_VAR_NOINIT) ptrRamStatus;
  VAR(Std_ReturnType, AUTOMATIC) putQueueResult;
  VAR(uint16, AUTOMATIC) presentIndex;

  putQueueResult = E_NOT_OK;

  /* @Trace: NvM_SUD_FUNC_458 */
  ptrRamStatus = &NvM_RamStatus[ptrDataPtr->ddBlock_Idx];
  SchM_Enter_NvM_RAM_STATUS_PROTECTION();
  /*- check queue full */
  if(NVM_ZERO != NvM_ImmFreeSlotsAvail)
  {
    /* @Trace: NvM_SUD_FUNC_459 */
    NvM_ImmFreeSlotsAvail--;
    NvM_ImmFreeIndx--;
    *ptrRamStatus = ((*ptrRamStatus) & NVM_NOT_ERROR_BIT_MASK) | 
      NVM_REQ_PENDING;
    presentIndex = NvM_ImmQueEndPos;
    while(NvM_ImmQueueBuffer[presentIndex].ddBlock_Idx != NVM_ZERO)
    {
      /* @Trace: NvM_SUD_MACRO_038 */
      presentIndex = (presentIndex + (uint16)NVM_ONE) % 
        (NVM_SIZE_IMMEDIATE_JOB_QUEUE);
    }
    NvM_ImmQueueBuffer[presentIndex].ucService_Id = ptrDataPtr->ucService_Id;
    NvM_ImmQueueBuffer[presentIndex].ddBlock_Idx = ptrDataPtr->ddBlock_Idx;
    NvM_ImmQueueBuffer[presentIndex].pTempRamBlkData = 
      ptrDataPtr->pTempRamBlkData;
    NvM_ImmQueueBuffer[presentIndex].ucPriority = ptrDataPtr->ucPriority;
    NvM_ImmQueueBuffer[presentIndex].ucPreviousIndex = NvM_ImmQueEndPos;
    NvM_ImmQueueBuffer[presentIndex].ucNextIndex = NvM_ImmQueStartPos;
    NvM_ImmQueueBuffer[NvM_ImmQueStartPos].ucPreviousIndex = presentIndex;
    NvM_ImmQueueBuffer[NvM_ImmQueEndPos].ucNextIndex = presentIndex;
    NvM_ImmQueEndPos = presentIndex;
    putQueueResult = E_OK;
  } /* end of if(NVM_ZERO != NvM_ImmFreeSlotsAvail) */
  /* @Trace: NvM_SUD_FUNC_460 */
  SchM_Exit_NvM_RAM_STATUS_PROTECTION();
  /* @Trace: NvM_SUD_FUNC_461 */
  return(putQueueResult);
} /* End of function body */

#endif  /* (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) */

/*******************************************************************************
** Function Name        : NvM_StdQueueWrite                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function performs the write operation of Standerd   **
**                        queue                                               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ptrDataPtr                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : putQueueResult                                      **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_RamStatus,             **
**                        NvM_StdFreeSlotsAvail, NvM_StdFreeIndx,             **
**                        NvM_StdQueueBuffer, NvM_StdQueStartPos,             **
**                        NvM_StdQueEndPos                                    **
**                        Function(s) invoked    :                            **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION(),              **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION()              **
*******************************************************************************/
/* @Trace: SRS_Mem_00013 NvM_SUD_MACRO_047 */
#if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
FUNC(Std_ReturnType, NVM_CODE) NvM_StdQueueWrite(
  CONSTP2CONST(NvM_JobQueue, AUTOMATIC, NVM_APPL_DATA) ptrDataPtr)
{
  P2VAR(uint16, AUTOMATIC, NVM_VAR_NOINIT) ptrRamStatus;
  VAR(Std_ReturnType, AUTOMATIC) putQueueResult;
  VAR(uint16, AUTOMATIC) presentIndex;

  putQueueResult = E_NOT_OK;
  /* @Trace: NvM_SUD_FUNC_454 */
  ptrRamStatus = &NvM_RamStatus[ptrDataPtr->ddBlock_Idx];
  SchM_Enter_NvM_RAM_STATUS_PROTECTION();
  /*- check queue full */
  if(NVM_ZERO != NvM_StdFreeSlotsAvail)
  {
    /* @Trace: NvM_SUD_FUNC_455 */
    NvM_StdFreeSlotsAvail--;
    NvM_StdFreeIndx--;
    *ptrRamStatus = ((*ptrRamStatus) & NVM_NOT_ERROR_BIT_MASK) | 
      NVM_REQ_PENDING;
    presentIndex = NvM_StdQueEndPos;
    while(NvM_StdQueueBuffer[presentIndex].ddBlock_Idx != NVM_ZERO)
    {
      /* @Trace: NvM_SUD_MACRO_039 */
      presentIndex = (presentIndex + (uint16)NVM_ONE) % 
        (NVM_SIZE_STANDARD_JOB_QUEUE);
    }
    NvM_StdQueueBuffer[presentIndex].ucService_Id = ptrDataPtr->ucService_Id;
    NvM_StdQueueBuffer[presentIndex].ddBlock_Idx = ptrDataPtr->ddBlock_Idx;
    NvM_StdQueueBuffer[presentIndex].pTempRamBlkData = 
      ptrDataPtr->pTempRamBlkData;
    /* @Trace: NvM_SUD_MACRO_025 */
    #if(STD_ON == NVM_JOB_PRIORITIZATION)
      NvM_StdQueueBuffer[presentIndex].ucPriority = ptrDataPtr->ucPriority;
    #endif
    NvM_StdQueueBuffer[presentIndex].ucPreviousIndex = NvM_StdQueEndPos;
    NvM_StdQueueBuffer[presentIndex].ucNextIndex = NvM_StdQueStartPos;
    NvM_StdQueueBuffer[NvM_StdQueStartPos].ucPreviousIndex = presentIndex;
    NvM_StdQueueBuffer[NvM_StdQueEndPos].ucNextIndex = presentIndex;
    NvM_StdQueEndPos = presentIndex;
    putQueueResult = E_OK;
  } /* end of if(NVM_ZERO != NvM_StdFreeSlotsAvail) */
  /* @Trace: NvM_SUD_FUNC_456 */
  SchM_Exit_NvM_RAM_STATUS_PROTECTION();  
  /* @Trace: NvM_SUD_FUNC_457 */
  return(putQueueResult);
} /* End of function body */

#endif  /* (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) */

/*******************************************************************************
** Function Name        : NvM_ImmQueueCancel                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function performs the Immediate QueueCancel         **
**                        operation                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : blockId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : returnValue                                         **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_ImmFreeSlotsAvail,     **
**                        NvM_ImmQueueBuffer, NvM_ImmQueStartPos,             **
**                        NvM_ImmQueEndPos, NvM_ImmFreeIndx                   **
**                        Function(s) invoked    :                            **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION()               **
*******************************************************************************/
/* @Trace: SRS_Mem_08558 SRS_Mem_08560 */
#if(STD_ON == NVM_JOB_PRIO)
FUNC(Std_ReturnType, NVM_CODE) NvM_ImmQueueCancel(
  VAR(NvM_BlockIdType, AUTOMATIC) blockId)
{
  /* @Trace: NvM_SUD_FUNC_376 */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  VAR(uint16, AUTOMATIC) indexCnt;
  VAR(uint16, AUTOMATIC) preIndex;
  VAR(uint16, AUTOMATIC) nextIndex;
  returnValue = E_NOT_OK;
  /* @Trace: NvM_SUD_MACRO_038 */
  if(NVM_SIZE_IMMEDIATE_JOB_QUEUE > NvM_ImmFreeIndx)
  {
    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    indexCnt = NvM_ImmQueStartPos;
    while(indexCnt != NvM_ImmQueEndPos)
    {
      if(NvM_ImmQueueBuffer[indexCnt].ddBlock_Idx == blockId)
      {
        break;
      }
      else
      {
        indexCnt = NvM_ImmQueueBuffer[indexCnt].ucNextIndex;
      }
    }

    if(NvM_ImmQueueBuffer[indexCnt].ddBlock_Idx == blockId)
    {
      returnValue = E_OK;
      NvM_ImmFreeIndx++;
      NvM_ImmFreeSlotsAvail++;
      nextIndex = NvM_ImmQueueBuffer[indexCnt].ucNextIndex;
      preIndex = NvM_ImmQueueBuffer[indexCnt].ucPreviousIndex;
      if(indexCnt == NvM_ImmQueStartPos)
      {
        NvM_ImmQueStartPos = nextIndex;
      }
      else if(indexCnt == NvM_ImmQueEndPos)
      {
        NvM_ImmQueEndPos = preIndex;
      }
      else
      {
      }

      NvM_ImmQueueBuffer[preIndex].ucNextIndex = nextIndex;
      NvM_ImmQueueBuffer[nextIndex].ucPreviousIndex = preIndex;
      NvM_ImmQueueBuffer[indexCnt].ddBlock_Idx = NVM_ZERO;
    } /* @End of if(NvM_ImmQueueBuffer[index].ddBlock_Idx == blockId) */
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
  } /* end of if(NVM_ZERO != NvM_ImmFreeIndx) */
  return(returnValue);
} /* End of function body */

#endif

/*******************************************************************************
** Function Name        : NvM_StdQueueCancel                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function performs the  operation of Standard        **
**                        queue Cancel operation                              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : blockId                                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : returnValue                                         **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_StdFreeSlotsAvail,     **
**                        NvM_StdQueStartPos, NvM_StdQueueBuffer,             **
**                        NvM_StdQueEndPos, NvM_StdFreeIndx                   **
**                        Function(s) invoked    :                            **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION()               **
*******************************************************************************/
/* @Trace: SRS_Mem_08558 SRS_Mem_08560 NvM_SUD_MACRO_047 */
#if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
FUNC(Std_ReturnType, NVM_CODE) NvM_StdQueueCancel(
  VAR(NvM_BlockIdType, AUTOMATIC) blockId)
{
  /* @Trace: NvM_SUD_FUNC_375 */
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  VAR(uint16, AUTOMATIC) indexCnt;
  VAR(uint16, AUTOMATIC) preIndex;
  VAR(uint16, AUTOMATIC) nextIndex;
  returnValue = E_NOT_OK;
  /* @Trace: NvM_SUD_MACRO_039 */
  if(NVM_SIZE_STANDARD_JOB_QUEUE > NvM_StdFreeIndx)
  {
    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    indexCnt = NvM_StdQueStartPos;
    while(indexCnt != NvM_StdQueEndPos)
    {
      if(NvM_StdQueueBuffer[indexCnt].ddBlock_Idx == blockId)
      {
        break;
      }
      else
      {
        indexCnt = NvM_StdQueueBuffer[indexCnt].ucNextIndex;
      }
    }

    if(NvM_StdQueueBuffer[indexCnt].ddBlock_Idx == blockId)
    {
      returnValue = E_OK;
      NvM_StdFreeIndx++;
      NvM_StdFreeSlotsAvail++;
      nextIndex = NvM_StdQueueBuffer[indexCnt].ucNextIndex;
      preIndex = NvM_StdQueueBuffer[indexCnt].ucPreviousIndex;
      if(indexCnt == NvM_StdQueStartPos)
      {
        NvM_StdQueStartPos = nextIndex;
      }
      else if(indexCnt == NvM_StdQueEndPos)
      {
        NvM_StdQueEndPos = preIndex;
      }
      else
      {
      }
      NvM_StdQueueBuffer[preIndex].ucNextIndex = nextIndex;
      NvM_StdQueueBuffer[nextIndex].ucPreviousIndex = preIndex;
      NvM_StdQueueBuffer[indexCnt].ddBlock_Idx = NVM_ZERO;
    } /* @End of if(NvM_StdQueueBuffer[indexCnt].ddBlock_Idx == blockId) */
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
  } /* end of if(NVM_ZERO != NvM_StdFreeIndx) */
  return(returnValue);
} /* End of function body */

#endif

/*******************************************************************************
** Function Name        : NvM_StdQueuePosClear                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function performs the  operation of Standard        **
**                        queue position  clear operation                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_StdFreeSlotsAvail      **
**                        Function(s) invoked    :                            **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION()               **
*******************************************************************************/
/* @Trace: SRS_Mem_00034 NvM_SUD_MACRO_047 */
#if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
NVM_STATIC FUNC(void, NVM_CODE) NvM_StdQueuePosClear(void)
{
  /* @Trace: NvM_SUD_FUNC_374 NvM_SUD_MACRO_039 */
  if(NVM_SIZE_STANDARD_JOB_QUEUE > NvM_StdFreeSlotsAvail)
  {
    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    NvM_StdFreeSlotsAvail++;
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
  }
}
#endif

/*******************************************************************************
** Function Name        : NvM_ImmQueuePosClear                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function performs the  operation of Immediate       **
**                        queue position clear operation                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_ImmFreeSlotsAvail      **
**                        Function(s) invoked    :                            **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION()               **
*******************************************************************************/
/* @Trace: SRS_Mem_00034 */
#if(STD_ON == NVM_JOB_PRIO)
NVM_STATIC FUNC(void, NVM_CODE) NvM_ImmQueuePosClear(void)
{
  /* @Trace: NvM_SUD_FUNC_373 NvM_SUD_MACRO_038 */
  if(NVM_SIZE_IMMEDIATE_JOB_QUEUE > NvM_ImmFreeSlotsAvail)
  {
    SchM_Enter_NvM_RAM_STATUS_PROTECTION();
    NvM_ImmFreeSlotsAvail++;
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();
  }
} /* End of function body */
#endif

/*******************************************************************************
** Function Name        : NvM_WriteNvBlockProcess                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service writes data and CRC from RAM           **
**                        to NV block.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)   : NvM_MirrorBuffer,            **
**                        NvM_MirrorCount, NvM_BlockIdx, NvM_State,           **
**                        NvM_RamAddr, NvM_SubState, NvM_NvmBlkDescTbl,       **
**                        NvM_RetryCount, NvM_RamStatus, NvM_CrcStepCnt,      **
**                        NvM_ReadCRCSID                                      **
**                        Function(s) invoked  : NvM_CompareCrcMechanism(),   **
**                        NvM_CalculateCRCStaticID(), NvM_EndProcessBlock(),  **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION(),              **
**                        Dem_SetEventStatus()                                **
*******************************************************************************/
NVM_STATIC FUNC(void, NVM_CODE) NvM_WriteNvBlockProcess(void)
{
  /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
  #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
    VAR(Std_ReturnType, AUTOMATIC) status;
  #endif
  /* @Trace: NvM_SUD_MACRO_017 NvM_SUD_MACRO_040 */
  #if((STD_ON == NVM_STATIC_ID_CHECK) || (STD_ON == NVM_CRC_SUPPORT))
    VAR(uint16, AUTOMATIC) blkParams;
    VAR(uint8, AUTOMATIC) varCRCSIDIndex;
  #endif
  VAR(uint16, AUTOMATIC) varCnt;
  P2VAR(uint8, AUTOMATIC, NVM_VAR_NOINIT) ptrDataBuffer;
  NvM_DataWordType nvmBufferTmp;
  /* @Trace: NvM_SUD_MACRO_017 */
  #if(STD_ON == NVM_CRC_SUPPORT)
    VAR(uint8, AUTOMATIC) varCrcLength;
  #endif
  /* @Trace: NvM_SUD_MACRO_004 NvM_SUD_MACRO_017 */
  #if((STD_ON == NVM_CRC_SUPPORT) && \
    (STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM))
    VAR(boolean, AUTOMATIC) cmpMatch;
  #endif

  /* @Trace: NvM_SUD_FUNC_446 NvM_SUD_MACRO_017 NvM_SUD_MACRO_040 */
  #if((STD_ON == NVM_STATIC_ID_CHECK) || (STD_ON == NVM_CRC_SUPPORT))
    blkParams = NvM_NvmBlkDescTbl->usBlkParams;
    varCRCSIDIndex = (uint8)NVM_ZERO;
  #endif
  /* @Trace: NvM_SUD_MACRO_004 NvM_SUD_MACRO_017 */
  #if((STD_ON == NVM_CRC_SUPPORT) && \
    (STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM))
    cmpMatch = NVM_FALSE;
  #endif
  /* If Explicit mechanism is configured, callback copy data from ram to ram mirror */
  /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
  #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
    /* @Trace: NvM_SUD_FUNC_504 */
    status = E_OK;
    if((&NvM_MirrorBuffer[0] == NvM_RamAddr) && ((NVM_ONE != NvM_BlockIdx)
      /* @Trace: NvM_SUD_MACRO_041 NvM_SUD_MACRO_047 */
      #if((0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS) && \
        (NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS))
      || (NVM_FIRSTINITALL_SID == NvM_State)
      #endif
      ) 
      /* @Trace: NvM_SUD_MACRO_041 NvM_SUD_MACRO_047 */
      #if((0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS) && \
        (NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS))
      && ((NVM_FIRSTINITALL_SID != NvM_State) || 
      (NULL_PTR == NvM_NvmBlkDescTbl->pRomBlkData)) /* First init all only copy default data to NvBlock */
      #endif
      /* @Trace: NvM_SUD_MACRO_017 */
      #if(STD_ON == NVM_CRC_SUPPORT)
        && (NVM_ZERO == NvM_CrcStepCnt) /* Skip read callback to avoid time */
      #endif
    )
    { /* start block comment 1 */
      /* Invoke callback to copy data from Ram to Ram Mirror */
      /* @Trace: NvM_SUD_FUNC_271 */
      if(NULL_PTR != NvM_NvmBlkDescTbl->pNvMWriteRamBlockToNvm)
      {
        status = (NvM_NvmBlkDescTbl->pNvMWriteRamBlockToNvm)(
          (void *)(&NvM_MirrorBuffer[0]));
      }
      /* Copy success */
      /* @Trace: NvM_SUD_FUNC_272 */
      if(E_OK != status)
      {
        /* descrease retryCount */
        if(NVM_ZERO != NvM_MirrorCount)
        {
          /* @Trace: NvM_SUD_FUNC_273 */
          NvM_MirrorCount--;
        }
        else
        {
          /* @Trace: NvM_SUD_MACRO_021 */
          #if(STD_ON == NVM_DEMERROR_REPORT)
            /* @Trace: NvM_SUD_FUNC_274 */
            (void)Dem_SetEventStatus(NVM_E_REQ_FAILED, DEM_EVENT_STATUS_FAILED);
          #endif
            /* @Trace: NvM_SUD_FUNC_275 */
            NvM_EndProcessBlock(NVM_REQ_NOT_OK);
        }
      }
    } /* end block comment 1 */
    if(E_OK == status)
  #endif
    {
      /* @Trace: NvM_SUD_MACRO_017 NvM_SUD_MACRO_040 */
      #if((STD_ON == NVM_STATIC_ID_CHECK) || \
        (STD_ON == NVM_CRC_SUPPORT))
        if((NVM_CALC_RAM_BLK_CRC == (blkParams & 
          NVM_CALC_RAM_BLK_CRC)) || (NVM_STATIC_BLOCK_ID_CHECK == (
          blkParams & NVM_STATIC_BLOCK_ID_CHECK)))
        {
          /* @Trace: NvM_SUD_FUNC_277 */
          NvM_CalculateCRCStaticID();
        }
      #endif
      /* @Trace: NvM_SUD_MACRO_017 */
      #if(STD_ON == NVM_CRC_SUPPORT)
        /* @Trace: NvM_SUD_FUNC_447 */
        varCrcLength = NvM_NvmBlkDescTbl->ucCrcLength;
        if(NVM_ZERO == NvM_CrcStepCnt)
      #endif
        {
          /* polyspace-begin RTE:IDP [Justified:Low] "NvM_DataBuffer has the size greater than STATIC_ID + Crc + NvBlock length" */
          /* @Trace: NvM_SUD_FUNC_278 */
          ptrDataBuffer = &NvM_DataBuffer[0];
          /* @Trace: NvM_SUD_MACRO_040 */
          #if(STD_ON == NVM_STATIC_ID_CHECK)
            if(NVM_STATIC_BLOCK_ID_CHECK == (blkParams & 
              NVM_STATIC_BLOCK_ID_CHECK))
            {
              for(varCnt = NVM_ZERO; varCnt < NVM_TWO; varCnt++)
              {
                *ptrDataBuffer = NvM_ReadCRCSID[varCRCSIDIndex];
                ptrDataBuffer++;
                varCRCSIDIndex++;
              }
            }
          #endif

          /* @Trace: NvM_SUD_MACRO_004 NvM_SUD_MACRO_017 */
          /* Compare machanism */
          #if((STD_ON == NVM_CRC_SUPPORT) && \
            (STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM)) 
            if((NVM_BLOCK_USE_CRC_COMP_MASK == (blkParams & 
              NVM_BLOCK_USE_CRC_COMP_MASK)) && (NVM_CALC_RAM_BLK_CRC 
              == (blkParams & NVM_CALC_RAM_BLK_CRC)))
            { /* start block comment 2 */
              /* @Trace: NvM_SUD_FUNC_501 */
              cmpMatch = NvM_CompareCrcMechanism(varCrcLength, varCRCSIDIndex);
            } /* end block comment 2 */
          #endif

            if((NVM_FIRSTINITALL_SID != NvM_State) && (NVM_ONE == NvM_BlockIdx))
            {
              /* @Trace: NvM_SUD_FUNC_502 */
              nvmBufferTmp.u_uint16 = NVM_COMPILED_CONFIG_ID;
              ptrDataBuffer[0] = nvmBufferTmp.u_uint8[0];
              ptrDataBuffer[1] = nvmBufferTmp.u_uint8[1];
              /* @Trace: NvM_SUD_MACRO_011 */
              ptrDataBuffer++;
              ptrDataBuffer++;
              varCnt = NVM_TWO;
            }
            else
            {
              /* @Trace: NvM_SUD_FUNC_503 */
              varCnt = NVM_ZERO;
            }
            if(NULL_PTR != NvM_RamAddr)
            {
              for(; varCnt < NvM_NvmBlkDescTbl->usNvBlkDataLength; varCnt++)
              {
                /* @Trace: NvM_SUD_FUNC_448 */
                *ptrDataBuffer = NvM_RamAddr[varCnt];
                ptrDataBuffer++;
              }
            }
          /* 
           * This section - BEGIN: Add crc value to tail of NV block + 
           * Implement crc comparing mechanims
           */
          /* @Trace: NvM_SUD_MACRO_017 */
          #if(STD_ON == NVM_CRC_SUPPORT)
            /* @Trace: NvM_SUD_FUNC_282 */
            if(NVM_CALC_RAM_BLK_CRC == (blkParams & NVM_CALC_RAM_BLK_CRC))
            { /* start block comment 3 */
              for(varCnt = NVM_ZERO; varCnt < varCrcLength; varCnt++)
              {
                *ptrDataBuffer = NvM_ReadCRCSID[varCRCSIDIndex];
                ptrDataBuffer++;
                varCRCSIDIndex++;
              }
            } /* end block comment 3 */
          #endif
          /* 
           * This section - END: Add crc value to tail of NV block + 
           * Implement crc comparing mechanims
           */
          /* polyspace-end RTE:IDP */
          /* after prepare data buffer, invoke MemIf_Write to write data */

          /* @Trace: NvM_SUD_MACRO_004 NvM_SUD_MACRO_017 */
          #if((STD_ON == NVM_CRC_SUPPORT) && \
            (STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM)) 
            if((NVM_TRUE == cmpMatch) && (NVM_CHECK_LOSS_OF_REDUNDANCY != 
              (NvM_RamStatus[NvM_BlockIdx] & NVM_CHECK_LOSS_OF_REDUNDANCY)))
            {
              /* @Trace: NvM_SUD_FUNC_283 */
              #if(STD_ON == UPDATE_RAM_STATUS_ENABLE)
                NvM_UpdateRamStateStatus(NVM_VALID_UNCHANGED);
              #endif
              if((NVM_WRITE_BLOCK_ONCE == (blkParams & 
                NVM_WRITE_BLOCK_ONCE)) && (NVM_FIRSTINITALL_SID != NvM_State))
              {
                /* @Trace: NvM_SUD_FUNC_285 */
                SchM_Enter_NvM_RAM_STATUS_PROTECTION();
                NvM_RamStatus[NvM_BlockIdx] |= NVM_WRITE_PROTECT_MASK;
                SchM_Exit_NvM_RAM_STATUS_PROTECTION();
              }
              /* @Trace: NvM_SUD_FUNC_284 */
              NvM_EndProcessBlock(NVM_REQ_OK);
            }
            else
          #endif
            {
              /* @Trace: NvM_SUD_FUNC_287 */
              NvM_SubState = NVM_PROCESS_WRITE_ACCEPT;
            }
        } /* @End of if(NVM_ZERO == NvM_CrcStepCnt) */
    } /* @End of if(E_OK == status) */
}

/*******************************************************************************
** Function Name        : NvM_SubWriteProcessNvBlock                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service writes data and CRC from RAM           **
**                        to NV block.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)   : NvM_SubState, NvM_ReStatus,  **
**                        NvM_BlkMngmntType, NvM_NvmBlkDescTbl, NvM_RamStatus,**
**                        NvM_RetryCount                                      **
**                        Function(s) invoked  : Dem_SetEventStatus(),        **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION(),              **
**                        NvM_EndProcessBlock(), NvM_StoreCrcOffset()         **
*******************************************************************************/
NVM_STATIC FUNC(void, NVM_CODE) NvM_SubWriteProcessNvBlock(void)
{
  /* @Trace: NvM_SUD_MACRO_004 NvM_SUD_MACRO_017 */
  #if((STD_ON == NVM_CRC_SUPPORT) && \
    (STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM))
    VAR(uint16, AUTOMATIC) blkParams;
    /* @Trace: NvM_SUD_FUNC_506 */
    blkParams = NvM_NvmBlkDescTbl->usBlkParams;
  #endif
  if(NVM_ZERO != NvM_RetryCount)
  {
    /* @Trace: NvM_SUD_FUNC_295 */
    NvM_RetryCount--;
    NvM_SubState = NVM_PROCESS_WRITE_ACCEPT;
  }
  else
  {
    /* Write 1st nv block fail => write 2nd nv block */
    /* @Trace: NvM_SUD_MACRO_021 */
    #if(STD_ON == NVM_DEMERROR_REPORT)
      /* @Trace: NvM_SUD_FUNC_296 */
      (void)Dem_SetEventStatus(NVM_E_REQ_FAILED, DEM_EVENT_STATUS_FAILED);
    #endif
      if((NVM_BLOCK_REDUNDANT == NvM_BlkMngmntType) &&
        (NVM_RE_CHK_NONE == NvM_ReStatus))
      { /* start block comment 5 */
        /*
         * If the Write to 1st NV block fails when block is of Redundant
         * type, process the 2nd NV block of Redundant block
         */
        /* @Trace: NvM_SUD_FUNC_297 */
        NvM_SubState = NVM_PROCESS_WRITE_ACCEPT;
        NvM_ReStatus = NVM_RE_CHKED_ORIGIN;
        /* Reloading Write retires counter */
        NvM_RetryCount = NvM_NvmBlkDescTbl->ucMaxNumOfWriteRetries;
        SchM_Enter_NvM_RAM_STATUS_PROTECTION();
        /* @Trace: NvM_SUD_FUNC_298 */
        NvM_RamStatus[NvM_BlockIdx] |= NVM_CHECK_LOSS_OF_REDUNDANCY;
        SchM_Exit_NvM_RAM_STATUS_PROTECTION();
      } /* end block comment 5 */
      else if(NVM_RE_CHKED_COPY == NvM_ReStatus)
      {
        /* @Trace: NvM_SUD_FUNC_299 */
        #if(STD_ON == UPDATE_RAM_STATUS_ENABLE)
          NvM_UpdateRamStateStatus(NVM_VALID_UNCHANGED);
        #endif
        /*
         * If writing of both NV blocks are complete in case of
         * Redundant block, end the write processing
         */
        NvM_EndProcessBlock(NVM_REQ_OK);
        /* @Trace: NvM_SUD_MACRO_004 NvM_SUD_MACRO_017 */
        #if((STD_ON == NVM_CRC_SUPPORT) && \
          (STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM)) 
          if((NVM_BLOCK_USE_CRC_COMP_MASK == (blkParams & 
            NVM_BLOCK_USE_CRC_COMP_MASK)) && (NVM_CALC_RAM_BLK_CRC == 
            (blkParams & NVM_CALC_RAM_BLK_CRC)))
          {
            NvM_StoreCrcOffset();
          }
        #endif
      } /* end of else if(NVM_RE_CHKED_COPY == NvM_ReStatus) */
      else
      {
        /* @Trace: NvM_SUD_FUNC_301 */
        NvM_EndProcessBlock(NVM_REQ_NOT_OK);
      }

  }  /* end else part of if(NVM_ZERO != NvM_RetryCount) */
}

/*******************************************************************************
** Function Name        : NvM_WriteProcessNvBlock                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service writes data and CRC from RAM           **
**                        to NV block.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)   : NvM_MirrorBuffer, NvM_State, **
**                        NvM_JobResultLowLevel, NvM_SubState, NvM_RamStatus, **
**                        NvM_BlkMngmntType, NvM_ReStatus, NvM_NvmBlkDescTbl, **
**                        NvM_RetryCount, NvM_BackUp, NvM_BlockIdx,           **
**                        NvM_RamAddr, NvM_WriteVerify, NvM_ReadAllRequest,   **
**                        NvM_FirstBlock                                      **
**                        Function(s) invoked  : NvM_StoreCrcOffset(),        **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION(),              **
**                        NvM_EndProcessBlock(), NvM_SubWriteProcessNvBlock(),**
**                        Dem_SetEventStatus()                                **
*******************************************************************************/
NVM_STATIC FUNC(void, NVM_CODE) NvM_WriteProcessNvBlock(void)
{
  VAR(Std_ReturnType, AUTOMATIC) status;
  VAR(uint16, AUTOMATIC) blkParams;

  status = E_OK;
  blkParams = NvM_NvmBlkDescTbl->usBlkParams;
  /* Wait for the MEMIF layer to process the request */
  if(NVM_REQ_PENDING != NvM_JobResultLowLevel)
  {
    /* Check if MEMIF returns the job result as NVM_REQ_OK */
    if(NVM_REQ_OK == NvM_JobResultLowLevel)
    {
      /* @Trace: NvM_SUD_MACRO_046 */
      #if(STD_ON == NVM_WRITE_VERIFICATION)
        if((NVM_WRITE_VERIFICATION_ENABLE == (blkParams & 
          NVM_WRITE_VERIFICATION_ENABLE)) && (NvM_WriteVerify == NVM_ZERO))
        {
          /* @Trace: NvM_SUD_FUNC_291 */
          NvM_WriteVerify = NVM_ONE;
          NvM_SubState = NVM_READ_START;
          NvM_State = NVM_READBLOCK_SID;
          NvM_JobResultLowLevel = NVM_REQ_NOT_OK;
          status = E_NOT_OK;
        }
        else
      #endif
        if(NVM_TRUE == NvM_BackUp)
        {
          /* @Trace: NvM_SUD_FUNC_290 */
          SchM_Enter_NvM_RAM_STATUS_PROTECTION();
          NvM_RamStatus[NvM_BlockIdx] &= NVM_CLEAR_LOSS_OF_REDUNDANCY;
          SchM_Exit_NvM_RAM_STATUS_PROTECTION();
        }
        else
        {
          /* @Trace: NvM_SUD_FUNC_289 */
          if((NVM_BLOCK_REDUNDANT == NvM_BlkMngmntType) &&
            (NVM_RE_CHK_NONE == NvM_ReStatus))
          {
            NvM_ReStatus = NVM_RE_CHKED_COPY;
            NvM_RetryCount = NvM_NvmBlkDescTbl->ucMaxNumOfWriteRetries;
            NvM_SubState = NVM_PROCESS_WRITE_ACCEPT;
          }
          else
          { /* start block comment 4 */
            #if(STD_ON == UPDATE_RAM_STATUS_ENABLE)
              NvM_UpdateRamStateStatus(NVM_VALID_UNCHANGED);
            #endif
            if(NVM_RE_CHKED_COPY == NvM_ReStatus)
            {
              SchM_Enter_NvM_RAM_STATUS_PROTECTION();
              NvM_RamStatus[NvM_BlockIdx] &= NVM_CLEAR_LOSS_OF_REDUNDANCY;
              SchM_Exit_NvM_RAM_STATUS_PROTECTION();
            }
            /* @Trace: NvM_SUD_MACRO_004 NvM_SUD_MACRO_017 */
            #if((STD_ON == NVM_CRC_SUPPORT) && \
              (STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM)) 
              if((NVM_BLOCK_USE_CRC_COMP_MASK == (blkParams & 
                NVM_BLOCK_USE_CRC_COMP_MASK)) && (NVM_CALC_RAM_BLK_CRC
                == (blkParams & NVM_CALC_RAM_BLK_CRC)))
              {
                NvM_StoreCrcOffset();
              }
            #endif
            NvM_EndProcessBlock(NVM_REQ_OK);
          } /* end block comment 4 */
          if((NVM_WRITE_BLOCK_ONCE == (blkParams & 
            NVM_WRITE_BLOCK_ONCE)) && (NVM_FIRSTINITALL_SID != NvM_State))
          {
            /* @Trace: NvM_SUD_FUNC_292 */
            SchM_Enter_NvM_RAM_STATUS_PROTECTION();
            NvM_RamStatus[NvM_BlockIdx] |= NVM_WRITE_PROTECT_MASK;
            SchM_Exit_NvM_RAM_STATUS_PROTECTION();
          }
        } /* end else part of if(NVM_TRUE == NvM_BackUp) */
    }  /* @End of if(NVM_REQ_OK == NvM_JobResultLowLevel) */
    else
    {
      /*
       * Checks if Write Retry counter is exceeded when write operation
       * fails
       */
      /* @Trace: NvM_SUD_MACRO_021 */
      #if(STD_ON == NVM_DEMERROR_REPORT)
        if((NVM_REQ_NOT_OK == NvM_JobResultLowLevel) && 
          ((NVM_FALSE == NvM_BackUp) || (NVM_MULTIBLK_IN_PROGRESS 
          == NvM_ReadAllRequest)))
        {
          /* @Trace: NvM_SUD_FUNC_293 */
          (void)Dem_SetEventStatus(NVM_E_HARDWARE, DEM_EVENT_STATUS_FAILED);
        }
      #endif
      if(NVM_TRUE == NvM_BackUp)
      {
        /* @Trace: NvM_SUD_MACRO_021 */
        #if(STD_ON == NVM_DEMERROR_REPORT)
          /* @Trace: NvM_SUD_FUNC_294 */
          (void)Dem_SetEventStatus(
            NVM_E_LOSS_OF_REDUNDANCY, DEM_EVENT_STATUS_FAILED);
        #endif
      }
      else
      {
        /* @Trace: NvM_SUD_FUNC_505 */
        NvM_SubWriteProcessNvBlock();
      } /* end else part of if(NVM_TRUE == NvM_BackUp) */
    }  /* end else part of if(NvM_JobResultLowLevel ==
        * NVM_REQ_OK)
        */
    if((NVM_TRUE == NvM_BackUp) && (E_OK == status))
    {
      /* @Trace: NvM_SUD_FUNC_300 NvM_SUD_MACRO_042 */
      #if(0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS)
      if(NVM_MULTIBLK_IN_PROGRESS == NvM_ReadAllRequest)
      {
        NvM_State = NVM_READALL_SID;
      }
      else
      #endif
      {
        NvM_State = NVM_READBLOCK_SID;
      }
      /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
      #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
        if((&NvM_MirrorBuffer[0] == NvM_RamAddr) &&
          (NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE == (blkParams & 
          NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE)))
        {
          /* @Trace: NvM_SUD_FUNC_303 */
          NvM_SubState = NVM_READ_REPEAT;
          #if(STD_ON == UPDATE_RAM_STATUS_ENABLE)
            NvM_UpdateRamStateStatus(NVM_INVALID_UNCHANGED);
          #endif
        }
        else
      #endif
        {
          /* @Trace: NvM_SUD_FUNC_302 */
          NvM_EndProcessBlock(NVM_REQ_OK);
        }
    } /* @End of if((NVM_TRUE == NvM_BackUp) && (E_OK == status)) */
  } /* end if(NVM_REQ_PENDING != NvM_JobResultLowLevel) */
}

/*******************************************************************************
** Function Name        : NvM_ProcessWriteVerify                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service verify data and CRC from RAM           **
**                        with NV block.                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)   : NvM_MirrorBuffer, NvM_State, **
**                        NvM_JobResultLowLevel, NvM_SubState, NvM_RamAddr,   **
**                        NvM_NvmBlkDescTbl, NvM_WriteVerify, NvM_BlockLength,**
**                        NvM_DataBuffer, NvM_WriteAllRequest, NvM_BackUp,    **
**                        NvM_FirstInitAllRequest, NvM_HighPriorityRequest    **
**                        Function(s) invoked  : Dem_SetEventStatus()         **
*******************************************************************************/
/* @Trace: NvM_SUD_MACRO_046 */
#if(STD_ON == NVM_WRITE_VERIFICATION)
NVM_STATIC FUNC(void, NVM_CODE) NvM_ProcessWriteVerify(void)
{
  VAR(uint16, AUTOMATIC) varCRCSIDIndex;
  VAR(uint16, AUTOMATIC) varCnt;
  VAR(boolean, AUTOMATIC) result;
  VAR(uint16, AUTOMATIC) verifyDataSize;
  VAR(uint16, AUTOMATIC) varOffset;
  /* @Trace: NvM_SUD_MACRO_017 NvM_SUD_MACRO_040 */
  #if((STD_ON == NVM_CRC_SUPPORT) || (STD_ON == NVM_STATIC_ID_CHECK))
    VAR(uint16, AUTOMATIC) blkParams;
  #endif
  /* @Trace: NvM_SUD_MACRO_017 */
  #if(STD_ON == NVM_CRC_SUPPORT)
    VAR(uint8, AUTOMATIC) varCrcLength;
  #endif

  /* @Trace: NvM_SUD_FUNC_304 */
  result = NVM_TRUE;
  varOffset = NVM_ZERO;
  verifyDataSize = NVM_ZERO;
  /* @Trace: NvM_SUD_MACRO_017 NvM_SUD_MACRO_040 */
  #if((STD_ON == NVM_CRC_SUPPORT) || (STD_ON == NVM_STATIC_ID_CHECK))
    blkParams = NvM_NvmBlkDescTbl->usBlkParams;
  #endif

  varCRCSIDIndex = NVM_ZERO;
  /* @Trace: NvM_SUD_MACRO_040 */
  #if(STD_ON == NVM_STATIC_ID_CHECK)
    if(NVM_STATIC_BLOCK_ID_CHECK == (blkParams & NVM_STATIC_BLOCK_ID_CHECK))
    {
      varCRCSIDIndex = NVM_TWO;
    }
  #endif
  /* @Trace: NvM_SUD_MACRO_017 */
  #if(STD_ON == NVM_CRC_SUPPORT)
    if(NVM_CALC_RAM_BLK_CRC == (blkParams & NVM_CALC_RAM_BLK_CRC))
    { /* start block comment 7 */
      varCrcLength = NvM_NvmBlkDescTbl->ucCrcLength;
      varCRCSIDIndex += varCrcLength;
    } /* end block comment 7 */
  #endif

    if(NVM_REQ_OK == NvM_JobResultLowLevel)
    {
      /* verify data size is always lower or equal NvBlock size in validate rule */
      verifyDataSize = NvM_NvmBlkDescTbl->usWriteVerificationDataSize;
      varOffset = (NvM_WriteVerify - NVM_ONE) * verifyDataSize;
      if(((NvM_BlockLength + varCRCSIDIndex) - varOffset) < verifyDataSize)
      {
        verifyDataSize = (NvM_BlockLength + varCRCSIDIndex) - varOffset;
      }
      /* @Trace: NvM_SUD_MACRO_016 NvM_SUD_MACRO_028 */
      if((((uint32)varOffset + (uint32)verifyDataSize) <= 
        ((uint32)NVM_MIRROR_BUFFER + (uint32)NVM_CRC_SID_SIZE)) &&
        (NULL_PTR != NvM_DataBuffer))
      {
        verifyDataSize %= (NVM_MIRROR_BUFFER + 1);
        for(varCnt = NVM_ZERO; varCnt < verifyDataSize; varCnt++)
        {
          if(NvM_DataBuffer[varOffset + varCnt] != NvM_MirrorBuffer[varCnt])
          {
            result = NVM_FALSE;
            break;
          }
        }
      }
    } /* @End of if(NVM_REQ_OK == NvM_JobResultLowLevel) */
    else
    {
      result = NVM_FALSE;
    }

    /* @Trace: NvM_SUD_FUNC_305 */
    if(NVM_MULTIBLK_IN_PROGRESS == NvM_WriteAllRequest)
    {
      NvM_State = NVM_WRITEALL_SID;
    }
  /* @Trace: NvM_SUD_MACRO_041 NvM_SUD_MACRO_047 */
  #if((0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS) && \
    (NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS))
    else if((NVM_MULTIBLK_IN_PROGRESS == NvM_FirstInitAllRequest)
      #if(STD_ON == NVM_JOB_PRIO)
        && (NVM_FALSE == NvM_HighPriorityRequest)
      #endif
    )
    {
      NvM_State = NVM_FIRSTINITALL_SID;
    }
    else
    {
    }
  #endif

    if(NVM_FALSE == result)
    {
      /* @Trace: NvM_SUD_FUNC_306 NvM_SUD_MACRO_021 */
      #if(STD_ON == NVM_DEMERROR_REPORT)
        if((NVM_FALSE == NvM_BackUp) || 
          (NVM_MULTIBLK_IN_PROGRESS == NvM_ReadAllRequest))
        {
          /* @Trace: NvM_SUD_MACRO_003 */
          /* @Trace: NvM_SUD_DATATYPE_001 */
          /* @Trace: NvM_SUD_DATATYPE_002 */
          (void)Dem_SetEventStatus(NVM_E_VERIFY_FAILED, 
            DEM_EVENT_STATUS_FAILED);
        }
      #endif
        NvM_SubState = NVM_WRITE_PROCESS_NV_BLOCK;
        NvM_JobResultLowLevel = NVM_REQ_INTEGRITY_FAILED;
    }
    else
    {
      /* @Trace: NvM_SUD_FUNC_307 */
      /* End the verify */
      if((varOffset + verifyDataSize) == (NvM_BlockLength + varCRCSIDIndex))
      {
        NvM_SubState = NVM_WRITE_PROCESS_NV_BLOCK;
      }
      else
      /* Continue verify */
      {
        NvM_WriteVerify++;
        NvM_SubState = NVM_READ_START;
        NvM_State = NVM_READBLOCK_SID;
        NvM_JobResultLowLevel = NVM_REQ_NOT_OK;
      }
    } /* end else part of if(NVM_FALSE == result) */

    /* reload GpRamData */
    /* if verify ok or fail, perform reload data to original ram */
    /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
    #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
      if((NVM_READBLOCK_SID != NvM_State) && ((NVM_TRUE == NvM_BackUp) && 
        (NvM_RamAddr == &NvM_MirrorBuffer[0])))
      {
        /* if the content of NvM_RamAddr is same as NvM_DataBuffer,
         * do not reload NvM_RamAddr
         */
        if((NVM_ZERO == varCRCSIDIndex) && (NVM_TRUE == result)
          && (NVM_ONE == NvM_WriteVerify))
        {
        }
        else
        {
          /* @Trace: NvM_SUD_FUNC_449 NvM_SUD_MACRO_017 */
          #if(STD_ON == NVM_CRC_SUPPORT)
            if(NVM_CALC_RAM_BLK_CRC == (blkParams & NVM_CALC_RAM_BLK_CRC))
            { /* start block comment 7 */
              varCRCSIDIndex -= (uint16)varCrcLength;
            } /* end block comment 7 */
          #endif
            /* polyspace-begin RTE:IDP [Justified:Low] "NvM_RamAddr is pointing to NvM_MirrorBuffer and is a valid buffer" */
            if((NVM_TWO >= varCRCSIDIndex) && (NULL_PTR != NvM_DataBuffer))
            {
              for(varCnt = NVM_ZERO; varCnt < NvM_BlockLength; varCnt++)
              {
                NvM_RamAddr[varCnt] = NvM_DataBuffer[varCRCSIDIndex];
                varCRCSIDIndex++;
              }
            }
            /* polyspace-end RTE:IDP */
        }
      }
    #endif
}
#endif

/*******************************************************************************
** Function Name        : NvM_ProcessWriteBlock                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This service writes data and CRC from RAM           **
**                        to NV block.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)   : NvM_SubState,                **
**                        NvM_NvmBlkDescTbl, NvM_FirstBlock,                  **
**                        NvM_BackUp, NvM_DataBuffer, NvM_BlockIdx,           **
**                        NvM_JobResultLowLevel, NvM_BlkMngmntType,           **
**                        NvM_RamStatus, NvM_WriteVerify                      **
**                        Function(s) invoked  : NvM_WriteNvBlockProcess(),   **
**                        NvM_CalcBlkNumber(), NvM_ProcessWriteVerify(),      **
**                        NvM_WriteProcessNvBlock(), MemIf_Write()            **
*******************************************************************************/
/* @Trace: SRS_LIBS_08535 SRS_Mem_00017 SRS_Mem_00027 SRS_Mem_00136 SRS_Mem_08554 SRS_Mem_08556 SRS_BSW_00339 SRS_Mem_00011 SRS_Mem_08000 */
FUNC(void, NVM_CODE) NvM_ProcessWriteBlock(void)
{
  VAR(Std_ReturnType, AUTOMATIC) status;
  VAR(uint8, AUTOMATIC) deviceID;
  VAR(uint16, AUTOMATIC) blkNumber;
  P2VAR(uint16, AUTOMATIC, NVM_VAR_NOINIT) ptrRamStatus;

  if(NULL_PTR != NvM_NvmBlkDescTbl)
  {
    switch (NvM_SubState)
    {
      case NVM_WRITE_NVBLOCK:
      case NVM_PROCESS_WRITE_ACCEPT:
        if (NVM_WRITE_NVBLOCK == NvM_SubState)
        {
          /* @Trace: NvM_SUD_FUNC_497 */
          NvM_WriteNvBlockProcess();
        }

        if (NVM_PROCESS_WRITE_ACCEPT == NvM_SubState)
        {
          deviceID = NvM_NvmBlkDescTbl->ucNvramDeviceId;
          /* set up block 1st nv to write */
          if(NVM_BLOCK_REDUNDANT == NvM_BlkMngmntType)
          {
            /* @Trace: NvM_SUD_FUNC_286 */
            ptrRamStatus = &NvM_RamStatus[NvM_BlockIdx];
            if((NVM_FIR_REDUNDANT_MASK == (*(ptrRamStatus) & 
              NVM_FIR_REDUNDANT_MASK)) || (NVM_TRUE == NvM_BackUp))
            {
              NvM_FirstBlock = NVM_RE_COPY_FIRST;
            }
          }
          /* @Trace: NvM_SUD_FUNC_288 */
          blkNumber = NvM_CalcBlkNumber();
          NvM_JobResultLowLevel = NVM_REQ_PENDING;
          if (NVM_ZERO != blkNumber)
          {
            status = MemIf_Write(deviceID, blkNumber, NvM_DataBuffer);
          }
          else
          {
            status = E_NOT_OK;
          }

          if (E_OK != status)
          {
            NvM_JobResultLowLevel = NVM_REQ_INTEGRITY_FAILED;
          }
          else
          {
            /* Writing of data is being processed */
          }
          NvM_SubState = NVM_WRITE_PROCESS_NV_BLOCK;
          /* @Trace: NvM_SUD_MACRO_027 NvM_SUD_MACRO_046 */
          #if(STD_ON == NVM_WRITE_VERIFICATION)
            NvM_WriteVerify = NVM_ZERO;
          #endif
        }
      break;

      case NVM_WRITE_PROCESS_NV_BLOCK:
        /* @Trace: NvM_SUD_FUNC_498 */
        NvM_WriteProcessNvBlock();
      break;
      /* @Trace: NvM_SUD_MACRO_046 */
      /* write verification after read data from NV */
      #if(STD_ON == NVM_WRITE_VERIFICATION)
        case NVM_PROCESS_WRITE_VERIFY:
          /* @Trace: NvM_SUD_FUNC_499 */
          NvM_ProcessWriteVerify();
        break;
      #endif

      default:
        /* Do nothing */
        break;

    }  /* end switch (NvM_SubState) */
  } /* end of if(NULL_PTR != NvM_NvmBlkDescTbl) */
} /* End of function body */

/*******************************************************************************
** Function Name        : NvM_WriteAllProcess                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Processes request to synchronize the contents of RAM**
**                        blocks to their corresponding NV blocks during      **
**                        shutdown.                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)  : NvM_WriteAllSubState,         **
**                        NvM_RamStatus, NvM_CancelWriteAllRequest,           **
**                        NvM_SubState, NvM_NotifiedGlobalStatus,             **
**                        NvM_RetryCount, NvM_WriteAllCnt, NvM_SetModeStatus, **
**                        NvM_BlockIdx, NvM_BlkDescTbls, NvM_WriteAllBlocks,  **
**                        NvM_NvmBlkDescTbl, NvM_JobResultLowLevel            **
**                        Function(s) invoked  : NvM_UpdateGlobalVars(),      **
**                        MemIf_SetMode(), BswM_NvM_CurrentBlockMode(),       **
**                        NvM_CalculateCrcOffset()                            **
*******************************************************************************/
/* @Trace: NvM_SUD_MACRO_044 */
#if(0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS)
NVM_STATIC FUNC(void, NVM_CODE) NvM_WriteAllProcess(void)
{
  P2VAR(uint16, AUTOMATIC, NVM_VAR_NOINIT) ptrRamStatus;
  VAR(uint16, AUTOMATIC) writeAllCnt;
  VAR(NvM_BlockIdType, AUTOMATIC) blockIdx;
  VAR(uint16, AUTOMATIC) blkParams;
  VAR(boolean, AUTOMATIC) varFlag;

  if(NVM_TRUE == NvM_CancelWriteAllRequest)
  {
    /* - set all single block that has not yet write from pending to cancel */
    /* @Trace: NvM_SUD_FUNC_314 NvM_SUD_MACRO_044 */
    for(writeAllCnt = NvM_WriteAllCnt; writeAllCnt <
      NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS; writeAllCnt++)
    {
      /* @Trace: NvM_SUD_FUNC_315 NvM_SUD_GLOBALDATA_030 */
      blockIdx = NvM_WriteAllBlocks[writeAllCnt];
      if(NVM_REQ_PENDING == NVM_GET_JOB_RESULT(blockIdx))
      {
        NVM_SET_JOB_RESULT(blockIdx, NVM_REQ_CANCELED);
        /* Inform to BswM */
        NvM_NvmBlkDescTbl = &NvM_BlkDescTbls[blockIdx];
        blkParams = NvM_NvmBlkDescTbl->usBlkParams;
        if(NVM_BSWM_BLOCK_STATUS_INFORMATION == 
          (blkParams & NVM_BSWM_BLOCK_STATUS_INFORMATION))
        {
          BswM_NvM_CurrentBlockMode(blockIdx, NVM_REQ_CANCELED);
        }
      }
    } /* @End of for(writeAllCnt = NvM_WriteAllCnt; ... */

    /* @Trace: NvM_SUD_FUNC_317 */
    NvM_NotifiedGlobalStatus = NVM_REQ_CANCELED;

    /* Clear the sub states and the flags */
    NvM_WriteAllSubState = NVM_WRITE_ALL_IDLE;
    NvM_SubState = NVM_SUB_IDLE;

    /*
     * Invoke function (if configured) to put the memory devices back to
     * 'Slow' mode when cancelling the WriteAll request 
     * - note: when NVM_DRV_MODE_SWTCH == STD_ON, NVM will change mode fast 
     * when ReadAll or WriteAll
     */
    /* @Trace: NvM_SUD_MACRO_022 */
    #if(STD_ON == NVM_DRV_MODE_SWITCH)
      /* @Trace: NvM_SUD_FUNC_318 */
      /* @Trace: NvM_SUD_DATATYPE_004 */
      MemIf_SetMode(MEMIF_MODE_SLOW);
      NvM_JobResultLowLevel = NVM_REQ_PENDING;
      NvM_SetModeStatus = NVM_TRUE;
    #endif

  }  /* end if(NVM_TRUE == NvM_CancelWriteAllRequest) */
  /* Continue processing, if processing of all blocks is not complete */
  else
  {
    /* @Trace: NvM_SUD_MACRO_044 */
    if(NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS > NvM_WriteAllCnt)
    {
      do
      {
        /* @Trace: NvM_SUD_FUNC_452 NvM_SUD_GLOBALDATA_030 */
        NvM_BlockIdx = NvM_WriteAllBlocks[NvM_WriteAllCnt];
        NvM_NvmBlkDescTbl = &NvM_BlkDescTbls[NvM_BlockIdx];
        ptrRamStatus = &NvM_RamStatus[NvM_BlockIdx];
        /* @Trace: NvM_SUD_MACRO_004 NvM_SUD_MACRO_017 */
        #if((STD_ON == NVM_CRC_SUPPORT) && \
        (STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM))
          blkParams = NvM_NvmBlkDescTbl->usBlkParams;
        #endif

        if(NVM_REQ_PENDING == (*(ptrRamStatus) & NVM_ERROR_BIT_MASK))
        {
          /* @Trace: NvM_SUD_FUNC_319 */
          varFlag = NVM_TRUE;
          /* Load the Retry counter */
          NvM_RetryCount = NvM_NvmBlkDescTbl->ucMaxNumOfWriteRetries;
          NvM_UpdateGlobalVars();
          NvM_SubState = NVM_WRITE_NVBLOCK;
          NvM_WriteAllSubState = NVM_WRITE_ALL_PROCESS;
          /* @Trace: NvM_SUD_MACRO_004 NvM_SUD_MACRO_017 */
          #if((STD_ON == NVM_CRC_SUPPORT) && \
          (STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM)) 
            if((NVM_BLOCK_USE_CRC_COMP_MASK == (blkParams & 
              NVM_BLOCK_USE_CRC_COMP_MASK)) && (NVM_CALC_RAM_BLK_CRC ==
              (blkParams & NVM_CALC_RAM_BLK_CRC)))
            {
              NvM_CalculateCrcOffset(NvM_BlockIdx);
            }
          #endif
        } /* @End of if(NVM_REQ_PENDING == (*(ptrRamStatus) & NVM_ERROR_BIT_MASK)) */
        else
        {
          /* @Trace: NvM_SUD_FUNC_451 */
          NvM_WriteAllCnt++;
          varFlag = NVM_FALSE;
        }
      /* @Trace: NvM_SUD_MACRO_044 */
      }while((varFlag == NVM_FALSE) &&
        (NvM_WriteAllCnt < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS));
    } /* end of if(NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS > NvM_WriteAllCnt) */
    /* @Trace: NvM_SUD_MACRO_044 */
    if(NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS <= NvM_WriteAllCnt)
    {
      /* If processing of all blocks is complete, update the Global status */
      /* @Trace: NvM_SUD_FUNC_320 */
      NvM_BlockIdx = NVM_ZERO;

      NvM_NvmBlkDescTbl = &NvM_BlkDescTbls[NVM_ZERO];
      /*
       * Invoke function (if configured) to put the memory devices back to
       * 'Slow' mode after completion of WriteAll request
       */
      NvM_WriteAllSubState = NVM_WRITE_ALL_IDLE;
      /* @Trace: NvM_SUD_MACRO_022 */
      #if(STD_ON == NVM_DRV_MODE_SWITCH)
        /* @Trace: NvM_SUD_FUNC_321 */
        MemIf_SetMode(MEMIF_MODE_SLOW);
        NvM_JobResultLowLevel = NVM_REQ_PENDING;
        NvM_SetModeStatus = NVM_TRUE;
      #endif
    } /* end if(NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS <= NvM_WriteAllCnt) */
  } /* end else part of if(NVM_TRUE == NvM_CancelWriteAllRequest) */
}
#endif

/*******************************************************************************
** Function Name        : NvM_ProcessWriteAllBlocks                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Processes request to synchronize the contents of RAM**
**                        blocks to their corresponding NV blocks during      **
**                        shutdown.                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)  : NvM_WriteAllSubState,         **
**                        NvM_RamStatus, NvM_NotWriteAll, NvM_BlkDescTbls,    **
**                        NvM_SubState, NvM_WriteAllCnt, NvM_NvmBlkDescTbl,   **
**                        NvM_WriteAllBlocks, NvM_SetModeStatus,              **
**                        NvM_JobResultLowLevel, NvM_ConfigIdMatch            **
**                        Function(s) invoked  : NvM_WriteAllProcess(),       **
**                        Det_ReportError(), NvM_ProcessWriteBlock(),         **
**                        MemIf_GetStatus(), BswM_NvM_CurrentBlockMode()      **
*******************************************************************************/
/* @Trace: SRS_Mem_08535 SRS_Mem_08540 SRS_Mem_00011 NvM_SUD_MACRO_044 */
#if(0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS)
FUNC(void, NVM_CODE) NvM_ProcessWriteAllBlocks(void)
{
  P2VAR(uint16, AUTOMATIC, NVM_VAR_NOINIT) ptrRamStatus;
  VAR(uint16, AUTOMATIC) writeAllCnt;
  VAR(NvM_BlockIdType, AUTOMATIC) blockIdx;
  VAR(NvM_RequestResultType, AUTOMATIC) result;
  VAR(uint16, AUTOMATIC) blkParams;

  /* @Trace: NvM_SUD_MACRO_022 */
  #if(STD_ON == NVM_DRV_MODE_SWITCH)
  if((NVM_TRUE == NvM_SetModeStatus) && 
    (NVM_REQ_PENDING == NvM_JobResultLowLevel))
  {
    if(MEMIF_BUSY != MemIf_GetStatus(MEMIF_BROADCAST_ID))
    {
      /* Finish SetMode job */
      /* @Trace: NvM_SUD_FUNC_527 */
      NvM_JobResultLowLevel = NVM_REQ_OK;
      NvM_SetModeStatus = NVM_FALSE;
    }
  }
  else
  {
    NvM_SetModeStatus = NVM_FALSE;
  }

  if((NVM_TRUE != NvM_SetModeStatus) || 
    (NVM_REQ_PENDING != NvM_JobResultLowLevel))
  #endif
  {
    switch (NvM_WriteAllSubState)
    {
      /* Holds the count of blocks to be processed for WriteAll operation */
      case NVM_WRITE_ALL_INIT:
        NvM_WriteAllCnt = NVM_ZERO;
        /* @Trace: NvM_SUD_MACRO_049 */
        #if(NVM_BLOCKS_NOT_CONFIG_WRITEALL > 0)
        /* @Trace: NvM_SUD_FUNC_308 NvM_SUD_MACRO_049 */
        for(writeAllCnt = NVM_ZERO; NVM_BLOCKS_NOT_CONFIG_WRITEALL >
          writeAllCnt; writeAllCnt++)
        {
          /* @Trace: NvM_SUD_GLOBALDATA_028 */
          blockIdx = NvM_NotWriteAll[writeAllCnt];

          NVM_SET_JOB_RESULT(blockIdx, NVM_REQ_BLOCK_SKIPPED);

          /* Inform to BswM */
          NvM_NvmBlkDescTbl = &NvM_BlkDescTbls[blockIdx];
          blkParams = NvM_NvmBlkDescTbl->usBlkParams;
          if(NVM_BSWM_BLOCK_STATUS_INFORMATION == 
            (blkParams & NVM_BSWM_BLOCK_STATUS_INFORMATION))
          {
            BswM_NvM_CurrentBlockMode(blockIdx, NVM_REQ_BLOCK_SKIPPED);
          }
        } /* @End of for(writeAllCnt = NVM_ZERO; ... */
        #endif
        /* @Trace: NvM_SUD_MACRO_044 */
        for(writeAllCnt = NVM_ZERO; NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS > 
          writeAllCnt; writeAllCnt++)
        {
          /* @Trace: NvM_SUD_FUNC_312 NvM_SUD_GLOBALDATA_030 */
          blockIdx = NvM_WriteAllBlocks[writeAllCnt];
          ptrRamStatus = &NvM_RamStatus[blockIdx];
          NvM_NvmBlkDescTbl = &NvM_BlkDescTbls[blockIdx];
          blkParams = NvM_NvmBlkDescTbl->usBlkParams;
          /*Check protection and "valid/modified" in advanced */
          if((NVM_LOCK_RAM_MASK != (*(ptrRamStatus) & NVM_LOCK_RAM_MASK)) &&
            ((NVM_CHECK_LOSS_OF_REDUNDANCY == (*(ptrRamStatus) & 
            NVM_CHECK_LOSS_OF_REDUNDANCY)) || (NVM_WRITE_PROTECT_MASK != 
            (*(ptrRamStatus) & NVM_WRITE_PROTECT_MASK)))
            /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_034 NvM_SUD_MACRO_036 NvM_SUD_MACRO_032 */
            #if((STD_ON == NVM_SET_RAM_BLOCK_STATUS_API) && \
              ((STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS) || \
              (STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)))
              && ((NVM_BLOCK_USE_SETRAMBLOCKSTATUS != 
                (blkParams & NVM_BLOCK_USE_SETRAMBLOCKSTATUS)) ||
                (NVM_VALID_CHANGED == (*(ptrRamStatus) & NVM_RAM_STATUS_MASK)) 
                /* @Trace: NvM_SUD_MACRO_008 */
                #if(STD_ON == NVM_DYNAMIC_CONFIGURATION)
                || ((NVM_ONE == blockIdx) && (NVM_FALSE == NvM_ConfigIdMatch))
                #endif
                )
            #endif
            && ((NVM_ONE != blockIdx)
            #if(STD_ON == NVM_DYNAMIC_CONFIGURATION)
              || (NVM_FALSE == NvM_ConfigIdMatch)
            #endif
            )
            #if(STD_ON == NVM_DATASET_PRESENT)
              && ((NVM_BLOCK_DATASET != NvM_NvmBlkDescTbl->enBlkMngmntType) ||
              (NvM_NvmBlkDescTbl->ucNumOfNvBlks > NvM_RamIndex[blockIdx]))
            #endif
          )
          { /* start block comment 1 */
            /* @Trace: NvM_SUD_FUNC_310 */
            if((NVM_WRITE_BLOCK_ONCE == (blkParams & NVM_WRITE_BLOCK_ONCE)) && (
              NVM_CHECK_READ_PRIOR != (*(ptrRamStatus) & NVM_CHECK_READ_PRIOR)))
            {
              result = NVM_REQ_BLOCK_SKIPPED;
              /* @Trace: NvM_SUD_MACRO_007 */
              #if(STD_ON == NVM_DEV_ERROR_DETECT)
                (void)Det_ReportError(NVM_MODULE_ID, NVM_INSTANCE_ID, 
                  NVM_WRITEALL_SID, NVM_E_WRITE_ONCE_STATUS_UNKNOWN);
              #endif
            }
            else
            {
              result = NVM_REQ_PENDING;
            }
          } /* end block comment 1 */
          else
          {
            /* @Trace: NvM_SUD_FUNC_311 */
            result = NVM_REQ_BLOCK_SKIPPED;
          }
          /* @Trace: NvM_SUD_FUNC_313 */
          NVM_SET_JOB_RESULT(blockIdx, result);
          if(NVM_BSWM_BLOCK_STATUS_INFORMATION == (blkParams & 
            NVM_BSWM_BLOCK_STATUS_INFORMATION))
          {
            BswM_NvM_CurrentBlockMode(blockIdx, result);
          }
        } /* end of for(writeAllCnt = NVM_ZERO; ... */
        /* @Trace: NvM_SUD_FUNC_309 */
        NvM_WriteAllSubState = NVM_WRITE_ALL_BLOCK;
      break;

      case NVM_WRITE_ALL_BLOCK:
        /* @Trace: NvM_SUD_FUNC_500 */
        NvM_WriteAllProcess();
      break;

      case NVM_WRITE_ALL_PROCESS:
        /* Call the function to copy the RAM data to NV block */
        /* @Trace: NvM_SUD_FUNC_322 */
        NvM_ProcessWriteBlock();

        if(NVM_SUB_IDLE == NvM_SubState)
        {
          /*
           * If the processing of the block is complete, increment block index to
           * process the next block
           */
          NvM_WriteAllCnt++;
          NvM_WriteAllSubState = NVM_WRITE_ALL_BLOCK;
        }
      break;

      default:
        /* Do nothing */
        break;

    }  /* end switch (NvM_WriteAllSubState) */
  }
}  /* End of function body */
#endif

/*******************************************************************************
** Function Name        : NvM_ProcessImmdWrite                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function which performs the immediate          **
**                        write operation                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_State, NvM_BlockIdx,   **
**                        NvM_RetryCount, NvM_SubState, NvM_NvmBlkDescTbl,    **
**                        Function(s) invoked    : NvM_CalculateCrcOffset(),  **
**                        NvM_ProcessWriteBlock()                             **
*******************************************************************************/
/* @Trace: NvM_SUD_MACRO_023 NvM_SUD_MACRO_025 NvM_SUD_MACRO_047 */
#if((NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) && \
    (STD_ON == NVM_JOB_PRIORITIZATION) && (STD_ON == NVM_IMM_JOB_PRIORITY))
NVM_STATIC FUNC(void, NVM_CODE) NvM_ProcessImmdWrite(void)
{
  /* @Trace: NvM_SUD_FUNC_323 */
  if((NULL_PTR != NvM_NvmBlkDescTbl) && 
    (NVM_TOTAL_NUM_OF_NVRAM_BLOCKS > NvM_BlockIdx))
  { /* start block comment 1 */
    if(NVM_IMMD_WRITE_PENDING == NvM_State)
    {
      NvM_State = NVM_WRITEBLOCK_SID;
    }
    else
    {
      NvM_State = NVM_WRITEPRAMBLOCK_SID;
    }

    NvM_RetryCount = NvM_NvmBlkDescTbl->ucMaxNumOfWriteRetries;
    NvM_SubState = NVM_WRITE_NVBLOCK;
    /* @Trace: NvM_SUD_MACRO_004 NvM_SUD_MACRO_017 */
    #if((STD_ON == NVM_CRC_SUPPORT) && \
      (STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM)) 
      if((NVM_BLOCK_USE_CRC_COMP_MASK == (NvM_NvmBlkDescTbl->usBlkParams & 
        NVM_BLOCK_USE_CRC_COMP_MASK)) && (NVM_CALC_RAM_BLK_CRC == 
        (NvM_NvmBlkDescTbl->usBlkParams & NVM_CALC_RAM_BLK_CRC)))
      {
        NvM_CalculateCrcOffset(NvM_BlockIdx);
      }
    #endif
    #if(STD_ON == UPDATE_RAM_STATUS_ENABLE)
      NvM_UpdateRamStateStatus(NVM_VALID_CHANGED);
    #endif
      NvM_ProcessWriteBlock();
  } /* end block comment 1 */
} /* end of function body */
#endif

#endif /* end #if((NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) || \
  (0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS) || \
  (0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS)) */

/*******************************************************************************
** Function Name        : NvM_ValidateAllProcess                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is NVRAM Manager internal function.            **
**                        This function checks and loads the RAM contents     **
**                        and reports the Global error/status                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_ValidateAllCnt,        **
**                        NvM_BlockIdx, NvM_NvmBlkDescTbl, NvM_MirrorBuffer,  **
**                        NvM_BlkDescTbls, NvM_ValidateAllBlocks, NvM_State,  **
**                        NvM_NotifiedGlobalStatus, NvM_MirrorCount,          **
**                        NvM_ValidateAllState, NvM_ValidateAllRequest        **
**                                                                            **
**                        Function(s) invoked    : Dem_SetEventStatus(),      **
**                        BswM_NvM_CurrentBlockMode(),                        **
**                        BswM_NvM_CurrentJobMode, NVM_MULTI_BLOCK_CBK(),     **
*******************************************************************************/
/* @Trace: NvM_SUD_MACRO_043 NvM_SUD_MACRO_047 */
#if((0 < NVM_TOTAL_NUM_OF_VALIDATEALL_BLOCKS) && \
  (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS))
NVM_STATIC FUNC(void, NVM_CODE) NvM_ValidateAllProcess(void)
{
  /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
  #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
    VAR(Std_ReturnType, AUTOMATIC) returnValue;
    VAR(boolean, AUTOMATIC) isFail;
    /* @Trace: NvM_SUD_FUNC_520 */
    returnValue = E_OK;
    isFail = NVM_FALSE;
  #endif
  /* @Trace: NvM_SUD_MACRO_043 */
  if(NVM_TOTAL_NUM_OF_VALIDATEALL_BLOCKS > NvM_ValidateAllCnt)
  {
    /* @Trace: NvM_SUD_FUNC_138 NvM_SUD_GLOBALDATA_031 */
    NvM_BlockIdx = NvM_ValidateAllBlocks[NvM_ValidateAllCnt];
    NvM_NvmBlkDescTbl = &NvM_BlkDescTbls[NvM_BlockIdx];
    if(NVM_REQ_PENDING == NVM_GET_JOB_RESULT(NvM_BlockIdx))
    {
      /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
      #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
        if(NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE == (
          NvM_NvmBlkDescTbl->usBlkParams & NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE))
        { /* start block comment 1 */
          /* @Trace: NvM_SUD_FUNC_142 */
          if(NULL_PTR !=  NvM_NvmBlkDescTbl->pNvMWriteRamBlockToNvm)
          {
            returnValue = (NvM_NvmBlkDescTbl->pNvMWriteRamBlockToNvm)
              ((void *)(&NvM_MirrorBuffer[0]));
          }

          if(E_OK == returnValue)
          {
            /* @Trace: NvM_SUD_FUNC_139 NvM_SUD_MACRO_035 */
            NvM_MirrorCount = NVM_REPEAT_MIRROR_OPERATIONS;
          }
          else
          {
            /* @Trace: NvM_SUD_FUNC_140 */
            if(NVM_ZERO != NvM_MirrorCount)
            {
              NvM_MirrorCount--;
            }
            else
            {
              /* @Trace: NvM_SUD_MACRO_021 */
              #if(STD_ON == NVM_DEMERROR_REPORT)
                (void)Dem_SetEventStatus(NVM_E_REQ_FAILED, 
                  DEM_EVENT_STATUS_FAILED);
              #endif
                isFail = NVM_TRUE;
            }
          }
        } /* end block comment 1 */
      #endif
    } /* end of if(NVM_REQ_PENDING == NVM_GET_JOB_RESULT(NvM_BlockIdx)) */
    /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
    #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
      if((NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE == (NvM_NvmBlkDescTbl->usBlkParams 
        & NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE)) && (NVM_TRUE == isFail))
      {
        /* @Trace: NvM_SUD_FUNC_141 NvM_SUD_MACRO_035 */
        NvM_MirrorCount = NVM_REPEAT_MIRROR_OPERATIONS;
        NVM_SET_JOB_RESULT(NvM_BlockIdx, NVM_REQ_NOT_OK);
        /* @Trace: NvM_SUD_FUNC_143 */
        if(NVM_BSWM_BLOCK_STATUS_INFORMATION == (
          NvM_NvmBlkDescTbl->usBlkParams & NVM_BSWM_BLOCK_STATUS_INFORMATION))
        {
          BswM_NvM_CurrentBlockMode(NvM_BlockIdx, NVM_REQ_NOT_OK);
        }
        NvM_ValidateAllCnt++;
        NvM_NotifiedGlobalStatus = NVM_REQ_NOT_OK;
      }
      else if(E_OK == returnValue)
    #endif
      {
        /* @Trace: NvM_SUD_FUNC_145 */
        NvM_ValidateAllCnt++;
        NVM_SET_JOB_RESULT(NvM_BlockIdx, NVM_REQ_OK);
        if(NVM_BSWM_BLOCK_STATUS_INFORMATION == (
          NvM_NvmBlkDescTbl->usBlkParams & NVM_BSWM_BLOCK_STATUS_INFORMATION))
        {
          BswM_NvM_CurrentBlockMode(NvM_BlockIdx, NVM_REQ_OK);
        }
      }
    /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
    #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
      else
      {
      }
    #endif
  } /* end of if(NVM_TOTAL_NUM_OF_VALIDATEALL_BLOCKS > NvM_ValidateAllCnt) */
  else
  {
    /* If processing of all blocks is complete, update the Global status */
    /* @Trace: NvM_SUD_FUNC_144 */
    NvM_BlockIdx = NVM_ZERO;
    NvM_NvmBlkDescTbl = &NvM_BlkDescTbls[NVM_ZERO];
    /* Update the Global status */
    NVM_SET_JOB_RESULT(NVM_RESERVED_BLOCK_ID, NvM_NotifiedGlobalStatus);
    /* @Trace: NvM_SUD_FUNC_146 NvM_SUD_MACRO_006 */
    #if(STD_ON == NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION)
      (void)BswM_NvM_CurrentJobMode(NVM_VALIDATE_ALL, NvM_NotifiedGlobalStatus);
    /* @Trace: NvM_SUD_MACRO_029 NvM_SUD_MACRO_031 */
    #elif(STD_ON == NVM_MULTIBLKCBK_ENABLE)
      (void)NVM_MULTI_BLOCK_CBK(NVM_VALIDATE_ALL, NvM_NotifiedGlobalStatus);
    #endif
      /* @Trace: NvM_SUD_FUNC_147 */
      NvM_ValidateAllState = NVM_VALIDATEALL_IDLE;
      NvM_State = NVM_IDLE;
      NvM_ValidateAllRequest = NVM_MULTIBLK_UNREQUESTED;
  } /* end else (NVM_TOTAL_NUM_OF_NVRAM_BLOCKS > NvM_BlockIdx) */
}
#endif

/*******************************************************************************
** Function Name        : NvM_ProcessValidateAllBlocks                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This is NVRAM Manager internal function.            **
**                        This function checks and loads the RAM contents     **
**                        and reports the Global error/status                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_ValidateAllState,      **
**                        NvM_NvmBlkDescTbl, NvM_ValidateAllBlocks,           **
**                        NvM_BlkDescTbls, NvM_MirrorCount,                   **
**                        NvM_ValidateAllCnt                                  **
**                                                                            **
**                        Function(s) invoked    : NvM_ValidateAllProcess()   **
*******************************************************************************/
/* @Trace: SRS_Mem_00137 NvM_SUD_MACRO_043 NvM_SUD_MACRO_047 */
#if((0 < NVM_TOTAL_NUM_OF_VALIDATEALL_BLOCKS) && \
  (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS))
FUNC(void, NVM_CODE) NvM_ProcessValidateAllBlocks(void)
{
  VAR(uint16, AUTOMATIC) indexCnt;

  switch (NvM_ValidateAllState)
  {
    case NVM_VALIDATEALL_INIT:
      /* @Trace: NvM_SUD_MACRO_043 */
      for(indexCnt = NVM_ZERO; indexCnt < NVM_TOTAL_NUM_OF_VALIDATEALL_BLOCKS;
        indexCnt++)
      {
        /* @Trace: NvM_SUD_FUNC_136 NvM_SUD_GLOBALDATA_031 */
        NvM_NvmBlkDescTbl = &NvM_BlkDescTbls[NvM_ValidateAllBlocks[indexCnt]];
        NVM_SET_JOB_RESULT(NvM_ValidateAllBlocks[indexCnt], NVM_REQ_PENDING);
        if(NVM_BSWM_BLOCK_STATUS_INFORMATION == (
          NvM_NvmBlkDescTbl->usBlkParams & NVM_BSWM_BLOCK_STATUS_INFORMATION))
        {
          BswM_NvM_CurrentBlockMode
            (NvM_ValidateAllBlocks[indexCnt], NVM_REQ_PENDING);
        }
      }
        /* @Trace: NvM_SUD_FUNC_137 NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
      #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
        /* @Trace: NvM_SUD_MACRO_035 */
        NvM_MirrorCount = NVM_REPEAT_MIRROR_OPERATIONS;
      #endif
        NvM_ValidateAllState = NVM_VALIDATEALL_PROCESS;
        NvM_ValidateAllCnt = NVM_ZERO;
    break;

    case NVM_VALIDATEALL_PROCESS:
      /* @Trace: NvM_SUD_FUNC_519 */
      NvM_ValidateAllProcess();
    break;

    default:
      /* Do nothing */
      break;

  }  /* end switch (NvM_ValidateAllState) */

} /* End of function body */
#endif

/*******************************************************************************
** Function Name        : NvM_MainFunctionMultiProcess                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function which performs the immediate          **
**                        write operation                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)    : NvM_State, NvM_SubState,    **
**                        NvM_ReadAllRequest, NvM_WriteAllRequest,            **
**                        NvM_FirstInitAllRequest, NvM_ValidateAllRequest     **
**                        NvM_JobResultLowLevel, NvM_NotifiedGlobalStatus,    **
**                        NvM_ReadAllState, NvM_WriteAllSubState,             **
**                        NvM_SetModeStatus, NvM_ValidateAllState,            **
**                        NvM_FirstInitAllState, NvM_PMCount                  **
**                        Function(s) invoked   : NvM_ProcessWriteAllBlocks(),**
**                        NvM_ProcessReadAllBlocks(), NvM_ScanQueue(),        **
**                        BswM_NvM_CurrentJobMode(), MemIf_SetMode(),         **
**                        SchM_Enter_NvM_RAM_STATUS_PROTECTION(),             **
**                        SchM_Exit_NvM_RAM_STATUS_PROTECTION(),              **
**                        NVM_MULTI_BLOCK_CBK(), BswM_RequestMode(),          **
**                        NvM_ProcessValidateAllBlocks(),                     **
**                        NvM_ProcessFirstInitAllBlocks()                     **
*******************************************************************************/
FUNC(void, NVM_CODE) NvM_MainFunctionMultiProcess(void)
{
  switch (NvM_State)
  {
    case NVM_IDLE:
      /*
       * The queue implementations are available only for API
       * Configuration Class 2 and 3
       */
      /* @Trace: NvM_SUD_MACRO_047 */
      #if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
      /* Scan the standard priority queue */
        if(NVM_FALSE == NvM_ScanQueue())
      #endif
        { /* Start of Block comment-2 */
          /*
           * If none of the queued requests are in progress and ReadAll
           * is requested
           */
          if(NVM_MULTIBLK_REQUESTED == NvM_ReadAllRequest)
          {
            /* @Trace: NvM_SUD_MACRO_042 */
            #if(0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS)
              /* @Trace: NvM_SUD_FUNC_346 */
              NvM_State = NVM_READALL_SID;
              NvM_ReadAllRequest = NVM_MULTIBLK_IN_PROGRESS;

              /* MemIf_SetMode function to be invoked with fast mode before
               * the start of the read activity
               */
              /* @Trace: NvM_SUD_MACRO_022 */
              #if(STD_ON == NVM_DRV_MODE_SWITCH)
                /* @Trace: NvM_SUD_DATATYPE_004 */
                MemIf_SetMode(MEMIF_MODE_FAST);
                NvM_JobResultLowLevel = NVM_REQ_PENDING;
                NvM_SetModeStatus = NVM_TRUE;
              #endif
                /* @Trace: NvM_SUD_FUNC_347 */
                NvM_NotifiedGlobalStatus = NVM_REQ_OK;
                NvM_ReadAllState = NVM_READALL_INIT;
                NvM_ProcessReadAllBlocks();
            #else
              /* @Trace: NvM_SUD_FUNC_348 NvM_SUD_MACRO_006 */
              NVM_SET_JOB_RESULT(NVM_RESERVED_BLOCK_ID, NVM_REQ_OK);
              #if(STD_ON == NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION)
                /* @Trace: NvM_SUD_FUNC_349 */
                (void)BswM_NvM_CurrentJobMode(NVM_READ_ALL, NVM_REQ_OK);
              /* @Trace: NvM_SUD_MACRO_029 */
              #elif(STD_ON == NVM_MULTIBLKCBK_ENABLE)
                /* @Trace: NvM_SUD_FUNC_350 NvM_SUD_MACRO_031 */
                (void)NVM_MULTI_BLOCK_CBK(NVM_READ_ALL, NvM_NotifiedGlobalStatus);
              #endif
                /* Clear the main state and flags */
                /* Update the ReadAll request flag */
                /* @Trace: NvM_SUD_FUNC_453 */
                NvM_ReadAllRequest = NVM_MULTIBLK_UNREQUESTED;
            #endif
          } /* End of if(NVM_MULTIBLK_REQUESTED == NvM_ReadAllRequest) */
          /*
           * If none of the queued requests are in progress and WriteAll
           * is requested
           */
          else if(NVM_MULTIBLK_REQUESTED == NvM_WriteAllRequest)
          {
            /* Update the Write and WriteAll sub states */
            /* @Trace: NvM_SUD_FUNC_351 */
            NvM_State = NVM_WRITEALL_SID;
            NvM_WriteAllRequest = NVM_MULTIBLK_IN_PROGRESS;
            /* @Trace: NvM_SUD_MACRO_044 */
            #if(0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS)
              /* @Trace: NvM_SUD_FUNC_352 */
              NvM_NotifiedGlobalStatus = NVM_REQ_OK;
              NvM_WriteAllSubState = NVM_WRITE_ALL_INIT;
              /* Update the global error status */
              /* @Trace: NvM_SUD_MACRO_022 */
              #if(STD_ON == NVM_DRV_MODE_SWITCH)
                MemIf_SetMode(MEMIF_MODE_FAST);
                NvM_JobResultLowLevel = NVM_REQ_PENDING;
                NvM_SetModeStatus = NVM_TRUE;
              #endif
                NvM_ProcessWriteAllBlocks();
            #else
              /* @Trace: NvM_SUD_FUNC_353 */
              NvM_NotifiedGlobalStatus = NVM_REQ_OK;
              NvM_WriteAllSubState = NVM_WRITE_ALL_IDLE;
            #endif
          } /* End of else if(NVM_MULTIBLK_REQUESTED == NvM_WriteAllRequest) */
          /* @Trace: NvM_SUD_MACRO_047 */
          #if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
            else if(NVM_MULTIBLK_REQUESTED == NvM_ValidateAllRequest)
            {
              /* @Trace: NvM_SUD_FUNC_357 */
              NvM_State = NVM_VALIDATEALL_SID;

              /* Update the global error status */
              NvM_NotifiedGlobalStatus = NVM_REQ_OK;

              NvM_ValidateAllRequest = NVM_MULTIBLK_IN_PROGRESS;
              /* @Trace: NvM_SUD_MACRO_043 */
              #if(0 < NVM_TOTAL_NUM_OF_VALIDATEALL_BLOCKS)
                /* @Trace: NvM_SUD_FUNC_354 */
                NvM_ValidateAllState = NVM_VALIDATEALL_INIT;
                NvM_ProcessValidateAllBlocks();
              #else
                /* @Trace: NvM_SUD_FUNC_355 */
                NVM_SET_JOB_RESULT(NVM_RESERVED_BLOCK_ID, NVM_REQ_OK);
                /* @Trace: NvM_SUD_FUNC_356 NvM_SUD_MACRO_006 */
                #if(STD_ON == NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION)
                  (void)BswM_NvM_CurrentJobMode(NVM_VALIDATE_ALL, NVM_REQ_OK);
                /* @Trace: NvM_SUD_MACRO_029 NvM_SUD_MACRO_031 */
                #elif(STD_ON == NVM_MULTIBLKCBK_ENABLE)
                  (void)NVM_MULTI_BLOCK_CBK(NVM_VALIDATE_ALL, 
                    NvM_NotifiedGlobalStatus);
                #endif
                  NvM_State = NVM_IDLE;
                  NvM_ValidateAllRequest = NVM_MULTIBLK_UNREQUESTED;
              #endif
            } /* End of else if(NVM_MULTIBLK_REQUESTED == NvM_ValidateAllRequest) */
          #endif
          /* @Trace: NvM_SUD_MACRO_047 */
          #if(NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS)
            else if(NVM_MULTIBLK_REQUESTED == NvM_FirstInitAllRequest)
            {
              /* Update the FirstInitAll sub states */
              /* @Trace: NvM_SUD_MACRO_041 */
              #if(0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS)
                /* @Trace: NvM_SUD_FUNC_358 */
                NvM_State = NVM_FIRSTINITALL_SID;
                NvM_NotifiedGlobalStatus = NVM_REQ_OK;
                NvM_FirstInitAllRequest = NVM_MULTIBLK_IN_PROGRESS;
                NvM_FirstInitAllState = NVM_FIRSTINITALL_INIT;
                NvM_ProcessFirstInitAllBlocks();
              #else
                /* @Trace: NvM_SUD_FUNC_359 */
                /* Clear main state and flag */
                NvM_State = NVM_IDLE;
                NvM_SubState = NVM_SUB_IDLE;
                NVM_SET_JOB_RESULT(NVM_RESERVED_BLOCK_ID, NVM_REQ_OK);
                /* @Trace: NvM_SUD_FUNC_360 NvM_SUD_MACRO_006 */
                #if(STD_ON == NVM_BSWM_MULTI_BLOCK_JOB_STATUS_INFORMATION)
                  (void)BswM_NvM_CurrentJobMode(NVM_FIRST_INIT_ALL, NVM_REQ_OK);
                /* @Trace: NvM_SUD_MACRO_029 NvM_SUD_MACRO_031 */
                #elif(STD_ON == NVM_MULTIBLKCBK_ENABLE)
                  (void)NVM_MULTI_BLOCK_CBK(NVM_FIRST_INIT_ALL, NVM_REQ_OK);
                #endif
                /* Update the firstinitall request flag */
                  NvM_FirstInitAllRequest = NVM_MULTIBLK_UNREQUESTED;
              #endif
            } /* End of else if(NVM_MULTIBLK_REQUESTED == NvM_FirstInitAllRequest) */
          #endif
            else
            {
              /* @Trace: NvM_SUD_FUNC_361 */
              SchM_Enter_NvM_RAM_STATUS_PROTECTION();
              if (NVM_ZERO == NvM_PMCount)
              {
                SchM_Exit_NvM_RAM_STATUS_PROTECTION();
                BswM_RequestMode((BswM_UserType)NVM_MODULE_ID,
                              (BswM_ModeType)NVM_LOWPOWER_ALLOW);
              }
              else
              {
                SchM_Exit_NvM_RAM_STATUS_PROTECTION();
              }
            }
        }
    break;
    /* @Trace: NvM_SUD_MACRO_043 NvM_SUD_MACRO_047 */
    #if((0 < NVM_TOTAL_NUM_OF_VALIDATEALL_BLOCKS) && \
    (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS))
      case NVM_VALIDATEALL_SID :
        /* @Trace: NvM_SUD_FUNC_371 */
        NvM_ProcessValidateAllBlocks();
      break;
    #endif
    /* @Trace: NvM_SUD_MACRO_041 NvM_SUD_MACRO_047 */
    #if((0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS) && \
      (NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS))
      case NVM_FIRSTINITALL_SID :
        /* @Trace: NvM_SUD_FUNC_372 */
        NvM_ProcessFirstInitAllBlocks();
      break;
    #endif
    /* @Trace: NvM_SUD_MACRO_042 */
    #if(0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS)
      case NVM_READALL_SID :
        /* @Trace: NvM_SUD_FUNC_370 */
        NvM_ProcessReadAllBlocks();
      break;
    #endif

    /* polyspace-begin RTE:UNR [Justified:Low] " Default case to avoid misra and warning" */
    default: 
      /* Do nothing */
    break;
    /* polyspace-end RTE:UNR */
  }
}

/*******************************************************************************
** Function Name        : NvM_MainFunctionProcessImmediate                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function which performs the immediate          **
**                        write operation                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : jobSwitch                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : processImm                                          **
**                                                                            **
** Preconditions        : NvM should be initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     : NvM_State, NvM_BlkDescTbls,**
**                        NvM_HighPriorityRequest, NvM_JobResultLowLevel,     **
**                        NvM_NvmBlkDescTbl, NvM_WriteAllRequest,             **
**                        NvM_ReadAllRequest, NvM_BlockIdx, NvM_RamAddr,      **
**                        NvM_MirrorBuffer                                    **
**                        Function(s) invoked    : NvM_ProcessImmdWrite(),    **
**                        NvM_ProcessWriteBlock(), NvM_ProcessReadBlock(),    **
**                        NvM_ImmQueueRead(), MemIf_GetStatus(),              **
**                        NvM_UpdateGlobalVars(), MemIf_Cancel()              **
*******************************************************************************/
/* @Trace: SRS_Mem_00011 */
#if(STD_ON == NVM_JOB_PRIO)
FUNC(boolean, NVM_CODE) NvM_MainFunctionProcessImmediate(
  VAR(uint8, AUTOMATIC) jobSwitch)
{
  VAR(NvM_JobQueue, AUTOMATIC) varCheckQueue;
  VAR(boolean, AUTOMATIC) pending;
  VAR(boolean, AUTOMATIC) immQueuecheck;
  VAR(boolean, AUTOMATIC) processImm;
  processImm = NVM_FALSE;

  if(NVM_WRITE_IMM_JOB == jobSwitch)
  {
    if(NVM_TRUE == NvM_HighPriorityRequest)
    {
      /* @Trace: NvM_SUD_FUNC_518 */
      processImm = NVM_TRUE;
      /* Immediate priority 'Write' request is being processed */
      switch (NvM_State)
      {
        case NVM_IMMD_WRITE_PENDING :
        case NVM_IMMD_WRITE_PRAM_PENDING:
          if(NVM_REQ_PENDING != NvM_JobResultLowLevel)
          {
            /* @Trace: NvM_SUD_FUNC_339 */
            NvM_ProcessImmdWrite();
          }
          break;
        case NVM_WRITEBLOCK_SID :
        case NVM_WRITEPRAMBLOCK_SID:
          /* @Trace: NvM_SUD_FUNC_340 */
          NvM_ProcessWriteBlock();
          break;
        case NVM_READBLOCK_SID:
          /* @Trace: NvM_SUD_FUNC_341 */
          NvM_ProcessReadBlock();
          break;
        default:
          /* Do nothing */
          break;
      }
    }
  }
  else
  {
    /* @Trace: NvM_SUD_FUNC_342 */
    if((NVM_MULTIBLK_IN_PROGRESS != NvM_WriteAllRequest) &&
      (NVM_MULTIBLK_IN_PROGRESS != NvM_ReadAllRequest))
    {
      immQueuecheck = NvM_ImmQueueRead(&varCheckQueue);
    }
    else
    {
      immQueuecheck = NVM_FALSE;
    }
    /* Check if immediate priority queue is not empty */
    if(NVM_TRUE == immQueuecheck)
    { /* Start block comment 4 */
      pending = NVM_FALSE;
      processImm = NVM_TRUE;
      /*
       * If the request is in progress, cancel the request to process
       * immediate priority job
       */
      if ((NULL_PTR != NvM_NvmBlkDescTbl) && (NVM_REQ_PENDING == 
        NvM_JobResultLowLevel))
      {
        pending = NVM_TRUE;
      
        MemIf_Cancel(NvM_NvmBlkDescTbl->ucNvramDeviceId);
        /* @Trace: NvM_SUD_DATATYPE_005 */
        if(MEMIF_IDLE == MemIf_GetStatus(NvM_NvmBlkDescTbl->ucNvramDeviceId))
        {
          NvM_JobResultLowLevel = NVM_REQ_OK;
        }
      }

      if((NVM_IDLE != NvM_State) && (NvM_FirstInitAllRequest != 
        NVM_MULTIBLK_IN_PROGRESS) && (NvM_ValidateAllRequest != 
        NVM_MULTIBLK_IN_PROGRESS))
      {
        /*
         * Set a flag to indicate that a immediate request is aborting the
         * standard request and save the states to resume the aborted request
         */
        NvM_PrevReqImm = NVM_TRUE;
        NvM_StdPrevReq.pTempRamBlkData = NvM_RamAddr;
      }

      /*
       * Update the Global Descriptor pointer to process the immediate
       * priority request
       */
      NvM_NvmBlkDescTbl = &NvM_BlkDescTbls[varCheckQueue.ddBlock_Idx];

      NvM_UpdateGlobalVars();
      NvM_BlockIdx = varCheckQueue.ddBlock_Idx;
      NvM_RamAddr = varCheckQueue.pTempRamBlkData;
      /* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
      #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
        if((NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE == 
          (NvM_NvmBlkDescTbl->usBlkParams & 
          NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE)) && (NULL_PTR == NvM_RamAddr))
        {
          /* @Trace: NvM_SUD_FUNC_343 */
          NvM_RamAddr = NvM_MirrorBuffer;
        }
        else
      #endif
        {
          /* If not temporary ram or using ram mirror => using permanent ram */
          if(NULL_PTR == NvM_RamAddr)
          {
            /* @Trace: NvM_SUD_MACRO_034 */
            #if(STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS)
              if(NULL_PTR != NvM_NvmBlkDescTbl->pRamBlkData)
              {
                /* @Trace: NvM_SUD_FUNC_344 */
                /* polyspace-begin CERT-C:EXP36-C [Justified:Low] "Follow AUTOSAR specification, NvM does not know user data type so It need to be cast from (void*) to (uint8*) " */
                NvM_RamAddr = (uint8*)NvM_NvmBlkDescTbl->pRamBlkData;
                /* polyspace-end CERT-C:EXP36-C [Justified:Low] "Follow AUTOSAR specification, NvM does not know user data type so It need to be cast from (void*) to (uint8*) " */
              }
            #endif
          }
        }
        /* Indicate immediate priority request is under progress */
        /* @Trace: NvM_SUD_FUNC_345 */
        NvM_HighPriorityRequest = NVM_TRUE;

        if(NVM_WRITEBLOCK_SID == varCheckQueue.ucService_Id)
        {
          NvM_State = NVM_IMMD_WRITE_PENDING;
        }
        else
        {
          NvM_State = NVM_IMMD_WRITE_PRAM_PENDING;
        }

        if(NVM_TRUE == pending)
        {
        /* update the global status to check for the pending immediate write */
        }
        else
        {
          NvM_ProcessImmdWrite();
        }
    }  /* End block comment 4 */
  }

  return processImm;
}
#endif

#define NVM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end MISRA2012:11.5 */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
