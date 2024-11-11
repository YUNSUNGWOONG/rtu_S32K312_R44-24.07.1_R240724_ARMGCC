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
**  SRC-MODULE: Com_IpduGrp.c                                                 **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR Com Module                                            **
**                                                                            **
**  PURPOSE   : Provision of start/stop of I-PDU group & deadline monitoring  **
**              system.                                                       **
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
** 1.1.11.0  10-Oct-2023   PhucNHM     CP44-2759                              **
** 1.1.9.0   28-Mar-2023   PhucNHM     CP44-267                               **
** 1.1.6.0   07-Dec-2022   PhucNHM     CP44-1269                              **
** 1.1.4.0   11-Oct-2022   HaoTA4      CP44-771                               **
** 1.1.4.0   27-Jul-2022   PhucNHM     R44-Redmine #29406 #28007 #28012       **
** 1.1.3.1   21-Jun-2022   SMKwon      CP44-109                               **
** 1.1.2     25-Apr-2022   PhucNHM     R44-Redmine #25517 #25617 #25631       **
**                                                 #25654 #26755              **
** 1.1.1     25-Mar-2022   PhuPV10     R44-Redmine #25573 #25073              **
** 1.1.0     10-Feb-2022   PhucNHM     R44-Redmine #19316 #23495 #23725       **
**                                                 #23982 #24211              **
** 1.0.1     28-Sep-2021   DuyNGB      R44-Redmine #20139                     **
** 1.0.0     04-Dec-2020   SMKwon      Initial Version                        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/

#include "Com.h"          /* Com header file */
#include "Com_Main.h"     /* Com Main header file */
#include "Com_Error.h"    /* Com Error header file */
#include "Com_IpduGrp.h"  /* Com Ipdu Group header file */
#include "SchM_Com.h"     /* SchM Com header file */
#if(COM_DEV_ERROR_DETECT == STD_ON)
#include "Det.h"          /* Det header file */
#endif
#if (STD_ON == COM_MULTI_CORE_SUPPORT)
#include "Os.h"
#endif /* STD_ON == COM_MULTI_CORE_SUPPORT */
#include "string.h"       /* memcpy() */

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/


/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/


/*******************************************************************************
**                      Function Declaration                                  **
*******************************************************************************/

#if(COM_RX_IPDU == STD_ON)
#if((COM_RX_SIGGROUP == STD_ON) || \
  ((COM_RX_SIGNAL_FILTER == STD_ON) && (COM_RX_SIGNAL == STD_ON)) || \
  ((COM_RX_SIGGROUP_FILTER == STD_ON) && (COM_RX_SIGGROUP == STD_ON)))
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_RxBuffersReInit(PduIdType LddIpduHandleId);
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Com_IpduGroupStart                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function starts a pre-configured I-PDU group.  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different I-PDU groups.               **
**                        Non-Reentrant for same I-PDU group.                 **
**                                                                            **
** Input Parameters     : IpduGroupId, Initialize                             **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaIpduGroup           **
**                                                 Com_GaaIpduGrpEnStatus     **
**                                                 Com_GaaIpduGrpDmStatus     **
**                                                 Com_GaaTxIpduGroup         **
**                                                 Com_GaaTxIpduStatus        **
**                                                 Com_GaaTxIpduStatusBit     **
**                                                 Com_GaaRxIpduGroup         **
**                                                 Com_GaaRxIpduStatus        **
**                        Function(s) invoked    : SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
*******************************************************************************/
#if (((COM_VARIANT_POSTBUILD_SUPPORT == STD_ON) &&\
  ((COM_TX_IPDU_GROUP_COUNT_MAX>0) || (COM_RX_IPDU_GROUP_COUNT_MAX >0))) || \
((COM_TX_IPDU_GROUP_COUNT>0) || (COM_RX_IPDU_GROUP_COUNT >0)))
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_00218, SRS_Com_02090, SRS_Com_02099*/
FUNC(void, COM_CODE) Com_IpduGroupStart(Com_IpduGroupIdType IpduGroupId,
  boolean Initialize)
{
  /* @Trace: Com_SUD_API_00187 */
  /* polyspace:begin<MISRA-C:1.1:Not a defect:Justify with annotations> Code structure for optimal performance */  
  /* Pointer to Ipdu group structure */
  P2CONST(Com_IpduGroup, AUTOMATIC, COM_CONST) LpIpduGroup;
  PduIdType LddPduIndex;
  
  /* Local variable to store no. Of Ipdus */
  PduIdType LddNoOfIpdus;
  
  boolean blIpduGrp;
 
  Com_IpduGroupIdType LddIpduGroupId;
  /* Local variable carrying I-PDU Group Enable status */
  uint8 LucIpduGrpEnStatus;
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  uint8 LucReturnValue;
  LucReturnValue = E_OK;
  /* Check whether module is initialized */
  COM_DET_INIT_STATUS_CHECK_FLAG(COMSERVICEID_IPDUGROUPSTART);
  /* Check whether I-PDU group ID is out of range */
  #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01311 */
  COM_DET_IPDUGROUPID_RANGE_CHECK_FLAG(COMSERVICEID_IPDUGROUPSTART);
  #else
  /* @Trace: Com_SUD_API_01312 */
  COM_DET_IPDUGROUPID_RANGE_CHECK_FLAG_PB(COMSERVICEID_IPDUGROUPSTART);
  #endif
  if(LucReturnValue == (uint8)E_OK)
  #endif
  {
    /* @Trace: Com_SUD_API_00188 */
    LddIpduGroupId = IpduGroupId;
    /* Get the pointer to the I-PDU group structure */
    LpIpduGroup = &Com_GaaIpduGroup[LddIpduGroupId];
    SchM_Enter_Com_IPDU_GROUP_STATUS_PROTECTION();
    /* Get the enable status of I-PDU Group */
    LucIpduGrpEnStatus = Com_GaaIpduGrpEnStatus[LpIpduGroup->ucGroupIndex];
    SchM_Exit_Com_IPDU_GROUP_STATUS_PROTECTION();
    if((LucIpduGrpEnStatus & (LpIpduGroup->ucStatusMask)) == COM_FALSE)
    /*Check this IPDU Grp is already enable */
    {
      /* @Trace: Com_SUD_API_00189 */
      SchM_Enter_Com_IPDU_GROUP_STATUS_PROTECTION();
      /* Enable Ipdu Group Status */
      Com_GaaIpduGrpEnStatus[LpIpduGroup->ucGroupIndex] |=
                                                (LpIpduGroup->ucStatusMask);
      /* Enable Ipdu Group Status */
      Com_GaaIpduGrpDmStatus[LpIpduGroup->ucGroupIndex] |=
                                                (LpIpduGroup->ucStatusMask);
      SchM_Exit_Com_IPDU_GROUP_STATUS_PROTECTION();
      blIpduGrp = COM_TRUE;
      #if(COM_TX_IPDU == STD_ON)
      /* Get the number of Tx I-PDUs  */
      LddNoOfIpdus = (PduIdType) LpIpduGroup->ddNoOfTxIpdus;
      LddPduIndex = (PduIdType) LpIpduGroup->ddTxIpduIndex;
      /*Check this IPDu grp has Tx Ipdu */
      if(LddNoOfIpdus != 0)
      {
        while(LddNoOfIpdus != (PduIdType)COM_ZERO)
        {
          /* @Trace: Com_SUD_API_00211 */
          --LddNoOfIpdus;
          /* Start Tx IPDUs in this IPDU grp */
          Com_StartTxIPDUs(LddPduIndex, Initialize, blIpduGrp);
          ++LddPduIndex;
        }
      }
      #endif /*end of (COM_TX_IPDU == STD_ON) */
    
      #if(COM_RX_IPDU == STD_ON)
      /* @Trace: Com_SUD_API_00191 */
      /* Get the number of Tx I-PDUs  */
      LddNoOfIpdus = (PduIdType) LpIpduGroup->ddNoOfRxIpdus;
      /* Get the group index */
      LddPduIndex = (PduIdType) LpIpduGroup->ddRxIpduIndex;
      /*Check this IPDu grp has Tx Ipdu */
      if(LddNoOfIpdus != 0)
      {
        while(LddNoOfIpdus != (PduIdType)COM_ZERO)
        {
          /* @Trace: Com_SUD_API_00192 */
          --LddNoOfIpdus;
          /* Start Rx IPDUs in this IPDU grp */
          Com_StartRxIPDUs(LddPduIndex, Initialize, blIpduGrp);

          ++LddPduIndex;
        }
      }
      #endif /*end of (COM_RX_IPDU == STD_ON) */
      /* Loop for all Rx PDUs */
    } /* @End if(((Com_GaaIpduGrpEnStatus[LpIpduGroup->ucGroupIndex] &
            (LpIpduGroup->ucStatusMask)) == COM_FALSE) && 
            (LddIpduGroupId <= ((uint8)COM_IPDUGROUP_COUNT - COM_ONE))) */
  } 
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#else
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_IpduGroupStart(Com_IpduGroupIdType IpduGroupId,
  boolean Initialize)
{
  /* @Trace: Com_SUD_API_01313 */
  COM_UNUSED(IpduGroupId);
  COM_UNUSED(Initialize);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_StopTxIPDUs                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_IpduGroupStop                   **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
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
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if(COM_TX_IPDU == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COM_CODE) Com_StopTxIPDUs(
  P2CONST(Com_IpduGroup, AUTOMATIC, COM_CONST) LpIpduGroup)
{
  /* @Trace: Com_SUD_API_01407 */
  /* Local variable to store no. Of Ipdus */
  PduIdType LddNoOfIpdus;
  /* Local variable to store Com Ipdu handle ID */
  PduIdType LddPduIndex;
  PduIdType LddIpduHandleId;
  #if((COM_TX_IPDU_ERRORNOTIFY == STD_ON) || \
    (COM_TX_IPDU_COUNTER_ENABLED == STD_ON))
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu;
  #endif
  #if(COM_TX_IPDU_ERRORNOTIFY == STD_ON)
  /* Pointer to Tx Ipdu confirm structure */
  P2CONST(Com_TxIpduConfirm, AUTOMATIC, COM_CONST) LpTxIpduConfirm;
  /* Pointer to signal error Call back structure */
  P2CONST(Com_SigErrorCbk, AUTOMATIC, COM_CONST) LpSigErrorCbk;
  #endif
  #if(COM_TX_IPDU_ERRORNOTIFY == STD_ON)
  uint8 LddNoOfCount;
  Com_ErrCbkCountType LddSigErrorCbkIndex;
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  uint8 CoreMaskCheck;
  uint8 CoreIdCheck;
  uint8 CoreIdMask;
  CoreIdType CoreId;
  /* create mask of core id */
  CoreId = GetCoreID();
  CoreIdMask = COM_ONE<<CoreId;
  #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
  #endif  
  #if(COM_TX_IPDU_COUNTER_ENABLED == STD_ON)
  P2CONST(Com_TxIpduCounter, AUTOMATIC, COM_CONST) LpTxIpduCounter;
  P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack;
  uint8 LucTxIpduCntVal;
  #endif
  /* Get the number of Tx I-PDUs  */
  LddNoOfIpdus = (PduIdType) LpIpduGroup->ddNoOfTxIpdus;
  LddPduIndex = (PduIdType) LpIpduGroup->ddTxIpduIndex;
  /* Loop for all PDUs */
  while(LddNoOfIpdus != (PduIdType)COM_ZERO)
  {
    /* @Trace: Com_SUD_API_00196 */
    --LddNoOfIpdus;
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    LddIpduHandleId = (PduIdType)Com_GaaTxIpduGroup[LddPduIndex];
    LddPduIndex++;
    if((uint16)COM_ZERO < Com_GaaTxIpduStatus[LddIpduHandleId])
    {
      /* @Trace: Com_SUD_API_01794 */
      /* change the status */
      Com_GaaTxIpduStatus[LddIpduHandleId]--;
    }

    if(Com_GaaTxIpduStatus[LddIpduHandleId] == (PduIdType)COM_ZERO)
    {
      /* @Trace: Com_SUD_API_00197 */
      #if((COM_TX_IPDU_ERRORNOTIFY == STD_ON) || \
      (COM_TX_IPDU_COUNTER_ENABLED == STD_ON))
      /* Get the pointer to Tx Ipdu */
      LpTxIpdu = &Com_GaaTxIpdu[LddIpduHandleId];
      #endif
      #if(COM_TX_IPDU_ERRORNOTIFY == STD_ON)
      if((Com_GaaTxIpduStatusBit[LddIpduHandleId] &
                                    COM_TX_REQ_STATUS_MASK) != COM_FALSE)
      {  
        if(LpTxIpdu->ddTxPduConfirmIndex != COM_INVALID_TXID_PARAM)
        {
          /* @Trace: Com_SUD_API_00198*/
          /* Get the pointer to Tx Confirmation Structure */
          LpTxIpduConfirm =
                    &Com_GaaTxIpduConfirm[LpTxIpdu->ddTxPduConfirmIndex];
          /* Get the number of signals configured for call-back
            notification */
          LddNoOfCount = LpTxIpduConfirm->ucNoOfSigErrorCbk;
          /* Check whether number of signal call-back notification
          count is not equal to zero */
          if(LddNoOfCount != COM_ZERO)
          {
            /* @Trace: Com_SUD_API_00199 */
            /* Get the pointer to SigErrorCbk structure */
            LddSigErrorCbkIndex = LpTxIpduConfirm->ddSigErrCbkIndex;
            LpSigErrorCbk =
                &Com_GaaSigErrorCbk[LddSigErrorCbkIndex];
            /* Loop for all the signals configured for timeout error
            
            notification */
            do
            {
              #if (STD_ON == COM_MULTI_CORE_SUPPORT)
              /* @Trace: Com_SUD_API_00200 */
              CoreMaskCheck = 
                Com_GaaSigErrorCbkPositionMask[LddSigErrorCbkIndex];
              if(COM_ZERO != (CoreMaskCheck & CoreIdMask))
              {
                /* @Trace: Com_SUD_API_00201 */
                #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */
                /* Invoke the error notification function  */
                /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
                (LpSigErrorCbk->pSigErrorCbk)();
                #if (STD_ON == COM_MULTI_CORE_SUPPORT)	
              }
              else
              {
                /* @Trace: Com_SUD_API_00202 */
                SchM_Enter_Com_SWITCH_CORE_PROTECTION_AREA();
                Com_GaaSigErrorCbkFlag[LddSigErrorCbkIndex] = CoreMaskCheck;
                SchM_Exit_Com_SWITCH_CORE_PROTECTION_AREA();
                /* Get ptr of notify function */
                CoreIdCheck = CoreMaskCheck >> COM_ONE;
                /* Trigger Ioc write */
                (void)Com_GaaMulticoreNotifyList[CoreIdCheck](COM_TRUE);
              } 
              #endif /* (STD_ON == COM_MULTI_CORE_SUPPORT) */

              /* @Trace: Com_SUD_API_00203 */
              /* Get the pointer to n SigErrorCbk structure */
              LddSigErrorCbkIndex++;
              LpSigErrorCbk =
                &Com_GaaSigErrorCbk[LddSigErrorCbkIndex];
              /* Decrement the signal error notification
              call-back count */
              LddNoOfCount--;
            }while(LddNoOfCount != COM_ZERO); 

          } /* Check whether number of error callback is configured */
        }
      } /* Check whether Tx Request bit is set to true */
      #endif /*#if(COM_TX_IPDU_ERRORNOTIFY == STD_ON))*/
      
      #if(COM_TX_IPDU_COUNTER_ENABLED == STD_ON)
      if(LpTxIpdu->ddTxIpduCounter != COM_INVALID_TXID_PARAM)
      {
        /* @Trace: Com_SUD_API_00204 */
        /* Get the pointer to Tx I-PDU counter structure */
        LpTxIpduCounter = 
          &Com_GaaTxIpduCounter[LpTxIpdu->ddTxIpduCounter];
        Com_GaaTxIpduCountVal[LpTxIpduCounter->ucTxIpduCountData] = 
              COM_ZERO;
        
        /* Get the pointer to TxPack structure */
        LpTxPack = &Com_GaaTxPack[LpTxIpduCounter->ddTxPackIndex];
        /* Get the present counter data */
        LucTxIpduCntVal = 
          Com_GaaTxIpduCountVal[LpTxIpduCounter->ucTxIpduCountData];
        
        /* Apply wrap around mask to the counter data */
        LucTxIpduCntVal &= LpTxIpduCounter->ucTxIpduCntWrpMask;
        #if(COM_SIG_WR_FUNC_COUNT > COM_MACRO_ZERO)
        /* @Trace: SWS_Com_00472, SWS_Com_00674, SWS_Com_00829 */
        /* Invoke write function to pack counter data to I-PDU buffer */
        (void)Com_PackRequestWrite(LpTxPack,
        (P2CONST(void, AUTOMATIC, COM_CONST))&LucTxIpduCntVal);
        #endif
        
        /* Load present counter data in buffer */
        Com_GaaTxIpduCountVal[LpTxIpduCounter->ucTxIpduCountData] = 
        LucTxIpduCntVal;
      }
      #endif
    }
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif /*End of Tx IPDU*/

/*******************************************************************************
** Function Name        : Com_StopRxIPDUs                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_IpduGroupStop                   **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
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
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#if(COM_RX_IPDU == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COM_CODE) Com_StopRxIPDUs(
  P2CONST(Com_IpduGroup, AUTOMATIC, COM_CONST) LpIpduGroup)
{
  /* @Trace: Com_SUD_API_00205 */
  /* Local variable to store no. Of Ipdus */
  PduIdType LddNoOfIpdus;
  /* Local variable to store Com Ipdu handle ID */
  PduIdType LddPduIndex;
  PduIdType LddIpduHandleId;
  /* Get the number of Rx I-PDUs  */
  LddNoOfIpdus = (PduIdType) LpIpduGroup->ddNoOfRxIpdus;
  LddPduIndex = (PduIdType) LpIpduGroup->ddRxIpduIndex;
  /* Loop for all PDUs */
  while(LddNoOfIpdus != (PduIdType)COM_ZERO)
  {
    /* @Trace: Com_SUD_API_00206 */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    LddIpduHandleId = (PduIdType)Com_GaaRxIpduGroup[LddPduIndex];
    --LddNoOfIpdus;
    LddPduIndex++;
    if((uint16) COM_ZERO < Com_GaaRxIpduStatus[LddIpduHandleId])
    {
      /* @Trace: Com_SUD_API_01795 */
      Com_GaaRxIpduStatus[LddIpduHandleId]--;
    }
  }
  #if((COM_RX_IPDU_DM == STD_ON) || \
      (COM_RX_SIGNAL_UBDM == STD_ON) || \
      (COM_RX_SIGGROUP_UBDM == STD_ON))
  /* Check whether requested I-PDU group is active for Deadline
    monitoring */
  if((Com_GaaIpduGrpDmStatus[LpIpduGroup->ucGroupIndex] &
                              (LpIpduGroup->ucStatusMask)) != COM_FALSE)
  {
    /* @Trace: Com_SUD_API_00207 */
    /* Enable Ipdu Group Status */
    Com_GaaIpduGrpDmStatus[LpIpduGroup->ucGroupIndex] &=
                                      (uint8)(~(LpIpduGroup->ucStatusMask));
    /* Get the number of Rx I-PDUs  */
    LddNoOfIpdus = (PduIdType) LpIpduGroup->ddNoOfRxIpdus;

    LddPduIndex = (PduIdType) LpIpduGroup->ddRxIpduIndex;
    /* Loop for all PDUs */
    while(LddNoOfIpdus != (PduIdType)COM_ZERO)
    {
      /* @Trace: Com_SUD_API_00208 */
      LddIpduHandleId = Com_GaaRxIpduGroup[LddPduIndex];
      --LddNoOfIpdus;
      LddPduIndex++;
      /* polyspace +1 RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */
      if((Com_GaaRxIpdu[LddIpduHandleId].ucRxConfig &
                                      COM_RX_DM_CONFIG_MASK) != COM_FALSE)
      {
        if((uint16)COM_ZERO < 
          Com_GaaRxDmStatus[Com_GaaRxIpdu[LddIpduHandleId].ddRxIpduDmIndex])
        {
          /* @Trace: Com_SUD_API_00209 */
          Com_GaaRxDmStatus[Com_GaaRxIpdu[LddIpduHandleId].ddRxIpduDmIndex]--;
        }
      }
    }
  } /* Check whether deadline monitoring is active */
  #endif /* Dead line Monitoring */
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_IpduGroupStop                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This Internal function stops a                      **
**                        pre-configured I-PDU group.                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different I-PDU groups.               **
**                        Non-Reentrant for same I-PDU group.                 **
**                                                                            **
** Input Parameters     : IpduGroupId                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaIpduGroup           **
**                                                 Com_GaaIpduGrpEnStatus     **
**                                                 Com_GaaTxIpduGroup         **
**                                                 Com_GaaTxIpduStatus        **
**                                                 Com_GaaTxIpduStatusBit     **
**                                                 Com_GaaTxIpdu              **
**                                                 Com_GaaTxIpduConfirm       **
**                                                 Com_GaaSigErrorCbk         **
**                                                 Com_GaaTxIpduCounter       **
**                                                 Com_GaaTxIpduCountVal      **
**                                                 Com_GaaRxIpduGroup         **
**                                                 Com_GaaRxIpduStatus        **
**                                                 Com_GaaIpduGrpDmStatus     **
**                                                 Com_GaaRxIpdu              **
**                                                 Com_GaaRxDmStatus          **
**                        Function(s) invoked    : SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
**                                                 pSigErrorCbk               **
**                                                 Com_TxZeroCounterUpdate()  **
*******************************************************************************/
#if (((COM_VARIANT_POSTBUILD_SUPPORT == STD_ON) &&\
  ((COM_TX_IPDU_GROUP_COUNT_MAX>0) || (COM_RX_IPDU_GROUP_COUNT_MAX >0))) || \
  ((COM_TX_IPDU_GROUP_COUNT>0) || (COM_RX_IPDU_GROUP_COUNT >0)))
