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
**  SRC-MODULE: Fota_SwVersionCheck.c                                         **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : Cdd_FBL                                                       **
**                                                                            **
**  PURPOSE   : SW Version Check                                              **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision  Date          By               Description                       **
********************************************************************************
** 2.7.0.0   31-Aug-2022   LinhTT36     Redmine #36804                        **
** 2.6.0.0   08-Aug-2022   LinhTT36     Redmine #36424                        **
** 2.3.0.0   12-May-2022   JSChoi           Redmine #34783                    **
** 1.23.0    27-Dec-2021   JH Lim           R40-Redmine #31776                **
*******************************************************************************/


/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Fota_Cfg.h"
#include "Mem_76_Pfls.h"
#include "Mem_76_Pfls_Types.h"
#include "Mem_76_Pfls_Globals.h"
#if ((FOTA_SOFTWARE_VERSION_CHECK == FOTA_STD_ON) &&\
  (FOTA_MCU_MEMORY_ACCESS_TYPE == FOTA_SINGLE_TYPE))
#include "Fota_SoftwareVersionCheck.h"
#include "Det.h"
#include "Fota.h"
#include "Fota_Globals.h"
#include "Fota_IntFunc.h"
#include "Fota_PflsInterface.h"
#include "Fota_Verify.h"
#include "Fota_User_Callouts.h"
#include "Fota_Types.h"
/*******************************************************************************
**                      Global Data                                           **
*******************************************************************************/
static Fota_JobResultType  FotaVersionCheckResult;

static Fota_VersionCheckStateType Fota_VersionCheckState;

static Fota_VersionCheckMemType Fota_MemProcessing;

static uint8 Fota_PreviousBuffer[FOTA_SVC_MAX_LENGTH_VERSION];

static uint8 Fota_CurrentBuffer[FOTA_SVC_MAX_LENGTH_VERSION];

static uint8 Fota_NewBuffer[FOTA_SVC_MAX_LENGTH_VERSION];

static Fota_BlkStateType Fota_BlkState;

static uint32 Fota_BlkHeaderAddr;

static uint32 Fota_BlkTrailerAddr;

static Fota_VersionInfoType Fota_PreviousVersion;
static Fota_VersionInfoType Fota_CurrentVersion;
static Fota_VersionInfoType Fota_NewVersion;

static uint32 Fota_SvcSectorSizeHeader;
static uint32 Fota_SvcSectorSizeTrailer;

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/
/* polyspace-begin MISRA-C3:8.5 [Justified:Low] "Not a defect" */

#define Fota_START_SEC_CODE
#include "Fota_MemMap.h"

static FUNC(Std_ReturnType, FOTA_CODE) Fota_SvcGetVersion(uint32 uHeader, \
  uint32 uTrailer, boolean *recoveryBlkFlag);

static FUNC(Std_ReturnType, FOTA_CODE) Fota_SvcUpdateBlk(uint32 uTarget,
                                        Fota_VersionInfoType *previousVersion);

static FUNC(Std_ReturnType, FOTA_CODE) Fota_SvcRecoveryBlk(uint32 uTarget, \
  Fota_BlkCrcInfo* pSource);

static FUNC(Std_ReturnType, FOTA_CODE) Fota_SvcVerifyAndCopyBlk(const Fota_BlkFlashInfo* pTarget, \
  Fota_BlkCrcInfo* pBlock, uint32 magicNumber);

static FUNC(Std_ReturnType, FOTA_CODE) Fota_CheckSoftwareVersionBeforeErase(
                                                       boolean *recoveryBlkFlag);

static FUNC(Std_ReturnType, FOTA_CODE) Fota_SvcRecoverTrailer(uint8 *currentVersion, uint8 length);

static FUNC(Std_ReturnType, FOTA_CODE) Fota_SvcEraseBlk(Fota_BlkType blkType);

static FUNC(void, FOTA_CODE) Fota_VersionCheckDowngrade(uint32 addressCheck);

static FUNC(Fota_VersionCompareType, FOTA_CODE) Fota_CompareSoftwareVersion(
                                                        uint8 *currentVersion,
                                                        uint8 *previousVersion,
                                                        uint8 lengthCurrentVersion,
                                                        uint8 lengthPreviousVersion);
