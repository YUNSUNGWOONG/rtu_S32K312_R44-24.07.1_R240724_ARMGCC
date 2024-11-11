/*******************************************************************************
**                                                                            **
** (C) 2021 HYUNDAI AUTOEVER Corp.                                            **
** Confidential Proprietary Information. Distribution Limited.                **
** This source code is permitted to be used only in projects contracted       **
** with Hyundai Autoever, and any other use is prohibited.                    **
** If you use it for other purposes or change the source code,                **
** you may take legal responsibility.                                         **
** In this case, There is no warranty and technical support.                  **
**                                                                            **
**  SRC-MODULE: Dcm_Config.c                                                  **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Dcm configuration file                                        **
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
** 0.0.1     31-Dec-2019   SonDT1         AR440 Implementation                **
** 0.0.2     16-Aug-2020   HueKM          Add getter for Did configuration    **
** 0.0.3     13-Oct-2020   HueKM          Changes made as per #15766          **
** 0.0.4     04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
** 0.0.5     18-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.0.2     18-May-2022   LanhLT         Changes made as per #26479          **
** 1.0.7     16-Dec-2022   LanhLT         Fix UNECE                           **
** 1.3.0_HF1 13-Jan-2024   SY Kim         Refer #45119                        **
*******************************************************************************/

