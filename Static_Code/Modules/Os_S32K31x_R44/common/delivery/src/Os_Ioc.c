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
**  SRC-MODULE: Os_Ioc.c                                                      **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR OS                                                    **
**                                                                            **
**  PURPOSE   : Provision of Ioc functionality.                               **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/* @Trace: SRS_BSW_00003 SRS_BSW_00006 SRS_BSW_00007 SRS_BSW_00009 SRS_BSW_00301 SRS_BSW_00302 SRS_BSW_00305
 SRS_BSW_00415 SRS_BSW_00305 SRS_BSW_00307 SRS_BSW_00308 SRS_BSW_00310 SRS_BSW_00328 SRS_BSW_00441 */
/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 1.5.3     16-Feb-2024   HG.Kim           Jira CP44-3828                    **
** 1.5.1     06-Oct-2023   JC.Kim           Jira CP44-2438                    **
** 1.5.0     26-Apr-2023   SH.Yoo           Jira CP44-2097                    **
**                                          Jira CP44-2028                    **
** 1.3.9.1   23-Jun-2022   KhanhPQ8         Jira CP44-287                     **
** 1.3.4     07-Jan-2022   TinHV1           R44-Redmine #23444/#23536         **
** 1.3.3     23-Dec-2021   DatNXT           R44-Redmine #22670                **
** 1.3.0     20-Aug-2021   DatNXT           R44-Redmine #18022                **
** 1.0.6.0   23-Mar-2021   Thao             Redmine #18032                    **
** 1.0.3     25-Aug-2020   TamNN1           R44-Redmine #12870                **
**                                          Fixed Misra-C 12.1                **
** 1.0.2     14-Aug-2020   Thao             R44-Redmine #13463                **
**                                          Add SRS Traceability              **
** 1.0.1     31-Jul-2020   DanhDC1          R44-Redmine #14813                **
**                                          Check the called IOC API before   **
**                                          Staring Os                        **
** 1.0.0     15-Dec-2019   Paul             R44-Redmine #1505 Initial version **
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA-C RULE CHECKER)                **
*******************************************************************************/
/* polyspace-begin MISRA-C3:21.15 [Not a defect:No action planned] "This is Standard Library" */
/* polyspace:begin<RTE:IDP:Not a defect:No action planned> It is defined from statically defined value */
/* polyspace-begin MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-begin MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
/* polyspace-begin MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
/* polyspace-begin MISRA-C3:11.4 [Not a defect:Justify with annotations] "Conversion is needed for implementation" */
/* polyspace:begin<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Os.h"
#include "Os_Ram.h"
#include "Os_Multicore.h"
#include "Os_Error.h"
/* @Trace: SRS_BSW_00410 */
#if (OS_MULTICORE == STD_ON)
#include "Os_MulticoreMessage.h"
#endif
#include "Os_IocInternalTypes.h"
#include "Os_Ioc.h"
#include "Os_SystemCallTable.h"

/*******************************************************************************
**                      Version Information                                   **
*******************************************************************************/

