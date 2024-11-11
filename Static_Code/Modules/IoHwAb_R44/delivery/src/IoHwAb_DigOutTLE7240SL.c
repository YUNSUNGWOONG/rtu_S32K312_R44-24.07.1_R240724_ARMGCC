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
**  SRC-MODULE: IoHwAb_DigOutTLE7240SL.c                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb TLE7240SL module               **
**              IoHwAb_DigOutTLE7240SLSwitchOn                                **
**              IoHwAb_DigOutTLE7240SLSwitchOff                               **
**              IoHwAb_DigOutTLE7240SL                                        **
**                                                                            **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.3.0.1   30-Jun-2022  KhaLN1            #CP44-365                         **
** 1.3.0     16-Mar-2022  PhucNHM           R44-Redmine #24320                **
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb.h"
#include "IoHwAb_DigOutTLE7240SL.h"
#include "IoHwAb_Config.h"
#if (IOHWAB_USE_TLE7240SL == STD_ON)
#include "Spi.h"
#endif /* (IOHWAB_USE_TLE7240SL == STD_ON) */
#include "SchM_IoHwAb.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#if (IOHWAB_USE_TLE7240SL == STD_ON)
#define IOHWAB_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
/* variable to check the first Diagnosis trial for TLE7240SL */
static VAR(uint8, IOHWAB_VAR) IoHwAb_GucTLE7240SLDiagStatus; /* polyspace VARIABLE:* [Not a defect:Low] "System intended for multitasking" */
#define IOHWAB_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif /* (IOHWAB_USE_TLE7240SL == STD_ON) */


