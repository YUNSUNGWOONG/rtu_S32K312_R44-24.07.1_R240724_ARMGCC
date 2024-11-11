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
**  SRC-MODULE: CanIf_CanTrcv.c                                               **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Provision of Can Transceiver functionality                    **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
*******************************************************************************/
/*******************************************************************************
** Revision  Date          By             Description                         **
********************************************************************************
** 1.1.0     29-Feb-2024   Jh Yang        #CP44-2947                          **
** 1.0.9     03-Oct-2022   HieuTM8        #CP44-832                           **
** 1.0.5     30-Jun-2022   HieuTM8        #CP44-130                           **
** 1.0.2     04-Apr-2022   JW Oh          #25353                              **
** 1.0.1     22-Sep-2021   HieuTM8        #20891                              **
** 1.0.0     21-Dec-2020   SJ Kim         Initialization                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf.h"               /* CanIf header file */
#if (STD_ON == CANIF_CANTRCV_SUPPORT)
#include "CanIf_Ram.h"           /* CanIf RAM header file */
#include "CanIf_PCTypes.h"       /* Pre-compile time header file */
#include "CanSM_CanIf.h"         /* CanIf call back header file */
#include "CanIf_Error.h"         /* CanIf DET header file */
#include "CanIf_UserInc.h"       /* CanIf User Included header file */
#include "SchM_CanIf.h"          /* CanIf SchM header file */
#include "CanIf_Cbk.h"           /* CanIf Callback header file */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANIF_CANTRCV_C_AR_RELEASE_MAJOR_VERSION    4
#define CANIF_CANTRCV_C_AR_RELEASE_MINOR_VERSION    4
#define CANIF_CANTRCV_C_AR_RELEASE_REVISION_VERSION 0

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANIF_CANTRCV_H_AR_RELEASE_MAJOR_VERSION != \
  CANIF_CANTRCV_C_AR_RELEASE_MAJOR_VERSION)
  #error "CANIF_CANTRCV.c : Mismatch in Specification Major Version"
#endif
#if (CANIF_CANTRCV_H_AR_RELEASE_MINOR_VERSION != \
  CANIF_CANTRCV_C_AR_RELEASE_MINOR_VERSION)
  #error "CANIF_CANTRCV.c : Mismatch in Specification Minor Version"
#endif
#if (CANIF_CANTRCV_H_AR_RELEASE_REVISION_VERSION != \
  CANIF_CANTRCV_C_AR_RELEASE_REVISION_VERSION)
  #error "CANIF_CANTRCV.c : Mismatch in Specification Revision Version"
#endif
#endif

/* polyspace-begin RTE:UNR [No action planned:Low] "It's depends on the configuration of CanIf. No impact" */ 
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : CanIf_SetTrcvMode                                   **
**                                                                            **
** Service ID           : 0x0d                                                **
**                                                                            **
** Description          : This service changes the operation mode of          **
**                        the tansceiver TransceiverId, via calling           **
**                        the corresponding CAN Transceiver Driver service.   **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : TransceiverId, TransceiverMode                      **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : CanIf module must be initialized                    **
**                                                                            **
** Remarks              : Global Variable(s)     : CanIf_CanTrcv,             **
**                                                 CanIf_OperMode             **
**                                                 CanIf_CanTrcvDriver        **
**                                                 CanIf_CanIfStatus          **
**                        Function(s) invoked    : CanTrcv_SetOpMode,         **
**                                                 Det_ReportError            **
*******************************************************************************/
#if (STD_ON == CANIF_CANTRCV_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00323 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetTrcvMode (
                           VAR(uint8, CANIF_VAR) TransceiverId,
                           VAR(CanTrcv_TrcvModeType, CANIF_VAR) TransceiverMode)
{
  /* @Trace: CanIf_SUD_API_069 */
  /* @Trace: SWS_CANIF_00287 */
  VAR(Std_ReturnType, CANIF_VAR) retVal;

  #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
  P2CONST(CanIf_CanTrcvDriverType, AUTOMATIC, CANIF_CONST) ptrCanTrcvDriver;
  P2CONST(CanIf_TransceiverConfigType, AUTOMATIC, CANIF_CONST) ptrCanTrcv;
  #endif/* #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT) */

  #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
  /* Get the pointer to corresponding Can Transceiver Channel structure  */
  ptrCanTrcv = &CanIf_CanTrcv[TransceiverId];
  #endif

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  /* Initialize the Standard Return Value with E_OK */
  retVal = (uint8) E_OK;

  /* Report to DET, if module is not initialized  */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_SET_TRCV_MODE_SID, retVal);

  /* Report to DET, if Transceiver Id is out of range  */
  /* @Trace: CanIf_SUD_API_070 */
  /* @Trace: SWS_CANIF_00538 */
  CANIF_TRANSCEIVERID_RANGE_ERROR(CANIF_SET_TRCV_MODE_SID, retVal);

  /* Report to DET, if Transceiver Id is out of range  */ 
  /* Polyspace +2 RTE:UNR [Not a defect:Low] "it's to cover autosar requirement when error occurs & reduce length of code" */ 
  /* @Trace: SWS_CANIF_00648 */  
  CANIF_TRCV_MODE_INVALID_ERROR(CANIF_SET_TRCV_MODE_SID, TransceiverMode, retVal); 

  /* Is any DET error invoked */
  if ((uint8) E_OK == retVal)
  #endif /* #if (STD_ON == CANIF_DEV_ERROR_DETECT) */
  {
    #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
    /* Get the pointer to corresponding Can Transceiver Driver structure  */
    ptrCanTrcvDriver = &CanIf_CanTrcvDriver[ptrCanTrcv->CanTrcvDriverId];

    /* Invoke corresponding Driver function  */
    /* @Trace: CanIf_SUD_API_071 */    
    /* @Trace: SWS_CANIF_00358 */
    retVal = ptrCanTrcvDriver->CanTrcvSetOpMode(ptrCanTrcv->CanTrcvId,
                                                               TransceiverMode);
    #else
    /* Invoke CanTrcv_SetOpMode function  */
    /* @Trace: CanIf_SUD_API_072 */
    /* @Trace: SWS_CANIF_00358 */
    retVal = CanTrcv_SetOpMode(TransceiverId, TransceiverMode);
    #endif/*#if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT) */

    #if (STD_ON == CANIF_DEV_ERROR_DETECT)
    /* Store the current requested mode */
    CanIf_OperMode[TransceiverId] = (uint8)TransceiverMode;
    #endif/* #if (STD_ON == CANIF_DEV_ERROR_DETECT) */
  }
  return(retVal);
}

