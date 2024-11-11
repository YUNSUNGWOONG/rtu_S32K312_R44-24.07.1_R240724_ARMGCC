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
**  SRC-MODULE: CanCM.h                                                       **
**                                                                            **
**  TARGET    : General CAN Communication Manager                             **
**                                                                            **
**  PRODUCT   : AUTOEVER CAN Communication Manager Module                     **
**                                                                            **
**  PURPOSE   : Header file of CanCM.c                                        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.0.7     20-Jun-2023   HieuTM8          CP44-2219                         **
** 1.0.5     14-Oct-2022   NhatTD2          CP44-1009                         **
** 1.0.5     14-Oct-2022   NhatTD2          CP44-812                          **
** 1.0.3.1   29-Jun-2022   NhatTD2          CP44-135                          **
** 1.0.2     23-Feb-2022   HieuTM8          Redmine #20448                    **
** 1.0.1     22-Sep-2021   LinhTT36         Redmine #20380                    **
** 1.0.0     22-Dec-2020   SJ Kim           Initial Version                   **
*******************************************************************************/
#ifndef CANCM_H
#define CANCM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: SRS_BSW_00301 */
#include "CanCM_Ram.h"
#include "ComM.h"
#include "EcuM.h"
#include "IoHwAb.h"
#include "BswM.h"
#include "CanIf.h"
/* @Trace: CanCM_SUD_DATATYPE_002 CanCM_SUD_DATATYPE_003 */
#include "Std_Types.h"         /* Standard type header */
/* @Trace: CanCM_SUD_DATATYPE_011 */
#include "ComStack_Types.h"
#include "CanCM_InitTypes.h"
#include "CanCM_Error.h"       /* CanCM DET header file */
#include "CanCM_PCTypes.h"
/* @Trace: CanCM_SUD_DATATYPE_001 */
#include "EcuM_Types.h"
#include "CanCM_Cfg.h"

/*******************************************************************************
**                      Defines Section                                       **
*******************************************************************************/
/* @Trace: CanCM_SUD_MACRO_005 */
/* Service ID for CanCM_MainFunction */
#define CANCM_INIT_SID                        (0x01U)
#define CANCM_MAINFUNCTION_SID                (0x02U)
#define CANCM_COMMODEINDICATION_SID           (0x03U)
#define CANCM_GETCURRENTVOLTAGEMODE_SID       (0x04U)
#define CANCM_GETCURRENTNETWORKSTATE_SID      (0x05U)
#define CANCM_GETVOLTAGEFAILCOUNT_SID         (0x06U)
#define CANCM_GETVERSION_SID                  (0x07U)
#define CANCM_CHECKWAKEUP_SID                 (0x08U)

#define CANCM_INSTANCE_ID                     (0x00U)

#define CANCM_ZERO            ((uint8)0x0)
#define CANCM_ONE             ((uint8)0x1)
#define CANCM_TWO             ((uint8)0x2)
#define CANCM_EIGHT           ((uint8)0x8)
#define CANCM_INVALID         (0xFFFFFFFFU)
#define CANCM_INVALID_CHANNEL ((uint8)0xFF)


#define CANCM_INITIALISED     (0x01U)
#define CANCM_UNINITIALISED   (0x00U)

/* polyspace-begin MISRA-C3:D4.9 [Not a defect:Low] "Use function like-macro in order to reduce the length and complexity of the code" */
#define CanCMBswmMTxInd(chid)   ((uint16)((uint16)(chid) << CANCM_EIGHT) + 0xF0)
#define CanCMBswmMRxInd(chid)   ((uint16)((uint16)(chid) << CANCM_EIGHT) + 0xF1)
#define CanCMBswmMVolInd(chid)  ((uint16)((uint16)(chid) << CANCM_EIGHT) + 0xF2)
/* polyspace-end MISRA-C3:D4.9 [Not a defect:Low] "Use function like-macro in order to reduce the length and complexity of the code" */
/*******************************************************************************
**                           Macros                                           **
********************************************************************************/
/* MISRA-C 14.2 fixed */
/* polyspace<MISRA-C:19.7:Not a defect:Justify with annotations> use function like-macro for removing unused argument compiler warning */
#define CANCM_UNUSED_PTR(x)                               do{\
                                                             if((x) != NULL_PTR) {} \
                                                            }while(0)
/* polyspace<MISRA-C:19.7:Not a defect:Justify with annotations> use function like-macro for removing unused argument compiler warning */
#define CANCM_UNUSED(x)                                   (void)x

/*******************************************************************************
**                           Typedef section                                  **
********************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
/* Declaration of array which store multiple configuration */
/* @Trace: CanCM_SUD_GLOBALVAR_035 */
#if(STD_ON == CANCM_VARIANT_POSTBUILD_SUPPORT)
#include "CanCM_PBcfg.h"
#endif /* end of (STD_ON == CANCM_VARIANT_POSTBUILD_SUPPORT) */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define CANCM_START_SEC_CODE
#include "MemMap.h"
#if(STD_ON==CANCM_VARIANT_POSTBUILD_SUPPORT)
extern FUNC(void, CANCM_CODE) CanCM_Init(P2CONST
                (CanCM_ConfigType, AUTOMATIC,CANCM_APPL_CONST) ConfigPtr);
#else
extern FUNC(void, CANCM_CODE) CanCM_Init(void);
#endif
#define CANCM_STOP_SEC_CODE
#include "MemMap.h"

#define CANCM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANCM_CODE) CanCM_MainFunction(void);
#define CANCM_STOP_SEC_CODE
#include "MemMap.h"

#define CANCM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANCM_CODE) CanCM_GetCurrentNetworkState
        (NetworkHandleType channelIdCanCm,
        P2VAR(CanCM_CommStatType, AUTOMATIC, CANCM_APPL_DATA) ptrCommStat);
#define CANCM_STOP_SEC_CODE
#include "MemMap.h"

#define CANCM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANCM_CODE) CanCM_GetVoltageFailCount
                (P2VAR(uint16, AUTOMATIC, CANCM_APPL_DATA) ptrCount);
#define CANCM_STOP_SEC_CODE
#include "MemMap.h"

#define CANCM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType , CANCM_CODE) CanCM_GetCurrentVoltageMode
        (CanCM_ChannelType channelIdCanCm,
        P2VAR(CanCM_VolModType, AUTOMATIC, CANCM_APPL_DATA) ptrVolMode);
#define CANCM_STOP_SEC_CODE
#include "MemMap.h"

#define CANCM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANCM_CODE) CanCM_CheckWakeup(EcuM_WakeupSourceType source);
#define CANCM_STOP_SEC_CODE
#include "MemMap.h"

#if(STD_ON == CANCM_VERSION_INFO_API)
#define CANCM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANCM_CODE)CanCM_GetVersionInfo
      (P2VAR(Std_VersionInfoType, AUTOMATIC, CANCM_APPL_DATA) ptrVersionInfo);
#define CANCM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/
