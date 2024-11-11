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
**  SRC-MODULE: NvM_Globals.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : Global Variable declarations.                                 **
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
** 0.0.1       06-Dec-2019    VinhLV5     Initial version                     **
** 0.0.2       04-May-2020    VinhLV5     Update traceability, apply          **
**                                        new v cycle, Fix Misra              **
** 0.0.3       24-Jul-2020    VinhLV5     R44-Redmine #9958                   **
** 1.0.2       27-Aug-2021    JH Lim      R44-Redmine #19726                  **
** 1.1.0       08-Dec-2021    JH Lim      R44-Redmine #19388                  **
** 1.1.1.1     29-Jun-2022    SH Park     Improvement mobilegence             **
**                                          Classic <CP44-221>                **
*******************************************************************************/

#ifndef NVM_GLOBALS_H
#define NVM_GLOBALS_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/* Init RAM 32 Bit Section */
#if((STD_ON == NVM_CRC_SUPPORT) && (STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM))
#define NVM_START_SEC_VAR_CLEARED_32
#include "MemMap.h"

/* Variable to hold CrcOffset */
extern VAR(uint32, NVM_VAR_NOINIT) NvM_CrcOffSet;

#define NVM_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"
#endif
/* End RAM 32 Bit Section */

/* Init RAM 16 Bit Section */
#define NVM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"

/* Holds the total block length */
extern VAR(uint16, NVM_VAR_NOINIT) NvM_BlockLength;

/* @Trace: NvM_SUD_GLOBALVAR_001 */
/* Holds the total block length */
extern VAR(uint16, NVM_VAR_NOINIT) NvM_RamStatus[NVM_TOTAL_NUM_OF_NVRAM_BLOCKS];

#if(0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS)
/* Holds the count of blocks to be processed for ReadAll operation */
extern VAR(uint16, NVM_VAR_NOINIT) NvM_ReadAllCnt;
#endif

#if((0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS) && \
  (NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS))
/* Holds the count of blocks to be processed for FirstInitAll operation */
extern VAR(uint16, NVM_VAR_NOINIT) NvM_FirstInitAllCnt;
#endif

#if(0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS)
/* Holds the count of blocks to be processed for WriteAll operation */
extern VAR(uint16, NVM_VAR_NOINIT) NvM_WriteAllCnt;
#endif

#if((0 < NVM_TOTAL_NUM_OF_VALIDATEALL_BLOCKS) && \
  (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS))
/* Holds the count of blocks to be processed for ValidateAll operation */
extern VAR(uint16, NVM_VAR_NOINIT) NvM_ValidateAllCnt;
#endif

#if((NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) && \
  (STD_ON == NVM_JOB_PRIORITIZATION) && (STD_ON == NVM_IMM_JOB_PRIORITY))
/* Holds the start position of Immediate queue buffer */
extern VAR(uint16, NVM_VAR_NOINIT) NvM_ImmQueStartPos;

/* Holds the end position of Immediate queue buffer */
extern VAR(uint16, NVM_VAR_NOINIT) NvM_ImmQueEndPos;

/* Holds the index of Immediate Free list */
extern VAR(uint16, NVM_VAR_NOINIT) NvM_ImmFreeIndx;

/* Holds the index of Immediate Free list */
extern VAR(uint16, NVM_VAR_NOINIT) NvM_ImmFreeSlotsAvail;
#endif

#if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
/* Holds the start position of Standard queue buffer */
extern VAR(uint16, NVM_VAR_NOINIT) NvM_StdQueStartPos;

/* Holds the end position of Standard queue buffer */
extern VAR(uint16, NVM_VAR_NOINIT) NvM_StdQueEndPos;
/* Holds the free index of Standard queue buffer */

/* Holds the index of Standard Free list */
extern VAR(uint16, NVM_VAR_NOINIT) NvM_StdFreeIndx;

