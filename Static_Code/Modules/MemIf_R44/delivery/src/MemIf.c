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
**  SRC-MODULE: MemIf.c                                                       **
**                                                                            **
**  TARGET    : All                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR MemIf Module                                          **
**                                                                            **
**  PURPOSE   : AutoEver Custom Memory API Functionality                      **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision   Date            By                 Description                  **
********************************************************************************
** 0.0.1     25-Nov-2019     Ngocvm2;HuyP4      Initial Version               **
** 0.0.2     06-Jan-2020     VietPT4            Fix misra rule                **
** 0.0.3     27-Apr-2020     NgocVM2            Follow New V Cycle            **
** 0.0.4     07-Jul-2020     Thaodx          Updated SUD R44-Remine <#11836>  **
** 0.0.5     13-Jul-2020     NamTV9          Fix Defect R44-Redmine <#14587>  **
** 1.0.1     02-Dec-2021     JH Lim          Fix Defect R44-Redmine <#19737>  **
**                                           Fix Defect R44-Redmine <#22520>  **
** 1.0.2     29-Jun-2022     SH Park         Improvement mobilegence          **
**                                             Classic <CP44-224>             **
** 1.0.3     30-Sep-2022     SH Park         Improvement mobilegence          **
**                                             Classic <CP44-77>              **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "MemIf.h"
#if (STD_ON == MEMIF_DEV_ERROR_DETECT)
  #include "Det.h"
#endif
#ifdef MEMIF_FEE_DRIVER_INDEX
  #include "Fee.h"
#endif
#ifdef MEMIF_EA_DRIVER_INDEX
  #include "Ea.h"
#endif
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

/*******************************************************************************
** Function Name      : MemIf_SetMode                                         **
**                                                                            **
** Service ID         : 0x01                                                  **
**                                                                            **
** Description        : Invokes the "SetMode" functions of all underlying     **
**                      memory abstraction modules                            **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : Mode : Desired mode for the underlying module         **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return Parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s): None                              **
**                      Function(s) Invoked: Ea_SetMode,                      **
**                                           Fee_SetMode                      **
*******************************************************************************/
#define MEMIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_MemHwAb_14022 SRS_BSW_00384 SRS_BSW_00392 SRS_MemHwAb_14019 SRS_SPAL_12078 */
FUNC(void, MEMIF_CODE) MemIf_SetMode(VAR(MemIf_ModeType, AUTOMATIC) Mode) /* polyspace MISRA2012:5.8 [Justified:Low] "Variable is named following to AUTOSAR specification" */
{
  /* @Trace: MemIf_SUD_MACRO_003 */
  #ifdef MEMIF_FEE_DRIVER_INDEX
    /* @Trace: MemIf_SUD_FUNC_001 */
    /* Set Mode for Fee */
    Fee_SetMode(Mode);
  #endif /* MEMIF_FEE_DRIVER_INDEX */
  /* @Trace: MemIf_SUD_MACRO_002 */
  #ifdef MEMIF_EA_DRIVER_INDEX
    /* @Trace: MemIf_SUD_FUNC_002 */
    /* Set Mode for Ea */
    Ea_SetMode(Mode);
  #endif /* MEMIF_EA_DRIVER_INDEX */
}

