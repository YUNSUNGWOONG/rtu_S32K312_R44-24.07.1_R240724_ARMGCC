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
**  SRC-MODULE: NvM_Globals.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : Global variable declarations.                                 **
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
** 1.1.1.1     29-Jun-2022    SH Park     Improvement mobilegence             **
**                                          Classic <CP44-221>                **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin VARIABLE:* [Justified:Low] "Global variable used within NvM module" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "NvM.h"
#include "NvM_IntTypes.h"
#if(STD_ON == NVM_DEMERROR_REPORT)
#include "NvM_Dem_Cfg.h"      /* Dem header file */
#endif
#include "NvM_Globals.h"      /* Global variables header file */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* @Trace: NvM_SUD_MACRO_017 */
/* Init RAM 32 Bit Section */
#if((STD_ON == NVM_CRC_SUPPORT) && (STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM))
#define NVM_START_SEC_VAR_CLEARED_32
#include "MemMap.h"

/* Variable to hold CrcOffset */
VAR(uint32, NVM_VAR_NOINIT) NvM_CrcOffSet;

#define NVM_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"
#endif
/* End RAM 32 Bit Section */

/* Init RAM 16 Bit Section */
#define NVM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"

/* Holds the total block length */
VAR(uint16, NVM_VAR_NOINIT) NvM_BlockLength;

/* Holds the total block length */
VAR(uint16, NVM_VAR_NOINIT) NvM_RamStatus[NVM_TOTAL_NUM_OF_NVRAM_BLOCKS];
/* @Trace: NvM_SUD_MACRO_042 */
#if(0 < NVM_TOTAL_NUM_OF_READALL_BLOCKS)
/* Holds the count of blocks to be processed for ReadAll operation */
VAR(uint16, NVM_VAR_NOINIT) NvM_ReadAllCnt;
#endif
/* @Trace: NvM_SUD_MACRO_044 */
#if(0 < NVM_TOTAL_NUM_OF_WRITEALL_BLOCKS)
/* Holds the count of blocks to be processed for WriteAll operation */
VAR(uint16, NVM_VAR_NOINIT) NvM_WriteAllCnt;
#endif
/* @Trace: NvM_SUD_MACRO_047 */
#if((0 < NVM_TOTAL_NUM_OF_VALIDATEALL_BLOCKS) && \
  (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS))
/* Holds the count of blocks to be processed for ValidateAll operation */
VAR(uint16, NVM_VAR_NOINIT) NvM_ValidateAllCnt;
#endif
/* @Trace: NvM_SUD_MACRO_047 */
#if((0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS) && \
  (NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS))
/* Holds the count of blocks to be processed for FirstInitAll operation */
VAR(uint16, NVM_VAR_NOINIT) NvM_FirstInitAllCnt;
#endif
/* @Trace: NvM_SUD_MACRO_047 */
#if((NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) && \
  (STD_ON == NVM_JOB_PRIORITIZATION) && (STD_ON == NVM_IMM_JOB_PRIORITY))
/* Holds the start position of Immediate queue buffer */
VAR(uint16, NVM_VAR_NOINIT) NvM_ImmQueStartPos;

/* Holds the end position of Immediate queue buffer */
VAR(uint16, NVM_VAR_NOINIT) NvM_ImmQueEndPos;

/* Holds the index of Immediate Free list */
VAR(uint16, NVM_VAR_NOINIT) NvM_ImmFreeIndx;

/* Holds the index of Immediate Free list */
VAR(uint16, NVM_VAR_NOINIT) NvM_ImmFreeSlotsAvail;
#endif
/* @Trace: NvM_SUD_MACRO_047 */
#if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
/* Holds the start position of Standard queue buffer */
VAR(uint16, NVM_VAR_NOINIT) NvM_StdQueStartPos;

/* Holds the end position of Standard queue buffer */
VAR(uint16, NVM_VAR_NOINIT) NvM_StdQueEndPos;
/* Holds the free index of Standard queue buffer */

/* Holds the index of Standard Free list */
VAR(uint16, NVM_VAR_NOINIT) NvM_StdFreeIndx;

/* Holds the index of Standard Free list */
VAR(uint16, NVM_VAR_NOINIT) NvM_StdFreeSlotsAvail;

