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
**  INC-MODULE: ComM_Ram.c                                                    **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
**                                                                            **
**  PURPOSE   : Provision of Communication Manager Ram                        **
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
** 1.1.0          12-Aug-2022         ThuanVT          R44-Redmine #27547,    **
**                                                     #29733                 **
** 1.0.4.1        20-Jun-2022         SMKwon           CP44-115               **
** 1.0.4          29-Apr-2022         ThuanVT          R44-Redmine #25646     **
** 1.0.2          05-Apr-2021         DatNXT           R44-Redmine #14793,    **
**                                                     #14801                 **
** 1.0.0          15-Dec-2020         JsLim            Initial Version        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: ComM_SUD_MACRO_002 */
/* @Trace: SRS_ComM_AR_00217 SRS_ComM_AR_00217 SRS_ComM_AR_00223
 * SRS_ComM_AR_00224 SRS_ComM_AR_00226 SRS_ComM_AR_00227 SRS_ComM_AR_00228
 * SRS_ComM_AR_00229 SRS_ComM_AR_00230 SRS_ComM_AR_00231 SRS_ComM_AR_00233
 * SRS_ComM_AR_00234 SRS_ComM_AR_00237 SRS_ComM_AR_00238 SRS_ComM_AR_00239 
 */
/* @Trace: ComM_SUD_MACRO_005   */
#include "ComM_Ram.h"             /* Global variables header file */

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
#define COMM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* This array contains the Sub States of the channel */
VAR(ComM_StateType, COMM_VAR_POWER_ON_INIT)
ComM_SubComMode[COMM_TOTAL_CHANNELS];
#define COMM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define COMM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* This array contains the Requested Com Mode of the Channel */
VAR(ComM_ModeType, COMM_VAR_POWER_ON_INIT)
ComM_ReqedComModeCnt[COMM_TOTAL_CHANNELS];
#define COMM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define COMM_START_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* This array contains the Requested Communication mode of the User */
VAR(ComM_ModeType, COMM_VAR_POWER_ON_INIT)
ComM_RequestedComMode[COMM_TOTAL_USERS];
#define COMM_STOP_SEC_VAR_POWER_ON_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define COMM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Global Variable to store initialization status of ComM */
VAR(ComM_InitStatusType, COMM_VAR_POWER_ON_INIT) ComM_InitFlag;
#define COMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define COMM_START_SEC_VAR_CLEARED_32
#include "MemMap.h"

/* This array contains the Timeout Counter of the Channel: Maximum Range */
VAR(ComM_TimeType, COMM_VAR_POWER_ON_INIT)
ComM_TimeCnt[COMM_TOTAL_CHANNELS];
#define COMM_STOP_SEC_VAR_CLEARED_32
#include "MemMap.h"

#if ((COMM_FULLCOMM_REQ_NOTFN_ENABLED == STD_ON) &&\
  (COMM_DIRECT_USER_MAPPING == STD_OFF))
#define COMM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* This array contains the Number of Full Communication Requests
   of the Channel during Inhibition State */
VAR(ComM_UserHandleArrayType, COMM_VAR_POWER_ON_INIT)
ComM_FullComReq[COMM_TOTAL_CHANNELS];
#define COMM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if ((COMM_NVM_BLOCK_DESCRIPTOR == STD_ON) &&\
    (COMM_NVMSTORE_CHANNELS != COMM_ZERO))
#define COMM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

/* This array contains NvM Inhibition Status of the Channel */
VAR(uint8, COMM_VAR_POWER_ON_INIT)
ComM_NvmChannelInhibition[COMM_NVMSTORE_CHANNELS];
#define COMM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif

#define COMM_START_SEC_VAR_SAVED_ZONE_UNSPECIFIED
#include "MemMap.h"

/* This variable contains the information which is to be stored in NvM */
VAR(ComM_DataType, COMM_VAR_NOINIT) ComM_Data;
#define COMM_STOP_SEC_VAR_SAVED_ZONE_UNSPECIFIED
#include "MemMap.h"

