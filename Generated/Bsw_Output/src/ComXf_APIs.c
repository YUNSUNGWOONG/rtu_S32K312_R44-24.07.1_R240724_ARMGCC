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
**  Generate On : The time-stamp is removed                                   **
**                                                                            **
**  SRC-MODULE:           ComXf_APIs.c                                        **
**                                                                            **
**  PRODUCT   :           AUTOSAR COM Based Transformer Module                **
**                                                                            **
**  PURPOSE   :           This file contain internal macros, externs etc.     **
**                        API's.                                              **
**                                                                            **
**  HARDWARE DEPENDANT [Yes/No]: No                                           **
**                                                                            **
**  AUTOSAR RELEASE:  4.4.0                                                   **
*******************************************************************************/

/*******************************************************************************
**                      Generation Tool Information                           **
********************************************************************************
**  FrameWork  Version: 1.1.5                                                 **
**                                                                            **
**  Module Version: 1.0.11.1                                                   **
**                                                                            **
**  Change History: Refer log file (use -l option to generate log file)       **
**                                                                            ** 
*******************************************************************************/

/*******************************************************************************
**              PRE-JUSTIFICATION BEGIN (MISRA RULE CHECKER)                  **
*******************************************************************************/
/* polyspace-begin MISRA2012:20.1 [Not a defect:Low] "see SWS_MemMap_00003 of AUTOSAR" */  
/* polyspace-begin MISRA2012:D4.14 [Justified:Low] "The validity of all external parameters has checked" */ 
/* polyspace-begin MISRA2012:5.1 [Justified:Low] "This violation depends naming, that is defined by system configuration" */
/* polyspace-begin MISRA2012:11.3 [Justified:Low] "The dataElement address is cast to a pointer, that point to an object has size type is equal with dataElement size type to get the correct value in memory" */
/* polyspace-begin MISRA2012:D4.1 [Justified:Low] "The return value of called function and the result object(sub-element of dataElement) are same type. The conversion from greater data type to small data type in this case is needed to get the correct the return value." */  
/* polyspace-begin RTE:OVFL [Justified:Low] "The return value of called function and the result object(sub-element of dataElement) are same type. The conversion from greater data type to small data type in this case is needed to get the correct the return value." */

/*******************************************************************************
**                            Function Declaration                            **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: SafeComXf_SUD_FILE_001 */
/*include for ComXf.h*/
#include "ComXf.h"
/*include for ComXf_APIs.h*/
#include "ComXf_APIs.h"
/*include for ComXf_Lib.h*/
#include "ComXf_Lib.h"
#if (COMXF_PRECOMPILE_CONFIG == STD_OFF)
/*include for ComXf_PbCfg.h*/
#include "ComXf_PbCfg.h"
#endif /*End of (COMXF_PRECOMPILE_CONFIG == STD_OFF)*/



/*=============================================================================*
** Function Name        : ComXf_Init                                          **
**                                                                            **
** Service ID           : 0x01                                                **
**                                                                            **
** Description          : This service initializes the transformer for the    **
**                        further processing.                                 **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : config                                              **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : void                                                **
**                                                                            **
** Preconditions        : No Preconditions                                    **
**                                                                            **
** Remarks              : Global Variable(s)  : ComXf_InitStatus              **
**                        Function(s) invoked : None                          **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_BSW_00407 SRS_BSW_00411 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(void, COMXF_CODE) ComXf_Init(
  P2CONST(ComXf_ConfigType, AUTOMATIC, COMXF_APPL_CONST) config)
{
  #if (COMXF_PRECOMPILE_CONFIG == STD_OFF)
  VAR(uint8, AUTOMATIC) index;
  #endif
  
  /* @Trace: BEGIN SafeComXf_SUD_API_001 */
#if (COMXF_PRECOMPILE_CONFIG == STD_ON)
  if ((config) == NULL_PTR) {
  	/* Store module initialization value into global */
  	ComXf_InitStatus = (boolean)COMXF_CS_INIT;
  }
#else
  if (NULL_PTR == config)
  {
    #if (COMXF_DEV_ERROR_DETECT == STD_ON)
    /* Report to DET SWS_E2EXf_00144 */
    (void)Det_ReportError(COMXF_MODULE_ID, COMXF_INSTANCE_ID, \
      COMXF_INIT_SERVICE_ID, COMXF_E_PARAM_POINTER);
    #endif /* End of (COMXF_DEV_ERROR_DETECT == STD_ON) */
  }
  else
  {
        /* Store module initialization value into global */
        ComXf_InitStatus = (boolean)COMXF_CS_INIT;

        /* Break for loop */
        break;
      }
    }
  }
