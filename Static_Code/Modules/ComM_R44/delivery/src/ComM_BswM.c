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
**  SRC-MODULE: ComM_BswM.c                                                   **
**                                                                            **
**  TARGET    : ALL                                                           **
**                                                                            **
**  PRODUCT   : AUTOSAR COM Manager                                           **
**                                                                            **
**  PURPOSE   : Provision of ComM BswM Indication APIs                        **
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
** 1.1.0.0        12-Aug-2022         ThuanVT          R44-Redmine #29733     **
** 1.0.4.1        20-Jun-2022         SMKwon           CP44-115               **
** 1.0.1          27-Dec-2020         DatNXT           R44-Redmine #14801     **
** 1.0.0          15-Dec-2020         JsLim            Initial Version        **
 ******************************************************************************/

/*******************************************************************************
**                      Include Section                                       **
*******************************************************************************/
#include "ComM_Internal.h"
/* @Trace: ComM_SUD_MACRO_002 */
/* @Trace: SRS_ComM_AR_00217 SRS_ComM_AR_00217 SRS_ComM_AR_00223
 * SRS_ComM_AR_00224 SRS_ComM_AR_00226 SRS_ComM_AR_00227 SRS_ComM_AR_00228
 * SRS_ComM_AR_00229 SRS_ComM_AR_00230 SRS_ComM_AR_00231 SRS_ComM_AR_00233
 * SRS_ComM_AR_00234 SRS_ComM_AR_00237 SRS_ComM_AR_00238 SRS_ComM_AR_00239 
 */
/* @Trace: ComM_SUD_MACRO_005   */
#include "ComM_Ram.h"
#include "ComM_BswM.h"
#include "BswM_ComM.h"
#include "SchM_ComM.h"

/*******************************************************************************
**                      Global Data Types                                     **
*******************************************************************************/

/*******************************************************************************
**                      Function Definitions                                  **
*******************************************************************************/

/*******************************************************************************
** Function Name        : ComM_CommunicationAllowed                           **
**                                                                            **
** Service ID           : 0x35                                                **
**                                                                            **
** Description          : Indicates ComM when communication is allowed        **
**                                                                            **
** Sync/Async           : Asynchronous                                        **
**                                                                            **
** Reentrancy           : Non Reentrant                                       **
**                                                                            **
** Input Parameters     : Channel, Allowed                                    **
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
**                        ComM_CommunicationAllowedFlag[],                    **
**                        ComM_ChannelMapArray[]                              **
**                                                                            **
**                        Function(s) invoked    :                            **
**                        ComM_ChannelDETCheck()                              **
*******************************************************************************/
/* @Trace: SRS_BSW_00323 SRS_BSW_00327 SRS_BSW_00337 SRS_BSW_00385 SRS_BSW_00386
 * SRS_BSW_00406 SRS_ComM_AR_00008 SRS_ComM_AR_00009 SRS_ComM_AR_00067 SRS_ComM_AR_00180
 */
#define COMM_START_SEC_CODE
#include "MemMap.h"
FUNC(void, COMM_CODE)
  ComM_CommunicationAllowed(NetworkHandleType Channel, boolean Allowed)
{
  /* @Trace: ComM_SUD_API_092 */
  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  /* Standard return type variable */
  Std_ReturnType returnValue;
  #endif

  /* Variable to store channel */
  NetworkHandleType handleChnlIndex;

  #if (COMM_DEV_ERROR_DETECT == STD_ON)
  /* Check if the channel is valid or not */
  returnValue = ComM_ChannelDETCheck(Channel, COMM_COMMUNICATIONALLOWED_SID);

  /* Check, if no development error occurred */
  if (E_OK == returnValue)
  #endif
  {
    /* @Trace: ComM_SUD_API_093 */
    #if (COMM_CHANNEL_SEQUENTIAL == STD_OFF)
    /* Get the channel id from the mapping array */
    handleChnlIndex = ComM_ChannelMapArray[Channel]; /* polyspace MISRA-C3:D4.14 [Not a defect:Low] "Channel value and ComM_ChannelMapArray are generated by Tcode and has checked manual and it is not having any impact" */
    #else
    /* Channel Id is updated into local variable */
    handleChnlIndex = Channel;
    #endif

    if (TRUE == Allowed)
    {
      /* @Trace: ComM_SUD_API_094 */
      /* Variable stored if communication is allowed for ComM */
      /* polyspace +4 DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      ComM_CommunicationAllowedFlag[handleChnlIndex] = COMM_TRUE; /* polyspace RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    }
    else
    {
      /* @Trace: ComM_SUD_API_095 */
      /* Variable stored if communication is not allowed for ComM */
      /* polyspace +4 DEFECT:OUT_BOUND_ARRAY [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +3 MISRA2012:D4.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +2 MISRA2012:18.1 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      /* polyspace +1 MISRA2012:D4.14 [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
      ComM_CommunicationAllowedFlag[handleChnlIndex] = COMM_FALSE; /* polyspace RTE:OBAI [Not a defect:Low] "This index verified by GenTool. It is not having any impact" */
    }
  } /* End of if (returnValue == E_OK) */
} /* End of ComM_CommunicationAllowed */

#define COMM_STOP_SEC_CODE
#include "MemMap.h"

/*******************************************************************************
**                      End of File                                           **
*******************************************************************************/