#endif
/* @Trace: NvM_SUD_MACRO_046 */
/* To hold the status of write verification */
#if(STD_ON == NVM_WRITE_VERIFICATION)
VAR(uint16, NVM_VAR_NOINIT) NvM_WriteVerify;
#endif
/* @Trace: NvM_SUD_MACRO_017 */
#if(STD_ON == NVM_CRC_SUPPORT)
/* Hold the step calculate Crc */
VAR(uint16, NVM_VAR_NOINIT) NvM_CrcStepCnt;
#endif

#define NVM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

/* Init RAM 8 Bit Section */
#define NVM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* Holds the retry count */
VAR(uint8, NVM_VAR_NOINIT) NvM_RetryCount;
/* @Trace: NvM_SUD_MACRO_019 NvM_SUD_MACRO_018 NvM_SUD_MACRO_020 */
#if(STD_ON == NVM_DATASET_PRESENT)
/* Holds the dataset index */
VAR(uint8, NVM_VAR_NOINIT) NvM_RamIndex[NVM_TOTAL_NUM_OF_NVRAM_BLOCKS];
#endif

/*
 * Following variables are used for maintaining Main and Sub states of NVRAM
 * Manager Module
 */
/* Holds the NVRAM Manager main state */
VAR(uint8, NVM_VAR_NOINIT) NvM_State;

/* Holds the NVRAM Manager Sub state */
VAR(uint8, NVM_VAR_NOINIT) NvM_SubState;

/* Holds the NVRAM Manager Sub states of ReadAll Function */
VAR(uint8, NVM_VAR_NOINIT) NvM_ReadAllState;

/*  Holds the NVRAM Manager Sub states of WriteAll Function */
VAR(uint8, NVM_VAR_NOINIT) NvM_WriteAllSubState;
/* @Trace: NvM_SUD_MACRO_047 */
/*  Holds the NVRAM Manager Sub states of ValidateAll Function */
#if((0 < NVM_TOTAL_NUM_OF_VALIDATEALL_BLOCKS) && \
  (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS))
VAR(uint8, NVM_VAR_NOINIT) NvM_ValidateAllState;
#endif
/* @Trace: NvM_SUD_MACRO_047 */
#if((NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS) && \
  (0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS))
/*  Holds the NVRAM Manager Sub states of FirstInitAll Function */
VAR(uint8, NVM_VAR_NOINIT) NvM_FirstInitAllState;
#endif

/* Following variables are used for generic purpose */

/* Indicates Global status of WriteAll/ReadAll function */
VAR(uint8, NVM_VAR_NOINIT) NvM_NotifiedGlobalStatus;

/*
 * Following variables are used as flags for holding the status of NVRAM
 * Manager operation during different API requests
 */

/* Flag to indicate status of processing of Redundant block */
VAR(NvM_StatusReBlock, NVM_VAR_NOINIT) NvM_ReStatus;

/* Flag to indicate status of processing of Redundant block */
VAR(NvM_RefirstBlock, NVM_VAR_NOINIT) NvM_FirstBlock;

/* Flag to indicate NvM_WriteAll request acceptance */
VAR(uint8, NVM_VAR_NOINIT) NvM_WriteAllRequest;

/* Flag to indicate NvM_ReadAll request acceptance */
VAR(uint8, NVM_VAR_NOINIT) NvM_ReadAllRequest;
/* @Trace: NvM_SUD_MACRO_047 */
/* Flag to indicate NvM_FirstInitAll request acceptance */
#if(NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS)
VAR(uint8, NVM_VAR_NOINIT) NvM_FirstInitAllRequest;
#endif
/* @Trace: NvM_SUD_MACRO_047 */
/* Flag to indicate NvM_ValidateAll request acceptance */
#if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
VAR(uint8, NVM_VAR_NOINIT) NvM_ValidateAllRequest;
#endif

/* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_032 */
#if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
/* Holds count for Mirror Retries */
VAR(uint8, NVM_VAR_NOINIT) NvM_MirrorCount;
#endif

/* Holds count for sending PM Prevent */
volatile VAR(uint8, NVM_VAR_NOINIT) NvM_PMCount;