#define COMM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

/* This array contains the Inhibition status of the Channels */
VAR(ComM_InhibitionStatusType, COMM_NO_INIT_DATA)
ComM_ChannelInhibition[COMM_TOTAL_CHANNELS];
#define COMM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))

#define COMM_START_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

/* This array contains the Sub PNC mode of the Pncs */
VAR(ComM_PncModeType, COMM_NO_INIT_DATA)
ComM_SubPNCMode[COMM_TOTAL_PNCS];
#define COMM_STOP_SEC_VAR_NO_INIT_UNSPECIFIED
#include "MemMap.h"

#define COMM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"

/* This array contains the PNC Timeout Counter of the Channel */ /*#13018*/
VAR(uint16, COMM_VAR_POWER_ON_INIT) ComM_PncTimeCnt[COMM_TOTAL_PNCS];
#define COMM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
        *(COMM_FRNETWORK_PRESENT == STD_ON)) */
#endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
        *STD_ON)) */

#define COMM_START_SEC_VAR_POWER_ON_CLEARED_8
#include "MemMap.h"
/* @Trace: SRS_ComM_AR_00006 */
/* This array contains the Current Communication mode of the channels */
VAR(uint8, COMM_VAR_POWER_ON_INIT) ComM_CurComMode[COMM_TOTAL_CHANNELS];

#define COMM_STOP_SEC_VAR_POWER_ON_CLEARED_8
#include "MemMap.h"

#define COMM_START_SEC_VAR_POWER_ON_CLEARED_8
#include "MemMap.h"

/* This array contains the Network indications of the Channel */
VAR(uint8, COMM_VAR_POWER_ON_INIT)
ComM_NmIndication[COMM_TOTAL_CHANNELS];
#define COMM_STOP_SEC_VAR_POWER_ON_CLEARED_8
#include "MemMap.h"

#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
#if (COMM_TOTAL_TX_SIGNALS != COMM_ZERO)
#define COMM_START_SEC_VAR_POWER_ON_CLEARED_8
#include "MemMap.h"

/* This array contains the signal to be TX from ComM */
VAR(uint8, COMM_VAR_POWER_ON_INIT) ComM_SignalTx[COMM_TOTAL_TX_SIGNALS][PNC_COM_MAX_INFO];
#define COMM_STOP_SEC_VAR_POWER_ON_CLEARED_8
#include "MemMap.h"
#endif
#endif
#endif

#define COMM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"

/* Global variable to store the number of channels left No Communication mode
 *   and entered Full Communication mode */
VAR(uint16, COMM_VAR_POWER_ON_INIT) ComM_ChannelsFullComMode;
#define COMM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define COMM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

/* This array contains whether Network is requested for the Channel */
VAR(uint8, COMM_VAR_POWER_ON_INIT) ComM_NmRequested[COMM_TOTAL_CHANNELS];
#define COMM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#if (COMM_FULL_NMVARIANT_SUPPORT == STD_ON)

#define COMM_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"

/* This array contains the if SM is requested or not for the channels */
VAR(boolean, COMM_VAR_POWER_ON_INIT)
ComM_NmRequestProcessing[COMM_TOTAL_CHANNELS];
#define COMM_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"
#endif

#define COMM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"

/* This array contains the Inhibited Communication request of the channels
 *   during bus wake up inhibition */
VAR(uint8, COMM_VAR_POWER_ON_INIT)
ComM_InhibitionReqst[COMM_TOTAL_CHANNELS];
#define COMM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#define COMM_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"

/* This array contains the information to track the user RTE indication */
VAR(boolean, COMM_VAR_POWER_ON_INIT)
ComM_UserRteInd[COMM_TOTAL_USERS];
#define COMM_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"

#define COMM_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"

/* This array contains the if SM is requested or not for the channels */
VAR(boolean, COMM_VAR_POWER_ON_INIT)
ComM_ModeRequested[COMM_TOTAL_CHANNELS];
#define COMM_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"