/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (IOHWAB_USE_TLE7240SL == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_DigOutTLE7240SLSwitchOn                      **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
** Remarks              : Global Variable(s)     :                            **
**                          IOHWAB_NUM_DIGOUT_TLE7240SL,                     **
**                          IoHwAb_GaaDigOutTLE7240SLInfos                    **
**                        Function(s) invoked    :                            **
**                          Spi_SetupEB                                       **
**                          Spi_SyncTransmit                                  **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection,                **
**                          Det_ReportError,                                  **
**                          Dem_ReportErrorStatus                             **
*******************************************************************************/
/* @Trace: SWS_IoHwAb_00079 */
/* @Trace: IoHwAb_SUD_API_081 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigOutTLE7240SLSwitchOn(void)
{
  Std_ReturnType LddReturnvalue = E_OK;
  uint8 LucIdx;
  Spi_DataType LaaTxTLE7240SL[IOHWAB_TWO] = {0U,0U};
  Spi_DataType LaaRxTLE7240SL[IOHWAB_TWO] = {0U,0U};
  /* Initialize IN1~IN4 */
  LaaTxTLE7240SL[0] = 0x00U;
  /* Initialize IN5~IN8 */
  LaaTxTLE7240SL[1] = 0x00U;

  /* Initialize DiagStatus */
  IoHwAb_GucTLE7240SLDiagStatus = 0U ; 
  
  for (LucIdx = 0U; LucIdx < IOHWAB_NUM_DIGOUT_TLE7240SL; LucIdx++)
  {
    /* Disable all int */
    SchM_Enter_IoHwAb_IoHwAbProtection();
    /* Set RTS to turn on the IC */
    Dio_WriteChannel(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddResetDioChType, STD_HIGH);

    /* SetupExternal buffer */
    LddReturnvalue = Spi_SetupEB(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddSpiChType,
      (Spi_DataType*)(LaaTxTLE7240SL), (Spi_DataType*)(LaaRxTLE7240SL), 2);
    if (LddReturnvalue != E_OK)
    {
      #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void) Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
        (uint8)IOHWAB_DIGOUT_TLE7240SL_SID, (uint8)IOHWAB_E_DET_SETUP_FAIL);
      #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
      #if (IOHWAB_USE_DEM_EVENT == STD_ON)
      Dem_ReportErrorStatus(IOHWAB_E_SETUP_FAIL, DEM_EVENT_STATUS_FAILED);
      #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
    }
    else
    {
      if ( (IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].blManualCS) != 0U )
      {
        Dio_WriteChannel(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddCSDioChType, STD_LOW);
      }

      LddReturnvalue = Spi_SyncTransmit(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddSpiSeqType);

      if ( (IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].blManualCS) != 0U )
      {
        Dio_WriteChannel(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddCSDioChType, STD_HIGH);
      }

      if (LddReturnvalue != E_OK)
      {
        #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void) Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
          (uint8)IOHWAB_DIGOUT_TLE7240SL_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
        #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
        #if (IOHWAB_USE_DEM_EVENT == STD_ON)
        Dem_ReportErrorStatus(IOHWAB_E_PROC_FAIL, DEM_EVENT_STATUS_FAILED);
        #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
      }
    }

    /* Enable all int */
    SchM_Exit_IoHwAb_IoHwAbProtection();
  }

  return LddReturnvalue;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigOutTLE7240SLSwitchOff                     **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
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
** Remarks              : Global Variable(s)     :                            **
**                          IOHWAB_NUM_DIGOUT_TLE7240SL,                     **
**                          IoHwAb_GaaDigOutTLE7240SLInfos                    **
**                        Function(s) invoked    :                            **
**                          Spi_SetupEB                                       **
**                          Spi_SyncTransmit                                  **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection,                **
**                          Det_ReportError,                                  **
**                          Dem_ReportErrorStatus                             **
*******************************************************************************/
/* @Trace: SWS_IoHwAb_00079 */
/* @Trace: IoHwAb_SUD_API_082 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigOutTLE7240SLSwitchOff(void)
{
  Std_ReturnType LddReturnvalue = E_OK;
  uint8 LucIdx;
  Spi_DataType LaaTxTLE7240SL[IOHWAB_TWO] = {0,0};

  /* Initialize IN1~IN4 */
  LaaTxTLE7240SL[0] = 0x00U;
  /* Initialize IN5~IN8 */
  LaaTxTLE7240SL[1] = 0x00U;

  for (LucIdx = 0; LucIdx < IOHWAB_NUM_DIGOUT_TLE7240SL; LucIdx++)
  {
    /* Disable all int */
    SchM_Enter_IoHwAb_IoHwAbProtection();

    LddReturnvalue = Spi_SetupEB(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddSpiChType,
      (Spi_DataType*)(LaaTxTLE7240SL), IOHWAB_NULL_PTR, 2);
    if (LddReturnvalue != E_OK)
    {
      #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void) Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
        (uint8)IOHWAB_DIGOUT_TLE7240SL_SID, (uint8)IOHWAB_E_DET_SETUP_FAIL);
      #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
      #if (IOHWAB_USE_DEM_EVENT == STD_ON)
      Dem_ReportErrorStatus(IOHWAB_E_SETUP_FAIL, DEM_EVENT_STATUS_FAILED);
      #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
    }
    else
    {
      if ( (IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].blManualCS) != 0U )
      {
        Dio_WriteChannel(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddCSDioChType, STD_LOW);
      }

      LddReturnvalue = Spi_SyncTransmit(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddSpiSeqType);

      if ( (IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].blManualCS) != 0U )
      {
        Dio_WriteChannel(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddCSDioChType, STD_HIGH);
      }

      if (LddReturnvalue != E_OK)
      {
        #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void) Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
          (uint8)IOHWAB_DIGOUT_TLE7240SL_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
        #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
        #if (IOHWAB_USE_DEM_EVENT == STD_ON)
        Dem_ReportErrorStatus(IOHWAB_E_PROC_FAIL, DEM_EVENT_STATUS_FAILED);
        #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
      }
    }

    /* Enable all int */
    SchM_Exit_IoHwAb_IoHwAbProtection();
  }

  return LddReturnvalue;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigOutTLE7240SL                              **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddReturnvalue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IOHWAB_NUM_DIGOUT_TLE7240SL,                     **
