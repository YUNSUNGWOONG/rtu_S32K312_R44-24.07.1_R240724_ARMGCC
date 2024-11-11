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
**  SRC-MODULE:   LinTrcv.c                                                   **
**                                                                            **
**  TARGET    :   MC33661                                                     **
**                                                                            **
**  PRODUCT   :   AUTOSAR LIN Transceiver Driver                              **
**                                                                            **
**  PURPOSE   :   APIs Implementation for LinTrcv module                      **
**                LinTrcv_Init                                                **
**                LinTrcv_GetVersionInfo                                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: yes                                          **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                  By           Description              **
********************************************************************************
** 1.0.7          08-Apr-2024           YB Song      #CP44-7310               **
** 1.0.5          17-May-2023           KhaLN1       #CP44-2131               **
** 1.0.4          11-Jan-2023           KhaLN1       #CP44-1198, #CP44-1381   **
** 1.0.3.1        01-Nov-2022           KhaLN1       #CP44-565, #CP44-801     **
** 1.0.2          17-May-2022           DuyNHP2      R44-Redmine #20124       **
** 1.0.0          22-Dec-2020           SJ Kim       Initial Version          **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
 /* @Trace: SRS_BSW_00301 SRS_BSW_00409 SRS_BSW_00361 SRS_BSW_00413 */
 /* @Trace: LinTrcv_SUD_FILE_001 */
#include "LinTrcv.h"             /* Module Header file */
#if (STD_ON == LINTRCV_DEV_ERROR_DETECT)
#include "Det.h"                 /* Det header file */
#endif
#include "LinTrcv_ModeCtrl.h"    /* LinTrcv Internal functions header file */

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
 **                      Function Definitions                                 **
 ******************************************************************************/

/*******************************************************************************
** Function Name        : LinTrcv_Init                                        **
**                                                                            **
** Service ID           : 0x00                                                **
**                                                                            **
** Description          : Initializes the Lin Transceiver Driver module.      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
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
** Remarks              : Global Variable(s)  : LinTrcv_GblInitStatus         **
**                                              LinTrcv_GaaNetworkInfo[]      **
**                                              LinTrcv_GaaNetworkRamData[]   **
**                        Function(s) invoked :  EcuM_SetWakeupEvent(),       **
**                        LinTrcv_SetNormalMode(), Dio_ReadChannel(),         **
**                        LinTrcv_SetSleepMode(),LinTrcv_SetStandByMode()     **
*******************************************************************************/
/* @Trace: SWS_LinTrcv_00001 SWS_LinTrcv_00173 SWS_LinTrcv_00119
 * SWS_LinTrcv_00099 SWS_LinTrcv_00066 SRS_BSW_00101 SRS_BSW_00371 SRS_BSW_00414 SRS_BSW_00358 SRS_Can_01096 SRS_Can_01097 
 * SRS_Lin_01514 SRS_Lin_01563
 */
