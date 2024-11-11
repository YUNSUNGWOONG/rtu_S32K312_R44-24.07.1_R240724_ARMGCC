/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: FOTA.c                                                        **
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
**                             Revision History                               **
********************************************************************************
** Revision  Date          By           Description                           **
********************************************************************************
** 1.0.0     30-Mar-2022   jys          Initial version                       **
** 1.0.1     11-Dec-2023   VuPH6        #CP44-3526                            **
**                                      #CP44-3527                            **
**                                      #CP44-3545                            **
**                                      #CP44-3542                            **
**                         jys          #CP44-4173                            **
** 1.1.0     26-Mar-2024   jys          #CP44-3525                            **
**                                      #CP44-3708                            **
**                                      #CP44-3720                            **
**                                      #CP44-4173                            **
**                                      #CP44-5405                            **
** 1.1.0.0_HF1 26-Apr-2024  KJShim      #CP44-8300                            **
** 1.1.0.0_HF2 07-Jun-2024  JSKang      #CP44-9298                            **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Fota.h"
#include "Fota_Globals.h"
#include "Mem_76_Pfls.h"
#include "Mem_76_Pfls_Types.h"
#include "Mem_76_Pfls_Globals.h"
#include "Fota_PflsInterface.h"
#include "Fota_User_Callouts.h"
#include "Fota_NonMmuSubFunc.h"
#include "Fota_MagicKeyMgr.h"
#include "Fota_MacUpdateMgr.h"
#include "Rte_Fota.h"
#if (FOTA_MODE == FOTA_FBL_MODE) || (FOTA_MODE == FOTA_APP_MODE)
#include "Fota_AreaSyncMgr.h"
#include "Fota_IntFunc.h"
#include "Fota_Verify.h"
#include "HwResource.h"
#include "Fota_Diag.h"
#include "Csm.h"
#include "Fota_BootManager.h"
#include "Fota_SoftwareVersionCheck.h"
#if (FOTA_STD_ON == FOTA_SF20_ENABLE)
#include "Fota_Decrypt.h"
#endif /* (FOTA_STD_ON == FOTA_SF20_ENABLE) */
#elif (FOTA_MODE == FOTA_UPDATER_MODE)
#include "Fota_Updater.h"
#endif
/* polyspace-begin MISRA-C3:2.7,8.13,20.9 [Justified:Low] "Not a defect" */
/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/


/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                     Global Data                                            **
*******************************************************************************/
/* polyspace-begin MISRA-C3:8.9 [Not a defect: Justify with annotations] "No Impact of this rule violation" */
static Fota_FlashWriteType Fota_Write;

Fota_RetransferType Fota_Retransfer = {STD_ON, 0x00000000UL, FOTA_FALSE};

static Fota_FwBlockProcessingType *BlockProcessingRulePtr;

static uint8 Fota_ActiveBankCheckValue = 0u;

#if (FOTA_STD_ON == FOTA_SF20_ENABLE)
static uint8 Lau8_DecryptedBuffer[FOTA_TP_BLOCK_LENGTH - 2U];
#endif /* (FOTA_STD_ON == FOTA_SF20_ENABLE) */
static uint8 Lau8_SignedBuffer[SEC_SF_SIGNATURE_DELIMITER_LENGTH + SEC_SF_SIGNATURE_SIZE_LENGTH+SEC_SF_SIGNATURE_SIZE];
/* polyspace-end MISRA-C3:8.9 [Not a defect: Justify with annotations] "No Impact of this rule violation" */
#if (FOTA_STD_ON == FOTA_SF20_ENABLE)
static uint8 Fota_MetaDataRequestCheck = FOTA_FALSE;
#endif
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/*******************************************************************************
** Function Name        : Fota_Init                                           **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : Initialization function - initializes all variables **
**                        and sets the module state to initialized            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : ConfigPtr: Pointer to the configuration             **
**                          data structure - since Mem driver is a precompile **
**                          module this parameter is typically not used       **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                                                            **
**                        Function(s) invoked :                               **
*******************************************************************************/
/* @Trace: FOTA_SRS_ES98765_02E_00027 FOTA_SRS_ES98765_02E_00031 FOTA_SRS_ES98765_02E_00037 FOTA_SRS_ES98765_02E_00038 FOTA_SRS_UDS_00011 */
/* @Trace: FOTA_SRS_ES95489_52E_00008 FOTA_SRS_ES98765_01E_00001 FOTA_SRS_ES98765_02E_00039 FOTA_SRS_UDS_00014*/
FUNC(void, FOTA_CODE) Fota_Init(void)
{
  /* @Trace: FOTA_SUD_API_00001 */
  Fota_PflsInit();

  #if FOTA_BOOT_MANAGER_USED
  #if (FOTA_MODE == FOTA_FBL_MODE)
  Fota_BootManager();
  #endif
  #endif
  Fota_State = FOTA_INIT;
  #if (FOTA_MODE == FOTA_UPDATER_MODE)
  Fota_InitUpdaterMode();
  #endif
  Fota_InitStatus = FOTA_MODULEINIT;
}

