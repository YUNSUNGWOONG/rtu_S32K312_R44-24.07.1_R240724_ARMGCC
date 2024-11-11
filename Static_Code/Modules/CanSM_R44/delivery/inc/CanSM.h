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
**  SRC-MODULE: CanSM.h                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : Provision of External declaration of APIs Service Ids         **
**            related to the following features:                              **
**              Initialization and De-initialize                              **
**              Start and Stop WakeUp source                                  **
**              Version information                                           **
**              Pretended networking                                          ** 
**              Request and get requested communication mode                  **
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
** 1.0.5     31-Oct-2022   HieuTM8        #CP44-1035                          **
** 1.0.1     14-Jan-2022   HieuTM8        R44-Redmine #14419,#19306           **
** 1.0.0     04-Dec-2020   SMKwon         Initial Version                     **
*******************************************************************************/
/* @Trace: CanSM_SUD_FILE_001  */
#ifndef CANSM_H
#define CANSM_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: CanSM_SUD_DATATYPE_006 CanSM_SUD_DATATYPE_007 CanSM_SUD_DATATYPE_008 */
#include "ComStack_Types.h"       /* Com Stack Types header file */

#include "CanSM_InternalTypes.h"
#include "CanSM_Types.h"          /* CanSM Types header file */
#include "CanSM_Internal.h"       /* BaudRate header file */

/* @Trace: CanSM_SUD_MACRO_011  */
#if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
#include "CanSM_PBcfg.h"                /* CanSM Config header file */
#endif

/* @Trace: CanSM_SUD_DATATYPE_005 */
#include "ComM.h"                 /* ComM header file */

#include "Rte_Type.h"             /* ComM header file */
/* @Trace: CanSM_SUD_DATATYPE_011 CanSM_SUD_DATATYPE_012 CanSM_SUD_MACRO_012 */
#include "Std_Types.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: CanSM_SUD_MACRO_009  */
/* AUTOSAR Specification Version Information */
#define CANSM_H_AR_RELEASE_MAJOR_VERSION         0x04u
#define CANSM_H_AR_RELEASE_MINOR_VERSION         0x04u
#define CANSM_H_AR_RELEASE_REVISION_VERSION      0x00u

/* Software Version Information */
#define CANSM_H_SW_MAJOR_VERSION                 0x01u
#define CANSM_H_SW_MINOR_VERSION                 0x00u

/*******************************************************************************
**                      Published Information                                 **
*******************************************************************************/
/* Module Instance ID  */
#define CANSM_MODULE_INSTANCE_ID                ((uint8) 0)

/*******************************************************************************
**                      DET error value                                       **
*******************************************************************************/
/* @Trace: DET_SUD_MACRO_013 */
/* Not yet initialized */
#define CANSM_E_UNINIT                          ((uint8) 0x01)

/* Called with NULL PTR */
#define CANSM_E_PARAM_POINTER                   ((uint8) 0x02)

/* Network number invalid */
#define CANSM_E_INVALID_NETWORK_HANDLE          ((uint8) 0x03)

/* Controller number invalid */
#define CANSM_E_PARAM_CONTROLLER                ((uint8) 0x04)

/* Transceiver number invalid */
#define CANSM_E_PARAM_TRANSCEIVER               ((uint8) 0x05)

/* not all CAN networks are in state CANSM_NO_COMMUNICATION */
#define CANSM_E_NOT_IN_NO_COM					((uint8) 0x0B)

/*******************************************************************************
**                      Service id of CANSM API's                             **
*******************************************************************************/
/* @Trace: CanSM_SUD_MACRO_011 */
/* Service id for CanSM_Init API */
#define CANSMSERVICEID_INIT                     ((uint8) 0x00)

/* Service ID of CanSM Get Version Info */
#define CANSMSERVICEID_GETVERSIONINFO           ((uint8) 0x01)

/* Service ID of CanSM RequestMode */
#define CANSMSERVICEID_REQCOMMODE               ((uint8) 0x02)

/* Service ID of CanSM Get CurrentMode */
#define CANSMSERVICEID_GETCURRENTCOMMODE        ((uint8) 0x03)

/* Service ID of CanSM ControllerBusoff */
#define CANSMSERVICEID_CONTROLLERBUSOFF         ((uint8) 0x04)

/* Service ID of CanSM MainFunction */
#define CANSMSERVICEID_MAINFUNCTION             ((uint8) 0x05)

/* Service ID of CanSM Confirm Pn Availability */
#define CANSMSERVICEID_CONFIRMPNAVAILABILTY     ((uint8) 0x06)

/* Service ID of CanSM Trcv Timeout Exception */
#define CANSMSERVICEID_TXTIMEOUTEXCEPTION       ((uint8) 0x0B)

/* Service ID of CanSM Clear WUF Indication */
#define CANSMSERVICEID_CLRTRCVWUFFLAGINDCN      ((uint8) 0x08)

