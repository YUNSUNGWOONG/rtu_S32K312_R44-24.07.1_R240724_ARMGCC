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
**  SRC-MODULE: Com_Ram.c                                                     **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of initialization of RAM area.                      **
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
** 1.1.4.0   27-Jul-2022   PhucNHM     R44-Redmine #29440                     **
** 1.1.3.1   21-Jun-2022   SMKwon      CP44-109                               **
** 1.1.2     09-Apr-2022   PhuPV10     R44-Redmine #25517                     **
** 1.1.1     25-Mar-2022   PhuPV10     R44-Redmine #25573 #25073              **
** 1.1.0     10-Feb-2022   PhucNHM     R44-Redmine #19316 #23495 #23725       **
**                                                 #23982 #24211              **
** 1.0.1     28-Sep-2021   DuyNGB      R44-Redmine #20139                     **
** 1.0.0     04-Dec-2020   SMKwon      Initial Version                        **
*******************************************************************************/
/* polyspace-begin VARIABLE:* [Not a defect:Low] "System intended for multitasking" */

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Com.h"          /* Com header file */
#include "Com_Types.h"
#include "Com_PCTypes.h"
/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/
/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
/* Global variable to store initialization status of COM Module */
VAR (Com_StatusType, COM_VAR) Com_GddComStatus = COM_UNINIT;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
 
#if((COM_RX_REPLICATION == STD_ON) && \
            (COM_RX_IPDU_COUNTER_ENABLED == STD_ON))
#define COM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h" 
/* Global variable to store initialization status of COM Module */
VAR (boolean, COM_VAR) Com_GblNoConfirmation;
#define COM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_COUNTER_ENABLED == STD_ON)
#define COM_START_SEC_VAR_CLEARED_8
#include "MemMap.h" 
/* Global variable to store initialization status of COM Module */
VAR (uint8, COM_VAR) Com_GaaCounterStatusFlag[COM_TX_IPDU_COUNTER_SIZE];
#define COM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h" 
#endif

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
/*  I-PDU group status. */
VAR(uint8, COM_VAR) Com_GaaIpduGrpEnStatus[COM_IPDU_GRP_VECTOR_SIZE];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
/*  I-PDU group DeadLine monitoring status. */
VAR(uint8, COM_VAR) Com_GaaIpduGrpDmStatus[COM_IPDU_GRP_VECTOR_SIZE];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 

#if((COM_RX_SIG_GATEWAY == STD_ON) || (COM_RX_SIGNAL_GW_DES == STD_ON))
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED_ALIGN4
#include "MemMap.h" 
/*  signal gateway process temporary buffer */
VAR(uint8, COM_VAR) Com_GaaSignalGWBuffer[COM_MAX_TOTAL_PDU_SIZE];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED_ALIGN4
#include "MemMap.h"
#endif

#if(COM_RX_SIG_GATEWAY == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED_ALIGN4
#include "MemMap.h" 
/*  signal gateway process temporary sub buffer */
VAR(uint8, COM_VAR) Com_GaaSignalGWBufferSub[COM_MAX_TOTAL_PDU_SIZE];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED_ALIGN4
#include "MemMap.h"
#endif

#if((COM_RX_SIGNAL_IMMEDIATENOTIFY == STD_ON) || \
                    (COM_RX_SIGGROUP_IMMEDIATENOTIFY == STD_ON))
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED_ALIGN4
#include "MemMap.h" 
/*  signal filter, invalid, UB process temporary buffer */
VAR(uint8, COM_VAR) Com_GaaSignalValidCKBufferIM[COM_MAX_TOTAL_PDU_SIZE];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED_ALIGN4
#include "MemMap.h"
#endif

#if(COM_RX_IPDU_DEFERRED == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED_ALIGN4
#include "MemMap.h" 
/*  signal filter, invalid, UB process temporary buffer */
VAR(uint8, COM_VAR) Com_GaaSignalValidCKBufferDE[COM_MAX_TOTAL_PDU_SIZE];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED_ALIGN4
#include "MemMap.h"
#endif