#define MEMIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : MemIf_Read                                            **
**                                                                            **
** Service ID         : 0x02                                                  **
**                                                                            **
** Description        : Invokes the "Read" function of the underlying memory  **
**                      abstraction module selected by the parameter          **
**                      DeviceIndex                                           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : DeviceIndex : Index of memory abstraction modules     **
**                      BlockNumber : Number of logical block, also denoting  **
**                                    start address of the block              **
**                      BlockOffset : Read address offset inside the block    **
**                      Length : Number of bytes to read                      **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : DataBufferPtr : Pointer to data buffer                **
**                                                                            **
** Return Parameter   : E_OK : The requested job has been accepted by         **
**                             the underlying module                          **
**                      E_NOT_OK: The requested job has not been accepted by  **
**                                the underlying module                       **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s):None                               **
**                      Function(s) Invoked: Det_ReportError,                 **
**                                           Fee_Read,                        **
**                                           Ea_Read                          **
*******************************************************************************/
#define MEMIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00369 SRS_MemHwAb_14022  SRS_MemHwAb_14029 SRS_MemHwAb_14020 */
/* @Trace: SRS_BSW_00385 SRS_BSW_00337      SRS_BSW_00386     SRS_SPAL_12448 */
/* @Trace: SRS_BSW_00384 SRS_MemHwAb_14019  SRS_MemHwAb_14021 SRS_SPAL_12078 */
FUNC(Std_ReturnType, MEMIF_CODE) MemIf_Read(\
  VAR(uint8, AUTOMATIC) DeviceIndex,\
  VAR(uint16, AUTOMATIC) BlockNumber,\
  VAR(uint16, AUTOMATIC) BlockOffset,\
  P2VAR(uint8, AUTOMATIC, MEMIF_APPL_DATA) DataBufferPtr,\
  VAR(uint16, AUTOMATIC) Length)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;
  /* @Trace: MemIf_SUD_MACRO_009 */
  #if (MEMIF_ONE_DRIVER == MEMIF_NO_OF_DEVICES)
    returnValue = E_NOT_OK;
    MEMIF_UNUSE(DeviceIndex);
    /* @Trace: MemIf_SUD_MACRO_001 */
    #if (STD_ON == MEMIF_DEV_ERROR_DETECT)
      /* Check value of DataBufferPtr */
      if (NULL_PTR == DataBufferPtr)
      {
        /* @Trace: MemIf_SUD_FUNC_052 */
        /* Invalid value of pointer, Report error to DET */
        (void) Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID,\
          MEMIF_READ_SID, MEMIF_E_PARAM_POINTER);
      }
      else
      {
    #endif /* (STD_ON == MEMIF_DEV_ERROR_DETECT) */
        /* @Trace: MemIf_SUD_MACRO_003 */
        #ifdef MEMIF_FEE_DRIVER_INDEX
          /* @Trace: MemIf_SUD_FUNC_053 */
          /* Call Fee */
          returnValue = Fee_Read(BlockNumber, BlockOffset,\
            DataBufferPtr, Length);
        #endif /* MEMIF_FEE_DRIVER_INDEX */
        /* @Trace: MemIf_SUD_MACRO_002 */
        #ifdef MEMIF_EA_DRIVER_INDEX
          /* @Trace: MemIf_SUD_FUNC_054 */
          /* Call Ea */
          returnValue = Ea_Read(BlockNumber, BlockOffset, DataBufferPtr,\
            Length);
        #endif /* MEMIF_EA_DRIVER_INDEX */
    #if (STD_ON == MEMIF_DEV_ERROR_DETECT)
      }
    #endif /* (STD_ON == MEMIF_DEV_ERROR_DETECT) */
  /* More than one underlying device */
  /* @Trace: MemIf_SUD_MACRO_009 */
  #elif (MEMIF_ONE_DRIVER < MEMIF_NO_OF_DEVICES)
    returnValue = E_NOT_OK;
    /* @Trace: MemIf_SUD_MACRO_001 */
    /* Check status dev error detect */
    #if (STD_ON == MEMIF_DEV_ERROR_DETECT)
      /* Check value of DataBufferPtr */
      if (NULL_PTR == DataBufferPtr)
      {
        /* @Trace: MemIf_SUD_FUNC_055 */
        /* Invalid value of pointer, Report error to DET */
        (void) Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID,\
          MEMIF_READ_SID, MEMIF_E_PARAM_POINTER);
      }
      else
      {
    #endif /* (STD_ON == MEMIF_DEV_ERROR_DETECT) */
        /*
        * Check the passed DeviceIndex and call the underlying
        * GetJobResult API as applicable
        */
        switch (DeviceIndex)
        {
          /* Call Fee */
          /* @Trace: MemIf_SUD_MACRO_003 */
          case MEMIF_FEE_DRIVER_INDEX:
            /* @Trace: MemIf_SUD_FUNC_057 */
            returnValue = Fee_Read(BlockNumber, BlockOffset, DataBufferPtr,\
              Length);
            break;
          /* Call Ea */
          /* @Trace: MemIf_SUD_MACRO_002 */
          case MEMIF_EA_DRIVER_INDEX:
            /* @Trace: MemIf_SUD_FUNC_058 */
            returnValue = Ea_Read(BlockNumber, BlockOffset, DataBufferPtr,\
              Length);
            break;
          default:
            /* @Trace: MemIf_SUD_MACRO_001 */
            #if (STD_ON == MEMIF_DEV_ERROR_DETECT)
              /* @Trace: MemIf_SUD_FUNC_056 */
              /* Invalid DeviceIndex, Report error to DET */
              (void) Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID,\
                MEMIF_READ_SID, MEMIF_E_PARAM_DEVICE);
            #endif /* (STD_ON == MEMIF_DEV_ERROR_DETECT) */
            break;
        }
    #if (STD_ON == MEMIF_DEV_ERROR_DETECT)
      }
    #endif /* (STD_ON == MEMIF_DEV_ERROR_DETECT) */
  #else
    returnValue = E_NOT_OK;
  #endif /* (MEMIF_ONE_DRIVER > MEMIF_NO_OF_DEVICES) */

  /* @Trace: MemIf_SUD_FUNC_059 */
  return(returnValue);
}