**                          IOHWAB_NUM_DIGOUT_TLE7240SL_START_IDX,             **
**                          IoHwAb_GaaDigOutTLE7240SLInfos,                   **
**                          IoHwAb_GaaDigOutResultBuffer                      **
**                        Function(s) invoked    :                            **
**                          Spi_SetupEB                                       **
**                          Spi_SyncTransmit                                  **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection,                **
**                          Det_ReportError,                                  **
**                          Dem_ReportErrorStatus                             **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_12418 */
/* @Trace: SWS_IoHwAb_00079 */
/* @Trace: IoHwAb_SUD_API_083 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigOutTLE7240SL(void)
{
  Std_ReturnType LddReturnvalue = E_OK;
  uint8 LucIdx;
  uint8 LucResBufIdx;
  Spi_DataType LaaTxTLE7240SL[IOHWAB_TWO] = {0U,0U};
  Spi_DataType LaaRxTLE7240SL[IOHWAB_TWO] = {0U,0U};
  uint8 LucDigOutBuf;
  uint8 LucInputMode;
  uint8 LucRevInputMode;

  for (LucIdx = 0U; LucIdx < IOHWAB_NUM_DIGOUT_TLE7240SL; LucIdx++)
  {
    LucResBufIdx = LucIdx + IOHWAB_NUM_DIGOUT_TLE7240SL_START_IDX;
    LucDigOutBuf = (uint8)IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucResult;    
    LucInputMode = (uint8)IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ucInputMode;
    LucRevInputMode = 0xFFU - LucInputMode;
    
    /* fill-up the Tx buffer */
    if (((IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ucDiagnosis) != 0U) &&
         (IoHwAb_GucTLE7240SLDiagStatus == 0U) )
    {
       LaaTxTLE7240SL[0] = 0x00U;
       LaaTxTLE7240SL[1] = 0x00U;
    }
    else
    {
       /* IN5 ~ IN8 */
       LaaTxTLE7240SL[0] =
       (uint8)(0xFFU - (((LucInputMode & 0x10U) >> 3) | (((LucDigOutBuf & LucRevInputMode)& 0x10U) >> 4)
       |((LucInputMode & 0x20U) >> 2) | (((LucDigOutBuf & LucRevInputMode)& 0x20U) >> 3)
       |((LucInputMode & 0x40U) >> 1) | (((LucDigOutBuf & LucRevInputMode)& 0x40U) >> 2)
       |((LucInputMode & 0x80U)     ) | (((LucDigOutBuf & LucRevInputMode)& 0x80U) >> 1)));
       /* IN1 ~ IN4 */
       LaaTxTLE7240SL[1] =
       (uint8)(0xFFU - (((LucInputMode & 0x1U) << 1) | (((LucDigOutBuf & LucRevInputMode)& 0x1U)) 
       |((LucInputMode & 0x2U) << 2) | (((LucDigOutBuf & LucRevInputMode)& 0x2U) << 1)
       |((LucInputMode & 0x4U) << 3) | (((LucDigOutBuf & LucRevInputMode)& 0x4U) << 2)
       |((LucInputMode & 0x8U) << 4) | (((LucDigOutBuf & LucRevInputMode)& 0x8U) << 3)));
    }
    LddReturnvalue = Spi_SetupEB(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddSpiChType,
      (Spi_DataType*)LaaTxTLE7240SL, (Spi_DataType*)LaaRxTLE7240SL, 2);

    if (LddReturnvalue != E_OK)
    {
      #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void) Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
      (uint8)IOHWAB_DIGOUT_TLE7240SL_SID, (uint8)IOHWAB_E_DET_SETUP_FAIL);
      #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
      #if (IOHWAB_USE_DEM_EVENT == STD_ON)
      Dem_ReportErrorStatus(IOHWAB_E_SETUP_FAIL, DEM_EVENT_STATUS_FAILED);
      #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
    }
    else
    {
      /* Disable all int */
      SchM_Enter_IoHwAb_IoHwAbProtection();
      if ( (IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].blManualCS) != 0U )
      {
        Dio_WriteChannel(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddCSDioChType, STD_LOW);
      }
      /* SPI Sync Transmit */
      LddReturnvalue = Spi_SyncTransmit(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddSpiSeqType);

      if ( (IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].blManualCS) != 0U )
      {
        Dio_WriteChannel(IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ddCSDioChType, STD_HIGH);
      }
      /* Enable all int */
      SchM_Exit_IoHwAb_IoHwAbProtection();

      if (((IoHwAb_GaaDigOutTLE7240SLInfos[LucIdx].ucDiagnosis) != 0U) &&
           (IoHwAb_GucTLE7240SLDiagStatus == 0U) )
      {
		    /* Diagnosis data */
        IoHwAb_GaaDigOutTLE7240SLDiagBuffer[LucIdx] = 0U;
        IoHwAb_GucTLE7240SLDiagStatus++;
			}
      else
      {
        IoHwAb_GaaDigOutTLE7240SLDiagBuffer[LucIdx]  = 0U; 
        IoHwAb_GaaDigOutTLE7240SLDiagBuffer[LucIdx] |= ( ((uint16)LaaRxTLE7240SL[0]) <<8);
        IoHwAb_GaaDigOutTLE7240SLDiagBuffer[LucIdx] |= (uint16)LaaRxTLE7240SL[1];
 
      }

      if (LddReturnvalue != E_OK)
      {
        #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void) Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
         (uint8)IOHWAB_DIGOUT_TLE7240SL_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
        #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
        #if (IOHWAB_USE_DEM_EVENT == STD_ON)
        Dem_ReportErrorStatus(IOHWAB_E_PROC_FAIL, DEM_EVENT_STATUS_FAILED);
        #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
      }
    }
  }
  return LddReturnvalue;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigOutTLE7240SLGetOpenLoad                   **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddReturnvalue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigOutTLE7240SLDiagBuffer               **