#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
/* polyspace +1 CODE-METRICS:LEVEL [Reviewed:Low] "CONDITIONAL PASS" */
FUNC(void, LINTRCV_CODE) LinTrcv_Init(const LinTrcv_ConfigType* ConfigPtr)
{
  
  /* @Trace: LinTrcv_SUD_API_001 */
  P2CONST(LinTrcv_ConfigType, AUTOMATIC, LINTRCV_CONST) LpLinTrcvConfigPtr;
  P2VAR(LinTrcv_NetworkRamData, AUTOMATIC, LINTRCV_VAR) LpLinTrcvNetworkRamData;
  VAR (LinTrcv_TrcvModeType, LINTRCV_VAR) LddCurrentOpMode;
  VAR (uint8, LINTRCV_VAR) LucLinNetwork;

  #if (STD_ON == LINTRCV_WAKEUP_SUPPORT)
  Dio_LevelType LddDioReturnvalueRxD;
  #endif

  /* Initialize the Lin network value to zero */
  LucLinNetwork = LINTRCV_ZERO;

  #if (STD_ON == LINTRCV_DEV_ERROR_DETECT)
  if (ConfigPtr != NULL_PTR)
  { 
    /* @Trace: SRS_BSW_00327 SRS_BSW_00385 SRS_BSW_00386 */
    /* @Trace: LinTrcv_SUD_API_002*/
    (void)Det_ReportError(LINTRCV_MODULE_ID, LINTRCV_INSTANCE_ID,
                LINTRCV_INIT_SID, LINTRCV_E_PARAM_POINTER);
  }
  else
  #endif
  {
    /* @Trace: SRS_BSW_00414 */
   /* @Trace: LinTrcv_SUD_API_003*/ 
    UNUSED(ConfigPtr);
    #if (LINTRCV_ONE < LINTRCV_NUM_OF_NETWORKS)
    /* Loop for initializing all the configured LIN Transceiver Driver networks */
    do
    {
    #endif /* (LINTRCV_ONE < LINTRCV_NUM_OF_NETWORKS) */
    /* @Trace: LinTrcv_SUD_API_004*/ 
      /* Get the pointer to the structure of first network */
      LpLinTrcvConfigPtr = &LinTrcv_GaaNetworkInfo[LucLinNetwork];
      /* Get the pointer to the Ram data structure of first network */
      LpLinTrcvNetworkRamData = &LinTrcv_GaaNetworkRamData[LucLinNetwork];

      /* Check if the channel is used */
      /* polyspace-begin RTE:UNR [Justified:Low] "It has covered by App_LinIf_Init" */
      if (LINTRCV_TRUE == LpLinTrcvConfigPtr->blChannelUsed)
      {
        /* Get the current configured Operation mode into a local variable */
        #if (STD_ON == LINTRCV_WAKEUP_SUPPORT)
        /* Check if wake up by bus is used */
        if (LINTRCV_TRUE == LpLinTrcvConfigPtr->blLinTrcvWakeupByBusUsed)
        {
      /* @Trace: LinTrcv_SUD_API_005*/ 
          /* Invoke function to read the value of the ddRxDPin for wake up */
          LddDioReturnvalueRxD = LinTrcv_ReadDioConfigType(
                                  LpLinTrcvConfigPtr->ddRxDPin);

          /* check if the Dio return value is LOW */
          if ((Dio_LevelType)STD_LOW == LddDioReturnvalueRxD)
          {
        /* @Trace: LinTrcv_SUD_API_006*/ 
            /* Report Wake-up detection to the EcuM */
            EcuM_SetWakeupEvent(LpLinTrcvConfigPtr->ddWakeupSourceId);
            /* Report Wake-up detection to the LinIf */
            LinIf_WakeupConfirmation(LpLinTrcvConfigPtr->ddWakeupSourceId);
            /* Set the current Operation mode as Standby */
            LpLinTrcvNetworkRamData->ddOpMode =
                (LinTrcv_TrcvModeType)LINTRCV_TRCV_MODE_STANDBY;
          }
        }
        #endif

        /* Check if the LIN Transceiver Driver is previously uninitialized*/
        if (LINTRCV_UNINIT == LinTrcv_GblInitStatus)
        {
      /* @Trace: LinTrcv_SUD_API_007*/
          /* HW power-up is Standby, Invoke the function to set
           * LIN Transceiver Driver to normal mode */
          LinTrcv_SetNormalMode(LucLinNetwork);
          /* Invoke the function to set LIN Transceiver Driver to Sleep mode */
          LinTrcv_SetSleepMode(LucLinNetwork);
        }
        else
        {
      /* @Trace: LinTrcv_SUD_API_008*/
          /* Get the current Operation mode of LIN Transceiver Driver */
          LddCurrentOpMode = LpLinTrcvNetworkRamData->ddOpMode;

          /* Check if current mode is normal */
          if (LINTRCV_TRCV_MODE_NORMAL == LddCurrentOpMode)
          {
        /* @Trace: LinTrcv_SUD_API_009*/
            /* Invoke the function to set LIN Transceiver Driver to sleep mode */
            LinTrcv_SetSleepMode(LucLinNetwork);
          }
          /* Check if current mode is standby */
          else if (LINTRCV_TRCV_MODE_STANDBY == LddCurrentOpMode)
          {
        /* @Trace: LinTrcv_SUD_API_010*/
            /* Invoke the function to set LIN Transceiver Driver to normal mode */
            LinTrcv_SetNormalMode(LucLinNetwork);
            /* Invoke the function to set LIN Transceiver Driver to Sleep mode */
            LinTrcv_SetSleepMode(LucLinNetwork);
          }
          else
          {
            /* do nothing */
          }
        }
      }
      /* polyspace-end RTE:UNR [Justified:Low] "It has covered by App_LinIf_Init" */
    #if (LINTRCV_ONE < LINTRCV_NUM_OF_NETWORKS)
    /* @Trace: LinTrcv_SUD_API_011*/
      /* Increment the network number */
      LucLinNetwork++;
    }while (LINTRCV_NUM_OF_NETWORKS > LucLinNetwork);
    #endif /* (LINTRCV_ONE < LINTRCV_NUM_OF_NETWORKS) */
     /* @Trace: LinTrcv_SUD_API_012*/
    /* Set the global variable for init status to 'initialized' */
    LinTrcv_GblInitStatus = LINTRCV_INIT;
  }
}
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : LinTrcv_GetVersionInfo                              **
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : This service provides the version information of    **
**                        this module through the parameter "versioninfo".    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : versioninfo                                         **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                        Function(s) invoked : Det_ReportError()             **
 ******************************************************************************/
