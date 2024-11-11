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
**  SRC-MODULE: IoHwAb_DigOutL9826.c                                          **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR IOHWAB                                                **
**                                                                            **
**  PURPOSE   : APIs implementation for IoHwAb L9826 module                   **
**              IoHwAb_DigOutL9826SwitchOn                                    **
**              IoHwAb_DigOutL9826SwitchOff                                   **
**              IoHwAb_DigOutL9826                                            **
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
#include "IoHwAb_DigOutL9826.h"
#include "IoHwAb_Config.h"
#if (IOHWAB_USE_L9826 == STD_ON)
#include "Spi.h"
#include "Dio.h"
#endif /* (IOHWAB_USE_L9826 == STD_ON) */
#include "SchM_IoHwAb.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#if (IOHWAB_USE_L9826 == STD_ON)
/*******************************************************************************
** Function Name        : IoHwAb_DigOutL9826SwitchOn                          **
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
**                          IoHwAb_GaaDigOutL9826Infos,                       **
**                          IoHwAb_GaaDigOutL9826ResultBuffer,                **
**                        Function(s) invoked    :                            **
**                          Dio_WriteChannel                                  **
*******************************************************************************/
/* @Trace: IoHwAb_SUD_API_078 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigOutL9826SwitchOn(void)
{
  uint8 LucIdx;

  /* clear the blStartDiag */
  for (LucIdx = 0; LucIdx < IOHWAB_NUM_DIGOUT_L9826; LucIdx++)
  {
    IoHwAb_GaaDigOutL9826ResultBuffer[LucIdx].blStartDiag = IOHWAB_FALSE;

    IoHwAb_GaaDigOutL9826ResultBuffer[LucIdx].ucDiagSCBResult = 0;
    IoHwAb_GaaDigOutL9826ResultBuffer[LucIdx].ucDiagSCGResult = 0;

    Dio_WriteChannel(IoHwAb_GaaDigOutL9826Infos[LucIdx].ddResetDioChType, IOHWAB_HIGH);
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigOutL9826SwitchOff                         **
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
**                          IoHwAb_GaaDigOutL9826Infos                        **
**                        Function(s) invoked    :                            **
**                          Dio_WriteChannel                                  **
*******************************************************************************/
/* @Trace: IoHwAb_SUD_API_079 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(void, IOHWAB_CODE)IoHwAb_DigOutL9826SwitchOff(void)
{
  uint8 LucIdx;

  for (LucIdx = 0; LucIdx < IOHWAB_NUM_DIGOUT_L9826; LucIdx++)
  {
    Dio_WriteChannel(IoHwAb_GaaDigOutL9826Infos[LucIdx].ddResetDioChType, IOHWAB_LOW);
  }
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : IoHwAb_DigOutL9826                                  **
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
**                          IoHwAb_GaaDigOutL9826Infos,                       **
**                          IoHwAb_GaaDigOutResultBuffer,                     **
**                          IoHwAb_GaaDigOutL9826ResultBuffer                 **
**                        Function(s) invoked    :                            **
**                          Spi_SetupEB                                       **
**                          Spi_SyncTransmit                                  **
**                          SchM_Enter_IoHwAb_IoHwAbProtection,               **
**                          SchM_Exit_IoHwAb_IoHwAbProtection,                **
**                          Det_ReportError,                                  **
**                          Dem_ReportErrorStatus                             **
*******************************************************************************/
/* @Trace: SRS_IoHwAb_12418 SRS_IoHwAb_12242 SRS_IoHwAb_13900 SRS_IoHwAb_13901 */
/* @Trace: SWS_IoHwAb_00079 */
/* @Trace: IoHwAb_SUD_API_080 */
#define IOHWAB_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, IOHWAB_CODE)IoHwAb_DigOutL9826(void)
{
  Std_ReturnType LddReturnvalue = E_OK;
  uint8 LucIdx;
  uint8 LucResBufIdx;
  Spi_DataType LaaTempL9826Diag[IOHWAB_EIGHT] = {0U,0U,0U,0U,0U,0U,0U,0U};
  Spi_DataType *TempL9826DiagPtr; 
  Spi_DataType LddTempTx;

  for (LucIdx = 0; LucIdx < IOHWAB_NUM_DIGOUT_L9826; LucIdx++)
  {
    /* Disable all int */
    SchM_Enter_IoHwAb_IoHwAbProtection();

    LucResBufIdx = LucIdx + IOHWAB_NUM_DIGOUT_L9826_START_IDX;
    LddTempTx = IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucResult;
    TempL9826DiagPtr = &LaaTempL9826Diag[LucIdx];

    LddReturnvalue = Spi_SetupEB(IoHwAb_GaaDigOutL9826Infos[LucIdx].ddSpiChType,
      (Spi_DataType*)&LddTempTx, TempL9826DiagPtr, IOHWAB_ONE);
    if (LddReturnvalue != E_OK)
    {
      #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
      /* Report to DET */
      (void) Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
        (uint8)IOHWAB_DIGOUT_L9826_SID, (uint8)IOHWAB_E_DET_SETUP_FAIL);
      #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
      #if (IOHWAB_USE_DEM_EVENT == STD_ON)
      Dem_ReportErrorStatus(IOHWAB_E_SETUP_FAIL, DEM_EVENT_STATUS_FAILED);
      #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
    }
    else
    {
      if (IoHwAb_GaaDigOutL9826Infos[LucIdx].blManualCS == TRUE)
      {
        Dio_WriteChannel(IoHwAb_GaaDigOutL9826Infos[LucIdx].ddCSDioChType, STD_LOW);
      }

      LddReturnvalue = Spi_SyncTransmit(IoHwAb_GaaDigOutL9826Infos[LucIdx].ddSpiSeqType);

      if (IoHwAb_GaaDigOutL9826Infos[LucIdx].blManualCS == TRUE)
      {
        Dio_WriteChannel(IoHwAb_GaaDigOutL9826Infos[LucIdx].ddCSDioChType, STD_HIGH);
      }

      if (LddReturnvalue != E_OK)
      {
        #if (IOHWAB_DEV_ERROR_DETECT == STD_ON)
        /* Report to DET */
        (void) Det_ReportError((uint16)IOHWAB_MODULE_ID, (uint8)IOHWAB_INSTANCE_ID,
          (uint8)IOHWAB_DIGOUT_L9826_SID, (uint8)IOHWAB_E_DET_PROC_FAIL);
        #endif /* (IOHWAB_DEV_ERROR_DETECT  == STD_ON) */
        #if (IOHWAB_USE_DEM_EVENT == STD_ON)
        Dem_ReportErrorStatus(IOHWAB_E_PROC_FAIL, DEM_EVENT_STATUS_FAILED);
        #endif /* (IOHWAB_USE_DEM_EVENT == STD_ON) */
      }
      else
      {
        #if (IOHWAB_USE_L9826_DIAG == STD_ON)
        /* check whether this diagnosis information update is first or not */
        /* Because the update for the first diagnosis information has not to be
          taken */
        if (IoHwAb_GaaDigOutL9826ResultBuffer[LucIdx].blStartDiag == FALSE)
        {
          IoHwAb_GaaDigOutL9826ResultBuffer[LucIdx].blStartDiag = TRUE;
        }
        else
        {
          /* Pin Mapping
          Logical pin 7  6  5  4  3  2  1  0
          L9826 pin   4  0  5  1  6  2  7  3
          */

          /* update the SCB diagnostic information into SCB area */
          IoHwAb_GaaDigOutL9826ResultBuffer[LucIdx].ucDiagSCBResult
            = (((uint8)(LaaTempL9826Diag[LucIdx] & 0xFFU)
            & IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucTempResult)
            | (IoHwAb_GaaDigOutL9826ResultBuffer[LucIdx].ucDiagSCBResult
            & ~IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucTempResult));

          /* update the SCG diagnostic information into SCG area */
          IoHwAb_GaaDigOutL9826ResultBuffer[LucIdx].ucDiagSCGResult
            = (( (uint8)( (uint8)(~(uint8)LaaTempL9826Diag[LucIdx]) & 0xFFU)
            & (uint8)(~IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucTempResult))
            | (IoHwAb_GaaDigOutL9826ResultBuffer[LucIdx].ucDiagSCGResult
            & IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucTempResult));
        }

        /* store the output data into ucTempResult */
        IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucTempResult
          = IoHwAb_GaaDigOutResultBuffer[LucResBufIdx].ucResult;
        #endif /* (IOHWAB_USE_L9826_DIAG    == STD_ON) */
      }
    }

    /* Enable all int */
    SchM_Exit_IoHwAb_IoHwAbProtection();
  }

  return LddReturnvalue;
}
#define IOHWAB_STOP_SEC_CODE
#include "MemMap.h"

#endif /* (IOHWAB_USE_L9826 == STD_ON) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