#include "Dcm.h"
#include "Dcm_Ram.h"
#include "Dcm_Types.h"
#include "Dcm_DspServices.h"
#include "Rte_Dcm.h"
#include "SchM_Dcm.h"
#include "Dcm_Config.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Dcm_CfgInternal_WriteSigTypeSenderReceiver          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to write data by              **
**                        sender receiver interface                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pDataConfig, pInBuffer                              **
**                                                                            **
** InOut parameter      : pData                                               **
**                                                                            **
** Output Parameters    : pErrorCode                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if (DCM_WRITEDATA_BYIDENTIFIER_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgInternal_WriteSigTypeSenderReceiver(
  Dcm_DataConfigConstPtrType pDataConfig,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pInBuffer,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_20340 */
  Std_ReturnType LddRetVal = E_NOT_OK;

  if ((NULL_PTR != pDataConfig) && 
      (NULL_PTR != pInBuffer) && 
      (NULL_PTR != pErrorCode))
  {
    /* @Trace: Dcm_SUD_API_20341 */
    *pErrorCode = DCM_E_GENERALREJECT;

    #if ((DCM_READ_WRITE_SEND_RECV_UINT8 == STD_ON) || \
      (DCM_READ_WRITE_SEND_RECV_UINT16 == STD_ON) || \
      (DCM_READ_WRITE_SEND_RECV_UINT32 == STD_ON) || \
      (DCM_READ_WRITE_SEND_RECV_SINT8 == STD_ON)  || \
      (DCM_READ_WRITE_SEND_RECV_SINT16 == STD_ON) || \
      (DCM_READ_WRITE_SEND_RECV_SINT32 == STD_ON))

    uint8 LucFuncIdx = pDataConfig->ucWriteFunctionIndex;

    switch(pDataConfig->ucDcmDspDataType)
    {
      #if (DCM_READ_WRITE_SEND_RECV_UINT8 == STD_ON)
      case DCM_DATA_TYPE_UINT8:
      case DCM_DATA_TYPE_UINT8_N:
        if (NULL_PTR != Dcm_GaaSigReadWriteUint8Func[LucFuncIdx].pWriteDataUint8Func)
        {
          /* @Trace: Dcm_SUD_API_20342 */
          LddRetVal = Dcm_GaaSigReadWriteUint8Func[LucFuncIdx].pWriteDataUint8Func(
            (uint8 *) pInBuffer);
        }
        break;
      #endif

      #if (DCM_READ_WRITE_SEND_RECV_UINT16 == STD_ON)
      case DCM_DATA_TYPE_UINT16:
      case DCM_DATA_TYPE_UINT16_N:
        if (NULL_PTR != Dcm_GaaSigReadWriteUint16Func[LucFuncIdx].pWriteDataUint16Func)
        {
          /* @Trace: Dcm_SUD_API_20343 */
          LddRetVal = Dcm_GaaSigReadWriteUint16Func[LucFuncIdx].pWriteDataUint16Func(
            (uint16 *) pInBuffer);
        }
        break;
      #endif

      #if (DCM_READ_WRITE_SEND_RECV_UINT32 == STD_ON)
      case DCM_DATA_TYPE_UINT32:
      case DCM_DATA_TYPE_UINT32_N:
        if (NULL_PTR != Dcm_GaaSigReadWriteUint32Func[LucFuncIdx].pWriteDataUint32Func)
        {
          /* @Trace: Dcm_SUD_API_20344 */
          LddRetVal = Dcm_GaaSigReadWriteUint32Func[LucFuncIdx].pWriteDataUint32Func(
            (uint32 *) pInBuffer);
        }
        break;
      #endif

      #if (DCM_READ_WRITE_SEND_RECV_SINT8 == STD_ON)
      case DCM_DATA_TYPE_SINT8:
      case DCM_DATA_TYPE_SINT8_N:
        if (NULL_PTR != Dcm_GaaSigReadWriteSint8Func[LucFuncIdx].pWriteDataSint8Func)
        {
          /* @Trace: Dcm_SUD_API_20345 */
          LddRetVal = Dcm_GaaSigReadWriteSint8Func[LucFuncIdx].pWriteDataSint8Func(
            (sint8 *) pInBuffer);
        }
        break;
      #endif

      #if (DCM_READ_WRITE_SEND_RECV_SINT16 == STD_ON)
      case DCM_DATA_TYPE_SINT16:
      case DCM_DATA_TYPE_SINT16_N:
        if (NULL_PTR != Dcm_GaaSigReadWriteSint16Func[LucFuncIdx].pWriteDataSint16Func)
        {
          /* @Trace: Dcm_SUD_API_20346 */
          LddRetVal = Dcm_GaaSigReadWriteSint16Func[LucFuncIdx].pWriteDataSint16Func(
            (sint16 *) pInBuffer);
        }
        break;
      #endif

      #if (DCM_READ_WRITE_SEND_RECV_SINT32 == STD_ON)
      case DCM_DATA_TYPE_SINT32:
      case DCM_DATA_TYPE_SINT32_N:
        if (NULL_PTR != Dcm_GaaSigReadWriteSint32Func[LucFuncIdx].pWriteDataSint32Func)
        {
          /* @Trace: Dcm_SUD_API_20347 */
          LddRetVal = Dcm_GaaSigReadWriteSint32Func[LucFuncIdx].pWriteDataSint32Func(
            (sint32 *) pInBuffer);
        }
        break;
      #endif

      default:
        /* @Trace: Dcm_SUD_API_20348 */
        LddRetVal = E_NOT_OK;
        break;
    }

    if (E_OK == LddRetVal)
    {
      /* @Trace: Dcm_SUD_API_20349 */
      *pErrorCode = DCM_POS_RESP;
    }
    #endif
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_CfgInternal_ReadSigTypeEcuSignal                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to read data by               **
**                        ecu signal interface                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pDataConfig                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pOutBuffer                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* polyspace +5 MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) ||\
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON))
FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgInternal_ReadSigTypeEcuSignal(
  Dcm_DataConfigConstPtrType pDataConfig,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pOutBuffer)
{
  /* @Trace: Dcm_SUD_API_20350 */
  Std_ReturnType LddRetVal = E_NOT_OK;

  if ((NULL_PTR != pDataConfig) && (NULL_PTR != pOutBuffer))
  {
    #if ((DCM_DSP_USE_ECU_SIGNAL_UINT8 == STD_ON)   || \
         (DCM_DSP_USE_ECU_SIGNAL_UINT16 == STD_ON)  || \
         (DCM_DSP_USE_ECU_SIGNAL_UINT32 == STD_ON)  || \
         (DCM_DSP_USE_ECU_SIGNAL_SINT8 == STD_ON)   || \
         (DCM_DSP_USE_ECU_SIGNAL_SINT16 == STD_ON)  || \
         (DCM_DSP_USE_ECU_SIGNAL_SINT32 == STD_ON))

    uint8 LucFuncIdx = pDataConfig->ucEcuSignalFunctionIndex;
    /* polyspace +12 MISRA-C3:11.5 [Justified:Low] Justify with annotations */
    switch(pDataConfig->ucDcmDspDataType)
    {
      #if (DCM_DSP_USE_ECU_SIGNAL_UINT8 == STD_ON)
      case DCM_DATA_TYPE_UINT8:
      case DCM_DATA_TYPE_UINT8_N:
        if (NULL_PTR != Dcm_GaaEcuSignalUint8Func[LucFuncIdx].pDataReadEcuSignalUint8)
        {
          /* @Trace: Dcm_SUD_API_20351 */
          LddRetVal = E_OK;
          /* polyspace +2 CERT-C:EXP36-C [Justified:Low] "pOutBuffer depend on configuration of ucDcmDspDataType. No Impact" */
          Dcm_GaaEcuSignalUint8Func[LucFuncIdx].pDataReadEcuSignalUint8(
            (uint8 *) pOutBuffer);
        }
        break;
      #endif

      #if (DCM_DSP_USE_ECU_SIGNAL_UINT16 == STD_ON)
      case DCM_DATA_TYPE_UINT16:
      case DCM_DATA_TYPE_UINT16_N:
        if (NULL_PTR != Dcm_GaaEcuSignalUint16Func[LucFuncIdx].pDataReadEcuSignalUint16)
        {
          /* @Trace: Dcm_SUD_API_20352 */
          LddRetVal = E_OK;

          Dcm_GaaEcuSignalUint16Func[LucFuncIdx].pDataReadEcuSignalUint16(
            (uint16 *) pOutBuffer);
        }
        break;
      #endif

      #if (DCM_DSP_USE_ECU_SIGNAL_UINT32 == STD_ON)
      case DCM_DATA_TYPE_UINT32:
      case DCM_DATA_TYPE_UINT32_N:
        if (NULL_PTR != Dcm_GaaEcuSignalUint32Func[LucFuncIdx].pDataReadEcuSignalUint32)
        {
          /* @Trace: Dcm_SUD_API_20353 */
          LddRetVal = E_OK;

          Dcm_GaaEcuSignalUint32Func[LucFuncIdx].pDataReadEcuSignalUint32(
            (uint32 *) pOutBuffer);
        }
        break;
      #endif

      #if (DCM_DSP_USE_ECU_SIGNAL_SINT8 == STD_ON)
      case DCM_DATA_TYPE_SINT8:
      case DCM_DATA_TYPE_SINT8_N:
        if (NULL_PTR != Dcm_GaaEcuSignalSint8Func[LucFuncIdx].pDataReadEcuSignalSint8)
        {
          /* @Trace: Dcm_SUD_API_20354 */
          LddRetVal = E_OK;

          Dcm_GaaEcuSignalSint8Func[LucFuncIdx].pDataReadEcuSignalSint8(
            (sint8 *) pOutBuffer);
        }
        break;
      #endif

      #if (DCM_DSP_USE_ECU_SIGNAL_SINT16 == STD_ON)
      case DCM_DATA_TYPE_SINT16:
      case DCM_DATA_TYPE_SINT16_N:
        if (NULL_PTR != Dcm_GaaEcuSignalSint16Func[LucFuncIdx].pDataReadEcuSignalSint16)
        {
          /* @Trace: Dcm_SUD_API_20355 */
          LddRetVal = E_OK;

          Dcm_GaaEcuSignalSint16Func[LucFuncIdx].pDataReadEcuSignalSint16(
            (sint16 *) pOutBuffer);
        }
        break;
      #endif

      #if (DCM_DSP_USE_ECU_SIGNAL_SINT32 == STD_ON)
      case DCM_DATA_TYPE_SINT32:
      case DCM_DATA_TYPE_SINT32_N:
        if (NULL_PTR != Dcm_GaaEcuSignalSint32Func[LucFuncIdx].pDataReadEcuSignalSint32)
        {
          /* @Trace: Dcm_SUD_API_20356 */
          LddRetVal = E_OK;

          Dcm_GaaEcuSignalSint32Func[LucFuncIdx].pDataReadEcuSignalSint32(
            (sint32 *) pOutBuffer);
        }
        break;
      #endif

      default:
        /* @Trace: Dcm_SUD_API_20357 */
        LddRetVal = E_NOT_OK;
        break;
    }
    #endif
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_CfgInternal_IOControlSigTypeEcuSignal           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to control data by            **
**                        ecu signal interface                                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : LucDataType                                         **
**                                                                            **
** InOut parameter      : pData                                               **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
#if (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON)
FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgInternal_IOControlSigTypeEcuSignal(
  Dcm_DataConfigConstPtrType pDataConfig,
  uint8 Action,
  P2CONST(void, AUTOMATIC, DCM_APPL_CONST) pInBuffer,
  Dcm_NrcPtrType pErrorCode)
{
  /* @Trace: Dcm_SUD_API_20358 */
  Std_ReturnType LddRetVal = E_NOT_OK;

  if ((NULL_PTR != pDataConfig) && (NULL_PTR != pErrorCode))
  {
    /* @Trace: Dcm_SUD_API_20359 */
    *pErrorCode = DCM_E_GENERALREJECT;

    #if ((DCM_DSP_USE_ECU_SIGNAL_UINT8 == STD_ON)  || \
         (DCM_DSP_USE_ECU_SIGNAL_UINT16 == STD_ON) || \
         (DCM_DSP_USE_ECU_SIGNAL_UINT32 == STD_ON) || \
         (DCM_DSP_USE_ECU_SIGNAL_SINT8 == STD_ON)  || \
         (DCM_DSP_USE_ECU_SIGNAL_SINT16 == STD_ON) || \
         (DCM_DSP_USE_ECU_SIGNAL_SINT32 == STD_ON))

    uint8 LucFuncIdx = pDataConfig->ucEcuSignalFunctionIndex;

    switch(pDataConfig->ucDcmDspDataType)
    {
      #if (DCM_DSP_USE_ECU_SIGNAL_UINT8 == STD_ON)
      case DCM_DATA_TYPE_UINT8:
      case DCM_DATA_TYPE_UINT8_N:
        if (NULL_PTR != Dcm_GaaEcuSignalUint8Func[LucFuncIdx].pDataControlEcuSignalUint8Fnc)
        {
          /* @Trace: Dcm_SUD_API_20360 */
          LddRetVal = E_OK;
          uint8 LucInputVal = DCM_ZERO;

          if (NULL_PTR != pInBuffer)
          {
            /* @Trace: Dcm_SUD_API_20366 */
            P2CONST(uint8, AUTOMATIC, DCM_APPL_CONST) LpInputVal = (const uint8 *) pInBuffer;
            LucInputVal = *LpInputVal;
          }

          Dcm_GaaEcuSignalUint8Func[LucFuncIdx].pDataControlEcuSignalUint8Fnc(
            Action, LucInputVal);
        }
        break;
      #endif

      #if (DCM_DSP_USE_ECU_SIGNAL_UINT16 == STD_ON)
      case DCM_DATA_TYPE_UINT16:
      case DCM_DATA_TYPE_UINT16_N:
        if (NULL_PTR != Dcm_GaaEcuSignalUint16Func[LucFuncIdx].pDataControlEcuSignalUint16Fnc)
        {
          /* @Trace: Dcm_SUD_API_20361 */
          LddRetVal = E_OK;
          uint16 LusInputVal = DCM_ZERO;

          if (NULL_PTR != pInBuffer)
          {
            /* @Trace: Dcm_SUD_API_20367 */
            P2CONST(uint16, AUTOMATIC, DCM_APPL_CONST) LpInputVal = (const uint16 *) pInBuffer;
            LusInputVal = *LpInputVal;
          }

          Dcm_GaaEcuSignalUint16Func[LucFuncIdx].pDataControlEcuSignalUint16Fnc(
            Action, LusInputVal);
        }
        break;
      #endif

      #if (DCM_DSP_USE_ECU_SIGNAL_UINT32 == STD_ON)
      case DCM_DATA_TYPE_UINT32:
      case DCM_DATA_TYPE_UINT32_N:
        if (NULL_PTR != Dcm_GaaEcuSignalUint32Func[LucFuncIdx].pDataControlEcuSignalUint32Fnc)
        {
          /* @Trace: Dcm_SUD_API_20362 */
          LddRetVal = E_OK;
          uint32 LulInputVal = DCM_ZERO;

          if (NULL_PTR != pInBuffer)
          {
            /* @Trace: Dcm_SUD_API_20368 */
            P2CONST(uint32, AUTOMATIC, DCM_APPL_CONST) LpInputVal = (const uint32 *) pInBuffer;
            LulInputVal = *LpInputVal;
          }

          Dcm_GaaEcuSignalUint32Func[LucFuncIdx].pDataControlEcuSignalUint32Fnc(
            Action, LulInputVal);
        }
        break;
      #endif

      #if (DCM_DSP_USE_ECU_SIGNAL_SINT8 == STD_ON)
      case DCM_DATA_TYPE_SINT8:
      case DCM_DATA_TYPE_SINT8_N:
        if (NULL_PTR !=  Dcm_GaaEcuSignalSint8Func[LucFuncIdx].pDataControlEcuSignalSint8Fnc)
        {
          /* @Trace: Dcm_SUD_API_20363 */
          LddRetVal = E_OK;
          sint8 LscInputVal = DCM_ZERO;

          if (NULL_PTR != pInBuffer)
          {
            /* @Trace: Dcm_SUD_API_20369 */
            P2CONST(sint8, AUTOMATIC, DCM_APPL_CONST) LpInputVal = (const sint8 *) pInBuffer;
            LscInputVal = *LpInputVal;
          }

          Dcm_GaaEcuSignalSint8Func[LucFuncIdx].pDataControlEcuSignalSint8Fnc(
            Action, LscInputVal);
        }
        break;
      #endif

      #if (DCM_DSP_USE_ECU_SIGNAL_SINT16 == STD_ON)
      case DCM_DATA_TYPE_SINT16:
      case DCM_DATA_TYPE_SINT16_N:
        if (NULL_PTR != Dcm_GaaEcuSignalSint16Func[LucFuncIdx].pDataControlEcuSignalSint16Fnc)
        {
          /* @Trace: Dcm_SUD_API_20364 */
          LddRetVal = E_OK;
          sint16 LssInputVal = DCM_ZERO;

          if (NULL_PTR != pInBuffer)
          {
            /* @Trace: Dcm_SUD_API_20370 */
            P2CONST(sint16, AUTOMATIC, DCM_APPL_CONST) LpInputVal = (const sint16 *) pInBuffer;
            LssInputVal = *LpInputVal;
          }

          Dcm_GaaEcuSignalSint16Func[LucFuncIdx].pDataControlEcuSignalSint16Fnc(
            Action, LssInputVal);
        }
        break;
      #endif

      #if (DCM_DSP_USE_ECU_SIGNAL_SINT32 == STD_ON)
      case DCM_DATA_TYPE_SINT32:
      case DCM_DATA_TYPE_SINT32_N:
        if (NULL_PTR != Dcm_GaaEcuSignalSint32Func[LucFuncIdx].pDataControlEcuSignalSint32Fnc)
        {
          /* @Trace: Dcm_SUD_API_20365 */
          LddRetVal = E_OK;
          sint32 LslInputVal = DCM_ZERO;

          if (NULL_PTR != pInBuffer)
          {
            /* @Trace: Dcm_SUD_API_20371 */
            P2CONST(sint32, AUTOMATIC, DCM_APPL_CONST) LpInputVal = (const sint32 *) pInBuffer;
            LslInputVal = *LpInputVal;
          }

          Dcm_GaaEcuSignalSint32Func[LucFuncIdx].pDataControlEcuSignalSint32Fnc(
            Action, LslInputVal);
        }
        break;
      #endif

      default:
        /* @Trace: Dcm_SUD_API_20372 */
        LddRetVal = E_NOT_OK;
        break;
    }

    if (E_OK == LddRetVal)
    {
      /* @Trace: Dcm_SUD_API_20373 */
      *pErrorCode = DCM_POS_RESP;
    }
    #endif
  }

  DCM_UNUSED(Action);
  DCM_UNUSED(pInBuffer);
  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_CfgInternal_ReadSigTypeSenderReceiver           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to read data by               **
**                        sender receiver interface                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pDataConfig                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pOutBuffer                                          **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : None                                                **
**                                                                            **
*******************************************************************************/
/* polyspace +6 MISRA2012:8.13 [Justified:Low] Justify with annotations */
#if ((DCM_READ_DATA_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_IOCONTROL_BYIDENTIFIER_SERVICE == STD_ON) || \
     (DCM_MODE_CONDITION_SR_DID_USED == STD_ON))
