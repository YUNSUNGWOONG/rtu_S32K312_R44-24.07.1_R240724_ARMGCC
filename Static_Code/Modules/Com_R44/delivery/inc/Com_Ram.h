/*******************************************************************************
**                                                                            **
**  (C) 2021 HYUNDAI AUTOEVER Corp.                                           **
**                                                                            **
**  Confidential Proprietary Information. Distribution Limited.               **
**  This source code is permitted to be used only in projects contracted      **
**  with Hyundai Autoever, and any other use is prohibited.                   **
**  If you use it for other purposes or change the source code,               **
**  you may take legal responsibility.                                        **
**  In this case, There is no warranty and technical support.                 **
**                                                                            **
**  SRC-MODULE: Com_Ram.h                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of declaration of RAM area.                         **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By          Description                            **
********************************************************************************
** 1.1.9.0   28-Mar-2023   PhucNHM     CP44-267                               **
** 1.1.4.0   11-Oct-2022   HaoTA4      CP44-770                               **
** 1.1.4.0   27-Jul-2022   PhucNHM     R44-Redmine #29406                     **
** 1.1.3.1   21-Jun-2022   SMKwon      CP44-109                               **
** 1.1.2     09-Apr-2022   PhuPV10     R44-Redmine #24777 #25517              **
** 1.1.1     25-Mar-2022   PhuPV10     R44-Redmine #25075 #25573 #25073       **
** 1.1.0     10-Feb-2022   PhucNHM     R44-Redmine #19316 #23495 #23725       **
**                                                 #23982 #24211              **
** 1.0.1     28-Sep-2021   DuyNGB      R44-Redmine #20139                     **
** 1.0.0     04-Dec-2020   SMKwon      Initial Version                        **
*******************************************************************************/
#ifndef COM_RAM_H
#define COM_RAM_H

#include "Com_PCTypes.h"
#include "ComStack_Cfg.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/
/* @Trace: Com_SUD_GLOBALVAR_016 */
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
/* Global variable to store initialization status of COM Module */
extern VAR (Com_StatusType, COM_VAR) Com_GddComStatus;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
 
 /* @Trace: Com_SUD_GLOBALVAR_017 */
#if((COM_RX_REPLICATION == STD_ON) && \
            (COM_RX_IPDU_COUNTER_ENABLED == STD_ON))
#define COM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" 
/* Global variable to store initialization status of COM Module */
extern VAR (boolean, COM_VAR) Com_GblNoConfirmation;
#define COM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif

/* @Trace: Com_SUD_GLOBALVAR_018 */
#if(COM_TX_IPDU_COUNTER_ENABLED == STD_ON)
#define COM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" 
/* Global variable to store initialization status of COM Module */
extern VAR (uint8, COM_VAR) Com_GaaCounterStatusFlag[COM_TX_IPDU_COUNTER_SIZE];
#define COM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" 
#endif

/* @Trace: Com_SUD_GLOBALVAR_019 */
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
/*  I-PDU group status. */
extern VAR(uint8, COM_VAR) Com_GaaIpduGrpEnStatus[COM_IPDU_GRP_VECTOR_SIZE];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 

/* @Trace: Com_SUD_GLOBALVAR_020 */
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
/*  I-PDU group DeadLine monitoring status. */
extern VAR(uint8, COM_VAR) Com_GaaIpduGrpDmStatus[COM_IPDU_GRP_VECTOR_SIZE];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 

/* @Trace: Com_SUD_GLOBALVAR_021 */
#if((COM_RX_SIG_GATEWAY == STD_ON) || (COM_RX_SIGNAL_GW_DES == STD_ON))
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED_ALIGN4
#include "MemMap.h" 
/*  signal gateway process temporary buffer */
extern VAR(uint8, COM_VAR) Com_GaaSignalGWBuffer[COM_MAX_TOTAL_PDU_SIZE];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED_ALIGN4
#include "MemMap.h"
#endif

/* @Trace: Com_SUD_GLOBALVAR_022 */
#if(COM_RX_SIG_GATEWAY == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED_ALIGN4
#include "MemMap.h" 
/*  signal gateway process temporary sub buffer */
extern VAR(uint8, COM_VAR) Com_GaaSignalGWBufferSub[COM_MAX_TOTAL_PDU_SIZE];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED_ALIGN4
#include "MemMap.h"
#endif

