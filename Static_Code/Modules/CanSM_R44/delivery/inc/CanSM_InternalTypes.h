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
**  SRC-MODULE: CanSM_InternalTypes.h                                         **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR CAN State Manager Module                              **
**                                                                            **
**  PURPOSE   : To provide configuration specific data types                  **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision    Date          By             Description                       **
********************************************************************************
** 1.0.9_HF1   23-Feb-2024   MU Kim         CP44-2851                         **
** 1.0.5       31-Oct-2022   HieuTM8        #CP44-1035                        **
** 1.0.4       30-Sep-2022   HieuTM8        #CP44-876                         **
** 1.0.2       27-Apr-2022   HieuTM8        R44-Redmine #25635, #23926        **
** 1.0.1       14-Jan-2022   HieuTM8        R44-Redmine #14419,#19306         **
** 1.0.0       04-Dec-2020   SMKwon         Initial Version                   **
*******************************************************************************/
/* @Trace: CanSM_SUD_FILE_001  */
#ifndef CANSM_INTERNALTYPES_H
#define CANSM_INTERNALTYPES_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "CanSM.h"
#include "CanSM_Error.h"          /* CanSM Error header file */
#include "SchM_CanSM.h"           /* SchM CanSM header file */
#include "CanSM_Version.h"        /* CanSM Version header file */

/* @Trace: CanSM_SUD_DATATYPE_010 DEM_SUD_MACRO_014 */
#if(STD_ON == CANSM_DEM_STATUS)
#include "Dem.h"                  /* Dem header file */
#endif

/* @Trace: CanSM_SUD_DATATYPE_001  CanSM_SUD_DATATYPE_002  */
#if(STD_ON == CANSM_TX_OFFLINE_ACTIVE_SUPPORT)
#include "CanIf_Types.h"		  /* Types used for CanIf */
#endif

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/* @Trace: CanSM_SUD_MACRO_006  */
/* AUTOSAR Specification Version Information */
#define CANSM_INTERNALTYPES_AR_RELEASE_MAJOR_VERSION         0x04u
#define CANSM_INTERNALTYPES_AR_RELEASE_MINOR_VERSION         0x04u
#define CANSM_INTERNALTYPES_AR_RELEASE_REVISION_VERSION      0x00

/* Software Version Information */
#define CANSM_INTERNALTYPES_SW_MAJOR_VERSION                 0x01u
#define CANSM_INTERNALTYPES_SW_MINOR_VERSION                 0x00u

/*******************************************************************************
**                      MACRO Definitions                                     **
*******************************************************************************/

/* Macro for fetching the Network handle */

#define CANSM_NETWORKHANDLE                    (networkHandle)
/* Macro for the number of internal functions manipulated by the main function*/
#if (STD_ON == CANSM_PNC_AVAILABILITY)
#define CANSM_INTERNALFUNCTIONS_IN_MAINFUNCTION 0x12u
#else
#define CANSM_INTERNALFUNCTIONS_IN_MAINFUNCTION 0x10u
#endif

/* Macro for fetching the BOR counter and Tx Ensured */
#define CANSM_BOR_L1TOL2                          (ptrStaticNetwork->BorCounterL1ToL2)


/* Macro for fetching the BOR timer values */
#define CANSM_BOR_TIMEL1                          (ptrStaticNetwork->CanSMBorTimeL1)
#define CANSM_BOR_TIMEL2                          (ptrStaticNetwork->CanSMBorTimeL2)
#define CANSM_BOR_TIME_TXENSURED                  (ptrStaticNetwork->BorTimeTxEnsured)




/* Macro for setting the controller mode for respective networks */
/* polyspace-begin MISRA-C3:D4.9 [Not a defect:Low] "The function like-macro is used to reduce the complexity of the code" */
/* polyspace-begin MISRA-C3:10.3 [Not a defect:Low] "The type of parameter and argument are different because the two software layers follows different AUTOSAR version" */
#if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
#define CANIF_SETCONTROLLERMODE(ControllerID, ControllerMode)\
  {\
    (noOfController) = (ptrStaticNetwork->NumberOfController);\
    (controllerIndex) = (ControllerID);\
    do\
    {\
      result |= CanIf_SetControllerMode(CanSM_CtrlIndexToId[controllerIndex], \
        ControllerMode);\
      --noOfController;\
      ++controllerIndex;\
    } while (noOfController != CANSM_ZERO);\
  }