static FUNC(void, FOTA_CODE) Fota_SetVersionCheckResult(Fota_JobResultType result);
/*******************************************************************************
** Function Name        : Fota_SvcInit                                        **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function shall initialize global variable      **
**                        defined in the VersionCheck                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
**                            Fota_PreviousVersion                        **
**                            Fota_CurrentVersion                         **
**                            Fota_NewVersion                             **
**                            Fota_VersionStatus                           **
**                            Fota_BlkState                                **
**                        Function(s) invoked :                               **
**                            None                                            **
*******************************************************************************/
/* @Trace: FOTA_SRS_GENSEC_00007 */
FUNC(Std_ReturnType, FOTA_CODE) Fota_SvcInit(uint8 swUnitIndex)
{
  Std_ReturnType retVal;
  /* @Trace: FOTA_SUD_API_00061 */
  Fota_PreviousVersion.Length = 0;
  Fota_CurrentVersion.Length = 0;
  Fota_NewVersion.Length = 0;

  FOTA_MEMSET(Fota_PreviousBuffer, 0, FOTA_SVC_MAX_LENGTH_VERSION);
  FOTA_MEMSET(Fota_CurrentBuffer, 0, FOTA_SVC_MAX_LENGTH_VERSION);
  FOTA_MEMSET(Fota_NewBuffer, 0, FOTA_SVC_MAX_LENGTH_VERSION);

  Fota_PreviousVersion.Data = &Fota_PreviousBuffer[0];
  Fota_CurrentVersion.Data = &Fota_CurrentBuffer[0];
  Fota_NewVersion.Data = &Fota_NewBuffer[0];

  Fota_VersionStatus = FOTA_VERSION_INIT;

  Fota_BlkState = FOTA_BLK_INIT;

  Fota_VersionCheckState = FOTA_VERSION_CHECK_INIT;

  Fota_MemProcessing = FOTA_MEM_INIT;

  Fota_BlkHeaderAddr =
    Fota_Gast_SwUnitTable[swUnitIndex].BlkHeaderAddress;

  Fota_BlkTrailerAddr =
    Fota_Gast_SwUnitTable[swUnitIndex].BlkTrailerAddress;

  retVal = Fota_PflsGetSectorSize(Fota_MemoryInstance,
                                  &Fota_SvcSectorSizeHeader,
                                  Fota_BlkHeaderAddr);
  if (E_OK == retVal)
  {
    retVal = Fota_PflsGetSectorSize(Fota_MemoryInstance,
                                    &Fota_SvcSectorSizeTrailer,
                                    Fota_BlkTrailerAddr);
  }
  return retVal;
}
/*******************************************************************************
** Function Name        : Fota_SvcResetGlobalVariable                         **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function shall reset global variable           **
**                        defined in the VersionCheck                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
**                            Fota_BlkHeaderAddr                              **
**                            Fota_BlkTrailerAddr                             **
**                        Function(s) invoked :                               **
**                            None                                            **
*******************************************************************************/
#if (FOTA_IMPLEMENTATION_RULE == FOTA_OTA_ES98765_02)
/* @Trace: FOTA_SRS_ES98765_02E_00033 FOTA_SRS_GENSEC_00007 */
FUNC(void, FOTA_CODE) Fota_SvcResetGlobalVariable(uint8 indexSwUnit)
{
  /* @Trace: FOTA_SUD_API_00021 */
  Fota_BlkHeaderAddr =
    Fota_Gast_SwUnitTable[indexSwUnit].BlkHeaderAddress;

  Fota_BlkTrailerAddr =
    Fota_Gast_SwUnitTable[indexSwUnit].BlkTrailerAddress;

  FOTA_MEMCPY(Fota_CurrentVersion.Data,
         Fota_SvcResultAllSwUnit[indexSwUnit].CurrentVersion,
         Fota_SvcResultAllSwUnit[indexSwUnit].LengthCurrentVersion);

  Fota_CurrentVersion.Length =
    Fota_SvcResultAllSwUnit[indexSwUnit].LengthCurrentVersion;

  FOTA_MEMCPY(Fota_NewVersion.Data, Fota_SvcResultAllSwUnit[indexSwUnit].NewVersion,
         Fota_SvcResultAllSwUnit[indexSwUnit].LengthNewVersion);

  Fota_NewVersion.Length = Fota_SvcResultAllSwUnit[indexSwUnit].LengthNewVersion;

  (void)Fota_GetMemInstanceBySwUnit(indexSwUnit, &Fota_MemoryInstance);

  (void)Fota_PflsGetSectorSize(Fota_MemoryInstance,
                                  &Fota_SvcSectorSizeHeader,
                                  Fota_BlkHeaderAddr);
  (void)Fota_PflsGetSectorSize(Fota_MemoryInstance,
                                    &Fota_SvcSectorSizeTrailer,
                                    Fota_BlkTrailerAddr);
}
#endif
/*******************************************************************************
** Function Name        : Fota_SetVersionCheckResult                          **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to set value of FotaVersionCheckResult     **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Result                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : none                                                **
**                                                                            **
** Remarks              :                                                     **
*******************************************************************************/
/* @Trace: FOTA_SRS_GENSEC_00007 FOTA_SRS_GENSEC_00011 */
static FUNC(void, FOTA_CODE) Fota_SetVersionCheckResult(Fota_JobResultType result)
{
  /* @Trace: FOTA_SUD_API_00027 */
  FotaVersionCheckResult = result;
}
/*******************************************************************************
** Function Name        : Fota_VersionCheckRequest                            **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function shall initialize global variable      **
**                        defined in the VersionCheck                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
**                            Fota_PreviousVersion                            **
**                            Fota_CurrentVersion                             **
**                            Fota_NewVersion                                 **
**                            None                                            **
*******************************************************************************/
/* @Trace: FOTA_SRS_GENSEC_00007 FOTA_SRS_GENSEC_00009 FOTA_SRS_GENSEC_00013 */
FUNC(void, FOTA_CODE) Fota_VersionCheckRequest(
                                  Fota_VersionCheckRequestType requestType,
                                  uint32 addressCheck)
{
  /* @Trace: FOTA_SUD_API_00025 */
  /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "No Impact of this rule violation These function are for User." */
  if (FOTA_VERSION_CHECK_BEFORE_ERASE_REQUEST == requestType)
  {
    Fota_BeforeFlashReadFunc();
    Fota_VersionCheckState = FOTA_VERSION_CHECK_BEFORE_ERASE;
  }
  else if (FOTA_VERSION_CHECK_AFTER_DOWNLOAD_REQUEST == requestType)
  {
    Fota_BeforeFlashReadFunc();
    Fota_VersionCheckDowngrade(addressCheck);
    Fota_VersionCheckState = FOTA_VERSION_CHECK_UPDATE_HEADER_AFTER_DOWNLOAD;
  }
  else if (FOTA_VERSION_CHECK_CPD_REQUEST == requestType)
  {
    Fota_BeforeFlashReadFunc();
    Fota_VersionCheckState = FOTA_VERSION_CHECK_UPDATE_TRAILER_AFTER_CPD;
  }
  else if (FOTA_VERSION_CHECK_ERASE_ROM_REQUEST == requestType)
  {
    Fota_BeforeFlashReadFunc();
    Fota_VersionCheckState = FOTA_VERSION_CHECK_ERASE_TRAILER_BEFORE_ERASE_ROM;
  }
  else
  {
    /* Do Nothing */
  }
  Fota_SetVersionCheckResult(FOTA_JOB_PENDING);
  /* polyspace-end MISRA-C3:2.2 [Justified:Low] "No Impact of this rule violation These function are for User." */
}
/*******************************************************************************
** Function Name        : Fota_VersionCheckResult                             **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function shall initialize global variable      **
**                        defined in the VersionCheck                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
**                        Function(s) invoked :                               **
**                            None                                            **
*******************************************************************************/
/* @Trace: FOTA_SRS_GENSEC_00007 FOTA_SRS_GENSEC_00011 */
FUNC(Fota_JobResultType, FOTA_CODE) Fota_VersionCheckResult(void)
{
  Fota_JobResultType jobResult;
  /* @Trace: FOTA_SUD_API_00028 */
  jobResult = FotaVersionCheckResult;

  /* Finish software version check process */
  if ((FOTA_JOB_OK == jobResult) || (FOTA_JOB_FAILED == jobResult))
  {
    /* polyspace-begin MISRA-C3:2.2 [Justified:Low] "No Impact of this rule violation This function is for User." */
    Fota_AfterFlashReadFunc();
    /* polyspace-end MISRA-C3:2.2 [Justified:Low] "No Impact of this rule violation This function is for User." */
  }
  return jobResult;
}
/*******************************************************************************
** Function Name        : Fota_VersionCheckEraseRomLength                     **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function shall initialize global variable      **
**                        defined in the VersionCheck                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
**                        Function(s) invoked :                               **
**                            None                                            **
*******************************************************************************/
/* @Trace: FOTA_SRS_ES98765_02E_00033 FOTA_SRS_GENSEC_00007 */
FUNC(uint32, FOTA_CODE) Fota_VersionCheckEraseRomLength(uint8 swUnitIndex)
{
  /* @Trace: FOTA_SUD_API_00030 */
  uint32 eraseRomLength;
  uint32 sectorStartAddrOfTrailerStart = 0;

  /* Area for sector which include header */
  sectorStartAddrOfTrailerStart = Fota_BlkTrailerAddr -
    (Fota_BlkTrailerAddr % Fota_SvcSectorSizeTrailer);
  /* 1st Erase Area for sector which include header */
  eraseRomLength = sectorStartAddrOfTrailerStart -
    Fota_Gast_SwUnitTable[swUnitIndex].StartAddress;

  return eraseRomLength;
}
/*******************************************************************************
** Function Name        : Fota_MainVersionCheck                               **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function shall initialize global variable      **
**                        defined in the VersionCheck                         **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
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
**                            Fota_PreviousVersion                        **
**                            Fota_CurrentVersion                         **
**                            Fota_NewVersion                             **
**                            Fota_BlkState                                **
**                        Function(s) invoked :                               **
**                            None                                            **
*******************************************************************************/
/* @Trace: FOTA_SRS_GENSEC_00007 FOTA_SRS_GENSEC_00010 */
FUNC(void, FOTA_CODE) Fota_MainVersionCheck(void)
{
  Std_ReturnType retVal;
  boolean recoveryBlkTrailer;
  Fota_BlkCrcInfo tmpBlock;
  Fota_BlkFlashInfo* pTarget;
  Mem_76_Pfls_JobResultType memJobResult;
  Fota_VersionCompareType compareResult;

  switch (Fota_VersionCheckState)
  {
    case FOTA_VERSION_CHECK_INIT:

    case FOTA_VERSION_CHECK_BEFORE_ERASE:
      /* @Trace: FOTA_SUD_API_00105 */
      retVal = Fota_CheckSoftwareVersionBeforeErase(&recoveryBlkTrailer);
      if (E_OK == retVal)
      {
        if (FOTA_TRUE == recoveryBlkTrailer)
        {
          retVal = Fota_SvcEraseBlk(FOTA_BLK_TRAILER);
          if (E_OK == retVal)
          {
            Fota_MemProcessing = FOTA_MEM_ERASE_TRAILER_BEFORE_ERASE;
            Fota_VersionCheckState = FOTA_VERSION_CHECK_MEM_JOB_RESULT;
          }
          else
          {
            Fota_SetVersionCheckResult(FOTA_JOB_FAILED);
          }
        }
        else
        {
          Fota_SetVersionCheckResult(FOTA_JOB_OK);
        }
      }
      else
      {
        Fota_SetVersionCheckResult(FOTA_JOB_FAILED);
      }
      break;

    case FOTA_VERSION_CHECK_UPDATE_HEADER_AFTER_DOWNLOAD:
      /* @Trace: FOTA_SUD_API_00255 */
      retVal = Fota_SvcUpdateBlk(Fota_BlkHeaderAddr, &Fota_CurrentVersion);
      if (E_OK == retVal)
      {
        Fota_VersionCheckState = FOTA_VERSION_CHECK_MEM_JOB_RESULT;
        Fota_MemProcessing = FOTA_MEM_WRITE_HEADER_UPDATE;
      }
      else
      {
        Fota_SetVersionCheckResult(FOTA_JOB_FAILED);
      }
      break;

    case FOTA_VERSION_CHECK_UPDATE_TRAILER_AFTER_CPD:
      /* @Trace: FOTA_SUD_API_00256 */
      retVal = Fota_SvcUpdateBlk(Fota_BlkTrailerAddr, &Fota_CurrentVersion);
      if (E_OK == retVal)
      {
        Fota_VersionCheckState = FOTA_VERSION_CHECK_MEM_JOB_RESULT;
        Fota_MemProcessing = FOTA_MEM_WRITE_TRAILER_UPDATE_CPD;
      }
      else
      {
        Fota_SetVersionCheckResult(FOTA_JOB_FAILED);
      }
      break;

    case FOTA_VERSION_CHECK_ERASE_TRAILER_BEFORE_ERASE_ROM:
      /* @Trace: FOTA_SUD_API_00257 */
      retVal = Fota_SvcEraseBlk(FOTA_BLK_TRAILER);
      if (E_OK == retVal)
      {
        Fota_VersionCheckState = FOTA_VERSION_CHECK_MEM_JOB_RESULT;
        Fota_MemProcessing = FOTA_MEM_RECOVERY_TRAILER_BEFORE_ERASE_ROM;
      }
      else
      {
        Fota_SetVersionCheckResult(FOTA_JOB_FAILED);
      }
      break;

    case FOTA_VERSION_CHECK_MEM_JOB_RESULT:
      /* @Trace: FOTA_SUD_API_00106 */
      /* polyspace-begin CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
       * the register value can be read via the address" */
      memJobResult = Fota_PflsGetJobResult(Fota_MemoryInstance);

      if (memJobResult == MEM_JOB_PENDING)
      {
        /* Do nothing */
      }
      else if (memJobResult ==  MEM_JOB_OK)
      {
        if (FOTA_MEM_ERASE_TRAILER_BEFORE_ERASE == Fota_MemProcessing)
        {
          /* polyspace-begin DEFECT:PTR_CAST, CERT-C:EXP39-C, MISRA-C3:11.8,11.3 [Justified:Low]"Not a defect. Type cast for memcpy is safe" */
          pTarget = (Fota_BlkFlashInfo*)Fota_BlkHeaderAddr;
          retVal = Fota_SvcRecoverTrailer(pTarget->currentVersion,
                                          pTarget->lengthCurrentVersion);
          /* polyspace-end DEFECT:PTR_CAST, CERT-C:EXP39-C, MISRA-C3:11.8,11.3 [Justified:Low]"Not a defect. Type cast for memcpy is safe" */
          if (E_OK == retVal)
          {
            Fota_MemProcessing = FOTA_MEM_WRITE_RECOVERY_TRAILER;
            Fota_VersionCheckState = FOTA_VERSION_CHECK_MEM_JOB_RESULT;
          }
          else
          {
            Fota_SetVersionCheckResult(FOTA_JOB_FAILED);
          }
        }
        else if (FOTA_MEM_WRITE_RECOVERY_TRAILER == Fota_MemProcessing)
        {
          pTarget = (Fota_BlkFlashInfo*)Fota_BlkTrailerAddr;
          if (E_OK == Fota_SvcVerifyAndCopyBlk( \
            pTarget, &tmpBlock, FOTA_BLK_MAGIC_NUMBER_TRAILER))
          {
            Fota_SetVersionCheckResult(FOTA_JOB_OK);
          }
          else
          {
            Fota_SetVersionCheckResult(FOTA_JOB_FAILED);
          }
        }
        else if (FOTA_MEM_WRITE_HEADER_UPDATE == Fota_MemProcessing)
        {
          pTarget = (Fota_BlkFlashInfo*)Fota_BlkHeaderAddr;

          if (E_OK == Fota_SvcVerifyAndCopyBlk( \
            pTarget, &tmpBlock, pTarget->magicNumber))
          {
            if (E_OK == Fota_SvcEraseBlk(FOTA_BLK_TRAILER_LAST))
            {
              Fota_VersionCheckState = FOTA_VERSION_CHECK_MEM_JOB_RESULT;
              Fota_MemProcessing = FOTA_MEM_ERASE_TRAILER_AFTER_DOWNLOAD;
            }
            else
            {
              Fota_SetVersionCheckResult(FOTA_JOB_FAILED);
            }
          }
          else
          {
            /* Bad CRC */
            Fota_SetVersionCheckResult(FOTA_JOB_FAILED);
            #if (FOTA_DEV_ERROR_DETECT == STD_ON)
            /* Report Det Error */
            (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
              FOTA_MAIN_FUNCTION_SID, FOTA_E_BLK_UPDATE_FAIL);
            #endif
          }
        }
        else if (FOTA_MEM_ERASE_TRAILER_AFTER_DOWNLOAD ==
                                                  Fota_MemProcessing)
        {
          Fota_SetVersionCheckResult(FOTA_JOB_OK);
        }
        else if (FOTA_MEM_WRITE_TRAILER_UPDATE_CPD == Fota_MemProcessing)
        {
          compareResult = Fota_CompareSoftwareVersion(
            ((Fota_BlkFlashInfo*)Fota_BlkTrailerAddr)->currentVersion,
            Fota_NewVersion.Data,
            ((Fota_BlkFlashInfo*)Fota_BlkTrailerAddr)->lengthCurrentVersion,
            Fota_NewVersion.Length);

          if (FOTA_VERSION_CHECK_EQUAL == compareResult)
          {
            /* Trailer version is valid */
            Fota_SetVersionCheckResult(FOTA_JOB_OK);
          }
          else
          {
          /* Trailer Current Version is not same as Header Current Version
             * This can occur only the User's ROM Structure Error
             */
            Fota_SetVersionCheckResult(FOTA_JOB_FAILED);
          }
        }
        else if (FOTA_MEM_RECOVERY_TRAILER_BEFORE_ERASE_ROM == Fota_MemProcessing)
        {
          retVal = Fota_SvcRecoverTrailer(Fota_CurrentVersion.Data,
                                          Fota_CurrentVersion.Length);
          if (E_OK == retVal)
          {
            Fota_VersionCheckState = FOTA_VERSION_CHECK_MEM_JOB_RESULT;
            Fota_MemProcessing = FOTA_MEM_WAITING_RECOVERY_TRAILER;
          }
          else
          {
            Fota_SetVersionCheckResult(FOTA_JOB_FAILED);
          }
        }
        else if (FOTA_MEM_WAITING_RECOVERY_TRAILER == Fota_MemProcessing)
        {
          Fota_SetVersionCheckResult(FOTA_JOB_OK);
        }
        else
        {
          /* Do Nothing */
        }
      }
      else
      {
        #if (FOTA_DEV_ERROR_DETECT == STD_ON)
        /* Report Det Error */
        (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
          FOTA_MAIN_FUNCTION_SID, FOTA_E_SVC_MEM_JOB_FAILED);
        #endif
        Fota_SetVersionCheckResult(FOTA_JOB_FAILED);
      }
      /* polyspace-end CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
       * the register value can be read via the address" */
      break;

    default:
      /*Do nothing */
      break;
  }
}

