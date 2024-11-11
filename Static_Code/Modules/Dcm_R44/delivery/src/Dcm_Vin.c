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
**  SRC-MODULE: Dcm_Vin.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Provided API Dcm_GetVin                                       **
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
** 0.0.1     27-Apr-2020   LanhLT         AR440 Implementation                **
** 0.0.2     28-Apr-2020   LanhLT         add Dcm_InternalPackVinSignal()     **
** 0.0.3     16-Aug-2020   HueKM          Fix defect and coding rules         **
** 0.0.4     13-Oct-2020   LanhLT         Changes made as per #15766          **
** 0.0.5     04-Dec-2020   LanhLT         Changes made as per #16818          **
** 0.0.6     18-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.0.2     18-May-2022   LanhLT         Changes made as per #26479          **
** 1.1.0     12-Oct-2023   SY Kim         Refer #CP44-3106                    **
*******************************************************************************/

#include "Dcm.h"
#include "Dcm_PCTypes.h"
#include "Dcm_Ram.h"
#include "Dcm_Validate.h"
#include "Dcm_Utils.h"

#define VIN_DATA_LEN (17)
#define VIN_DID ((uint16)0xF190)

/* polyspace +2 MISRA2012:2.4 [Justified:Low] Justify with annotations */
#if (DCM_VIN_REF_CONFIGURED == STD_ON)
typedef struct STagDcm_VinStateType
{
  boolean Fetched;
  uint8 Data[VIN_DATA_LEN];
} Dcm_VinStateType;
static VAR(Dcm_VinStateType, DCM_VAR) Dcm_VinState;


#define DCM_START_SEC_CODE
#include "MemMap.h"

// main logic
static FUNC(Dcm_DidParaConfigConstPtrType, DCM_CODE) Dcm_GetVinDidConfigPtr(void);

static FUNC(boolean, DCM_CODE) Dcm_ConditionCheckReadSignal(Dcm_DataConfigConstPtrType pDataCfg);

static FUNC(boolean, DCM_CODE) Dcm_ReadSignalData(Dcm_DataConfigConstPtrType pDataCfg);

static FUNC(boolean, DCM_CODE) Dcm_PackSignalData(Dcm_DidSignalConfigPtrType pSignalCfg);

// util
static FUNC(void, DCM_CODE) Dcm_InitVinDataState(void);

static FUNC(boolean, DCM_CODE) Dcm_IsVinDataFetched(void);

// getter/setter
static FUNC(boolean, DCM_CODE) Dcm_GetFetchedVinData(void);

static FUNC(void, DCM_CODE) Dcm_SetFetchedVinData(boolean FetchedVinData);

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif

#define DCM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Dcm_GetVin                                          **
**                                                                            **
** Service ID           : 0x07                                                **
**                                                                            **
** Description          : Function to get the VIN (as defined in SAE J1979-DA)**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Data                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
/* @Trace: SWS_Dcm_00950 */
FUNC(Std_ReturnType, DCM_CODE) Dcm_GetVin(Dcm_Uint8PtrType pData)
{
  /* @Trace: Dcm_SUD_API_20294 */
  Std_ReturnType RetVal = E_NOT_OK;

  #if (DCM_VIN_REF_CONFIGURED == STD_ON)
  /* Check init state and input arguments */
  boolean ChkVal = Dcm_ChkInit(DCM_GET_VIN_SID);
  CHK_NEXT(ChkVal, Dcm_ChkP2Var(DCM_GET_VIN_SID, pData));

  if (DCM_TRUE == ChkVal)
  {
    /* @Trace: Dcm_SUD_API_20295 */
    /* Get fetch vin data status */
    boolean IsVinDataFetched = Dcm_IsVinDataFetched();

    /* In case vin data is not fetched */
    if (DCM_TRUE != IsVinDataFetched)
    {
      /* @Trace: Dcm_SUD_API_20296 */
      /* If the fetch vin operation is failed at start-up time,
       * we will fetch it again at the next call of Dcm_GetVin() function */
      Dcm_FetchVin();
      IsVinDataFetched = Dcm_IsVinDataFetched();
    }

    /* In case vin data is fetched successfully */
    if (DCM_TRUE == IsVinDataFetched)
    {
      /* @Trace: Dcm_SUD_API_20298 */
      RetVal = E_OK;
      Dcm_MemCopy(pData, Dcm_VinState.Data, VIN_DATA_LEN);
    }
  }
  #else
  DCM_UNUSED(pData);
  #endif

  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_FetchVin                                        **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Function to Fectch Vin after Dcm_Int                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) : Dcm_ConditionCheckReadSignal          **