/* @Trace: Com_SUD_GLOBALVAR_024 */
#if((COM_RX_SIGNAL_IMMEDIATENOTIFY == STD_ON) || \
                    (COM_RX_SIGGROUP_IMMEDIATENOTIFY == STD_ON))
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED_ALIGN4
#include "MemMap.h" 
/*  signal filter, invalid, UB process temporary buffer */
extern VAR(uint8, COM_VAR) Com_GaaSignalValidCKBufferIM[COM_MAX_TOTAL_PDU_SIZE];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED_ALIGN4
#include "MemMap.h"
#endif

/* @Trace: Com_SUD_GLOBALVAR_025 */
#if(COM_RX_IPDU_DEFERRED == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED_ALIGN4
#include "MemMap.h" 
/*  signal filter, invalid, UB process temporary buffer */
extern VAR(uint8, COM_VAR) Com_GaaSignalValidCKBufferDE[COM_MAX_TOTAL_PDU_SIZE];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED_ALIGN4
#include "MemMap.h"
#endif

/* @Trace: Com_SUD_GLOBALVAR_026 */
#if(COM_TX_SIGGROUP_ARRAY_TMS == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
/*  signal filter, invalid, UB process temporary buffer */
extern VAR(uint8, COM_VAR) Com_GaaSignalGrpSigArray[COM_MAX_TOTAL_PDU_SIZE];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

/* @Trace: Com_SUD_GLOBALVAR_007 */
#if(COM_RX_IPDU_COUNTER_ENABLED == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for maintaining Ipdu Counter status. Indicates whether the Ipdu
counter is started/Enabled or not */
extern VAR(uint8, COM_VAR) 
Com_GaaRamIpduCounterSts[COM_RAM_IPDU_COUNTER_STS_SIZE];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

/* @Trace: Com_SUD_GLOBALVAR_008 */
#if(COM_RX_REPLICATION == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for maintaining Ipdu Replication status. Indicates whether the
Ipdu Replication is enabled is Enabled or not */
/* Change the declaration size as empty(#648) - 14.03.03 by Chan Kim START */
extern VAR(uint8, COM_VAR) Com_GaaRamIpduRepliSts[];
/* Change the declaration size as empty(#648) - 14.03.03 by Chan Kim END */
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

/* @Trace: Com_SUD_GLOBALVAR_009 */
#if(COM_RX_REPLICATION == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for maintaining Ipdu Replication count. Indicates the
number of Ipdus needed for Quorum voting to be complete */
/* Change the declaration size as empty(#648) - 14.03.03 by Chan Kim START */
extern VAR(uint8, COM_VAR) Com_GaaRxRepliCount[];
/* Change the declaration size as empty(#648) - 14.03.03 by Chan Kim END */
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

/* @Trace: Com_SUD_CONSTVAR_011 */
#define COM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* This global array holds the memory size of signal based on its type */
extern CONST(uint8, COM_CONST)
Com_GaaSigMemSize[COM_FIVE];
#define COM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"

/* @Trace: Com_SUD_GLOBALVAR_027 */
#if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
#if (COM_RX_IPDU_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
/*  Rx Ipdu Status */
extern VAR(PduIdType, COM_VAR) Com_GaaRxIpduStatus[COM_RX_IPDU_COUNT];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

/*#if(((COM_RX_IPDU_CALLOUT == STD_ON) && (COM_RX_TP_SUPPORT == STD_ON))\
 && (COM_RX_SIGGROUP_INVALID == STD_ON) ||(COM_RX_SIGNAL_INVALID == STD_ON))*/
 /* @Trace: Com_SUD_GLOBALVAR_030 */
#if(COM_RX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
extern VAR(uint8, COM_VAR) Com_GaaRxTPflg[COM_RX_IPDU_COUNT];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
#endif

/* @Trace: Com_SUD_GLOBALVAR_034 */
#if(COM_TX_IPDU_DM_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for allocating RAM area of Tx Dm Timer */
extern VAR(uint16, COM_VAR)  Com_GaaTxDMTimer[COM_TX_IPDU_DM_COUNT];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

/* #7705 */
/* @Trace: Com_SUD_GLOBALVAR_040 */
#if(COM_TX_SIGGROUP_GROUPSIG_TRIGONCHANGE == STD_ON)
#define COM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* This global array holds the status of Signal Group which configured as OnChange attribute with sub transfer property of Group Signal */
extern VAR(uint8, COM_VAR) Com_GaaSigGroupChangedStatus[];
#define COM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

/* @Trace: Com_SUD_CONSTVAR_032 */
#if(COM_RX_SIG_INGRP_GW_COUNT > COM_MACRO_ZERO)
#if(COM_RX_SIGNAL_GW_DES == STD_ON)
#define COM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array for GWRxSigInGrp structure */
extern CONST(Com_RxGWSigInGrp, COM_CONST) 
Com_GaaRxGWSigInGrp[COM_RX_SIG_INGRP_GW_COUNT];
#define COM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