/*******************************************************************************
** Function Name        : Fota_DeInit                                         **
**                                                                            **
** Service ID           : 0x0B                                                **
**                                                                            **
** Description          : De-initialize module. If there is still an access   **
**                        job pending, it is immediately terminated (using    **
**                        hardware cancel operation) and the Mem driver       **
**                        module state is set to unitialized. Therefore, Mem  **
**                        must be re-initialized before it will accept any    **
**                        new job requests after this service is processed.   **
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
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                                                            **
**                        Function(s) invoked :                               **
*******************************************************************************/
FUNC(void, FOTA_CODE) Fota_DeInit(void)
{
  /* @Trace: FOTA_SUD_API_00006 */
  Fota_PflsDeinit();

  Fota_State = FOTA_IDLE;
  Fota_InitStatus = FOTA_MODULEDEINIT;
}
/*******************************************************************************
** Function Name        : Fota_ProcessReadActiveArea                          **
**                                                                            **
** Service ID           : 0x0B                                                **
**                                                                            **
** Description          : Read active bank memory, it's 0xA or 0xB            **
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
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                                                            **
**                        Function(s) invoked :                               **
*******************************************************************************/
/* @Trace: FOTA_SRS_UDS_00002 */
#if (FOTA_MODE == FOTA_FBL_MODE) || (FOTA_MODE == FOTA_APP_MODE)
FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessReadActiveArea
(
  VAR(uint16, AUTOMATIC) InEcuSwUnit,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpOut_MemoryArea,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
)
{
  VAR(Std_ReturnType,AUTOMATIC) retVal = E_NOT_OK;
  VAR(Fota_PartitionType,AUTOMATIC) LenActivePartition;
  VAR(Fota_ActAreaResType,AUTOMATIC) LenRetArea;
  VAR(uint8, AUTOMATIC) rub_UnUsed;
  FOTA_UNUSED(InEcuSwUnit);
  FOTA_UNUSED(OpStatus);

  *LpErrorCode = DCM_E_GENERALREJECT;

  /* polyspace-begin MISRA-C3:14.3 [Justified:Low] "if-condition depends on the configuration." */
  if (FOTA_MCU_MEMORY_ACCESS_TYPE!=FOTA_SINGLE_TYPE)
  {
    if((Fota_GetSoftwareModuleBlkBySwType(FOTA_RTSW_PARTA_TYPE,&rub_UnUsed)==E_OK) && /* from Ldj function name should be changed */
     (Fota_GetSoftwareModuleBlkBySwType(FOTA_RTSW_PARTB_TYPE,&rub_UnUsed)==E_OK))
    {
      /* @Trace: FOTA_SUD_API_00009 */
      if(Fota_GetActivePartition(&LenActivePartition)==E_OK)
      {
        if(LenActivePartition==FOTA_PARTITION_A)
        {
          LenRetArea = FOTA_AREA_A;

          retVal = E_OK;
          *LpOut_MemoryArea = (uint8)LenRetArea;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else if(LenActivePartition==FOTA_PARTITION_B)
        {
          LenRetArea = FOTA_AREA_B;

          retVal = E_OK;
          *LpOut_MemoryArea = (uint8)LenRetArea;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else
        {
          #if (FOTA_MODE==FOTA_FBL_MODE)
          LenRetArea = FOTA_AREA_B;

          retVal = E_OK;
          *LpOut_MemoryArea = (uint8)LenRetArea;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
          #else

          #endif
        }
      }
      else
      {
        #if (FOTA_MODE==FOTA_FBL_MODE)
        LenRetArea = FOTA_AREA_B;

        retVal = E_OK;
        *LpOut_MemoryArea = (uint8)LenRetArea;
        *LpErrorCode = DCM_E_POSITIVERESPONSE;
        #else

        #endif
      }
    }
    else
    {
      /* @Trace: FOTA_SUD_API_00015 */
      retVal=Fota_PflsGetActiveBank(&Fota_ActiveBankCheckValue);
      if(E_OK==retVal)
      {
        *LpOut_MemoryArea = Fota_ActiveBankCheckValue;
        *LpErrorCode = DCM_E_POSITIVERESPONSE;
      }
      else
      {
        *LpErrorCode = DCM_E_GENERALREJECT;
      }
    }
  }
  /* polyspace-end MISRA-C3:14.3 [Justified:Low] "if-condition depends on the configuration." */
  return retVal;
}
#endif
/*******************************************************************************
** Function Name        : Fota_ProcessActivateSingleMem                       **
**                                                                            **
** Service ID           : 0x0B                                                **
**                                                                            **
** Description          : Trigger Acitvate service                            **
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
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                                                            **
**                        Function(s) invoked :                               **
*******************************************************************************/
#if ((FOTA_IMPLEMENTATION_RULE == FOTA_OTA_ES98765_02) &&\
  (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessActivateSingleMem
(
  VAR(uint8, AUTOMATIC) InMemArea,
  VAR(uint16, AUTOMATIC) InEcuSwUnit,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
)
{
  FOTA_UNUSED(InMemArea);
  FOTA_UNUSED(InEcuSwUnit);
  VAR(Std_ReturnType, AUTOMATIC) retVal = E_NOT_OK;
  VAR(Mem_76_Pfls_JobResultType, AUTOMATIC) memJobResult;
  VAR(Fota_SetKeyResultType, AUTOMATIC) setKeyResult;
  static Fota_SwapStatType swapState = FOTA_SWAP_ERR;
  static VAR(uint8, AUTOMATIC) indexSwUnit = 0;
  uint32 eraseRomLength;
  #if FOTA_SOFTWARE_VERSION_CHECK
  static Fota_VersionCheckRequestType versionCheckRequest;
  Fota_JobResultType versionCheckResult;
  static boolean recoveryAllSwUnit;
  uint8 index;
  #endif

  *LpErrorCode = DCM_E_GENERALREJECT;

  if ((OpStatus == DCM_INITIAL) || (OpStatus == DCM_PENDING))
  {
    /* @Trace: FOTA_SUD_API_00018 */
    if (OpStatus == DCM_INITIAL)
    {
      Fota_ProgrammingSWUnitId = FOTA_ZERO;

      (void)Fota_GetMemInstanceBySwUnit(Fota_ProgrammingSWUnitId, &Fota_MemoryInstance);

      #if (FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON)
      Fota_SvcResetGlobalVariable(indexSwUnit);
      /* Set Version check process */
      Fota_State = FOTA_VERSION_CHECK_PROCESSING;

      retVal = Fota_CheckAllSwUnitVersionCheck();

      if (E_OK == retVal)
      {
        swapState = FOTA_SWAP_VERSION_CHECK_REQUEST;
        recoveryAllSwUnit = FOTA_FALSE;
      }
      else
      {
        recoveryAllSwUnit = FOTA_TRUE;
        swapState = FOTA_SWAP_RECOVERY_TRAILER_ERASE_ROM;
      }
      #else
      swapState = FOTA_SWAP_VERIFY_KEY_CHK;
      #endif
      /* polyspace-begin MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
      retVal = DCM_E_PENDING;
      /* polyspace-end MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
      *LpErrorCode = DCM_E_POSITIVERESPONSE;
    }

    switch (swapState)
    {
      #if FOTA_SOFTWARE_VERSION_CHECK
      case FOTA_SWAP_VERSION_CHECK_REQUEST:
        /* @Trace: FOTA_SUD_API_00019 */
        versionCheckRequest = FOTA_VERSION_CHECK_CPD_REQUEST;
        Fota_VersionCheckRequest(versionCheckRequest, FOTA_ZERO);

        swapState = FOTA_SWAP_VERSION_CHECK_RESULT;
        retVal     = DCM_E_PENDING;
        *LpErrorCode = DCM_E_POSITIVERESPONSE;
        break;

      case FOTA_SWAP_VERSION_CHECK_RESULT:
        /* @Trace: FOTA_SUD_API_00207 */
        versionCheckResult = Fota_VersionCheckResult();
        if (FOTA_JOB_PENDING == versionCheckResult)
        {
          /* Do nothing */
        }
        else if (FOTA_JOB_OK == versionCheckResult)
        {
          retVal = Fota_CheckNextSwUnitVersionCheck(&indexSwUnit);

          if (FOTA_FALSE == recoveryAllSwUnit)
          {
            if (E_OK == retVal)
            {
              /* Go to next SwUnit */
              swapState = FOTA_SWAP_VERSION_CHECK_REQUEST;
            }
            else
            {
              /* Finished all SwUnit for version check */
              Fota_State = FOTA_READY;
              swapState = FOTA_SWAP_VERIFY_KEY_CHK;
            }
          }
          else
          {
            if (E_OK == retVal)
            {
              /* Go to next SwUnit for recovery */
              swapState = FOTA_SWAP_RECOVERY_TRAILER_ERASE_ROM;
            }
            else
            {
              /* Finished recovery version check for all SwUnit */
              indexSwUnit = 0;
              Fota_State = FOTA_READY;
              swapState = FOTA_SWAP_ERASE;
            }
          }
        }
        else if (FOTA_JOB_FAILED == versionCheckResult)
        {
          if (FOTA_VERSION_CHECK_CPD_REQUEST == versionCheckRequest)
          {
            #if (FOTA_DEV_ERROR_DETECT == STD_ON)
            /* Report Det Error */
            (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
              FOTA_ROUTINE_CONTROL_CPD_SID, FOTA_E_SVC_UPDATE_TRAILER_FAILED);
            #endif
            /* Recovery trailer and erase rom all SwUnit */
            indexSwUnit = 0;
            Fota_SvcResetGlobalVariable(indexSwUnit);
            recoveryAllSwUnit = FOTA_TRUE;
            swapState = FOTA_SWAP_RECOVERY_TRAILER_ERASE_ROM;
          }
          else if (FOTA_VERSION_CHECK_ERASE_ROM_REQUEST == versionCheckRequest)
          {
            #if (FOTA_DEV_ERROR_DETECT == STD_ON)
            /* Report Det Error */
            (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
              FOTA_ROUTINE_CONTROL_CPD_SID, FOTA_E_SVC_RECOVERY_TRAILER_FAILED);
            #endif
            indexSwUnit = 0;
            Fota_State = FOTA_READY;
            swapState = FOTA_SWAP_ERASE;
          }
          else
          {
            /* Do nothing */
          }
        }
        else
        {
          /* Do nothing */
        }
        retVal = DCM_E_PENDING;
        *LpErrorCode = DCM_E_POSITIVERESPONSE;
        break;

      case FOTA_SWAP_RECOVERY_TRAILER_ERASE_ROM:
        /* @Trace: FOTA_SUD_API_00208 */
        versionCheckRequest = FOTA_VERSION_CHECK_ERASE_ROM_REQUEST;

        Fota_VersionCheckRequest(versionCheckRequest, FOTA_ZERO);

        swapState = FOTA_SWAP_VERSION_CHECK_RESULT;
        retVal     = DCM_E_PENDING;
        *LpErrorCode = DCM_E_POSITIVERESPONSE;
        break;
      #endif /* #if FOTA_SOFTWARE_VERSION_CHECK */

      case FOTA_SWAP_VERIFY_KEY_CHK:
        /* @Trace: FOTA_SUD_API_00209 */
        if (E_OK == Fota_ChkVfyKeyAllSwUnit(FOTA_TARGET_AREA))
        {
          indexSwUnit = 0;
          swapState = FOTA_SWAP_ACTIVATE_KEY_WRITE;
        }
        else
        {
          indexSwUnit = 0;
          swapState = FOTA_SWAP_ERASE;
        }
        retVal = DCM_E_PENDING;
        *LpErrorCode = DCM_E_POSITIVERESPONSE;
        break;

      case FOTA_SWAP_ERASE:
        /* @Trace: FOTA_SUD_API_00210 */
        /* Erase area which same as routine-control erase
         * If version check enable, this delete except trailer
         */
        #if FOTA_SOFTWARE_VERSION_CHECK
        if (Fota_SvcResultAllSwUnit[indexSwUnit].CheckVersion ==
                                                            FOTA_VERSION_USED)
        {
          Fota_SvcResetGlobalVariable(indexSwUnit);
          /* 1st Erase Area for sector which include header */
          eraseRomLength = Fota_VersionCheckEraseRomLength(indexSwUnit);
        }
        else
        #endif
        {
          eraseRomLength =
            Fota_Gast_SwUnitTable[indexSwUnit].EndAddress -
            Fota_Gast_SwUnitTable[indexSwUnit].StartAddress + 1;
        }

        swapState = FOTA_SWAP_ERASE_CHK;
        (void)Fota_GetMemInstanceBySwUnit(indexSwUnit, &Fota_MemoryInstance);

        if (E_OK == Fota_PflsEraseRequest(
             Fota_MemoryInstance,
             Fota_Gast_SwUnitTable[indexSwUnit].StartAddress,
             eraseRomLength))
        {
          swapState = FOTA_SWAP_ERASE_CHK;
          retVal     = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else
        {
          #if (FOTA_DEV_ERROR_DETECT == STD_ON)
          /* Report Det Error */
          (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
           FOTA_ROUTINE_CONTROL_CPD_SID, FOTA_E_ERASE_REQUEST_FAILED);
          #endif
          swapState = FOTA_SWAP_ERR;
          retVal     = DCM_E_PENDING;
        }
        break;

      case FOTA_SWAP_ERASE_CHK:
        /* @Trace: FOTA_SUD_API_00211 */
        memJobResult = Fota_PflsGetJobResult(Fota_MemoryInstance);

        if (memJobResult == MEM_JOB_PENDING)
        {
          retVal  = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else if (memJobResult ==  MEM_JOB_OK)
        {
          indexSwUnit++;
          if (indexSwUnit < FOTA_NUM_OF_SWUNIT)
          {
            swapState = FOTA_SWAP_ERASE;
          }
          else
          {
            swapState = FOTA_SWAP_ERR;
          }
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
          retVal = DCM_E_PENDING;
        }
        else
        {
          #if (FOTA_DEV_ERROR_DETECT == STD_ON)
          /* Report Det Error */
          (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
           FOTA_ROUTINE_CONTROL_CPD_SID, FOTA_E_ERASE_JOB_FAILED);
          #endif
          swapState = FOTA_SWAP_ERR;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
          retVal = DCM_E_PENDING;
        }
        break;

      case FOTA_SWAP_ACTIVATE_KEY_WRITE:
        /* @Trace: FOTA_SUD_API_00212 */
        if(E_OK==Fota_ChkActKey(indexSwUnit,FOTA_TARGET_AREA))
        {
          indexSwUnit++;
          if(indexSwUnit < FOTA_NUM_OF_SWUNIT)
          {
            (void)Fota_GetMemInstanceBySwUnit(indexSwUnit, &Fota_MemoryInstance);
          }
          else
          {
            swapState = FOTA_SWAP_END;
          }
          retVal = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else
        {
          if (E_OK==Fota_SetActKey_Request(FOTA_FLKEY_MGR, indexSwUnit))
          {
            swapState = FOTA_SWAP_ACTIVATE_KEY_WRITE_CHK;
            retVal = DCM_E_PENDING;
            *LpErrorCode = DCM_E_POSITIVERESPONSE;
          }
          else
          {
            swapState = FOTA_SWAP_ERR;
            retVal = DCM_E_PENDING;
          }
        }
        break;


      case FOTA_SWAP_ACTIVATE_KEY_WRITE_CHK:
        /* @Trace: FOTA_SUD_API_00213 */
        setKeyResult = Fota_SetKey_Result();
        if (FOTA_SETMAGICKEY_OK == setKeyResult)
        {
          indexSwUnit++;
          if(indexSwUnit < FOTA_NUM_OF_SWUNIT)
          {
            (void)Fota_GetMemInstanceBySwUnit(indexSwUnit, &Fota_MemoryInstance);
            swapState = FOTA_SWAP_ACTIVATE_KEY_WRITE;
          }
          else
          {
            swapState = FOTA_SWAP_END;
          }
          retVal = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else if (FOTA_SETMAGICKEY_FAILED == setKeyResult)
        {
          swapState = FOTA_SWAP_ERR;
          retVal  = DCM_E_PENDING;
        }
        else
        {
          retVal = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        break;

      case FOTA_SWAP_END:
        /* @Trace: FOTA_SUD_API_00214 */
        *LpErrorCode = DCM_E_POSITIVERESPONSE;
        retVal = E_OK;
        break;

      case FOTA_SWAP_ERR:
      default:
        /* @Trace: FOTA_SUD_API_00215 */
        #if (FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON)
        if (FOTA_TRUE == recoveryAllSwUnit)
        {
          *LpErrorCode = DCM_E_LOWERVERSIONDOWNLOADATTEMPT;
          recoveryAllSwUnit = FOTA_FALSE;
        }
        else
        #endif
        {
          *LpErrorCode = DCM_E_GENERALREJECT;
        }
        retVal = E_NOT_OK;
        break;
    }
  }
  return retVal;
}
#endif /* #if (FOTA_IMPLEMENTATION_RULE == FOTA_OTA_ES98765_02) */

/*******************************************************************************
** Function Name        : Fota_ProcessActivateDualMem                         **
**                                                                            **
** Service ID           : 0x0B                                                **
**                                                                            **
** Description          : Trigger Swap memory service                         **
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
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                                                            **
**                        Function(s) invoked :                               **
*******************************************************************************/
/* @Trace: FOTA_SRS_ES98765_02E_00021 FOTA_SRS_ES98765_02E_00029 FOTA_SRS_ES98765_02E_00033 FOTA_SRS_ES98765_02E_00032 */
/* @Trace: FOTA_SRS_ES98765_02E_00034 FOTA_SRS_ES98765_02E_00036 FOTA_SRS_UDS_00004 FOTA_SRS_UDS_00026 */
#if (FOTA_MCU_MEMORY_ACCESS_TYPE!=FOTA_SINGLE_TYPE)
FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessActivateDualMem
(
  VAR(uint8, AUTOMATIC) InMemArea,
  VAR(uint16, AUTOMATIC) InEcuSwUnit,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
)
{
  /* @Trace: FOTA_SUD_API_00035 */
  VAR(Std_ReturnType,AUTOMATIC) retVal = E_NOT_OK;
  VAR(Mem_76_Pfls_JobResultType, AUTOMATIC) memJobResult;
  VAR(Fota_SetKeyResultType, AUTOMATIC) setKeyResult;
  VAR(Fota_PartitionType,AUTOMATIC) TgtPart=FOTA_PARTITION_UNKNOWN;
  static Fota_SwapStatType swapState = FOTA_SWAP_ERR;
  VAR(Std_ReturnType,AUTOMATIC) retSetKey = E_NOT_OK;
  VAR(Fota_JobResultType,AUTOMATIC) retMacUpdate;
  #if((FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_02) && (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE))
  VAR(uint8, AUTOMATIC) rub_UnUsed;
  #endif

  *LpErrorCode = DCM_E_POSITIVERESPONSE;

  if((OpStatus == DCM_INITIAL)||(OpStatus == DCM_PENDING))
  {
    if(OpStatus == DCM_INITIAL)
    {
      /* @Trace: FOTA_SUD_API_00036 */
      #if(FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_01)
      if (E_OK == Fota_ValidateMemoryArea(InMemArea))
      {
        if(Fota_IsDualPartitionSwUnit(InEcuSwUnit)==E_OK)
        {
          if(Fota_GetTargetPartition(&TgtPart)==E_OK)
          {
            retVal = Fota_GetSwUnitIdByPartition(TgtPart,&Fota_ProgrammingSWUnitId);
          }
          else
          {
            retVal = E_NOT_OK;
          }
        }
        else
        {
          retVal = Fota_GetSwUnitIdByLabel(InEcuSwUnit, &Fota_ProgrammingSWUnitId);
        }
      }
      #elif (FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_02)
      FOTA_UNUSED(InMemArea);
      FOTA_UNUSED(InEcuSwUnit);
      #if (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_NON_MMU_TYPE)
      if (Fota_GetTargetPartition(&TgtPart)==E_OK)
      {
        retVal = Fota_GetSwUnitIdByPartition(TgtPart,&Fota_ProgrammingSWUnitId);
      }
      else
      {
        retVal = E_NOT_OK;
      }
      #else
      FOTA_UNUSED(TgtPart);
      Fota_ProgrammingSWUnitId = FOTA_ZERO;
      retVal = E_OK;
      #endif /* FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_NON_MMU_TYPE */
      #else
      FOTA_UNUSED(TgtPart);
      #endif /* FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_02 */

      /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
      if (E_OK != retVal)
      {
        /* Server shall respond NRC 31 */
        *LpErrorCode = DCM_E_REQUESTOUTOFRANGE;
        swapState = FOTA_SWAP_ERR;
        #if (FOTA_DEV_ERROR_DETECT == STD_ON)
        /* Report Det Error */
        (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
          FOTA_ROUTINE_CONTROL_CPD_SID, FOTA_E_BLOCKID_INVALID);
        #endif
      }
      else
      {
        (void)Fota_GetMemInstanceBySwUnit(Fota_ProgrammingSWUnitId, &Fota_MemoryInstance);

        #if (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)
        (void)Fota_PflsTgtAreaSet(Fota_MemoryInstance,FOTA_ALT_ADDR);
        #endif

        #if (FOTA_DOWN_GRADE_PROTECTION_USED == FOTA_STD_ON)
        if(Fota_DualMemDownGradeChk_Callout()==E_OK)
        #endif
        {
          if(Fota_DualMemSwUnitsVerDependChk_Callout()==E_OK)
          {
            swapState = FOTA_SWAP_VERIFY_KEY_CHK;
          }
          else
          {
            swapState = FOTA_SWAP_ERR;
          }
        }
        #if (FOTA_DOWN_GRADE_PROTECTION_USED == FOTA_STD_ON)
        else
        {
          swapState = FOTA_SWAP_ERASE;
        }
        #endif
        /* polyspace-begin MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
        retVal = DCM_E_PENDING;
        /* polyspace-end MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
        *LpErrorCode = DCM_E_POSITIVERESPONSE;
      }
      /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
    }

    switch(swapState)
    {
      case FOTA_SWAP_VERIFY_KEY_CHK:
        /* @Trace: FOTA_SUD_API_00037 */
        #if((FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_02)&&(FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)) /* MMU Type and 2ndGen */
        if(E_OK==Fota_ChkVfyKeyAllSwUnit(FOTA_TARGET_AREA))
        #else
        if (E_OK==Fota_ChkVfyKey(Fota_ProgrammingSWUnitId,FOTA_TARGET_AREA))
        #endif
        {
          swapState = FOTA_SWAP_ACTIVATE_KEY_WRITE;
          retVal = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else
        {
          swapState = FOTA_SWAP_ERR;
          retVal = DCM_E_PENDING;
        }
        break;

      case FOTA_SWAP_ACTIVATE_KEY_WRITE:
        /* @Trace: FOTA_SUD_API_00216 */
        #if(FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_NON_MMU_TYPE)

        retSetKey=Fota_SetTopPrioActKey_Request(FOTA_FLKEY_MGR, Fota_ProgrammingSWUnitId);

        if(retSetKey==E_OK)
        {
          swapState = FOTA_SWAP_ACTIVATE_KEY_WRITE_CHK;
          retVal = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else
        {
          if(retSetKey==FOTA_E_NOT_OK_STORIGE_FULL)
          {
            swapState = FOTA_SWAP_ERR_CNT_OVER;
            retVal = DCM_E_PENDING;
          }
          else
          {
            swapState = FOTA_SWAP_ERR;
            retVal = DCM_E_PENDING;
          }
        }
        #else
        #if(FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_02)
        if (E_OK == Fota_ChkActKey(Fota_ProgrammingSWUnitId,FOTA_TARGET_AREA))
        {
          Fota_ProgrammingSWUnitId++;
          if (Fota_ProgrammingSWUnitId < FOTA_NUM_OF_SWUNIT)
          {
            (void)Fota_GetMemInstanceBySwUnit(Fota_ProgrammingSWUnitId, &Fota_MemoryInstance);
          }
          else
          {
            if(Fota_GetSoftwareModuleBlkBySwType(FOTA_FBL_TYPE,&rub_UnUsed)==E_OK)
            {
              swapState = FOTA_SWAP_SECURE_BOOT_MAC_UPDATE;
            }
            else
            {
              swapState = FOTA_SWAP_CMD;
            }

          }
          retVal = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else

        #endif
        {
          retSetKey=Fota_SetActKey_Request(FOTA_FLKEY_MGR, Fota_ProgrammingSWUnitId);

          if(retSetKey==E_OK)
          {
            swapState = FOTA_SWAP_ACTIVATE_KEY_WRITE_CHK;
            retVal = DCM_E_PENDING;
            *LpErrorCode = DCM_E_POSITIVERESPONSE;
          }
          else
          {
            swapState = FOTA_SWAP_ERR;
            retVal = DCM_E_PENDING;
          }
        }
        #endif
        break;

      case FOTA_SWAP_ACTIVATE_KEY_WRITE_CHK:
        /* @Trace: FOTA_SUD_API_00217 */
        setKeyResult = Fota_SetKey_Result();
        if (FOTA_SETMAGICKEY_OK == setKeyResult)
        {
          #if((FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_02) && (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE))
          Fota_ProgrammingSWUnitId++;
          if (Fota_ProgrammingSWUnitId < FOTA_NUM_OF_SWUNIT)
          {
            (void)Fota_GetMemInstanceBySwUnit(Fota_ProgrammingSWUnitId, &Fota_MemoryInstance);

            #if (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)
            (void)Fota_PflsTgtAreaSet(Fota_MemoryInstance,FOTA_ALT_ADDR);
            #endif

            swapState = FOTA_SWAP_ACTIVATE_KEY_WRITE;
          }
          else
          {
            if (Fota_GetSoftwareModuleBlkBySwType(FOTA_FBL_TYPE, &rub_UnUsed)==E_OK)
            {
              swapState = FOTA_SWAP_SECURE_BOOT_MAC_UPDATE;
            }
            else
            {
              swapState = FOTA_SWAP_CMD;
            }
          }
          #else
          {
            swapState = FOTA_SWAP_CMD;
          }
          #endif
          retVal = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else if (FOTA_SETMAGICKEY_FAILED == setKeyResult)
        {
          swapState = FOTA_SWAP_ERR;
          retVal  = DCM_E_PENDING;
        }
        else
        {
          retVal = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        break;

      /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the MCU." */
      case FOTA_SWAP_SECURE_BOOT_MAC_UPDATE:
        /* @Trace: FOTA_SUD_API_00218 */
        if(Fota_MacUpdateRequest()==E_OK)
        {
          swapState = FOTA_SWAP_SECURE_BOOT_MAC_UPDATE_CHK;
        }
        else
        {
          swapState = FOTA_SWAP_ERR;
        }

        retVal  = DCM_E_PENDING;
      break;

      case FOTA_SWAP_SECURE_BOOT_MAC_UPDATE_CHK:
        /* @Trace: FOTA_SUD_API_00219 */
        retMacUpdate=Fota_MacUpdateResult();

        if(retMacUpdate==FOTA_JOB_OK)
        {
          swapState = FOTA_SWAP_CMD;
        }
        else if(retMacUpdate==FOTA_JOB_FAILED)
        {
          swapState = FOTA_SWAP_ERR;
        }
        else
        {
          /* Do Nothing */
        }
        retVal  = DCM_E_PENDING;

        break;
      /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the MCU." */

      case FOTA_SWAP_CMD:
        /* @Trace: FOTA_SUD_API_00220 */
        if(E_OK == Fota_PflsSwapBankRequest())
        {
          swapState = FOTA_SWAP_CMD_CHK;
          retVal  = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else
        {
          swapState = FOTA_SWAP_ERR;
          retVal  = DCM_E_PENDING;
        }
        break;

      case FOTA_SWAP_CMD_CHK:
        /* @Trace: FOTA_SUD_API_00221 */
        memJobResult = Fota_PflsGetJobResult(FOTA_PFLS_INT_ZERO);
        if (MEM_JOB_OK == memJobResult)
        {
          swapState = FOTA_SWAP_END;
          retVal  = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else if (MEM_JOB_FAILED == memJobResult)
        {
          swapState = FOTA_SWAP_ERR;
          retVal  = DCM_E_PENDING;
        }
        else
        {
          retVal = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        break;

      case FOTA_SWAP_ERASE:
        /* @Trace: FOTA_SUD_API_00222 */
        #if (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE) /* MMU Dual */

        (void)Fota_PflsTgtAreaSet(Fota_MemoryInstance,FOTA_ALT_ADDR);

        #else

        (void)Fota_PflsTgtAreaSet(Fota_MemoryInstance,FOTA_STD_ADDR);

        #endif

        if (E_OK == Fota_PflsEraseRequest(
                  Fota_MemoryInstance,
                  Fota_Gast_SwUnitTable[Fota_ProgrammingSWUnitId].StartAddress,
                  Fota_Gast_SwUnitTable[Fota_ProgrammingSWUnitId].EndAddress - Fota_Gast_SwUnitTable[Fota_ProgrammingSWUnitId].StartAddress + 1))
        {
          swapState  = FOTA_SWAP_ERASE_CHK;
          retVal     = DCM_E_PENDING;
        }
        else
        {
          swapState = FOTA_SWAP_ERR_VERSION;
          retVal = DCM_E_PENDING;
        }

        break;

      case FOTA_SWAP_ERASE_CHK:
        /* @Trace: FOTA_SUD_API_00223 */
        memJobResult = Fota_PflsGetJobResult(Fota_MemoryInstance);

        if(memJobResult == MEM_JOB_PENDING)
        {
          retVal  = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else if (memJobResult ==  MEM_JOB_OK)
        {
          #if ((FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE) && (FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_02))/* MMU Dual */

          /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the Configuration." */
          if(Fota_ProgrammingSWUnitId >= (FOTA_NUM_OF_SWUNIT-FOTA_ONE))
          {
            Fota_ProgrammingSWUnitId=FOTA_ZERO;
            swapState = FOTA_SWAP_ERR_VERSION;
            retVal = DCM_E_PENDING;
          }
          else
          {
            Fota_ProgrammingSWUnitId++;
            swapState = FOTA_SWAP_ERASE;
            retVal = DCM_E_PENDING;
          }
          /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the Configuration." */

          #else

          swapState = FOTA_SWAP_ERR_VERSION;
          retVal = DCM_E_PENDING;

          #endif

        }
        else
        {
          swapState = FOTA_SWAP_ERR_VERSION;
          retVal = DCM_E_PENDING;
        }

        break;
      case FOTA_SWAP_END:
        /* @Trace: FOTA_SUD_API_00224 */
        *LpErrorCode = DCM_E_POSITIVERESPONSE;
        retVal = E_OK;

        break;

      case FOTA_SWAP_ERR_VERSION:
        /* @Trace: FOTA_SUD_API_00225 */
        *LpErrorCode = DCM_E_LOWERVERSIONDOWNLOADATTEMPT;
        retVal = E_NOT_OK;

        break;

      case FOTA_SWAP_ERR_CNT_OVER:
        /* @Trace: FOTA_SUD_API_00226 */
        *LpErrorCode = DCM_E_GENERALPROGRAMMINGFAILURE;
        retVal = E_NOT_OK;

        break;

      case FOTA_SWAP_ERR:
      default:
        /* @Trace: FOTA_SUD_API_00227 */
        /* polyspace-begin MISRA-C3:14.3 [Justified:Low] "No Impact of this rule violation" */
        if (DCM_E_POSITIVERESPONSE == *LpErrorCode)
        {
          *LpErrorCode = DCM_E_GENERALREJECT;
        }
        else
        {
          /* Do nothing */
        }
        /* polyspace-end MISRA-C3:14.3 [Justified:Low] "No Impact of this rule violation" */
        retVal = E_NOT_OK;
        break;
    }
  }
  return retVal;
}
#endif /* #if (FOTA_MCU_MEMORY_ACCESS_TYPE!=FOTA_SINGLE_TYPE) */
/*******************************************************************************
** Function Name        : Fota_ProcessEraseTargetArea                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Server Function in the Client-Server Port Comm      **
**                        DCM Call this to erase target area (RID = 0x0212)   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus,                                           **
**                                                                            **
**                                                                            **
**                                                                            **
** InOut parameter      :                                                     **
**                                                                            **
** Output Parameters    :                                                     **
**                                                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: FOTA_SRS_UDS_00003 FOTA_SRS_UDS_00013 FOTA_SRS_ES98765_02E_00019 FOTA_SRS_UDS_00024 */
/* @Trace: FOTA_SRS_ES98765_02E_00033 FOTA_SRS_GENSEC_00007 FOTA_SRS_UDS_00001 */

FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessEraseTargetArea
(
  VAR(uint8, AUTOMATIC) InMemArea,
  VAR(uint16, AUTOMATIC) InEcuSwUnit,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpOut_MemoryArea,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
)
{
  VAR(Std_ReturnType,AUTOMATIC) retVal = E_NOT_OK;
  VAR(uint32,AUTOMATIC) startAddress;
  VAR(uint32,AUTOMATIC) eraseLen;

  VAR(Mem_76_Pfls_JobResultType,AUTOMATIC) ren_CodeEraseReport;
  P2VAR(Fota_FirmwareType, AUTOMATIC, FOTA_APPL_DATA) firmwareInfoPtr;
  P2CONST(Fota_SwModule, AUTOMATIC, FOTA_APPL_CONST) swUnitHandlePtr;
  static VAR(Fota_PartitionType,AUTOMATIC) TgtPart;
  #if ((FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE) &&\
       (FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_02))
  VAR(Fota_JobResultType,AUTOMATIC) rue_SyncJobResult;
  #endif

  static VAR(Fota_EraseStatType,AUTOMATIC) eraseState = FOTA_ERASE_ERR;

  #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
    (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
  VAR(uint32,AUTOMATIC) blkTrailerAddress;
  Fota_JobResultType versionCheckResult;
  #endif

  *LpErrorCode = DCM_E_GENERALREJECT;

  if (OpStatus == DCM_INITIAL)
  {
    /* @Trace: FOTA_SUD_API_00045 */
    TgtPart = FOTA_PARTITION_UNKNOWN;
    #if ((FOTA_MCU_MEMORY_ACCESS_TYPE!=FOTA_SINGLE_TYPE) &&\
      (FOTA_IMPLEMENTATION_RULE == FOTA_OTA_ES98765_01))
    retVal = Fota_ValidateMemoryArea(InMemArea);
    #else
    FOTA_UNUSED(InMemArea);
    retVal = E_OK;
    #endif

    /* polyspace-begin MISRA-C3:14.3 [Justified:Low] "if-condition depends on the configuration." */
    if (E_OK == retVal)
    {
      #if(FOTA_MCU_MEMORY_ACCESS_TYPE!=FOTA_SINGLE_TYPE)
      if(Fota_IsDualPartitionSwUnit(InEcuSwUnit)==E_OK)
      {
        if(Fota_GetTargetPartition(&TgtPart)==E_OK)
        {
          retVal = Fota_GetSwUnitIdByPartition(TgtPart,&Fota_ProgrammingSWUnitId);
        }
        else
        {
          retVal = E_NOT_OK;
        }
      }
      else
      #else
      FOTA_UNUSED(TgtPart);
      #endif
      {
        retVal = Fota_GetSwUnitIdByLabel(InEcuSwUnit, &Fota_ProgrammingSWUnitId);
      }
      (void)Fota_GetMemInstanceBySwUnit(Fota_ProgrammingSWUnitId, &Fota_MemoryInstance);
      (void)Fota_PflsGetFlashAlignment(Fota_MemoryInstance, &Fota_PflsWriteAlignmentValue);
    }
    /* polyspace-end MISRA-C3:14.3 [Justified:Low] "if-condition depends on the configuration." */

    if (E_OK != retVal)
    {
      /* Server shall respond NRC 31 */
      *LpErrorCode = DCM_E_REQUESTOUTOFRANGE;
      #if (FOTA_DEV_ERROR_DETECT == STD_ON)
      /* Report Det Error */
      (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
      FOTA_ERASE_MEMORY_SID, FOTA_E_BLOCKID_INVALID);
      #endif
    }
    else
    {
      /* set the erase state to be FOTA_ERASE_CMD */
      #if ((FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE) &&\
        (FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_02))

      /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
      if(FOTA_NUM_OF_SWUNIT>FOTA_ONE)
      {
        eraseState = FOTA_ERASE_RESYNC_REQUEST;
      }
      else
      {
        eraseState = FOTA_ERASE_CMD;
      }
      /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */

      #else
        #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
          (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
        retVal = Fota_SvcInit(Fota_ProgrammingSWUnitId);
        if (E_OK == retVal)
        {
          #if (FOTA_IMPLEMENTATION_RULE == FOTA_OTA_ES98765_02)
          if (Fota_SvcResultAllSwUnit[Fota_ProgrammingSWUnitId].CheckVersion ==
                                                            FOTA_VERSION_USED)
          #endif
          {
            eraseState = FOTA_ERASE_VERSION_CHECK_REQUEST;
          }
          #if (FOTA_IMPLEMENTATION_RULE == FOTA_OTA_ES98765_02)
          else
          {
            eraseState = FOTA_ERASE_CMD;
          }
          #endif
        }
        else
        {
          eraseState = FOTA_ERASE_ERR_VERSION;
        }
        #else
        eraseState = FOTA_ERASE_CMD;
        #endif
      #endif
      retVal = DCM_E_FORCE_RCRRP;
    }
  }
  else if ((OpStatus == DCM_FORCE_RCRRP_OK) || (OpStatus == DCM_PENDING))
  {
    switch (eraseState)
    {
      #if ((FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE) &&\
        (FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_02))

      case FOTA_ERASE_RESYNC_REQUEST:
        /* @Trace: FOTA_SUD_API_00046 */
        /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
        if(Fota_AreaSyncRequest(FOTA_SYNC_VERIFIED_NONACT_SWUNIT)==E_OK)
        {
          eraseState = FOTA_ERASE_RESYNC_RESULT;
          retVal     = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else
        {
            eraseState = FOTA_ERASE_ERR;
            retVal     = DCM_E_PENDING;
        }
        /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */

        break;

      case FOTA_ERASE_RESYNC_RESULT:
        /* @Trace: FOTA_SUD_API_00228 */
        rue_SyncJobResult = Fota_AreaSyncResult();

        /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
        if(rue_SyncJobResult==FOTA_JOB_OK)
        {
            eraseState = FOTA_ERASE_CMD;
            retVal = DCM_E_PENDING;
            *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else if(rue_SyncJobResult==FOTA_JOB_PENDING)
        {
          retVal = DCM_E_PENDING;
            *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else
        {
            eraseState = FOTA_ERASE_ERR;
            retVal     = DCM_E_PENDING;
        }
        break;
      #endif

      #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
        (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
      case FOTA_ERASE_VERSION_CHECK_REQUEST:
        /* @Trace: FOTA_SUD_API_00229 */
        Fota_VersionCheckRequest(
                            FOTA_VERSION_CHECK_BEFORE_ERASE_REQUEST, FOTA_ZERO);
        Fota_State = FOTA_VERSION_CHECK_PROCESSING;
        eraseState = FOTA_ERASE_VERSION_CHECK_RESULT;
        retVal     = DCM_E_PENDING;
        *LpErrorCode = DCM_E_POSITIVERESPONSE;
        break;

      case FOTA_ERASE_VERSION_CHECK_RESULT:
        /* @Trace: FOTA_SUD_API_00230 */
        versionCheckResult = Fota_VersionCheckResult();
        if (FOTA_JOB_PENDING == versionCheckResult)
        {
          retVal  = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else if (FOTA_JOB_OK == versionCheckResult)
        {
          Fota_State = FOTA_READY;
          eraseState = FOTA_ERASE_CMD;
          retVal     = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else if (FOTA_JOB_FAILED == versionCheckResult)
        {
          eraseState = FOTA_ERASE_ERR_VERSION;
          retVal     = DCM_E_PENDING;
          #if (FOTA_DEV_ERROR_DETECT == STD_ON)
          /* Report Det Error */
          (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
            FOTA_ERASE_MEMORY_SID, FOTA_E_SVC_ERASE_CHECK_FAILED);
          #endif
        }
        else
        {
          /* Do Nothing */
        }
        break;
      #endif

      case FOTA_ERASE_CMD:
        /* @Trace: FOTA_SUD_API_00231 */
        swUnitHandlePtr = &Fota_Gast_SwUnitTable[Fota_ProgrammingSWUnitId];
        #if (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)
        (void)Fota_PflsTgtAreaSet(Fota_MemoryInstance, FOTA_ALT_ADDR);
        #endif
        /* get start address for erase operation  */
        startAddress = swUnitHandlePtr->StartAddress;
        /* memory length to be erased   */
        eraseLen = swUnitHandlePtr->EndAddress - swUnitHandlePtr->StartAddress + FOTA_ONE;

        firmwareInfoPtr = swUnitHandlePtr->FirmwareInfoPtr;

        if (NULL_PTR != firmwareInfoPtr)
        {
          #if (FOTA_STD_ON == FOTA_SF20_ENABLE)
          Fota_MetaDataRequestCheck = FOTA_FALSE;
          #endif
          BlockProcessingRulePtr = firmwareInfoPtr->FwBlockProcessingInfo;
        }
        #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
          (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
        #if (FOTA_IMPLEMENTATION_RULE == FOTA_OTA_ES98765_02)
        if (Fota_SvcResultAllSwUnit[Fota_ProgrammingSWUnitId].CheckVersion ==
                                                          FOTA_VERSION_USED)
        #endif
        {
          blkTrailerAddress =
            Fota_Gast_SwUnitTable[Fota_ProgrammingSWUnitId].BlkTrailerAddress;

          if ((swUnitHandlePtr->StartAddress + eraseLen) > blkTrailerAddress)
          {

            retVal = Fota_PflsGetSectorSize(Fota_MemoryInstance, &Fota_PflsEraseAlignmentValue,
                                   blkTrailerAddress);
            if (E_OK == retVal)
            {
              /* Erase memory without trailer area */
              eraseLen = (blkTrailerAddress - (blkTrailerAddress %
                Fota_PflsEraseAlignmentValue)) - swUnitHandlePtr->StartAddress;
            }
            else
            {
              eraseState = FOTA_ERASE_ERR_VERSION;
              retVal     = DCM_E_PENDING;
            }
          }
          else
          {
            #if (FOTA_DEV_ERROR_DETECT == STD_ON)
            /* Report Det Error */
            (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
              FOTA_ERASE_MEMORY_SID, FOTA_E_SVC_ERASE_LENGTH_INVALID);
            #endif
            eraseState = FOTA_ERASE_ERR_VERSION;
            retVal     = DCM_E_PENDING;
          }
        }
        #if (FOTA_IMPLEMENTATION_RULE == FOTA_OTA_ES98765_02)
        else
        {
          retVal = E_OK;
        }
        #endif
        if (E_OK == retVal)
        #endif
        {
          retVal = Fota_ValidateAddressLengthAlignment(startAddress, eraseLen,
                                                         FOTA_ERASE_ACCESS_TYPE);
          if (E_OK == retVal)
          {
            if (E_OK == Fota_PflsEraseRequest(\
                  Fota_MemoryInstance, \
                  startAddress, \
                  eraseLen))
            {
            eraseState = FOTA_ERASE_CHK;
            retVal     = DCM_E_PENDING;
            *LpErrorCode = DCM_E_POSITIVERESPONSE;
            }
            else
            {
            eraseState = FOTA_ERASE_ERR;
            retVal     = DCM_E_PENDING;
            }
          }
          else
          {
            eraseState = FOTA_ERASE_ERR;
            retVal     = DCM_E_PENDING;
          }
        }

        break;

      case FOTA_ERASE_CHK:
      /* @Trace: FOTA_SUD_API_00047 */
      ren_CodeEraseReport = Fota_PflsGetJobResult(Fota_MemoryInstance);

      if(ren_CodeEraseReport == MEM_JOB_PENDING)
      {
        /* Time for erase one sector in Chorus 10M is long (~1s)
         * => need return DCM_E_FORCE_RCRRP for transmit a pending response NRC78 to tester
         * this probelm is not occurn in RTSW due to task is managed by interrupt */
        #if (((FOTA_MODE == FOTA_FBL_MODE) && (FOTA_MCU_MEMORY_ACCESS_TYPE != FOTA_MMU_TYPE)) \
         && (FOTA_LARGE_SECTOR == STD_ON))
        retVal  = DCM_E_FORCE_RCRRP;
        #else
        retVal = DCM_E_PENDING;
        #endif
        *LpErrorCode = DCM_E_POSITIVERESPONSE;
      }
      else if(ren_CodeEraseReport==MEM_JOB_OK)
      {
        eraseState = FOTA_ERASE_END;
        retVal = DCM_E_PENDING;
        *LpErrorCode = DCM_E_POSITIVERESPONSE;
      }
      else
      {
        eraseState = FOTA_ERASE_ERR;
        retVal = DCM_E_PENDING;
      }
      break;

      case FOTA_ERASE_END:
      /* @Trace: FOTA_SUD_API_00048 */
      #if(FOTA_IMPLEMENTATION_RULE==FOTA_OTA_ES98765_02)
      if(TgtPart==FOTA_PARTITION_A)
      {
        LpOut_MemoryArea[FOTA_ZERO] = (uint8)FOTA_AREA_A;
      }
      else if(TgtPart==FOTA_PARTITION_B)
      {
        LpOut_MemoryArea[FOTA_ZERO] = (uint8)FOTA_AREA_B;
      }
      else
      {
        LpOut_MemoryArea[FOTA_ZERO] = (uint8)FOTA_AREA_UNKNOWN;
      }
      #else
        FOTA_UNUSED(LpOut_MemoryArea);
      #endif

      *LpErrorCode = DCM_E_POSITIVERESPONSE;
      Fota_State = FOTA_INIT;
      retVal = E_OK;
      break;

      #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
        (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
      case FOTA_ERASE_ERR_VERSION:
        /* @Trace: FOTA_SUD_API_00049 */
        *LpErrorCode = DCM_E_LOWERVERSIONDOWNLOADATTEMPT;
        retVal = E_NOT_OK;
      break;
      #endif

      case FOTA_ERASE_ERR:
      default :
      /* @Trace: FOTA_SUD_API_00232 */
      *LpErrorCode = DCM_E_GENERALREJECT;
      retVal = E_NOT_OK;

      break;
    }
  }
  /* @Trace: FOTA_SUD_API_00050 */
  else if (OpStatus == DCM_CANCEL)
  {
    (void)Fota_PflsCancelReq(Fota_MemoryInstance);
    retVal = DCM_WRITE_FAILED;
  }
  else
  {
    retVal = DCM_WRITE_FAILED;
  }

  return retVal;
}
/*******************************************************************************
** Function Name        : Fota_ProcessRequestDownload                         **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : DCM CallOut function call this to request download  **
**                                                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, DataFormatIdentifier,                     **
**                        MemoryAddress, MemorySize                           **
**                                                                            **
**                                                                            **
** InOut parameter      :                                                     **
**                                                                            **
** Output Parameters    : LpBlockLength, LpNegativeErrorCode                  **
**                                                                            **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: FOTA_SRS_ES95489_52E_00004 FOTA_SRS_ES95489_52E_00005 FOTA_SRS_ES95489_52E_00006 FOTA_SRS_UDS_00006 FOTA_SRS_ES98765_01E_00005*/
/* @Trace: FOTA_SRS_ES98765_02E_00024 FOTA_SRS_ES98765_01E_00011 FOTA_SRS_ES98765_01E_00012 FOTA_SRS_ES98765_01E_00013 */
/* @Trace: FOTA_SRS_ES98765_01E_00006 FOTA_SRS_ES98765_02E_00025 FOTA_SRS_ES98765_02E_00026 FOTA_SRS_ES98765_02E_00039 FOTA_SRS_UDS_00014 */
#if (FOTA_MODE == FOTA_FBL_MODE) || (FOTA_MODE == FOTA_APP_MODE)
FUNC(Std_ReturnType, FOTA_CODE) Fota_ProcessRequestDownload
(
  Dcm_OpStatusType OpStatus,
  uint8 DataFormatIdentifier,
  uint32 MemoryAddress,
  uint32 MemorySize,
  P2VAR(uint32, AUTOMATIC, FOTA_PRIVATE_DATA) LpBlockLength,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
)
{
  Std_ReturnType retVal = E_NOT_OK;
  #if (FOTA_STD_ON == FOTA_SF20_ENABLE)
  uint32 decryptionJobId;
  uint32 decryptionLen = FOTA_TP_BLOCK_LENGTH;
  #endif
  *(LpBlockLength) = FOTA_TP_BLOCK_LENGTH;
  Fota_Write.rul_BlockType = FOTA_UNKNOWN;

  FOTA_UNUSED(DataFormatIdentifier);

  if ((OpStatus == DCM_INITIAL) || (OpStatus == DCM_PENDING))
  {
    if ((Fota_State==FOTA_INIT) || (Fota_State==FOTA_READY))
    {
      Fota_Retransfer.TDataAfterReq = STD_ON;

      #if (FOTA_STD_ON == FOTA_SF20_ENABLE)
      if (FOTA_TRUE == Fota_CheckMetadataArea(MemoryAddress))
      {
        /* @Trace: FOTA_SUD_API_00067 */
        if (FOTA_TRUE == Fota_CheckMetadataSize(MemorySize))
        {
          if (FOTA_TRUE == Fota_SecureFlashDecryptOn)
          {
            decryptionJobId =
              BlockProcessingRulePtr[Fota_ProgrammingFwBlockId].DecryptJobId;
            if(Fota_DecryptFinish(FOTA_REQUEST_DOWNLOAD_SID, decryptionJobId,
                      &Lau8_DecryptedBuffer[0], &decryptionLen) == E_OK)
            {
               retVal = E_OK;
            }
            else
            {
              *LpErrorCode = DCM_E_CONDITIONSNOTCORRECT;
              retVal = E_NOT_OK;
            }
          }
          else
          {
            retVal = E_OK;
          }
          Fota_Write.rul_BlockType = FOTA_METADATA;
          Fota_ProgrammingFwBlockId = 0xFF;
          Fota_PreviousFwBlockId = 0;
          Fota_MetaDataRequestCheck = FOTA_TRUE;
        }
        else
        {
          *LpErrorCode = DCM_E_REQUESTOUTOFRANGE;
          retVal=E_NOT_OK;
        }
      }
      else
      #endif /* (FOTA_STD_ON == FOTA_SF20_ENABLE) */
      /* @Trace: FOTA_SUD_API_00068 */
      if (FOTA_TRUE == Fota_CheckFwBlockArea(MemoryAddress))
      {
        Fota_Write.rul_BlockType = FOTA_FIRMWARE;
        retVal = E_OK;

        #if (FOTA_STD_ON == FOTA_SF20_ENABLE)
        if (Fota_PreviousFwBlockId != Fota_ProgrammingFwBlockId)
        {
          /* This data chunk belong to another Fw block. Check whether a
            decryption flow is on-going. */
          if (FOTA_TRUE == BlockProcessingRulePtr[\
                            Fota_ProgrammingFwBlockId].IsEncrypted)
          {
            if (FOTA_TRUE == Fota_MetaDataRequestCheck)
            {
              if (FOTA_TRUE == Fota_SecureFlashDecryptOn)
              {
                /* Previous Fw block decryption is on-going. Check whether new
                  Fw block belong to a different decryption flow. */
                if (BlockProcessingRulePtr[Fota_PreviousFwBlockId].DecryptJobId !=
                  BlockProcessingRulePtr[Fota_ProgrammingFwBlockId].DecryptJobId)
                {
                  /* Change of decryption job between Fw block detected. Finish
                    the previous flow before starting a new one. */
                  decryptionJobId =
                    BlockProcessingRulePtr[Fota_PreviousFwBlockId].DecryptJobId;
                  if(Fota_DecryptFinish(FOTA_REQUEST_DOWNLOAD_SID, decryptionJobId,
                                     &Lau8_DecryptedBuffer[0], &decryptionLen) == E_OK)
                  {
                    decryptionJobId =
                      BlockProcessingRulePtr[Fota_ProgrammingFwBlockId].DecryptJobId;
                    if(Fota_DecryptStart(decryptionJobId) == E_OK)
                    {
                      retVal = E_OK;
                    }
                    else
                    {
                      *LpErrorCode = DCM_E_CONDITIONSNOTCORRECT;
                      retVal = E_NOT_OK;
                    }
                  }
                  else
                  {
                    *LpErrorCode = DCM_E_CONDITIONSNOTCORRECT;
                    retVal = E_NOT_OK;
                  }
                }
                else
                {
                  /* The next Fw block still belong to the same encryption job
                    with previous Fw block. No need to alter decryption flow. */
                }
              }
              else
              {
                /* No previous decryption job is on-going. Check if new Fw block
                  needs decryption so start a new decryption flow.*/
                if(Fota_DecryptStart(BlockProcessingRulePtr[\
                              Fota_ProgrammingFwBlockId].DecryptJobId) == E_OK)
                {
                  retVal = E_OK;
                }
                else
                {
                  *LpErrorCode = DCM_E_CONDITIONSNOTCORRECT;
                  retVal = E_NOT_OK;
                }
              }
            }
            else
            {
              *LpErrorCode = DCM_E_CONDITIONSNOTCORRECT;
              retVal = E_NOT_OK;
            }
          }
          else
          {
        	  /* Do nothing */
          }
        }
        else
        {
          /* This data chunk belong to the same Fw block. Keep current
            block processing rule. */
          if (FOTA_TRUE == BlockProcessingRulePtr[\
                            Fota_ProgrammingFwBlockId].IsEncrypted)
          {
            if (FOTA_TRUE == Fota_MetaDataRequestCheck)
            {
          	  /* Do nothing */
            }
            else
            {
              *LpErrorCode = DCM_E_CONDITIONSNOTCORRECT;
              retVal = E_NOT_OK;
            }
          }
        }
        #endif
      }
      else if (FOTA_TRUE == Fota_CheckAddressIsSignatureArea(MemoryAddress))
      {
        if (MemorySize == FOTA_SIGNATURE_BLOCK_LENGTH)
        {
          Fota_Write.rul_BlockType = FOTA_SIGNATURE;
          retVal = E_OK;
        }
        else
        {
          *LpErrorCode = DCM_E_REQUESTOUTOFRANGE;
          retVal = E_NOT_OK;
        }
      }
      else
      {
        retVal = E_NOT_OK;
        *(LpErrorCode) = DCM_E_REQUESTOUTOFRANGE;
        #if (FOTA_DEV_ERROR_DETECT == STD_ON)
        /* Report Det Error */
        (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
          FOTA_REQUEST_DOWNLOAD_SID, FOTA_E_ADDRESS_LENGTH_INVALID);
        #endif
      }

      if(retVal==E_OK)
      {
        Fota_Write.rul_StartAddPhy = MemoryAddress;
        Fota_Write.rul_WriteAddPhy = MemoryAddress;
        Fota_Write.rul_TotalLen    = MemorySize;
        Fota_Write.rul_Writelen = 0UL;     /* Transfer Data will be set this */
        Fota_Write.rul_TotalWrittenlen = 0UL;

        retVal = E_OK;
        Fota_State = FOTA_WAIT;
        *(LpErrorCode) = DCM_E_POSITIVERESPONSE;
      }
    }
    else
    {
       retVal = E_NOT_OK;
    }
  }
  /* @Trace: FOTA_SUD_API_00069 */
  else if (OpStatus == DCM_CANCEL)
  {
    retVal = E_NOT_OK;
  }
  else if (OpStatus == DCM_FORCE_RCRRP_OK)
  {
    retVal = E_NOT_OK;
  }
  else
  {
    retVal = E_NOT_OK;
  }

  return retVal;
}
#endif
/*******************************************************************************
** Function Name        : Fota_ProcessTransferDataWrite                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : DCM CallOut function call this to transfer data     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, MemoryIdentifier, MemoryAddress           **
**                        MemoryWriteLen, pWriteData                          **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : Dcm_ReturnWriteMemoryType                           **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Fota_State                    **
**                                              Fota_SvcResultAllSwUnit       **
**                                              Fota_ProgrammingSWUnitId      **
**                                              Fota_VersionStatus            **
**                                              Fota_Gast_SwUnitTable         **
**                                              Fota_Retransfer               **
**                                              Fota_Write                    **
**                                              Fota_PflsWriteAlignmentValue  **
**                                              Lau8_SignedBuffer             **
**                                              Fota_Retransfer               **
**                                                                            **
**                        Function(s) invoked :      Fota_VersionCheckRequest **
**                                                    Fota_VersionCheckResult **
**                                                      (void)Det_ReportError **
**                                                                            **
*******************************************************************************/

/* @Trace: FOTA_SRS_UDS_00007 FOTA_SRS_ES98765_02E_00033 FOTA_SRS_GENSEC_00007 FOTA_SRS_GENSEC_00012 */
/* @Trace: FOTA_SRS_GENSEC_00010 FOTA_SRS_GENSEC_00014 FOTA_SRS_ES95489_52E_00004 FOTA_SRS_ES95489_52E_00005 */
/* @Trace: FOTA_SRS_ES95489_52E_00006 FOTA_SRS_ES98765_01E_00004 FOTA_SRS_ES98765_02E_00023 FOTA_SRS_ES98765_02E_00018 */

#if (FOTA_MODE == FOTA_FBL_MODE) || (FOTA_MODE == FOTA_APP_MODE)
FUNC(Dcm_ReturnWriteMemoryType, FOTA_CODE) Fota_ProcessTransferDataWrite
(
  Dcm_OpStatusType OpStatus,
  uint8 MemoryIdentifier /* Not Supported Argument */,
  uint32 MemoryAddress,
  uint32 MemoryWriteLen,
  P2CONST(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) pWriteData
)
{
  Dcm_ReturnWriteMemoryType retVal = DCM_WRITE_FAILED;
  uint32 remainingForMemAlign;
  static Fota_DownloadStatType downloadState = FOTA_DOWNLOAD_NORMAL;
  #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
    (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
  Fota_JobResultType versionCheckResult;
  #endif

  FOTA_UNUSED(MemoryIdentifier);

  if (OpStatus == DCM_INITIAL)
  {
    /* @Trace: FOTA_SUD_API_00076 */
    if (Fota_State==FOTA_WAIT) /* Fota job check */
    {
      #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
        (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
      #if (FOTA_IMPLEMENTATION_RULE == FOTA_OTA_ES98765_02)
      if (Fota_SvcResultAllSwUnit[Fota_ProgrammingSWUnitId].CheckVersion ==
                                                        FOTA_VERSION_USED)
      #endif
      {
        if (Fota_VersionStatus == FOTA_VERSION_INIT)
        {
          if (MemoryAddress >= (Fota_Gast_SwUnitTable[
            Fota_ProgrammingSWUnitId].BlkHeaderAddress + FOTA_BLK_TOTAL_LENGTH))
          {
            downloadState = FOTA_DOWNLOAD_VERSION_CHECK_REQUEST;
          }
        }
      }
      #endif

      if ((Fota_Retransfer.TDataAfterReq==STD_ON) || \
          (Fota_Retransfer.SavedAddr!=MemoryAddress) )
      {
        if ((FOTA_SIGNATURE == Fota_Write.rul_BlockType) || \
            (FOTA_METADATA == Fota_Write.rul_BlockType))
        {
          remainingForMemAlign = MemoryWriteLen % Fota_PflsWriteAlignmentValue;
          if(remainingForMemAlign>0UL)
          {
            Fota_Write.rul_Writelen = MemoryWriteLen + (Fota_PflsWriteAlignmentValue - remainingForMemAlign);
            Fota_Write.rul_TotalLen += Fota_PflsWriteAlignmentValue - remainingForMemAlign;
          }
          else
          {
            Fota_Write.rul_Writelen = MemoryWriteLen;
          }
        }
        else
        {
          Fota_Write.rul_Writelen = MemoryWriteLen;
        }

        if (FOTA_SIGNATURE == Fota_Write.rul_BlockType)
        {
          (void)FOTA_MEMSET(Lau8_SignedBuffer, 0xFF, sizeof(Lau8_SignedBuffer));
          (void)FOTA_MEMCPY(Lau8_SignedBuffer, pWriteData, MemoryWriteLen);
        }

        Fota_Write.pWriteData = pWriteData;
        Fota_Retransfer.SavedAddr = MemoryAddress;

        #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
          (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
        if((FOTA_DOWNLOAD_VERSION_CHECK_REQUEST == downloadState) || (FOTA_DOWNLOAD_VERSION_CHECK_RESULT == downloadState))
        {
          Fota_Retransfer.New_Chunk_Received = FOTA_FALSE;
        }
        else
        {
          Fota_Retransfer.New_Chunk_Received = FOTA_TRUE;
        }
        #else
        Fota_Retransfer.New_Chunk_Received = FOTA_TRUE;
        #endif

        #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
        (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
        retVal = DCM_WRITE_FORCE_RCRRP;
        #else
        retVal = DCM_WRITE_PENDING;
        #endif
      }
      else
      {
        retVal = DCM_WRITE_FAILED;
      }
    }
    else
    {
      retVal = DCM_WRITE_FAILED;
    }
  }
  else if ((OpStatus == DCM_FORCE_RCRRP_OK) || (OpStatus == DCM_PENDING))
  {
    switch (downloadState)
    {
      #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
        (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
      case FOTA_DOWNLOAD_VERSION_CHECK_REQUEST:
        /* @Trace: FOTA_SUD_API_00077 */
        Fota_VersionCheckRequest(
                    FOTA_VERSION_CHECK_AFTER_DOWNLOAD_REQUEST, MemoryAddress);

        Fota_State = FOTA_VERSION_CHECK_PROCESSING;
        downloadState = FOTA_DOWNLOAD_VERSION_CHECK_RESULT;
        retVal     = DCM_WRITE_PENDING;
        break;

      case FOTA_DOWNLOAD_VERSION_CHECK_RESULT:
        /* @Trace: FOTA_SUD_API_00233 */
        versionCheckResult = Fota_VersionCheckResult();
        if (FOTA_JOB_PENDING == versionCheckResult)
        {
          retVal = DCM_WRITE_PENDING;
        }
        else if (FOTA_JOB_OK == versionCheckResult)
        {
          Fota_State = FOTA_WAIT;
          downloadState = FOTA_DOWNLOAD_NORMAL;
          Fota_Retransfer.New_Chunk_Received = FOTA_TRUE;
          retVal = DCM_WRITE_PENDING;
        }
        else if (FOTA_JOB_FAILED == versionCheckResult)
        {
          #if (FOTA_DEV_ERROR_DETECT == STD_ON)
          /* Report Det Error */
          (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
            FOTA_TRANSFER_DATA_SID, FOTA_E_SVC_UPDATE_HEADER_FAILED);
          #endif
          Fota_State = FOTA_WAIT;
          downloadState = FOTA_DOWNLOAD_NORMAL;
          Fota_Retransfer.New_Chunk_Received = FOTA_TRUE;
          retVal = DCM_WRITE_PENDING;
        }
        else
        {
          /* Do Nothing */
        }
        break;
      #endif

      case FOTA_DOWNLOAD_NORMAL:
        /* @Trace: FOTA_SUD_API_00234 */
        if (Fota_State == FOTA_PROCESSING) /* Fota job check */
        {
          retVal = DCM_WRITE_PENDING;
        }
        else if (Fota_State == FOTA_WAIT)
        {
          if (Fota_Retransfer.New_Chunk_Received == FOTA_FALSE)
          {
            if (Fota_Write.rul_TotalLen > Fota_Write.rul_TotalWrittenlen)
            {
              Fota_Write.rul_WriteAddPhy     += Fota_Write.rul_Writelen;
              Fota_Write.rul_TotalWrittenlen += Fota_Write.rul_Writelen;
            }
            else
            {
              Fota_Write.rul_Writelen = MemoryWriteLen;
              Fota_Write.pWriteData = pWriteData;

              if (FOTA_SIGNATURE == Fota_Write.rul_BlockType)
              {
                (void)FOTA_MEMSET(Lau8_SignedBuffer, 0xFF, sizeof(Lau8_SignedBuffer));
                (void)FOTA_MEMCPY(Lau8_SignedBuffer, pWriteData, MemoryWriteLen);
              }
            }
            retVal = DCM_WRITE_OK;
          }
          else
          {
            retVal = DCM_WRITE_PENDING;
          }
        }
        else
        {
          retVal = DCM_WRITE_FAILED;
        }
        break;
      /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
      default :
        /* @Trace: FOTA_SUD_API_00235 */
        retVal = DCM_WRITE_FAILED;
        break;
      /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
    }
  }
  /* @Trace: FOTA_SUD_API_00078 */
  else if (OpStatus == DCM_CANCEL)
  {
    retVal = DCM_WRITE_FAILED;
  }
  else if (OpStatus == DCM_FORCE_RCRRP_OK)
  {
    retVal = DCM_WRITE_FAILED;
  }
  else
  {
    retVal = DCM_WRITE_FAILED;
  }

  return retVal;
}
#endif
/*******************************************************************************
** Function Name        : Fota_ProcessRequestTransferExit                     **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : DCM CallOut function call this to transfer exit     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus, LpMemoryData, LulParameterRecordSize      **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpErrorCode                                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Fota_Write                    **
**                                              Fota_Retransfer               **
**                                              Fota_State                    **
**                                                                            **
**                        Function(s) invoked : None                          **
**                                                                            **
*******************************************************************************/
/* @Trace: FOTA_SRS_UDS_00008 */
#if (FOTA_MODE == FOTA_FBL_MODE) || (FOTA_MODE == FOTA_APP_MODE)
FUNC(Std_ReturnType, FOTA_CODE) Fota_ProcessRequestTransferExit
(
  Dcm_OpStatusType OpStatus,
  P2VAR(uint8, AUTOMATIC, DCM_APPL_DATA) LpMemoryData,
  uint32* LulParameterRecordSize,
  P2VAR(Dcm_NegativeResponseCodeType, AUTOMATIC, FOTA_PRIVATE_DATA)LpErrorCode
)
{
  /* @Trace: FOTA_SUD_API_00079 */
  Std_ReturnType retVal = E_NOT_OK;
  *LpErrorCode = DCM_E_POSITIVERESPONSE;

  FOTA_UNUSED(OpStatus);
  FOTA_UNUSED(LpMemoryData);
  FOTA_UNUSED(LulParameterRecordSize);

  if (Fota_Write.rul_TotalLen == Fota_Write.rul_TotalWrittenlen)
  {
    *LpErrorCode = DCM_E_POSITIVERESPONSE;
    Fota_Retransfer.TDataAfterReq=STD_OFF;
    Fota_State = FOTA_READY;
    retVal = E_OK;
  }
  else
  {
    *LpErrorCode = DCM_E_REQUESTSEQUENCEERROR;
    Fota_State = FOTA_ERROR;
    retVal = E_NOT_OK;
  }

  return retVal;
}
#endif
/*******************************************************************************
** Function Name        : Fota_ProcessVerifyGenOne                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Fota Verify function in CPD Service                 **
**                        (Reprogram Gen 1 Case (FOTA_OTA_ES98765_01))        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : InMemArea, InEcuSwUnit, OpStatus                    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpOut_MemoryArea, LpErrorCode                       **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Fota_ProgrammingSWUnitId      **
**                                              Fota_MemoryInstance           **
**                                              Fota_VersionStatus            **
**                                              Fota_SecureFlashDecryptOn     **
**                                              BlockProcessingRulePtr        **
**                                              Lau8_DecryptedBuffer          **
**                                              Fota_ProgrammingMemoryArea    **
**                                              Fota_State                    **
**                                              Fota_Gast_SwUnitTable         **
**                                                                            **
**                        Function(s) invoked :       Fota_ValidateMemoryArea **
**                                                 Fota_IsDualPartitionSwUnit **
**                                                    Fota_GetTargetPartition **
**                                                Fota_GetSwUnitIdByPartition **
**                                                    Fota_GetSwUnitIdByLabel **
**                                                Fota_GetMemInstanceBySwUnit **
**                                                         Fota_DecryptFinish **
**                                                         Fota_VerifyRequest **
**                                                       Fota_VerifyJobResult **
**                                                   Fota_VersionCheckRequest **
**                                                    Fota_VersionCheckResult **
**                                                     Fota_SetActKey_Request **
**                                                         Fota_SetKey_Result **
**                                            Fota_VersionCheckEraseRomLength **
**                                                        Fota_PflsTgtAreaSet **
**                                                      Fota_PflsEraseRequest **
**                                                      Fota_PflsGetJobResult **
**                                                      (void)Det_ReportError **
**                                                                            **
*******************************************************************************/
/* @Trace: FOTA_SRS_ES95489_52E_00008 FOTA_SRS_ES95489_52E_00009 FOTA_SRS_ES98765_01E_00003 FOTA_SRS_GENSEC_00009 FOTA_SRS_UDS_00005 */
/* @Trace: FOTA_SRS_ES95489_52E_00001 FOTA_SRS_GENSEC_00007 FOTA_SRS_GENSEC_00010 FOTA_SRS_GENSEC_00012 */
/* @Trace: FOTA_SRS_ES98765_02E_00021 FOTA_SRS_ES98765_02E_00029 FOTA_SRS_UDS_00004 FOTA_SRS_UDS_00026 */
#if (FOTA_IMPLEMENTATION_RULE == FOTA_OTA_ES98765_01)
FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessVerifyGenOne
(
  VAR(uint8, AUTOMATIC) InMemArea,
  VAR(uint16, AUTOMATIC) InEcuSwUnit,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpOut_MemoryArea,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
)
{
  VAR(Std_ReturnType,AUTOMATIC) retVal;
  VAR(Fota_JobResultType,AUTOMATIC) jobVerifyResult;
  VAR(Mem_76_Pfls_JobResultType,AUTOMATIC) memJobResult;
  VAR(Fota_SetKeyResultType, AUTOMATIC) setKeyResult;
  VAR(Fota_PartitionType,AUTOMATIC) TgtPart;

  static Fota_CpdStatType programmingState = FOTA_CPD_ERR;
  #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
    (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
  static Fota_VersionCheckRequestType versionCheckRequest =
                                            FOTA_VERSION_CHECK_CPD_REQUEST;
  Fota_JobResultType versionCheckResult;
  #endif
  uint32 eraseRomLength;
  #if (FOTA_STD_ON == FOTA_SF20_ENABLE)
  uint32 decryptJobId;
  uint32 decryptionLen = FOTA_TP_BLOCK_LENGTH;
  #endif
  FOTA_UNUSED(LpOut_MemoryArea);
  *LpErrorCode = DCM_E_POSITIVERESPONSE;
  /* polyspace-begin MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
  retVal = E_NOT_OK;
  /* polyspace-end MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */

  if ((OpStatus == DCM_INITIAL)||(OpStatus == DCM_PENDING))
  {
    if (OpStatus == DCM_INITIAL)
    {
      /* @Trace: FOTA_SUD_API_00080 */
      /* get the memory area to local variable */
      if (E_OK == Fota_ValidateMemoryArea(InMemArea))
      {
        /* get ECU software Unit ID */
        if(Fota_IsDualPartitionSwUnit(InEcuSwUnit)==E_OK)
        {
          if(Fota_GetTargetPartition(&TgtPart)==E_OK)
          {
            retVal = Fota_GetSwUnitIdByPartition(TgtPart,&Fota_ProgrammingSWUnitId);
          }
          else
          {
            retVal = E_NOT_OK;
          }
        }
        else
        {
          retVal = Fota_GetSwUnitIdByLabel(InEcuSwUnit, &Fota_ProgrammingSWUnitId);
        }
      }
      /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
      if (E_OK != retVal)
      {
        /* Server shall respond NRC 31 */
        *LpErrorCode = DCM_E_REQUESTOUTOFRANGE;
        programmingState = FOTA_CPD_ERR;
        #if (FOTA_DEV_ERROR_DETECT == STD_ON)
        /* Report Det Error */
        (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
          FOTA_ROUTINE_CONTROL_CPD_SID, FOTA_E_BLOCKID_INVALID);
        #endif
      }
      else
      {
        (void)Fota_GetMemInstanceBySwUnit(Fota_ProgrammingSWUnitId, &Fota_MemoryInstance);
        programmingState = FOTA_CPD_CMD;
      }
      /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
    }

    switch(programmingState)
    {
      case FOTA_CPD_CMD:
        /* @Trace: FOTA_SUD_API_00081 */
        #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
          (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
        if (Fota_VersionStatus == FOTA_VERSION_OK)
        #endif
        {
          #if (FOTA_STD_ON == FOTA_SF20_ENABLE)
          if (FOTA_TRUE == Fota_SecureFlashDecryptOn)
          {
            decryptJobId = \
              BlockProcessingRulePtr[Fota_ProgrammingFwBlockId].DecryptJobId;
            if(Fota_DecryptFinish(FOTA_ROUTINE_CONTROL_CPD_SID, decryptJobId,
                                     &Lau8_DecryptedBuffer[0], &decryptionLen) == E_OK)
            {
               retVal = E_OK;
            }
            else
            {
              *LpErrorCode = DCM_E_GENERALPROGRAMMINGFAILURE;
              programmingState = FOTA_CPD_ERR;
              retVal = DCM_E_PENDING;
            }
          }
          if(E_OK == retVal)
        #endif /* (FOTA_STD_ON == FOTA_SF20_ENABLE) */
          /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
          {
            if (Fota_VerifyRequest(Fota_ProgrammingMemoryArea) == E_OK)
            {
              Fota_State = FOTA_VERIFY;
              programmingState = FOTA_CPD_INTEGRITY_CHECK;
              retVal = DCM_E_PENDING;
              *LpErrorCode = DCM_E_POSITIVERESPONSE;
            }
            else
            {
              #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
                (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
              programmingState = FOTA_CPD_RECOVERY_TRAILER_ERASE_ROM;
              #else
              programmingState = FOTA_CPD_ERASE_ROM;
              #endif
              retVal = DCM_E_PENDING;
              *LpErrorCode = DCM_E_POSITIVERESPONSE;
            }
          }
          /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
        }
        #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
          (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
        else
        {
          retVal = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
          programmingState = FOTA_CPD_RECOVERY_TRAILER_ERASE_ROM;
        }
        #endif
        break;

      case FOTA_CPD_INTEGRITY_CHECK:
        if(FotaVerifyState == FOTA_STAT_VERIFY_INIT)
        {
          retVal  = DCM_E_PENDING;
        }
        else
        {
          /* @Trace: FOTA_SUD_API_00236 */
          jobVerifyResult = Fota_VerifyJobResult();

          if (jobVerifyResult == FOTA_JOB_PENDING)
          {
            retVal  = DCM_E_PENDING;
            *LpErrorCode = DCM_E_POSITIVERESPONSE;
          }
          else if (jobVerifyResult == FOTA_JOB_OK)
          {
            #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
              (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))

            programmingState = FOTA_CPD_VERSION_CHECK_REQUEST;

            #else

            #if (FOTA_MCU_MEMORY_ACCESS_TYPE!=FOTA_SINGLE_TYPE)
            programmingState = FOTA_CPD_CPDKEY_WRITE;
            #else
            programmingState = FOTA_CPD_PARTITION_WRITE;
            #endif

            #endif /* #if (FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) */
            retVal = DCM_E_PENDING;
            *LpErrorCode = DCM_E_POSITIVERESPONSE;
          }
          else
          {
            #if (FOTA_DEV_ERROR_DETECT == STD_ON)
            /* Report Det Error */
            (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
              FOTA_ROUTINE_CONTROL_CPD_SID, FOTA_E_VERIFY_JOB_FAILED);
            #endif

            #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
              (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
            programmingState = FOTA_CPD_RECOVERY_TRAILER_ERASE_ROM;
            #else
            programmingState = FOTA_CPD_ERASE_ROM;
            #endif
            retVal = DCM_E_PENDING;
            *LpErrorCode = DCM_E_POSITIVERESPONSE;
          }
        }
        break;

      #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
        (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
      case FOTA_CPD_VERSION_CHECK_REQUEST:
        /* @Trace: FOTA_SUD_API_00237 */
        Fota_VersionCheckRequest(versionCheckRequest, FOTA_ZERO);

        Fota_State = FOTA_VERSION_CHECK_PROCESSING;
        programmingState = FOTA_CPD_VERSION_CHECK_RESULT;
        retVal     = DCM_E_PENDING;
        *LpErrorCode = DCM_E_POSITIVERESPONSE;
        break;

      case FOTA_CPD_VERSION_CHECK_RESULT:
      #else
      #if (FOTA_MCU_MEMORY_ACCESS_TYPE!=FOTA_SINGLE_TYPE)
      case FOTA_CPD_CPDKEY_WRITE:
      #else
      case FOTA_CPD_PARTITION_WRITE:
      #endif
      #endif
        /* @Trace: FOTA_SUD_API_00238 */
        #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
          (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
        versionCheckResult = Fota_VersionCheckResult();
        if (FOTA_JOB_PENDING == versionCheckResult)
        {
          retVal = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else if (FOTA_JOB_OK == versionCheckResult)
        {
          if (FOTA_VERSION_CHECK_CPD_REQUEST == versionCheckRequest)
          {
            #if (FOTA_MCU_MEMORY_ACCESS_TYPE!=FOTA_SINGLE_TYPE)
            programmingState = FOTA_CPD_CPDKEY_WRITE;
            #else
            programmingState = FOTA_CPD_PARTITION_WRITE;
            #endif
            retVal = DCM_E_PENDING;
            *LpErrorCode = DCM_E_POSITIVERESPONSE;
          }
          else if (FOTA_VERSION_CHECK_ERASE_ROM_REQUEST == versionCheckRequest)
          {
            Fota_State = FOTA_READY;
            programmingState = FOTA_CPD_ERASE_ROM;
            retVal = DCM_E_PENDING;
            *LpErrorCode = DCM_E_POSITIVERESPONSE;
          }
          else
          {
            /* Do Nothing */
          }
        }
        else if (FOTA_JOB_FAILED == versionCheckResult)
        {
          Fota_VersionStatus = FOTA_VERSION_NOT_OK;

          if (FOTA_VERSION_CHECK_CPD_REQUEST == versionCheckRequest)
          {
            #if (FOTA_DEV_ERROR_DETECT == STD_ON)
            /* Report Det Error */
            (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
              FOTA_ROUTINE_CONTROL_CPD_SID, FOTA_E_SVC_UPDATE_TRAILER_FAILED);
            #endif
            programmingState = FOTA_CPD_RECOVERY_TRAILER_ERASE_ROM;
            retVal = DCM_E_PENDING;
            *LpErrorCode = DCM_E_POSITIVERESPONSE;
          }
          else if (FOTA_VERSION_CHECK_ERASE_ROM_REQUEST == versionCheckRequest)
          {
            #if (FOTA_DEV_ERROR_DETECT == STD_ON)
            /* Report Det Error */
            (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
              FOTA_ROUTINE_CONTROL_CPD_SID, FOTA_E_SVC_RECOVERY_TRAILER_FAILED);
            #endif
            Fota_State = FOTA_READY;
            programmingState = FOTA_CPD_ERASE_ROM;
            retVal = DCM_E_PENDING;
            *LpErrorCode = DCM_E_POSITIVERESPONSE;
          }
          else
          {
            /* Do Nothing */
          }
        }
        else
        {
          /* Do Nothing */
        }

        if ((FOTA_CPD_PARTITION_WRITE == programmingState) || \
          (FOTA_CPD_CPDKEY_WRITE == programmingState))
        #endif /* #if FOTA_SOFTWARE_VERSION_CHECK */
        {
          #if (FOTA_MCU_MEMORY_ACCESS_TYPE!=FOTA_SINGLE_TYPE)
          if (E_OK == Fota_SetVfyKey_Request(Fota_ProgrammingSWUnitId))
          {
            programmingState = FOTA_CPD_CPDKEY_WRITE_CHECK;
            retVal  = DCM_E_PENDING;
            *LpErrorCode = DCM_E_POSITIVERESPONSE;
          }
          #else
          if (E_OK==Fota_SetActKey_Request(FOTA_FLKEY_MGR, Fota_ProgrammingSWUnitId))
          {
            programmingState = FOTA_CPD_PARTITION_WRITE_CHECK;
            retVal  = DCM_E_PENDING;
            *LpErrorCode = DCM_E_POSITIVERESPONSE;
          }
          #endif
          else
          {
            #if (FOTA_DEV_ERROR_DETECT == STD_ON)
            /* Report Det Error */
            (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
              FOTA_ROUTINE_CONTROL_CPD_SID, FOTA_E_WRITE_REQUEST_FAILED);
            #endif
            #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
              (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
            programmingState = FOTA_CPD_RECOVERY_TRAILER_ERASE_ROM;
            #else
            programmingState = FOTA_CPD_ERASE_ROM;
            #endif
            retVal = DCM_E_PENDING;
            *LpErrorCode = DCM_E_POSITIVERESPONSE;
          }
        }
        break;

      #if (FOTA_MCU_MEMORY_ACCESS_TYPE!=FOTA_SINGLE_TYPE)
      case FOTA_CPD_CPDKEY_WRITE_CHECK:
      #else
      case FOTA_CPD_PARTITION_WRITE_CHECK:
      #endif
        /* @Trace: FOTA_SUD_API_00239 */
        setKeyResult = Fota_SetKey_Result();
        if (FOTA_SETMAGICKEY_OK == setKeyResult)
        {
          if (FOTA_UPDATER_TYPE == Fota_Gast_SwUnitTable[Fota_ProgrammingSWUnitId].SoftwareType)
          {
            programmingState = FOTA_CPD_END_ACTIVATE;
          }
          else
          {
            programmingState = FOTA_CPD_END_READY;
          }
          retVal  = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else if (FOTA_SETMAGICKEY_FAILED == setKeyResult)
        {
          #if (FOTA_DEV_ERROR_DETECT == STD_ON)
          /* Report Det Error */
          (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
            FOTA_ROUTINE_CONTROL_CPD_SID, FOTA_E_WRITE_JOB_FAILED);
          #endif

          #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
            (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
          programmingState = FOTA_CPD_RECOVERY_TRAILER_ERASE_ROM;
          #else
          programmingState = FOTA_CPD_ERASE_ROM;
          #endif
          retVal  = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else
        {
          retVal = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        break;

      #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
        (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
      case FOTA_CPD_RECOVERY_TRAILER_ERASE_ROM:
        /* @Trace: FOTA_SUD_API_00240 */
        versionCheckRequest = FOTA_VERSION_CHECK_ERASE_ROM_REQUEST;
        Fota_VersionCheckRequest(versionCheckRequest, FOTA_ZERO);

        Fota_State = FOTA_VERSION_CHECK_PROCESSING;
        programmingState = FOTA_CPD_VERSION_CHECK_RESULT;

        retVal     = DCM_E_PENDING;
        *LpErrorCode = DCM_E_POSITIVERESPONSE;
        break;
      #endif

      case FOTA_CPD_ERASE_ROM:
        /* @Trace: FOTA_SUD_API_00241 */
        /* Erase area which same as routine-control erase
         * If version check enable, this delete except trailer
         */
        #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
          (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
        /* 1st Erase Area for sector which include header */
        eraseRomLength = Fota_VersionCheckEraseRomLength(Fota_ProgrammingSWUnitId);
        #else
        eraseRomLength =
          Fota_Gast_SwUnitTable[Fota_ProgrammingSWUnitId].EndAddress -
          Fota_Gast_SwUnitTable[Fota_ProgrammingSWUnitId].StartAddress + 1;
        #endif

        programmingState = FOTA_CPD_ERASE_ROM_CHECK;

        #if (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)
        (void)Fota_PflsTgtAreaSet(Fota_MemoryInstance, FOTA_ALT_ADDR);
        #else
        (void)Fota_PflsTgtAreaSet(Fota_MemoryInstance, FOTA_STD_ADDR);
        #endif

        if (E_OK == Fota_PflsEraseRequest(
             Fota_MemoryInstance,
             Fota_Gast_SwUnitTable[Fota_ProgrammingSWUnitId].StartAddress,
             eraseRomLength))
        {
          programmingState = FOTA_CPD_ERASE_ROM_CHECK;
        }
        else
        {
          #if (FOTA_DEV_ERROR_DETECT == STD_ON)
          /* Report Det Error */
          (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
           FOTA_ROUTINE_CONTROL_CPD_SID, FOTA_E_ERASE_REQUEST_FAILED);
          #endif
          programmingState = FOTA_CPD_ERR;
        }
        retVal     = DCM_E_PENDING;
        *LpErrorCode = DCM_E_POSITIVERESPONSE;
        break;

      case FOTA_CPD_ERASE_ROM_CHECK:
        /* @Trace: FOTA_SUD_API_00242 */
        memJobResult = Fota_PflsGetJobResult(Fota_MemoryInstance);

        if (memJobResult == MEM_JOB_PENDING)
        {
          retVal  = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else if (memJobResult ==  MEM_JOB_OK)
        {
          programmingState = FOTA_CPD_ERR;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
          retVal = DCM_E_PENDING;
        }
        else
        {
          #if (FOTA_DEV_ERROR_DETECT == STD_ON)
          /* Report Det Error */
          (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
           FOTA_ROUTINE_CONTROL_CPD_SID, FOTA_E_ERASE_JOB_FAILED);
          #endif
          programmingState = FOTA_CPD_ERR;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
          retVal = DCM_E_PENDING;
        }
        break;

      case FOTA_CPD_END_READY:
        /* @Trace: FOTA_SUD_API_00243 */
        (void)Fota_PflsTgtAreaSet(Fota_MemoryInstance,FOTA_STD_ADDR);

        *LpErrorCode = DCM_E_POSITIVERESPONSE;
        Fota_State = FOTA_READY;
        retVal = E_OK;

        break;

      case FOTA_CPD_END_ACTIVATE:
        /* @Trace: FOTA_SUD_API_00244 */
        (void)Fota_PflsTgtAreaSet(Fota_MemoryInstance,FOTA_STD_ADDR);

        Fota_State = FOTA_ACTIVATE;
        retVal = DCM_E_PENDING;
        *LpErrorCode = DCM_E_POSITIVERESPONSE;

        break;

      case FOTA_CPD_ERR:
      default :
        /* @Trace: FOTA_SUD_API_00245 */
        #if (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)
        (void)Fota_PflsTgtAreaSet(Fota_MemoryInstance, FOTA_ALT_ADDR);
        #else
        (void)Fota_PflsTgtAreaSet(Fota_MemoryInstance, FOTA_STD_ADDR);
        #endif

        #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
          (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
        if (Fota_VersionStatus == FOTA_VERSION_NOT_OK)
        {
          *LpErrorCode = DCM_E_LOWERVERSIONDOWNLOADATTEMPT;
        }
        else
        #endif
        {
          if (DCM_E_POSITIVERESPONSE == *LpErrorCode)
          {
            *LpErrorCode = DCM_E_GENERALPROGRAMMINGFAILURE;
          }
        }
        retVal = E_NOT_OK;
        Fota_State = FOTA_ERROR;

        break;
    }
  }
  /* @Trace: FOTA_SUD_API_00082 */
  else if (OpStatus == DCM_CANCEL)
  {
    retVal = DCM_WRITE_FAILED;
  }
  else if(OpStatus == DCM_FORCE_RCRRP_OK)
  {
    retVal = DCM_WRITE_FAILED;
  }
  else
  {
    retVal = DCM_WRITE_FAILED;
  }

  return retVal;
}
#endif /* #if (FOTA_IMPLEMENTATION_RULE == FOTA_OTA_ES98765_01) */
/*******************************************************************************
** Function Name        : Fota_ProcessVerifyGenTwo                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Fota Verify function in Check Memory Service        **
**                        (Reprogram Gen 2 Case (FOTA_OTA_ES98765_02))        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : InMemArea, InEcuSwUnit, OpStatus                    **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpOut_MemoryArea, LpErrorCode                       **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : Fota_ProgrammingSWUnitId      **
**                                              Fota_MemoryInstance           **
**                                              Fota_VersionStatus            **
**                                              Fota_SvcResultAllSwUnit       **
**                                              Fota_SecureFlashDecryptOn     **
**                                              BlockProcessingRulePtr        **
**                                              Lau8_DecryptedBuffer          **
**                                              Fota_ProgrammingMemoryArea    **
**                                              Fota_State                    **
**                                              Fota_Gast_SwUnitTable         **
**                                                                            **
**                        Function(s) invoked :   Fota_GetMemInstanceBySwUnit **
**                                                         Fota_DecryptFinish **
**                                                         Fota_VerifyRequest **
**                                                       Fota_VerifyJobResult **
**                                                     Fota_SetVfyKey_Request **
**                                                         Fota_SetKey_Result **
**                                                        Fota_PflsTgtAreaSet **
**                                                      (void)Det_ReportError **
**                                                                            **
*******************************************************************************/
/* @Trace:FOTA_SRS_ES95489_52E_00009 FOTA_SRS_ES98765_01E_00003 FOTA_SRS_ES95489_52E_00008 FOTA_SRS_GENSEC_00009 */
/* @Trace: FOTA_SRS_ES95489_52E_00001 FOTA_SRS_ES98765_02E_00020 FOTA_SRS_GENSEC_00007 FOTA_SRS_GENSEC_00010 FOTA_SRS_GENSEC_00012 */
#if (FOTA_IMPLEMENTATION_RULE == FOTA_OTA_ES98765_02)
FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessVerifyGenTwo
(
  VAR(uint8, AUTOMATIC) InMemArea,
  VAR(uint16, AUTOMATIC) InEcuSwUnit,
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpOut_MemoryArea,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
)
{
  VAR(Std_ReturnType,AUTOMATIC) retVal;
  VAR(Fota_JobResultType,AUTOMATIC) jobVerifyResult;
  VAR(Fota_SetKeyResultType, AUTOMATIC) setKeyResult;

  static Fota_CpdStatType programmingState = FOTA_CPD_ERR;
  #if (FOTA_STD_ON == FOTA_SF20_ENABLE)
  uint32 decryptJobId;
  uint32 decryptionLen = FOTA_TP_BLOCK_LENGTH;
  #endif
  FOTA_UNUSED(InMemArea);
  FOTA_UNUSED(InEcuSwUnit);
  FOTA_UNUSED(LpOut_MemoryArea);
  *LpErrorCode = DCM_E_GENERALREJECT;
  /* polyspace-begin MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
  retVal = E_NOT_OK;
  /* polyspace-end MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */

  if ((OpStatus == DCM_INITIAL)||(OpStatus == DCM_PENDING))
  {
    if (OpStatus == DCM_INITIAL)
    {
      /* @Trace: FOTA_SUD_API_00086 */
      (void)Fota_GetMemInstanceBySwUnit(Fota_ProgrammingSWUnitId, &Fota_MemoryInstance);
      programmingState = FOTA_CPD_CMD;
    }

    switch(programmingState)
    {
      case FOTA_CPD_CMD:
        /* @Trace: FOTA_SUD_API_00087 */
        #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
          (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
        if (Fota_VersionStatus == FOTA_VERSION_OK)
        #endif
        {
          #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
            (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
          if (Fota_SvcResultAllSwUnit[Fota_ProgrammingSWUnitId].CheckVersion ==
                                                              FOTA_VERSION_USED)
          {
            Fota_SvcResultAllSwUnit[Fota_ProgrammingSWUnitId].
                                                      VersionCheckResult = E_OK;
          }
          #endif

          #if (FOTA_STD_ON == FOTA_SF20_ENABLE)
          if (FOTA_TRUE == Fota_SecureFlashDecryptOn)
          {
            decryptJobId = \
              BlockProcessingRulePtr[Fota_ProgrammingFwBlockId].DecryptJobId;
            if(Fota_DecryptFinish(FOTA_ROUTINE_CONTROL_CPD_SID,decryptJobId,
                                     &Lau8_DecryptedBuffer[0], &decryptionLen) == E_OK)
            {
               retVal = E_OK;
            }
            else
            {
              *LpErrorCode = DCM_E_GENERALPROGRAMMINGFAILURE;
              programmingState = FOTA_CPD_ERR;
              retVal = DCM_E_PENDING;
            }
          }
          if(E_OK == retVal)
          #endif /* (FOTA_STD_ON == FOTA_SF20_ENABLE) */

          /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
          {
            if (Fota_VerifyRequest(Fota_ProgrammingMemoryArea) == E_OK)
            {
              Fota_State = FOTA_VERIFY;
              programmingState = FOTA_CPD_INTEGRITY_CHECK;
              retVal = DCM_E_PENDING;
              *LpErrorCode = DCM_E_POSITIVERESPONSE;
            }
            else
            {
              programmingState = FOTA_CPD_ERR;
              retVal = DCM_E_PENDING;
              *LpErrorCode = DCM_E_POSITIVERESPONSE;
            }
          }
          /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
        }
        #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
          (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
        else
        {
          if (Fota_SvcResultAllSwUnit[Fota_ProgrammingSWUnitId].CheckVersion ==
                                                              FOTA_VERSION_USED)
          {
            Fota_SvcResultAllSwUnit[Fota_ProgrammingSWUnitId].
                                                  VersionCheckResult = E_NOT_OK;
          }
          retVal = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
          programmingState = FOTA_CPD_END_READY;
        }
        #endif
        break;

      case FOTA_CPD_INTEGRITY_CHECK:
        /* @Trace: FOTA_SUD_API_00246 */
        jobVerifyResult = Fota_VerifyJobResult();

        if (jobVerifyResult == FOTA_JOB_PENDING)
        {
          retVal  = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else if (jobVerifyResult == FOTA_JOB_OK)
        {
          programmingState = FOTA_CPD_CPDKEY_WRITE;
          retVal = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else
        {
          #if (FOTA_DEV_ERROR_DETECT == STD_ON)
          /* Report Det Error */
          (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
            FOTA_ROUTINE_CONTROL_CPD_SID, FOTA_E_VERIFY_JOB_FAILED);
          #endif
          programmingState = FOTA_CPD_ERR;
          retVal = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        break;

      case FOTA_CPD_CPDKEY_WRITE:
        /* @Trace: FOTA_SUD_API_00247 */
        if (E_OK == Fota_SetVfyKey_Request(Fota_ProgrammingSWUnitId))
        {
          programmingState = FOTA_CPD_CPDKEY_WRITE_CHECK;
          retVal  = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else
        {
          #if (FOTA_DEV_ERROR_DETECT == STD_ON)
          /* Report Det Error */
          (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
            FOTA_ROUTINE_CONTROL_CPD_SID, FOTA_E_WRITE_REQUEST_FAILED);
          #endif
          programmingState = FOTA_CPD_ERR;
          retVal = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        break;

      case FOTA_CPD_CPDKEY_WRITE_CHECK:
        /* @Trace: FOTA_SUD_API_00248 */
        setKeyResult = Fota_SetKey_Result();

        if (FOTA_SETMAGICKEY_OK == setKeyResult)
        {
          if (FOTA_UPDATER_TYPE == Fota_Gast_SwUnitTable[Fota_ProgrammingSWUnitId].SoftwareType)
          {
            programmingState = FOTA_CPD_END_ACTIVATE;
          }
          else
          {
            programmingState = FOTA_CPD_END_READY;
          }
          retVal  = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else if (FOTA_SETMAGICKEY_FAILED == setKeyResult)
        {
          #if (FOTA_DEV_ERROR_DETECT == STD_ON)
          /* Report Det Error */
          (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
            FOTA_ROUTINE_CONTROL_CPD_SID, FOTA_E_WRITE_JOB_FAILED);
          #endif

          programmingState = FOTA_CPD_ERR;
          retVal  = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        else
        {
          retVal = DCM_E_PENDING;
          *LpErrorCode = DCM_E_POSITIVERESPONSE;
        }
        break;

      case FOTA_CPD_END_READY:
        /* @Trace: FOTA_SUD_API_00249 */
        (void)Fota_PflsTgtAreaSet(Fota_MemoryInstance, FOTA_STD_ADDR);
        *LpErrorCode = DCM_E_POSITIVERESPONSE;
        Fota_State = FOTA_READY;
        retVal = E_OK;
        break;

      case FOTA_CPD_END_ACTIVATE:
        /* @Trace: FOTA_SUD_API_00250 */
        (void)Fota_PflsTgtAreaSet(Fota_MemoryInstance, FOTA_STD_ADDR);
        Fota_State = FOTA_ACTIVATE;
        retVal = DCM_E_PENDING;
        *LpErrorCode = DCM_E_POSITIVERESPONSE;
        break;

      case FOTA_CPD_ERR:
      default :
        /* @Trace: FOTA_SUD_API_00251 */
        #if (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)
        (void)Fota_PflsTgtAreaSet(Fota_MemoryInstance, FOTA_ALT_ADDR);
        #else
        (void)Fota_PflsTgtAreaSet(Fota_MemoryInstance, FOTA_STD_ADDR);
        #endif
        *LpErrorCode = DCM_E_GENERALPROGRAMMINGFAILURE;
        retVal = E_NOT_OK;
        Fota_State = FOTA_ERROR;
        break;
    }
  }
  /* @Trace: FOTA_SUD_API_00088 */
  else if (OpStatus == DCM_CANCEL)
  {
    retVal = DCM_WRITE_FAILED;
  }
  else if(OpStatus == DCM_FORCE_RCRRP_OK)
  {
    retVal = DCM_WRITE_FAILED;
  }
  else
  {
    retVal = DCM_WRITE_FAILED;
  }

  return retVal;
}
#endif /* #if (FOTA_IMPLEMENTATION_RULE == FOTA_OTA_ES98765_02) */

/*******************************************************************************
** Function Name        : Fota_ProcessAreaDataSync                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Fota Verify function in Finish Update Service       **
**                        (Reprogram Gen 2 Case (FOTA_OTA_ES98765_02))        **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : OpStatus                                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : LpErrorCode                                         **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  : None                          **
**                                                                            **
**                        Function(s) invoked :          Fota_AreaSyncRequest **
**                                                        Fota_AreaSyncResult **
**                                                                            **
*******************************************************************************/
/* @Trace: FOTA_SRS_ES98765_02E_00022 FOTA_SRS_UDS_00027 */
#if (FOTA_IMPLEMENTATION_RULE == FOTA_OTA_ES98765_02)
FUNC (Std_ReturnType, FOTA_CODE) Fota_ProcessAreaDataSync
(
  VAR(uint8, AUTOMATIC) OpStatus,
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) LpErrorCode
)
{
  VAR(Std_ReturnType,AUTOMATIC) retVal;

  /* polyspace-begin MISRA-C3:14.3 [Justified:Low] "if-condition depends on the configuration." */

#if (FOTA_SYNC_PROCESS_RES_SUPPRESSION == STD_ON)
    /* @Trace: FOTA_SUD_API_00089 */
    if (OpStatus == DCM_INITIAL)
    {
  #if (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)

    if(FOTA_NUM_OF_SWUNIT>FOTA_ZERO)
    {
        (void)Fota_AreaSyncRequest(FOTA_SYNC_ALL_SWUNIT);
    }
    else /*  if single swuint, do nothing */
    {

    }

  #endif

    *LpErrorCode = DCM_E_POSITIVERESPONSE;
    retVal = DCM_E_OK;
    }
    else
    {
      *LpErrorCode = DCM_E_POSITIVERESPONSE;
      retVal = DCM_E_OK;
    }

#else
  /* @Trace: FOTA_SUD_API_00090 */
  VAR(Fota_JobResultType,AUTOMATIC) rue_SyncJobResult;

    if (OpStatus == DCM_INITIAL)
    {

  #if (FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)
    if(FOTA_NUM_OF_SWUNIT>FOTA_ZERO)
    {
        if(Fota_AreaSyncRequest(FOTA_SYNC_ALL_SWUNIT)==E_OK)
        {
          retVal = DCM_E_PENDING;
        }
        else
        {
          *LpErrorCode = DCM_E_GENERALREJECT;
          retVal = E_NOT_OK;
        }
    }
    else
    {
    *LpErrorCode = DCM_E_POSITIVERESPONSE;
    retVal = DCM_E_OK;
    }

  #else
        *LpErrorCode = DCM_E_POSITIVERESPONSE;
        retVal = DCM_E_OK;
  #endif

    }
    else if(OpStatus == DCM_CANCEL)
    {
      *LpErrorCode = DCM_E_GENERALREJECT;
      retVal = E_NOT_OK;
    }
    else /* DCM_PENDING or DCM_FORCE_RRCP_OK */
    {
  rue_SyncJobResult = Fota_AreaSyncResult();

  if(rue_SyncJobResult==FOTA_JOB_OK)
  {
      *LpErrorCode = DCM_E_POSITIVERESPONSE;
        retVal = DCM_E_OK;
  }
  else if(rue_SyncJobResult==FOTA_JOB_PENDING)
  {
      retVal = DCM_E_PENDING;
  }
  else
  {
      *LpErrorCode = DCM_E_GENERALREJECT;
      retVal = E_NOT_OK;
  }

    }

#endif

  /* polyspace-end MISRA-C3:14.3 [Justified:Low] "if-condition depends on the configuration." */

  return retVal;
}
#endif /* #if (FOTA_IMPLEMENTATION_RULE == FOTA_OTA_ES98765_02) */
/*******************************************************************************
** Function Name        : Fota_GetVersionInfo                                 **
**                                                                            **
** Service ID           : 0xF1                                                **
**                                                                            **
** Description          : This service returns the version information of     **
**                        this module.                                        **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Input Parameters     : None                                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : Std_VersionInfoType *versioninfo                    **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s) :                                **
**                        None                                                **
**                                                                            **
** Function(s) invoked :  Det_ReportError()                                   **
**                                                                            **
*******************************************************************************/
/* @Trace: FOTA_SRS_ES98765_02E_00033 FOTA_SRS_GENSEC_00007 */
#if (FOTA_VERSION_INFO_API == STD_ON)
FUNC(void, FOTA_CODE) Fota_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC,
    FOTA_PRIVATE_DATA) versioninfo)
{
  /* @Trace: FOTA_SUD_API_00091 */
  #if (FOTA_DEV_ERROR_DETECT == STD_ON)
  /* Check whether Version Information is equal to Null Ptr */
  if (NULL_PTR == versioninfo)
  {
    /* Report to DET  */
    (void)(Det_ReportError(FOTA_MODULE_ID, FOTA_ZERO, FOTA_GET_VERSION_SID,
      FOTA_E_NULL_POINTER));
  }
  else
  #endif /* End of if (FOTA_DEV_ERROR_DETECT == STD_ON) */
  {
    /* Requirement PDUR234 - Fota_GetVersionInfo shall return the version
    information of this module in the passed argument *versionInfo*/
    /* Copy the vendor Id */
    versioninfo->vendorID = FOTA_VENDOR_ID;
    /* Copy the module Id */
    versioninfo->moduleID = FOTA_MODULE_ID;
    /* Copy Software Major Version */
    versioninfo->sw_major_version = FOTA_SW_MAJOR_VERSION;
    /* Copy Software Minor Version */
    versioninfo->sw_minor_version = FOTA_SW_MINOR_VERSION;
    /* Copy Software Patch Version */
    versioninfo->sw_patch_version = FOTA_SW_PATCH_VERSION;
  }
} /* End of Fota_GetVersionInfo(P2VAR(Std_VersionInfoType, AUTOMATIC,
   *Fota_APPL_DATA) versioninfo) */
#endif /* #if (FOTA_VERSION_INFO_API == STD_ON) */
/*******************************************************************************
** Function Name        : Fota_MainFunction                                   **
**                                                                            **
** Service ID           :                                                     **
**                                                                            **
** Description          :                                                     **
**                                                                            **
** Sync/Async           :                                                     **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     :  **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     :  **
**                                                                            **
** Preconditions        : None                                                **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                                                                            **
**                        Function(s) invoked :                               **
*******************************************************************************/
#if (FOTA_MODE == FOTA_FBL_MODE) || (FOTA_MODE == FOTA_APP_MODE)
FUNC(void, FOTA_CODE) Fota_MainFunction(void)
{
  Mem_76_Pfls_JobResultType memJobResult;
  Std_ReturnType retVal = E_NOT_OK;
  #if ((FOTA_STD_ON == FOTA_SF20_ENABLE) || (FOTA_STD_ON == FOTA_USER_CALL_OUT_USED))
  Fota_StateType localFotaState;
  #endif
  #if (FOTA_STD_ON == FOTA_SF20_ENABLE)
  uint32 decryptJobId;
  #endif
  #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
    (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
  #endif
  switch(Fota_State)
  {
    case FOTA_IDLE:

      /* Initial state of the FOTA Handler after the ECU startup procedure */
      break;

    case FOTA_INIT:
      /* @Trace: FOTA_SUD_API_00252 */
      /* The FOTA Handler is initialized and Dcm is set into the correct state
        * (in Dcm FOTA session and security access has been granted).
        */
      #if (FOTA_STD_ON == FOTA_SF20_ENABLE)
        #if (HWRESOURCE_VENDOR(HWRESOURCE_NXP))
          Fota_S32k3_Hse_Psk_injection(); /* Usercode */
        #endif
      #endif

      break;

    case FOTA_WAIT:
     /* The FOTA Handler has successfully processed the last received data chunk,
      * returned the Dcm callout function and is waiting for the next data chunk.
      */
      /* @Trace: FOTA_SUD_API_00092 */
      if (Fota_Retransfer.New_Chunk_Received == FOTA_TRUE)
      {
        /* To prevent Dcm transferData preemption during Decryption or Pfls writing,
         * Set FOTA_PROCESSING state here
         */
        Fota_State = FOTA_PROCESSING;
        #if ((FOTA_STD_ON == FOTA_SF20_ENABLE) || (FOTA_STD_ON == FOTA_USER_CALL_OUT_USED))
        localFotaState = FOTA_WAIT;
        #endif
        #if (FOTA_STD_ON == FOTA_SF20_ENABLE)
        if (Fota_Write.rul_BlockType == FOTA_METADATA)
        {
          retVal = Fota_MetaDataProcessing(&Fota_Write, localFotaState);
        }
        else
        #endif /* (FOTA_STD_ON == FOTA_SF20_ENABLE) */
        {
          if (Fota_Write.rul_BlockType == FOTA_FIRMWARE)
          {
            #if (FOTA_STD_ON == FOTA_USER_CALL_OUT_USED)
            retVal = Fota_UserCallOutProcessing(BlockProcessingRulePtr,
                                                localFotaState);
            #else
            retVal = E_OK;
            #endif
            #if (FOTA_STD_ON == FOTA_SF20_ENABLE)
            if (FOTA_TRUE == Fota_SecureFlashDecryptOn)
            {
              decryptJobId = BlockProcessingRulePtr[\
                        Fota_ProgrammingFwBlockId].DecryptJobId;

              retVal |= Fota_DecryptUpdate(
                          decryptJobId,
                          Fota_Write.pWriteData,
                          Lau8_DecryptedBuffer,
                          (uint32*)&Fota_Write.rul_Writelen);

              Fota_Write.pWriteData = Lau8_DecryptedBuffer;
            }
            else
            {
              /* Decryption is not needed. */
            }
            #endif /* (FOTA_STD_ON == FOTA_SF20_ENABLE) */
          }
          else if (Fota_Write.rul_BlockType == FOTA_SIGNATURE)
          {
            Fota_Write.pWriteData = Lau8_SignedBuffer;
            retVal = E_OK;
          }
          else
          {
            /* Other Target Block type */
            retVal = E_OK;
          }

          /* polyspace-begin MISRA-C3:14.3 [Justified:Low] "if-condition depends on the configuration." */
          if (E_OK == retVal)
          {
             retVal = Fota_PflsWriteRequest(Fota_MemoryInstance, \
                      Fota_Write.rul_WriteAddPhy, \
                      Fota_Write.pWriteData, Fota_Write.rul_Writelen);
            #if (FOTA_DEV_ERROR_DETECT == STD_ON)
            if (E_NOT_OK == retVal)
            {
              /* Report Det Error */
              (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
                FOTA_MAIN_FUNCTION_SID, FOTA_E_WRITE_REQUEST_FAILED);
            }
            #endif
          }
          /* polyspace-end MISRA-C3:14.3 [Justified:Low] "if-condition depends on the configuration." */
        }

        if (retVal != E_OK)
        {
          Fota_State = FOTA_ERROR;
        }
      }
      break;

    case FOTA_PROCESSING:
     /* The FOTA Handler is triggered by the Dcm callout since a new chunk has been
      * received and is processed in the callout context.
      */
      /* @Trace: FOTA_SUD_API_00093 */
      if (Fota_Retransfer.New_Chunk_Received == FOTA_TRUE)
      {
        #if (FOTA_STD_ON == FOTA_SF20_ENABLE)
        if (Fota_Write.rul_BlockType == FOTA_METADATA)
        {
          if (FOTA_TRUE == Fota_CheckMetaWriteRequest())
          {
            memJobResult = Fota_PflsGetJobResult(Fota_MemoryInstance);
          }
          else
          {
            memJobResult = MEM_JOB_OK;
          }
        }
        else
        #endif
        {
          memJobResult = Fota_PflsGetJobResult(Fota_MemoryInstance);
        }

        if (MEM_JOB_FAILED == memJobResult)
        {
          #if (FOTA_DEV_ERROR_DETECT == STD_ON)
          /* Report Det Error */
          (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
            FOTA_MAIN_FUNCTION_SID, FOTA_E_WRITE_JOB_FAILED);
          #endif
          Fota_Retransfer.New_Chunk_Received = FOTA_FALSE;
          Fota_State = FOTA_ERROR;
        }
        else if (MEM_JOB_OK == memJobResult)
        {
          #if ((FOTA_STD_ON == FOTA_SF20_ENABLE) || (FOTA_STD_ON == FOTA_USER_CALL_OUT_USED))
          localFotaState = FOTA_PROCESSING;
          #endif
          #if (FOTA_STD_ON == FOTA_SF20_ENABLE)
          if (Fota_Write.rul_BlockType == FOTA_METADATA)
          {
            retVal = Fota_MetaDataProcessing(&Fota_Write, localFotaState);
            if(retVal == CRYPTO_E_BUSY) // CRYPTO_E_BUSY 0x02
            {
              /* Wait until CRYPTO_E_BUSY end */
            }
            else if(E_OK != retVal)
            {
              /* Dcm_WriteMemory don't have item of errCode, response only NRC 72 in this case. */
              Fota_State = FOTA_ERROR;
            }
          }
          else
          #endif /* (FOTA_STD_ON == FOTA_SF20_ENABLE) */
          {
            retVal = E_OK;
            #if (FOTA_STD_ON == FOTA_USER_CALL_OUT_USED)
            if (Fota_Write.rul_BlockType == FOTA_FIRMWARE)
            {
              retVal = Fota_UserCallOutProcessing(BlockProcessingRulePtr,
                                                  localFotaState);
            }
            #endif
          }
        }
        else
        {
          /* Do Nothing */
        }

        if (E_OK == retVal)
        {
          Fota_Retransfer.New_Chunk_Received = FOTA_FALSE;
          Fota_State = FOTA_WAIT;
        }
      }
      break;

    #if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
      (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
    case FOTA_VERSION_CHECK_PROCESSING:
      /* @Trace: FOTA_SUD_API_00094 */
      Fota_MainVersionCheck();
      break;
    #endif
    case FOTA_VERIFY:
      /* @Trace: FOTA_SUD_API_00253 */
      /* Optional and implementer specific step, since the FOTA Target does not
        * specify any details on the verification process.
        */
      Fota_JobVerifyProcess();

      break;

    case FOTA_READY:
      /* All FOTA data chunks have been installed, activation procedure can be triggered. */

      break;

    case FOTA_ACTIVATE:
      /* @Trace: FOTA_SUD_API_00254 */
      /* FOTA installation has finished and received a respective service job
        * from the FOTA Master that indicates the partition switch during
        * the next boot process.
        */
      Fota_RequestReset();
      break;

    case FOTA_ERROR:
      /* Optional and implementer specific. Reserved state for e.g. implementer
        * specific error handling, which is not (yet) covered by the FOTA Target.
        */
      break;

    default:
      /*Do nothing */
      break;
  }

  /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "if-condition depends on the Configuration." */
  #if (FOTA_IMPLEMENTATION_RULE == FOTA_OTA_ES98765_02)
  Fota_MacUpdateMain();
  Fota_AreaSyncMain();
  #endif
  /* polyspace-end MISRA-C3:2.2 [Justified:Low] "if-condition depends on the Configuration." */

}
#elif (FOTA_MODE == FOTA_UPDATER_MODE)
FUNC(void, FOTA_CODE) Fota_MainFunction(void)
{
  switch(Fota_State)
  {
    case FOTA_IDLE:
      /* Initial state of the FOTA Handler after the ECU startup procedure */
      break;

    case FOTA_INIT:
      /* The FOTA Handler is initialized and Dcm is set into the correct state
        * (in Dcm FOTA session and security access has been granted).
        */
      break;

    case FOTA_READY:
      /* All FOTA data chunks have been installed, activation procedure can be triggered. */
      break;

    case FOTA_ACTIVATE:
      /* @Trace: FOTA_SUD_API_00169 */
      Fota_RequestReset();
      /* FOTA installation has finished and received a respective service job
        * from the FOTA Master that indicates the partition switch during
        * the next boot process.
        */
      break;

    case FOTA_ERROR:
      /* Optional and implementer specific. Reserved state for e.g. implementer
        * specific error handling, which is not (yet) covered by the FOTA Target.
        */
      break;
    default:
      /* @Trace: FOTA_SUD_API_00270 */
      Fota_UpdaterMainFunction();
      break;
  }
}
#endif
/* polyspace-end MISRA-C3:2.7,8.13,20.9 [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
