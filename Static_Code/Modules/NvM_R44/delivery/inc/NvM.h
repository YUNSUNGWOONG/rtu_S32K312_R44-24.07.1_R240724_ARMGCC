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
**  SRC-MODULE: NvM.h                                                         **
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
** 0.0.1       06-Dec-2019    VinhLV5     Initial version                     **
** 0.0.2       04-May-2020    VinhLV5     Update traceability, apply          **
**                                        new v cycle, Fix Misra              **
** 0.0.3       24-Jul-2020    VinhLV5     R44-Redmine #9958                   **
** 1.0.2       27-Aug-2021    JH Lim      R44-Redmine #19726                  **
** 1.1.0       08-Dec-2021    JH Lim      R44-Redmine #19388                  **
** 1.1.1       09-May-2022    SH Park     R44-Redmine #27456                  **
** 1.1.1.1     29-Jun-2022    SH Park     Improvement mobilegence             **
**                                          Classic <CP44-221>                **
** 1.1.2       12-Aug-2022    SH Park     Improvement mobilegence             **
**                                          Classic <CP44-76>                 **
*******************************************************************************/

#ifndef NVM_H
#define NVM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "NvM_Cfg.h"
#include "NvM_IntTypes.h"
#include "NvM_MemIf.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/* Service Id Of All Application APIS */
/* @Trace: NvM_SUD_MACRO_001 */
/* Service ID for NvM_SetDataIndex */
#define  NVM_SETDATAINDEX_SID                 ((uint8)0x01)

/* Service ID for NvM_GetDataIndex */
#define  NVM_GETDATAINDEX_SID                 ((uint8)0x02)

/* Service ID for NvM_SetBlockProtection */
#define  NVM_SETBLOCKPROTECTION_SID           ((uint8)0x03)

/* Service ID for NvM_GetErrorStatus */
#define  NVM_GETERRORSTATUS_SID               ((uint8)0x04)

/* Service ID for NvM_SetRamBlockStatus */
#define  NVM_SETRAMBLOCKSTATUS_SID            ((uint8)0x05)

/* Service ID for NvM_ReadBlock */
#define  NVM_READBLOCK_SID                    ((uint8)0x06)

/* Service ID for NvM_ReadPRAMBlock */
#define  NVM_READPRAMBLOCK_SID                ((uint8)0x16)

/* Service ID for NvM_WritePRAMBlock */
#define NVM_WRITEPRAMBLOCK_SID                ((uint8)0x17)

/* Service ID for NvM_WriteBlock */
#define  NVM_WRITEBLOCK_SID                   ((uint8)0x07)

/* Service ID for NvM_RestoreBlockDefaults */
#define  NVM_RESTOREBLOCKDEFAULTS_SID         ((uint8)0x08)

/* Service ID for NvM_RestorePRAMBlockDefaults */
#define NVM_RESTOREPRAMBLOCKDEFAULTS_SID      ((uint8)0x18)

/* Service ID for NvM_EraseNvBlock */
#define  NVM_ERASENVBLOCK_SID                 ((uint8)0x09)

/* Service ID for NvM_CancelWriteAll */
#define  NVM_CANCELWRITEALL_SID               ((uint8)0x0a)

/* Service ID for NvM_InvalidateNvBlock */
#define  NVM_INVALIDATENVBLOCK_SID            ((uint8)0x0b)

/* Service ID for NvM_ReadAll */
#define  NVM_READALL_SID                      ((uint8)0x0c)

/* Service ID for NvM_WriteAll */
#define  NVM_WRITEALL_SID                     ((uint8)0x0d)

/* Service ID for NvM_FirstInitAll */
#define  NVM_FIRSTINITALL_SID                 ((uint8)0x14)

/* Service ID for NvM_GetVersionInfo */
#define  NVM_GETVERSIONINFO_SID               ((uint8)0x0f)

/* Service ID for NvM_SetBlockLockStatus */
#define NVM_SETBLOCKLOCKSTATUS_SID            ((uint8)0x13)

/* Service ID for NvM_CancelJobs */
#define NVM_CANCELJOBS_SID                    ((uint8)0x10)

/* Service ID for NvM_ValidateAll */
#define NVM_VALIDATEALL_SID                   ((uint8)0x19)