/* @Trace: Com_SUD_GLOBALVAR_041 */
#if(COM_FILTER_STATUS_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* Global array for Filter Status */
extern VAR(uint8, COM_VAR)  Com_GaaFilterStatus[COM_FILTER_STATUS_COUNT];
#define COM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#else /* #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF) */

/* @Trace: Com_SUD_GLOBALVAR_109 */
#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* Global array for TxIpdu structure */
extern VAR(uint16, COM_VAR)Com_GlNoOfTxIpdu;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

/* @Trace: Com_SUD_GLOBALVAR_110 */
#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* Global array for TxIpdu structure */
extern VAR(uint16, COM_VAR)Com_GlNoOfTxSignal;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

/* @Trace: Com_SUD_GLOBALVAR_111 */
#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* Global array for TxIpdu structure */
extern VAR(uint16, COM_VAR)Com_GlNoOfIpduGrp;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

/* @Trace: Com_SUD_GLOBALVAR_112 */
#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* Global array for TxIpdu structure */
extern VAR(uint16, COM_VAR)Com_GlNoOfTxSigGrp;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

/* @Trace: Com_SUD_GLOBALVAR_113 */
#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* Global array for TxIpdu structure */
extern VAR(uint16, COM_VAR)Com_GlNoOfTxSigInGrp;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

/* @Trace: Com_SUD_GLOBALVAR_114 */
#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* Global array for TxIpdu structure */
extern VAR(uint16, COM_VAR)Com_GlNoOfRxIpdu;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

/* @Trace: Com_SUD_GLOBALVAR_115 */
#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* Global array for TxIpdu structure */
extern VAR(uint16, COM_VAR)Com_GlNoOfRxSignal;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

/* @Trace: Com_SUD_GLOBALVAR_116 */
#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* Global array for TxIpdu structure */
extern VAR(uint16, COM_VAR)Com_GlNoOfRxSigGrp;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

/* @Trace: Com_SUD_GLOBALVAR_117 */
#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* Global array for TxIpdu structure */
extern VAR(uint16, COM_VAR)Com_GlNoOfRxSigInGrp;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

/* @Trace: Com_SUD_GLOBALVAR_118 */
#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* Global array for TxIpdu structure */
extern VAR(uint16, COM_VAR)Com_GlNoOfTxIpduUngrp;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

/* @Trace: Com_SUD_GLOBALVAR_119 */
#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* Global array for TxIpdu structure */
extern VAR(uint16, COM_VAR)Com_GlNoOfRxIpduUngrp;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

/* @Trace: Com_SUD_GLOBALVAR_120 */
#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* Global array for TxIpdu structure */
extern VAR(uint16, COM_VAR)Com_GlNoOfTxIpduDMCnt;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

/* @Trace: Com_SUD_GLOBALVAR_121 */
#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
/* Global array for RxIpdu structure */
extern VAR(uint16, COM_VAR)Com_GlNoOfRxIpduDMCnt;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

/* @Trace: Com_SUD_GLOBALVAR_056 */
#if(COM_TX_SIGGROUP_GROUPSIG_TRIGONCHANGE == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* This global array holds the status of Signal Group which configured as OnChange attribute with sub transfer property of Group Signal */
extern P2VAR(uint8, AUTOMATIC, COM_VAR) Com_GaaSigGroupChangedStatus;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

/* @Trace: Com_SUD_GLOBALVAR_065 */
#if(COM_RX_SIG_INGRP_GW_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for GWRxSigInGrp structure */
extern P2CONST(Com_RxGWSigInGrp,AUTOMATIC, COM_CONST) 
Com_GaaRxGWSigInGrp;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

/* @Trace: Com_SUD_GLOBALVAR_078 */
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Filter Status */
extern P2VAR(uint8, AUTOMATIC, COM_VAR)  Com_GaaFilterStatus;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#endif /*#if (COM_VARIANT_POSTBUILD_SUPPORT == STD_ON) */

#if (STD_ON == COM_MULTI_CORE_SUPPORT)
/* @Trace: Com_SUD_CONSTVAR_069 */
#define COM_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, COM_CONST) Com_GaaRxSigPosition[];
#define COM_STOP_SEC_CONST_8
#include "MemMap.h"	

/* @Trace: Com_SUD_CONSTVAR_070 */
#define COM_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, COM_CONST) Com_GaaRxSigGroupPosition[];
#define COM_STOP_SEC_CONST_8
#include "MemMap.h"	

