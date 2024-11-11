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
**  SRC-MODULE: CanSM_Error.h                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : This file provides macros for DET checking for CanSM module   **
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
** 1.0.3     25-Jul-2022   HieuTM8        CP44-511                            **
** 1.0.1     14-Jan-2022   HieuTM8        R44-Redmine #14419,#19306           **
** 1.0.0     04-Dec-2020   SMKwon         Initial Version                     **
*******************************************************************************/
/* @Trace: CanSM_SUD_FILE_001  */
#ifndef CANSM_ERROR_H
#define CANSM_ERROR_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanSM.h"
#include "CanSM_Types.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: CanSM_SUD_MACRO_004  */
/* AUTOSAR Specification Version Information */
#define CANSM_ERROR_AR_RELEASE_MAJOR_VERSION         0x04u
#define CANSM_ERROR_AR_RELEASE_MINOR_VERSION         0x04u
#define CANSM_ERROR_AR_RELEASE_REV_VERSION           0x00u

/* Software Version Information */
#define CANSM_ERROR_H_SW_MAJOR_VERSION         0x01u
#define CANSM_ERROR_H_SW_MINOR_VERSION         0x00u

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* polyspace-begin MISRA-C3:D4.9 [Not a defect:Low] "The function like-macro is used to reduce the complexity of the code" */
#if (STD_ON == CANSM_DEV_ERROR_DETECT)
/* @Trace: SRS_BSW_00337 */
/* Note: Error handling for CanSM not initialized */
/*------------------------ CANSM_INITED_DET_CHECK ----------------------------*/
#define CANSM_INITED_DET_CHECK(result, ServiceID)\
  do{\
    if ((CanSM_InitStatus) == ((CanSM_StateType)CANSM_UNINITED))\
    {\
      (void)Det_ReportError(CANSM_MODULE_ID, CANSM_MODULE_INSTANCE_ID,\
        ServiceID, CANSM_E_UNINIT);\
      (result) = ((uint8)(E_NOT_OK));\
    }\
    else\
    {\
      (result) = (uint8)(E_OK);\
    }\
  }while(0)

/* @Trace: SRS_BSW_00337 */
/* Note: Error handling for invalid transceiver network */
/*------------------------ CANSM_VALID_TRCV_NETWORK_CHECK ------------------*/
#define CANSM_VALID_TRCV_NETWORK_CHECK(result, networkHandle, ServiceID)\
  do{\
    if ((uint8)CANSM_INVALID_NETWORK == (networkHandle))\
    {\
      (void)Det_ReportError(CANSM_MODULE_ID, CANSM_MODULE_INSTANCE_ID, \
        (ServiceID), CANSM_E_PARAM_TRANSCEIVER);\
      (result) = (uint8)E_NOT_OK;\
    }\
    else\
    {\
        (result) = ((uint8)(E_OK));\
    }\
  }while(0)

/* @Trace: SRS_BSW_00337 */
/* Note: Error handling for invalid transceiver ID */
#if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT )
/*------------------------ CANSM_CHECK_INVALID_TRANSCEIVERID -----------------*/
#define CANSM_CHECK_INVALID_TRANSCEIVERID(result, TranseiverId, ServiceID)\
  do{\
    if ((TranseiverId) > ((uint8)(CanSM_LastTrcvHandle)))\
    {\
      (void)Det_ReportError(CANSM_MODULE_ID, CANSM_MODULE_INSTANCE_ID, \
        ServiceID, CANSM_E_PARAM_TRANSCEIVER);\
      (result) = ((uint8)(E_NOT_OK));\
    }\
  }while(0)
#else
#define CANSM_CHECK_INVALID_TRANSCEIVERID(result, TranseiverId, ServiceID)\
  do{\
    if ((TranseiverId) > ((uint8)(CANSM_LAST_TRCV_HANDLE)))\
    {\
      (void)Det_ReportError(CANSM_MODULE_ID, CANSM_MODULE_INSTANCE_ID, \
        ServiceID, CANSM_E_PARAM_TRANSCEIVER);\
      (result) = ((uint8)(E_NOT_OK));\
    }\
  }while(0)
#endif




/* @Trace: SRS_BSW_00337 */
/* Note: Error handling for invalid network */
/*------------------------ CANSM_CHECK_INVALID_NETWORK ---------------------*/
#if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
#define CANSM_CHECK_INVALID_NETWORK(result, NetworkHandle, ServiceID)\
  do{\
    if (((NetworkHandleType)(CanSM_LastNWHandle)) < (NetworkHandle))\
    {\
      (void)Det_ReportError(CANSM_MODULE_ID, CANSM_MODULE_INSTANCE_ID, \
        ServiceID, CANSM_E_INVALID_NETWORK_HANDLE);\
      (result) = ((uint8)(E_NOT_OK));\
    }\
    else\
    {\
      (result) = ((uint8)(E_OK));\
    }\
  }while(0)