#if(COM_TX_SIGGROUP_ARRAY_TMS == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
/*  signal filter, invalid, UB process temporary buffer */
VAR(uint8, COM_VAR) Com_GaaSignalGrpSigArray[COM_MAX_TOTAL_PDU_SIZE];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

/* Global variable to store config pointer */
#if (COM_VARIANT_POSTBUILD_SUPPORT == STD_ON)/******************************************************************************/

#if(COM_RX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
VAR(uint8, COM_VAR) Com_GaaRxTPflg[COM_RX_IPDU_COUNT_MAX];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
#endif

#if(COM_RX_IPDU_COUNT_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
/*  Rx Ipdu Status */
VAR(PduIdType, COM_VAR) Com_GaaRxIpduStatus[COM_RX_IPDU_COUNT_MAX];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_CALLOUT_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Tx IpduCallout structure */
P2CONST(Com_TxIpduCallOut, AUTOMATIC, COM_CONST) 
Com_GaaTxIpduCallOut;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_MDT_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for allocating RAM area of Tx Minimum Delay Timer */
P2VAR(uint16, AUTOMATIC, COM_VAR)  Com_GaaTxMDTimer;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_TX_REPT_TIMER_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for allocating RAM area of Tx Rept Timer */
P2VAR(uint16, AUTOMATIC, COM_VAR)  
Com_GaaTxReptTimer;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_TX_REPT_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for allocating RAM area of Tx Rept Timer */
P2VAR(uint8, AUTOMATIC, COM_VAR)  Com_GaaTxReptCount;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for allocating RAM area of Tx Rept Sub Timer */
P2VAR(uint8, AUTOMATIC, COM_VAR)  Com_GaaTxReptSubCount;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(((COM_RX_IPDU_GWSTATUS_COUNT > COM_MACRO_ZERO) &&\
   (COM_RX_SIG_GATEWAY == STD_ON)) || (COM_RX_SIGNAL_GW_DES == STD_ON))
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for allocating RAM area of 8 bits for Rx GW I-PDU status */
P2VAR(uint8, AUTOMATIC, COM_VAR) 
Com_GaaRxGWIpduStatus;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_RX_IPDU_CALLOUT_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Rx IpduCallout structure */
P2CONST(Com_RxIpduCallOut, AUTOMATIC, COM_CONST) 
Com_GaaRxIpduCallOut;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_WR_FUNC_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for WrFuncPtr structure */
P2CONST(Com_WrFuncPtr, AUTOMATIC, COM_CONST) Com_GaaWrFuncPtr;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if((COM_RX_SIGGROUP_REPLACE == STD_ON) || \
   (COM_RX_SIGGROUP_UBDMREPLACE == STD_ON))
#if(COM_SIGGRP_REPLACE_COUNT > COM_MACRO_ZERO)      
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Signal Replace structure */
P2CONST(Com_SigGrpReplace, AUTOMATIC, COM_CONST) 
Com_GaaSigGrpReplace;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif
#endif
/* #7744 end */

/* #7705 */
#if(COM_TX_SIGGROUP_GROUPSIG_TRIGONCHANGE == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* This global array holds the status of Signal Group which configured as OnChange attribute with sub transfer property of Group Signal */
P2VAR(uint8, AUTOMATIC, COM_VAR) Com_GaaSigGroupChangedStatus;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

/* #7429, #7744 */
#if(COM_TX_SIGGROUP == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* This global array holds the masking value in memory area occupied by Signal Group */
P2CONST(uint8,AUTOMATIC, COM_CONST) Com_GaaSigGroupMaskInfo;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_RX_IPDU_COUNTER_ENABLED == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Rx Ipdu Counter */
P2CONST(Com_RxIpduCounter, AUTOMATIC, COM_CONST) 
Com_GaaRxIpduCounter;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_COUNTER_ENABLED == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Tx Ipdu Counter */
P2CONST(Com_TxIpduCounter, AUTOMATIC, COM_CONST) 
Com_GaaTxIpduCounter;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for InvalidFuncPtr structure */
P2CONST(Com_InvalidFuncPtr, AUTOMATIC, COM_CONST) Com_GaaInvalidFuncPtr;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

