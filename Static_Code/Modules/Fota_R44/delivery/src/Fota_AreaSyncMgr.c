/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fota_AreaSyncMgr.c                                            **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR FOTA                                                  **
**                                                                            **
**  PURPOSE   : Provide definition of FOTA function                           **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By           Description                           **
** 1.0.0     23-Oct-2023   Djlee        Initial version                       **
********************************************************************************
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Fota.h"
#include "Fota_Types.h"
#include "Fota_IntFunc.h"
#include "Fota_Cfg.h"
#include "Fota_Globals.h"
#include "Mem_76_Pfls.h"
#include "Fota_PflsInterface.h"
#include "Fota_AreaSyncMgr.h"
#include "Fota_BootManager.h"
#include "Fota_MagicKeyMgr.h"
#include "Fota_User_Callouts.h"

/* polyspace-begin MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
/*******************************************************************************
**                      Macros                                                **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

static Fota_SyncStatType   rue_AreaSyncState    = FOTA_SYNC_IDLE;
#if (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)
static Fota_JobResultType  rue_AreaSyncResult   = FOTA_JOB_FAILED;
static Fota_SyncReqType    rue_AreaSyncReq      = FOTA_SYNC_ALL_SWUNIT;
static Fota_SyncCancelType rue_AreaSyncCancel   = FOTA_SYNC_CANCEL_OFF;
static uint8               rub_AreaSyncRetryCnt = FOTA_SYNC_ALL_RETRY_CNT;
#endif

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"

#if (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)
static FUNC(void, FOTA_CODE)Fota_AreaSyncEnd_Cbk(void);
static FUNC(void, FOTA_CODE)Fota_AreaSyncErr_Cbk(void);
static FUNC(Std_ReturnType, FOTA_CODE) Fota_FlashCmp(uint32 CmpAddr1,uint32 CmpAddr2,uint32 Length);
#endif

/*******************************************************************************
** Function Name        : Fota_AreaSyncIdleChk                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : check Idle state of sync                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(Std_ReturnType, FOTA_CODE) Fota_AreaSyncIdleChk(void)
{
	/* @Trace: FOTA_SUD_API_00197 */
	Std_ReturnType RetVal=E_NOT_OK;

	/* polyspace-begin MISRA-C3:14.3 [Justified:Low] "if-condition depends on the configuration." */
	if(rue_AreaSyncState==FOTA_SYNC_IDLE)
	{
		RetVal=E_OK;
	}
	/* polyspace-end MISRA-C3:14.3 [Justified:Low] "if-condition depends on the configuration." */

	return RetVal;
}

/*******************************************************************************
** Function Name        : Fota_GetAreaSyncState                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get Area Sync state                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(Fota_SyncStatType, FOTA_CODE) Fota_GetAreaSyncState(void)
{
	/* @Trace: FOTA_SUD_API_00198 */
	return rue_AreaSyncState;
}



/*******************************************************************************
** Function Name        : Fota_AreaSyncRequest                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Request start area sync operation                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* polyspace-begin MISRA-C3:2.7 [Justified:Low] "Parameter depends on the Configuration." */
FUNC(Std_ReturnType, FOTA_CODE) Fota_AreaSyncRequest(Fota_SyncReqType ren_ReqSync)
/* polyspace-end MISRA-C3:2.7 [Justified:Low] "Parameter depends on the Configuration." */
{
	/* @Trace: FOTA_SUD_API_00062 */
	Std_ReturnType RetVal=E_NOT_OK;

	#if (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)

		if(rue_AreaSyncState==FOTA_SYNC_IDLE)
		{
			if(ren_ReqSync == FOTA_SYNC_ALL_SWUNIT)
			{
				rue_AreaSyncReq      = ren_ReqSync;
				rue_AreaSyncCancel   = FOTA_SYNC_CANCEL_OFF;
				rue_AreaSyncResult   = FOTA_JOB_PENDING;
				rue_AreaSyncState    = FOTA_SYNC_START;
				rub_AreaSyncRetryCnt = FOTA_SYNC_ALL_RETRY_CNT;

				RetVal=E_OK;
			}
			else if(ren_ReqSync == FOTA_SYNC_VERIFIED_NONACT_SWUNIT)
			{
				rue_AreaSyncReq      = ren_ReqSync;
				rue_AreaSyncCancel   = FOTA_SYNC_CANCEL_OFF;
				rue_AreaSyncResult   = FOTA_JOB_PENDING;
				rue_AreaSyncState    = FOTA_SYNC_START;
				rub_AreaSyncRetryCnt = FOTA_SYNC_VERIFIED_NONACT_SWUNIT_RETRY_CNT;

				RetVal=E_OK;
			}
			else
			{

			}
		}
	#else
	FOTA_UNUSED(ren_ReqSync);
	#endif

	return RetVal;
}