**                                      Dcm_ReadSignalData                    **
**                                      Dcm_PackSignalData                    **
**                                                                            **
*******************************************************************************/
#if (DCM_VIN_REF_CONFIGURED == STD_ON)
FUNC(void, DCM_CODE) Dcm_FetchVin(void)
{
  /* @Trace: Dcm_SUD_API_20299 */
  Dcm_InitVinDataState();

  Dcm_DidParaConfigConstPtrType pDidCfg = Dcm_GetVinDidConfigPtr();
  if ((NULL_PTR != pDidCfg)
      && (0 < pDidCfg->ucDcmDspSignalCount))
  {
    Dcm_DidSignalConfigPtrType pSignalCfg;
    Dcm_DataConfigConstPtrType pDataCfg;

    uint8 SignalCount = pDidCfg->ucDcmDspSignalCount;
    uint8 idx;
    for (idx = 0; idx < SignalCount; idx++)
    {
      /* @Trace: Dcm_SUD_API_20301 */
      pSignalCfg = &pDidCfg->pDcmDspSignal[idx];
      pDataCfg = pSignalCfg->pDataConfig;
      boolean ChkVal = Dcm_ConditionCheckReadSignal(pDataCfg);
      CHK_NEXT(ChkVal, Dcm_ReadSignalData(pDataCfg));
      CHK_NEXT(ChkVal, Dcm_PackSignalData(pSignalCfg));

      if (DCM_FALSE == ChkVal)
      {
        /* @Trace: Dcm_SUD_API_20302 */
        break;
      }
    }

    /* @Trace: Dcm_SUD_API_20303 Dcm_SUD_API_20304 */
    Dcm_SetFetchedVinData((SignalCount == idx) ? DCM_TRUE : DCM_FALSE);
  }
}
#endif

/*******************************************************************************
** Function Name        : Dcm_GetVinDidConfigPtr                              **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Function to get DID configuration of DcmVinRef refer**
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pDidCfg                                             **
**                                                                            **
** Return parameter     : Dcm_DidParaConfigConstPtrType                       **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
#if (DCM_VIN_REF_CONFIGURED == STD_ON)
static FUNC(Dcm_DidParaConfigConstPtrType, DCM_CODE) Dcm_GetVinDidConfigPtr(void)
{
  Dcm_DidParaConfigConstPtrType pDidCfg = NULL_PTR;
  Dcm_DidParaConfigConstPtrType pTempDidCfg = NULL_PTR;

  for (uint8 idx = 0; idx < DCM_NUM_OF_DIDPARACONFIG; idx++)
  {
    /* @Trace: Dcm_SUD_API_20305 */
    pTempDidCfg = &Dcm_GaaDIDParaConfig[idx];

    if ((DCM_TRUE == pTempDidCfg->blDspDidUsed)
        && (VIN_DID == pTempDidCfg->usDcmDspDidIdentifier))
    {
      /* @Trace: Dcm_SUD_API_20306 */
      pDidCfg = pTempDidCfg;
      break;
    }
  }

  return pDidCfg;
}

