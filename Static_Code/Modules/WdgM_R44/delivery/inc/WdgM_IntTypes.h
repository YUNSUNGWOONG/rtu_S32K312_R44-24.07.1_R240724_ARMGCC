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
**  SRC-MODULE: WdgM_IntTypes.h                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR WDGM                                                  **
**                                                                            **
**  PURPOSE   : WdgM type definition                                          **
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
** 0.0.1     16-Sep-2019   ThanhNT      Initial version                       **
** 0.0.2     23-Sep-2019   ThanhNT      Added new element to WdgM_ConfigType  **
** 0.0.3     15-Oct-2019   ThanhNT      Update module version information     **
** 0.0.4     24-Oct-2019   ThanhNT      Update coding convention              **
** 0.0.5     24-Oct-2019   ThanhNT      Update version checking mechanism     **
** 0.0.7     21-Nov-2019   ThanhNT      Update SUD and SRS Ids                **
** 0.0.8     27-Nov-2019   ThanhNT      Fix misra warning                     **
** 0.0.9     11-Mar-2020   TienVD       Update traceability                   **
** 0.0.16    26-Mar-2020   ThanhNT      Fix misra defect                      **
** 0.0.17    10-Aug-2020   ThanhNH5     Removed EcuCPar ref (#15195)          **
** 0.0.18    10-Sept-2020  ThanhNH5     Changed type to uint32 for            **
**                                      WdgM_ExAliveIndicationsCountType      **
**                                      (#15676)                              **
** 0.0.19    10-Sept-2020  ThanhNH5     Added type WdgM_CoreIdType (#15739)   **
** 0.0.20    11-Sept-2020  ThanhNH5     Fixed DEM configuration issue(#15741) **
** 0.0.21    12-Sep-2020   ThanhNH5     Added Os APIs checking (#15690)       **
** 0.0.22    14-Sep-2020   ThanhNH5     Removed Workaround comments (#15690)  **
** 0.0.23    16-Sep-2020   ThanhNH5     Added DeInit time out for each core   **
**                                      (#15843)                              **
** 0.0.24    17-Sep-2020   ThanhNH5     Removed RunTime error report(#15690)  **
** 0.0.25    05-Oct-2020   ThanhNH5     Merge variables in single and         **
**                                      multi core (#15485)                   **
** 0.0.30    16-Oct-2020   ThanhNT      Update MemMap ASIL_D (#16306)         **
** 1.2.0     01-Dec-2021   HiepVT1      Added WdgM_TrustedType, update        **
**                                      WdgM_SupervisedEntityType             **
** 1.3.0.1   30-Jun-2022   TriBD        #CP44-322                             **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:20.1 [Not a defect:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-begin MISRA-C3:D4.8 [Not a defect:Low] "see SWS_COMPILER_00013 of AUTOSAR" */
/* polyspace:begin<CERT-C:PRE00-C:Not a defect:Justify with annotations> Macro is used to improve the readability of code */

#ifndef WDGM_INT_TYPES_H
#define WDGM_INT_TYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "WdgM_Cfg.h"                   /* WdgM Pre-compile header file */
#include "WdgIf.h"                      /* WdgIf header file */
#include "Os.h"                         /* Os header file */
#if(WDGM_DEM_ERROR_REPORT == STD_ON)
#include "Dem.h"                        /* Dem header file */
#endif
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      File version check                                    **
*******************************************************************************/

/*******************************************************************************
**                      DET Error Codes                                       **
*******************************************************************************/
/* polyspace-begin MISRA-C3:2.5 [Not a defect:Low] "macro is used according to user configuration" */
/* @Trace: SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 */
/* DET error is reported if an API is invoked without module initialization */
#define WDGM_E_UNINIT                             0x10U
/* DET error is reported if an WdgM_Init is invoked with an erroneous configuration set */
#define WDGM_E_PARAM_CONFIG                       0x11U
/* DET error is reported if an API is invoked with wrong "mode" parameter */
#define WDGM_E_PARAM_MODE                         0x12U
/* DET error is reported if an API is invoked with wrong "SEID" parameter */
#define WDGM_E_PARAM_SEID                         0x13U
/* DET error is reported if an API is invoked with a null pointer parameter */
#define WDGM_E_INV_POINTER                        0x14U
/* DET error is reported if Disabling of watchdog not allowed  */
#define WDGM_E_DISABLE_NOT_ALLOWED                0x15U
/* DET error is reported if an API is invoked with an invalid CheckpointId */
#define WDGM_E_CPID                               0x16U

/*
   DET error is reported if WdgM_UpdateAliveIndication cannot determine the
   Checkpoint, because there are more than one alive supervisions configured
   in the current mode for the given Supervised Entity
 */
/* polyspace-begin MISRA-C3:2.5 [Not a defect:Low] "This macro is defined according to WdgM specification" */
#define WDGM_E_AMBIGIOUS                          0x18U
/* polyspace-end MISRA-C3:2.5 */

/*
   DET error is reported if WdgM_CheckpointReached is invoked with a checkpoint
   of a Supervised Entity that is deactivated in the current Watchdog Manager
   mode
 */
#define WDGM_E_SEDEACTIVATED                      0x19U
/* DET error is reported if WdgM_Init is invoked without module de-initialization */
#define WDGM_E_NO_DEINIT                          0x1AU
/* DET error is reported if WdgM is called by an invalid core */
#define WDGM_E_COREINACTIVATED                    0x1FU
/* polyspace-end MISRA-C3:2.5 */
#define WDGM_GLOBALSTATUS_TOTAL               5
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* polyspace-begin MISRA-C3:2.5 [Not a defect:Low] "macro is used according to user configuration" */

#define WDGM_ZERO                                 0x00U
#define WDGM_ONE                                  0x01U

#define WDGM_TRUE                             (TRUE)
#define WDGM_FALSE                            (FALSE)

/*  Macros to Update and Extract the SE Local Supervision status*/
#define WDGM_CLEAR_STATUS                         0x00U
#define WDGM_STATUS_MASK                          0x07U
#define WDGM_CLEAR_SE                             0xF8U

#define WDGM_ALIVESUPERVISION_CORRECT             0x10U
#define WDGM_DEADLINESUPERVISION_CORRECT          0x20U
#define WDGM_LGSUPERVISION_CORRECT                0x40U
#define WDGM_SET_ALLSUPVSN_CORRECT                0x70U

#define WDGM_ALIVESUPERVISION_INCORRECT           0xEFU
#define WDGM_DEADLINESUPERVISION_INCORRECT        0xDFU
#define WDGM_LGSUPERVISION_INCORRECT              0xBFU

/*  Macros to check Deadline Supervision Started or not */
#define WDGM_DS_STARTED                           0x01U
#define WDGM_DS_NOT_STARTED                       0x00U

/* Macros to extract SE parameters  */
#define WDGM_B0_AS                                0x01U
#define WDGM_B1_DS                                0x02U
#define WDGM_B2_ILS                               0x04U
#define WDGM_B3_ELS                               0x08U
/* polyspace-end MISRA-C3:2.5 */

/*******************************************************************************
**                                  Macros                                    **
*******************************************************************************/
/* polyspace-begin MISRA-C3:D4.9 [Not a defect:Low] "macro is used for improving performance" */
/* polyspace-begin MISRA-C3:2.5 [Not a defect:Low] "This marco is used in WdgM_InternalSetMode when WDGM_ENABLE_TRIGGER == STD_OFF" */
/* avoid violation of unused varialbe */
#define WDGM_UNUSED(x)                   (void)(x)
/* polyspace-end MISRA-C3:2.5 */
/* avoid violation of unused pointere */
#define WDGM_UNUSED_PTR(x)               WDGM_UNUSED(x)
/* polyspace-end MISRA-C3:D4.9 */

/*******************************************************************************
**                       Global Data Types                                    **
*******************************************************************************/
/* Type used for Rte Direct API */
typedef P2FUNC(Std_ReturnType, WDGM_CODE, WdgM_RteFuncPtrType)
  (const Rte_ModeType_WdgM_Mode ddModeType);

/* @Trace: SRS_ModeMgm_09221 SRS_ModeMgm_09222 */
/* @Trace: SafeWdgM_SUD_DATATYPE_019 */
typedef enum
{
  WDGM_CP_INITIAL = 0x00U,
  WDGM_CP_FINAL,
  WDGM_CP_BI
} WdgM_CpType;

#if(WDGM_ENABLE_TRIGGER == STD_ON)
/* @Trace:  */
/* @Trace: SafeWdgM_SUD_DATATYPE_020 */
typedef enum
{
  WDGM_TM_NORMAL = 0x00U,
  WDGM_TM_TIMEOUT,
  WDGM_TM_DEINIT
} WdgM_TriggerModeType;
#endif

#if(WDGM_ENABLE_OS_APPLICATION == STD_ON)
typedef enum
{
  WDGM_OS_APPLICATION_TRUSTED = 0x00U,
  WDGM_OS_APPLICATION_NON_TRUSTED
} WdgM_TrustedType;
#endif

/* @Trace: WdgM_SRS_ECUC_00329 */
/* @Trace: SafeWdgM_SUD_DATATYPE_025 */
typedef uint16 WdgM_ExpSupCycleTolType;

#if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
/* @Trace: WdgM_SRS_ECUC_00327 */
/* @Trace: SafeWdgM_SUD_DATATYPE_026 */
typedef uint16 WdgM_FailureTolType;

/* @Trace: SRS_ModeMgm_09106 */
/* @Trace: SafeWdgM_SUD_DATATYPE_023 */
typedef uint32 WdgM_ExAliveIndicationsCountType;

/* @Trace: SRS_ModeMgm_09106 */
/* @Trace: SafeWdgM_SUD_DATATYPE_021 */
typedef uint16 WdgM_AliveSupRefCycleCountType;

/* @Trace: SRS_ModeMgm_09106 */
/* @Trace: SafeWdgM_SUD_DATATYPE_002 */
typedef struct
{
  /* Supervised entity to be supervised */
  WdgM_SupervisedEntityIdType SEId;
  /* Index to the SE array WdgM_SupervisedEntity */
  WdgM_SupervisedEntityIndexType SEArrayIndex;
  /* Checkpoint to be supervised */
  WdgM_CheckpointIdType Checkpoint;
  /* Expected alive indications of the Checkpoint */
  WdgM_ExAliveIndicationsCountType ExAliveIndications;
  /* Reference supervision cycles to perform the checkup with counted
    alive indications */
  WdgM_AliveSupRefCycleCountType SupervisionRefCycle;
  /* Allowed additional to the expected alive indications */
  uint8 ExAliveIndMaxMargin;
  /* Allowed missing expected alive indications */
  uint8 ExAliveIndMinMargin;
} WdgM_AliveSupervisionType;
#endif

#if(WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON)
/* @Trace: SRS_WdgM_CUS_00007 */
/* @Trace: SafeWdgM_SUD_DATATYPE_007 */
typedef struct
{
  /* Tick value updated by OS */
  TickType TickValue;
  /* Status of the corresponding deadline monitoring i.e. WDGM_DS_STARTED,
    WDGM_DS_NOT_STARTED */
  uint8 DSStatus;
} WdgM_DeadlineSupervisionStatusType;

/* @Trace: SRS_WdgM_CUS_00007 */
/* @Trace: SafeWdgM_SUD_DATATYPE_008 */
typedef struct
{
  /* Supervised entity to be supervised */
  WdgM_SupervisedEntityIdType SEId;
  /* Final Checkpoint to be supervised */
  WdgM_CheckpointIdType InitialCheckpoint;
  /* Final Checkpoint to be supervised */
  WdgM_CheckpointIdType FinalCheckpoint;
  /* Allowed additional time span for deadline */
  uint32 DeadlineMax;
  /* Allowed missing time span for deadline */
  uint32 DeadlineMin;
} WdgM_DeadlineSupervisionType;
#endif

#if(WDGM_ENABLE_INTERNAL_TRANSITION == STD_ON)
/* @Trace: SRS_ModeMgm_09221 SRS_ModeMgm_09222 */
/* @Trace: SafeWdgM_SUD_DATATYPE_015 */
typedef struct
{
  /* Store the last reported CP details for internal transition */
  WdgM_CheckpointIdType LastReportedCP;
  /* Store the activity status of the corresponding internal transition */
  boolean ActivityFlag;
} WdgM_IntLogicalSupervisionStatusType;
#endif

#if(WDGM_ENABLE_EXTERNAL_TRANSITION == STD_ON)
/* @Trace: SRS_ModeMgm_09221 SRS_ModeMgm_09222 */
/* @Trace: SafeWdgM_SUD_DATATYPE_024 */
typedef uint32 WdgM_ExLSGraphArrayType;

/* @Trace: SRS_ModeMgm_09221 SRS_ModeMgm_09222 */
/* @Trace: SafeWdgM_SUD_DATATYPE_013 */
typedef struct
{
  /* Store the last reported SE/CP details for external transition */
  WdgM_ExLSGraphArrayType LastRepExLSGraphArrIdx;
  /* Store the activity status of the corresponding external transition */
  boolean ActivityFlag;
} WdgM_ExtLogicalSupervisionStatusType;

/* @Trace: SRS_ModeMgm_09221 SRS_ModeMgm_09222 */
/* @Trace: SafeWdgM_SUD_DATATYPE_011 */
typedef struct
{
  /* Supervised entity to be supervised */
  WdgM_SupervisedEntityIdType SEId;
  /* Final Checkpoint to be supervised */
  WdgM_CheckpointIdType Checkpoint;
  /* Index of Checkpoint Mapping Array
    WdgM_GaaExLS<MODE_ID><GRAPH_ID>MapArray */
  WdgM_CpMapArrayIndexType CpMapArrayIndex;
  /* Maximum available transition paths for a corresponding check point */
  uint8 MaxBranches;
  /* Check point type. Either WDGM_CP_INITIAL, WDGM_CP_FINAL or WDGM_CP_BI */
  WdgM_CpType CpType;
} WdgM_ExLSGraphType;
/* @Trace: SRS_ModeMgm_09221 SRS_ModeMgm_09222 */

/* @Trace: SRS_ModeMgm_09221 SRS_ModeMgm_09222 */
/* @Trace: SafeWdgM_SUD_DATATYPE_010 */
typedef struct
{
  /* Supervised entity to be supervised */
  WdgM_SupervisedEntityIdType SEId;
  /* Final Checkpoint to be supervised */
  WdgM_CheckpointIdType Checkpoint;
} WdgM_ExLSGraphMapArrayType;

/* @Trace: SRS_ModeMgm_09221 SRS_ModeMgm_09222 */
/* @Trace: SafeWdgM_SUD_DATATYPE_012 */
typedef struct
{
  /* Pointer to corresponding WdgM_GaaExLSGraph<MODE_ID><GRAPH_ID> */
  P2CONST(WdgM_ExLSGraphType, AUTOMATIC, WDGM_CONST) PtrExLSGraph;
  /* Pointer to corresponding WdgM_GaaExLSGraph<MODE_ID><GRAPH_ID>MapArray */
  P2CONST(WdgM_ExLSGraphMapArrayType, AUTOMATIC, WDGM_CONST)
    PtrExLSGraphMapArray;
  /* Total number of checkpoints configured in the external graph */
  WdgM_CheckpointIdType TotalCheckpoints;
} WdgM_ExLogicalSupervisionType;
#endif
/* @Trace: WdgM_SRS_ECUC_00303 WdgM_SRS_ECUC_00325 WdgM_SRS_ECUC_00326 WdgM_SRS_ECUC_00327 */
/* @Trace: SafeWdgM_SUD_DATATYPE_001 */
typedef struct
{
  /* Supervised entity to be supervised */
  WdgM_SupervisedEntityIdType SEId;
  /* Index to the SE array WdgM_SupervisedEntity */
  WdgM_SupervisedEntityIndexType SEArrayIndex;
  /* Failed Alive supervision tolerance */
  uint8 FailedTolerance;
} WdgM_ActiveSEType;
/* @Trace: WdgM_SRS_ECUC_00303 WdgM_SRS_ECUC_00325 WdgM_SRS_ECUC_00326 WdgM_SRS_ECUC_00327 */

#if(WDGM_ENABLE_TRIGGER == STD_ON)
/* @Trace:  */
/* @Trace: SafeWdgM_SUD_DATATYPE_018 */
typedef struct
{
  /* WdgIf mode for the corresponding WdgM mode */
  WdgIf_ModeType WdgIfMode;
  /* Wdg Trigger Timeout */
  uint16 WdgIfTimeout;
  /* WdgIf Device Id */
  uint8 WdgIfDeviceId;
} WdgM_TriggerType;
#endif
/* @Trace: SRS_ModeMgm_09221 SRS_ModeMgm_09222 SRS_WdgM_CUS_00007 SRS_ModeMgm_09106 */
/* @Trace: SafeWdgM_SUD_DATATYPE_003 */
typedef struct
{
  #if(WDGM_ENABLE_INTERNAL_TRANSITION == STD_ON)
  /* Index of Checkpoint Mapping Array WdgM_GaaSE<SEID>CpIntLSGraphMap */
  WdgM_CpMapArrayIndexType CpMapArrayIndex;
  /* Maximum available transition paths for a corresponding check point */
  uint8 MaxBranches;
  /* Index of an internal superivison graph of a SE which Checkpoint belongs to */
  uint16 GraphIdx;
  #endif
  /* Check point type. Either WDGM_CP_INITIAL, WDGM_CP_FINAL or WDGM_CP_BI */
  WdgM_CpType CpType;
} WdgM_CheckpointGraphType;

#if(WDGM_ENABLE_INTERNAL_TRANSITION == STD_ON)
/* @Trace: SRS_ModeMgm_09221 SRS_ModeMgm_09222 */
/* @Trace: SafeWdgM_SUD_DATATYPE_014 */
typedef struct
{
  /* Pointer to corresponding WdgM_GaaIntLSGraphSE<SEID>MapArray */
  P2CONST(WdgM_CheckpointIdType, AUTOMATIC, WDGM_CONST) PtrIntLSGraphMapArray;
  /* Index to Internal Logical Supervision Status Array */
  WdgM_IntLogicSupStatArrIndexType ILSIndex;
} WdgM_IntLSGraphArrayType;
#endif

/* @Trace: SRS_ModeMgm_09221 SRS_ModeMgm_09222 SRS_WdgM_CUS_00007 SRS_ModeMgm_09106 */
/* @Trace: SafeWdgM_SUD_DATATYPE_017 */
typedef struct
{
  /* Pointer to corresponding WdgM_GaaSE<SEID>Checkpoints */
  P2CONST(WdgM_CheckpointGraphType, AUTOMATIC, WDGM_CONST) PtrCheckpoint;
  #if(WDGM_ENABLE_INTERNAL_TRANSITION == STD_ON)
  /* Pointer to corresponding WdgM_GaaIntLSGraphSE<SEID>Array. 
   * the pointer contains all configured internal logical supervision graph for SE
   */
  P2CONST(WdgM_IntLSGraphArrayType, AUTOMATIC, WDGM_CONST) PtrIntLSGraphArray;
  /* Total number of configured internal graph for a coressponding SE */
  uint16 NumberOfInternalGraph;
  #endif
  /* Pointer to Rte function pointer switch */
  WdgM_RteFuncPtrType PtrRteSwitchMode;
  /* Total configured check points for a supervised entity */
  WdgM_CheckpointIdType TotalCheckpoints;
  /* Supervised Entity Id */
  WdgM_SupervisedEntityIdType SEId;
  #if(WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON)
  /* OsCounter ID */
  CounterType CounterID;
  #endif
  #if(WDGM_ENABLE_OS_APPLICATION == STD_ON)
  /* OS Application ID */
  ApplicationType ApplicationId;
  /* OS Application Trusted type */
  WdgM_TrustedType TrustedType;
  #endif
  /* Supervision algorithms applicable for SE */
  uint8 SupervisionMechanism;
} WdgM_SupervisedEntityType;

/* @Trace: SRS_ModeMgm_09221 SRS_ModeMgm_09222 SRS_WdgM_CUS_00007 SRS_ModeMgm_09106 */
/* @Trace: SafeWdgM_SUD_DATATYPE_016 */
typedef struct
{
  #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
  /* Pointer to corresponding WdgM_GaaMode<MODE_ID>AliveSupervisions[] */
  P2CONST(WdgM_AliveSupervisionType, AUTOMATIC, WDGM_CONST)
    PtrAliveSupervisions;
  #endif
  #if(WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON)
  /* Pointer to corresponding  WdgM_GaaMode<MODE_ID>DeadlineSupervision */
  P2CONST(WdgM_DeadlineSupervisionType, AUTOMATIC, WDGM_CONST)
    PtrDeadlineSupervisions;
  #endif
  #if(WDGM_ENABLE_EXTERNAL_TRANSITION == STD_ON)
  /* Pointer to corresponding  WdgM_GaaMode<MODE_ID>ExLogicalSupervisions */
  P2CONST(WdgM_ExLogicalSupervisionType, AUTOMATIC, WDGM_CONST)
    PtrExLogicalSupervisions;
  #endif
  /* Pointer to corresponding  WdgM_GaaMode<MODE_ID>ActiveSE */
  P2CONST(WdgM_ActiveSEType, AUTOMATIC, WDGM_CONST) PtrActiveSEList;
  #if(WDGM_ENABLE_TRIGGER == STD_ON)
  /* Pointer to corresponding  WdgM_GaaMode<MODE_ID>Triggers */
  P2CONST(WdgM_TriggerType, AUTOMATIC, WDGM_CONST) PtrTriggers;
  #endif
  /* Duration in which the blocking of watchdog triggering shall be postponed */
  uint16 WdgTrigBlockCount;
  /* MainFunction period */
  uint16 SupervisionCycle;
  #if(WDGM_ENABLE_ALIVE_SUPERVISION == STD_ON)
  /* Total Configured Alive Supervisions */
  uint16 TotalAliveSupervisions;
  #endif
  #if(WDGM_ENABLE_DEADLINE_SUPERVISION == STD_ON)
  /* Total Configured Deadline Supervisions */
  uint16 TotalDeadlineSupervisions;
  #endif
  #if(WDGM_ENABLE_EXTERNAL_TRANSITION == STD_ON)
  /* Total Configured External Logical Supervisions */
  uint16 TotalExLogicalSupervisions;
  #endif
  /* Total number of active SE's in the current mode */
  WdgM_SupervisedEntityIndexType TotalSEInMode;
  #if(WDGM_ENABLE_TRIGGER == STD_ON)
  /* Total Configured Triggers */
  uint8 TotalTriggers;
  #endif
} WdgM_ModePropertyType;

#if(WDGM_DEM_ERROR_REPORT == STD_ON)
/* @Trace: WdgM_SRS_ECUC_00362 WdgM_SRS_ECUC_00355 WdgM_SRS_ECUC_00353 */
/* @Trace: SafeWdgM_SUD_DATATYPE_009 */
typedef struct 
{
  /* WDGM_E_SET_MODE error code */
  boolean ESetModeEnable;
  Dem_EventIdType ESetMode;
#if(WDGM_DEM_STOPPED_SUPERVISION_REPORT == STD_ON)
  /* WDGM_E_SUPERVISION error code */
  boolean ESupervisionEnable;
  Dem_EventIdType ESupervision;
#endif
} WdgM_DemEventParameterType;
#endif

/* @Trace: WdgM_SRS_ECUC_00337 WdgM_SRS_ECUC_00335 WdgM_SRS_ECUC_00336 WdgM_SRS_ECUC_00362 WdgM_SRS_ECUC_00355 WdgM_SRS_ECUC_00353 */
/* @Trace: SafeWdgM_SUD_DATATYPE_005 */
typedef struct 
{
#if(WDGM_DEM_ERROR_REPORT == STD_ON)
  /* Dem Event Parameter */
  WdgM_DemEventParameterType DemEventParam;
#endif
  /* Inital Mode of ConfigSet */
  WdgM_ModeType InitialMode;
  /* Total Modes configured in a ConfigSet */
  WdgM_ModeType TotalMode;
  /* Pointer to configured Modes of a ConfigSet */
  P2CONST(WdgM_ModePropertyType, AUTOMATIC, WDGM_CONST) PtrModes;
#if(WDGM_ENABLE_ALIVE_SUPERVISION)
  /* Maximum Alive Supervision Reference Cycle */
  uint32 MaxAliveSupervisionRefCycle;
#endif
} WdgM_ConfigType;

typedef VAR(uint8, WDGM_VAR_POWER_ON_INIT) WdgM_CoreIdType;

/* @Trace: SRS_ModeMgm_09221 SRS_ModeMgm_09222 SRS_WdgM_CUS_00007 SRS_ModeMgm_09106 */
#define WDGM_START_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include"MemMap.h"
extern CONST(WdgM_SupervisedEntityType, WDGM_CONST)
  WdgM_SupervisedEntity[WDGM_TOTAL_SES];
#define WDGM_STOP_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include "MemMap.h"

/* @Trace: SRS_BSW_00310 SRS_BSW_00336 */
#define WDGM_START_SEC_CONFIG_DATA_PREBUILD_ASIL_D_16
#include "MemMap.h"
/* WDGM_DEINIT_TIMEOUT */
extern CONST(uint16, WDGM_CONST) WdgM_DeInitTimeout[WDGM_TOTAL_CORES];
#define WDGM_STOP_SEC_CONFIG_DATA_PREBUILD_ASIL_D_16
#include "MemMap.h"

/* @Trace:  SRS_ModeMgm_09221 SRS_ModeMgm_09222 SRS_WdgM_CUS_00007 SRS_ModeMgm_09106 */
#define WDGM_START_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include "MemMap.h"
/* WDGM_TOTAL_SES */
extern CONST(WdgM_SupervisedEntityIndexType, WDGM_CONST) WdgM_TotalSEs;
#define WDGM_STOP_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include "MemMap.h"

#define WDGM_START_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include "MemMap.h"
extern CONSTP2CONST(WdgM_ConfigType, AUTOMATIC, WDGM_CONST) WdgM_Config[WDGM_TOTAL_CORES];
#define WDGM_STOP_SEC_CONFIG_DATA_PREBUILD_ASIL_D_UNSPECIFIED
#include "MemMap.h"

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                 **
*******************************************************************************/
/* polyspace-begin MISRA-C3:D4.8 */
/* polyspace-end MISRA-C3:20.1 */
/* polyspace:end<CERT-C:PRE00-C> */

#endif /* WDGM_INT_TYPES_H */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