**                        Function(s) invoked    :                            **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection,                **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_13902 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigOutTLE7240SLGetOpenLoad(IoHwAb_IndexType ChIdx, 
P2VAR(IoHwAb_LevelType, AUTOMATIC, IOHWAB_APPL_DATA) Level)
{
  uint16 LucHWIdx = 0;
  uint16 LucShiftBit = ((ChIdx % 8) * 2) + 1U;

  if((ChIdx / 8) >= IOHWAB_NUM_DIGOUT_TLE7240SL_START_IDX)
  {
    LucHWIdx = (ChIdx / 8) - IOHWAB_NUM_DIGOUT_TLE7240SL_START_IDX;
  }
  else
  {
    #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void) Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
    (uint8)IOHWAB_DIGOUT_TLE7240SL_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
    #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
    #if (IOHWAB_USE_DEM_EVENT == STD_ON)
    Dem_ReportErrorStatus(IOHWAB_E_PROC_FAIL, DEM_EVENT_STATUS_FAILED);
    #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
  }

  if ( Level != NULL_PTR ) 
  {
    if ( LucHWIdx < IOHWAB_NUM_DIGOUT_TLE7240SL )
    {
      SchM_Enter_IoHwAb_IoHwAbProtection();
      /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
      *Level = (uint8)(( IoHwAb_GaaDigOutTLE7240SLDiagBuffer[LucHWIdx] & 
              ((uint16)(0x1U) << LucShiftBit) ) >> LucShiftBit);
      SchM_Exit_IoHwAb_IoHwAbProtection();
    }
    else
    {
      #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void) Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
      (uint8)IOHWAB_DIGOUT_TLE7240SL_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
      #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
      #if (IOHWAB_USE_DEM_EVENT == STD_ON)
      Dem_ReportErrorStatus(IOHWAB_E_PROC_FAIL, DEM_EVENT_STATUS_FAILED);
      #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */ 
    }
    

  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : IoHwAb_DigOutTLE7240SLGetOverCurrent                **
**                                                                            **
** Service ID           : Not yet defined                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddReturnvalue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                          IoHwAb_GaaDigOutTLE7240SLDiagBuffer               **
**                        Function(s) invoked    :                            **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection,                **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_13903 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigOutTLE7240SLGetOverCurrent(IoHwAb_IndexType ChIdx, 
P2VAR(IoHwAb_LevelType, AUTOMATIC, IOHWAB_APPL_DATA) Level)
{
  uint16 LucHWIdx = 0;
  uint16 LucShiftBit = (ChIdx % 8) * 2;

  if((ChIdx / 8) >= IOHWAB_NUM_DIGOUT_TLE7240SL_START_IDX)
  {
    LucHWIdx = (ChIdx / 8) - IOHWAB_NUM_DIGOUT_TLE7240SL_START_IDX;
  }
  else
  {
    #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET */
    (void) Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
    (uint8)IOHWAB_DIGOUT_TLE7240SL_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
    #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
    #if (IOHWAB_USE_DEM_EVENT == STD_ON)
    Dem_ReportErrorStatus(IOHWAB_E_PROC_FAIL, DEM_EVENT_STATUS_FAILED);
    #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
  }

  if ( Level != NULL_PTR ) 
  {
    if ( LucHWIdx < IOHWAB_NUM_DIGOUT_TLE7240SL )
    {
      SchM_Enter_IoHwAb_IoHwAbProtection();
      /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "NULL pointer was checked before accessing" */
      *Level = (uint8)((IoHwAb_GaaDigOutTLE7240SLDiagBuffer[LucHWIdx] & 
              ((uint16)(0x1U) << LucShiftBit) ) >> LucShiftBit);
      SchM_Exit_IoHwAb_IoHwAbProtection();
    }
    else
    {
      #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void) Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
      (uint8)IOHWAB_DIGOUT_TLE7240SL_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
      #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
      #if (IOHWAB_USE_DEM_EVENT == STD_ON)
      Dem_ReportErrorStatus(IOHWAB_E_PROC_FAIL, DEM_EVENT_STATUS_FAILED);
      #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */      
    }    
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (IOHWAB_USE_TLE7240SL == STD_ON) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

