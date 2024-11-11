/*******************************************************************************
**                                                                            **
**  (C) 2022 HYUNDAI AUTOEVER Corp.                                           **
**  Confidential Proprietary Information. Distribution Limited.               **
**  Do Not Copy Without Prior Permission                                      **
**                                                                            **
**  SRC-MODULE: Fota_Updater.c                                                **
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
** 2.0.0     20-Feb-2023   VuPH6        Initial version                       **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "Fota_Updater.h"
#if (FOTA_MODE == FOTA_UPDATER_MODE)
#include "Fota.h"
#include "Fota_Types.h"
#include "Fota_Globals.h"
#include "Fota_IntFunc.h"
#include "Fota_Verify.h"
#include "Fota_PflsInterface.h"
#include "Fota_BootManager.h"
/*******************************************************************************
**                             Macro Definition                               **
*******************************************************************************/

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                     Global Data                                            **
*******************************************************************************/


/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : Fota_UpdaterMainFunction                            **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Operation sequense in Updater mode                  **
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
FUNC(void, FOTA_CODE) Fota_UpdaterMainFunction(void)
{
  VAR(Fota_SetKeyResultType, AUTOMATIC) setKeyResult;
  Fota_JobResultType jobState;
  uint32 startPflsAddress;
  uint32 endPflsAddress;
  uint32 startNewFblAddress;
  uint8 *ptrSourceData;
  uint32 dataLength;
  Std_ReturnType retVal;

  static Fota_MemStateType memState = FOTA_MEM_FIRMWARE_ERASE_CHECK;
  static uint8 blockEraseIndex = 0;
  static uint8 blockCopyIndex = 0;
  jobState = FOTA_JOB_OK;
  retVal = E_NOT_OK;

  switch (Fota_State)
  {
    case FOTA_MEM_ERASE_FBL_PROCESSING:
      /* @Trace: FOTA_SUD_API_00170 */
      Fota_FindBlockInfo(Fota_SwFblIndex, blockEraseIndex,
                                 &startPflsAddress, &endPflsAddress);

      dataLength = endPflsAddress - startPflsAddress + 1;

      retVal = Fota_CalibrationStartAddressLength(&dataLength,
                                                 &startPflsAddress,
                                                 endPflsAddress);
      if (retVal == E_OK)
      {
        if (Fota_PflsEraseRequest(Fota_MemoryInstance, startPflsAddress, dataLength) == E_OK)
        {
          memState = FOTA_MEM_FIRMWARE_ERASE_CHECK;
          Fota_State = FOTA_MEM_JOB_CHECK;
        }
        else
        {
          Fota_State = FOTA_ERROR;
          #if (FOTA_DEV_ERROR_DETECT == STD_ON)
          /* Report Det Error */
          (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
            FOTA_MAIN_FUNCTION_SID, FOTA_E_UPDATER_ERASE_REQUEST_FAILED);
          #endif
        }
      }
      else
      {
        Fota_State = FOTA_ERROR;
        #if (FOTA_DEV_ERROR_DETECT == STD_ON)
        /* Report Det Error */
        (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
          FOTA_MAIN_FUNCTION_SID, FOTA_E_UPDATER_CALIB_ADDRESS_LENGTH_FAILED);
        #endif
      }
      break;

    case FOTA_MEM_WRITE_FBL_PROCESSING:
      /* @Trace: FOTA_SUD_API_00171 */
      Fota_FindBlockInfo(Fota_SwFblIndex, blockCopyIndex,
                                 &startPflsAddress, &endPflsAddress);

      Fota_FindBlockInfo(Fota_SwNewFblIndex, blockCopyIndex,
                                 &startNewFblAddress, NULL_PTR);

      ptrSourceData = (uint8 *)startNewFblAddress;
      dataLength = endPflsAddress - startPflsAddress + 1;

      if (E_NOT_OK == Fota_BlockProtectedCheck(startPflsAddress,dataLength))
      {
        retVal = Fota_PflsWriteRequest(Fota_MemoryInstance, startPflsAddress,
                                       ptrSourceData,
                                       dataLength);
        #if (FOTA_DEV_ERROR_DETECT == STD_ON)
        if (E_NOT_OK == retVal)
        {
          /* Report Det Error */
          (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
            FOTA_MAIN_FUNCTION_SID, FOTA_E_UPDATER_WRITE_REQUEST_FAILED);
        }
        #endif
      }
      else
      {
        #if (FOTA_DEV_ERROR_DETECT == STD_ON)
        /* Report Det Error */
        (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
          FOTA_MAIN_FUNCTION_SID, FOTA_E_UPDATER_ADDRESS_LENGTH_INVALID);
        #endif
      }

      if (E_OK == retVal)
      {
        memState = FOTA_MEM_WRITE_FIRMWARE_CHECK;
        Fota_State = FOTA_MEM_JOB_CHECK;
      }
      else
      {
        Fota_State = FOTA_ERROR;
      }
      break;

    case FOTA_MEM_VERIFY_PROCESSING:
      /* @Trace: FOTA_SUD_API_00172 */
      Fota_JobVerifyProcess();

      jobState = Fota_VerifyJobResult();

      if (jobState == FOTA_JOB_PENDING)
      {
        Fota_State = FOTA_MEM_VERIFY_PROCESSING;
      }
      else if (jobState == FOTA_JOB_OK)
      {
        Fota_State = FOTA_PARTITION_WRITE_PROCESSING;
      }
      else
      {
        Fota_State = FOTA_ERROR;
        #if (FOTA_DEV_ERROR_DETECT == STD_ON)
        /* Report Det Error */
        (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
          FOTA_MAIN_FUNCTION_SID, FOTA_E_UPDATER_VERIFY_JOB_FAILED);
        #endif
      }
      break;

    case FOTA_PARTITION_WRITE_PROCESSING:
      /* @Trace: FOTA_SUD_API_00173 */
      if (E_OK==Fota_SetActKey_Request(FOTA_FLKEY_MGR, Fota_ProgrammingSWUnitId)) //Fota_WritePartitionFlag(Fota_ProgrammingSWUnitId))
      {
        memState = FOTA_MEM_PARTITION_WRITE_CHECK;
        Fota_State = FOTA_MEM_JOB_CHECK;
      }
      else
      {
        Fota_State = FOTA_ERROR;
        #if (FOTA_DEV_ERROR_DETECT == STD_ON)
        /* Report Det Error */
        (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
          FOTA_MAIN_FUNCTION_SID, FOTA_E_UPDATER_WRITE_PARTITION_REQUEST_FAILED);
        #endif
      }
      break;

    case FOTA_MEM_JOB_CHECK:
      /* @Trace: FOTA_SUD_API_00174 */
      setKeyResult = Fota_SetKey_Result(); //Fota_PflsGetJobResult(Fota_MemoryInstance);

      if (FOTA_SETMAGICKEY_OK == setKeyResult)
      {
        if (FOTA_MEM_FIRMWARE_ERASE_CHECK == memState)
        {
          blockEraseIndex++;
          if (blockEraseIndex < Fota_NumOfFblBlock)
          {
            Fota_State = FOTA_MEM_ERASE_FBL_PROCESSING;
          }
          else
          {
            Fota_State = FOTA_MEM_WRITE_FBL_PROCESSING;
            /* Reset init value */
            blockEraseIndex = 0;
            /* Set init value */
            blockCopyIndex = 0;
          }
        }
        else if (FOTA_MEM_WRITE_FIRMWARE_CHECK == memState)
        {
          blockCopyIndex++;
          /* copy block data except last block - partition plag */
          if (blockCopyIndex < (Fota_NumOfFblBlock - 1))
          {
            Fota_State = FOTA_MEM_WRITE_FBL_PROCESSING;
          }
          else
          {
            /* Set init value in next state*/
            blockCopyIndex = 0;

            Fota_ProgrammingSWUnitId = Fota_SwFblIndex;

            if (Fota_VerifyRequest(Fota_ProgrammingSWUnitId)==E_OK)
            {
              Fota_State = FOTA_MEM_VERIFY_PROCESSING;
            }
            else
            {
              Fota_State = FOTA_ERROR;
            }
          }
        }
        else if (FOTA_MEM_PARTITION_WRITE_CHECK == memState)
        {
          Fota_State = FOTA_ACTIVATE;
        }
        else
        {
          /* Do nothing */
        }
      }
      else if (FOTA_SETMAGICKEY_PENDING == setKeyResult)
      {
        Fota_State = FOTA_MEM_JOB_CHECK;
      }
      else if(FOTA_SETMAGICKEY_FAILED == setKeyResult)
      {
        Fota_State = FOTA_ERROR;
        #if (FOTA_DEV_ERROR_DETECT == STD_ON)
        /* Report Det Error */
        (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
          FOTA_MAIN_FUNCTION_SID, FOTA_E_UPDATER_MEM_JOB_FAILED);
        #endif
      }
      break;

    default:
      /*Do nothing */
      break;
  }
}
/*******************************************************************************
** Function Name        : Fota_InitUpdaterMode                                **
**                                                                            **
** Service ID           : NA                                                  **
**                                                                            **
** Description          : Function to set some global variable and init Fota  **
**                        state                                              **
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
FUNC(void, FOTA_CODE) Fota_InitUpdaterMode(void)
{
  /* @Trace: FOTA_SUD_API_00003 */
  Fota_SwFblIndex = Fota_FindSoftwareArea(FOTA_FBL_TYPE);

  if (FOTA_INVALID_INDEX != Fota_SwFblIndex)
  {
    Fota_SwNewFblIndex = Fota_FindSoftwareArea(FOTA_NEW_FBL_TYPE);
    if (FOTA_INVALID_INDEX != Fota_SwNewFblIndex)
    {
      Fota_NumOfFblBlock = Fota_FindNumberOfFblBlock(Fota_SwFblIndex);
      Fota_State = FOTA_MEM_ERASE_FBL_PROCESSING;
    }
  }
  else
  {
    #if (FOTA_DEV_ERROR_DETECT == STD_ON)
    /* Report Det Error */
    (void)Det_ReportError(FOTA_MODULE_ID, FOTA_INSTANCE_ID,
      FOTA_MAIN_FUNCTION_SID, FOTA_E_UPDATER_NOT_FOUNT_SOFTWARE_INDEX);
    #endif
  }
}
#endif
/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