#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif/* #if (STD_ON == CANIF_CANTRCV_SUPPORT) */

/*******************************************************************************
** Function Name        : CanIf_GetTrcvMode                                   **
**                                                                            **
** Service ID           : 0x0e                                                **
**                                                                            **
** Description          : This function invokes CanTrcv_GetOpMode and updates **
**                        the parameter TransceiverModePtr with the value     **
**                        OpMode provided by CanTrcv.                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : TransceiverId                                       **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : TransceiverModePtr                                  **
**                                                                            **
** Return value         : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : CanIf module must be initialized                    **
**                                                                            **
** Remarks              : Global Variable(s) : CanIf_CanTrcv,                 **
**                                             CanIf_CanTrcvDriver            **
**                                             CanIf_CanIfStatus              **
**                        Function(s) invoked: CanTrcv_GetOpMode              **
**                                             Det_ReportError                **
*******************************************************************************/
#if (STD_ON == CANIF_CANTRCV_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00323 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetTrcvMode (
            VAR(uint8, CANIF_VAR) TransceiverId,
            P2VAR(CanTrcv_TrcvModeType, AUTOMATIC, CANIF_VAR)TransceiverModePtr)
{
  /* @Trace: CanIf_SUD_API_129 */
  /* @Trace: SWS_CANIF_00288 */
  #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
  P2CONST(CanIf_CanTrcvDriverType, AUTOMATIC, CANIF_CONST) ptrCanTrcvDriver;
  P2CONST(CanIf_TransceiverConfigType, AUTOMATIC, CANIF_CONST) ptrCanTrcv;
  #endif/* #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)*/
  VAR(Std_ReturnType, CANIF_VAR) retVal;

  #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
  /* Get the pointer to corresponding Can Transceiver Channel structure  */
  ptrCanTrcv = &CanIf_CanTrcv[TransceiverId];
  #endif
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  /* Initialize retVal with E_OK  */
  retVal = (uint8) E_OK;

  /* Report to DET, if module is not initialized  */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_GET_TRCV_MODE_SID, retVal);

  /* Report to DET, if Transceiver Id is out of range  */
  /* @Trace: CanIf_SUD_API_130 */
  /* @Trace: SWS_CANIF_00364 */
  CANIF_TRANSCEIVERID_RANGE_ERROR(CANIF_GET_TRCV_MODE_SID, retVal);

  /* Report to DET, if Transceiver Mode is Invalid  */
  /* @Trace: CanIf_SUD_API_131 */
  /* @Trace: SWS_CANIF_00650 */
  CANIF_NULL_PTR_ERROR(CANIF_GET_TRCV_MODE_SID, retVal, TransceiverModePtr);

  /* Is any DET error invoked */
  if ((uint8) E_OK == retVal)
  #endif /* #if (STD_ON == CANIF_DEV_ERROR_DETECT) */
  {
    #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
    /* Get the pointer to corresponding Can Transceiver Driver structure  */
    ptrCanTrcvDriver = &CanIf_CanTrcvDriver[ptrCanTrcv->CanTrcvDriverId];

    /* Invoke corresponding Driver function  */
    /* @Trace: CanIf_SUD_API_132 */
    /* @Trace: SWS_CANIF_00363 */
    retVal = ptrCanTrcvDriver->CanTrcvGetOpMode(ptrCanTrcv->CanTrcvId,
                                                            TransceiverModePtr);
    #else
    /* Invoke CanTrcv_GetOpMode function  */
    /* @Trace: CanIf_SUD_API_132 */
    /* @Trace: SWS_CANIF_00363 */
    retVal = CanTrcv_GetOpMode(TransceiverId, TransceiverModePtr);
    #endif/*#if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)*/
  }
  return(retVal);
}