/* @Trace: SWS_LinTrcv_00008 SWS_LinTrcv_00131 SWS_LinTrcv_00134 SRS_BSW_00369
 * SRS_BSW_00406 SRS_BSW_00407 SRS_BSW_00371

 */
#if (STD_ON == LINTRCV_GET_VERSION_INFO)
#define LINTRCV_START_SEC_CODE
#include "MemMap.h"
FUNC(void, LINTRCV_CODE) LinTrcv_GetVersionInfo
(P2VAR(Std_VersionInfoType, AUTOMATIC, LINTRCV_APPL_DATA) versioninfo)
{
  /* Check whether the versioninfo is equal to null pointer */
  if (NULL_PTR != versioninfo)
  {
    /* @Trace: LinTrcv_SUD_API_052*/
    /* Copy the vendor Id */
    /* @Trace: SRS_BSW_00347 */
  /* polyspace +1 MISRA-C3:D4.14 [Not a defect:Low] "Pointer is checked by generator, it can't be null" */
    versioninfo->vendorID = LINTRCV_VENDOR_ID;
    /* Copy the module Id */
    versioninfo->moduleID = LINTRCV_MODULE_ID;
    /* Copy Software Major Version */
    versioninfo->sw_major_version = (uint8)LINTRCV_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    versioninfo->sw_minor_version = (uint8)LINTRCV_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    versioninfo->sw_patch_version = (uint8)LINTRCV_SW_PATCH_VERSION;
  }
  else
  {
    #if (STD_ON == LINTRCV_DEV_ERROR_DETECT)
  /* @Trace: SRS_BSW_00327 SRS_BSW_00385 SRS_BSW_00386 */
  /* @Trace: LinTrcv_SUD_API_053*/
    /* polyspace MISRA-C3:D4.14 [Not a defect:Low]. Jufify: "The pointer has checked for not NULL." */
    /* Report to DET */
    (void)Det_ReportError(LINTRCV_MODULE_ID, LINTRCV_INSTANCE_ID,
    LINTRCV_GETVERSIONINFO_SID, LINTRCV_E_PARAM_POINTER);
    #endif /* #if(STD_ON == LINTRCV_DEV_ERROR_DETECT) */
  }
}
#define LINTRCV_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
