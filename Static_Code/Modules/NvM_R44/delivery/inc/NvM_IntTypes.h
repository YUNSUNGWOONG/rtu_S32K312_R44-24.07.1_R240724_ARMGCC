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
**  SRC-MODULE: NvM_PCTypes.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR NvM Module                                            **
**                                                                            **
**  PURPOSE   : Provision of AUTOSAR NVRAM Manager Type Definitions and       **
**              Block Descriptor structure.                                   **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date          By             Description                       **
********************************************************************************
** 0.0.1       06-Dec-2019    VinhLV5     Initial version                     **
** 0.0.2       04-May-2020    VinhLV5     Update traceability, apply          **
**                                        new v cycle, Fix Misra              **
** 0.0.3       24-Jul-2020    VinhLV5     R44-Redmine #9958                   **
** 1.0.2       27-Aug-2021    JH Lim      R44-Redmine #19726                  **
** 1.1.0       08-Dec-2021    JH Lim      R44-Redmine #19388                  **
** 1.1.1.1     29-Jun-2022    SH Park     Improvement mobilegence             **
**                                          Classic <CP44-221>                **
** 1.1.2       12-Aug-2022    SH Park     Improvement mobilegence             **
**                                          Classic <CP44-76>                 **
*******************************************************************************/

#ifndef NVM_INTTYPES_H
#define NVM_INTTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/*******************************************************************************
**                        Global Data                                         **
*******************************************************************************/

/* Bit Order for Block Descriptor Parameters  (ucBlkParams) */

#define NVM_TRUE                          TRUE
#define NVM_FALSE                         FALSE

/* Macros used used for accessing a particular block */
#define NVM_ZERO                          ((uint16)0)
#define NVM_ONE                           ((uint16)1)
#define NVM_TWO                           ((uint16)2)
#define NVM_THREE                         ((uint16)3)
#define NVM_FOUR                          ((uint16)4)
#define NVM_SIX                           ((uint16)6)
#define NVM_EIGHT                         ((uint16)8)
#define NVM_SIXTEEN                       ((uint16)16)
#define NVM_TWENTYFOUR                    ((uint16)24)
#define NVM_FF                            (0xFF)

#define NVM_IMM_PRIORITY                  ((uint8)0)

/* Macros used for CRC offset values */
#define NVM_1BYECRC_STARTVALUE            ((uint8)0xFF)
#define NVM_2BYECRC_STARTVALUE            ((uint16)0xFFFF)
#define NVM_4BYECRC_STARTVALUE            ((uint32)0xFFFFFFFFU)

/* MACROS USED FOR PROCESSING BYTES/BLOCKS IN MULTIPLE CYCLES */

/* MASKS USED TO READ/SET THE SPECIFIC BITS IN NvM_RamStatus */

/* To get the error bits in the error field of RAM */
#define NVM_ERROR_BIT_MASK                ((uint16)0x000F)

/* To update the error bits in the error field of RAM */
#define NVM_NOT_ERROR_BIT_MASK            ((uint16)0xFFF0)

/* Mask to set the Write protection bit */
#define NVM_WRITE_PROTECT_MASK            ((uint16)0x0080)

/* Mask to clear the Write protection bit */
#define NVM_NOT_WRITE_PROTECT_MASK        ((uint16)0xFF7F)

/* Mask to Set the Lock protection bit */
#define NVM_LOCK_RAM_MASK                 ((uint16)0x0040)

/* Mask to clear the Lock protection bit */
#define NVM_UNLOCK_RAM_MASK               ((uint16)0xFFBF)

/* Mask to set RamCrcRequested bit */
#define NVM_CRC_REQUESTED_MASK            ((uint16)0x0100)

/* Mask to Set the check redundant which block is first write bit */
#define NVM_FIR_REDUNDANT_MASK            ((uint16)0x0200)

/* Mask to Set the check redundant which block is first write bit */
#define NVM_SEC_REDUNDANT_MASK            ((uint16)0xFDFF)

/* Mask to Set the need to check redundant bit */
#define NVM_CHECK_NEED_REDUNDANT_MASK     ((uint16)0x0400)

/* Mask to clear the need to check redundant bit */
#define NVM_CHECK_DONE_REDUNDANT_MASK     ((uint16)0xFBFF)

/* Mask to Set Read prior */
#define NVM_CHECK_READ_PRIOR              ((uint16)0x0800)

/* Mask to Set loss of redundancy */
#define NVM_CHECK_LOSS_OF_REDUNDANCY      ((uint16)0x1000)