#define MEMIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : MemIf_Write                                           **
**                                                                            **
** Service ID         : 0x03                                                  **
**                                                                            **
** Description        : Invokes the "Write" function of the underlying memory **
**                      abstraction module selected by the parameter          **
**                      DeviceIndex                                           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : DeviceIndex : Index of memory abstraction modules     **
**                      BlockNumber : Number of logical block, also denoting  **
**                                    start address of the block              **
**                      DataBufferPtr : Pointer to data buffer                **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return Parameter   : E_OK : The requested job has been accepted by         **
**                             the underlying module                          **
**                      E_NOT_OK: The requested job has not been accepted by  **
**                                the underlying module                       **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s):None                               **
**                      Function(s) Invoked: Det_ReportError,                 **
**                                           Fee_Write,                       **
**                                           Ea_Write                         **
*******************************************************************************/
#define MEMIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00369 SRS_MemHwAb_14010  SRS_MemHwAb_14022 SRS_MemHwAb_14020 */
/* @Trace: SRS_BSW_00337 SRS_BSW_00385      SRS_BSW_00386     SRS_SPAL_12448 */
/* @Trace: SRS_BSW_00384 SRS_MemHwAb_14019  SRS_SPAL_12078 */
FUNC(Std_ReturnType, MEMIF_CODE) MemIf_Write(\
  VAR(uint8, AUTOMATIC) DeviceIndex,\
  VAR(uint16, AUTOMATIC) BlockNumber,\
  P2CONST(uint8, AUTOMATIC, MEMIF_APPL_DATA) DataBufferPtr)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* One underlying device */
  /* @Trace: MemIf_SUD_MACRO_009 */
  #if (MEMIF_ONE_DRIVER == MEMIF_NO_OF_DEVICES)
    returnValue = E_NOT_OK;
    MEMIF_UNUSE(DeviceIndex);
    /* @Trace: MemIf_SUD_MACRO_001 */
    #if (STD_ON == MEMIF_DEV_ERROR_DETECT)
      /* Check value of DataBufferPtr */
      if (NULL_PTR == DataBufferPtr)
      {
        /* @Trace: MemIf_SUD_FUNC_102 */
        /* Invalid value of pointer, Report error to DET */
        (void) Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID,\
          MEMIF_WRITE_SID, MEMIF_E_PARAM_POINTER);
      }
      else
      {
    #endif /* (STD_ON == MEMIF_DEV_ERROR_DETECT) */
        /* @Trace: MemIf_SUD_MACRO_003 */
        #ifdef MEMIF_FEE_DRIVER_INDEX
          /* @Trace: MemIf_SUD_FUNC_105 */
          /* Call Fee */
          returnValue = Fee_Write(BlockNumber, DataBufferPtr);
        #endif /* MEMIF_FEE_DRIVER_INDEX */
        /* @Trace: MemIf_SUD_MACRO_002 */
        #ifdef MEMIF_EA_DRIVER_INDEX
          /* @Trace: MemIf_SUD_FUNC_107 */
          /* Call Ea */
          returnValue = Ea_Write(BlockNumber, DataBufferPtr);
        #endif /* MEMIF_EA_DRIVER_INDEX */
    #if (STD_ON == MEMIF_DEV_ERROR_DETECT)
      }
    #endif /* (STD_ON == MEMIF_DEV_ERROR_DETECT) */
  /* More than one underlying device */
  /* @Trace: MemIf_SUD_MACRO_009 */
  #elif (MEMIF_ONE_DRIVER < MEMIF_NO_OF_DEVICES)
    returnValue = E_NOT_OK;
    /* @Trace: MemIf_SUD_MACRO_001 */
    /* Check status dev error detect */
    #if (STD_ON == MEMIF_DEV_ERROR_DETECT)
      /* Check value of DataBufferPtr */
      if (NULL_PTR == DataBufferPtr)
      {
        /* @Trace: MemIf_SUD_FUNC_103 */
        /* Invalid value of pointer, Report error to DET */
        (void) Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID,\
          MEMIF_WRITE_SID, MEMIF_E_PARAM_POINTER);
      }
      else
      {
    #endif /* (STD_ON == MEMIF_DEV_ERROR_DETECT) */
        /*
        * Check the passed DeviceIndex and call the underlying
        * GetJobResult API as applicable
        */
        switch (DeviceIndex)
        {
          /* Call Fee */
          /* @Trace: MemIf_SUD_MACRO_003 */
          case MEMIF_FEE_DRIVER_INDEX:
            /* @Trace: MemIf_SUD_FUNC_106 */
            returnValue = Fee_Write(BlockNumber, DataBufferPtr);
            break;
          /* Call Ea */
          /* @Trace: MemIf_SUD_MACRO_002 */
          case MEMIF_EA_DRIVER_INDEX:
            /* @Trace: MemIf_SUD_FUNC_108 */
            returnValue = Ea_Write(BlockNumber, DataBufferPtr);
            break;
          default:
            /* @Trace: MemIf_SUD_MACRO_001 */
            #if (STD_ON == MEMIF_DEV_ERROR_DETECT)
              /* @Trace: MemIf_SUD_FUNC_104 */
              /* Report to DET */
              (void) Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID, \
                MEMIF_WRITE_SID, MEMIF_E_PARAM_DEVICE);
            #endif /* (STD_ON == MEMIF_DEV_ERROR_DETECT) */
            break;
        }
    #if (STD_ON == MEMIF_DEV_ERROR_DETECT)
      }
    #endif /* (STD_ON == MEMIF_DEV_ERROR_DETECT) */
  #else
    returnValue = E_NOT_OK;
  #endif /* (MEMIF_ONE_DRIVER > MEMIF_NO_OF_DEVICES) */

  /* @Trace: MemIf_SUD_FUNC_109 */
  return(returnValue);
}

