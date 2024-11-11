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
**  SRC-MODULE: Tm.h                                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Time Service Module                                   **
**                                                                            **
**  PURPOSE   : Provision of callback functions and their functionality.      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.0.1     24-Jun-2022   PhatCT         R44-Redmine #25858, #28232          **
** 1.0.0     19-Jun-2020   VuCH1          Initial Version                     **
*******************************************************************************/
#ifndef TM_H
#define TM_H
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* This header file includes all the standard data types, platform dependent
  header file and common return types */
#include "Std_Types.h"
#include "Tm_Types.h" 
#include "Tm_Cfg.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Service IDs                                           **
*******************************************************************************/
/* @Trace: Tm_SUD_MACRO_007 Tm_SUD_FILE_001  */
/* Service id for Det_GetVersionInfo */
#define TM_GETVERSIONINFO_SID                   ((uint8)0x01u)

/* Service id for Timer1us16bit */
#define TM_RESETTIMER1US16BIT_SID               ((uint8)0x02u)
#define TM_GETTIMESPAN1US16BIT_SID              ((uint8)0x03u)
#define TM_SHIFTTIMESPAN1US16BIT_SID            ((uint8)0x04u)
#define TM_SYNCTIMESPAN1US16BIT_SID             ((uint8)0x05u)
#define TM_BUSYWAIT1US16BIT_SID                 ((uint8)0x06u)

/* Service id for Timer1us24bit */
#define TM_RESETTIMER1US24BIT_SID               ((uint8)0x07u)
#define TM_GETTIMESPAN1US24BIT_SID              ((uint8)0x08u)
#define TM_SHIFTTIMESPAN1US24BIT_SID            ((uint8)0x09u)
#define TM_SYNCTIMESPAN1US24BIT_SID             ((uint8)0x0au)
#define TM_BUSYWAIT1US24BIT_SID                 ((uint8)0x0bu)

/* Service id for Timer1us32bit */
#define TM_RESETTIMER1US32BIT_SID               ((uint8)0x0cu)
#define TM_GETTIMESPAN1US32BIT_SID              ((uint8)0x0du)
#define TM_SHIFTTIMESPAN1US32BIT_SID            ((uint8)0x0eu)
#define TM_SYNCTIMESPAN1US32BIT_SID             ((uint8)0x0fu)
#define TM_BUSYWAIT1US32BIT_SID                 ((uint8)0x10u)

/* Service id for Timer100us32bit */
#define TM_RESETTIMER100US32BIT_SID             ((uint8)0x11u)
#define TM_GETTIMESPAN100US32BIT_SID            ((uint8)0x12u)
#define TM_SHIFTTIMESPAN100US32BIT_SID          ((uint8)0x13u)
#define TM_SYNCTIMESPAN100US32BIT_SID           ((uint8)0x14u)

/*******************************************************************************
**                      DET Error Codes                                       **
*******************************************************************************/
/* @Trace: Tm_SUD_MACRO_010 */
/* Det Error Codes */
#define TM_E_PARAM_POINTER                      ((uint8)0x01u)
#define TM_E_PARAM_VALUE                        ((uint8)0x02u)
#define TM_E_HARDWARE_TIMER                     ((uint8)0x03u)

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#define TM_START_SEC_CODE
#include "MemMap.h"

#if (TM_VERSION_INFO_API == STD_ON)

extern FUNC(void, TM_CODE)Tm_GetVersionInfo
  (P2VAR(Std_VersionInfoType, AUTOMATIC, TM_APPL_DATA) versioninfo);
#endif /* TM_VERSION_INFO_API == STD_ON */

/* Specifies if the Predef Timer 1us16bit shall be enabled */
#if (TM_ENABLE_PREDEFTIMER_1US_16BIT  == STD_ON)

extern FUNC(Std_ReturnType, TM_CODE) Tm_ResetTimer1us16bit(
          P2VAR(Tm_PredefTimer1us16bitType, AUTOMATIC, TM_APPL_CONST) TimerPtr
            );

extern FUNC(Std_ReturnType, TM_CODE) Tm_GetTimeSpan1us16bit(
          P2CONST(Tm_PredefTimer1us16bitType, AUTOMATIC, TM_APPL_CONST) TimerPtr, 
          P2VAR(uint16, AUTOMATIC, TM_APPL_CONST) TimeSpanPtr 
            );

extern FUNC(void, TM_CODE) Tm_ShiftTimer1us16bit(
          P2VAR(Tm_PredefTimer1us16bitType, AUTOMATIC, TM_APPL_CONST) TimerPtr,
          uint16 TimeValue
            );

extern FUNC(void, TM_CODE) Tm_SyncTimer1us16bit(
          P2VAR(Tm_PredefTimer1us16bitType, AUTOMATIC, TM_APPL_CONST) TimerDstPtr,
          P2CONST(Tm_PredefTimer1us16bitType, AUTOMATIC, TM_APPL_CONST) TimerSrcPtr
            );