/* @Trace: Com_SUD_API_01319 */
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_00218, SRS_Com_02090*/
FUNC(void, COM_CODE) Com_IpduGroupStop(Com_IpduGroupIdType IpduGroupId)
{
  /* @Trace: Com_SUD_API_00193 */
  /* Pointer to Ipdu group structure */
  P2CONST(Com_IpduGroup, AUTOMATIC, COM_CONST) LpIpduGroup;
  /* Local variable carrying I-PDU Group Enable status */
  uint8 LucIpduGrpEnStatus;
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  uint8 LucReturnValue;
  LucReturnValue = E_OK;
  /* Check whether module is initialized */
  COM_DET_INIT_STATUS_CHECK_FLAG(COMSERVICEID_IPDUGROUPSTOP);
  /* Check whether I-PDU group ID is out of range */
  #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01314 */
  COM_DET_IPDUGROUPID_RANGE_CHECK_FLAG(COMSERVICEID_IPDUGROUPSTOP);
  #else
  /* @Trace: Com_SUD_API_01315 */
  COM_DET_IPDUGROUPID_RANGE_CHECK_FLAG_PB(COMSERVICEID_IPDUGROUPSTOP);
  #endif
  /* Get the pointer to the I-PDU group structure */
  if(LucReturnValue == (uint8)E_OK)
  #endif
  {
    /* @Trace: Com_SUD_API_00194 */
    LpIpduGroup = &Com_GaaIpduGroup[IpduGroupId];
    SchM_Enter_Com_IPDU_GROUP_STATUS_PROTECTION();
    /* Get the enable status of I-PDU Group */
    LucIpduGrpEnStatus = Com_GaaIpduGrpEnStatus[LpIpduGroup->ucGroupIndex];
    SchM_Exit_Com_IPDU_GROUP_STATUS_PROTECTION();
      /* stops only one Ipdu group since an Ipdu can be
    stopped only if it is stopped in all the Ipdu Groups
    it is contained in */
    /* IpduGroupId range checked at COM_DET_IPDUGROUPID_RANGE_CHECK_FLAG_PB */
    if((LucIpduGrpEnStatus & (LpIpduGroup->ucStatusMask)) != COM_FALSE)
    {
      /* @Trace: Com_SUD_API_00195 */
      SchM_Enter_Com_IPDU_GROUP_STATUS_PROTECTION();
      /* Disable Ipdu Group Status */
      Com_GaaIpduGrpEnStatus[LpIpduGroup->ucGroupIndex] &= 
                                          (uint8)(~(LpIpduGroup->ucStatusMask));
      SchM_Exit_Com_IPDU_GROUP_STATUS_PROTECTION();
      #if(COM_TX_IPDU == STD_ON)
      Com_StopTxIPDUs(LpIpduGroup);
      #endif
      #if(COM_RX_IPDU == STD_ON)
      Com_StopRxIPDUs(LpIpduGroup);
      #endif
    }
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#else
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_IpduGroupStop(Com_IpduGroupIdType IpduGroupId)
{
  /* @Trace: Com_SUD_API_01316 */
  COM_UNUSED(IpduGroupId);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

#if (((COM_VARIANT_POSTBUILD_SUPPORT == STD_ON) &&\
  ((COM_TX_IPDU_GROUP_COUNT_MAX>0) || (COM_RX_IPDU_GROUP_COUNT_MAX >0))) || \
  ((COM_TX_IPDU_GROUP_COUNT>0) || (COM_RX_IPDU_GROUP_COUNT >0)))
/*******************************************************************************
** Function Name        : Com_IpduStatusInit                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function init IpduStatus              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** InOut parameter      :                                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Com_GaaIpduGroup              **
**                        Function(s) invoked : Det_ReportError()             **
*******************************************************************************/
#if(COM_TX_IPDU == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
static FUNC(void, COM_CODE) Com_IpduStatusInit(PduIdType LddIpduHandleId, 
  boolean Initialize)
{
  /* Check if initialization is equal to true then clear all bits */
  if(COM_TRUE == Initialize)
  {
    /* @Trace: Com_SUD_API_00214 */
    Com_GaaTxIpduStatusBit[LddIpduHandleId] &= (COM_TX_TMS_STATUS_MASK);
  }
  else
  {
    /* @Trace: Com_SUD_API_00215 */
    Com_GaaTxIpduStatusBit[LddIpduHandleId] &= ((COM_TX_TMS_STATUS_MASK) |
                                                (COM_TX_PT_STATUS_MASK) |
                                                (COM_TX_RETRY_STATUS_MASK));
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_ProcessIpduFilterStatus                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function start for Ipdu filter status **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** InOut parameter      :                                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Com_GaaIpduGroup              **
**                        Function(s) invoked : Det_ReportError()             **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_TX_IPDU == STD_ON)
#if((COM_TX_IPDU_TMS_EXPLICIT == STD_ON) || \
    (COM_TX_IPDU_TMS_SIG_BASED == STD_ON) || \
    (COM_TX_IPDU_PT == STD_ON))
static FUNC(void, COM_CODE) Com_ProcessIpduFilterStatus(PduIdType LddIpduHandleId,
                             P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu)
{
  /* @Trace: Com_SUD_API_01409 */
  #if(COM_TX_IPDU_TMS_SIG_BASED == STD_ON)
  P2CONST(Com_TxIpduModeSel, AUTOMATIC, COM_CONST) LpTxModeSelect;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpFilterStatus;
  uint8 LucFilterStatusIndex;
  #endif

  #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) ||\
    (COM_TX_IPDU_TMS_EXPLICIT == STD_ON))
  boolean LblFilterResult;  
  #endif

  #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) ||\
    (COM_TX_IPDU_TMS_EXPLICIT==STD_ON))

  #if(COM_TX_IPDU_PT == STD_ON)
  /* Pointer to Tx mode structure */
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode;
  #endif

  LblFilterResult = COM_TRUE;

  #if(COM_TX_IPDU_TMS_EXPLICIT == STD_ON)
  if(LpTxIpdu->ucTxConfigExtn == COM_TRUE)
  {
    /* @Trace: Com_SUD_API_00217 */
    LblFilterResult = (boolean)
      (Com_GaaTxIpduStatusBit[LddIpduHandleId] & COM_TX_TMS_STATUS_MASK);
  }
  #endif
  
  #if(COM_TX_IPDU_TMS_SIG_BASED == STD_ON)
  if((LpTxIpdu->ucTxConfig & COM_TX_IPDU_TMS_CONFIG_MASK) != COM_FALSE)
  {
    /* @Trace: Com_SUD_API_00218 */
    LblFilterResult = COM_FALSE;
    LpTxModeSelect = LpTxIpdu->pTxModeSelect;
    /* Get the pointer to filter status */
    /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null and inside its bound. This is assured by generator" */
    LucFilterStatusIndex = LpTxModeSelect->ucFilterStatusIndex;
    LpFilterStatus =
          &Com_GaaFilterStatus[LucFilterStatusIndex];
    /* Update filter status */
    Com_IpduFilterStatusUpdate(LpTxModeSelect, LpFilterStatus,
      &LblFilterResult, &LucFilterStatusIndex);
  }
  #endif /* #if(COM_TX_IPDU_TMS_SIG_BASED == STD_ON) */

  #if(COM_TX_IPDU_PT == STD_ON) 
  if((Com_GaaTxIpduStatusBit[LddIpduHandleId]&COM_TX_TMS_STATUS_MASK) !=
    LblFilterResult)
  {
    /* @Trace: Com_SUD_API_00219 */
    /* Get the pointer to Tx Mode */
    LpTxMode = &Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex]; 
      
    if(COM_FALSE == LblFilterResult)
    {
      /* @Trace: Com_SUD_API_00220 */
      LpTxMode = 
      &Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex
      +(PduIdType)COM_ONE];
    } 
    if(((LpTxMode->ucTxMode) <= COM_TX_MIXEDNTIMES_MODE) &&
                      ((LpTxMode->ucTxMode) != COM_TX_NONE_MODE))
    {
      /* @Trace: Com_SUD_API_00221 */
      /* Load the the periodic timer with offset value */
      /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
      Com_GaaTxPeriodicTimer[LpTxIpdu->ddTxPeriodicTimerIndex] =
                                  (LpTxMode->usOffsetValue);
    } /* Check whether Tx mode of the I-PDU is periodic or mixed */
  }
  #endif

  /* @Trace: Com_SUD_API_00222 */
  Com_GaaTxIpduStatusBit[LddIpduHandleId] 
      &= (uint16)(COM_TX_TMS_STATUS_CLEAR_MASK);
  Com_GaaTxIpduStatusBit[LddIpduHandleId] 
      |= LblFilterResult;
  #else
  /* @Trace: Com_SUD_API_01317 */
  Com_GaaTxIpduStatusBit[LddIpduHandleId] 
    |= (COM_TX_TMS_STATUS_MASK);          
  #endif

  #if((COM_TX_IPDU_TMS_SIG_BASED == STD_OFF) && \
    (COM_TX_IPDU_TMS_EXPLICIT == STD_OFF))
  COM_UNUSED_PTR(LpTxIpdu);
  #endif
}
#endif
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_ProcessIpduGrpStart                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function start initialization for     **
**                        IPDUs in group                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** InOut parameter      :                                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Com_GaaIpduGroup              **
**                        Function(s) invoked : Det_ReportError()             **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_TX_IPDU == STD_ON)
#if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) ||\
  (COM_TX_IPDU_TMS_EXPLICIT == STD_ON))