/*******************************************************************************
**                      Version Check                                         **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* @Trace: SRS_BSW_00351 */
#define OS_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#if (OS_APPLICATION == STD_ON)
/*******************************************************************************
** Function Name        : Os_KernIocRead                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function read data through IOC                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : IocID                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : data                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GaaIocUnqueuedCfg, Os_Ioc_Count_Unqueued         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_GetSpinlock(), Os_ReleaseSpinlock(),             **
**                        Os_MemCopy()                                        **
*******************************************************************************/
/* @Trace: SRS_Os_80006 SRS_Os_80020 */
/* polyspace +2 MISRA-C3:8.13 [Justified:Low] "Kernel entry internal function, Ioc buffer has been checked previously" */
FUNC(Std_ReturnType, OS_CODE) Os_KernIocRead(uint32 IocID,
                                      P2VAR(uint32, AUTOMATIC, OS_VAR) data[])
{
  StatusType LddStatusReturn;
  P2CONST(Os_IocUnqueuedCfgType, AUTOMATIC, OS_CONST) LpCfg;
  P2CONST(Os_IocBufType, AUTOMATIC, OS_CONST) LpBuf;
  uint32 LulDataCount;

  LddStatusReturn = IOC_E_OK;
  LulDataCount = OS_ZERO;
  /* @Trace: SafeOs_SUD_API_19701 */
  /* Check whether Os has started or not */
  OS_CHECK_IOC_NOT_STARTOS(&LddStatusReturn);
  /* check IOC ID */
  /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "IocID have been checked before using" */
  /* polyspace<RTE:UNR:Not a defect:No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
  OS_CHECK_IOC_ID_ERROR(IocID, Os_Ioc_Count_Unqueued, LddStatusReturn);
  /* check null pointer */
  /* polyspace<RTE:UNR:Not a defect : No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
  OS_CHECK_IOC_INVALID_UNQUEUED_BUF_ERROR(data, IocID, LulDataCount, LddStatusReturn);
  /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "IocID have been checked before using" */

  /* polyspace-begin MISRA-C3:14.3,2.1 DEFECT:DEAD_CODE [Not a defect:Low] "Verified manually with no impacts due to error check characteristic of user configuration" */
  if(LddStatusReturn == IOC_E_OK)
  {
    #if (OS_MULTICORE == STD_ON)
    /* @Trace: SafeOs_SUD_API_19702 */
    Os_GetSpinlock(OS_IOCLOCKBASE_UNQUEUED+IocID);
    #endif
    /* @Trace: SafeOs_SUD_API_19703 */
    /* read IOC data */
    LpCfg = &Os_GaaIocUnqueuedCfg[IocID];
    for(LulDataCount = OS_ZERO; LulDataCount < LpCfg->ulDataCount;
                                                                 LulDataCount++)
    {
      /* @Trace: SafeOs_SUD_API_19704 */
      LpBuf = &(LpCfg->pBuffer[LulDataCount]);
      /* polyspace:begin<MISRA-C:10.1:Not a defect:Justify with annotations> It is used for consistency */
      /* polyspace:begin<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
      /* polyspace +4 MISRA-C3:D4.11 [Justified:Low] "function is called with a valid arguments that are confirmed by testing" */
      /* polyspace +3 MISRA-C3:11.8 [Justified:Low] "Constant is not removed in this code" */
      /* polyspace<RTE: STD_LIB : Not a defect : No Action Planned > function is called with a valid arguments that are confirmed by testing */
      /* polyspace<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually */
      Os_MemCopy((void*)(data[LulDataCount]), (void*)(LpBuf->pIocBuf),
                                                  (Os_Size_T)LpBuf->ulDataSize);
      /* polyspace:end<MISRA-C:10.1:Not a defect:Justify with annotations>  It is used for consistency */
      /* polyspace:end<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
    }
    #if (OS_MULTICORE == STD_ON)
    /* @Trace: SafeOs_SUD_API_19705*/
    Os_ReleaseSpinlock(OS_IOCLOCKBASE_UNQUEUED+IocID);
    #endif
  }
  /* polyspace-end MISRA-C3:14.3,2.1 DEFECT:DEAD_CODE [Not a defect:Low] "Verified manually with no impacts due to error check characteristic of user configuration" */
  /* @Trace: SafeOs_SUD_API_19706 */
  return LddStatusReturn;
}

/*******************************************************************************
** Function Name        : Os_KernIocWrite                                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function read data through IOC                 **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : IocID, data                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GaaIocUnqueuedCfg, Os_Ioc_Count_Unqueued         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_GetSpinlock(), Os_ReleaseSpinlock(),             **
**                        Os_MemCopy()                                        **
*******************************************************************************/
/* @Trace: SRS_Os_80006 SRS_Os_80020 */
FUNC(Std_ReturnType, OS_CODE) Os_KernIocWrite(uint32 IocID,
                                 CONSTP2CONST(uint32, AUTOMATIC, OS_CONST) data[])
{
  StatusType LddStatusReturn;
  P2CONST(Os_IocUnqueuedCfgType, AUTOMATIC, OS_CONST) LpCfg;
  P2CONST(Os_IocBufType, AUTOMATIC, OS_CONST) LpBuf;
  uint32 LulDataCount;

  LddStatusReturn = IOC_E_OK;
  LulDataCount = OS_ZERO;
  /* @Trace: SafeOs_SUD_API_19601 */
  /* Check whether Os has started or not */
  OS_CHECK_IOC_NOT_STARTOS(&LddStatusReturn);
  /* check IOC ID */
  /* polyspace<RTE:UNR:Not a defect:No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
  OS_CHECK_IOC_ID_ERROR(IocID, Os_Ioc_Count_Unqueued, LddStatusReturn);

  /* check null pointer */
  /* polyspace +3 MISRA-C3:D4.14 [Justified:Low] "IocID have been checked before using" */
  /* polyspace<RTE:UNR:Not a defect:No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
  OS_CHECK_IOC_INVALID_UNQUEUED_BUF_ERROR(data, IocID, LulDataCount, LddStatusReturn);

  /* polyspace:begin<RTE:UNR:Not a defect:No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
  /* polyspace-begin MISRA-C3:14.3,2.1 DEFECT:DEAD_CODE [Not a defect:Low] "Verified manually with no impacts due to error check characteristic of user configuration" */
  if(LddStatusReturn == IOC_E_OK)
  {
    #if (OS_MULTICORE == STD_ON)
     /* @Trace: SafeOs_SUD_API_19602 */
    Os_GetSpinlock(OS_IOCLOCKBASE_UNQUEUED+IocID);
    #endif
    /* read IOC data */
    /* @Trace: SafeOs_SUD_API_19603 */
    LpCfg = &Os_GaaIocUnqueuedCfg[IocID];
    for(LulDataCount = OS_ZERO; LulDataCount < LpCfg->ulDataCount;
                                                                 LulDataCount++)
    {
      /* @Trace: SafeOs_SUD_API_19604 */
      LpBuf = &(LpCfg->pBuffer[LulDataCount]);
      /* polyspace:begin<MISRA-C:10.1:Not a defect:Justify with annotations> It is used for consistency */
      /* polyspace:begin<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
      /* polyspace +3 MISRA-C3:D4.11 [Justified:Low] "function is called with a valid arguments that are confirmed by testing" */
      /* polyspace<RTE: STD_LIB : Not a defect : No Action Planned > function is called with a valid arguments that are confirmed by testing */
      /* polyspace<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually */
      Os_MemCopy((void*)(LpBuf->pIocBuf), data[LulDataCount],
                                             (Os_Size_T)LpBuf->ulDataSize);
      /* polyspace:end<MISRA-C:10.1:Not a defect:Justify with annotations>  It is used for consistency */
      /* polyspace:end<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
    }
    #if (OS_MULTICORE == STD_ON)
    /* @Trace: SafeOs_SUD_API_19605 */
    Os_ReleaseSpinlock(OS_IOCLOCKBASE_UNQUEUED+IocID);
    #endif
  }
  /* polyspace-end MISRA-C3:14.3,2.1 DEFECT:DEAD_CODE [Not a defect:Low] "Verified manually with no impacts due to error check characteristic of user configuration" */
  /* polyspace:end<RTE:UNR:Not a defect:No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
  /* @Trace: SafeOs_SUD_API_19606 */
  return LddStatusReturn;
}

/*******************************************************************************
** Function Name        : Os_KernIocReceive                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function receive data through IOC              **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : IocID                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : data                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GaaIocQueuedCfg, Os_Ioc_Count_Queued             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_GetSpinlock(), Os_ReleaseSpinlock(),             **
**                        Os_MemCopy()                                        **
*******************************************************************************/
/* @Trace: SRS_Os_80006 SRS_Os_80020 */
/* polyspace +2 MISRA-C3:8.13 [Justified:Low] "Kernel entry internal function, Ioc buffer has been checked previously" */
FUNC(Std_ReturnType, OS_CODE) Os_KernIocReceive(uint32 IocID,
                                      P2VAR(uint32, AUTOMATIC, OS_VAR) data[])
{
  StatusType LddStatusReturn;
  P2VAR(Os_IocQueuedCfgType, AUTOMATIC, OS_VAR) LpCfg;
  P2CONST(Os_IocBufType, AUTOMATIC, OS_CONST) LpBuf;
  uint32 LulDataCount;
  uint32 LulStartIdx;
  uint32 LulIocBuf;

  LddStatusReturn = IOC_E_OK;
  LulDataCount = OS_ZERO;
  /* @Trace: SafeOs_SUD_API_19901*/
  /* Check whether Os has started or not */
  OS_CHECK_IOC_NOT_STARTOS(&LddStatusReturn);
  /* check IOC ID */
  /* polyspace<RTE:UNR:Not a defect : No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
  OS_CHECK_IOC_ID_ERROR(IocID, Os_Ioc_Count_Queued, LddStatusReturn);
  /* polyspace +3 MISRA-C3:D4.14 [Justified:Low] "IocID have been checked before using" */
  /* check null pointer */
  /* polyspace<RTE:UNR:Not a defect : No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
  OS_CHECK_IOC_INVALID_QUEUED_BUF_ERROR(data, IocID, LulDataCount, LddStatusReturn);
  /* polyspace:begin<RTE:UNR:Not a defect : No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
  /* polyspace-begin MISRA-C3:14.3,2.1 DEFECT:DEAD_CODE [Not a defect:Low] "Verified manually with no impacts due to error check characteristic of user configuration" */
  /* polyspace-begin CERT-C:MSC12-C [Not a defect:Low] "Value of LddStatusReturn depends on User-Configuration" */
  if(LddStatusReturn == IOC_E_OK)
  {
    #if (OS_MULTICORE == STD_ON)
    /* @Trace: SafeOs_SUD_API_19902*/
    Os_GetSpinlock(OS_IOCLOCKBASE_QUEUED+IocID);
    #endif
    /* @Trace: SafeOs_SUD_API_19903*/
    /* receive IOC data */
    LpCfg = &Os_GaaIocQueuedCfg[IocID];
    if(LpCfg->ulQueueCount == OS_ZERO)
    {
      /* @Trace: SafeOs_SUD_API_19904*/
      /* Queue is empty */
      LddStatusReturn = (StatusType)IOC_E_NO_DATA;
    }
    else
    {
      for(LulDataCount = OS_ZERO; LulDataCount < LpCfg->ulDataCount;
                                                               LulDataCount++)
      {
        /* @Trace: SafeOs_SUD_API_19905*/
        LpBuf = &(LpCfg->pBuffer[LulDataCount]);
        /* polyspace<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
        LulStartIdx = LpCfg->ulQueueRead * LpBuf->ulDataSize;

        /* polyspace:begin<MISRA-C:10.1:Not a defect:Justify with annotations> It is used for consistency */
        /* polyspace:begin<RTE:OVFL:Not a defect:No action planned> It is defined from statically defined value */
        /* polyspace:begin<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually */
        /* polyspace-begin CERT-C:INT36-C [Justified:Low] "This conversion cannot be modified to handle memory" */
        /* polyspace +6 MISRA-C3:18.4 [Justified:Low] "Increment operator on pointer used to achieve better throughput" */
        /* polyspace-begin MISRA-C3:11.8 [Justified:Low] "Type cast for memcpy is safe" */
        /* polyspace +4 MISRA-C3:D4.11 [Justified:Low] "function is called with a valid arguments that are confirmed by testing" */
        /* polyspace<RTE:STD_LIB:Not a defect:No action planned> It is used for consistency */
        /* polyspace-begin MISRA-C3:11.5 [Justified:Low] "No Impact of this rule violation" */
        /* polyspace-begin MISRA-C3:11.4 [Justified:Low] "Conversion is needed for implementation" */
        LulIocBuf = (uint32)(LpBuf->pIocBuf);
        Os_MemCopy((void*)(data[LulDataCount]),
            (void*)(&((uint8*)LulIocBuf)[LulStartIdx]), (Os_Size_T)LpBuf->ulDataSize);
        /* polyspace-end MISRA-C3:11.4 [Justified:Low] "Conversion is needed for implementation" */
        /* polyspace-end MISRA-C3:11.5 [Justified:Low] "No Impact of this rule violation" */
        /* polyspace-end MISRA-C3:11.8 [Justified:Low] "Type cast for memcpy is safe" */
        /* polyspace-end CERT-C:INT36-C [Justified:Low] "This conversion cannot be modified to handle memory" */
        /* polyspace:end<RTE:OVFL:Not a defect:No action planned> It is defined from statically defined value */
        /* polyspace:end<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually */
        /* polyspace:end<MISRA-C:10.1:Not a defect:Justify with annotations>  It is used for consistency */
      }
      /* @Trace: SafeOs_SUD_API_19906*/
      LpCfg->ulQueueRead = (LpCfg->ulQueueRead < (LpCfg->ulQueueLen - OS_ONE)) ?
                                          (LpCfg->ulQueueRead + OS_ONE) : OS_ZERO;
      LpCfg->ulQueueCount--;

      if(LpCfg->blDataLost == OS_TRUE)
      {
        /* @Trace: SafeOs_SUD_API_19907 */
        LpCfg->blDataLost = OS_FALSE;
        LddStatusReturn = IOC_E_LOST_DATA;
      }
    }
    #if (OS_MULTICORE == STD_ON)
    /* @Trace: SafeOs_SUD_API_19908*/
    Os_ReleaseSpinlock(OS_IOCLOCKBASE_QUEUED+IocID);
    #endif
  }
  /* polyspace-end CERT-C:MSC12-C [Not a defect:Low] "Value of LddStatusReturn depends on User-Configuration" */
  /* polyspace-end MISRA-C3:14.3,2.1 DEFECT:DEAD_CODE [Not a defect:Low] "Verified manually with no impacts due to error check characteristic of user configuration" */
  /* polyspace:end<RTE:UNR:Not a defect : No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
  /* @Trace: SafeOs_SUD_API_19909*/
  return LddStatusReturn;
}

/*******************************************************************************
** Function Name        : Os_KernIocSend                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function send data through IOC                 **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : IocID                                               **
**                                                                            **
** InOut parameter      : data                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GaaIocQueuedCfg, Os_Ioc_Count_Queued             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_GetSpinlock(), Os_ReleaseSpinlock(),             **
**                        Os_MemCopy()                                        **
*******************************************************************************/
/* @Trace: SRS_Os_80006 SRS_Os_80020 */
FUNC(Std_ReturnType, OS_CODE) Os_KernIocSend(uint32 IocID,
                                 CONSTP2CONST(uint32, AUTOMATIC, OS_CONST) data[])
{
  StatusType LddStatusReturn;
  P2VAR(Os_IocQueuedCfgType, AUTOMATIC, OS_VAR) LpCfg;
  P2CONST(Os_IocBufType, AUTOMATIC, OS_CONST) LpBuf;
  uint32 LulDataCount;
  uint32 LulStartIdx;
  uint32 LulIocBuf;

  LddStatusReturn = IOC_E_OK;
  LulDataCount = OS_ZERO;

  /* @Trace: SafeOs_SUD_API_19801 */
  /* Check whether Os has started or not */
  OS_CHECK_IOC_NOT_STARTOS(&LddStatusReturn);
  /* check IOC ID */
  /* polyspace<RTE:UNR:Not a defect:No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
  OS_CHECK_IOC_ID_ERROR(IocID, Os_Ioc_Count_Queued, LddStatusReturn);
  /* polyspace +3 MISRA-C3:D4.14 [Justified:Low] "IocID have been checked before using" */
  /* check null pointer */
  /* polyspace<RTE:UNR:Not a defect:No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
  OS_CHECK_IOC_INVALID_QUEUED_BUF_ERROR(data, IocID, LulDataCount, LddStatusReturn);
  /* polyspace:begin<RTE:UNR:Not a defect:No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
  /* polyspace-begin MISRA-C3:14.3,2.1 DEFECT:DEAD_CODE [Not a defect:Low] "Verified manually with no impacts due to error check characteristic of user configuration" */
  /* polyspace-begin CERT-C:MSC12-C [Not a defect:Low] "Value of LddStatusReturn depends on User-Configuration" */
  if(LddStatusReturn == IOC_E_OK)
  {
    #if (OS_MULTICORE == STD_ON)
    /* @Trace: SafeOs_SUD_API_19802 */
    Os_GetSpinlock(OS_IOCLOCKBASE_QUEUED+IocID);
    #endif
    /* @Trace: SafeOs_SUD_API_19803 */
    /* receive IOC data */
    LpCfg = &Os_GaaIocQueuedCfg[IocID];
    if(LpCfg->ulQueueCount >= LpCfg->ulQueueLen)
    {
      /* @Trace: SafeOs_SUD_API_19804 */
      /* Queue is full */
      LpCfg->blDataLost = OS_TRUE;
      LddStatusReturn = (StatusType)IOC_E_LIMIT;
    }
    else
    {
      for(LulDataCount = OS_ZERO; LulDataCount < LpCfg->ulDataCount;
                                                               LulDataCount++)
      {
        /* @Trace: SafeOs_SUD_API_19805 */
        LpBuf = &(LpCfg->pBuffer[LulDataCount]);
        /* polyspace<RTE:NIV:Not a defect:No Action Planned> variable is initialized and code is verified manually */
        LulStartIdx = LpCfg->ulQueueWrite * LpBuf->ulDataSize;
        /* polyspace:begin<MISRA-C:10.1:Not a defect:Justify with annotations> It is used for consistency */
        /* polyspace-begin CERT-C:INT36-C [Justified:Low] "This conversion cannot be modified to handle memory" */
        /* polyspace<RTE:OVFL:Not a defect:No action planned> It is defined from statically defined value */
        /* polyspace<RTE:STD_LIB:Not a defect:No action planned> It is used for consistency */
        /* polyspace<RTE:NIP:Not a defect:No Action Planned> ptr points to a valid value and code is verified manually */
        /* polyspace +4 MISRA-C3:18.4 [Justified:Low] "Increment operator on pointer used to achieve better throughput" */
        /* polyspace +4 MISRA-C3:D4.11 [Justified:Low] "function is called with a valid arguments that are confirmed by testing" */
        /* polyspace +2 MISRA-C3:11.5 [Justified:Low] "No Impact of this rule violation" */
        /* polyspace-begin MISRA-C3:11.4 [Justified:Low] "The conversion needed for imlementation" */
        LulIocBuf = (uint32)(LpBuf->pIocBuf);
        Os_MemCopy((void*)(&((uint8*)LulIocBuf)[LulStartIdx]),
                              data[LulDataCount], (Os_Size_T)LpBuf->ulDataSize);
        /* polyspace-end MISRA-C3:11.4 [Justified:Low] "The conversion needed for imlementation" */
        /* polyspace-end CERT-C:INT36-C [Justified:Low] "This conversion cannot be modified to handle memory" */
        /* polyspace:end<MISRA-C:10.1:Not a defect:Justify with annotations>  It is used for consistency */
      }
      /* @Trace: SafeOs_SUD_API_19806 */
      LpCfg->ulQueueWrite =
        (LpCfg->ulQueueWrite < (LpCfg->ulQueueLen - OS_ONE)) ?
                                         (LpCfg->ulQueueWrite + OS_ONE) : OS_ZERO;
      LpCfg->ulQueueCount++;
    }
    #if (OS_MULTICORE == STD_ON)
    /* @Trace: SafeOs_SUD_API_19807 */
    Os_ReleaseSpinlock(OS_IOCLOCKBASE_QUEUED+IocID);
    #endif
  }
  /* polyspace-end CERT-C:MSC12-C [Not a defect:Low] "Value of LddStatusReturn depends on User-Configuration" */
  /* polyspace-end MISRA-C3:14.3,2.1 DEFECT:DEAD_CODE [Not a defect:Low] "Verified manually with no impacts due to error check characteristic of user configuration" */
  /* polyspace:end<RTE:UNR:Not a defect:No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
/* @Trace: SafeOs_SUD_API_19808 */
  return LddStatusReturn;
}

/*******************************************************************************
** Function Name        : Os_KernIocEmptyQueue                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function empty Queue                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : IocID                                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GaaIocQueuedCfg, Os_Ioc_Count_Queued             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_GetSpinlock(), Os_ReleaseSpinlock()              **
*******************************************************************************/
/* @Trace: SRS_Os_80020 */
FUNC(Std_ReturnType, OS_CODE) Os_KernIocEmptyQueue(uint32 IocID)
{
  StatusType LddStatusReturn;
  P2VAR(Os_IocQueuedCfgType, AUTOMATIC, OS_VAR) LpCfg;

  LddStatusReturn = IOC_E_OK;
  /* @Trace: SafeOs_SUD_API_19501 */
  /* Check whether Os has started or not */
  OS_CHECK_IOC_NOT_STARTOS(&LddStatusReturn);
  /* check IOC ID */
  /* polyspace<RTE:UNR:Not a defect : No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
  OS_CHECK_IOC_ID_ERROR(IocID, Os_Ioc_Count_Queued, LddStatusReturn);

  /* polyspace:begin<RTE:UNR:Not a defect : No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
  /* polyspace-begin MISRA-C3:14.3,2.1 DEFECT:DEAD_CODE [Not a defect:Low] "Verified manually with no impacts due to error check characteristic of user configuration" */
  /* polyspace-begin CERT-C:MSC12-C [Not a defect:Low] "Value of LddStatusReturn depends on User-Configuration" */
  if(LddStatusReturn == IOC_E_OK)
  {
    #if (OS_MULTICORE == STD_ON)
    /* @Trace: SafeOs_SUD_API_19502 */
    Os_GetSpinlock(OS_IOCLOCKBASE_QUEUED+IocID);
    #endif
    /* @Trace: SafeOs_SUD_API_19503 */
    /* receive IOC data */
    LpCfg = &Os_GaaIocQueuedCfg[IocID];
    LpCfg->ulQueueRead = OS_ZERO;
    LpCfg->ulQueueWrite = OS_ZERO;
    LpCfg->ulQueueCount = OS_ZERO;
    LpCfg->blDataLost = OS_FALSE;
    #if (OS_MULTICORE == STD_ON)
    /* @Trace: SafeOs_SUD_API_19504 */
    Os_ReleaseSpinlock(OS_IOCLOCKBASE_QUEUED+IocID);
    #endif
  }
  /* polyspace-end CERT-C:MSC12-C [Not a defect:Low] "Value of LddStatusReturn depends on User-Configuration" */
  /* polyspace-end MISRA-C3:14.3,2.1 DEFECT:DEAD_CODE [Not a defect:Low] "Verified manually with no impacts due to error check characteristic of user configuration" */
  /* polyspace:end<RTE:UNR:Not a defect : No Action Planned> Because error check characteristic, unreachable code occurs. But this code has already been verified and no impact of this rule violation */
  /* @Trace: SafeOs_SUD_API_19505 */
  return LddStatusReturn;
}

/*******************************************************************************
** Function Name        : Os_DoIocPullCB                                      **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function pull IOC callback function            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : pIocPullCB, recvAppID                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GddAppId                                         **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        pIocPullCB()                                        **
*******************************************************************************/
FUNC(void, OS_CODE) Os_DoIocPullCB(
    P2FUNC(void, OS_CONST, pIocPullCB) (void), ApplicationType recvAppID)
{
  ApplicationType backupAppID;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* @Trace: SafeOs_SUD_API_19401 */
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);
  /* polyspace +5 DEFECT:OUT_BOUND_ARRAY [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +4 CERT-C:ARR30-C [Justified:Low] "The maximum number of element of array is equal to number of core. It is determined by hardware" */
  /* polyspace +4 MISRA-C3:2.2 [Justified:Low] "Backup and Resrote AppID is needed" */
  /* polyspace +3 DEFECT:USELESS_WRITE [Not a defect:Low] "Backup and Resrote AppID is needed" */
  /* polyspace +1 RTE:OBAI [Not a defect:Low] "configured array index" */
  backupAppID = Os_GddAppId[OS_CORE_ID];
  Os_GddAppId[OS_CORE_ID] = recvAppID;

  if(pIocPullCB != NULL_PTR){
    /* polyspace<RTE: COR : Not a defect : No Action Planned > function ptr points to a valid function and code is manually checked*/
    /* @Trace: SafeOs_SUD_API_19402 */
    pIocPullCB();
  }
  /* @Trace: SafeOs_SUD_API_19403 */
  Os_GddAppId[OS_CORE_ID] = backupAppID;
}

/*******************************************************************************
** Function Name        : Os_KernIocPullCB                                    **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : This function pull IOC callback function            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Re-entrant                                          **
**                                                                            **
** Input Parameters     : pIocPullCB, recvAppID                               **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        Os_GaaStaticApplication                             **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        Os_SendIocPullCB(),                                 **
**                        Os_DoIocPullCB()                                    **
*******************************************************************************/
/* @Trace: SRS_Os_80020 SRS_Os_11013 */
FUNC(void, OS_CODE) Os_KernIocPullCB(
    P2FUNC(void, OS_CONST, pIocPullCB) (void), ApplicationType recvAppID)
{
  StatusType LddStatusReturn;
  #if (OS_MULTICORE == STD_ON)
  CoreIDType OS_CORE_ID;
  #endif

  /* Set the return status value to "E_OK" */
  LddStatusReturn = IOC_E_OK;
  /* @Trace: SafeOs_SUD_API_19301*/
  /* Get The coreID */
  OS_GET_CORE_ID(OS_CORE_ID);

  /* Check whether Os has started or not */
  OS_CHECK_IOC_NOT_STARTOS(&LddStatusReturn);
  /* Check NULL_PTR for pIocPullCB */
  OS_CHECK_IOC_NULL_PTR(pIocPullCB, LddStatusReturn);

  /* Check no error */
  if(LddStatusReturn == IOC_E_OK)
  {
    /* Store the static task corresponding to TaskID in local pointer */
    #if (OS_MULTICORE == STD_ON)
    /* Check if new task belongs to same core */
    /* polyspace-begin MISRA-C3:D4.14 [Justified:Low] "recvAppID have been checked before using" */
    /* polyspace +1 RTE:OBAI [Not a defect:Low] "configured array index" */
    if (Os_GaaStaticApplication[recvAppID].ddCoreID != OS_CORE_ID)
    {
      /* @Trace: SafeOs_SUD_API_19302*/
      /* Call Os_SendActivateTask to schedule task on respective core */
      Os_SendIocPullCB(pIocPullCB, recvAppID);
    } /* End of if (LpStaticTask->ddCoreId != OS_CORE_ID) */
    else
    #endif /* End of if (OS_MULTICORE == STD_ON) */
    {
      /* @Trace: SafeOs_SUD_API_19303*/
      /* Call Os_DoIocPullCB */
      Os_DoIocPullCB(pIocPullCB, recvAppID);
    }
    /* polyspace-end MISRA-C3:D4.14 [Justified:Low] "recvAppID have been checked before using" */
  }
}
#endif /* if (OS_APPLICATION == STD_ON) */

#define OS_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

#define OS_API_START_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"
#if (OS_APPLICATION == STD_ON)
/***************************************************************************//**
 * Function Name        : Os_CallIocRead
 *
 * Service ID           : IOCServiceId_IOC_Read
 *
 * Description          : This service is used to read data through IOC
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : IocID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : data
 *
 * @return              : Std_ReturnType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
FUNC(StatusType, OS_CODE) Os_CallIocRead(uint32 IocID, P2VAR(void, AUTOMATIC, OS_VAR) data[])
{  
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_56501 */
  LddStatusReturn = OS_SYSCALL_IOCREAD(IocID, data);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : Os_CallIocWrite
 *
 * Service ID           : IOCServiceId_IOC_Write
 *
 * Description          : This service is used to write data through IOC
 *
 * Sync/Async           : Asynchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : IocID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : data
 *
 * @return              : Std_ReturnType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* @Trace: SRS_Os_00097 */
FUNC(StatusType, OS_CODE) Os_CallIocWrite(uint32 IocID,
                                 CONSTP2CONST(void, AUTOMATIC, OS_CONST) data[])
{  
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_56601 */
  LddStatusReturn = OS_SYSCALL_IOCWRITE(IocID, data);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : Os_CallIocReceive
 *
 * Service ID           : IOCServiceId_IOC_Receive
 *
 * Description          : This service is used to receive data through IOC
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : IocID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : data
 *
 * @return              : Std_ReturnType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* polyspace +1 MISRA-C3:8.13 [Justified:Low] "This pointer is modified by syscall but not visible in polyspace" */
FUNC(Std_ReturnType, OS_CODE) Os_CallIocReceive(uint32 IocID,
                                      P2VAR(void, AUTOMATIC, OS_VAR) data[])
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_56701 */
  LddStatusReturn = OS_SYSCALL_IOCRECEIVE(IocID, data);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : Os_CallIocSend
 *
 * Service ID           : IOCServiceId_IOC_Send
 *
 * Description          : This service is used to send data through IOC
 *
 * Sync/Async           : Asynchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : IocID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : data
 *
 * @return              : Std_ReturnType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* polyspace +1 MISRA-C3:8.13 [Justified:Low] "This pointer is modified by syscall but not visible in polyspace" */
FUNC(Std_ReturnType, OS_CODE) Os_CallIocSend(uint32 IocID, CONSTP2CONST(void, AUTOMATIC, OS_CONST) data[])
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_56801 */
  LddStatusReturn = OS_SYSCALL_IOCSEND(IocID, data);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : Os_CallIocEmptyQueue
 *
 * Service ID           : IOCServiceId_IOC_EmptyQueue
 *
 * Description          : This service is used to empty Queue
 *
 * Sync/Async           : Synchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : IocID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : Std_ReturnType
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* polyspace +1 MISRA-C3:8.13 [Justified:Low] "This pointer is modified by syscall but not visible in polyspace" */
FUNC(Std_ReturnType, OS_CODE) Os_CallIocEmptyQueue(uint32 IocID)
{
  StatusType LddStatusReturn = E_OK;
  /* @Trace : SafeOs_SUD_API_56901 */
  LddStatusReturn = OS_SYSCALL_IOCEMPTYQUEUE(IocID);

  return LddStatusReturn;
}

/***************************************************************************//**
 * Function Name        : Os_CallIocPullCB
 *
 * Service ID           : OSServiceId_Os_IocPullCB
 *
 * Description          : This service is used to pull IOC callback function
 *
 * Sync/Async           : Asynchronous
 *
 * Re-entrancy          : Re-entrancy
 *
 * Input Parameters     : pIocPullCB, recvAppID
 *
 * InOut parameter      : None
 *
 * Output Parameters    : None
 *
 * @return              : None
 *
 * @pre                 : StartOS() API should be invoked
 *
 * @remarks             : Global Variable(s)  : None
 *                        Function(s) invoked : None
 ******************************************************************************/
/* polyspace +1 MISRA-C3:8.13 [Justified:Low] "This pointer is modified by syscall but not visible in polyspace" */
FUNC(void, OS_CODE) Os_CallIocPullCB(P2FUNC(void, OS_CONST, pIocPullCB) (void),
    ApplicationType recvAppID)
{
  /* @Trace : SafeOs_SUD_API_56401 */
  OS_SYSCALL_IOCPULLCB(pIocPullCB, recvAppID);
}
#endif /* if (OS_APPLICATION == STD_ON) */
#define OS_API_STOP_SEC_CODE_ASIL_D_GLOBAL
#include "MemMap.h"

/*******************************************************************************
**              PRE-JUSTIFICATION END (MISRA-C RULE CHECKER)                  **
*******************************************************************************/
/* polyspace:end<ISO-17961:intptrconv:Not a defect:Justify with annotations> Conversion is needed for implementation */
/* polyspace-end MISRA-C3:11.4 [Not a defect:Justify with annotations] "Conversion is needed for implementation" */
/* polyspace:end<RTE:IDP:Not a defect:No action planned> It is defined from statically defined value */
/* polyspace-end MISRA-C3:20.1 [Justified:Low] "see SWS_MemMap_00003 of AUTOSAR" */
/* polyspace-end MISRA-C3:D4.1 [Justified:Low] "Ptr points to a valid value and code is verified manually" */
/* polyspace-end MISRA-C3:18.1 [Justified:Low] "Array index has been configured inside bounds and code is verified manually" */
/* polyspace-begin MISRA-C3:21.15 [Not a defect:No action planned] "This is Standard Library" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