/*******************************************************************************
** Function Name        : Fota_AreaSyncResult                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : result check area sync operation                    **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/

FUNC(Fota_JobResultType, FOTA_CODE) Fota_AreaSyncResult(void)
{
	/* @Trace: FOTA_SUD_API_00063 */
#if (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)
	return rue_AreaSyncResult;
#else
	return FOTA_JOB_FAILED;
#endif
}

/**
FUNC(Std_ReturnType, FOTA_CODE) Fota_AreaSyncCancel(void)
{
	Std_ReturnType RetVal=E_NOT_OK;

	#if (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)

		if(rue_AreaSyncState==FOTA_SYNC_IDLE)
		{
			rue_AreaSyncCancel = FOTA_SYNC_CANCEL_ON;

			RetVal=E_OK;
		}

	#endif

	return RetVal;
}
**/

/*******************************************************************************
** Function Name        : Fota_AreaSyncEnd_Cbk                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : End result save                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/

#if (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)
static FUNC(void, FOTA_CODE) Fota_AreaSyncEnd_Cbk(void)
{
	/* @Trace: FOTA_SUD_API_00167 */
	rue_AreaSyncState  = FOTA_SYNC_IDLE;
	rue_AreaSyncCancel = FOTA_SYNC_CANCEL_OFF;
	rue_AreaSyncResult = FOTA_JOB_OK;
}

/*******************************************************************************
** Function Name        : Fota_AreaSyncErr_Cbk                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Err result save                                     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/

static FUNC(void, FOTA_CODE) Fota_AreaSyncErr_Cbk(void)
{
	/* @Trace: FOTA_SUD_API_00168 */
	rue_AreaSyncState  = FOTA_SYNC_IDLE;
	rue_AreaSyncCancel = FOTA_SYNC_CANCEL_OFF;
	rue_AreaSyncResult = FOTA_JOB_FAILED;
}

/*******************************************************************************
** Function Name        : Fota_FlashCmp                                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : flash compare                                       **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : CmpAddr1,CmpAddr2,Length                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Std_ReturnType, FOTA_CODE) Fota_FlashCmp(uint32 CmpAddr1,uint32 CmpAddr2,uint32 Length)
{
	/* @Trace: FOTA_SUD_API_00166 */
	uint32 rul_Loop;
	uint32 rul_u32Length;

	Std_ReturnType retVal=E_OK;

	rul_u32Length=(uint32)(Length/FOTA_FOUR)*FOTA_FOUR;

	Fota_BeforeFlashReadFunc();

	for(rul_Loop=FOTA_ZERO;rul_Loop<rul_u32Length;rul_Loop+=FOTA_FOUR)
	{		
		/* polyspace-begin CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
		* the register value can be read via the address" */
		if((rue_AreaSyncCancel == FOTA_SYNC_CANCEL_ON)||((*(uint32 *)(CmpAddr1+rul_Loop))!=(*(uint32 *)(CmpAddr2+rul_Loop))))
		{
			retVal=E_NOT_OK;
			break;
		}
		/* polyspace-end CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
		* the register value can be read via the address" */
	}
	/* @Trace: FOTA_SUD_API_00201 */
	if(retVal==E_OK)
	{
		for(                 ;rul_Loop<Length;rul_Loop++)
		{			
			/* polyspace-begin CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
			* the register value can be read via the address" */
			if((rue_AreaSyncCancel == FOTA_SYNC_CANCEL_ON)||((*(uint8 *)(CmpAddr1+rul_Loop))!=(*(uint8 *)(CmpAddr2+rul_Loop))))
			{
				retVal=E_NOT_OK;
				break;
			}
			/* polyspace-end CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
			* the register value can be read via the address" */
		}
	}

	Fota_AfterFlashReadFunc();

	return retVal;
}