/* Global array for RxInvalid structure */
#if(COM_RX_SIGNAL_INVALID == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
P2CONST(Com_RxInvalid, AUTOMATIC, COM_CONST) Com_GaaRxInvalid;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

/* #7744 start */
#if((COM_RX_SIGNAL_REPLACE == STD_ON) || \
   (COM_RX_SIGNAL_UBDMREPLACE == STD_ON))
#if(COM_SIG_REPLACE_COUNT > COM_MACRO_ZERO)   
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Signal Replace structure */
P2CONST(Com_SigReplace, AUTOMATIC, COM_CONST) 
Com_GaaSigReplace;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif
#endif

#if(COM_SIG_WR_FUNC_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for SigWrFuncPtr structure */
P2CONST(Com_SigWrFuncPtr, AUTOMATIC, COM_CONST) 
Com_GaaSigWrFuncPtr;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_SIG_RD_FUNC_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for SigRdFuncPtr structure */
P2CONST(Com_SigRdFuncPtr, AUTOMATIC, COM_CONST) 
Com_GaaSigRdFuncPtr;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_RX_SIG_INGRP_GW_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for GWRxSigInGrp structure */
P2CONST(Com_RxGWSigInGrp,AUTOMATIC, COM_CONST) 
Com_GaaRxGWSigInGrp;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

/* Redmine #15832: Com_GaaRxGWSignal should be declared when there is only a group signal 
   in the source of the Signal Gateway */
#if((COM_RX_SIGNAL_GW == STD_ON) || (COM_RX_SIGINGROUP_GW == STD_ON))
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
P2CONST(Com_RxGWSignal, AUTOMATIC, COM_CONST) Com_GaaRxGWSignal ;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_RX_SIG_GATEWAY == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
P2CONST(Com_TxGWSignal, AUTOMATIC, COM_CONST) Com_GaaTxGWSignal;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_RX_GW_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for GWRxIpdu structure */
P2CONST(Com_RxGWIpdu, AUTOMATIC, COM_CONST)
           Com_GaaRxGWIpdu;
/* Global array for GWRxSignal structure */
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_TX_SIGGRP_MODE_SEL_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for RxUnpack structure */
P2CONST(Com_TxSigGrpModeSel, AUTOMATIC, COM_CONST) 
           Com_GaaTxSigGrpModeSel;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Redmine #13931: Global array for RxInvOrFltSigGroup structure */
#if((COM_RX_SIGGROUP_INVALID == STD_ON) || \
  (COM_RX_SIGGROUP_FILTER == STD_ON))
P2CONST(Com_RxInvOrFltSigGroup, AUTOMATIC, COM_CONST) 
Com_GaaRxInvOrFltSigGroup;
#endif
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#if(COM_RX_SIGINGROUP_COUNT_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for RxSigInGrp structure */
P2CONST(Com_RxSigInGrp, AUTOMATIC, COM_CONST) 
Com_GaaRxSigInGrp;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_MDT_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for allocating RAM area of Tx Update bit masks */
P2CONST(uint16,AUTOMATIC, COM_CONST) Com_GaaTxMDTimeout;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_FILTER_STATUS_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Filter Status */
P2VAR(uint8, AUTOMATIC, COM_VAR)  Com_GaaFilterStatus;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_TX_PERIOD_TIMER_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for allocating RAM area of 16 bits for timer */
P2VAR(uint16, AUTOMATIC, COM_VAR)  Com_GaaTxPeriodicTimer;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_TX_SIGGROUP == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for TxSigInGrp structure */
P2CONST(Com_TxSigInGrp,AUTOMATIC,  COM_CONST) 
Com_GaaTxSigInGrp;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_TX_SIGGROUP_COUNT_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for TxSigSignal structure */
P2CONST(Com_TxSigGrp, AUTOMATIC, COM_CONST) 
          Com_GaaTxSigGroup;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_TX_SIGINGROUP_COUNT_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for TxGroupSignal structure */
