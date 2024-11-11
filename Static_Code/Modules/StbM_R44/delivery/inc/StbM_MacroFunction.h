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
**  SRC-MODULE: StbM_MacroFunction.h                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Synchronized Time-Base Manager Module                 **
**                                                                            **
**  PURPOSE   : Provision of internal macro functions and their functionality.**
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision        Date                By              Description            **
********************************************************************************
** 1.0.3           21-Jul-2022         ThuanVT         JIRA BUGCLASSIC-152,   **
**												  	   R44-Redmine #633	      **
** 1.0.1           15-Sep-2021         SHKim           #20096                 **
** 1.0.0     	   16-Dec-2020         SHKim           Initial Version        **
*******************************************************************************/
#ifndef STBM_MACROFUNCTION_H
#define STBM_MACROFUNCTION_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Numeric Constants                                     **
*******************************************************************************/

/*******************************************************************************
**                      Macro Definitions                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/* Macro to copy the user data*/
#define STBM_GET_USERDATA(LpDestPtr, LpSrcPtr)                    \
  (LpDestPtr) -> userDataLength = (LpSrcPtr) -> userDataLength;   \
  (LpDestPtr) -> userByte0 = (LpSrcPtr) -> userByte0;             \
  (LpDestPtr) -> userByte1 = (LpSrcPtr) -> userByte1;             \
  (LpDestPtr) -> userByte2 = (LpSrcPtr) -> userByte2

/* @Trace: SWS_StbM_00381 */
#define STBM_SET_USERDATA(LpDestPtr, LpSrcPtr)                     \
  if(NULL_PTR != (LpSrcPtr)) {                                     \
    if(((LpSrcPtr) -> userDataLength)>0) {                         \
      (LpDestPtr) -> userDataLength = (LpSrcPtr) -> userDataLength;\
      (LpDestPtr) -> userByte0 = (LpSrcPtr) -> userByte0;          \
      (LpDestPtr) -> userByte1 = (LpSrcPtr) -> userByte1;          \
      (LpDestPtr) -> userByte2 = (LpSrcPtr) -> userByte2;  } }

/* Set USERDATA without check null ptr */
#define STBM_COPY_USERDATA(LpDestPtr, LpSrcPtr)                    \
    if(((LpSrcPtr) -> userDataLength)>0) {                         \
      (LpDestPtr) -> userDataLength = (LpSrcPtr) -> userDataLength;\
      (LpDestPtr) -> userByte0 = (LpSrcPtr) -> userByte0;          \
      (LpDestPtr) -> userByte1 = (LpSrcPtr) -> userByte1;          \
      (LpDestPtr) -> userByte2 = (LpSrcPtr) -> userByte2;  }

/* Macro to copy TimeStamp*/
#define STBM_COPY_TIMESTAMP(LpDestPtr, LpSrcPtr)               \
  (LpDestPtr) -> nanoseconds = (LpSrcPtr) -> nanoseconds;      \
  (LpDestPtr) -> seconds = (LpSrcPtr) -> seconds;              \
  (LpDestPtr) -> secondsHi = (LpSrcPtr) -> secondsHi

#define STBM_COPY_STATUS(LpDestPtr, LpSrcPtr)                  \
  (LpDestPtr) -> timeBaseStatus = (LpSrcPtr) -> timeBaseStatus;

/* @Trace: StbM_SDD_DATATYPE_030 */
#define STBM_COPY_STATUS_AND_TIMESTAMP(LpDestPtr, LpSrcPtr)    \
  (LpDestPtr) -> timeBaseStatus = (LpSrcPtr) -> timeBaseStatus;\
  (LpDestPtr) -> nanoseconds = (LpSrcPtr) -> nanoseconds;      \
  (LpDestPtr) -> seconds = (LpSrcPtr) -> seconds;              \
  (LpDestPtr) -> secondsHi = (LpSrcPtr) -> secondsHi

/* Macro to copy TimeStamp*/
#define STBM_COPY_VLTIME(LpDestPtr, LpSrcPtr)                  \
  (LpDestPtr) -> nanosecondsLo = (LpSrcPtr) -> nanosecondsLo;  \
  (LpDestPtr) -> nanosecondsHi = (LpSrcPtr) -> nanosecondsHi; 