#else
#define CANIF_SETCONTROLLERMODE(ControllerID, ControllerMode)\
  {\
    (noOfController) = (ptrStaticNetwork->NumberOfController);\
    (controllerIndex) = (ControllerID);\
    do\
    {\
      result |= CanIf_SetControllerMode(CanSM_StaticController[controllerIndex], \
        ControllerMode);\
      --noOfController;\
      ++controllerIndex;\
    } while (noOfController != CANSM_ZERO);\
  }
#endif
/* polyspace-end MISRA-C3:10.3 [Not a defect:Low] "The type of parameter and argument are different because the two software layers follows different AUTOSAR version" */
/* Macro for setting the Pdu mode*/
#if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
#define CANIF_SETPDUMODE(ControllerID, PduMode)\
  {\
    (noOfController) = (ptrStaticNetwork->NumberOfController);\
    (controllerIndex) = (ControllerID);\
    do\
    {\
      result |= CanIf_SetPduMode(CanSM_CtrlIndexToId[controllerIndex], PduMode);\
      --noOfController;\
      ++controllerIndex;\
    } while (noOfController != CANSM_ZERO);\
  }
#else
#define CANIF_SETPDUMODE(ControllerID, PduMode)\
  {\
    (noOfController) = (ptrStaticNetwork->NumberOfController);\
    (controllerIndex) = (ControllerID);\
    do\
    {\
      result |= CanIf_SetPduMode(CanSM_StaticController[controllerIndex], PduMode);\
      --noOfController;\
      ++controllerIndex;\
    } while (noOfController != CANSM_ZERO);\
  }
#endif


/* Macro for get a state of tx confirmation*/
#if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
#define CANIF_GETTXCONFIRMATIONSTATE(ControllerID)\
  {\
    (noOfController) = (ptrStaticNetwork->NumberOfController);\
    (controllerIndex) = (ControllerID);\
    do\
    {\
      retVal = CanIf_GetTxConfirmationState(CanSM_CtrlIndexToId[controllerIndex]);\
      --noOfController;\
      ++controllerIndex;\
    } while ((noOfController != CANSM_ZERO)&&(retVal == CANIF_TX_RX_NOTIFICATION));\
  }
#else
#define CANIF_GETTXCONFIRMATIONSTATE(ControllerID)\
  {\
    (noOfController) = (ptrStaticNetwork->NumberOfController);\
    (controllerIndex) = (ControllerID);\
    do\
    {\
      retVal = CanIf_GetTxConfirmationState(CanSM_StaticController[controllerIndex]);\
      --noOfController;\
      ++controllerIndex;\
    } while ((noOfController != CANSM_ZERO)&&(retVal == CANIF_TX_RX_NOTIFICATION));\
  }
#endif



/* Macro for setting BaudRateConfigID of controllers for respective networks */
#if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT)
#define CANIF_SETBAUDRATE(ControllerID,BaudRateConfigID)\
  {\
	(noOfController) = (ptrStaticNetwork->NumberOfController);\
	(controllerIndex) = (ControllerID);\
	do\
    {\
      (void)CanIf_SetBaudrate(CanSM_CtrlIndexToId[controllerIndex], BaudRateConfigID);\
      --noOfController;\
      ++controllerIndex;\
    } while (noOfController != CANSM_ZERO);\
  }
#else
#define CANIF_SETBAUDRATE(ControllerID,BaudRateConfigID)\
  {\
    (noOfController) = (ptrStaticNetwork->NumberOfController);\
    (controllerIndex) = (ControllerID);\
    do\
    {\
      (void)CanIf_SetBaudrate(CanSM_StaticController[controllerIndex], BaudRateConfigID);\
      --noOfController;\
      ++controllerIndex;\
    } while (noOfController != CANSM_ZERO);\
  }
#endif
/* polyspace-end MISRA-C3:D4.9 [Not a defect:Low] "The function like-macro is used to reduce the complexity of the code" */


#define  CANSM_DEM_NO_EVENT                       ((Dem_EventIdType)0x00)

#define  CANSM_CANTRCV_INVALID_ID                 ((uint8)0xFF)
#define  CANSM_INVALID_ID                         ((uint8)0xFF)

/* This type define the network is Invalid */
#define  CANSM_INVALID_NETWORK                    ((uint8)0xFF)