/* Global variable to calculate CRC */
/* @Trace: NvM_SUD_MACRO_013 NvM_SUD_MACRO_017 */
#if((STD_ON == NVM_CRC_SUPPORT) || (STD_ON == NVM_STATIC_ID_CHECK))
#if((STD_ON == NVM_CRC32_SUPPORT) && (STD_ON == NVM_CRC_SUPPORT))
/* Hold the High byte of Crc */
VAR(uint8, NVM_VAR_NOINIT) NvM_Msb;
/* Hold the Mid high byte of Crc */
VAR(uint8, NVM_VAR_NOINIT) NvM_MidHi;
/* Hold the Mid low byte of Crc */
VAR(uint8, NVM_VAR_NOINIT) NvM_MidLow;
/* Hold the Low byte of Crc */
VAR(uint8, NVM_VAR_NOINIT) NvM_Lsb;
#if(STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM)
/* @Trace: NvM_SUD_MACRO_010 */
/* Array to hold high byte of NVRAM config to use compare mechanism */
VAR(uint8, NVM_VAR_NOINIT) NvM_MsbArray[NVM_COMPARE_NUM_NV_BLOCK];
/* Array to hold Mid high byte of NVRAM config to use compare mechanism */
VAR(uint8, NVM_VAR_NOINIT) NvM_MidHiArray[NVM_COMPARE_NUM_NV_BLOCK];
/* Array to hold Mid low byte of NVRAM config to use compare mechanism */
VAR(uint8, NVM_VAR_NOINIT) NvM_MidLowArray[NVM_COMPARE_NUM_NV_BLOCK];
/* Array to hold low byte of NVRAM config to use compare mechanism */
VAR(uint8, NVM_VAR_NOINIT) NvM_LsbArray[NVM_COMPARE_NUM_NV_BLOCK];
#endif
/* @Trace: NvM_SUD_MACRO_017 */
#elif(((STD_ON == NVM_CRC16_SUPPORT) && (STD_ON == NVM_CRC_SUPPORT)) || \
(STD_ON == NVM_STATIC_ID_CHECK))
VAR(uint8, NVM_VAR_NOINIT) NvM_Msb;
VAR(uint8, NVM_VAR_NOINIT) NvM_Lsb;
#if(STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM)
/* @Trace: NvM_SUD_MACRO_010 */
VAR(uint8, NVM_VAR_NOINIT) NvM_MsbArray[NVM_COMPARE_NUM_NV_BLOCK];
VAR(uint8, NVM_VAR_NOINIT) NvM_LsbArray[NVM_COMPARE_NUM_NV_BLOCK];
#endif
#else
#if(STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM)
/* @Trace: NvM_SUD_MACRO_010 */
VAR(uint8, NVM_VAR_NOINIT) NvM_LsbArray[NVM_COMPARE_NUM_NV_BLOCK];
#endif
#endif
#endif
/* @Trace: NvM_SUD_MACRO_005 NvM_SUD_MACRO_046 NvM_SUD_MACRO_047 NvM_SUD_MACRO_032 */
#if((STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM) || ((NVM_API_CONFIG_CLASS_3 == \
  NVM_API_CONFIG_CLASS) && (0 < NVM_TOTAL_NUM_OF_FIRSTINITALL_BLOCKS)) || \
  ((STD_ON == NVM_WRITE_VERIFICATION)))
/* Buffer to hold Mirror data, hold data for internal buffer for first init all */
VAR(uint8, NVM_VAR_NOINIT) NvM_MirrorBuffer[NVM_MIRROR_BUFFER
  #if(STD_ON == NVM_WRITE_VERIFICATION)
  + 2U
  #endif
  ];
#endif

/* Pointer to the RAM data block */
P2VAR(uint8, NVM_VAR_NOINIT, NVM_APPL_DATA) NvM_RamAddr;
/* Pointer to the Buffer use to read and write */
P2VAR(uint8, NVM_VAR_NOINIT, NVM_VAR_NOINIT) NvM_DataBuffer;
/* Hold the restore block state */
VAR(uint8, NVM_VAR_NOINIT) NvM_RestoreBlockstate;
#define NVM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define NVM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* @Trace: NvM_SUD_MACRO_017 */
#if((STD_ON == NVM_STATIC_ID_CHECK) || (STD_ON == NVM_CRC_SUPPORT))
/* @Trace: NvM_SUD_MACRO_016 */
/* Holds the CRC/Static ID data */
VAR(uint8, NVM_VAR_NOINIT) NvM_ReadCRCSID[NVM_CRC_SID_SIZE];
#endif