#else
#define CANSM_CHECK_INVALID_NETWORK(result, NetworkHandle, ServiceID)\
  do{\
    if (((NetworkHandleType)(CANSM_LAST_NW_HANDLE)) < (NetworkHandle))\
    {\
      (void)Det_ReportError(CANSM_MODULE_ID, CANSM_MODULE_INSTANCE_ID, \
        ServiceID, CANSM_E_INVALID_NETWORK_HANDLE);\
      (result) = ((uint8)(E_NOT_OK));\
    }\
    else\
    {\
      (result) = ((uint8)(E_OK));\
    }\
  }while(0)
#endif

/* @Trace: SRS_BSW_00337 */
/* Note: Error handling for invalid network handle */
/*------------------------ CANSM_CHECK_INVALID_NETWORK_HANDLE ---------------*/
#define CANSM_CHECK_INVALID_NETWORK_HANDLE(result, networkHandle, \
                                           ServiceID)\
  do{\
    if (((NetworkHandleType)(CANSM_INVALID_NETWORK)) == (networkHandle))\
    {\
      (void)Det_ReportError(CANSM_MODULE_ID, CANSM_MODULE_INSTANCE_ID, \
        ServiceID, CANSM_E_INVALID_NETWORK_HANDLE);\
      (result) = (uint8)(E_NOT_OK);\
    }\
    else\
    {\
      (result) = (uint8)(E_OK);\
    }\
  }while(0)

/* @Trace: SRS_BSW_00337 */
/* Note: Error handling for invalid pointer */
/*------------------------ CANSM_CHECK_INVALID_POINTER ----------------------*/
#define CANSM_CHECK_INVALID_POINTER(result, Pointer, ServiceID)\
  do{\
    if ((NULL_PTR) == (Pointer))\
    {\
      (void)Det_ReportError(CANSM_MODULE_ID, CANSM_MODULE_INSTANCE_ID, \
        ServiceID, CANSM_E_PARAM_POINTER);\
      (result) = ((uint8)(E_NOT_OK));\
    }\
    else\
    {\
        (result) = (uint8)(E_OK);\
    }\
  }while(0)


/* @Trace: SRS_BSW_00337 */
/* Note: Error handling for invalid controller */
/*------------------------ CANSM_CHECK_INVALID_CONTROLLER -------------------*/
#if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
#define CANSM_CHECK_INVALID_CONTROLLER(result, Controller, ServiceID)\
  do{\
    if (((Controller) > ((uint8)(CanSM_LastCtrlHandle)))||((uint8)(CANSM_INVALID_ID) == CanSM_CtrlIDToNW[Controller]))\
    {\
      (void)Det_ReportError(CANSM_MODULE_ID, CANSM_MODULE_INSTANCE_ID, \
        ServiceID, CANSM_E_PARAM_CONTROLLER);\
      (result) = ((uint8)(E_NOT_OK));\
    }\
    else\
    {\
      (result) = (uint8)(E_OK);\
    }\
  }while(0)
#else
#define CANSM_CHECK_INVALID_CONTROLLER(result, Controller, ServiceID)\
  do{\
    if (((Controller) > ((uint8)(CANSM_LAST_CTRL_HANDLE)))||((uint8)(CANSM_INVALID_ID) == CanSM_InternalController[Controller]))\
    {\
      (void)Det_ReportError(CANSM_MODULE_ID, CANSM_MODULE_INSTANCE_ID, \
        ServiceID, CANSM_E_PARAM_CONTROLLER);\
      (result) = ((uint8)(E_NOT_OK));\
    }\
    else\
    {\
      (result) = (uint8)(E_OK);\
    }\
  }while(0)
#endif

/* @Trace: SRS_BSW_00337 */
/* Note: Error handling for not all network are in no communication mode */
/*-------------------------CANSM_E_NOT_IN_NO_COM ------------------------------*/
#define CANSM_NOT_IN_NO_COM_INDICATION(ServiceID)\
	do{\
				(void)Det_ReportError(CANSM_MODULE_ID,CANSM_MODULE_INSTANCE_ID, \
					ServiceID, CANSM_E_NOT_IN_NO_COM);\
	}while(0)

  /* polyspace:end<MISRA-C:19.7:Not a defect:Justify with annotations> No Impact of this rule violation*/
#endif /* End of if (STD_ON == CANSM_DEV_ERROR_DETECT) */

#endif /* CANSM_ERROR_H */
/* polyspace-end MISRA-C3:D4.9 [Not a defect:Low] "The function like-macro is used to reduce the complexity of the code" */
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/