#define MEMIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : MemIf_Cancel                                          **
**                                                                            **
** Service ID         : 0x04                                                  **
**                                                                            **
** Description        : Invokes the "Cancel" function of the underlying       **
**                      memory abstraction module selected by the parameter   **
**                      DeviceIndex                                           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : DeviceIndex : Index of memory abstraction modules     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return Parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s):None                               **
**                      Function(s) Invoked: Det_ReportError,                 **
**                                           Fee_Cancel,                      **
**                                           Ea_Cancel                        **
*******************************************************************************/
#define MEMIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_MemHwAb_14020  SRS_MemHwAb_14022 SRS_MemHwAb_14031 SRS_BSW_00337 */
/* @Trace: SRS_BSW_00385      SRS_BSW_00386     SRS_SPAL_12448    SRS_BSW_00384 */
/* @Trace: SRS_MemHwAb_14019  SRS_MemHwAb_14021 SRS_SPAL_12078 */
FUNC(void, MEMIF_CODE) MemIf_Cancel(VAR(uint8, AUTOMATIC) DeviceIndex)
{
  /* One underlying device */
  /* @Trace: MemIf_SUD_MACRO_009 */
  #if (MEMIF_ONE_DRIVER == MEMIF_NO_OF_DEVICES)
    MEMIF_UNUSE(DeviceIndex);
    /* @Trace: MemIf_SUD_MACRO_003 */
    #ifdef MEMIF_FEE_DRIVER_INDEX
      /* @Trace: MemIf_SUD_FUNC_153 */
      /* Call Fee */
      Fee_Cancel();
    #endif /* MEMIF_FEE_DRIVER_INDEX */
    /* @Trace: MemIf_SUD_MACRO_002 */
    #ifdef MEMIF_EA_DRIVER_INDEX
      /* @Trace: MemIf_SUD_FUNC_155 */
      /* Call Ea */
      Ea_Cancel();
    #endif /* MEMIF_EA_DRIVER_INDEX */
  /* More than one underlying device */
  /* @Trace: MemIf_SUD_MACRO_009 */
  #elif (MEMIF_ONE_DRIVER < MEMIF_NO_OF_DEVICES)
    /*
     * Check the passed DeviceIndex and call the underlying
     * GetJobResult API as applicable
     */
    switch (DeviceIndex)
    {
      /* Call Fee */
      /* @Trace: MemIf_SUD_MACRO_003 */
      case MEMIF_FEE_DRIVER_INDEX:
        /* @Trace: MemIf_SUD_FUNC_154 */
        Fee_Cancel();
        break;
      /* Call Ea */
      /* @Trace: MemIf_SUD_MACRO_002 */
      case MEMIF_EA_DRIVER_INDEX:
        /* @Trace: MemIf_SUD_FUNC_156 */
        Ea_Cancel();
        break;
      default:
        /* @Trace: MemIf_SUD_MACRO_001 */
        #if (STD_ON == MEMIF_DEV_ERROR_DETECT)
          /* @Trace: MemIf_SUD_FUNC_152 */
          /* Invalid DeviceIndex, Report error to DET */
          (void) Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID,\
            MEMIF_CANCEL_SID, MEMIF_E_PARAM_DEVICE);
        #endif /* (STD_ON == MEMIF_DEV_ERROR_DETECT) */
        break;
    }
  #else
  /* Do nothing if no device */
  #endif /* (MEMIF_ONE_DRIVER > MEMIF_NO_OF_DEVICES) */
}