extern FUNC(Std_ReturnType, TM_CODE) Tm_BusyWait1us16bit(uint8 WaitingTimeMin);

#endif /* TM_ENABLE_PREDEFTIMER_1US_16BIT == STD_ON */

/* Specifies if the Predef Timer 1us24bit shall be enabled */
#if (TM_ENABLE_PREDEFTIMER_1US_24BIT  == STD_ON)

extern FUNC(Std_ReturnType, TM_CODE) Tm_ResetTimer1us24bit(
          P2VAR(Tm_PredefTimer1us24bitType, AUTOMATIC, TM_APPL_CONST) TimerPtr
            );

extern FUNC(Std_ReturnType, TM_CODE) Tm_GetTimeSpan1us24bit(
          P2CONST(Tm_PredefTimer1us24bitType, AUTOMATIC, TM_APPL_CONST) TimerPtr, 
          P2VAR(uint32, AUTOMATIC, TM_APPL_CONST) TimeSpanPtr 
            );

extern FUNC(void, TM_CODE) Tm_ShiftTimer1us24bit(
          P2VAR(Tm_PredefTimer1us24bitType, AUTOMATIC, TM_APPL_CONST) TimerPtr,
          uint32 TimeValue
            );

extern FUNC(void, TM_CODE) Tm_SyncTimer1us24bit(
          P2VAR(Tm_PredefTimer1us24bitType, AUTOMATIC, TM_APPL_CONST) TimerDstPtr,
          P2CONST(Tm_PredefTimer1us24bitType, AUTOMATIC, TM_APPL_CONST) TimerSrcPtr
            );

extern FUNC(Std_ReturnType, TM_CODE) Tm_BusyWait1us24bit(uint8 WaitingTimeMin);

#endif /* TM_ENABLE_PREDEFTIMER_1US_24BIT == STD_ON */

/* Specifies if the Predef Timer 1us32bit shall be enabled */
#if (TM_ENABLE_PREDEFTIMER_1US_32BIT  == STD_ON)

extern FUNC(Std_ReturnType, TM_CODE) Tm_ResetTimer1us32bit(
          P2VAR(Tm_PredefTimer1us32bitType, AUTOMATIC, TM_APPL_CONST) TimerPtr
            );

extern FUNC(Std_ReturnType, TM_CODE) Tm_GetTimeSpan1us32bit(
          P2CONST(Tm_PredefTimer1us32bitType, AUTOMATIC, TM_APPL_CONST) TimerPtr, 
          P2VAR(uint32, AUTOMATIC, TM_APPL_CONST) TimeSpanPtr 
            );

extern FUNC(void, TM_CODE) Tm_ShiftTimer1us32bit(
          P2VAR(Tm_PredefTimer1us32bitType, AUTOMATIC, TM_APPL_CONST) TimerPtr,
          uint32 TimeValue
            );

extern FUNC(void, TM_CODE) Tm_SyncTimer1us32bit(
          P2VAR(Tm_PredefTimer1us32bitType, AUTOMATIC, TM_APPL_CONST) TimerDstPtr,
          P2CONST(Tm_PredefTimer1us32bitType, AUTOMATIC, TM_APPL_CONST) TimerSrcPtr
            );

extern FUNC(Std_ReturnType, TM_CODE) Tm_BusyWait1us32bit(uint8 WaitingTimeMin);

#endif /* TM_ENABLE_PREDEFTIMER_1US_32BIT == STD_ON */

/* Specifies if the Predef Timer 100us32bit shall be enabled */
#if (TM_ENABLE_PREDEFTIMER_100US_32BIT  == STD_ON)

extern FUNC(Std_ReturnType, TM_CODE) Tm_ResetTimer100us32bit(
          P2VAR(Tm_PredefTimer100us32bitType, AUTOMATIC, TM_APPL_CONST) TimerPtr
            );

extern FUNC(Std_ReturnType, TM_CODE) Tm_GetTimeSpan100us32bit(
          P2CONST(Tm_PredefTimer100us32bitType, AUTOMATIC, TM_APPL_CONST) TimerPtr, 
          P2VAR(uint32, AUTOMATIC, TM_APPL_CONST) TimeSpanPtr 
            );

extern FUNC(void, TM_CODE) Tm_ShiftTimer100us32bit(
          P2VAR(Tm_PredefTimer100us32bitType, AUTOMATIC, TM_APPL_CONST) TimerPtr,
          uint32 TimeValue
            );

extern FUNC(void, TM_CODE) Tm_SyncTimer100us32bit(
          P2VAR(Tm_PredefTimer100us32bitType, AUTOMATIC, TM_APPL_CONST) TimerDstPtr,
          P2CONST(Tm_PredefTimer100us32bitType, AUTOMATIC, TM_APPL_CONST) TimerSrcPtr
            );

#endif /* TM_ENABLE_PREDEFTIMER_100US_32BIT == STD_ON */

#define TM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* TM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