/*******************************************************************************
** Function Name        : Dcm_ConditionCheckReadSignal                        **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Function check condition to read DID signal         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pDataCfg                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_ConditionCheckReadSignal(Dcm_DataConfigConstPtrType pDataCfg)
{
  /* @Trace: Dcm_SUD_API_20307 */
  boolean ChkVal = DCM_FALSE;

  if ((NULL_PTR != pDataCfg)
      && (NULL_PTR != pDataCfg->pConditionCheckReadSyncFun))
  {
    Dcm_NegativeResponseCodeType ErrorCode = DCM_POS_RESP;
    Std_ReturnType RetVal = pDataCfg->pConditionCheckReadSyncFun(&ErrorCode);

    /* @Trace: Dcm_SUD_API_20308 Dcm_SUD_API_20309 */
    ChkVal = (RetVal == E_OK) ? DCM_TRUE : DCM_FALSE;
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_ReadSignalData                                  **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Function Read DID signal which DcmVinRef reference  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pDataCfg                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_ReadSignalData(Dcm_DataConfigConstPtrType pDataCfg)
{
  /* @Trace: Dcm_SUD_API_20310 */
  boolean ChkVal = DCM_FALSE;

  if ((NULL_PTR != pDataCfg)
      && (NULL_PTR != pDataCfg->pReadDataSyncFun))
  {
    Std_ReturnType RetVal = pDataCfg->pReadDataSyncFun(Dcm_GaaDidReadSignalData);

    /* @Trace: Dcm_SUD_API_20311 Dcm_SUD_API_20312 */
    ChkVal = (RetVal == E_OK) ? DCM_TRUE : DCM_FALSE;
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_PackSignalData                                  **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Function packet DID data which DcmVinRef reference  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pSignalCfg                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : Global Variable(s) :Dcm_VinState                    **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
/* polyspace +1 MISRA2012:8.13 [Justified:Low] Justify with annotations */
static FUNC(boolean, DCM_CODE) Dcm_PackSignalData(Dcm_DidSignalConfigPtrType pSignalCfg)
{
  /* @Trace: Dcm_SUD_API_50904 */
  boolean ChkVal = DCM_FALSE;
  Dcm_DataConfigConstPtrType pDataCfg = pSignalCfg->pDataConfig;

  if ((NULL_PTR != pSignalCfg)
      && (NULL_PTR != pDataCfg)
      && (pSignalCfg->ucPackFuncIndex < DCM_NUM_OF_PACK_FUNC_CONFIG))
  {
    /* @Trace: Dcm_SUD_API_20313 */
    Dcm_PackUnPackType LddPackSignal;
    LddPackSignal.usSignalSize = pDataCfg->usDcmDspDataByteSize;
    LddPackSignal.blByteConversion = pSignalCfg->blByteConversion;

    Dcm_Uint8PtrType pDst = &Dcm_VinState.Data[pSignalCfg->usByteOffset];
    Dcm_Uint8PtrType pSrc = Dcm_GaaDidReadSignalData;
    Dcm_GaaPackFunc[pSignalCfg->ucPackFuncIndex].pPackFunc(pSrc, pDst, &LddPackSignal);

    ChkVal = DCM_TRUE;
  }

  return ChkVal;
}

/*******************************************************************************
** Function Name        : Dcm_InitVinDataState                                **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Function Init Vin State                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : Global Variable(s) :Dcm_VinState                    **
**                                                                            **
**                        Function(s) : Dcm_SetFetchedVinData                 **
**                                      Dcm_MemClear                          **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_InitVinDataState(void)
{
  /* @Trace: Dcm_SUD_API_20314 */
  Dcm_SetFetchedVinData(DCM_FALSE);
  Dcm_MemClear(Dcm_VinState.Data, VIN_DATA_LEN);
}

/*******************************************************************************
** Function Name        : Dcm_IsVinDataFetched                                **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Function check Vin Data fected                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                                                                            **
**                        Function(s) : Dcm_GetFetchedVinData                 **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_IsVinDataFetched(void)
{
  /* @Trace: Dcm_SUD_API_20315 */
  uint8 RetVal;
  RetVal = Dcm_GetFetchedVinData();
  return RetVal;
}

/*******************************************************************************
** Function Name        : Dcm_GetFetchedVinData                               **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Function get status of Fetched Vin Data             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : boolean                                             **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_VinState                   **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
static FUNC(boolean, DCM_CODE) Dcm_GetFetchedVinData(void)
{
  /* @Trace: Dcm_SUD_API_20316 */
  return Dcm_VinState.Fetched;
}

/*******************************************************************************
** Function Name        : Dcm_SetFetchedVinData                               **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : Function set status of Fetched Vin Data             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : FetchedVinData                                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : Dcm_Init should be called before calling this       **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_VinState                   **
**                                                                            **
**                        Function(s) :                                       **
**                                                                            **
*******************************************************************************/
static FUNC(void, DCM_CODE) Dcm_SetFetchedVinData(boolean FetchedVinData)
{
  /* @Trace: Dcm_SUD_API_20317 */
  Dcm_VinState.Fetched = FetchedVinData;
}
#endif

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