/* Indicates status of MEMIF Driver service command */
VAR(NvM_RequestResultType, NVM_VAR_NOINIT) NvM_JobResultLowLevel;
/* Indicates status of first Redundant block */
VAR(NvM_RequestResultType, NVM_VAR_NOINIT) NvM_JobResultFirstBlock;
/* @Trace: NvM_SUD_MACRO_047 */
#if (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)
/* Buffer to hold the standard priority request Block Id and Service Id */
VAR(NvM_JobQueue, NVM_VAR_NOINIT) 
  /* @Trace: NvM_SUD_MACRO_039 */
  NvM_StdQueueBuffer[NVM_SIZE_STANDARD_JOB_QUEUE];

/* Structure to hold the standard priority request Block Id and Service Id */
VAR(NvM_JobQueue, NVM_VAR_NOINIT) NvM_StdPrevReq;
#endif
/* @Trace: NvM_SUD_MACRO_047 */
#if((NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) && \
  (STD_ON == NVM_JOB_PRIORITIZATION) && (STD_ON == NVM_IMM_JOB_PRIORITY))
/* Buffer to hold the immediate priority request Block Id and Service Id */
VAR(NvM_JobQueue, NVM_VAR_NOINIT) 
  /* @Trace: NvM_SUD_MACRO_038 */
  NvM_ImmQueueBuffer[NVM_SIZE_IMMEDIATE_JOB_QUEUE];
#endif

/* Pointer to Global Descriptor Table */
P2CONST(NvM_BlkDescTbl, NVM_VAR_NOINIT, NVM_CONST) NvM_NvmBlkDescTbl;

/* Indicates the Global Block Id which is under progress */
VAR(NvM_BlockIdType, NVM_VAR_NOINIT) NvM_BlockIdx;

/* Holds the Block Management type */
VAR(NvM_BlockManagementType, NVM_VAR_NOINIT) NvM_BlkMngmntType;
#define NVM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define NVM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* Hold the status of MemIf_SetMode job */
#if(STD_ON == NVM_DRV_MODE_SWITCH)
VAR(boolean, NVM_VAR_NOINIT) NvM_SetModeStatus;
#endif

/* Hold the status of backup redundant block */
VAR(boolean, NVM_VAR_NOINIT) NvM_BackUp;
/* @Trace: NvM_SUD_MACRO_047 */
#if((NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) && \
  (STD_ON == NVM_JOB_PRIORITIZATION) && (STD_ON == NVM_IMM_JOB_PRIORITY))
/*
 * Flag to indicate immediate priority request (immediate Erase/Write) is in
 * progress
 */
VAR(boolean, NVM_VAR_NOINIT) NvM_HighPriorityRequest;

/* Flag holds the status of previous immediate request */
VAR(boolean, NVM_VAR_NOINIT) NvM_PrevReqImm;
#endif

/* Flag to indicate status of "Cancel Write All" request */
VAR(boolean, NVM_VAR_NOINIT) NvM_CancelWriteAllRequest;

/* Flag to indicate that stored and compiled Configuration Ids are matching */
#if(STD_ON == NVM_DYNAMIC_CONFIGURATION)
VAR(boolean, NVM_VAR_NOINIT) NvM_ConfigIdMatch;
#endif

/* Variable to indicate NVRAM Manager is initialized */
VAR(boolean, NVM_VAR_NOINIT) NvM_InitStatus;

#define NVM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define NVM_START_SEC_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED
#include "MemMap.h"

/* @Trace: NvM_SUD_MACRO_016 */
/* Buffer to hold Mirror data, 6 : management bytes for EA , 2 : reserved */
VAR(uint8, NVM_VAR_NOINIT)
  NvM_DataBufferSource[NVM_MIRROR_BUFFER+NVM_CRC_SID_SIZE + 8U];

#define NVM_STOP_SEC_VAR_CLEARED_ALIGNED_ADDR_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-end VARIABLE:* */

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