/* Service ID of CanSM Trcv Mode Indication */
#define CANSMSERVICEID_TRCVMODEINDICATION       ((uint8) 0x09)

/* Service ID of CanSM Ccheck WUF Indication */
#define CANSMSERVICEID_CHKTRCVWUFFLAGINDCN      ((uint8) 0x0A)

/* Service ID of CanSM Controller Mode Indication */
#define CANSMSERVICEID_CHECKCONTRLMODEINDICATON ((uint8) 0x07)

/* Service ID of CanSM Start wakeup source */
#define CANSMSERVICEID_STARTWAKEUPSOURCE		((uint8) 0x11)

/* Service ID of CanSM Stop wakeup source */
#define CANSMSERVICEID_STOPWAKEUPSOURCE			((uint8) 0x12)

/* Service ID of CanSM De-initialize */
#define CANSMSERVICEID_DEINITIALIZE				((uint8) 0x14)

/* Service ID of CanSM SetIComConfiguration */
#define CANSMSERVICEID_SETICOMCONFIGURATION		((uint8) 0x0F)

/* Service ID of CanSM CurrentIcomConfiguration */
#define CANSMSERVICEID_CURRENTICOMCONFIGURATION	((uint8) 0x10)

/* Service ID of CanSM SetECUPassive */
#define CANSMSERVICEID_SETECUPASSIVE			((uint8) 0x13)

/* Service ID of CanSM SetBaudrate */
#define CANSMSERVICEID_SETBAUDRATE				((uint8) 0x0D)

/*******************************************************************************
**                                  Macros                                    **
*******************************************************************************/
/* MISRA-C 14.2 fixed */
/* polyspace-begin MISRA-C3:D4.9 [Not a defect:Low] "The function like-macro is used to reduce the complexity of the code" */
#define CANSM_UNUSED_PTR(x)                        do { \
                                                    if((x) != NULL_PTR) {} \
                                                  } while(0)


#define CANSM_UNUSED(x)                            do { \
                                                    if((uint32)(x) != \
                                                    (uint32)CANSM_ZERO) {} \
                                                  } while(0)      
/* polyspace-end MISRA-C3:D4.9 [Not a defect:Low] "The function like-macro is used to reduce the complexity of the code" */                                                   
/**********************************************************************************
 * *                    Macros which define initialized status                   **
 **********************************************************************************/
/* Macro defined the initialization of CanSM */
#define CANSM_INITIALIZED                                ((uint8) 0x01)
/* Macro defined the de-initialization of CanSM */
#define CANSM_DEINITIALIZED                               ((uint8) 0x00)


/*******************************************************************************
**                      Global Data Types                                    **
*******************************************************************************/

/* CanSM module specific types */
/* @Trace: SRS_ModeMgm_09251 */
/* @Trace:  CanSM_SUD_DATATYPE_014 */
typedef enum
{
  CANSM_BSWM_NO_COMMUNICATION,
  CANSM_BSWM_SILENT_COMMUNICATION,
  CANSM_BSWM_FULL_COMMUNICATION,
  CANSM_BSWM_BUS_OFF,
  CANSM_BSWM_CHANGE_BAUDRATE
} CanSM_BswMCurrentStateType;

/* @Trace: SRS_BSW_00405 SRS_BSW_00101 SRS_BSW_00406 SRS_BSW_00358 SRS_BSW_00414 SRS_BSW_00404 */
/* @Trace: CanSM_SUD_DATATYPE_013 */
typedef enum
{
  CANSM_INITED = CANSM_INITIALIZED,
  CANSM_UNINITED = CANSM_DEINITIALIZED
} CanSM_StateType;

#if((STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)&&(STD_ON == CANSM_BOR_TX_CONFIRMATION_POLLING))
/* Global data which store configuration for CanSMBorTxConfirmationPolling which support post-build */
/* @Trace: CanSM_SUD_DATATYPE_021 */
typedef struct
{
  /* the configured value of CanSMBorTxConfirmationPolling */
  boolean CanSMBorTxConfirmationPolling;
}CanSM_BorTxConfirmationPolling;
#endif

#if((STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)&&(STD_ON == CANSM_ENABLE_BUS_OFF_DELAY))
/* Global data which store configuration for CanSMEnableBusOffDelay which support post-build */
/* @Trace: CanSM_SUD_DATATYPE_022 */
typedef struct
{
  /* the configured value of CanSMEnableBusOffDelay */
  boolean CanSMEnableBusOffDelay;
}CanSM_EnableBusOffDelay;

#endif