/* Mask to clear loss of redundancy */
#define NVM_CLEAR_LOSS_OF_REDUNDANCY      ((uint16)0xEFFF)

/* MACROS TO READ CONFIGURATION INFORMATION FROM usBlkParams*/

/* Bit 0 - Generation of CRC */
#define NVM_CALC_RAM_BLK_CRC                  ((uint16)0x0001)
/* Bit 1 - Default Write Protection */
#define NVM_BLOCK_WRITE_PROT                  ((uint16)0x0002)
/* Bit 2 - Block is of one time Write */
#define NVM_WRITE_BLOCK_ONCE                  ((uint16)0x0004)
/* Bit 3 - Resistant to changed software */
#define NVM_RESISTANT_TO_CHANGED_SW           ((uint16)0x0008)
/* Bit 4 - Enables/Disables processing block during readall */
#define NVM_SELECT_BLOCK_FOR_READALL          ((uint16)0x0010)
/* Bit 6 - Enables/Disables explicit synchronization mechanism*/
#define NVM_BLOCK_USE_SYNC_MECHANISM_ENABLE   ((uint16)0x0040)
/* Bit 8 - Enables/Disables Write Verification */
#define NVM_WRITE_VERIFICATION_ENABLE         ((uint16)0x0100)
/* Bit 9 - Enables/Disables Static ID check */
#define NVM_STATIC_BLOCK_ID_CHECK             ((uint16)0x0200)
/* Bit 10 - If it is set, it intimates to BswM about the current status */
#define NVM_BSWM_BLOCK_STATUS_INFORMATION     ((uint16)0x0400)
/* Bit 11 - If it is set, it intimates to Calculate CRC on ROM data */
#define NVM_DEFAULT_ROM_CRC_ENABLED           ((uint16)0x0800)
/* 
 * Bit 12 - If it is set, it intimates to use NvMSetRamBlockStatusApi 
 * on this block or not 
 */
#define NVM_BLOCK_USE_SETRAMBLOCKSTATUS       ((uint16)0x1000)
/* Bit 13 - If it is set, compare crc in Nvram block is used */
#define NVM_BLOCK_USE_CRC_COMP_MASK           ((uint16)0x2000)
/* Macro to check CRC configured */
#define NVM_CALC_CRC_BLOCK_CHECK              ((uint16)0x0021)

/* MACROS RELATED TO CRC CALCULATION */

/* Defines macros for CRC length */
#define NVM_CRC_4BYTE                     ((uint8)0x04)
#define NVM_CRC_2BYTE                     ((uint8)0x02)
#define NVM_CRC_1BYTE                     ((uint8)0x01)

/* MACROS RELATED TO RAM INTERNAL STATES */

/* Macro to define RAM status */
#define NVM_INVALID_UNCHANGED             ((uint8)0x0000)
#define NVM_VALID_UNCHANGED               ((uint8)0x0020)
#define NVM_VALID_CHANGED                 ((uint8)0x0030)

/* MACROS RELATED TO MASK RAM INTERNAL STATES */
#define NVM_CLEAR_RAM_INTERNAL_STATE      ((uint16)0xFFCF)
#define NVM_RAM_STATUS_MASK               ((uint16)0x0030)

/* Macro to indicate the status of Redundant block */
typedef enum
{
  NVM_RE_CHK_NONE = 0U,
  NVM_RE_CHKED_ORIGIN,
  NVM_RE_CHKED_COPY,
} NvM_StatusReBlock;

/* Macro to indicate the first write of Redundant block */
typedef enum
{
  NVM_RE_ORIGINAL_FIRST = 0U,
  NVM_RE_COPY_FIRST,
} NvM_RefirstBlock;

/* Macro to indicate the status of ReadAll/WriteAll processing */
#define NVM_MULTIBLK_UNREQUESTED          ((uint8)0x00)
#define NVM_MULTIBLK_REQUESTED            ((uint8)0x01)
#define NVM_MULTIBLK_IN_PROGRESS          ((uint8)0x02)

/* MACROS TO DEFINE VARIOUS FUNCTIONAL STATES */
/* Common state values used in all API processing functions */
#define NVM_IDLE                          ((uint8)0x00)
#define NVM_SUB_IDLE                      ((uint8)0x00)

/* Sub states of WriteBlock function */
#define   NVM_WRITE_NVBLOCK               ((uint8)0x01)
#define   NVM_WRITE_PROCESS_NV_BLOCK      ((uint8)0x02)
#define   NVM_IMMD_WRITE_PENDING          ((uint8)0x03)
#define   NVM_PROCESS_WRITE_VERIFY        ((uint8)0x04)
#define   NVM_IMMD_WRITE_PRAM_PENDING     ((uint8)0x05)
#define   NVM_PROCESS_WRITE_ACCEPT        ((uint8)0x06)
#define   NVM_WRITE_IMM_JOB               ((uint8)0x07)
#define   NVM_WRITE_START_IMM             ((uint8)0x08)