#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif/* #if (STD_ON == CANIF_CANTRCV_SUPPORT) */

/*******************************************************************************
** Function Name        : CanIf_GetTrcvWakeupReason                           **
**                                                                            **
** Service ID           : 0x0f                                                **
**                                                                            **
** Description          : This service returns the reason for the wake up     **
**                        of the transceiver TransceiverId, via calling       **
**                        the corresponding CAN Transceiver Driver service.   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : TransceiverId                                       **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : TrcvWuReasonPtr                                     **
**                                                                            **
** Return value         : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : CanIf module must be initialized                    **
**                                                                            **
** Remarks              : Global Variable(s)     :    CanIf_CanTrcv           **
**                                                    CanIf_CanTrcvDriver     **
**                                                    CanIf_CanIfStatus       **
**                        Function(s) invoked    :    CanTrcv_GetBusWuReason  **
**                                                    Det_ReportError         **
*******************************************************************************/
#if (STD_ON == CANIF_TRCV_WAKEUP_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00323 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_GetTrcvWakeupReason (
       VAR(uint8, CANIF_VAR) TransceiverId,
       P2VAR(CanTrcv_TrcvWakeupReasonType, AUTOMATIC, CANIF_VAR)TrcvWuReasonPtr)
{
  /* @Trace: SWS_CANIF_00289 */
  #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
  P2CONST(CanIf_CanTrcvDriverType, AUTOMATIC, CANIF_CONST) ptrCanTrcvDriver;
  P2CONST(CanIf_TransceiverConfigType, AUTOMATIC, CANIF_CONST) ptrCanTrcv;
  #endif/* #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT) */
  VAR(Std_ReturnType, CANIF_VAR) retVal;

  #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
  /* Get the pointer to corresponding Can Transceiver Channel structure  */
  ptrCanTrcv = &CanIf_CanTrcv[TransceiverId];
  #endif

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  /* Initialize retVal with E_OK  */
  retVal = (uint8) E_OK;

  /* Report to DET, if module is not initialized  */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_GET_TRCV_WAKEUPREASON_SID, retVal);

  /* Report to DET, if Transceiver Id is out of range  */
  /* @Trace: SWS_CANIF_00537 */
  CANIF_TRANSCEIVERID_RANGE_ERROR(CANIF_GET_TRCV_WAKEUPREASON_SID, retVal);

  /* Report to DET, if Transceiver Wakeup reason is invalid  */
  /* @Trace: SWS_CANIF_00649 */
  CANIF_NULL_PTR_ERROR(CANIF_GET_TRCV_WAKEUPREASON_SID, retVal, TrcvWuReasonPtr);

  /* Check for any development error  */
  /* @Trace: CanIf_SUD_API_132 */
  if ((uint8) E_OK == retVal)
  #endif /* #if (STD_ON == CANIF_DEV_ERROR_DETECT) */
  {
    /* @Trace: CanIf_SUD_API_133 */
    #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)

    /* Get the pointer to corresponding Can Transceiver Driver structure  */
    ptrCanTrcvDriver = &CanIf_CanTrcvDriver[ptrCanTrcv->CanTrcvDriverId];

    /* Invoke corresponding Driver function  */
    /* @Trace: SWS_CANIF_00368 */
    retVal = ptrCanTrcvDriver->CanTrcvGetBusWuReason
                                      (ptrCanTrcv->CanTrcvId, TrcvWuReasonPtr);
    #else
    /* Invoke CanTrcv_GetBusWuReason function  */
    /* @Trace: SWS_CANIF_00368 */
    retVal = CanTrcv_GetBusWuReason(TransceiverId, TrcvWuReasonPtr);
    #endif/*#if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)*/
  }
  /* @Trace: CanIf_SUD_API_132 */
  
  return(retVal);
}