/* Macro to copy TimeStamp*/
#define STBM_INIT_TIMESTAMP(LpDestPtr)               \
  (LpDestPtr) -> timeBaseStatus = STBM_ZERO;         \
  (LpDestPtr) -> nanoseconds = STBM_ZERO;            \
  (LpDestPtr) -> seconds = STBM_ZERO;                \
  (LpDestPtr) -> secondsHi = STBM_ZERO;  

/* Macro to copy TimeStamp*/
#define STBM_INIT_VLTIME(LpDestPtr)                  \
  (LpDestPtr) -> nanosecondsLo = STBM_ZERO;          \
  (LpDestPtr) -> nanosecondsHi = STBM_ZERO; 

/* Check module is initialized */
#define STBM_CHECK_INIT(LddReturnVal,ServiceID)                             \
    if(STBM_UNINITIALIZED == StbM_GblInitStatus)                            \
    {                                                                       \
      LddReturnVal = E_NOT_OK;                                              \
      Det_ReportError(STBM_MODULE_ID, STBM_INSTANCE_ID,                     \
                        ServiceID, STBM_E_UNINIT);                          \
    }   

/* Check timeBaseId is not configured or within the reserved value range   */
/* [0..STBM_MAX_SYNC_TIME_BASES_CONFIGURED]..15: Synchronized Time Bases   */
/* [16..STBM_MAX_OFFSET_TIME_BASES_CONFIGURED]..31: Offset Time Bases      */
/* [32..STBM_MAX_PURE_TIME_BASES_CONFIGURED]..127: Pure Local Time Bases   */
/* 128 .. 65535: Reserved */

#define STBM_CHECK_TIME_BASE_ID(LddReturnVal,timeBaseId,ServiceID)          \
    if(E_OK == LddReturnVal)                                                \
    {                                                                       \
      if(((timeBaseId > STBM_MAX_SYNC_TIME_BASES_CONFIGURED) &&             \
           (timeBaseId < STBM_SIXTEEN)) ||                                  \
                 ((timeBaseId > STBM_MAX_OFFSET_TIME_BASES_CONFIGURED)&&    \
           (timeBaseId < STBM_THIRTY_TWO)) ||                               \
                 (timeBaseId > STBM_MAX_PURE_TIME_BASES_CONFIGURED))        \
      {                                                                     \
        LddReturnVal = E_NOT_OK;                                            \
        Det_ReportError(STBM_MODULE_ID, STBM_INSTANCE_ID,                   \
                        ServiceID, STBM_E_PARAM);                           \
      }                                                                     \
    }

#define STBM_CHECK_SYNC_TIME_BASE_ID(LddReturnVal,timeBaseId,ServiceID)     \
    if(E_OK == LddReturnVal)                                                \
    {                                                                       \
      if(!(timeBaseId <= STBM_MAX_SYNC_TIME_BASES_CONFIGURED))              \
      {                                                                     \
        LddReturnVal = E_NOT_OK;                                            \
        Det_ReportError(STBM_MODULE_ID, STBM_INSTANCE_ID,                   \
                        ServiceID, STBM_E_PARAM);                           \
      }                                                                     \
    }

#define STBM_CHECK_OFFSET_TIME_BASE_ID(LddReturnVal,timeBaseId,ServiceID)   \
    if(E_OK == LddReturnVal)                                                \
    {                                                                       \
      if(!((timeBaseId >= STBM_SIXTEEN) &&                                  \
                 (timeBaseId <= STBM_MAX_OFFSET_TIME_BASES_CONFIGURED)))    \
      {                                                                     \
        LddReturnVal = E_NOT_OK;                                            \
        Det_ReportError(STBM_MODULE_ID, STBM_INSTANCE_ID,                   \
                        ServiceID, STBM_E_PARAM);                           \
      }                                                                     \
    }

#define STBM_CHECK_SYNC_PURE_TIME_BASE_ID(LddReturnVal,timeBaseId,ServiceID)\
    if(E_OK == LddReturnVal)                                                \
    {                                                                       \
      if(!((timeBaseId <= STBM_MAX_SYNC_TIME_BASES_CONFIGURED) ||           \
           ((timeBaseId >= STBM_THIRTY_TWO) &&                              \
                 (timeBaseId <= STBM_MAX_PURE_TIME_BASES_CONFIGURED))))     \
      {                                                                     \
        LddReturnVal = E_NOT_OK;                                            \
        Det_ReportError(STBM_MODULE_ID, STBM_INSTANCE_ID,                   \
                        ServiceID, STBM_E_PARAM);                           \
      }                                                                     \
    }