/* Sub states of WriteAll function */
#define   NVM_WRITE_ALL_IDLE              ((uint8)0x00)
#define   NVM_WRITE_ALL_BLOCK             ((uint8)0x01)
#define   NVM_WRITE_ALL_PROCESS           ((uint8)0x02)
#define   NVM_WRITE_ALL_INIT              ((uint8)0x03)

/* Sub states of Erase/Invalidate function */
#define NVM_ERASEINVALIDATE_START         ((uint8)0x01)
#define NVM_ERASEINVALIDATE_PROCESSING    ((uint8)0x02)

/* State of restore block function*/
#define NVM_RESTORE_START                 ((uint8)0x01)
#define NVM_RESTORE_REPEAT                ((uint8)0x02)
#define NVM_RESTORE_END                   ((uint8)0x03)

/* Sub states of ProcessReadblock function */
#define NVM_READ_START                    ((uint8)0x01)
#define NVM_READ_NVBLOCK                  ((uint8)0x02)
#define NVM_READ_ROM                      ((uint8)0x03)
#define NVM_READ_REPEAT                   ((uint8)0x04)

/* Sub states of ProcessReadAllBlocks function */
#define NVM_READALL_INIT                  ((uint8)0x01)
#define NVM_READALL_PROCESS               ((uint8)0x02)
#define NVM_READALL_BLKPROCESS            ((uint8)0x03)
#define NVM_READALL_ROMBLK_PROCESS        ((uint8)0x04)

/* Sub states of ProcessValidateAllBlocks function */
#define NVM_VALIDATEALL_IDLE              ((uint8)0x00)
#define NVM_VALIDATEALL_INIT              ((uint8)0x01)
#define NVM_VALIDATEALL_PROCESS           ((uint8)0x02)

/* Sub states of ProcessFirstInitAllblocks function */
#define NVM_FIRSTINITALL_INIT             ((uint8)0x01)
#define NVM_FIRSTINITALL_PROCESS          ((uint8)0x02)
#define NVM_FIRSTINITALL_ROMBLK_PROCESS   ((uint8)0x03)
#define NVM_FIRSTINITALL_INVALI_PROCESS   ((uint8)0x04)
#define NVM_FIRSTINITALL_WRITEBLK_PROCESS ((uint8)0x05)

/* Macro for use of immediate job */
#if((STD_ON == NVM_JOB_PRIORITIZATION) && (NVM_API_CONFIG_CLASS != \
      NVM_API_CONFIG_CLASS_1) && (STD_ON == NVM_IMM_JOB_PRIORITY))
#define NVM_JOB_PRIO                      (STD_ON)
#else
#define NVM_JOB_PRIO                      (STD_OFF)
#endif

/* polyspace-begin MISRA2012:D4.9 [Not a defect:Low] "Macro used for small pieces of code to improve performance, reduce stack use" */
/* Macro for unused variable */
#define NVM_UNUSED(arg)                   (void)(arg)

/* Macro for Set bit read prior */
#define SET_READ_PRIOR() {\
  if((NvM_NvmBlkDescTbl->usBlkParams & NVM_WRITE_BLOCK_ONCE) == \
    NVM_WRITE_BLOCK_ONCE)\
  {\
    SchM_Enter_NvM_RAM_STATUS_PROTECTION();\
    NvM_RamStatus[NvM_BlockIdx] |= NVM_CHECK_READ_PRIOR;\
    SchM_Exit_NvM_RAM_STATUS_PROTECTION();\
  }\
\
}

#define NVM_SET_JOB_RESULT(BlockId, NewReqResult)  \
do\
{\
  SchM_Enter_NvM_RAM_STATUS_PROTECTION();\
  NvM_RamStatus[(BlockId)] = (NvM_RamStatus[(BlockId)] & \
    NVM_NOT_ERROR_BIT_MASK) | (uint16)NewReqResult;\
  SchM_Exit_NvM_RAM_STATUS_PROTECTION();\
} while(0)

#define NVM_GET_JOB_RESULT(BlockId) ((NvM_RequestResultType)(\
  NVM_ERROR_BIT_MASK & NvM_RamStatus[(BlockId)]))
/* polyspace-end MISRA2012:D4.9 */