FUNC(Std_ReturnType, DCM_CODE) Dcm_CfgInternal_ReadSigTypeSenderReceiver(
  Dcm_DataConfigConstPtrType pDataConfig,
  P2VAR(void, AUTOMATIC, DCM_APPL_DATA) pOutBuffer)
{
  /* @Trace: Dcm_SUD_API_20374 */
  Std_ReturnType LddRetVal = E_NOT_OK;

  if ((NULL_PTR != pDataConfig) && (NULL_PTR != pOutBuffer))
  {
    #if ((DCM_READ_WRITE_SEND_RECV_UINT8 == STD_ON) || \
        (DCM_READ_WRITE_SEND_RECV_UINT16 == STD_ON) || \
        (DCM_READ_WRITE_SEND_RECV_UINT32 == STD_ON) || \
        (DCM_READ_WRITE_SEND_RECV_SINT8 == STD_ON)  || \
        (DCM_READ_WRITE_SEND_RECV_SINT16 == STD_ON) || \
        (DCM_READ_WRITE_SEND_RECV_SINT32 == STD_ON))

    uint8 LucFuncIdx = pDataConfig->ucReadFunctionIndex;

    switch (pDataConfig->ucDcmDspDataType)
    {
      #if (DCM_READ_WRITE_SEND_RECV_UINT8 == STD_ON)
      case DCM_DATA_TYPE_UINT8:
      case DCM_DATA_TYPE_UINT8_N:
        if (NULL_PTR != Dcm_GaaSigReadWriteUint8Func[LucFuncIdx].pReadDataUint8Func)
        {
          /* @Trace: Dcm_SUD_API_20375 */
          LddRetVal = Dcm_GaaSigReadWriteUint8Func[LucFuncIdx].pReadDataUint8Func(
            (uint8 *) pOutBuffer);
        }
        break;
      #endif

      #if (DCM_READ_WRITE_SEND_RECV_UINT16 == STD_ON)
      case DCM_DATA_TYPE_UINT16:
      case DCM_DATA_TYPE_UINT16_N:
        if (NULL_PTR != Dcm_GaaSigReadWriteUint16Func[LucFuncIdx].pReadDataUint16Func)
        {
          /* @Trace: Dcm_SUD_API_20376 */
          LddRetVal = Dcm_GaaSigReadWriteUint16Func[LucFuncIdx].pReadDataUint16Func(
            (uint16 *) pOutBuffer);
        }
        break;
      #endif

      #if (DCM_READ_WRITE_SEND_RECV_UINT32 == STD_ON)
      case DCM_DATA_TYPE_UINT32:
      case DCM_DATA_TYPE_UINT32_N:
        if (NULL_PTR != Dcm_GaaSigReadWriteUint32Func[LucFuncIdx].pReadDataUint32Func)
        {
          /* @Trace: Dcm_SUD_API_20377 */
          LddRetVal = Dcm_GaaSigReadWriteUint32Func[LucFuncIdx].pReadDataUint32Func(
            (uint32 *) pOutBuffer);
        }
        break;
      #endif

      #if (DCM_READ_WRITE_SEND_RECV_SINT8 == STD_ON)
      case DCM_DATA_TYPE_SINT8:
      case DCM_DATA_TYPE_SINT8_N:
        if (NULL_PTR != Dcm_GaaSigReadWriteSint8Func[LucFuncIdx].pReadDataSint8Func)
        {
          /* @Trace: Dcm_SUD_API_20378 */
          LddRetVal = Dcm_GaaSigReadWriteSint8Func[LucFuncIdx].pReadDataSint8Func(
            (sint8 *) pOutBuffer);
        }
        break;
      #endif

      #if (DCM_READ_WRITE_SEND_RECV_SINT16 == STD_ON)
      case DCM_DATA_TYPE_SINT16:
      case DCM_DATA_TYPE_SINT16_N:
        if (NULL_PTR != Dcm_GaaSigReadWriteSint16Func[LucFuncIdx].pReadDataSint16Func)
        {
          /* @Trace: Dcm_SUD_API_20379 */
          LddRetVal = Dcm_GaaSigReadWriteSint16Func[LucFuncIdx].pReadDataSint16Func(
            (sint16 *) pOutBuffer);
        }
        break;
      #endif

      #if (DCM_READ_WRITE_SEND_RECV_SINT32 == STD_ON)
      case DCM_DATA_TYPE_SINT32:
      case DCM_DATA_TYPE_SINT32_N:
        if (NULL_PTR != Dcm_GaaSigReadWriteSint32Func[LucFuncIdx].pReadDataSint32Func)
        {
          /* @Trace: Dcm_SUD_API_20380 */
          LddRetVal = Dcm_GaaSigReadWriteSint32Func[LucFuncIdx].pReadDataSint32Func(
            (sint32 *) pOutBuffer);
        }
        break;
      #endif

      default:
        /* @Trace: Dcm_SUD_API_20381 */
        LddRetVal = E_NOT_OK;
        break;
    }
    #endif
  }

  return LddRetVal;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_CfgInternal_GetDidRangeConfig                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to read DidRange informations **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DidIndex                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LpDidRangeConfig                                    **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON)