#define MEMIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : MemIf_GetStatus                                       **
**                                                                            **
** Service ID         : 0x05                                                  **
**                                                                            **
** Description        : Invokes the "GetStatus" function of the underlying    **
**                      memory abstraction module selected by the parameter   **
**                      DeviceIndex                                           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : DeviceIndex : Index of memory abstraction modules     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return Parameter   : statusMemIf : Status return from underlying modules    **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s):None                               **
**                      Function(s) Invoked: Det_ReportError,                 **
**                                           Fee_GetStatus,                   **
**                                           Ea_GetStatus                     **
*******************************************************************************/
#define MEMIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00369 SRS_BSW_00392      SRS_MemHwAb_14020  SRS_MemHwAb_14022 */
/* @Trace: SRS_BSW_00337 SRS_BSW_00385      SRS_BSW_00386      SRS_SPAL_12448 */
/* @Trace: SRS_BSW_00384 SRS_MemHwAb_14019  SRS_MemHwAb_14021  SRS_BSW_00323 */
/* @Trace: SRS_MemHwAb_14023 SRS_SPAL_12078 */
FUNC(MemIf_StatusType, MEMIF_CODE) MemIf_GetStatus(\
  VAR(uint8, AUTOMATIC) DeviceIndex)
{
  VAR(MemIf_StatusType, AUTOMATIC) statusMemIf;
  /* @Trace: MemIf_SUD_MACRO_009 */
  #if (MEMIF_ONE_DRIVER < MEMIF_NO_OF_DEVICES)
    VAR(MemIf_StatusType, AUTOMATIC) statusEa;
    VAR(MemIf_StatusType, AUTOMATIC) statusFee;
  #endif /* (MEMIF_ONE_DRIVER < MEMIF_NO_OF_DEVICES) */
  /* @Trace: MemIf_SUD_MACRO_009 */
  #if (MEMIF_ONE_DRIVER == MEMIF_NO_OF_DEVICES)
    MEMIF_UNUSE(DeviceIndex);
    /* @Trace: MemIf_SUD_MACRO_003 */
    #ifdef MEMIF_FEE_DRIVER_INDEX
      /* @Trace: MemIf_SUD_FUNC_203 */
      /* Call Fee */
      statusMemIf = Fee_GetStatus();
    #endif /* MEMIF_FEE_DRIVER_INDEX */
    /* @Trace: MemIf_SUD_MACRO_002 */
    #ifdef MEMIF_EA_DRIVER_INDEX
      /* @Trace: MemIf_SUD_FUNC_205 */
      /* Call Ea */
      statusMemIf = Ea_GetStatus();
    #endif /* MEMIF_EA_DRIVER_INDEX */
  /* @Trace: MemIf_SUD_MACRO_009 */
  #elif (MEMIF_ONE_DRIVER < MEMIF_NO_OF_DEVICES)
    statusMemIf = MEMIF_UNINIT;
    switch (DeviceIndex)
    {
      /* Call Fee */
      /* @Trace: MemIf_SUD_MACRO_003 */
      case MEMIF_FEE_DRIVER_INDEX:
        /* @Trace: MemIf_SUD_FUNC_204 */
        statusFee = Fee_GetStatus();
        statusMemIf = statusFee;
        break;
      /* Call Ea */
      /* @Trace: MemIf_SUD_MACRO_002 */
      case MEMIF_EA_DRIVER_INDEX:
        /* @Trace: MemIf_SUD_FUNC_206 */
        statusEa = Ea_GetStatus();
        statusMemIf = statusEa;
        break;
      case MEMIF_BROADCAST_ID:
        /* @Trace: MemIf_SUD_FUNC_207 */
        statusEa = Ea_GetStatus();
        statusFee = Fee_GetStatus();
        switch (statusEa)
        {
          case MEMIF_UNINIT:
            /* @Trace: MemIf_SUD_FUNC_208 */
            statusMemIf = MEMIF_UNINIT;
            break;
          case MEMIF_IDLE:
            /* @Trace: MemIf_SUD_FUNC_209 */
            statusMemIf = statusFee;
            break;
          case MEMIF_BUSY:
            if (MEMIF_UNINIT == statusFee)
            {
            /* @Trace: MemIf_SUD_FUNC_210 */
              statusMemIf = MEMIF_UNINIT;
            }
            else
            {
            /* @Trace: MemIf_SUD_FUNC_211 */
              statusMemIf = MEMIF_BUSY;
            }
            break;
          case MEMIF_BUSY_INTERNAL:
            if (MEMIF_UNINIT == statusFee)
            {
            /* @Trace: MemIf_SUD_FUNC_212 */
              statusMemIf = MEMIF_UNINIT;
            }
            else if (MEMIF_BUSY == statusFee)
            {
            /* @Trace: MemIf_SUD_FUNC_213 */
              statusMemIf = MEMIF_BUSY;
            }
            else
            {
            /* @Trace: MemIf_SUD_FUNC_214 */
              statusMemIf = MEMIF_BUSY_INTERNAL;
            }
            break;
          default:
            /* Do nothing */
            break;
        }
        break;
      default:
        /* @Trace: MemIf_SUD_MACRO_001 */
        #if (STD_ON == MEMIF_DEV_ERROR_DETECT)
          /* @Trace: MemIf_SUD_FUNC_202 */
          /* Invalid DeviceIndex, Report error to DET */
          (void) Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID,\
            MEMIF_GETSTATUS_SID, MEMIF_E_PARAM_DEVICE);
        #endif /* (STD_ON == MEMIF_DEV_ERROR_DETECT) */
        break;
    }
  #else
    statusMemIf = MEMIF_UNINIT;
  #endif /* (MEMIF_ONE_DRIVER > MEMIF_NO_OF_DEVICES) */

  /* @Trace: MemIf_SUD_FUNC_215 */
  return statusMemIf;
}

