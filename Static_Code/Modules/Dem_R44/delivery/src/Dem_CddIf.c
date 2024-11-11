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
**  SRC-MODULE: Dem_CddIf.c                                                   **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Diagnostic Event Manager                              **
**                                                                            **
**  PURPOSE   : Provision of CDD interface Functionality                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By            Description                          **
********************************************************************************
** 1.0.1.0   07-May-2021   HaoLT6        R44-Redmine #18724                   **
** 1.0.0     26-Feb-2021   EK Kim        Initial version                      **
** 1.0.16    09-Nov-2023   DanhTQ1       Refer [BUGCLASSIC-885]               **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Dem.h"
#include "Dem_Ram.h"
#if (DEM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"
#endif
#include "NvM.h"              /* NVRAM manager symbols Header File */

#include "SchM_Dem.h"
#include "Rte_Dem.h"

#include "Dem_NvData.h"
#include "Dem_Event.h"
#include "Dem_EventRelatedData.h"
#include "Dem_EventCallback.h"
#include "Dem_Indicator.h"
#include "Dem_EventDebounce.h"
#include "Dem_Dtc.h"
#include "Dem_EventAging.h"
#include "Dem_EventMemory.h"


/* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations>
 * Not a defect */


/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

#define DEM_START_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Dem_CddClearDTC                                     **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This API shall be used to clear single DTC's as     **
**                        well as group of DTC's                              **
**                                                                            **
** Sync/Async           : Synchronous/Asynchronous                            **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ClientId                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : The API Dem_PreInit(), Dem_Init()                   **
**                        should have been called in sequence                 **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: Dem_SUD_MACRO_045 */
/* polyspace +2 MISRA-C3:8.4 [Justified:Low] Justify with annotations */
FUNC(Std_ReturnType, DEM_CODE) Dem_CddClearDTC(uint8 ClientId)
{

  Std_ReturnType LddRetVal = DEM_CLEAR_FAILED;

  SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();
  /* @Trace: Dem_SUD_API_21051 */
  #if (DEM_NUMBER_OF_DEM_CLIENT > DEM_ZERO)
  if (ClientId >= DEM_NUMBER_OF_DEM_CLIENT)
  { /* @Trace: Dem_SUD_API_21057 */
    /*LddRetVal = DEM_CLEAR_FAILED;*/
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
  }
  else
  /* @Trace: Dem_SUD_API_20002 */
  #endif

  if ((DEM_CLEARDTC_STATE_USER_DCM == Dem_ClearDtcState[ClientId].cds_User) ||
    (DEM_CLEARDTC_STATE_USER_J1939DCM == Dem_ClearDtcState[ClientId].cds_User))
  {
	  /* @Trace: Dem_SUD_API_21052 */
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    LddRetVal = DEM_PENDING; /* It means 'busy' state */
  }
  else /* DEM_CLEARDTC_STATE_USER_CDD or IDLE */
  {
    /* @Trace: Dem_SUD_API_21054 */
    Dem_ClearDtcState[ClientId].cds_User = DEM_CLEARDTC_STATE_USER_CDD;
    /* @Trace: Dem_SUD_API_21053 */
    #if (DEM_J1939_CLEAR_DTC_SUPPORT == STD_ON)
    /* @Trace: Dem_SUD_API_20001 */
    Dem_ClearDtcState[ClientId].cds_DTCTypeFilter = DEM_ZERO;   /* Not used */
    #endif
    SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    
    LddRetVal = Dem_InternalClearDTC(
        ClientId,
        Dem_ClientSelectDtcState[ClientId].selectedDTC,
        Dem_ClientSelectDtcState[ClientId].selectedDTCFormat,
        Dem_ClientSelectDtcState[ClientId].selectedDTCOrigin);
    /* @Trace: Dem_SUD_API_21055 */
    if (DEM_PENDING != LddRetVal)
    {
      /* @Trace: Dem_SUD_API_21056 */
      SchM_Enter_Dem_REQUEST_STATUS_PROTECTION();    
      Dem_ClearDtcState[ClientId].cds_User = DEM_CLEARDTC_STATE_USER_IDLE;
      SchM_Exit_Dem_REQUEST_STATUS_PROTECTION();
    }
  }

  return LddRetVal;
}

#define DEM_STOP_SEC_CODE
#include "MemMap.h"

/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations>
 * Not a defect */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