/*******************************************************************************
** Function Name        : Fota_StdAltFlashCmp                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : STD, ALT in pfls flash compare                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : rul_StdAddr,rul_StdLeng, rub_memInstance            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
static FUNC(Std_ReturnType, FOTA_CODE) Fota_StdAltFlashCmp(uint32 rul_StdAddr,uint32 rul_StdLeng, uint8 rub_memInstance)
{
	uint32 rul_AltCovAddr;
	uint32 rul_AltCovLeng;
	uint32 rul_RemainLeng;
	uint16 ruw_CmpLoop;

	Std_ReturnType retVal=E_OK;

	rul_AltCovAddr=rul_StdAddr;
	rul_AltCovLeng=rul_StdLeng;
	rul_RemainLeng=rul_AltCovLeng;

	/* @Trace: FOTA_SUD_API_00165 */
	for(ruw_CmpLoop=FOTA_ZERO;ruw_CmpLoop<MAX_OF_CMPLOOPCNT;ruw_CmpLoop++)
	{
	  if(E_OK==Fota_PflsGetCovAddr(rub_memInstance, \
									FOTA_ALT_ADDR, \
									&rul_AltCovAddr, \
									&rul_AltCovLeng))
	  {
		  if(rue_AreaSyncCancel == FOTA_SYNC_CANCEL_ON)
		  {
			  retVal=E_NOT_OK;
		  }
		  else
		  {
			  if(Fota_FlashCmp(rul_StdAddr,rul_AltCovAddr,rul_AltCovLeng)==E_OK)
			  {
				  /* polyspace-begin MISRA-C3:17.8 [Justified:Low] "It Modified for comparison of different address areas." */
				  rul_StdAddr   =rul_StdAddr   +rul_AltCovLeng;
				  /* polyspace-end MISRA-C3:17.8 [Justified:Low] "It Modified for comparison of different address areas." */
				  rul_AltCovAddr=rul_StdAddr;

				  rul_RemainLeng=rul_RemainLeng-rul_AltCovLeng;
				  rul_AltCovLeng=rul_RemainLeng;
			  }
			  else
			  {
				  retVal=E_NOT_OK;
			  }
		  }
	  }
	  else
	  {
		retVal=E_NOT_OK;
	  }

	  if((retVal==E_NOT_OK)||(rul_RemainLeng==FOTA_ZERO))
	  {
		break;
	  }
	}

	return retVal;
}
#endif