/*******************************************************************************
** Function Name        : Fota_CheckSoftwareVersionBeforeErase                **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function parse the version information which   **
**                        saved in the code flash.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pHeader, pTrailer                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pCurrentVersion, pPreviousVersion                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : This function is called after routineControlErase   **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                            Fota_BlkState                                **
**                        Function(s) invoked :                               **
**                            Fota_SvcVerifyAndCopyBlk                        **
**                            Det_ReportError                                 **
**                            Fota_SvcRecoveryBlk                             **
*******************************************************************************/
/* @Trace: FOTA_SRS_ES98765_02E_00033 FOTA_SRS_GENSEC_00007 */
static FUNC(Std_ReturnType, FOTA_CODE) Fota_CheckSoftwareVersionBeforeErase(
                                                       boolean *recoveryBlkFlag)
{
  /* @Trace: FOTA_SUD_API_00107 */
  Std_ReturnType retVal;

  uint32 sectorStartAddrOfHeaderStart = 0;
  uint32 sectorStartAddrOfHeaderEnd = 0;
  uint32 sectorStartAddrOfTrailerStart = 0;
  uint32 sectorStartAddrOfTrailerEnd = 0;

  sectorStartAddrOfHeaderStart = Fota_BlkHeaderAddr - \
    (Fota_BlkHeaderAddr % Fota_SvcSectorSizeHeader);

  sectorStartAddrOfHeaderEnd = (Fota_BlkHeaderAddr + FOTA_BLK_TOTAL_LENGTH - 1U) - \
    ((Fota_BlkHeaderAddr + FOTA_BLK_TOTAL_LENGTH - 1U) % Fota_SvcSectorSizeHeader);

  sectorStartAddrOfTrailerStart = Fota_BlkTrailerAddr - \
    (Fota_BlkTrailerAddr % Fota_SvcSectorSizeTrailer);

  sectorStartAddrOfTrailerEnd = (Fota_BlkTrailerAddr + FOTA_BLK_TOTAL_LENGTH - 1U) - \
    ((Fota_BlkTrailerAddr + FOTA_BLK_TOTAL_LENGTH - 1U) % Fota_SvcSectorSizeTrailer);

  /*
   * Each Block should located indivisual block
   * Each Block does not share specific Sector
   */
  if ((sectorStartAddrOfHeaderEnd != sectorStartAddrOfTrailerStart) && \
     (sectorStartAddrOfHeaderStart == sectorStartAddrOfHeaderEnd) && \
     (sectorStartAddrOfTrailerStart == sectorStartAddrOfTrailerEnd))
  {
    /* If OTA Swap is enabled, current version should be located in the
     * active partition. If active partition is B, header and trailer
     * address should plus the offset
     * This is only needed on the get current version */
    /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition is not always true, the left side of the comparison depends on the configuration.
     * The if-condition can be false if a different configuration is applied" */
    //if (Fota_MemorySwapEnable == FOTA_STD_ON)
    //{
      /* Fbl_GetActivePartitionBlkAddress(&headerStartAddr, &trailerStartAddr); */
    //}
    /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition is not always true, the left side of the comparison depends on the configuration.
     * The if-condition can be false if a different configuration is applied" */
    /* Get Version */
    /* polyspace +10 ISO-17961:intptrconv [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
     * the register value can be read via the address" */
    /* polyspace +5 MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
     * the register value can be read via the address" */
    retVal = Fota_SvcGetVersion(Fota_BlkHeaderAddr,
                                Fota_BlkTrailerAddr,
                                recoveryBlkFlag);

    #if (FOTA_IMPLEMENTATION_RULE == FOTA_OTA_ES98765_02)
    FOTA_MEMCPY(Fota_SvcResultAllSwUnit[Fota_ProgrammingSWUnitId].CurrentVersion,
           Fota_CurrentVersion.Data, Fota_CurrentVersion.Length);

    Fota_SvcResultAllSwUnit[Fota_ProgrammingSWUnitId].LengthCurrentVersion =
                                                    Fota_CurrentVersion.Length;
    #endif
  }
  else
  {
    /* Block Sector configuration is not available */
    #if (FOTA_DEV_ERROR_DETECT == STD_ON)
    /* Report Det Error */
    (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
      FOTA_MAIN_FUNCTION_SID, FOTA_E_SVC_HEADER_TRAILER_ADDRESS_INVALID);
    #endif
    retVal = E_NOT_OK;
  }
  return retVal;
}
/*******************************************************************************
** Function Name        : Fota_SvcGetVersion                                   **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function parse the version information which   **
**                        saved in the code flash.                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pHeader, pTrailer                                   **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pCurrentVersion, pPreviousVersion                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : This function is called after routineControlErase   **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                            Fota_BlkState                                **
**                        Function(s) invoked :                               **
**                            Fota_SvcVerifyAndCopyBlk                        **
**                            Det_ReportError                                 **
**                            Fota_SvcRecoveryBlk                             **
*******************************************************************************/
/* @Trace: FOTA_SRS_ES98765_02E_00033 FOTA_SRS_GENSEC_00007 FOTA_SRS_GENSEC_00011 */
static FUNC(Std_ReturnType, FOTA_CODE) Fota_SvcGetVersion(uint32 uHeader, \
  uint32 uTrailer, boolean *recoveryBlkFlag)
{
  Fota_BlkCrcInfo header;
  Fota_BlkCrcInfo trailer;
  const Fota_BlkFlashInfo* pHeader;
  const Fota_BlkFlashInfo* pTrailer;
  Fota_BlkStateType blkState = FOTA_BLK_INIT;
  Fota_VersionCompareType result;

  Std_ReturnType headerCheck = E_OK;
  Std_ReturnType trailerCheck = E_OK;
  Std_ReturnType retVal = E_OK;
  *recoveryBlkFlag = FOTA_FALSE;

  /* polyspace +7 CERT-C:INT36-C [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
   * the register value can be read via the address" */
  /* polyspace +5 ISO-17961:intptrconv [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
   * the register value can be read via the address" */
  /* polyspace +3 MISRA-C3:11.4 [Justified:Low] "The integer value represents the memory address. It should be casted to an address so that
   * the memory value can be accessed via the address" */
  /* polyspace +1 CERT-C:INT36-C [Justified:Low] "Converting a pointer to integer or integer to pointer has no impact" */
  pHeader = (const Fota_BlkFlashInfo*)uHeader;
  /* polyspace +7 CERT-C:INT36-C [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
   * the register value can be read via the address" */
  /* polyspace +5 ISO-17961:intptrconv [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
   * the register value can be read via the address" */
  /* polyspace +3 MISRA-C3:11.4 [Justified:Low] "The integer value represents the memory address. It should be casted to an address so that
   * the memory value can be accessed via the address" */
  /* polyspace +1 CERT-C:INT36-C [Justified:Low] "Converting a pointer to integer or integer to pointer has no impact" */
  pTrailer = (const Fota_BlkFlashInfo*)uTrailer;

  /* Copy blk and check the header vaildity */
  headerCheck = Fota_SvcVerifyAndCopyBlk(pHeader, &header, FOTA_BLK_MAGIC_NUMBER_HEADER);

  /* Copy blk and check the trailer vaildity */
  trailerCheck = Fota_SvcVerifyAndCopyBlk(pTrailer, &trailer, FOTA_BLK_MAGIC_NUMBER_TRAILER);

  /* Check the Header Validity*/
  if (E_OK == headerCheck)
  {
    /* @Trace: FOTA_SUD_API_00108 */
    /* Check the Trailer Validity */
    if (E_OK == trailerCheck)
    {
      result = Fota_CompareSoftwareVersion(header.blkInfo.currentVersion,
                                           trailer.blkInfo.currentVersion,
                                           header.blkInfo.lengthCurrentVersion,
                                           trailer.blkInfo.lengthCurrentVersion);
      /* Check the Current Version of both block */
      if (FOTA_VERSION_CHECK_EQUAL == result)
      {
        blkState = FOTA_BLK_NORMAL;
      }
      else
      {
        result = Fota_CompareSoftwareVersion(header.blkInfo.previousVersion,
                                           trailer.blkInfo.currentVersion,
                                           header.blkInfo.lengthPreviousVersion,
                                           trailer.blkInfo.lengthCurrentVersion);
        /* Check the Header is later than Trailer */
        if (FOTA_VERSION_CHECK_EQUAL == result)
        {
          /* Header is the latest then trailer */
          blkState = FOTA_BLK_HEADER_UPDATED;
        }
        else
        {
          /* Trailer is the latest then Header */
          blkState = FOTA_BLK_TRAILER_UPDATED;
        }
      }
    }
    else
    {
      /* Only Header is valid */
      blkState = FOTA_BLK_TRAILER_INVALID;
    }
  }
  else /* Header is not valid */
  {
    /* @Trace: FOTA_SUD_API_00274 */
    /* Check the Trailer Validity */
    if (E_OK == trailerCheck)
    {
      /* Only Trailer is valid */
      blkState = FOTA_BLK_HEADER_INVALID;
    }
    else /* both are not vaild */
    {
      /* Both block have no information, generally at the first time */
      blkState = FOTA_BLK_VIRGIN;
    }
  }

  /*
   * Get the current version or restore the trailer
   */
  switch(blkState)
  {
    case FOTA_BLK_TRAILER_UPDATED:
      /* @Trace: FOTA_SUD_API_00110 */
      /*
       * It is impossible to reach INIT and
       * TRAILER UPDATE State after Stm_GetVbrStatus()
       * In this case, Invoke Det and Reset Current Version to Zero
       * Ideally, this can not be reached.
       */
      /* Set the current version to 0 for all firmware */
      FOTA_MEMSET(Fota_CurrentVersion.Data, FOTA_BLK_SWVERSION_INIT,
                                  FOTA_SVC_MAX_LENGTH_SUPPORT);
      FOTA_MEMSET(Fota_PreviousVersion.Data, FOTA_BLK_SWVERSION_INIT,
                                   FOTA_SVC_MAX_LENGTH_SUPPORT);

      Fota_CurrentVersion.Length = FOTA_SVC_SWVERSION_LENGTH_INIT;
      Fota_PreviousVersion.Length = FOTA_SVC_SWVERSION_LENGTH_INIT;
      break;

    case FOTA_BLK_VIRGIN:
      /* @Trace: FOTA_SUD_API_00271 */
      /* Set the current version to 0 for all firmware */
      FOTA_MEMSET(Fota_CurrentVersion.Data, FOTA_BLK_SWVERSION_INIT,
                                  FOTA_SVC_MAX_LENGTH_SUPPORT);
      FOTA_MEMSET(Fota_PreviousVersion.Data, FOTA_BLK_SWVERSION_INIT,
                                   FOTA_SVC_MAX_LENGTH_SUPPORT);

      Fota_CurrentVersion.Length = FOTA_SVC_SWVERSION_LENGTH_INIT;
      Fota_PreviousVersion.Length = FOTA_SVC_SWVERSION_LENGTH_INIT;
      break;

    case FOTA_BLK_HEADER_INVALID:
    case FOTA_BLK_HEADER_UPDATED:
    case FOTA_BLK_NORMAL:
      /* @Trace: FOTA_SUD_API_00272 */
      /*
       * Set the current version using trailer current version
       * Thease states have common characteristic which trailer is valid.
       */
      FOTA_MEMCPY(Fota_CurrentVersion.Data, trailer.blkInfo.currentVersion,
                                  trailer.blkInfo.lengthCurrentVersion);

      FOTA_MEMCPY(Fota_PreviousVersion.Data, trailer.blkInfo.previousVersion,
                                   trailer.blkInfo.lengthPreviousVersion);

      Fota_CurrentVersion.Length = trailer.blkInfo.lengthCurrentVersion;
      Fota_PreviousVersion.Length = trailer.blkInfo.lengthPreviousVersion;
      break;

    case FOTA_BLK_TRAILER_INVALID:
      /* @Trace: FOTA_SUD_API_00273 */
      *recoveryBlkFlag = FOTA_TRUE;
      /*
       * This case is occur when reset during the erase & flash the trailer block
       * In this case, before Routinecontrol erase, Trailer block should be
       * restored
       */
      /* Set the current version using header current version */
      FOTA_MEMCPY(Fota_CurrentVersion.Data, header.blkInfo.previousVersion,
                                  header.blkInfo.lengthPreviousVersion);

      Fota_CurrentVersion.Length = header.blkInfo.lengthPreviousVersion;


      FOTA_MEMSET(Fota_PreviousVersion.Data, FOTA_BLK_SWVERSION_INIT,
                                   FOTA_SVC_MAX_LENGTH_SUPPORT);

      Fota_PreviousVersion.Length = FOTA_SVC_SWVERSION_LENGTH_INIT;
      break;

    /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition is not always true, the left side of the comparison depends on the configuration.
     * The if-condition can be false if a different configuration is applied" */
    /* polyspace-begin CERT-C:MSC12-C [Justified:Low] "if-condition is not always true, the left side of the comparison depends on the configuration.
     * The if-condition can be false if a different configuration is applied" */
    default:
      /* The case default is reached if blkState = FOTA_BLK_INIT */
      break;
    /* polyspace-end CERT-C:MSC12-C [Justified:Low] "if-condition is not always true, the left side of the comparison depends on the configuration.
     * The if-condition can be false if a different configuration is applied" */
    /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition is not always true, the left side of the comparison depends on the configuration.
     * The if-condition can be false if a different configuration is applied" */
  }

  /* State Update for Debug */
  Fota_BlkState = blkState;

  return retVal;
}
/*******************************************************************************
** Function Name        : Fota_SvcRecoverTrailer                              **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function updates previousVersion and crc       **
**                          at the flash                                      **
**                        crc target : pTarget's magic num, currentVersion,   **
**                          previousVersion                                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pTarget, previousVersion                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pCurrentVersion, pPreviousVersion                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Code Flash should be accesable (erase/write)        **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                            N/A                                             **
**                        Function(s) invoked :                               **
**                            Fota_Crc16CoverArea                              **
**                            FlsIf_Write                                     **
**                            Det_ReportError                                 **
*******************************************************************************/
/* @Trace: FOTA_SRS_ES98765_02E_00033 FOTA_SRS_GENSEC_00007 FOTA_SRS_GENSEC_00011 */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "Not a defect" */
static FUNC(Std_ReturnType, FOTA_CODE) Fota_SvcRecoverTrailer(uint8 *currentVersion, uint8 length)
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "Not a defect" */
{
  /* @Trace: FOTA_SUD_API_00109 */
  Std_ReturnType retVal;
  Fota_BlkCrcInfo trailer;
  /*
   * This case is occur when reset during the erase & flash the trailer block
   * In this case, before Routinecontrol erase, Trailer block should be
   * restored
   */
  /*
   * Recover the trailer Variable using Header's previous version
   * These information will be flashed in tail
   * It needs for the specific situation which header is broken
   */
  trailer.blkInfo.magicNumber = FOTA_BLK_MAGIC_NUMBER_TRAILER;
  FOTA_MEMCPY(trailer.blkInfo.currentVersion, currentVersion,
                                                  FOTA_SVC_MAX_LENGTH_SUPPORT);
  trailer.blkInfo.lengthCurrentVersion = length;
  FOTA_MEMSET(trailer.blkInfo.previousVersion, FOTA_BLK_SWVERSION_INIT,
         FOTA_SVC_MAX_LENGTH_SUPPORT);
  trailer.blkInfo.lengthPreviousVersion = FOTA_SVC_SWVERSION_LENGTH_INIT;
  trailer.blkCrcInit = 0;

  /* Recovery the Trailer Block */
  retVal = Fota_SvcRecoveryBlk(Fota_BlkTrailerAddr, &trailer);
  return retVal;
}