P2CONST(Com_TxGroupSignal, AUTOMATIC,COM_CONST) 
Com_GaaTxGroupSignal;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_RX_COUNTER_NOTIFY == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array counter error notification */
P2CONST(Com_RxCountNotify,AUTOMATIC, COM_CONST) 
Com_GaaRxCntNotify;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_COUNT_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Tx IPDU structure allocating memory to IPDU's.
   Calculation of Ipdu length in case of dynamic Ipdu:
   The length of the Ipdu must be generated according to the initial
   values of the dynamic signal present. The length of the Ipdu will be the
   minimum length that can accomodate the uint8_DYN signal.
   For e.g.: Suppose an IPDU has allocated a maximum size of 4 bytes to the DYN
   signal. There are 3 other signals in the Ipdu occupying a total of 4 bytes.
   Hence, the maximum size of the Ipdu is 8 bytes. However suppose that the
   initial value of the uint8_DYN signal is 96, 52, 12. Then the size generated
   here should be 7 bytes */
P2VAR(PduInfoType, AUTOMATIC, COM_VAR) Com_GaaTxPduInfoPtr;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_RX_IPDU_COUNT_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/*  Memory allocated to different Pdu's */
P2CONST(Com_RxPduInfoType,AUTOMATIC, COM_CONST) 
Com_GaaRxPduInfoPtr;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
VAR(uint16, COM_VAR)Com_GlNoOfTxIpdu;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
VAR(uint16, COM_VAR)Com_GlNoOfRxIpdu;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
VAR(uint16, COM_VAR)Com_GlNoOfTxSignal;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
VAR(uint16, COM_VAR)Com_GlNoOfTxSigGrp;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
VAR(uint16, COM_VAR)Com_GlNoOfTxSigInGrp;     
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
VAR(uint16, COM_VAR)Com_GlNoOfRxSignal;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
VAR(uint16, COM_VAR)Com_GlNoOfRxSigGrp;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
VAR(uint16, COM_VAR)Com_GlNoOfRxSigInGrp;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
VAR(uint16, COM_VAR)Com_GlNoOfTxIpduUngrp;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
VAR(uint16, COM_VAR)Com_GlNoOfRxIpduUngrp;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
VAR(uint16, COM_VAR)Com_GlNoOfIpduGrp;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
VAR(uint16, COM_VAR)Com_GlNoOfTxIpduDMCnt;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#define COM_START_SEC_VAR_CLEARED_16
#include "MemMap.h"
VAR(uint16, COM_VAR)Com_GlNoOfRxIpduDMCnt;
#define COM_STOP_SEC_VAR_CLEARED_16
#include "MemMap.h"

#if(COM_RX_IPDU_GROUP_COUNT_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array for RxIpduGroup structure */
P2CONST(PduIdType, AUTOMATIC, COM_CONST)
Com_GaaRxIpduGroup;
#define COM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_SIG_NOTIF_CBK_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array for SigNotifCbk structure */
P2CONST(Com_SigNotifCbk, AUTOMATIC, COM_CONST) 
Com_GaaSigNotifCbk;
#define COM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_GROUP_COUNT_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array for TxIpduGroup structure */
P2CONST(PduIdType,AUTOMATIC, COM_CONST) Com_GaaTxIpduGroup;
#define COM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_RX_IPDU_COUNT_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Structure for Rx I-PDU Group Count Per One I-PDU */
P2CONST(uint16,AUTOMATIC, COM_CONST) Com_GaaRxIpduBelongGroup;
#define COM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_COUNT_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Structure for Tx I-PDU Group Count Per One I-PDU */
P2CONST(uint16,AUTOMATIC, COM_CONST) Com_GaaTxIpduBelongGroup;
#define COM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_RX_IPDU_COUNT_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Structure for Rx I-PDU Group DM Count Per One I-PDU */
P2CONST(uint16,AUTOMATIC, COM_CONST) Com_GaaRxIpduDmBelongGroup;
#define COM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif


#if(COM_TX_IPDU == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
/*  Tx Ipdu Status Bit */
VAR(uint16, COM_VAR) Com_GaaTxIpduStatusBit[COM_TX_IPDU_COUNT_MAX];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
/*  Tx Ipdu Status */
VAR(PduIdType, COM_VAR) Com_GaaTxIpduStatus[COM_TX_IPDU_COUNT_MAX];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
#endif /*#if(COM_TX_IPDU == STD_ON)*/

#if(COM_TX_IPDU_COUNT_MAX > COM_MACRO_ZERO )
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
 /*Global array for TxIpdu structure */
VAR(uint8, COM_VAR) Com_GaaReptStatus[COM_TX_IPDU_COUNT_MAX];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_RX_IPDU_DM_COUNT_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
/* Global array for allocating RAM area of Rx Dm Timer */
P2VAR(uint32, AUTOMATIC, COM_VAR) Com_GaaRxDMTimer;
#define COM_STOP_SEC_VAR_INIT_UNSPECIFIED
#include "MemMap.h"
#endif

#if((COM_TX_SIGNAL_UB == STD_ON) || (COM_TX_SIGGROUP_UB == STD_ON))
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Tx Update Bitstructure */
P2CONST(Com_TxUpdateBit,AUTOMATIC, COM_CONST) 
Com_GaaTxUpdateBit;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

/* Redmine #13931: Global array for RxSigInGrpInvOrFlt structure */
#if((COM_RX_SIGGROUP_INVALID == STD_ON) || \
  (COM_RX_SIGGROUP_FILTER == STD_ON))
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
P2CONST(Com_RxSigInGrpInvOrFlt, AUTOMATIC, COM_CONST) 
Com_GaaRxSigInGrpInvOrFlt;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_TX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Tx TP Ipdu's. Instances of these will contain details
   about relevant TP (and dynamic) Ipdu's */
P2CONST(Com_TxTPIpdu, AUTOMATIC, COM_CONST) Com_GaaTxTPIpdu;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_RX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for Rx TP Ipdu's. Instances of these will contain details
   about relevant TP (and dynamic) Ipdu's */
P2CONST(Com_RxTPIpdu,AUTOMATIC, COM_CONST) Com_GaaRxTPIpdu;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_IPDUGROUP_COUNT_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for TxIpduGroup structure */
P2CONST(Com_IpduGroup, AUTOMATIC, COM_CONST) Com_GaaIpduGroup;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_COUNT_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for TxIpdu structure */
P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) Com_GaaTxIpdu;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_RX_IPDU_COUNT_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for RxIpdu structure */
P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) Com_GaaRxIpdu;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_RX_IPDU_DM_COUNT_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for RxDm structure */
P2CONST(Com_RxDm, AUTOMATIC, COM_CONST) Com_GaaRxDm;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_TX_SIGNAL_COUNT_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for TxSignal structure */
P2CONST(Com_TxSignal, AUTOMATIC, COM_CONST) Com_GaaTxSignal;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_RX_SIGNAL_COUNT_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for RxSignal structure */
P2CONST(Com_RxSignal, AUTOMATIC, COM_CONST) Com_GaaRxSignal;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_RX_SIGGROUP_COUNT_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array for RxSigGroup structure */
P2CONST(Com_RxSigGroup, AUTOMATIC, COM_CONST) Com_GaaRxSigGroup;
#define COM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_CONFIRM_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for TxIpduCnfrm structure */
P2CONST(Com_TxIpduConfirm, AUTOMATIC, COM_CONST) 
                                  Com_GaaTxIpduConfirm;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_TX_IPDU_DM_COUNT_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for TxIpduDm structure */
P2CONST(Com_TxIpduDm, AUTOMATIC, COM_CONST) Com_GaaTxIpduDm;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

/* Array size calculation error - Fixed by AUTRON START*/  
#if(COM_PACK_FUNC_COUNT_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for TxPack structure */
P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) Com_GaaTxPack;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif
/* Array size calculation error - Fixed by AUTRON END*/  