/* Holds the index of Standard Free list */
extern VAR(uint16, NVM_VAR_NOINIT) NvM_StdFreeSlotsAvail;

#endif

/* To hold the status of write verification */
#if(STD_ON == NVM_WRITE_VERIFICATION)
extern VAR(uint16, NVM_VAR_NOINIT) NvM_WriteVerify;
#endif

#if(STD_ON == NVM_CRC_SUPPORT)
/* Hold the step calculate Crc */
extern VAR(uint16, NVM_VAR_NOINIT) NvM_CrcStepCnt;
#endif

#define NVM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

/* Init RAM 8 Bit Section */
#define NVM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* Holds the retry count */
extern VAR(uint8, NVM_VAR_NOINIT) NvM_RetryCount;

#if(STD_ON == NVM_DATASET_PRESENT)
/* @Trace: NvM_SUD_GLOBALVAR_018 */
/* Holds the dataset index */
extern VAR(uint8, NVM_VAR_NOINIT) NvM_RamIndex[NVM_TOTAL_NUM_OF_NVRAM_BLOCKS];
#endif

/*
 * Following variables are used for maintaining Main and Sub states of NVRAM
 * Manager Module
 */

/* Holds the NVRAM Manager main state */
extern VAR(uint8, NVM_VAR_NOINIT) NvM_State;

/* Holds the NVRAM Manager Sub state */
extern VAR(uint8, NVM_VAR_NOINIT) NvM_SubState;

/* Holds the NVRAM Manager Sub states of ReadAll Function */
extern VAR(uint8, NVM_VAR_NOINIT) NvM_ReadAllState;

/*  Holds the NVRAM Manager Sub states of WriteAll Function */
extern VAR(uint8, NVM_VAR_NOINIT) NvM_WriteAllSubState;

/*  Holds the NVRAM Manager Sub states of ValidateAll Function */
#if((0 < NVM_TOTAL_NUM_OF_VALIDATEALL_BLOCKS) && \
  (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS))
extern VAR(uint8, NVM_VAR_NOINIT) NvM_ValidateAllState;
#endif

#if((NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS) && \
  (0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS))
/* Holds the NVRAM Manager Sub states of FirstInitAll Function */
extern VAR(uint8, NVM_VAR_NOINIT) NvM_FirstInitAllState;
#endif

/* Following variables are used for generic purpose */

/* Indicates Global status of WriteAll/ReadAll function */
extern VAR(uint8, NVM_VAR_NOINIT) NvM_NotifiedGlobalStatus;

/*
 * Following variables are used as flags for holding the status of NVRAM
 * Manager operation during different API requests
 */

/* Flag to indicate status of processing of Redundant block */
extern VAR(NvM_StatusReBlock, NVM_VAR_NOINIT) NvM_ReStatus;

/* Flag to indicate status of processing of Redundant block */
extern VAR(NvM_RefirstBlock, NVM_VAR_NOINIT) NvM_FirstBlock;

/* Flag to indicate NvM_WriteAll request acceptance */
extern VAR(uint8, NVM_VAR_NOINIT) NvM_WriteAllRequest;

/* Flag to indicate NvM_ReadAll request acceptance */
extern VAR(uint8, NVM_VAR_NOINIT) NvM_ReadAllRequest;

/* Flag to indicate NvM_FirstInitAll request acceptance */
#if(NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS)
extern VAR(uint8, NVM_VAR_NOINIT) NvM_FirstInitAllRequest;
#endif

/* Flag to indicate NvM_ValidateAll request acceptance */
#if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
extern VAR(uint8, NVM_VAR_NOINIT) NvM_ValidateAllRequest;
#endif

#if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
/* Holds count for Mirror Retries */
extern VAR(uint8, NVM_VAR_NOINIT) NvM_MirrorCount;
#endif

/* Holds count for sending PM Prevent */
extern volatile VAR(uint8, NVM_VAR_NOINIT) NvM_PMCount;