#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif/* #if (STD_ON == CANIF_CANTRCV_SUPPORT) */

/*******************************************************************************
** Function Name        : CanIf_SetTrcvWakeupMode                             **
**                                                                            **
** Service ID           : 0x10                                                **
**                                                                            **
** Description          : This service enables, disables and clears the       **
**                        notification for wakeup events on the addressed     **
**                        transceiver.                                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Re-entrant                                      **
**                                                                            **
** Input Parameters     : TransceiverId, TrcvWakeupMode                       **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_ReturnType (E_OK or E_NOT_OK)                   **
**                                                                            **
** Preconditions        : CanIf module must be initialized                    **
**                                                                            **
** Remarks              : Global Variable(s)  : CanIf_CanTrcv                 **
**                                              CanIf_CanTrcvDriver           **
**                                              CanIf_CanIfStatus             **
**                        Function(s) invoked : CanTrcv_SetWakeupMode         **
**                                              Det_ReportError               **
*******************************************************************************/
#if  (STD_ON == CANIF_TRCV_WAKEUP_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00323 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetTrcvWakeupMode (
                      VAR(uint8, CANIF_VAR) TransceiverId,
                      VAR(CanTrcv_TrcvWakeupModeType, CANIF_VAR) TrcvWakeupMode)
{
  /* @Trace: CanIf_SUD_API_073 */
  /* @Trace: SWS_CANIF_00290 */
  VAR(Std_ReturnType, CANIF_VAR) retVal;

  #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
  P2CONST(CanIf_CanTrcvDriverType, AUTOMATIC, CANIF_CONST) ptrCanTrcvDriver;
  P2CONST(CanIf_TransceiverConfigType, AUTOMATIC, CANIF_CONST) ptrCanTrcv;
  #endif/* #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT) */

  #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
  /* Get the pointer to corresponding Can Transceiver Channel structure  */
  ptrCanTrcv = &CanIf_CanTrcv[TransceiverId];
  #endif

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  /* Initialize retVal with E_OK  */
  retVal = (uint8) E_OK;

  /* Report to DET, if module is not initialized  */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_SET_TRCV_WAKEUP_MODE_SID, retVal);

  /*  Report to DET, if Transceiver Id is out of range   */
  /* @Trace: CanIf_SUD_API_074 */
  /* @Trace: SWS_CANIF_00535 */
  CANIF_TRANSCEIVERID_RANGE_ERROR(CANIF_SET_TRCV_WAKEUP_MODE_SID, retVal);

  /* Report to DET, if Transceiver Wakeup mode is invalid  */  
  /* Polyspace +6 RTE:UNR [Not a defect:Low] "SWS_CANIF_00536" */
  /* "for Checking TrcvWakeupMode As valid values of TrcvWakeupMode are of enum type, 
   * TrcvWakeupMode can't have values other than defined values. 
   * If such scenarios occurrs it will be taken care by DET check" */
  /* @Trace: CanIf_SUD_API_075 */
  /* @Trace: SWS_CANIF_00536 */
  CANIF_INVALID_TRCV_WAKEUPMODE_ERROR(CANIF_SET_TRCV_WAKEUP_MODE_SID, retVal); 

  /* Is any DET error invoked */
  if ((uint8) E_OK == retVal)
  #endif /* #if (STD_ON == CANIF_DEV_ERROR_DETECT)) */
  {
    if (CanIf_TrcvMode[TransceiverId] != (uint8)TrcvWakeupMode)
    {
      #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
      /* Get the pointer to corresponding Can Transceiver Driver structure  */
      ptrCanTrcvDriver = &CanIf_CanTrcvDriver[ptrCanTrcv->CanTrcvDriverId];

      /* Invoke corresponding Driver function  */
      /* @Trace: CanIf_SUD_API_076 */
      /* @Trace: SWS_CANIF_00372 */
      retVal = ptrCanTrcvDriver->CanTrcvSetWakeupMode
                                      (ptrCanTrcv->CanTrcvId, TrcvWakeupMode);

      /* Store the Transceiver mode in CanIf_TrcvMode array */
      CanIf_TrcvMode[TransceiverId] = (uint8)TrcvWakeupMode;
      #else
      /* Invoke CanTrcv_SetWakeupMode function  */
      /* @Trace: CanIf_SUD_API_076 */
      /* @Trace: SWS_CANIF_00372 */
      retVal = CanTrcv_SetWakeupMode(TransceiverId, TrcvWakeupMode);

      /* Store the Transceiver mode in CanIf_TrcvMode array */
      CanIf_TrcvMode[CANIF_ZERO] = (uint8)TrcvWakeupMode;
      #endif/*#if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)*/
    }
    else
    {
      /* @Trace: CanIf_SUD_API_151 */
      /* Set return value to E_NOT_OK */
      retVal = (uint8)E_NOT_OK;
    }
  }
  return(retVal);
}