/*******************************************************************************
** Function Name        : Fota_SvcEraseBlk                                    **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function updates previousVersion and crc       **
**                          at the flash                                      **
**                        crc target : pTarget's magic num, currentVersion,   **
**                          previousVersion                                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pTarget, previousVersion                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pCurrentVersion, pPreviousVersion                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Code Flash should be accesable (erase/write)        **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                            N/A                                             **
**                        Function(s) invoked :                               **
**                            Fota_Crc16CoverArea                              **
**                            FlsIf_Write                                     **
**                            Det_ReportError                                 **
*******************************************************************************/
/* @Trace: FOTA_SRS_ES98765_02E_00033 FOTA_SRS_GENSEC_00007 FOTA_SRS_GENSEC_00011 FOTA_SRS_GENSEC_00013 */
static FUNC(Std_ReturnType, FOTA_CODE) Fota_SvcEraseBlk(Fota_BlkType blkType)
{
  /* @Trace: FOTA_SUD_API_00114 */
  Std_ReturnType retVal;
  uint32 sectorStartAddrOfStart = 0;
  uint32 eraseSize;
  retVal = E_NOT_OK;

  if (FOTA_BLK_TRAILER == blkType)
  {
    /* Area for sector which include trailer */
    sectorStartAddrOfStart = Fota_BlkTrailerAddr - \
      (Fota_BlkTrailerAddr % Fota_SvcSectorSizeTrailer);

    eraseSize = Fota_SvcSectorSizeTrailer;
  }
  else if (FOTA_BLK_TRAILER_LAST == blkType)
  {
    /* Area for sector which include trailer */
    sectorStartAddrOfStart = Fota_BlkTrailerAddr - \
      (Fota_BlkTrailerAddr % Fota_SvcSectorSizeTrailer);

    eraseSize = Fota_Gast_SwUnitTable[Fota_ProgrammingSWUnitId].EndAddress -
      sectorStartAddrOfStart + 1;
  }
  else
  {
    /* Do nothing */
  }
  if (E_OK == Fota_PflsEraseRequest(
                Fota_MemoryInstance,
                sectorStartAddrOfStart,
				        eraseSize))
  {
    retVal = E_OK;
  }
  else
  {
    #if (FOTA_DEV_ERROR_DETECT == STD_ON)
    /* Report Det Error */
    (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
      FOTA_MAIN_FUNCTION_SID, FOTA_E_SVC_ERASE_REQUEST_FAILED);
    #endif
  }
  return retVal;
}
/*******************************************************************************
** Function Name        : Sec_SvcRecoveryBlk                                  **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function calculate provided block's crc and    **
**                        re-flash all data of block                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pTarget, pSource                                    **
**                                                                            **
** InOut parameter      : pBlock                                              **
**                                                                            **
** Output Parameters    : pCurrentVersion, pPreviousVersion                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Code Flash should be accesable (erase/write)        **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                            N/A                                             **
**                        Function(s) invoked :                               **
**                            Sec_Crc16CoverArea                              **
**                            FlsIf_Erase                                     **
**                            FlsIf_Write                                     **
**                            Det_ReportError                                 **
**                            Sec_SvcVerifyAndCopyBlk                         **
*******************************************************************************/
/* @Trace: FOTA_SRS_ES98765_02E_00033 FOTA_SRS_GENSEC_00007 FOTA_SRS_GENSEC_00011 */
static FUNC(Std_ReturnType, FOTA_CODE) Fota_SvcRecoveryBlk(uint32 uTarget,
  Fota_BlkCrcInfo* pSource)
{
  /* @Trace: FOTA_SUD_API_00117 */
  Fota_BlkFlashInfo block;
  Std_ReturnType retVal = E_OK;
  uint16 Lu16_Crc16 = 0;

  /* Set Crc init Value */
  Lu16_Crc16 = pSource->blkCrcInit;
  /* Calculate CRC */
  Lu16_Crc16 = Fota_Crc16CoverArea((uint8*)(&pSource->blkInfo), \
    (uint32)(FOTA_BLK_CRC_TARGET_LENGTH), Lu16_Crc16);

  /* Set the Recovery Data to global variable */
  block.magicNumber = pSource->blkInfo.magicNumber;

  FOTA_MEMCPY(block.currentVersion, pSource->blkInfo.currentVersion,
         FOTA_SVC_MAX_LENGTH_SUPPORT);
  FOTA_MEMCPY(block.previousVersion, pSource->blkInfo.previousVersion,
         FOTA_SVC_MAX_LENGTH_SUPPORT);
  block.lengthCurrentVersion = pSource->blkInfo.lengthCurrentVersion;
  block.lengthPreviousVersion = pSource->blkInfo.lengthPreviousVersion;
  block.crcInit = pSource->blkCrcInit;
  block.crcVal = Lu16_Crc16;

  /* Erase Success */
  if (E_OK == Fota_PflsWriteRequest(Fota_MemoryInstance,
                                    uTarget, (uint8 *)&block,
                                    (uint32)FOTA_BLK_TOTAL_LENGTH))
  {
    /* Write request success*/
    retVal = E_OK;
  }
  else
  {
    /* Write Fail */
    retVal = E_NOT_OK;
    #if (FOTA_DEV_ERROR_DETECT == STD_ON)
    /* Report Det Error */
    (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
      FOTA_MAIN_FUNCTION_SID, FOTA_E_SVC_WRITE_REQUEST_FAILED);
    #endif
  }

  return retVal;
}