/* Global variable to calculate CRC */
#if((STD_ON == NVM_CRC_SUPPORT) || (STD_ON == NVM_STATIC_ID_CHECK))
#if((STD_ON == NVM_CRC32_SUPPORT) && (STD_ON == NVM_CRC_SUPPORT))
/* Hold the High byte of Crc */
extern VAR(uint8, NVM_VAR_NOINIT) NvM_Msb;
/* Hold the Mid high byte of Crc */
extern VAR(uint8, NVM_VAR_NOINIT) NvM_MidHi;
/* Hold the Mid low byte of Crc */
extern VAR(uint8, NVM_VAR_NOINIT) NvM_MidLow;
/* Hold the Low byte of Crc */
extern VAR(uint8, NVM_VAR_NOINIT) NvM_Lsb;
#if(STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM)
/* Array to hold high byte of NVRAM config to use compare mechanism */
extern VAR(uint8, NVM_VAR_NOINIT) NvM_MsbArray[NVM_COMPARE_NUM_NV_BLOCK];
/* Array to hold Mid high byte of NVRAM config to use compare mechanism */
extern VAR(uint8, NVM_VAR_NOINIT) NvM_MidHiArray[NVM_COMPARE_NUM_NV_BLOCK];
/* Array to hold Mid low byte of NVRAM config to use compare mechanism */
extern VAR(uint8, NVM_VAR_NOINIT) NvM_MidLowArray[NVM_COMPARE_NUM_NV_BLOCK];
/* Array to hold low byte of NVRAM config to use compare mechanism */
extern VAR(uint8, NVM_VAR_NOINIT) NvM_LsbArray[NVM_COMPARE_NUM_NV_BLOCK];
#endif
#elif(((STD_ON == NVM_CRC16_SUPPORT) && (STD_ON == NVM_CRC_SUPPORT)) || \
  (STD_ON == NVM_STATIC_ID_CHECK))
extern VAR(uint8, NVM_VAR_NOINIT) NvM_Msb;
extern VAR(uint8, NVM_VAR_NOINIT) NvM_Lsb;
#if(STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM)
extern VAR(uint8, NVM_VAR_NOINIT) NvM_MsbArray[NVM_COMPARE_NUM_NV_BLOCK];
extern VAR(uint8, NVM_VAR_NOINIT) NvM_LsbArray[NVM_COMPARE_NUM_NV_BLOCK];
#endif
#else
#if(STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM)
extern VAR(uint8, NVM_VAR_NOINIT) NvM_LsbArray[NVM_COMPARE_NUM_NV_BLOCK];
#endif
#endif
#endif

#if((STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM) || ((NVM_API_CONFIG_CLASS_3 == \
  NVM_API_CONFIG_CLASS) && (0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS)) || \
  ((STD_ON == NVM_WRITE_VERIFICATION)))
/* @Trace: NvM_SUD_GLOBALVAR_048 */
/* Buffer to hold Mirror data, hold data for internal buffer for first init all */
extern VAR(uint8, NVM_VAR_NOINIT) NvM_MirrorBuffer[NVM_MIRROR_BUFFER
  #if(STD_ON == NVM_WRITE_VERIFICATION)
  + 2U
  #endif
  ];
#endif

/* Pointer to the RAM data block */
extern P2VAR(uint8, NVM_VAR_NOINIT, NVM_APPL_DATA) NvM_RamAddr;
/* Pointer to the Buffer use to read and write */
extern P2VAR(uint8, NVM_VAR_NOINIT, NVM_VAR_NOINIT) NvM_DataBuffer;
/* Hold the restore block state */
extern VAR(uint8, NVM_VAR_NOINIT) NvM_RestoreBlockstate;
#define NVM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define NVM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#if((STD_ON == NVM_STATIC_ID_CHECK) || (STD_ON == NVM_CRC_SUPPORT))
/* Holds the CRC/Static ID data */
extern VAR(uint8, NVM_VAR_NOINIT) NvM_ReadCRCSID[NVM_CRC_SID_SIZE];
#endif