/* Array size calculation error - Fixed by AUTRON START*/  
#if(COM_UNPACK_FUNC_COUNT_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for RxUnpack structure */
P2CONST(Com_RxUnpack, AUTOMATIC, COM_CONST) Com_GaaRxUnpack;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif
/* Array size calculation error - Fixed by AUTRON END*/  

#if(COM_TX_MODE_COUNT_MAX > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for TxMode structure */
P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) Com_GaaTxMode;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if((COM_RX_IPDU_DM == STD_ON) \
      || (COM_RX_SIGNAL_UBDM == STD_ON) \
      || (COM_RX_SIGGROUP_UBDM == STD_ON))
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
/*  Rx Ipdu Status */
VAR(PduIdType, COM_VAR)  Com_GaaRxDmStatus[COM_RX_IPDU_DM_COUNT_MAX];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
#endif

#if(COM_SIG_ERROR_CBK_COUNT>COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
P2CONST(Com_SigErrorCbk, AUTOMATIC, COM_CONST) Com_GaaSigErrorCbk;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif /* (COM_SIG_ERROR_CBK_COUNT>COM_MACRO_ZERO) */

#if(COM_RX_INVALIDNOTIFY == STD_ON)
#define COM_START_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
/* Global array for InvalidSigNotifCbk structure */
P2CONST(pInvSigNotifCbkPtr,AUTOMATIC, COM_CONST) Com_GaaInvNotifCbk;
#define COM_STOP_SEC_CONST_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_NO_OF_FILTER_ONEVERYN > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for FilterOneEveryN structure */
P2CONST(Com_FilterOneEveryN, AUTOMATIC, COM_CONST) 
Com_GaaFilterOneEveryN;
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#else /*COM_VARIANT_POSTBUILD_SUPPORT*/
#if (COM_RX_IPDU_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
/*  Rx Ipdu Status */
VAR(PduIdType, COM_VAR) Com_GaaRxIpduStatus[COM_RX_IPDU_COUNT];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#if(COM_TX_IPDU == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
/*  Tx Ipdu Status Bit */
VAR(uint16, COM_VAR) Com_GaaTxIpduStatusBit[COM_TX_IPDU_COUNT];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
/*  Tx Ipdu Status */
VAR(PduIdType, COM_VAR) Com_GaaTxIpduStatus[COM_TX_IPDU_COUNT];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 

#if(COM_TX_IPDU_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
 /*Global array for TxIpdu structure */
VAR(uint8, COM_VAR) Com_GaaReptStatus[COM_TX_IPDU_COUNT];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#endif/* #if(COM_TX_IPDU == STD_ON)*/

#if((COM_RX_IPDU_DM == STD_ON) \
      || (COM_RX_SIGNAL_UBDM == STD_ON) \
      || (COM_RX_SIGGROUP_UBDM == STD_ON))
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
/*  Rx Ipdu Status */
VAR(PduIdType, COM_VAR)  Com_GaaRxDmStatus[COM_RX_IPDU_DM_COUNT];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
#endif

#if(COM_RX_TP_SUPPORT == STD_ON)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
VAR(uint8, COM_VAR) Com_GaaRxTPflg[COM_RX_IPDU_COUNT];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h" 
#endif

#endif   /*COM_VARIANT_POSTBUILD_SUPPORT*/
#if (STD_ON == COM_MULTI_CORE_SUPPORT)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
VAR(uint8, COM_VAR) Com_GaaReceiveIpduEachCore[COM_RX_IPDU_COUNT];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
	