#define COMM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* This array contains the wake up indication of the channels */
VAR(boolean, COMM_VAR_POWER_ON_INIT)
ComM_WakeupIndication[COMM_TOTAL_CHANNELS];
#define COMM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"


#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
#define COMM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* This array contains the wake up indication of the channels */
VAR(boolean, COMM_VAR_POWER_ON_INIT)
ComM_PNCWakeupIndication[COMM_TOTAL_PNCS];
#define COMM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif
#endif

#if (COMM_MODE_LIMITATION_ENABLED == STD_ON)
#define COMM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* Global Variable to store Limit ECU to No Communication inhibition */
VAR(boolean, COMM_VAR_POWER_ON_INIT) ComM_LimitEcuToNoCom;
#define COMM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif

#define COMM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* Global variable to indicate the DCM active diagnostic mode detected */
VAR(boolean, COMM_VAR_POWER_ON_INIT)
ComM_DcmActiveDiagnostic[COMM_TOTAL_CHANNELS];
#define COMM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define COMM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* Global variable to indicate DCM inactive diagnostic mode detected */
VAR(boolean, COMM_VAR_POWER_ON_INIT)
ComM_DcmInactiveDiagnostic[COMM_TOTAL_CHANNELS];
#define COMM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define COMM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* Global variable to store if communication is allowed or not */
/* @Trace: SRS_ComM_AR_00008 */
VAR(boolean, COMM_VAR_POWER_ON_INIT)
ComM_CommunicationAllowedFlag[COMM_TOTAL_CHANNELS];

#define COMM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) &&\
  (COMM_FULL_NMVARIANT_SUPPORT == STD_ON))
#define COMM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* Global variable to store managing channel request full mode */
VAR(boolean, COMM_VAR_POWER_ON_INIT)
ComM_ManagingSetMode[COMM_TOTAL_CHANNELS];
#define COMM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif

#define COMM_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"

/* This array contains the pnc full com requested received PNC signal info */
VAR(boolean, COMM_VAR_POWER_ON_INIT) ComM_PncReqtedflag[COMM_TOTAL_CHANNELS];
#define COMM_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"

#if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED == STD_ON))
#if ((COMM_CANNETWORK_PRESENT == STD_ON) || (COMM_FRNETWORK_PRESENT == STD_ON) ||\
     (COMM_ETHNETWORK_PRESENT == STD_ON))
#define COMM_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"

/* This array contains the User PNC Requests */
VAR(boolean, COMM_NO_INIT_DATA)
ComM_RequestedPNCMode[COMM_TOTAL_PNCS];
#define COMM_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"

#define COMM_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"

/* This array contains the pnc Requested flags */
VAR(boolean, COMM_VAR_POWER_ON_INIT) ComM_ReqFlag[COMM_TOTAL_PNCS];
#define COMM_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"

#if (COMM_0PNCVECTOR_AVOIDANCE == STD_ON)
#define COMM_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"

/* This array contains the pnc Requested flags */
VAR(boolean, COMM_VAR_POWER_ON_INIT) ComM_ReleaseFlag[COMM_TOTAL_PNCS];
#define COMM_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"
#endif

#define COMM_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"

/* This array contains the pnc Requested to pnc ready flags */
VAR(boolean, COMM_VAR_POWER_ON_INIT)
ComM_ReqToReadyFlag[COMM_TOTAL_PNCS];
#define COMM_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"

#define COMM_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"

/* This array contains the status of PNC for Rx EIRA */
VAR(boolean, COMM_VAR_POWER_ON_INIT) ComM_PncRxEIRA[COMM_TOTAL_PNCS];
#define COMM_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"

#define COMM_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"

/* This array contains the Rx EIRA signal of Pncs */
VAR(boolean, COMM_VAR_POWER_ON_INIT)
/* polyspace +1 MISRA-C3:2.2 [Justified:Low] "The call to this function will have effect depending on configuration" */
ComM_PncRxEIRASignal[(uint8)(COMM_TOTAL_PNCS*COMM_TOTAL_SIGNALS)];
#define COMM_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"