/* This type define Max Bor Counter */
#define  CANSM_MAX_BOR_COUNTER                    ((uint8)0xFF)

/* Defined for Numerical value*/
#define CANSM_ZERO                                ((uint8) 0x00)
#define CANSM_ONE                                 ((uint8) 0x01)
#define CANSM_TWO                                 ((uint8) 0x02)
#define CANSM_THREE                               ((uint8) 0x03)
#define CANSM_FOUR                                ((uint8) 0x04)
#define CANSM_FIVE                                ((uint8) 0x05)
#define CANSM_SIX                                 ((uint8) 0x06)
#define CANSM_SEVEN                               ((uint8) 0x07)
#define CANSM_EIGHT                               ((uint8) 0x08)
#define CANSM_TRUE                                ((uint8) 0x01)
#define CANSM_FALSE                               ((uint8) 0x00)

/* MISRA-C 10.1, 10.5, 12.8 fixed **/

/* CanSM BswM Mode */
/* polyspace +1 MISRA-C3:D4.9 [Not a defect:Low] "The function like-macro is used to reduce the complexity of the code" */
#define CANSM_BSWM_USER_ID(chid)    	((uint16)((uint16)(chid) << CANSM_EIGHT) + (CANSM_MODULE_ID))


/* Mode indication status for NO COMMUNICATION */
#define CANSM_NOCOMMUNICATION                     ((uint8) 0x00)

/* Mode indication status for SILENT COMMUNICATION */
#define CANSM_SILENTCOMMUNICATION                 ((uint8) 0x01)

/* Mode indication status for FULL COMMUNICATION */
#define CANSM_FULLCOMMUNICATION                   ((uint8) 0x02)

/* Mode indication status for Bus Off Recovery START*/
#define CANSM_BORSTART                            ((uint8) 0x03)

/* Mode indication status for Bus Off Recovery Wait */
#define CANSM_BORWAIT                             ((uint8) 0x04)

/* Mode indication status for checking Bus Off*/
#define CANSM_CHECKBUSOFF                         ((uint8) 0x05)

/* Mode indication status for No to Full Communication*/
#define CANSM_NOTOFULLCOMMREQUESTED               ((uint8) 0x06)

/* Mode indication status for Silent to Full Communication*/
#define CANSM_SILENTTOFULLCOMMREQUESTED           ((uint8) 0x07)

/* Mode indication status for Silent Communication*/
#define CANSM_FULLTOSILENTCOMMREQUESTED	          ((uint8) 0x08)

/* Mode indication status for Silent communication bus off recovery */
#define CANSM_SILENTCOMMUNICATION_BOR             ((uint8) 0x09)

/* Mode indication status for Changiong the Baud Rate*/
#define CanSM_SetBaudrateSERVICE                  ((uint8) 0x0A)

/* Mode indication status for the change of baudrate to full com */
#define CANSM_BAUDRATEENDFULLCOM				  ((uint8) 0x0B)

/* Mode indication status for the change of baudrate to Silent com */
#define CANSM_BAUDRATEENDSILENTCOM				  ((uint8) 0x0C)


/* Mode indication status for wake up validation  */
#define CANSM_WAKEUPVALIDATION					  ((uint8) 0x0D)

/* Mode indication status for WUVALIDATION to Full com */
#define CANSM_WAKEUPTOFULLCOMREQUESTED	  		  ((uint8) 0x0E)

/* Mode indication status for Partial Networking Not Supported*/
#define CANSM_DEINITPNNOTSUPPORTED                ((uint8) 0x0F)

/* Mode indication status for Partial Networking Supported*/
#define CANSM_DEINITPNSUPPORTED                   ((uint8) 0x10)

/* Mode indication status for TimeOut*/
#define CANSM_TXTIMEOUTEXCEPTION           ((uint8) 0x11)


/* Macro for internal SubState in CANSM_BSM_S_SILENTCOM_BOR */
#define CANSM_SILENT_BOR_RESTART_CC				  ((uint8) 0x00)
#define CANSM_SILENT_BOR_RESTART_CC_WAIT		  ((uint8) 0x01)
#define CANSM_SILENT_BOR_TX_OFF 				  ((uint8) 0x02)


