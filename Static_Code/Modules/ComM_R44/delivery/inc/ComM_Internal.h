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
**  SRC-MODULE: ComM_Internal.h                                               **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
**                                                                            **
**  PURPOSE   : Provision of Internal Main Function and                       **
**              sub functions to change the mode                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                By               Description            **
********************************************************************************
** 1.1.7          31-Jan-2024         MUKim            CP44-3149              **
** 1.1.4          07-Mar-2022         ThuanVT          CP44-1152              **
** 1.1.0          12-Aug-2022         ThuanVT          R44-Redmine #27547     **
** 1.0.4.1        20-Jun-2022         SMKwon           CP44-115               **
** 1.0.4          29-Apr-2022         ThuanVT          R44-Redmine #25646,    **
**                                                     #25674                 **
** 1.0.2          05-Apr-2021         DatNXT           R44-Redmine #14793,    **
**                                                     #14801                 **
** 1.0.0          15-Dec-2020         JsLim            Initial Version        **
*******************************************************************************/

#ifndef COMM_INTERNAL_H
#define COMM_INTERNAL_H

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* ComM Pre Compile Types header file */
/* @Trace: ComM_SUD_MACRO_004  */
/* @Trace: ComM_SUD_MACRO_006  */
#include "ComM_PCTypes.h"
#if (COMM_LINNETWORK_PRESENT == STD_ON)
#include "LinSM.h"                /* LinSM Module header file */
#endif
#if (COMM_CANNETWORK_PRESENT == STD_ON)
#include "CanSM.h"                /* CanSM Module header file */
#endif
#if (COMM_FRNETWORK_PRESENT == STD_ON)
#include "FrSM.h"                 /* FrSM Module header file */
#endif
#if (COMM_ETHNETWORK_PRESENT == STD_ON)
#include "EthSM.h"                /* EthSM Module header file */
#endif
#if (COMM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"                  /* Det Module header file */
#endif
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#define COMM_START_SEC_CODE
#include "MemMap.h"

/* Extern for ComM Switch Communication Mode */
extern FUNC(void, COMM_CODE) ComM_SwitchComMMode(uint8 chIndex, ComM_ModeType
  comMMode);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */

/* Extern for ComM Switch Mode to Full communication */
extern FUNC(void, COMM_CODE) ComM_SwitchToFullCom(uint8 chIndex);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */

/* Extern for ComM Switch Mode to no communication */
extern FUNC(void, COMM_CODE) ComM_SwitchToNoCom(uint8 chIndex);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */

/* Extern for processing the Pending Request in no Communication */
extern FUNC(boolean, COMM_CODE) ComM_NoComNoPendingRequest(uint8 chIndex);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */

/* Extern for processing the Request Pending in no Communication */
extern FUNC(void, COMM_CODE) ComM_NoComRequestPending(uint8 chIndex, boolean
  passiveWakeFlag);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_ETHNETWORK_PRESENT == STD_ON))
/* #define COMM_START_SEC_CODE
#include "MemMap.h" */

/* Extern for switching from ComM Full Communication To Silent Communication */
extern FUNC(void, COMM_CODE) ComM_FullComMToSilentComM(uint8 chIndex);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */
#endif

#if ((COMM_WAKEUP_INHIBITION_ENABLED == STD_ON) ||\
  (COMM_MODE_LIMITATION_ENABLED == STD_ON))
/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
extern FUNC(boolean, COMM_CODE) ComM_RequestComModeInhibitionCheck(uint8
  chIndex, ComM_ModeType comMMode);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */
#endif

#if ((COMM_FULLCOMM_REQ_NOTFN_ENABLED == STD_ON) &&\
  (COMM_DIRECT_USER_MAPPING == STD_OFF))
/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
extern FUNC(void, COMM_CODE) ComM_RequestComModeRteUpdate(uint8 chIndex, uint8
  userInx, ComM_ModeType comMMode);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */
#endif

#if (COMM_DEV_ERROR_DETECT == STD_ON)
/* #define COMM_START_SEC_CODE
#include "MemMap.h" */

/* Extern for ComM_UserDETCheck*/
extern FUNC(Std_ReturnType, COMM_CODE) ComM_UserDETCheck(ComM_UserHandleType
  User, uint8 ApiId);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */

/* Extern for ComM_ChannelDETCheck*/
extern FUNC(Std_ReturnType, COMM_CODE) ComM_ChannelDETCheck(NetworkHandleType
  Channel, uint8 ApiId);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */
#endif /* (COMM_DEV_ERROR_DETECT == STD_ON) */

#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
extern FUNC(void, COMM_CODE) ComM_PncUserHandle(PNCHandleType tmpPncIndex,
  ComM_ModeType comMode);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
extern FUNC(void, COMM_CODE) ComM_PncUserLowestMode(uint8 userIndx);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_GetCurComModePNC(uint8 userIndex,
  P2VAR(ComM_ModeType, AUTOMATIC, COMM_APPL_DATA) lowestMode);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */

/* Static function if current PNC mode is Full */
extern FUNC(void, COMM_CODE) ComM_PNCFullMode(PNCHandleType tmpPncIndex);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */

/* Static function if current PNC mode is No */
extern FUNC(void, COMM_CODE) ComM_PNCNoMode(PNCHandleType tmpPncIndex);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
extern FUNC(void, COMM_CODE) ComM_PNCComSigFullCom(uint8 chIndex);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
extern FUNC(void, COMM_CODE) ComM_PNCNetwReq(PNCHandleType tmpPncIndex, uint8 chIndex);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
#if (((COMM_PNC_EIRA_SIGNAL_PRESENT == STD_ON) ||\
  (COMM_PNC_ERA_SIGNAL_PRESENT == STD_ON)) &&\
  (COMM_PNC_RX_SIGNAL_PRESENT == STD_ON))