#define STBM_CHECK_SYNC_OFFSET_TIME_BASE_ID(LddReturnVal,timeBaseId,ServiceID)\
    if(E_OK == LddReturnVal)                                                \
    {                                                                       \
      if(!((timeBaseId <= STBM_MAX_SYNC_TIME_BASES_CONFIGURED) ||           \
           ((timeBaseId >= STBM_SIXTEEN) &&                                 \
                 (timeBaseId <= STBM_MAX_OFFSET_TIME_BASES_CONFIGURED))))   \
      {                                                                     \
        LddReturnVal = E_NOT_OK;                                            \
        Det_ReportError(STBM_MODULE_ID, STBM_INSTANCE_ID,                   \
                        ServiceID, STBM_E_PARAM);                           \
      }                                                                     \
    }

/* Check NULL pointer for parameter */
#define STBM_CHECK_INVALID_POINTER(LddReturnVal,Pointer,ServiceID)          \
    if(E_OK == LddReturnVal)                                                \
    {                                                                       \
      if(NULL_PTR == Pointer)                                               \
      {                                                                     \
        LddReturnVal = E_NOT_OK;                                            \
        Det_ReportError(STBM_MODULE_ID, STBM_INSTANCE_ID,                   \
                        ServiceID, STBM_E_PARAM_POINTER);                   \
      }                                                                     \
    }


/* Get address of TimeBaseConfig */  
#define STBM_GET_ADDRESS_TIME_BASES_CONFIGURED(timeBaseId,lusConfigPtr)     \
    if(timeBaseId <= STBM_MAX_SYNC_TIME_BASES_CONFIGURED)                   \
    {                                                                       \
      lusConfigPtr = (uint16)timeBaseId;                                    \
    }                                                                       \
    else if(timeBaseId <= STBM_MAX_OFFSET_TIME_BASES_CONFIGURED)            \
    {                                                                       \
      lusConfigPtr = (uint16)timeBaseId - STBM_SIXTEEN +                    \
                      STBM_BASE_OFFSET_TIME_BASES_CONFIGURED;               \
    }                                                                       \
    else                                                                    \
    {                                                                       \
      lusConfigPtr = (uint16)timeBaseId - STBM_THIRTY_TWO +                 \
                      STBM_BASE_PURE_TIME_BASES_CONFIGURED;                 \
    }

#define STBM_GET_ADDRESS_SYNC_TIME_BASES_CONFIGURED(timeBaseId,lusConfigPtr)\
      lusConfigPtr = (uint16)timeBaseId;                                    

#define STBM_GET_ADDRESS_OFFSET_TIME_BASES_CONFIGURED(timeBaseId,lusConfigPtr)\
      lusConfigPtr = (uint16)timeBaseId - STBM_SIXTEEN +                    \
                      STBM_BASE_OFFSET_TIME_BASES_CONFIGURED;   

#define STBM_GET_ADDRESS_SYNC_PURE_TIME_BASES_CONFIGURED(timeBaseId,lusConfigPtr)     \
    if(timeBaseId <= STBM_MAX_SYNC_TIME_BASES_CONFIGURED)                   \
    {                                                                       \
      lusConfigPtr = (uint16)timeBaseId;                                    \
    }                                                                       \
    else                                                                    \
    {                                                                       \
      lusConfigPtr = (uint16)timeBaseId - STBM_THIRTY_TWO +                 \
                      STBM_BASE_PURE_TIME_BASES_CONFIGURED;                 \
    }
                      
#define STBM_GET_ADDRESS_SYNC_OFFSET_TIME_BASES_CONFIGURED(timeBaseId,lusConfigPtr)     \
    if(timeBaseId <= STBM_MAX_SYNC_TIME_BASES_CONFIGURED)                   \
    {                                                                       \
      lusConfigPtr = (uint16)timeBaseId;                                    \
    }                                                                       \
    else                                                                    \
    {                                                                       \
      lusConfigPtr = (uint16)timeBaseId - STBM_SIXTEEN +                    \
                      STBM_BASE_OFFSET_TIME_BASES_CONFIGURED;               \
    }                                                                                                                   


/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#endif /* STBM_MACROFUNCTION_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