/******************************************************************************
**                     Global Variable                                       **
*******************************************************************************/
/* Extern for CanSM_Config */
#if(STD_OFF == CANSM_VARIANT_POSTBUILD_SUPPORT)
/*If the module support post-build feature */
#define CANSM_START_SEC_CONFIG_DATA_PREBUILD_32
#include "MemMap.h"
extern CONST(CanSM_ConfigType, CANSM_CONST) CanSM_Config[CANSM_NUMBER_OF_CONFIGURATION];
#define CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_32
#include "MemMap.h"
#else
/*If the module does not support post-build feature */
#define CANSM_START_SEC_CONFIG_DATA_POSTBUILD_32
#include "MemMap.h"
extern CONST(CanSM_ConfigType, CANSM_CONST) CanSM_Config[CANSM_NUMBER_OF_CONFIGURATION];
#define CANSM_STOP_SEC_CONFIG_DATA_POSTBUILD_32
#include "MemMap.h"
#endif
/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
/* @Trace: SRS_BSW_00447 */
#define CANSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANSM_CODE) CanSM_Init(P2CONST(CanSM_ConfigType, AUTOMATIC,CANSM_APPL_CONST) ConfigPtr);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

#if (STD_ON == CANSM_VERSION_INFO_API)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANSM_CODE) CanSM_GetVersionInfo(P2VAR(Std_VersionInfoType,AUTOMATIC, CANSM_APPL_DATA) versionInfo);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#define CANSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void, CANSM_CODE) CanSM_MainFunction(void);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

#define CANSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,CANSM_CODE) CanSM_DeInit(void);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

#define CANSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_RequestComMode(VAR(NetworkHandleType,CANSM_VAR) network,
 VAR(ComM_ModeType,CANSM_VAR) ComM_Mode);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

#define CANSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_GetCurrentComMode(VAR(NetworkHandleType,CANSM_VAR) network,
P2VAR(ComM_ModeType, AUTOMATIC,CANSM_APPL_DATA) ComM_ModePtr);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h" /* Memmap header file */



#if (STD_ON == CANSM_SET_BAUDRATE_API)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType, CANSM_CODE) CanSM_SetBaudrate(VAR(NetworkHandleType,CANSM_VAR) network, VAR(uint16,CANSM_VAR) BaudRateConfigID);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of if (STD_ON == CANSM_SET_BAUDRATE_API) */


#define CANSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType,CANSM_CODE) CanSM_StartWakeupSource(VAR(NetworkHandleType,CANSM_VAR) network);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"

#define CANSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType,CANSM_CODE) CanSM_StopWakeupSource(VAR(NetworkHandleType,CANSM_VAR) network);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"


#if(STD_ON == CANSM_ICOM_SUPPORT)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType,CANSM_CODE) CanSM_SetIcomConfiguration(VAR(NetworkHandleType,CANSM_VAR) Network,
  VAR(IcomConfigIdType,CANSM_VAR) ConfigurationId);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of (STD_ON == CANSM_ICOM_SUPPORT)*/

#if(STD_ON == CANSM_ICOM_SUPPORT)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(void,CANSM_CODE) CanSM_CurrentIcomConfiguration(VAR(uint8,CANSM_VAR) ControllerId,
  VAR(IcomConfigIdType,CANSM_VAR) ConfigurationId,VAR(IcomSwitch_ErrorType,CANSM_VAR) Error);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* End of (STD_ON == CANSM_ICOM_SUPPORT)*/

#if(STD_ON == CANSM_TX_OFFLINE_ACTIVE_SUPPORT)
#define CANSM_START_SEC_CODE
#include "MemMap.h"
extern FUNC(Std_ReturnType,CANSM_CODE) CanSM_SetEcuPassive(VAR(boolean,CANSM_VAR) CanSM_Passive);
#define CANSM_STOP_SEC_CODE
#include "MemMap.h"
#endif /* end if of (STD_ON == CANSM_TX_OFFLINE_ACTIVE_SUPPORT) */

#if((STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)&&(STD_ON == CANSM_BOR_TX_CONFIRMATION_POLLING))
/*If the module support post-build feature */
#define CANSM_START_SEC_CONFIG_DATA_PREBUILD_32
#include "MemMap.h"
extern CONST(CanSM_BorTxConfirmationPolling, CANSM_CONST) CanSM_NwTxConfirmationPolling[CANSM_MAX_NUMBER_OF_STATIC_NWS];
#define CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_32
#include "MemMap.h"
#endif

#if((STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)&&(STD_ON == CANSM_ENABLE_BUS_OFF_DELAY))
/*If the module support post-build feature */
#define CANSM_START_SEC_CONFIG_DATA_PREBUILD_32
#include "MemMap.h"
extern CONST(CanSM_EnableBusOffDelay, CANSM_CONST) CanSM_NwEnableBusOffDelay[CANSM_MAX_NUMBER_OF_STATIC_NWS];
#define CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_32
#include "MemMap.h"
#endif


#endif /* End of ifndef CANSM_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

