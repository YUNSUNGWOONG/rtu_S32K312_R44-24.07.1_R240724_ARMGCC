/* polyspace +1 MISRA2012:1.1 [Not a defect:Low] "This rule is manually checked and has no impact." */
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
**  SRC-MODULE: ComM_Dcm.c                                                    **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
**                                                                            **
**  PURPOSE   : Provision of ComM Dcm Indication APIs                         **
**                                                                            **
**  PLATFORM DEPENDANT [yes/no]: no                                           **
**                                                                            **
**  TO BE CHANGED BY USER [yes/no]: no                                        **
**                                                                            **
*******************************************************************************/

/*******************************************************************************
**                      Revision History                                      **
********************************************************************************
** Revision       Date                By               Description            **
********************************************************************************
** 1.1.7_HF1      04-Mar-2024         Minuk Kim        CP44-3875              **
** 1.1.0.0        12-Aug-2022         ThuanVT          R44-Redmine #29733     **
** 1.0.4.1        20-Jun-2022         SMKwon           CP44-115               **
** 1.0.4          29-Apr-2022         ThuanVT          R44-Redmine #25641     **
** 1.0.1          27-Dec-2020         DatNXT           R44-Redmine #14801     **
** 1.0.0          15-Dec-2020         JsLim            Initial Version        **
*******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
/* @Trace: ComM_SUD_MACRO_003 */
#include "ComM.h"
#include "ComM_Dcm.h"
/* @Trace: ComM_SUD_MACRO_002 */
/* @Trace: SRS_ComM_AR_00217 SRS_ComM_AR_00217 SRS_ComM_AR_00223
 * SRS_ComM_AR_00224 SRS_ComM_AR_00226 SRS_ComM_AR_00227 SRS_ComM_AR_00228
 * SRS_ComM_AR_00229 SRS_ComM_AR_00230 SRS_ComM_AR_00231 SRS_ComM_AR_00233
 * SRS_ComM_AR_00234 SRS_ComM_AR_00237 SRS_ComM_AR_00238 SRS_ComM_AR_00239 
 */