static FUNC(void, COM_CODE) Com_ProcessIpduGrpStart(PduIdType LddIpduHandleId,
  boolean blIpduGrp, P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu)
{
  /* @Trace: Com_SUD_API_01410 */
  #if(COM_TX_IPDU_DM == STD_ON)  
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxModeTrue;
  #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) ||\
    (COM_TX_IPDU_TMS_EXPLICIT == STD_ON))
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxModeFalse;
  #endif
  #endif

  if (blIpduGrp == COM_TRUE) 
  {
    #if(COM_TX_IPDU_DM == STD_ON)
    #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) ||\
      (COM_TX_IPDU_TMS_EXPLICIT == STD_ON))
    if((COM_FALSE == (LpTxIpdu->ucTxConfig & COM_TX_IPDU_TMS_CONFIG_MASK))
        ||(COM_FALSE == LpTxIpdu->ucTxConfigExtn))
    #endif
    {
      /* @Trace: Com_SUD_API_00235 */
      LpTxModeTrue = &Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex];
      #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) ||\
        (COM_TX_IPDU_TMS_EXPLICIT == STD_ON))
      LpTxModeFalse = LpTxModeTrue;
      #endif
      #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) ||\
        (COM_TX_IPDU_TMS_EXPLICIT == STD_ON))
      if((((LpTxIpdu->ucTxConfig & COM_TX_IPDU_TMS_CONFIG_MASK)!= COM_ZERO) ||
        (LpTxIpdu->ucTxConfigExtn!=COM_FALSE))&& 
        ((Com_GaaTxIpduStatusBit[LddIpduHandleId]&COM_TX_TMS_STATUS_MASK) != 
          COM_ZERO))
      { 
        /* @Trace: Com_SUD_API_00236 */
        LpTxModeFalse = 
        &Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex
        +(PduIdType)COM_ONE];    
      }
      #endif
      /* polyspace-begin RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */
      if((COM_TX_NONE_MODE == LpTxModeTrue->ucTxMode) &&
        (((LpTxIpdu->ucTxConfig & COM_TX_IPDU_TMS_CONFIG_MASK) 
        != COM_FALSE)
        #if(COM_TX_IPDU_TMS_EXPLICIT == STD_ON)
        ||(LpTxIpdu->ucTxConfigExtn != COM_FALSE)
        #endif
        ))
      {
        /* @Trace: Com_SUD_API_00237 */
        #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) ||\
          (COM_TX_IPDU_TMS_EXPLICIT == STD_ON))
        if(COM_TX_NONE_MODE == LpTxModeFalse->ucTxMode)
        #endif
        {
          /* polyspace +2 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
          Com_GaaTxDMTimer[LpTxIpdu->ddTxIpduDmIndex] =
          Com_GaaTxIpduDm[LpTxIpdu->ddTxIpduDmIndex].usDmTimeout 
          + (uint16)COM_ONE;
          /* Set Request bit */
          Com_GaaTxIpduStatusBit[LddIpduHandleId] 
            |= COM_TX_REQ_STATUS_MASK;
        }
      }
      /* polyspace-end RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */
    }
  #endif
  }
  #if(COM_TX_IPDU_DM == STD_OFF)
  /* @Trace: Com_SUD_API_01551 */
  COM_UNUSED(LddIpduHandleId);
  COM_UNUSED_PTR(LpTxIpdu);
  #endif
}
#endif
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_ProcessIpduTiming                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function start initialization for     **
**                        IPDUs related to timing                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** InOut parameter      :                                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Com_GaaIpduGroup              **
**                        Function(s) invoked : Det_ReportError()             **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_TX_IPDU == STD_ON)
#if((COM_TX_IPDU_DM == STD_ON) || \
    (COM_TX_IPDU_PT == STD_ON))
static FUNC(void, COM_CODE) Com_ProcessIpduTiming(PduIdType LddIpduHandleId,
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu, 
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode)
{
  #if(COM_TX_IPDU_DM == STD_ON)
  if((LpTxIpdu->ucTxConfig & COM_TX_IPDU_DM_CONFIG_MASK) != COM_FALSE)
  {
    /* @Trace: Com_SUD_API_00228 */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    Com_GaaTxDMTimer[LpTxIpdu->ddTxIpduDmIndex] = (uint16)COM_ZERO;
    if((((LpTxIpdu->ucTxConfig & COM_TX_IPDU_TMS_CONFIG_MASK) == COM_FALSE)
    #if(COM_TX_IPDU_TMS_EXPLICIT == STD_ON)
    ||(LpTxIpdu->ucTxConfigExtn == COM_FALSE)
    #endif
    )&& (LpTxMode->ucTxMode == COM_TX_NONE_MODE))
    {
      /* @Trace: Com_SUD_API_00229 */
      Com_GaaTxIpduStatusBit[LddIpduHandleId] 
        |= COM_TX_DM_STATUS_MASK;
    }
  
      /* @Trace: Com_SUD_API_00230 */
      Com_GaaTxIpduStatusBit[LddIpduHandleId] 
        |= COM_TX_DM_STATUS_MASK_1ST;
  }
  #endif  
  #if(COM_TX_IPDU_PT == STD_ON) 
  if(((LpTxMode->ucTxMode) <= COM_TX_MIXEDNTIMES_MODE) &&
          ((LpTxMode->ucTxMode) != COM_TX_NONE_MODE))
  {
    /* @Trace: Com_SUD_API_00231 */
    /* Load the the periodic timer with offset value */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    Com_GaaTxPeriodicTimer[LpTxIpdu->ddTxPeriodicTimerIndex] =
                      (LpTxMode->usOffsetValue);

  } /* Check whether Tx mode of the I-PDU is periodic or mixed */
  #endif 
  #if(COM_TX_IPDU_DM == STD_OFF)
  /* @Trace: Com_SUD_API_01550 */
  COM_UNUSED(LddIpduHandleId);
  #endif
}
#endif
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h" 

/*******************************************************************************
** Function Name        : Com_StartTxIPDUs_TpIpduStatus                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function start initialization for     **
**                        IP IPDU status                                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** InOut parameter      :                                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Com_GaaIpduGroup              **
**                        Function(s) invoked : Det_ReportError()             **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h" 
#if(COM_TX_IPDU == STD_ON)
#if(COM_TX_TP_SUPPORT == STD_ON)
static FUNC(void, COM_CODE) Com_StartTxIPDUs_TpIpduStatus(
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu)
{    
  /* @Trace: Com_SUD_API_01411 */
  /* Pointer to TP Ipdu structure */
  P2CONST(Com_TxTPIpdu, AUTOMATIC, COM_CONST) LpTxTPIpdu;
  /* #1632 : Initialize TP status */
  /* Get the pointer to Tx Ipdu */
  if(LpTxIpdu->ucTxTPRef != COM_INVALID_PARAM)
  {
    /* @Trace: Com_SUD_API_00239 */
    LpTxTPIpdu = &Com_GaaTxTPIpdu[LpTxIpdu->ucTxTPRef];
    Com_GaaTxTPStatus[LpTxTPIpdu->ucTxTPStatusRef] &= 
                          (uint8)~(LpTxTPIpdu->ucTxTPStatusMask);
  }
}
#endif
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h" 

/*******************************************************************************
** Function Name        : Com_ProcessFilterOneEveryN                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function start initialization for     **
**                        filter one every N                                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** InOut parameter      :                                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Com_GaaIpduGroup              **
**                        Function(s) invoked : Det_ReportError()             **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h" 
#if(COM_TX_IPDU == STD_ON)
#if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) &&\
  (COM_FILTER_ONEEVERYN == STD_ON))
static FUNC(void, COM_CODE) Com_ProcessFilterOneEveryN(PduIdType LddIpduHandleId,
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu)
{
  /* @Trace: Com_SUD_API_01412 */

  uint8 LucFilterStsCount;

  if((LpTxIpdu->ucTxConfig & COM_TX_IPDU_TMS_CONFIG_MASK) 
    != COM_FALSE)
  {
    /* @Trace: Com_SUD_API_00232 */
    LucFilterStsCount = COM_NO_OF_FILTER_ONEVERYN;
    do
    {
      /* @Trace: Com_SUD_API_00233 */
      --LucFilterStsCount;
      if(Com_GaaFilterOneEveryN[LucFilterStsCount].ddComPduId ==
                                                    LddIpduHandleId)
      {
        #if(COM_RX_SIGNAL_FILTER == STD_ON)
        if(Com_GaaFilterOneEveryN[LucFilterStsCount].ucFltrStsMask
                                                        != COM_ZERO)
        #endif
        /* polyspace +1 RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */
        {
          /* @Trace: Com_SUD_API_00234 */
          *Com_GaaFilterOneEveryN[LucFilterStsCount].pCounter =
                                                        (uint16)COM_ZERO;
        }
      }
    }while(LucFilterStsCount != COM_ZERO);
  }
}
#endif
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h" 