FUNC(Dcm_DidRangeConfigPtrType, DCM_CODE) Dcm_CfgInternal_GetDidRangeConfig(
  uint16 DidIndex)
{
  /* @Trace: Dcm_SUD_API_20386 */
  Dcm_DidRangeConfigPtrType LpDidRangeConfig = NULL_PTR;

  #if (DCM_NUM_OF_DCMDSPDIDRANGECONFIG != DCM_ZERO)
  if (DidIndex < DCM_NUM_OF_DCMDSPDIDRANGECONFIG)
  {
    /* @Trace: Dcm_SUD_API_20382 */
    LpDidRangeConfig = &Dcm_GaaDcmDspDIDRangeConfig[DidIndex];
  }
  #else
  DCM_UNUSED(DidIndex);
  #endif

  return LpDidRangeConfig;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_CfgInternal_GetDidConfig                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to read Did informations      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DidIndex                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LpDidConfig                                         **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_DIDSERVICE_SUPPORT_ENABLE == STD_ON)
FUNC(Dcm_DidParaConfigConstPtrType, DCM_CODE) Dcm_CfgInternal_GetDidConfig(
  uint16 DidIndex)
{
  /* @Trace: Dcm_SUD_API_20387 */
  Dcm_DidParaConfigConstPtrType LpDidConfig = NULL_PTR;

  #if (DCM_NUM_OF_DIDPARACONFIG != DCM_ZERO)
  if (DidIndex < DCM_NUM_OF_DIDPARACONFIG)
  {
    /* @Trace: Dcm_SUD_API_20383 */
    LpDidConfig = &Dcm_GaaDIDParaConfig[DidIndex];
  }
  #else
  DCM_UNUSED(DidIndex);
  #endif

  return LpDidConfig;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_CfgInternal_GetPdidInfo                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to read Pdid informations     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : PdidIndex                                           **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LpPerDidInfo                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_READ_DATA_BYPERIODICIDENTIFIER_SERVICE == STD_ON)