extern FUNC(void, COMM_CODE) ComM_ComSignalReception(Com_SignalIdType signalId,
  P2CONST(uint8, AUTOMATIC, COMM_APPL_DATA) comSignalRxPtr );
#endif
/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
extern FUNC(void, COMM_CODE) ComM_PNCFullModePrepareSleep(PNCHandleType tmpPncIndex);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
extern FUNC(void, COMM_CODE) ComM_PNCFullModeReadySleep(PNCHandleType tmpPncIndex);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
extern FUNC(void, COMM_CODE) ComM_PNCFullModeRequested(PNCHandleType tmpPncIndex);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_RequestComModePNC(uint8
  userInx, ComM_ModeType comMode);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
extern FUNC(void, COMM_CODE) ComM_GetMaxComModePNC(uint8 userIndex,
  P2VAR(ComM_ModeType, AUTOMATIC, COMM_APPL_DATA) lowestMode);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

#endif /*(COMM_PNC_SUPPORT == STD_ON)&& (COMM_PNC_ENABLED == STD_ON)*/
#endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
        *STD_ON)) */

#if (COMM_DIRECT_CHANNEL == STD_ON)
/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_RequestComModeDirectChnl(uint8
  userInx, ComM_ModeType comMode);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
extern FUNC(Std_ReturnType, COMM_CODE) ComM_GetCurComModeDirectChnl(uint8
  userChannelIndex, uint8 noOfChannels, P2VAR(ComM_ModeType, AUTOMATIC,
    COMM_APPL_DATA) lowestMode);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
extern FUNC(void, COMM_CODE) ComM_GetMaxComModeDirectChnl(uint8
  userChannelIndex, uint8 noOfChannels, P2VAR(ComM_ModeType, AUTOMATIC,
    COMM_APPL_DATA) lowestMode);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

#endif /* End of if (COMM_DIRECT_CHANNEL == STD_ON) */

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */

/* STATIC function if current comm mode is Full comm */
extern FUNC(void, COMM_CODE) ComM_FullComMode(uint8 chIndex);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */

/* STATIC function if current comm mode is No comm */
extern FUNC(void, COMM_CODE) ComM_NoComMode(uint8 chIndex);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_ETHNETWORK_PRESENT == STD_ON))
/* #define COMM_START_SEC_CODE
#include "MemMap.h" */

/* STATIC function if current comm mode is Silent comm */
extern FUNC(void, COMM_CODE) ComM_SilentComMode(uint8 chIndex);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */
#endif

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
extern FUNC(void, COMM_CODE) ComM_FullComNetwReq(uint8 chIndex);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
extern FUNC(void, COMM_CODE) ComM_FullComReadySleep(uint8 chIndex);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
extern FUNC(void, COMM_CODE) ComM_FullComNetwReqSubThree(uint8 chIndex);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

#if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))
/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
extern FUNC(uint8, COMM_CODE) ComM_FullComNetwReqSubOne(uint8 chIndex);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */
#endif

#if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
#if (COMM_REFERENCE_CHANEL == STD_ON)
/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
extern FUNC(void, COMM_CODE)
                           ComM_SwitchReadySleepWithManagedChannel(uint8 chIndex);

/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */
#endif
#endif

/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
extern FUNC(void, COMM_CODE) ComM_SwithFullModeReference(uint8 chIndex);
/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */

#if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
extern FUNC(void, COMM_CODE) ComM_FullComNetwReqSubTwo(uint8 chIndex);
/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */
#endif

#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if (COMM_PNC_GW_ENABLED == STD_ON)
#if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO)
/* #define COMM_START_SEC_CODE
#include "MemMap.h" */
extern FUNC(void, COMM_CODE)
                  ComM_PNCNetwReq_PassiveGW(PNCHandleType pncIndex, uint8 handleChnlId);
extern FUNC(void, COMM_CODE) ComM_ProcessTxSignal(uint16 signalTxIndex,
  uint16 signalHandleId, uint8 byteIndex, uint8 mask, boolean isPncCleared);
/* #define COMM_STOP_SEC_CODE
#include "MemMap.h" */
#endif
#endif
#endif

extern FUNC(void, COMM_CODE) ComM_ClearGlobalVariables(void);

#if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
  (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))
extern FUNC(uint8, COMM_CODE) ComM_FullComNetwReqSetFlagMode(uint8 chIndex);
#else
extern FUNC(void, COMM_CODE) ComM_FullComNetwReqSetFlagMode(uint8 chIndex);
#endif

extern FUNC(void, COMM_CODE) ComM_FullComReadySleepReleaseNmBus(uint8 chIndex);

extern FUNC(void, COMM_CODE) ComM_FullComReadySleepSwitchMode(uint8 chIndex);

#if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)
extern FUNC(void, COMM_CODE) ComM_NoComNoPendingReleaseNmBus(uint8 chIndex);
#endif

extern FUNC(boolean, COMM_CODE) ComM_CheckPassiveAndSyncWakeUp(uint8 chIndex);

extern FUNC(void, COMM_CODE) ComM_NoComNoPendingRequestSetSubMode(uint8 chIndex,
  boolean fullFlag, boolean passiveWakeFlag);

extern FUNC(void, COMM_CODE) ComM_FullComModePassiveWakeUp(uint8 chIndex, boolean
  passiveWakeFlag);

#if (COMM_DIRECT_USER_MAPPING == STD_OFF)  
extern FUNC(void, COMM_CODE) ComM_IndicatePncUserLowestMode(uint8 userIndx);
#endif

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

#endif /* COMM_INTERNAL_H */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