/*******************************************************************************
** Function Name        : Fota_AreaSyncMain                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Area Sync Main Function                             **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
FUNC(void, FOTA_CODE) Fota_AreaSyncMain(void)
{
#if (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)
	VAR(Fota_SetKeyResultType, AUTOMATIC) setKeyResult;
	static uint8 rub_SwUnitIdx;

	static const Fota_SwModule *swUnitHandlePtr;
	static uint8 rub_NumOfVerification;
	static uint8 rub_JobIndexVerification;
	static uint8 rub_NumOfVBlock;
	static uint8 rub_JobIndexVBlock;
	static const Fota_VerificationType *ptrVerification;
	static Fota_VerificationSwUnitType *ptrSWUnitHandler;
	static Fota_VerificationSwUnitType *ptrHandler;
	static const Fota_TargetBlockSwUnitType *targetBlockPtr;
	static const Fota_TargetBlockSwUnitType *ptrBlock;
	static const Fota_TargetBlockSwUnitType *ptrSig;
	static uint8 rub_SyncMemoryInstance;
	static uint32 rul_SyncWaitCnt=FOTA_ZERO;

	uint32 rul_StdAddr;
	uint32 rul_StdLeng;

	VAR(Mem_76_Pfls_JobResultType,AUTOMATIC) ren_CodeEraseReport;
	Mem_76_Pfls_JobResultType memJobResult;

    switch(rue_AreaSyncState)
    {
      case FOTA_SYNC_IDLE:


      break;

      case FOTA_SYNC_START:	
		/* @Trace: FOTA_SUD_API_00264 */
      	rue_AreaSyncState = FOTA_SYNC_SET_SWUNIT;
      	rub_SwUnitIdx = FOTA_ZERO;

      	if(rub_AreaSyncRetryCnt>FOTA_ZERO)
      	{
      		rub_AreaSyncRetryCnt--;
      	}

      break;

      case FOTA_SYNC_SET_SWUNIT:
		/* @Trace: FOTA_SUD_API_00153 */
    	(void)Fota_GetMemInstanceBySwUnit(rub_SwUnitIdx, &rub_SyncMemoryInstance);
    	swUnitHandlePtr = &Fota_Gast_SwUnitTable[rub_SwUnitIdx];
    	ptrVerification = swUnitHandlePtr->VerificationInfoPtr;

    	if(rue_AreaSyncReq==FOTA_SYNC_ALL_SWUNIT)
    	{
    		rue_AreaSyncState = FOTA_SYNC_ERASE_SWUNIT_REQ;
    	}
    	else
    	{
            if ((E_OK==Fota_ChkVfyKey(rub_SwUnitIdx,FOTA_TARGET_AREA))&&(E_OK!=Fota_ChkActKey(rub_SwUnitIdx,FOTA_TARGET_AREA)))
            {
            	rue_AreaSyncState = FOTA_SYNC_SET_SWUNIT_END;
            }
            else
            {
            	rue_AreaSyncState = FOTA_SYNC_ERASE_SWUNIT_REQ;
            }
    	}

      break;

      case FOTA_SYNC_ERASE_SWUNIT_REQ:
		/* @Trace: FOTA_SUD_API_00154 */
        #if (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)
        (void)Fota_PflsTgtAreaSet(rub_SyncMemoryInstance,FOTA_ALT_ADDR);
        #endif

  		if (E_OK == Fota_PflsEraseRequest(\
  					rub_SyncMemoryInstance, \
					swUnitHandlePtr->StartAddress, \
					swUnitHandlePtr->EndAddress - swUnitHandlePtr->StartAddress + FOTA_ONE))
  		{
  			rul_SyncWaitCnt   = FOTA_ZERO;
  			rue_AreaSyncState = FOTA_SYNC_ERASE_SWUNIT_CHK;
  		}
  		else
  		{
  			rue_AreaSyncState = FOTA_SYNC_ERR;
  		}

      break;

      case FOTA_SYNC_ERASE_SWUNIT_CHK:
	  	/* @Trace: FOTA_SUD_API_00155 */
    	ren_CodeEraseReport = Fota_PflsGetJobResult(rub_SyncMemoryInstance);

    	if(ren_CodeEraseReport == MEM_JOB_PENDING)
    	{
    		if(rue_AreaSyncCancel == FOTA_SYNC_CANCEL_ON)
    		{
    			// to do pfls cancel request
    			// to do rue_AreaSyncState = FOTA_SYNC_ERR;
    		}

            if(rul_SyncWaitCnt>FOTA_SYNCWAITCNT)
            {
            	rue_AreaSyncState = FOTA_SYNC_ERR;
            }
            else
            {
            	rul_SyncWaitCnt++;
            }
    	}
    	else if(ren_CodeEraseReport==MEM_JOB_OK)
    	{
    	  rue_AreaSyncState = FOTA_SYNC_SET_VERIFY_UNIT;
    	  rub_JobIndexVerification = 0;
    	}
    	else
    	{
    	  rue_AreaSyncState = FOTA_SYNC_ERR;
    	}
    	break;

      case FOTA_SYNC_SET_VERIFY_UNIT:
		  /* @Trace: FOTA_SUD_API_00156 */
    	  rub_NumOfVerification = ptrVerification->NumOfVerification;

    	  ptrSWUnitHandler = ptrVerification->VerificationSWUnit;
    	  ptrHandler = &ptrSWUnitHandler[rub_JobIndexVerification];
    	  rub_JobIndexVBlock       = 0;

    	  rue_AreaSyncState = FOTA_SYNC_SET_VERIFY_UNIT_MODULE;

    	break;

      case FOTA_SYNC_SET_VERIFY_UNIT_MODULE:
		  /* @Trace: FOTA_SUD_API_00265 */
    	  rub_NumOfVBlock = ptrHandler->VerifyNumberOfBlock;

    	  targetBlockPtr = ptrHandler->VerifyTargetBlock;
    	  ptrBlock = &targetBlockPtr[rub_JobIndexVBlock];

    	  rue_AreaSyncState = FOTA_SYNC_WRITE_FW_REQ;

        break;

      case FOTA_SYNC_WRITE_FW_REQ:
		 /* @Trace: FOTA_SUD_API_00157 */
		 #if (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)
		 (void)Fota_PflsTgtAreaSet(rub_SyncMemoryInstance,FOTA_ALT_ADDR);
		 #endif
		 
   		 /* polyspace-begin CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
   		 * the register value can be read via the address" */
		 Fota_BeforeFlashReadFunc();

   		 if (E_OK == Fota_PflsWriteRequest(rub_SyncMemoryInstance, \
      		                              (uint32)(ptrBlock->StartAddress), \
				                          (uint8*)(ptrBlock->StartAddress), ptrBlock->EndAddress - ptrBlock->StartAddress + FOTA_ONE))

         {
   			 rul_SyncWaitCnt   = FOTA_ZERO;
     	     rue_AreaSyncState = FOTA_SYNC_WRITE_FW_CHK;
         }
         else
         {
        	 Fota_AfterFlashReadFunc();
        	 rue_AreaSyncState = FOTA_SYNC_ERR;
         }
   		 /* polyspace-end CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
   		 * the register value can be read via the address" */

      break;

      case FOTA_SYNC_WRITE_FW_CHK:
		  /* @Trace: FOTA_SUD_API_00158 */
          memJobResult = Fota_PflsGetJobResult(rub_SyncMemoryInstance);

          if (MEM_JOB_OK == memJobResult)
          {
        	  rul_StdAddr   =ptrBlock->StartAddress;
        	  rul_StdLeng   =ptrBlock->EndAddress - ptrBlock->StartAddress + FOTA_ONE;

        	  if(Fota_StdAltFlashCmp(rul_StdAddr,rul_StdLeng,rub_SyncMemoryInstance)==E_OK)
        	  {
        		  rue_AreaSyncState = FOTA_SYNC_SET_VERIFY_UNIT_MODULE_END;
        	  }
        	  else
        	  {
        		  rue_AreaSyncState = FOTA_SYNC_ERR;
        	  }

        	  Fota_AfterFlashReadFunc();
          }
          else if (MEM_JOB_FAILED == memJobResult)
          {
        	  Fota_AfterFlashReadFunc();

        	  rue_AreaSyncState = FOTA_SYNC_ERR;
          }
          else
          {
      		if(rue_AreaSyncCancel == FOTA_SYNC_CANCEL_ON)
      		{
      			/* to do pfls cancel request */
      			/* to do rue_AreaSyncState = FOTA_SYNC_ERR; */
      		}

            if(rul_SyncWaitCnt>FOTA_SYNCWAITCNT)
            {
            	Fota_AfterFlashReadFunc();

            	rue_AreaSyncState = FOTA_SYNC_ERR;
            }
            else
            {
            	rul_SyncWaitCnt++;
            }

          }

      break;

      case FOTA_SYNC_SET_VERIFY_UNIT_MODULE_END:
		  /* @Trace: FOTA_SUD_API_00266 */
    	  if(rub_JobIndexVBlock >= (rub_NumOfVBlock-FOTA_ONE))
    	  {
    		  rue_AreaSyncState = FOTA_SYNC_WRITE_SIG_REQ;
    	  }
    	  else
    	  {
    		  rub_JobIndexVBlock++;
    		  rue_AreaSyncState = FOTA_SYNC_SET_VERIFY_UNIT_MODULE;
    	  }

      break;

      case FOTA_SYNC_WRITE_SIG_REQ:
		  /* @Trace: FOTA_SUD_API_00159 */
    	  ptrSig = ptrHandler->VerifySignature;

    	  #if (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)
		  (void)Fota_PflsTgtAreaSet(rub_SyncMemoryInstance,FOTA_ALT_ADDR);
		  #endif
		  
		  Fota_BeforeFlashReadFunc();

          /* polyspace-begin CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
          * the register value can be read via the address" */
          if (E_OK == Fota_PflsWriteRequest(rub_SyncMemoryInstance, \
         		                              (uint32)(ptrSig->StartAddress), \
 				                              (uint8*)(ptrSig->StartAddress), ptrSig->EndAddress - ptrSig->StartAddress + FOTA_ONE))
          {
        	 rul_SyncWaitCnt   = FOTA_ZERO;
      	     rue_AreaSyncState = FOTA_SYNC_WRITE_SIG_CHK;
          }
          else
          {
        	 Fota_AfterFlashReadFunc();

         	 rue_AreaSyncState = FOTA_SYNC_ERR;
          }
          /* polyspace-begin CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
          * the register value can be read via the address" */


      break;

      case FOTA_SYNC_WRITE_SIG_CHK:
		  /* @Trace: FOTA_SUD_API_00160 */
          memJobResult = Fota_PflsGetJobResult(rub_SyncMemoryInstance);

          if (MEM_JOB_OK == memJobResult)
          {
        	  rul_StdAddr   =ptrSig->StartAddress;
        	  rul_StdLeng   =ptrSig->EndAddress - ptrSig->StartAddress + FOTA_ONE;

        	  if(Fota_StdAltFlashCmp(rul_StdAddr,rul_StdLeng,rub_SyncMemoryInstance)==E_OK)
        	  {
        		  rue_AreaSyncState = FOTA_SYNC_SET_VERIFY_UNIT_END;
        	  }
        	  else
        	  {
        		  rue_AreaSyncState = FOTA_SYNC_ERR;
        	  }

        	  Fota_AfterFlashReadFunc();

          }
          else if (MEM_JOB_FAILED == memJobResult)
          {
        	  Fota_AfterFlashReadFunc();

        	  rue_AreaSyncState = FOTA_SYNC_ERR;
          }
          else
          {
      		if(rue_AreaSyncCancel == FOTA_SYNC_CANCEL_ON)
      		{
      			/* to do pfls cancel request */
      			/* to do rue_AreaSyncState = FOTA_SYNC_ERR; */
      		}

            if(rul_SyncWaitCnt>FOTA_SYNCWAITCNT)
            {
            	Fota_AfterFlashReadFunc();

            	rue_AreaSyncState = FOTA_SYNC_ERR;
            }
            else
            {
            	rul_SyncWaitCnt++;
            }

          }

      break;

      case FOTA_SYNC_SET_VERIFY_UNIT_END:
		  /* @Trace: FOTA_SUD_API_00161 */
    	  if(rub_JobIndexVerification >= (rub_NumOfVerification-FOTA_ONE))
    	  {
    		  rue_AreaSyncState = FOTA_SYNC_SET_SWUNIT_END;
    	  }
    	  else
    	  {
    		  rub_JobIndexVerification++;
    		  rue_AreaSyncState = FOTA_SYNC_SET_VERIFY_UNIT;
    	  }

      break;
      case FOTA_SYNC_SET_SWUNIT_END:
		  /* @Trace: FOTA_SUD_API_00267 */
    	  /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the Configuration." */
    	  #if (FOTA_NUM_OF_SWUNIT>1U)
    	    if(rub_SwUnitIdx >= (FOTA_NUM_OF_SWUNIT-FOTA_ONE))
    	    {
    		  rub_SwUnitIdx=FOTA_ZERO;
    		  rue_AreaSyncState = FOTA_SYNC_WRITE_VFYKEY_REQ;
    	    }
    	    else
    	    {
    		  rub_SwUnitIdx++;
    		  rue_AreaSyncState = FOTA_SYNC_SET_SWUNIT;
    	    }
    	  #else
    	    rue_AreaSyncState = FOTA_SYNC_WRITE_VFYKEY_REQ;
    	  #endif
    	  /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the Configuration." */

      break;

      case FOTA_SYNC_WRITE_VFYKEY_REQ:
		  /* @Trace: FOTA_SUD_API_00162 */
    	  if (E_OK == Fota_ChkVfyKey(rub_SwUnitIdx,FOTA_TARGET_AREA))
    	  {
        	  /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the Configuration." */
        	  #if (FOTA_NUM_OF_SWUNIT>1U) 
        	    if(rub_SwUnitIdx >= (FOTA_NUM_OF_SWUNIT-FOTA_ONE))
        	    {
        		  rue_AreaSyncState = FOTA_SYNC_END;
        	    }
        	    else
        	    {
        		  rub_SwUnitIdx++;
        	    }
        	  #else
        	    rue_AreaSyncState = FOTA_SYNC_END;
        	  #endif
        	  /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the Configuration." */
    	  }
    	  else
    	  {
			  if (E_OK == Fota_SetVfyKey_Request(rub_SwUnitIdx))
			  {
				  rue_AreaSyncState = FOTA_SYNC_WRITE_VFYKEY_CHK;
			  }
			  else
			  {
				  rue_AreaSyncState = FOTA_SYNC_ERR;
			  }
    	  }

      break;

      case FOTA_SYNC_WRITE_VFYKEY_CHK:
		  /* @Trace: FOTA_SUD_API_00163 */
          setKeyResult = Fota_SetKey_Result();

          if (FOTA_SETMAGICKEY_OK == setKeyResult)
          {
        	  /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the Configuration." */
        	  #if (FOTA_NUM_OF_SWUNIT>1U) 
        	    if(rub_SwUnitIdx >= (FOTA_NUM_OF_SWUNIT-FOTA_ONE))
        	    {
        		  rue_AreaSyncState = FOTA_SYNC_END;
        	    }
        	    else
        	    {
        		  rub_SwUnitIdx++;
        		  rue_AreaSyncState = FOTA_SYNC_WRITE_VFYKEY_REQ;
        	    }
        	  #else
        	    rue_AreaSyncState = FOTA_SYNC_END;
        	  #endif
        	  /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the Configuration." */
          }
          else if (FOTA_SETMAGICKEY_FAILED == setKeyResult)
          {
        	  rue_AreaSyncState = FOTA_SYNC_ERR;
          }
          else
          {

          }

      break;



      case FOTA_SYNC_END:
		  /* @Trace: FOTA_SUD_API_00164 */
    	  Fota_AreaSyncEnd_Cbk();

      break;

      case FOTA_SYNC_ERR:
		  /* @Trace: FOTA_SUD_API_00268 */
    	  /* retry for fail-safe */
    	  if(rub_AreaSyncRetryCnt>FOTA_ZERO)
    	  {
    		  rue_AreaSyncState = FOTA_SYNC_START;
    	  }
    	  else
    	  {
    		  Fota_AreaSyncErr_Cbk();
    	  }

      break;
      default:
		  /* @Trace: FOTA_SUD_API_00269 */
    	  Fota_AreaSyncErr_Cbk();

      break;
    }
#endif
}

#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"

/* polyspace-end MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