#define MEMIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : MemIf_GetJobResult                                    **
**                                                                            **
** Service ID         : 0x06                                                  **
**                                                                            **
** Description        : Invokes the "GetJobResult" function of the underlying **
**                      memory abstraction module selected by the parameter   **
**                      DeviceIndex                                           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : DeviceIndex : Index of memory abstraction modules     **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return Parameter   : jobResultType : Value of the called function of       **
**                                         the underlying module              **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s):None                               **
**                      Function(s) Invoked: Det_ReportError,                 **
**                                           Fee_GetJobResult,                **
**                                           Ea_GetJobResult                  **
*******************************************************************************/
#define MEMIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00392 SRS_MemHwAb_14022  SRS_MemHwAb_14020 SRS_MemHwAb_14022 */
/* @Trace: SRS_BSW_00337 SRS_BSW_00385      SRS_BSW_00386     SRS_SPAL_12448 */
/* @Trace: SRS_BSW_00384 SRS_MemHwAb_14019  SRS_MemHwAb_14020 SRS_MemHwAb_14021 SRS_SPAL_12078 */
FUNC(MemIf_JobResultType, MEMIF_CODE) MemIf_GetJobResult(\
  VAR(uint8, AUTOMATIC) DeviceIndex)
{
  VAR(MemIf_JobResultType, AUTOMATIC) jobResultType;

  /* @Trace: MemIf_SUD_MACRO_009 */
  #if (MEMIF_ONE_DRIVER == MEMIF_NO_OF_DEVICES)
    MEMIF_UNUSE(DeviceIndex);
    /* @Trace: MemIf_SUD_MACRO_003 */
    #ifdef MEMIF_FEE_DRIVER_INDEX
      /* @Trace: MemIf_SUD_FUNC_253 */
      /* Call Fee */
      jobResultType = Fee_GetJobResult();
    #endif /* MEMIF_FEE_DRIVER_INDEX */
    /* @Trace: MemIf_SUD_MACRO_002 */
    #ifdef MEMIF_EA_DRIVER_INDEX
      /* @Trace: MemIf_SUD_FUNC_255 */
      /* Call Ea */
      jobResultType = Ea_GetJobResult();
    #endif /* MEMIF_EA_DRIVER_INDEX */
  /* @Trace: MemIf_SUD_MACRO_009 */
  #elif (MEMIF_ONE_DRIVER < MEMIF_NO_OF_DEVICES)
    /* The default job */
    jobResultType = MEMIF_JOB_FAILED;
    /*
     * Check the passed DeviceIndex and call the underlying
     * GetJobResult API as applicable
     */
    switch (DeviceIndex)
    {
      /* Call Fee */
      /* @Trace: MemIf_SUD_MACRO_003 */
      case MEMIF_FEE_DRIVER_INDEX:
        /* @Trace: MemIf_SUD_FUNC_254 */
        jobResultType = Fee_GetJobResult();
        break;
      /* Call Ea */
      /* @Trace: MemIf_SUD_MACRO_002 */
      case MEMIF_EA_DRIVER_INDEX:
        /* @Trace: MemIf_SUD_FUNC_256 */
        jobResultType = Ea_GetJobResult();
        break;
      default:
        /* @Trace: MemIf_SUD_MACRO_001 */
        #if (STD_ON == MEMIF_DEV_ERROR_DETECT)
          /* @Trace: MemIf_SUD_FUNC_252 */
          /* Invalid DeviceIndex, Report error to DET */
          (void) Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID,\
            MEMIF_GETJOBRESULT_SID, MEMIF_E_PARAM_DEVICE);
        #endif /* (STD_ON == MEMIF_DEV_ERROR_DETECT) */
        break;
    }
  #else
    jobResultType = MEMIF_JOB_FAILED;
  #endif /* (MEMIF_ONE_DRIVER > MEMIF_NO_OF_DEVICES) */

  /* @Trace: MemIf_SUD_FUNC_257 */
  return(jobResultType);
}