#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif/*#if (STD_ON == CANIF_CANTRCV_SUPPORT)*/

/*******************************************************************************
** Function Name        :  CanIf_ClearTrcvWufFlag                             **
**                                                                            **
** Service ID           :  0x1e                                               **
**                                                                            **
** Description          :  This service indicates that the Transceiver has    **
**                         cleared the WufFlag                                **
**                                                                            **
** Sync/Async           :  Asynchronous                                       **
**                                                                            **
** Re-entrancy          :  Re-entrant                                         **
**                                                                            **
** Input Parameters     :  TransceiverId                                      **
**                                                                            **
** InOut Parameters     :  None                                               **
**                                                                            **
** Output Parameters    :  None                                               **
**                                                                            **
** Return value         :  None                                               **
**                                                                            **
** Preconditions        :  CanIf module must be initialized                   **
**                                                                            **
** Remarks              :  Global Variable(s) : CanIf_CanTrcv                 **
**                                              CanIf_CanTrcvDriver           **
**                                              CanIf_CanIfStatus             **
**                         Function(s) invoked: CanTrcv_ClearTrcvWufFlag      **
**                                              Det_ReportError               **
*******************************************************************************/
#if ((STD_ON == CANIF_CANTRCV_SUPPORT) && (STD_ON == CANIF_PN_SUPPORT))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_ClearTrcvWufFlag (
                                            VAR(uint8, CANIF_VAR) TransceiverId)
{
  /* @Trace: CanIf_SUD_API_097 */
  /* @Trace: SWS_CANIF_00761 */
  #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
  P2CONST(CanIf_CanTrcvDriverType, AUTOMATIC, CANIF_CONST) ptrCanTrcvDriver;
  P2CONST(CanIf_TransceiverConfigType, AUTOMATIC, CANIF_CONST) ptrCanTrcv;
  #endif/*#if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)*/

  VAR(Std_ReturnType, CANIF_VAR) retVal;

  #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
  /* Get the pointer to corresponding Can Transceiver Channel structure  */
  ptrCanTrcv = &CanIf_CanTrcv[TransceiverId];
  #endif

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  retVal = (uint8) E_OK;
  /* Check if CanIf is Initialised */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_CLEAR_TRCV_WUF_SID, retVal);

  /* Check if TRANSCEIVERID is in range */
  /* @Trace: CanIf_SUD_API_098 */
  /* @Trace: SWS_CANIF_00769 */
  CANIF_TRANSCEIVERID_RANGE_ERROR(CANIF_CLEAR_TRCV_WUF_SID, retVal);

  /* Is any DET error invoked */
  if ((uint8) E_OK == retVal)
  #endif/*#if (STD_ON == CANIF_DEV_ERROR_DETECT)*/
  {
    #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
    /* Get the pointer to corresponding Can Transceiver Driver structure  */
    ptrCanTrcvDriver = &CanIf_CanTrcvDriver[ptrCanTrcv->CanTrcvDriverId];

    /* Invoke corresponding Driver function  */
    /* @Trace: CanIf_SUD_API_099 */
    /* @Trace: SWS_CANIF_00766 */
    retVal = ptrCanTrcvDriver->ClearTrcvWufFlag(ptrCanTrcv->CanTrcvId);
    #else
    /* Invoke the CanTrcv_ClearTrcvWufFlag to clear the WUF flag */
    /* @Trace: CanIf_SUD_API_099 */
    /* @Trace: SWS_CANIF_00766 */
    retVal = CanTrcv_ClearTrcvWufFlag(TransceiverId);
    #endif/*#if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)*/
  }
  return (retVal);
}

#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif/*#if ((STD_ON == CANIF_CANTRCV_SUPPORT) && (...)*/

