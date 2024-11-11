/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fota_Verify.c                                                 **
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
** Revision    Date          By           Description                         **
** 1.0.0       23-Nov-2022   VuPH6        Initial version                     **
** 2.0.0       20-Feb-2023   VuPH6        Improvement                         **
** 1.1.0.0_HF1 26-Apr-2024   KJShim       #CP44-8300                          **
** 1.1.0.0_HF2 07-Jun-2024   JSKang       #CP44-9298                          **
********************************************************************************
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Fota.h"
#include "Fota_Types.h"
#include "Fota_IntFunc.h"
#include "Fota_Cfg.h"
#include "Fota_Verify.h"
#include "Fota_Globals.h"
#include "Rte_Csm_Type.h"
#include "Csm.h"
#include "Mem_76_Pfls.h"
#include "Fota_PflsInterface.h"
#include "Fota_User_Callouts.h"
/* polyspace-begin MISRA-C3:2.7,8.13 [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      Macros                                                **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
FotaVerify_StatType  FotaVerifyState = FOTA_STAT_VERIFY_INACTIVE;

static Fota_CrcInfoType Fota_CrcInfo[1];

static uint16 Fota_CalcVerifyCRC = 0;

static Fota_VerificationSwUnitType *Fota_PtrSWUnitHandler;
static uint8 Fota_NumOfVerification;
static uint8 Fota_JobIndexProcessing;
static SFSignChk_CmdType Fota_SFSignChkCmd[FOTA_NUM_OF_MAX_VERIFY];

static Fota_VerifyMethodType Fota_VerifyMethod;

#if FOTA_VERIFY_BUFFER_USED
static uint8 Fota_VerifyBufferUsed;

static uint32 Fota_DataSizeOneCycle = 0;

static uint8 Fota_SignatureReadData[SEC_SF_SIGNATURE_DELIMITER_LENGTH +
                                    SEC_SF_SIGNATURE_SIZE_LENGTH +
                                    SEC_SF_SIGNATURE_SIZE];
static uint8 Fota_DataReadBuffer[FOTA_VERIFY_DATA_SIZE_ONE_CYCLE_MAX];
#endif

static FUNC(Fota_JobResultType, FOTA_CODE) Fota_CRCInitDataPushDirect(void);

static FUNC(Fota_JobResultType, FOTA_CODE) Fota_CRCGetResult(void);

static FUNC(Std_ReturnType, FOTA_CODE) Fota_VerifyInitProcess(void);

static FUNC(Std_ReturnType, FOTA_CODE) Fota_GetSecureFlashPublicKeyByDelimiter(
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) rul_Delimiter);

static FUNC(Std_ReturnType, FOTA_CODE) Fota_SignInitDataPush(
  VAR(uint32, AUTOMATIC) signatureAddress);

static FUNC(Fota_JobResultType, FOTA_CODE) Fota_CalculateCRCDirect(void);

static FUNC(Fota_JobResultType, FOTA_CODE) Fota_CheckAllJobResult(void);

static FUNC(Fota_JobResultType, FOTA_CODE) Fota_VerifyCsmJobFinish(void);

static FUNC(Fota_JobResultType, FOTA_CODE) Fota_VerifyCsmJobUpdateDirect(void);

static FUNC(Fota_JobResultType, FOTA_CODE) Fota_VerifyCsmJobStart(
  uint32 *dataReadRemainSize,
  uint16 *blockIndexProcessing,
  uint32 *dataVerifiedSize);

#if FOTA_VERIFY_BUFFER_USED
static FUNC(void, FOTA_CODE) Fota_CRCInitDataPushBuffer(
                                                  uint32 *dataReadRemainSize,
                                                  uint16 *crcAreaNum,
                                                  uint32 *dataVerifiedSize);
static FUNC(void, FOTA_CODE) Fota_CalculateCRCBuffer(uint32 *dataReadRemainSize,
                                               uint16 *crcAreaNum,
                                               uint32 *dataVerifiedSize);

static FUNC(Fota_JobResultType, FOTA_CODE) Fota_VerifyCsmJobUpdateBuffer(
  uint32 *dataReadRemainSize,
  uint16 *blockIndexProcessing,
  uint32 *dataVerifiedSize);
static FUNC(Std_ReturnType, FOTA_CODE) Fota_VerifyBlockRead(
  uint32 dataReadRemainSize,
  uint16 blockIndexProcessing,
  uint16 crcAreaNum,
  uint32 dataVerifiedSize);
static FUNC(Std_ReturnType, FOTA_CODE) Fota_VerifyReadInfo(void);
#endif
/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"
/*******************************************************************************
** Function Name        : Fota_VerifyRequest                                  **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Request start verification operation                **
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
/* @Trace: FOTA_SRS_ES95489_52E_00008 */
FUNC(Std_ReturnType, FOTA_CODE) Fota_VerifyRequest(
  VAR(uint32, AUTOMATIC) In_MemoryArea
)
{
  /* @Trace: FOTA_SUD_API_00083 */
  Std_ReturnType en_ret=E_NOT_OK;

#if 0
  Fota_InstancesConfiguration[In_MemoryArea];
#else
  FOTA_UNUSED(In_MemoryArea);
#endif
  FotaVerifyState = FOTA_STAT_VERIFY_INIT;

  en_ret=E_OK;

  return en_ret;
}
/*******************************************************************************
** Function Name        : Fota_VerifyJobResult                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get result of verification operation                **
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
/* @Trace: FOTA_SRS_ES95489_52E_00008 */
FUNC(Fota_JobResultType, FOTA_CODE) Fota_VerifyJobResult(void)
{
  /* @Trace: FOTA_SUD_API_00084 */
  Fota_JobResultType jobResult;

  jobResult = Fota_GetVerifyJobResult();

  return jobResult;
}
/*******************************************************************************
** Function Name        : Fota_JobVerifyProcess                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Operation sequense in verification                  **
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
/* @Trace: FOTA_SRS_ES95489_52E_00008 */
FUNC(void, FOTA_CODE) Fota_JobVerifyProcess(void)
{
  Fota_JobResultType jobResult = FOTA_JOB_FAILED;
  Std_ReturnType retVal = E_NOT_OK;
  #if FOTA_VERIFY_BUFFER_USED
  VAR(Mem_76_Pfls_JobResultType, AUTOMATIC) memJobResult;
  static Fota_VerifyMemJobType memJobProcessing = FOTA_VERIFY_MEM_JOB_NONE;
  static uint32 dataReadRemainSize = 0;
  static uint32 dataVerifiedSize = 0;
  static uint16 crcAreaNum = 0;
  static uint16 blockIndexProcessing = 0;
  #endif
  switch (FotaVerifyState)
  {
    case FOTA_STAT_VERIFY_INACTIVE:
    break;

    case FOTA_STAT_VERIFY_INIT:
      /* @Trace: FOTA_SUD_API_00118 */
      /* polyspace-begin MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation. This function is for User." */
      Fota_BeforeFlashReadFunc();
      /* polyspace-end MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation. This function is for User." */
      retVal = Fota_VerifyInitProcess();

      if (E_OK == retVal)
      {
          Fota_SetVerifyJobResult(FOTA_JOB_PENDING);
          #if FOTA_VERIFY_BUFFER_USED
          if (FOTA_TRUE == Fota_VerifyBufferUsed)
          {
            FotaVerifyState = FOTA_STAT_VERIFY_INFO_READ;
          }
          else
          #endif
          {
            FotaVerifyState = FOTA_STAT_VERIFY_START;
          }
      }
      else
      {
    	  FotaVerifyState = FOTA_STAT_VERIFY_ERR;
      }

      break;
    #if FOTA_VERIFY_BUFFER_USED
    case FOTA_STAT_VERIFY_INFO_READ:
      /* @Trace: FOTA_SUD_API_00258 */
      retVal = Fota_VerifyReadInfo();
      if (retVal == E_OK)
      {
        memJobProcessing = FOTA_VERIFY_MEM_JOB_READ_SIGN;
        FotaVerifyState = FOTA_STAT_VERIFY_MEM_JOB_CHECK;
      }
      else
      {
        FotaVerifyState = FOTA_STAT_VERIFY_ERR;
      }
      break;
    #endif
    case FOTA_STAT_VERIFY_START:
      /* @Trace: FOTA_SUD_API_00119 */
      if (FOTA_SIGNATURE_VERIFY == Fota_VerifyMethod)
      {
        #if FOTA_VERIFY_BUFFER_USED
        if (FOTA_TRUE == Fota_VerifyBufferUsed)
        {
          jobResult = Fota_VerifyCsmJobStart(&dataReadRemainSize,
                                             &blockIndexProcessing,
                                             &dataVerifiedSize);
        }
        else
        #endif
        {
          jobResult = Fota_VerifyCsmJobStart(NULL_PTR, NULL_PTR,
                                             NULL_PTR);
        }
      }
      else if (FOTA_CRC_VERIFY == Fota_VerifyMethod)
      {
        #if FOTA_VERIFY_BUFFER_USED
        if (FOTA_TRUE == Fota_VerifyBufferUsed)
        {
          Fota_CRCInitDataPushBuffer(&dataReadRemainSize, &crcAreaNum,
                                     &dataVerifiedSize);
          jobResult = FOTA_JOB_OK;
        }
        else
        #endif
        {
          jobResult = Fota_CRCInitDataPushDirect();
        }
      }
      else
      {
        /* Do nothing */
      }
      /* polyspace-begin MISRA-C3:14.3 [Justified:Low] "if-condition depends on the configuration." */
      if (jobResult == FOTA_JOB_OK)
      {
        #if FOTA_VERIFY_BUFFER_USED
        if (FOTA_TRUE == Fota_VerifyBufferUsed)
        {
          FotaVerifyState = FOTA_STAT_VERIFY_BLOCK_READ;
        }
        else
        #endif
        {
          FotaVerifyState = FOTA_STAT_VERIFY_UPDATE;
        }
      }
      else if (jobResult == FOTA_JOB_FAILED)
      {
        #if (FOTA_DEV_ERROR_DETECT == STD_ON)
        /* Report Det Error */
        (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
          FOTA_MAIN_FUNCTION_SID, FOTA_E_VERIFY_CSM_START_FAILED);
        #endif
        FotaVerifyState = FOTA_STAT_VERIFY_ERR;
      }
      else
      {
        /* Do nothing */
      }
      /* polyspace-end MISRA-C3:14.3 [Justified:Low] "if-condition depends on the configuration." */
      break;
    #if FOTA_VERIFY_BUFFER_USED
    case FOTA_STAT_VERIFY_BLOCK_READ:
      /* @Trace: FOTA_SUD_API_00259 */
      retVal = Fota_VerifyBlockRead(dataReadRemainSize,
                                    blockIndexProcessing,
                                    crcAreaNum,
                                    dataVerifiedSize);
      if (retVal == E_OK)
      {
        memJobProcessing = FOTA_VERIFY_MEM_JOB_READ_FIRMWARE;
        FotaVerifyState = FOTA_STAT_VERIFY_MEM_JOB_CHECK;
      }
      else if (retVal == E_NOT_OK)
      {
        FotaVerifyState = FOTA_STAT_VERIFY_ERR;
      }
      else
      {
        /* Do nothing */
      }
      break;
    #endif
    case FOTA_STAT_VERIFY_UPDATE:
      /* @Trace: FOTA_SUD_API_00120 */
      if (FOTA_SIGNATURE_VERIFY == Fota_VerifyMethod)
      {
        #if FOTA_VERIFY_BUFFER_USED
        if (FOTA_TRUE == Fota_VerifyBufferUsed)
        {
          jobResult = Fota_VerifyCsmJobUpdateBuffer(&dataReadRemainSize,
                                              &blockIndexProcessing,
                                              &dataVerifiedSize);
        }
        else
        #endif
        {
          jobResult = Fota_VerifyCsmJobUpdateDirect();
        }
      }
      else if (FOTA_CRC_VERIFY == Fota_VerifyMethod)
      {
        #if FOTA_VERIFY_BUFFER_USED
        if (FOTA_TRUE == Fota_VerifyBufferUsed)
        {
          Fota_CalculateCRCBuffer(&dataReadRemainSize, &crcAreaNum,
                                  &dataVerifiedSize);
          jobResult = FOTA_JOB_OK;
        }
        else
        #endif
        {
          jobResult = Fota_CalculateCRCDirect();
        }
      }
      else
      {
        /* Do nothing */
      }

      if (jobResult == FOTA_JOB_OK)
      {
        /* Do nothing */
      }
      else if (jobResult == FOTA_JOB_FAILED)
      {
        #if (FOTA_DEV_ERROR_DETECT == STD_ON)
        /* Report Det Error */
        (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
          FOTA_MAIN_FUNCTION_SID, FOTA_E_VERIFY_CSM_UPDATE_FAILED);
        #endif
        FotaVerifyState = FOTA_STAT_VERIFY_ERR;
      }
      else
      {
        /* Do nothing */
      }
      break;
    #if FOTA_VERIFY_BUFFER_USED
    case FOTA_STAT_VERIFY_MEM_JOB_CHECK:
      /* @Trace: FOTA_SUD_API_00260 */
      memJobResult = Fota_PflsGetJobResult(Fota_MemoryInstance);
      if (MEM_JOB_OK == memJobResult)
      {
        if (FOTA_VERIFY_MEM_JOB_READ_SIGN == memJobProcessing)
        {
          FotaVerifyState = FOTA_STAT_VERIFY_START;
        }
        else if (FOTA_VERIFY_MEM_JOB_READ_FIRMWARE == memJobProcessing)
        {
          FotaVerifyState = FOTA_STAT_VERIFY_UPDATE;
        }
      }
      else if (MEM_JOB_FAILED == memJobResult)
      {
        FotaVerifyState = FOTA_STAT_VERIFY_ERR;
      }
      else
      {
        /* Do nothing */
      }
    break;
    #endif
    case FOTA_STAT_VERIFY_FINISH:
      /* @Trace: FOTA_SUD_API_00121 */
      if (FOTA_SIGNATURE_VERIFY == Fota_VerifyMethod)
      {
        jobResult = Fota_VerifyCsmJobFinish();
      }
      else if (FOTA_CRC_VERIFY == Fota_VerifyMethod)
      {
        jobResult = Fota_CRCGetResult();
      }
      else
      {
        /* Do nothing */
      }

      if (jobResult == FOTA_JOB_FAILED)
      {
        #if (FOTA_DEV_ERROR_DETECT == STD_ON)
        /* Report Det Error */
        (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
          FOTA_MAIN_FUNCTION_SID, FOTA_E_VERIFY_CSM_FINIISH_FAILED);
        #endif
        FotaVerifyState = FOTA_STAT_VERIFY_ERR;
      }
      else
      {
        FotaVerifyState = FOTA_STAT_VERIFY_CHECK;
      }
      break;

    case FOTA_STAT_VERIFY_CHECK:
      /* @Trace: FOTA_SUD_API_00122 */
      jobResult = Fota_CheckAllJobResult();

      /* polyspace-begin MISRA-C3:14.3 [Justified:Low] "if-condition depends on the configuration." */
      if (jobResult == FOTA_JOB_OK)
      {
        FotaVerifyState = FOTA_STAT_VERIFY_END;
      }
      else if (jobResult == FOTA_JOB_PENDING)
      {
        #if FOTA_VERIFY_BUFFER_USED
        if (FOTA_TRUE == Fota_VerifyBufferUsed)
        {
          /* All jobs are not handle, continue for remaining job */
          FotaVerifyState = FOTA_STAT_VERIFY_INFO_READ;
        }
        else
        #endif
        {
          /* All jobs are not handle, continue for remaining job */
          FotaVerifyState = FOTA_STAT_VERIFY_START;
        }
      }
      else if (jobResult == FOTA_JOB_FAILED)
      {
        FotaVerifyState = FOTA_STAT_VERIFY_ERR;
      }
      else
      {
        /* Do nothing */
      }
      /* polyspace-end MISRA-C3:14.3 [Justified:Low] "if-condition depends on the configuration." */
      break;

    case FOTA_STAT_VERIFY_END:  
      /* @Trace: FOTA_SUD_API_00123 */   
      Fota_SetVerifyJobResult(FOTA_JOB_OK);
      FotaVerifyState = FOTA_STAT_VERIFY_INACTIVE;
      /* polyspace-begin MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation. This function is for User." */
      Fota_AfterFlashReadFunc();
      /* polyspace-end MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation. This function is for User." */
      break;

    case FOTA_STAT_VERIFY_ERR:
    default:
      /* @Trace: FOTA_SUD_API_00261 */
      Fota_SetVerifyJobResult(FOTA_JOB_FAILED);
      FotaVerifyState = FOTA_STAT_VERIFY_INACTIVE;
      /* polyspace-begin MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation. This function is for User." */
      Fota_AfterFlashReadFunc();
      /* polyspace-end MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation. This function is for User." */
      break;
  }
}
/*******************************************************************************
** Function Name        : Fota_CRCInitDataPushBuffer                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Init data for caculation CRC                        **
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
#if FOTA_VERIFY_BUFFER_USED
static FUNC(void, FOTA_CODE) Fota_CRCInitDataPushBuffer(
                                                  uint32 *dataReadRemainSize,
                                                  uint16 *crcAreaNum,
                                                  uint32 *dataVerifiedSize)
{
  /* @Trace: FOTA_SUD_API_00137 */
  uint16 initVerifyCRC = 0;

  initVerifyCRC =
    Fota_CrcInfo->InitCrc[INIT_CRC_LEN - CRC_INIT_HIBYTE_OFF];

  initVerifyCRC = initVerifyCRC << 8;

  initVerifyCRC |=
  Fota_CrcInfo->InitCrc[INIT_CRC_LEN - CRC_INIT_LOBYTE_OFF];

  Fota_CalcVerifyCRC = initVerifyCRC;

  *crcAreaNum = 0;

  *dataReadRemainSize = Fota_CrcInfo->CrcArea[*crcAreaNum].EndAddress -
    Fota_CrcInfo->CrcArea[*crcAreaNum].StartAddress + 1;

  *dataVerifiedSize = 0;
}
#endif
/*******************************************************************************
** Function Name        : Fota_CRCInitDataPushDirect                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Init data for caculation CRC                        **
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
static FUNC(Fota_JobResultType, FOTA_CODE) Fota_CRCInitDataPushDirect(void)
{
  Fota_JobResultType jobResult;
  Std_ReturnType retVal = E_NOT_OK;
  Fota_VerificationSwUnitType *ptrHandler;
  const Fota_TargetBlockSwUnitType *signaturePtr;
  uint32 crcInfoAddress;
  uint32 crcInfoSize;
  /* @Trace: FOTA_SUD_API_00138 */
  /* polyspace-begin MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
  uint16 initVerifyCRC = 0;
  crcInfoSize = sizeof(Fota_CrcInfoType);
  ptrHandler = &Fota_PtrSWUnitHandler[Fota_JobIndexProcessing];
  signaturePtr = ptrHandler->VerifySignature;
  crcInfoAddress = signaturePtr->StartAddress;
  jobResult = FOTA_JOB_OK;
  /* polyspace-end MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
  
  /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
  if(FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)
  {	
    /* polyspace-begin DEFECT:PTR_CAST, MISRA-C3:11.3 [Justified:Medium] "The integer value represents the register address. It should be casted to an address so that
    * the register value can be read via the address" */
    /* polyspace-begin CERT-C:EXP39-C [Justified:Low] "This conversion is used for OSS. they are same type" */
    retVal = Fota_PflsGetCovAddr(Fota_MemoryInstance,
    		                     FOTA_ALT_ADDR,
								 &crcInfoAddress,
								 &crcInfoSize);
    /* polyspace-end DEFECT:PTR_CAST, MISRA-C3:11.3 [Justified:Medium] "The integer value represents the register address. It should be casted to an address so that
    * the register value can be read via the address" */
    /* polyspace-end CERT-C:EXP39-C [Justified:Low] "This conversion is used for OSS. they are same type" */
  }
  else
  {
    retVal = E_OK;
  }
  /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
  /* @Trace: FOTA_SUD_API_00139 */
  /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
  if (E_OK == retVal)
  {
    crcInfoAddress = crcInfoAddress - INIT_CRC_LEN;

    /* polyspace-begin CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
    * the register value can be read via the address" */
    FOTA_MEMCPY((uint8 *)Fota_CrcInfo, (uint8 *)crcInfoAddress, sizeof(Fota_CrcInfoType));
    /* polyspace-end CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
    * the register value can be read via the address" */

    initVerifyCRC =
      Fota_CrcInfo->InitCrc[INIT_CRC_LEN-CRC_INIT_HIBYTE_OFF];

    initVerifyCRC = initVerifyCRC << 8;

    initVerifyCRC |=
    Fota_CrcInfo->InitCrc[INIT_CRC_LEN-CRC_INIT_LOBYTE_OFF];

    Fota_CalcVerifyCRC = initVerifyCRC;
    jobResult = FOTA_JOB_OK;
  }
  else
  {
    jobResult = FOTA_JOB_FAILED;
  }
  /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
  return jobResult;
}
/*******************************************************************************
** Function Name        : Fota_Crc16CoverArea                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Caculate CRC16                                      **
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
FUNC(uint16, FOTA_CODE) Fota_Crc16CoverArea(
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) data,
  VAR(uint32, AUTOMATIC) length,
  VAR(uint16, AUTOMATIC) crc
)
{
  /* @Trace: FOTA_SUD_API_00112 */
  uint16 ret_crc;
  uint32 length_temp;
  uint32 data_cnt;

  length_temp=length;
  ret_crc=crc;
  data_cnt=0u;

  if (data != NULL_PTR)
  {
    while (length_temp > 0UL)
    {
      ret_crc = (ret_crc >> 8) ^ (uint16)Fota_Gau16_CRCA001_8[(ret_crc ^ (data[data_cnt])) & 0xFFU];
      length_temp--;
      data_cnt++;
    }
  }
  return ret_crc;
}
/*******************************************************************************
** Function Name        : Fota_CalculateCRCBuffer                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Calculate CRC for each block                        **
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
#if FOTA_VERIFY_BUFFER_USED
static FUNC(void, FOTA_CODE) Fota_CalculateCRCBuffer(uint32 *dataReadRemainSize,
                                               uint16 *crcAreaNum,
                                               uint32 *dataVerifiedSize)
{
  /* @Trace: FOTA_SUD_API_00144 */
  Fota_CalcVerifyCRC = Fota_Crc16CoverArea(Fota_DataReadBuffer,
                                          Fota_DataSizeOneCycle,
                                          Fota_CalcVerifyCRC);

  *dataReadRemainSize -= Fota_DataSizeOneCycle;
  *dataVerifiedSize += Fota_DataSizeOneCycle;

  if (*dataReadRemainSize == 0)
  {
    *crcAreaNum = *crcAreaNum + 1;
    if (*crcAreaNum < Fota_CrcInfo->NumberOfCrcAreas)
    {
      *dataReadRemainSize = Fota_CrcInfo->CrcArea[*crcAreaNum].EndAddress -
        Fota_CrcInfo->CrcArea[*crcAreaNum].StartAddress + 1;

      *dataVerifiedSize = 0;
      FotaVerifyState = FOTA_STAT_VERIFY_BLOCK_READ;
    }
    else
    {
      FotaVerifyState = FOTA_STAT_VERIFY_FINISH;
    }
  }
  else
  {
    FotaVerifyState = FOTA_STAT_VERIFY_BLOCK_READ;
  }
}
#endif
/*******************************************************************************
** Function Name        : Fota_CalculateCRCDirect                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Calculate CRC for each block                        **
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
static FUNC(Fota_JobResultType, FOTA_CODE) Fota_CalculateCRCDirect(void)
{
  /* @Trace: FOTA_SUD_API_00145 */
  Std_ReturnType retVal=E_OK;
  Fota_JobResultType jobResult;
  uint32 dataVerifySize;
  uint32 startAddress;
  static uint32 dataVerifiedSize = 0;
  static uint32 dataRemainSize = 0;
  static uint32 startAddressVerify;
  static uint16 crcAreaNum = 0;

  /* polyspace-begin MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
  jobResult = FOTA_JOB_FAILED;
  /* polyspace-end MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
  if (dataRemainSize == 0)
  {
    dataVerifiedSize = 0;
    startAddress  = Fota_CrcInfo->CrcArea[crcAreaNum].StartAddress;
    dataRemainSize = Fota_CrcInfo->CrcArea[crcAreaNum].EndAddress -
                 Fota_CrcInfo->CrcArea[crcAreaNum].StartAddress + 1;

    #if(FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)

    /* polyspace-begin DEFECT:PTR_CAST, MISRA-C3:11.3 [Justified:Medium] "The integer value represents the register address. It should be casted to an address so that
    * the register value can be read via the address" */
    /* polyspace-begin CERT-C:EXP39-C [Justified:Low] "This conversion is used for OSS. they are same type" */
    retVal = Fota_PflsGetCovAddr(Fota_MemoryInstance,
    		                     FOTA_ALT_ADDR,
								 &startAddress,
								 &dataRemainSize);
    /* polyspace-end DEFECT:PTR_CAST, MISRA-C3:11.3 [Justified:Medium] "The integer value represents the register address. It should be casted to an address so that
    * the register value can be read via the address" */
    /* polyspace-end CERT-C:EXP39-C [Justified:Low] "This conversion is used for OSS. they are same type" */

    #else
    retVal = E_OK;
    #endif
    startAddressVerify = startAddress;
  }
  /* @Trace: FOTA_SUD_API_00146 */
  /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
  if (E_OK == retVal)
  {
    if (dataRemainSize > CODE_FLASH_VERIFY_SIZE_OF_ONECYCLE)
    {
      dataVerifySize = CODE_FLASH_VERIFY_SIZE_OF_ONECYCLE;
    }
    else
    {
      dataVerifySize = dataRemainSize;
    }
	
    /* polyspace-begin CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
    * the register value can be read via the address" */
    /* polyspace-begin MISRA-C3:18.4 [Justified:Low] "Decrement and Increment operator is used to achieve better throughput" */
    Fota_CalcVerifyCRC = Fota_Crc16CoverArea((uint8 *)startAddressVerify + dataVerifiedSize,
                                          dataVerifySize,
                                          Fota_CalcVerifyCRC);
    /* polyspace-end CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
    * the register value can be read via the address" */
    /* polyspace-end MISRA-C3:18.4 [Justified:Low] "Decrement and Increment operator is used to achieve better throughput" */

    dataVerifiedSize += dataVerifySize;
    dataRemainSize -= dataVerifySize;

    if (dataRemainSize == 0)
    {
      crcAreaNum++;
      if (crcAreaNum >= Fota_CrcInfo->NumberOfCrcAreas)
      {
        crcAreaNum = 0;
        dataVerifiedSize = 0;
        FotaVerifyState = FOTA_STAT_VERIFY_FINISH;
        jobResult = FOTA_JOB_OK;
      }
      else
      {
        jobResult = FOTA_JOB_PENDING;
      }
    }
    else
    {
      jobResult = FOTA_JOB_PENDING;
    }
  }
  else
  {
    jobResult = FOTA_JOB_FAILED;
  }
  /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */

  return jobResult;
}
/*******************************************************************************
** Function Name        : Fota_CRCGetResult                                   **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get result of verification CRC                      **
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
static FUNC(Fota_JobResultType, FOTA_CODE) Fota_CRCGetResult(void)
{
  /* @Trace: FOTA_SUD_API_00148 */
  Fota_JobResultType jobResult = FOTA_JOB_FAILED;
  Fota_VerificationSwUnitType *ptrHandler;

  if (Fota_CalcVerifyCRC == Fota_CrcInfo->CrcValue)
  {
    ptrHandler = &Fota_PtrSWUnitHandler[Fota_JobIndexProcessing];
    ptrHandler->VerifyJobState = FOTA_CSM_JOB_FINISHED;
    ptrHandler->VerifyJobResult = FOTA_CSM_E_OK;
    jobResult = FOTA_JOB_OK;
  }

  return jobResult;
}
/*******************************************************************************
** Function Name        : Fota_GetSecureFlashPublicKeyByDelimiter             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check delimiter type and get pubic key              **
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
/* @Trace: FOTA_SRS_ES95489_52E_00002 FOTA_SRS_ES95489_52E_00003 */
/* @Trace: FOTA_SRS_ES95489_52E_00006 FOTA_SRS_ES95489_52E_00007 */
static FUNC(Std_ReturnType, FOTA_CODE) Fota_GetSecureFlashPublicKeyByDelimiter(
  P2VAR(uint8, AUTOMATIC, FOTA_PRIVATE_DATA) rul_Delimiter
)
{
  /* @Trace: FOTA_SUD_API_00133 */
  Std_ReturnType Ldt_RetValue = E_NOT_OK;
  uint8 Lu8_SwIndex;
  uint8 Lu8_MaxIndex;
  SFSign_MadeBy Ldt_CheckDelimiter = SF_MADEBY_NONE;
  /*---------------------------------------------*
  *| Secure Flash 2.0 Signaure                  |*
  *|-----------+-------+------------------------+*
  *|           | size  | data                   |*
  *|-----------+-------+------------------------+*
  *| Delimiter | 4byte | many kinds             |*
  *|-----------+-------+------------------------+*
  *| Length    | 4byte | 0x00, 0x00, 0x01, 0x00 |*
  -+--------------------------------------------+*/

  Lu8_MaxIndex = (uint8)sizeof(Sec_Gau8_Asims_Delimiter)/(0x04);

  for(Lu8_SwIndex = 0; Lu8_SwIndex < Lu8_MaxIndex; Lu8_SwIndex++)
  {
    if((rul_Delimiter[0]==Sec_Gau8_Asims_Delimiter[Lu8_SwIndex][0])&&
         (rul_Delimiter[1]==Sec_Gau8_Asims_Delimiter[Lu8_SwIndex][1])&&
         (rul_Delimiter[2]==Sec_Gau8_Asims_Delimiter[Lu8_SwIndex][2])&&
         (rul_Delimiter[3]==Sec_Gau8_Asims_Delimiter[Lu8_SwIndex][3]))
    {
      Ldt_CheckDelimiter = SF_MADEBY_ASIMS;
      Fota_SFSignChkCmd[Fota_JobIndexProcessing].PublicKeyBuffer =
        Fota_Sec_Gau8_ImageServPubKeyAsims;
      /* polyspace-begin MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
      Ldt_RetValue=E_OK;
      /* polyspace-end MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
      break;
    }
  }
  /* @Trace: FOTA_SUD_API_00134 */
  if (Ldt_CheckDelimiter == SF_MADEBY_NONE)
  {
    Lu8_MaxIndex = (uint8)sizeof(Sec_Gau8_Fst_Delimiter)/(0x04);

    for(Lu8_SwIndex = 0; Lu8_SwIndex < Lu8_MaxIndex; Lu8_SwIndex++)
    {
      if((rul_Delimiter[0]==Sec_Gau8_Fst_Delimiter[Lu8_SwIndex][0])&&
         (rul_Delimiter[1]==Sec_Gau8_Fst_Delimiter[Lu8_SwIndex][1])&&
         (rul_Delimiter[2]==Sec_Gau8_Fst_Delimiter[Lu8_SwIndex][2])&&
         (rul_Delimiter[3]==Sec_Gau8_Fst_Delimiter[Lu8_SwIndex][3]))
      {
        Ldt_CheckDelimiter = SF_MADEBY_FST;
        Fota_SFSignChkCmd[Fota_JobIndexProcessing].PublicKeyBuffer =
          Fota_Sec_Gau8_ImageServPubKeyFst;
        /* polyspace-begin MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
        Ldt_RetValue=E_OK;
        /* polyspace-end MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
        break;
      }
    }
  }

  if (Ldt_CheckDelimiter == SF_MADEBY_NONE)
  {
    Ldt_RetValue = E_NOT_OK;
  }
  else
  {
    /* check signature length */
    if((rul_Delimiter[4]==Sec_Gau8_Signature_Length[0])&&
         (rul_Delimiter[5]==Sec_Gau8_Signature_Length[1])&&
         (rul_Delimiter[6]==Sec_Gau8_Signature_Length[2])&&
         (rul_Delimiter[7]==Sec_Gau8_Signature_Length[3]))
    {
      Ldt_RetValue=E_OK;
    }
    else
    {
      Ldt_RetValue=E_NOT_OK;
    }
  }

  return Ldt_RetValue;
}
/*******************************************************************************
** Function Name        : Fota_SignInitDataPush                               **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Get signature data                                  **
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
/* @Trace: FOTA_SRS_ES95489_52E_00002 FOTA_SRS_ES95489_52E_00003 */
/* @Trace: FOTA_SRS_ES95489_52E_00006 FOTA_SRS_ES95489_52E_00007 */
/* @Trace: FOTA_SRS_ES95489_52E_00008 */
static FUNC(Std_ReturnType, FOTA_CODE) Fota_SignInitDataPush(
  VAR(uint32, AUTOMATIC) signatureAddress)
{
  /* @Trace: FOTA_SUD_API_00132 */
  Std_ReturnType retVal;
  /* polyspace-begin CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
  * the register value can be read via the address" */
  if (Fota_GetSecureFlashPublicKeyByDelimiter(
    (uint8 *)signatureAddress) == E_OK)
  {
    Fota_SFSignChkCmd[Fota_JobIndexProcessing].SignatureBuffer =
      (uint8*)(signatureAddress + (SEC_SF_SIGNATURE_DELIMITER_LENGTH +
                                   SEC_SF_SIGNATURE_SIZE_LENGTH));
    retVal = E_OK;
  }
  else
  {
    retVal = E_NOT_OK;
  }
  /* polyspace-end CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
  * the register value can be read via the address" */
  return retVal;
}
/*******************************************************************************
** Function Name        : Fota_VerifyInitProcess                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Init data for verification operation                **
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
/* @Trace: FOTA_SRS_ES95489_52E_00008 */
static FUNC(Std_ReturnType, FOTA_CODE) Fota_VerifyInitProcess(void)
{
  /* @Trace: FOTA_SUD_API_00124 */
  uint8 jobIndex;
  Std_ReturnType retVal;
  Fota_VerificationSwUnitType *ptrHandler;
  const Fota_VerificationType *ptrVerification;
  const Fota_SwModule *swUnitHandlePtr;
  const Fota_TargetBlockSwUnitType *signaturePtr;

  swUnitHandlePtr = &Fota_Gast_SwUnitTable[Fota_ProgrammingSWUnitId];

  Fota_JobIndexProcessing = 0;
  retVal = E_OK;

  ptrVerification = swUnitHandlePtr->VerificationInfoPtr;

  Fota_PtrSWUnitHandler = ptrVerification->VerificationSWUnit;

  ptrHandler = &Fota_PtrSWUnitHandler[Fota_JobIndexProcessing];
  #if FOTA_VERIFY_BUFFER_USED
  Fota_VerifyBufferUsed = ptrHandler->VerifyBufferUsed;
  #endif

  signaturePtr = ptrHandler->VerifySignature;

  if (FOTA_SIGNATURE == signaturePtr->BlockType)
  {
    Fota_VerifyMethod = FOTA_SIGNATURE_VERIFY;
  }
  else if (FOTA_CRC == signaturePtr->BlockType)
  {
    Fota_VerifyMethod = FOTA_CRC_VERIFY;
  }
  else
  {
	retVal = E_NOT_OK;
  }

  if (E_OK == retVal)
  {
	  Fota_NumOfVerification = ptrVerification->NumOfVerification;

	  for (jobIndex = 0; jobIndex < Fota_NumOfVerification; jobIndex++)
	  {
	    ptrHandler = &Fota_PtrSWUnitHandler[jobIndex];
	    ptrHandler->VerifyJobState = FOTA_CSM_JOB_IDLE;
	    ptrHandler->VerifyJobResult = FOTA_CSM_E_OK;
	  }
  }
  return retVal;
}
/*******************************************************************************
** Function Name        : Fota_VerifyReadInfo                                 **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Init data for verification operation                **
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
/* @Trace: FOTA_SRS_ES95489_52E_00008 */
#if FOTA_VERIFY_BUFFER_USED
static FUNC(Std_ReturnType, FOTA_CODE) Fota_VerifyReadInfo(void)
{
  /* @Trace: FOTA_SUD_API_00126 */
  Std_ReturnType retVal;
  Fota_VerificationSwUnitType *ptrHandler;
  const Fota_TargetBlockSwUnitType *signaturePtr;

  retVal = E_NOT_OK;
  ptrHandler = &Fota_PtrSWUnitHandler[Fota_JobIndexProcessing];

  signaturePtr = ptrHandler->VerifySignature;

  Fota_RequestSTDOrALTAccess();

  if (FOTA_SIGNATURE == signaturePtr->BlockType)
  {
    retVal = Fota_PflsReadRequest(Fota_MemoryInstance, \
                                  signaturePtr->StartAddress, \
                                  Fota_SignatureReadData, (SEC_SF_SIGNATURE_DELIMITER_LENGTH +
                                                            SEC_SF_SIGNATURE_SIZE_LENGTH +
                                                            SEC_SF_SIGNATURE_SIZE));
  }
  else if (FOTA_CRC == signaturePtr->BlockType)
  {
    retVal = Fota_PflsReadRequest(Fota_MemoryInstance, \
                                  signaturePtr->StartAddress - INIT_CRC_LEN, \
                                  (uint8 *)Fota_CrcInfo, sizeof(Fota_CrcInfoType));
  }
  else
  {
    /* Do nothing */
  }

  return retVal;
}
#endif
/*******************************************************************************
** Function Name        : Fota_VerifyCsmJobStart                              **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Init sequence and start Csm job service             **
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
/* @Trace: FOTA_SRS_ES95489_52E_00002 FOTA_SRS_ES95489_52E_00008 FOTA_SRS_GENSEC_00006 */
static FUNC(Fota_JobResultType, FOTA_CODE) Fota_VerifyCsmJobStart(
  uint32 *dataReadRemainSize,
  uint16 *blockIndexProcessing,
  uint32 *dataVerifiedSize)
{
  /* @Trace: FOTA_SUD_API_00130 */
  Std_ReturnType retVal;
  Fota_JobResultType result;
  Crypto_VerifyResultType verifyResult;

  Fota_VerificationSwUnitType *ptrHandler;
  #if FOTA_VERIFY_BUFFER_USED
  const Fota_TargetBlockSwUnitType *targetBlockPtr;
  #endif
  const Fota_TargetBlockSwUnitType *ptrBlockSignature;
  uint32 signatureAddress;
  uint32 signatureSize;
  result = FOTA_JOB_FAILED;
  /* polyspace-begin MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
  retVal = E_NOT_OK;
  /* polyspace-end MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */

  ptrHandler = &Fota_PtrSWUnitHandler[Fota_JobIndexProcessing];

  ptrBlockSignature = ptrHandler->VerifySignature;

  #if FOTA_VERIFY_BUFFER_USED
  if (FOTA_TRUE == Fota_VerifyBufferUsed)
  {
    retVal = Fota_SignInitDataPush((uint32)&Fota_SignatureReadData[0]);
  }
  else
  #endif
  {
    signatureAddress = ptrBlockSignature->StartAddress;
    /* polyspace-begin MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
    signatureSize = FOTA_VERIFY_SIGNATURE_LEN;
    /* polyspace-end MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */

    /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
    if(FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)
    {
      /* polyspace-begin DEFECT:PTR_CAST, MISRA-C3:11.3 [Justified:Medium] "The integer value represents the register address. It should be casted to an address so that
      * the register value can be read via the address" */
      /* polyspace-begin CERT-C:EXP39-C [Justified:Low] "This conversion is used for OSS. they are same type" */
      retVal = Fota_PflsGetCovAddr(Fota_MemoryInstance,
      		                     FOTA_ALT_ADDR,
  								 &signatureAddress,
  								 &signatureSize);
      /* polyspace-end DEFECT:PTR_CAST, MISRA-C3:11.3 [Justified:Medium] "The integer value represents the register address. It should be casted to an address so that
      * the register value can be read via the address" */
      /* polyspace-end CERT-C:EXP39-C [Justified:Low] "This conversion is used for OSS. they are same type" */

    }
    else
    {
      retVal = E_OK;
    }

    if (retVal == E_OK)
    {
      retVal = Fota_SignInitDataPush(signatureAddress);
    }
    /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
  }
  /* @Trace: FOTA_SUD_API_00131 */
  if (retVal == E_OK)
  {
    retVal = Csm_KeyElementSet(ptrHandler->VerifyCsmKeyId,
                               ptrHandler->VerifyCsmKeyElementId,
                               Fota_SFSignChkCmd[Fota_JobIndexProcessing].PublicKeyBuffer,
                               ptrHandler->VerifyCsmKeyLength);

    if (retVal == E_OK)
    {
       retVal = Csm_KeySetValid(ptrHandler->VerifyCsmKeyId);

      if (retVal == E_OK)
      {
        retVal = Csm_SignatureVerify(ptrHandler->VerifyCsmJobId,
                   CRYPTO_OPERATIONMODE_START,
                   NULL_PTR, 0,
                   Fota_SFSignChkCmd[Fota_JobIndexProcessing].SignatureBuffer,
                   FOTA_VERIFY_SIGNATURE_LEN,
                   &verifyResult);

        if (retVal == E_OK)
        {
          #if FOTA_VERIFY_BUFFER_USED
          if (FOTA_TRUE == Fota_VerifyBufferUsed)
          {
            targetBlockPtr = ptrHandler->VerifyTargetBlock;
            *blockIndexProcessing = 0;

            *dataReadRemainSize = targetBlockPtr[*blockIndexProcessing].EndAddress -
              targetBlockPtr[*blockIndexProcessing].StartAddress + 1;

            *dataVerifiedSize = 0;
          }
          #else
          FOTA_UNUSED(dataReadRemainSize);
          FOTA_UNUSED(blockIndexProcessing);
          FOTA_UNUSED(dataVerifiedSize);
          #endif
          result = FOTA_JOB_OK;
        }
      }
    }
    
    if(retVal == CRYPTO_E_BUSY) // CRYPTO_E_BUSY 0x02
    {
      /* Wait until CRYPTO_E_BUSY end */
      result = FOTA_JOB_PENDING;
    }
  } 

  return result;
}
/*******************************************************************************
** Function Name        : Fota_CheckAllJobResult                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Check all number of verification are successfully   **
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
/* @Trace: FOTA_SRS_ES95489_52E_00008 */
static FUNC(Fota_JobResultType, FOTA_CODE) Fota_CheckAllJobResult(void)
{
  /* @Trace: FOTA_SUD_API_00149 */
  uint8 jobIndex;
  uint8 countJobOk;
  Fota_JobResultType result;
  Fota_VerificationSwUnitType *ptrHandler;
  const Fota_TargetBlockSwUnitType *signaturePtr;

  result = FOTA_JOB_FAILED;
  countJobOk = 0;

  for (jobIndex = 0; jobIndex < Fota_NumOfVerification; jobIndex++)
  {
    ptrHandler = &Fota_PtrSWUnitHandler[jobIndex];

    if (FOTA_CSM_JOB_IDLE == ptrHandler->VerifyJobState)
    {
      /* Job is not handled, break function and start new sequence */
      #if FOTA_VERIFY_BUFFER_USED
      Fota_VerifyBufferUsed = ptrHandler->VerifyBufferUsed;
      #endif
      signaturePtr = ptrHandler->VerifySignature;

      if (FOTA_SIGNATURE == signaturePtr->BlockType)
      {
        Fota_VerifyMethod = FOTA_SIGNATURE_VERIFY;
      }
      else
      {
        Fota_VerifyMethod = FOTA_CRC_VERIFY;
      }
      Fota_JobIndexProcessing = jobIndex;
      result = FOTA_JOB_PENDING;
      break;
    }
    else if (FOTA_CSM_JOB_FINISHED == ptrHandler->VerifyJobState)
    {
      if (FOTA_CSM_E_OK == ptrHandler->VerifyJobResult)
      {
        countJobOk++;
      }
    }
    else
    {
      /* Do Nothing */
    }
  }
  if (countJobOk == Fota_NumOfVerification)
  {
    result = FOTA_JOB_OK;
  }
  return result;
}
/*******************************************************************************
** Function Name        : Fota_VerifyCsmJobFinish                             **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Finish Csm job service                              **
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
/* @Trace: FOTA_SRS_ES95489_52E_00002 FOTA_SRS_ES95489_52E_00008 FOTA_SRS_GENSEC_00006 */
static FUNC(Fota_JobResultType, FOTA_CODE) Fota_VerifyCsmJobFinish(void)
{
  /* @Trace: FOTA_SUD_API_00147 */
  Crypto_VerifyResultType verifyResult;
  Fota_JobResultType jobResult;
  Fota_VerificationSwUnitType *ptrHandler;
  Std_ReturnType retVal;

  jobResult = FOTA_JOB_OK;
  /* polyspace-begin MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
  retVal = E_NOT_OK;
  /* polyspace-end MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */

  ptrHandler = &Fota_PtrSWUnitHandler[Fota_JobIndexProcessing];

  retVal = Csm_SignatureVerify(ptrHandler->VerifyCsmJobId,
             CRYPTO_OPERATIONMODE_FINISH,
             NULL_PTR, 0,
             Fota_SFSignChkCmd[Fota_JobIndexProcessing].SignatureBuffer,
             FOTA_VERIFY_SIGNATURE_LEN,
             &verifyResult);

  if (E_OK == retVal)
  {
    ptrHandler->VerifyJobState = FOTA_CSM_JOB_FINISHED;

    if (CRYPTO_E_VER_OK == verifyResult)
    {
      ptrHandler->VerifyJobResult = FOTA_CSM_E_OK;
    }
    else
    {
      ptrHandler->VerifyJobResult = FOTA_CSM_E_NOT_OK;
    }
  }
  else
  {
    jobResult = FOTA_JOB_FAILED;
  }

  return jobResult;
}
/*******************************************************************************
** Function Name        : Fota_VerifyBlockRead                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Update Csm job service                              **
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
/* @Trace: FOTA_SRS_ES95489_52E_00008 FOTA_SRS_ES98765_02E_00020 FOTA_SRS_UDS_00025 */
#if FOTA_VERIFY_BUFFER_USED
static FUNC(Std_ReturnType, FOTA_CODE) Fota_VerifyBlockRead(
  uint32 dataReadRemainSize,
  uint16 blockIndexProcessing,
  uint16 crcAreaNum,
  uint32 dataVerifiedSize)
{
  /* @Trace: FOTA_SUD_API_00140 */
  Std_ReturnType retVal;
  const Fota_TargetBlockSwUnitType *targetBlockPtr;
  Fota_VerificationSwUnitType *ptrHandler;

  retVal = E_NOT_OK;
  ptrHandler = &Fota_PtrSWUnitHandler[Fota_JobIndexProcessing];
  targetBlockPtr = ptrHandler->VerifyTargetBlock;

  if (FOTA_SIGNATURE_VERIFY == Fota_VerifyMethod)
  {
    if (dataReadRemainSize >= ptrHandler->VerifyMaxDataSizeOneCycle)
    {
      Fota_DataSizeOneCycle = ptrHandler->VerifyMaxDataSizeOneCycle;
    }
    else
    {
      Fota_DataSizeOneCycle = dataReadRemainSize;
    }

    retVal = Fota_PflsReadRequest(Fota_MemoryInstance,
                                  targetBlockPtr[blockIndexProcessing].StartAddress +
                                  dataVerifiedSize,
                                  Fota_DataReadBuffer, Fota_DataSizeOneCycle);
  }
  else if (FOTA_CRC_VERIFY == Fota_VerifyMethod)
  {
    if (dataReadRemainSize >= ptrHandler->VerifyMaxDataSizeOneCycle)
    {
      Fota_DataSizeOneCycle = ptrHandler->VerifyMaxDataSizeOneCycle;
    }
    else
    {
      Fota_DataSizeOneCycle = dataReadRemainSize;
    }

    retVal = Fota_PflsReadRequest(Fota_MemoryInstance,
                                  (uint32)(Fota_CrcInfo->CrcArea[crcAreaNum].StartAddress) +
                                  dataVerifiedSize,
                                  Fota_DataReadBuffer, Fota_DataSizeOneCycle);
  }
  else
  {
    /* Do nothing */
  }
  return retVal;
}
#endif
/*******************************************************************************
** Function Name        : Fota_VerifyCsmJobUpdateBuffer                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Update Csm job service                              **
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
/* @Trace: FOTA_SRS_ES95489_52E_00002 FOTA_SRS_ES95489_52E_00008 FOTA_SRS_GENSEC_00006 */
#if FOTA_VERIFY_BUFFER_USED
static FUNC(Fota_JobResultType, FOTA_CODE) Fota_VerifyCsmJobUpdateBuffer(
  uint32 *dataReadRemainSize,
  uint16 *blockIndexProcessing,
  uint32 *dataVerifiedSize)
{
  /* @Trace: FOTA_SUD_API_00141 */
  Crypto_VerifyResultType verifyResult;
  Std_ReturnType retVal;
  Fota_JobResultType jobResult;
  Fota_VerificationSwUnitType *ptrHandler;
  const Fota_TargetBlockSwUnitType *targetBlockPtr;

  jobResult = FOTA_JOB_FAILED;
  retVal = E_NOT_OK;

  ptrHandler = &Fota_PtrSWUnitHandler[Fota_JobIndexProcessing];
  targetBlockPtr = ptrHandler->VerifyTargetBlock;

  retVal = Csm_SignatureVerify(ptrHandler->VerifyCsmJobId,
             CRYPTO_OPERATIONMODE_UPDATE,
             Fota_DataReadBuffer, Fota_DataSizeOneCycle,
             Fota_SFSignChkCmd[Fota_JobIndexProcessing].SignatureBuffer,
             FOTA_VERIFY_SIGNATURE_LEN,
             &verifyResult);

  if (E_OK == retVal)
  {
    ptrHandler->VerifyJobState = FOTA_CSM_JOB_UPDATED;

    *dataReadRemainSize -= Fota_DataSizeOneCycle;
    *dataVerifiedSize += Fota_DataSizeOneCycle;

    if (*dataReadRemainSize == 0)
    {
      *blockIndexProcessing = *blockIndexProcessing + 1;
      if (*blockIndexProcessing < ptrHandler->VerifyNumberOfBlock)
      {
        *dataReadRemainSize = targetBlockPtr[*blockIndexProcessing].EndAddress -
          targetBlockPtr[*blockIndexProcessing].StartAddress + 1;

        *dataVerifiedSize = 0;

        FotaVerifyState = FOTA_STAT_VERIFY_BLOCK_READ;
      }
      else
      {
        FotaVerifyState = FOTA_STAT_VERIFY_FINISH;
      }
    }
    else
    {
      FotaVerifyState = FOTA_STAT_VERIFY_BLOCK_READ;
    }
    jobResult = FOTA_JOB_OK;
  }
  else
  {

  }
  return jobResult;
}
#endif
/*******************************************************************************
** Function Name        : Fota_VerifyCsmJobUpdateDirect                       **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Update Csm job service                              **
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
/* @Trace: FOTA_SRS_ES95489_52E_00002 FOTA_SRS_ES95489_52E_00008 FOTA_SRS_GENSEC_00006 */
static FUNC(Fota_JobResultType, FOTA_CODE) Fota_VerifyCsmJobUpdateDirect(void)
{
  /* @Trace: FOTA_SUD_API_00142 */
  Crypto_VerifyResultType verifyResult;
  Std_ReturnType retVal;
  Fota_JobResultType jobResult;
  Fota_VerificationSwUnitType *ptrHandler;
  const Fota_TargetBlockSwUnitType *targetBlockPtr;
  uint32 startAddressVerify;
  uint32 dataSize;
  uint16 blockIndex;

  jobResult = FOTA_JOB_FAILED;
  /* polyspace-begin MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */
  retVal = E_NOT_OK;
  /* polyspace-end MISRA-C3:2.2 [Not a defect:Low] "No Impact of this rule violation" */

  ptrHandler = &Fota_PtrSWUnitHandler[Fota_JobIndexProcessing];
  targetBlockPtr = ptrHandler->VerifyTargetBlock;
  blockIndex = 0;
  do
  {
    startAddressVerify  = targetBlockPtr[blockIndex].StartAddress;
    dataSize = targetBlockPtr[blockIndex].EndAddress - startAddressVerify + 1;
	
    /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
    if(FOTA_MCU_MEMORY_ACCESS_TYPE==FOTA_MMU_TYPE)
    {
      /* polyspace-begin DEFECT:PTR_CAST, MISRA-C3:11.3 [Justified:Medium] "The integer value represents the register address. It should be casted to an address so that
      * the register value can be read via the address" */
      /* polyspace-begin CERT-C:EXP39-C [Justified:Low] "This conversion is used for OSS. they are same type" */
      retVal = Fota_PflsGetCovAddr(Fota_MemoryInstance,
      		                     FOTA_ALT_ADDR,
  								 &startAddressVerify,
  								 &dataSize);
      /* polyspace-end DEFECT:PTR_CAST, MISRA-C3:11.3 [Justified:Medium] "The integer value represents the register address. It should be casted to an address so that
      * the register value can be read via the address" */
      /* polyspace-end CERT-C:EXP39-C [Justified:Low] "This conversion is used for OSS. they are same type" */
    }
    else
    {
      retVal = E_OK;
    }

    if (E_OK == retVal)
    {
      /* polyspace-begin CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
      * the register value can be read via the address" */
      retVal = Csm_SignatureVerify(ptrHandler->VerifyCsmJobId,
                 CRYPTO_OPERATIONMODE_UPDATE,
                 (const uint8*)startAddressVerify, dataSize,
                 Fota_SFSignChkCmd[Fota_JobIndexProcessing].SignatureBuffer,
                 FOTA_VERIFY_SIGNATURE_LEN,
                 &verifyResult);
      /* polyspace-end CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
      * the register value can be read via the address" */
    }
    /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */

    retVal = retVal | retVal;

    blockIndex++;

  }
  while (blockIndex < ptrHandler->VerifyNumberOfBlock);
  /* @Trace: FOTA_SUD_API_00275 */
  if (E_OK == retVal)
  {
    jobResult = FOTA_JOB_OK;
    ptrHandler->VerifyJobState = FOTA_CSM_JOB_UPDATED;
    FotaVerifyState = FOTA_STAT_VERIFY_FINISH;
  }
  else
  {

  }
  return jobResult;
}
#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"
/* polyspace-end MISRA-C3:2.7,8.13 [Justified:Low] "Not a defect" */
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