FUNC(Dcm_PeriodicDidInfoPtrType, DCM_CODE) Dcm_CfgInternal_GetPdidInfo(
  uint16 PdidIndex)
{
  /* @Trace: Dcm_SUD_API_20388 */
  Dcm_PeriodicDidInfoPtrType LpPerDidInfo = NULL_PTR;

  #if (DCM_TOTAL_NUM_OF_PDID != DCM_ZERO)
  if (PdidIndex < DCM_TOTAL_NUM_OF_PDID)
  {
    /* @Trace: Dcm_SUD_API_20384 */
    LpPerDidInfo = &Dcm_GaaPerDidInfo[PdidIndex];
  }
  #else
  DCM_UNUSED(PdidIndex);
  #endif

  return LpPerDidInfo;
}
#endif

/*******************************************************************************
** Function Name        : Dcm_CfgInternal_GetDynDidInfo                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function is used to read DynDid informations   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DynDidIndex                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LpDynDidInfo                                        **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : NA                                                  **
**                                                                            **
*******************************************************************************/
#if (DCM_DYNAMICALLYDEFINE_DATA_IDENTIFIER_SERVICE == STD_ON)
FUNC(Dcm_DynDidInfoPtrType, DCM_CODE) Dcm_CfgInternal_GetDynDidInfo(
  uint16 DynDidIndex)
{
  /* @Trace: Dcm_SUD_API_20389 */
  Dcm_DynDidInfoPtrType LpDynDidInfo = NULL_PTR;

  #if (DCM_TOTAL_NUM_OF_DYN_DID != DCM_ZERO)
  /* polyspace +1 RTE:UNR [Justify:Low] "The index value is always less than maximun configuration DDID" */
  if (DynDidIndex < DCM_TOTAL_NUM_OF_DYN_DID)
  {
    /* @Trace: Dcm_SUD_API_20385 */
    LpDynDidInfo = &Dcm_GaaDynDidInfoConfig[DynDidIndex];
  }
  #else
  DCM_UNUSED(DynDidIndex);
  #endif

  return LpDynDidInfo;
}
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