/*******************************************************************************
** Function Name        : Com_ProcessIpduCounter                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function start initialization for     **
**                        IPDUs counter                                       **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** InOut parameter      :                                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Com_GaaIpduGroup              **
**                        Function(s) invoked : Det_ReportError()             **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h" 
#if(COM_TX_IPDU == STD_ON)
#if(COM_TX_IPDU_COUNTER_ENABLED == STD_ON)
static FUNC(void, COM_CODE) Com_ProcessIpduCounter(
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu)
{
  /* @Trace: Com_SUD_API_01413 */
  P2CONST(Com_TxIpduCounter, AUTOMATIC, COM_CONST) LpTxIpduCounter;

  if(LpTxIpdu->ddTxIpduCounter != COM_INVALID_TXID_PARAM)
  {
    /* @Trace: Com_SUD_API_00227 */
    LpTxIpduCounter 
      = &Com_GaaTxIpduCounter[LpTxIpdu->ddTxIpduCounter];
    Com_GaaTxIpduCountVal[LpTxIpduCounter->ucTxIpduCountData] &=
              (uint8)(~(LpTxIpduCounter->ucTxIpduCntWrpMask));
  }
}
#endif
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h" 

/*******************************************************************************
** Function Name        : Com_ProcessIpduRepetition                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function start initialization for     **
**                        IPDUs repetition arrays                             **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** InOut parameter      :                                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Com_GaaIpduGroup              **
**                        Function(s) invoked : Det_ReportError()             **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h" 
#if(COM_TX_IPDU == STD_ON)
#if(COM_TX_IPDU_REPETITION == STD_ON)
static FUNC(void, COM_CODE) Com_ProcessIpduRepetition(
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu)
{
  if((LpTxIpdu->ddTxReptIndex) != COM_INVALID_TXID_PARAM)
  {
    /* @Trace: Com_SUD_API_00238 */
    Com_GaaTxReptTimer[LpTxIpdu->ddTxReptIndex] = (uint16)COM_ZERO;
    Com_GaaTxReptCount[LpTxIpdu->ddTxReptIndex] = COM_ZERO;
    Com_GaaTxReptSubCount[LpTxIpdu->ddTxReptIndex] = COM_ZERO;
  }
}
#endif
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h" 

/*******************************************************************************
** Function Name        : Com_StartTxIPDUs                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function startTx IPDUs                **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** InOut parameter      :                                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Com_GaaIpduGroup              **
**                        Function(s) invoked : Det_ReportError()             **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_TX_IPDU == STD_ON)
FUNC(void, COM_CODE) Com_StartTxIPDUs(PduIdType IpduIndex, boolean Initialize, 
  boolean blIpduGrp)
{
  /* @Trace: Com_SUD_API_00210 */
  /* Pointer to Ipdu group structure */
  PduIdType LddIpduHandleId;
  /* Pointer to Tx Ipdu */
  #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) ||\
    (COM_TX_IPDU_TMS_EXPLICIT == STD_ON) || (COM_TX_IPDU_PT == STD_ON) ||\
    (COM_TX_IPDU_DM == STD_ON) || (COM_TX_TP_SUPPORT == STD_ON) ||\
    (COM_TX_IPDU_REPETITION == STD_ON) ||\
    (COM_TX_IPDU_COUNTER_ENABLED == STD_ON) ||\
    (COM_TX_SIGNAL_UB == STD_ON) || (COM_TX_SIGGROUP_UB == STD_ON) ||\
    (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON))
  P2CONST(Com_TxIpdu, AUTOMATIC, COM_CONST) LpTxIpdu; 
  #endif

  #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON)||(COM_TX_IPDU_PT == STD_ON) \
  ||(COM_TX_IPDU_DM == STD_ON)||(COM_TX_IPDU_TMS_EXPLICIT == STD_ON))
  /* Pointer to Tx mode structure */
  P2CONST(Com_TxMode, AUTOMATIC, COM_CONST) LpTxMode;
  #endif 

  if (blIpduGrp == COM_TRUE)
  {
    /* @Trace: Com_SUD_API_00212 */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    LddIpduHandleId = (PduIdType)Com_GaaTxIpduGroup[IpduIndex];
  }
  else 
  {
    /* @Trace: Com_SUD_API_00213 */
    LddIpduHandleId = IpduIndex;
  }

  if(Com_GaaTxIpduStatus[LddIpduHandleId] == (PduIdType)COM_ZERO)
  {
    /* @Trace: Com_SUD_API_00216 */
    Com_IpduStatusInit(LddIpduHandleId, Initialize);

    #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) ||\
      (COM_TX_IPDU_TMS_EXPLICIT == STD_ON) || (COM_TX_IPDU_PT == STD_ON) ||\
      (COM_TX_IPDU_DM == STD_ON) || (COM_TX_TP_SUPPORT == STD_ON) ||\
      (COM_TX_IPDU_REPETITION == STD_ON) ||\
      (COM_TX_IPDU_COUNTER_ENABLED == STD_ON) ||\
      (COM_TX_SIGNAL_UB == STD_ON) || (COM_TX_SIGGROUP_UB == STD_ON) ||\
      (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON))
    LpTxIpdu = &Com_GaaTxIpdu[LddIpduHandleId];
    #endif

    #if((COM_TX_IPDU_TMS_EXPLICIT == STD_ON) || \
        (COM_TX_IPDU_TMS_SIG_BASED == STD_ON) || \
        (COM_TX_IPDU_PT == STD_ON))
    Com_ProcessIpduFilterStatus(LddIpduHandleId, LpTxIpdu);
    #endif
    
    if(COM_TRUE == Initialize)
    {
      #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) ||\
        (COM_TX_IPDU_TMS_EXPLICIT == STD_ON) || (COM_TX_IPDU_PT == STD_ON) ||\
        (COM_TX_IPDU_DM == STD_ON) || (COM_TX_TP_SUPPORT == STD_ON) ||\
        (COM_TX_IPDU_REPETITION == STD_ON) ||\
        (COM_TX_IPDU_COUNTER_ENABLED == STD_ON) ||\
        (COM_TX_SIGNAL_UB == STD_ON) || (COM_TX_SIGGROUP_UB == STD_ON) ||\
        (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON) ||(COM_TX_SIGGROUP == STD_ON))
      /* @Trace: Com_SUD_API_00389 */
      Com_TxBuffersReInit(LddIpduHandleId);
      #endif
      /* @Trace: Com_SUD_API_00223 */
      #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON)||(COM_TX_IPDU_PT == STD_ON) \
      ||(COM_TX_IPDU_DM == STD_ON)||(COM_TX_IPDU_TMS_EXPLICIT == STD_ON))
      /* Get the pointer to Tx Mode */
      LpTxMode = &Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex];
      #endif  
      #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON)||(COM_TX_IPDU_PT == STD_ON)\
      ||(COM_TX_IPDU_TMS_EXPLICIT == STD_ON))
      if(COM_FALSE == 
      (Com_GaaTxIpduStatusBit[LddIpduHandleId] & COM_TX_TMS_STATUS_MASK))
      {
        /* @Trace: Com_SUD_API_00224 */
        LpTxMode = 
        &Com_GaaTxMode[LpTxIpdu->ddTrueTxModeIndex
        +(PduIdType)COM_ONE];
      }
      #endif  
      #if (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON)         
      /* polyspace +1 RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */ 
      if((LpTxIpdu->ucTxConfig & COM_TX_IPDU_MDT_CONFIG_MASK) 
        != COM_FALSE)
      {
        /* @Trace: Com_SUD_API_00225 */
        Com_GaaTxMDTimer[LpTxIpdu->ddTxMDTimerIndex] = (uint16)COM_ZERO;
      }
      #endif  
      #if((COM_TX_SIGNAL_UB == STD_ON) || \
                      (COM_TX_SIGGROUP_UB == STD_ON))
      if((LpTxIpdu->ucTxConfig & COM_TX_IPDU_UB_CONFIG_MASK) != COM_FALSE)
      {
        /* @Trace: Com_SUD_API_00226 */
        Com_TxClearUpdateBit(LpTxIpdu,
                Com_GaaTxPduInfoPtr[LddIpduHandleId].SduDataPtr);
      }
      #endif
      /* @Trace: Com_SUD_API_01552 */
      #if(COM_TX_IPDU_COUNTER_ENABLED == STD_ON)
      Com_ProcessIpduCounter(LpTxIpdu);
      #endif

      #if((COM_TX_IPDU_DM == STD_ON) || \
          (COM_TX_IPDU_PT == STD_ON))
      Com_ProcessIpduTiming(LddIpduHandleId, LpTxIpdu, LpTxMode);
      #endif

      #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) &&\
        (COM_FILTER_ONEEVERYN == STD_ON))
      Com_ProcessFilterOneEveryN(LddIpduHandleId, LpTxIpdu);
      #endif
    } /* @End if(Initialize == COM_TRUE) */
    
    /* @Trace: Com_SUD_API_01553 */
    #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) ||\
      (COM_TX_IPDU_TMS_EXPLICIT == STD_ON))
    Com_ProcessIpduGrpStart(LddIpduHandleId, blIpduGrp, LpTxIpdu);
    #endif

    #if(COM_TX_IPDU_REPETITION == STD_ON)
    Com_ProcessIpduRepetition(LpTxIpdu);
    #endif

    #if(COM_TX_TP_SUPPORT == STD_ON)
    Com_StartTxIPDUs_TpIpduStatus(LpTxIpdu);
    #endif
  }

  if((Com_GaaTxIpduStatus[LddIpduHandleId] < Com_GaaTxIpduBelongGroup
    [LddIpduHandleId]) ||((uint16)COM_ZERO == Com_GaaTxIpduBelongGroup
    [LddIpduHandleId]))
  {
    /* @Trace: Com_SUD_API_01796 */
    Com_GaaTxIpduStatus[LddIpduHandleId]++;
  }
}
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_RxBuffersReInit                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function reinitialize Rx Com buffers  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** InOut parameter      :                                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Com_GaaIpduGroup              **
**                        Function(s) invoked : Det_ReportError()             **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_RX_IPDU == STD_ON)
#if((COM_RX_SIGGROUP == STD_ON) || \
  ((COM_RX_SIGNAL_FILTER == STD_ON) && (COM_RX_SIGNAL == STD_ON)) || \
  ((COM_RX_SIGGROUP_FILTER == STD_ON) && (COM_RX_SIGGROUP == STD_ON)))
FUNC(void, COM_CODE) Com_RxBuffersReInit(PduIdType LddIpduHandleId)
{
  /* @Trace: Com_SUD_API_01414 */
  #if((COM_RX_SIGGROUP == STD_ON) || \
  ((COM_RX_SIGNAL_FILTER == STD_ON) && (COM_RX_SIGNAL == STD_ON)))
  /* Local Index */    
  uint16 lucIdx;
  #endif

  #if((COM_RX_SIGGROUP_ARRAY_ACCESS == STD_ON) ||\
     (COM_RX_SIGNAL_FILTER == STD_ON) ||\
     (COM_RX_SIGGROUP_FILTER == STD_ON))
  #if((COM_RX_SIGNAL_FILTER == STD_ON) && (COM_RX_SIGNAL == STD_ON))
  /* Pointer to Rx Signal Array */
  P2CONST(Com_RxSignal, AUTOMATIC, COM_CONST) pRxSig;
  #endif
  #if((COM_RX_SIGGROUP_FILTER == STD_ON) && (COM_RX_SIGGROUP == STD_ON))
  /* Pointer to Rx Signal Group Array */
  P2CONST(Com_RxSigInGrp, AUTOMATIC, COM_CONST) pRxSigGrp; 
  #endif
  #endif

  #if(COM_RX_SIGGROUP == STD_ON)
  /* Initialize shadow buffer of included signal groups */
  #if(COM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
  if (Com_GlNoOfRxSigGrp > (uint16)COM_MACRO_ZERO)
  #endif
  {
    #if(COM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
    /* @Trace: Com_SUD_API_01816 */
    /* @Trace: Com_SUD_API_01817 */
    for (lucIdx = 0 ; lucIdx < Com_GlNoOfRxSigGrp; lucIdx++)        
    #else
    for (lucIdx = 0 ; lucIdx < COM_RX_SIGGROUP_COUNT; lucIdx++)
    #endif
    {
      if(
        #if(COM_RX_SIGGROUP_ARRAY_ACCESS == STD_ON)
        (Com_GaaRxSigGroup[lucIdx].blArrayAccess == COM_FALSE) && 
        #endif
        (Com_GaaRxSigGroup[lucIdx].ddRxpduId == LddIpduHandleId)
        )
      {
        /* @Trace: Com_SUD_API_01818 */
        /* For Signal Group, The Total Length of Group is ddSigTypeOrSize element*/
        /* polyspace +1 RTE:STD_LIB [Not a defect:Low] "All pointers are available and in range. This is assured by generator" */
        memcpy((Com_GaaRxSigGroup[lucIdx].pPackShadowBuffer)->pWrBuffer,
          Com_GaaRxSigGroup[lucIdx].pReInitBuffer,
          Com_GaaTxPack[Com_GaaRxSigGroup[lucIdx].ddTxSigGrpPackIndex].
            ddSigTypeOrSize);
      }
    }
  }
  #endif

  /* Intialize old_value of filter mechanisms for each signal */
  /*For Signal*/
  #if((COM_RX_SIGNAL_FILTER == STD_ON) && (COM_RX_SIGNAL == STD_ON))
  #if(COM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
  /* @Trace: Com_SUD_API_01819 */
  /* @Trace: Com_SUD_API_01820 */
  for (lucIdx = 0 ; lucIdx < Com_GlNoOfRxSignal; lucIdx++)        
  #else
  for (lucIdx = 0 ; lucIdx < COM_RX_SIGNAL_COUNT; lucIdx++)
  #endif
  {
    /* @Trace: Com_SUD_API_01821 */
    /* Initialize pointer pRxSig */
    pRxSig = &Com_GaaRxSignal[lucIdx];
    /* polyspace-begin RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */ 
    /* Initialize old value only apply for Signal has filter type is MASKED_NEW_DIFFERS_MASKED_OLD */
    if((pRxSig->pFilter != NULL_PTR) &&\
      (pRxSig->blfilterMasked == COM_TRUE) &&\
      (pRxSig->ddRxpduId == LddIpduHandleId))
    {
    /* polyspace-end RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */ 
      /* @Trace: Com_SUD_API_01823 */
      memcpy(
        ((P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST))
          (pRxSig->pFilter))->pSignalBuffer,
        ((P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST))
          (pRxSig->pFilter))->pReInitBuffer,
        (Com_GaaRxUnpack[pRxSig->ddRxUnpackIndex].ddSignalSize));
    }
  }
  #endif  
  /*For Signal Group*/
  #if((COM_RX_SIGGROUP_FILTER == STD_ON) && (COM_RX_SIGGROUP == STD_ON))
  #if(COM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
  /* @Trace: Com_SUD_API_01824 */
  /* @Trace: Com_SUD_API_01825 */
  for (lucIdx = 0 ; lucIdx < Com_GlNoOfRxSigInGrp; lucIdx++)        
  #else
  for (lucIdx = 0 ; lucIdx < COM_RX_SIGINGROUP_COUNT; lucIdx++)
  #endif
  {
    /* @Trace: Com_SUD_API_01826 */
    /* Initialize pointer pRxSigGrp */
    pRxSigGrp = &Com_GaaRxSigInGrp[lucIdx];
    /* Initialize old value only apply for Signal has filter type is MASKED_NEW_DIFFERS_MASKED_OLD */
    if((pRxSigGrp->pFilter != NULL_PTR) &&
      (pRxSigGrp->blfilterMasked == COM_TRUE) && 
      (Com_GaaRxSigGroup[pRxSigGrp->ddSigGrpIndex].ddRxpduId == 
        LddIpduHandleId))
    {
      /* @Trace: Com_SUD_API_01828 */
      memcpy(
        ((P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST))
          (pRxSigGrp->pFilter))->pSignalBuffer,
        ((P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST))
          (pRxSigGrp->pFilter))->pReInitBuffer,
        (Com_GaaRxUnpack[pRxSigGrp->ddRxUnpackIndex].ddSignalSize));
    }
  }
  #endif
}
#endif
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_ProcessRxIpduTiming                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_StartRxIPDUs                    **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
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
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
#if((COM_RX_IPDU_DM == STD_ON) || \
  (COM_RX_SIGNAL_UBDM == STD_ON) || \
  (COM_RX_SIGGROUP_UBDM == STD_ON))