/* Indicates status of MEMIF Driver service command */
extern VAR(NvM_RequestResultType, NVM_VAR_NOINIT) NvM_JobResultLowLevel;
/* Indicates status of first Redundant block */
extern VAR(NvM_RequestResultType, NVM_VAR_NOINIT) NvM_JobResultFirstBlock;

#if (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
/* @Trace: NvM_SUD_GLOBALVAR_002 */
/* Buffer to hold the standard priority request Block Id and Service Id */
extern VAR(NvM_JobQueue, NVM_VAR_NOINIT) NvM_StdQueueBuffer[
  NVM_SIZE_STANDARD_JOB_QUEUE];

/* Structure to hold the standard priority request Block Id and Service Id */
extern VAR(NvM_JobQueue, NVM_VAR_NOINIT) NvM_StdPrevReq;
#endif

#if((NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) && \
  (STD_ON == NVM_JOB_PRIORITIZATION) && (STD_ON == NVM_IMM_JOB_PRIORITY))
/* @Trace: NvM_SUD_GLOBALVAR_058 */
/* Buffer to hold the immediate priority request Block Id and Service Id */
extern VAR(NvM_JobQueue, NVM_VAR_NOINIT) NvM_ImmQueueBuffer[
  NVM_SIZE_IMMEDIATE_JOB_QUEUE];
#endif

/* Pointer to Global Descriptor Table */
extern P2CONST(NvM_BlkDescTbl, NVM_VAR_NOINIT, NVM_CONST) NvM_NvmBlkDescTbl;

/* Indicates the Global Block Id which is under progress */
extern VAR(NvM_BlockIdType, NVM_VAR_NOINIT) NvM_BlockIdx;

/* Holds the Block Management type */
extern VAR(NvM_BlockManagementType, NVM_VAR_NOINIT) NvM_BlkMngmntType;
#define NVM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define NVM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* Hold the status of MemIf_SetMode job */
#if(STD_ON == NVM_DRV_MODE_SWITCH)
extern VAR(boolean, NVM_VAR_NOINIT) NvM_SetModeStatus;
#endif

/* Hold the status of backup redundant block */
extern VAR(boolean, NVM_VAR_NOINIT) NvM_BackUp;

#if((NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) && \
  (STD_ON == NVM_JOB_PRIORITIZATION) && (STD_ON == NVM_IMM_JOB_PRIORITY))
/*
 * Flag to indicate immediate priority request (immediate Erase/Write) is in
 * progress
 */
extern VAR(boolean, NVM_VAR_NOINIT) NvM_HighPriorityRequest;

/* Flag holds the status of previous immediate request */
extern VAR(boolean, NVM_VAR_NOINIT) NvM_PrevReqImm;
#endif

/* Flag to indicate status of "Cancel Write All" request */
extern VAR(boolean, NVM_VAR_NOINIT) NvM_CancelWriteAllRequest;

/* Flag to indicate that stored and compiled Configuration Ids are matching */
#if(STD_ON == NVM_DYNAMIC_CONFIGURATION)
extern VAR(boolean, NVM_VAR_NOINIT) NvM_ConfigIdMatch;
#endif

/* Variable to indicate NVRAM Manager is initialized */
extern VAR(boolean, NVM_VAR_NOINIT) NvM_InitStatus;

#define NVM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define NVM_START_SEC_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED
#include "MemMap.h"

/* Buffer to hold Mirror data, 6 : management bytes for EA , 2 : reserved */
extern VAR(uint8, NVM_VAR_NOINIT) NvM_DataBufferSource[
  NVM_MIRROR_BUFFER+NVM_CRC_SID_SIZE + 8U];

#define NVM_STOP_SEC_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED
#include "MemMap.h"

#endif  /* NVM_GLOBALS_H */

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