#define COM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
#if(COM_SIG_NOTIF_CBK_COUNT>COM_MACRO_ZERO)
VAR(uint8, COM_VAR) Com_GaaSigNotifCbkFlag[COM_SIG_NOTIF_CBK_COUNT];
#endif /* (COM_SIG_NOTIF_CBK_COUNT>COM_MACRO_ZERO) */
#if(COM_SIG_ERROR_CBK_COUNT>COM_MACRO_ZERO)
VAR(uint8, COM_VAR) Com_GaaSigErrorCbkFlag[COM_SIG_ERROR_CBK_COUNT];
#endif /* (COM_SIG_ERROR_CBK_COUNT>COM_MACRO_ZERO) */
#if(COM_INV_NOTIF_CBK_COUNT>COM_MACRO_ZERO)
VAR(uint8, COM_VAR) Com_GaaInvNotifCbkFlag[COM_INV_NOTIF_CBK_COUNT];
#endif /* (COM_INV_NOTIF_CBK_COUNT>COM_MACRO_ZERO) */
#if(COM_TX_IPDU_COUNT>COM_MACRO_ZERO)
VAR(uint8, COM_VAR) Com_GaaTxIpduTransmitFlag[COM_TX_IPDU_COUNT];
#endif /* (COM_TX_IPDU_COUNT>COM_MACRO_ZERO) */
#define COM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"

#if(COM_RX_IPDU_GWSTATUS_COUNT > COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
/* Global array for allocating RAM area of 8 bits for Rx GW I-PDU status */
VAR(uint8, COM_VAR) Com_GaaRxGWIpduMulticoreStatus[COM_RX_IPDU_GWSTATUS_COUNT];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
#endif

#define COM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global flag check DirectMode */
VAR(boolean, COM_VAR) Com_GaaMulticoreDirectMode;
#define COM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define COM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global flag to request switch core */
VAR(boolean, COM_VAR) Com_GaaMulticoreTriggerNotifyFlag[COM_MULTI_CORE_NUMBER];
#define COM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#define COM_START_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"
/* Global flag to request switch core by mainfunction */
VAR(boolean, COM_VAR) Com_GaaMulticoreMainNotifyFlag[COM_MULTI_CORE_NUMBER];
#define COM_STOP_SEC_VAR_CLEARED_BOOLEAN
#include "MemMap.h"

#if(COM_SIG_NOTIF_CBK_COUNT>COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
VAR(uint8, COM_VAR) Com_GaaMainSigNotifCbkFlag[COM_SIG_NOTIF_CBK_COUNT];
#define COM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif /* (COM_SIG_NOTIF_CBK_COUNT>COM_MACRO_ZERO) */

#if(COM_SIG_ERROR_CBK_COUNT>COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
VAR(uint8, COM_VAR) Com_GaaMainSigErrorCbkFlag[COM_SIG_ERROR_CBK_COUNT];
#define COM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif /* (COM_SIG_ERROR_CBK_COUNT>COM_MACRO_ZERO) */

#if(COM_INV_NOTIF_CBK_COUNT>COM_MACRO_ZERO)
#define COM_START_SEC_VAR_CLEARED_8
#include "MemMap.h"
VAR(uint8, COM_VAR) Com_GaaMainInvNotifCbkFlag[COM_INV_NOTIF_CBK_COUNT];
#define COM_STOP_SEC_VAR_CLEARED_8
#include "MemMap.h"
#endif /* (COM_INV_NOTIF_CBK_COUNT>COM_MACRO_ZERO) */

#else /* (STD_ON == COM_MULTI_CORE_SUPPORT) */

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
VAR(PduIdType, COM_VAR) Com_GaaReceiveIpduBuffer[COM_RX_IPDU_HISTORY_LIST];
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#define COM_START_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"
VAR(Com_ReceiveIpduListType, COM_VAR) Com_GaaReceiveIpduValue[] =
{

  {
    /* usWriteIndex */
    0,

    /* usReadIndex */
    0,

    /* usCount */
    0,

    /* usSize */
    COM_RX_IPDU_HISTORY_LIST,

    /* pList */
    &Com_GaaReceiveIpduBuffer[COM_ZERO]
  }
};
#define COM_STOP_SEC_VAR_CLEARED_UNSPECIFIED
#include "MemMap.h"

#endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */

/* polyspace-end VARIABLE:* [Not a defect:Low] "System intended for multitasking" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