/*******************************************************************************
** Function Name        : Fota_SvcUpdateBlk                                    **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function updates previousVersion and crc       **
**                          at the flash                                      **
**                        crc target : pTarget's magic num, currentVersion,   **
**                          previousVersion                                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pTarget, previousVersion                            **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : pCurrentVersion, pPreviousVersion                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Code Flash should be accesable (erase/write)        **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                            N/A                                             **
**                        Function(s) invoked :                               **
**                            Fota_Crc16CoverArea                              **
**                            FlsIf_Write                                     **
**                            Det_ReportError                                 **
*******************************************************************************/
/* @Trace: FOTA_SRS_ES98765_02E_00033 FOTA_SRS_ES98765_02E_00034 FOTA_SRS_GENSEC_00007 FOTA_SRS_GENSEC_00011 */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "Not a defect" */
static FUNC(Std_ReturnType, FOTA_CODE) Fota_SvcUpdateBlk(uint32 uTarget,
                                        Fota_VersionInfoType *previousVersion)
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "Not a defect" */
{
  /* @Trace: FOTA_SUD_API_00115 */
  Fota_BlkFlashInfo block;
  Fota_BlkCrcInfo tmpBlk;
  const Fota_BlkFlashInfo* pTarget;
  Std_ReturnType retVal = E_OK;
  uint16 Lu16_Crc16 = 0;

  /* polyspace +5 ISO-17961:intptrconv [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
   * the register value can be read via the address" */
  /* polyspace +3 MISRA-C3:11.4 [Justified:Low] "The integer value represents the memory address. It should be casted to an address so that
   * the memory value can be accessed via the address" */
  /* polyspace +1 CERT-C:INT36-C [Justified:Low] "Converting a pointer to integer or integer to pointer�has no impact" */
  pTarget = (const Fota_BlkFlashInfo*)uTarget;

  /* For calculate Crc with new previous Version */
  tmpBlk.blkInfo.magicNumber = pTarget->magicNumber;
  FOTA_MEMCPY(tmpBlk.blkInfo.currentVersion, pTarget->currentVersion,
         FOTA_SVC_MAX_LENGTH_SUPPORT);
  FOTA_MEMCPY(tmpBlk.blkInfo.previousVersion, previousVersion->Data,
         FOTA_SVC_MAX_LENGTH_SUPPORT);

  tmpBlk.blkInfo.lengthCurrentVersion = pTarget->lengthCurrentVersion;
  tmpBlk.blkInfo.lengthPreviousVersion = previousVersion->Length;
  tmpBlk.blkCrcInit = 0;
  Lu16_Crc16 = tmpBlk.blkCrcInit;

  tmpBlk.blkCrc16 = \
    Fota_Crc16CoverArea((uint8*)(&tmpBlk.blkInfo), \
      (uint32)(FOTA_BLK_CRC_TARGET_LENGTH), Lu16_Crc16);

  /* Set the Recovery Data to variable */
  FOTA_MEMCPY(block.previousVersion, tmpBlk.blkInfo.previousVersion,
         FOTA_SVC_MAX_LENGTH_SUPPORT);
  block.lengthPreviousVersion = tmpBlk.blkInfo.lengthPreviousVersion;
  block.crcInit = tmpBlk.blkCrcInit;
  block.crcVal = tmpBlk.blkCrc16;

  /* Erase was already done by rontine-control erase
   * This prever and crc area have no written yet */
  /* polyspace +5 ISO-17961:intptrconv [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
   * the register value can be read via the address" */
  /* polyspace +3 MISRA-C3:11.4 [Justified:Low] "The integer value represents the memory address. It should be casted to an address so that
   * the memory value can be accessed via the address" */
  if (E_OK == Fota_PflsWriteRequest(Fota_MemoryInstance,
                                    (uint32)&pTarget->previousVersion,
                                    (uint8 *)&block.previousVersion,
                                    (uint32)FOTA_BLK_HALF_LENGTH))
  {
    /* Write request success*/
    retVal = E_OK;
  }
  else
  {
    /* Write Fail */
    retVal = E_NOT_OK;
    #if (FOTA_DEV_ERROR_DETECT == STD_ON)
    /* Report Det Error */
    (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
      FOTA_MAIN_FUNCTION_SID, FOTA_E_SVC_WRITE_REQUEST_FAILED);
    #endif
  }

	return retVal;
}
/*******************************************************************************
** Function Name        : Fota_SvcVerifyAndCopyBlk                            **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : 1) This function verifies target block by using the **
**                           CRC value and Magic Number                       **
**                        2) This function save the target block information  **
**                           at the provided pBlock                           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : pTarget, previousVersion                            **
**                                                                            **
** InOut parameter      : pBlock                                              **
**                                                                            **
** Output Parameters    : pCurrentVersion, pPreviousVersion                   **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : Code Flash should be accesable (erase/write)        **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                            N/A                                             **
**                        Function(s) invoked :                               **
**                            Fota_Crc16CoverArea                              **
*******************************************************************************/
/* @Trace: FOTA_SRS_ES98765_02E_00033 FOTA_SRS_GENSEC_00007 FOTA_SRS_GENSEC_00011 */
static FUNC(Std_ReturnType, FOTA_CODE) Fota_SvcVerifyAndCopyBlk(const Fota_BlkFlashInfo* pTarget, \
  Fota_BlkCrcInfo* pBlock, uint32 magicNumber)
{
  /* @Trace: FOTA_SUD_API_00111 */
  uint16 Lu16_Crc16 = 0;
  Std_ReturnType retVal = E_OK;
  /*
   * Scan Header & Trailer Information
   */
  /* Update Header Info */
  pBlock->blkInfo.magicNumber = (uint32)(pTarget->magicNumber);
  FOTA_MEMCPY(pBlock->blkInfo.currentVersion, pTarget->currentVersion,
         FOTA_SVC_MAX_LENGTH_SUPPORT);

  FOTA_MEMCPY(pBlock->blkInfo.previousVersion, pTarget->previousVersion,
         FOTA_SVC_MAX_LENGTH_SUPPORT);

  pBlock->blkInfo.lengthCurrentVersion = pTarget->lengthCurrentVersion;
  pBlock->blkInfo.lengthPreviousVersion = pTarget->lengthPreviousVersion;
  pBlock->blkCrcInit = (uint16)(pTarget->crcInit);
  pBlock->blkCrc16 = (uint16)(pTarget->crcVal);

  /* Set Crc16 Init Value */
  Lu16_Crc16 = pBlock->blkCrcInit;
  /* Calculate CRC */
  Lu16_Crc16 = Fota_Crc16CoverArea((uint8*)(&pBlock->blkInfo), \
    (uint32)(FOTA_BLK_CRC_TARGET_LENGTH), Lu16_Crc16);

  /* Check the Header Validity*/
  if ((magicNumber == pBlock->blkInfo.magicNumber) && \
     (Lu16_Crc16 == pBlock->blkCrc16))
  {
    retVal = E_OK;
  }
  else /* Header is not valid */
  {
    #if (FOTA_DEV_ERROR_DETECT == STD_ON)
    /* Report Det Error */
    (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
      FOTA_MAIN_FUNCTION_SID, FOTA_E_SVC_CRC_CHECK_FAILED);
    #endif
    retVal = E_NOT_OK;
  }

  return retVal;
}
/*******************************************************************************
** Function Name        : Fota_CompareSoftwareVersion                         **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function for compare version                   **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : currentVersion                                      **
**                        previousVersion                                     **
**                        lengthCurrentVersion                                **
**                        lengthPreviousVersion                               **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : Fota_VersionCompareType                             **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                            N/A                                             **
**                        Function(s) invoked :                               **
*******************************************************************************/
/* @Trace: FOTA_SRS_ES98765_02E_00033 FOTA_SRS_GENSEC_00007 */
/* polyspace-begin MISRA-C3:8.13 [Justified:Low] "Not a defect" */
static FUNC(Fota_VersionCompareType, FOTA_CODE) Fota_CompareSoftwareVersion(
                                                  uint8 *currentVersion,
                                                  uint8 *previousVersion,
                                                  uint8 lengthCurrentVersion,
                                                  uint8 lengthPreviousVersion)