/* Macro for Intermediate Network SubState */
#define CANSM_FULL_T_BUSOFF                       ((uint8) 0x00)
#define CANSM_FULL_RESTART_CC                     ((uint8) 0x02)
#define CANSM_FULL_RESTART_CC_WAIT                ((uint8) 0x03)
#define CANSM_FULL_TX_OFF                         ((uint8) 0x04)

/* Macro for Internal SubState in CANSM_BSM_S_PRE_FULLCOM sub state Machine */
#define CANSM_PREFULL_TRCV_NORMAL                 ((uint8) 0x00)
#define CANSM_PREFULL_TRCV_NORMAL_WAIT            ((uint8) 0x01)
#define CANSM_PREFULL_CC_STOPPED                  ((uint8) 0x02)
#define CANSM_PREFULL_CC_STOPPED_WAIT             ((uint8) 0x03)
#define CANSM_PREFULL_CC_STARTED                  ((uint8) 0x04)
#define CANSM_PREFULL_CC_STARTED_WAIT             ((uint8) 0x05)
#define CANSM_PREFULL_CC_ONLINE                   ((uint8) 0x06)

/* Macro for Internal SubState in CANSM_BSM_DeinitPnSupported
                                                             sub state Machine*/
#define CANSM_PN_TRCV_CLEAR_WUF                   ((uint8) 0x00)
#define CANSM_PN_CLEAR_WUF_WAIT                   ((uint8) 0x01)
#define CANSM_PN_CC_STOPPED                       ((uint8) 0x02)
#define CANSM_PN_STOPPED_WAIT                     ((uint8) 0x03)
#define CANSM_PN_TRCV_NORMAL                      ((uint8) 0x04)
#define CANSM_PN_TRCV_NORMAL_WAIT                 ((uint8) 0x05)
#define CANSM_PN_TRCV_STANDBY                     ((uint8) 0x06)
#define CANSM_PN_TRCV_STANDBY_WAIT                ((uint8) 0x07)
#define CANSM_PN_CS_SLEEP                         ((uint8) 0x08)
#define CANSM_PN_CS_SLEEP_WAIT                    ((uint8) 0x09)
#define CANSM_PN_TRCV_CHECK_WUF                   ((uint8) 0x0A)
#define CANSM_PN_TRCV_CLEAR_WUF_WAIT              ((uint8) 0x0B)
#define CANSM_PN_NO_COMMUNICATION                 ((uint8) 0x0C)
#define CANSM_PN_WFLAG_IN_NOT_CC_SLEEP            ((uint8) 0x0E)
#define CANSM_PN_WFLAG_IN_NOT_CC_SLEEP_WAIT       ((uint8) 0x0F)
#define CANSM_PN_IN_NOT_CC_SLEEP_NOCOMM           ((uint8) 0x10)


/* Macro for Internal SubState in CANSM_BSM_DeinitPnNotSupported
                                                             sub state Machine*/
#define CANSM_WOPN_CS_STOPPED                     ((uint8) 0x00)
#define CANSM_WOPN_CS_STOPPED_WAIT                ((uint8) 0x01)
#define CANSM_WOPN_CS_SLEEP                       ((uint8) 0x02)
#define CANSM_WOPN_CS_SLEEP_WAIT                  ((uint8) 0x03)
#define CANSM_WOPN_TRCV_MODE_NORMAL               ((uint8) 0x04)
#define CANSM_WOPN_TRCV_MODE_NORMAL_WAIT          ((uint8) 0x05)
#define CANSM_WOPN_TRCV_MODE_STANDBY              ((uint8) 0x06)
#define CANSM_WOPN_TRCV_MODE_STANDBY_WAIT         ((uint8) 0x07)
#define CANSM_WOPN_NO_COMMUNICATION               ((uint8) 0x08)

/* Macros for CanSM Baudrate Substate Machine */
#define CANSM_BR_CC_STOPPED                       ((uint8) 0x00)
#define CANSM_BR_STARTED                          ((uint8) 0x02)
#define CANSM_BR_CC_ONLINE                        ((uint8) 0x04)

/* Macro for Internal SubState in CANSM_BSM_TX_TIMEOUTEXCEPTION
                                                            sub state Machine */
#define CANSM_TIMEOUT_CC_STOPPED                  ((uint8) 0x00)
#define CANSM_TIMEOUT_CC_STARTED                  ((uint8) 0x02)
#define CANSM_TIMEOUT_CC_ONLINE                   ((uint8) 0x04)

#define CANSM_E_WAITSTATE                         ((uint8) 0x80)

