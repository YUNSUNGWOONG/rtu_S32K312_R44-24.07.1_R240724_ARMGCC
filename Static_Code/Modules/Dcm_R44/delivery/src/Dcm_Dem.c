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
**  SRC-MODULE: Dcm_Dem.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Communication Manager Module               **
**                                                                            **
**  PURPOSE   : Provided API for Roe feature                                  **
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
** 0.0.1     31-Dec-2019   LamNV10        AR440 Implementation                **
** 0.0.2     13-Oct-2020   LanhLT         Changes made as per #15766          **
** 0.0.3     04-Dec-2020   HueKM          Polyspace fixing as per #15175      **
** 0.0.4     16-Dec-2020   HueKM          Mapping SUD API ID as per #17448    **
** 1.0.12    30-Jun-2023   SY Kim         Refer #CP44-2255                    **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dcm.h"
#if (DCM_DEM_CONFIGURED == STD_ON)
#include "Dcm_Ram.h"
#include "Dem.h"
#include "Dcm_Dem.h"
#include "Dcm_DspResponseOnEvent.h"

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define DCM_START_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Dcm_DemTriggerOnDTCStatus                           **
**                                                                            **
** Service ID           : 0x2B                                                **
**                                                                            **
** Description          : This API is triggered on changes of the UDS DTC     **
**                        status byte. It allows to trigger on ROE Event for  **
**                        subservice OnDTCStatusChanged.                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : DTC, DTCStatusOld, DTCStatusNew                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : LddReturnValue                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) : Dcm_GblRoeClearAll             **
**                                                                            **
**                        Function(s) invoked:                                **
**                                                                            **
*******************************************************************************/
FUNC(Std_ReturnType, DCM_CODE) Dcm_DemTriggerOnDTCStatus(
  uint32 DTC
  , Dem_UdsStatusByteType DTCStatusOld
  , Dem_UdsStatusByteType DTCStatusNew)
{
  #if ((DCM_RESPONSE_ON_EVENT_SERVICE == STD_ON) && \
    (DCM_ROE_ONDTCSTATUS_CHANGE_INDEX != 0xFF))
  /* @Trace: Dcm_SUD_API_00401 */
  P2CONST(Dcm_PduIdTable, AUTOMATIC, DCM_PRIVATE_CONST) LpPduIdTable;
  LpPduIdTable = &Dcm_GaaPduIdTableConfig[Dcm_GpRoeMsgContext->dcmRxPduId];

  uint8 LucNetworkId = LpPduIdTable->ComMChannelId;

  /* @Trace: SWS_Dcm_01410 SWS_Dcm_00135 */
  if ((Dcm_GaaCommMode[LucNetworkId] == DCM_FULL_COMMUNICATION)
      && (Dcm_GblRoeClearAll == DCM_FALSE)
      && (Dcm_PrtclTxBufStatus.ucClearDTCStatus == DCM_FALSE))
  {
    /* @Trace: Dcm_SUD_API_00402 */
    uint8 LucIndex = DCM_ROE_ONDTCSTATUS_CHANGE_INDEX;

    /* @Trace: SWS_Dcm_00912 SWS_Dcm_00913 */
    if ((Dcm_GddRoeRequestInfo[LucIndex].ucCurrentState == DCM_ROE_STARTED) &&
        (Dcm_GddRoeRequestInfo[LucIndex].RoeConfig.blIsOnChngOfDIDRxed == DCM_FALSE))
    {
      /* @Trace: SWS_Dcm_00914 */
      if ((DTCStatusOld & (uint8) Dcm_GddRoeRequestInfo[LucIndex].ucEventTypeRecord)
            != (DTCStatusNew & (uint8) Dcm_GddRoeRequestInfo[LucIndex].ucEventTypeRecord))
      {
        /* @Trace: Dcm_SUD_API_00404 */
        /* Store flag in case DTC status changed */
        Dcm_StoreRoeEventTriggeredInfo(LucIndex);
      }
    }
  }
  #else
  DCM_UNUSED(DTCStatusOld);
  DCM_UNUSED(DTCStatusNew);
  #endif
  
  DCM_UNUSED(DTC);
  return E_OK;
}

#define DCM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* #if (DCM_DEM_CONFIGURED == STD_ON) */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