/*******************************************************************************
** Function Name        :  CanIf_CheckTrcvWakeFlag                            **
**                                                                            **
** Service ID           :  0x1f                                               **
**                                                                            **
** Description          :  Request the CanIf module to check the wake flag    **
**                         of the designated CAN Transceiver                  **
**                                                                            **
** Sync/Async           :  Asynchronous                                       **
**                                                                            **
** Re-entrancy          :  Reentrant for different CAN Transceiver            **
**                                                                            **
** Input Parameters     :  TransceiverId                                      **
**                                                                            **
** InOut Parameters     :  None                                               **
**                                                                            **
** Output Parameters    :  None                                               **
**                                                                            **
** Return value         :  Std_ReturnType (E_OK or E_NOT_OK)                  **
**                                                                            **
** Preconditions        :  CanIf module must be initialized                   **
**                                                                            **
** Remarks              :  Global Variable(s) :CanIf_CanTrcv                  **
**                                             CanIf_CanTrcvDriver            **
**                                             CanIf_CanIfStatus              **
**                         Function(s) invoked:CanTrcv_CheckWakeFlag          **
**                                             Det_ReportError                **
*******************************************************************************/
#if ((STD_ON == CANIF_CANTRCV_SUPPORT) && (STD_ON == CANIF_PN_SUPPORT))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(Std_ReturnType, CANIF_CODE) CanIf_CheckTrcvWakeFlag (
                                            VAR(uint8, CANIF_VAR) TransceiverId)
{
  /* @Trace: CanIf_SUD_API_083 */
  /* @Trace: SWS_CANIF_00761 */
  #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
  P2CONST(CanIf_CanTrcvDriverType, AUTOMATIC, CANIF_CONST) ptrCanTrcvDriver;
  P2CONST(CanIf_TransceiverConfigType, AUTOMATIC, CANIF_CONST) ptrCanTrcv;
  #endif/*#if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)*/

  VAR(Std_ReturnType, CANIF_VAR) retVal;

  #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
  /* Get the pointer to corresponding Can Transceiver Channel structure  */
  ptrCanTrcv = &CanIf_CanTrcv[TransceiverId];
  #endif

  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  retVal = (uint8) E_OK;

  /* Check if CanIf is Initialised */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_CHECK_TRCV_WAKE_SID, retVal);
  /* @Trace: CanIf_SUD_API_084 */  
  /* Check if TRANSCEIVERID is in range */
  /* @Trace: SWS_CANIF_00770 */
  CANIF_TRANSCEIVERID_RANGE_ERROR(CANIF_CHECK_TRCV_WAKE_SID, retVal);

  /* Is any DET error invoked */
  if ((uint8) E_OK == retVal)
  #endif/* #if (STD_ON == CANIF_DEV_ERROR_DETECT) */
  {
    #if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)
    /* Get the pointer to corresponding Can Transceiver Driver structure  */
    ptrCanTrcvDriver = &CanIf_CanTrcvDriver[ptrCanTrcv->CanTrcvDriverId];
    /* @Trace: CanIf_SUD_API_085 */
    /* Invoke corresponding Driver function */
    /* @Trace: SWS_CANIF_00765 */
    retVal = ptrCanTrcvDriver->CheckWakeFlag(ptrCanTrcv->CanTrcvId);
    #else
    /* Invoke CanTrcv_CheckWakeFlag function  */
    /* @Trace: CanIf_SUD_API_085 */
    /* @Trace: SWS_CANIF_00765 */
    retVal = CanTrcv_CheckWakeFlag(TransceiverId);
    #endif/*#if (STD_ON == CANIF_MULTIPLE_TRCVDRV_SUPPORT)*/
  }
  return (retVal);
}

#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif/*#if ((STD_ON == CANIF_CANTRCV_SUPPORT) && (...))*/

/*******************************************************************************
** Function Name        :  CanIf_CheckTrcvWakeFlagIndication                  **
**                                                                            **
** Service ID           :  0x21                                               **
**                                                                            **
** Description          :  This service indicates that the check of           **
**                         the transceiver's wake-up flag has been finished   **
**                         by the corresponding CAN transceiver with          **
**                         the abstract CanIf TransceiverId. This indication  **
**                         is used to cope with the asynchronous              **
**                         transceiver communication.                         **
**                                                                            **
** Sync/Async           :  Synchronous                                        **
**                                                                            **
** Re-entrancy          :  Reentrant                                          **
**                                                                            **
** Input Parameters     :  TransceiverId                                      **
**                                                                            **
** InOut Parameters     :  None                                               **
**                                                                            **
** Output Parameters    :  None                                               **
**                                                                            **
** Return value         :  None                                               **
**                                                                            **
** Preconditions        :  CanIf module must be initialized                   **
**                                                                            **
** Remarks              :  Global Variable(s): CanIf_CanIfStatus              **
**                                                                            **
**                         Function(s) invoked: Det_ReportError               **
**                                              CanSM/Cdd_CheckTrcvWakeFlag   **
**                                              Indication                    **
*******************************************************************************/
#if ((STD_ON == CANIF_PN_SUPPORT) && (STD_ON == CANIF_CANTRCV_SUPPORT))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANIF_CODE) CanIf_CheckTrcvWakeFlagIndication (
                                            VAR(uint8, CANIF_VAR) TransceiverId)
{
  /* @Trace: CanIf_SUD_API_086 */
  /* @Trace: SWS_CANIF_00763 */
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  VAR(Std_ReturnType, CANIF_VAR) retVal;
  retVal = (uint8) E_OK;

  /* Check if CanIf is Initialised */
  /* @Trace: CanIf_SUD_API_087 */
  /* @Trace: SWS_CANIF_00810 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_CHECK_TRCV_WAKE_FLAG_IND_SID, retVal);

  /* Check if TRANSCEIVERID is in range */
  /* @Trace: CanIf_SUD_API_088 */
  /* @Trace: SWS_CANIF_00809 */
  CANIF_TRANSCEIVERID_RANGE_ERROR(CANIF_CHECK_TRCV_WAKE_FLAG_IND_SID, retVal);

  /* Is any DET error invoked */
  if ((uint8) E_OK == retVal)
  #endif/*#if (STD_ON == CANIF_DEV_ERROR_DETECT)*/
  {
    /* Invoking CanSM/Cdd_CheckTransceiverWakeFlagIndiction(TransceiverId) */
    /* @Trace: CanIf_SUD_API_089 */
    /* @Trace: SWS_CANIF_00759 */
    CANIF_DISPATCH_USERCHECKTRCVWAKEFLAGINDICATION_NAME(TransceiverId);
  }
}