#define CANSM_TRCV_CLEARWUPFLAG_INDICATION        ((uint8) 0x03)
#define CANSM_TRCV_CHECKWUPFLAG_INDICATION        ((uint8) 0x04)

/* Macro for internal SubState in CANSM_BSM_WUVALIDATION */
#define CANSM_WUV_TRCV_NORMAL					  ((uint8) 0x00)
#define CANSM_WUV_TRCV_NORMAL_WAIT				  ((uint8) 0x01)
#define CANSM_WUV_CC_STOPPED					  ((uint8) 0x02)
#define CANSM_WUV_CC_STOPPED_WAIT				  ((uint8) 0x03)
#define CANSM_WUV_CC_STARTED					  ((uint8) 0x04)
#define CANSM_WUV_CC_STARTED_WAIT				  ((uint8) 0x05)
#define CANSM_WUV_WAIT_LEAVE					  ((uint8) 0x06)

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
#if (STD_ON == CANSM_SET_BAUDRATE_API)
/* CanSM Direct Baudrate */
/* @Trace: CanSM_SUD_DATATYPE_016 */
typedef enum
{
    CANSM_DIRECT_BAUDRATE,
    CANSM_NOT_DIRECT_BAUDRATE,
    CANSM_UNIDENTIFIED_BAUDRATE
}CanSM_BaudrateDirect;
#endif

/* @Trace: CanSM_SUD_DATATYPE_018 */
typedef struct
{
  /* Network handle ID */
  NetworkHandleType CanSmNetworkHandle;

  /* Indicating Partial networking is Supported or not */
  #if (STD_ON == CANSM_PNC_AVAILABILITY)
  boolean pnSupported;
  #endif

  #if(STD_ON == CANSM_DEM_STATUS)
  /* Parameter indicating if Dem error reporting is enabled*/
  boolean DemStatusFlag;
  #endif

  /* Parameter indicating if polling is enabled or not */
  #if((STD_OFF == CANSM_VARIANT_POSTBUILD_SUPPORT)&&(STD_ON == CANSM_BOR_TX_CONFIRMATION_POLLING))
  boolean CanSMTxConfirmationPolling;
  #endif


  /* Parameter indicating if BusOffDelay is enabled or not */
  #if((STD_OFF == CANSM_VARIANT_POSTBUILD_SUPPORT)&&(STD_ON == CANSM_ENABLE_BUS_OFF_DELAY))
  boolean CanSMEnableBusOffDelay;
  #endif
  /* Transceiver ID */
  #if (STD_ON == CANSM_CANTRCV_SUPPORT)
  uint8 CanSmTranceiverId;
  #endif

  /* Number of controller Configured per Network */

  uint8 NumberOfController;


  /* Controller Index if single network */
  uint8 ControllerIndex;

  /* Threshold value for transition from L1 to L2 timer value */
  #if (STD_OFF == CANSM_BOR_COUNTER_MACRO_SUPPORT)
  CanSM_BusOffCntType BorCounterL1ToL2;
  #endif


  /* Timer Values for Bus OFF Recovery */
  #if (STD_OFF == CANSM_BUSOFF_RECOVERY_MACRO_SUPPORT)
  CanSM_TimerType CanSMBorTimeL1;
  CanSM_TimerType CanSMBorTimeL2;
  CanSM_TimerType BorTimeTxEnsured;
  #endif

  /* @Trace: CanSM_SUD_DATATYPE_009 */
  #if(STD_ON == CANSM_DEM_STATUS)
  /* Dem Event ID */
  Dem_EventIdType BusOffEventId;

  Dem_EventIdType TimeOutEventId;
  #endif
} CanSM_StaticNetworkType;


typedef P2FUNC(void, CANSM_CODE, CanSM_FunPtrType)(VAR(NetworkHandleType,CANSM_VAR) networkHandle);

/* Structure to pointers to function which mode transition in the CanSM */
/* @Trace: CanSM_SUD_DATATYPE_019 */
typedef struct
{
  P2FUNC(void, CANSM_CODE, pTransFuncPtr) (VAR(NetworkHandleType,CANSM_VAR) networkHandle);
} CanSM_TransFuncPtrType;