static FUNC(void, COM_CODE) Com_ProcessRxIpduTiming(PduIdType LddIpduHandleId,
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu)
{  
  /* @Trace: Com_SUD_API_01415 */
  P2CONST(Com_RxDm, AUTOMATIC, COM_CONST) LpRxDm;
  PduIdType LddRxDmTimerIndex;
  uint8 LucCount;
  /* polyspace +1 RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */
  if((Com_GaaRxIpdu[LddIpduHandleId].ucRxConfig &
                  COM_RX_DM_CONFIG_MASK) != COM_FALSE)
  {
    if(((PduIdType)COM_ZERO == 
                Com_GaaRxDmStatus[Com_GaaRxIpdu[LddIpduHandleId]
                .ddRxIpduDmIndex]))
    {
      /* @Trace: Com_SUD_API_00249 */
      LddRxDmTimerIndex = LpRxIpdu->ddRxIpduDmIndex;
      LpRxDm = &Com_GaaRxDm[LddRxDmTimerIndex];
      LucCount = LpRxDm->ucRxDmCount;
      do
      {
        /* @Trace: Com_SUD_API_00250 */
        Com_GaaRxDMTimer[LddRxDmTimerIndex] 
          = LpRxDm->ulRxDmFirstTimeout;
        --LucCount;
        LddRxDmTimerIndex++;
        LpRxDm = &Com_GaaRxDm[LddRxDmTimerIndex];
      }while(LucCount != COM_ZERO);
    }
  }
}
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h"


