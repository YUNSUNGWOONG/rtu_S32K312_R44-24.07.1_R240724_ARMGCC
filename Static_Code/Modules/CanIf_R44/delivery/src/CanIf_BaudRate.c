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
**  SRC-MODULE: CanIf_BaudRate.c                                              **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CanIf                                                 **
**                                                                            **
**  PURPOSE   : Provision to change the baud rate functionality               **
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
** 1.1.0    29-Feb-2024    Jh Yang        #CP44-2946, #CP44-2947, #CP44-3540  **
                                          #CP44-3755, #CP44-3811              **
** 1.0.9    03-Oct-2022    HieuTM8        #CP44-832                           **
** 1.0.5    30-Jun-2022    HieuTM8        #CP44-130                           **
** 1.0.1    22-Sep-2021    HieuTM8        #20891                              **
** 1.0.0    21-Dec-2020    SJ Kim         Initialization                      **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanIf.h"               /* CanIf header file */
#include "CanIf_BaudRate.h"      /* CanIf header file */
#include "CanIf_Ram.h"           /* CanIf RAM header file */
#include "CanIf_PCTypes.h"       /* Pre-compile time header file */
#include "CanIf_Error.h"         /* CanIf DET header file */
#include "Can.h"                 /* CAN driver header file*/
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* AUTOSAR specification version information */
#define CANIF_BAUDRATE_C_AR_RELEASE_MAJOR_VERSION    4
#define CANIF_BAUDRATE_C_AR_RELEASE_MINOR_VERSION    4
#define CANIF_BAUDRATE_C_AR_RELEASE_REVISION_VERSION 0

/* File version information */
#define CANIF_BAUDRATE_C_SW_MAJOR_VERSION       1
#define CANIF_BAUDRATE_C_SW_MINOR_VERSION       1
#define CANIF_BAUDRATE_C_SW_REVISION_VERSION    0

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/
#if (CANIF_BAUDRATE_AR_RELEASE_MAJOR_VERSION != \
  CANIF_BAUDRATE_C_AR_RELEASE_MAJOR_VERSION)
  #error "CANIF_BAUDRATE.c : Mismatch in Specification Major Version"
#endif
#if (CANIF_BAUDRATE_AR_RELEASE_MINOR_VERSION != \
  CANIF_BAUDRATE_C_AR_RELEASE_MINOR_VERSION)
  #error "CANIF_BAUDRATE.c : Mismatch in Specification Minor Version"
#endif
#if (CANIF_BAUDRATE_AR_RELEASE_REVISION_VERSION != \
  CANIF_BAUDRATE_C_AR_RELEASE_REVISION_VERSION)
  #error "CANIF_BAUDRATE.c : Mismatch in Specification Revision Version"
#endif
#if (CANIF_BAUDRATE_SW_MAJOR_VERSION != CANIF_BAUDRATE_C_SW_MAJOR_VERSION)
  #error "CANIF_BAUDRATE.c : Mismatch in Software Major Version"
#endif
#if (CANIF_BAUDRATE_SW_MINOR_VERSION != CANIF_BAUDRATE_C_SW_MINOR_VERSION)
  #error "CANIF_BAUDRATE.c : Mismatch in Software Minor Version"
#endif
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : CanIf_SetBaudrate                                   **
**                                                                            **
** Service ID           : 0x27                                                **
**                                                                            **
** Description          : This service shall set the baud rate configuration  **
**                        of the CAN controller. Depending on necessary       **
**                        baud rate modifications the controller might        **
**                        have to reset.                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different ControllerIds.              **
**                        Non reentrant for the same ControllerId.            **
**                                                                            **
** Input Parameters     : ControllerId, BaudRateConfigID                      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return value         : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : CanIf module must be initialized                    **
**                                                                            **
** Remarks              : Global Variable(s)  : CanIf_ControllerConfig        **
**                                              CanIf_CanDriver               **
**                        Function(s) invoked : Can_SetBaudrate()             **
**                                              Det_ReportError()             **
*******************************************************************************/
#if (STD_ON == CANIF_SET_BAUDRATE_API)
#define CANIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00323 */
FUNC(Std_ReturnType, CANIF_CODE) CanIf_SetBaudrate (
    VAR(uint8, CANIF_VAR) ControllerId,
    VAR(uint16, CANIF_VAR) BaudRateConfigID)
{
  /* @Trace: CanIf_SUD_API_080 */
  /* @Trace: SWS_CANIF_00867 */
  #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
  P2CONST(CanIf_ControllerConfigType, AUTOMATIC, CANIF_CONST) ptrStaticController;
  P2CONST(CanIf_CanDriverType, AUTOMATIC, CANIF_CONST) ptrDriver;
  #endif
  VAR(Std_ReturnType, CANIF_VAR) retVal;

  /* Initialize the Standard Return Value with E_OK */
  #if (STD_ON == CANIF_DEV_ERROR_DETECT)
  retVal = (uint8) E_OK;

  /* Report to DET, if module is not initialized */
  /* @Trace: SWS_CANIF_00661 */
  CANIF_GLOBAL_INIT_STATUS_ERROR(CANIF_SET_BAUD_RATE_SID, retVal);

  /* @Trace: CanIf_SUD_API_081 */
  /* @Trace: SWS_CANIF_00869 */
  /* Report to DET, if controller ID is out of range */
  CANIF_CONTROLLER_RANGE_ERROR(CANIF_SET_BAUD_RATE_SID, retVal);

  /* Is any DET error invoked */
  if ((uint8)E_NOT_OK != retVal)
  #endif/* #if (STD_ON == CANIF_DEV_ERROR_DETECT) */
  {
    /* @Trace: CanIf_SUD_API_150 */
    #if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT)
    
    /* Get the pointer to corresponding Can Controller structure */
    #if (STD_ON == CANIF_VARIANT_POSTBUILD_SUPPORT)
    ptrStaticController = &CanIfControllerConfig[ControllerId];
    #else
    ptrStaticController = &CanIf_ControllerConfig[ControllerId];
    #endif

    /* Get the pointer to corresponding Can Driver structure */
    ptrDriver = &CanIf_CanDriver[ptrStaticController->CanDriverId];
    
    /* Invoke the function Can_SetBaudrate */
    retVal = ptrDriver->CanSetBaudrate (ControllerId, BaudRateConfigID);
    #else
    /* Invoke the function Can_SetBaudrate */
    /* @Trace: CanIf_SUD_API_082 */
    /* @Trace: SWS_CANIF_00868 */
    #if ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR) && \
        (CAN_AR_RELEASE_MINOR_VERSION == CAN_AR_RELEASE_MINOR_VERSION_TWO))
    retVal = Can_ChangeBaudrate(ControllerId, BaudRateConfigID);
    #else
    retVal = Can_SetBaudrate(ControllerId, BaudRateConfigID);
    #endif /*#if ((CAN_AR_RELEASE_MAJOR_VERSION == CAN_AR_RELEASE_MAJOR_VERSION_FOUR)*/
    #endif/*#if (STD_ON == CANIF_MULTIPLE_CANDRV_SUPPORT) */
  }/* if (E_OK == retVal) */
  return (retVal);
}

#define CANIF_STOP_SEC_CODE
#include "MemMap.h"
#endif/* #if (STD_ON == CANIF_SET_BAUDRATE_API) */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