/* @Trace: CanSM_SUD_DATATYPE_020 */
typedef struct
{
	
  /* Variable to store the mode status for the network */
  uint8 ModeStatus;
  
  /* Variable to store the requested mode status for the network */
  uint8 ReqModeStatus;
  
  /* Variable to store the mode requested for Controllers and Transceiver for the network */
  uint8 Mode;
  
  /* Variable to store controller count for the network */
  uint8 CanSMCtrlCount;
  
  /* Variable to store the internal state for the network */
  uint8 CanSMNWIntSubState;
  
  /* Variable to store the mode request repeat value for the network */
  uint8 CanSMModeReqReptMax;
  
    /* Variable to store the result for the valid baudrate check */
  #if (STD_ON == CANSM_SET_BAUDRATE_API)
  uint8 Result;
  #endif

  /* Bug #703 - Add to check duplicate Bus off Event while Bus Off Recovery */
  /* Variable to store the Bus Off Repetition */
  uint8 BusOffRep;
   
  /* Variable to store set baudrate mode */
  #if (STD_ON == CANSM_SET_BAUDRATE_API)
  CanSM_BaudrateDirect Baudrate;
  #endif

  /* variable to store baudrate config ID */
  #if (STD_ON == CANSM_SET_BAUDRATE_API)
  uint16 BaudRateConfigID;
  #endif

  /* Variable to store the timer value for the network */

  CanSM_TimerType Timer;

  /* Variable to store the Requested Time Value for the network */

  CanSM_TimerType CanSMModeReqReptTime;

  /* Variable to store the Bus off count value for the network */
  CanSM_BusOffCntType BusOffCounter;
  
} CanSM_NetworkType;

/* CanSM Passive status*/
/* @Trace: CanSM_SUD_DATATYPE_015 */
typedef enum
{
	CANSM_ECUPASSIVE = CANSM_TRUE,
	CANSM_ECU_NOT_PASSIVE = CANSM_FALSE
}CanSM_ECUPassiveType;



/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/
#if(STD_OFF == CANSM_VARIANT_POSTBUILD_SUPPORT)

/* Extern for CanSM_StaticNetwork */
#define CANSM_START_SEC_CONFIG_DATA_PREBUILD_32
#include "MemMap.h"
extern CONST(CanSM_StaticNetworkType, CANSM_CONST) CanSM_StaticNetwork[CANSM_NUMBER_OF_STATIC_NWS];
#define CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_32
#include "MemMap.h"

/* Extern for CanSM_InternalController */
#define CANSM_START_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"
extern CONST(uint8, CANSM_CONST) CanSM_InternalController[CANSM_LAST_CTRL_HANDLE+1];
#define CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"


/* Extern for CanSM_InternalNetwork */
#define CANSM_START_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"
extern CONST(NetworkHandleType, CANSM_CONST) CanSM_InternalNetwork[CANSM_LAST_NW_HANDLE+1];
#define CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"

/* Extern for CanSM_StaticController */
#define CANSM_START_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"
extern CONST(uint8, CANSM_CONST) CanSM_StaticController[CANSM_NUMBER_OF_STATIC_CTRL];
#define CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"

//CANSM_START_SEC_CONFIG_DATA_PREBUILD_8
#if (STD_ON == CANSM_CANTRCV_SUPPORT)
/* Extern for CanSM_StaticTrvToNw */
#define CANSM_START_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"
/*  polyspace<MISRA-C:8.12:Not a defect:Justify with annotations> No Impact of this rule violation(Array size will fixed in linking time)   */
extern CONST(NetworkHandleType, CANSM_CONST) CanSM_StaticTrvToNw[CANSM_LAST_TRCV_HANDLE+1];

#define CANSM_STOP_SEC_CONFIG_DATA_PREBUILD_8
#include "MemMap.h"
#endif

#endif /* end of #if(STD_ON == CANSM_VARIANT_POSTBUILD_SUPPORT */


/* Global function pointer array */
#define CANSM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#if (STD_ON == CANSM_PNC_AVAILABILITY)
extern CONST(CanSM_TransFuncPtrType, CANSM_CONST) CanSM_TransFuncPtr[CANSM_INTERNALFUNCTIONS_IN_MAINFUNCTION];
#else
extern CONST(CanSM_TransFuncPtrType, CANSM_CONST) CanSM_TransFuncPtr[CANSM_INTERNALFUNCTIONS_IN_MAINFUNCTION];
#endif
#define CANSM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"


#endif /* CANSM_INTERNALTYPES_H */


/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