#if (COMM_PNC_GW_ENABLED == STD_ON)
#define COMM_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"

/* This array contains the status of PNC for Rx ERAn */
VAR(boolean, COMM_VAR_POWER_ON_INIT) ComM_PncRxERAn[COMM_TOTAL_PNCS];
#define COMM_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"

#define COMM_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"

/* This array contains the Rx ERA signal of Pncs */
VAR(boolean, COMM_VAR_POWER_ON_INIT)
/* polyspace +1 MISRA-C3:2.2 [Justified:Low] "The call to this function will have effect depending on configuration" */
ComM_PncRxERASignal[(uint8)(COMM_TOTAL_PNCS*COMM_TOTAL_SIGNALS)];
#define COMM_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"
#endif /* End of if (COMM_PNC_GW_ENABLED == STD_ON) */
#endif /* End of if ((COMM_CANNETWORK_PRESENT == STD_ON) ||
        *(COMM_FRNETWORK_PRESENT == STD_ON)) */
#endif /* End of if ((COMM_PNC_SUPPORT == STD_ON) && (COMM_PNC_ENABLED ==
        *STD_ON)) */

/* =================Global for implement Post-Build ==========================*/
#if (COMM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
#define COMM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array containing user data structure information dependcy to PNC */
P2CONST(ComM_UserPNCRelatedType, AUTOMATIC, COMM_CONST)
                                                      ComM_UserPNCRelatedGlobal;
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define COMM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array containing channel data structure information dependcy to PNC */
P2CONST(ComM_ChannelsPNCRelatedType, AUTOMATIC, COMM_CONST)
                                                  ComM_ChannelsPNCRelatedGlobal;
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* ===========User========= */
#define COMM_START_SEC_CONST_16
#include "MemMap.h"
/* Pnc indices array : In Users, Index --> PNC Index*/
P2CONST(PNCHandleType, AUTOMATIC, COMM_CONST) ComM_PncUserInxArrGlobal;
#define COMM_STOP_SEC_CONST_16
#include "MemMap.h"

#define COMM_START_SEC_CONST_8
#include "MemMap.h"
/* User to PNC map array for PNC associated with the User */
P2CONST(ComM_UserHandleType, AUTOMATIC, COMM_CONST) ComM_PncToUserMappingGlobal;
#define COMM_STOP_SEC_CONST_8
#include "MemMap.h"

/* ===========Channel========= */
#define COMM_START_SEC_CONST_8
#include "MemMap.h"
/* Channel indices array : In Pnc, Channel Index --> Channel ID */
P2CONST(NetworkHandleType, AUTOMATIC, COMM_CONST) ComM_ChnPncInxArrGlobal;
#define COMM_STOP_SEC_CONST_8
#include "MemMap.h"

#define COMM_START_SEC_CONST_16
#include "MemMap.h"
/* Channel to PNC map array : In Channels, Channel Index --> PNC Index */
P2CONST(PNCHandleType, AUTOMATIC, COMM_CONST) ComM_ChannelToPncMappingGlobal;
#define COMM_STOP_SEC_CONST_16
#include "MemMap.h"

/* ===========PNC========= */
#define COMM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Array containing PNC data structure information */
P2CONST(ComM_PncsType, AUTOMATIC, COMM_CONST) ComM_PncsGlobal;
#define COMM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

#define COMM_START_SEC_CONST_16
#include "MemMap.h"
/* Array to get Pnc sequence*/
P2CONST(PNCHandleType, AUTOMATIC, COMM_CONST) ComM_PncMapArrayGlobal;
#define COMM_STOP_SEC_CONST_16
#include "MemMap.h"

#define COMM_START_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global Variable to store state Pnc enabled for config variant */
VAR(boolean, COMM_VAR_POWER_ON_INIT) ComM_PncEnabledFlashPB;
#define COMM_STOP_SEC_VAR_POWER_ON_CLEARED_BOOLEAN
#include "MemMap.h"
#endif /* End of if COMM_VARIANT_POSTBUILD_SUPPORT == STD_ON */
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