/* Service ID for NvM_MainFunction */
#define NVM_MAINFUNCTION_SID                  ((uint8)0x0e)

/* NvM Instance Id */
#define  NVM_INSTANCE_ID                      ((uint8)0x00)

/* Det Error Codes */
/* @Trace: NvM_SUD_MACRO_002 SRS_BSW_00385 SRS_BSW_00327 SRS_BSW_00331 */
/* user-define development errors */
#define NVM_E_NO_ERROR                ((uint8)0x00)

/* DET Code to report request Invalid BlockID */
#define NVM_E_PARAM_BLOCK_ID          ((uint8)0x0a)

/* DET Code to report request of wrong parameter for Block Management type */
#define NVM_E_PARAM_BLOCK_TYPE        ((uint8)0x0b)

/* DET Code to report overflow of DataIndex parameter of configured datasets */
#define NVM_E_PARAM_BLOCK_DATA_IDX    ((uint8)0x0c)

/*
* DET Code to report absence of Permanent RAM block when NULL pointer is
* passed as parameter
*/
#define NVM_E_PARAM_ADDRESS           ((uint8)0x0d)

/* DET Code to report passing of NULL pointer as parameter in synchronous API */
#define NVM_E_PARAM_DATA              ((uint8)0x0e)

/* DET Code to report passing of NULL_PTR as parameter of versioninfo */
#define NVM_E_PARAM_POINTER           ((uint8)0x0f)

/* DET Code to report when either the NvM_RestoreBlockDeafults or 
* NvM_RestorePRAMBlockDefaults is called for a valid block ID that 
* has no default data and no NvMInitBlockCallback configured for the
* block. 
*/
#define NVM_E_BLOCK_WITHOUT_DEFAULTS  ((uint8)0x11)

/* DET Code to report Uninitialized state */
#define NVM_E_UNINIT                  ((uint8)0x14)

/* DET Code to report NVRAM block identifier is already in requested service */
#define NVM_E_BLOCK_PENDING           ((uint8)0x15)

/* DET Code to report the service is not possible with current configuration */
#define NVM_E_BLOCK_CONFIG            ((uint8)0x18)

/* DET Code to report if block is locked */
#define NVM_E_BLOCK_LOCKED            ((uint8)0x19)

/* DET Code to report if a write request is made for a block configured with 
NVM_WRITE_BLOCK_ONCE (TRUE) for which no read request was made prior */
#define NVM_E_WRITE_ONCE_STATUS_UNKNOWN     ((uint8)0x1A)

/* DET Code to report runtime errors if queue is full */
#define NVM_E_QUEUE_FULL              ((uint8)0xA0)

#define NVM_LOWPOWER_PREVENT          ((uint8)0x00)

#define NVM_LOWPOWER_ALLOW            ((uint8)0x01)

/* backward compatibility for Dem */
#define NVM_GPT_CHANNEL_ID
/*******************************************************************************
**                       Function Prototypes                                  **
*******************************************************************************/
/* polyspace-begin MISRA-C3:8.5 [Justified:Low] "These NvM functions can be invoked by AWS layer, therefore Rte code also declares them." */
#define NVM_START_SEC_CODE
#include "MemMap.h"
/* NvM_Init API Prototype Declarations */
extern FUNC(void, NVM_CODE)NvM_Init(
  P2CONST(NvM_ConfigType, AUTOMATIC, NVM_APPL_CONST) ConfigPtr);

/* NvM_CancelWriteAll API Prototype Declarations */
extern FUNC(void, NVM_CODE) NvM_CancelWriteAll(void);

/* NvM_ReadAll API Prototype Declarations */
extern FUNC(void, NVM_CODE) NvM_ReadAll(void);

/* NvM_WriteAll API Prototype Declarations */
extern FUNC(void, NVM_CODE) NvM_WriteAll(void);

/* NvM_SetBlockLockStatus API Prototype Declarations */
extern FUNC(void, NVM_CODE) NvM_SetBlockLockStatus(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId, VAR(boolean, AUTOMATIC) BlockLocked);

/* NvM_GetErrorStatus API Prototype Declarations */
extern FUNC(Std_ReturnType, NVM_CODE) NvM_GetErrorStatus(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId, 
  P2VAR(NvM_RequestResultType, AUTOMATIC, NVM_APPL_DATA) RequestResultPtr);