#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif/*#if ((STD_ON == CANIF_PN_SUPPORT) && (...))*/

/*******************************************************************************
** Function Name        :  CanIf_ClearTrcvWufFlagIndication                   **
**                                                                            **
** Service ID           :  0x20                                               **
**                                                                            **
** Description          :  This service indicates that the transceiver        **
**                         has cleared the WufFlag.                           **
**                                                                            **
** Sync/Async           :  Synchronous                                        **
**                                                                            **
** Re-entrancy          :  Re-entrant                                         **
**                                                                            **
** Input Parameters     :  TransceiverId                                      **
**                                                                            **
** InOut Parameters     :  None                                               **
**                                                                            **
** Output Parameters    :  None                                               **
**                                                                            **
** Return value         :  None                                               **
**                                                                            **
** Preconditions        :  CanIf module must be initialized                   **
**                                                                            **
** Remarks              : Global Variable(s)  :  CanIf_CanIfStatus            **
**                        Function(s) invoked :  Det_ReportError,             **
**                                               CanSM/Cdd_ClearTrcvWufFlag   **
**                                               Indication                   **
*******************************************************************************/
#if ((STD_ON == CANIF_PN_SUPPORT) && (STD_ON == CANIF_CANTRCV_SUPPORT))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANIF_CODE) CanIf_ClearTrcvWufFlagIndication(
                                            VAR(uint8, CANIF_VAR) TransceiverId)
{
  /* @Trace: CanIf_SUD_API_100 */
  /* @Trace: SWS_CANIF_00762 */
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  VAR(Std_ReturnType, CANIF_VAR) retVal;

  retVal = (uint8) E_OK;

  /* Check if CanIf is Initialized */
  /* @Trace: CanIf_SUD_API_101 */
  /* @Trace: SWS_CANIF_00806 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_CLEAR_TRCV_WAKE_FLAG_IND_SID, retVal);

  /* Check if TRANSCEIVERID is in range */
  /* @Trace: CanIf_SUD_API_102 */
  /* @Trace: SWS_CANIF_00805 */
  CANIF_TRANSCEIVERID_RANGE_ERROR(CANIF_CLEAR_TRCV_WAKE_FLAG_IND_SID, retVal);

  /* Is any DET error invoked */
  if ((uint8) E_OK == retVal)
  #endif/*#if (STD_ON == CANIF_DEV_ERROR_DETECT)*/
  {
    /* Invoking CanSM/Cdd_CheckTrcvWufFlagIndiction(TransceiverId) */
    /* @Trace: CanIf_SUD_API_103 */
    /* @Trace: SWS_CANIF_00757 */
    CANIF_DISPATCH_USERCLEARTRCVWUFFLAGINDICATION_NAME(TransceiverId);
  }
}

#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif/*#if ((STD_ON == CANIF_PN_SUPPORT) && (...))*/