#endif /*End of #if (COMXF_PRECOMPILE_CONFIG == STD_ON)*/

}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"


/*=============================================================================*
** Service Name         : ComXf_Com_ComISignalGroup_MsgGr_E2E_FD_CAN1_TCU_01_10ms_P11**
**                                                                            **
** Service ID           : 0x03                                                **
**                                                                            **
** Description          : This function transforms a Sender/Receiver          **
**                        Transformer communication using the serialization   **
**                        of COM Based It takes the data element as input and **
**                        outputs an uint8 array containing the serialized    **
**                        data called transformer module                      **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : dataElement                                         **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : buffer, bufferLength                                **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
** Remarks              : Global Variable(s)  : ComXf_InitStatus              **
**                                              ComXf_Kast_SigPackInfo        **
**                        Function(s) invoked :                               **
**                                              ComXf_Pack1ByteNotAlign       **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_BSW_00337 SRS_Xfrm_00201 SRS_BSW_00159 SRS_Xfrm_00202 SRS_BSW_00441 */
/* @Trace: SafeComXf_SUD_DATATYPE_008 SafeComXf_SUD_MACRO_007 SafeComXf_SUD_DATATYPE_001 */


#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(uint8, COMXF_CODE) ComXf_Com_ComISignalGroup_MsgGr_E2E_FD_CAN1_TCU_01_10ms_P11(
  P2VAR(uint8, AUTOMATIC, COMXF_APPL_DATA) buffer,
  P2VAR(uint32, AUTOMATIC, COMXF_APPL_DATA) bufferLength,
  P2CONST(MsgGr_E2E_FD_CAN1_TCU_01_10ms_P11, AUTOMATIC, COMXF_APPL_CONST)
  dataElement)
{
  VAR(uint8, AUTOMATIC) returnStatus;
  VAR(uint8, AUTOMATIC) devError;
  /* Pointer to signal for fetching signal properties */
  P2CONST(ComXf_PackSigType, AUTOMATIC, COMXF_APPL_CONST) packSigType;
  devError = (uint8) E_OK;
  returnStatus = (uint8) E_OK;

  if ((boolean) COMXF_CS_DEINIT == ComXf_InitStatus)
  {
    /* @Trace: SafeComXf_SUD_API_005 */
    devError = (uint8) COMXF_E_UNINIT;
  }
  else if (NULL_PTR == buffer)
  {
    /* @Trace: SafeComXf_SUD_API_006 */
    devError = (uint8) COMXF_E_PARAM_POINTER;
  }
  else if (NULL_PTR == bufferLength)
  {
    /* @Trace: SafeComXf_SUD_API_007 */
    devError = (uint8) COMXF_E_PARAM_POINTER;
  }
  else if (NULL_PTR == dataElement)
  {
    /* @Trace: SafeComXf_SUD_API_008 */
    devError = (uint8) COMXF_E_PARAM_POINTER;
  }
  else
  {
    /* Do nothing */
    ;
  }

  if(E_OK != devError){
  /* @Trace: SafeComXf_SUD_API_017 */
#if (STD_ON == COMXF_DEV_ERROR_DETECT)
    (void)Det_ReportError(COMXF_MODULE_ID, COMXF_INSTANCE_ID,
      COMXF_TRANSFORMER_SERVICE_ID, devError);
#endif/*#if (STD_ON == COMXF_DEV_ERROR_DETECT)*/
    returnStatus = (uint8) E_SER_GENERIC_ERROR;
  }

  if (E_OK == returnStatus)
  {
    /* @Trace: SafeComXf_SUD_API_009 */
    ComXf_FillUnusedBufferArea(&buffer[0], 8, 0x0);
    packSigType = &ComXf_Kast_SigPackInfo[ComXf_FD_CAN1_TCU_01_10ms_P11_TCU_EngRpmDisSta_Tx_P11];

    ComXf_Pack1ByteNotAlign(&buffer[3], packSigType, (uint8)dataElement->TCU_EngRpmDisSta_Tx_P11);

    *bufferLength = 8;
  }

  return returnStatus;
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"


/*=============================================================================*
** Service Name         : ComXf_Inv_Com_ComISignalGroup_MsgGr_E2E_FD_CAN1_BSD_01_50ms_P11**
**                                                                            **
** Service ID           : 0x04                                                **
**                                                                            **
** Description          : This function deserializes a Sender/Receiver        **
**                        communication using the deserialization of COM      **
**                        Based Transformer. It takes the uint8 array as      **
**                        containing the serialized data as input and outputs **
**                        the original data element which will be passed to   **
**                        the Rte.                                            **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Re-entrancy          : Reentrant                                           **
**                                                                            **
** Input Parameters     : buffer, bufferLength                                **
**                                                                            **
** InOut parameter      : None                                                **
**                                                                            **
** Output Parameters    : dataElement                                         **
**                                                                            **
** Return parameter     : uint8                                               **
**                                                                            **
** Preconditions        : ComXf_Init should be called                         **
**                                                                            **
** Remarks              : Global Variable(s)  : ComXf_InitStatus              **
**                                              ComXf_Kast_SigUnPackInfo      **
**                        Function(s) invoked :                               **
**                                              ComXf_UnPack1ByteNotAlign     **
**                                                                            **
**============================================================================*/

/* @Trace: SRS_BSW_00337 SRS_Xfrm_00201 SRS_BSW_00159 SRS_Xfrm_00202 SRS_BSW_00441 */
/* @Trace: SafeComXf_SUD_DATATYPE_008 SafeComXf_SUD_MACRO_007 SafeComXf_SUD_DATATYPE_001 */

#define COMXF_START_SEC_CODE_ASIL_D
#include "MemMap.h"
FUNC(uint8, COMXF_CODE) ComXf_Inv_Com_ComISignalGroup_MsgGr_E2E_FD_CAN1_BSD_01_50ms_P11(
  P2CONST(uint8, AUTOMATIC, COMXF_APPL_CONST) buffer,
  VAR(uint32, AUTOMATIC) bufferLength,
  P2VAR(MsgGr_E2E_FD_CAN1_BSD_01_50ms_P11, AUTOMATIC, COMXF_APPL_DATA)
  dataElement)
{
  VAR(uint8, AUTOMATIC) returnStatus;
  VAR(uint8, AUTOMATIC) devError;

  /* Pointer to signal for fetching signal properties */
  P2CONST(ComXf_UnPackSigType, AUTOMATIC, COMXF_APPL_CONST) unPackSigType;

  devError = (uint8) E_OK;
  returnStatus = (uint8) E_OK;

  if ((boolean) COMXF_CS_DEINIT == ComXf_InitStatus)
  { 
    /* @Trace: SafeComXf_SUD_API_010 */
    devError = (uint8) COMXF_E_UNINIT;
  }
  else if (NULL_PTR == buffer)
  {
    /* @Trace: SafeComXf_SUD_API_011 */
    devError = (uint8) COMXF_E_PARAM_POINTER;
  }
  else if (0 == bufferLength)
  {
    /* @Trace: SafeComXf_SUD_API_012 */
    devError = (uint8) COMXF_E_PARAM;
  }
  else if (NULL_PTR == dataElement)
  {
    /* @Trace: SafeComXf_SUD_API_013 */
    devError = (uint8) COMXF_E_PARAM_POINTER;
  }
  else
  {
    /* Do nothing */
    ;
  }

  if ((NULL_PTR == buffer) && (0 == bufferLength))
  {
    /* @Trace: SafeComXf_SUD_API_014 */
    devError = (uint8) E_OK;
    returnStatus = (uint8) E_NO_DATA;
  }

  if(E_OK != devError){
  /* @Trace: SafeComXf_SUD_API_018 */
#if (STD_ON == COMXF_DEV_ERROR_DETECT)
    (void)Det_ReportError(COMXF_MODULE_ID, COMXF_INSTANCE_ID,
      COMXF_INV_TRANSFORMER_SERVICE_ID, devError);
#endif/*#if (STD_ON == COMXF_DEV_ERROR_DETECT)*/
    returnStatus = (uint8) E_SER_GENERIC_ERROR;
  }

  if (E_OK == returnStatus)
  {
    /* @Trace: SafeComXf_SUD_API_015 */
    unPackSigType = &ComXf_Kast_SigUnPackInfo[ComXf_FD_CAN1_BSD_01_50ms_P11_TCU_EngRpmDisSta_Rx_P11];

    dataElement->TCU_EngRpmDisSta_Rx_P11 = (uint8)ComXf_UnPack1ByteNotAlign(&buffer[3], unPackSigType);

  }

  return returnStatus;
}
#define COMXF_STOP_SEC_CODE_ASIL_D
#include "MemMap.h"
  

/*******************************************************************************
**               PRE-JUSTIFICATION END (MISRA RULE CHECKER)                   **
*******************************************************************************/
/* polyspace-end MISRA2012:20.1 */
/* polyspace-end MISRA2012:11.3 */
/* polyspace-end MISRA2012:5.1 */ 
/* polyspace-end MISRA2012:D4.14*/
/* polyspace-end MISRA2012:D4.1*/
/* polyspace-end RTE:OVFL */

/*******************************************************************************
*                       End of File                                            *
*******************************************************************************/