/* Macro for Set ram block status */
#if((STD_ON == NVM_SET_RAM_BLOCK_STATUS_API) && \
   ((STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS) || \
    (STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)))
#define UPDATE_RAM_STATUS_ENABLE          (STD_ON)
#else
#define UPDATE_RAM_STATUS_ENABLE          (STD_OFF)
#endif

/* Macro for block Id 0 */
#define NVM_RESERVED_BLOCK_ID             ((NvM_BlockIdType)0)

/* Macro for RTRT and static funtion */
/* polyspace-begin MISRA2012:D4.9 [Not a defect:Low] "Macro used for RTRT test and better view of code" */
#ifdef RTRT_TEST
#define NVM_STATIC
#define NVM_EXTERN(func)                  extern func
#define NVM_CFG_EXTERN(type)              extern VAR(type, NVM_VAR_NOINIT)
#else
#define NVM_STATIC                        static
#define NVM_EXTERN(func)
#define NVM_CFG_EXTERN(type)              extern CONST(type, NVM_CONST)
#endif
/* polyspace-end MISRA2012:D4.9 */

/* Type for init block callback */
typedef P2FUNC(Std_ReturnType, NVM_APPL_CODE, NvM_InitNotificationFnType)
  (NvM_InitBlockRequestType InitBlockRequest);

/* Type for single block callback */
typedef P2FUNC(Std_ReturnType, NVM_APPL_CODE, NvM_NotificationFnType)
  (NvM_BlockRequestType BlockRequest, NvM_RequestResultType JobResult);

/* Type for ReadRamBlockFromNvm callback */
typedef P2FUNC(Std_ReturnType, NVM_APPL_CODE, NvMReadMirrorNotification)
  (const void* NvMBuffer);

/* Type for WriteRamBlockToNvm callback */
typedef P2FUNC(Std_ReturnType, NVM_APPL_CODE, NvMWriteMirrorNotification)
  (void* NvMBuffer);

/* Typedef of block management type */
typedef enum
{
  NVM_BLOCK_NATIVE = 0U,
  NVM_BLOCK_REDUNDANT,
  NVM_BLOCK_DATASET
} NvM_BlockManagementType;

typedef enum
{
  NVM_OPSTATUS_UNINIT = 0,
  NVM_OPSTATUS_IDLE,
  NVM_OPSTATUS_BUSY
} NvM_OpStatusType;