/*******************************************************************************
** Function Name        :  CanIf_ConfirmPnAvailability                        **
**                                                                            **
** Service ID           :  0x1a                                               **
**                                                                            **
** Description          :  This service indicates that the transceiver is     **
**                         running in PN communication mode                   **
**                                                                            **
** Sync/Async           :  Synchronous                                        **
**                                                                            **
** Re-entrancy          :  Re-entrant                                         **
**                                                                            **
** Input Parameters     :  TransceiverId                                      **
**                                                                            **
** InOut Parameters     :  None                                               **
**                                                                            **
** Output Parameters    :  None                                               **
**                                                                            **
** Return value         :  None                                               **
**                                                                            **
** Preconditions        :  CanIf module must be initialized                   **
**                                                                            **
** Remarks              : Global Variable(s)  :  CanIf_CanIfStatus            **
**                        Function(s) invoked :  Det_ReportError,             **
**                                               CanSM/Cdd_ConfirmPn          **
**                                               Availability                 **
*******************************************************************************/
#if ((STD_ON == CANIF_PN_SUPPORT) && (STD_ON == CANIF_CANTRCV_SUPPORT))
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANIF_CODE) CanIf_ConfirmPnAvailability (
                                            VAR(uint8, CANIF_VAR) TransceiverId)
{
  /* @Trace: CanIf_SUD_API_104 */
  /* @Trace: SWS_CANIF_00815 */
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  VAR(Std_ReturnType, CANIF_VAR) retVal;

  retVal = (uint8) E_OK;
  /* Check if CanIf is Initialized  */
  /* @Trace: CanIf_SUD_API_105 */
  /* @Trace: SWS_CANIF_00817 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_CONFIRM_PN_AVAILIBILITY_SID, retVal);

  /* Check if TRANSCEIVERID is in range  */
  /* @Trace: CanIf_SUD_API_106 */
  /* @Trace: SWS_CANIF_00816 */
  CANIF_TRANSCEIVERID_RANGE_ERROR(CANIF_CONFIRM_PN_AVAILIBILITY_SID, retVal);

  if ((uint8) E_OK == retVal)
  #endif/*#if (STD_ON == CANIF_DEV_ERROR_DETECT)*/
  {
    /* Invoking CanSM/Cdd_ConfirmPnAvailability(TransceiverId) */
    /* @Trace: CanIf_SUD_API_107 */
    /* @Trace: SWS_CANIF_00753 */
    CANIF_DISPATCH_USERCONFIRMPNAVAILABILITY_NAME(TransceiverId);
  }
}

#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif/*#if ((STD_ON == CANIF_PN_SUPPORT) && (...))*/

/*******************************************************************************
** Function Name        :  CanIf_TrcvModeIndication                           **
**                                                                            **
** Service ID           :  0x22                                               **
**                                                                            **
** Description          :  This service indicates that the transceiver        **
**                         mode has changed to TransceiverMode.               **
**                                                                            **
** Sync/Async           :  Synchronous                                        **
**                                                                            **
** Re-entrancy          :  Reentrant                                          **
**                                                                            **
** Input Parameters     :  TransceiverId, TransceiverMode                     **
**                                                                            **
** InOut Parameters     :  None                                               **
**                                                                            **
** Output Parameters    :  None                                               **
**                                                                            **
** Return value         :  None                                               **
**                                                                            **
** Preconditions        :  CanIf module must be initialized                   **
**                                                                            **
** Remarks              :  Global Variable(s)  : CanIf_CanIfStatus            **
**                         Function(s) invoked : Det_ReportError,             **
**                                               CanSM/Cdd_TransceiverMode    **
**                                               Indication                   **
*******************************************************************************/
#if (STD_ON == CANIF_CANTRCV_SUPPORT)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
FUNC(void, CANIF_CODE) CanIf_TrcvModeIndication (
                           VAR(uint8, CANIF_VAR) TransceiverId,
                           VAR(CanTrcv_TrcvModeType, CANIF_VAR) TransceiverMode)
{
  /* @Trace: CanIf_SUD_API_077 */
  /* @Trace: SWS_CANIF_00764 */
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  VAR(Std_ReturnType, CANIF_VAR) retVal;

  retVal = (uint8) E_OK;
  /* Check if CanIf is Initialized */
  /* @Trace: CanIf_SUD_API_078 */  
  /* @Trace: SWS_CANIF_00708 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_TRCV_MODE_IND_SID, retVal);

  /* Check if TRANSCEIVERID is in range */
  /* @Trace: CanIf_SUD_API_079 */  
  /* @Trace: SWS_CANIF_00706 */
  CANIF_TRANSCEIVERID_RANGE_ERROR(CANIF_TRCV_MODE_IND_SID, retVal);
  
  /* Check for no development errors */
  if ((uint8) E_OK == retVal)
  #endif/*#if (STD_ON == CANIF_DEV_ERROR_DETECT)*/
  {
    /* Invoking CanSM/Cdd_TrcvModeIndication(TransceiverId, TransceiverMode)*/
    CANIF_DISPATCH_USERTRCVMODEINDICATION_NAME(TransceiverId, TransceiverMode);
  }
}

#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif/*#if (STD_ON == CANIF_CANTRCV_SUPPORT)*/

/* polyspace-end RTE:UNR [No action planned:Low] "It's depends on the configuration of CanIf. No impact" */ 
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