#define MEMIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : MemIf_InvalidateBlock                                 **
**                                                                            **
** Service ID         : 0x07                                                  **
**                                                                            **
** Description        : Invokes the "InvalidateBlock" function of the         **
**                      underlying memory abstraction module selected by the  **
**                      parameter DeviceIndex                                 **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : DeviceIndex : Index of memory abstraction modules     **
**                      BlockNumber : Number of logical block, also denoting  **
**                                    start address of the block              **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return Parameter   : E_OK : The requested job has been accepted by         **
**                             the underlying module                          **
**                      E_NOT_OK: The requested job has not been accepted by  **
**                                the underlying module                       **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s):None                               **
**                      Function(s) Invoked: Det_ReportError,                 **
**                                           Fee_InvalidateBlock,             **
**                                           Ea_InvalidateBlock               **
*******************************************************************************/
#define MEMIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00369 SRS_MemHwAb_14022  SRS_MemHwAb_14028 SRS_MemHwAb_14020 */
/* @Trace: SRS_BSW_00337 SRS_BSW_00385      SRS_BSW_00386     SRS_SPAL_12448 */
/* @Trace: SRS_BSW_00384 SRS_MemHwAb_14019  SRS_MemHwAb_14021 SRS_SPAL_12078 */
FUNC(Std_ReturnType, MEMIF_CODE) MemIf_InvalidateBlock(\
  VAR(uint8, AUTOMATIC) DeviceIndex,\
  VAR(uint16, AUTOMATIC) BlockNumber)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* @Trace: MemIf_SUD_MACRO_009 */
  #if (MEMIF_ONE_DRIVER == MEMIF_NO_OF_DEVICES)
    MEMIF_UNUSE(DeviceIndex);
    /* @Trace: MemIf_SUD_MACRO_003 */
    #ifdef MEMIF_FEE_DRIVER_INDEX
      /* @Trace: MemIf_SUD_FUNC_303 */
      /* Call Fee */
      returnValue = Fee_InvalidateBlock(BlockNumber);
    #endif /* MEMIF_FEE_DRIVER_INDEX */
    /* @Trace: MemIf_SUD_MACRO_002 */
    #ifdef MEMIF_EA_DRIVER_INDEX
      /* @Trace: MemIf_SUD_FUNC_305 */
      /* Call Ea */
      returnValue = Ea_InvalidateBlock(BlockNumber);
    #endif /* MEMIF_EA_DRIVER_INDEX */
  /* @Trace: MemIf_SUD_MACRO_009 */
  #elif (MEMIF_ONE_DRIVER < MEMIF_NO_OF_DEVICES)
    returnValue = E_NOT_OK;
    /*
     * Check the passed DeviceIndex and call the underlying
     * InvalidateBlock API as applicable
     */
    switch (DeviceIndex)
    {
      /* Call Fee */
      /* @Trace: MemIf_SUD_MACRO_003 */
      case MEMIF_FEE_DRIVER_INDEX:
        /* @Trace: MemIf_SUD_FUNC_304 */
        returnValue = Fee_InvalidateBlock(BlockNumber);
        break;
      /* Call Ea */
      /* @Trace: MemIf_SUD_MACRO_002 */
      case MEMIF_EA_DRIVER_INDEX:
        /* @Trace: MemIf_SUD_FUNC_306 */
        returnValue = Ea_InvalidateBlock(BlockNumber);
        break;
      default:
        /* @Trace: MemIf_SUD_MACRO_001 */
        #if (STD_ON == MEMIF_DEV_ERROR_DETECT)
          /* @Trace: MemIf_SUD_FUNC_302 */
          /* Invalid DeviceIndex, Report error to DET */
          (void) Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID,\
            MEMIF_INVALIDATEBLOCK_SID, MEMIF_E_PARAM_DEVICE);
        #endif /* (STD_ON == MEMIF_DEV_ERROR_DETECT) */
        break;
    }
  #else
    returnValue = E_NOT_OK;
  #endif /* (MEMIF_ONE_DRIVER > MEMIF_NO_OF_DEVICES) */

  /* @Trace: MemIf_SUD_FUNC_307 */
  return(returnValue);
}

#define MEMIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : MemIf_EraseImmediateBlock                             **
**                                                                            **
** Service ID         : 0x09                                                  **
**                                                                            **
** Description        : Invokes the "EraseImmediateBlock" function of the     **
**                      underlying memory abstraction module selected by the  **
**                      parameter DeviceIndex                                 **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Non Reentrant                                         **
**                                                                            **
** Input Parameters   : DeviceIndex : Index of memory abstraction modules     **
**                      BlockNumber : Number of logical block, also denoting  **
**                                    start address of the block              **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : None                                                  **
**                                                                            **
** Return Parameter   : E_OK : The requested job has been accepted by         **
**                             the underlying module                          **
**                      E_NOT_OK: The requested job has not been accepted by  **
**                                the underlying module                       **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s):None                               **
**                      Function(s) Invoked: Det_ReportError,                 **
**                                           Fee_EraseImmediateBlock,         **
**                                           Ea_EraseImmediateBlock           **
*******************************************************************************/
#define MEMIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00369 SRS_MemHwAb_14022  SRS_MemHwAb_14032 SRS_MemHwAb_14020 */
/* @Trace: SRS_BSW_00337 SRS_BSW_00385      SRS_BSW_00386     SRS_SPAL_12448 SRS_SPAL_12078 */
FUNC(Std_ReturnType, MEMIF_CODE) MemIf_EraseImmediateBlock(\
  VAR(uint8, AUTOMATIC) DeviceIndex,VAR(uint16, AUTOMATIC) BlockNumber)
{
  VAR(Std_ReturnType, AUTOMATIC) returnValue;

  /* @Trace: MemIf_SUD_MACRO_009 */
  #if (MEMIF_ONE_DRIVER == MEMIF_NO_OF_DEVICES)
    MEMIF_UNUSE(DeviceIndex);
    /* @Trace: MemIf_SUD_MACRO_002 */
    #ifdef MEMIF_EA_DRIVER_INDEX
      /* @Trace: MemIf_SUD_FUNC_403 */
      /* Call Ea */
      returnValue = Ea_EraseImmediateBlock(BlockNumber);
    #endif /* MEMIF_EA_DRIVER_INDEX */
    /* @Trace: MemIf_SUD_MACRO_003 */
    #ifdef MEMIF_FEE_DRIVER_INDEX
      /* @Trace: MemIf_SUD_FUNC_405 */
      /* Call Fee */
      returnValue = Fee_EraseImmediateBlock(BlockNumber);
    #endif /* MEMIF_FEE_DRIVER_INDEX */
  /* @Trace: MemIf_SUD_MACRO_009 */
  #elif (MEMIF_ONE_DRIVER < MEMIF_NO_OF_DEVICES)
     returnValue = E_NOT_OK;
    /*
     * Check the passed DeviceIndex and call the underlying
     * EraseImmediateBlock API as applicable
     */
    switch(DeviceIndex)
    {
      /* Call Ea */
      /* @Trace: MemIf_SUD_MACRO_002 */
      case MEMIF_EA_DRIVER_INDEX:
        /* @Trace: MemIf_SUD_FUNC_404 */
        returnValue = Ea_EraseImmediateBlock(BlockNumber);
        break;
      /* Call Fee */
      /* @Trace: MemIf_SUD_MACRO_003 */
      case MEMIF_FEE_DRIVER_INDEX:
        /* @Trace: MemIf_SUD_FUNC_406 */
        returnValue = Fee_EraseImmediateBlock(BlockNumber);
        break;
      default:
        /* @Trace: MemIf_SUD_MACRO_001 */
        #if (STD_ON == MEMIF_DEV_ERROR_DETECT)
          /* @Trace: MemIf_SUD_FUNC_402 */
          /* Invalid DeviceIndex, Report error to DET */
          (void) Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID,\
            MEMIF_ERASEIMMEDIATEBLOCK_SID, MEMIF_E_PARAM_DEVICE);
        #endif /* (STD_ON == MEMIF_DEV_ERROR_DETECT) */
        break;
    }
  #else
    returnValue = E_NOT_OK;
  #endif /* (MEMIF_ONE_DRIVER > MEMIF_NO_OF_DEVICES) */

  /* @Trace: MemIf_SUD_FUNC_407 */
  return(returnValue);
}