/* Structure for Block Descriptor Table */
typedef struct
{
  /* Pointer to permanent RAM block data array */
  /* If NVM_RAM_BLOCK_DATA_ADDRESS is STD_ON and Ram Block address is not
   * configured for a particular block then generate NULL_PTR
   */
  #if(STD_ON == NVM_RAM_BLOCK_DATA_ADDRESS)
  P2VAR(void, AUTOMATIC, NVM_APPL_DATA)pRamBlkData;
  #endif

  /* Pointer to ROM Block Data */
  P2CONST(void, AUTOMATIC, NVM_APPL_CONST)pRomBlkData;

  /* Pointer to   Init Block callback */
  /* If NVM_INIT_CALLBACK is STD_ON and Notification is not configured then
   * generate NULL_PTR
   */
  #if (STD_ON == NVM_INIT_CALLBACK)
  NvM_InitNotificationFnType pNvMInitNotification_BlockId;
  #endif

  /* Pointer to Single Block callback  */
  /* If NVM_SINGLE_BLOCK_CALLBACK is STD_ON and Notification is not configured
   * then generate NULL_PTR
   */
  #if(STD_ON == NVM_SINGLE_BLOCK_CALLBACK)
  NvM_NotificationFnType pNvMNotification_BlockId;
  #endif

  /* Pointer to ReadRamBlockFromNvm callback */
  /* If NVM_BLOCK_USE_SYNC_MECHANISM is STD_ON and callback is not configured
   * then generate NULL_PTR
   */
  #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
  NvMReadMirrorNotification pNvMReadRamBlockFromNvm;
  #endif

  /* Pointer to WriteRamBlockToNv callback */
  #if(STD_ON == NVM_BLOCK_USE_SYNC_MECHANISM)
  NvMWriteMirrorNotification pNvMWriteRamBlockToNvm;
  #endif

  /* NVRAM Block Identifier */
  NvM_BlockIdType ddBlockId;

  NvM_BlockManagementType enBlkMngmntType;

  /* BlockBase Number */
  uint16 usNvBlkBaseNumber;

  /* Block Data Length */
  uint16 usNvBlkDataLength;

  /* Write Verification Data Size */
  /* If NVM_WRITE_VERIFICATION is STD_OFF & NvMWriteVerificationDataSize is
   * configured then the configured value should not be considered
   */
  #if(STD_ON == NVM_WRITE_VERIFICATION)
  uint16 usWriteVerificationDataSize;
  #endif

  /* Bit 0 - This bit is set if NvMBlockUseCrc parameter in NvMBlockDescriptor
   *         container is configured as true
   * Bit 1 - This bit is set if NvMBlockWriteProt parameter in
   *         NvMBlockDescriptor container is configured as true
   * Bit 2 - This bit is set if NvMWriteBlockOnce parameter in
   *         NvMBlockDescriptor container is configured as true
   * Bit 3 - This bit is set if NvMResistantToChangedSw parameter in
   *         NvMBlockDescriptor container is configured as true
   * Bit 4 - This bit is set if NvMSelectBlockForReadAll parameter in
   *         NvMBlockDescriptor container is configured as true
   * Bit 5 - This bit is set if NvMCalcRamBlockCrc parameter in
   *         NvMBlockDescriptor container is configured as true
   * Bit 6 - This bit is set if NvMBlockUseSyncMechanism parameter in
   *         NvMBlockDescriptor container is configured as true
   * Bit 7 - This bit is set if NvMSelectBlockForWriteAll parameter in
   *         NvMBlockDescriptor container is configured as true
   * Bit 8 - This bit is set if NvMWriteVerification parameter in
   *         NvMBlockDescriptor container is configured as true
   * Bit 9 - This bit is set if NvMStaticBlockIDCheck parameter in
   *         NvMBlockDescriptor container is configured as true
   * Bit 10 - This bit is set if NvMBswMBlockStatusInformation parameter in
   *         NvMBlockDescriptor container is configured as true
   * Bit 11 - This bit is set if NvMDefaultROMCRCEnabled parameter in
   *          NvMBlockDescriptor container is configured as true
   * Bit 12 - This bit is set if NvMBlockUseSetRamBlockStatus parameter in
   *          NvMBlockDescriptor container is configured as true
   * Bit 13 - If it is set, compare crc in Nvram block is used
   */
  uint16 usBlkParams;

  /* NVRAM device ID value */
  uint8 ucNvramDeviceId;

  /* = 0 if not configured, = 1 for 8 bit CRC, = 2 for 16 bit and =4 for
   * 32 bit
   */
  #if(STD_ON == NVM_CRC_SUPPORT)
  uint8 ucCrcLength;
  #endif

  /* Number of NV blocks */
  uint8 ucNumOfNvBlks;

  /* Number of ROM blocks */
  uint8 ucNumOfRomBlks;

  /* Max Number of Read Retries */
  uint8 ucMaxNumOfReadRetries;

  /* Max Number of Write Retries */
  uint8 ucMaxNumOfWriteRetries;

  /* Block Priority:0-Immediate other than 0-Standard   */
  #if((NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) && \
      (STD_ON == NVM_JOB_PRIORITIZATION))
  uint8 ucBlkJobPriority;
  #endif
}NvM_BlkDescTbl;
/* End of typedef struct */

/* Structure of Job queue */
typedef struct {
  uint8* pTempRamBlkData;
  uint8 ucService_Id;
  #if((NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) && \
      (STD_ON == NVM_JOB_PRIORITIZATION))
  uint8 ucPriority;
  #endif
  uint16 ucNextIndex;
  uint16 ddBlock_Idx;
  uint16 ucPreviousIndex;
}NvM_JobQueue;

/* Define struct for direct manipulation of 16 bit data */
typedef struct
{
  uint16 usWordReg16;
}NvM_Word16;

/* Define struct for direct manipulation of 32 bit register */
typedef struct
{
  uint32 ulLongReg32;
}NvM_DWord32;

/*
 * This array defines the structure for each NVRAM block configured
 * in input XML file
 */
#define NVM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array to hold information of all NVRAM blocks */
/* @Trace: NvM_SUD_GLOBALDATA_025 */
NVM_CFG_EXTERN(NvM_BlkDescTbl) NvM_BlkDescTbls[
  NVM_TOTAL_NUM_OF_NVRAM_BLOCKS];
/* Array to hold NVRAM blocks which use compare mechanism */
#if (STD_ON == NVM_BLOCK_USE_CRC_COMP_MECHANISM)
NVM_CFG_EXTERN(NvM_BlockIdType) NvM_CompareBlocks[
  NVM_COMPARE_NUM_NVRAM_BLOCK];
#endif
#define NVM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#endif /* NVM_INTTYPES_H */

/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