/*******************************************************************************
** Function Name        : Com_ProcessRxFilterOneEveryN                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_StartRxIPDUs                    **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
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
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_RX_IPDU == STD_ON)
#if((COM_FILTER_ONEEVERYN == STD_ON) && \
  (COM_RX_SIGNAL_FILTER == STD_ON))
static FUNC(void, COM_CODE) Com_ProcessRxFilterOneEveryN(PduIdType LddIpduHandleId)
{ 
  /* @Trace: Com_SUD_API_01416 */
  uint8 LucFilterStsCount;

  if(((Com_GaaRxIpdu[LddIpduHandleId].ucRxConfig &
    COM_RX_ONEVERYN_CONFIG_MASK) != COM_FALSE))
  {
    /* @Trace: Com_SUD_API_00246 */
    LucFilterStsCount = COM_NO_OF_FILTER_ONEVERYN;
    do
    {
      /* @Trace: Com_SUD_API_00247 */
      --LucFilterStsCount;
      #if(COM_TX_IPDU_TMS_SIG_BASED == STD_ON)
      if(Com_GaaFilterOneEveryN[LucFilterStsCount].ddComPduId ==
                                          LddIpduHandleId)
      #endif
      {
        #if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) \
        && (COM_NO_OF_FILTER_ONEVERYN > COM_MACRO_ZERO))
        /* polyspace +1 RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */
        if(COM_ZERO 
          == Com_GaaFilterOneEveryN[LucFilterStsCount].ucFltrStsMask)
        #endif
        {    
          /* @Trace: Com_SUD_API_00248 */             
          *Com_GaaFilterOneEveryN[LucFilterStsCount].pCounter 
            = (uint16)COM_ZERO;
        }
      }
    }while(LucFilterStsCount != COM_ZERO);
  }
}
#endif
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_ProcessRxIpduCounter                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_StartRxIPDUs                    **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
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
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_RX_IPDU_COUNTER_ENABLED == STD_ON)
static FUNC(void, COM_CODE) Com_ProcessRxIpduCounter(P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu)
{
  /* @Trace: Com_SUD_API_01417 */
  P2CONST(Com_RxIpduCounter, AUTOMATIC, COM_CONST) LpRxIpduCounter;

  SchM_Enter_Com_RX_IPDU_STS_PROTECTION_AREA();
  if((LpRxIpdu->ddRxIpduCounter != COM_INVALID_RXID_PARAM))
  {
    /* @Trace: Com_SUD_API_00252 */
    LpRxIpduCounter 
      = &Com_GaaRxIpduCounter[LpRxIpdu->ddRxIpduCounter];
	
    Com_GaaRxIpduCountVal[LpRxIpduCounter->ucRxIpduCountData] &=
    (uint8)(~(LpRxIpduCounter->ucRxIpduCntWrpMask));
    Com_GaaRamIpduCounterSts[LpRxIpduCounter->ucIpduCnterStsIndex] &=
    (uint8)(~(LpRxIpduCounter->ucIpduCounterEnMask));
  }
  /* @Trace: Com_SUD_API_01922 */
  SchM_Exit_Com_RX_IPDU_STS_PROTECTION_AREA();
}
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_ProcessRxIpduReplication                        **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_StartRxIPDUs                    **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
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
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_RX_REPLICATION == STD_ON)
static FUNC(void, COM_CODE) Com_ProcessRxIpduReplication(
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu)
{
  /* @Trace: Com_SUD_API_01418 */
  P2CONST(Com_RxIpduReplication, AUTOMATIC, COM_CONST) LpRxIpduRepl;

  if((LpRxIpdu->ucRxIpduRepliIndex != COM_INVALID_NONE))
  {
    /* @Trace: Com_SUD_API_00253 */
    LpRxIpduRepl
      = &Com_GaaRxIpduReplication[LpRxIpdu->ucRxIpduRepliIndex];
    Com_GaaRxRepliCount[LpRxIpduRepl->ucIpduRepliCountIndex] &=
      (uint8)(~(uint8)((COM_REPLICATION_MASK <<
      (COM_EIGHT - (LpRxIpduRepl->ucIpduRepliCountShift)))));
    Com_GaaRamIpduRepliSts[LpRxIpduRepl->ucIpduRepliStsIndex] &=
      (uint8)(~(LpRxIpduRepl->ucIpduRepliEnMask));
  }
}
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_ProcessRxTpIpduStatus                           **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Sub function of Com_StartRxIPDUs                    **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
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
** Remarks              : Global Variable(s)     :                            **
**                        Function(s) invoked    :                            **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_RX_TP_SUPPORT == STD_ON)
static FUNC(void, COM_CODE) Com_ProcessRxTpIpduStatus(P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu)
{
  /* @Trace: Com_SUD_API_01419 */
  /* Pointer to TP Ipdu structure */
  P2CONST(Com_RxTPIpdu, AUTOMATIC, COM_CONST) LpRxTPIpdu;
  /* Get the pointer to Rx Ipdu */
  if(LpRxIpdu->ucRxTPRef != COM_INVALID_PARAM)
  {
    /* @Trace: Com_SUD_API_00254 */
    /* Get the pointer to Rx TP structure */
    LpRxTPIpdu = &Com_GaaRxTPIpdu[LpRxIpdu->ucRxTPRef];
    Com_GaaRxTPStatus[LpRxTPIpdu->ucRxTPStatusRef] 
      &= (uint8)(~(LpRxTPIpdu->ucRxTPStatusMask));
    /* Set the length of Ipdu copied to zero */
    Com_GaaRxIpduTPLength[LpRxTPIpdu->ucRxIpduTPLengthRef] = COM_ZERO;
  }
}
#endif   
#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_StartRxIPDUs                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This internal function start Rx IPDUs               **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** InOut parameter      :                                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Com_GaaIpduGroup              **
**                        Function(s) invoked : Det_ReportError()             **
*******************************************************************************/
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_RX_IPDU == STD_ON)
FUNC(void, COM_CODE) Com_StartRxIPDUs(PduIdType IpduIndex, boolean Initialize, 
  boolean blIpduGrp)
{
  /* @Trace: Com_SUD_API_00241 */
  PduIdType LddIpduHandleId;

  #if((COM_RX_IPDU_DM == STD_ON) || \
    (COM_RX_SIGNAL_UBDM == STD_ON) || \
    (COM_RX_SIGGROUP_UBDM == STD_ON) || \
    (COM_RX_IPDU_COUNTER_ENABLED == STD_ON) || \
    (COM_RX_TP_SUPPORT == STD_ON) || \
    (COM_RX_REPLICATION == STD_ON))
  P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu;
  #endif    

  if (blIpduGrp == COM_TRUE)
  {
    /* @Trace: Com_SUD_API_00243 */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
    LddIpduHandleId = (PduIdType)Com_GaaRxIpduGroup[IpduIndex]; 
  }
  else 
  {
    /* @Trace: Com_SUD_API_00244 */
    LddIpduHandleId = IpduIndex;
  }
  
  /* Check if the I-PDU has already been started */
  if((PduIdType)COM_ZERO == Com_GaaRxIpduStatus[LddIpduHandleId])
  { 
    #if((COM_RX_IPDU_DM == STD_ON) || \
      (COM_RX_SIGNAL_UBDM == STD_ON) || \
      (COM_RX_SIGGROUP_UBDM == STD_ON) || \
      (COM_RX_IPDU_COUNTER_ENABLED == STD_ON) || \
      (COM_RX_TP_SUPPORT == STD_ON) || \
      (COM_RX_REPLICATION == STD_ON))
    /* @Trace: Com_SUD_API_00245 */
    LpRxIpdu = &Com_GaaRxIpdu[LddIpduHandleId];
    #endif

    if(COM_TRUE == Initialize)
    {
      #if((COM_RX_IPDU_DM == STD_ON) || \
        (COM_RX_SIGNAL_UBDM == STD_ON) || \
        (COM_RX_SIGGROUP_UBDM == STD_ON) || \
        (COM_RX_IPDU_COUNTER_ENABLED == STD_ON) || \
        (COM_RX_TP_SUPPORT == STD_ON) || \
        (COM_RX_REPLICATION == STD_ON))
      /* @Trace: Com_SUD_API_01815 */
      /* Initialize Data of the I-PDU */
      memcpy((void *)Com_GaaRxPduInfoPtr[LddIpduHandleId].SduDataPtr, \
        (const void *)(LpRxIpdu->pReInitBuffer),
        (uint16)LpRxIpdu->ddRxIpduLength);
      #endif  
      
      #if((COM_RX_SIGGROUP == STD_ON) || \
        ((COM_RX_SIGNAL_FILTER == STD_ON) && (COM_RX_SIGNAL == STD_ON)) || \
        ((COM_RX_SIGGROUP_FILTER == STD_ON) && (COM_RX_SIGGROUP == STD_ON)))
      Com_RxBuffersReInit(LddIpduHandleId);
      #endif

      #if((COM_FILTER_ONEEVERYN == STD_ON) && \
        (COM_RX_SIGNAL_FILTER == STD_ON))
      Com_ProcessRxFilterOneEveryN(LddIpduHandleId);
      #endif

      #if((COM_RX_IPDU_DM == STD_ON) || \
        (COM_RX_SIGNAL_UBDM == STD_ON) || \
        (COM_RX_SIGGROUP_UBDM == STD_ON))
      Com_ProcessRxIpduTiming(LddIpduHandleId, LpRxIpdu);
      #endif
      
      #if(COM_RX_IPDU_COUNTER_ENABLED == STD_ON)
      Com_ProcessRxIpduCounter(LpRxIpdu);
      #endif
      
      #if(COM_RX_REPLICATION == STD_ON)
      Com_ProcessRxIpduReplication(LpRxIpdu);
      #endif
    }
    /* @Trace: Com_SUD_API_01554 */
    /* #1632 : Initialize TP status */
    #if(COM_RX_TP_SUPPORT == STD_ON)
    Com_ProcessRxTpIpduStatus(LpRxIpdu);
    #endif          
  }
  if((Com_GaaRxIpduStatus[LddIpduHandleId] < Com_GaaRxIpduBelongGroup
    [LddIpduHandleId]) || ((uint16)COM_ZERO == Com_GaaRxIpduBelongGroup
    [LddIpduHandleId]))
  {
    /* @Trace: Com_SUD_API_01797 */
    Com_GaaRxIpduStatus[LddIpduHandleId]++;
  }  

  #if((COM_RX_IPDU_DM == STD_ON) || \
    (COM_RX_SIGNAL_UBDM == STD_ON) || \
    (COM_RX_SIGGROUP_UBDM == STD_ON))
  /* polyspace +1 RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */
  if((Com_GaaRxIpdu[LddIpduHandleId].ucRxConfig &
                  COM_RX_DM_CONFIG_MASK) != COM_FALSE)
  {
    if((Com_GaaRxIpduDmBelongGroup[LddIpduHandleId] > Com_GaaRxDmStatus
      [Com_GaaRxIpdu[LddIpduHandleId].ddRxIpduDmIndex]) ||
      ((uint16)COM_ZERO == Com_GaaRxIpduDmBelongGroup[LddIpduHandleId]))
    {
      /* @Trace: Com_SUD_API_00251 */
      Com_GaaRxDmStatus[Com_GaaRxIpdu[LddIpduHandleId]
        .ddRxIpduDmIndex]++;
    }
  }
  #endif
}
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h"
/*******************************************************************************
** Function Name        : Com_EnableReceptionDM                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function enables the reception deadline        **
**                        monitoring for the I-PDU(s) within the requested    **
**                        Rx I-PDU group.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different I-PDU groups.               **
**                        Non-Reentrant for same I-PDU group.                 **
**                                                                            **
** Input Parameters     : IpduGroupId                                         **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     :Com_GaaIpduGroup            **
**                                                Com_GaaIpduGrpDmStatus      **
**                                                Com_GaaRxIpduGroup          **
**                                                Com_GaaRxIpdu               **
**                                                Com_GaaRxDmStatus           **
**                                                Com_GaaRxDm                 **
**                                                Com_GaaRxDMTimer            **
**                        Function(s) invoked    :SchM_Enter_xxx()            **
**                                                SchM_Exit_xxx()             **
*******************************************************************************/
#if((COM_RX_IPDU_DM == STD_ON) || \
     (COM_RX_SIGNAL_UBDM == STD_ON) || \
     (COM_RX_SIGGROUP_UBDM == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_00192*/
FUNC(void, COM_CODE) Com_EnableReceptionDM(Com_IpduGroupIdType IpduGroupId)
{
  /* @Trace: Com_SUD_API_00256 */
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  uint8 LucReturnValue;
  LucReturnValue = E_OK;
  /* Check whether module is initialized */
  COM_DET_INIT_STATUS_CHECK_FLAG(COMSERVICEID_RECEPTIONDMENABLE);
  /* Check whether I-PDU group ID is out of range */
  #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01318 */
  COM_DET_IPDUGROUPID_RANGE_CHECK_FLAG(COMSERVICEID_RECEPTIONDMENABLE);
  #else
  /* @Trace: Com_SUD_API_01319 */
  COM_DET_IPDUGROUPID_RANGE_CHECK_FLAG_PB(COMSERVICEID_RECEPTIONDMENABLE);
  #endif
  /* Get the pointer to the I-PDU group structure */
  if(LucReturnValue == (uint8)E_OK)
  #endif
  {
    /* @Trace: Com_SUD_API_00257 */
    Com_IpduGroupIdType LddIpduGroupId;
    LddIpduGroupId = IpduGroupId;
    P2CONST(Com_IpduGroup, AUTOMATIC, COM_CONST) LpIpduGroup;
    /* Get the pointer to the I-PDU group structure */
    LpIpduGroup = &Com_GaaIpduGroup[LddIpduGroupId];
    /*Check this IPDU grp is enable API Rx En/Dis ReceptionDM*/
    if(COM_TRUE == (LpIpduGroup->blRxDmEnabled))
    {
      /* @Trace: Com_SUD_API_00258 */
      /* Pointer to Rx Ipdu structure */
      P2CONST(Com_RxIpdu, AUTOMATIC, COM_CONST) LpRxIpdu;
      #if(COM_RX_IPDU_DM == STD_ON)
      /* Pointer to RxDm structure */
      P2CONST(Com_RxDm, AUTOMATIC, COM_CONST) LpRxDm;
      #endif
      /* Local variable to store Com Ipdu handle ID */
      PduIdType LddIpduIndex;
      PduIdType LddPduIndex;
      /* Local variable to store no. Of Ipdus */
      PduIdType LddNoOfIpdus;
      #if(COM_RX_IPDU_DM == STD_ON)
      /* Local variable to store RxDm timer index*/
      PduIdType LddRxDmTimerIndex;
      /* Local variable to store count */
      uint8 LucCount;
      #endif

      /* Check whether requested I-PDU group deadline monitoring is stopped */
      if(COM_FALSE == (Com_GaaIpduGrpDmStatus[LpIpduGroup->ucGroupIndex] &
                                        (LpIpduGroup->ucStatusMask)))
      {
        /* @Trace: Com_SUD_API_00259 */
        /* Disable Ipdu Group Dm Status */
        Com_GaaIpduGrpDmStatus[LpIpduGroup->ucGroupIndex] |=
                                                    (LpIpduGroup->ucStatusMask);
        /* Get the number of Rx I-PDUs  */
        LddNoOfIpdus = LpIpduGroup->ddNoOfRxIpdus;
        LddPduIndex = (LpIpduGroup->ddRxIpduIndex + LddNoOfIpdus) - 
        (PduIdType)COM_ONE;
        /* Loop for all PDUs */
        while(LddNoOfIpdus != (PduIdType)COM_ZERO)
        {
          /* @Trace: Com_SUD_API_00260 */
          /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
          LddIpduIndex = Com_GaaRxIpduGroup[LddPduIndex];
          LpRxIpdu = &Com_GaaRxIpdu[LddIpduIndex];  
          LddRxDmTimerIndex = LpRxIpdu->ddRxIpduDmIndex;
          /* polyspace +1 RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */
          if(((Com_GaaRxIpdu[LddIpduIndex].ucRxConfig &
                  COM_RX_DM_CONFIG_MASK) != COM_FALSE) &&
           ((COM_INVALID_RXID_PARAM) != LddRxDmTimerIndex))
          {
            #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
            if(((PduIdType)(COM_RX_IPDU_DM_COUNT_MAX) > LddRxDmTimerIndex) &&
            #else
            if(((PduIdType)(COM_RX_IPDU_DM_COUNT) > LddRxDmTimerIndex) &&
            #endif
            ((PduIdType)COM_ZERO == Com_GaaRxDmStatus[LddRxDmTimerIndex]))
            {
              
              #if(COM_RX_IPDU_DM == STD_ON)
              /* @Trace: Com_SUD_API_01799 */
              LpRxDm = &Com_GaaRxDm[LddRxDmTimerIndex];
              LucCount = LpRxDm->ucRxDmCount;
              do
              {
                /* @Trace: Com_SUD_API_00262 */
                #if(COM_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
                SchM_Enter_Com_RX_DM_STS_PROTECTION_AREA();
                #endif
                Com_GaaRxDMTimer[LddRxDmTimerIndex] = LpRxDm->ulRxDmFirstTimeout;
                #if(COM_RX_INTERRUPT_BASED_PROCESS == STD_OFF)
                SchM_Exit_Com_RX_DM_STS_PROTECTION_AREA();
                #endif
                --LucCount;
                LddRxDmTimerIndex++;
                LpRxDm = &Com_GaaRxDm[LddRxDmTimerIndex];
              }while(LucCount != COM_ZERO);
              #endif
            }
            if((Com_GaaRxIpduDmBelongGroup[LddIpduIndex] > Com_GaaRxDmStatus
              [Com_GaaRxIpdu[LddIpduIndex].ddRxIpduDmIndex]) ||
              ((uint16)COM_ZERO == Com_GaaRxIpduDmBelongGroup[LddIpduIndex]))
            {
              /* @Trace: Com_SUD_API_00263 */
              Com_GaaRxDmStatus[Com_GaaRxIpdu[LddIpduIndex].ddRxIpduDmIndex]++;
            }
          }
          /* @Trace: Com_SUD_API_00264 */
          LddNoOfIpdus--;
          LddPduIndex--;
        }
      }
    }
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#else
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_EnableReceptionDM(Com_IpduGroupIdType IpduGroupId)
{
  /* @Trace: Com_SUD_API_01320 */
	COM_UNUSED(IpduGroupId);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_DisableReceptionDM                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function disables the reception deadline       **
**                        monitoring for the I-PDU(s) within the requested    **
**                        Rx I-PDU group.                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant for different I-PDU groups.               **
**                        Non-Reentrant for same I-PDU group.                 **
**                                                                            **
** Input Parameters     : IpduGroupId                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaIpduGroup           **
**                                                 Com_GaaIpduGrpDmStatus     **
**                                                 Com_GaaRxIpduGroup         **
**                                                 Com_GaaRxIpdu              **
**                                                 Com_GaaRxDmStatus          **
**                        Function(s) invoked    : SchM_Enter_xxx()           **
**                                                 SchM_Exit_xxx()            **
*******************************************************************************/
#if((COM_RX_IPDU_DM == STD_ON) || \
     (COM_RX_SIGNAL_UBDM == STD_ON) || \
     (COM_RX_SIGGROUP_UBDM == STD_ON))
#define COM_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_Com_00192*/
FUNC(void, COM_CODE) Com_DisableReceptionDM(Com_IpduGroupIdType IpduGroupId)
{
  /* @Trace: Com_SUD_API_00265 */
  #if(COM_DEV_ERROR_DETECT == STD_ON)
  uint8 LucReturnValue;
  LucReturnValue = E_OK;
  /* Check whether module is initialized */
  COM_DET_INIT_STATUS_CHECK_FLAG(COMSERVICEID_RECEPTIONDMDISABLE);
  /* Check whether I-PDU group ID is out of range */
  #if (COM_VARIANT_POSTBUILD_SUPPORT == STD_OFF)
  /* @Trace: Com_SUD_API_01321 */
  COM_DET_IPDUGROUPID_RANGE_CHECK_FLAG(COMSERVICEID_RECEPTIONDMDISABLE);
  #else
  /* @Trace: Com_SUD_API_01322 */
  COM_DET_IPDUGROUPID_RANGE_CHECK_FLAG_PB(COMSERVICEID_RECEPTIONDMDISABLE);
  #endif
  /* Get the pointer to the I-PDU group structure */
  if(LucReturnValue == (uint8)E_OK)
  #endif
  {
    /* @Trace: Com_SUD_API_00266 */
    /* Pointer to Ipdu group structure */
    P2CONST(Com_IpduGroup, AUTOMATIC, COM_CONST) LpIpduGroup;
    /* Get the pointer to the I-PDU group structure */
    LpIpduGroup = &Com_GaaIpduGroup[IpduGroupId];
    /*Check this IPDU grp is enable API Rx En/Dis ReceptionDM*/
    if(COM_TRUE == (LpIpduGroup->blRxDmEnabled))
    {
      /* @Trace: Com_SUD_API_00267 */
      /* Local variable to store Com Ipdu handle ID */
      PduIdType LddIpduIndex;
      PduIdType LddPduIndex;
      /* Local variable to store no Of Ipdus */
      PduIdType LddNoOfIpdus;
      /* Check whether its parent Ipdu Group */
      if((Com_GaaIpduGrpDmStatus[LpIpduGroup->ucGroupIndex] &
                                  (LpIpduGroup->ucStatusMask)) != COM_FALSE)
      {
        /* @Trace: Com_SUD_API_00268 */
        /* Enable Ipdu Group Status */
        Com_GaaIpduGrpDmStatus[LpIpduGroup->ucGroupIndex] &=
                                          (uint8)(~(LpIpduGroup->ucStatusMask));
        /* Get the number of Rx I-PDUs  */
        LddNoOfIpdus = LpIpduGroup->ddNoOfRxIpdus;
        LddPduIndex = (LpIpduGroup->ddRxIpduIndex + LddNoOfIpdus) 
        - (PduIdType)COM_ONE;
        /* Loop for all PDUs */
        while(LddNoOfIpdus != (PduIdType)COM_ZERO)
        {
          /* @Trace: Com_SUD_API_00269 */
          /* polyspace +1 RTE:OBAI [Not a defect:Low] "Array access index is in-bounds. This is assured by generator" */
          LddIpduIndex = Com_GaaRxIpduGroup[LddPduIndex];
          /* polyspace +1 RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */
          if((Com_GaaRxIpdu[LddIpduIndex].ucRxConfig &
                                            COM_RX_DM_CONFIG_MASK) != COM_FALSE)
          {
            if((uint16)COM_ZERO < 
              Com_GaaRxDmStatus[Com_GaaRxIpdu[LddIpduIndex].ddRxIpduDmIndex])
            {
              /* @Trace: Com_SUD_API_00270 */
              Com_GaaRxDmStatus[Com_GaaRxIpdu[LddIpduIndex].ddRxIpduDmIndex]--;
            }
          }
          /* @Trace: Com_SUD_API_00271 */
          LddNoOfIpdus--;
          LddPduIndex--;
        }
      } /* Check whether deadline monitoring is active */
    } /* @End if(COM_TRUE == (LpIpduGroup->blRxDmEnabled)) */
  }
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#else
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_DisableReceptionDM(Com_IpduGroupIdType IpduGroupId)
{
  /* @Trace: Com_SUD_API_01323 */
  COM_UNUSED(IpduGroupId);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif
#endif /*#if (((COM_VARIANT_POSTBUILD_SUPPORT == STD_ON) && ((COM_TX_IPDU_GROUP_COUNT_MAX>0) || (COM_RX_IPDU_GROUP_COUNT_MAX >0))) || \
((COM_TX_IPDU_GROUP_COUNT>0) || (COM_RX_IPDU_GROUP_COUNT >0)))*/
/*******************************************************************************
** Function Name        : Com_TxCounterUpdate                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function added for cyclomatic complexity reduction. **
**                        Updates counter value in the I-PDU buffer           **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : NA                                                  **
**                                                                            **
** Input Parameters     : LpTxIpduCounter                                     **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Com_GaaTxPack                 **
**                                              Com_GaaTxIpduCountVal         **
**                        Function(s) invoked : SchM_Enter_xxx()              **
**                                              SchM_Exit_xxx()               **
**                                              pWrFuncPtr                    **
*******************************************************************************/
#if(COM_TX_IPDU_COUNTER_ENABLED == STD_ON) 
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_TxCounterUpdate
   (P2CONST(Com_TxIpduCounter, AUTOMATIC, COM_CONST) LpTxIpduCounter)
{
  /* @Trace: Com_SUD_API_00272 */
  P2CONST(Com_TxPack, AUTOMATIC, COM_CONST) LpTxPack;
  uint8 LucTxIpduCntVal;
  /* Get the pointer to TxPack structure */
  LpTxPack = &Com_GaaTxPack[LpTxIpduCounter->ddTxPackIndex];
  /* Get the present counter data */
  LucTxIpduCntVal = 
    Com_GaaTxIpduCountVal[LpTxIpduCounter->ucTxIpduCountData];
  /* Increment I-PDU count value */
  LucTxIpduCntVal++;
  /* Apply wrap around mask to the counter data */
  LucTxIpduCntVal &= LpTxIpduCounter->ucTxIpduCntWrpMask;
  #if(COM_SIG_WR_FUNC_COUNT > COM_MACRO_ZERO)
  /* Invoke write function to pack counter data to I-PDU buffer */
  (void)Com_PackRequestWrite(LpTxPack,
  (P2CONST(void, AUTOMATIC, COM_CONST)) &LucTxIpduCntVal);
  #endif
  /* Enter protection area */
  SchM_Enter_Com_IPDU_COUNTER_PROTECTION();
  /* Load present counter data in buffer */
  Com_GaaTxIpduCountVal[LpTxIpduCounter->ucTxIpduCountData] = 
  LucTxIpduCntVal;
  /* Exit Critical Area */
  SchM_Exit_Com_IPDU_COUNTER_PROTECTION();
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_ReadReceiveIpduList                             **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Get ComRxPduId form ring buffer. This function will **
**                          return E_NOT_OK when don't have any unread data   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : ComRxPduId: Com_SignalIdType*                       **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaReceiveIpduList     **
**                                                 Com_GaaReceiveIpduValue    **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(Std_ReturnType, COM_CODE) Com_ReadReceiveIpduList(
                                                   PduIdType* ComRxPduId)
{
  /* @Trace: Com_SUD_API_00273 */
  Std_ReturnType lddReturnVal;
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  CoreIdType CoreId;
  #endif /* STD_ON == COM_MULTI_CORE_SUPPORT */
  uint16 lusReadIndex; 
  uint16 lusCount; 
  uint16 lusSize;   

  P2VAR(Com_ReceiveIpduListType, AUTOMATIC, COM_VAR) lpReceiveIpduList;

  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  /* @Trace: Com_SUD_API_01400 */
  lddReturnVal = E_NOT_OK;
  CoreId = GetCoreID();
  /* check core id vaild*/
  if(CoreId <= COM_MULTI_CORE_MAX) 
  {
    if(NULL_PTR != Com_GaaReceiveIpduList[CoreId].ptr)
    {
      /* @Trace: Com_SUD_API_00274 */
      /* Get address of buffer */
      lpReceiveIpduList = Com_GaaReceiveIpduList[CoreId].ptr;
      lddReturnVal = E_OK; 
    }    
  }

  if(E_OK==lddReturnVal)
  #else
  /* @Trace: Com_SUD_API_01324 */ 
  /* If multi core isn't support, only a buffer is generated */
  lpReceiveIpduList = &Com_GaaReceiveIpduValue[COM_ZERO];       
  #endif /* STD_ON == COM_MULTI_CORE_SUPPORT */
  {
    /* @Trace: Com_SUD_API_00275 */
    /* check number of unread cell  */ 
    SchM_Enter_Com_RX_IPDU_STS_PROTECTION_AREA();
    lusCount = lpReceiveIpduList->usCount;
    /* size of buffer  */ 
    if((uint16)COM_ZERO < lusCount)
    {
      /* @Trace: Com_SUD_API_00276 */
      lusSize = lpReceiveIpduList->usSize;
      if(((uint16)COM_ONE) <= lusSize)
      {
        /* @Trace: Com_SUD_API_00277 */
        /*read data form ring buffer*/
        lusReadIndex = lpReceiveIpduList->usReadIndex;
        /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is inside its bound. This is assured by generator" */
        *ComRxPduId = (PduIdType)(lpReceiveIpduList->pList[lusReadIndex]);
        /* inc pointer to next cell */
        if((lusSize - (uint16)COM_ONE) <= lusReadIndex)
        {
          /* @Trace: Com_SUD_API_00278 */
          /* reset pointer to start */
          lusReadIndex = (uint16)COM_ZERO;
        }
        else
        {
          /* @Trace: Com_SUD_API_00279 */
          lusReadIndex++;
        }
        /* @Trace: Com_SUD_API_00280 */
        /* backup value */
        lpReceiveIpduList->usReadIndex = lusReadIndex;
        /* update number of unread cell */
        lusCount--;
      }
      else
      {
        /* @Trace: Com_SUD_API_00281 */
        /* if only a IpduR is config, read data form Com_GaaRxIpdu */
        *ComRxPduId = (uint16)COM_ZERO;
        /* update number of unread cell */
        lusCount = (uint16)COM_ZERO;
      }
      /* @Trace: Com_SUD_API_00282 */
      /* backup value */
      lpReceiveIpduList->usCount = lusCount;
      /* set return ok */
      lddReturnVal = E_OK;
    }
    else
    {
      /* @Trace: Com_SUD_API_00283 */
      /* Don't have any unread data */
      lddReturnVal = E_NOT_OK;
    }
    SchM_Exit_Com_RX_IPDU_STS_PROTECTION_AREA();
  }
  /* @Trace: Com_SUD_API_00284 */
  /* Return value */
  return lddReturnVal;
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_WriteReceiveIpduList                            **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Put ComRxPduId to ring buffer. When ring buffer is  **
**                          full, oldest data will overwrite                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ComRxPduId                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaReceiveIpduList     **
**                                                 Com_GaaReceiveIpduValue    **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_WriteReceiveIpduList(PduIdType ComRxPduId)
{
  /* @Trace: Com_SUD_API_00285 */
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  Std_ReturnType lddReturnVal;
  CoreIdType CoreId;
  #endif /* STD_ON == COM_MULTI_CORE_SUPPORT */
  uint16 lusReadIndex; 
  uint16 lusWriteIndex; 
  uint16 lusCount; 
  uint16 lusSize;   

  P2VAR(Com_ReceiveIpduListType, AUTOMATIC, COM_VAR) lpReceiveIpduList;

  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  /* @Trace: Com_SUD_API_01401 */
  lddReturnVal = E_NOT_OK;
  CoreId = GetCoreID();
  /* check core id vaild*/
  if(CoreId <= COM_MULTI_CORE_MAX) 
  {
    if(NULL_PTR != Com_GaaReceiveIpduList[CoreId].ptr)
    {
      /* @Trace: Com_SUD_API_00286 */
      /* Get address of buffer */
      lpReceiveIpduList = Com_GaaReceiveIpduList[CoreId].ptr;
      lddReturnVal = E_OK; 
    }    
  }

  if(E_OK==lddReturnVal)    
  #else
  /* @Trace: Com_SUD_API_01325 */ 
  /* If multi core isn't support, only a buffer is generated */
  lpReceiveIpduList = &Com_GaaReceiveIpduValue[COM_ZERO];       
  #endif /* STD_ON == COM_MULTI_CORE_SUPPORT */
  {
    /* @Trace: Com_SUD_API_00287 */
    /* check number of unread cell  */ 
    SchM_Enter_Com_RX_IPDU_STS_PROTECTION_AREA();
    lusSize = lpReceiveIpduList->usSize;
    lusCount = lpReceiveIpduList->usCount;
    /* size of buffer  */ 
    if(((uint16)COM_ONE) <= lusSize)
    {
      /* @Trace: Com_SUD_API_00288 */
      /*write data form ring buffer*/
      lusWriteIndex = lpReceiveIpduList->usWriteIndex;
      /* polyspace +1 RTE:IDP [Not a defect:Low] "Pointer is not null. This is assured by generator" */
      lpReceiveIpduList->pList[lusWriteIndex] = (PduIdType)ComRxPduId;
      /* inc pointer to next cell */
      if((lusSize - (uint16)COM_ONE) <= lusWriteIndex)
      {
        /* @Trace: Com_SUD_API_00289 */
        /* reset pointer to start */
        lusWriteIndex = (uint16)COM_ZERO;
      }
      else
      {
        /* @Trace: Com_SUD_API_00290 */
        lusWriteIndex++;
      }
      /* @Trace: Com_SUD_API_00291 */
      lpReceiveIpduList->usWriteIndex = lusWriteIndex;
      /* check if buffer is full */
      if(lusSize <= lusCount)
      { 
        /* @Trace: Com_SUD_API_00292 */
        lusReadIndex = lpReceiveIpduList->usReadIndex;
        /* Remove a unread data */
        if((lusSize + (uint16)COM_ONE) <= lusReadIndex)
        {
          /* @Trace: Com_SUD_API_00293 */
          /* reset pointer to start */
          lusReadIndex = (uint16)COM_ZERO;
        }
        else
        {
          /* @Trace: Com_SUD_API_00294 */
          lusReadIndex++;
        }
        /* @Trace: Com_SUD_API_00295 */
        /* backup value */
        lpReceiveIpduList->usReadIndex = lusReadIndex;
      }
      else
      {  
        /* @Trace: Com_SUD_API_00296 */
        /* update number of unread cell */
        lusCount++;
      }  
    }
    else
    {
      /* @Trace: Com_SUD_API_00297 */
      /* if only a IpduR is config, don't need to store data */
    	lpReceiveIpduList->usCount = (uint16)COM_ONE;
    }
    /* @Trace: Com_SUD_API_00298 */
    /* backup value */
    lpReceiveIpduList->usCount = lusCount;
    SchM_Exit_Com_RX_IPDU_STS_PROTECTION_AREA();
  }
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_ResetReceiveIpduList                            **
**                                                                            **
** Service ID           : None                                                **
**                                                                            **
** Description          : Return number of unread data                        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : ComRxPduId                                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : uint16                                              **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)     : Com_GaaReceiveIpduList     **
**                                                 Com_GaaReceiveIpduValue    **
**                        Function(s) invoked    : None                       **
*******************************************************************************/

#define COM_START_SEC_CODE
#include "MemMap.h"

FUNC(void, COM_CODE) Com_ResetReceiveIpduList(void)
{
  /* @Trace: Com_SUD_API_00299 */
  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  Std_ReturnType lddReturnVal;
  CoreIdType CoreId;
  #endif /* STD_ON == COM_MULTI_CORE_SUPPORT */

  P2VAR(Com_ReceiveIpduListType, AUTOMATIC, COM_VAR) lpReceiveIpduList;

  #if (STD_ON == COM_MULTI_CORE_SUPPORT)
  /* @Trace: Com_SUD_API_01402 */
  lddReturnVal = E_NOT_OK;
  CoreId = GetCoreID();
  /* check core id vaild*/
  if(CoreId <= COM_MULTI_CORE_MAX) 
  {
    if(NULL_PTR != Com_GaaReceiveIpduList[CoreId].ptr)
    {
      /* @Trace: Com_SUD_API_00300 */
      /* Get address of buffer */
      lpReceiveIpduList = Com_GaaReceiveIpduList[CoreId].ptr;
      lddReturnVal = E_OK; 
    }    
  }

  if(E_OK==lddReturnVal)    
  #else
  /* @Trace: Com_SUD_API_01326 */  
  /* If multi core isn't support, only a buffer is generated */
  lpReceiveIpduList = &Com_GaaReceiveIpduValue[COM_ZERO];       
  #endif /* STD_ON == COM_MULTI_CORE_SUPPORT */
  {
    /* @Trace: Com_SUD_API_00301 */
    /* check number of unread cell  */ 
	SchM_Enter_Com_RX_IPDU_STS_PROTECTION_AREA();
    lpReceiveIpduList->usWriteIndex = (uint16)COM_ZERO;
    lpReceiveIpduList->usReadIndex = (uint16)COM_ZERO;
    lpReceiveIpduList->usCount = (uint16)COM_ZERO;
	SchM_Exit_Com_RX_IPDU_STS_PROTECTION_AREA();
  }
}

#define COM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : Com_IpduFilterStatusUpdate                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function update global data prepare for        **
**                        Tx IPDU TMS filter status                           **
**                                                                            **
** Sync/Async           : NA                                                  **
**                                                                            **
** Re-entrancy          : Cyclic                                              **
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
** Remarks              : Global Variable(s)     :   Com_GaaTxDMTimer         **
**                                                   Com_GaaTxIpduDm          **
**                                                   Com_GaaTxMDTimer         **
**                                                   Com_GaaTxIpduStatusBit   **
**                        Function(s) invoked    :   SchM_Enter_Com()         **
**                                                   SchM_Exit_Com()          **
*******************************************************************************/
#if(COM_TX_IPDU_TMS_SIG_BASED == STD_ON)
#define COM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COM_CODE) Com_IpduFilterStatusUpdate(
  P2CONST(Com_TxIpduModeSel, AUTOMATIC, COM_CONST) LpTxModeSelect,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpFilterStatus,
  P2VAR(boolean, AUTOMATIC, COM_VAR) LpFilterResult,
  P2VAR(uint8, AUTOMATIC, COM_VAR) LucFilterStatusIndex)   
{
  /* @Trace: Com_SUD_API_00302 */
  uint8 LucFilterStsCount;
  P2VAR(uint8, AUTOMATIC, COM_VAR) LpFilterStatusLocal;

  LpFilterStatusLocal = LpFilterStatus;

  /* Get the counter */
  LucFilterStsCount = LpTxModeSelect->ucFilterStatusCount;
  /* Loop for all the signals configured for filtering */
  do
  {
    /* @Trace: Com_SUD_API_00303 */
    /* Decrement the filter status count */
    LucFilterStsCount--;
    /* Check whether filter status is set to true */
    if(*LpFilterStatusLocal != COM_ZERO)
    {
      /* @Trace: Com_SUD_API_00304 */
      /* Set filter status count to zero to break the loop */
      LucFilterStsCount = COM_ZERO;
      /* Set the return value to true */
      *LpFilterResult = COM_TRUE;

    } /* if(*LpFilterStatus != COM_ZERO) */

    /* @Trace: Com_SUD_API_00305 */  
    /* Increment the filter status pointer to point to n
        filter status area */
    (*LucFilterStatusIndex)++;
    LpFilterStatusLocal =
        &Com_GaaFilterStatus[(*LucFilterStatusIndex)];         
  }while(LucFilterStsCount != COM_ZERO);
}
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
** Function Name        : Com_TxBuffersReInit                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This subfunction for startTx IPDUs                  **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     :                                                     **
**                                                                            **
** InOut parameter      :                                                     **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Com_GaaIpduGroup              **
*******************************************************************************/
#if (((COM_VARIANT_POSTBUILD_SUPPORT == STD_ON) &&\
  ((COM_TX_IPDU_GROUP_COUNT_MAX>0) || (COM_RX_IPDU_GROUP_COUNT_MAX >0))) || \
  ((COM_TX_IPDU_GROUP_COUNT>0) || (COM_RX_IPDU_GROUP_COUNT >0)))
#define COM_START_SEC_CODE
#include "MemMap.h"
#if(COM_TX_IPDU == STD_ON)
FUNC(void, COM_CODE) Com_TxBuffersReInit(PduIdType LddIpduHandleId)
{
  /* @Trace: Com_SUD_API_01829 */
  #if((COM_TX_SIGGROUP == STD_ON) || \
    ((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) && (COM_TX_SIGNAL == STD_ON)))
  /* Local Index */
  uint16 lucIdx;
  #endif
  
  #if(COM_TX_IPDU_TMS_SIG_BASED == STD_ON)
  #if(COM_TX_SIGNAL == STD_ON)
  /* Pointer to Tx Signal Array */
  P2CONST(Com_TxSignal, AUTOMATIC, COM_CONST) pTxSig;
  #endif

  #if(COM_TX_SIGGROUP == STD_ON) 
  /* Pointer to Tx Signal Group Array */
  P2CONST(Com_TxSigInGrp, AUTOMATIC, COM_CONST) pTxSigGrp;
  #endif
  #endif

  #if(COM_TX_IPDU_TMS_SIG_BASED == STD_ON)
  #if((COM_TX_SIGGROUP == STD_ON) || (COM_TX_SIGNAL == STD_ON))
  PduLengthType LddNoOfByte;
  uint8 LucSizeOrData;
  #endif
  #endif

	#if((COM_TX_IPDU_TMS_SIG_BASED == STD_ON) ||\
	 (COM_TX_IPDU_TMS_EXPLICIT == STD_ON) || (COM_TX_IPDU_PT == STD_ON) ||\
	 (COM_TX_IPDU_DM == STD_ON) || (COM_TX_TP_SUPPORT == STD_ON) ||\
	 (COM_TX_IPDU_REPETITION == STD_ON) ||\
	 (COM_TX_IPDU_COUNTER_ENABLED == STD_ON) ||\
	 (COM_TX_SIGNAL_UB == STD_ON) || (COM_TX_SIGGROUP_UB == STD_ON) ||\
	 (COM_TX_IPDU_MINDELAY_ENABLED == STD_ON))

	/* @Trace: Com_SUD_API_01801 */
	/* Initialize Data of the I-PDU */
	/* polyspace +1 RTE:STD_LIB [Not a defect:Low] "All pointers are available and in range. This is assured by generator" */
	memcpy((void *)Com_GaaTxPduInfoPtr[LddIpduHandleId].SduDataPtr, \
	  (const void *)(Com_GaaTxIpdu[LddIpduHandleId].pReInitBuffer), 
	  (uint16)Com_GaaTxPduInfoPtr[LddIpduHandleId].SduLength);
	#endif

	/* Initialize shadow buffer of included signal groups */
	#if(COM_TX_SIGGROUP == STD_ON)
	#if(COM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
	if (Com_GlNoOfTxSigGrp > (uint16)COM_MACRO_ZERO)
	#endif
	{
	  #if(COM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
	  /* @Trace: Com_SUD_API_01802 */
	  /* @Trace: Com_SUD_API_01803 */
	  for (lucIdx = 0 ; lucIdx < Com_GlNoOfTxSigGrp; lucIdx++)        
	  #else
	  for (lucIdx = 0 ; lucIdx < COM_TX_SIGGROUP_COUNT; lucIdx++)
	  #endif
	  {
		if(
		  #if(COM_TX_SIGGROUP_ARRAY_ACCESS == STD_ON)
		  (Com_GaaTxSigGroup[lucIdx].blArrayAccess == COM_FALSE) && 
		  #endif
		  (Com_GaaTxSigGroup[lucIdx].ddTxIpduIndex == LddIpduHandleId)
		)
		{   
		  /* @Trace: Com_SUD_API_01804 */
		  /* For Signal Group, The Total Length of Group is ddSigTypeOrSize element*/
		  /* polyspace +1 RTE:STD_LIB [Not a defect:Low] "All pointers are available and in range. This is assured by generator" */
		  memcpy(Com_GaaTxSigGroup[lucIdx].pShadowBuffer, 
			Com_GaaTxSigGroup[lucIdx].pReInitBuffer,
			Com_GaaTxPack[Com_GaaTxSigGroup[lucIdx].ddTxSigGrpPackIndex].
			  ddSigTypeOrSize);
		}
	  }
	}
	#endif

	/* Intialize old_value of filter mechanisms for each signal */
	#if(COM_TX_IPDU_TMS_SIG_BASED == STD_ON)
	#if(COM_TX_SIGNAL == STD_ON)
	/* For Signal */
	#if(COM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
	/* @Trace: Com_SUD_API_01805 */
	/* @Trace: Com_SUD_API_01806 */
	for (lucIdx = 0; 
	  lucIdx < Com_GlNoOfTxSignal - Com_GlNoOfTxSigInGrp; 
	  lucIdx++)
	#else
	for (lucIdx = 0 ; lucIdx < COM_TX_SIGNAL_COUNT; lucIdx++)
	#endif
	{
	  /* @Trace: Com_SUD_API_01807 */
	  /* Initialize pointer pTxSig */
	  pTxSig = &Com_GaaTxSignal[lucIdx];
	  /* polyspace +1 RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */
	  if (pTxSig->ddTxPackIndex != COM_INVALID_PACK_INDEX_PARAM)
	  {
		/* @Trace: Com_SUD_API_01808 */
		LddNoOfByte = 
		  (uint8)(Com_GaaTxPack[pTxSig->ddTxPackIndex].ddSigTypeOrSize);
		/* polyspace-begin RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */ 
		/* Initialize old value only apply for Signal has filter type is MASKED_NEW_DIFFERS_MASKED_OLD */ 
		if((pTxSig->pFilter != NULL_PTR) &&\
		  (pTxSig->blfilterMasked == COM_TRUE) &&\
		  (pTxSig->ddTxIpduIndex == LddIpduHandleId))
		{
		/* polyspace-end RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */ 
		  /* @Trace: Com_SUD_API_01809 */
		  LucSizeOrData = 
			((uint8)(LddNoOfByte & COM_SIG_SIZE_MASK_VALUE) >> COM_FOUR);
		  memcpy(
			((P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST))
			  (pTxSig->pFilter))->pSignalBuffer,
			((P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST))
			  (pTxSig->pFilter))->pReInitBuffer,
			((uint8)LucSizeOrData));
		}
	  }
	}
	#endif
	#endif

	/* For Signal Group */
	#if(COM_TX_IPDU_TMS_SIG_BASED == STD_ON)
	#if(COM_TX_SIGGROUP == STD_ON)
	#if(COM_VARIANT_POSTBUILD_SUPPORT == STD_ON)
	/* @Trace: Com_SUD_API_01810 */
	/* @Trace: Com_SUD_API_01811 */
	for (lucIdx = 0 ; lucIdx < Com_GlNoOfTxSigInGrp; lucIdx++)        
	#else
	for (lucIdx = 0 ; lucIdx < COM_TX_SIGINGROUP_COUNT; lucIdx++)
	#endif
	{
	  /* @Trace: Com_SUD_API_01812 */
	  /* Initialize pointer pTxSigGrp */
	  pTxSigGrp = &Com_GaaTxSigInGrp[lucIdx];
	  if (pTxSigGrp->ddTxPackIndex != COM_INVALID_PACK_INDEX_PARAM)
	  {
		/* polyspace-begin RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */ 
		/* Initialize old value only apply for Signal has filter type is MASKED_NEW_DIFFERS_MASKED_OLD */ 
		#if(COM_TX_SIGINGRP_FILTER_SUPPORT == STD_ON)
		/* @Trace: Com_SUD_API_01813 */
		LddNoOfByte = 
		  (uint8)(Com_GaaTxPack[pTxSigGrp->ddTxPackIndex].ddSigTypeOrSize);
		if((pTxSigGrp->blfilterMasked == COM_TRUE) &&\
		  (pTxSigGrp->pFilter != NULL_PTR) &&\
		  (Com_GaaTxSigGroup[pTxSigGrp->ddSigGrpIndex].ddTxIpduIndex == 
			LddIpduHandleId))
		{
		/* polyspace-end RTE:UNR [Not a defect:Low] "The section is reachable in another configuration" */ 
		  /* When SignalGroup doesn't use signal array access, the group singal will be available in Com_GaaTxPack
		  otherwise, if SignalGroup uses Arrayaccess, and the group signal with filter differ NULL_PTR will be 
		  available in Com_GaaRxUnpack*/ 

		  #if(COM_TX_SIGGROUP_ARRAY_ACCESS == STD_ON)
		  if(Com_GaaTxSigGroup[pTxSigGrp->ddSigGrpIndex].blArrayAccess ==
			 COM_FALSE)
		  #endif
		  {
			/* @Trace: Com_SUD_API_01814 */
			LucSizeOrData = 
			  ((uint8)(LddNoOfByte & COM_SIG_SIZE_MASK_VALUE) >> COM_FOUR);
			memcpy(
			  ((P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST))
				(pTxSigGrp->pFilter))->pSignalBuffer,
			  ((P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST))
				(pTxSigGrp->pFilter))->pReInitBuffer,
			  ((uint8)LucSizeOrData));
		  }
		  #if((COM_TX_SIGGROUP_ARRAY_ACCESS == STD_ON) &&\
			(COM_TX_SIGGROUP_ARRAY_TMS == STD_ON))
		  else
		  {
			/* @Trace: Com_SUD_API_01830 */
			  memcpy(
				((P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST))
				  (pTxSigGrp->pFilter))->pSignalBuffer,
				((P2CONST(Com_FilterMaskedNew, AUTOMATIC, COM_CONST))
				  (pTxSigGrp->pFilter))->pReInitBuffer,
				(Com_GaaRxUnpack[pTxSigGrp->ddTxUnpackIndex].ddSignalSize)); 
		  }
		  #endif                                                        
		}
		#endif
	  }
	}
	#endif
	#endif
}
#endif
#define COM_STOP_SEC_CODE
#include "MemMap.h"
#endif

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