#define MEMIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name      : MemIf_GetVersionInfo                                  **
**                                                                            **
** Service ID         : 0x08                                                  **
**                                                                            **
** Description        : Returns version information                           **
**                                                                            **
** Sync/Async         : Synchronous                                           **
**                                                                            **
** Re-entrancy        : Reentrant                                             **
**                                                                            **
** Input Parameters   : None                                                  **
**                                                                            **
** InOut parameter    : None                                                  **
**                                                                            **
** Output Parameters  : VersionInfoPtr : Pointer to standard version          **
**                                       information structure                **
**                                                                            **
** Return Parameter   : None                                                  **
**                                                                            **
** Preconditions      : None                                                  **
**                                                                            **
** Remarks            : Global Variable(s):None                               **
**                      Function(s) Invoked: Det_ReportError                  **
*******************************************************************************/
#define MEMIF_START_SEC_CODE
#include "MemMap.h"
/* @Trace: SRS_BSW_00407 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386 */
/* @Trace: MemIf_SUD_MACRO_010 MemIf_SUD_DATATYPE_002 */
/* Enable/Disable Version Information */
#if (STD_ON == MEMIF_VERSION_INFO_API)
  FUNC(void, MEMIF_CODE) MemIf_GetVersionInfo(\
    P2VAR(Std_VersionInfoType, AUTOMATIC, MEMIF_APPL_DATA) VersionInfoPtr)
  {
    /* @Trace: MemIf_SUD_MACRO_001 */
    /* Check status dev error detect */
    #if (STD_ON == MEMIF_DEV_ERROR_DETECT)
      if (NULL_PTR == VersionInfoPtr)
      {
        /* @Trace: MemIf_SUD_FUNC_351 */
        /* Invalid value of pointer, Report error to DET */
        (void) Det_ReportError(MEMIF_MODULE_ID, MEMIF_INSTANCE_ID,\
          MEMIF_GETVERSIONINFO_SID, MEMIF_E_PARAM_POINTER);
      }
      else
      {
    #endif /* (STD_ON == MEMIF_DEV_ERROR_DETECT) */
        /* @Trace: MemIf_SUD_FUNC_352 */
        /* Copy the vendor Id */
        /* polyspace-begin MISRA2012:D4.14 [Justified:Low] "VersionInfo will be checked before using" */
        VersionInfoPtr->vendorID = MEMIF_VENDOR_ID;
        /* Copy the module Id */
        VersionInfoPtr->moduleID = MEMIF_MODULE_ID;
        /* Copy Software Major Version */
        VersionInfoPtr->sw_major_version = MEMIF_SW_MAJOR_VERSION;
        /* Copy Software Minor Version */
        VersionInfoPtr->sw_minor_version = MEMIF_SW_MINOR_VERSION;
        /* Copy Software Patch Version */
        VersionInfoPtr->sw_patch_version = MEMIF_SW_PATCH_VERSION;
        /* polyspace-end MISRA2012:D4.14 */
    #if (STD_ON == MEMIF_DEV_ERROR_DETECT)
      }
    #endif /* (STD_ON == MEMIF_DEV_ERROR_DETECT) */
  }
#endif /* STD_ON == MEMIF_VERSION_INFO_API */

#define MEMIF_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