#if(STD_ON == NVM_SET_RAM_BLOCK_STATUS_API)
/* NvM_SetRamBlockStatus API Prototype Declarations */
extern FUNC(Std_ReturnType, NVM_CODE) NvM_SetRamBlockStatus(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId, 
  VAR(boolean, AUTOMATIC) BlockChanged);
#endif

#if(STD_ON == NVM_VERSION_INFO_API)
/* NvM_GetVersionInfo API Prototype Declarations */
extern FUNC(void, NVM_CODE) NvM_GetVersionInfo(
  P2VAR(Std_VersionInfoType, AUTOMATIC, NVM_APPL_DATA) versioninfo);
#endif /* (STD_ON == NVM_VERSION_INFO_API) */

#if(NVM_API_CONFIG_CLASS_3 == NVM_API_CONFIG_CLASS)

/* NvM_SetBlockProtection API Prototype Declarations */
extern FUNC(Std_ReturnType, NVM_CODE) NvM_SetBlockProtection(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId, 
  VAR(boolean, AUTOMATIC) ProtectionEnabled);

/* NvM_EraseNvBlock API Prototype Declarations */
extern FUNC(Std_ReturnType, NVM_CODE) NvM_EraseNvBlock(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId);

/* NvM_InvalidateNvBlock API Prototype Declarations */
extern FUNC(Std_ReturnType, NVM_CODE) NvM_InvalidateNvBlock(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId);

/* NvM_FirstInitAll API Prototype Declarations */
extern FUNC(void, NVM_CODE) NvM_FirstInitAll(void);
#endif

#if(NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS)

#if(STD_ON == NVM_DATASET_PRESENT)
/* NvM_SetDataIndex API Prototype Declarations */
extern FUNC(Std_ReturnType, NVM_CODE) NvM_SetDataIndex(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId, 
  VAR(uint8, AUTOMATIC) DataIndex);

/* NvM_GetDataIndex API Prototype Declarations */
extern FUNC(Std_ReturnType, NVM_CODE) NvM_GetDataIndex(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId, 
  P2VAR(uint8, AUTOMATIC, NVM_APPL_DATA) DataIndexPtr);
#endif

/* NvM_ReadBlock API Prototype Declarations */
extern FUNC(Std_ReturnType, NVM_CODE) NvM_ReadBlock(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId, 
  P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DstPtr);

/* NvM_ReadPRAMBlock API Prototype Declarations */
extern FUNC(Std_ReturnType, NVM_CODE) NvM_ReadPRAMBlock(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId);

/* NvM_WriteBlock API Prototype Declarations */
extern FUNC(Std_ReturnType, NVM_CODE) NvM_WriteBlock(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId, 
  P2CONST(void, AUTOMATIC, NVM_APPL_DATA) NvM_SrcPtr);

/* NvM_RestoreBlockDefaults API Prototype Declarations */
extern FUNC(Std_ReturnType, NVM_CODE) NvM_RestoreBlockDefaults(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId, 
  P2VAR(void, AUTOMATIC, NVM_APPL_DATA) NvM_DestPtr);

/* NvM_RestorePRAMBlockDefaults API Prototype Declarations */
extern FUNC(Std_ReturnType, NVM_CODE) NvM_RestorePRAMBlockDefaults(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId);

extern FUNC(Std_ReturnType, NVM_CODE) NvM_CancelJobs(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId);

/* NvM_WritePRAMBlock API Prototype Declarations */
extern FUNC(Std_ReturnType, NVM_CODE)NvM_WritePRAMBlock(
  VAR(NvM_BlockIdType, AUTOMATIC) BlockId);

/* NvM_ValidateAll API Prototype Declarations */
extern FUNC(void, NVM_CODE)NvM_ValidateAll(void);

#endif /* (NVM_API_CONFIG_CLASS_1 != NVM_API_CONFIG_CLASS) */

extern FUNC(NvM_OpStatusType, NVM_CODE) NvM_CddGetStatus(void);

#define NVM_STOP_SEC_CODE
#include "MemMap.h"
/* polyspace-end MISRA-C3:8.5 [Justified:Low] "These NvM functions can be invoked by AWS layer, therefore Rte code also declares them." */
#endif /* NVM_H */