/* @Trace: ComM_SUD_MACRO_005   */
#include "ComM_Ram.h"
#include "SchM_ComM.h"
#include "ComM_Internal.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : ComM_DCM_ActiveDiagnostic                           **
**                                                                            **
** Service ID           : 0x1f                                                **
**                                                                            **
** Description          : Indication of Active Diagnostic by the DCM          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : Channel                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : ComM shall be Initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_DcmActiveDiagnostic[],                         **
**                        ComM_DcmInActiveDiagnostic[],                       **
**                        ComM_ChannelMapArray[], ComM_TimeCnt[]              **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck(),                             **
**                        SchM_Enter_ComM_DCM_DIAGNOSTIC_PROTECTION(),        **
**                        SchM_Exit_ComM_DCM_DIAGNOSTIC_PROTECTION()          **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406 SRS_ComM_AR_00005 SRS_ComM_AR_00181 SRS_ComM_AR_00154
 */
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE)
  ComM_DCM_ActiveDiagnostic(NetworkHandleType Channel)
{
  /* @Trace: ComM_SUD_API_096 */
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Standard return type variable */
  Std_ReturnType returnValue;
  #endif

  /* Variable to store channel */
  NetworkHandleType handleChnlIndex;
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check if the channel is valid or not */
  returnValue = ComM_ChannelDETCheck(Channel, COMM_DCM_ACTIVEDIAGNOSTIC_SID);

  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif
  {
    /* @Trace: ComM_SUD_API_097 */
    /* Check If Binary Search Is Enabled*/
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
    /* Get the channel id from the mapping array */
    handleChnlIndex = ComM_ChannelMapArray[Channel]; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "Channel value and ComM_ChannelMapArray are generated by Tcode and has checked manual and it is not having any impact" */
    #else
    /* Channel Id is updated into local variable */
    handleChnlIndex = Channel;
    #endif

    /* Enter Data Protection */
    SchM_Enter_ComM_DCM_DIAGNOSTIC_PROTECTION();

    /* Update Status of Global Variable */
    /* polyspace +4 DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    ComM_DcmActiveDiagnostic[handleChnlIndex] = COMM_TRUE; /* polyspace RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    ComM_DcmInactiveDiagnostic[handleChnlIndex] = COMM_FALSE;

    /* Exit Data Protection */
    #if ((COMM_LIGHT_NMVARIANT_SUPPORT == STD_ON) ||\
      (COMM_NONE_NMVARIANT_SUPPORT == STD_ON))

    /* Start the Min amount of duration in full Communication counter */
    ComM_TimeCnt[handleChnlIndex] = (ComM_TimeType)COMM_ZERO;
    #endif
    SchM_Exit_ComM_DCM_DIAGNOSTIC_PROTECTION();
  }
} /* End of ComM_DCM_ActiveDiagnostic */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
** Function Name        : ComM_DCM_InactiveDiagnostic                         **
**                                                                            **
** Service ID           : 0x20                                                **
**                                                                            **
** Description          : Indication of Inactive Diagnostic                   **
**                        by the DCM                                          **
**                                                                            **
** Sync/Async           : Synchronous                                         **
**                                                                            **
** Reentrancy           : Reentrant                                           **
**                                                                            **
** Input Parameters     : Channel                                             **
**                                                                            **
** InOut Parameters     : None                                                **
**                                                                            **
** Output Parameters    : None                                                **
**                                                                            **
** Return parameter     : None                                                **
**                                                                            **
** Preconditions        : ComM shall be Initialized                           **
**                                                                            **
** Remarks              : Global Variable(s)     :                            **
**                        ComM_ChannelMapArray[],                             **
**                        ComM_DcmActiveDiagnostic[],                         **
**                        ComM_DcmInactiveDiagnostic[]                        **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck()                              **
**                        SchM_Enter_ComM_DCM_DIAGNOSTIC_PROTECTION()         **
**                        SchM_Exit_ComM_DCM_DIAGNOSTIC_PROTECTION()          **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406 SRS_ComM_AR_00182
 */
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE)
ComM_DCM_InactiveDiagnostic(NetworkHandleType Channel)
{
  /* @Trace: ComM_SUD_API_098 */
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Standard return type variable */
  Std_ReturnType returnValue;
  #endif

  /* Variable to store channel */
  NetworkHandleType handleChnlIndex;
  #if (COMM_DEV_ERROR_DETECT == STD_ON)

  /* Check if the channel is valid or not */
  returnValue = ComM_ChannelDETCheck(Channel, COMM_DCM_INACTIVEDIAGNOSTIC_SID);

  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif
  {
    /* @Trace: ComM_SUD_API_099 */
    /* Check If Binary Search Is Enabled*/
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
    /* Get the channel id from the mapping array */
    handleChnlIndex = ComM_ChannelMapArray[Channel]; /* polyspace MISRA2012:D4.14 [Not a defect:Low] "Channel value and ComM_ChannelMapArray are generated by Tcode and has checked manual and it is not having any impact" */
    #else
    /* Channel Id is updated into local variable */
    handleChnlIndex = Channel;
    #endif

    /* Enter Data Protection */
    SchM_Enter_ComM_DCM_DIAGNOSTIC_PROTECTION();

    /* Update Status of Global Variable */
    /* polyspace +5 DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +4 RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +2 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    if (ComM_DcmActiveDiagnostic[handleChnlIndex] == COMM_TRUE)
    {
      /* @Trace: ComM_SUD_API_734 */
      ComM_DcmInactiveDiagnostic[handleChnlIndex] = COMM_TRUE;
    }
    else
    {
      /* @Trace: ComM_SUD_API_735 */
      ComM_DcmInactiveDiagnostic[handleChnlIndex] = COMM_FALSE;
    }

    /* Exit Data Protection */
    SchM_Exit_ComM_DCM_DIAGNOSTIC_PROTECTION();
  }
} /* End of ComM_DCM_InactiveDiagnostic */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/

