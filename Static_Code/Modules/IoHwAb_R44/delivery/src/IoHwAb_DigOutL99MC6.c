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
**  SRC-MODULE: IoHwAb_DigOutL99MC6.c                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb L99MC6 module                  **
**              IoHwAb_DigOutL99MC6SwitchOn                                   **
**              IoHwAb_DigOutL99MC6SwitchOff                                  **
**              IoHwAb_DigOutL99MC6                                           **
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
** 1.0.0     04-Dec-2020  YangJin.Kim       R40-Redmine #26992                **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "IoHwAb.h"
#include "IoHwAb_DigOutL99MC6.h"
#include "IoHwAb_Config.h"
#if (IOHWAB_USE_L99MC6 == STD_ON)
#include "Spi.h"
#endif /* (IOHWAB_USE_L99MC6 == STD_ON) */
#include "SchM_IoHwAb.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (IOHWAB_USE_L99MC6 == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_DigOutL99MC6SwitchOn                          **
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
**                          IOHWAB_NUM_DIGOUT_L99MC6,                        **
**                          IoHwAb_GaaDigOutL99MC6Infos                       **
**                        Function(s) invoked    :                            **
**                          Spi_SetupEB                                       **
**                          Spi_SyncTransmit                                  **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection,                **
**                          Det_ReportError,                                  **
**                          Dem_ReportErrorStatus                             **
*******************************************************************************/
/* @Trace: SWS_IoHwAb_00079 */
/* @Trace: IoHwAb_SUD_API_075 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigOutL99MC6SwitchOn(void)
{
  Std_ReturnType LddReturnvalue = E_OK;
  uint8 LucIdx;
  Spi_DataType LaaTxL99MC6[IOHWAB_TWO];

  /* command : write operation / address 0x00h */
  LaaTxL99MC6[0] = 0x00U;
  /* data : EN -> 1 (go to Normal mode) */
  LaaTxL99MC6[1] = 0x80U;

  for (LucIdx = 0U; LucIdx < IOHWAB_NUM_DIGOUT_L99MC6; LucIdx++)
  {
    LddReturnvalue = Spi_SetupEB(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddSpiChType,
      (Spi_DataType*)(LaaTxL99MC6), IOHWAB_NULL_PTR, 2);
    if (LddReturnvalue != E_OK)
    {
      #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
        (uint8)IOHWAB_DIGOUT_L99MC6_SID, (uint8)IOHWAB_E_DET_SETUP_FAIL);
      #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
      #if (IOHWAB_USE_DEM_EVENT == STD_ON)
      Dem_ReportErrorStatus(IOHWAB_E_SETUP_FAIL, DEM_EVENT_STATUS_FAILED);
      #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
    }
    else
    {
      SchM_Enter_IoHwAb_IoHwAbProtection();
      if ( (IoHwAb_GaaDigOutL99MC6Infos[LucIdx].blManualCS) != 0U )
      {
        Dio_WriteChannel(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddCSDioChType, STD_LOW);
      }

      LddReturnvalue = Spi_SyncTransmit(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddSpiSeqType);

      if ( (IoHwAb_GaaDigOutL99MC6Infos[LucIdx].blManualCS) != 0U )
      {
        Dio_WriteChannel(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddCSDioChType, STD_HIGH);
      }
      SchM_Exit_IoHwAb_IoHwAbProtection();

      if (LddReturnvalue != E_OK)
      {
        #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
          (uint8)IOHWAB_DIGOUT_L99MC6_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
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
** Function Name        : IoHwAb_DigOutL99MC6SwitchOff                         **
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
**                          IOHWAB_NUM_DIGOUT_L99MC6,                        **
**                          IoHwAb_GaaDigOutL99MC6Infos                       **
**                        Function(s) invoked    :                            **
**                          Spi_SetupEB                                       **
**                          Spi_SyncTransmit                                  **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection,                **
**                          Det_ReportError,                                  **
**                          Dem_ReportErrorStatus                             **
*******************************************************************************/
/* @Trace: IoHwAb_SUD_API_076 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigOutL99MC6SwitchOff(void)
{
  Std_ReturnType LddReturnvalue = E_OK;
  uint8 LucIdx;
  Spi_DataType LaaTxL99MC6[IOHWAB_TWO];

  /* command : write operation / address 0x00h */
  LaaTxL99MC6[0] = 0x00U;
  /* data : EN -> 0 (go to standby mode) */
  LaaTxL99MC6[1] = 0x00U;

  for (LucIdx = 0; LucIdx < IOHWAB_NUM_DIGOUT_L99MC6; LucIdx++)
  {
    LddReturnvalue = Spi_SetupEB(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddSpiChType,
      (Spi_DataType*)(LaaTxL99MC6), IOHWAB_NULL_PTR, 2);
    if (LddReturnvalue != E_OK)
    {
      #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
        (uint8)IOHWAB_DIGOUT_L99MC6_SID, (uint8)IOHWAB_E_DET_SETUP_FAIL);
      #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
      #if (IOHWAB_USE_DEM_EVENT == STD_ON)
      Dem_ReportErrorStatus(IOHWAB_E_SETUP_FAIL, DEM_EVENT_STATUS_FAILED);
      #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
    }
    else
    {
      SchM_Enter_IoHwAb_IoHwAbProtection();
      if ( (IoHwAb_GaaDigOutL99MC6Infos[LucIdx].blManualCS) != 0U )
      {
        Dio_WriteChannel(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddCSDioChType, STD_LOW);
      }
      LddReturnvalue = Spi_SyncTransmit(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddSpiSeqType);
      if ( (IoHwAb_GaaDigOutL99MC6Infos[LucIdx].blManualCS) != 0U )
      {
        Dio_WriteChannel(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddCSDioChType, STD_HIGH);
      }
      SchM_Exit_IoHwAb_IoHwAbProtection();
      if (LddReturnvalue != E_OK)
      {
        #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
          (uint8)IOHWAB_DIGOUT_L99MC6_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
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
** Function Name        : IoHwAb_DigOutL99MC6                                  **
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
**                          IOHWAB_NUM_DIGOUT_L99MC6,                        **
**                          IOHWAB_NUM_DIGOUT_L99MC6_START_IDX,                **
**                          IoHwAb_GaaDigOutL99MC6Infos,                      **
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
/* @Trace: IoHwAb_SUD_API_077 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigOutL99MC6(void)
{
  Std_ReturnType LddReturnvalue = E_OK;
  uint8 LucIdx;
  uint8 LucSubIdx;
  uint8 LucResBufIdx;
  uint8 LucResBufResult;
  Spi_DataType LaaTxL99MC6[IOHWAB_TWO];
  uint8 LucOvCurRecvBuf;

  for (LucIdx = 0U; LucIdx < IOHWAB_NUM_DIGOUT_L99MC6; LucIdx++)
  {

    LucResBufIdx = LucIdx + IOHWAB_NUM_DIGOUT_L99MC6_START_IDX;

    SchM_Enter_IoHwAb_IoHwAbProtection();
    LucResBufResult= IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucResult;
    SchM_Exit_IoHwAb_IoHwAbProtection();

    for (LucSubIdx = 0U; LucSubIdx < IOHWAB_THREE; LucSubIdx++)
    {
      /* set into the command byte with address and operation mode as Write Mode*/
      LaaTxL99MC6[0] = 0x00 + (2 - LucSubIdx);

      /* arrange the L99MC6 Output into local buffer (from rauw_DigOutBuffer[]) */
      LaaTxL99MC6[1] = (Spi_DataType)(
        ((uint32)0xFF & ( (uint32)IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ulChargePumpControl >> ((uint32)8 * (uint32)LucSubIdx)))
        |  (((uint32)(LucResBufResult) & ((uint32)1 << (uint32)LucSubIdx)) >> (uint32)LucSubIdx)
        | ((((uint32)(LucResBufResult) & ((uint32)8 << (uint32)LucSubIdx)) >> (uint32)LucSubIdx) << (uint32)1)
        );

      /* arrange the L99MC6 OverCurrentRecovery enable information */
      LucOvCurRecvBuf = ((IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ucOverCurrentRecovery & (uint8)((uint8)1 << (uint8)LucSubIdx)) >> (uint8)LucSubIdx)
        | (uint8)(((IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ucOverCurrentRecovery & (uint8)((uint8)8 << (uint8)LucSubIdx)) >> (uint8)LucSubIdx) << (uint8)1);

      /* apply the OverCurrentRecovery to output data */
      LaaTxL99MC6[1] = LaaTxL99MC6[1]
        | ((Spi_DataType)((LaaTxL99MC6[1] & LucOvCurRecvBuf) << 1));

      LddReturnvalue = Spi_SetupEB(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddSpiChType,
        (Spi_DataType*)LaaTxL99MC6, IOHWAB_NULL_PTR, 2);
      if (LddReturnvalue != E_OK)
      {
        #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
          (uint8)IOHWAB_DIGOUT_L99MC6_SID, (uint8)IOHWAB_E_DET_SETUP_FAIL);
        #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
        #if (IOHWAB_USE_DEM_EVENT == STD_ON)
        Dem_ReportErrorStatus(IOHWAB_E_SETUP_FAIL, DEM_EVENT_STATUS_FAILED);
        #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
      }
      else
      {
        SchM_Enter_IoHwAb_IoHwAbProtection();        
        if ( (IoHwAb_GaaDigOutL99MC6Infos[LucIdx].blManualCS) != 0U )
        {
          Dio_WriteChannel(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddCSDioChType, STD_LOW);
        }
        LddReturnvalue = Spi_SyncTransmit(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddSpiSeqType);
        if ( (IoHwAb_GaaDigOutL99MC6Infos[LucIdx].blManualCS) != 0U )
        {
          Dio_WriteChannel(IoHwAb_GaaDigOutL99MC6Infos[LucIdx].ddCSDioChType, STD_HIGH);
        } 
        SchM_Exit_IoHwAb_IoHwAbProtection();  

        if (LddReturnvalue != E_OK)
        {
          #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
          /* Report to DET */
          (void)Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
            (uint8)IOHWAB_DIGOUT_L99MC6_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
          #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
          #if (IOHWAB_USE_DEM_EVENT == STD_ON)
          Dem_ReportErrorStatus(IOHWAB_E_PROC_FAIL, DEM_EVENT_STATUS_FAILED);
          #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
        }
      }
    }
  }

  return LddReturnvalue;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (IOHWAB_USE_L99MC6 == STD_ON) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