/* polyspace-end MISRA-C3:8.13 [Justified:Low] "Not a defect" */
{
  /* @Trace: FOTA_SUD_API_00113 */
  Fota_VersionCompareType result=FOTA_VERSION_CHECK_EQUAL;
  uint8 index;

  if (lengthCurrentVersion > lengthPreviousVersion)
  {
    result = FOTA_VERSION_CHECK_GREATER;
  }
  else if (lengthCurrentVersion < lengthPreviousVersion)
  {
    result = FOTA_VERSION_CHECK_SMALLER;
  }
  else
  {
    /* Check the Header is fully written */
    for (index = 0; index < lengthCurrentVersion; index++)
    {
      if (currentVersion[index] == previousVersion[index])
      {
        result = FOTA_VERSION_CHECK_EQUAL;
      }
      else if (currentVersion[index] > previousVersion[index])
      {
        result = FOTA_VERSION_CHECK_GREATER;
      }
      else
      {
        result = FOTA_VERSION_CHECK_SMALLER;
      }

      if(result!=FOTA_VERSION_CHECK_EQUAL)
      {
        break;
      }
    }
  }
  return result;
}
/*******************************************************************************
** Function Name        : Fota_VersionCheckDowngrade                          **
**                                                                            **
** Service ID           : N/A                                                 **
**                                                                            **
** Description          : This function for check downgrade version           **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Non-Reentrant                                       **
**                                                                            **
** Input Parameters     : addressCheck                                        **
**                                                                            **
** Output Parameters    : NA                                                  **
**                                                                            **
** Return parameter     : Std_ReturnType                                      **
**                                                                            **
** Preconditions        : NA                                                  **
**                                                                            **
** Remarks              : Global Variable(s)  :                               **
**                            N/A                                             **
**                        Function(s) invoked :                               **
*******************************************************************************/
/* @Trace: FOTA_SRS_ES98765_02E_00032 FOTA_SRS_ES98765_02E_00033 FOTA_SRS_ES98765_02E_00036 */
/* @Trace: FOTA_SRS_GENSEC_00007 FOTA_SRS_GENSEC_00010 FOTA_SRS_GENSEC_00011 */
/* @Trace: FOTA_SRS_GENSEC_00012 FOTA_SRS_GENSEC_00013 FOTA_SRS_GENSEC_00014 */
/* polyspace-begin MISRA-C3:2.7 [Justified:Low] "Not a defect" */
static FUNC(void, FOTA_CODE) Fota_VersionCheckDowngrade(uint32 addressCheck)
/* polyspace-end MISRA-C3:2.7 [Justified:Low] "Not a defect" */
{
  (void)addressCheck;
  /* Update New Version in the Global Variable
   * This value should be same as trailer new version
   */
  /* polyspace +6 CERT-C:INT36-C [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
   * the register value can be read via the address" */
  /* polyspace +4 ISO-17961:intptrconv [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
   * the register value can be read via the address" */
  /* polyspace +2 MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
   * the register value can be read via the address" */
  /* @Trace: FOTA_SUD_API_00026 */
  FOTA_MEMCPY(Fota_NewVersion.Data,
    ((const Fota_BlkFlashInfo*)Fota_BlkHeaderAddr)->currentVersion,
    ((const Fota_BlkFlashInfo*)Fota_BlkHeaderAddr)->lengthCurrentVersion);

  /* polyspace-begin CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
   * the register value can be read via the address" */
  Fota_NewVersion.Length =
    ((const Fota_BlkFlashInfo*)Fota_BlkHeaderAddr)->lengthCurrentVersion;
  /* polyspace-end CERT-C:INT36-C, MISRA-C3:11.4 [Justified:Low] "The integer value represents the register address. It should be casted to an address so that
   * the register value can be read via the address" */

  #if (FOTA_IMPLEMENTATION_RULE == FOTA_OTA_ES98765_02)
  /* Store new version data */
  FOTA_MEMCPY(Fota_SvcResultAllSwUnit[Fota_ProgrammingSWUnitId].NewVersion,
         Fota_NewVersion.Data,
         Fota_NewVersion.Length);

  Fota_SvcResultAllSwUnit[Fota_ProgrammingSWUnitId].LengthNewVersion =
    Fota_NewVersion.Length;

  if (Fota_SvcResultAllSwUnit[Fota_ProgrammingSWUnitId].CheckVersion ==
                                                      FOTA_VERSION_USED)
  #endif
  {
    /* polyspace-begin DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
    if (E_NOT_OK == Fota_SvcCheckVersion(Fota_NewVersion.Data,
                                         Fota_NewVersion.Length,
                                         Fota_CurrentVersion.Data,
                                         Fota_CurrentVersion.Length))
    {
      /*
       * Downgrade is detected.
       * retVal should not be E_NOT_OK until the end of this function
       * due to skip flash programming of the remain area
       */
      Fota_VersionStatus = FOTA_VERSION_NOT_OK;
      #if (FOTA_DEV_ERROR_DETECT == STD_ON)
      /* Report Det Error */
      (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
        FOTA_TRANSFER_DATA_SID, FOTA_E_SVC_DOWNGRADE_DETECT);
      #endif
    }
    else
    {
      /* Version is not downgrade*/
      Fota_VersionStatus = FOTA_VERSION_OK;
    }
    /* polyspace-end DEFECT:DEAD_CODE, MISRA-C3:14.3,2.1 [Justified:Low] "if-condition depends on the configuration." */
  }
  #if (FOTA_IMPLEMENTATION_RULE == FOTA_OTA_ES98765_02)
  else
  {
      Fota_VersionStatus = FOTA_VERSION_OK;
  }
  #endif
}

#define Fota_STOP_SEC_CODE
#include "Fota_MemMap.h"
/* polyspace-end MISRA-C3:8.5 [Justified:Low] "Not a defect" */
#endif
/*******************************************************************************
**                          End of File                                       **
*******************************************************************************/