/* @Trace: Com_SUD_CONSTVAR_071 */
#define COM_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, COM_CONST) Com_GaaTxSigPosition[];
#define COM_STOP_SEC_CONST_8
#include "MemMap.h"	

/* @Trace: Com_SUD_CONSTVAR_072 */
#define COM_START_SEC_CONST_8
#include "MemMap.h"
extern CONST(uint8, COM_CONST) Com_GaaTxSigGroupPosition[];
#define COM_STOP_SEC_CONST_8
#include "MemMap.h"	

/* @Trace: Com_SUD_GLOBALVAR_124 */
#if(COM_SIG_NOTIF_CBK_COUNT>COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
extern VAR(uint8, COM_VAR) Com_GaaSigNotifCbkFlag[COM_SIG_NOTIF_CBK_COUNT];
#define COM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif /* (COM_SIG_NOTIF_CBK_COUNT>COM_MACRO_ZERO) */

/* @Trace: Com_SUD_GLOBALVAR_125 */
#if(COM_SIG_ERROR_CBK_COUNT>COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
extern VAR(uint8, COM_VAR) Com_GaaSigErrorCbkFlag[COM_SIG_ERROR_CBK_COUNT];
#define COM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif /* (COM_SIG_ERROR_CBK_COUNT>COM_MACRO_ZERO) */

/* @Trace: Com_SUD_GLOBALVAR_126 */
#if(COM_INV_NOTIF_CBK_COUNT>COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
extern VAR(uint8, COM_VAR) Com_GaaInvNotifCbkFlag[COM_INV_NOTIF_CBK_COUNT];
#define COM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif /* (COM_INV_NOTIF_CBK_COUNT>COM_MACRO_ZERO) */

/* @Trace: Com_SUD_GLOBALVAR_128 */
#if(COM_RX_IPDU_GWSTATUS_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for allocating RAM area of 8 bits for Rx GW I-PDU status */
extern VAR(uint8, COM_VAR) 
  Com_GaaRxGWIpduMulticoreStatus[COM_RX_IPDU_GWSTATUS_COUNT];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

/* @Trace: Com_SUD_GLOBALVAR_129 */
#define COM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global flag check DirectMode */
extern VAR(boolean, COM_VAR) Com_GaaMulticoreDirectMode;
#define COM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* @Trace: Com_SUD_GLOBALVAR_130 */
#define COM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global flag to request switch core */
extern VAR(boolean, COM_VAR) 
  Com_GaaMulticoreTriggerNotifyFlag[COM_MULTI_CORE_NUMBER];
#define COM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* @Trace: Com_SUD_GLOBALVAR_131 */
#define COM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global flag to request switch core by mainfunction */
extern VAR(boolean, COM_VAR) 
  Com_GaaMulticoreMainNotifyFlag[COM_MULTI_CORE_NUMBER];
#define COM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

/* @Trace: Com_SUD_GLOBALVAR_132 */
#if(COM_SIG_NOTIF_CBK_COUNT>COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
extern VAR(uint8, COM_VAR) Com_GaaMainSigNotifCbkFlag[COM_SIG_NOTIF_CBK_COUNT];
#define COM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif /* (COM_SIG_NOTIF_CBK_COUNT>COM_MACRO_ZERO) */

/* @Trace: Com_SUD_GLOBALVAR_133 */
#if(COM_SIG_ERROR_CBK_COUNT>COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
extern VAR(uint8, COM_VAR) Com_GaaMainSigErrorCbkFlag[COM_SIG_ERROR_CBK_COUNT];
#define COM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif /* (COM_SIG_ERROR_CBK_COUNT>COM_MACRO_ZERO) */

/* @Trace: Com_SUD_GLOBALVAR_134 */
#if(COM_INV_NOTIF_CBK_COUNT>COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
extern VAR(uint8, COM_VAR) Com_GaaMainInvNotifCbkFlag[COM_INV_NOTIF_CBK_COUNT];
#define COM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif /* (COM_INV_NOTIF_CBK_COUNT>COM_MACRO_ZERO) */
#else /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
#endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */

/*******************************************************************************
**                      Function Prototypes                                   **
*******************************************************************************/

#endif /* COM_RAM_H */
/* polyspace:end<MISRA-C:1.1:Not a defect:Justify with annotations> Not a defect */
/* polyspace-end MISRA2012:8.11 [Justified:Low] "To avoid generate many macros, this violation could be accepted" */
/* polyspace-end MISRA2012:8.6 [Justified:Low] "No impact of this rule violation" */

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
